/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/tests.hpp
 */

#pragma once

#include <common.hpp>
#include <algorithm>
#include <array>
#include <bit>

namespace tests {

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

	template<json_libraries json_library> struct stage1_call;

	template<> struct stage1_call<json_libraries::simdjson> {
		static constexpr benchmarksuite::string_literal library_name{ simdjson_library_name };

		simdjson_inline static simdjson::error_code impl(simdjson_stage1_parser& parser_new, const std::string& json_data_in) {
			return parser_new->stage1(std::bit_cast<const uint8_t*>(json_data_in.data()), json_data_in.size(), simdjson::stage1_mode::regular);
		}
	};

	template<> struct stage1_call<json_libraries::jsonifier> {
		static constexpr benchmarksuite::string_literal library_name{ jsonifier_library_name };

		simdjson_inline static simdjson::error_code impl(simdjson_stage1_parser& parser_new, const std::string& json_data_in) {
			return parser_new->stage1_jsonifier(std::bit_cast<const uint8_t*>(json_data_in.data()), json_data_in.size());
		}
	};

	template<json_libraries json_library> simdjson_inline void run_simdjson_stage1(simdjson_stage1_parser& parser_new, const std::string& json_data_in) {
		benchmarksuite::do_not_optimize_away(stage1_call<json_library>::impl(parser_new, json_data_in));
		benchmarksuite::do_not_optimize_away(parser_new->n_structural_indexes);
	}

	template<json_libraries json_library, benchmarksuite::string_literal test_name_new, bool minified> struct library_traits {
		static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };

