/*
	MIT License

	Copyright (c) 2026 Nihilai Collective Corp

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
/// https://github.com/nihilai-collective/Json-Performance
#pragma once

#include "apache-builds.hpp"
#include "canada.hpp"
#include "citm_catalog.hpp"
#include "discord.hpp"
#include "github_events.hpp"
#include "google_maps_response.hpp"
#include "instruments.hpp"
#include "marine_ik.hpp"
#include "mesh.hpp"
#include "random.hpp"
#include "semanticscholar.hpp"
#include "twitter.hpp"

namespace tests {

	enum class json_libraries {
		jsonifier = 0,
		simdjson  = 1,
	};

	static constexpr benchmarksuite::stage_config_data config{ .clear_cpu_caches_before_iterations = true,
		.measured_iteration_count																   = measured_iteration_count,
		.max_iteration_count																	   = max_iteration_count,
		.max_time_in_s																			   = 10 };

	static constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Stage-1 + Stage-2 Parsing + Utf8 Validation" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<json_libraries json_library, benchmarksuite::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr bool partial_read{ true };
			static constexpr bool known_order{ true };
			jsonifier::jsonifier_core<> parser;
			std::string new_string;
			test_data_type json_data_out;
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out;
					parser_new.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified, .validateUtf8 = true }>(
						json_data_out, json_data_in);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre);
			parser.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified }>(json_data_out, json_data_in_pre);
			[[maybe_unused]] auto new_result = parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data_out, new_string);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-jsonifier.json");
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in) {
					test_data_type value;
					get_value(parser_new.iterate(json_data_in.data(), json_data_in.size(), json_data_in.capacity()), value);
					benchmarksuite::do_not_optimize_away(value);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre);
			std::string new_string;
			test_data_type json_data_out;
			try {
				get_value(parser.iterate(json_data_in_pre), json_data_out);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data_out, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
			return;
		}
	};

	std::string make_commit_row(std::string_view label, std::string_view org_repo, std::string_view commit) {
		std::string result;
		result.reserve(label.size() + org_repo.size() + commit.size() * 2 + 32);
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

	std::string make_section00(std::string_view os_id, std::string_view os_version, std::string_view compiler_id, std::string_view compiler_version) {
		std::string result;
		result.reserve(os_id.size() + os_version.size() + compiler_id.size() + compiler_version.size() + 128);
		result += "# Json-Performance\nPerformance profiling of JSON libraries (Compiled and run on ";
		result += os_id;
		result += " ";
		result += os_version;
		result += " using the ";
		result += compiler_id;
		result += " ";
		result += compiler_version;
		result += " compiler).  \n\nLatest Results: (";
		return result;
	}

	std::string make_section01() {
		std::string result;
		result.reserve(256);
		result += "#### Using the following commits:\n----\n";
		result += make_commit_row("Jsonifier", "nihilai-collective/jsonifier", JSONIFIER_COMMIT);
		result += make_commit_row("Simdjson (On Demand)", "simdjson/simdjson", SIMDJSON_COMMIT);
		return result;
	}

	std::string make_section02(std::string_view cpu_name, std::string_view jsonifier_cpu_name, std::string_view simdjson_cpu_name) {
		std::string stream;
		stream.reserve(1536);
		stream += "\n#### Active Implementations:\n";
		stream += "| Library | Active Implementation |\n";
		stream += "| ------- | --------------------- |\n";
		stream += "| Jsonifier | ";
		stream += jsonifier_cpu_name;
		stream += " |\n";
		stream += "| simdjson (ondemand) | ";
		stream += simdjson_cpu_name;
		stream += " |\n\n";
		stream +=
			"> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below.\n\n";
		stream += "> Both libraries are parsing fully into the target data structures by first performing stage-1, then stage-2 parsing, and both of them are performing utf-8 "
				  "validation in these tests. Adaptive sampling on (";
		stream += cpu_name;
		stream += "): iterations begin at ";
		stream += std::to_string(config.measured_iteration_count);
		stream += " and double each epoch (e.g. ";
		stream += std::to_string(config.measured_iteration_count);
		stream += " → ";
		stream += std::to_string(config.measured_iteration_count * 2);
		stream += " → ";
		stream += std::to_string(config.measured_iteration_count * 4);
		stream += " → ...) up to a maximum of ";
		stream += std::to_string(config.max_iteration_count);
		stream += " iterations. Each epoch runs all iterations and evaluates a trailing window of ";
		stream += "max(iterations/10, ";
		stream += std::to_string(config.min_k);
		stream += ") samples, capped at ";
		stream += std::to_string(config.max_k);
		stream += ". Convergence requires RSE < ";
		stream += std::to_string(config.rse_threshold);
		stream += "% AND mean shift < ";
		stream += std::to_string(config.convergence_threshold);
		stream += "% epoch-over-epoch simultaneously. ";
		stream += "The first epoch satisfying both conditions is retained as the canonical result. ";
		stream += "If convergence is never reached before ";
		stream += std::to_string(config.max_time_in_s);
		stream += " seconds elapse or the iteration cap is hit, the result is marked non-converged and ";
		stream += "excluded from all rankings — only converged results participate in win/tie/loss tallying. ";
		stream += "All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.\n\n";
		stream += "#### Note:\n This is the commit of BenchmarkSuite that was used to generate these results: [";
		stream += BNCH_SWT_COMMIT;
		stream += "](https://github.com/realtimechris/benchmarksuite/commit/";
		stream += BNCH_SWT_COMMIT;
		stream += ").\n ";
		return stream;
	}

	std::string make_abc_note() {
		return "The JSON documents in these two tests feature keys ranging from \"a\" to \"z\","
			   " where each key corresponds to an array of values. Notably, the library parsing methods in this test"
			   " arrange these keys in reverse order, deviating from the typical \"a\" to \"z\" arrangement.\n"
			   "This test effectively demonstrates the challenges encountered when utilizing simdjson and"
			   " iterative parsers that lack the ability to efficiently locate memory locations through"
			   " hashing. In cases where the keys are not in the expected sequence, performance is"
			   " significantly compromised, with the severity escalating as the document size increases.\n"
			   "In contrast, hash-based solutions offer a viable alternative by circumventing these issues"
			   " and maintaining optimal performance regardless of the JSON document's scale, or ordering"
			   " of the keys being parsed.  \n\n";
	}

	std::string generate_section(std::string_view test_name_new_graph, std::string_view test_name_new_json) {
		std::string test_name_json{ benchmarksuite::url_encode(std::string{ test_name_new_json }) };
		std::string test_name_graph{ benchmarksuite::url_encode(std::string{ test_name_new_graph }) };
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
		if ((test_name_new_graph.find("Out of Order") != std::string_view::npos) && (test_name_new_graph.find("Read") != std::string_view::npos)) {
			result += make_abc_note();
		}
		return result;
	}

	template<benchmarksuite::string_literal test_name_new, typename test_data_type, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ [] {
			return benchmarksuite::string_literal{ " Read" };
		}() };

		template<typename library_type, typename json_input_type> static void run(json_input_type& json_data_new) {
			library_type::run(json_data_new);
		}

		template<typename json_input_type> static std::string run(json_input_type& json_data_new) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + test_type_string };
			std::string json_results;
			(run<library_traits>(json_data_new), ...);
			auto results = benchmark_stage::get_test_results(test_name);
			results.print(false);
			if (results.sorted_results.size() > 1) {
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

	inline std::string get_padded_json_string(const std::string& path) {
		auto raw_data = benchmarksuite::file_handle::get(path);
		raw_data.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		return raw_data;
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name, typename... library_traits> void execute_test(std::string& newer_string) {
		std::string full_path;
		full_path.reserve(json_path.size() + 1 + test_name.size() + 5);
		full_path += json_path.operator std ::string_view();
		full_path += "/";
		full_path += test_name.operator std ::string_view();
		full_path += ".json";
		auto json_data_in = get_padded_json_string(full_path);
		newer_string += test_traits<test_name, test_data_type, library_traits...>::run(json_data_in);
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name, json_libraries... json_library_vals> void run_test_pair(std::string& newer_string) {
		execute_test<test_data_type, test_name + " (Minified)", library_traits<json_library_vals, test_name + " (Minified)", true, test_data_type>...>(newer_string);
		execute_test<test_data_type, test_name + " (Prettified)", library_traits<json_library_vals, test_name + " (Prettified)", false, test_data_type>...>(newer_string);
	}

	void test_function() {
		const std::string jsonifier_cpu_name{ jsonifier::cpu_arch_name };
		const std::string simdjson_cpu_name{ simdjson::get_active_implementation()->name() };
		std::string cpu_name{ benchmarksuite::internal::get_device_info<benchmarksuite::benchmark_types::cpu>() };
		cpu_name += "-";
		cpu_name += benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::instruction_set_name;
		std::string newer_string{ make_section00(benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::os_id,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::os_version,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::compiler_id,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::compiler_version) +
			benchmarksuite::get_time() + ")\n" + make_section01() + make_section02(cpu_name, jsonifier_cpu_name, simdjson_cpu_name) };
		benchmarksuite::pin_for_benchmark();
		run_test_pair<abc_in_order_partial_test, "Abc (In Order) Partial Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<abc_in_order_test, "Abc (In Order) Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<abc_out_of_order_partial_test, "Abc (Out of Order) Partial Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<abc_out_of_order_test, "Abc (Out of Order) Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<apache_builds_message, "Apache Builds Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<canada_message, "Canada Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<citm_catalog_message, "CitmCatalog Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<discord_message, "Discord Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<github_events_message, "Github Events Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<google_maps_response_message, "Google Maps Response Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<instruments_message, "Instruments Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<marine_ik, "Marine IK Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<mesh_message, "Mesh Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<random_message, "Random Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<semantic_scholar_message, "Semanticscholar Corpus Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<twitter_partial_message, "Twitter Partial Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<twitter_message, "Twitter Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		benchmarksuite::file_handle::save_file(static_cast<std::string>(newer_string), base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}