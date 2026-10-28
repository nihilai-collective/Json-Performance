/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/tests.hpp
 */

#pragma once

#include <common.hpp>

namespace tests {

	enum class json_libraries {
		jsonifier = 0,
		simdjson  = 1,
	};

#if JP_CI_RUN
	inline constexpr double convergence_threshold{ 5.0 };
	inline constexpr double rse_threshold{ 10.0 };
#else
	inline constexpr double convergence_threshold{ 2.5 };
	inline constexpr double rse_threshold{ 5.0 };
#endif

	inline constexpr benchmarksuite::stage_config_data config{ .clear_cpu_caches_before_iterations = true,
		.include_non_converged_results															   = true,
		.measured_iteration_count																   = measured_iteration_count,
		.max_iteration_count																	   = max_iteration_count,
		.convergence_threshold																	   = convergence_threshold,
		.max_time_in_s																			   = 5,
		.rse_threshold																			   = rse_threshold };

	inline constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Stage-1 Parsing" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<json_libraries json_library, benchmarksuite::string_literal test_name, bool minified> struct library_traits;

	inline size_t total_element_size(const std::vector<std::string>& values) {
		size_t total{};
		for (auto& value: values) {
			total += value.size();
		}
		return total;
	}

	template<benchmarksuite::string_literal test_name_new, bool minified> struct library_traits<json_libraries::jsonifier, test_name_new, minified> {
		inline static auto run(const std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::string& json_data_in, uint64_t size) {
					benchmarksuite::do_not_optimize_away(parser_new.collectStructurals<jsonifier::parse_options{ .partialRead = true, .minified = minified }>(json_data_in));
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre, json_data_in_pre.size());
			return;
		}

		inline static auto run(const std::vector<std::string>& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in, uint64_t size) {
					for (auto& element: json_data_in) {
						benchmarksuite::do_not_optimize_away(parser_new.collectStructuralsSingle<jsonifier::parse_options{ .partialRead = true, .minified = minified }>(element));
					}
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre, total_element_size(json_data_in_pre));
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified> struct library_traits<json_libraries::simdjson, test_name_new, minified> {
		inline static auto run(const std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				inline static size_t impl(simdjson::ondemand::parser& parser_new, const std::string& json_data_in, uint64_t size, uint64_t capacity) {
					benchmarksuite::do_not_optimize_away(parser_new.iterate(json_data_in.data(), size, capacity));
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre, json_data_in_pre.size(),
				json_data_in_pre.capacity());
			return;
		}

		inline static auto run(const std::vector<std::string>& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				inline static size_t impl(simdjson::ondemand::parser& parser_new, const std::vector<std::string>& json_data_in, uint64_t size) {
					for (auto& element: json_data_in) {
						benchmarksuite::do_not_optimize_away(parser_new.iterate(element.data(), element.size(), element.capacity()));
					}
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre, total_element_size(json_data_in_pre));
			return;
		}
	};

	template<benchmarksuite::string_literal label, benchmarksuite::string_literal org_repo, benchmarksuite::string_literal commit> inline consteval auto make_commit_row() {
		return benchmarksuite::string_literal{ "| " + label + ": [" + commit + "](https://github.com/" + org_repo + "/commit/" + commit + ")  \n" };
	}

	inline consteval auto make_section00() {
		using system_info = benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>;
		return benchmarksuite::string_literal{ "# Json-Performance\nPerformance profiling of JSON libraries (Compiled and run on " + system_info::os_id + " " +
			system_info::os_version + " using the " + system_info::compiler_id + " " + system_info::compiler_version + " compiler).  \n\nLatest Results: (" };
	}

