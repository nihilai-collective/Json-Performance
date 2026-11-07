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

set(JSON_PERFORMANCE_TEST_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" CACHE STRING "Root path the unit tests resolve their JSON data against")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install/" CACHE PATH "Prefix prepended to install directories" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)

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

set(SIMDJSON_DEVELOPMENT_CHECKS OFF CACHE BOOL "" FORCE)
set(SIMDJSON_SKIPUTF8VALIDATION ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  simdjson
  GIT_REPOSITORY https://github.com/nihilai-collective/simdjson.git
  GIT_TAG for-comparison
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(simdjson)
getCommitHash(${simdjson_SOURCE_DIR} SIMDJSON_COMMIT_HASH)

add_executable(${PROJECT_NAME} ./source/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ./include)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  "BASE_PATH=\"${JSON_PERFORMANCE_TEST_BASE_PATH}\""
  "JSONIFIER_COMMIT=\"${JSONIFIER_COMMIT_HASH}\""
  "SIMDJSON_COMMIT=\"${SIMDJSON_COMMIT_HASH}\""
  "BNCH_SWT_COMMIT=\"${BNCH_SWT_COMMIT_HASH}\""
  "JP_CI_RUN=$<BOOL:${JP_CI_RUN}>"
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  benchmarksuite::benchmarksuite
  Jsonifier::Jsonifier
  simdjson
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION bin OPTIONAL)
endif()