		inline static auto run(const std::string& json_data_in_pre) {
			auto parser = make_simdjson_stage1_parser(json_data_in_pre.size());
			struct parse_test_struct {
				inline static size_t impl(simdjson_stage1_parser& parser_new, const std::string& json_data_in, uint64_t size) {
					run_simdjson_stage1<json_library>(parser_new, json_data_in);
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, stage1_call<json_library>::library_name, parse_test_struct>(parser, json_data_in_pre, json_data_in_pre.size());
		}

		inline static auto run(const std::vector<std::string>& json_data_in_pre) {
			auto parser = make_simdjson_stage1_parser(max_element_size(json_data_in_pre));
			struct parse_test_struct {
				inline static size_t impl(simdjson_stage1_parser& parser_new, const std::vector<std::string>& json_data_in, uint64_t size) {
					for (const auto& element: json_data_in) {
						run_simdjson_stage1<json_library>(parser_new, element);
					}
					return size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, stage1_call<json_library>::library_name, parse_test_struct>(parser, json_data_in_pre, total_element_size(json_data_in_pre));
		}
	};

	template<benchmarksuite::string_literal label, benchmarksuite::string_literal org_repo, benchmarksuite::string_literal commit> consteval auto make_commit_row() {
		return benchmarksuite::string_literal{ "| " + label + ": [" + commit + "](https://github.com/" + org_repo + "/commit/" + commit + ")  \n" };
	}

	consteval auto make_section00() {
		using system_info = benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>;
		return benchmarksuite::string_literal{ "# " + stage_name + "\nJust a bit of performance profiling of some JSON libraries (compiled and run on " + system_info::os_id + " " +
			system_info::os_version + " using the " + system_info::compiler_id + " " + system_info::compiler_version + " compiler).  \n\nLatest results: (" };
	}

	consteval auto make_section01() {
		return benchmarksuite::string_literal{ "#### Here are the commits we used:\n----\n" + make_commit_row<"simdjson", "nihilai-collective/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> consteval auto generate_section() {
		static constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_graph + " Results [(Here is the data we used for this test)](./json/" + benchmarksuite::url_encode_literal<test_name_new_json>() +
			".json):\n\n" + "<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" +
			current_path + "/" + test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"1200\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result =
			std::format("\n#### How We Benchmarked & What We Tested\n\n"
						"| Library | Active Implementation |\n"
						"| :--- | :--- |\n"
						"| **Jsonifier (simdjson stage-1)** | `{0}` |\n"
						"| **simdjson (stage-1)** | `{0}` |\n\n"
						"> Both rows come from one build of our simdjson fork and share its runtime-selected kernel. Jsonifier (simdjson stage-1) runs our transplanted "
						"Jsonifier stage-1 through `stage1_jsonifier()`, and simdjson (stage-1) runs the original `stage1()`.\n\n",
				simdjson::get_active_implementation()->name());

		result += std::format("> **Sampling ({0}):**  \n"
							  "> Iterations: {1} → {2} → {3} ... (max {4}), doubling per epoch.  \n"
							  "> Window: last `max(iterations/10, {5})` samples (max {6}). Runs for {7}s or until the cap.  \n"
							  "> Epoch used: lowest RSE + mean shift (1st epoch is just a fallback).  \n"
							  "> Converged = RSE ≤ {8}% and mean shift ≤ {9}%. Non-converged ones still get ranked.  \n"
							  "> Ties: Welch's t-test (Bessel-corrected).\n\n"
							  "---\n\n",
			benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name(), config.measured_iteration_count, config.measured_iteration_count * 2,
			config.measured_iteration_count * 4, config.max_iteration_count, config.min_k, config.max_k, config.max_time_in_s, config.rse_threshold, config.convergence_threshold);

		result += "##### A Few Details\n"
				  "* **Stage-1 Only:** Just stage-1 on both sides, structural indexing with no tape or DOM built.\n"
				  "* **Same Parser, Same Buffers:** Both stage-1s write into the same simdjson parser's structural index array.\n"
				  "* **No UTF-8 Validation:** The Jsonifier stage-1 never validates, and simdjson is built with `SIMDJSON_SKIPUTF8VALIDATION`.\n\n"
				  "---\n";

		result += "*Generated with BenchmarkSuite commit: [" + std::string{ BNCH_SWT_COMMIT } + "](https://github.com/nihilai-collective/benchmarksuite/commit/" +
			std::string{ BNCH_SWT_COMMIT } + ")*\n";
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

	inline std::string normalize_test_name(std::string_view name_new) {
		std::string result;
		result.reserve(name_new.size());
		bool space_pending{ false };
		for (char value: name_new) {
			if (value == '(' || value == ')') {
				continue;
			}
			if (std::isspace(static_cast<unsigned char>(value))) {
				space_pending = !result.empty();
				continue;
			}
			if (space_pending) {
				result += ' ';
				space_pending = false;
			}
			result += static_cast<char>(std::tolower(static_cast<unsigned char>(value)));
		}
		return result;
	}

	struct test_descriptor {
		std::string_view base_name{};
		std::string_view name{};
		test_flags flags{};
	};

	class test_selection {
	  public:
		inline test_selection(int32_t argc, char** argv) {
			std::string joined;
			for (int32_t index = 1; index < argc; ++index) {
				const std::string_view argument{ argv[index] };
				const bool has_space{ argument.find(' ') != std::string_view::npos };
				if (!joined.empty()) {
					joined += has_space ? ',' : ' ';
				}
				joined += argument;
				if (has_space) {
					joined += ',';
				}
			}
			test_flags flags_new{ test_flags::none };
			size_t start{};
			while (start <= joined.size()) {
				size_t end = joined.find(',', start);
				if (end == std::string::npos) {
					end = joined.size();
				}
				std::string token = normalize_test_name(std::string_view{ joined }.substr(start, end - start));
				if (const test_flags flag = flag_for_token(token); flag != test_flags::none) {
					flags_new = flags_new | flag;
				} else if (!token.empty()) {
					requested.emplace_back(std::move(token));
				}
				start = end + 1;
			}
			mask = complete_flags(flags_new);
		}

		template<size_t count> inline std::vector<size_t> resolve(const std::array<test_descriptor, count>& descriptors) const {
			std::vector<size_t> indices;
			if (requested.empty()) {
				for (size_t index = 0; index < count; ++index) {
					push_if_allowed(descriptors[index], index, indices);
				}
				return indices;
			}
			std::string unknown;
			for (const auto& token: requested) {
				bool found{ false };
				for (size_t index = 0; index < count; ++index) {
					if (token_matches(token, descriptors[index])) {
						found = true;
						push_if_allowed(descriptors[index], index, indices);
					}
				}
				if (!found) {
					unknown += (unknown.empty() ? "" : ", ") + token;
				}
			}
			if (unknown.empty()) {
				return indices;
			}
			std::string message{ "Unknown test name(s): " + unknown + "\nAvailable tests:\n" };
			for (const auto& descriptor: descriptors) {
				message += "  " + std::string{ descriptor.name } + "\n";
			}
			throw std::runtime_error{ message };
		}

	  protected:
		std::vector<std::string> requested{};
		test_flags mask{ test_flags::all };

		inline static test_flags flag_for_token(std::string_view token) {
			if (token == "--minified") {
				return test_flags::minified;
			}
			if (token == "--prettified") {
				return test_flags::prettified;
			}
			return test_flags::none;
		}

		inline static bool token_matches(const std::string& token, const test_descriptor& descriptor) {
			return token == normalize_test_name(descriptor.name) || token == normalize_test_name(descriptor.base_name);
		}

		inline bool allows(test_flags flags) const {
			return !has_flags(flags, test_flags::formats) || has_flags(flags & mask, test_flags::formats);
		}

		inline void push_if_allowed(const test_descriptor& descriptor, size_t index, std::vector<size_t>& indices) const {
			if (allows(descriptor.flags) && std::find(indices.begin(), indices.end(), index) == indices.end()) {
				indices.emplace_back(index);
			}
		}
	};

	template<typename... types> struct type_list {};

	template<typename... lists> struct concat_lists {
		using type = type_list<>;
	};

	template<typename... types> struct concat_lists<type_list<types...>> {
		using type = type_list<types...>;
	};

	template<typename... lhs_types, typename... rhs_types, typename... remaining> struct concat_lists<type_list<lhs_types...>, type_list<rhs_types...>, remaining...>
		: concat_lists<type_list<lhs_types..., rhs_types...>, remaining...> {};

	template<typename... entries> struct test_group {
		using variants = typename concat_lists<typename entries::variants...>::type;
	};

	template<bool keep, typename variant> struct keep_if {
		using variants = type_list<>;
	};

	template<typename variant> struct keep_if<true, variant> {
		using variants = type_list<variant>;
	};

	template<json_libraries... json_library> struct library_list {};

	template<test_flags flags_new> struct flag_set {
		static constexpr test_flags flags{ complete_flags(flags_new) };
		static constexpr bool prettified{ has_flags(flags, test_flags::prettified) };
		static constexpr bool minified{ has_flags(flags, test_flags::minified) };
	};

	template<test_flags format> struct format_suffix {
		static constexpr benchmarksuite::string_literal value{ "" };
	};

	template<> struct format_suffix<test_flags::minified> {
		static constexpr benchmarksuite::string_literal value{ " (Minified)" };
	};

	template<> struct format_suffix<test_flags::prettified> {
		static constexpr benchmarksuite::string_literal value{ " (Prettified)" };
	};

	template<typename index_sequence, typename... variants> struct test_dispatcher;

	template<size_t... indices, typename... variants> struct test_dispatcher<std::index_sequence<indices...>, variants...> {
		inline static void impl(size_t index) {
			((index == indices ? (variants::execute(), true) : false) || ...);
		}
	};

	template<typename variant_list> struct test_registry_impl;

	template<typename... variants> struct test_registry_impl<type_list<variants...>> {
		static constexpr std::array<test_descriptor, sizeof...(variants)> descriptors{ { variants::descriptor... } };

		inline static void run(const test_selection& selection) {
			const std::vector<size_t> indices{ selection.resolve(descriptors) };
			benchmarksuite::pin_for_benchmark();
			for (const size_t index: indices) {
				test_dispatcher<std::index_sequence_for<variants...>, variants...>::impl(index);
			}
		}
	};

	template<typename... entries> using test_registry = test_registry_impl<typename test_group<entries...>::variants>;

	inline std::string read_file_if_present(const std::string& path) {
		try {
			return benchmarksuite::file_handle::get(path);
		} catch (const std::runtime_error&) {
			return {};
		}
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

	using stage_one_libraries = library_list<json_libraries::simdjson, json_libraries::jsonifier>;

	template<benchmarksuite::string_literal base_name_new, bool pod_new, test_flags flags_new, typename libraries> struct test_variant;

	template<benchmarksuite::string_literal base_name_new, bool pod_new, test_flags flags_new, json_libraries... json_library>
	struct test_variant<base_name_new, pod_new, flags_new, library_list<json_library...>> {
		static constexpr benchmarksuite::string_literal name{ base_name_new + format_suffix<(flags_new & test_flags::formats)>::value };
		static constexpr benchmarksuite::string_literal base_name{ base_name_new };
		static constexpr test_flags flags{ flags_new & test_flags::formats };
		static constexpr test_descriptor descriptor{ .base_name = base_name, .name = name, .flags = flags };
		static constexpr bool traits_flag{ pod_new || has_flags(flags_new, test_flags::minified) };
		using variants = type_list<test_variant>;

		inline static void execute() {
			execute_test<name, pod_new, library_traits<json_library, name, traits_flag>...>();
		}
	};

	template<benchmarksuite::string_literal base_name> struct pod_tests {
		using variants = type_list<test_variant<base_name, true, test_flags::none, stage_one_libraries>>;
	};

	template<benchmarksuite::string_literal base_name, test_flags flags_new = test_flags::all> struct json_tests {
		using set	   = flag_set<flags_new>;
		using variants = typename test_group<keep_if<set::minified, test_variant<base_name, false, test_flags::minified, stage_one_libraries>>,
			keep_if<set::prettified, test_variant<base_name, false, test_flags::prettified, stage_one_libraries>>>::variants;
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

	inline std::vector<std::string> split_csv_line(std::string_view line_new) {
		std::vector<std::string> fields;
		size_t start{};
		while (true) {
			size_t end = line_new.find(',', start);
			fields.emplace_back(line_new.substr(start, end == std::string_view::npos ? std::string_view::npos : end - start));
			if (end == std::string_view::npos) {
				return fields;
			}
			start = end + 1;
		}
	}

	inline void tally_positions(const std::string& csv_data_new, std::vector<library_tally>& tallies) {
		const std::string_view csv_view{ csv_data_new };
		size_t position_idx{ std::string::npos };
		size_t start{};
		while (start < csv_view.size()) {
			size_t end = csv_view.find('\n', start);
			if (end == std::string_view::npos) {
				end = csv_view.size();
			}
			std::string_view line = csv_view.substr(start, end - start);
			start				  = end + 1;
			if (!line.empty() && line.back() == '\r') {
				line.remove_suffix(1);
			}
			if (line.empty() || line.front() == '#') {
				continue;
			}
			auto fields = split_csv_line(line);
			if (position_idx == std::string::npos) {
				if (fields.front() == "Library") {
					auto found = std::find(fields.begin(), fields.end(), "Position");
					if (found != fields.end()) {
						position_idx = static_cast<size_t>(found - fields.begin());
					}
				}
				continue;
			}
			if (fields.size() <= position_idx) {
				continue;
			}
			auto existing				= std::find_if(tallies.begin(), tallies.end(), library_name_matcher{ fields.front() });
			library_tally& tally		= existing != tallies.end() ? *existing : tallies.emplace_back(library_tally{ .name = fields.front() });
			const std::string& position = fields[position_idx];
			if (position == "Win") {
				++tally.wins;
			} else if (position == "Tie") {
				++tally.ties;
			} else if (position == "Loss") {
				++tally.losses;
			}
		}
	}

	template<typename registry> inline std::string assemble_markdown() {
		std::string result{ make_section00().operator std::string() + benchmarksuite::get_time() + ")\n" + make_section01().operator std::string() + make_section02() };
		for (const auto& descriptor: registry::descriptors) {
			result += read_file_if_present(results_file_stem(descriptor.name) + ".md");
		}
		return result;
	}

	template<typename registry> inline std::string assemble_results_csv() {
		std::string current{ benchmark_stage::get_all_results().to_csv() };
		static constexpr std::string_view tally_header{ "Library,Wins,Ties,Losses" };
		const size_t header_pos = current.find(tally_header);
		std::string result{ header_pos == std::string::npos ? current : current.substr(0, header_pos + tally_header.size()) };
		result += '\n';
		std::vector<library_tally> tallies;
		for (const auto& descriptor: registry::descriptors) {
			tally_positions(read_file_if_present(results_file_stem(descriptor.name) + ".csv"), tallies);
		}
		std::sort(tallies.begin(), tallies.end(), std::greater<library_tally>{});
		for (const auto& tally: tallies) {
			result += tally.name + "," + std::to_string(tally.wins) + "," + std::to_string(tally.ties) + "," + std::to_string(tally.losses) + "\n";
		}
		return result;
	}

	using registered_tests = test_registry<pod_tests<"Bool Test">, pod_tests<"Double Test">, pod_tests<"Int64 Test">, pod_tests<"String Test">, pod_tests<"Uint64 Test">,
		json_tests<"Apache Builds Test">, json_tests<"Canada Test">, json_tests<"CitmCatalog Test">, json_tests<"Discord Test">, json_tests<"Github Events Test">,
		json_tests<"Google Maps Response Test">, json_tests<"Instruments Test">, json_tests<"Marine IK Test">, json_tests<"Random Test">, json_tests<"Twitter Test">>;

	inline void test_function(const test_selection& selection) {
		registered_tests::run(selection);
		std::string markdown{ assemble_markdown<registered_tests>() };
		benchmarksuite::file_handle::save_file(markdown, base_path + "/" + current_path + ".md");
		benchmarksuite::file_handle::save_file(assemble_results_csv<registered_tests>(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << markdown << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}