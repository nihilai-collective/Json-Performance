/*
	MIT License

	Copyright (c) 2026 Nihilai Collective Corp

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
/// https://github.com/nihilai-collective/Json-Performance
#pragma once

#include <benchmarksuite>
#include <simdjson.h>
#include <jsonifier>

#if defined(NDEBUG)
static constexpr auto max_iteration_count{ 100000 };
static constexpr auto measured_iteration_count{ 80 };
#else
static constexpr auto max_iteration_count{ 100 };
static constexpr auto measured_iteration_count{ 20 };
#endif

constexpr benchmarksuite::string_literal current_path{ benchmarksuite::get_current_path_impl() };
constexpr benchmarksuite::string_literal base_path{ BASE_PATH };
constexpr benchmarksuite::string_literal json_path{ base_path + "/json" };
constexpr benchmarksuite::string_literal csv_out_path{ base_path + "/csv" + "/" + current_path };
constexpr benchmarksuite::string_literal json_out_path{ json_path + "/" + current_path };
constexpr benchmarksuite::string_literal graphs_path{ base_path + "/graphs/" + current_path + "/" };
constexpr benchmarksuite::string_literal jsonifier_library_name{ "jsonifier" };
constexpr benchmarksuite::string_literal simdjson_library_name{ "simdjson (ondemand)" };

struct abc_in_order_test_struct {
	std::string test_string;
	uint64_t test_uint;
	int64_t test_int;
	double test_double;
	bool test_bool;
};

struct abc_in_order_test {
	std::vector<abc_in_order_test_struct> a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
};

struct abc_out_of_order_test_struct {
	bool test_bool;
	double test_double;
	int64_t test_int;
	uint64_t test_uint;
	std::string test_string;
};

struct abc_out_of_order_test {
	std::vector<abc_out_of_order_test_struct> z, y, x, w, v, u, t, s, r, q, p, o, n, m, l, k, j, i, h, g, f, e, d, c, b, a;
};

struct abc_in_order_partial_test_struct {
	std::string test_string;
	int64_t test_int;
	bool test_bool;
};

struct abc_in_order_partial_test {
	std::vector<abc_in_order_partial_test_struct> a, m, z;
};

struct abc_out_of_order_partial_test_struct {
	bool test_bool;
	int64_t test_int;
	std::string test_string;
};

struct abc_out_of_order_partial_test {
	std::vector<abc_out_of_order_partial_test_struct> z, m, a;
};

template<> struct jsonifier::core<abc_in_order_partial_test_struct> {
	using value_type				 = abc_in_order_partial_test_struct;
	static constexpr auto parseValue = createValue<&value_type::test_string, &value_type::test_int, &value_type::test_bool>();
};

template<> struct jsonifier::core<abc_in_order_partial_test> {
	using value_type				 = abc_in_order_partial_test;
	static constexpr auto parseValue = createValue<&value_type::a, &value_type::m, &value_type::z>();
};

template<> struct jsonifier::core<abc_in_order_test_struct> {
	using value_type				 = abc_in_order_test_struct;
	static constexpr auto parseValue = createValue<&value_type::test_string, &value_type::test_uint, &value_type::test_int, &value_type::test_double, &value_type::test_bool>();
};

template<> struct jsonifier::core<abc_in_order_test> {
	using value_type				 = abc_in_order_test;
	static constexpr auto parseValue = createValue<&value_type::a, &value_type::b, &value_type::c, &value_type::d, &value_type::e, &value_type::f, &value_type::g, &value_type::h,
		&value_type::i, &value_type::j, &value_type::k, &value_type::l, &value_type::m, &value_type::n, &value_type::o, &value_type::p, &value_type::q, &value_type::r,
		&value_type::s, &value_type::t, &value_type::u, &value_type::v, &value_type::w, &value_type::x, &value_type::y, &value_type::z>();
};

template<> struct jsonifier::core<abc_out_of_order_partial_test_struct> {
	using value_type				 = abc_out_of_order_partial_test_struct;
	static constexpr auto parseValue = createValue<&value_type::test_bool, &value_type::test_int, &value_type::test_string>();
};

template<> struct jsonifier::core<abc_out_of_order_partial_test> {
	using value_type				 = abc_out_of_order_partial_test;
	static constexpr auto parseValue = createValue<&value_type::z, &value_type::m, &value_type::a>();
};

template<> struct jsonifier::core<abc_out_of_order_test_struct> {
	using value_type				 = abc_out_of_order_test_struct;
	static constexpr auto parseValue = createValue<&value_type::test_bool, &value_type::test_double, &value_type::test_int, &value_type::test_uint, &value_type::test_string>();
};

template<> struct jsonifier::core<abc_out_of_order_test> {
	using value_type				 = abc_out_of_order_test;
	static constexpr auto parseValue = createValue<&value_type::z, &value_type::y, &value_type::x, &value_type::w, &value_type::v, &value_type::u, &value_type::t, &value_type::s,
		&value_type::r, &value_type::q, &value_type::p, &value_type::o, &value_type::n, &value_type::m, &value_type::l, &value_type::k, &value_type::j, &value_type::i,
		&value_type::h, &value_type::g, &value_type::f, &value_type::e, &value_type::d, &value_type::c, &value_type::b, &value_type::a>();
};

std::vector<std::string> string_to_vector(const std::string& input) {
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
concept document_or_value = std::is_same_v<simdjson::ondemand::value, std::remove_cvref_t<v_type>> || std::is_same_v<simdjson::ondemand::document, std::remove_cvref_t<v_type>> ||
	std::is_same_v<simdjson::simdjson_result<simdjson::ondemand::document>, std::remove_cvref_t<v_type>>;

template<document_or_value simdjson_type, typename v_type> inline void get_value(simdjson_type val_new, v_type&);

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<decltype(std::vector<bool>{}[0]), v_type>)
JSONIFIER_INLINE void get_value(simdjson_type doc, v_type& msg) {
	msg = doc.get_bool();
}

template<document_or_value simdjson_type> JSONIFIER_INLINE void get_value(simdjson_type val_new, std::nullptr_t&) {
	val_new.is_null();
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<v_type, std::string> || std::is_same_v<v_type, std::string_view>)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_string().value());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<v_type, bool> || std::is_same_v<decltype(std::vector<bool>{}[0]), std::remove_cvref_t<v_type>>)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_bool());
}

template<document_or_value simdjson_type> JSONIFIER_INLINE void get_value(simdjson_type val_new, bool& data_new) {
	data_new = static_cast<bool>(val_new.get_bool());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::unsigned_integral<v_type> && sizeof(v_type) == 4)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_uint32());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::unsigned_integral<v_type> && sizeof(v_type) == 8)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_uint64());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::signed_integral<v_type> && sizeof(v_type) == 4)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_int32());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::signed_integral<v_type> && sizeof(v_type) == 8)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_int64());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::floating_point<v_type>)
JSONIFIER_INLINE void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_double());
}

template<document_or_value simdjson_type, typename t> JSONIFIER_INLINE void get_value(simdjson_type val_new, std::optional<t>& data_new) {
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

template<document_or_value simdjson_type, typename v_type> inline void get_value(simdjson_type val_new, std::vector<v_type>& data_new) {
	simdjson::ondemand::array array{ get_array(val_new) };
	auto begin = array.begin();
	auto end   = array.end();
	for (; begin != end; ++begin) {
		get_value(begin.value().operator*().value(), data_new.emplace_back());
	}
}

template<document_or_value simdjson_type, typename k_type, typename v_type> inline void get_value(simdjson_type val_new, std::unordered_map<k_type, v_type>& data_new) {
	simdjson::ondemand::object object{ get_object(val_new) };
	for (auto field: object) {
		std::string_view unescaped{ field.unescaped_key().value() };
		k_type key;
		if constexpr (std::is_same_v<k_type, std::string_view>) {
			key = unescaped;
		} else {
			key = k_type(unescaped.data(), unescaped.size());
		}
		simdjson::ondemand::value child{ field.value().value() };
		auto [it, inserted] = data_new.try_emplace(std::move(key));
		get_value(child, it->second);
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

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_in_order_partial_test_struct& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "test_string", data_new.test_string);
	get_field(obj, "test_int", data_new.test_int);
	get_field(obj, "test_bool", data_new.test_bool);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_in_order_partial_test& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "a", data_new.a);
	get_field(obj, "m", data_new.m);
	get_field(obj, "z", data_new.z);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_in_order_test_struct& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "test_string", data_new.test_string);
	get_field(obj, "test_uint", data_new.test_uint);
	get_field(obj, "test_int", data_new.test_int);
	get_field(obj, "test_double", data_new.test_double);
	get_field(obj, "test_bool", data_new.test_bool);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_in_order_test& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "a", data_new.a);
	get_field(obj, "b", data_new.b);
	get_field(obj, "c", data_new.c);
	get_field(obj, "d", data_new.d);
	get_field(obj, "e", data_new.e);
	get_field(obj, "f", data_new.f);
	get_field(obj, "g", data_new.g);
	get_field(obj, "h", data_new.h);
	get_field(obj, "i", data_new.i);
	get_field(obj, "j", data_new.j);
	get_field(obj, "k", data_new.k);
	get_field(obj, "l", data_new.l);
	get_field(obj, "m", data_new.m);
	get_field(obj, "n", data_new.n);
	get_field(obj, "o", data_new.o);
	get_field(obj, "p", data_new.p);
	get_field(obj, "q", data_new.q);
	get_field(obj, "r", data_new.r);
	get_field(obj, "s", data_new.s);
	get_field(obj, "t", data_new.t);
	get_field(obj, "u", data_new.u);
	get_field(obj, "v", data_new.v);
	get_field(obj, "w", data_new.w);
	get_field(obj, "x", data_new.x);
	get_field(obj, "y", data_new.y);
	get_field(obj, "z", data_new.z);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_out_of_order_partial_test_struct& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "test_bool", data_new.test_bool);
	get_field_unordered(obj, "test_int", data_new.test_int);
	get_field_unordered(obj, "test_string", data_new.test_string);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_out_of_order_partial_test& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "z", data_new.z);
	get_field_unordered(obj, "m", data_new.m);
	get_field_unordered(obj, "a", data_new.a);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_out_of_order_test_struct& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "test_bool", data_new.test_bool);
	get_field_unordered(obj, "test_double", data_new.test_double);
	get_field_unordered(obj, "test_int", data_new.test_int);
	get_field_unordered(obj, "test_uint", data_new.test_uint);
	get_field_unordered(obj, "test_string", data_new.test_string);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_out_of_order_test& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "z", data_new.z);
	get_field_unordered(obj, "y", data_new.y);
	get_field_unordered(obj, "x", data_new.x);
	get_field_unordered(obj, "w", data_new.w);
	get_field_unordered(obj, "v", data_new.v);
	get_field_unordered(obj, "u", data_new.u);
	get_field_unordered(obj, "t", data_new.t);
	get_field_unordered(obj, "s", data_new.s);
	get_field_unordered(obj, "r", data_new.r);
	get_field_unordered(obj, "q", data_new.q);
	get_field_unordered(obj, "p", data_new.p);
	get_field_unordered(obj, "o", data_new.o);
	get_field_unordered(obj, "n", data_new.n);
	get_field_unordered(obj, "m", data_new.m);
	get_field_unordered(obj, "l", data_new.l);
	get_field_unordered(obj, "k", data_new.k);
	get_field_unordered(obj, "j", data_new.j);
	get_field_unordered(obj, "i", data_new.i);
	get_field_unordered(obj, "h", data_new.h);
	get_field_unordered(obj, "g", data_new.g);
	get_field_unordered(obj, "f", data_new.f);
	get_field_unordered(obj, "e", data_new.e);
	get_field_unordered(obj, "d", data_new.d);
	get_field_unordered(obj, "c", data_new.c);
	get_field_unordered(obj, "b", data_new.b);
	get_field_unordered(obj, "a", data_new.a);
}

template<document_or_value simdjson_type, typename value_type> inline void get_value(simdjson_type val_new, value_type& data_new) {
	get_value(val_new.get_value(), data_new);
}
