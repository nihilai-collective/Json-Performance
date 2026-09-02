// MIT License @ /License.md
// Copyright (c) 2026 Nihilai Collective Corp
// https://github.com/nihilai-collective/json-performance
// source/common.hpp

#pragma once

#include <benchmarksuite>
#include <simdjson.h>
#include <jsonifier>

#if defined(NDEBUG)
static constexpr auto max_iteration_count{ 100000 };
static constexpr auto measured_iteration_count{ 40 };
#else
static constexpr auto max_iteration_count{ 100 };
static constexpr auto measured_iteration_count{ 20 };
#endif

constexpr benchmarksuite::string_literal current_path{ benchmarksuite::get_current_path_impl() };
constexpr benchmarksuite::string_literal base_path{ BASE_PATH };
constexpr benchmarksuite::string_literal json_path{ base_path + "/json" };
constexpr benchmarksuite::string_literal csv_out_path{ base_path + "/csv" + "/" + current_path };
constexpr benchmarksuite::string_literal graphs_path{ base_path + "/graphs/" + current_path + "/" };
constexpr benchmarksuite::string_literal jsonifier_library_name{ "jsonifier" };
constexpr benchmarksuite::string_literal simdjson_library_name{ "simdjson" };
