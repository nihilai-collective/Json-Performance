/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/tests.hpp
 */

#pragma once

#include <package_json.hpp>

namespace tests {

	template<benchmarksuite::string_literal label, benchmarksuite::string_literal org_repo, benchmarksuite::string_literal commit> consteval auto make_commit_row() {
		return benchmarksuite::string_literal{ "| " + label + ": [" + commit + "](https://github.com/" + org_repo + "/commit/" + commit + ")  \n" };
	}

	consteval auto make_section00() {
		using system_info = benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>;
		return benchmarksuite::string_literal{ "# " + stage_name + "\nJust a bit of performance profiling of some JSON libraries (compiled and run on " + system_info::os_id + " " +
			system_info::os_version + " using the " + system_info::compiler_id + " " + system_info::compiler_version + " compiler).  \n\nLatest results: (" };
	}

	consteval auto make_section01() {
		return benchmarksuite::string_literal{ "#### Here are the commits we used:\n----\n" +
			make_commit_row<"Jsonifier (Generic)", "nihilai-collective/Jsonifier", JSONIFIER_COMMIT>() + make_commit_row<"simdjson", "simdjson/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> consteval auto generate_section() {
		constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_graph + " Results [(Here is the data we used for this test)](./json/" + benchmarksuite::url_encode_literal<test_name_new_json>() +
			".json):\n\n" + "<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" +
			current_path + "/" + test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"1200\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result =
			std::format("\n#### How We Benchmarked & What We Tested\n\n"
						"| Library | Active Implementation |\n"
						"| :--- | :--- |\n"
						"| **Jsonifier (generic)** | `{}` |\n"
						"| **simdjson (ondemand)** | `{}` |\n\n"
						"> Each library picks its own instruction-set implementation at build or run time, and these are the ones that produced the results below.\n\n",
				jsonifier::cpuArchName, simdjson::get_active_implementation()->name());

		result += std::format("> **How the sampling/convergence works ({0}):**  \n"
							  "> We double the iterations every epoch ({1} → {2} → {3} ...) up to a max of {4}.  \n"
							  "> Each epoch gets scored on a trailing window of `max(iterations/10, {5})` (capped at {6}). There is no early stopping, so the epochs just keep "
							  "going until {7}s have passed or we hit the cap.  \n"
							  "> The first epoch is only there as a fallback; the epoch that actually counts is whichever later one has the lowest (RSE + epoch-over-epoch mean "
							  "shift), converged or not.  \n"
							  "> Converged means RSE ≤ {8}% and mean shift ≤ {9}%. Non-converged results still count toward the rankings and the win/tie/loss tallies, so just "
							  "take them with a grain of salt.  \n"
							  "> Ties get called using Welch's t-test with Bessel-corrected variance.\n\n"
							  "---\n\n",
			benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name(), config.measured_iteration_count, config.measured_iteration_count * 2,
			config.measured_iteration_count * 4, config.max_iteration_count, config.min_k, config.max_k, config.max_time_in_s, config.rse_threshold, config.convergence_threshold);

		result += "##### A Few Details\n"
				  "* **Corpus:** Every unique package.json that is a JSON object in the deps/ folder of Node.js's add-jsonifier-main branch (the same set Node's "
				  "benchmark/module/package-json-corpus.js reads), split by size into the same buckets. `json/package_json/Sources.txt` tells you where each file came from.\n"
				  "* **Work per document:** Each library runs Node.js's own package.json field loop, so name, main, type, private, and the raw JSON of exports, imports "
				  "and scripts, skipping every other key. One benchmark iteration parses every document in the bucket once, reusing one parser across all of them.\n"
				  "* **Padding:** Every document gets stored with `SIMDJSON_PADDING` bytes of spare capacity, so simdjson can parse it in place without a copy.\n"
				  "* **Jsonifier:** Built from our `node` branch, which is the C++20 subset that gets vendored into Node.js.\n\n"
				  "---\n";

		result += std::format("*Generated with BenchmarkSuite commit: [{0}](https://github.com/nihilai-collective/benchmarksuite/commit/{0})*\n", BNCH_SWT_COMMIT);
		return result;
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

	inline std::string_view base_test_name(std::string_view variant_name) {
		if (variant_name.empty() || variant_name.back() != ')') {
			return variant_name;
		}
		const size_t open_pos = variant_name.rfind(" (");
		return open_pos == std::string_view::npos ? variant_name : variant_name.substr(0, open_pos);
	}

	inline std::string read_file_if_present(const std::string& path) {
		if (!std::filesystem::exists(path)) {
			return {};
		}
		return benchmarksuite::file_handle::get(path);
	}

	inline std::string result_file_stem(std::string_view result_name) {
		return std::string{ csv_out_path.operator std::string_view() } + "/" + std::string{ result_name };
	}

	class test_registry {
	  public:
		inline test_registry(int32_t argc, char** argv) {
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
				if (token == "--fresh") {
					selected_benchmark_mode = selected_benchmark_mode == benchmark_modes::reused ? benchmark_modes::all : benchmark_modes::fresh;
				} else if (token == "--reused") {
					selected_benchmark_mode = selected_benchmark_mode == benchmark_modes::fresh ? benchmark_modes::all : benchmark_modes::reused;
				} else if (token == "--minified") {
					excluded_suffix = excluded_suffix == "(Minified)" ? std::string_view{} : std::string_view{ "(Prettified)" };
				} else if (token == "--prettified") {
					excluded_suffix = excluded_suffix == "(Prettified)" ? std::string_view{} : std::string_view{ "(Minified)" };
				} else if (!token.empty()) {
					requested.emplace_back(std::move(token));
				}
				start = end + 1;
			}
		}

		inline bool select(std::string_view variant_name) {
			if (collecting) {
				variants.emplace_back(variant_name);
				return false;
			}
			return wants(variant_name) && (excluded_suffix.empty() || !variant_name.ends_with(excluded_suffix));
		}

		inline void finish_collecting() {
			collecting = false;
			std::string unknown;
			for (const auto& token: requested) {
				if (!matches_any(token)) {
					unknown += (unknown.empty() ? "" : ", ") + token;
				}
			}
			if (unknown.empty()) {
				return;
			}
			std::string message{ "Unknown test name(s): " + unknown + "\nAvailable tests:\n" };
			for (const auto& variant: variants) {
				message += "  " + variant + "\n";
			}
			throw std::runtime_error{ message };
		}

		inline std::string assemble_markdown(std::string header) const {
			for (const auto& variant: variants) {
				header += read_file_if_present(result_file_stem(variant + " Read") + ".md");
				header += read_file_if_present(result_file_stem(variant + " Read" + std::string{ reused_suffix.operator std::string_view() }) + ".md");
			}
			return header;
		}

		inline std::vector<std::string> result_csv_paths() const {
			std::vector<std::string> paths;
			paths.reserve(variants.size() * 2);
			for (const auto& variant: variants) {
				paths.emplace_back(result_file_stem(variant + " Read") + ".csv");
				paths.emplace_back(result_file_stem(variant + " Read" + std::string{ reused_suffix.operator std::string_view() }) + ".csv");
			}
			return paths;
		}

	  protected:
		std::vector<std::string> requested{};
		std::vector<std::string> variants{};
		std::string_view excluded_suffix{};
		bool collecting{ true };

		inline bool token_matches(const std::string& token, std::string_view variant_name) const {
			return token == normalize_test_name(variant_name) || token == normalize_test_name(base_test_name(variant_name));
		}

		inline bool matches_any(const std::string& token) const {
			for (const auto& variant: variants) {
				if (token_matches(token, variant)) {
					return true;
				}
			}
			return false;
		}

		inline bool wants(std::string_view variant_name) const {
			if (requested.empty()) {
				return true;
			}
			for (const auto& token: requested) {
				if (token_matches(token, variant_name)) {
					return true;
				}
			}
			return false;
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

	inline std::string assemble_results_csv(const test_registry& registry) {
		std::string current{ benchmark_stage::get_all_results().to_csv() };
		static constexpr std::string_view tally_header{ "Library,Wins,Ties,Losses" };
		const size_t header_pos = current.find(tally_header);
		std::string result{ header_pos == std::string::npos ? current : current.substr(0, header_pos + tally_header.size()) };
		result += '\n';
		std::vector<library_tally> tallies;
		for (const auto& path: registry.result_csv_paths()) {
			tally_positions(read_file_if_present(path), tallies);
		}
		std::sort(tallies.begin(), tallies.end(), std::greater<library_tally>{});
		for (const auto& tally: tallies) {
			result += std::format("{},{},{},{}\n", tally.name, tally.wins, tally.ties, tally.losses);
		}
		return result;
	}

	template<benchmarksuite::string_literal test_name_new, typename test_data_type, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ " Read" };

		template<typename library_type, typename json_input_type> inline static void run(json_input_type& json_data_new) {
			library_type::run(json_data_new);
		}

		template<typename json_input_type> inline static void run(json_input_type& json_data_new) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + test_type_string };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			(run<library_traits>(json_data_new), ...);
			report_results<test_name>();
			report_results<reused_test_name>();
		}

