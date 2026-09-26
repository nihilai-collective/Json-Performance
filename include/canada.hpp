/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/canada.hpp
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
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "coordinates", data_new.coordinates);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, properties_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, feature& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "properties", data_new.properties);
	get_field(obj, "geometry", data_new.geometry);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, canada_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "features", data_new.features);
}

template<> struct glz::meta<geometry_data> {
	using value_type			= geometry_data;
	static constexpr auto value = object(&value_type::type, &value_type::coordinates);
};

template<> struct glz::meta<properties_data> {
	using value_type			= properties_data;
	static constexpr auto value = object(&value_type::name);
};

template<> struct glz::meta<feature> {
	using value_type			= feature;
	static constexpr auto value = object(&value_type::type, &value_type::properties, &value_type::geometry);
};

template<> struct glz::meta<canada_message> {
	using value_type			= canada_message;
	static constexpr auto value = object(&value_type::type, &value_type::features);
};

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