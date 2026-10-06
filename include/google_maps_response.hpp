/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/google_maps_response.hpp
 */

#pragma once

#include <common.hpp>

struct distance_data {
	std::string text;
	int64_t value;
};

struct element {
	distance_data distance;
	distance_data duration;
	std::string status;
};

struct row {
	std::vector<element> elements;
};

struct google_maps_response_message {
	std::vector<std::string> destination_addresses;
	std::vector<std::string> origin_addresses;
	std::vector<row> rows;
	std::string status;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, distance_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "text", data_new.text);
	get_field(obj, "value", data_new.value);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, element& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "distance", data_new.distance);
	get_field(obj, "duration", data_new.duration);
	get_field(obj, "status", data_new.status);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, row& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "elements", data_new.elements);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_response_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "destination_addresses", data_new.destination_addresses);
	get_field(obj, "origin_addresses", data_new.origin_addresses);
	get_field(obj, "rows", data_new.rows);
	get_field(obj, "status", data_new.status);
}

template<> struct jsonifier::core<distance_data> {
	using value_type				 = distance_data;
	static constexpr auto parseValue = createValue<&value_type::text, &value_type::value>();
};

template<> struct jsonifier::core<element> {
	using value_type				 = element;
	static constexpr auto parseValue = createValue<&value_type::distance, &value_type::duration, &value_type::status>();
};

template<> struct jsonifier::core<row> {
	using value_type				 = row;
	static constexpr auto parseValue = createValue<&value_type::elements>();
};

template<> struct jsonifier::core<google_maps_response_message> {
	using value_type				 = google_maps_response_message;
	static constexpr auto parseValue = createValue<&value_type::destination_addresses, &value_type::origin_addresses, &value_type::rows, &value_type::status>();
};

struct distance_data_reverse {
	int64_t value;
	std::string text;
};

struct element_reverse {
	std::string status;
	distance_data_reverse duration;
	distance_data_reverse distance;
};

struct row_reverse {
	std::vector<element_reverse> elements;
};

struct google_maps_response_message_reverse {
	std::string status;
	std::vector<row_reverse> rows;
	std::vector<std::string> origin_addresses;
	std::vector<std::string> destination_addresses;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, distance_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "value", data_new.value);
	get_field_unordered(obj, "text", data_new.text);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, element_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "status", data_new.status);
	get_field_unordered(obj, "duration", data_new.duration);
	get_field_unordered(obj, "distance", data_new.distance);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, row_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "elements", data_new.elements);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_response_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "status", data_new.status);
	get_field_unordered(obj, "rows", data_new.rows);
	get_field_unordered(obj, "origin_addresses", data_new.origin_addresses);
	get_field_unordered(obj, "destination_addresses", data_new.destination_addresses);
}

template<> struct jsonifier::core<distance_data_reverse> {
	using value_type				 = distance_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::value, &value_type::text>();
};

template<> struct jsonifier::core<element_reverse> {
	using value_type				 = element_reverse;
	static constexpr auto parseValue = createValue<&value_type::status, &value_type::duration, &value_type::distance>();
};

template<> struct jsonifier::core<row_reverse> {
	using value_type				 = row_reverse;
	static constexpr auto parseValue = createValue<&value_type::elements>();
};

template<> struct jsonifier::core<google_maps_response_message_reverse> {
	using value_type				 = google_maps_response_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::status, &value_type::rows, &value_type::origin_addresses, &value_type::destination_addresses>();
};

struct google_maps_distance_sparse {
	int64_t value;
};

struct google_maps_element_sparse {
	google_maps_distance_sparse distance;
	std::string status;
};

struct google_maps_row_sparse {
	std::vector<google_maps_element_sparse> elements;
};

struct google_maps_response_sparse_message {
	std::vector<google_maps_row_sparse> rows;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_distance_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "value", data_new.value);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_element_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "distance", data_new.distance);
	get_field(obj, "status", data_new.status);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_row_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "elements", data_new.elements);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_response_sparse_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "rows", data_new.rows);
}

template<> struct jsonifier::core<google_maps_distance_sparse> {
	using value_type				 = google_maps_distance_sparse;
	static constexpr auto parseValue = createValue<&value_type::value>();
};

template<> struct jsonifier::core<google_maps_element_sparse> {
	using value_type				 = google_maps_element_sparse;
	static constexpr auto parseValue = createValue<&value_type::distance, &value_type::status>();
};

template<> struct jsonifier::core<google_maps_row_sparse> {
	using value_type				 = google_maps_row_sparse;
	static constexpr auto parseValue = createValue<&value_type::elements>();
};

template<> struct jsonifier::core<google_maps_response_sparse_message> {
	using value_type				 = google_maps_response_sparse_message;
	static constexpr auto parseValue = createValue<&value_type::rows>();
};

struct google_maps_element_sparse_reverse {
	std::string status;
	google_maps_distance_sparse distance;
};

struct google_maps_row_sparse_reverse {
	std::vector<google_maps_element_sparse_reverse> elements;
};

struct google_maps_response_sparse_message_reverse {
	std::vector<google_maps_row_sparse_reverse> rows;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_element_sparse_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "status", data_new.status);
	get_field_unordered(obj, "distance", data_new.distance);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_row_sparse_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "elements", data_new.elements);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, google_maps_response_sparse_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "rows", data_new.rows);
}

template<> struct jsonifier::core<google_maps_element_sparse_reverse> {
	using value_type				 = google_maps_element_sparse_reverse;
	static constexpr auto parseValue = createValue<&value_type::status, &value_type::distance>();
};

template<> struct jsonifier::core<google_maps_row_sparse_reverse> {
	using value_type				 = google_maps_row_sparse_reverse;
	static constexpr auto parseValue = createValue<&value_type::elements>();
};

template<> struct jsonifier::core<google_maps_response_sparse_message_reverse> {
	using value_type				 = google_maps_response_sparse_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::rows>();
};
