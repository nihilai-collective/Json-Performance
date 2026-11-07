/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/tests.hpp
 */

#pragma once

#include <algorithm>
#include <atomic>
#include <csignal>
#include <cstdlib>
#include <filesystem>
#include <sstream>
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
			for (auto& value: parser.getErrors()) {
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
			for (auto& value: parser.getErrors()) {
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
			for (auto& value: parser.getErrors()) {
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
			for (auto& value: parser.getErrors()) {
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
			static constexpr glz::opts read_opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified };
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
			static constexpr glz::opts read_opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified };
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
			static constexpr bool error_on_unknown_keys{ !std::is_same_v<test_data_type, twitter_message> };
			test_data_type json_data{};
			if (auto error = glz::read<glz::opts{ .error_on_unknown_keys = error_on_unknown_keys, .skip_null_members = false, .prettify = !minified, .minified = minified }>(
					json_data, json_data_in_pre);
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
			simdjson::dom::parser parser;
			struct minify_test_struct {
				inline static size_t minify(simdjson::dom::parser& parser_new, std::string& json_data_in, std::string& json_data_out) {
					json_data_out = simdjson::minify(parser_new.parse(json_data_in));
					benchmarksuite::do_not_optimize_away(json_data_out);
					return json_data_out.size();
				}

				inline static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in) {
					std::string json_data_out;
					return minify(parser_new, json_data_in, json_data_out);
				}
			};
			std::string json_data_out;
			try {
				gated_benchmark<test_name, simdjson_library_name, minify_test_struct>::impl(parser, json_data_in);
				minify_test_struct::minify(parser, json_data_in, json_data_out);
				static constexpr benchmarksuite::string_literal reused_test_name{ test_name + reused_suffix };
				struct reused_minify_test_struct {
					inline static void before(simdjson::dom::parser&, std::string&, std::string& json_data_out) {
						json_data_out.clear();
					}

					inline static size_t impl(simdjson::dom::parser& parser_new, std::string& json_data_in, std::string& json_data_out) {
						return minify_test_struct::minify(parser_new, json_data_in, json_data_out);
					}
				};
				std::string reused_output;
				gated_benchmark<reused_test_name, simdjson_library_name, reused_minify_test_struct>::impl(parser, json_data_in, reused_output);
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

	template<benchmarksuite::string_literal label, benchmarksuite::string_literal org_repo, benchmarksuite::string_literal commit> inline consteval auto make_commit_row() {
		return benchmarksuite::string_literal{ "| " + label + ": [" + commit + "](https://github.com/" + org_repo + "/commit/" + commit + ")  \n" };
	}

	inline consteval auto make_section00() {
		using system_info = benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>;
		return benchmarksuite::string_literal{ "# " + stage_name + "\nPerformance profiling of JSON libraries (Compiled and run on " + system_info::os_id + " " +
			system_info::os_version + " using the " + system_info::compiler_id + " " + system_info::compiler_version + " compiler).  \n\nLatest Results: (" };
	}

	inline consteval auto make_section01() {
		return benchmarksuite::string_literal{ "#### Using the following commits:\n----\n" + make_commit_row<"Jsonifier", "nihilai-collective/Jsonifier", JSONIFIER_COMMIT>() +
			make_commit_row<"Glaze", "stephenberry/glaze", GLAZE_COMMIT>() + make_commit_row<"simdjson", "simdjson/simdjson", SIMDJSON_COMMIT>() };
	}

	template<benchmarksuite::string_literal test_name_new_graph, benchmarksuite::string_literal test_name_new_json> inline consteval auto generate_section() {
		constexpr benchmarksuite::string_literal test_name_graph{ benchmarksuite::url_encode_literal<test_name_new_graph>() };
		return "\n----\n### " + test_name_new_graph + " Results [(View the data used in the following test)](./json/" + benchmarksuite::url_encode_literal<test_name_new_json>() +
			".json):\n\n" + "<p align=\"left\"><a href=\"./graphs/" + current_path + "/" + test_name_graph + "_Results.png\" target=\"_blank\"><img src=\"./graphs/" +
			current_path + "/" + test_name_graph + "_Results.png?raw=true\" \nalt=\"\" width=\"1200\"/></a></p>\n\n";
	}

	inline std::string make_section02() {
		std::string result = std::format("\n#### Benchmark Methodology & Test Matrix\n\n"
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

		result += std::format("> **Adaptive Sampling & Convergence ({0}):**  \n"
							  "> Iterations scale geometrically ({1} → {2} → {3} ...) up to a maximum of {4}.  \n"
							  "> Scores evaluate a trailing window of `max(iterations/10, {5})` (cap: {6}) over at most {7}s.  \n"
							  "> Canonical epochs are chosen by minimum (RSE + epoch-over-epoch mean shift).  \n"
							  "> Converged: RSE ≤ {8}% and mean shift ≤ {9}%. Tie detection: Welch's t-test with Bessel-corrected variance.\n\n"
							  "---\n\n",
			benchmarksuite::system_info_data<benchmarksuite::benchmark_types::cpu>::device_name(), config.measured_iteration_count, config.measured_iteration_count * 2,
			config.measured_iteration_count * 4, config.max_iteration_count, config.min_k, config.max_k, config.max_time_in_s, config.rse_threshold, config.convergence_threshold);

		result +=
			"##### Test Variants\n"
			"* **Standard vs. (Reused):** Standard measures full instantiation, parsing/serialization, and teardown per iteration. `(Reused)` holds the buffer/object across "
			"iterations and clears it outside the timed region to isolate raw parse/format throughput.\n"
			"* **Document Sizes:** \"Small\" tests cap minified payloads at 5 KiB (via `GenerateSmallJson.py`) to highlight dispatch, setup, and small-allocation latency rather "
			"than bulk vector throughput.\n"
			"* **Key Traversal Order:** Standard tests provide keys in sequential order. Tests labeled `Reverse` parse keys backwards to highlight the $O(N^2)$ penalty inherent "
			"to single-pass forward-only decoders (e.g., simdjson On Demand) versus hash/DOM-indexed alternatives.\n\n"
			"##### Implementation Details\n"
			"* **simdjson (ondemand):** Includes the harness mapping layer (`include/common.hpp`). On MSVC, uses `find_field` / `find_field_unordered` due to severe compiler "
			"overhead when instantiating `object::for_each`.\n"
#if SIMDJSON_STATIC_REFLECTION
			"* **simdjson (reflection):** C++26 static reflection API (P2996). Minified serialization only.\n"
#else
			"* **simdjson (reflection):** Absent from this run; current toolchain lacks P2996 static reflection support.\n"
#endif
			"* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.\n"
			"* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.\n\n"
			"---\n";

		result += std::format("*Environment generated via BenchmarkSuite commit: [{0}](https://github.com/nihilai-collective/benchmarksuite/commit/{0})*\n", BNCH_SWT_COMMIT);
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
				if (std::ranges::find(variants, variant_name) == variants.end()) {
					variants.emplace_back(variant_name);
				}
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

		inline std::vector<std::string> result_stems() const {
			static constexpr std::string_view suffixes[]{ " Read", " Read (Reused)", " Write", " Write (Reused)" };
			std::vector<std::string> stems;
			stems.reserve(variants.size() * std::size(suffixes));
			for (const auto& variant: variants) {
				for (const auto suffix: suffixes) {
					stems.emplace_back(result_file_stem(variant + std::string{ suffix }));
				}
			}
			return stems;
		}

		inline std::string assemble_markdown(std::string header) const {
			for (const auto& stem: result_stems()) {
				header += read_file_if_present(stem + ".md");
			}
			return header;
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
			auto existing		 = std::ranges::find_if(tallies, library_name_matcher{ entry.name });
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

	inline std::string assemble_results_csv(const test_registry& registry) {
		std::string current{ benchmark_stage::get_all_results().to_csv() };
		static constexpr std::string_view tally_header{ "Library,Wins,Ties,Losses" };
		const size_t header_pos = current.find(tally_header);
		std::string result{ header_pos == std::string::npos ? current : current.substr(0, header_pos + tally_header.size()) };
		result += '\n';
		std::vector<library_tally> tallies;
		library_tally jsonifier_combined{ .name = "Jsonifier (combined)" };
		library_tally simdjson_combined{ .name = "simdjson (combined)" };
		for (const auto& stem: registry.result_stems()) {
			const auto entries{ read_ranks(stem + ".ranks") };
			tally_positions(entries, tallies);
			tally_combined(entries, jsonifier_library_name.operator std::string_view(), jsonifier_two_stage_library_name.operator std::string_view(), jsonifier_combined);
			tally_combined(entries, simdjson_library_name.operator std::string_view(), simdjson_reflection_library_name.operator std::string_view(), simdjson_combined);
		}
		std::ranges::sort(tallies, std::greater<library_tally>{});
		for (const auto& tally: tallies) {
			result += format_tally(tally);
		}
		result += format_tally(jsonifier_combined);
		result += format_tally(simdjson_combined);
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

	template<test_types test_type, typename test_data_type, benchmarksuite::string_literal test_name, bool is_pod = false, typename... library_traits>
	inline void execute_test(test_registry& registry) {
		if (!registry.select(test_name.operator std::string_view())) {
			return;
		}
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

	template<benchmarksuite::string_literal test_name, typename test_data_type, bool is_pod = false> inline void run_pod_tests(test_registry& registry) {
		execute_test<test_types::parse, test_data_type, test_name, is_pod, library_traits<test_types::parse, json_libraries::glaze, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name, is_pod, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name, is_pod, test_data_type>>(registry);
		execute_test<test_types::serialize, test_data_type, test_name, is_pod, library_traits<test_types::serialize, json_libraries::glaze, test_name, is_pod, test_data_type>,
			library_traits<test_types::serialize, json_libraries::jsonifier, test_name, is_pod, test_data_type>,
			library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name, is_pod, test_data_type>>(registry);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> inline void run_minified_pair(test_registry& registry) {
		execute_test<test_types::parse, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name + " (Minified)", true, test_data_type>>(registry);
		execute_test<test_types::serialize, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::serialize, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::serialize, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name + " (Minified)", true, test_data_type>>(registry);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> inline void run_prettified_pair(test_registry& registry) {
		execute_test<test_types::parse, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name + " (Prettified)", false, test_data_type>>(registry);
		execute_test<test_types::serialize, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::serialize, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::serialize, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::serialize, json_libraries::simdjson_reflection, test_name + " (Prettified)", false, test_data_type>>(registry);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> inline void run_tests_pair(test_registry& registry) {
		run_minified_pair<test_name, test_data_type>(registry);
		run_prettified_pair<test_name, test_data_type>(registry);
	}

	template<benchmarksuite::string_literal test_name, typename test_data_type> inline void run_parse_tests(test_registry& registry) {
		execute_test<test_types::parse, test_data_type, test_name + " (Minified)", false,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Minified)", true, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name + " (Minified)", true, test_data_type>>(registry);
		execute_test<test_types::parse, test_data_type, test_name + " (Prettified)", false,
			library_traits<test_types::parse, json_libraries::jsonifier, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::jsonifier_two_stage, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::glaze, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson, test_name + " (Prettified)", false, test_data_type>,
			library_traits<test_types::parse, json_libraries::simdjson_reflection, test_name + " (Prettified)", false, test_data_type>>(registry);
	}

	inline void run_all_tests(test_registry& registry) {
		run_pod_tests<"Bool Test", bool, true>(registry);
		run_pod_tests<"Double Test", double, true>(registry);
		run_pod_tests<"Int64 Test", int64_t, true>(registry);
		run_pod_tests<"String Test", std::string, true>(registry);
		run_pod_tests<"Uint64 Test", uint64_t, true>(registry);
		run_tests_pair<"Apache Builds Test", apache_builds_message>(registry);
		run_tests_pair<"Canada Test", canada_message>(registry);
		run_tests_pair<"CitmCatalog Test", citm_catalog_message>(registry);
		run_tests_pair<"Discord Test", discord_message>(registry);
		run_tests_pair<"Github Events Test", github_events_message>(registry);
		run_tests_pair<"Google Maps Response Test", google_maps_response_message>(registry);
		run_tests_pair<"Instruments Test", instruments_message>(registry);
		run_tests_pair<"Marine IK Reverse Test", marine_ik_reverse>(registry);
		run_tests_pair<"Marine IK Test", marine_ik>(registry);
		run_tests_pair<"Random Test", random_message>(registry);
		run_parse_tests<"Twitter Partial Test", twitter_partial_message>(registry);
		run_tests_pair<"Twitter Test", twitter_message>(registry);
		run_tests_pair<"Apache Builds Small Test", apache_builds_message>(registry);
		run_tests_pair<"Canada Small Test", canada_message>(registry);
		run_tests_pair<"CitmCatalog Small Test", citm_catalog_message>(registry);
		run_tests_pair<"Discord Small Test", discord_message>(registry);
		run_tests_pair<"Github Events Small Test", github_events_message>(registry);
		run_tests_pair<"Google Maps Response Small Test", google_maps_response_message>(registry);
		run_tests_pair<"Instruments Small Test", instruments_message>(registry);
		run_tests_pair<"Marine IK Reverse Small Test", marine_ik_reverse>(registry);
		run_tests_pair<"Marine IK Small Test", marine_ik>(registry);
		run_tests_pair<"Random Small Test", random_message>(registry);
		run_parse_tests<"Twitter Partial Small Test", twitter_partial_message>(registry);
		run_tests_pair<"Twitter Small Test", twitter_message>(registry);
		execute_test<test_types::minify, std::string, "Minify Test", false, library_traits<test_types::minify, json_libraries::glaze, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::jsonifier, "Minify Test", false, std::string>,
			library_traits<test_types::minify, json_libraries::simdjson, "Minify Test", false, std::string>>(registry);
		execute_test<test_types::prettify, std::string, "Prettify Test", false,
			library_traits<test_types::prettify, json_libraries::jsonifier, "Prettify Test", false, std::string>,
			library_traits<test_types::prettify, json_libraries::glaze, "Prettify Test", false, std::string>,
			library_traits<test_types::prettify, json_libraries::simdjson, "Prettify Test", false, std::string>>(registry);
		execute_test<test_types::validate, std::string, "Validate Test", false,
			library_traits<test_types::validate, json_libraries::jsonifier, "Validate Test", false, std::string>,
			library_traits<test_types::validate, json_libraries::glaze, "Validate Test", false, std::string>>(registry);
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