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
		jsonifier = 0,
		glaze	  = 1,
		simdjson  = 2,
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
		.max_time_in_s																			   = 20,
		.rse_threshold																			   = rse_threshold };

	static constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Jsonifier vs Glaze vs simdjson" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<test_types test_type, json_libraries json_library, benchmarksuite::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<typename value_type>
	concept pod_types = std::is_same_v<bool, value_type> || std::is_same_v<std::string, value_type> || std::is_same_v<int64_t, value_type> ||
		std::is_same_v<uint64_t, value_type> || std::is_same_v<double, value_type>;

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(const std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			jsonifier::jsonifier_core<> parser;
			std::vector<test_data_type> test_datas;
			test_datas.resize(json_data_in.size());
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<test_data_type>& test_datas, const std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						parser_new.parseJson<jsonifier::parse_options{ .minified = minified }>(test_datas[x], json_data_in[x]);
						benchmarksuite::do_not_optimize_away(test_datas[x]);
						new_size += json_data_in[x].size();
					}
					return new_size;
				}
			};
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, parse_test_struct>(parser, test_datas, json_data_in);
			std::string new_string;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-jsonifier.json");
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
			std::vector<std::string> json_data_out;
			json_data_out.resize(json_data_in.size());
			struct serialize_test_struct {
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
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, serialize_test_struct>(parser, test_datas, json_data_out);
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

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool partial_read{ std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr bool known_order{ true };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out;
					parser_new.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified }>(
						json_data_out, json_data_in);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			test_data_type json_data_out;
			parser.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified }>(json_data_out,
				json_data_in_pre);
			std::string new_string;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data_out, new_string);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-jsonifier.json");
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			test_data_type json_data;
			parser.parseJson<jsonifier::parse_options{ .minified = minified }>(json_data, json_data_in_pre);
			std::string json_data_in;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			struct serialize_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const test_data_type& json_data_in) {
					std::string json_data_out;
					parser_new.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, serialize_test_struct>(parser, json_data);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(static_cast<std::string>(json_data_in), json_out_path + "/" + test_name + "-jsonifier.json");
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::jsonifier, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			std::string json_data_out;
			parser.prettifyJson(json_data_in, json_data_out);
			struct prettify_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					parser_new.prettifyJson(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, prettify_test_struct>(parser, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-jsonifier.json");
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::jsonifier, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			std::string json_data_out;
			parser.minifyJson(json_data_in, json_data_out);
			struct minify_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					parser_new.minifyJson(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, minify_test_struct>(parser, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-jsonifier.json");
			return;
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
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			std::vector<test_data_type> test_datas;
			test_datas.resize(json_data_in.size());
			using value_type = test_data_type;
			struct parse_test_struct {
				static size_t impl(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						if constexpr (std::is_same_v<value_type, bool>) {
							bool new_value;
							if (auto error =
									glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
										new_value, json_data_in[x]);
								error) {
								std::cout << "Glaze Error: " << glz::format_error(error, json_data_in[x]) << std::endl;
							}
							test_datas[x] = new_value;
						} else {
							if (auto error =
									glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
										test_datas[x], json_data_in[x]);
								error) {
								std::cout << "Glaze Error: " << glz::format_error(error, json_data_in[x]) << std::endl;
							}
						}
						benchmarksuite::do_not_optimize_away(test_datas[x]);
						new_size += json_data_in[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, parse_test_struct>(test_datas, json_data_in);
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
			std::vector<test_data_type> test_datas;
			test_datas.resize(json_data_in.size());
			using value_type = test_data_type;
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			for (size_t x = 0; x < test_datas.size(); ++x) {
				if constexpr (std::is_same_v<value_type, bool>) {
					bool new_value;
					if (auto error =
							glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
								new_value, json_data_in[x]);
						error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_in[x]) << std::endl;
					}
					test_datas[x] = new_value;
				} else {
					if (auto error =
							glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
								test_datas[x], json_data_in[x]);
						error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_in[x]) << std::endl;
					}
				}
			}
			std::vector<std::string> json_data_out;
			json_data_out.resize(json_data_in.size());
			struct serialize_test_struct {
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
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, serialize_test_struct>(test_datas, json_data_out);
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
			struct parse_test_struct {
				static size_t impl(std::string& json_data_in) {
					test_data_type json_data_out;
					if (auto error =
							glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
								json_data_out, json_data_in);
						error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_in) << std::endl;
					}
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, parse_test_struct>(json_data_in_pre);
			test_data_type json_data_out;
			if (auto error = glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
					json_data_out, json_data_in_pre);
				error) {
				std::cout << "Glaze Error: " << glz::format_error(error, json_data_in_pre) << std::endl;
			}
			std::string new_string;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(json_data_out, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-glaze.json");
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			test_data_type json_data;
			if (auto error = glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
					json_data, json_data_in_pre);
				error) {
				std::cout << "Glaze Error: " << glz::format_error(error, json_data_in_pre) << std::endl;
			}
			std::string json_data_in;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(json_data, json_data_in); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, json_data_in) << std::endl;
			}
			struct serialize_test_struct {
				static size_t impl(const test_data_type& json_data_in) {
					std::string json_data_out;
					if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(json_data_in, json_data_out); error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_out) << std::endl;
					}
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, serialize_test_struct>(json_data);
			benchmarksuite::file_handle::save_file(json_data_in, json_out_path + "/" + test_name + "-glaze.json");
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::glaze, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			std::string json_data_out;
			glz::prettify_json(json_data_in, json_data_out);
			struct prettify_test_struct {
				static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					glz::prettify_json(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, prettify_test_struct>(json_data_in);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-glaze.json");
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::glaze, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			std::string json_data_out;
			glz::minify_json(json_data_in, json_data_out);
			struct minify_test_struct {
				static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					glz::minify_json(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, minify_test_struct>(json_data_in);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-glaze.json");
			return;
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
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			simdjson::ondemand::parser parser;
			using value_type = test_data_type;
			std::vector<test_data_type> test_datas;
			test_datas.resize(json_data_in.size());
			struct parse_test_struct {
				static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						if constexpr (std::is_same_v<value_type, bool>) {
							bool new_value;
							get_value(parser_new.iterate(json_data_in[x].data(), json_data_in[x].size(), json_data_in[x].capacity()), new_value);
							test_datas[x] = new_value;
						} else {
							get_value(parser_new.iterate(json_data_in[x].data(), json_data_in[x].size(), json_data_in[x].capacity()), test_datas[x]);
						}
						benchmarksuite::do_not_optimize_away(test_datas[x]);
						new_size += json_data_in[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name, simdjson_library_name, parse_test_struct>(parser, test_datas, json_data_in);
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
				static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in) {
					test_data_type json_data_out;
					get_value(parser_new.iterate(json_data_in.data(), json_data_in.size(), json_data_in.capacity()), json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre);
			std::string new_string;
			test_data_type json_data_out;
			try {
				get_value(parser.iterate(json_data_in_pre), json_data_out);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(json_data_out, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::simdjson, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			simdjson::dom::parser parser;
			std::string json_data_out;
			try {
				json_data_out = simdjson::minify(parser.parse(json_data_in));
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			struct minify_test_struct {
				static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					json_data_out = simdjson::minify(parser_new.parse(json_data_in));
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, simdjson_library_name, minify_test_struct>(parser, json_data_in);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-simdjson.json");
			return;
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
		result += ". Convergence requires RSE < ";
		result += std::to_string(config.rse_threshold);
		result += "% AND mean shift < ";
		result += std::to_string(config.convergence_threshold);
		result += "% epoch-over-epoch simultaneously. ";
		result += "The first epoch satisfying both conditions is retained as the canonical result. ";
		result += "If convergence is never reached before ";
		result += std::to_string(config.max_time_in_s);
		result += " seconds elapse or the iteration cap is hit, the result is marked non-converged and ";
		result += "excluded from all rankings — only converged results participate in win/tie/loss tallying. ";
		result += "All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.\n\n##### (All of the libraries are performing UTF8-validation in "
				  "these tests. Jsonifier is only performing \"structural "
				  "indexing/stage-1 + stage-2\" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)\n\n";
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
		execute_test<test_types::parse, test_data_type, test_name, is_pod, library_traits<test_types::parse, json_libraries::jsonifier, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name, is_pod, test_data_type>>(newer_string);
		execute_test<test_types::serialize, test_data_type, test_name, is_pod, library_traits<test_types::serialize, json_libraries::jsonifier, test_name, is_pod, test_data_type>,
			library_traits<test_types::serialize, json_libraries::glaze, test_name, is_pod, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_minified_pair(std::string& newer_string) {
		//execute_test<test_types::parse, test_data_type, test_name + " (Minified)", false,
		//library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
		//library_traits<test_types::parse, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
		//			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Minified)", true, test_data_type>>(newer_string);
		//execute_test<test_types::serialize, test_data_type, test_name + " (Minified)", false,
		//			library_traits<test_types::serialize, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
		//			library_traits<test_types::serialize, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_prettified_pair(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Prettified)", false, test_data_type>>(newer_string);
		//execute_test<test_types::serialize, test_data_type, test_name + " (Prettified)", false,
		//library_traits<test_types::serialize, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
		//library_traits<test_types::serialize, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_min_pretty_tests(std::string& newer_string) {
		//run_minified_pair<test_name, test_data_type>(newer_string);
		run_prettified_pair<test_name, test_data_type>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_parse_only_tests(std::string& newer_string) {
		//execute_test<test_types::parse, test_data_type, test_name + " (Minified)", false,
		//library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
		//library_traits<test_types::parse, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
		//library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Minified)", true, test_data_type>>(newer_string);
		execute_test<test_types::parse, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Prettified)", false, test_data_type>>(newer_string);
	}

	void test_function() {
		std::string newer_string{ make_section00() + benchmarksuite::get_time() + ")\n" + make_section01() + make_section02() };
		benchmarksuite::pin_for_benchmark();
		//run_pod_tests<"Double Test", double, true>(newer_string);
		//run_pod_tests<"Uint64 Test", uint64_t, true>(newer_string);
		//run_pod_tests<"Int64 Test", int64_t, true>(newer_string);
		//run_pod_tests<"Bool Test", bool, true>(newer_string);
		//run_pod_tests<"String Test", std::string, true>(newer_string);
		run_min_pretty_tests<"Canada Test", canada_message>(newer_string);
		run_min_pretty_tests<"CitmCatalog Test", citm_catalog_message>(newer_string);
		run_min_pretty_tests<"Discord Test", discord_message>(newer_string);
		run_min_pretty_tests<"Google Maps Response Test", google_maps_response_message>(newer_string);
		run_min_pretty_tests<"Instruments Test", instruments_message>(newer_string);
		run_min_pretty_tests<"Marine IK Reverse Test", marine_ik_reverse>(newer_string);
		run_min_pretty_tests<"Marine IK Test", marine_ik>(newer_string);
		run_min_pretty_tests<"Mesh Test", mesh_message>(newer_string);
		run_min_pretty_tests<"Random Test", random_message>(newer_string);
		run_parse_only_tests<"Twitter Partial Test", twitter_partial_message>(newer_string);
		run_min_pretty_tests<"Twitter Test", twitter_message>(newer_string);
		/*
		execute_test<test_types::minify, std::string, "Minify Test", false, library_traits<test_types::minify, json_libraries::jsonifier, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::glaze, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::simdjson, "Minify Test", false, std::string>>(newer_string);
		execute_test<test_types::prettify, std::string, "Prettify Test", false,
			library_traits<test_types::prettify, json_libraries::jsonifier, "Prettify Test", false, std::string>,
			library_traits<test_types::prettify, json_libraries::glaze, "Prettify Test", false, std::string>>(newer_string);
		execute_test<test_types::validate, std::string, "Validate Test", false,
			library_traits<test_types::validate, json_libraries::jsonifier, "Validate Test", false, std::string>,
			library_traits<test_types::validate, json_libraries::glaze, "Validate Test", false, std::string>>(newer_string);*/
		benchmarksuite::file_handle::save_file(newer_string, base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}