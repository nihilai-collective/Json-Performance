/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/package_json.hpp
 */

#pragma once

#include <common.hpp>
#include <fstream>
#include <optional>

namespace tests {

	struct package_json_fields {
		std::optional<std::string> exports{};
		std::optional<std::string> imports{};
		std::optional<std::string> scripts{};
		std::optional<std::string> name{};
		std::optional<std::string> main{};
		std::string type{ "none" };
		std::optional<bool> is_private{};
	};

	struct package_json_corpus {
		std::vector<std::string> documents{};
		uint64_t bytes{};
	};

	inline package_json_corpus load_package_json_corpus(uint64_t low, uint64_t high) {
		const std::string folder{ std::string{ json_path.operator std::string_view() } + "/package_json" };
		std::ifstream listing{ folder + "/Sources.txt" };
		package_json_corpus corpus{};
		std::string name;
		uint64_t size{};
		std::string source;
		while (listing >> name >> size >> source) {
			if (size < low || size >= high) {
				continue;
			}
			std::string text{ benchmarksuite::file_handle::get(folder + "/" + name) };
			std::string padded;
			padded.reserve(text.size() + simdjson::SIMDJSON_PADDING);
			padded.assign(text);
			corpus.bytes += padded.size();
			corpus.documents.emplace_back(std::move(padded));
		}
		if (corpus.documents.empty()) {
			throw std::runtime_error{ std::format("No package.json corpus files between {} and {} bytes under {}", low, high, folder) };
		}
		return corpus;
	}

	struct jsonifier_package_json_parser {
		jsonifier::generic::package_json_fields view{};
		jsonifier::jsonifier_core parser{};

		inline static void store(std::optional<std::string>& target, bool present, jsonifier::string_view text) {
			if (present) {
				target.emplace(text.data(), static_cast<size_t>(text.size()));
			}
		}

		inline bool parse(const std::string& json, package_json_fields& fields) {
			view = jsonifier::generic::package_json_fields{};
			if (parser.readPackageJson(json, view) != jsonifier::generic::error_codes::success) {
				return false;
			}
			store(fields.exports, view.hasExports, view.exports);
			store(fields.imports, view.hasImports, view.imports);
			store(fields.scripts, view.hasScripts, view.scripts);
			store(fields.name, view.hasName, view.name);
			store(fields.main, view.hasMain, view.main);
			if (!view.type.empty()) {
				fields.type.assign(view.type.data(), static_cast<size_t>(view.type.size()));
			}
			if (view.hasPrivate) {
				fields.is_private = view.isPrivate;
			}
			return true;
		}
	};

	struct simdjson_package_json_parser {
		simdjson::ondemand::parser parser{};

		inline bool parse(const std::string& json, package_json_fields& fields) {
			simdjson::ondemand::document document;
			simdjson::ondemand::object main_object;
			if (parser.iterate(simdjson::padded_string_view{ json.data(), json.size(), json.capacity() }).get(document) || document.get_object().get(main_object)) {
				return false;
			}
			simdjson::ondemand::raw_json_string key;
			simdjson::ondemand::value value;
			std::string_view field_value;
			simdjson::ondemand::json_type field_type;
			for (auto field: main_object) {
				if (field.key().get(key) || field.value().get(value)) {
					return false;
				}
				if (key.raw() == nullptr) {
					continue;
				}
				if (key == "name") {
					std::string name;
					if (value.get_string(name)) {
						return false;
					}
					fields.name = std::move(name);
				} else if (key == "main") {
					std::string main;
					if (!value.get_string(main)) {
						fields.main = std::move(main);
					}
				} else if (key == "exports" || key == "imports") {
					std::optional<std::string>& target = key == "exports" ? fields.exports : fields.imports;
					if (value.type().get(field_type)) {
						return false;
					}
					if (field_type == simdjson::ondemand::json_type::object || field_type == simdjson::ondemand::json_type::array) {
						if (value.raw_json().get(field_value)) {
							return false;
						}
						target = std::string{ field_value };
					} else if (field_type == simdjson::ondemand::json_type::string) {
						std::string text;
						if (value.get_string(text)) {
							return false;
						}
						target = std::move(text);
					}
				} else if (key == "type") {
					if (value.get_string().get(field_value)) {
						return false;
					}
					if (field_value == "commonjs" || field_value == "module") {
						fields.type = std::string{ field_value };
					}
				} else if (key == "private") {
					bool is_private;
					if (!value.get_bool().get(is_private)) {
						fields.is_private = is_private;
					}
				} else if (key == "scripts") {
					if (value.type().get(field_type)) {
						return false;
					}
					if (field_type == simdjson::ondemand::json_type::object) {
						if (value.raw_json().get(field_value)) {
							return false;
						}
						fields.scripts = std::string{ field_value };
					}
				}
			}
			return true;
		}
	};

	template<typename parser_type> struct package_json_corpus_pass {
		inline static size_t impl(parser_type& parser, package_json_corpus& corpus) {
			uint64_t failures{};
			for (const std::string& document: corpus.documents) {
				package_json_fields fields{};
				failures += parser.parse(document, fields) ? 0 : 1;
				benchmarksuite::do_not_optimize_away(fields);
			}
			if (failures != 0) {
				throw std::runtime_error{ std::format("{} package.json corpus documents failed to parse", failures) };
			}
			return corpus.bytes;
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified>
	struct library_traits<json_libraries::jsonifier_generic, test_name_new, minified, package_json_corpus> {
		inline static auto run(package_json_corpus& corpus) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
			jsonifier_package_json_parser parser{};
			gated_benchmark<test_name_read, jsonifier_generic_library_name, package_json_corpus_pass<jsonifier_package_json_parser>>::impl(parser, corpus);
		}
	};

	template<benchmarksuite::string_literal test_name_new, bool minified> struct library_traits<json_libraries::simdjson, test_name_new, minified, package_json_corpus> {
		inline static auto run(package_json_corpus& corpus) {
			static constexpr benchmarksuite::string_literal test_name_read{ test_name_new + " Read" };
			simdjson_package_json_parser parser{};
			try {
				gated_benchmark<test_name_read, simdjson_library_name, package_json_corpus_pass<simdjson_package_json_parser>>::impl(parser, corpus);
			} catch (const std::exception& error) {
				std::cout << "simdjson Error: " << error.what() << std::endl;
			}
		}
	};

	struct package_json_parity {
		inline static void impl(const package_json_corpus& corpus) {
			jsonifier_package_json_parser jsonifier_parser{};
			simdjson_package_json_parser simdjson_parser{};
			for (size_t index = 0; index < corpus.documents.size(); ++index) {
				package_json_fields a{};
				package_json_fields b{};
				const bool parsed_a = jsonifier_parser.parse(corpus.documents[index], a);
				const bool parsed_b = simdjson_parser.parse(corpus.documents[index], b);
				if (parsed_a != parsed_b || a.name != b.name || a.main != b.main || a.type != b.type || a.exports != b.exports || a.imports != b.imports ||
					a.scripts != b.scripts || a.is_private != b.is_private) {
					throw std::runtime_error{ std::format("package.json parity mismatch on corpus document {}", index) };
				}
			}
		}
	};

}
