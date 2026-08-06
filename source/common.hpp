/*
	MIT License

	Copyright (c) 2024 RealTimeChris

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the Software
	without restriction, including without limitation the rights to use, copy, modify, merge,
	publish, distribute, sublicense, and/or sell copies of the Software, and to permit
	persons to whom the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or
	substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/
/// https://github.com/RealTimeChris/Json-Performance
#pragma once

#include <bnch_swt>
#include <jsonifier>
#include <simdjson.h>
#include <unordered_set>
#include <thread>
#include <random>

#if defined(NDEBUG)
static constexpr auto max_iteration_count{ 100000 };
static constexpr auto measured_iteration_count{ 80 };
static constexpr auto allocation_size{ 1024 * 1024 * 128 };
static constexpr auto min_k{ 20 };
#else
static constexpr auto max_iteration_count{ 100 };
static constexpr auto measured_iteration_count{ 20 };
static constexpr auto allocation_size{ 1024 * 1024 * 128 };
static constexpr auto min_k{ 10 };
#endif

inline static std::string current_path{ bnch_swt::get_current_path_impl() };
constexpr bnch_swt::string_literal base_path{ BASE_PATH };
constexpr bnch_swt::string_literal test_path{ base_path + "/source" };
constexpr bnch_swt::string_literal read_me_path{ BASE_PATH };
constexpr bnch_swt::string_literal json_path{ base_path + "/json" };
constexpr bnch_swt::string_literal csv_path{ base_path + "/csv" };
inline static std::string json_out_path{ json_path.operator std::string() + "/" + current_path };
inline static std::string csv_out_path{ csv_path.operator std::string() + "/" + current_path };
inline static std::string graphs_path{ base_path.operator std::string() + "/graphs/" + current_path + "/" };
constexpr bnch_swt::string_literal jsonifier_library_name{ "jsonifier" };
constexpr bnch_swt::string_literal jsonifier_commit_url_base{ "https://github.com/realtimechris/jsonifier/commit/" };
constexpr bnch_swt::string_literal jsonifier_commit_url{ jsonifier_commit_url_base + JSONIFIER_COMMIT };
constexpr bnch_swt::string_literal simdjson_library_name{ "simdjson" };
constexpr bnch_swt::string_literal simdjson_commit_url_base{ "https://github.com/simdjson/simdjson/commit/" };
constexpr bnch_swt::string_literal simdjson_commit_url{ simdjson_commit_url_base + SIMDJSON_COMMIT };
