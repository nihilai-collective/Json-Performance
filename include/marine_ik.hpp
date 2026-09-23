/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/marine_ik.hpp
 */

#pragma once

#include <common.hpp>

struct marine_ik_animation {
	std::vector<std::optional<std::string>> tracks;
	int64_t fps;
	std::string name;
};

struct key {
	std::vector<double> pos;
	double time;
	std::vector<double> scl;
	std::vector<double> rot;
};

struct hierarchy_data {
	int64_t parent;
	std::vector<key> keys;
};

struct data_animation {
	std::vector<hierarchy_data> hierarchy;
	double length;
	int64_t fps;
	std::string name;
};

struct bone {
	int64_t parent;
	std::vector<double> pos;
	std::vector<double> rotq;
	std::vector<int64_t> scl;
	std::string name;
};

struct data_metadata {
	int64_t uvs;
	int64_t version;
	int64_t faces;
	std::string generator;
	int64_t normals;
	int64_t bones;
	int64_t vertices;
};

struct data_data {
	std::vector<std::vector<double>> uvs;
	std::vector<data_animation> animations;
	std::vector<double> vertices;
	data_metadata metadata;
	std::string name;
	std::vector<double> skinWeights;
	std::vector<int64_t> skinIndices;
	int64_t influencesPerVertex;
	std::vector<double> normals;
	std::vector<bone> bones;
	std::vector<int64_t> faces;
};

struct marine_ik_geometry_data {
	std::string type;
	std::string uuid;
	data_data data;
};

struct image_data {
	std::string url;
	std::string uuid;
	std::string name;
};

struct material_data {
	int64_t vertexColors;
	std::string name;
	std::string type;
	std::string uuid;
	std::string blending;
	std::string map;
	bool transparent;
	bool depthTest;
	int64_t color;
	int64_t shininess;
	int64_t emissive;
	bool depthWrite;
	int64_t specular;
};

struct marine_ik_metadata {
	std::string sourceFile;
	std::string generator;
	std::string type;
	double version;
};

struct child {
	std::string name;
	std::string uuid;
	std::vector<int64_t> matrix;
	bool visible;
	std::string type;
	std::string material;
	bool castShadow;
	bool receiveShadow;
	std::string geometry;
};

struct object_data {
	std::vector<child> children;
	std::string type;
	std::vector<int64_t> matrix;
	std::string uuid;
};

struct texture_data {
	std::vector<int64_t> repeat;
	std::vector<int64_t> wrap;
	int64_t anisotropy;
	std::string image;
	std::string name;
	int64_t mapping;
	int64_t minFilter;
	std::string uuid;
	int64_t magFilter;
};

struct marine_ik {
	std::vector<image_data> images;
	std::vector<marine_ik_geometry_data> geometries;
	std::vector<texture_data> textures;
	marine_ik_metadata metadata;
	std::vector<material_data> materials;
	object_data object;
	std::vector<marine_ik_animation> animations;
};

struct marine_ik_animation_reverse {
	std::string name;
	int64_t fps;
	std::vector<std::optional<std::string>> tracks;
};

struct key_reverse {
	std::vector<double> rot;
	std::vector<double> scl;
	double time;
	std::vector<double> pos;
};

struct hierarchy_data_reverse {
	std::vector<key_reverse> keys;
	int64_t parent;
};

struct data_animation_reverse {
	std::string name;
	int64_t fps;
	double length;
	std::vector<hierarchy_data_reverse> hierarchy;
};

struct bone_reverse {
	std::string name;
	std::vector<int64_t> scl;
	std::vector<double> rotq;
	std::vector<double> pos;
	int64_t parent;
};

struct data_metadata_reverse {
	int64_t vertices;
	int64_t bones;
	int64_t normals;
	std::string generator;
	int64_t faces;
	int64_t version;
	int64_t uvs;
};

struct data_data_reverse {
	std::vector<int64_t> faces;
	std::vector<bone_reverse> bones;
	std::vector<double> normals;
	int64_t influencesPerVertex;
	std::vector<int64_t> skinIndices;
	std::vector<double> skinWeights;
	std::string name;
	data_metadata_reverse metadata;
	std::vector<double> vertices;
	std::vector<data_animation_reverse> animations;
	std::vector<std::vector<double>> uvs;
};

