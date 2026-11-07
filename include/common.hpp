/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/common.hpp
 */

#pragma once

#include <glaze/glaze.hpp>
#include <benchmarksuite>
#include <simdjson.h>
#include <jsonifier>

namespace tests {

#if defined(NDEBUG)
	inline constexpr auto max_iteration_count{ 100000 };
	inline constexpr auto measured_iteration_count{ 100 };
#else
	inline constexpr auto max_iteration_count{ 100 };
	inline constexpr auto measured_iteration_count{ 20 };
#endif

	inline constexpr benchmarksuite::string_literal current_path{ benchmarksuite::get_current_path_impl() };
	inline constexpr benchmarksuite::string_literal base_path{ BASE_PATH };
	inline constexpr benchmarksuite::string_literal json_path{ base_path + "/json" };
	inline constexpr benchmarksuite::string_literal csv_out_path{ base_path + "/csv" + "/" + current_path };
	inline constexpr benchmarksuite::string_literal json_out_path{ json_path + "/" + current_path };
	inline constexpr benchmarksuite::string_literal graphs_path{ base_path + "/graphs/" + current_path + "/" };
	inline constexpr benchmarksuite::string_literal jsonifier_library_name{ "Jsonifier" };
	inline constexpr benchmarksuite::string_literal jsonifier_two_stage_library_name{ "Jsonifier (two-stage)" };
	inline constexpr benchmarksuite::string_literal simdjson_library_name{ "simdjson (ondemand)" };
	inline constexpr benchmarksuite::string_literal simdjson_reflection_library_name{ "simdjson (reflection)" };
	inline constexpr benchmarksuite::string_literal glaze_library_name{ "Glaze" };

	enum class test_types {
		parse	  = 0,
		serialize = 1,
		minify	  = 2,
		prettify  = 3,
		validate  = 4,
	};

	enum class json_libraries {
		jsonifier			= 0,
		glaze				= 1,
		simdjson			= 2,
		simdjson_reflection = 3,
		jsonifier_two_stage = 4,
	};

	template<json_libraries json_library>
	concept jsonifier_parse_library = json_library == json_libraries::jsonifier || json_library == json_libraries::jsonifier_two_stage;

	template<json_libraries json_library> struct jsonifier_parse_variant {
		static constexpr bool two_stage{ false };
		static constexpr benchmarksuite::string_literal library_name{ jsonifier_library_name };
		static constexpr benchmarksuite::string_literal file_tag{ "-jsonifier.json" };
	};

	template<> struct jsonifier_parse_variant<json_libraries::jsonifier_two_stage> {
		static constexpr bool two_stage{ true };
		static constexpr benchmarksuite::string_literal library_name{ jsonifier_two_stage_library_name };
		static constexpr benchmarksuite::string_literal file_tag{ "-jsonifier-two-stage.json" };
	};

#if JP_CI_RUN
	inline constexpr double convergence_threshold{ 5.0 };
	inline constexpr double rse_threshold{ 10.0 };
#else
	inline constexpr double convergence_threshold{ 2.5 };
	inline constexpr double rse_threshold{ 5.0 };
#endif

	inline constexpr benchmarksuite::stage_config_data config{ .clear_cpu_caches_before_iterations = true,
		.include_non_converged_results															   = true,
		.measured_iteration_count																   = measured_iteration_count,
		.max_iteration_count																	   = max_iteration_count,
		.convergence_threshold																	   = convergence_threshold,
		.max_time_in_s																			   = 5,
		.rse_threshold																			   = rse_threshold };

	inline constexpr benchmarksuite::string_literal stage_name{ "Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson" };

	using benchmark_stage = benchmarksuite::benchmark_stage<stage_name, config>;

	inline constexpr benchmarksuite::string_literal reused_suffix{ " (Reused)" };

	template<test_types test_type, json_libraries json_library, benchmarksuite::string_literal test_name, bool minified, typename test_data_type> struct library_traits;

	template<typename value_type>
	concept pod_types = std::is_same_v<bool, value_type> || std::is_same_v<std::string, value_type> || std::is_same_v<int64_t, value_type> ||
		std::is_same_v<uint64_t, value_type> || std::is_same_v<double, value_type>;

#if SIMDJSON_STATIC_REFLECTION
	#define JP_SIMDJSON_RENAME(json_key) [[= simdjson::rename<json_key>]]
#else
	#define JP_SIMDJSON_RENAME(json_key)
#endif

