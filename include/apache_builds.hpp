/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/apache_builds.hpp
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

template<tests::document_or_value simdjson_type> inline void get_value(simdjson_type val_new, overall_load_data&) {
	static_cast<void>(tests::get_object(val_new));
}

template<tests::document_or_value simdjson_type> inline void get_value(simdjson_type val_new, job_data& data_new) {
	simdjson::ondemand::object obj{ tests::get_object(val_new) };
	tests::get_fields<"name", "url", "color">(obj, data_new.name, data_new.url, data_new.color);
}

template<tests::document_or_value simdjson_type> inline void get_value(simdjson_type val_new, view_data& data_new) {
	simdjson::ondemand::object obj{ tests::get_object(val_new) };
	tests::get_fields<"name", "url">(obj, data_new.name, data_new.url);
}

template<tests::document_or_value simdjson_type> inline void get_value(simdjson_type val_new, apache_builds_message& data_new) {
	simdjson::ondemand::object obj{ tests::get_object(val_new) };
	tests::get_fields<"assignedLabels", "mode", "nodeDescription", "nodeName", "numExecutors", "description", "jobs", "overallLoad", "primaryView", "quietingDown", "slaveAgentPort",
		"unlabeledLoad", "useCrumbs", "useSecurity", "views">(obj, data_new.assignedLabels, data_new.mode, data_new.nodeDescription, data_new.nodeName, data_new.numExecutors,
		data_new.description, data_new.jobs, data_new.overallLoad, data_new.primaryView, data_new.quietingDown, data_new.slaveAgentPort, data_new.unlabeledLoad, data_new.useCrumbs,
		data_new.useSecurity, data_new.views);
}

template<> struct glz::meta<overall_load_data> {
	using value_type			= overall_load_data;
	static constexpr auto value = object();
};

template<> struct glz::meta<job_data> {
	using value_type			= job_data;
	static constexpr auto value = object("name", &value_type::name, "url", &value_type::url, "color", &value_type::color);
};

template<> struct glz::meta<view_data> {
	using value_type			= view_data;
	static constexpr auto value = object("name", &value_type::name, "url", &value_type::url);
};

template<> struct glz::meta<apache_builds_message> {
	using value_type			= apache_builds_message;
	static constexpr auto value = object("assignedLabels", &value_type::assignedLabels, "mode", &value_type::mode, "nodeDescription", &value_type::nodeDescription, "nodeName",
		&value_type::nodeName, "numExecutors", &value_type::numExecutors, "description", &value_type::description, "jobs", &value_type::jobs, "overallLoad",
		&value_type::overallLoad, "primaryView", &value_type::primaryView, "quietingDown", &value_type::quietingDown, "slaveAgentPort", &value_type::slaveAgentPort,
		"unlabeledLoad", &value_type::unlabeledLoad, "useCrumbs", &value_type::useCrumbs, "useSecurity", &value_type::useSecurity, "views", &value_type::views);
};

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