struct marine_ik_geometry_data_reverse {
	data_data_reverse data;
	std::string uuid;
	std::string type;
};

struct image_data_reverse {
	std::string name;
	std::string uuid;
	std::string url;
};

struct material_data_reverse {
	int64_t specular;
	bool depthWrite;
	int64_t emissive;
	int64_t shininess;
	int64_t color;
	bool depthTest;
	bool transparent;
	std::string map;
	std::string blending;
	std::string uuid;
	std::string type;
	std::string name;
	int64_t vertexColors;
};

struct marine_ik_metadata_reverse {
	double version;
	std::string type;
	std::string generator;
	std::string sourceFile;
};

struct child_reverse {
	std::string geometry;
	bool receiveShadow;
	bool castShadow;
	std::string material;
	std::string type;
	bool visible;
	std::vector<int64_t> matrix;
	std::string uuid;
	std::string name;
};

struct object_data_reverse {
	std::string uuid;
	std::vector<int64_t> matrix;
	std::string type;
	std::vector<child_reverse> children;
};

struct texture_data_reverse {
	int64_t magFilter;
	std::string uuid;
	int64_t minFilter;
	int64_t mapping;
	std::string name;
	std::string image;
	int64_t anisotropy;
	std::vector<int64_t> wrap;
	std::vector<int64_t> repeat;
};

struct marine_ik_reverse {
	std::vector<marine_ik_animation_reverse> animations;
	object_data_reverse object;
	std::vector<material_data_reverse> materials;
	marine_ik_metadata_reverse metadata;
	std::vector<texture_data_reverse> textures;
	std::vector<marine_ik_geometry_data_reverse> geometries;
	std::vector<image_data_reverse> images;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, marine_ik_animation& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "tracks", data_new.tracks);
	get_field(obj, "fps", data_new.fps);
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, key& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "pos", data_new.pos);
	get_field(obj, "time", data_new.time);
	get_field(obj, "scl", data_new.scl);
	get_field(obj, "rot", data_new.rot);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, hierarchy_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "parent", data_new.parent);
	get_field(obj, "keys", data_new.keys);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, data_animation& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "hierarchy", data_new.hierarchy);
	get_field(obj, "length", data_new.length);
	get_field(obj, "fps", data_new.fps);
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, bone& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "parent", data_new.parent);
	get_field(obj, "pos", data_new.pos);
	get_field(obj, "rotq", data_new.rotq);
	get_field(obj, "scl", data_new.scl);
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, data_metadata& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "uvs", data_new.uvs);
	get_field(obj, "version", data_new.version);
	get_field(obj, "faces", data_new.faces);
	get_field(obj, "generator", data_new.generator);
	get_field(obj, "normals", data_new.normals);
	get_field(obj, "bones", data_new.bones);
	get_field(obj, "vertices", data_new.vertices);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, data_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "uvs", data_new.uvs);
	get_field(obj, "animations", data_new.animations);
	get_field(obj, "vertices", data_new.vertices);
	get_field(obj, "metadata", data_new.metadata);
	get_field(obj, "name", data_new.name);
	get_field(obj, "skinWeights", data_new.skinWeights);
	get_field(obj, "skinIndices", data_new.skinIndices);
	get_field(obj, "influencesPerVertex", data_new.influencesPerVertex);
	get_field(obj, "normals", data_new.normals);
	get_field(obj, "bones", data_new.bones);
	get_field(obj, "faces", data_new.faces);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, marine_ik_geometry_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "uuid", data_new.uuid);
	get_field(obj, "data", data_new.data);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, image_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "url", data_new.url);
	get_field(obj, "uuid", data_new.uuid);
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, material_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "vertexColors", data_new.vertexColors);
	get_field(obj, "name", data_new.name);
	get_field(obj, "type", data_new.type);
	get_field(obj, "uuid", data_new.uuid);
	get_field(obj, "blending", data_new.blending);
	get_field(obj, "map", data_new.map);
	get_field(obj, "transparent", data_new.transparent);
	get_field(obj, "depthTest", data_new.depthTest);
	get_field(obj, "color", data_new.color);
	get_field(obj, "shininess", data_new.shininess);
	get_field(obj, "emissive", data_new.emissive);
	get_field(obj, "depthWrite", data_new.depthWrite);
	get_field(obj, "specular", data_new.specular);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, marine_ik_metadata& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "sourceFile", data_new.sourceFile);
	get_field(obj, "generator", data_new.generator);
	get_field(obj, "type", data_new.type);
	get_field(obj, "version", data_new.version);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, child& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
	get_field(obj, "uuid", data_new.uuid);
	get_field(obj, "matrix", data_new.matrix);
	get_field(obj, "visible", data_new.visible);
	get_field(obj, "type", data_new.type);
	get_field(obj, "material", data_new.material);
	get_field(obj, "castShadow", data_new.castShadow);
	get_field(obj, "receiveShadow", data_new.receiveShadow);
	get_field(obj, "geometry", data_new.geometry);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, object_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "children", data_new.children);
	get_field(obj, "type", data_new.type);
	get_field(obj, "matrix", data_new.matrix);
	get_field(obj, "uuid", data_new.uuid);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, texture_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "repeat", data_new.repeat);
	get_field(obj, "wrap", data_new.wrap);
	get_field(obj, "anisotropy", data_new.anisotropy);
	get_field(obj, "image", data_new.image);
	get_field(obj, "name", data_new.name);
	get_field(obj, "mapping", data_new.mapping);
	get_field(obj, "minFilter", data_new.minFilter);
	get_field(obj, "uuid", data_new.uuid);
	get_field(obj, "magFilter", data_new.magFilter);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, marine_ik& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "images", data_new.images);
	get_field(obj, "geometries", data_new.geometries);
	get_field(obj, "textures", data_new.textures);
	get_field(obj, "metadata", data_new.metadata);
	get_field(obj, "materials", data_new.materials);
	get_field(obj, "object", data_new.object);
	get_field(obj, "animations", data_new.animations);
}

