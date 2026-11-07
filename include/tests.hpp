/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/tests.hpp
 */

#pragma once

#include <apache_builds.hpp>
#include <canada.hpp>
#include <citm_catalog.hpp>
#include <discord.hpp>
#include <github_events.hpp>
#include <google_maps_response.hpp>
#include <instruments.hpp>
#include <marine_ik.hpp>
#include <random.hpp>
#include <streams.hpp>
#include <twitter.hpp>

namespace tests {

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::jsonifier_generic, test_name_new, minified, test_data_type> {
		static constexpr jsonifier::parse_options parse_opts{ .minified = minified };

		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t parse(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					get_value(parser_new.template iterate<parse_opts>(json_data_in), json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name_read, jsonifier_generic_library_name, parse_test_struct>::impl(parser, json_data_in_pre);
			struct reused_parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
				}
			};
			test_data_type json_data{};
			gated_benchmark<reused_test_name, jsonifier_generic_library_name, reused_parse_test_struct>::impl(parser, json_data_in_pre, json_data);
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name_new + "-jsonifier-generic.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<json_libraries::jsonifier_generic, test_name_new, minified, test_data_type> {
		static constexpr jsonifier::parse_options parse_opts{ .minified = minified };

		inline static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t parse(jsonifier::jsonifier_core<>& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					size_t new_size{};
					for (size_t x = 0; x < json_data_in.size(); ++x) {
						if constexpr (std::is_same_v<test_data_type, bool>) {
							bool new_value{};
							get_value(parser_new.template iterate<parse_opts>(json_data_in[x]), new_value);
							test_datas.push_back(new_value);
						} else {
							get_value(parser_new.template iterate<parse_opts>(json_data_in[x]), test_datas.emplace_back());
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
			gated_benchmark<test_name_read, jsonifier_generic_library_name, parse_test_struct>::impl(parser, json_data_in);
			struct reused_parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> test_datas;
			gated_benchmark<reused_test_name, jsonifier_generic_library_name, reused_parse_test_struct>::impl(parser, json_data_in, test_datas);
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name_new + "-jsonifier-generic.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, test_data_type> {
		inline static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
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
			gated_benchmark<test_name_read, simdjson_library_name, parse_test_struct>::impl(parser, json_data_in);
			struct reused_parse_test_struct {
				inline static void before(simdjson::ondemand::parser&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> test_datas;
			gated_benchmark<reused_test_name, simdjson_library_name, reused_parse_test_struct>::impl(parser, json_data_in, test_datas);
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name_new + "-simdjson.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, test_data_type> {
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
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
				gated_benchmark<test_name_read, simdjson_library_name, parse_test_struct>::impl(parser, json_data_in_pre);
				gated_benchmark<reused_test_name, simdjson_library_name, reused_parse_test_struct>::impl(parser, json_data_in_pre, json_data);
			} catch (const std::exception& error) {
				std::cout << "simdjson Error: " << error.what() << std::endl;
			}
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name_new + "-simdjson.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename record_type, bool comma, uint64_t skip>
	struct library_traits<json_libraries::jsonifier_generic, test_name_new, minified, stream_test<record_type, comma, skip>> {
		static constexpr jsonifier::parse_options parse_opts{ .newLineDelimited = !comma, .minified = minified };

		inline static auto run(stream_input& input) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
			jsonifier::jsonifier_core<> parser;
			stream_sink<record_type> sink{};
			struct parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, stream_sink<record_type>& sink_new, std::string&) {
					sink_new.reset();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, stream_sink<record_type>& sink_new, std::string& json_data_in) {
					uint64_t index{};
					for (jsonifier::generic::generic_document<parse_opts.minified> doc: parser_new.template iterateMany<parse_opts>(json_data_in, stream_batch_size)) {
						if (index++ < skip) {
							continue;
						}
						get_value(doc, sink_new.next());
						sink_new.commit();
					}
					benchmarksuite::do_not_optimize_away(sink_new);
					return json_data_in.size();
				}
			};
			gated_benchmark<test_name_read, jsonifier_generic_library_name, parse_test_struct>::impl(parser, sink, input.json);
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = true }>(sink.output(), new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name_new + "-jsonifier-generic.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename record_type, bool comma, uint64_t skip>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, stream_test<record_type, comma, skip>> {
		static constexpr simdjson::stream_format format{ comma ? simdjson::stream_format::comma_delimited : simdjson::stream_format::whitespace_delimited };

		inline static auto run(stream_input& input) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
			simdjson::ondemand::parser parser;
#ifdef SIMDJSON_THREADS_ENABLED
			parser.threaded = false;
#endif
			stream_sink<record_type> sink{};
			struct parse_test_struct {
				inline static void before(simdjson::ondemand::parser&, stream_sink<record_type>& sink_new, std::string&) {
					sink_new.reset();
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, stream_sink<record_type>& sink_new, std::string& json_data_in) {
					uint64_t index{};
					simdjson::ondemand::document_stream docs = parser_new.iterate_many(json_data_in.data(), json_data_in.size(), stream_batch_size, format).value();
					for (auto doc: docs) {
						if (index++ < skip) {
							continue;
						}
						simdjson::ondemand::value value{ doc.get_value().value() };
						get_value(value, sink_new.next());
						sink_new.commit();
					}
					benchmarksuite::do_not_optimize_away(sink_new);
					return json_data_in.size();
				}
			};
			try {
				gated_benchmark<test_name_read, simdjson_library_name, parse_test_struct>::impl(parser, sink, input.json);
			} catch (const std::exception& error) {
				std::cout << "simdjson Error: " << error.what() << std::endl;
			}
			std::string new_string;
			jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = true }>(sink.output(), new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name_new + "-simdjson.json");
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
		return benchmarksuite::string_literal{ "#### Using the following commits:\n----\n" +
			make_commit_row<"Jsonifier (Generic)", "nihilai-collective/Jsonifier", JSONIFIER_COMMIT>() + make_commit_row<"simdjson", "simdjson/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> inline consteval auto generate_section() {
		static constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_graph + " Results [(View the data used in the following test)](./json/" + benchmarksuite::url_encode_literal<test_name_new_json>() +
			".json):\n\n" + "<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" +
			current_path + "/" + test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"1200\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result = std::format("\n#### Benchmark Methodology & Test Matrix\n\n"
										 "| Library | Active Implementation |\n"
										 "| :--- | :--- |\n"
										 "| **Jsonifier (generic)** | `{}` |\n"
										 "| **simdjson (ondemand)** | `{}` |\n\n"
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

		result +=
			"##### Implementation Details\n"
			"* **UTF-8 Validation:** Both libraries perform full UTF-8 validation in every test.\n"
			"* **Schema-Free Traversal:** Neither library is given a schema. `Jsonifier (generic)` walks its stage-1 structural tape through the re-accessible "
			"`jsonifier::generic` "
			"API; `simdjson (ondemand)` walks its On Demand API. Both fill the exact same structs through the exact same field-by-field traversal.\n"
			"* **Streaming:** `Jsonifier (generic)` uses `jsonifier::jsonifier_core::iterateMany`; `simdjson (ondemand)` uses `ondemand::parser::iterate_many` (unthreaded). "
			"Both use a 1 MiB batch size.\n\n"
			"##### Test Variants\n"
			"* **Amazon Cellphones:** Aggregates ratings per brand over `amazon_cellphones.ndjson` (from the simdjson repository; repeated to 10 MiB for the Large variant).\n"
			"* **Stream Formats:** Reads and sums `\"id\"` over generated `{\"id\",\"name\",\"payload\",\"flag\"}` documents, following simdjson's stream benchmarks, with 16- and "
			"4096-byte payloads, repeated to 16 MB to fit the sampling window.\n"
			"* **Stream:** Splits each corpus document's main record array into one document per record, repeated to 4 MiB.\n"
			"* **(NDJSON) vs. (Comma-Separated):** Documents separated by newlines, or by commas (simdjson's `stream_format::comma_delimited`, Jsonifier's "
			"`allowCommaSeparated`).\n"
			"* **Key Traversal Order:** Standard tests request keys in document order. Tests labeled `Reverse` request each object's keys backwards, forcing forward-only "
			"iterative parsers (e.g., simdjson On Demand) into sequential rescans or rewinds, degrading from $O(N)$ toward $O(N^2)$ as object size grows.\n"
			"* **Sparse:** Reads the same document as its full counterpart but requests only a small subset of fields (a few per record of the main arrays, in the spirit of "
			"Twitter Partial); all other fields are skipped by each library. `Sparse Reverse` requests that subset in reverse document order.\n\n"
			"---\n";

		result += std::format("*Environment generated via BenchmarkSuite commit: [{0}](https://github.com/nihilai-collective/benchmarksuite/commit/{0})*\n", BNCH_SWT_COMMIT);
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
			auto existing		 = std::find_if(tallies.begin(), tallies.end(), library_name_matcher{ fields.front() });
			library_tally& tally = existing != tallies.end() ? *existing : tallies.emplace_back(library_tally{ .name = fields.front() });
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

	inline std::string get_padded_json_string(const std::string& path) {
		auto raw_data = benchmarksuite::file_handle::get(path);
		raw_data.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		return raw_data;
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name_new, bool is_pod, typename... library_traits> inline void execute_test() {
		std::string full_path;
		static constexpr auto source_name{ test_name_new };
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
			test_traits<test_name_new, test_data_type, library_traits...>::run(test_datas);
		} else {
			auto json_data_in = get_padded_json_string(full_path);
			test_traits<test_name_new, test_data_type, library_traits...>::run(json_data_in);
		}
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name_new, bool is_pod, json_libraries... json_library_vals>
	inline void run_test_pair(test_registry& registry) {
		static constexpr benchmarksuite::string_literal minified_name{ test_name_new + " (Minified)" };
		static constexpr benchmarksuite::string_literal prettified_name{ test_name_new + " (Prettified)" };
		if constexpr (is_pod) {
			if (registry.select(test_name_new.operator std::string_view())) {
				execute_test<test_data_type, test_name_new, is_pod, library_traits<json_library_vals, test_name_new, true, test_data_type>...>();
			}
		} else {
			if (registry.select(minified_name.operator std::string_view())) {
				execute_test<test_data_type, minified_name, is_pod, library_traits<json_library_vals, minified_name, true, test_data_type>...>();
			}
			if (registry.select(prettified_name.operator std::string_view())) {
				execute_test<test_data_type, prettified_name, is_pod, library_traits<json_library_vals, prettified_name, false, test_data_type>...>();
			}
		}
	}

	template<benchmarksuite::string_literal test_name_new, typename test_data_type> inline void run_stream_test(stream_input& input) {
		test_traits<test_name_new, test_data_type, library_traits<json_libraries::jsonifier_generic, test_name_new, false, test_data_type>,
			library_traits<json_libraries::simdjson, test_name_new, false, test_data_type>>::run(input);
	}

	template<benchmarksuite::string_literal test_name_new> inline void run_stream_format_tests(test_registry& registry) {
		static constexpr benchmarksuite::string_literal ndjson_name{ test_name_new + " (NDJSON)" };
		static constexpr benchmarksuite::string_literal comma_name{ test_name_new + " (Comma-Separated)" };
		if (registry.select(ndjson_name.operator std::string_view())) {
			stream_input ndjson{ load_stream_input(ndjson_name.operator std::string_view(), stream_formats_target_bytes, false) };
			run_stream_test<ndjson_name, stream_test<stream_format_record, false>>(ndjson);
		}
		if (registry.select(comma_name.operator std::string_view())) {
			stream_input comma{ load_stream_input(comma_name.operator std::string_view(), stream_formats_target_bytes, true) };
			run_stream_test<comma_name, stream_test<stream_format_record, true>>(comma);
		}
	}

	template<typename record_type, typename record_type_reverse, benchmarksuite::string_literal source_name> inline void run_record_stream_tests(test_registry& registry) {
		static constexpr benchmarksuite::string_literal ndjson_name{ source_name + " Stream Test (NDJSON)" };
		static constexpr benchmarksuite::string_literal ndjson_reverse_name{ source_name + " Stream Reverse Test (NDJSON)" };
		static constexpr benchmarksuite::string_literal comma_name{ source_name + " Stream Test (Comma-Separated)" };
		static constexpr benchmarksuite::string_literal comma_reverse_name{ source_name + " Stream Reverse Test (Comma-Separated)" };
		const bool run_ndjson{ registry.select(ndjson_name.operator std::string_view()) };
		const bool run_ndjson_reverse{ registry.select(ndjson_reverse_name.operator std::string_view()) };
		if (run_ndjson || run_ndjson_reverse) {
			stream_input ndjson{ load_stream_input(ndjson_name.operator std::string_view(), record_stream_target_bytes, false) };
			if (run_ndjson) {
				run_stream_test<ndjson_name, stream_test<record_type, false>>(ndjson);
			}
			if (run_ndjson_reverse) {
				run_stream_test<ndjson_reverse_name, stream_test<record_type_reverse, false>>(ndjson);
			}
		}
		const bool run_comma{ registry.select(comma_name.operator std::string_view()) };
		const bool run_comma_reverse{ registry.select(comma_reverse_name.operator std::string_view()) };
		if (run_comma || run_comma_reverse) {
			stream_input comma{ load_stream_input(comma_name.operator std::string_view(), record_stream_target_bytes, true) };
			if (run_comma) {
				run_stream_test<comma_name, stream_test<record_type, true>>(comma);
			}
			if (run_comma_reverse) {
				run_stream_test<comma_reverse_name, stream_test<record_type_reverse, true>>(comma);
			}
		}
	}

	inline void run_all_tests(test_registry& registry) {
		run_test_pair<bool, "Bool Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<double, "Double Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<int64_t, "Int64 Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<std::string, "String Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<uint64_t, "Uint64 Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<apache_builds_message, "Apache Builds Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<apache_builds_message_reverse, "Apache Builds Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<apache_builds_sparse_message, "Apache Builds Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<apache_builds_sparse_message_reverse, "Apache Builds Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<canada_message, "Canada Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<canada_message_reverse, "Canada Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<canada_sparse_message, "Canada Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<canada_sparse_message_reverse, "Canada Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<citm_catalog_message, "CitmCatalog Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<citm_catalog_message_reverse, "CitmCatalog Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<citm_catalog_sparse_message, "CitmCatalog Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<citm_catalog_sparse_message_reverse, "CitmCatalog Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<discord_message, "Discord Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<discord_message_reverse, "Discord Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<discord_sparse_message, "Discord Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<discord_sparse_message_reverse, "Discord Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<github_events_message, "Github Events Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<github_events_message_reverse, "Github Events Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<github_events_sparse_message, "Github Events Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<github_events_sparse_message_reverse, "Github Events Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<google_maps_response_message, "Google Maps Response Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<google_maps_response_message_reverse, "Google Maps Response Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<google_maps_response_sparse_message, "Google Maps Response Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<google_maps_response_sparse_message_reverse, "Google Maps Response Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(
			registry);
		run_test_pair<instruments_message, "Instruments Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<instruments_message_reverse, "Instruments Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<instruments_sparse_message, "Instruments Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<instruments_sparse_message_reverse, "Instruments Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<marine_ik, "Marine IK Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<marine_ik_reverse, "Marine IK Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<marine_ik_sparse, "Marine IK Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<marine_ik_sparse_reverse, "Marine IK Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<random_message, "Random Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<random_message_reverse, "Random Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<random_sparse_message, "Random Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<random_sparse_message_reverse, "Random Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<twitter_message, "Twitter Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<twitter_message_reverse, "Twitter Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<twitter_sparse_message, "Twitter Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<twitter_sparse_message_reverse, "Twitter Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<apache_builds_message, "Apache Builds Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<apache_builds_message_reverse, "Apache Builds Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<apache_builds_sparse_message, "Apache Builds Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<apache_builds_sparse_message_reverse, "Apache Builds Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(
			registry);
		run_test_pair<canada_message, "Canada Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<canada_message_reverse, "Canada Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<canada_sparse_message, "Canada Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<canada_sparse_message_reverse, "Canada Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<citm_catalog_message, "CitmCatalog Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<citm_catalog_message_reverse, "CitmCatalog Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<citm_catalog_sparse_message, "CitmCatalog Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<citm_catalog_sparse_message_reverse, "CitmCatalog Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(
			registry);
		run_test_pair<discord_message, "Discord Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<discord_message_reverse, "Discord Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<discord_sparse_message, "Discord Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<discord_sparse_message_reverse, "Discord Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<github_events_message, "Github Events Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<github_events_message_reverse, "Github Events Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<github_events_sparse_message, "Github Events Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<github_events_sparse_message_reverse, "Github Events Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(
			registry);
		run_test_pair<google_maps_response_message, "Google Maps Response Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<google_maps_response_message_reverse, "Google Maps Response Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(
			registry);
		run_test_pair<google_maps_response_sparse_message, "Google Maps Response Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(
			registry);
		run_test_pair<google_maps_response_sparse_message_reverse, "Google Maps Response Small Sparse Reverse Test", false, json_libraries::jsonifier_generic,
			json_libraries::simdjson>(registry);
		run_test_pair<instruments_message, "Instruments Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<instruments_message_reverse, "Instruments Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<instruments_sparse_message, "Instruments Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<instruments_sparse_message_reverse, "Instruments Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(
			registry);
		run_test_pair<marine_ik, "Marine IK Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<marine_ik_reverse, "Marine IK Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<marine_ik_sparse, "Marine IK Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<marine_ik_sparse_reverse, "Marine IK Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<random_message, "Random Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<random_message_reverse, "Random Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<random_sparse_message, "Random Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<random_sparse_message_reverse, "Random Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<twitter_message, "Twitter Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<twitter_message_reverse, "Twitter Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<twitter_sparse_message, "Twitter Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		run_test_pair<twitter_sparse_message_reverse, "Twitter Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(registry);
		if (registry.select("Amazon Cellphones Test (NDJSON)")) {
			stream_input amazon_small{ load_stream_input("Amazon Cellphones Test (NDJSON)", 0, false) };
			run_stream_test<"Amazon Cellphones Test (NDJSON)", stream_test<amazon_cellphone_row, false, 1>>(amazon_small);
		}
		if (registry.select("Large Amazon Cellphones Test (NDJSON)")) {
			stream_input amazon_large{ load_stream_input("Large Amazon Cellphones Test (NDJSON)", large_amazon_target_bytes, false, true) };
			run_stream_test<"Large Amazon Cellphones Test (NDJSON)", stream_test<amazon_cellphone_row, false, 1>>(amazon_large);
		}
		run_stream_format_tests<"Stream Formats Small Test">(registry);
		run_stream_format_tests<"Stream Formats Large Test">(registry);
		run_record_stream_tests<job_data, job_data_reverse, "Apache Builds">(registry);
		run_record_stream_tests<performance, performance_reverse, "CitmCatalog">(registry);
		run_record_stream_tests<row, row_reverse, "Google Maps Response">(registry);
		run_record_stream_tests<pattern, pattern_reverse, "Instruments">(registry);
		run_record_stream_tests<result_data, result_data_reverse, "Random">(registry);
		run_record_stream_tests<status_data, status_data_reverse, "Twitter">(registry);
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