	inline std::vector<std::string> string_to_vector(const std::string& input) {
		std::vector<std::string> result;
		static constexpr std::string_view start_tag = "[START]";
		static constexpr std::string_view end_tag	= "[END]";
		size_t pos									= 0;

		while (true) {
			size_t start_pos = input.find(start_tag, pos);
			if (start_pos == std::string::npos) {
				break;
			}
			start_pos += start_tag.size();

			size_t end_pos = input.find(end_tag, start_pos);
			if (end_pos == std::string::npos) {
				size_t slice_length = input.size() - start_pos;
				std::string sliced;
				sliced.reserve(slice_length + simdjson::SIMDJSON_PADDING);
				sliced.append(input, start_pos, slice_length);
				result.emplace_back(std::move(sliced));
				break;
			}

			size_t slice_length = end_pos - start_pos;
			std::string sliced;
			sliced.reserve(slice_length + simdjson::SIMDJSON_PADDING);
			sliced.append(input, start_pos, slice_length);
			result.emplace_back(std::move(sliced));

			pos = end_pos + end_tag.size();
		}

		return result;
	}

	template<typename v_type>
	concept document_or_value =
		std::is_same_v<simdjson::ondemand::value, std::remove_cvref_t<v_type>> || std::is_same_v<simdjson::ondemand::document, std::remove_cvref_t<v_type>> ||
		std::is_same_v<simdjson::simdjson_result<simdjson::ondemand::document>, std::remove_cvref_t<v_type>>;

	template<tests::document_or_value simdjson_type, typename v_type> inline void get_value(simdjson_type val_new, v_type&);

	template<tests::document_or_value simdjson_type, typename v_type> inline void get_value(simdjson_type val_new, std::vector<v_type>& data_new);

	template<tests::document_or_value simdjson_type, typename k_type, typename v_type> inline void get_value(simdjson_type val_new, std::unordered_map<k_type, v_type>& data_new);

	template<tests::document_or_value simdjson_type, typename v_type>
		requires(std::is_same_v<decltype(std::vector<bool>{}[0]), v_type>)
	JSONIFIER_INLINE void get_value(simdjson_type doc, v_type& msg) {
		msg = doc.get_bool();
	}

	template<tests::document_or_value simdjson_type> JSONIFIER_INLINE void get_value(simdjson_type val_new, std::optional<std::string>&) {
		val_new.is_null();
	}