template<> struct glz::meta<marine_ik_animation> {
	using value_type			= marine_ik_animation;
	static constexpr auto value = object(&value_type::tracks, &value_type::fps, &value_type::name);
};

template<> struct glz::meta<key> {
	using value_type			= key;
	static constexpr auto value = object(&value_type::pos, &value_type::time, &value_type::scl, &value_type::rot);
};

template<> struct glz::meta<hierarchy_data> {
	using value_type			= hierarchy_data;
	static constexpr auto value = object(&value_type::parent, &value_type::keys);
};

template<> struct glz::meta<data_animation> {
	using value_type			= data_animation;
	static constexpr auto value = object(&value_type::hierarchy, &value_type::length, &value_type::fps, &value_type::name);
};

template<> struct glz::meta<bone> {
	using value_type			= bone;
	static constexpr auto value = object(&value_type::parent, &value_type::pos, &value_type::rotq, &value_type::scl, &value_type::name);
};

template<> struct glz::meta<data_metadata> {
	using value_type = data_metadata;
	static constexpr auto value =
		object(&value_type::uvs, &value_type::version, &value_type::faces, &value_type::generator, &value_type::normals, &value_type::bones, &value_type::vertices);
};

template<> struct glz::meta<data_data> {
	using value_type			= data_data;
	static constexpr auto value = object(&value_type::uvs, &value_type::animations, &value_type::vertices, &value_type::metadata, &value_type::name, &value_type::skinWeights,
		&value_type::skinIndices, &value_type::influencesPerVertex, &value_type::normals, &value_type::bones, &value_type::faces);
};

template<> struct glz::meta<marine_ik_geometry_data> {
	using value_type			= marine_ik_geometry_data;
	static constexpr auto value = object(&value_type::type, &value_type::uuid, &value_type::data);
};

template<> struct glz::meta<image_data> {
	using value_type			= image_data;
	static constexpr auto value = object(&value_type::url, &value_type::uuid, &value_type::name);
};

template<> struct glz::meta<material_data> {
	using value_type			= material_data;
	static constexpr auto value = object(&value_type::vertexColors, &value_type::name, &value_type::type, &value_type::uuid, &value_type::blending, &value_type::map,
		&value_type::transparent, &value_type::depthTest, &value_type::color, &value_type::shininess, &value_type::emissive, &value_type::depthWrite, &value_type::specular);
};

template<> struct glz::meta<marine_ik_metadata> {
	using value_type			= marine_ik_metadata;
	static constexpr auto value = object(&value_type::sourceFile, &value_type::generator, &value_type::type, &value_type::version);
};

