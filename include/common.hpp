/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/common.hpp
 */

#pragma once

#include <benchmarksuite>
#include <simdjson.h>
#include <jsonifier>

namespace tests {

	inline constexpr double convergence_threshold{ 2.5 };
	inline constexpr double rse_threshold{ 5.0 };

#if defined(NDEBUG)
	inline constexpr uint64_t measured_iteration_count{ 100 };
	inline constexpr uint64_t max_iteration_count{ 100000 };
#else
	inline constexpr uint64_t measured_iteration_count{ 20 };
	inline constexpr uint64_t max_iteration_count{ 100 };
#endif

	inline constexpr benchmarksuite::string_literal current_path{ benchmarksuite::get_current_path_impl() };
	inline constexpr benchmarksuite::string_literal base_path{ BASE_PATH };
	inline constexpr benchmarksuite::string_literal json_path{ base_path + "/json" };
	inline constexpr benchmarksuite::string_literal csv_out_path{ base_path + "/csv" + "/" + current_path };
	inline constexpr benchmarksuite::string_literal graphs_path{ base_path + "/graphs/" + current_path + "/" };
	inline constexpr benchmarksuite::string_literal jsonifier_library_name{ "Jsonifier" };
	inline constexpr benchmarksuite::string_literal simdjson_library_name{ "simdjson (stage-1)" };
	inline constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Stage-1 Parsing (AVX512)" };

	inline constexpr benchmarksuite::stage_config_data config{ .measured_iteration_count = measured_iteration_count,
		.max_iteration_count															 = max_iteration_count,
		.convergence_threshold															 = convergence_threshold,
		.max_time_in_s																	 = 5,
		.rse_threshold																	 = rse_threshold,
		.clear_cpu_caches_before_iterations												 = true,
		.include_non_converged_results													 = true };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	enum class json_libraries {
		jsonifier = 0,
		simdjson  = 1,
	};

	template<json_libraries json_library, benchmarksuite::string_literal test_name, bool minified> struct library_traits;

	inline size_t total_element_size(const std::vector<std::string>& values) {
		size_t total{};
		for (auto& value: values) {
			total += value.size();
		}
		return total;
	}

	inline std::vector<std::string> string_to_vector(const std::string& input) {
		std::vector<std::string> result;
		static constexpr std::string_view start_tag = "[START]";
		static constexpr std::string_view end_tag	= "[END]";
		size_t pos									= 0;

		while (true) {
			size_t start_pos = input.find(start_tag, pos);
			if (start_pos == std::string::npos) {
				break;
			}
			start_pos += start_tag.size();

			size_t end_pos = input.find(end_tag, start_pos);
			if (end_pos == std::string::npos) {
				size_t slice_length = input.size() - start_pos;
				std::string sliced;
				sliced.reserve(slice_length + simdjson::SIMDJSON_PADDING);
				sliced.append(input, start_pos, slice_length);
				result.emplace_back(std::move(sliced));
				break;
			}

			size_t slice_length = end_pos - start_pos;
			std::string sliced;
			sliced.reserve(slice_length + simdjson::SIMDJSON_PADDING);
			sliced.append(input, start_pos, slice_length);
			result.emplace_back(std::move(sliced));

			pos = end_pos + end_tag.size();
		}

		return result;
	}

}
