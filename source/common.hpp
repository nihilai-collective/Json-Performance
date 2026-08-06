/*
	MIT License

	Copyright (c) 2024 RealTimeChris

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
/// https://github.com/RealTimeChris/Json-Performance
#pragma once

#include <bnch_swt>
#include <jsonifier>
#include <simdjson.h>
#include <unordered_set>
#include <thread>
#include <random>

#if defined(NDEBUG)
static constexpr auto max_iteration_count{ 100000 };
static constexpr auto measured_iteration_count{ 80 };
static constexpr auto allocation_size{ 1024 * 1024 * 128 };
static constexpr auto min_k{ 20 };
#else
static constexpr auto max_iteration_count{ 100 };
static constexpr auto measured_iteration_count{ 20 };
static constexpr auto allocation_size{ 1024 * 1024 * 128 };
static constexpr auto min_k{ 10 };
#endif

inline static std::string current_path{ bnch_swt::get_current_path_impl() };
constexpr bnch_swt::string_literal base_path{ BASE_PATH };
constexpr bnch_swt::string_literal test_path{ base_path + "/source" };
constexpr bnch_swt::string_literal read_me_path{ BASE_PATH };
constexpr bnch_swt::string_literal json_path{ base_path + "/json" };
constexpr bnch_swt::string_literal csv_path{ base_path + "/csv" };
inline static std::string json_out_path{ json_path.operator std::string() + "/" + current_path };
inline static std::string csv_out_path{ csv_path.operator std::string() + "/" + current_path };
inline static std::string graphs_path{ base_path.operator std::string() + "/graphs/" + current_path + "/" };
constexpr bnch_swt::string_literal jsonifier_library_name{ "jsonifier" };
constexpr bnch_swt::string_literal jsonifier_commit_url_base{ "https://github.com/realtimechris/jsonifier/commit/" };
constexpr bnch_swt::string_literal jsonifier_commit_url{ jsonifier_commit_url_base + JSONIFIER_COMMIT };
constexpr bnch_swt::string_literal simdjson_library_name{ "simdjson" };
constexpr bnch_swt::string_literal simdjson_commit_url_base{ "https://github.com/simdjson/simdjson/commit/" };
constexpr bnch_swt::string_literal simdjson_commit_url{ simdjson_commit_url_base + SIMDJSON_COMMIT };

struct abc_in_order_partial_test_struct {
	std::string test_string;
	bool test_bool;
};

struct abc_out_of_order_test_struct {
	bool test_bool;
	double test_double;
	int64_t test_int;
	uint64_t test_uint;
	std::string test_string;
};

template<typename value_type> struct abc_out_of_order_test {
	std::vector<value_type> z, y, x, w, v, u, t, s, r, q, p, o, n, m, l, k, j, i, h, g, f, e, d, c, b, a;
};

template<typename value_type> struct abc_in_order_partial_test {
	std::vector<value_type> a, z;
};

BNCH_SWT_HOST std::string generate_integer_part(uint64_t min_length = 1, uint64_t max_length = 15) {
	bnch_swt::random_generator<uint64_t> rg;
	uint64_t length = rg.impl(min_length, max_length);

	if (length == 1 && rg.impl(0, 1) == 0 && rg.impl(0, 9) == 0)
		return "0";

	std::string s;
	s += std::to_string(rg.impl(1, 9));

	for (uint64_t i = 1; i < length; ++i) {
		s += std::to_string(rg.impl(0, 9));
	}
	return s;
}

BNCH_SWT_HOST std::string maybe_add_sign(const std::string& s) {
	bnch_swt::random_generator<uint64_t> rg;
	return (rg.impl(0, 1) == 1) ? ("-" + s) : s;
}

BNCH_SWT_HOST std::string generate_1_simple_integer() {
	return maybe_add_sign(generate_integer_part(1, 10));
}

BNCH_SWT_HOST std::string generate_2_simple_float() {
	bnch_swt::random_generator<uint64_t> rg;
	std::string s = generate_integer_part(1, 5);
	s += ".";

	uint64_t fractional_length = rg.impl(1, 10);
	for (uint64_t i = 0; i < fractional_length; ++i) {
		s += std::to_string(rg.impl(0, 9));
	}
	return maybe_add_sign(s);
}

BNCH_SWT_HOST std::string generate_3_scientific() {
	bnch_swt::random_generator<uint64_t> rg;
	std::string s;

	if (rg.impl(0, 1) == 0) {
		s = generate_integer_part(1, 3) + ".";
		s += std::to_string(rg.impl(0, 9));
	} else {
		s = generate_integer_part(1, 5);
	}

	s += (rg.impl(0, 1) == 0 ? 'e' : 'E');
	s += (rg.impl(0, 1) == 0 ? '+' : '-');
	uint64_t exponent = rg.impl(1, 100);
	s += std::to_string(exponent);

	return maybe_add_sign(s);
}

BNCH_SWT_HOST std::string generate_4_min_max_boundary() {
	bnch_swt::random_generator<uint64_t> rg;
	bnch_swt::random_generator<double> rg_double;
	if (rg.impl(0, 1) == 0) {
		double mantissa	  = rg_double.impl(1.0, 9.9);
		uint64_t exponent = rg.impl(300, 308);
		double val		  = mantissa * std::pow(10.0, exponent);
		if (rg.impl(0, 1) == 1)
			val = -val;

		std::stringstream ss;
		ss << std::scientific << std::setprecision(16) << val;
		return ss.str();
	} else {
		double mantissa	  = rg_double.impl(1.0, 9.9);
		uint64_t exponent = rg.impl(300, 308);
		double val		  = mantissa * std::pow(10.0, static_cast<double>(-static_cast<int64_t>(exponent)));
		if (rg.impl(0, 1) == 1)
			val = -val;

		std::stringstream ss;
		ss << std::scientific << std::setprecision(16) << val;
		return ss.str();
	}
}

BNCH_SWT_HOST std::string generate_5_precision_boundary() {
	bnch_swt::random_generator<uint64_t> rg;
	std::string s;
	s += maybe_add_sign(std::to_string(rg.impl(1, 9)));
	s += ".";

	for (uint64_t i = 0; i < 18; ++i) {
		s += std::to_string(rg.impl(0, 9));
	}

	if (rg.impl(0, 1) == 0) {
		s += 'e';
		s += std::to_string(rg.impl(1, 100));
	}
	return s;
}

BNCH_SWT_HOST std::string generate_6_zero_subnormal() {
	bnch_swt::random_generator<double> rg_double;
	bnch_swt::random_generator<uint64_t> rg;
	if (rg.impl(0, 1) == 0) {
		static constexpr std::array zero_forms = { "0", "0.0", "-0.0", "0e0", "-0e5", "0.0e-10" };
		uint64_t index						   = rg.impl(0, zero_forms.size() - 1);
		return zero_forms[index];
	} else {
		double mantissa = rg_double.impl(1.0, 9.9);
		double val		= mantissa * std::pow(10.0, -315);

		std::stringstream ss;
		ss << std::scientific << std::setprecision(16) << val;
		return maybe_add_sign(ss.str());
	}
}

BNCH_SWT_HOST std::string generate_7_structural_edge() {
	bnch_swt::random_generator<uint64_t> rg;
	static constexpr std::array edge_forms = { "1e10", "-9e-10", "0.1", "-9.0", "1.2e0", "-3e+0", "123.000000", "0.0000001" };
	uint64_t index						   = rg.impl(0, edge_forms.size() - 1);
	return edge_forms[index];
}

BNCH_SWT_HOST std::string generate_random_double_string() {
	bnch_swt::random_generator<uint64_t> rg;
	static constexpr std::array weights = { 40.0, 30.0, 10.0, 5.0, 5.0, 5.0, 5.0 };

	static constexpr std::array generators = { generate_1_simple_integer, generate_2_simple_float, generate_3_scientific, generate_4_min_max_boundary,
		generate_5_precision_boundary, generate_6_zero_subnormal, generate_7_structural_edge };

	uint64_t roll = rg.impl(0, 99);

	uint64_t cumulative_weight = 0;
	for (size_t i = 0; i < weights.size(); ++i) {
		cumulative_weight += static_cast<uint64_t>(weights[i]);
		if (roll < cumulative_weight) {
			return generators[i]();
		}
	}
	return generators.back()();
}

BNCH_SWT_HOST double generate_random_double() {
	double test_double;
	do {
		std::string test_string = generate_random_double_string();
		auto new_ptr			= test_string.data() + test_string.size();
		test_double				= strtod(test_string.data(), &new_ptr);
	} while (test_double == std::numeric_limits<double>::infinity() || std::isnan(test_double) || test_double == -std::numeric_limits<double>::infinity());
	return test_double;
}

std::vector<std::string> stringToVector(const std::string& input) {
	std::vector<std::string> result;

	const std::string startTag = "[START]";

	const std::string endTag = "[END]";

	size_t pos = 0;

	while (true) {
		size_t startPos = input.find(startTag, pos);

		if (startPos == std::string::npos) {
			break;
		}

		startPos += startTag.size();

		size_t endPos = input.find(endTag, startPos);

		if (endPos == std::string::npos) {
			result.emplace_back(input.substr(startPos));

			break;
		}

		result.emplace_back(input.substr(startPos, endPos - startPos));

		pos = endPos + endTag.size();
	}

	return result;
}

std::string vectorToString(const std::vector<std::string>& vec) {
	std::string result;
	for (size_t i = 0; i < vec.size(); ++i) {
		const std::string& s = vec[i];
		result += "[START]";
		result += s;
		result += "[END]\n";
	}
	return result;
}

struct test_generator {
	template<jsonifier::concepts::string_t value_type> static value_type generate_value() {
		bnch_swt::random_generator<uint64_t> rg;
		bnch_swt::random_generator<std::string> rg_string;
		return rg_string.impl(rg.impl(16ull, 64ull));
	}

	template<jsonifier::concepts::float_t value_type> static value_type generate_value() {
		return generate_random_double();
	}

	template<jsonifier::concepts::bool_t value_type> static value_type generate_value() {
		bnch_swt::random_generator<bool> rg;
		return rg.impl();
	}

	template<jsonifier::concepts::uint64_types value_type> static value_type generate_value() {
		bnch_swt::random_generator<uint64_t> rg;
		return rg.impl();
	}

	template<jsonifier::concepts::int64_types value_type> static value_type generate_value() {
		bnch_swt::random_generator<int64_t> rg;
		return rg.impl();
	}

	static abc_out_of_order_test_struct generate_test_struct() {
		abc_out_of_order_test_struct return_values;
		return_values.test_bool	  = generate_value<bool>();
		return_values.test_double = generate_value<double>();
		return_values.test_int	  = generate_value<int64_t>();
		return_values.test_uint	  = generate_value<uint64_t>();
		return_values.test_string = generate_value<std::string>();
		return return_values;
	}

	template<typename value_type> static std::vector<value_type> generate_values(size_t value_count) {
		std::vector<value_type> return_values;
		return_values.resize(value_count);
		for (size_t x = 0; x < value_count; ++x) {
			return_values[x] = generate_value<value_type>();
		}
		return return_values;
	}

	static abc_out_of_order_test<abc_out_of_order_test_struct> generate_test() {
		bnch_swt::random_generator<uint64_t> rg;
		abc_out_of_order_test<abc_out_of_order_test_struct> return_values;
		auto fill = [&](auto& v) {
			const auto array_size_01 = rg.impl(1ull, 15ull);
			v.resize(array_size_01);
			for (uint64_t x = 0; x < array_size_01; ++x) {
				v[x] = generate_test_struct();
			}
		};

		fill(return_values.a);
		fill(return_values.b);
		fill(return_values.c);
		fill(return_values.d);
		fill(return_values.e);
		fill(return_values.f);
		fill(return_values.g);
		fill(return_values.h);
		fill(return_values.i);
		fill(return_values.j);
		fill(return_values.k);
		fill(return_values.l);
		fill(return_values.m);
		fill(return_values.n);
		fill(return_values.o);
		fill(return_values.p);
		fill(return_values.q);
		fill(return_values.r);
		fill(return_values.s);
		fill(return_values.t);
		fill(return_values.u);
		fill(return_values.v);
		fill(return_values.w);
		fill(return_values.x);
		fill(return_values.y);
		fill(return_values.z);
		return return_values;
	}
};

template<typename v_type>
concept document_or_value = std::is_same_v<simdjson::ondemand::value, std::remove_cvref_t<v_type>> || std::is_same_v<simdjson::ondemand::document, std::remove_cvref_t<v_type>> ||
	std::is_same_v<simdjson::simdjson_result<simdjson::ondemand::document>, std::remove_cvref_t<v_type>>;

template<document_or_value simdjson_type, typename v_type> inline void get_value(simdjson_type val_new, v_type&);

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<decltype(std::vector<bool>{}[0]), v_type>)
inline void get_value(simdjson_type doc, v_type& msg) {
	msg = doc.get_bool();
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, std::nullptr_t&) {
	val_new.is_null();
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<v_type, std::string> || std::is_same_v<v_type, std::string_view>)
inline void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_string().value());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::is_same_v<v_type, bool> || std::is_same_v<decltype(std::vector<bool>{}[0]), std::remove_cvref_t<v_type>>)
inline void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_bool());
}

template<document_or_value simdjson_type>
inline void get_value(simdjson_type val_new, bool& data_new) {
	data_new = static_cast<bool>(val_new.get_bool());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::unsigned_integral<v_type> && sizeof(v_type) == 4)
inline void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_uint32());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::unsigned_integral<v_type> && sizeof(v_type) == 8)
inline void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_uint64());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::signed_integral<v_type> && sizeof(v_type) == 4)
inline void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_int32());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::signed_integral<v_type> && sizeof(v_type) == 8)
inline void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_int64());
}

template<document_or_value simdjson_type, typename v_type>
	requires(std::floating_point<v_type>)
inline void get_value(simdjson_type val_new, v_type& data_new) {
	data_new = static_cast<v_type>(val_new.get_double());
}

template<document_or_value simdjson_type, typename t> inline void get_value(simdjson_type val_new, std::optional<t>& data_new) {
	if (val_new.is_null()) {
		data_new.reset();
		return;
	}
	get_value(val_new, data_new.emplace());
}

inline simdjson::ondemand::object get_object(simdjson::ondemand::value val_new) {
	return val_new.get_object();
}

inline simdjson::ondemand::array get_array(simdjson::ondemand::value val_new) {
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
	get_field_unordered(obj, "test_string", data_new.test_string);
	get_field_unordered(obj, "test_bool", data_new.test_bool);
}

template<document_or_value simdjson_type, typename value_type> inline void get_value(simdjson_type val_new, abc_in_order_partial_test<value_type>& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "a", data_new.a);
	get_field_unordered(obj, "z", data_new.z);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, abc_out_of_order_test_struct& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field_unordered(obj, "test_bool", data_new.test_bool);
	get_field_unordered(obj, "test_double", data_new.test_double);
	get_field_unordered(obj, "test_int", data_new.test_int);
	get_field_unordered(obj, "test_uint", data_new.test_uint);
	get_field_unordered(obj, "test_string", data_new.test_string);
}

template<document_or_value simdjson_type, typename value_type> inline void get_value(simdjson_type val_new, abc_out_of_order_test<value_type>& data_new) {
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

template<> struct jsonifier::core<abc_in_order_partial_test_struct> {
	using value_type				 = abc_in_order_partial_test_struct;
	static constexpr auto parseValue = createValue<&value_type::test_string, &value_type::test_bool>();
};

template<> struct jsonifier::core<abc_out_of_order_test_struct> {
	using value_type				 = abc_out_of_order_test_struct;
	static constexpr auto parseValue = createValue<&value_type::test_bool, &value_type::test_double, &value_type::test_int, &value_type::test_uint, &value_type::test_string>();
};

template<typename value_type_new> struct jsonifier::core<abc_in_order_partial_test<value_type_new>> {
	using value_type				 = abc_in_order_partial_test<value_type_new>;
	static constexpr auto parseValue = createValue<&value_type::a, &value_type::z>();
};

template<typename value_type_new> struct jsonifier::core<abc_out_of_order_test<value_type_new>> {
	using value_type				 = abc_out_of_order_test<value_type_new>;
	static constexpr auto parseValue = createValue<&value_type::z, &value_type::y, &value_type::x, &value_type::w, &value_type::v, &value_type::u, &value_type::t, &value_type::s,
		&value_type::r, &value_type::q, &value_type::p, &value_type::o, &value_type::n, &value_type::m, &value_type::l, &value_type::k, &value_type::j, &value_type::i,
		&value_type::h, &value_type::g, &value_type::f, &value_type::e, &value_type::d, &value_type::c, &value_type::b, &value_type::a>();
};
