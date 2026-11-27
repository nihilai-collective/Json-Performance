/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/tests.hpp
 */

#pragma once

#include <apache_builds.hpp>
#include <array>
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
			gated_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>::impl(parser, json_data_in_pre);
			struct reused_parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
				}
			};
			test_data_type json_data{};
			gated_benchmark<reused_test_name, jsonifier_library_name, reused_parse_test_struct>::impl(parser, json_data_in_pre, json_data);
			std::string new_string;
			[[maybe_unused]] auto new_result = parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
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
			gated_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>::impl(parser, json_data_in);
			struct reused_parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> test_datas;
			gated_benchmark<reused_test_name, jsonifier_library_name, reused_parse_test_struct>::impl(parser, json_data_in, test_datas);
			std::string new_string;
			[[maybe_unused]] auto new_result = parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
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
			gated_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>::impl(parser, sink, input.json);
			std::string new_string;
			[[maybe_unused]] auto new_result = parser.serializeJson<jsonifier::serialize_options{ .prettify = true }>(sink.output(), new_string);
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
		static constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_graph + " Results [(Here is the data we used for this test)](./json/" + benchmarksuite::url_encode_literal<test_name_new_json>() +
			".json):\n\n" + "<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" +
			current_path + "/" + test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"1200\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result = std::format("\n#### How We Benchmarked & What We Tested\n\n"
										 "| Library | Active Implementation |\n"
										 "| :--- | :--- |\n"
										 "| **Jsonifier (generic)** | `{}` |\n"
										 "| **simdjson (ondemand)** | `{}` |\n\n"
										 "> SIMD paths above are whatever each library picked at build/run time on this box.\n\n",
			jsonifier::cpuArchName, simdjson::get_active_implementation()->name());

		result += std::format("> **Sampling ({0}):**  \n"
							  "> Iterations: {1} → {2} → {3} ... (max {4}), doubling per epoch.  \n"
							  "> Window: last `max(iterations/10, {5})` samples (max {6}). Runs for {7}s or until the cap.  \n"
							  "> Epoch used: lowest RSE + mean shift (1st epoch is just a fallback).  \n"
							  "> Converged = RSE ≤ {8}% and mean shift ≤ {9}%. Non-converged ones still get ranked.  \n"
							  "> Ties: Welch's t-test (Bessel-corrected).\n\n"
							  "---\n\n",
			benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name(), config.measured_iteration_count, config.measured_iteration_count * 2,
			config.measured_iteration_count * 4, config.max_iteration_count, config.min_k, config.max_k, config.max_time_in_s, config.rse_threshold, config.convergence_threshold);

		result +=
			"##### A Few Details\n"
			"* **UTF-8 Validation:** Full validation, both libraries, every test.\n"
			"* **Schema-Free Traversal:** No schemas. `Jsonifier (generic)` walks its stage-1 tape via `jsonifier::generic`, `simdjson (ondemand)` walks On Demand. "
			"Same structs, same field-by-field fill.\n"
			"* **Streaming:** `jsonifier_core::iterateMany` vs `ondemand::parser::iterate_many` (unthreaded), 1 MiB batches.\n\n"
			"##### The Test Variants\n"
			"* **Amazon Cellphones:** Ratings per brand over `amazon_cellphones.ndjson` (from the simdjson repo, 10 MiB for Large).\n"
			"* **Stream Formats:** Sums `\"id\"` over `{\"id\",\"name\",\"payload\",\"flag\"}` docs (same as simdjson's stream benchmarks), 16/4096-byte payloads, 16 MB total.\n"
			"* **Stream:** Each corpus doc's main record array, split into one doc per record, 4 MiB total.\n"
			"* **(NDJSON) vs. (Comma-Separated):** Newline vs comma separators (simdjson `stream_format::comma_delimited`, Jsonifier `allowCommaSeparated`).\n"
			"* **Key Traversal Order:** Standard = document order. `Reverse` = each object's keys backwards, worst case for forward-only parsers like simdjson On Demand "
			"($O(N^2)$ rescans).\n"
			"* **Sparse:** Same doc, only a few fields per record of the main arrays (like Twitter Partial). `Sparse Reverse` = same fields, reversed.\n\n"
			"---\n";

		result += "*Generated with BenchmarkSuite commit: [" + std::string{ BNCH_SWT_COMMIT } + "](https://github.com/nihilai-collective/benchmarksuite/commit/" +
			std::string{ BNCH_SWT_COMMIT } + ")*\n";
		return result;
	}

	inline std::string normalize_test_name(std::string_view name_new) {
		std::string result;
		result.reserve(name_new.size());
		bool space_pending{ false };
		for (char value: name_new) {
			if (value == '(' || value == ')') {
				continue;
			}
			if (value == ' ' || value == '\t') {
				space_pending = !result.empty();
				continue;
			}
			if (space_pending) {
				result += ' ';
				space_pending = false;
			}
			result += (value >= 'A' && value <= 'Z') ? static_cast<char>(value + ('a' - 'A')) : value;
		}
		return result;
	}

	inline std::string read_file_if_present(const std::string& path) {
		try {
			return benchmarksuite::file_handle::get(path);
		} catch (const std::runtime_error&) {
			return {};
		}
	}

	inline std::string result_file_stem(std::string_view result_name) {
		return std::string{ csv_out_path.operator std::string_view() } + "/" + std::string{ result_name };
	}

	struct test_descriptor {
		std::string_view base_name{};
		std::string_view name{};
		test_flags flags{};
	};

	inline std::string result_name(const test_descriptor& descriptor_new) {
		return std::string{ descriptor_new.name } + " Read";
	}

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

		inline test_flags runtime_mask() const {
			return mask;
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
				message += "  " + result_name(descriptor) + "\n";
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
			if (token == "--fresh") {
				return test_flags::fresh;
			}
			if (token == "--reused") {
				return test_flags::reused;
			}
			return test_flags::none;
		}

		inline static bool token_matches(const std::string& token, const test_descriptor& descriptor) {
			return token == normalize_test_name(result_name(descriptor)) || token == normalize_test_name(descriptor.name) || token == normalize_test_name(descriptor.base_name);
		}

		inline bool axis_allows(test_flags flags_new, test_flags axis_new) const {
			return !has_flags(flags_new, axis_new) || has_flags(flags_new & mask, axis_new);
		}

		inline bool allows(test_flags flags_new) const {
			return axis_allows(flags_new, test_flags::formats) && axis_allows(flags_new, test_flags::modes);
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
		static constexpr test_flags modes{ flags & test_flags::modes };
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

		inline static void run(const test_selection& selection_new) {
			const std::vector<size_t> indices{ selection_new.resolve(descriptors) };
			benchmarksuite::pin_for_benchmark();
			for (const size_t index: indices) {
				active_test_flags = descriptors[index].flags & selection_new.runtime_mask();
				test_dispatcher<std::index_sequence_for<variants...>, variants...>::impl(index);
			}
		}
	};

	template<typename... entries> using test_registry = test_registry_impl<typename test_group<entries...>::variants>;

	template<typename registry> inline std::vector<std::string> result_stems() {
		std::vector<std::string> stems;
		stems.reserve(registry::descriptors.size() * 2);
		for (const auto& descriptor: registry::descriptors) {
			const std::string name{ result_name(descriptor) };
			stems.emplace_back(result_file_stem(name));
			stems.emplace_back(result_file_stem(name + std::string{ reused_suffix.operator std::string_view() }));
		}
		return stems;
	}

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

	template<typename registry> inline std::string assemble_results_csv() {
		std::string current{ benchmark_stage::get_all_results().to_csv() };
		static constexpr std::string_view tally_header{ "Library,Wins,Ties,Losses" };
		const size_t header_pos = current.find(tally_header);
		std::string result{ header_pos == std::string::npos ? current : current.substr(0, header_pos + tally_header.size()) };
		result += '\n';
		std::vector<library_tally> tallies;
		for (const auto& stem: result_stems<registry>()) {
			tally_positions(read_file_if_present(stem + ".csv"), tallies);
		}
		std::sort(tallies.begin(), tallies.end(), std::greater<library_tally>{});
		for (const auto& tally: tallies) {
			result += tally.name + "," + std::to_string(tally.wins) + "," + std::to_string(tally.ties) + "," + std::to_string(tally.losses) + "\n";
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
		static constexpr std::string_view reverse_tag{ " Reverse" };
		static constexpr std::string_view sparse_tag{ " Sparse" };
		if (const size_t reverse_pos = full_path.find(" Reverse Test"); reverse_pos != std::string::npos) {
			full_path.erase(reverse_pos, reverse_tag.size());
		}
		if (const size_t sparse_pos = full_path.find(" Sparse Test"); sparse_pos != std::string::npos) {
			full_path.erase(sparse_pos, sparse_tag.size());
		}

		if constexpr (is_pod) {
			auto test_datas = string_to_vector(benchmarksuite::file_handle::get(full_path));
			test_traits<test_name_new, test_data_type, library_traits...>::run(test_datas);
		} else {
			auto json_data_in = get_padded_json_string(full_path);
			test_traits<test_name_new, test_data_type, library_traits...>::run(json_data_in);
		}
	}

	template<benchmarksuite::string_literal test_name_new, typename test_data_type> inline void run_stream_test(stream_input& input) {
		test_traits<test_name_new, test_data_type, library_traits<json_libraries::jsonifier_generic, test_name_new, false, test_data_type>,
			library_traits<json_libraries::simdjson, test_name_new, false, test_data_type>>::run(input);
	}

	using generic_libraries = library_list<json_libraries::jsonifier_generic, json_libraries::simdjson>;

	template<benchmarksuite::string_literal base_name_new, typename test_data_type, bool pod_new, test_flags flags_new, typename libraries> struct test_variant;

	template<benchmarksuite::string_literal base_name_new, typename test_data_type, bool pod_new, test_flags flags_new, json_libraries... json_library>
	struct test_variant<base_name_new, test_data_type, pod_new, flags_new, library_list<json_library...>> {
		static constexpr benchmarksuite::string_literal name{ base_name_new + format_suffix<flags_new & test_flags::formats>::value };
		static constexpr test_flags flags{ flags_new & (test_flags::formats | test_flags::modes) };
		static constexpr benchmarksuite::string_literal base_name{ base_name_new };
		static constexpr test_descriptor descriptor{ .base_name = base_name, .name = name, .flags = flags };
		static constexpr bool traits_flag{ pod_new || has_flags(flags_new, test_flags::minified) };
		using variants = type_list<test_variant>;

		inline static void execute() {
			execute_test<test_data_type, name, pod_new, library_traits<json_library, name, traits_flag, test_data_type>...>();
		}
	};

	template<bool comma_separated> struct stream_suffix {
		static constexpr benchmarksuite::string_literal value{ " (NDJSON)" };
	};

	template<> struct stream_suffix<true> {
		static constexpr benchmarksuite::string_literal value{ " (Comma-Separated)" };
	};

	template<benchmarksuite::string_literal base_name_new, benchmarksuite::string_literal input_base_name_new, typename stream_type_new, size_t target_bytes_new,
		bool comma_separated_new, bool skip_header_new, test_flags flags_new>
	struct stream_variant {
		static constexpr benchmarksuite::string_literal input_name{ input_base_name_new + stream_suffix<comma_separated_new>::value };
		static constexpr benchmarksuite::string_literal name{ base_name_new + stream_suffix<comma_separated_new>::value };
		static constexpr test_flags flags{ flags_new & test_flags::modes };
		static constexpr benchmarksuite::string_literal base_name{ base_name_new };
		static constexpr test_descriptor descriptor{ .base_name = base_name, .name = name, .flags = flags };
		using variants = type_list<stream_variant>;

		inline static void execute() {
			stream_input input{ load_stream_input(input_name.operator std::string_view(), target_bytes_new, comma_separated_new, skip_header_new) };
			run_stream_test<name, stream_type_new>(input);
		}
	};

	template<benchmarksuite::string_literal base_name, typename test_data_type, test_flags flags_new = test_flags::all> struct pod_tests {
		using set	   = flag_set<flags_new>;
		using variants = type_list<test_variant<base_name, test_data_type, true, set::modes, generic_libraries>>;
	};

	template<benchmarksuite::string_literal base_name, typename test_data_type, test_flags flags_new = test_flags::all> struct json_tests {
		using set = flag_set<flags_new>;
		static constexpr test_flags prettified_flags{ test_flags::prettified | set::modes };
		static constexpr test_flags minified_flags{ test_flags::minified | set::modes };
		using variants = typename test_group<keep_if<set::minified, test_variant<base_name, test_data_type, false, minified_flags, generic_libraries>>,
			keep_if<set::prettified, test_variant<base_name, test_data_type, false, prettified_flags, generic_libraries>>>::variants;
	};

	template<benchmarksuite::string_literal base_name_new, benchmarksuite::string_literal input_base_name_new, typename record_type_new, size_t target_bytes_new,
		test_flags flags_new = test_flags::all>
	struct stream_tests {
		using set	   = flag_set<flags_new>;
		using variants = type_list<stream_variant<base_name_new, input_base_name_new, stream_test<record_type_new, false>, target_bytes_new, false, false, set::modes>,
			stream_variant<base_name_new, input_base_name_new, stream_test<record_type_new, true>, target_bytes_new, true, false, set::modes>>;
	};

	template<benchmarksuite::string_literal base_name_new, typename stream_type_new, size_t target_bytes_new, bool skip_header_new, test_flags flags_new = test_flags::all>
	struct ndjson_test {
		using set	   = flag_set<flags_new>;
		using variants = type_list<stream_variant<base_name_new, base_name_new, stream_type_new, target_bytes_new, false, skip_header_new, set::modes>>;
	};

	using registered_tests = test_registry<pod_tests<"Bool Test", bool>, pod_tests<"Double Test", double>, pod_tests<"Int64 Test", int64_t>, pod_tests<"String Test", std::string>,
		pod_tests<"Uint64 Test", uint64_t>, json_tests<"Apache Builds Test", apache_builds_message>, json_tests<"Apache Builds Reverse Test", apache_builds_message_reverse>,
		json_tests<"Apache Builds Sparse Test", apache_builds_sparse_message>, json_tests<"Apache Builds Sparse Reverse Test", apache_builds_sparse_message_reverse>,
		json_tests<"Canada Test", canada_message>, json_tests<"Canada Reverse Test", canada_message_reverse>, json_tests<"Canada Sparse Test", canada_sparse_message>,
		json_tests<"Canada Sparse Reverse Test", canada_sparse_message_reverse>, json_tests<"CitmCatalog Test", citm_catalog_message>,
		json_tests<"CitmCatalog Reverse Test", citm_catalog_message_reverse>, json_tests<"CitmCatalog Sparse Test", citm_catalog_sparse_message>,
		json_tests<"CitmCatalog Sparse Reverse Test", citm_catalog_sparse_message_reverse>, json_tests<"Discord Test", discord_message>,
		json_tests<"Discord Reverse Test", discord_message_reverse>, json_tests<"Discord Sparse Test", discord_sparse_message>,
		json_tests<"Discord Sparse Reverse Test", discord_sparse_message_reverse>, json_tests<"Github Events Test", github_events_message>,
		json_tests<"Github Events Reverse Test", github_events_message_reverse>, json_tests<"Github Events Sparse Test", github_events_sparse_message>,
		json_tests<"Github Events Sparse Reverse Test", github_events_sparse_message_reverse>, json_tests<"Google Maps Response Test", google_maps_response_message>,
		json_tests<"Google Maps Response Reverse Test", google_maps_response_message_reverse>, json_tests<"Google Maps Response Sparse Test", google_maps_response_sparse_message>,
		json_tests<"Google Maps Response Sparse Reverse Test", google_maps_response_sparse_message_reverse>, json_tests<"Instruments Test", instruments_message>,
		json_tests<"Instruments Reverse Test", instruments_message_reverse>, json_tests<"Instruments Sparse Test", instruments_sparse_message>,
		json_tests<"Instruments Sparse Reverse Test", instruments_sparse_message_reverse>, json_tests<"Marine IK Test", marine_ik>,
		json_tests<"Marine IK Reverse Test", marine_ik_reverse>, json_tests<"Marine IK Sparse Test", marine_ik_sparse>,
		json_tests<"Marine IK Sparse Reverse Test", marine_ik_sparse_reverse>, json_tests<"Random Test", random_message>, json_tests<"Random Reverse Test", random_message_reverse>,
		json_tests<"Random Sparse Test", random_sparse_message>, json_tests<"Random Sparse Reverse Test", random_sparse_message_reverse>,
		json_tests<"Twitter Test", twitter_message>, json_tests<"Twitter Reverse Test", twitter_message_reverse>, json_tests<"Twitter Sparse Test", twitter_sparse_message>,
		json_tests<"Twitter Sparse Reverse Test", twitter_sparse_message_reverse>, json_tests<"Apache Builds Small Test", apache_builds_message>,
		json_tests<"Apache Builds Small Reverse Test", apache_builds_message_reverse>, json_tests<"Apache Builds Small Sparse Test", apache_builds_sparse_message>,
		json_tests<"Apache Builds Small Sparse Reverse Test", apache_builds_sparse_message_reverse>, json_tests<"Canada Small Test", canada_message>,
		json_tests<"Canada Small Reverse Test", canada_message_reverse>, json_tests<"Canada Small Sparse Test", canada_sparse_message>,
		json_tests<"Canada Small Sparse Reverse Test", canada_sparse_message_reverse>, json_tests<"CitmCatalog Small Test", citm_catalog_message>,
		json_tests<"CitmCatalog Small Reverse Test", citm_catalog_message_reverse>, json_tests<"CitmCatalog Small Sparse Test", citm_catalog_sparse_message>,
		json_tests<"CitmCatalog Small Sparse Reverse Test", citm_catalog_sparse_message_reverse>, json_tests<"Discord Small Test", discord_message>,
		json_tests<"Discord Small Reverse Test", discord_message_reverse>, json_tests<"Discord Small Sparse Test", discord_sparse_message>,
		json_tests<"Discord Small Sparse Reverse Test", discord_sparse_message_reverse>, json_tests<"Github Events Small Test", github_events_message>,
		json_tests<"Github Events Small Reverse Test", github_events_message_reverse>, json_tests<"Github Events Small Sparse Test", github_events_sparse_message>,
		json_tests<"Github Events Small Sparse Reverse Test", github_events_sparse_message_reverse>, json_tests<"Google Maps Response Small Test", google_maps_response_message>,
		json_tests<"Google Maps Response Small Reverse Test", google_maps_response_message_reverse>,
		json_tests<"Google Maps Response Small Sparse Test", google_maps_response_sparse_message>,
		json_tests<"Google Maps Response Small Sparse Reverse Test", google_maps_response_sparse_message_reverse>, json_tests<"Instruments Small Test", instruments_message>,
		json_tests<"Instruments Small Reverse Test", instruments_message_reverse>, json_tests<"Instruments Small Sparse Test", instruments_sparse_message>,
		json_tests<"Instruments Small Sparse Reverse Test", instruments_sparse_message_reverse>, json_tests<"Marine IK Small Test", marine_ik>,
		json_tests<"Marine IK Small Reverse Test", marine_ik_reverse>, json_tests<"Marine IK Small Sparse Test", marine_ik_sparse>,
		json_tests<"Marine IK Small Sparse Reverse Test", marine_ik_sparse_reverse>, json_tests<"Random Small Test", random_message>,
		json_tests<"Random Small Reverse Test", random_message_reverse>, json_tests<"Random Small Sparse Test", random_sparse_message>,
		json_tests<"Random Small Sparse Reverse Test", random_sparse_message_reverse>, json_tests<"Twitter Small Test", twitter_message>,
		json_tests<"Twitter Small Reverse Test", twitter_message_reverse>, json_tests<"Twitter Small Sparse Test", twitter_sparse_message>,
		json_tests<"Twitter Small Sparse Reverse Test", twitter_sparse_message_reverse>,
		ndjson_test<"Amazon Cellphones Test", stream_test<amazon_cellphone_row, false, 1>, 0, false>,
		ndjson_test<"Large Amazon Cellphones Test", stream_test<amazon_cellphone_row, false, 1>, large_amazon_target_bytes, true>,
		stream_tests<"Stream Formats Small Test", "Stream Formats Small Test", stream_format_record, stream_formats_target_bytes>,
		stream_tests<"Stream Formats Large Test", "Stream Formats Large Test", stream_format_record, stream_formats_target_bytes>,
		stream_tests<"Apache Builds Stream Test", "Apache Builds Stream Test", job_data, record_stream_target_bytes>,
		stream_tests<"Apache Builds Stream Reverse Test", "Apache Builds Stream Test", job_data_reverse, record_stream_target_bytes>,
		stream_tests<"CitmCatalog Stream Test", "CitmCatalog Stream Test", performance, record_stream_target_bytes>,
		stream_tests<"CitmCatalog Stream Reverse Test", "CitmCatalog Stream Test", performance_reverse, record_stream_target_bytes>,
		stream_tests<"Google Maps Response Stream Test", "Google Maps Response Stream Test", row, record_stream_target_bytes>,
		stream_tests<"Google Maps Response Stream Reverse Test", "Google Maps Response Stream Test", row_reverse, record_stream_target_bytes>,
		stream_tests<"Instruments Stream Test", "Instruments Stream Test", pattern, record_stream_target_bytes>,
		stream_tests<"Instruments Stream Reverse Test", "Instruments Stream Test", pattern_reverse, record_stream_target_bytes>,
		stream_tests<"Random Stream Test", "Random Stream Test", result_data, record_stream_target_bytes>,
		stream_tests<"Random Stream Reverse Test", "Random Stream Test", result_data_reverse, record_stream_target_bytes>,
		stream_tests<"Twitter Stream Test", "Twitter Stream Test", status_data, record_stream_target_bytes>,
		stream_tests<"Twitter Stream Reverse Test", "Twitter Stream Test", status_data_reverse, record_stream_target_bytes>>;

	inline std::string write_final_results() {
		std::string markdown{ make_section00().operator std::string() + benchmarksuite::get_time() + ")\n" + make_section01().operator std::string() + make_section02() };
		for (const auto& stem: result_stems<registered_tests>()) {
			markdown += read_file_if_present(stem + ".md");
		}
		benchmarksuite::file_handle::save_file(markdown, base_path + "/" + current_path + ".md");
		benchmarksuite::file_handle::save_file(assemble_results_csv<registered_tests>(), csv_out_path + "/Results.csv");
		return markdown;
	}

	struct interrupt_handler {
		inline static std::atomic_flag finalizing{};

		inline static void impl(int32_t signal_new) {
			if (finalizing.test_and_set()) {
				std::exit(128 + signal_new);
			}
			std::cout << "\nInterrupted, writing Results.csv and the final .md from the files on disk..." << std::endl;
			try {
				write_final_results();
				std::cout << "Final results written." << std::endl;
			} catch (const std::exception& error) {
				std::cout << "Error while writing final results: " << error.what() << std::endl;
			}
			std::exit(128 + signal_new);
		}

		inline static void install() {
			std::signal(SIGINT, &interrupt_handler::impl);
		}
	};

	inline void test_function(const test_selection& selection) {
		interrupt_handler::install();
		registered_tests::run(selection);
		const std::string markdown{ write_final_results() };
		std::cout << "Md Data: " << markdown << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}