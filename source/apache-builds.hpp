// MIT License @ /License.md
// Copyright (c) 2026 Nihilai Collective Corp
// https://github.com/nihilai-collective/json-performance
// source/apache-builds.hpp

#pragma once

#include "common.hpp"

struct overall_load_data {};

struct job {
	std::string name;
	std::string url;
	std::string color;
};

struct view {
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
	std::vector<job> jobs;
	overall_load_data overallLoad;
	view primaryView;
	bool quietingDown;
	int64_t slaveAgentPort;
	overall_load_data unlabeledLoad;
	bool useCrumbs;
	bool useSecurity;
	std::vector<view> views;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, overall_load_data&) {
	get_object(val_new);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, job& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
	get_field(obj, "url", data_new.url);
	get_field(obj, "color", data_new.color);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, view& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
	get_field(obj, "url", data_new.url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, apache_builds_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
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

template<> struct jsonifier::core<job> {
	using value_type				 = job;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::url, &value_type::color>();
};

template<> struct jsonifier::core<view> {
	using value_type				 = view;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::url>();
};

template<> struct jsonifier::core<apache_builds_message> {
	using value_type				 = apache_builds_message;
	static constexpr auto parseValue = createValue<&value_type::assignedLabels, &value_type::mode, &value_type::nodeDescription, &value_type::nodeName, &value_type::numExecutors,
		&value_type::description, &value_type::jobs, &value_type::overallLoad, &value_type::primaryView, &value_type::quietingDown, &value_type::slaveAgentPort,
		&value_type::unlabeledLoad, &value_type::useCrumbs, &value_type::useSecurity, &value_type::views>();
};
