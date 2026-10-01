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
	auto obj{ get_object(val_new) };
	get_field(obj, "indexRange", data_new.indexRange);
	get_field(obj, "vertexRange", data_new.vertexRange);
	get_field(obj, "usedBones", data_new.usedBones);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, morph_targets&) {
	get_object(val_new);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, mesh_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "batches", data_new.batches);
	get_field(obj, "morphTargets", data_new.morphTargets);
	get_field(obj, "positions", data_new.positions);
	get_field(obj, "tex0", data_new.tex0);
	get_field(obj, "colors", data_new.colors);
	get_field(obj, "influences", data_new.influences);
	get_field(obj, "normals", data_new.normals);
	get_field(obj, "indices", data_new.indices);
}

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

struct batch_reverse {
	std::vector<int64_t> usedBones;
	std::vector<int64_t> vertexRange;
	std::vector<int64_t> indexRange;
};

struct morph_targets_reverse {};

struct mesh_message_reverse {
	std::vector<int64_t> indices;
	std::vector<double> normals;
	std::vector<std::vector<int64_t>> influences;
	std::vector<int64_t> colors;
	std::vector<double> tex0;
	std::vector<double> positions;
	morph_targets_reverse morphTargets;
	std::vector<batch_reverse> batches;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, batch_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "usedBones", data_new.usedBones);
	get_field_unordered(obj, "vertexRange", data_new.vertexRange);
	get_field_unordered(obj, "indexRange", data_new.indexRange);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, morph_targets_reverse&) {
	get_object(val_new);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, mesh_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "indices", data_new.indices);
	get_field_unordered(obj, "normals", data_new.normals);
	get_field_unordered(obj, "influences", data_new.influences);
	get_field_unordered(obj, "colors", data_new.colors);
	get_field_unordered(obj, "tex0", data_new.tex0);
	get_field_unordered(obj, "positions", data_new.positions);
	get_field_unordered(obj, "morphTargets", data_new.morphTargets);
	get_field_unordered(obj, "batches", data_new.batches);
}

template<> struct jsonifier::core<batch_reverse> {
	using value_type				 = batch_reverse;
	static constexpr auto parseValue = createValue<&value_type::usedBones, &value_type::vertexRange, &value_type::indexRange>();
};

template<> struct jsonifier::core<morph_targets_reverse> {
	using value_type				 = morph_targets_reverse;
	static constexpr auto parseValue = createValue();
};

template<> struct jsonifier::core<mesh_message_reverse> {
	using value_type				 = mesh_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::indices, &value_type::normals, &value_type::influences, &value_type::colors, &value_type::tex0, &value_type::positions, &value_type::morphTargets, &value_type::batches>();
};

struct mesh_batch_sparse {
	std::vector<int64_t> indexRange;
	std::vector<int64_t> vertexRange;
};

struct mesh_sparse_message {
	std::vector<mesh_batch_sparse> batches;
	std::vector<int64_t> indices;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, mesh_batch_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "indexRange", data_new.indexRange);
	get_field(obj, "vertexRange", data_new.vertexRange);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, mesh_sparse_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "batches", data_new.batches);
	get_field(obj, "indices", data_new.indices);
}

template<> struct jsonifier::core<mesh_batch_sparse> {
	using value_type				 = mesh_batch_sparse;
	static constexpr auto parseValue = createValue<&value_type::indexRange, &value_type::vertexRange>();
};

template<> struct jsonifier::core<mesh_sparse_message> {
	using value_type				 = mesh_sparse_message;
	static constexpr auto parseValue = createValue<&value_type::batches, &value_type::indices>();
};

struct mesh_batch_sparse_reverse {
	std::vector<int64_t> vertexRange;
	std::vector<int64_t> indexRange;
};

struct mesh_sparse_message_reverse {
	std::vector<int64_t> indices;
	std::vector<mesh_batch_sparse_reverse> batches;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, mesh_batch_sparse_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "vertexRange", data_new.vertexRange);
	get_field_unordered(obj, "indexRange", data_new.indexRange);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, mesh_sparse_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "indices", data_new.indices);
	get_field_unordered(obj, "batches", data_new.batches);
}

template<> struct jsonifier::core<mesh_batch_sparse_reverse> {
	using value_type				 = mesh_batch_sparse_reverse;
	static constexpr auto parseValue = createValue<&value_type::vertexRange, &value_type::indexRange>();
};

template<> struct jsonifier::core<mesh_sparse_message_reverse> {
	using value_type				 = mesh_sparse_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::indices, &value_type::batches>();
};
