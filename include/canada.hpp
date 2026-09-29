/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/canada.hpp
 */

#pragma once

#include <common.hpp>

struct geometry_data {
	std::string type;
	std::vector<std::vector<std::vector<double>>> coordinates;
};

struct properties_data {
	std::string name;
};

struct feature {
	std::string type;
	properties_data properties;
	geometry_data geometry;
};

struct canada_message {
	std::string type;
	std::vector<feature> features;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, geometry_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "coordinates", data_new.coordinates);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, properties_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, feature& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "properties", data_new.properties);
	get_field(obj, "geometry", data_new.geometry);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "features", data_new.features);
}

template<> struct jsonifier::core<geometry_data> {
	using value_type				 = geometry_data;
	static constexpr auto parseValue = createValue<&value_type::type, &value_type::coordinates>();
};

template<> struct jsonifier::core<properties_data> {
	using value_type				 = properties_data;
	static constexpr auto parseValue = createValue<&value_type::name>();
};

template<> struct jsonifier::core<feature> {
	using value_type				 = feature;
	static constexpr auto parseValue = createValue<&value_type::type, &value_type::properties, &value_type::geometry>();
};

template<> struct jsonifier::core<canada_message> {
	using value_type				 = canada_message;
	static constexpr auto parseValue = createValue<&value_type::type, &value_type::features>();
};

struct geometry_data_reverse {
	std::vector<std::vector<std::vector<double>>> coordinates;
	std::string type;
};

struct properties_data_reverse {
	std::string name;
};

struct feature_reverse {
	geometry_data_reverse geometry;
	properties_data_reverse properties;
	std::string type;
};

struct canada_message_reverse {
	std::vector<feature_reverse> features;
	std::string type;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, geometry_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "coordinates", data_new.coordinates);
	get_field_unordered(obj, "type", data_new.type);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, properties_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, feature_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "geometry", data_new.geometry);
	get_field_unordered(obj, "properties", data_new.properties);
	get_field_unordered(obj, "type", data_new.type);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "features", data_new.features);
	get_field_unordered(obj, "type", data_new.type);
}

template<> struct jsonifier::core<geometry_data_reverse> {
	using value_type				 = geometry_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::coordinates, &value_type::type>();
};

template<> struct jsonifier::core<properties_data_reverse> {
	using value_type				 = properties_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::name>();
};

template<> struct jsonifier::core<feature_reverse> {
	using value_type				 = feature_reverse;
	static constexpr auto parseValue = createValue<&value_type::geometry, &value_type::properties, &value_type::type>();
};

template<> struct jsonifier::core<canada_message_reverse> {
	using value_type				 = canada_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::features, &value_type::type>();
};

struct canada_properties_sparse {
	std::string name;
};

struct canada_geometry_sparse {
	std::string type;
};

struct canada_feature_sparse {
	canada_properties_sparse properties;
	canada_geometry_sparse geometry;
};

struct canada_sparse_message {
	std::vector<canada_feature_sparse> features;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_properties_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_geometry_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_feature_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "properties", data_new.properties);
	get_field(obj, "geometry", data_new.geometry);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_sparse_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "features", data_new.features);
}

template<> struct jsonifier::core<canada_properties_sparse> {
	using value_type				 = canada_properties_sparse;
	static constexpr auto parseValue = createValue<&value_type::name>();
};

template<> struct jsonifier::core<canada_geometry_sparse> {
	using value_type				 = canada_geometry_sparse;
	static constexpr auto parseValue = createValue<&value_type::type>();
};

template<> struct jsonifier::core<canada_feature_sparse> {
	using value_type				 = canada_feature_sparse;
	static constexpr auto parseValue = createValue<&value_type::properties, &value_type::geometry>();
};

template<> struct jsonifier::core<canada_sparse_message> {
	using value_type				 = canada_sparse_message;
	static constexpr auto parseValue = createValue<&value_type::features>();
};

struct canada_feature_sparse_reverse {
	canada_geometry_sparse geometry;
	canada_properties_sparse properties;
};

struct canada_sparse_message_reverse {
	std::vector<canada_feature_sparse_reverse> features;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_feature_sparse_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "geometry", data_new.geometry);
	get_field_unordered(obj, "properties", data_new.properties);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_sparse_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "features", data_new.features);
}

template<> struct jsonifier::core<canada_feature_sparse_reverse> {
	using value_type				 = canada_feature_sparse_reverse;
	static constexpr auto parseValue = createValue<&value_type::geometry, &value_type::properties>();
};

template<> struct jsonifier::core<canada_sparse_message_reverse> {
	using value_type				 = canada_sparse_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::features>();
};
