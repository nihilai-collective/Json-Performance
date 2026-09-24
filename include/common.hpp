/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/common.hpp
 */

#pragma once

#include <benchmarksuite>
#include <simdjson.h>
#include <jsonifier>

#if defined(NDEBUG)
static constexpr auto max_iteration_count{ 100000 };
static constexpr auto measured_iteration_count{ 100 };
#else
static constexpr auto max_iteration_count{ 100 };
static constexpr auto measured_iteration_count{ 20 };
#endif

constexpr benchmarksuite::string_literal current_path{ benchmarksuite::get_current_path_impl() };
constexpr benchmarksuite::string_literal base_path{ BASE_PATH };
constexpr benchmarksuite::string_literal json_path{ base_path + "/json" };
constexpr benchmarksuite::string_literal csv_out_path{ base_path + "/csv" + "/" + current_path };
constexpr benchmarksuite::string_literal json_out_path{ json_path + "/" + current_path };
constexpr benchmarksuite::string_literal graphs_path{ base_path + "/graphs/" + current_path + "/" };
constexpr benchmarksuite::string_literal jsonifier_library_name{ "jsonifier" };
constexpr benchmarksuite::string_literal simdjson_library_name{ "simdjson (ondemand)" };

std::vector<std::string> string_to_vector(const std::string& input) {
	std::vector<std::string> result;
	static constexpr std::string_view start_tag = "[START]";
	static constexpr std::string_view end_tag	= "[END]";
	size_t pos									= 0;

	while (true) {
		size_t start_pos = input.find(start_tag, pos);
		if (start_pos == std::string::npos) {
			break;
		}
		start_pos += start_tag.size();

		size_t end_pos = input.find(end_tag, start_pos);
		if (end_pos == std::string::npos) {
			size_t slice_length = input.size() - start_pos;
			std::string sliced;
			sliced.reserve(slice_length + simdjson::SIMDJSON_PADDING);
			sliced.append(input, start_pos, slice_length);
			result.emplace_back(std::move(sliced));
			break;
		}

		size_t slice_length = end_pos - start_pos;
		std::string sliced;
		sliced.reserve(slice_length + simdjson::SIMDJSON_PADDING);
		sliced.append(input, start_pos, slice_length);
		result.emplace_back(std::move(sliced));

		pos = end_pos + end_tag.size();
	}

	return result;
}

template<typename v_type>
concept document_or_value = std::is_same_v<simdjson::ondemand::value, std::remove_cvref_t<v_type>> || std::is_same_v<simdjson::ondemand::document, std::remove_cvref_t<v_type>> ||
	std::is_same_v<simdjson::simdjson_result<simdjson::ondemand::document>, std::remove_cvref_t<v_type>>;

template<document_or_value simdjson_type, typename v_type> inline void get_value(simdjson_type val_new, v_type&);

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<decltype(std::vector<bool>{}[0]), v_type>)
JSONIFIER_INLINE void get_value(simdjson_type doc, v_type& msg) {
	msg = doc.get_bool();
}

template<document_or_value simdjson_type> JSONIFIER_INLINE void get_value(simdjson_type val_new, std::nullptr_t&) {
	val_new.is_null();
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<v_type, std::string> || std::is_same_v<v_type, std::string_view>)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_string().value());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<v_type, bool> || std::is_same_v<decltype(std::vector<bool>{}[0]), std::remove_cvref_t<v_type>>)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_bool());
}

template<document_or_value simdjson_type> JSONIFIER_INLINE void get_value(simdjson_type val_new, bool& data_new) {
	data_new = static_cast<bool>(val_new.get_bool());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::unsigned_integral<v_type> && sizeof(v_type) == 4)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_uint32());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::unsigned_integral<v_type> && sizeof(v_type) == 8)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_uint64());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::signed_integral<v_type> && sizeof(v_type) == 4)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_int32());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::signed_integral<v_type> && sizeof(v_type) == 8)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_int64());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::floating_point<v_type>)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_double());
}

template<document_or_value simdjson_type, typename t> JSONIFIER_INLINE void get_value(simdjson_type val_new, std::optional<t>& data_new) {
	if (val_new.is_null()) {
		data_new.reset();
		return;
	}
	get_value(val_new, data_new.emplace());
}

JSONIFIER_INLINE simdjson::ondemand::object get_object(simdjson::ondemand::value val_new) {
	return val_new.get_object();
}

JSONIFIER_INLINE simdjson::ondemand::array get_array(simdjson::ondemand::value val_new) {
	return val_new.get_array();
}

template<document_or_value simdjson_type, typename v_type> inline void get_value(simdjson_type val_new, std::vector<v_type>& data_new) {
	simdjson::ondemand::array array{ get_array(val_new) };
	auto begin = array.begin();
	auto end   = array.end();
	for (; begin != end; ++begin) {
		get_value(begin.value().operator*().value(), data_new.emplace_back());
	}
}

template<document_or_value simdjson_type, typename k_type, typename v_type> inline void get_value(simdjson_type val_new, std::unordered_map<k_type, v_type>& data_new) {
	simdjson::ondemand::object object{ get_object(val_new) };
	for (auto field: object) {
		std::string_view unescaped{ field.unescaped_key().value() };
		k_type key;
		if constexpr (std::is_same_v<k_type, std::string_view>) {
			key = unescaped;
		} else {
			key = k_type(unescaped.data(), unescaped.size());
		}
		simdjson::ondemand::value child{ field.value().value() };
		auto [it, inserted] = data_new.try_emplace(std::move(key));
		get_value(child, it->second);
	}
}

template<typename v_type> inline void get_field(simdjson::ondemand::object& obj, const char* key, v_type& data_new) {
	simdjson::ondemand::value val;
	if (auto result = obj.find_field(key).get(val); !result) {
		get_value(val, data_new);
	}
	return;
}

template<typename v_type> inline void get_field_unordered(simdjson::ondemand::object& obj, const char* key, v_type& data_new) {
	simdjson::ondemand::value val;
	if (auto result = obj.find_field_unordered(key).get(val); !result) {
		get_value(val, data_new);
	}
	return;
}

template<document_or_value simdjson_type, typename value_type> inline void get_value(simdjson_type val_new, value_type& data_new) {
	get_value(val_new.get_value(), data_new);
}
