# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# CMakeLists.txt

cmake_minimum_required(VERSION 3.18)

project(
  Json-Performance
  VERSION 1.0.0
  LANGUAGES CXX
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install/)

option(JP_SIMDJSON_REFLECTION "Benchmark simdjson's C++26 static-reflection API when the compiler provides P2996 reflection" ON)
if(JP_SIMDJSON_REFLECTION AND NOT MSVC)
  include(CheckCXXSourceCompiles)
  set(CMAKE_REQUIRED_FLAGS "-std=c++26 -freflection")
  check_cxx_source_compiles("
#include <meta>
#if !defined(__cpp_impl_reflection) || !defined(__cpp_lib_reflection) || !defined(__cpp_expansion_statements) || !defined(__cpp_lib_define_static)
#error static reflection unavailable
#endif
int main() { return 0; }
" JP_HAS_STATIC_REFLECTION)
  unset(CMAKE_REQUIRED_FLAGS)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
if(JP_HAS_STATIC_REFLECTION)
  set(CMAKE_CXX_STANDARD 26)
  add_compile_options(-freflection)
else()
  set(CMAKE_CXX_STANDARD 23)
endif()

include(FetchContent)
include(GetCommitHash.cmake)

FetchContent_Declare(
  jsonifier
  GIT_REPOSITORY https://github.com/nihilai-collective/Jsonifier.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(jsonifier)
getCommitHash(${jsonifier_SOURCE_DIR} JSONIFIER_COMMIT_HASH)

FetchContent_Declare(
  glaze
  GIT_REPOSITORY https://github.com/stephenberry/glaze.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glaze)
getCommitHash(${glaze_SOURCE_DIR} GLAZE_COMMIT_HASH)

FetchContent_Declare(
  benchmarksuite
  GIT_REPOSITORY https://github.com/nihilai-collective/benchmarksuite.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(benchmarksuite)
getCommitHash(${benchmarksuite_SOURCE_DIR} BNCH_SWT_COMMIT_HASH)

set(SIMDJSON_DEVELOPMENT_CHECKS OFF CACHE BOOL "" FORCE)
set(SIMDJSON_SKIPUTF8VALIDATION OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  simdjson
  GIT_REPOSITORY https://github.com/simdjson/simdjson.git
  GIT_TAG master
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(simdjson)
getCommitHash(${simdjson_SOURCE_DIR} SIMDJSON_COMMIT_HASH)
get_target_property(_sj_iface simdjson INTERFACE_COMPILE_DEFINITIONS)
if(_sj_iface)
    list(FILTER _sj_iface EXCLUDE REGEX "^SIMDJSON_DEVELOPMENT_CHECKS")
    set_target_properties(simdjson PROPERTIES INTERFACE_COMPILE_DEFINITIONS "${_sj_iface}")
endif()

get_target_property(_sj_priv simdjson COMPILE_DEFINITIONS)
if(_sj_priv)
    list(FILTER _sj_priv EXCLUDE REGEX "^SIMDJSON_DEVELOPMENT_CHECKS")
    set_target_properties(simdjson PROPERTIES COMPILE_DEFINITIONS "${_sj_priv}")
endif()

add_library(simdjson-stage-1 STATIC ${simdjson_SOURCE_DIR}/src/simdjson.cpp)
target_include_directories(
    simdjson-stage-1
    PUBLIC ${simdjson_SOURCE_DIR}/include
    PRIVATE ${simdjson_SOURCE_DIR}/src
)
get_target_property(_sj_link simdjson INTERFACE_LINK_LIBRARIES)
if(_sj_link)
    find_package(Threads REQUIRED)
    target_link_libraries(simdjson-stage-1 PUBLIC ${_sj_link})
endif()
get_target_property(_sj_iface simdjson INTERFACE_COMPILE_DEFINITIONS)
if(_sj_iface)
    target_compile_definitions(simdjson-stage-1 PUBLIC ${_sj_iface})
endif()
target_compile_definitions(simdjson-stage-1 PUBLIC SIMDJSON_UTF8VALIDATION=0)

set(JSON_PERFORMANCE_MSVC_COMPILER_OPTIONS
    /bigobj
    $<$<CONFIG:RELEASE>:/O2> /arch:AVX2 /GL /Oi /Ot
    /Zc:preprocessor /EHsc /GS-
)

set(JSON_PERFORMANCE_CLANG_COMPILER_OPTIONS
    -O3 -march=native
    -funroll-loops -fomit-frame-pointer
    -flto=thin -finline-functions
    -ffunction-sections
    -fdata-sections
)

set(JSON_PERFORMANCE_MSVC_LINKER_OPTIONS
    /LTCG 
    /OPT:REF 
    /OPT:ICF 
    /INCREMENTAL:NO
)

set(JSON_PERFORMANCE_APPLE_CLANG_COMPILER_OPTIONS
    ${JSON_PERFORMANCE_CLANG_COMPILER_OPTIONS}
)

if(APPLE)
    set(JSON_PERFORMANCE_GCC_LTO)
else()
    set(JSON_PERFORMANCE_GCC_LTO -flto=auto)
endif()

set(JSON_PERFORMANCE_GCC_COMPILER_OPTIONS
    -O3 -march=native
    -funroll-loops -fomit-frame-pointer
    ${JSON_PERFORMANCE_GCC_LTO}
    -falign-functions=64
    -ffunction-sections
    -fdata-sections
)

set(JSON_PERFORMANCE_GCC_VECTORIZE_OPTIONS
    -fvect-cost-model=unlimited
    -falign-loops=64
)

function(json_performance_add_harness target_name harness_dir harness_name)
    cmake_parse_arguments(PARSE_ARGV 3 harness "" "" "LIBRARIES;DEFINITIONS;GCC_OPTIONS")

    add_executable(
      ${target_name}
      ./${harness_dir}source/main.cpp
    )

    target_include_directories(
        ${target_name} PUBLIC
        "./${harness_dir}include"
    )

    target_compile_options(
        ${target_name} PUBLIC
        $<$<CXX_COMPILER_ID:Clang>:${JSON_PERFORMANCE_CLANG_COMPILER_OPTIONS}>
        $<$<CXX_COMPILER_ID:AppleClang>:${JSON_PERFORMANCE_APPLE_CLANG_COMPILER_OPTIONS}>
        $<$<CXX_COMPILER_ID:GNU>:${JSON_PERFORMANCE_GCC_COMPILER_OPTIONS};${harness_GCC_OPTIONS}>
        $<$<CXX_COMPILER_ID:MSVC>:${JSON_PERFORMANCE_MSVC_COMPILER_OPTIONS}>
    )

    target_link_options(
        ${target_name} PUBLIC
        $<$<AND:$<CXX_COMPILER_ID:Clang>,$<NOT:$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>>:-flto=thin;-fuse-ld=lld;-Wl,-O2;-Wl,--gc-sections;-Wl,-z,now>
        $<$<AND:$<CXX_COMPILER_ID:Clang>,$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>:-Wl,-dead_strip>
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<NOT:$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>>:${JSON_PERFORMANCE_GCC_LTO};-Wl,-O2;-Wl,--gc-sections;-Wl,-z,now>
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>:-Wl,-dead_strip>
        $<$<AND:$<CXX_COMPILER_ID:AppleClang>,$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>:-Wl,-dead_strip>
        $<$<CXX_COMPILER_ID:MSVC>:${JSON_PERFORMANCE_MSVC_LINKER_OPTIONS}>
    )

    target_link_libraries(
    	${target_name} PUBLIC 
    	Jsonifier::Jsonifier benchmarksuite::benchmarksuite ${harness_LIBRARIES}
    )

    if (WIN32)
    	install(
    		FILES 
    		$<TARGET_PDB_FILE:${target_name}>
    		DESTINATION $<IF:$<CONFIG:Debug>,bin,bin>
    		OPTIONAL
    	)
    endif()

    target_compile_definitions(
    	${target_name} PUBLIC 
    	"BASE_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}\""
    	"JP_HARNESS_NAME=\"${harness_name}\""
    	"JSONIFIER_COMMIT=\"${JSONIFIER_COMMIT_HASH}\""
    	"SIMDJSON_COMMIT=\"${SIMDJSON_COMMIT_HASH}\""
        "BNCH_SWT_COMMIT=\"${BNCH_SWT_COMMIT_HASH}\""
    	"OPERATING_SYSTEM_NAME=\"${CMAKE_SYSTEM_NAME}\""
    	"OPERATING_SYSTEM_VERSION=\"${CMAKE_SYSTEM_VERSION}\""
    	"COMPILER_ID=\"${CMAKE_CXX_COMPILER_ID}\""
    	"COMPILER_VERSION=\"${CMAKE_CXX_COMPILER_VERSION}\""
        JP_CI_RUN=$<BOOL:${JP_CI_RUN}>
        ${harness_DEFINITIONS}
    )

    install(
    	FILES 
    	$<TARGET_FILE:${target_name}>
    	DESTINATION $<IF:$<CONFIG:Debug>,bin,bin>
    	OPTIONAL
    )
endfunction()

json_performance_add_harness(
    ${PROJECT_NAME} "" "schema-aware"
    LIBRARIES glaze::glaze simdjson
    DEFINITIONS "GLAZE_COMMIT=\"${GLAZE_COMMIT_HASH}\""
)

json_performance_add_harness(
    ${PROJECT_NAME}-Stage-1 "stage-1/" "stage-1"
    LIBRARIES simdjson-stage-1
    GCC_OPTIONS ${JSON_PERFORMANCE_GCC_VECTORIZE_OPTIONS}
)

json_performance_add_harness(
    ${PROJECT_NAME}-Generic "generic/" "generic"
    LIBRARIES simdjson
    GCC_OPTIONS -Wpedantic -Wall ${JSON_PERFORMANCE_GCC_VECTORIZE_OPTIONS}
)
