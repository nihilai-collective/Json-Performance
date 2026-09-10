/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/tests.hpp
 */

#pragma once

#include <canada.hpp>
#include <citm_catalog.hpp>
#include <discord.hpp>
#include <google_maps_response.hpp>
#include <instruments.hpp>
#include <marine_ik.hpp>
#include <mesh.hpp>
#include <random.hpp>
#include <twitter.hpp>

namespace tests {

	enum class json_libraries {
		jsonifier			= 0,
		simdjson			= 1,
		jsonifier_two_stage = 2,
	};

#if JP_CI_RUN
	static constexpr double convergence_threshold{ 5.0 };
	static constexpr double rse_threshold{ 10.0 };
#else
	static constexpr double convergence_threshold{ 2.5 };
	static constexpr double rse_threshold{ 5.0 };
#endif

	static constexpr benchmarksuite::stage_config_data config{ .clear_cpu_caches_before_iterations = true,
		.measured_iteration_count																   = measured_iteration_count,
		.max_iteration_count																	   = max_iteration_count,
		.convergence_threshold																	   = convergence_threshold,
		.max_time_in_s																			   = 5,
		.rse_threshold																			   = rse_threshold };

	static constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Scalar Structural Parsing vs Two-Stage Parsing vs simdjson" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<json_libraries json_library, benchmarksuite::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<typename value_type>
	concept pod_types = std::is_same_v<bool, value_type> || std::is_same_v<std::string, value_type> || std::is_same_v<int64_t, value_type> ||
		std::is_same_v<uint64_t, value_type> || std::is_same_v<double, value_type>;

	template<benchmarksuite::string_literal library_name, benchmarksuite::string_literal file_tag, bool partial_read, benchmarksuite::string_literal test_name_new, bool minified,
		typename test_data_type>
	struct jsonifier_traits {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr jsonifier::parse_options parse_opts{ .partialRead = partial_read, .knownOrder = true, .minified = minified };
			jsonifier::jsonifier_core<> parser;
			test_data_type json_data;
			struct parse_test_struct {
				static void before(jsonifier::jsonifier_core<>&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					parser_new.parseJson<parse_opts>(json_data_out, json_data_in);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, library_name, parse_test_struct>(parser, json_data_in_pre, json_data);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string new_string;
			[[maybe_unused]] auto new_result = parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-" + file_tag + ".json");
		}
	};