	inline consteval auto make_section01() {
		return benchmarksuite::string_literal{ "#### Using the following commits:\n----\n" + make_commit_row<"Jsonifier", "nihilai-collective/jsonifier", JSONIFIER_COMMIT>() +
			make_commit_row<"simdjson(On Demand)", "simdjson/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> inline consteval auto generate_section() {
		constexpr benchmarksuite::string_literal test_name_json{ benchmarksuite::url_encode_literal<test_name_new_json>() };
		constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_json + " Results [(View the data used in the following test)](./json/" + test_name_json + ".json):\n\n" +
			"<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" + current_path + "/" +
			test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"400\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result = std::format("\n#### Benchmark Methodology & Test Matrix\n\n"
										 "| Library | Active Implementation |\n"
										 "| :--- | :--- |\n"
										 "| **Jsonifier** | `{}` |\n"
										 "| **simdjson (ondemand)** | `{}` |\n\n"
										 "> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.\n\n",
			jsonifier::activeBackendName(), simdjson::get_active_implementation()->name());

		result += std::format(
			"> **Adaptive Sampling & Convergence ({0}):**  \n"
			"> Iterations double each epoch ({1} → {2} → {3} ...) up to a maximum of {4}.  \n"
			"> Each epoch scores a trailing window of `max(iterations/10, {5})` (cap: {6}). No early stopping: epochs run until {7}s elapse or the cap is hit.  \n"
			"> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  \n"
			"> Converged: RSE ≤ {8}% and mean shift ≤ {9}%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  \n"
			"> Tie detection: Welch's t-test with Bessel-corrected variance.\n\n"
			"---\n\n",
			benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name(), config.measured_iteration_count, config.measured_iteration_count * 2,
			config.measured_iteration_count * 4, config.max_iteration_count, config.min_k, config.max_k, config.max_time_in_s, config.rse_threshold, config.convergence_threshold);

		result += "##### Implementation Details\n"
				  "* **Stage-1 Only:** Both libraries execute only stage-1 parsing, identifying structural indices and nothing more.\n"
				  "* **No UTF-8 Validation:** Neither library performs UTF-8 validation in these tests.\n\n"
				  "---\n";

		result += std::format("*Environment generated via BenchmarkSuite commit: [{0}](https://github.com/nihilai-collective/benchmarksuite/commit/{0})*\n", BNCH_SWT_COMMIT);
		return result;
	}

	template<benchmarksuite::string_literal test_name_new, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ " Read" };

		template<typename library_type, typename json_input_type> inline static void run(const json_input_type& json_data_new) {
			library_type::run(json_data_new);
		}

		template<typename json_input_type> inline static std::string run(const json_input_type& json_data_new) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + test_type_string };
			std::string json_results;
			(run<library_traits>(json_data_new), ...);
			auto results = benchmark_stage::get_test_results(test_name);
			results.print(false);
			if (results.size() > 1) {
				static constexpr auto section{ generate_section<test_name, test_name_new>() };
				json_results += section.operator std::string_view();
				json_results += results.to_markdown(false, false);
				benchmarksuite::file_handle::save_file(results.to_csv(), csv_out_path + "/" + test_name + ".csv");
			}
			return json_results;
		}
	};

	inline std::string get_padded_json_string(const std::string& path) {
		auto raw_data = benchmarksuite::file_handle::get(path);
		raw_data.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		return raw_data;
	}

	template<benchmarksuite::string_literal test_name, bool is_pod, typename... library_traits> inline void execute_test(std::string& newer_string) {
		std::string json_file_path;
		json_file_path.reserve(json_path.size() + 1 + test_name.size() + 5);
		json_file_path += json_path.operator std::string_view();
		json_file_path += "/";
		json_file_path += test_name.operator std::string_view();
		json_file_path += ".json";
		if constexpr (is_pod) {
			auto json_data_in = string_to_vector(benchmarksuite::file_handle::get(json_file_path));
			newer_string += test_traits<test_name, library_traits...>::run(json_data_in);
		} else {
			auto json_data_in = get_padded_json_string(json_file_path);
			newer_string += test_traits<test_name, library_traits...>::run(json_data_in);
		}
	}

	template<benchmarksuite::string_literal test_name, bool is_pod, json_libraries... json_library> inline void run_test_pair(std::string& newer_string) {
		if constexpr (is_pod) {
			execute_test<test_name, true, library_traits<json_library, test_name, true>...>(newer_string);
		} else {
			execute_test<test_name + " (Minified)", false, library_traits<json_library, test_name + " (Minified)", true>...>(newer_string);
			execute_test<test_name + " (Prettified)", false, library_traits<json_library, test_name + " (Prettified)", false>...>(newer_string);
		}
	}

	inline int32_t test_function() {
#if JSONIFIER_PLATFORM_MAC && JSONIFIER_ARCH_ARM64 && JP_CI_RUN
		if (benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name().find("M1") != std::string_view::npos) {
			return 1;
		}
#endif
		std::string newer_string{ make_section00().operator std::string() + benchmarksuite::get_time() + ")\n" + make_section01().operator std::string() + make_section02() };
		benchmarksuite::pin_for_benchmark();
		run_test_pair<"Bool Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Double Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Int64 Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"String Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Uint64 Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Apache Builds Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Canada Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"CitmCatalog Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Discord Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Github Events Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Google Maps Response Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Instruments Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Marine IK Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Random Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Twitter Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		benchmarksuite::file_handle::save_file(newer_string, base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
		return 0;
	}
}