template<> struct glz::meta<child> {
	using value_type			= child;
	static constexpr auto value = object(&value_type::name, &value_type::uuid, &value_type::matrix, &value_type::visible, &value_type::type, &value_type::material,
		&value_type::castShadow, &value_type::receiveShadow, &value_type::geometry);
};

template<> struct glz::meta<object_data> {
	using value_type			= object_data;
	static constexpr auto value = object(&value_type::children, &value_type::type, &value_type::matrix, &value_type::uuid);
};

template<> struct glz::meta<texture_data> {
	using value_type			= texture_data;
	static constexpr auto value = object(&value_type::repeat, &value_type::wrap, &value_type::anisotropy, &value_type::image, &value_type::name, &value_type::mapping,
		&value_type::minFilter, &value_type::uuid, &value_type::magFilter);
};

template<> struct glz::meta<marine_ik> {
	using value_type = marine_ik;
	static constexpr auto value =
		object(&value_type::images, &value_type::geometries, &value_type::textures, &value_type::metadata, &value_type::materials, &value_type::object, &value_type::animations);
};

template<> struct jsonifier::core<marine_ik_animation> {
	using value_type				 = marine_ik_animation;
	static constexpr auto parseValue = createValue<&value_type::tracks, &value_type::fps, &value_type::name>();
};

template<> struct jsonifier::core<key> {
	using value_type				 = key;
	static constexpr auto parseValue = createValue<&value_type::pos, &value_type::time, &value_type::scl, &value_type::rot>();
};

template<> struct jsonifier::core<hierarchy_data> {
	using value_type				 = hierarchy_data;
	static constexpr auto parseValue = createValue<&value_type::parent, &value_type::keys>();
};

template<> struct jsonifier::core<data_animation> {
	using value_type				 = data_animation;
	static constexpr auto parseValue = createValue<&value_type::hierarchy, &value_type::length, &value_type::fps, &value_type::name>();
};

template<> struct jsonifier::core<bone> {
	using value_type				 = bone;
	static constexpr auto parseValue = createValue<&value_type::parent, &value_type::pos, &value_type::rotq, &value_type::scl, &value_type::name>();
};

template<> struct jsonifier::core<data_metadata> {
	using value_type = data_metadata;
	static constexpr auto parseValue =
		createValue<&value_type::uvs, &value_type::version, &value_type::faces, &value_type::generator, &value_type::normals, &value_type::bones, &value_type::vertices>();
};

template<> struct jsonifier::core<data_data> {
	using value_type				 = data_data;
	static constexpr auto parseValue = createValue<&value_type::uvs, &value_type::animations, &value_type::vertices, &value_type::metadata, &value_type::name,
		&value_type::skinWeights, &value_type::skinIndices, &value_type::influencesPerVertex, &value_type::normals, &value_type::bones, &value_type::faces>();
};

template<> struct jsonifier::core<marine_ik_geometry_data> {
	using value_type				 = marine_ik_geometry_data;
	static constexpr auto parseValue = createValue<&value_type::type, &value_type::uuid, &value_type::data>();
};

template<> struct jsonifier::core<image_data> {
	using value_type				 = image_data;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::uuid, &value_type::name>();
};

template<> struct jsonifier::core<material_data> {
	using value_type				 = material_data;
	static constexpr auto parseValue = createValue<&value_type::vertexColors, &value_type::name, &value_type::type, &value_type::uuid, &value_type::blending, &value_type::map,
		&value_type::transparent, &value_type::depthTest, &value_type::color, &value_type::shininess, &value_type::emissive, &value_type::depthWrite, &value_type::specular>();
};

template<> struct jsonifier::core<marine_ik_metadata> {
	using value_type				 = marine_ik_metadata;
	static constexpr auto parseValue = createValue<&value_type::sourceFile, &value_type::generator, &value_type::type, &value_type::version>();
};

template<> struct jsonifier::core<child> {
	using value_type				 = child;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::uuid, &value_type::matrix, &value_type::visible, &value_type::type, &value_type::material,
		&value_type::castShadow, &value_type::receiveShadow, &value_type::geometry>();
};

template<> struct jsonifier::core<object_data> {
	using value_type				 = object_data;
	static constexpr auto parseValue = createValue<&value_type::children, &value_type::type, &value_type::matrix, &value_type::uuid>();
};

