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

	static constexpr benchmarksuite::stage_config_data config{ .clear_cpu_caches_before_iterations = true,
		.measured_iteration_count																   = measured_iteration_count,
		.max_iteration_count																	   = max_iteration_count,
		.max_time_in_s																			   = 10 };

	static constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Jsonifier vs Glaze vs simdjson" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	template<test_types test_type, json_libraries json_library, benchmarksuite::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<typename value_type>
	concept pod_types = std::is_same_v<std::vector<bool>, value_type> || std::is_same_v<std::vector<std::string>, value_type> || std::is_same_v<std::vector<int64_t>, value_type> ||
		std::is_same_v<std::vector<uint64_t>, value_type> || std::is_same_v<std::vector<double>, value_type>;

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			jsonifier::jsonifier_core<> parser;
			test_data_type test_datas;
			test_datas.resize(json_data_in.size());
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, test_data_type& test_datas, std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						parser_new.parseJson<jsonifier::parse_options{ .minified = minified, .validateUtf8 = true }>(test_datas[x], json_data_in[x]);
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
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			test_data_type test_datas;
			test_datas.resize(json_data_in.size());
			for (size_t x = 0; x < test_datas.size(); ++x) {
				parser.parseJson<jsonifier::parse_options{ .minified = minified, .validateUtf8 = true }>(test_datas[x], json_data_in[x]);
			}
			std::vector<std::string> json_data_out;
			json_data_out.resize(json_data_in.size());
			struct serialize_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, test_data_type& test_datas, std::vector<std::string>& json_data_out) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						parser_new.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas[x], json_data_out[x]);
						benchmarksuite::do_not_optimize_away(json_data_out[x]);
						new_size += json_data_out[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, serialize_test_struct>(parser, test_datas, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool partial_read{ std::is_same_v<test_data_type, abc_in_order_partial_test> || std::is_same_v<test_data_type, abc_out_of_order_partial_test> ||
				std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr bool known_order{ !std::is_same_v<test_data_type, abc_out_of_order_test> };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out;
					parser_new.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified, .validateUtf8 = true }>(
						json_data_out, json_data_in);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			return;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			test_data_type json_data;
			parser.parseJson<jsonifier::parse_options{ .minified = minified, .validateUtf8 = true }>(json_data, json_data_in_pre);
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
			test_data_type test_datas;
			test_datas.resize(json_data_in.size());
			using value_type = typename test_data_type::value_type;
			struct parse_test_struct {
				static size_t impl(test_data_type& test_datas, std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						if constexpr (std::is_same_v<value_type, std::vector<bool>::value_type>) {
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
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			test_data_type test_datas;
			test_datas.resize(json_data_in.size());
			using value_type = typename test_data_type::value_type;
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			for (size_t x = 0; x < test_datas.size(); ++x) {
				if constexpr (std::is_same_v<value_type, std::vector<bool>::value_type>) {
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
				static size_t impl(test_data_type& test_datas, std::vector<std::string>& json_data_out) {
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
			static constexpr bool partial_read{ std::is_same_v<test_data_type, abc_in_order_partial_test> || std::is_same_v<test_data_type, abc_out_of_order_partial_test> ||
				std::is_same_v<test_data_type, twitter_partial_message> };
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
			using value_type = typename test_data_type::value_type;
			test_data_type test_datas;
			test_datas.resize(json_data_in.size());
			struct parse_test_struct {
				static size_t impl(simdjson::ondemand::parser& parser_new, test_data_type& test_datas, std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						if constexpr (std::is_same_v<value_type, std::vector<bool>::value_type>) {
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
		result.reserve(384);
		result += "#### Using the following commits:\n----\n";
		result += make_commit_row("Jsonifier", "nihilai-collective/jsonifier", JSONIFIER_COMMIT);
		result += make_commit_row("Glaze", "stephenberry/glaze", GLAZE_COMMIT);
		result += make_commit_row("Simdjson", "simdjson/simdjson", SIMDJSON_COMMIT);
		return result;
	}

	std::string make_section02(std::string_view cpu_name, std::string_view jsonifier_cpu_name, std::string_view simdjson_cpu_name, std::string_view glaze_utf8_name,
		std::string_view glaze_escape_name, std::string_view glaze_float_name) {
		std::string stream;
		stream.reserve(2048);
		stream += "\n#### Active Implementations:\n";
		stream += "| Library | Active Implementation |\n";
		stream += "| ------- | --------------------- |\n";
		stream += "| Jsonifier | `";
		stream += jsonifier_cpu_name;
		stream += "` |\n";
		stream += "| simdjson (ondemand) | `";
		stream += simdjson_cpu_name;
		stream += "` |\n";
		stream += "| Glaze (utf8-validation) | `";
		stream += glaze_utf8_name;
		stream += "` |\n";
		stream += "| Glaze (string-escape) | `";
		stream += glaze_escape_name;
		stream += "` |\n";
		stream += "| Glaze (float-write) | `";
		stream += glaze_float_name;
		stream += "` |\n\n";
		stream += "> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. "
				  "Glaze reports per-subsystem backends, which may differ from one another within a single build.\n\n";
		stream += "> Adaptive sampling on (";
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
		stream += "All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.\n\n##### (All of the libraries are performing UTF8-validation in "
				  "these tests. Jsonifier is only performing \"structural "
				  "indexing/stage-1 + stage-2\" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)\n\n";
		stream += "#### Note:\n  This is the commit of BenchmarkSuite that was used to generate these results: [";
		stream += BNCH_SWT_COMMIT;
		stream += "](https://github.com/realtimechris/benchmarksuite/commit/";
		stream += BNCH_SWT_COMMIT;
		stream += ").\n  ";
		stream.shrink_to_fit();
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
		if ((test_name_new_graph.find("Out of Order") != std::string_view::npos) && (test_name_new_graph.find("Read") != std::string_view::npos)) {
			result += make_abc_note();
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

	template<benchmarksuite::string_literal test_name, typename test_data_type, bool is_pod = false> void run_pod_pair(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name, is_pod, library_traits<test_types::parse, json_libraries::jsonifier, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name, is_pod, test_data_type>>(newer_string);
		execute_test<test_types::serialize, test_data_type, test_name, is_pod, library_traits<test_types::serialize, json_libraries::jsonifier, test_name, is_pod, test_data_type>,
			library_traits<test_types::serialize, json_libraries::glaze, test_name, is_pod, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_minified_pair(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Minified)", true, test_data_type>>(newer_string);
		execute_test<test_types::serialize, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::serialize, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_prettified_pair(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Prettified)", false, test_data_type>>(newer_string);
		execute_test<test_types::serialize, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::serialize, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_min_pretty_quad(std::string& newer_string) {
		run_minified_pair<test_name, test_data_type>(newer_string);
		run_prettified_pair<test_name, test_data_type>(newer_string);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> void run_parse_only_pair(std::string& newer_string) {
		execute_test<test_types::parse, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Minified)", true, test_data_type>>(newer_string);
		execute_test<test_types::parse, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Prettified)", false, test_data_type>>(newer_string);
	}

	void test_function() {
		const std::string jsonifier_cpu_name{ jsonifier::cpu_arch_name };
		const std::string simdjson_cpu_name{ simdjson::get_active_implementation().operator*().name() };
		const std::string glaze_utf8_name{ glz::simd_info.utf8_validation };
		const std::string glaze_escape_name{ glz::simd_info.string_escape };
		const std::string glaze_float_name{ glz::simd_info.float_write };
		std::string cpu_name{ benchmarksuite::internal::get_device_info<benchmarksuite::benchmark_types::cpu>() };
		cpu_name += "-";
		cpu_name += benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::instruction_set_name;
		std::string newer_string{ make_section00(benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::os_id,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::os_version,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::compiler_id,
									  benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::compiler_version) +
			benchmarksuite::get_time() + ")\n" + make_section01() +
			make_section02(cpu_name, jsonifier_cpu_name, simdjson_cpu_name, glaze_utf8_name, glaze_escape_name, glaze_float_name) };
		benchmarksuite::pin_for_benchmark();
		run_pod_pair<"Double Test", std::vector<double>, true>(newer_string);
		run_pod_pair<"Uint64 Test", std::vector<uint64_t>, true>(newer_string);
		run_pod_pair<"Int64 Test", std::vector<int64_t>, true>(newer_string);
		run_pod_pair<"Bool Test", std::vector<bool>, true>(newer_string);
		run_pod_pair<"String Test", std::vector<std::string>, true>(newer_string);
		run_parse_only_pair<"Abc (In Order) Partial Test", abc_in_order_partial_test>(newer_string);
		run_min_pretty_quad<"Abc (In Order) Test", abc_in_order_test>(newer_string);
		run_parse_only_pair<"Abc (Out of Order) Partial Test", abc_out_of_order_partial_test>(newer_string);
		run_min_pretty_quad<"Abc (Out of Order) Test", abc_out_of_order_test>(newer_string);
		run_min_pretty_quad<"Apache Builds Test", apache_builds_message>(newer_string);
		run_min_pretty_quad<"Canada Test", canada_message>(newer_string);
		run_min_pretty_quad<"CitmCatalog Test", citm_catalog_message>(newer_string);
		run_min_pretty_quad<"Discord Test", discord_message>(newer_string);
		run_min_pretty_quad<"Github Events Test", github_events_message>(newer_string);
		run_min_pretty_quad<"Google Maps Response Test", google_maps_response_message>(newer_string);
		run_min_pretty_quad<"Instruments Test", instruments_message>(newer_string);
		run_min_pretty_quad<"Marine IK Test", marine_ik>(newer_string);
		run_min_pretty_quad<"Mesh Test", mesh_message>(newer_string);
		run_min_pretty_quad<"Random Test", random_message>(newer_string);
		run_min_pretty_quad<"Semanticscholar Corpus Test", semantic_scholar_message>(newer_string);
		run_parse_only_pair<"Twitter Partial Test", twitter_partial_message>(newer_string);
		run_min_pretty_quad<"Twitter Test", twitter_message>(newer_string);
		execute_test<test_types::minify, std::string, "Minify Test", false, library_traits<test_types::minify, json_libraries::jsonifier, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::glaze, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::simdjson, "Minify Test", false, std::string>>(newer_string);
		execute_test<test_types::prettify, std::string, "Prettify Test", false,
			library_traits<test_types::prettify, json_libraries::jsonifier, "Prettify Test", false, std::string>,
			library_traits<test_types::prettify, json_libraries::glaze, "Prettify Test", false, std::string>>(newer_string);
		execute_test<test_types::validate, std::string, "Validate Test", false,
			library_traits<test_types::validate, json_libraries::jsonifier, "Validate Test", false, std::string>,
			library_traits<test_types::validate, json_libraries::glaze, "Validate Test", false, std::string>>(newer_string);
		benchmarksuite::file_handle::save_file(newer_string, base_path + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		benchmarksuite::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		benchmarksuite::execute_python_script(base_path + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}