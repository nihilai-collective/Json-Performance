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
#include <twitter.hpp>

namespace tests {

	template<json_libraries json_library, benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
		requires jsonifier_parse_library<json_library>
	struct library_traits<test_types::parse, json_library, test_name_new, minified, test_data_type> {
		using variant = jsonifier_parse_variant<json_library>;
		inline static auto run(const std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t parse(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
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

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in) {
					std::vector<test_data_type> test_datas;
					return parse(parser_new, json_data_in, test_datas);
				}
			};
			gated_benchmark<test_name, variant::library_name, parse_test_struct>::impl(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, const std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, const std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> reused_datas;
			gated_benchmark<reused_test_name, variant::library_name, reused_parse_test_struct>::impl(parser, json_data_in, reused_datas);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::vector<test_data_type> test_datas;
			parse_test_struct::parse(parser, json_data_in, test_datas);
			std::string new_string;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + variant::file_tag);
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		inline static auto run(const std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			std::vector<test_data_type> test_datas;
			test_datas.resize(json_data_in.size());
			for (size_t x = 0; x < test_datas.size(); ++x) {
				parser.parseJson<jsonifier::parse_options{ .minified = minified }>(test_datas[x], json_data_in[x]);
			}
			struct serialize_test_struct {
				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<test_data_type>& test_datas) {
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
			gated_benchmark<test_name, jsonifier_library_name, serialize_test_struct>::impl(parser, test_datas);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_serialize_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
					json_data_out.resize(test_datas.size());
					for (auto& value: json_data_out) {
						clear_value(value);
					}
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
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
			gated_benchmark<reused_test_name, jsonifier_library_name, reused_serialize_test_struct>::impl(parser, test_datas, reused_output);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string new_string;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(test_datas, new_string);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<json_libraries json_library, benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
		requires jsonifier_parse_library<json_library>
	struct library_traits<test_types::parse, json_library, test_name_new, minified, test_data_type> {
		using variant = jsonifier_parse_variant<json_library>;
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool partial_read{ variant::two_stage || std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr bool known_order{ !std::is_same_v<test_data_type, twitter_partial_message> };
			jsonifier::jsonifier_core<> parser;
			struct parse_test_struct {
				inline static size_t parse(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					parser_new.parseJson<jsonifier::parse_options{ .partialRead = partial_read, .knownOrder = known_order, .minified = minified }>(json_data_out, json_data_in);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name, variant::library_name, parse_test_struct>::impl(parser, json_data_in_pre);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
				}
			};
			test_data_type reused_data{};
			gated_benchmark<reused_test_name, variant::library_name, reused_parse_test_struct>::impl(parser, json_data_in_pre, reused_data);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			test_data_type json_data{};
			parse_test_struct::parse(parser, json_data_in_pre, json_data);
			std::string new_string;
			parser.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data, new_string);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + variant::file_tag);
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::jsonifier, test_name_new, minified, test_data_type> {
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			test_data_type json_data{};
			parser.parseJson<jsonifier::parse_options{ .minified = minified }>(json_data, json_data_in_pre);
			struct serialize_test_struct {
				inline static size_t serialize(jsonifier::jsonifier_core<>& parser_new, const test_data_type& json_data_in, std::string& json_data_out) {
					parser_new.serializeJson<jsonifier::serialize_options{ .prettify = !minified }>(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, const test_data_type& json_data_in) {
					std::string json_data_out;
					return serialize(parser_new, json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name, jsonifier_library_name, serialize_test_struct>::impl(parser, json_data);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_serialize_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, const test_data_type&, std::string& json_data_out) {
					json_data_out.clear();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, const test_data_type& json_data_in, std::string& json_data_out) {
					return serialize_test_struct::serialize(parser_new, json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			gated_benchmark<reused_test_name, jsonifier_library_name, reused_serialize_test_struct>::impl(parser, json_data, reused_output);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string json_data_out;
			serialize_test_struct::serialize(parser, json_data, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::jsonifier, test_name_new, false, std::string> {
		inline static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			struct prettify_test_struct {
				inline static size_t prettify(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, std::string& json_data_out) {
					parser_new.prettifyJson(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					return prettify(parser_new, json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name, jsonifier_library_name, prettify_test_struct>::impl(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_prettify_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::string&, std::string& json_data_out) {
					json_data_out.clear();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, std::string& json_data_out) {
					return prettify_test_struct::prettify(parser_new, json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			gated_benchmark<reused_test_name, jsonifier_library_name, reused_prettify_test_struct>::impl(parser, json_data_in, reused_output);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string json_data_out;
			prettify_test_struct::prettify(parser, json_data_in, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::jsonifier, test_name_new, false, std::string> {
		inline static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			jsonifier::jsonifier_core<> parser;
			struct minify_test_struct {
				inline static size_t minify(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, std::string& json_data_out) {
					parser_new.minifyJson(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					return minify(parser_new, json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name, jsonifier_library_name, minify_test_struct>::impl(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_minify_test_struct {
				inline static void before(jsonifier::jsonifier_core<>&, std::string&, std::string& json_data_out) {
					json_data_out.clear();
				}

				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in, std::string& json_data_out) {
					return minify_test_struct::minify(parser_new, json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			gated_benchmark<reused_test_name, jsonifier_library_name, reused_minify_test_struct>::impl(parser, json_data_in, reused_output);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			std::string json_data_out;
			minify_test_struct::minify(parser, json_data_in, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::validate, json_libraries::jsonifier, test_name_new, false, std::string> {
		inline static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			struct validate_test_struct {
				inline static size_t impl(jsonifier::jsonifier_core<>& parser_new, std::string& json_data_in) {
					if (auto result = parser_new.validateJson(json_data_in); !result) {
						benchmarksuite::do_not_optimize_away(result);
						return uint64_t{};
					}
					return json_data_in.size();
				}
			};
			jsonifier::jsonifier_core<> parser;
			gated_benchmark<test_name, jsonifier_library_name, validate_test_struct>::impl(parser, json_data_in);
			if (auto& value = parser.getError(); value.hasError()) {
				std::cout << "Jsonifier Error: " << value << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_in, json_out_path + "/" + test_name + "-jsonifier.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::glaze, test_name_new, minified, test_data_type> {
		inline static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			static constexpr glz::opts read_opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .minified = minified };
			struct parse_test_struct {
				inline static size_t parse(std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
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

				inline static size_t impl(std::vector<std::string>& json_data_in) {
					std::vector<test_data_type> test_datas;
					return parse(json_data_in, test_datas);
				}
			};
			gated_benchmark<test_name, glaze_library_name, parse_test_struct>::impl(json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				inline static void before(std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> reused_datas;
			gated_benchmark<reused_test_name, glaze_library_name, reused_parse_test_struct>::impl(json_data_in, reused_datas);
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
		inline static auto run(const std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> && !std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr glz::opts read_opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .minified = minified };
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
				inline static size_t impl(std::vector<test_data_type>& test_datas) {
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
			gated_benchmark<test_name, glaze_library_name, serialize_test_struct>::impl(test_datas);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_serialize_test_struct {
				inline static void before(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
					json_data_out.resize(test_datas.size());
					for (auto& value: json_data_out) {
						clear_value(value);
					}
				}

				inline static size_t impl(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
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
			gated_benchmark<reused_test_name, glaze_library_name, reused_serialize_test_struct>::impl(test_datas, reused_output);
			std::string new_string;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(test_datas, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::glaze, test_name_new, minified, test_data_type> {
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			static constexpr bool partial_read{ std::is_same_v<test_data_type, twitter_partial_message> };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> && !partial_read };
			static constexpr glz::opts read_opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .minified = minified };
			struct parse_test_struct {
				inline static size_t parse(std::string& json_data_in, test_data_type& json_data_out) {
					if (auto error = glz::read<read_opts>(json_data_out, json_data_in); error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_in) << std::endl;
					}
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				inline static size_t impl(std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name, glaze_library_name, parse_test_struct>::impl(json_data_in_pre);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				inline static void before(std::string&, test_data_type& json_data_out) {
					clear_value(json_data_out);
				}

				inline static size_t impl(std::string& json_data_in, test_data_type& json_data_out) {
					return parse_test_struct::parse(json_data_in, json_data_out);
				}
			};
			test_data_type reused_data{};
			gated_benchmark<reused_test_name, glaze_library_name, reused_parse_test_struct>::impl(json_data_in_pre, reused_data);
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
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> && !std::is_same_v<test_data_type, twitter_partial_message> };
			test_data_type json_data{};
			if (auto error = glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .minified = minified }>(json_data, json_data_in_pre);
				error) {
				std::cout << "Glaze Error: " << glz::format_error(error, json_data_in_pre) << std::endl;
			}
			struct serialize_test_struct {
				inline static size_t serialize(const test_data_type& json_data_in, std::string& json_data_out) {
					if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified, .minified = minified }>(json_data_in, json_data_out); error) {
						std::cout << "Glaze Error: " << glz::format_error(error, json_data_out) << std::endl;
					}
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(const test_data_type& json_data_in) {
					std::string json_data_out;
					return serialize(json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name, glaze_library_name, serialize_test_struct>::impl(json_data);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_serialize_test_struct {
				inline static void before(const test_data_type&, std::string& json_data_out) {
					json_data_out.clear();
				}

				inline static size_t impl(const test_data_type& json_data_in, std::string& json_data_out) {
					return serialize_test_struct::serialize(json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			gated_benchmark<reused_test_name, glaze_library_name, reused_serialize_test_struct>::impl(json_data, reused_output);
			std::string json_data_out;
			serialize_test_struct::serialize(json_data, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::glaze, test_name_new, false, std::string> {
		inline static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			struct prettify_test_struct {
				inline static size_t prettify(std::string& json_data_in, std::string& json_data_out) {
					glz::prettify_json(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					return prettify(json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name, glaze_library_name, prettify_test_struct>::impl(json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_prettify_test_struct {
				inline static void before(std::string&, std::string& json_data_out) {
					json_data_out.clear();
				}

				inline static size_t impl(std::string& json_data_in, std::string& json_data_out) {
					return prettify_test_struct::prettify(json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			gated_benchmark<reused_test_name, glaze_library_name, reused_prettify_test_struct>::impl(json_data_in, reused_output);
			std::string json_data_out;
			prettify_test_struct::prettify(json_data_in, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::glaze, test_name_new, false, std::string> {
		inline static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			struct minify_test_struct {
				inline static size_t minify(std::string& json_data_in, std::string& json_data_out) {
					glz::minify_json(json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					return minify(json_data_in, json_data_out);
				}
			};
			gated_benchmark<test_name, glaze_library_name, minify_test_struct>::impl(json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_minify_test_struct {
				inline static void before(std::string&, std::string& json_data_out) {
					json_data_out.clear();
				}

				inline static size_t impl(std::string& json_data_in, std::string& json_data_out) {
					return minify_test_struct::minify(json_data_in, json_data_out);
				}
			};
			std::string reused_output;
			gated_benchmark<reused_test_name, glaze_library_name, reused_minify_test_struct>::impl(json_data_in, reused_output);
			std::string json_data_out;
			minify_test_struct::minify(json_data_in, json_data_out);
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::validate, json_libraries::glaze, test_name_new, false, std::string> {
		inline static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			struct validate_test_struct {
				inline static size_t impl(std::string& json_data_in) {
					if (auto result = glz::validate_json(json_data_in); result) {
						std::cout << "Glaze Error: " << glz::format_error(result, json_data_in) << std::endl;
						benchmarksuite::do_not_optimize_away(result);
						return uint64_t{};
					}
					return json_data_in.size();
				}
			};
			gated_benchmark<test_name, glaze_library_name, validate_test_struct>::impl(json_data_in);
			benchmarksuite::file_handle::save_file(json_data_in, json_out_path + "/" + test_name + "-glaze.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson, test_name_new, minified, test_data_type> {
		inline static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
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
			gated_benchmark<test_name, simdjson_library_name, parse_test_struct>::impl(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				inline static void before(simdjson::ondemand::parser&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> reused_datas;
			gated_benchmark<reused_test_name, simdjson_library_name, reused_parse_test_struct>::impl(parser, json_data_in, reused_datas);
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
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
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
			test_data_type json_data{};
			try {
				gated_benchmark<test_name, simdjson_library_name, parse_test_struct>::impl(parser, json_data_in_pre);
				parse_test_struct::parse(parser, json_data_in_pre, json_data);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_parse_test_struct {
					inline static void before(simdjson::ondemand::parser&, std::string&, test_data_type& json_data_out) {
						clear_value(json_data_out);
					}

					inline static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
						return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
					}
				};
				test_data_type reused_data{};
				gated_benchmark<reused_test_name, simdjson_library_name, reused_parse_test_struct>::impl(parser, json_data_in_pre, reused_data);
			} catch (const std::exception& error) {
				std::cout << "simdjson Error: " << error.what() << std::endl;
			}
			std::string new_string;
			if (auto error = glz::write<glz::opts{ .skip_null_members = false, .prettify = !minified }>(json_data, new_string); error) {
				std::cout << "Glaze Error: " << glz::format_error(error, new_string) << std::endl;
			}
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

#if SIMDJSON_STATIC_REFLECTION
	template<typename test_data_type> inline void simdjson_reflection_parse(simdjson::ondemand::parser& parser, std::string& json_data_in, test_data_type& json_data_out) {
		simdjson::ondemand::document document;
		auto error = parser.iterate(json_data_in.data(), json_data_in.size(), json_data_in.capacity()).get(document);
		if (!error) {
			error = document.get(json_data_out);
		}
		if (error) {
			std::cout << "simdjson Reflection Error: " << simdjson::error_message(error) << std::endl;
		}
	}

	template<typename test_data_type> inline void simdjson_reflection_serialize(const test_data_type& json_data_in, std::string& json_data_out) {
		if (auto error = simdjson::to_json(json_data_in, json_data_out); error) {
			std::cout << "simdjson Reflection Error: " << simdjson::error_message(error) << std::endl;
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

	template<typename test_data_type> inline void simdjson_reflection_serialize_pretty(const test_data_type& json_data_in, std::string& json_data_out) {
		static const simdjson::fractured_json_options options{ make_simdjson_expanded_options() };
		if (auto error = simdjson::to_fractured_json_string(json_data_in, options).get(json_data_out); error) {
			std::cout << "simdjson Reflection Error: " << simdjson::error_message(error) << std::endl;
		}
	}

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		inline static auto run(const std::vector<std::string>& json_data_in) {
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
				inline static size_t impl(std::vector<test_data_type>& test_datas) {
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
				gated_benchmark<test_name, simdjson_reflection_library_name, serialize_test_struct>::impl(test_datas);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_serialize_test_struct {
					inline static void before(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
						json_data_out.resize(test_datas.size());
						for (auto& value: json_data_out) {
							clear_value(value);
						}
					}

					inline static size_t impl(std::vector<test_data_type>& test_datas, std::vector<std::string>& json_data_out) {
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
				gated_benchmark<reused_test_name, simdjson_reflection_library_name, reused_serialize_test_struct>::impl(test_datas, reused_output);
			} catch (const std::exception& error) {
				std::cout << "simdjson Reflection Error: " << error.what() << std::endl;
			}
			std::string new_string;
			simdjson_reflection_serialize(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson-reflection.json");
		}
	};

	template<typename test_data_type> inline void simdjson_from_parse(simdjson::ondemand::parser& parser, std::string& json_data_in, test_data_type& json_data_out) {
		if (auto error = simdjson::from(parser, simdjson::padded_string_view(json_data_in.data(), json_data_in.size(), json_data_in.capacity())).get(json_data_out); error) {
			std::cout << "simdjson Reflection Error: " << simdjson::error_message(error) << std::endl;
		}
	}

	template<benchmarksuite::string_literal test_name_new, bool minified, pod_types test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		inline static auto run(std::vector<std::string>& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				inline static size_t parse(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					size_t new_size{};
					for (size_t x = 0; x < json_data_in.size(); ++x) {
						if constexpr (std::is_same_v<test_data_type, bool>) {
							bool new_value{};
							simdjson_from_parse(parser_new, json_data_in[x], new_value);
							test_datas.push_back(new_value);
						} else {
							simdjson_from_parse(parser_new, json_data_in[x], test_datas.emplace_back());
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
			gated_benchmark<test_name, simdjson_reflection_library_name, parse_test_struct>::impl(parser, json_data_in);
			static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
			struct reused_parse_test_struct {
				inline static void before(simdjson::ondemand::parser&, std::vector<std::string>&, std::vector<test_data_type>& test_datas) {
					clear_value(test_datas);
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, std::vector<std::string>& json_data_in, std::vector<test_data_type>& test_datas) {
					return parse_test_struct::parse(parser_new, json_data_in, test_datas);
				}
			};
			std::vector<test_data_type> reused_datas;
			gated_benchmark<reused_test_name, simdjson_reflection_library_name, reused_parse_test_struct>::impl(parser, json_data_in, reused_datas);
			std::vector<test_data_type> test_datas;
			parse_test_struct::parse(parser, json_data_in, test_datas);
			std::string new_string;
			simdjson_reflection_serialize(test_datas, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson-reflection.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Read" };
			simdjson::ondemand::parser parser;
			struct parse_test_struct {
				inline static size_t parse(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
					simdjson_reflection_parse(parser_new, json_data_in, json_data_out);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_in.size();
				}

				inline static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in) {
					test_data_type json_data_out{};
					return parse(parser_new, json_data_in, json_data_out);
				}
			};
			test_data_type json_data{};
			try {
				gated_benchmark<test_name, simdjson_reflection_library_name, parse_test_struct>::impl(parser, json_data_in_pre);
				parse_test_struct::parse(parser, json_data_in_pre, json_data);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_parse_test_struct {
					inline static void before(simdjson::ondemand::parser&, std::string&, test_data_type& json_data_out) {
						clear_value(json_data_out);
					}

					inline static size_t impl(simdjson::ondemand::parser& parser_new, std::string& json_data_in, test_data_type& json_data_out) {
						return parse_test_struct::parse(parser_new, json_data_in, json_data_out);
					}
				};
				test_data_type reused_data{};
				gated_benchmark<reused_test_name, simdjson_reflection_library_name, reused_parse_test_struct>::impl(parser, json_data_in_pre, reused_data);
			} catch (const std::exception& error) {
				std::cout << "simdjson Reflection Error: " << error.what() << std::endl;
			}
			std::string new_string;
			simdjson_reflection_serialize(json_data, new_string);
			benchmarksuite::file_handle::save_file(new_string, json_out_path + "/" + test_name + "-simdjson-reflection.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		inline static auto run(std::string& json_data_in_pre) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			simdjson::ondemand::parser parser;
			test_data_type json_data{};
			simdjson_reflection_parse(parser, json_data_in_pre, json_data);
			struct serialize_test_struct {
				inline static size_t serialize(const test_data_type& json_data_in, std::string& json_data_out) {
					if constexpr (minified) {
						simdjson_reflection_serialize(json_data_in, json_data_out);
					} else {
						simdjson_reflection_serialize_pretty(json_data_in, json_data_out);
					}
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(const test_data_type& json_data_in) {
					std::string json_data_out;
					return serialize(json_data_in, json_data_out);
				}
			};
			std::string json_data_out;
			try {
				gated_benchmark<test_name, simdjson_reflection_library_name, serialize_test_struct>::impl(json_data);
				serialize_test_struct::serialize(json_data, json_data_out);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_serialize_test_struct {
					inline static void before(const test_data_type&, std::string& json_data_out) {
						json_data_out.clear();
					}

					inline static size_t impl(const test_data_type& json_data_in, std::string& json_data_out) {
						return serialize_test_struct::serialize(json_data_in, json_data_out);
					}
				};
				std::string reused_output;
				gated_benchmark<reused_test_name, simdjson_reflection_library_name, reused_serialize_test_struct>::impl(json_data, reused_output);
			} catch (const std::exception& error) {
				std::cout << "simdjson Reflection Error: " << error.what() << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-simdjson-reflection.json");
		}
	};
#else
	template<test_types test_type, benchmarksuite::string_literal test_name_new, bool minified, typename test_data_type>
	struct library_traits<test_type, json_libraries::simdjson_reflection, test_name_new, minified, test_data_type> {
		template<typename json_input_type> inline static void run(json_input_type&) {
		}
	};
#endif

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::minify, json_libraries::simdjson, test_name_new, false, std::string> {
		inline static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			struct minify_test_struct {
				inline static size_t minify(std::string& json_data_in, std::string& json_data_out) {
					json_data_out.resize(json_data_in.size());
					size_t minified_size{};
					if (simdjson::minify(json_data_in.data(), json_data_in.size(), json_data_out.data(), minified_size) != simdjson::SUCCESS) {
						minified_size = 0;
					}
					json_data_out.resize(minified_size);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return minified_size;
				}

				inline static size_t impl(std::string& json_data_in) {
					std::string json_data_out;
					return minify( json_data_in, json_data_out);
				}
			};
			std::string json_data_out;
			try {
				gated_benchmark<test_name, simdjson_library_name, minify_test_struct>::impl(json_data_in);
				minify_test_struct::minify(json_data_in, json_data_out);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_minify_test_struct {
					inline static void before(std::string&, std::string& json_data_out) {
						json_data_out.clear();
					}

					inline static size_t impl(std::string& json_data_in, std::string& json_data_out) {
						return minify_test_struct::minify( json_data_in, json_data_out);
					}
				};
				std::string reused_output;
				gated_benchmark<reused_test_name, simdjson_library_name, reused_minify_test_struct>::impl(json_data_in, reused_output);
			} catch (const std::exception& error) {
				std::cout << "simdjson Error: " << error.what() << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-simdjson.json");
		}
	};

	template<benchmarksuite::string_literal test_name_new> struct library_traits<test_types::prettify, json_libraries::simdjson, test_name_new, false, std::string> {
		inline static auto run(std::string& json_data_in) {
			static constexpr benchmarksuite::string_literal test_name{ test_name_new + " Write" };
			simdjson::dom::parser parser;
			struct prettify_test_struct {
				inline static size_t prettify(simdjson::dom::parser& parser_new, std::string& json_data_in, std::string& json_data_out) {
					simdjson::dom::element element;
					if (auto error = parser_new.parse(json_data_in).get(element); error) {
						std::cout << "simdjson Error: " << simdjson::error_message(error) << std::endl;
						return 0;
					}
					json_data_out = simdjson::prettify(element);
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					return prettify(parser_new, json_data_in, json_data_out);
				}
			};
			std::string json_data_out;
			try {
				gated_benchmark<test_name, simdjson_library_name, prettify_test_struct>::impl(parser, json_data_in);
				prettify_test_struct::prettify(parser, json_data_in, json_data_out);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_prettify_test_struct {
					inline static void before(simdjson::dom::parser&, std::string&, std::string& json_data_out) {
						json_data_out.clear();
					}

					inline static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in, std::string& json_data_out) {
						return prettify_test_struct::prettify(parser_new, json_data_in, json_data_out);
					}
				};
				std::string reused_output;
				gated_benchmark<reused_test_name, simdjson_library_name, reused_prettify_test_struct>::impl(parser, json_data_in, reused_output);
			} catch (const std::exception& error) {
				std::cout << "simdjson Error: " << error.what() << std::endl;
			}
			benchmarksuite::file_handle::save_file(json_data_out, json_out_path + "/" + test_name + "-simdjson.json");
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
		return benchmarksuite::string_literal{ "#### Here are the commits we used:\n----\n" + make_commit_row<"Jsonifier", "nihilai-collective/Jsonifier", JSONIFIER_COMMIT>() +
			make_commit_row<"Glaze", "stephenberry/glaze", GLAZE_COMMIT>() + make_commit_row<"simdjson", "simdjson/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> consteval auto generate_section() {
		constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_graph + " Results [(Here is the data we used for this test)](./json/" + benchmarksuite::url_encode_literal<test_name_new_json>() +
			".json):\n\n" + "<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" +
			current_path + "/" + test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"1200\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result = std::format("\n#### How We Benchmarked & What We Tested\n\n"
										 "| Library | Active Implementation / Backends |\n"
										 "| :--- | :--- |\n"
										 "| **Jsonifier** | `{}` |\n"
										 "| **simdjson (ondemand)** | `{}` |\n",
			jsonifier::cpuArchName, simdjson::get_active_implementation()->name());

#if SIMDJSON_STATIC_REFLECTION
		result += std::format("| **simdjson (reflection)** | `{}` |\n", simdjson::get_active_implementation()->name());
#endif

		result += std::format("| **Glaze** | utf8: `{}`, escape: `{}`, float: `{}`, struct-skip: `{}` |\n\n", glz::simd_info.utf8_validation, glz::simd_info.string_escape,
			glz::simd_info.float_write, glz::simd_info.structural_skip);

		result += std::format("> **How the sampling/convergence works ({0}):**  \n"
							  "> The iterations grow geometrically ({1} → {2} → {3} ...) up to a max of {4}.  \n"
							  "> Scores come from a trailing window of `max(iterations/10, {5})` (capped at {6}) over at most {7}s.  \n"
							  "> The epoch that counts is whichever one has the lowest (RSE + epoch-over-epoch mean shift).  \n"
							  "> Converged means RSE ≤ {8}% and mean shift ≤ {9}%. Ties get called using Welch's t-test with Bessel-corrected variance.\n\n"
							  "---\n\n",
			benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name(), config.measured_iteration_count, config.measured_iteration_count * 2,
			config.measured_iteration_count * 4, config.max_iteration_count, config.min_k, config.max_k, config.max_time_in_s, config.rse_threshold, config.convergence_threshold);

		result +=
			"##### The Test Variants\n"
			"* **Standard vs. (Reused):** Standard builds, parses/serializes, and tears everything down every iteration. `(Reused)` keeps the buffer/object around across "
			"iterations and clears it outside the timed region, so you just see the raw parse/format throughput.\n"
			"* **Document Sizes:** \"Small\" tests cap minified payloads at 5 KiB (via `GenerateSmallJson.py`), so dispatch/setup/small-alloc latency dominates "
			"instead of bulk SIMD throughput.\n"
			"* **Key Traversal Order:** Standard tests go in key order, `Reverse` tests go backwards, which hits single-pass forward-only decoders (simdjson On Demand) "
			"with an $O(N^2)$ penalty that hash/DOM-indexed ones dodge.\n\n"
			"##### A Few Details\n"
			"* **simdjson (ondemand):** Includes the harness mapping layer (`include/common.hpp`). On MSVC it uses `find_field` / `find_field_unordered` instead, because of some "
			"pretty severe compiler "
			"overhead when instantiating `object::for_each`.\n"
#if SIMDJSON_STATIC_REFLECTION
			"* **simdjson (reflection):** The C++26 static reflection API (P2996). Minified serialization only, for now.\n"
#else
			"* **simdjson (reflection):** Not in this run, since this toolchain does not support P2996 static reflection yet.\n"
#endif
			"* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.\n"
			"* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.\n\n"
			"---\n";

		result += "*Generated with BenchmarkSuite commit: [" + std::string{ BNCH_SWT_COMMIT } + "](https://github.com/nihilai-collective/benchmarksuite/commit/" +
			std::string{ BNCH_SWT_COMMIT } + ")*\n";
		return result;
	}

	template<typename results_type> struct ranked_rows : results_type {
		inline explicit ranked_rows(const results_type& base) : results_type{ base } {
		}

		inline const auto& rows() const {
			return this->sorted_results;
		}
	};

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

	inline std::string read_file_if_present(const std::string& path) {
		if (!std::filesystem::exists(path)) {
			return {};
		}
		return benchmarksuite::file_handle::get(path);
	}

	inline std::string result_file_stem(std::string_view result_name) {
		return std::string{ csv_out_path.operator std::string_view() } + "/" + std::string{ result_name };
	}

	inline std::string position_type_name(uint64_t position_type_val) {
		switch (position_type_val) {
			case static_cast<uint64_t>(benchmarksuite::internal::position_type::win): {
				return "Win";
			}
			case static_cast<uint64_t>(benchmarksuite::internal::position_type::tie): {
				return "Tie";
			}
			case static_cast<uint64_t>(benchmarksuite::internal::position_type::loss): {
				return "Loss";
			}
			default: {
				return "None";
			}
		}
	}

	struct test_descriptor {
		std::string_view base_name{};
		std::string_view name{};
		test_flags flags{};
	};

	inline std::string result_name(const test_descriptor& descriptor) {
		return std::string{ descriptor.name } + (has_flags(descriptor.flags, test_flags::write) ? " Write" : " Read");
	}

	class test_selection {
	  public:
		inline test_selection(int32_t argc, char** argv) {
			std::string joined;
			for (int32_t index = 1; index < argc; ++index) {
				const std::string_view argument{ argv[index] };
				const bool quoted_name{ argument.find(' ') != std::string_view::npos };
				if (!joined.empty()) {
					joined += quoted_name ? ',' : ' ';
				}
				joined += argument;
				if (quoted_name) {
					joined += ',';
				}
			}
			test_flags requested_flags{ test_flags::none };
			size_t start{};
			while (start <= joined.size()) {
				size_t end = joined.find(',', start);
				if (end == std::string::npos) {
					end = joined.size();
				}
				std::string token = normalize_test_name(std::string_view{ joined }.substr(start, end - start));
				if (const test_flags flag = flag_for_token(token); flag != test_flags::none) {
					requested_flags = requested_flags | flag;
				} else if (!token.empty()) {
					requested.emplace_back(std::move(token));
				}
				start = end + 1;
			}
			mask = complete_flags(requested_flags);
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
			if (token == "--read") {
				return test_flags::read;
			}
			if (token == "--write") {
				return test_flags::write;
			}
			return test_flags::none;
		}

		inline static bool token_matches(const std::string& token, const test_descriptor& descriptor) {
			return token == normalize_test_name(result_name(descriptor)) || token == normalize_test_name(descriptor.name) || token == normalize_test_name(descriptor.base_name);
		}

		inline bool axis_allows(test_flags flags, test_flags axis) const {
			return !has_flags(flags, axis) || has_flags(flags & mask, axis);
		}

		inline bool allows(test_flags flags) const {
			return axis_allows(flags, test_flags::formats) && axis_allows(flags, test_flags::modes) && axis_allows(flags, test_flags::directions);
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
		static constexpr bool write{ has_flags(flags, test_flags::write) };
		static constexpr bool read{ has_flags(flags, test_flags::read) };
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
			static_cast<void>(((index == indices ? (variants::execute(), true) : false) || ...));
		}
	};

	template<typename variant_list> struct test_registry_impl;

	template<typename... variants> struct test_registry_impl<type_list<variants...>> {
		static constexpr std::array<test_descriptor, sizeof...(variants)> descriptors{ { variants::descriptor... } };

		inline static void run(const test_selection& selection) {
			const std::vector<size_t> indices{ selection.resolve(descriptors) };
			benchmarksuite::pin_for_benchmark();
			for (const size_t index: indices) {
				active_test_flags = descriptors[index].flags & selection.runtime_mask();
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

	struct ranked_entry {
		std::string name{};
		uint64_t position{};
		std::string position_type{};
	};

	inline std::vector<ranked_entry> read_ranks(const std::string& path) {
		std::vector<ranked_entry> entries;
		std::istringstream stream{ read_file_if_present(path) };
		std::string line;
		while (std::getline(stream, line)) {
			if (!line.empty() && line.back() == '\r') {
				line.pop_back();
			}
			const size_t type_pos	  = line.rfind(',');
			const size_t position_pos = type_pos == std::string::npos || type_pos == 0 ? std::string::npos : line.rfind(',', type_pos - 1);
			if (position_pos == std::string::npos) {
				continue;
			}
			entries.emplace_back(ranked_entry{ .name = line.substr(0, position_pos),
				.position							 = std::stoull(line.substr(position_pos + 1, type_pos - position_pos - 1)),
				.position_type						 = line.substr(type_pos + 1) });
		}
		return entries;
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

	inline void tally_positions(const std::vector<ranked_entry>& entries, std::vector<library_tally>& tallies) {
		for (const auto& entry: entries) {
			auto existing		 = std::find_if(tallies.begin(), tallies.end(), library_name_matcher{ entry.name });
			library_tally& tally = existing != tallies.end() ? *existing : tallies.emplace_back(library_tally{ .name = entry.name });
			if (entry.position_type == "Win") {
				++tally.wins;
			} else if (entry.position_type == "Tie") {
				++tally.ties;
			} else if (entry.position_type == "Loss") {
				++tally.losses;
			}
		}
	}

	inline void tally_combined(const std::vector<ranked_entry>& entries, std::string_view first_variant, std::string_view second_variant, library_tally& tally) {
		static constexpr uint64_t unranked{ std::numeric_limits<uint64_t>::max() };
		uint64_t best_variant_position{ unranked };
		for (const auto& entry: entries) {
			if (entry.name == first_variant || entry.name == second_variant) {
				best_variant_position = std::min(best_variant_position, entry.position);
			}
		}
		if (best_variant_position == unranked) {
			return;
		}
		bool tied_with_other_library{};
		for (const auto& entry: entries) {
			if (entry.name != first_variant && entry.name != second_variant && entry.position == best_variant_position) {
				tied_with_other_library = true;
			}
		}
		if (tied_with_other_library) {
			++tally.ties;
		} else if (best_variant_position == 1) {
			++tally.wins;
		} else {
			++tally.losses;
		}
	}

	inline std::string format_tally(const library_tally& tally) {
		return tally.name + "," + std::to_string(tally.wins) + "," + std::to_string(tally.ties) + "," + std::to_string(tally.losses) + "\n";
	}

	template<typename registry> inline std::string assemble_results_csv() {
		std::string current{ benchmark_stage::get_all_results().to_csv() };
		static constexpr std::string_view tally_header{ "Library,Wins,Ties,Losses" };
		const size_t header_pos = current.find(tally_header);
		std::string result{ header_pos == std::string::npos ? current : current.substr(0, header_pos + tally_header.size()) };
		result += '\n';
		std::vector<library_tally> tallies;
		library_tally jsonifier_combined{ .name = "Jsonifier (combined)" };
		library_tally simdjson_combined{ .name = "simdjson (combined)" };
		for (const auto& stem: result_stems<registry>()) {
			const auto entries{ read_ranks(stem + ".ranks") };
			tally_positions(entries, tallies);
			tally_combined(entries, jsonifier_library_name.operator std::string_view(), jsonifier_two_stage_library_name.operator std::string_view(), jsonifier_combined);
			tally_combined(entries, simdjson_library_name.operator std::string_view(), simdjson_reflection_library_name.operator std::string_view(), simdjson_combined);
		}
		std::sort(tallies.begin(), tallies.end(), std::greater<library_tally>{});
		for (const auto& tally: tallies) {
			result += format_tally(tally);
		}
		result += format_tally(jsonifier_combined);
		result += format_tally(simdjson_combined);
		return result;
	}

	template<test_types test_type> struct test_type_suffix {
		static constexpr benchmarksuite::string_literal value{ " Write" };
	};

	template<> struct test_type_suffix<test_types::parse> {
		static constexpr benchmarksuite::string_literal value{ " Read" };
	};

	template<> struct test_type_suffix<test_types::validate> {
		static constexpr benchmarksuite::string_literal value{ " Read" };
	};

	template<test_types test_type, benchmarksuite::string_literal test_name_new, typename test_data_type, typename... library_traits> struct test_traits {
		static constexpr benchmarksuite::string_literal test_type_string{ test_type_suffix<test_type>::value };

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
			const std::string stem{ result_file_stem(result_name.operator std::string_view()) };
			std::string ranks;
			const ranked_rows<std::remove_cvref_t<decltype(results)>> ranked{ results };
			for (const auto& row: ranked.rows()) {
				ranks += std::string{ row.name } + "," + std::to_string(row.position) + "," + position_type_name(static_cast<uint64_t>(row.position_type_val)) + "\n";
			}
			benchmarksuite::file_handle::save_file(ranks, stem + ".ranks");
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
				benchmarksuite::file_handle::save_file(json_results, stem + ".md");
			}
		}
	};

	inline std::string get_padded_json_string(const std::string& path) {
		auto raw_data = benchmarksuite::file_handle::get(path);
		raw_data.reserve(raw_data.size() + simdjson::SIMDJSON_PADDING);
		return raw_data;
	}

	template<test_types test_type, typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod = false, typename... library_traits> inline void execute_test() {
		std::string full_path;
		full_path.reserve(json_path.size() + 1 + test_name.size() + 5);
		full_path += std::string_view{ json_path };
		full_path += "/";
		full_path += std::string_view{ test_name };
		full_path += ".json";

		if constexpr (is_pod) {
			auto test_datas = string_to_vector(benchmarksuite::file_handle::get(full_path));
			test_traits<test_type, test_name, test_data_type, library_traits...>::run(test_datas);
		} else {
			auto json_data_in = get_padded_json_string(full_path);
			test_traits<test_type, test_name, test_data_type, library_traits...>::run(json_data_in);
		}
	}

	inline constexpr test_flags direction_of(test_types test_type) noexcept {
		return test_type == test_types::parse || test_type == test_types::validate ? test_flags::read : test_flags::write;
	}

	using json_parse_libraries =
		library_list<json_libraries::glaze, json_libraries::jsonifier, json_libraries::jsonifier_two_stage, json_libraries::simdjson, json_libraries::simdjson_reflection>;
	using pod_parse_libraries = library_list<json_libraries::glaze, json_libraries::jsonifier, json_libraries::simdjson, json_libraries::simdjson_reflection>;
	using serialize_libraries = library_list<json_libraries::glaze, json_libraries::jsonifier, json_libraries::simdjson_reflection>;
	using prettify_libraries  = library_list<json_libraries::jsonifier, json_libraries::glaze, json_libraries::simdjson>;
	using minify_libraries	  = library_list<json_libraries::glaze, json_libraries::jsonifier, json_libraries::simdjson>;
	using validate_libraries  = library_list<json_libraries::jsonifier, json_libraries::glaze>;

	template<test_types test_type, benchmarksuite::string_literal base_name_new, typename test_data_type, bool pod_new, test_flags flags_new, typename libraries>
	struct test_variant;

	template<test_types test_type, benchmarksuite::string_literal base_name_new, typename test_data_type, bool pod_new, test_flags flags_new, json_libraries... json_library>
	struct test_variant<test_type, base_name_new, test_data_type, pod_new, flags_new, library_list<json_library...>> {
		static constexpr benchmarksuite::string_literal name{ base_name_new + format_suffix<flags_new & test_flags::formats>::value };
		static constexpr test_flags flags{ (flags_new & (test_flags::formats | test_flags::modes)) | direction_of(test_type) };
		static constexpr benchmarksuite::string_literal base_name{ base_name_new };
		static constexpr test_descriptor descriptor{ .base_name = base_name, .name = name, .flags = flags };
		static constexpr bool traits_flag{ pod_new || has_flags(flags_new, test_flags::minified) };
		using variants = type_list<test_variant>;

		inline static void execute() {
			execute_test<test_type, test_data_type, name, pod_new, library_traits<test_type, json_library, name, traits_flag, test_data_type>...>();
		}
	};

	template<benchmarksuite::string_literal base_name, typename test_data_type, test_flags flags_new = test_flags::all> struct pod_tests {
		using set	   = flag_set<flags_new>;
		using variants = typename test_group<keep_if<set::read, test_variant<test_types::parse, base_name, test_data_type, true, set::modes, pod_parse_libraries>>,
			keep_if<set::write, test_variant<test_types::serialize, base_name, test_data_type, true, set::modes, serialize_libraries>>>::variants;
	};

	template<benchmarksuite::string_literal base_name, typename test_data_type, test_flags flags_new = test_flags::all> struct json_tests {
		using set = flag_set<flags_new>;
		static constexpr test_flags prettified_flags{ test_flags::prettified | set::modes };
		static constexpr test_flags minified_flags{ test_flags::minified | set::modes };
		using variants =
			typename test_group<keep_if<set::minified && set::read, test_variant<test_types::parse, base_name, test_data_type, false, minified_flags, json_parse_libraries>>,
				keep_if<set::minified && set::write, test_variant<test_types::serialize, base_name, test_data_type, false, minified_flags, serialize_libraries>>,
				keep_if<set::prettified && set::read, test_variant<test_types::parse, base_name, test_data_type, false, prettified_flags, json_parse_libraries>>,
				keep_if<set::prettified && set::write, test_variant<test_types::serialize, base_name, test_data_type, false, prettified_flags, serialize_libraries>>>::variants;
	};

	template<test_types test_type, benchmarksuite::string_literal base_name, typename libraries, test_flags flags_new = test_flags::all> struct raw_test {
		using set	   = flag_set<flags_new>;
		using variants = typename keep_if<has_flags(set::flags, direction_of(test_type)), test_variant<test_type, base_name, std::string, false, set::modes, libraries>>::variants;
	};

	using registered_tests = test_registry<pod_tests<"Bool Test", bool>, pod_tests<"Double Test", double>, pod_tests<"Int64 Test", int64_t>, pod_tests<"String Test", std::string>,
		pod_tests<"Uint64 Test", uint64_t>, raw_test<test_types::minify, "Minify Test", minify_libraries>>;

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