template<> struct jsonifier::core<texture_data> {
	using value_type				 = texture_data;
	static constexpr auto parseValue = createValue<&value_type::repeat, &value_type::wrap, &value_type::anisotropy, &value_type::image, &value_type::name, &value_type::mapping,
		&value_type::minFilter, &value_type::uuid, &value_type::magFilter>();
};

template<> struct jsonifier::core<marine_ik> {
	using value_type				 = marine_ik;
	static constexpr auto parseValue = createValue<&value_type::images, &value_type::geometries, &value_type::textures, &value_type::metadata, &value_type::materials,
		&value_type::object, &value_type::animations>();
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, marine_ik_animation_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "fps", data_new.fps);
	get_field_unordered(obj, "tracks", data_new.tracks);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, key_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "rot", data_new.rot);
	get_field_unordered(obj, "scl", data_new.scl);
	get_field_unordered(obj, "time", data_new.time);
	get_field_unordered(obj, "pos", data_new.pos);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, hierarchy_data_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "keys", data_new.keys);
	get_field_unordered(obj, "parent", data_new.parent);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, data_animation_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "fps", data_new.fps);
	get_field_unordered(obj, "length", data_new.length);
	get_field_unordered(obj, "hierarchy", data_new.hierarchy);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, bone_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "scl", data_new.scl);
	get_field_unordered(obj, "rotq", data_new.rotq);
	get_field_unordered(obj, "pos", data_new.pos);
	get_field_unordered(obj, "parent", data_new.parent);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, data_metadata_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "vertices", data_new.vertices);
	get_field_unordered(obj, "bones", data_new.bones);
	get_field_unordered(obj, "normals", data_new.normals);
	get_field_unordered(obj, "generator", data_new.generator);
	get_field_unordered(obj, "faces", data_new.faces);
	get_field_unordered(obj, "version", data_new.version);
	get_field_unordered(obj, "uvs", data_new.uvs);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, data_data_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "faces", data_new.faces);
	get_field_unordered(obj, "bones", data_new.bones);
	get_field_unordered(obj, "normals", data_new.normals);
	get_field_unordered(obj, "influencesPerVertex", data_new.influencesPerVertex);
	get_field_unordered(obj, "skinIndices", data_new.skinIndices);
	get_field_unordered(obj, "skinWeights", data_new.skinWeights);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "metadata", data_new.metadata);
	get_field_unordered(obj, "vertices", data_new.vertices);
	get_field_unordered(obj, "animations", data_new.animations);
	get_field_unordered(obj, "uvs", data_new.uvs);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, marine_ik_geometry_data_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "data", data_new.data);
	get_field_unordered(obj, "uuid", data_new.uuid);
	get_field_unordered(obj, "type", data_new.type);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, image_data_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "uuid", data_new.uuid);
	get_field_unordered(obj, "url", data_new.url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, material_data_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "specular", data_new.specular);
	get_field_unordered(obj, "depthWrite", data_new.depthWrite);
	get_field_unordered(obj, "emissive", data_new.emissive);
	get_field_unordered(obj, "shininess", data_new.shininess);
	get_field_unordered(obj, "color", data_new.color);
	get_field_unordered(obj, "depthTest", data_new.depthTest);
	get_field_unordered(obj, "transparent", data_new.transparent);
	get_field_unordered(obj, "map", data_new.map);
	get_field_unordered(obj, "blending", data_new.blending);
	get_field_unordered(obj, "uuid", data_new.uuid);
	get_field_unordered(obj, "type", data_new.type);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "vertexColors", data_new.vertexColors);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, marine_ik_metadata_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "version", data_new.version);
	get_field_unordered(obj, "type", data_new.type);
	get_field_unordered(obj, "generator", data_new.generator);
	get_field_unordered(obj, "sourceFile", data_new.sourceFile);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, child_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "geometry", data_new.geometry);
	get_field_unordered(obj, "receiveShadow", data_new.receiveShadow);
	get_field_unordered(obj, "castShadow", data_new.castShadow);
	get_field_unordered(obj, "material", data_new.material);
	get_field_unordered(obj, "type", data_new.type);
	get_field_unordered(obj, "visible", data_new.visible);
	get_field_unordered(obj, "matrix", data_new.matrix);
	get_field_unordered(obj, "uuid", data_new.uuid);
	get_field_unordered(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, object_data_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "uuid", data_new.uuid);
	get_field_unordered(obj, "matrix", data_new.matrix);
	get_field_unordered(obj, "type", data_new.type);
	get_field_unordered(obj, "children", data_new.children);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, texture_data_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "magFilter", data_new.magFilter);
	get_field_unordered(obj, "uuid", data_new.uuid);
	get_field_unordered(obj, "minFilter", data_new.minFilter);
	get_field_unordered(obj, "mapping", data_new.mapping);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "image", data_new.image);
	get_field_unordered(obj, "anisotropy", data_new.anisotropy);
	get_field_unordered(obj, "wrap", data_new.wrap);
	get_field_unordered(obj, "repeat", data_new.repeat);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, marine_ik_reverse& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "animations", data_new.animations);
	get_field_unordered(obj, "object", data_new.object);
	get_field_unordered(obj, "materials", data_new.materials);
	get_field_unordered(obj, "metadata", data_new.metadata);
	get_field_unordered(obj, "textures", data_new.textures);
	get_field_unordered(obj, "geometries", data_new.geometries);
	get_field_unordered(obj, "images", data_new.images);
}

