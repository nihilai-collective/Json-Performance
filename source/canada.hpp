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
/// https://github.com/RealTimeChris/Json-Performance
#pragma once

#include "common.hpp"

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