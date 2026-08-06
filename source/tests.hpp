/*
	MIT License

	Copyright (c) 2024 RealTimeChris

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

#include "all_tests.hpp"

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

	static constexpr bnch_swt::stage_config_data config{ .clear_cpu_caches_before_iterations = true,
		.measured_iteration_count															 = measured_iteration_count,
		.max_iteration_count																 = max_iteration_count,
		.max_time_in_s																		 = 10 };

	static constexpr bnch_swt::string_literal stage_name{ "Json-Performance" };

	using benchmark_stage = bnch_swt::benchmark_stage<stage_name, config>;

	template<test_types test_type, json_libraries json_library, bnch_swt::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<typename value_type>
	concept pod_types = std::is_same_v<std::vector<bool>, value_type> || std::is_same_v<std::vector<std::string>, value_type> || std::is_same_v<std::vector<int64_t>, value_type> ||
		std::is_same_v<std::vector<uint64_t>, value_type> || std::is_same_v<std::vector<double>, value_type>;

	template<bnch_swt::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_read{ test_name + " Read" };
			jsonifier::jsonifier_core<> parser;
			test_data_type test_datas;
			test_datas.resize(json_data_in.size());
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, test_data_type& test_datas, std::vector<std::string>& json_data_in) {
					size_t new_size{};
					for (size_t x = 0; x < test_datas.size(); ++x) {
						parser_new.parseJson<jsonifier::parse_options{ .minified = minified, .validateUtf8 = true }>(test_datas[x], json_data_in[x]);
						bnch_swt::do_not_optimize_away(test_datas[x]);
						new_size += json_data_in[x].size();
					}
					return new_size;
				}
			};
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, test_datas, json_data_in);
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_write{ test_name + " Write" };
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
						bnch_swt::do_not_optimize_away(json_data_out[x]);
						new_size += json_data_out[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_write, jsonifier_library_name, serialize_test_struct>(parser, test_datas, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_read{ test_name + " Read" };
			static constexpr bool partial_read{ std::is_same_v<test_data_type, abc_in_order_partial_test> || std::is_same_v<test_data_type, abc_out_of_order_partial_test> ||
				std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr bool known_order{ true };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out;
					parser_new.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified, .validateUtf8 = true }>(
						json_data_out, json_data_in);
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, jsonifier_library_name, parse_test_struct>(parser, json_data_in_pre);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_write{ test_name + " Write" };
			static constexpr bool partial_read{ std::is_same_v<test_data_type, abc_in_order_partial_test> || std::is_same_v<test_data_type, abc_out_of_order_partial_test> ||
				std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr bool known_order{ true };
			jsonifier::jsonifier_core<> parser;
			test_data_type json_data;
			parser.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified, .validateUtf8 = true }>(json_data,
				json_data_in_pre);
			std::string json_data_in;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			struct serialize_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, const test_data_type& json_data_in) {
					std::string json_data_out;
					parser_new.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data_in, json_data_out);
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name_write, jsonifier_library_name, serialize_test_struct>(parser, json_data);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			bnch_swt::file_handle::save_file(static_cast<std::string>(json_data_in), json_out_path + "/" + test_name.operator std::string() + "-jsonifier.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::jsonifier, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			std::string json_data_out;
			parser.prettifyJson(json_data_in, json_data_out);
			struct prettify_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					parser_new.prettifyJson(json_data_in, json_data_out);
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, prettify_test_struct>(parser, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			bnch_swt::file_handle::save_file(json_data_out, json_out_path + "/" + test_name.operator std::string() + "-jsonifier.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::jsonifier, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			std::string json_data_out;
			parser.minifyJson(json_data_in, json_data_out);
			struct minify_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					parser_new.minifyJson(json_data_in, json_data_out);
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, jsonifier_library_name, minify_test_struct>(parser, json_data_in);
			for (auto& value: parser.getErrors()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			bnch_swt::file_handle::save_file(json_data_out, json_out_path + "/" + test_name.operator std::string() + "-jsonifier.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new> struct library_traits<test_types::validate, json_libraries::jsonifier, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new + " Read" };
			struct validate_test_struct {
				static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					if (auto result = parser_new.validateJson(json_data_in); !result) {
						bnch_swt::do_not_optimize_away(result);
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
			bnch_swt::file_handle::save_file(json_data_in, json_out_path + "/" + test_name.operator std::string() + "-jsonifier.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_read{ test_name + " Read" };
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
						bnch_swt::do_not_optimize_away(test_datas[x]);
						new_size += json_data_in[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, glaze_library_name, parse_test_struct>(test_datas, json_data_in);
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_write{ test_name + " Write" };
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
						[[maybe_unused]] auto new_result =
							glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(test_datas[x], json_data_out[x]);
						bnch_swt::do_not_optimize_away(json_data_out[x]);
						new_size += json_data_out[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_write, glaze_library_name, serialize_test_struct>(test_datas, json_data_out);
			std::string new_string;
			[[maybe_unused]] auto new_result = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(test_datas, new_string);
			bnch_swt::file_handle::save_file(new_string, json_out_path + "/" + test_name.operator std::string() + "-glaze.json");
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_read{ test_name + " Read" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			struct parse_test_struct {
				static size_t impl(std::string& json_data_in) {
					test_data_type json_data_out;
					if (auto error =
							glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
								json_data_out, json_data_in);
						error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_in) << std::endl;
					}
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, glaze_library_name, parse_test_struct>(json_data_in_pre);
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::glaze, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_write{ test_name + " Write" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			test_data_type json_data;
			if (auto error = glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
					json_data, json_data_in_pre);
				error) {
				std::cout << "Glaze Error: " << glz::format_error(error, json_data_in_pre) << std::endl;
			}
			std::string json_data_in;
			[[maybe_unused]] auto prep_result = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(json_data, json_data_in);
			struct serialize_test_struct {
				static size_t impl(const test_data_type& json_data_in) {
					std::string json_data_out;
					[[maybe_unused]] auto new_result =
						glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(json_data_in, json_data_out);
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name_write, glaze_library_name, serialize_test_struct>(json_data);
			bnch_swt::file_handle::save_file(json_data_in, json_out_path + "/" + test_name.operator std::string() + "-glaze.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::glaze, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new + " Write" };
			std::string json_data_out;
			glz::prettify_json(json_data_in, json_data_out);
			struct prettify_test_struct {
				static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					glz::prettify_json(json_data_in, json_data_out);
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, prettify_test_struct>(json_data_in);
			bnch_swt::file_handle::save_file(json_data_out, json_out_path + "/" + test_name.operator std::string() + "-glaze.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::glaze, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new + " Write" };
			std::string json_data_out;
			glz::minify_json(json_data_in, json_data_out);
			struct minify_test_struct {
				static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					glz::minify_json(json_data_in, json_data_out);
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, minify_test_struct>(json_data_in);
			bnch_swt::file_handle::save_file(json_data_out, json_out_path + "/" + test_name.operator std::string() + "-glaze.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new> struct library_traits<test_types::validate, json_libraries::glaze, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new + " Read" };
			struct validate_test_struct {
				static size_t impl(std::string& json_data_in) {
					if (auto result = glz::validate_json(json_data_in); result) {
						bnch_swt::do_not_optimize_away(result);
						return uint64_t{};
					}
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, glaze_library_name, validate_test_struct>(json_data_in);
			bnch_swt::file_handle::save_file(json_data_in, json_out_path + "/" + test_name.operator std::string() + "-glaze.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson, test_name_new, minified, test_data_type> {
		static auto run(std::vector<std::string>& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_read{ test_name + " Read" };
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
						bnch_swt::do_not_optimize_away(test_datas[x]);
						new_size += json_data_in[x].size();
					}
					return new_size;
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, test_datas, json_data_in);
			std::string new_string;
			[[maybe_unused]] auto new_result = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(test_datas, new_string);
			bnch_swt::file_handle::save_file(new_string, json_out_path + "/" + test_name.operator std::string() + "-simdjson.json");
		}
	};

	template<bnch_swt::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson, test_name_new, minified, test_data_type> {
		static auto run(std::string& json_data_in_pre) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new };
			static constexpr bnch_swt::string_literal test_name_read{ test_name + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in) {
					test_data_type json_data_out;
					get_value(parser_new.iterate(json_data_in.data(), json_data_in.size(), json_data_in.capacity()), json_data_out);
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name_read, simdjson_library_name, parse_test_struct>(parser, json_data_in_pre);
			std::string new_string;
			test_data_type json_data_out;
			try {
				get_value(parser.iterate(json_data_in_pre), json_data_out);
			} catch (const std::exception& error) {
				std::cout << "Simdjson Error: " << error.what() << std::endl;
			}
			[[maybe_unused]] auto new_result = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(json_data_out, new_string);
			bnch_swt::file_handle::save_file(new_string, json_out_path + "/" + test_name.operator std::string() + "-simdjson.json");
			return;
		}
	};

	template<bnch_swt::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::simdjson, test_name_new, false, std::string> {
		static auto run(std::string& json_data_in) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new + " Write" };
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
					bnch_swt::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}
			};
			benchmark_stage::template run_benchmark<test_name, simdjson_library_name, minify_test_struct>(parser, json_data_in);
			bnch_swt::file_handle::save_file(json_data_out, json_out_path + "/" + test_name.operator std::string() + "-simdjson.json");
			return;
		}
	};

	std::string make_commit_row(std::string_view label, std::string_view org_repo, std::string_view commit) {
		return std::string("| ") + std::string(label) + ": [" + std::string(commit) + "](https://github.com/" + std::string(org_repo) + "/commit/" + std::string(commit) + ")  \n";
	}

	std::string make_section00(const std::string& os_id, const std::string& os_version, const std::string& compiler_id, const std::string& compiler_version) {
		return std::string("# Json-Performance\nPerformance profiling of JSON libraries (Compiled and run on ") + os_id + " " + os_version + " using the " + compiler_id + " " +
			compiler_version + " compiler).  \n\nLatest Results: (";
	}

	std::string make_section01() {
		return std::string("#### Using the following commits:\n----\n") + make_commit_row("Jsonifier", "nihilai-collective/jsonifier", JSONIFIER_COMMIT) +
			make_commit_row("Glaze", "stephenberry/glaze", GLAZE_COMMIT) + make_commit_row("Simdjson", "simdjson/simdjson", SIMDJSON_COMMIT);
	}

	std::string make_section02(const std::string& cpu_name, const std::string& jsonifier_cpu_name, const std::string& simdjson_cpu_name, const std::string& glaze_utf8_name,
		const std::string& glaze_escape_name, const std::string& glaze_float_name) {
		std::stringstream stream;
		stream << "\n#### Active Implementations:\n";
		stream << "| Library | Active Implementation |\n";
		stream << "| ------- | --------------------- |\n";
		stream << "| Jsonifier | `" << jsonifier_cpu_name << "` |\n";
		stream << "| simdjson (ondemand) | `" << simdjson_cpu_name << "` |\n";
		stream << "| Glaze (utf8-validation) | `" << glaze_utf8_name << "` |\n";
		stream << "| Glaze (string-escape) | `" << glaze_escape_name << "` |\n";
		stream << "| Glaze (float-write) | `" << glaze_float_name << "` |\n\n";
		stream << "> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. "
				  "Glaze reports per-subsystem backends, which may differ from one another within a single build.\n\n";
		stream << "> Adaptive sampling on (" << cpu_name << "): iterations begin at " << std::to_string(config.measured_iteration_count);
		stream << " and double each epoch (e.g. " << std::to_string(config.measured_iteration_count) << " → " << std::to_string(config.measured_iteration_count * 2) << " → "
			   << std::to_string(config.measured_iteration_count * 4) << " → ...) up to a maximum of " << std::to_string(config.max_iteration_count);
		stream << " iterations. Each epoch runs all iterations and evaluates a trailing window of "
			   << "max(iterations/10, " << std::to_string(config.min_k) << ") samples, capped at " << std::to_string(config.max_k) << ". Convergence requires RSE < "
			   << config.rse_threshold << "% AND mean shift < " << config.convergence_threshold << "% epoch-over-epoch simultaneously. ";
		stream << "The first epoch satisfying both conditions is retained as the canonical result. "
			   << "If convergence is never reached before " << config.max_time_in_s << " seconds elapse or the iteration cap is hit, the result is marked non-converged and "
			   << "excluded from all rankings — only converged results participate in win/tie/loss tallying. "
			   << "All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.\n\n##### (All of the libraries are performing UTF8-validation in "
				  "these tests. Jsonifier is only performing \"structural "
				  "indexing/stage-1 + stage-2\" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)\n\n";
		stream << "#### Note:\n  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).\n  ";
		return stream.str();
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

	std::string generate_section(const auto&& test_name_new_graph, const auto&& test_name_new_json) {
		std::string test_name_json{ bnch_swt::url_encode(static_cast<std::string>(test_name_new_json)) };
		std::string test_name_graph{ bnch_swt::url_encode(static_cast<std::string>(test_name_new_graph)) };
		std::string current_path_new{ static_cast<std::string>(current_path) };
		return "\n----\n### " + test_name_new_graph + " Results [(View the data used in the following test)](./json/" + test_name_json +
			".json):\n\n"
			"<p align=\"left\"><a href=\"./graphs/" +
			current_path_new + "/" + test_name_graph +
			"_Results.png\" target=\"_blank\">"
			"<img src=\"./graphs/" +
			current_path_new + "/" + test_name_graph + std::string{ "_Results.png?raw=true\" \nalt=\"\" width=\"400\"/></p>\n\n" } +
			((test_name_new_graph.find("Out of Order") != std::string::npos) && (test_name_new_graph.find("Read") != std::string::npos) ? make_abc_note() : "");
	}

	template<test_types test_type, bnch_swt::string_literal test_name_new, typename test_data_type, typename... library_traits> struct test_traits {
		static constexpr bnch_swt::string_literal test_type_string{ [] {
			if constexpr (test_type == test_types::parse || test_type == test_types::validate) {
				return bnch_swt::string_literal{ " Read" };
			} else {
				return bnch_swt::string_literal{ " Write" };
			}
		}() };

		template<typename library_type, typename json_input_type> static void run(json_input_type& json_data_new) {
			library_type::run(json_data_new);
		}

		template<typename json_input_type> static std::string run(json_input_type& json_data_new) {
			static constexpr bnch_swt::string_literal test_name{ test_name_new + test_type_string };
			std::string json_results;
			(run<library_traits>(json_data_new), ...);
			auto results = benchmark_stage::get_test_results(test_name.operator std::string());
			results.print(false);
			if (results.sorted_results.size() > 1) {
				json_results += generate_section(test_name.operator std::string(), test_name_new.operator std::string());
				json_results += results.to_markdown(false, false);
				bnch_swt::file_handle::save_file(results.to_csv(), csv_out_path + "/" + test_name.operator std::string() + ".csv");
			}
			return json_results;
		}
	};

	inline std::string getPaddedJsonString(const std::string& path) {
		auto raw_data = bnch_swt::file_handle::get(path);

		std::string padded_string;
		padded_string.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		padded_string.assign(raw_data);

		return padded_string;
	}

	template<test_types test_type, typename test_data_type, bnch_swt::string_literal test_name, bool is_pod = false, typename... library_traits>
	void execute_test(std::string& newer_string) {
		const std::string full_path = json_path.operator std::string() + "/" + test_name.operator std::string() + ".json";

		if constexpr (is_pod) {
			auto test_datas = stringToVector(bnch_swt::file_handle::get(full_path));
			newer_string += test_traits<test_type, test_name, test_data_type, library_traits...>::run(test_datas);
		} else {
			auto json_data_in = getPaddedJsonString(full_path);
			newer_string += test_traits<test_type, test_name, test_data_type, library_traits...>::run(json_data_in);
		}
	}

	void test_function() {
		const std::string jsonifier_cpu_name{ jsonifier::cpu_arch_name };
		const std::string simdjson_cpu_name{ simdjson::get_active_implementation().operator*().name() };
		const std::string glaze_utf8_name{ glz::simd_info.utf8_validation };
		const std::string glaze_escape_name{ glz::simd_info.string_escape };
		const std::string glaze_float_name{ glz::simd_info.float_write };
		bnch_swt::pin_for_benchmark();
		std::cout << "Jsonifier Active Implementation: " << jsonifier_cpu_name << std::endl;
		std::cout << "simdjson Active Implementation: " << simdjson_cpu_name << std::endl;
		std::cout << "Glaze UTF8-Validation: " << glaze_utf8_name << std::endl;
		std::cout << "Glaze String-Escape: " << glaze_escape_name << std::endl;
		std::cout << "Glaze Float-Write: " << glaze_float_name << std::endl;
		
		const std::string cpu_name{ bnch_swt::internal::get_device_info<bnch_swt::benchmark_types::cpu>() + "-" +
			static_cast<std::string>(bnch_swt::system_info_data<bnch_swt::benchmark_types::cpu>::instruction_set_name) };

		std::string newer_string{ make_section00(static_cast<std::string>(bnch_swt::system_info_data<bnch_swt::benchmark_types::cpu>::os_id),
									  static_cast<std::string>(bnch_swt::system_info_data<bnch_swt::benchmark_types::cpu>::os_version),
									  static_cast<std::string>(bnch_swt::system_info_data<bnch_swt::benchmark_types::cpu>::compiler_id),
									  static_cast<std::string>(bnch_swt::system_info_data<bnch_swt::benchmark_types::cpu>::compiler_version)) +
			bnch_swt::get_time() + ")\n" + make_section01() +
			make_section02(cpu_name, jsonifier_cpu_name, simdjson_cpu_name, glaze_utf8_name, glaze_escape_name, glaze_float_name) };
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, std::vector<double>, "Double Test", true,
			library_traits<test_types::parse, json_libraries::jsonifier, "Double Test", true, std::vector<double>>,
			library_traits<test_types::parse, json_libraries::glaze, "Double Test", true, std::vector<double>>,
			library_traits<test_types::parse, json_libraries::simdjson, "Double Test", true, std::vector<double>>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, std::vector<double>, "Double Test", true,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Double Test", true, std::vector<double>>,
			library_traits<test_types::serialize, json_libraries::glaze, "Double Test", true, std::vector<double>>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, std::vector<uint64_t>, "Uint64 Test", true,
			library_traits<test_types::parse, json_libraries::jsonifier, "Uint64 Test", true, std::vector<uint64_t>>,
			library_traits<test_types::parse, json_libraries::glaze, "Uint64 Test", true, std::vector<uint64_t>>,
			library_traits<test_types::parse, json_libraries::simdjson, "Uint64 Test", true, std::vector<uint64_t>>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, std::vector<uint64_t>, "Uint64 Test", true,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Uint64 Test", true, std::vector<uint64_t>>,
			library_traits<test_types::serialize, json_libraries::glaze, "Uint64 Test", true, std::vector<uint64_t>>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, std::vector<int64_t>, "Int64 Test", true,
			library_traits<test_types::parse, json_libraries::jsonifier, "Int64 Test", true, std::vector<int64_t>>,
			library_traits<test_types::parse, json_libraries::glaze, "Int64 Test", true, std::vector<int64_t>>,
			library_traits<test_types::parse, json_libraries::simdjson, "Int64 Test", true, std::vector<int64_t>>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, std::vector<int64_t>, "Int64 Test", true,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Int64 Test", true, std::vector<int64_t>>,
			library_traits<test_types::serialize, json_libraries::glaze, "Int64 Test", true, std::vector<int64_t>>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, std::vector<bool>, "Bool Test", true, library_traits<test_types::parse, json_libraries::jsonifier, "Bool Test", true, std::vector<bool>>,
			library_traits<test_types::parse, json_libraries::glaze, "Bool Test", true, std::vector<bool>>,
			library_traits<test_types::parse, json_libraries::simdjson, "Bool Test", true, std::vector<bool>>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, std::vector<bool>, "Bool Test", true,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Bool Test", true, std::vector<bool>>,
			library_traits<test_types::serialize, json_libraries::glaze, "Bool Test", true, std::vector<bool>>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, std::vector<std::string>, "String Test", true,
			library_traits<test_types::parse, json_libraries::jsonifier, "String Test", true, std::vector<std::string>>,
			library_traits<test_types::parse, json_libraries::glaze, "String Test", true, std::vector<std::string>>,
			library_traits<test_types::parse, json_libraries::simdjson, "String Test", true, std::vector<std::string>>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, std::vector<std::string>, "String Test", true,
			library_traits<test_types::serialize, json_libraries::jsonifier, "String Test", true, std::vector<std::string>>,
			library_traits<test_types::serialize, json_libraries::glaze, "String Test", true, std::vector<std::string>>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, abc_in_order_partial_test, "Abc (In Order) Partial Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Abc (In Order) Partial Test (Minified)", true, abc_in_order_partial_test>,
			library_traits<test_types::parse, json_libraries::simdjson, "Abc (In Order) Partial Test (Minified)", true, abc_in_order_partial_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, abc_in_order_partial_test, "Abc (In Order) Partial Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Abc (In Order) Partial Test (Prettified)", false, abc_in_order_partial_test>,
			library_traits<test_types::parse, json_libraries::simdjson, "Abc (In Order) Partial Test (Prettified)", false, abc_in_order_partial_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, abc_in_order_test, "Abc (In Order) Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Abc (In Order) Test (Minified)", true, abc_in_order_test>,
			library_traits<test_types::parse, json_libraries::glaze, "Abc (In Order) Test (Minified)", true, abc_in_order_test>,
			library_traits<test_types::parse, json_libraries::simdjson, "Abc (In Order) Test (Minified)", true, abc_in_order_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, abc_in_order_test, "Abc (In Order) Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Abc (In Order) Test (Minified)", true, abc_in_order_test>,
			library_traits<test_types::serialize, json_libraries::glaze, "Abc (In Order) Test (Minified)", true, abc_in_order_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, abc_in_order_test, "Abc (In Order) Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Abc (In Order) Test (Prettified)", false, abc_in_order_test>,
			library_traits<test_types::parse, json_libraries::glaze, "Abc (In Order) Test (Prettified)", false, abc_in_order_test>,
			library_traits<test_types::parse, json_libraries::simdjson, "Abc (In Order) Test (Prettified)", false, abc_in_order_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, abc_in_order_test, "Abc (In Order) Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Abc (In Order) Test (Prettified)", false, abc_in_order_test>,
			library_traits<test_types::serialize, json_libraries::glaze, "Abc (In Order) Test (Prettified)", false, abc_in_order_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, abc_out_of_order_partial_test, "Abc (Out of Order) Partial Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Abc (Out of Order) Partial Test (Minified)", true, abc_out_of_order_partial_test>,
			library_traits<test_types::parse, json_libraries::simdjson, "Abc (Out of Order) Partial Test (Minified)", true, abc_out_of_order_partial_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, abc_out_of_order_partial_test, "Abc (Out of Order) Partial Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Abc (Out of Order) Partial Test (Prettified)", false, abc_out_of_order_partial_test>,
			library_traits<test_types::parse, json_libraries::simdjson, "Abc (Out of Order) Partial Test (Prettified)", false, abc_out_of_order_partial_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, abc_out_of_order_test, "Abc (Out of Order) Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Abc (Out of Order) Test (Minified)", true, abc_out_of_order_test>,
			library_traits<test_types::parse, json_libraries::glaze, "Abc (Out of Order) Test (Minified)", true, abc_out_of_order_test>,
			library_traits<test_types::parse, json_libraries::simdjson, "Abc (Out of Order) Test (Minified)", true, abc_out_of_order_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, abc_out_of_order_test, "Abc (Out of Order) Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Abc (Out of Order) Test (Minified)", true, abc_out_of_order_test>,
			library_traits<test_types::serialize, json_libraries::glaze, "Abc (Out of Order) Test (Minified)", true, abc_out_of_order_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, abc_out_of_order_test, "Abc (Out of Order) Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Abc (Out of Order) Test (Prettified)", false, abc_out_of_order_test>,
			library_traits<test_types::parse, json_libraries::glaze, "Abc (Out of Order) Test (Prettified)", false, abc_out_of_order_test>,
			library_traits<test_types::parse, json_libraries::simdjson, "Abc (Out of Order) Test (Prettified)", false, abc_out_of_order_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, abc_out_of_order_test, "Abc (Out of Order) Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Abc (Out of Order) Test (Prettified)", false, abc_out_of_order_test>,
			library_traits<test_types::serialize, json_libraries::glaze, "Abc (Out of Order) Test (Prettified)", false, abc_out_of_order_test>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, apache_builds_message, "Apache Builds Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Apache Builds Test (Minified)", true, apache_builds_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Apache Builds Test (Minified)", true, apache_builds_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Apache Builds Test (Minified)", true, apache_builds_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, apache_builds_message, "Apache Builds Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Apache Builds Test (Minified)", true, apache_builds_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Apache Builds Test (Minified)", true, apache_builds_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, apache_builds_message, "Apache Builds Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Apache Builds Test (Prettified)", false, apache_builds_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Apache Builds Test (Prettified)", false, apache_builds_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Apache Builds Test (Prettified)", false, apache_builds_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, apache_builds_message, "Apache Builds Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Apache Builds Test (Prettified)", false, apache_builds_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Apache Builds Test (Prettified)", false, apache_builds_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, canada_message, "Canada Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Canada Test (Minified)", true, canada_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Canada Test (Minified)", true, canada_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Canada Test (Minified)", true, canada_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, canada_message, "Canada Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Canada Test (Minified)", true, canada_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Canada Test (Minified)", true, canada_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, canada_message, "Canada Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Canada Test (Prettified)", false, canada_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Canada Test (Prettified)", false, canada_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Canada Test (Prettified)", false, canada_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, canada_message, "Canada Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Canada Test (Prettified)", false, canada_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Canada Test (Prettified)", false, canada_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, citm_catalog_message, "CitmCatalog Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "CitmCatalog Test (Minified)", true, citm_catalog_message>,
			library_traits<test_types::parse, json_libraries::glaze, "CitmCatalog Test (Minified)", true, citm_catalog_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "CitmCatalog Test (Minified)", true, citm_catalog_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, citm_catalog_message, "CitmCatalog Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "CitmCatalog Test (Minified)", true, citm_catalog_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "CitmCatalog Test (Minified)", true, citm_catalog_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, citm_catalog_message, "CitmCatalog Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "CitmCatalog Test (Prettified)", false, citm_catalog_message>,
			library_traits<test_types::parse, json_libraries::glaze, "CitmCatalog Test (Prettified)", false, citm_catalog_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "CitmCatalog Test (Prettified)", false, citm_catalog_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, citm_catalog_message, "CitmCatalog Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "CitmCatalog Test (Prettified)", false, citm_catalog_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "CitmCatalog Test (Prettified)", false, citm_catalog_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, discord_message, "Discord Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Discord Test (Minified)", true, discord_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Discord Test (Minified)", true, discord_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Discord Test (Minified)", true, discord_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, discord_message, "Discord Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Discord Test (Minified)", true, discord_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Discord Test (Minified)", true, discord_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, discord_message, "Discord Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Discord Test (Prettified)", false, discord_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Discord Test (Prettified)", false, discord_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Discord Test (Prettified)", false, discord_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, discord_message, "Discord Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Discord Test (Prettified)", false, discord_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Discord Test (Prettified)", false, discord_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, github_events_message, "Github Events Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Github Events Test (Minified)", true, github_events_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Github Events Test (Minified)", true, github_events_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Github Events Test (Minified)", true, github_events_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, github_events_message, "Github Events Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Github Events Test (Minified)", true, github_events_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Github Events Test (Minified)", true, github_events_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, github_events_message, "Github Events Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Github Events Test (Prettified)", false, github_events_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Github Events Test (Prettified)", false, github_events_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Github Events Test (Prettified)", false, github_events_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, github_events_message, "Github Events Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Github Events Test (Prettified)", false, github_events_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Github Events Test (Prettified)", false, github_events_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, google_maps_response_message, "Google Maps Response Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Google Maps Response Test (Minified)", true, google_maps_response_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Google Maps Response Test (Minified)", true, google_maps_response_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Google Maps Response Test (Minified)", true, google_maps_response_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, google_maps_response_message, "Google Maps Response Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Google Maps Response Test (Minified)", true, google_maps_response_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Google Maps Response Test (Minified)", true, google_maps_response_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, google_maps_response_message, "Google Maps Response Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Google Maps Response Test (Prettified)", false, google_maps_response_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Google Maps Response Test (Prettified)", false, google_maps_response_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Google Maps Response Test (Prettified)", false, google_maps_response_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, google_maps_response_message, "Google Maps Response Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Google Maps Response Test (Prettified)", false, google_maps_response_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Google Maps Response Test (Prettified)", false, google_maps_response_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, instruments_message, "Instruments Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Instruments Test (Minified)", true, instruments_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Instruments Test (Minified)", true, instruments_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Instruments Test (Minified)", true, instruments_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, instruments_message, "Instruments Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Instruments Test (Minified)", true, instruments_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Instruments Test (Minified)", true, instruments_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, instruments_message, "Instruments Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Instruments Test (Prettified)", false, instruments_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Instruments Test (Prettified)", false, instruments_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Instruments Test (Prettified)", false, instruments_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, instruments_message, "Instruments Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Instruments Test (Prettified)", false, instruments_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Instruments Test (Prettified)", false, instruments_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, marine_ik, "Marine IK Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Marine IK Test (Minified)", true, marine_ik>,
			library_traits<test_types::parse, json_libraries::glaze, "Marine IK Test (Minified)", true, marine_ik>,
			library_traits<test_types::parse, json_libraries::simdjson, "Marine IK Test (Minified)", true, marine_ik>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, marine_ik, "Marine IK Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Marine IK Test (Minified)", true, marine_ik>,
			library_traits<test_types::serialize, json_libraries::glaze, "Marine IK Test (Minified)", true, marine_ik>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, marine_ik, "Marine IK Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Marine IK Test (Prettified)", false, marine_ik>,
			library_traits<test_types::parse, json_libraries::glaze, "Marine IK Test (Prettified)", false, marine_ik>,
			library_traits<test_types::parse, json_libraries::simdjson, "Marine IK Test (Prettified)", false, marine_ik>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, marine_ik, "Marine IK Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Marine IK Test (Prettified)", false, marine_ik>,
			library_traits<test_types::serialize, json_libraries::glaze, "Marine IK Test (Prettified)", false, marine_ik>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, mesh_message, "Mesh Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Mesh Test (Minified)", true, mesh_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Mesh Test (Minified)", true, mesh_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Mesh Test (Minified)", true, mesh_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, mesh_message, "Mesh Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Mesh Test (Minified)", true, mesh_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Mesh Test (Minified)", true, mesh_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, mesh_message, "Mesh Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Mesh Test (Prettified)", false, mesh_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Mesh Test (Prettified)", false, mesh_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Mesh Test (Prettified)", false, mesh_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, mesh_message, "Mesh Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Mesh Test (Prettified)", false, mesh_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Mesh Test (Prettified)", false, mesh_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, random_message, "Random Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Random Test (Minified)", true, random_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Random Test (Minified)", true, random_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Random Test (Minified)", true, random_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, random_message, "Random Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Random Test (Minified)", true, random_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Random Test (Minified)", true, random_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, random_message, "Random Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Random Test (Prettified)", false, random_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Random Test (Prettified)", false, random_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Random Test (Prettified)", false, random_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, random_message, "Random Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Random Test (Prettified)", false, random_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Random Test (Prettified)", false, random_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, semantic_scholar_message, "Semanticscholar Corpus Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Semanticscholar Corpus Test (Minified)", true, semantic_scholar_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Semanticscholar Corpus Test (Minified)", true, semantic_scholar_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Semanticscholar Corpus Test (Minified)", true, semantic_scholar_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, semantic_scholar_message, "Semanticscholar Corpus Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Semanticscholar Corpus Test (Minified)", true, semantic_scholar_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Semanticscholar Corpus Test (Minified)", true, semantic_scholar_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, semantic_scholar_message, "Semanticscholar Corpus Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Semanticscholar Corpus Test (Prettified)", false, semantic_scholar_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Semanticscholar Corpus Test (Prettified)", false, semantic_scholar_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Semanticscholar Corpus Test (Prettified)", false, semantic_scholar_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, semantic_scholar_message, "Semanticscholar Corpus Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Semanticscholar Corpus Test (Prettified)", false, semantic_scholar_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Semanticscholar Corpus Test (Prettified)", false, semantic_scholar_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, twitter_partial_message, "Twitter Partial Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Twitter Partial Test (Minified)", true, twitter_partial_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Twitter Partial Test (Minified)", true, twitter_partial_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, twitter_partial_message, "Twitter Partial Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Twitter Partial Test (Prettified)", false, twitter_partial_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Twitter Partial Test (Prettified)", false, twitter_partial_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, twitter_message, "Twitter Test (Minified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Twitter Test (Minified)", true, twitter_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Twitter Test (Minified)", true, twitter_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Twitter Test (Minified)", true, twitter_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, twitter_message, "Twitter Test (Minified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Twitter Test (Minified)", true, twitter_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Twitter Test (Minified)", true, twitter_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::parse, twitter_message, "Twitter Test (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, "Twitter Test (Prettified)", false, twitter_message>,
			library_traits<test_types::parse, json_libraries::glaze, "Twitter Test (Prettified)", false, twitter_message>,
			library_traits<test_types::parse, json_libraries::simdjson, "Twitter Test (Prettified)", false, twitter_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS
		execute_test<test_types::serialize, twitter_message, "Twitter Test (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::jsonifier, "Twitter Test (Prettified)", false, twitter_message>,
			library_traits<test_types::serialize, json_libraries::glaze, "Twitter Test (Prettified)", false, twitter_message>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS && JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::minify, std::string, "Minify Test", false, library_traits<test_types::minify, json_libraries::jsonifier, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::glaze, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::simdjson, "Minify Test", false, std::string>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS && JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::prettify, std::string, "Prettify Test", false,
			library_traits<test_types::prettify, json_libraries::jsonifier, "Prettify Test", false, std::string>,
			library_traits<test_types::prettify, json_libraries::glaze, "Prettify Test", false, std::string>>(newer_string);
#endif
#if JSON_PERFORMANCE_WRITE_TESTS && JSON_PERFORMANCE_READ_TESTS
		execute_test<test_types::validate, std::string, "Validate Test", false,
			library_traits<test_types::validate, json_libraries::jsonifier, "Validate Test", false, std::string>,
			library_traits<test_types::validate, json_libraries::glaze, "Validate Test", false, std::string>>(newer_string);
#endif
		bnch_swt::file_handle::save_file(static_cast<std::string>(newer_string), read_me_path.operator std::string() + "/" + current_path + ".md");
		auto stage_results = benchmark_stage::get_all_results();
		bnch_swt::file_handle::save_file(stage_results.to_csv(), csv_out_path + "/Results.csv");
		std::cout << "Md Data: " << newer_string << std::endl;
		bnch_swt::execute_python_script(base_path.operator std::string() + "/GenerateGraphs.py", csv_out_path + "/", graphs_path);
	}
}