	template<tests::document_or_value simdjson_type, typename v_type>
		requires(std::is_same_v<v_type, std::string> || std::is_same_v<v_type, std::string_view>)
	JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
		data_new = static_cast<v_type>(val_new.get_string().value());
	}

	template<tests::document_or_value simdjson_type, typename v_type>
		requires(std::is_same_v<v_type, bool> || std::is_same_v<decltype(std::vector<bool>{}[0]), std::remove_cvref_t<v_type>>)
	JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
		data_new = static_cast<v_type>(val_new.get_bool());
	}

	template<tests::document_or_value simdjson_type> JSONIFIER_INLINE void get_value(simdjson_type val_new, bool& data_new) {
		data_new = static_cast<bool>(val_new.get_bool());
	}

	template<tests::document_or_value simdjson_type, typename v_type>
		requires(std::unsigned_integral<v_type> && sizeof(v_type) == 4)
	JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
		data_new = static_cast<v_type>(val_new.get_uint32());
	}

	template<tests::document_or_value simdjson_type, typename v_type>
		requires(std::unsigned_integral<v_type> && sizeof(v_type) == 8)
	JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
		data_new = static_cast<v_type>(val_new.get_uint64());
	}

	template<tests::document_or_value simdjson_type, typename v_type>
		requires(std::signed_integral<v_type> && sizeof(v_type) == 4)
	JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
		data_new = static_cast<v_type>(val_new.get_int32());
	}

	template<tests::document_or_value simdjson_type, typename v_type>
		requires(std::signed_integral<v_type> && sizeof(v_type) == 8)
	JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
		data_new = static_cast<v_type>(val_new.get_int64());
	}

	template<tests::document_or_value simdjson_type, typename v_type>
		requires(std::floating_point<v_type>)
	JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
		data_new = static_cast<v_type>(val_new.get_double());
	}

	template<tests::document_or_value simdjson_type, typename t> JSONIFIER_INLINE void get_value(simdjson_type val_new, std::optional<t>& data_new) {
		if (val_new.is_null()) {
			data_new.reset();
			return;
		}
		get_value(val_new, data_new.emplace());
	}

	JSONIFIER_INLINE simdjson::ondemand::object get_object(simdjson::ondemand::value val_new) {
		return val_new.get_object();
	}

	JSONIFIER_INLINE simdjson::ondemand::array get_array(simdjson::ondemand::value val_new) {
		return val_new.get_array();
	}

	template<tests::document_or_value simdjson_type, typename v_type> inline void get_value(simdjson_type val_new, std::vector<v_type>& data_new) {
		for (auto element: get_array(val_new)) {
			get_value(element.value(), data_new.emplace_back());
		}
	}

	template<tests::document_or_value simdjson_type, typename k_type, typename v_type> inline void get_value(simdjson_type val_new, std::unordered_map<k_type, v_type>& data_new) {
		for (auto field: get_object(val_new)) {
			std::string_view unescaped{ field.unescaped_key().value() };
			auto [it, inserted] = data_new.try_emplace(k_type(unescaped.data(), unescaped.size()));
			get_value(field.value().value(), it->second);
		}
	}

	template<typename v_type> inline void get_field(simdjson::ondemand::object& obj, const char* key, v_type& data_new) {
		simdjson::ondemand::value val;
		if (auto result = obj.find_field(key).get(val); !result) {
			get_value(val, data_new);
		}
		return;
	}

	template<typename v_type> inline void get_field_unordered(simdjson::ondemand::object& obj, const char* key, v_type& data_new) {
		simdjson::ondemand::value val;
		if (auto result = obj.find_field_unordered(key).get(val); !result) {
			get_value(val, data_new);
		}
		return;
	}

#if JSONIFIER_COMPILER_MSVC
	template<simdjson::constevalutil::fixed_string... keys, typename... v_types> inline void get_fields(simdjson::ondemand::object& obj, v_types&... data_new) {
		(get_field(obj, keys.data, data_new), ...);
	}

	template<simdjson::constevalutil::fixed_string... keys, typename... v_types> inline void get_fields_unordered(simdjson::ondemand::object& obj, v_types&... data_new) {
		(get_field_unordered(obj, keys.data, data_new), ...);
	}
#else
	template<typename v_type> struct field_target {
		v_type& target;

		JSONIFIER_INLINE void operator()(simdjson::ondemand::value val_new) const {
			get_value(val_new, target);
		}
	};

	template<simdjson::constevalutil::fixed_string... keys, typename... v_types> inline void get_fields(simdjson::ondemand::object& obj, v_types&... data_new) {
		static_cast<void>(obj.template for_each<keys...>(field_target<v_types>{ data_new }...));
	}

	template<simdjson::constevalutil::fixed_string... keys, typename... v_types> inline void get_fields_unordered(simdjson::ondemand::object& obj, v_types&... data_new) {
		get_fields<keys...>(obj, data_new...);
	}
#endif

	template<tests::document_or_value simdjson_type, typename value_type> inline void get_value(simdjson_type val_new, value_type& data_new) {
		get_value(val_new.get_value(), data_new);
	}

	template<typename value_type> inline void clear_value(value_type& value);

	template<typename value_type, uint64_t... indices> inline void clear_members(value_type& value, std::integer_sequence<uint64_t, indices...>) {
		(clear_value(value.*(jsonifier::internal::getBecauseOtherLibAuthorsResolve<indices>(jsonifier::core<value_type>::parseValue).memberPtr)), ...);
	}

	template<typename value_type> inline void clear_value(value_type& value) {
		if constexpr (requires { value.clear(); }) {
			value.clear();
		} else if constexpr (requires { value.reset(); }) {
			value.reset();
		} else if constexpr (jsonifier::internal::jsonifier_object_types<value_type>) {
			clear_members(value, std::make_integer_sequence<uint64_t, jsonifier::internal::coreTupleSize<value_type>>{});
		} else {
			value = value_type{};
		}
	}

}