	template<benchmarksuite::string_literal library_name, benchmarksuite::string_literal file_tag, bool partial_read, benchmarksuite::string_literal test_name_new, bool minified,
		pod_types test_data_type>
	struct jsonifier_traits<library_name, file_tag, partial_read, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr jsonifier::parse_options parse_opts{ .partialRead = partial_read, .minified = minified };
			jsonifier::jsonifier_core<> parser;
			std::vector<test_data_type> test_datas;
			struct parse_test_struct {
				static void before(jsonifier::jsonifier_core<>&, std::vector<test_data_type>& test_datas, std::vector<std::string>&) {
					test_datas.clear();
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < json_data_in.size(); ++x) {
						if constexpr (std::is_same_v<test_data_type, bool>) {
							bool new_value{};
							parser_new.parseJson<parse_opts>(new_value, json_data_in[x]);
							test_datas.push_back(new_value);
						} else {
							parser_new.parseJson<parse_opts>(test_datas.emplace_back(), json_data_in[x]);
						}
						benchmarksuite::do_not_optimize_away(test_datas.back());
						new_size += json_data_in[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, library_name, parse_test_struct>(parser, test_datas, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string new_string;
			[[maybe_unused]] auto new_result = parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-" + file_tag + ".json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::jsonifier, test_name_new, minified, test_data_type>
		: jsonifier_traits<jsonifier_library_name, "jsonifier", false, test_name_new, minified, test_data_type> {};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::jsonifier_two_stage, test_name_new, minified, test_data_type>
		: jsonifier_traits<jsonifier_two_stage_library_name, "jsonifier-two-stage", true, test_name_new, minified, test_data_type> {};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			simdjson::ondemand::parser parser;
			using value_type = test_data_type;
			std::vector<test_data_type> test_datas;
			struct parse_test_struct {
				static void before(simdjson::ondemand::parser&, std::vector<test_data_type>& test_datas, std::vector<std::string>&) {
					test_datas.clear();
				}

				static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < json_data_in.size(); ++x) {
						if constexpr (std::is_same_v<value_type, bool>) {
							bool new_value;
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
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, test_datas, json_data_in);
			std::string new_string;
			jsonifier::jsonifier_core jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			simdjson::ondemand::parser parser;
			test_data_type json_data;
			struct parse_test_struct {
				static void before(simdjson::ondemand::parser&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					get_value(parser_new.iterate(json_data_in.data(), json_data_in.size(), json_data_in.capacity()), json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			try {
				benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre, json_data);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			std::string new_string;
			jsonifier::jsonifier_core jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

	std::string make_commit_row(std::string_view label, std::string_view org_repo, std::string_view commit) {
		std::string result;
		result.reserve(94);
		result += "| ";
		result += label;
		result += ": [";
		result += commit;
		result += "](https://github.com/";
		result += org_repo;
		result += "/commit/";
		result += commit;
		result += ")  \n";
		return result;
	}

	std::string make_section00() {
		std::string result;
		result.reserve(164);
		result += "# Json-Performance\nPerformance profiling of JSON libraries (Compiled and run on ";
		result += benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::os_id;
		result += " ";
		result += benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::os_version;
		result += " using the ";
		result += benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::compiler_id;
		result += " ";
		result += benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::compiler_version;
		result += " compiler).  \n\nLatest Results: (";
		return result;
	}

	std::string make_section01() {
		std::string result;
		result.reserve(223);
		result += "#### Using the following commits:\n----\n";
		result += make_commit_row("Jsonifier", "nihilai-collective/jsonifier", JSONIFIER_COMMIT);
		result += make_commit_row("Simdjson (On Demand)", "simdjson/simdjson", SIMDJSON_COMMIT);
		return result;
	}

	std::string make_section02() {
		std::string result;
		result.reserve(1403);
		result += "\n#### Active Implementations:\n";
		result += "| Library | Active Implementation |\n";
		result += "| ------- | --------------------- |\n";
		result += "| Jsonifier | `";
		result += jsonifier::cpu_arch_name;
		result += "` |\n";
		result += "| simdjson (ondemand) | `";
		result += simdjson::get_active_implementation()->name();
		result += "` |\n";
		result +=
			"> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. \n\n";
		result += "> Adaptive sampling on (";
		result += benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name();
		result += "): iterations begin at ";
		result += std::to_string(config.measured_iteration_count);
		result += " and double each epoch (e.g. ";
		result += std::to_string(config.measured_iteration_count);
		result += " → ";
		result += std::to_string(config.measured_iteration_count * 2);
		result += " → ";
		result += std::to_string(config.measured_iteration_count * 4);
		result += " → ...) up to a maximum of ";
		result += std::to_string(config.max_iteration_count);
		result += " iterations. Each epoch runs all iterations and evaluates a trailing window of ";
		result += "max(iterations/10, ";
		result += std::to_string(config.min_k);
		result += ") samples, capped at ";
		result += std::to_string(config.max_k);
		result += ". Sampling does not stop early: epochs continue until ";
		result += std::to_string(config.max_time_in_s);
		result += " seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), ";
		result += "and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < ";
		result += std::to_string(config.rse_threshold);
		result += "% AND mean shift < ";
		result += std::to_string(config.convergence_threshold);
		result += "%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. ";
		result += "All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.\n\n##### (All of the libraries are performing UTF8-validation in "
				  "these tests. \"jsonifier\" is performing scalar structural iteration; \"jsonifier (two-stage)\" is the same parse call routed through stage-1 + stage-2)\n\n";
		result += "In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.\n\n";
		result += "#### Note:\n  This is the commit of BenchmarkSuite that was used to generate these results: [";
		result += BNCH_SWT_COMMIT;
		result += "](https://github.com/nihilai-collective/benchmarksuite/commit/";
		result += BNCH_SWT_COMMIT;
		result += ").\n  ";
		return result;
	}

	std::string make_reverse_note() {
		return "These tests parse keys in reverse order relative to their appearance in the JSON document.\n\n"
			   "This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only "
			   "parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans "
			   "(or rewinds), degrading performance from O(N) to O(N^2) as document size grows.\n\n"
			   "In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent "
			   "lookup time regardless of key ordering.\n\n";
	}

	std::string generate_section(std::string_view test_name_new_graph, std::string_view test_name_new_json) {
		std::string test_name_json{ benchmarksuite::url_encode(test_name_new_json) };
		std::string test_name_graph{ benchmarksuite::url_encode(test_name_new_graph) };
		std::string result;
		result.reserve(test_name_new_graph.size() + test_name_json.size() + test_name_graph.size() * 2 + current_path.size() * 2 + 200);
		result += "\n----\n### ";
		result += test_name_new_graph;
		result += " Results [(View the data used in the following test)](./json/";
		result += test_name_json;
		result += ".json):\n\n<p align=\"left\"><a href=\"./graphs/";
		result += current_path.operator std::string_view();
		result += "/";
		result += test_name_graph;
		result += "_Results.png\" target=\"_blank\"><img src=\"./graphs/";
		result += current_path.operator std::string_view();
		result += "/";
		result += test_name_graph;
		result += "_Results.png?raw=true\" \nalt=\"\" width=\"400\"/></p>\n\n";
		if ((test_name_new_graph.find("Reverse") != std::string_view::npos) && (test_name_new_graph.find("Read") != std::string_view::npos)) {
			result += make_reverse_note();
		}
		return result;
	}

	template<benchmarksuite::string_literal test_name_new, typename test_data_type, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ " Read" };

		template<typename library_type, typename json_input_type> static void run(json_input_type& json_data_new) {
			library_type::run(json_data_new);
		}

		template<typename json_input_type> static std::string run(json_input_type& json_data_new) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + test_type_string };
			std::string json_results;
			(run<library_traits>(json_data_new), ...);
			auto results = benchmark_stage::get_test_results(test_name);
			results.print(false);
			if (results.size() > 1) {
				json_results += generate_section(test_name, test_name_new);
				json_results += results.to_markdown(false, false);
				std::string csv_path;
				csv_path.reserve(csv_out_path.size() + 1 + test_name.size() + 4);
				csv_path += csv_out_path.operator std::string_view();
				csv_path += "/";
				csv_path += test_name.operator std::string_view();
				csv_path += ".csv";
				benchmarksuite::file_handle::save_file(results.to_csv(), csv_path);
			}
			return json_results;
		}
	};

	std::string get_padded_json_string(const std::string& path) {
		auto raw_data = benchmarksuite::file_handle::get(path);
		raw_data.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		return raw_data;
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod, typename... library_traits> void execute_test(std::string& newer_string) {
		std::string full_path;
		full_path.reserve(json_path.size() + 1 + test_name.size() + 5);
		full_path += json_path.operator std::string_view();
		full_path += "/";
		full_path += test_name.operator std::string_view();
		full_path += ".json";

		if constexpr (is_pod) {
			auto test_datas = string_to_vector(benchmarksuite::file_handle::get(full_path));
			newer_string += test_traits<test_name, test_data_type, library_traits...>::run(test_datas);
		} else {
			auto json_data_in = get_padded_json_string(full_path);
			newer_string += test_traits<test_name, test_data_type, library_traits...>::run(json_data_in);
		}
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod, json_libraries... json_library_vals> void run_test_pair(std::string& newer_string) {
		if constexpr (is_pod) {
			execute_test<test_data_type, test_name, is_pod, library_traits<json_library_vals, test_name, true, test_data_type>...>(newer_string);
		} else {
			execute_test<test_data_type, test_name + " (Minified)", is_pod, library_traits<json_library_vals, test_name + " (Minified)", true, test_data_type>...>(newer_string);
			execute_test<test_data_type, test_name + " (Prettified)", is_pod, library_traits<json_library_vals, test_name + " (Prettified)", false, test_data_type>...>(
				newer_string);
		}
	}

	template<typename results_type> struct ranked_rows : results_type {
		explicit ranked_rows(const results_type& base) : results_type{ base } {
		}

		const auto& rows() const {
			return this->sorted_results;
		}
	};

	std::string with_combined_jsonifier_tally(std::string stage_csv) {
		static constexpr uint64_t unranked{ std::numeric_limits<uint64_t>::max() };
		uint64_t wins{};
		uint64_t ties{};
		uint64_t losses{};
		for (const auto& test: benchmark_stage::get_finished_tests()) {
			const ranked_rows<std::remove_cvref_t<decltype(test)>> ranked{ test };
			uint64_t best_jsonifier_position{ unranked };
			uint64_t simdjson_position{ unranked };
			for (const auto& row: ranked.rows()) {
				if (row.name == simdjson_library_name.operator std::string_view()) {
					simdjson_position = row.position;
				} else {
					best_jsonifier_position = std::min(best_jsonifier_position, row.position);
				}
			}
			if (best_jsonifier_position == unranked || simdjson_position == unranked) {
				continue;
			}
			if (best_jsonifier_position < simdjson_position) {
				++wins;
			} else if (best_jsonifier_position == simdjson_position) {
				++ties;
			} else {
				++losses;
			}
		}
		const size_t tally_start{ stage_csv.find("Library,Wins,Ties,Losses") };
		if (tally_start != std::string::npos) {
			stage_csv.resize(tally_start);
		}
		stage_csv += "Library,Wins,Ties,Losses\n";
		stage_csv += std::string{ jsonifier_library_name.operator std::string_view() } + "," + std::to_string(wins) + "," + std::to_string(ties) + "," + std::to_string(losses) + "\n";
		stage_csv += std::string{ simdjson_library_name.operator std::string_view() } + "," + std::to_string(losses) + "," + std::to_string(ties) + "," + std::to_string(wins) + "\n";
		return stage_csv;
	}

	void test_function() {
		std::string newer_string{ make_section00() + benchmarksuite::get_time() + ")\n" + make_section01() + make_section02() };
		benchmarksuite::pin_for_benchmark();
		run_test_pair<bool, "Bool Test", true, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<double, "Double Test", true, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<int64_t, "Int64 Test", true, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<std::string, "String Test", true, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<uint64_t, "Uint64 Test", true, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_message, "Canada Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_message, "CitmCatalog Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_message, "Discord Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_message, "Google Maps Response Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_message, "Instruments Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik_reverse, "Marine IK Reverse Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik, "Marine IK Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_message, "Mesh Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<random_message, "Random Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_message, "Twitter Test", false, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson>(newer_string);
		benchmarksuite::file_handle::save_file(static_cast<std::string>(newer_string), base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(with_combined_jsonifier_tally(stage_results.to_csv()), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}