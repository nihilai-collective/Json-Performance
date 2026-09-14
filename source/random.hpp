// MIT License @ /License.md
// Copyright (c) 2026 Nihilai Collective Corp
// https://github.com/nihilai-collective/json-performance
// source/random.hpp

/// Sep 17, 2024
#pragma once

#include "common.hpp"

struct friend_element {
	int64_t id;
	std::string name;
	std::string phone;
};

struct result_data {
	int64_t id;
	std::string avatar;
	int64_t age;
	bool admin;
	std::string name;
	std::string company;
	std::string phone;
	std::string email;
	std::string birthDate;
	std::vector<friend_element> friends;
	std::string field;
};

struct random_message {
	int64_t id;
	std::string jsonrpc;
	int64_t total;
	std::vector<result_data> result;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, friend_element& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
	get_field(obj, "phone", data_new.phone);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, result_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "avatar", data_new.avatar);
	get_field(obj, "age", data_new.age);
	get_field(obj, "admin", data_new.admin);
	get_field(obj, "name", data_new.name);
	get_field(obj, "company", data_new.company);
	get_field(obj, "phone", data_new.phone);
	get_field(obj, "email", data_new.email);
	get_field(obj, "birthDate", data_new.birthDate);
	get_field(obj, "friends", data_new.friends);
	get_field(obj, "field", data_new.field);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, random_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "jsonrpc", data_new.jsonrpc);
	get_field(obj, "total", data_new.total);
	get_field(obj, "result", data_new.result);
}

template<> struct jsonifier::core<friend_element> {
	using value_type				 = friend_element;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::name, &value_type::phone>();
};

template<> struct jsonifier::core<result_data> {
	using value_type				 = result_data;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::avatar, &value_type::age, &value_type::admin, &value_type::name, &value_type::company,
		&value_type::phone, &value_type::email, &value_type::birthDate, &value_type::friends, &value_type::field>();
};

template<> struct jsonifier::core<random_message> {
	using value_type				 = random_message;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::jsonrpc, &value_type::total, &value_type::result>();
};