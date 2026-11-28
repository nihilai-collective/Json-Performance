# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# CMakeLists.txt

cmake_minimum_required(VERSION 3.18)

project(
  Json-Performance
  LANGUAGES CXX
)

option(JP_SIMDJSON_REFLECTION "Benchmark simdjson's C++26 static-reflection API when the compiler provides P2996 reflection" ON)

set(JSON_PERFORMANCE_TEST_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" CACHE STRING "Root path the unit tests resolve their JSON data against")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install/" CACHE PATH "Prefix prepended to install directories" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

if(JP_SIMDJSON_REFLECTION AND NOT MSVC)
  include(CheckCXXSourceCompiles)
  set(CMAKE_REQUIRED_FLAGS "-std=c++26 -freflection")
  check_cxx_source_compiles([=[
#include <meta>
#if !defined(__cpp_impl_reflection) || !defined(__cpp_lib_reflection) || !defined(__cpp_expansion_statements) || !defined(__cpp_lib_define_static)
#error static reflection unavailable
#endif
int main() { return 0; }
]=] JP_HAS_STATIC_REFLECTION)
  unset(CMAKE_REQUIRED_FLAGS)
endif()

if(JP_HAS_STATIC_REFLECTION)
  set(CMAKE_CXX_STANDARD 26)
  add_compile_options(-freflection)
else()
  set(CMAKE_CXX_STANDARD 23)
endif()

include(GetCommitHash.cmake)
include(FetchContent)

FetchContent_Declare(
  Jsonifier
  GIT_REPOSITORY https://github.com/nihilai-collective/jsonifier.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Jsonifier)
getCommitHash(${jsonifier_SOURCE_DIR} JSONIFIER_COMMIT_HASH)

FetchContent_Declare(
  benchmarksuite
  GIT_REPOSITORY https://github.com/nihilai-collective/benchmarksuite.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(benchmarksuite)
getCommitHash(${benchmarksuite_SOURCE_DIR} BNCH_SWT_COMMIT_HASH)

FetchContent_Declare(
  glaze
  GIT_REPOSITORY https://github.com/stephenberry/glaze.git
  GIT_TAG 283c966480db1514579dabac33cb61b064c6238f
)
FetchContent_MakeAvailable(glaze)
getCommitHash(${glaze_SOURCE_DIR} GLAZE_COMMIT_HASH)

set(SIMDJSON_DEVELOPMENT_CHECKS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  simdjson
  GIT_REPOSITORY https://github.com/simdjson/simdjson.git
  GIT_TAG 4ba1cb3aee235c06ce7a372f0c31a1e3219870ce
)
FetchContent_MakeAvailable(simdjson)
getCommitHash(${simdjson_SOURCE_DIR} SIMDJSON_COMMIT_HASH)

file(GLOB JP_SOURCES CONFIGURE_DEPENDS ./source/*.cpp)
add_executable(${PROJECT_NAME} ${JP_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ./include)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  "BASE_PATH=\"${JSON_PERFORMANCE_TEST_BASE_PATH}\""
  "JSONIFIER_COMMIT=\"${JSONIFIER_COMMIT_HASH}\""
  "SIMDJSON_COMMIT=\"${SIMDJSON_COMMIT_HASH}\""
  "BNCH_SWT_COMMIT=\"${BNCH_SWT_COMMIT_HASH}\""
  "GLAZE_COMMIT=\"${GLAZE_COMMIT_HASH}\""
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  benchmarksuite::benchmarksuite
  Jsonifier::Jsonifier
  glaze::glaze
  simdjson
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION bin OPTIONAL)
endif()
