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
#include <filesystem>
#include <algorithm>
#include <csignal>
#include <cstdlib>
#include <sstream>
#include <atomic>
#include <format>

namespace tests {

#if JP_CI_RUN
	inline constexpr double convergence_threshold{ 5.0 };
	inline constexpr double rse_threshold{ 10.0 };
#else
	inline constexpr double convergence_threshold{ 2.5 };
	inline constexpr double rse_threshold{ 5.0 };
#endif

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
	inline constexpr benchmarksuite::string_literal json_out_path{ json_path + "/" + current_path };
	inline constexpr benchmarksuite::string_literal graphs_path{ base_path + "/graphs/" + current_path + "/" };
	inline constexpr benchmarksuite::string_literal jsonifier_library_name{ "Jsonifier" };
	inline constexpr benchmarksuite::string_literal jsonifier_generic_library_name{ "Jsonifier (generic)" };
	inline constexpr benchmarksuite::string_literal simdjson_library_name{ "simdjson (ondemand)" };
	inline constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Node.js package.json Corpus vs simdjson On Demand" };
	inline constexpr benchmarksuite::string_literal reused_suffix{ " (Reused)" };

	enum class benchmark_modes {
		all	   = 0,
		fresh  = 1,
		reused = 2,
	};

	inline benchmark_modes selected_benchmark_mode{ benchmark_modes::all };

	template<benchmarksuite::string_literal test_name>
	inline constexpr bool is_reused_test{ test_name.operator std::string_view().ends_with(reused_suffix.operator std::string_view()) };

	inline constexpr benchmarksuite::stage_config_data config{ .measured_iteration_count = measured_iteration_count,
		.max_iteration_count															 = max_iteration_count,
		.convergence_threshold															 = convergence_threshold,
		.max_time_in_s																	 = 5,
		.rse_threshold																	 = rse_threshold,
		.clear_cpu_caches_before_iterations												 = true,
		.include_non_converged_results													 = true };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<benchmarksuite::string_literal test_name, benchmarksuite::string_literal library_name, typename functor_type> struct gated_benchmark {
		static constexpr benchmark_modes excluded_mode{ is_reused_test<test_name> ? benchmark_modes::fresh : benchmark_modes::reused };

		template<typename... arg_types> inline static void impl(arg_types&&... args) {
			if (selected_benchmark_mode == excluded_mode) {
				return;
			}
			benchmark_stage::template run_benchmark<test_name, library_name, functor_type>(std::forward<arg_types>(args)...);
		}
	};

	enum class json_libraries {
		jsonifier_generic = 0,
		simdjson		  = 1,
	};

	template<json_libraries json_library, benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type> struct library_traits;

}