template<> struct glz::meta<marine_ik_animation_reverse> {
	using value_type			= marine_ik_animation_reverse;
	static constexpr auto value = object(&value_type::name, &value_type::fps, &value_type::tracks);
};

template<> struct glz::meta<key_reverse> {
	using value_type			= key_reverse;
	static constexpr auto value = object(&value_type::rot, &value_type::scl, &value_type::time, &value_type::pos);
};

template<> struct glz::meta<hierarchy_data_reverse> {
	using value_type			= hierarchy_data_reverse;
	static constexpr auto value = object(&value_type::keys, &value_type::parent);
};

template<> struct glz::meta<data_animation_reverse> {
	using value_type			= data_animation_reverse;
	static constexpr auto value = object(&value_type::name, &value_type::fps, &value_type::length, &value_type::hierarchy);
};

template<> struct glz::meta<bone_reverse> {
	using value_type			= bone_reverse;
	static constexpr auto value = object(&value_type::name, &value_type::scl, &value_type::rotq, &value_type::pos, &value_type::parent);
};

template<> struct glz::meta<data_metadata_reverse> {
	using value_type = data_metadata_reverse;
	static constexpr auto value =
		object(&value_type::vertices, &value_type::bones, &value_type::normals, &value_type::generator, &value_type::faces, &value_type::version, &value_type::uvs);
};

template<> struct glz::meta<data_data_reverse> {
	using value_type			= data_data_reverse;
	static constexpr auto value = object(&value_type::faces, &value_type::bones, &value_type::normals, &value_type::influencesPerVertex, &value_type::skinIndices,
		&value_type::skinWeights, &value_type::name, &value_type::metadata, &value_type::vertices, &value_type::animations, &value_type::uvs);
};

template<> struct glz::meta<marine_ik_geometry_data_reverse> {
	using value_type			= marine_ik_geometry_data_reverse;
	static constexpr auto value = object(&value_type::data, &value_type::uuid, &value_type::type);
};

template<> struct glz::meta<image_data_reverse> {
	using value_type			= image_data_reverse;
	static constexpr auto value = object(&value_type::name, &value_type::uuid, &value_type::url);
};

template<> struct glz::meta<material_data_reverse> {
	using value_type			= material_data_reverse;
	static constexpr auto value = object(&value_type::specular, &value_type::depthWrite, &value_type::emissive, &value_type::shininess, &value_type::color, &value_type::depthTest,
		&value_type::transparent, &value_type::map, &value_type::blending, &value_type::uuid, &value_type::type, &value_type::name, &value_type::vertexColors);
};

template<> struct glz::meta<marine_ik_metadata_reverse> {
	using value_type			= marine_ik_metadata_reverse;
	static constexpr auto value = object(&value_type::version, &value_type::type, &value_type::generator, &value_type::sourceFile);
};

template<> struct glz::meta<child_reverse> {
	using value_type			= child_reverse;
	static constexpr auto value = object(&value_type::geometry, &value_type::receiveShadow, &value_type::castShadow, &value_type::material, &value_type::type, &value_type::visible,
		&value_type::matrix, &value_type::uuid, &value_type::name);
};

template<> struct glz::meta<object_data_reverse> {
	using value_type			= object_data_reverse;
	static constexpr auto value = object(&value_type::uuid, &value_type::matrix, &value_type::type, &value_type::children);
};

