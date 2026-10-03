/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * generic/include/tests.hpp
 */

#pragma once

#include <apache_builds.hpp>

namespace tests {

	enum class json_libraries {
		jsonifier_generic = 0,
		simdjson		  = 1,
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
		.max_time_in_s																			   = 4,
		.rse_threshold																			   = rse_threshold };

	inline constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Generic Parsing & Streaming vs simdjson On Demand" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<json_libraries json_library, benchmarksuite::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<typename value_type>
	concept pod_types = std::is_same_v<bool, value_type> || std::is_same_v<std::string, value_type> || std::is_same_v<int64_t, value_type> ||
		std::is_same_v<uint64_t, value_type> || std::is_same_v<double, value_type>;

	inline constexpr benchmarksuite::string_literal reused_suffix{ " (Reused)" };

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::jsonifier_generic, test_name_new, minified, test_data_type> {
		static constexpr jsonifier::parse_options parse_opts{ .minified = minified };

		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t parse(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					get_value(parser_new.iterate<parse_opts>(json_data_in), json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_generic_library_name, parse_test_struct>(parser, json_data_in_pre);
			struct reused_parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
				}
			};
			test_data_type json_data{};
			benchmark_stage::template run_benchmark<reused_test_name, jsonifier_generic_library_name, reused_parse_test_struct>(parser, json_data_in_pre, json_data);
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-jsonifier-generic.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<json_libraries::jsonifier_generic, test_name_new, minified, test_data_type> {
		static constexpr jsonifier::parse_options parse_opts{ .minified = minified };

		inline static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t parse(jsonifier::jsonifier_core<>& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					size_t new_size{};
					for (size_t x = 0; x < json_data_in.size(); ++x) {
						if constexpr (std::is_same_v<test_data_type, bool>) {
							bool new_value{};
							get_value(parser_new.iterate<parse_opts>(json_data_in[x]), new_value);
							test_datas.push_back(new_value);
						} else {
							get_value(parser_new.iterate<parse_opts>(json_data_in[x]), test_datas.emplace_back());
						}
						benchmarksuite::do_not_optimize_away(test_datas.back());
						new_size += json_data_in[x].size();
					}
					return new_size;
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<std::string>& json_data_in) {
					std::vector<test_data_type> test_datas;
					return parse(parser_new, json_data_in, test_datas);
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_generic_library_name, parse_test_struct>(parser, json_data_in);
			struct reused_parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> test_datas;
			benchmark_stage::template run_benchmark<reused_test_name, jsonifier_generic_library_name, reused_parse_test_struct>(parser, json_data_in, test_datas);
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-jsonifier-generic.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, test_data_type> {
		inline static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				inline static size_t parse(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					size_t new_size{};
					for (size_t x = 0; x < json_data_in.size(); ++x) {
						if constexpr (std::is_same_v<test_data_type, bool>) {
							bool new_value{};
							get_value(parser_new.iterate(json_data_in[x].data(), json_data_in[x].size(), json_data_in[x].capacity()), new_value);
							test_datas.push_back(new_value);
						} else {
							get_value(parser_new.iterate(json_data_in[x].data(), json_data_in[x].size(), json_data_in[x].capacity()), test_datas.emplace_back());
						}
						benchmarksuite::do_not_optimize_away(test_datas.back());
						new_size += json_data_in[x].size();
					}
					return new_size;
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in) {
					std::vector<test_data_type> test_datas;
					return parse(parser_new, json_data_in, test_datas);
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in);
			struct reused_parse_test_struct {
				inline static void before(simdjson::ondemand::parser&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> test_datas;
			benchmark_stage::template run_benchmark<reused_test_name, simdjson_library_name, reused_parse_test_struct>(parser, json_data_in, test_datas);
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, test_data_type> {
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				inline static size_t parse(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					get_value(parser_new.iterate(json_data_in.data(), json_data_in.size(), json_data_in.capacity()), json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
				}
			};
			struct reused_parse_test_struct {
				inline static void before(simdjson::ondemand::parser&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
				}
			};
			test_data_type json_data{};
			try {
				benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre);
				benchmark_stage::template run_benchmark<reused_test_name, simdjson_library_name, reused_parse_test_struct>(parser, json_data_in_pre, json_data);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

	template<benchmarksuite::string_literal source_name_new> struct iterate_only {
		static constexpr benchmarksuite::string_literal source_name{ source_name_new };
	};

	template<typename value_type> struct is_iterate_only : std::false_type {};

	template<benchmarksuite::string_literal source_name> struct is_iterate_only<iterate_only<source_name>> : std::true_type {};

	template<typename test_data_type, benchmarksuite::string_literal test_name> inline constexpr auto source_file_name() {
		if constexpr (is_iterate_only<test_data_type>::value) {
			return test_data_type::source_name;
		} else {
			return test_name;
		}
	}

	template<benchmarksuite::string_literal label, benchmarksuite::string_literal org_repo, benchmarksuite::string_literal commit> inline consteval auto make_commit_row() {
		return benchmarksuite::string_literal{ "| " + label + ": [" + commit + "](https://github.com/" + org_repo + "/commit/" + commit + ")  \n" };
	}

	inline consteval auto make_section00() {
		using system_info = benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>;
		return benchmarksuite::string_literal{ "# Json-Performance\nPerformance profiling of JSON libraries (Compiled and run on " + system_info::os_id + " " +
			system_info::os_version + " using the " + system_info::compiler_id + " " + system_info::compiler_version + " compiler).  \n\nLatest Results: (" };
	}

	inline consteval auto make_section01() {
		return benchmarksuite::string_literal{ "#### Using the following commits:\n----\n" +
			make_commit_row<"Jsonifier (Generic)", "nihilai-collective/jsonifier", JSONIFIER_COMMIT>() +
			make_commit_row<"Simdjson (On Demand)", "simdjson/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> inline consteval auto generate_section() {
		constexpr benchmarksuite::string_literal test_name_json{ benchmarksuite::url_encode_literal<test_name_new_json>() };
		constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_graph + " Results [(View the data used in the following test)](../../json/" + test_name_json + ".json):\n\n" +
			"<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" + current_path + "/" +
			test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"400\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result = std::format("\n#### Benchmark Methodology & Test Matrix\n\n"
										 "| Library | Active Implementation |\n"
										 "| :--- | :--- |\n"
										 "| **Jsonifier (generic)** | `{}` |\n"
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

		result +=
			"##### Implementation Details\n"
			"* **UTF-8 Validation:** Both libraries perform full UTF-8 validation in every test.\n"
			"* **Schema-Free Traversal:** Neither library is given a schema. `jsonifier (generic)` walks its stage-1 structural tape through the re-accessible "
			"`jsonifier::generic` "
			"API; `simdjson (ondemand)` walks its On Demand API. Both fill the exact same structs through the exact same field-by-field traversal.\n\n"
			"##### Test Variants\n"
			"* **Key Traversal Order:** Standard tests request keys in document order. Tests labeled `Reverse` request each object's keys backwards, forcing forward-only "
			"iterative parsers (e.g., simdjson On Demand) into sequential rescans or rewinds, degrading from $O(N)$ toward $O(N^2)$ as object size grows.\n"
			"* **Sparse:** Reads the same document as its full counterpart but requests only a small subset of fields (a few per record of the main arrays, in the spirit of "
			"Twitter Partial); all other fields are skipped by each library. `Sparse Reverse` requests that subset in reverse document order.\n\n"
			"---\n";

		result += std::format("*Environment generated via BenchmarkSuite commit: [{0}](https://github.com/nihilai-collective/benchmarksuite/commit/{0})*\n", BNCH_SWT_COMMIT);
		return result;
	}

	template<benchmarksuite::string_literal test_name_new, typename test_data_type, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ " Read" };

		template<typename library_type, typename json_input_type> inline static void run(json_input_type& json_data_new) {
			library_type::run(json_data_new);
		}

		template<typename json_input_type> inline static std::string run(json_input_type& json_data_new) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + test_type_string };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			(run<library_traits>(json_data_new), ...);
			std::string json_results{ report_results<test_name>() };
			json_results += report_results<reused_test_name>();
			return json_results;
		}

		template<benchmarksuite::string_literal result_name> inline static std::string report_results() {
			std::string json_results;
			auto results = benchmark_stage::get_test_results(result_name);
			if (results.size() == 0) {
				return json_results;
			}
			results.print(false);
			if (results.size() > 1) {
				static constexpr auto section{ generate_section<result_name, test_name_new>() };
				json_results += section.operator std::string_view();
				json_results += results.to_markdown(false, false);
				std::string csv_path;
				csv_path.reserve(csv_out_path.size() + 1 + result_name.size() + 4);
				csv_path += csv_out_path.operator std::string_view();
				csv_path += "/";
				csv_path += result_name.operator std::string_view();
				csv_path += ".csv";
				benchmarksuite::file_handle::save_file(results.to_csv(), csv_path);
			}
			return json_results;
		}
	};

	inline std::string get_padded_json_string(const std::string& path) {
		auto raw_data = benchmarksuite::file_handle::get(path);
		raw_data.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		return raw_data;
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod, typename... library_traits> inline void execute_test(std::string& newer_string) {
		std::string full_path;
		static constexpr auto source_name{ source_file_name<test_data_type, test_name>() };
		full_path.reserve(json_path.size() + 1 + source_name.size() + 5);
		full_path += json_path.operator std::string_view();
		full_path += "/";
		full_path += source_name.operator std::string_view();
		full_path += ".json";
		if (const size_t reverse_pos = full_path.find(" Reverse Test"); reverse_pos != std::string::npos) {
			full_path.erase(reverse_pos, 8);
		}
		if (const size_t sparse_pos = full_path.find(" Sparse Test"); sparse_pos != std::string::npos) {
			full_path.erase(sparse_pos, 7);
		}

		if constexpr (is_pod) {
			auto test_datas = string_to_vector(benchmarksuite::file_handle::get(full_path));
			newer_string += test_traits<test_name, test_data_type, library_traits...>::run(test_datas);
		} else {
			auto json_data_in = get_padded_json_string(full_path);
			newer_string += test_traits<test_name, test_data_type, library_traits...>::run(json_data_in);
		}
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod, json_libraries... json_library_vals>
	inline void run_test_pair(std::string& newer_string) {
		if constexpr (is_pod) {
			execute_test<test_data_type, test_name, is_pod, library_traits<json_library_vals, test_name, true, test_data_type>...>(newer_string);
		} else {
			execute_test<test_data_type, test_name + " (Minified)", is_pod, library_traits<json_library_vals, test_name + " (Minified)", true, test_data_type>...>(newer_string);
			execute_test<test_data_type, test_name + " (Prettified)", is_pod, library_traits<json_library_vals, test_name + " (Prettified)", false, test_data_type>...>(
				newer_string);
		}
	}

	inline void test_function() {
		std::string newer_string{ make_section00().operator std::string() + benchmarksuite::get_time() + ")\n" + make_section01().operator std::string() + make_section02() };
		benchmarksuite::pin_for_benchmark();
		run_test_pair<apache_builds_message, "Apache Builds Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<apache_builds_message_reverse, "Apache Builds Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<apache_builds_sparse_message, "Apache Builds Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<apache_builds_sparse_message_reverse, "Apache Builds Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<apache_builds_message, "Apache Builds Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<apache_builds_message_reverse, "Apache Builds Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<apache_builds_sparse_message, "Apache Builds Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<apache_builds_sparse_message_reverse, "Apache Builds Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(
			newer_string);
		benchmarksuite::file_handle::save_file(static_cast<std::string>(newer_string), results_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}