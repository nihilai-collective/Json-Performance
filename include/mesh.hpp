/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/mesh.hpp
 */

#pragma once

#include <common.hpp>

struct batch {
	std::vector<int64_t> indexRange;
	std::vector<int64_t> vertexRange;
	std::vector<int64_t> usedBones;
};

struct morph_targets {};

struct mesh_message {
	std::vector<batch> batches;
	morph_targets morphTargets;
	std::vector<double> positions;
	std::vector<double> tex0;
	std::vector<int64_t> colors;
	std::vector<std::vector<int64_t>> influences;
	std::vector<double> normals;
	std::vector<int64_t> indices;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, batch& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"indexRange", "vertexRange", "usedBones">(obj, data_new.indexRange, data_new.vertexRange, data_new.usedBones);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, morph_targets&) {
	get_object(val_new);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, mesh_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"batches", "morphTargets", "positions", "tex0", "colors", "influences", "normals", "indices">(obj, data_new.batches, data_new.morphTargets, data_new.positions,
		data_new.tex0, data_new.colors, data_new.influences, data_new.normals, data_new.indices);
}

template<> struct glz::meta<batch> {
	using value_type			= batch;
	static constexpr auto value = object(&value_type::indexRange, &value_type::vertexRange, &value_type::usedBones);
};

template<> struct glz::meta<morph_targets> {
	using value_type			= morph_targets;
	static constexpr auto value = object();
};

template<> struct glz::meta<mesh_message> {
	using value_type			= mesh_message;
	static constexpr auto value = object(&value_type::batches, &value_type::morphTargets, &value_type::positions, &value_type::tex0, &value_type::colors, &value_type::influences,
		&value_type::normals, &value_type::indices);
};

template<> struct jsonifier::core<batch> {
	using value_type				 = batch;
	static constexpr auto parseValue = createValue<&value_type::indexRange, &value_type::vertexRange, &value_type::usedBones>();
};

template<> struct jsonifier::core<morph_targets> {
	using value_type				 = morph_targets;
	static constexpr auto parseValue = createValue();
};

template<> struct jsonifier::core<mesh_message> {
	using value_type				 = mesh_message;
	static constexpr auto parseValue = createValue<&value_type::batches, &value_type::morphTargets, &value_type::positions, &value_type::tex0, &value_type::colors,
		&value_type::influences, &value_type::normals, &value_type::indices>();
};