template<> struct glz::meta<texture_data_reverse> {
	using value_type			= texture_data_reverse;
	static constexpr auto value = object(&value_type::magFilter, &value_type::uuid, &value_type::minFilter, &value_type::mapping, &value_type::name, &value_type::image,
		&value_type::anisotropy, &value_type::wrap, &value_type::repeat);
};

template<> struct glz::meta<marine_ik_reverse> {
	using value_type = marine_ik_reverse;
	static constexpr auto value =
		object(&value_type::animations, &value_type::object, &value_type::materials, &value_type::metadata, &value_type::textures, &value_type::geometries, &value_type::images);
};

template<> struct jsonifier::core<marine_ik_animation_reverse> {
	using value_type				 = marine_ik_animation_reverse;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::fps, &value_type::tracks>();
};

template<> struct jsonifier::core<key_reverse> {
	using value_type				 = key_reverse;
	static constexpr auto parseValue = createValue<&value_type::rot, &value_type::scl, &value_type::time, &value_type::pos>();
};

template<> struct jsonifier::core<hierarchy_data_reverse> {
	using value_type				 = hierarchy_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::keys, &value_type::parent>();
};

template<> struct jsonifier::core<data_animation_reverse> {
	using value_type				 = data_animation_reverse;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::fps, &value_type::length, &value_type::hierarchy>();
};

template<> struct jsonifier::core<bone_reverse> {
	using value_type				 = bone_reverse;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::scl, &value_type::rotq, &value_type::pos, &value_type::parent>();
};

template<> struct jsonifier::core<data_metadata_reverse> {
	using value_type = data_metadata_reverse;
	static constexpr auto parseValue =
		createValue<&value_type::vertices, &value_type::bones, &value_type::normals, &value_type::generator, &value_type::faces, &value_type::version, &value_type::uvs>();
};

template<> struct jsonifier::core<data_data_reverse> {
	using value_type				 = data_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::faces, &value_type::bones, &value_type::normals, &value_type::influencesPerVertex, &value_type::skinIndices,
		&value_type::skinWeights, &value_type::name, &value_type::metadata, &value_type::vertices, &value_type::animations, &value_type::uvs>();
};

template<> struct jsonifier::core<marine_ik_geometry_data_reverse> {
	using value_type				 = marine_ik_geometry_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::data, &value_type::uuid, &value_type::type>();
};

template<> struct jsonifier::core<image_data_reverse> {
	using value_type				 = image_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::uuid, &value_type::url>();
};

template<> struct jsonifier::core<material_data_reverse> {
	using value_type = material_data_reverse;
	static constexpr auto parseValue =
		createValue<&value_type::specular, &value_type::depthWrite, &value_type::emissive, &value_type::shininess, &value_type::color, &value_type::depthTest,
			&value_type::transparent, &value_type::map, &value_type::blending, &value_type::uuid, &value_type::type, &value_type::name, &value_type::vertexColors>();
};

template<> struct jsonifier::core<marine_ik_metadata_reverse> {
	using value_type				 = marine_ik_metadata_reverse;
	static constexpr auto parseValue = createValue<&value_type::version, &value_type::type, &value_type::generator, &value_type::sourceFile>();
};

template<> struct jsonifier::core<child_reverse> {
	using value_type				 = child_reverse;
	static constexpr auto parseValue = createValue<&value_type::geometry, &value_type::receiveShadow, &value_type::castShadow, &value_type::material, &value_type::type,
		&value_type::visible, &value_type::matrix, &value_type::uuid, &value_type::name>();
};

template<> struct jsonifier::core<object_data_reverse> {
	using value_type				 = object_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::uuid, &value_type::matrix, &value_type::type, &value_type::children>();
};

template<> struct jsonifier::core<texture_data_reverse> {
	using value_type				 = texture_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::magFilter, &value_type::uuid, &value_type::minFilter, &value_type::mapping, &value_type::name, &value_type::image,
		&value_type::anisotropy, &value_type::wrap, &value_type::repeat>();
};

template<> struct jsonifier::core<marine_ik_reverse> {
	using value_type				 = marine_ik_reverse;
	static constexpr auto parseValue = createValue<&value_type::animations, &value_type::object, &value_type::materials, &value_type::metadata, &value_type::textures,
		&value_type::geometries, &value_type::images>();
};