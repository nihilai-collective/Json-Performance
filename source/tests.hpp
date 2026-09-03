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

#include "common.hpp"

namespace tests {

	enum class json_libraries {
		jsonifier = 0,
		simdjson  = 1,
	};

	static constexpr benchmarksuite::stage_config_data config{ .clear_cpu_caches_before_iterations = true,
		.measured_iteration_count																   = measured_iteration_count,
		.max_iteration_count																	   = max_iteration_count,
		.max_time_in_s																			   = 10 };

	static constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Stage-1 Parsing" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<json_libraries json_library, benchmarksuite::string_literal test_name, bool minified> struct library_traits;

	template<benchmarksuite::string_literal test_name_new, bool minified> struct library_traits<json_libraries::jsonifier, test_name_new, minified> {
		static auto run(const std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr bool partial_read{ true };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::string& json_data_in, uint64_t size) {
					benchmarksuite::do_not_optimize_away(
						parser_new.collectStructurals<jsonifier::parse_options{ .partialRead = partial_read, .minified = minified }>(json_data_in));
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre, json_data_in_pre.size());
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
		stream += "> Both libraries are executing only 'stage-1' parsing, where they identify the structural indices, and neither of them are performing utf-8 validation in "
				  "these tests. Adaptive sampling on (";
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

	std::string generate_section(std::string_view test_name_new_graph, std::string_view test_name_new_json) {
		std::string test_name_json{ benchmarksuite::url_encode(test_name_new_json) };
		std::string test_name_graph{ benchmarksuite::url_encode(test_name_new_graph) };
		std::string result;
		result.reserve(test_name_new_json.size() + test_name_json.size() + test_name_graph.size() * 2 + current_path.size() * 2 + 200);
		result += "\n----\n### ";
		result += test_name_new_json;
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
		return result;
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
			if (results.sorted_results.size() > 1) {
				json_results += generate_section(test_name, test_name_new);
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

	template<benchmarksuite::string_literal test_name, typename... library_traits> void execute_test(std::string& newer_string) {
		std::string json_file_path;
		json_file_path.reserve(json_path.size() + 1 + test_name.size() + 5);
		json_file_path += json_path.operator std::string_view();
		json_file_path += "/";
		json_file_path += test_name.operator std::string_view();
		json_file_path += ".json";
		auto json_data_in = get_padded_json_string(json_file_path);
		newer_string += test_traits<test_name, library_traits...>::run(json_data_in);
	}

	template<benchmarksuite::string_literal test_name, json_libraries... json_library> void run_test_pair(std::string& newer_string) {
		execute_test<test_name + " (Minified)", library_traits<json_library, test_name + " (Minified)", true>...>(newer_string);
		execute_test<test_name + " (Prettified)", library_traits<json_library, test_name + " (Prettified)", false>...>(newer_string);
	}

	void test_function() {
		const std::string jsonifier_cpu_name{ jsonifier::cpu_arch_name };
		const std::string simdjson_cpu_name{ simdjson::get_active_implementation().operator*().name() };
		const auto& instruction_set_name = benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::instruction_set_name;
		std::string cpu_name;
		cpu_name.reserve(benchmarksuite::internal::get_device_info<benchmarksuite::benchmark_types::cpu>().size() + instruction_set_name.size() + 1);
		cpu_name += benchmarksuite::internal::get_device_info<benchmarksuite::benchmark_types::cpu>();
		cpu_name += "-";
		cpu_name += instruction_set_name;
		std::string newer_string{ make_section00(benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::os_id,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::os_version,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::compiler_id,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::compiler_version) +
			benchmarksuite::get_time() + ")\n" + make_section01() + make_section02(cpu_name, jsonifier_cpu_name, simdjson_cpu_name) };
		benchmarksuite::pin_for_benchmark();
		run_test_pair<"Abc Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Apache Builds Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Canada Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"CitmCatalog Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Discord Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Github Events Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Google Maps Response Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Instruments Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Marine IK Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Mesh Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Random Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Semanticscholar Corpus Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		run_test_pair<"Twitter Test", json_libraries::simdjson, json_libraries::jsonifier>(newer_string);
		benchmarksuite::file_handle::save_file(newer_string, base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}