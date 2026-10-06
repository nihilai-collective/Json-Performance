/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/random.hpp
 */


#pragma once

#include <common.hpp>

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
	auto obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
	get_field(obj, "phone", data_new.phone);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, result_data& data_new) {
	auto obj{ get_object(val_new) };
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
	auto obj{ get_object(val_new) };
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

struct friend_element_reverse {
	std::string phone;
	std::string name;
	int64_t id;
};

struct result_data_reverse {
	std::string field;
	std::vector<friend_element_reverse> friends;
	std::string birthDate;
	std::string email;
	std::string phone;
	std::string company;
	std::string name;
	bool admin;
	int64_t age;
	std::string avatar;
	int64_t id;
};

struct random_message_reverse {
	std::vector<result_data_reverse> result;
	int64_t total;
	std::string jsonrpc;
	int64_t id;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, friend_element_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "phone", data_new.phone);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "id", data_new.id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, result_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "field", data_new.field);
	get_field_unordered(obj, "friends", data_new.friends);
	get_field_unordered(obj, "birthDate", data_new.birthDate);
	get_field_unordered(obj, "email", data_new.email);
	get_field_unordered(obj, "phone", data_new.phone);
	get_field_unordered(obj, "company", data_new.company);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "admin", data_new.admin);
	get_field_unordered(obj, "age", data_new.age);
	get_field_unordered(obj, "avatar", data_new.avatar);
	get_field_unordered(obj, "id", data_new.id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, random_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "result", data_new.result);
	get_field_unordered(obj, "total", data_new.total);
	get_field_unordered(obj, "jsonrpc", data_new.jsonrpc);
	get_field_unordered(obj, "id", data_new.id);
}

template<> struct jsonifier::core<friend_element_reverse> {
	using value_type				 = friend_element_reverse;
	static constexpr auto parseValue = createValue<&value_type::phone, &value_type::name, &value_type::id>();
};

template<> struct jsonifier::core<result_data_reverse> {
	using value_type				 = result_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::field, &value_type::friends, &value_type::birthDate, &value_type::email, &value_type::phone, &value_type::company, &value_type::name, &value_type::admin, &value_type::age, &value_type::avatar, &value_type::id>();
};

template<> struct jsonifier::core<random_message_reverse> {
	using value_type				 = random_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::result, &value_type::total, &value_type::jsonrpc, &value_type::id>();
};

struct random_friend_sparse {
	std::string name;
};

struct random_result_sparse {
	int64_t id;
	std::string name;
	std::vector<random_friend_sparse> friends;
};

struct random_sparse_message {
	int64_t total;
	std::vector<random_result_sparse> result;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, random_friend_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, random_result_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
	get_field(obj, "friends", data_new.friends);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, random_sparse_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "total", data_new.total);
	get_field(obj, "result", data_new.result);
}

template<> struct jsonifier::core<random_friend_sparse> {
	using value_type				 = random_friend_sparse;
	static constexpr auto parseValue = createValue<&value_type::name>();
};

template<> struct jsonifier::core<random_result_sparse> {
	using value_type				 = random_result_sparse;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::name, &value_type::friends>();
};

template<> struct jsonifier::core<random_sparse_message> {
	using value_type				 = random_sparse_message;
	static constexpr auto parseValue = createValue<&value_type::total, &value_type::result>();
};

struct random_result_sparse_reverse {
	std::vector<random_friend_sparse> friends;
	std::string name;
	int64_t id;
};

struct random_sparse_message_reverse {
	std::vector<random_result_sparse_reverse> result;
	int64_t total;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, random_result_sparse_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "friends", data_new.friends);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "id", data_new.id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, random_sparse_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "result", data_new.result);
	get_field_unordered(obj, "total", data_new.total);
}

template<> struct jsonifier::core<random_result_sparse_reverse> {
	using value_type				 = random_result_sparse_reverse;
	static constexpr auto parseValue = createValue<&value_type::friends, &value_type::name, &value_type::id>();
};

template<> struct jsonifier::core<random_sparse_message_reverse> {
	using value_type				 = random_sparse_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::result, &value_type::total>();
};
