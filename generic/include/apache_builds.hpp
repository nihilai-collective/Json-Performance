/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * generic/include/apache_builds.hpp
 */

#pragma once

#include <common.hpp>

struct overall_load_data {};

struct job_data {
	std::string name;
	std::string url;
	std::string color;
};

struct view_data {
	std::string name;
	std::string url;
};

struct apache_builds_message {
	std::vector<overall_load_data> assignedLabels;
	std::string mode;
	std::string nodeDescription;
	std::string nodeName;
	int64_t numExecutors;
	std::string description;
	std::vector<job_data> jobs;
	overall_load_data overallLoad;
	view_data primaryView;
	bool quietingDown;
	int64_t slaveAgentPort;
	overall_load_data unlabeledLoad;
	bool useCrumbs;
	bool useSecurity;
	std::vector<view_data> views;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, overall_load_data&) {
	get_object(val_new);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, job_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
	get_field(obj, "url", data_new.url);
	get_field(obj, "color", data_new.color);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, view_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
	get_field(obj, "url", data_new.url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, apache_builds_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "assignedLabels", data_new.assignedLabels);
	get_field(obj, "mode", data_new.mode);
	get_field(obj, "nodeDescription", data_new.nodeDescription);
	get_field(obj, "nodeName", data_new.nodeName);
	get_field(obj, "numExecutors", data_new.numExecutors);
	get_field(obj, "description", data_new.description);
	get_field(obj, "jobs", data_new.jobs);
	get_field(obj, "overallLoad", data_new.overallLoad);
	get_field(obj, "primaryView", data_new.primaryView);
	get_field(obj, "quietingDown", data_new.quietingDown);
	get_field(obj, "slaveAgentPort", data_new.slaveAgentPort);
	get_field(obj, "unlabeledLoad", data_new.unlabeledLoad);
	get_field(obj, "useCrumbs", data_new.useCrumbs);
	get_field(obj, "useSecurity", data_new.useSecurity);
	get_field(obj, "views", data_new.views);
}

template<> struct jsonifier::core<overall_load_data> {
	using value_type				 = overall_load_data;
	static constexpr auto parseValue = createValue();
};

template<> struct jsonifier::core<job_data> {
	using value_type				 = job_data;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::url, &value_type::color>();
};

template<> struct jsonifier::core<view_data> {
	using value_type				 = view_data;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::url>();
};

template<> struct jsonifier::core<apache_builds_message> {
	using value_type				 = apache_builds_message;
	static constexpr auto parseValue = createValue<&value_type::assignedLabels, &value_type::mode, &value_type::nodeDescription, &value_type::nodeName, &value_type::numExecutors,
		&value_type::description, &value_type::jobs, &value_type::overallLoad, &value_type::primaryView, &value_type::quietingDown, &value_type::slaveAgentPort,
		&value_type::unlabeledLoad, &value_type::useCrumbs, &value_type::useSecurity, &value_type::views>();
};

struct overall_load_data_reverse {};

struct job_data_reverse {
	std::string color;
	std::string url;
	std::string name;
};

struct view_data_reverse {
	std::string url;
	std::string name;
};

struct apache_builds_message_reverse {
	std::vector<view_data_reverse> views;
	bool useSecurity;
	bool useCrumbs;
	overall_load_data_reverse unlabeledLoad;
	int64_t slaveAgentPort;
	bool quietingDown;
	view_data_reverse primaryView;
	overall_load_data_reverse overallLoad;
	std::vector<job_data_reverse> jobs;
	std::string description;
	int64_t numExecutors;
	std::string nodeName;
	std::string nodeDescription;
	std::string mode;
	std::vector<overall_load_data_reverse> assignedLabels;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, overall_load_data_reverse&) {
	get_object(val_new);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, job_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "color", data_new.color);
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, view_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, apache_builds_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "views", data_new.views);
	get_field_unordered(obj, "useSecurity", data_new.useSecurity);
	get_field_unordered(obj, "useCrumbs", data_new.useCrumbs);
	get_field_unordered(obj, "unlabeledLoad", data_new.unlabeledLoad);
	get_field_unordered(obj, "slaveAgentPort", data_new.slaveAgentPort);
	get_field_unordered(obj, "quietingDown", data_new.quietingDown);
	get_field_unordered(obj, "primaryView", data_new.primaryView);
	get_field_unordered(obj, "overallLoad", data_new.overallLoad);
	get_field_unordered(obj, "jobs", data_new.jobs);
	get_field_unordered(obj, "description", data_new.description);
	get_field_unordered(obj, "numExecutors", data_new.numExecutors);
	get_field_unordered(obj, "nodeName", data_new.nodeName);
	get_field_unordered(obj, "nodeDescription", data_new.nodeDescription);
	get_field_unordered(obj, "mode", data_new.mode);
	get_field_unordered(obj, "assignedLabels", data_new.assignedLabels);
}

template<> struct jsonifier::core<overall_load_data_reverse> {
	using value_type				 = overall_load_data_reverse;
	static constexpr auto parseValue = createValue();
};

template<> struct jsonifier::core<job_data_reverse> {
	using value_type				 = job_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::color, &value_type::url, &value_type::name>();
};

template<> struct jsonifier::core<view_data_reverse> {
	using value_type				 = view_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::name>();
};

template<> struct jsonifier::core<apache_builds_message_reverse> {
	using value_type				 = apache_builds_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::views, &value_type::useSecurity, &value_type::useCrumbs, &value_type::unlabeledLoad, &value_type::slaveAgentPort,
		&value_type::quietingDown, &value_type::primaryView, &value_type::overallLoad, &value_type::jobs, &value_type::description, &value_type::numExecutors,
		&value_type::nodeName, &value_type::nodeDescription, &value_type::mode, &value_type::assignedLabels>();
};

struct job_data_sparse {
	std::string name;
	std::string color;
};

struct view_data_sparse {
	std::string name;
};

struct apache_builds_sparse_message {
	std::vector<job_data_sparse> jobs;
	std::vector<view_data_sparse> views;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, job_data_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
	get_field(obj, "color", data_new.color);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, view_data_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, apache_builds_sparse_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "jobs", data_new.jobs);
	get_field(obj, "views", data_new.views);
}

template<> struct jsonifier::core<job_data_sparse> {
	using value_type				 = job_data_sparse;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::color>();
};

template<> struct jsonifier::core<view_data_sparse> {
	using value_type				 = view_data_sparse;
	static constexpr auto parseValue = createValue<&value_type::name>();
};

template<> struct jsonifier::core<apache_builds_sparse_message> {
	using value_type				 = apache_builds_sparse_message;
	static constexpr auto parseValue = createValue<&value_type::jobs, &value_type::views>();
};

struct job_data_sparse_reverse {
	std::string color;
	std::string name;
};

struct apache_builds_sparse_message_reverse {
	std::vector<view_data_sparse> views;
	std::vector<job_data_sparse_reverse> jobs;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, job_data_sparse_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "color", data_new.color);
	get_field_unordered(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, apache_builds_sparse_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "views", data_new.views);
	get_field_unordered(obj, "jobs", data_new.jobs);
}

template<> struct jsonifier::core<job_data_sparse_reverse> {
	using value_type				 = job_data_sparse_reverse;
	static constexpr auto parseValue = createValue<&value_type::color, &value_type::name>();
};

template<> struct jsonifier::core<apache_builds_sparse_message_reverse> {
	using value_type				 = apache_builds_sparse_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::views, &value_type::jobs>();
};
