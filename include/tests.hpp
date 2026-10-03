/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/tests.hpp
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

	enum class test_types {
		parse	  = 0,
		serialize = 1,
		minify	  = 2,
		prettify  = 3,
		validate  = 4,
	};

	enum class json_libraries {
		jsonifier			= 0,
		glaze				= 1,
		simdjson			= 2,
		simdjson_reflection = 3,
		jsonifier_two_stage = 4,
	};

	template<json_libraries json_library>
	concept jsonifier_parse_library = json_library == json_libraries::jsonifier || json_library == json_libraries::jsonifier_two_stage;

	template<json_libraries json_library> struct jsonifier_parse_variant {
		static constexpr bool two_stage{ false };
		static constexpr benchmarksuite::string_literal library_name{ jsonifier_library_name };
		static constexpr benchmarksuite::string_literal file_tag{ "-jsonifier.json" };
	};

	template<> struct jsonifier_parse_variant<json_libraries::jsonifier_two_stage> {
		static constexpr bool two_stage{ true };
		static constexpr benchmarksuite::string_literal library_name{ jsonifier_two_stage_library_name };
		static constexpr benchmarksuite::string_literal file_tag{ "-jsonifier-two-stage.json" };
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

	static constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	static constexpr benchmarksuite::string_literal reused_suffix{ " (Reused)" };

	template<test_types test_type, json_libraries json_library, benchmarksuite::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<typename value_type>
	concept pod_types = std::is_same_v<bool, value_type> || std::is_same_v<std::string, value_type> || std::is_same_v<int64_t, value_type> ||
		std::is_same_v<uint64_t, value_type> || std::is_same_v<double, value_type>;

	template<json_libraries json_library, benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
		requires jsonifier_parse_library<json_library>
	struct library_traits<test_types::parse, json_library, test_name_new, minified, test_data_type> {
		using variant = jsonifier_parse_variant<json_library>;
		static auto run(const std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				static size_t parse(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					size_t new_size{};
					for (size_t x = 0; x < json_data_in.size(); ++x) {
						if constexpr (std::is_same_v<test_data_type, bool>) {
							bool new_value{};
							parser_new.parseJson<jsonifier::parse_options{ .partialRead = variant::two_stage, .minified = minified }>(new_value, json_data_in[x]);
							test_datas.push_back(new_value);
						} else {
							parser_new.parseJson<jsonifier::parse_options{ .partialRead = variant::two_stage, .minified = minified }>(test_datas.emplace_back(), json_data_in[x]);
						}
						benchmarksuite::do_not_optimize_away(test_datas.back());
						new_size += json_data_in[x].size();
					}
					return new_size;
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in) {
					std::vector<test_data_type> test_datas;
					return parse(parser_new, json_data_in, test_datas);
				}
			};
			benchmark_stage::template run_benchmark<test_name, variant::library_name, parse_test_struct>(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				static void before(jsonifier::jsonifier_core<>&, const std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> reused_datas;
			benchmark_stage::template run_benchmark<reused_test_name, variant::library_name, reused_parse_test_struct>(parser, json_data_in, reused_datas);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::vector<test_data_type> test_datas;
			parse_test_struct::parse(parser, json_data_in, test_datas);
			std::string new_string;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + variant::file_tag);
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(const std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			std::vector<test_data_type> test_datas;
			test_datas.resize(json_data_in.size());
			for (size_t x = 0; x < test_datas.size(); ++x) {
				parser.parseJson<jsonifier::parse_options{ .minified = minified }>(test_datas[x], json_data_in[x]);
			}
			struct serialize_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<test_data_type>& test_datas) {
					std::vector<std::string> json_data_out;
					json_data_out.resize(test_datas.size());
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						parser_new.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas[x], json_data_out[x]);
						benchmarksuite::do_not_optimize_away(json_data_out[x]);
						new_size += json_data_out[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, serialize_test_struct>(parser, test_datas);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_serialize_test_struct {
				static void before(jsonifier::jsonifier_core<>&, std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
					json_data_out.resize(test_datas.size());
					for (auto& value: json_data_out) {
						clear_value(value);
					}
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						parser_new.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas[x], json_data_out[x]);
						benchmarksuite::do_not_optimize_away(json_data_out[x]);
						new_size += json_data_out[x].size();
					}
					return new_size;
				}
			};
			std::vector<std::string> reused_output;
			benchmark_stage::template run_benchmark<reused_test_name, jsonifier_library_name, reused_serialize_test_struct>(parser, test_datas, reused_output);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string new_string;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<json_libraries json_library, benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
		requires jsonifier_parse_library<json_library>
	struct library_traits<test_types::parse, json_library, test_name_new, minified, test_data_type> {
		using variant = jsonifier_parse_variant<json_library>;
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool partial_read{ variant::two_stage || std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr bool known_order{ !std::is_same_v<test_data_type, twitter_partial_message> };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				static size_t parse(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					parser_new.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified }>(json_data_out, json_data_in);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name, variant::library_name, parse_test_struct>(parser, json_data_in_pre);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				static void before(jsonifier::jsonifier_core<>&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
				}
			};
			test_data_type reused_data{};
			benchmark_stage::template run_benchmark<reused_test_name, variant::library_name, reused_parse_test_struct>(parser, json_data_in_pre, reused_data);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			test_data_type json_data{};
			parse_test_struct::parse(parser, json_data_in_pre, json_data);
			std::string new_string;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + variant::file_tag);
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			test_data_type json_data{};
			parser.parseJson<jsonifier::parse_options{ .minified = minified }>(json_data, json_data_in_pre);
			struct serialize_test_struct {
				static size_t serialize(jsonifier::jsonifier_core<>& parser_new, const test_data_type& json_data_in, std::string& json_data_out) {
					parser_new.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const test_data_type& json_data_in) {
					std::string json_data_out;
					return serialize(parser_new, json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, serialize_test_struct>(parser, json_data);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_serialize_test_struct {
				static void before(jsonifier::jsonifier_core<>&, const test_data_type&, std::string& json_data_out) {
					json_data_out.clear();
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const test_data_type& json_data_in, std::string& json_data_out) {
					return serialize_test_struct::serialize(parser_new, json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			benchmark_stage::template run_benchmark<reused_test_name, jsonifier_library_name, reused_serialize_test_struct>(parser, json_data, reused_output);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string json_data_out;
			serialize_test_struct::serialize(parser, json_data, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::jsonifier, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			struct prettify_test_struct {
				static size_t prettify(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, std::string& json_data_out) {
					parser_new.prettifyJson(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					return prettify(parser_new, json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, prettify_test_struct>(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_prettify_test_struct {
				static void before(jsonifier::jsonifier_core<>&, std::string&, std::string& json_data_out) {
					json_data_out.clear();
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, std::string& json_data_out) {
					return prettify_test_struct::prettify(parser_new, json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			benchmark_stage::template run_benchmark<reused_test_name, jsonifier_library_name, reused_prettify_test_struct>(parser, json_data_in, reused_output);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string json_data_out;
			prettify_test_struct::prettify(parser, json_data_in, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::jsonifier, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			struct minify_test_struct {
				static size_t minify(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, std::string& json_data_out) {
					parser_new.minifyJson(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					return minify(parser_new, json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, minify_test_struct>(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_minify_test_struct {
				static void before(jsonifier::jsonifier_core<>&, std::string&, std::string& json_data_out) {
					json_data_out.clear();
				}

				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, std::string& json_data_out) {
					return minify_test_struct::minify(parser_new, json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			benchmark_stage::template run_benchmark<reused_test_name, jsonifier_library_name, reused_minify_test_struct>(parser, json_data_in, reused_output);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string json_data_out;
			minify_test_struct::minify(parser, json_data_in, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::validate, json_libraries::jsonifier, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			struct validate_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					if (auto result = parser_new.validateJson(json_data_in); !result) {
						benchmarksuite::do_not_optimize_away(result);
						return uint64_t{};
					}
					return json_data_in.size();
				}
			};
			jsonifier::jsonifier_core<> parser;
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, validate_test_struct>(parser, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_in, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			static constexpr glz::opts read_opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified };
			struct parse_test_struct {
				static size_t parse(std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					size_t new_size{};
					for (size_t x = 0; x < json_data_in.size(); ++x) {
						if constexpr (std::is_same_v<test_data_type, bool>) {
							bool new_value{};
							if (auto error = glz::read<read_opts>(new_value, json_data_in[x]); error) {
								std::cout << "Glaze Error: " << glz::format_error(error, json_data_in[x]) << std::endl;
							}
							test_datas.push_back(new_value);
						} else {
							if (auto error = glz::read<read_opts>(test_datas.emplace_back(), json_data_in[x]); error) {
								std::cout << "Glaze Error: " << glz::format_error(error, json_data_in[x]) << std::endl;
							}
						}
						benchmarksuite::do_not_optimize_away(test_datas.back());
						new_size += json_data_in[x].size();
					}
					return new_size;
				}

				static size_t impl(std::vector<std::string>& json_data_in) {
					std::vector<test_data_type> test_datas;
					return parse(json_data_in, test_datas);
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, parse_test_struct>(json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				static void before(std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				static size_t impl(std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> reused_datas;
			benchmark_stage::template run_benchmark<reused_test_name, glaze_library_name, reused_parse_test_struct>(json_data_in, reused_datas);
			std::vector<test_data_type> test_datas;
			parse_test_struct::parse(json_data_in, test_datas);
			std::string new_string;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(test_datas, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(const std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			static constexpr glz::opts read_opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified };
			std::vector<test_data_type> test_datas;
			test_datas.resize(json_data_in.size());
			for (size_t x = 0; x < test_datas.size(); ++x) {
				if constexpr (std::is_same_v<test_data_type, bool>) {
					bool new_value{};
					if (auto error = glz::read<read_opts>(new_value, json_data_in[x]); error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_in[x]) << std::endl;
					}
					test_datas[x] = new_value;
				} else {
					if (auto error = glz::read<read_opts>(test_datas[x], json_data_in[x]); error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_in[x]) << std::endl;
					}
				}
			}
			struct serialize_test_struct {
				static size_t impl(std::vector<test_data_type>& test_datas) {
					std::vector<std::string> json_data_out;
					json_data_out.resize(test_datas.size());
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(test_datas[x], json_data_out[x]); error) {
							std::cout << "Glaze Error: " << glz::format_error(error, json_data_out[x]) << std::endl;
						}
						benchmarksuite::do_not_optimize_away(json_data_out[x]);
						new_size += json_data_out[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, serialize_test_struct>(test_datas);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_serialize_test_struct {
				static void before(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
					json_data_out.resize(test_datas.size());
					for (auto& value: json_data_out) {
						clear_value(value);
					}
				}

				static size_t impl(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(test_datas[x], json_data_out[x]); error) {
							std::cout << "Glaze Error: " << glz::format_error(error, json_data_out[x]) << std::endl;
						}
						benchmarksuite::do_not_optimize_away(json_data_out[x]);
						new_size += json_data_out[x].size();
					}
					return new_size;
				}
			};
			std::vector<std::string> reused_output;
			benchmark_stage::template run_benchmark<reused_test_name, glaze_library_name, reused_serialize_test_struct>(test_datas, reused_output);
			std::string new_string;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(test_datas, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool partial_read{ std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> && !partial_read };
			static constexpr glz::opts read_opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified };
			struct parse_test_struct {
				static size_t parse(std::string& json_data_in, test_data_type& json_data_out) {
					if (auto error = glz::read<read_opts>(json_data_out, json_data_in); error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_in) << std::endl;
					}
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				static size_t impl(std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, parse_test_struct>(json_data_in_pre);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				static void before(std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				static size_t impl(std::string& json_data_in, test_data_type& json_data_out) {
					return parse_test_struct::parse(json_data_in, json_data_out);
				}
			};
			test_data_type reused_data{};
			benchmark_stage::template run_benchmark<reused_test_name, glaze_library_name, reused_parse_test_struct>(json_data_in_pre, reused_data);
			test_data_type json_data{};
			parse_test_struct::parse(json_data_in_pre, json_data);
			std::string new_string;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(json_data, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			test_data_type json_data{};
			if (auto error = glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
					json_data, json_data_in_pre);
				error) {
				std::cout << "Glaze Error: " << glz::format_error(error, json_data_in_pre) << std::endl;
			}
			struct serialize_test_struct {
				static size_t serialize(const test_data_type& json_data_in, std::string& json_data_out) {
					if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(json_data_in, json_data_out); error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_out) << std::endl;
					}
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(const test_data_type& json_data_in) {
					std::string json_data_out;
					return serialize(json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, serialize_test_struct>(json_data);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_serialize_test_struct {
				static void before(const test_data_type&, std::string& json_data_out) {
					json_data_out.clear();
				}

				static size_t impl(const test_data_type& json_data_in, std::string& json_data_out) {
					return serialize_test_struct::serialize(json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			benchmark_stage::template run_benchmark<reused_test_name, glaze_library_name, reused_serialize_test_struct>(json_data, reused_output);
			std::string json_data_out;
			serialize_test_struct::serialize(json_data, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::glaze, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			struct prettify_test_struct {
				static size_t prettify(std::string& json_data_in, std::string& json_data_out) {
					glz::prettify_json(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					return prettify(json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, prettify_test_struct>(json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_prettify_test_struct {
				static void before(std::string&, std::string& json_data_out) {
					json_data_out.clear();
				}

				static size_t impl(std::string& json_data_in, std::string& json_data_out) {
					return prettify_test_struct::prettify(json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			benchmark_stage::template run_benchmark<reused_test_name, glaze_library_name, reused_prettify_test_struct>(json_data_in, reused_output);
			std::string json_data_out;
			prettify_test_struct::prettify(json_data_in, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::glaze, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			struct minify_test_struct {
				static size_t minify(std::string& json_data_in, std::string& json_data_out) {
					glz::minify_json(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					return minify(json_data_in, json_data_out);
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, minify_test_struct>(json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_minify_test_struct {
				static void before(std::string&, std::string& json_data_out) {
					json_data_out.clear();
				}

				static size_t impl(std::string& json_data_in, std::string& json_data_out) {
					return minify_test_struct::minify(json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			benchmark_stage::template run_benchmark<reused_test_name, glaze_library_name, reused_minify_test_struct>(json_data_in, reused_output);
			std::string json_data_out;
			minify_test_struct::minify(json_data_in, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::validate, json_libraries::glaze, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			struct validate_test_struct {
				static size_t impl(std::string& json_data_in) {
					if (auto result = glz::validate_json(json_data_in); result) {
						std::cout << "Glaze Error: " << glz::format_error(result, json_data_in) << std::endl;
						benchmarksuite::do_not_optimize_away(result);
						return uint64_t{};
					}
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, validate_test_struct>(json_data_in);
			benchmarksuite::file_handle::save_file(json_data_in, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
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
			benchmark_stage::template run_benchmark<test_name, simdjson_library_name, parse_test_struct>(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				static void before(simdjson::ondemand::parser&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> reused_datas;
			benchmark_stage::template run_benchmark<reused_test_name, simdjson_library_name, reused_parse_test_struct>(parser, json_data_in, reused_datas);
			std::vector<test_data_type> test_datas;
			parse_test_struct::parse(parser, json_data_in, test_datas);
			std::string new_string;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(test_datas, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
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
			test_data_type json_data{};
			try {
				benchmark_stage::template run_benchmark<test_name, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre);
				parse_test_struct::parse(parser, json_data_in_pre, json_data);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_parse_test_struct {
					static void before(simdjson::ondemand::parser&, std::string&, test_data_type& json_data_out) {
						clear_value(json_data_out);
					}

					static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
						return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
					}
				};
				test_data_type reused_data{};
				benchmark_stage::template run_benchmark<reused_test_name, simdjson_library_name, reused_parse_test_struct>(parser, json_data_in_pre, reused_data);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			std::string new_string;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(json_data, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

#if SIMDJSON_STATIC_REFLECTION
	template<typename test_data_type> void simdjson_reflection_parse(simdjson::ondemand::parser& parser, std::string& json_data_in, test_data_type& json_data_out) {
		simdjson::ondemand::document document;
		auto error = parser.iterate(json_data_in.data(), json_data_in.size(), json_data_in.capacity()).get(document);
		if (!error) {
			error = document.get(json_data_out);
		}
		if (error) {
			std::cout << "Simdjson Reflection Error: " << simdjson::error_message(error) << std::endl;
		}
	}

	template<typename test_data_type> void simdjson_reflection_serialize(const test_data_type& json_data_in, std::string& json_data_out) {
		if (auto error = simdjson::to_json(json_data_in, json_data_out); error) {
			std::cout << "Simdjson Reflection Error: " << simdjson::error_message(error) << std::endl;
		}
	}

	inline simdjson::fractured_json_options make_simdjson_expanded_options() {
		simdjson::fractured_json_options options;
		options.indent_spaces			 = 3;
		options.always_expand_depth		 = 1000;
		options.enable_table_format		 = false;
		options.enable_compact_multiline = false;
		return options;
	}

	template<typename test_data_type> void simdjson_reflection_serialize_pretty(const test_data_type& json_data_in, std::string& json_data_out) {
		static const simdjson::fractured_json_options options{ make_simdjson_expanded_options() };
		if (auto error = simdjson::to_fractured_json_string(json_data_in, options).get(json_data_out); error) {
			std::cout << "Simdjson Reflection Error: " << simdjson::error_message(error) << std::endl;
		}
	}

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		static auto run(const std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			simdjson::ondemand::parser parser;
			std::vector<test_data_type> test_datas;
			for (size_t x = 0; x < json_data_in.size(); ++x) {
				std::string padded_json{ json_data_in[x] };
				padded_json.reserve(padded_json.size() + simdjson::SIMDJSON_PADDING);
				test_data_type new_value{};
				simdjson_reflection_parse(parser, padded_json, new_value);
				test_datas.push_back(std::move(new_value));
			}
			struct serialize_test_struct {
				static size_t impl(std::vector<test_data_type>& test_datas) {
					std::vector<std::string> json_data_out;
					json_data_out.resize(test_datas.size());
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						simdjson_reflection_serialize(static_cast<const test_data_type&>(test_datas[x]), json_data_out[x]);
						benchmarksuite::do_not_optimize_away(json_data_out[x]);
						new_size += json_data_out[x].size();
					}
					return new_size;
				}
			};
			try {
				benchmark_stage::template run_benchmark<test_name, simdjson_reflection_library_name, serialize_test_struct>(test_datas);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_serialize_test_struct {
					static void before(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
						json_data_out.resize(test_datas.size());
						for (auto& value: json_data_out) {
							clear_value(value);
						}
					}

					static size_t impl(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
						size_t new_size{};
						for (size_t x = 0; x < test_datas.size(); ++x) {
							simdjson_reflection_serialize(static_cast<const test_data_type&>(test_datas[x]), json_data_out[x]);
							benchmarksuite::do_not_optimize_away(json_data_out[x]);
							new_size += json_data_out[x].size();
						}
						return new_size;
					}
				};
				std::vector<std::string> reused_output;
				benchmark_stage::template run_benchmark<reused_test_name, simdjson_reflection_library_name, reused_serialize_test_struct>(test_datas, reused_output);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Reflection Error: " << error.what() << std::endl;
			}
			std::string new_string;
			simdjson_reflection_serialize(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson-reflection.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				static size_t parse(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					simdjson_reflection_parse(parser_new, json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
				}
			};
			test_data_type json_data{};
			try {
				benchmark_stage::template run_benchmark<test_name, simdjson_reflection_library_name, parse_test_struct>(parser, json_data_in_pre);
				parse_test_struct::parse(parser, json_data_in_pre, json_data);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_parse_test_struct {
					static void before(simdjson::ondemand::parser&, std::string&, test_data_type& json_data_out) {
						clear_value(json_data_out);
					}

					static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
						return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
					}
				};
				test_data_type reused_data{};
				benchmark_stage::template run_benchmark<reused_test_name, simdjson_reflection_library_name, reused_parse_test_struct>(parser, json_data_in_pre, reused_data);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Reflection Error: " << error.what() << std::endl;
			}
			std::string new_string;
			simdjson_reflection_serialize(json_data, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson-reflection.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			simdjson::ondemand::parser parser;
			test_data_type json_data{};
			simdjson_reflection_parse(parser, json_data_in_pre, json_data);
			struct serialize_test_struct {
				static size_t serialize(const test_data_type& json_data_in, std::string& json_data_out) {
					if constexpr (minified) {
						simdjson_reflection_serialize(json_data_in, json_data_out);
					} else {
						simdjson_reflection_serialize_pretty(json_data_in, json_data_out);
					}
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(const test_data_type& json_data_in) {
					std::string json_data_out;
					return serialize(json_data_in, json_data_out);
				}
			};
			std::string json_data_out;
			try {
				benchmark_stage::template run_benchmark<test_name, simdjson_reflection_library_name, serialize_test_struct>(json_data);
				serialize_test_struct::serialize(json_data, json_data_out);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_serialize_test_struct {
					static void before(const test_data_type&, std::string& json_data_out) {
						json_data_out.clear();
					}

					static size_t impl(const test_data_type& json_data_in, std::string& json_data_out) {
						return serialize_test_struct::serialize(json_data_in, json_data_out);
					}
				};
				std::string reused_output;
				benchmark_stage::template run_benchmark<reused_test_name, simdjson_reflection_library_name, reused_serialize_test_struct>(json_data, reused_output);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Reflection Error: " << error.what() << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-simdjson-reflection.json");
		}
	};
#else
	template<test_types test_type, benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_type, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		template<typename json_input_type> static void run(json_input_type&) {
		}
	};
#endif

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::simdjson, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			simdjson::dom::parser parser;
			struct minify_test_struct {
				static size_t minify(simdjson::dom::parser& parser_new, std::string& json_data_in, std::string& json_data_out) {
					json_data_out = simdjson::minify(parser_new.parse(json_data_in));
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					return minify(parser_new, json_data_in, json_data_out);
				}
			};
			std::string json_data_out;
			try {
				benchmark_stage::template run_benchmark<test_name, simdjson_library_name, minify_test_struct>(parser, json_data_in);
				minify_test_struct::minify(parser, json_data_in, json_data_out);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_minify_test_struct {
					static void before(simdjson::dom::parser&, std::string&, std::string& json_data_out) {
						json_data_out.clear();
					}

					static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in, std::string& json_data_out) {
						return minify_test_struct::minify(parser_new, json_data_in, json_data_out);
					}
				};
				std::string reused_output;
				benchmark_stage::template run_benchmark<reused_test_name, simdjson_library_name, reused_minify_test_struct>(parser, json_data_in, reused_output);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::simdjson, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			simdjson::dom::parser parser;
			struct prettify_test_struct {
				static size_t prettify(simdjson::dom::parser& parser_new, std::string& json_data_in, std::string& json_data_out) {
					simdjson::dom::element element;
					if (auto error = parser_new.parse(json_data_in).get(element); error) {
						std::cout << "Simdjson Error: " << simdjson::error_message(error) << std::endl;
						return 0;
					}
					json_data_out = simdjson::prettify(element);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					return prettify(parser_new, json_data_in, json_data_out);
				}
			};
			std::string json_data_out;
			try {
				benchmark_stage::template run_benchmark<test_name, simdjson_library_name, prettify_test_struct>(parser, json_data_in);
				prettify_test_struct::prettify(parser, json_data_in, json_data_out);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_prettify_test_struct {
					static void before(simdjson::dom::parser&, std::string&, std::string& json_data_out) {
						json_data_out.clear();
					}

					static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in, std::string& json_data_out) {
						return prettify_test_struct::prettify(parser_new, json_data_in, json_data_out);
					}
				};
				std::string reused_output;
				benchmark_stage::template run_benchmark<reused_test_name, simdjson_library_name, reused_prettify_test_struct>(parser, json_data_in, reused_output);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-simdjson.json");
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
		result.reserve(205);
		result += "#### Using the following commits:\n----\n";
		result += make_commit_row("Jsonifier", "nihilai-collective/jsonifier", JSONIFIER_COMMIT);
		result += make_commit_row("Glaze", "stephenberry/glaze", GLAZE_COMMIT);
		result += make_commit_row("Simdjson", "simdjson/simdjson", SIMDJSON_COMMIT);
		return result;
	}

	std::string make_section02() {
		std::string result;
		result.reserve(1723);
		result += "\n#### Active Implementations:\n";
		result += "| Library | Active Implementation |\n";
		result += "| ------- | --------------------- |\n";
		result += "| Jsonifier | `";
		result += jsonifier::cpu_arch_name;
		result += "` |\n";
		result += "| simdjson (ondemand) | `";
		result += simdjson::get_active_implementation()->name();
		result += "` |\n";
#if SIMDJSON_STATIC_REFLECTION
		result += "| simdjson (reflection) | `";
		result += simdjson::get_active_implementation()->name();
		result += "` |\n";
#endif
		result += "| Glaze (utf8-validation) | `";
		result += glz::simd_info.utf8_validation;
		result += "` |\n";
		result += "| Glaze (string-escape) | `";
		result += glz::simd_info.string_escape;
		result += "` |\n";
		result += "| Glaze (float-write) | `";
		result += glz::simd_info.float_write;
		result += "` |\n";
		result += "| Glaze (structural-skip) | `";
		result += glz::simd_info.structural_skip;
		result += "` |\n\n";
		result += "> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. "
				  "Glaze reports per-subsystem backends, which may differ from one another within a single build.\n\n";
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
				  "these tests. \"jsonifier\" performs fused scalar structural iteration; \"jsonifier (two-stage)\" is the same parse call routed through "
				  "structural indexing/stage-1 + stage-2. The 'partial' tests require stage-1 + stage-2, so both jsonifier rows take the two-stage path there)\n\n";
		result += "Each test is run twice. In the standard run, every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it "
				  "again inside the timed region, so allocation and deallocation are part of each measurement. In the run labelled \"(Reused)\", the object or string is "
				  "created once and held across iterations; it is cleared (keeping its capacity) outside the timed region before each iteration, so only the parse or "
				  "serialize work is measured. Parser instances are reused in both.\n\n";
		result +=
			"The \"Small\" tests use cut-down copies of the large documents, truncated by `GenerateSmallJson.py` so that each minified document is at most 5 KiB "
			"(arrays and numerically-keyed objects are shortened to as many leading entries as fit; the document structure is otherwise unchanged). "
			"They exercise per-call overhead (setup, dispatch, small allocations) rather than bulk throughput, which is where the standard and \"(Reused)\" runs differ most.\n\n";
		result += "In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.\n\n";
#if SIMDJSON_STATIC_REFLECTION
		result +=
			"`simdjson (reflection)` is simdjson 5's C++26 static-reflection API (`document.get<T>()` for reads, `simdjson::to_json` into a `std::string` for writes). "
			"Its single-pass writer emits minified JSON only (pretty output is a second FracturedJson reformatting pass), so it is absent from the prettified write tests.\n\n";
#else
		result += "`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.\n\n";
#endif
#if JSONIFIER_COMPILER_MSVC
		result +=
			"`simdjson (ondemand)` extracts each field with an individual `find_field` lookup (`find_field_unordered` for the reverse-order tests) on MSVC/Windows, rather than "
			"the `object::for_each` API used on the other platforms, because instantiating `for_each` across these test structures drives MSVC compile times to "
			"intractable levels.\n\n";
#endif
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
		std::string test_name_json{ benchmarksuite::url_encode(std::string{ test_name_new_json }) };
		std::string test_name_graph{ benchmarksuite::url_encode(std::string{ test_name_new_graph }) };
		std::string_view current_path_new{ current_path };
		std::string result;
		result.reserve(test_name_new_graph.size() + test_name_json.size() + test_name_graph.size() * 2 + current_path_new.size() * 2 + 200);
		result += "\n----\n### ";
		result += test_name_new_graph;
		result += " Results [(View the data used in the following test)](./json/";
		result += test_name_json;
		result += ".json):\n\n<p align=\"left\"><a href=\"./graphs/";
		result += current_path_new;
		result += "/";
		result += test_name_graph;
		result += "_Results.png\" target=\"_blank\"><img src=\"./graphs/";
		result += current_path_new;
		result += "/";
		result += test_name_graph;
		result += "_Results.png?raw=true\" \nalt=\"\" width=\"400\"/></p>\n\n";
		if ((test_name_new_graph.find("Reverse") != std::string_view::npos) && (test_name_new_graph.find("Read") != std::string_view::npos)) {
			result += make_reverse_note();
		}
		return result;
	}

	template<test_types test_type, benchmarksuite::string_literal test_name_new, typename test_data_type, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ [] {
			if constexpr (test_type == test_types::parse || test_type == test_types::validate) {
				return benchmarksuite::string_literal{ " Read" };
			} else {
				return benchmarksuite::string_literal{ " Write" };
			}
		}() };

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

		static std::string report_non_converged(const std::string& test_name) {
			const auto* raw_results = benchmark_stage::get_raw_test_data().find(test_name);
			if (raw_results == nullptr) {
				return {};
			}
			std::string message{ "### " + test_name + " Did Not Converge\n\nExcluded from rankings. Libraries that missed the RSE / mean-shift thresholds:\n\n" };
			for (const auto& [library_name, library_data]: raw_results->results) {
				if (!library_data.converged) {
					message += "- " + std::string{ library_name } + " (RSE " + std::to_string(library_data.final_rse) + "%)\n";
				}
			}
			message += "\n";
			std::cout << message;
			return message;
		}

		template<benchmarksuite::string_literal result_name> static std::string report_results() {
			std::string json_results;
			auto results = benchmark_stage::get_test_results(result_name);
			if (results.size() == 0) {
				return report_non_converged(result_name);
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

	template<test_types test_type, typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod = false, typename... library_traits>
	void execute_test(std::string& newer_string) {
		std::string full_path;
		full_path.reserve(json_path.size() + 1 + test_name.size() + 5);
		full_path += std::string_view{ json_path };
		full_path += "/";
		full_path += std::string_view{ test_name };
		full_path += ".json";

		if constexpr (is_pod) {
			auto test_datas = string_to_vector(benchmarksuite::file_handle::get(full_path));
			newer_string += test_traits<test_type, test_name, test_data_type, library_traits...>::run(test_datas);
		} else {
			auto json_data_in = get_padded_json_string(full_path);
			newer_string += test_traits<test_type, test_name, test_data_type, library_traits...>::run(json_data_in);
		}
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type, bool is_pod = false> void run_pod_tests(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name, is_pod, library_traits<test_types::parse, json_libraries::glaze, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name, is_pod, test_data_type>>(newer_string);
		execute_test<test_types::serialize, test_data_type, test_name, is_pod, library_traits<test_types::serialize, json_libraries::glaze, test_name, is_pod, test_data_type>,
			library_traits<test_types::serialize, json_libraries::jsonifier, test_name, is_pod, test_data_type>,
			library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name, is_pod, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_minified_pair(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name + " (Minified)", true, test_data_type>>(newer_string);
		execute_test<test_types::serialize, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::serialize, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::serialize, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name + " (Minified)", true, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_prettified_pair(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name + " (Prettified)", false, test_data_type>>(newer_string);
		execute_test<test_types::serialize, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::serialize, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name + " (Prettified)", false, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_min_pretty_tests(std::string& newer_string) {
		run_minified_pair<test_name, test_data_type>(newer_string);
		run_prettified_pair<test_name, test_data_type>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_parse_only_tests(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name + " (Minified)", true, test_data_type>>(newer_string);
		execute_test<test_types::parse, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name + " (Prettified)", false, test_data_type>>(newer_string);
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
		const std::string_view jsonifier_names[]{ jsonifier_library_name.operator std::string_view(), jsonifier_two_stage_library_name.operator std::string_view() };
		uint64_t wins{};
		uint64_t ties{};
		uint64_t losses{};
		for (const auto& test: benchmark_stage::get_finished_tests()) {
			const ranked_rows<std::remove_cvref_t<decltype(test)>> ranked{ test };
			uint64_t best_jsonifier_position{ unranked };
			for (const auto& row: ranked.rows()) {
				if (std::ranges::find(jsonifier_names, std::string_view{ row.name }) != std::end(jsonifier_names)) {
					best_jsonifier_position = std::min(best_jsonifier_position, row.position);
				}
			}
			if (best_jsonifier_position == unranked) {
				continue;
			}
			bool tied_with_other_library{};
			for (const auto& row: ranked.rows()) {
				if (std::ranges::find(jsonifier_names, std::string_view{ row.name }) == std::end(jsonifier_names) && row.position == best_jsonifier_position) {
					tied_with_other_library = true;
				}
			}
			if (tied_with_other_library) {
				++ties;
			} else if (best_jsonifier_position == 1) {
				++wins;
			} else {
				++losses;
			}
		}
		if (!stage_csv.empty() && stage_csv.back() != '\n') {
			stage_csv += "\n";
		}
		stage_csv += "jsonifier (combined)," + std::to_string(wins) + "," + std::to_string(ties) + "," + std::to_string(losses) + "\n";
		return stage_csv;
	}

	void test_function() {
		static_assert(std::string_view{ jsonifier::cpu_arch_name }.find("AVX512") != std::string::npos, "Sorry, but this build requires AVX512");
		std::string newer_string{ make_section00() + benchmarksuite::get_time() + ")\n" + make_section01() + make_section02() };
		benchmarksuite::pin_for_benchmark();
		/*
		run_pod_tests<"Bool Test", bool, true>(newer_string);
		run_pod_tests<"Double Test", double, true>(newer_string);
		run_pod_tests<"Int64 Test", int64_t, true>(newer_string);
		run_pod_tests<"String Test", std::string, true>(newer_string);
		run_pod_tests<"Uint64 Test", uint64_t, true>(newer_string);*/
		run_min_pretty_tests<"Canada Test", canada_message>(newer_string);
		run_min_pretty_tests<"CitmCatalog Test", citm_catalog_message>(newer_string); /*
		run_min_pretty_tests<"Discord Test", discord_message>(newer_string);
		run_min_pretty_tests<"Google Maps Response Test", google_maps_response_message>(newer_string);
		run_min_pretty_tests<"Instruments Test", instruments_message>(newer_string);
		run_min_pretty_tests<"Marine IK Reverse Test", marine_ik_reverse>(newer_string);
		run_min_pretty_tests<"Marine IK Test", marine_ik>(newer_string);
		run_min_pretty_tests<"Mesh Test", mesh_message>(newer_string);
		run_min_pretty_tests<"Random Test", random_message>(newer_string);*/
		run_parse_only_tests<"Twitter Partial Test", twitter_partial_message>(newer_string);
		run_min_pretty_tests<"Twitter Test", twitter_message>(newer_string);
		/*
		run_min_pretty_tests<"Canada Small Test", canada_message>(newer_string);
		run_min_pretty_tests<"CitmCatalog Small Test", citm_catalog_message>(newer_string);
		run_min_pretty_tests<"Discord Small Test", discord_message>(newer_string);
		run_min_pretty_tests<"Google Maps Response Small Test", google_maps_response_message>(newer_string);
		run_min_pretty_tests<"Instruments Small Test", instruments_message>(newer_string);
		run_min_pretty_tests<"Marine IK Reverse Small Test", marine_ik_reverse>(newer_string);
		run_min_pretty_tests<"Marine IK Small Test", marine_ik>(newer_string);
		run_min_pretty_tests<"Mesh Small Test", mesh_message>(newer_string);
		run_min_pretty_tests<"Random Small Test", random_message>(newer_string);
		run_parse_only_tests<"Twitter Partial Small Test", twitter_partial_message>(newer_string);
		run_min_pretty_tests<"Twitter Small Test", twitter_message>(newer_string);
		execute_test<test_types::minify, std::string, "Minify Test", false, library_traits<test_types::minify, json_libraries::glaze, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::jsonifier, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::simdjson, "Minify Test", false, std::string>>(newer_string);
		execute_test<test_types::prettify, std::string, "Prettify Test", false,
			library_traits<test_types::prettify, json_libraries::jsonifier, "Prettify Test", false, std::string>,
			library_traits<test_types::prettify, json_libraries::glaze, "Prettify Test", false, std::string>,
			library_traits<test_types::prettify, json_libraries::simdjson, "Prettify Test", false, std::string>>(newer_string);
		execute_test<test_types::validate, std::string, "Validate Test", false,
			library_traits<test_types::validate, json_libraries::jsonifier, "Validate Test", false, std::string>,
			library_traits<test_types::validate, json_libraries::glaze, "Validate Test", false, std::string>>(newer_string);*/
		benchmarksuite::file_handle::save_file(newer_string, base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(with_combined_jsonifier_tally(stage_results.to_csv()), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}