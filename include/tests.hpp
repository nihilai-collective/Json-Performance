/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/tests.hpp
 */

#pragma once

#include <common.hpp>
#include <algorithm>
#include <bit>
#include <filesystem>
#include <sstream>

namespace tests {

	template<benchmarksuite::string_literal test_name_new, bool minified> struct library_traits<json_libraries::jsonifier, test_name_new, minified> {
		static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
		inline static auto run(const std::string& json_data_in_pre) {
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::string& json_data_in, uint64_t size) {
					benchmarksuite::do_not_optimize_away(parser_new.collectStructurals<jsonifier::parse_options{ .minified = minified }>(json_data_in));
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre, json_data_in_pre.size());
			return;
		}

		inline static auto run(const std::vector<std::string>& json_data_in_pre) {
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in, uint64_t size) {
					for (const auto& element: json_data_in) {
						benchmarksuite::do_not_optimize_away(parser_new.collectStructuralsSingle<jsonifier::parse_options{ .minified = minified }>(element));
					}
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre, total_element_size(json_data_in_pre));
			return;
		}
	};

	using simdjson_stage1_parser = std::unique_ptr<simdjson::internal::dom_parser_implementation>;

	inline simdjson_stage1_parser make_simdjson_stage1_parser(size_t capacity) {
		simdjson_stage1_parser parser;
		if (simdjson::get_active_implementation()->create_dom_parser_implementation(capacity, simdjson::DEFAULT_MAX_DEPTH, parser) != simdjson::SUCCESS) {
			throw std::runtime_error{ "Failed to create the simdjson stage-1 parser." };
		}
		return parser;
	}

	inline size_t max_element_size(const std::vector<std::string>& json_data_in) {
		size_t result{};
		for (const auto& element: json_data_in) {
			result = std::max(result, element.size());
		}
		return result;
	}

	template<benchmarksuite::string_literal test_name_new, bool minified> struct library_traits<json_libraries::simdjson, test_name_new, minified> {
		static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
		inline static auto run(const std::string& json_data_in_pre) {
			auto parser = make_simdjson_stage1_parser(json_data_in_pre.size());
			struct parse_test_struct {
				inline static size_t impl(simdjson_stage1_parser& parser_new, const std::string& json_data_in, uint64_t size) {
					benchmarksuite::do_not_optimize_away(parser_new->stage1(std::bit_cast<const uint8_t*>(json_data_in.data()), size, simdjson::stage1_mode::regular));
					benchmarksuite::do_not_optimize_away(parser_new->n_structural_indexes);
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre, json_data_in_pre.size());
			return;
		}

		inline static auto run(const std::vector<std::string>& json_data_in_pre) {
			auto parser = make_simdjson_stage1_parser(max_element_size(json_data_in_pre));
			struct parse_test_struct {
				inline static size_t impl(simdjson_stage1_parser& parser_new, const std::vector<std::string>& json_data_in, uint64_t size) {
					for (const auto& element: json_data_in) {
						benchmarksuite::do_not_optimize_away(parser_new->stage1(std::bit_cast<const uint8_t*>(element.data()), element.size(), simdjson::stage1_mode::regular));
						benchmarksuite::do_not_optimize_away(parser_new->n_structural_indexes);
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
		return benchmarksuite::string_literal{ "# " + stage_name + "\nPerformance profiling of JSON libraries (Compiled and run on " + system_info::os_id + " " +
			system_info::os_version + " using the " + system_info::compiler_id + " " + system_info::compiler_version + " compiler).  \n\nLatest Results: (" };
	}

	inline consteval auto make_section01() {
		return benchmarksuite::string_literal{ "#### Using the following commits:\n----\n" + make_commit_row<"Jsonifier", "nihilai-collective/Jsonifier", JSONIFIER_COMMIT>() +
			make_commit_row<"simdjson", "simdjson/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> inline consteval auto generate_section() {
		static constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_json + " Results [(View the data used in the following test)](./json/" + benchmarksuite::url_encode_literal<test_name_new_json>() +
			".json):\n\n" + "<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" +
			current_path + "/" + test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"1200\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result = std::format("\n#### Benchmark Methodology & Test Matrix\n\n"
										 "| Library | Active Implementation |\n"
										 "| :--- | :--- |\n"
										 "| **Jsonifier** | `{}` |\n"
										 "| **simdjson (stage-1)** | `{}` |\n\n"
										 "> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.\n\n",
			jsonifier::cpuArchName, simdjson::get_active_implementation()->name());

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

	inline std::string normalize_test_name(std::string_view input) {
		std::string result;
		result.reserve(input.size());
		bool pending_space{ false };
		for (char value: input) {
			if (value == '(' || value == ')') {
				continue;
			}
			if (std::isspace(static_cast<unsigned char>(value))) {
				pending_space = !result.empty();
				continue;
			}
			if (pending_space) {
				result += ' ';
				pending_space = false;
			}
			result += static_cast<char>(std::tolower(static_cast<unsigned char>(value)));
		}
		return result;
	}

	class test_selection {
	  public:
		inline test_selection(int32_t argc, char** argv) {
			std::string joined;
			for (int32_t index = 1; index < argc; ++index) {
				if (!joined.empty()) {
					joined += ' ';
				}
				joined += argv[index];
			}
			size_t start{};
			while (start <= joined.size()) {
				size_t end = joined.find(',', start);
				if (end == std::string::npos) {
					end = joined.size();
				}
				std::string token = normalize_test_name(std::string_view{ joined }.substr(start, end - start));
				if (!token.empty()) {
					requested.emplace_back(std::move(token));
				}
				start = end + 1;
			}
		}

		inline bool wants(std::string_view base_name, std::string_view variant_name) const {
			if (requested.empty()) {
				return true;
			}
			const std::string base{ normalize_test_name(base_name) };
			const std::string variant{ normalize_test_name(variant_name) };
			for (const auto& token: requested) {
				if (token == base || token == variant) {
					return true;
				}
			}
			return false;
		}

		inline void validate(const std::vector<std::pair<std::string, std::string>>& known_names) const {
			std::string unknown;
			for (const auto& token: requested) {
				bool found{ false };
				for (const auto& [base, variant]: known_names) {
					if (token == normalize_test_name(base) || token == normalize_test_name(variant)) {
						found = true;
						break;
					}
				}
				if (!found) {
					unknown += (unknown.empty() ? "" : ", ") + token;
				}
			}
			if (unknown.empty()) {
				return;
			}
			std::string message{ "Unknown test name(s): " + unknown + "\nAvailable tests:\n" };
			for (const auto& [base, variant]: known_names) {
				message += "  " + variant + "\n";
			}
			throw std::runtime_error{ message };
		}

	  protected:
		std::vector<std::string> requested{};
	};

	inline std::string read_file_if_present(const std::string& path) {
		if (!std::filesystem::exists(path)) {
			return {};
		}
		return benchmarksuite::file_handle::get(path);
	}

	inline std::string results_file_stem(std::string_view variant_name) {
		return std::string{ csv_out_path.operator std::string_view() } + "/" + std::string{ variant_name } + " Read";
	}

	template<benchmarksuite::string_literal test_name, bool is_pod, typename... library_traits> inline void execute_test() {
		std::string json_file_path;
		json_file_path.reserve(json_path.size() + 1 + test_name.size() + 5);
		json_file_path += json_path.operator std::string_view();
		json_file_path += "/";
		json_file_path += test_name.operator std::string_view();
		json_file_path += ".json";
		std::string fragment;
		if constexpr (is_pod) {
			auto json_data_in = string_to_vector(benchmarksuite::file_handle::get(json_file_path));
			fragment		  = test_traits<test_name, library_traits...>::run(json_data_in);
		} else {
			auto json_data_in = get_padded_json_string(json_file_path);
			fragment		  = test_traits<test_name, library_traits...>::run(json_data_in);
		}
		if (!fragment.empty()) {
			benchmarksuite::file_handle::save_file(fragment, results_file_stem(test_name.operator std::string_view()) + ".md");
		}
	}

	template<benchmarksuite::string_literal test_name_new, bool is_pod_new> struct test_entry {
		static constexpr benchmarksuite::string_literal test_name{ test_name_new };
		static constexpr bool is_pod{ is_pod_new };
		static constexpr benchmarksuite::string_literal minified_name{ test_name_new + " (Minified)" };
		static constexpr benchmarksuite::string_literal prettified_name{ test_name_new + " (Prettified)" };

		inline static void collect_names(std::vector<std::pair<std::string, std::string>>& names) {
			if constexpr (is_pod) {
				names.emplace_back(std::string{ test_name.operator std::string_view() }, std::string{ test_name.operator std::string_view() });
			} else {
				names.emplace_back(std::string{ test_name.operator std::string_view() }, std::string{ minified_name.operator std::string_view() });
				names.emplace_back(std::string{ test_name.operator std::string_view() }, std::string{ prettified_name.operator std::string_view() });
			}
		}

		template<json_libraries... json_library> inline static void run(const test_selection& selection) {
			if constexpr (is_pod) {
				if (selection.wants(test_name.operator std::string_view(), test_name.operator std::string_view())) {
					execute_test<test_name, true, library_traits<json_library, test_name, true>...>();
				}
			} else {
				if (selection.wants(test_name.operator std::string_view(), minified_name.operator std::string_view())) {
					execute_test<minified_name, false, library_traits<json_library, minified_name, true>...>();
				}
				if (selection.wants(test_name.operator std::string_view(), prettified_name.operator std::string_view())) {
					execute_test<prettified_name, false, library_traits<json_library, prettified_name, false>...>();
				}
			}
		}
	};

	struct library_tally {
		std::string name{};
		uint64_t wins{};
		uint64_t ties{};
		uint64_t losses{};

		inline bool operator>(const library_tally& rhs) const noexcept {
			if (wins != rhs.wins) {
				return wins > rhs.wins;
			}
			if (ties != rhs.ties) {
				return ties > rhs.ties;
			}
			if (losses != rhs.losses) {
				return losses < rhs.losses;
			}
			return name < rhs.name;
		}
	};

	struct library_name_matcher {
		std::string_view name{};

		inline bool operator()(const library_tally& tally) const noexcept {
			return tally.name == name;
		}
	};

	inline std::vector<std::string> split_csv_line(std::string_view line) {
		std::vector<std::string> fields;
		size_t start{};
		while (true) {
			size_t end = line.find(',', start);
			fields.emplace_back(line.substr(start, end == std::string_view::npos ? std::string_view::npos : end - start));
			if (end == std::string_view::npos) {
				return fields;
			}
			start = end + 1;
		}
	}

	inline void tally_positions(const std::string& csv_text, std::vector<library_tally>& tallies) {
		std::istringstream stream{ csv_text };
		std::string line;
		size_t position_index{ std::string::npos };
		while (std::getline(stream, line)) {
			if (!line.empty() && line.back() == '\r') {
				line.pop_back();
			}
			if (line.empty() || line.front() == '#') {
				continue;
			}
			auto fields = split_csv_line(line);
			if (position_index == std::string::npos) {
				if (fields.front() == "Library") {
					auto found = std::find(fields.begin(), fields.end(), "Position");
					if (found != fields.end()) {
						position_index = static_cast<size_t>(found - fields.begin());
					}
				}
				continue;
			}
			if (fields.size() <= position_index) {
				continue;
			}
			auto existing				= std::find_if(tallies.begin(), tallies.end(), library_name_matcher{ fields.front() });
			library_tally& tally		= existing != tallies.end() ? *existing : tallies.emplace_back(library_tally{ .name = fields.front() });
			const std::string& position = fields[position_index];
			if (position == "Win") {
				++tally.wins;
			} else if (position == "Tie") {
				++tally.ties;
			} else if (position == "Loss") {
				++tally.losses;
			}
		}
	}

	template<typename... entries> struct test_suite {
		static std::vector<std::pair<std::string, std::string>> names() {
			std::vector<std::pair<std::string, std::string>> result;
			(entries::collect_names(result), ...);
			return result;
		}

		template<json_libraries... json_library> inline static void run(const test_selection& selection) {
			selection.validate(names());
			benchmarksuite::pin_for_benchmark();
			(entries::template run<json_library...>(selection), ...);
		}

		inline static std::string assemble_markdown() {
			std::string result{ make_section00().operator std::string() + benchmarksuite::get_time() + ")\n" + make_section01().operator std::string() + make_section02() };
			for (const auto& [base, variant]: names()) {
				result += read_file_if_present(results_file_stem(variant) + ".md");
			}
			return result;
		}

		inline static std::string assemble_results_csv() {
			std::string current{ benchmark_stage::get_all_results().to_csv() };
			static constexpr std::string_view tally_header{ "Library,Wins,Ties,Losses" };
			const size_t header_pos = current.find(tally_header);
			std::string result{ header_pos == std::string::npos ? current : current.substr(0, header_pos + tally_header.size()) };
			result += '\n';
			std::vector<library_tally> tallies;
			for (const auto& [base, variant]: names()) {
				tally_positions(read_file_if_present(results_file_stem(variant) + ".csv"), tallies);
			}
			std::sort(tallies.begin(), tallies.end(), std::greater<library_tally>{});
			for (const auto& tally: tallies) {
				result += std::format("{},{},{},{}\n", tally.name, tally.wins, tally.ties, tally.losses);
			}
			return result;
		}
	};

	using all_tests = test_suite<test_entry<"Bool Test", true>, test_entry<"Double Test", true>, test_entry<"Int64 Test", true>, test_entry<"String Test", true>,
		test_entry<"Uint64 Test", true>, test_entry<"Apache Builds Test", false>, test_entry<"Canada Test", false>, test_entry<"CitmCatalog Test", false>,
		test_entry<"Discord Test", false>, test_entry<"Github Events Test", false>, test_entry<"Google Maps Response Test", false>, test_entry<"Instruments Test", false>,
		test_entry<"Marine IK Test", false>, test_entry<"Random Test", false>, test_entry<"Twitter Test", false>>;

	inline void test_function(const test_selection& selection) {
		all_tests::run<json_libraries::simdjson, json_libraries::jsonifier>(selection);
		std::string markdown{ all_tests::assemble_markdown() };
		benchmarksuite::file_handle::save_file(markdown, base_path + "/" + current_path + ".md");
		benchmarksuite::file_handle::save_file(all_tests::assemble_results_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << markdown << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}
