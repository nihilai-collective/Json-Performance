cmake_minimum_required(VERSION 3.18)

project(
  Json-Performance
  VERSION 1.0.0
  LANGUAGES CXX
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install/)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)
include(GetCommitHash.cmake)

FetchContent_Declare(
  jsonifier
  GIT_REPOSITORY https://github.com/realtimechris/jsonifier.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(jsonifier)
getCommitHash(${jsonifier_SOURCE_DIR} JSONIFIER_COMMIT_HASH)

FetchContent_Declare(
  benchmarksuite
  GIT_REPOSITORY https://github.com/RealTimeChris/benchmarksuite.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(benchmarksuite)

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

add_executable(
  ${PROJECT_NAME} 
  ./source/main.cpp
)

set(JSON_PERFORMANCE_MSVC_COMPILER_OPTIONS
    /wd4324 /wd4820 /wd5039 /wd4710 /wd5045 /wd4711
    /Wall /W4 /bigobj
    $<$<CONFIG:RELEASE>:/O2> /arch:AVX2 /GL /Oi /Ot
    /Zc:preprocessor /EHsc /GS-
)

set(JSON_PERFORMANCE_CLANG_COMPILER_OPTIONS
    -Weverything -Wpedantic
    -Wno-unsafe-buffer-usage
    -Wno-c++20-extensions
    -Wextra -Wall
    -Wno-c++98-compat-pedantic
    -Wno-c++98-compat
    -Wno-padded
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
    -Wpedantic -Wall
    -O3 -march=native
    -funroll-loops -fomit-frame-pointer
    ${JSON_PERFORMANCE_GCC_LTO}
    -fvect-cost-model=unlimited
    -falign-functions=64 -falign-loops=64
    -ffunction-sections
    -fdata-sections
)

target_compile_options(
    ${PROJECT_NAME} PUBLIC
    $<$<CXX_COMPILER_ID:Clang>:${JSON_PERFORMANCE_CLANG_COMPILER_OPTIONS}>
    $<$<CXX_COMPILER_ID:AppleClang>:${JSON_PERFORMANCE_APPLE_CLANG_COMPILER_OPTIONS}>
    $<$<CXX_COMPILER_ID:GNU>:${JSON_PERFORMANCE_GCC_COMPILER_OPTIONS}>
    $<$<CXX_COMPILER_ID:MSVC>:${JSON_PERFORMANCE_MSVC_COMPILER_OPTIONS}>
)

target_link_options(
    ${PROJECT_NAME} PUBLIC
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<NOT:$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>>:-fuse-ld=lld;-Wl,-O2;-Wl,--gc-sections;-Wl,-z,now>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>:-Wl,-dead_strip>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<NOT:$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>>:-Wl,-O2;-Wl,--gc-sections;-Wl,-z,now>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>:-Wl,-dead_strip>
    $<$<AND:$<CXX_COMPILER_ID:AppleClang>,$<STREQUAL:${CMAKE_SYSTEM_NAME},Darwin>>:-Wl,-dead_strip>
    $<$<CXX_COMPILER_ID:MSVC>:${JSON_PERFORMANCE_MSVC_LINKER_OPTIONS}>
)

target_link_libraries(
	${PROJECT_NAME} PUBLIC 
	Jsonifier::Jsonifier simdjson benchmarksuite::benchmarksuite
)

if (WIN32)
	install(
		FILES 
		$<TARGET_PDB_FILE:${PROJECT_NAME}>
		DESTINATION $<IF:$<CONFIG:Debug>,bin,bin>
		OPTIONAL
	)
endif()

target_compile_definitions(
	${PROJECT_NAME} PUBLIC 
	"BASE_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}\""
	"JSONIFIER_COMMIT=\"${JSONIFIER_COMMIT_HASH}\""
	"SIMDJSON_COMMIT=\"${SIMDJSON_COMMIT_HASH}\""
	"OPERATING_SYSTEM_NAME=\"${CMAKE_SYSTEM_NAME}\""
	"OPERATING_SYSTEM_VERSION=\"${CMAKE_SYSTEM_VERSION}\""
	"COMPILER_ID=\"${CMAKE_CXX_COMPILER_ID}\""
	"COMPILER_VERSION=\"${CMAKE_CXX_COMPILER_VERSION}\""
)

install(
	FILES 
	$<TARGET_FILE:${PROJECT_NAME}>
	DESTINATION $<IF:$<CONFIG:Debug>,bin,bin>
	OPTIONAL
)