		template<benchmarksuite::string_literal result_name> inline static void report_results() {
			std::string json_results;
			auto results = benchmark_stage::get_test_results(result_name);
			if (results.size() == 0) {
				return;
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
				benchmarksuite::file_handle::save_file(json_results, result_file_stem(result_name.operator std::string_view()) + ".md");
			}
		}
	};

	template<benchmarksuite::string_literal test_name_new, uint64_t low, uint64_t high> inline void run_package_json_test(test_registry& registry) {
		if (!registry.select(test_name_new.operator std::string_view())) {
			return;
		}
		package_json_corpus corpus{ load_package_json_corpus(low, high) };
		package_json_parity::impl(corpus);
		test_traits<test_name_new, package_json_corpus, library_traits<json_libraries::jsonifier_generic, test_name_new, false, package_json_corpus>,
			library_traits<json_libraries::simdjson, test_name_new, false, package_json_corpus>>::run(corpus);
	}

	inline void run_all_tests(test_registry& registry) {
		run_package_json_test<"Package.json Corpus 0-512 Test", 0, 512>(registry);
		run_package_json_test<"Package.json Corpus 512-1024 Test", 512, 1024>(registry);
		run_package_json_test<"Package.json Corpus 1024-2048 Test", 1024, 2048>(registry);
		run_package_json_test<"Package.json Corpus 2048-65536 Test", 2048, 65536>(registry);
		run_package_json_test<"Package.json Corpus All Test", 0, 65536>(registry);
	}

	inline std::string write_final_results(const test_registry& registry) {
		std::string markdown{ registry.assemble_markdown(
			make_section00().operator std::string() + benchmarksuite::get_time() + ")\n" + make_section01().operator std::string() + make_section02()) };
		benchmarksuite::file_handle::save_file(markdown, base_path + "/" + current_path + ".md");
		benchmarksuite::file_handle::save_file(assemble_results_csv(registry), csv_out_path + "/Results.csv");
		return markdown;
	}

	struct interrupt_handler {
		inline static std::atomic<const test_registry*> registry{};
		inline static std::atomic_flag finalizing{};

		inline static void impl(int32_t signal_value) {
			if (finalizing.test_and_set()) {
				std::_Exit(128 + signal_value);
			}
			std::cout << "\nInterrupted, writing Results.csv and the final .md from the files on disk..." << std::endl;
			if (const test_registry* active_registry = registry.load(); active_registry) {
				try {
					write_final_results(*active_registry);
					std::cout << "Final results written." << std::endl;
				} catch (const std::exception& error) {
					std::cout << "Error while writing final results: " << error.what() << std::endl;
				}
			}
			std::_Exit(128 + signal_value);
		}

		inline static void install(const test_registry& registry_new) {
			registry.store(&registry_new);
			std::signal(SIGINT, &interrupt_handler::impl);
		}
	};

	inline void collect_test_names(test_registry& registry) {
		run_all_tests(registry);
		registry.finish_collecting();
	}

	inline void test_function(test_registry& registry) {
		interrupt_handler::install(registry);
		collect_test_names(registry);
		benchmarksuite::pin_for_benchmark();
		run_all_tests(registry);
		const std::string markdown{ write_final_results(registry) };
		std::cout << "Md Data: " << markdown << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}
