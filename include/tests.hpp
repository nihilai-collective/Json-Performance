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
	static constexpr double convergence_threshold{ 5.0 };
	static constexpr double rse_threshold{ 10.0 };
#else
	static constexpr double convergence_threshold{ 2.5 };
	static constexpr double rse_threshold{ 5.0 };
#endif

	static constexpr benchmarksuite::stage_config_data config{ .clear_cpu_caches_before_iterations = true,
		.include_non_converged_results															   = true,
		.measured_iteration_count																   = measured_iteration_count,
		.max_iteration_count																	   = max_iteration_count,
		.convergence_threshold																	   = convergence_threshold,
		.max_time_in_s																			   = 5,
		.rse_threshold																			   = rse_threshold };

	static constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Stage-1 Parsing" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<json_libraries json_library, benchmarksuite::string_literal test_name, bool minified> struct library_traits;

	size_t total_element_size(const std::vector<std::string>& values) {
		size_t total{};
		for (auto& value: values) {
			total += value.size();
		}
		return total;
	}

	template<benchmarksuite::string_literal test_name_new, bool minified> struct library_traits<json_libraries::jsonifier, test_name_new, minified> {
		static auto run(const std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::string& json_data_in, uint64_t size) {
					benchmarksuite::do_not_optimize_away(
						parser_new.collectStructurals<jsonifier::parse_options{ .partialRead = true, .minified = minified }>(json_data_in));
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre, json_data_in_pre.size());
			return;
		}

		static auto run(const std::vector<std::string>& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in, uint64_t size) {
					for (auto& element: json_data_in) {
						benchmarksuite::do_not_optimize_away(parser_new.collectStructuralsSingle<jsonifier::parse_options{ .partialRead = true, .minified = minified }>(element));
					}
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre,
				total_element_size(json_data_in_pre));
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified> struct library_traits<json_libraries::simdjson, test_name_new, minified> {
		static auto run(const std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				static size_t impl(simdjson::ondemand::parser& parser_new, const std::string& json_data_in, uint64_t size, uint64_t capacity) {
					benchmarksuite::do_not_optimize_away(parser_new.iterate(json_data_in.data(), size, capacity));
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre, json_data_in_pre.size(),
				json_data_in_pre.capacity());
			return;
		}

		static auto run(const std::vector<std::string>& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				static size_t impl(simdjson::ondemand::parser& parser_new, const std::vector<std::string>& json_data_in, uint64_t size) {
					for (auto& element: json_data_in) {
						benchmarksuite::do_not_optimize_away(parser_new.iterate(element.data(), element.size(), element.capacity()));
					}
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre,
				total_element_size(json_data_in_pre));
			return;
		}
	};

	template<benchmarksuite::string_literal label, benchmarksuite::string_literal org_repo, benchmarksuite::string_literal commit>
	consteval auto make_commit_row() {
		return benchmarksuite::string_literal{ "| " + label + ": [" + commit + "](https://github.com/" + org_repo + "/commit/" + commit + ")  \n" };
	}

	consteval auto make_section00() {
		using system_info = benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>;
		constexpr benchmarksuite::string_literal os_id{ system_info::os_id };
		constexpr benchmarksuite::string_literal os_version{ system_info::os_version };
		constexpr benchmarksuite::string_literal compiler_id{ system_info::compiler_id };
		constexpr benchmarksuite::string_literal compiler_version{ system_info::compiler_version };
		return benchmarksuite::string_literal{ "# Json-Performance\nPerformance profiling of JSON libraries (Compiled and run on " + os_id + " " + os_version + " using the " +
			compiler_id + " " + compiler_version + " compiler).  \n\nLatest Results: (" };
	}

	consteval auto make_section01() {
		return benchmarksuite::string_literal{ "#### Using the following commits:\n----\n" + make_commit_row<"Jsonifier", "nihilai-collective/jsonifier", JSONIFIER_COMMIT>() +
			make_commit_row<"simdjson(On Demand)", "simdjson/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> consteval auto generate_section() {
		constexpr benchmarksuite::string_literal test_name_json{ benchmarksuite::url_encode_literal<test_name_new_json>() };
		constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_json + " Results [(View the data used in the following test)](./json/" + test_name_json + ".json):\n\n" +
			"<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" + current_path + "/" +
			test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"400\"/></a></p>\n\n";
	}

	std::string make_section02() {
		return std::format(
			"\n#### Active Implementations:\n"
			"| Library | Active Implementation |\n"
			"| ------- | --------------------- |\n"
			"| Jsonifier | `{0}` |\n"
			"| simdjson (ondemand) | `{1}` |\n\n"
			"> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below.\n\n"
			"> Adaptive sampling on ({2}): iterations begin at {3} and double each epoch (e.g. {3} → {4} → {5} → ...) up to a maximum of {6} iterations. "
			"Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, {7}) samples, capped at {8}. "
			"Sampling does not stop early: epochs continue until {9} seconds have elapsed or the iteration cap is reached. "
			"The first epoch is kept only as an initial fallback; every later epoch is scored by its RSE plus its epoch-over-epoch mean shift (%), "
			"and the lowest-scoring epoch is retained as the canonical result, whether or not it met the convergence thresholds. A result counts as converged only if that "
			"retained epoch has RSE <= {10}% AND mean shift <= {11}%; "
			"non-converged results are still included in the rankings and in win/tie/loss tallying, so a result that did not meet these thresholds "
			"should be read with its reduced statistical confidence in mind. "
			"All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.\n\n"
			"##### (Both libraries are executing only 'stage-1' parsing, where they identify the structural indices, and neither of them are performing utf-8 validation in "
			"these tests)\n\n"
			"#### Note:\n This is the commit of BenchmarkSuite that was used to generate these results: "
			"[{12}](https://github.com/nihilai-collective/benchmarksuite/commit/{12}).\n ",
			jsonifier::activeBackendName(), simdjson::get_active_implementation()->name(), benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name(),
			config.measured_iteration_count, config.measured_iteration_count * 2, config.measured_iteration_count * 4, config.max_iteration_count, config.min_k, config.max_k,
			config.max_time_in_s, config.rse_threshold, config.convergence_threshold, BNCH_SWT_COMMIT);
	}

	template<benchmarksuite::string_literal test_name_new, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ " Read" };

		template<typename library_type, typename json_input_type> static void run(const json_input_type& json_data_new) {
			library_type::run(json_data_new);
		}

		template<typename json_input_type> static std::string run(const json_input_type& json_data_new) {
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

	std::string get_padded_json_string(const std::string& path) {
		auto raw_data = benchmarksuite::file_handle::get(path);
		raw_data.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		return raw_data;
	}

	template<benchmarksuite::string_literal test_name, bool is_pod, typename... library_traits> void execute_test(std::string& newer_string) {
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

	template<benchmarksuite::string_literal test_name, bool is_pod, json_libraries... json_library> void run_test_pair(std::string& newer_string) {
		if constexpr (is_pod) {
			execute_test<test_name, true, library_traits<json_library, test_name, true>...>(newer_string);
		} else {
			execute_test<test_name + " (Minified)", false, library_traits<json_library, test_name + " (Minified)", true>...>(newer_string);
			execute_test<test_name + " (Prettified)", false, library_traits<json_library, test_name + " (Prettified)", false>...>(newer_string);
		}
	}

	void test_function() {
		std::string newer_string{ make_section00().operator std::string() + benchmarksuite::get_time() + ")\n" + make_section01().operator std::string() + make_section02() };
		benchmarksuite::pin_for_benchmark();
		run_test_pair<"Bool Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Double Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Int64 Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"String Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Uint64 Test", true, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Canada Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"CitmCatalog Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Discord Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Google Maps Response Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Instruments Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Marine IK Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Mesh Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Random Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Twitter Test", false, json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		benchmarksuite::file_handle::save_file(newer_string, base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}
