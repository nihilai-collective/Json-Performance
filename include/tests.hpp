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
#include <streams.hpp>

namespace tests {

	enum class json_libraries {
		jsonifier_generic = 0,
		simdjson		  = 1,
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
		.max_time_in_s																			   = 4,
		.rse_threshold																			   = rse_threshold };

	static constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Generic Parsing & Streaming vs simdjson On Demand" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<json_libraries json_library, benchmarksuite::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<typename value_type>
	concept pod_types = std::is_same_v<bool, value_type> || std::is_same_v<std::string, value_type> || std::is_same_v<int64_t, value_type> ||
		std::is_same_v<uint64_t, value_type> || std::is_same_v<double, value_type>;

	static constexpr benchmarksuite::string_literal reused_suffix{ " (Reused)" };

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<json_libraries::jsonifier_generic, test_name_new, minified, test_data_type> {
		static constexpr jsonifier::parse_options parse_opts{ .minified = minified };

		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			jsonifier::generic::parser<> parser;
			struct parse_test_struct {
				static size_t parse(jsonifier::generic::parser<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					get_value(parser_new.iterate<parse_opts>(json_data_in), json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				static size_t impl(jsonifier::generic::parser<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_generic_library_name, parse_test_struct>(parser, json_data_in_pre);
			struct reused_parse_test_struct {
				static void before(jsonifier::generic::parser<>&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				static size_t impl(jsonifier::generic::parser<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
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

		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			jsonifier::generic::parser<> parser;
			struct parse_test_struct {
				static size_t parse(jsonifier::generic::parser<>& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
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

				static size_t impl(jsonifier::generic::parser<>& parser_new, std::vector<std::string>& json_data_in) {
					std::vector<test_data_type> test_datas;
					return parse(parser_new, json_data_in, test_datas);
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_generic_library_name, parse_test_struct>(parser, json_data_in);
			struct reused_parse_test_struct {
				static void before(jsonifier::generic::parser<>&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				static size_t impl(jsonifier::generic::parser<>& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
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
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				static size_t parse(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
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

				static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in) {
					std::vector<test_data_type> test_datas;
					return parse(parser_new, json_data_in, test_datas);
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in);
			struct reused_parse_test_struct {
				static void before(simdjson::ondemand::parser&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
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
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new };
			static constexpr benchmarksuite::string_literal test_name_read{ test_name + " Read" };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name_read + reused_suffix };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				static size_t parse(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					get_value(parser_new.iterate(json_data_in.data(), json_data_in.size(), json_data_in.capacity()), json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
				}
			};
			struct reused_parse_test_struct {
				static void before(simdjson::ondemand::parser&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
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

	template<typename test_data_type, benchmarksuite::string_literal test_name> static constexpr auto source_file_name() {
		if constexpr (is_iterate_only<test_data_type>::value) {
			return test_data_type::source_name;
		} else {
			return test_name;
		}
	}

	template<benchmarksuite::string_literal test_name_new, bool minified, typename record_type, bool comma, uint64_t skip>
	struct library_traits<json_libraries::jsonifier_generic, test_name_new, minified, stream_test<record_type, comma, skip>> {
		static constexpr jsonifier::parse_options parse_opts{ .newLineDelimited = !comma };

		static auto run(stream_input& input) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
			jsonifier::generic::parser<> parser;
			stream_sink<record_type> sink{};
			struct parse_test_struct {
				static void before(jsonifier::generic::parser<>&, stream_sink<record_type>& sink_new, std::string&) {
					sink_new.reset();
				}

				static size_t impl(jsonifier::generic::parser<>& parser_new, stream_sink<record_type>& sink_new, std::string& json_data_in) {
					uint64_t index{};
					for (jsonifier::generic::document doc: parser_new.template iterateMany<parse_opts>(json_data_in, stream_batch_size)) {
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
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_generic_library_name, parse_test_struct>(parser, sink, input.json);
			std::string new_string;
jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = true }>(sink.output(), new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name_new + "-jsonifier-generic.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename record_type, bool comma, uint64_t skip>
	struct library_traits<json_libraries::simdjson, test_name_new, minified, stream_test<record_type, comma, skip>> {
		static constexpr simdjson::stream_format format{ comma ? simdjson::stream_format::comma_delimited : simdjson::stream_format::whitespace_delimited };

		static auto run(stream_input& input) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
			simdjson::ondemand::parser parser;
#ifdef SIMDJSON_THREADS_ENABLED
			parser.threaded = false;
#endif
			stream_sink<record_type> sink{};
			struct parse_test_struct {
				static void before(simdjson::ondemand::parser&, stream_sink<record_type>& sink_new, std::string&) {
					sink_new.reset();
				}

				static size_t impl(simdjson::ondemand::parser& parser_new, stream_sink<record_type>& sink_new, std::string& json_data_in) {
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
				benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, sink, input.json);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			std::string new_string;
jsonifier::jsonifier_core<> jsonifier_parser{};
			[[maybe_unused]] auto new_result = jsonifier_parser.serializeJson<jsonifier::serialize_options{ .prettify = true }>(sink.output(), new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name_new + "-simdjson.json");
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
		result += make_commit_row("Jsonifier (Generic)", "nihilai-collective/jsonifier", JSONIFIER_COMMIT);
		result += make_commit_row("Simdjson (On Demand)", "simdjson/simdjson", SIMDJSON_COMMIT);
		return result;
	}

	std::string make_section02() {
		std::string result;
		result.reserve(1403);
		result += "\n#### Active Implementations:\n";
		result += "| Library | Active Implementation |\n";
		result += "| ------- | --------------------- |\n";
		result += "| Jsonifier (generic) | `";
		result += jsonifier::activeBackendName();
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
		result += "All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.\n\n##### (Both libraries are performing UTF8-validation in "
				  "these tests. Neither library is given a schema: \"jsonifier (generic)\" walks its stage-1 structural tape through the schema-free, re-accessible "
				  "jsonifier::generic API, and \"simdjson (ondemand)\" walks its On Demand API, with both filling the exact same structs through the exact same "
				  "field-by-field traversal. In the streaming tests, \"jsonifier (generic)\" walks each document of the stream through "
				  "jsonifier::generic::parser::iterateMany, and \"simdjson (ondemand)\" walks each document through ondemand::parser::iterate_many (unthreaded), "
				  "using the same 1 MiB batch size)\n\n";
		result += "The \"Amazon Cellphones\" tests aggregate ratings per brand over amazon_cellphones.ndjson (from the simdjson repository; repeated to 10 MiB "
				  "for the Large variant). The \"Stream Formats\" tests read and sum \"id\" over generated {\"id\",\"name\",\"payload\",\"flag\"} documents, "
				  "following simdjson's stream benchmarks, with 16- and 4096-byte payloads, repeated to 16 MB to fit the sampling window. The \"Stream\" tests split the main record "
				  "array of each corpus document into one document per record, repeated to 4 MiB. \"(NDJSON)\" tests separate documents with newlines; "
				  "\"(Comma-Separated)\" tests separate them with commas (simdjson's stream_format::comma_delimited, Jsonifier's allowCommaSeparated).\n\n";
		result += "Every test whose name contains \"Reverse\" deliberately requests each object's keys in the reverse of their order in the JSON document; "
				  "every other test requests them in document order. The reverse tests exercise out-of-order access, which forces forward-only iterative "
				  "parsers such as simdjson's On Demand API into sequential rescans (or rewinds), degrading from O(N) toward O(N^2) as object size grows.\n\n";
		result += "Every test whose name contains \"Sparse\" reads the same document as its full counterpart but requests only a small subset of its fields "
				  "(a few fields from each record of the document's main arrays, in the spirit of the Twitter Partial test); every other field is skipped by each library. "
				  "\"Sparse Reverse\" tests request that subset in the reverse of its document order.\n\n";
		result += "#### Note:\n  This is the commit of BenchmarkSuite that was used to generate these results: [";
		result += BNCH_SWT_COMMIT;
		result += "](https://github.com/nihilai-collective/benchmarksuite/commit/";
		result += BNCH_SWT_COMMIT;
		result += ").\n  ";
		return result;
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
		return result;
	}

	template<benchmarksuite::string_literal test_name_new, typename test_data_type, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ " Read" };

		template<typename library_type, typename json_input_type> static void run(json_input_type& json_data_new) {
			library_type::run(json_data_new);
		}

		template<typename json_input_type> static std::string run(json_input_type& json_data_new) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + test_type_string };
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			(run<library_traits>(json_data_new), ...);
			std::string json_results{ report_results<test_name>() };
			json_results += report_results<reused_test_name>();
			return json_results;
		}

		template<benchmarksuite::string_literal result_name> static std::string report_results() {
			std::string json_results;
			auto results = benchmark_stage::get_test_results(result_name);
			if (results.size() == 0) {
				return json_results;
			}
			results.print(false);
			if (results.size() > 1) {
				json_results += generate_section(result_name, test_name_new);
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

	std::string get_padded_json_string(const std::string& path) {
		auto raw_data = benchmarksuite::file_handle::get(path);
		raw_data.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		return raw_data;
	}

	template<typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod, typename... library_traits> void execute_test(std::string& newer_string) {
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

	template<typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod, json_libraries... json_library_vals> void run_test_pair(std::string& newer_string) {
		if constexpr (is_pod) {
			execute_test<test_data_type, test_name, is_pod, library_traits<json_library_vals, test_name, true, test_data_type>...>(newer_string);
		} else {
			execute_test<test_data_type, test_name + " (Minified)", is_pod, library_traits<json_library_vals, test_name + " (Minified)", true, test_data_type>...>(newer_string);
			execute_test<test_data_type, test_name + " (Prettified)", is_pod, library_traits<json_library_vals, test_name + " (Prettified)", false, test_data_type>...>(
				newer_string);
		}
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_stream_test(std::string& newer_string, stream_input& input) {
		newer_string += test_traits<test_name, test_data_type, library_traits<json_libraries::jsonifier_generic, test_name, false, test_data_type>,
			library_traits<json_libraries::simdjson, test_name, false, test_data_type>>::run(input);
	}

	template<benchmarksuite::string_literal test_name> void run_stream_format_tests(std::string& newer_string) {
		static constexpr benchmarksuite::string_literal ndjson_name{ test_name + " (NDJSON)" };
		static constexpr benchmarksuite::string_literal comma_name{ test_name + " (Comma-Separated)" };
		stream_input ndjson{ load_stream_input(ndjson_name.operator std::string_view(), stream_formats_target_bytes, false) };
		run_stream_test<ndjson_name, stream_test<stream_format_record, false>>(newer_string, ndjson);
		stream_input comma{ load_stream_input(comma_name.operator std::string_view(), stream_formats_target_bytes, true) };
		run_stream_test<comma_name, stream_test<stream_format_record, true>>(newer_string, comma);
	}

	template<typename record_type, typename record_type_reverse, benchmarksuite::string_literal source_name> void run_record_stream_tests(std::string& newer_string) {
		static constexpr benchmarksuite::string_literal ndjson_name{ source_name + " Stream Test (NDJSON)" };
		static constexpr benchmarksuite::string_literal comma_name{ source_name + " Stream Test (Comma-Separated)" };
		stream_input ndjson{ load_stream_input(ndjson_name.operator std::string_view(), record_stream_target_bytes, false) };
		run_stream_test<ndjson_name, stream_test<record_type, false>>(newer_string, ndjson);
		run_stream_test<source_name + " Stream Reverse Test (NDJSON)", stream_test<record_type_reverse, false>>(newer_string, ndjson);
		stream_input comma{ load_stream_input(comma_name.operator std::string_view(), record_stream_target_bytes, true) };
		run_stream_test<comma_name, stream_test<record_type, true>>(newer_string, comma);
		run_stream_test<source_name + " Stream Reverse Test (Comma-Separated)", stream_test<record_type_reverse, true>>(newer_string, comma);
	}

	void test_function() {
		std::string newer_string{ make_section00() + benchmarksuite::get_time() + ")\n" + make_section01() + make_section02() };
		benchmarksuite::pin_for_benchmark();
		run_test_pair<bool, "Bool Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<double, "Double Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<int64_t, "Int64 Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<std::string, "String Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<uint64_t, "Uint64 Test", true, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_message, "Canada Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_message_reverse, "Canada Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_sparse_message, "Canada Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_sparse_message_reverse, "Canada Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_message, "CitmCatalog Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_message_reverse, "CitmCatalog Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_sparse_message, "CitmCatalog Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_sparse_message_reverse, "CitmCatalog Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_message, "Discord Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_message_reverse, "Discord Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_sparse_message, "Discord Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_sparse_message_reverse, "Discord Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_message, "Google Maps Response Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_message_reverse, "Google Maps Response Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_sparse_message, "Google Maps Response Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_sparse_message_reverse, "Google Maps Response Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_message, "Instruments Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_message_reverse, "Instruments Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_sparse_message, "Instruments Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_sparse_message_reverse, "Instruments Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik, "Marine IK Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik_reverse, "Marine IK Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik_sparse, "Marine IK Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik_sparse_reverse, "Marine IK Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_message, "Mesh Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_message_reverse, "Mesh Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_sparse_message, "Mesh Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_sparse_message_reverse, "Mesh Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<random_message, "Random Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<random_message_reverse, "Random Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<random_sparse_message, "Random Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<random_sparse_message_reverse, "Random Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_message, "Twitter Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_message_reverse, "Twitter Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_sparse_message, "Twitter Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_sparse_message_reverse, "Twitter Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_message, "Canada Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_message_reverse, "Canada Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_sparse_message, "Canada Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<canada_sparse_message_reverse, "Canada Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_message, "CitmCatalog Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_message_reverse, "CitmCatalog Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_sparse_message, "CitmCatalog Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<citm_catalog_sparse_message_reverse, "CitmCatalog Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_message, "Discord Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_message_reverse, "Discord Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_sparse_message, "Discord Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<discord_sparse_message_reverse, "Discord Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_message, "Google Maps Response Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_message_reverse, "Google Maps Response Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_sparse_message, "Google Maps Response Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<google_maps_response_sparse_message_reverse, "Google Maps Response Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_message, "Instruments Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_message_reverse, "Instruments Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_sparse_message, "Instruments Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<instruments_sparse_message_reverse, "Instruments Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik, "Marine IK Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik_reverse, "Marine IK Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik_sparse, "Marine IK Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<marine_ik_sparse_reverse, "Marine IK Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_message, "Mesh Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_message_reverse, "Mesh Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_sparse_message, "Mesh Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<mesh_sparse_message_reverse, "Mesh Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<random_message, "Random Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<random_message_reverse, "Random Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<random_sparse_message, "Random Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<random_sparse_message_reverse, "Random Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_message, "Twitter Small Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_message_reverse, "Twitter Small Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_sparse_message, "Twitter Small Sparse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		run_test_pair<twitter_sparse_message_reverse, "Twitter Small Sparse Reverse Test", false, json_libraries::jsonifier_generic, json_libraries::simdjson>(newer_string);
		{
			stream_input amazon_small{ load_stream_input("Amazon Cellphones Test (NDJSON)", 0, false) };
			run_stream_test<"Amazon Cellphones Test (NDJSON)", stream_test<amazon_cellphone_row, false, 1>>(newer_string, amazon_small);
			stream_input amazon_large{ load_stream_input("Large Amazon Cellphones Test (NDJSON)", large_amazon_target_bytes, false, true) };
			run_stream_test<"Large Amazon Cellphones Test (NDJSON)", stream_test<amazon_cellphone_row, false, 1>>(newer_string, amazon_large);
		}
		run_stream_format_tests<"Stream Formats Small Test">(newer_string);
		run_stream_format_tests<"Stream Formats Large Test">(newer_string);
		run_record_stream_tests<performance, performance_reverse, "CitmCatalog">(newer_string);
		run_record_stream_tests<row, row_reverse, "Google Maps Response">(newer_string);
		run_record_stream_tests<pattern, pattern_reverse, "Instruments">(newer_string);
		run_record_stream_tests<result_data, result_data_reverse, "Random">(newer_string);
		run_record_stream_tests<status_data, status_data_reverse, "Twitter">(newer_string);
		benchmarksuite::file_handle::save_file(static_cast<std::string>(newer_string), base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}