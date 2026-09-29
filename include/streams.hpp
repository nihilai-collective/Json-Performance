/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/streams.hpp
 */

#pragma once

#include <citm_catalog.hpp>
#include <google_maps_response.hpp>
#include <instruments.hpp>
#include <random.hpp>
#include <twitter.hpp>
#include <map>

struct amazon_cellphone_row {
	std::string brand;
	double rating;
	uint64_t reviews;
};

struct amazon_brand {
	double cumulative_rating;
	uint64_t reviews_count;
};

struct stream_format_record {
	uint64_t id;
};

template<simdjson_document_or_value simdjson_type> inline void get_value(simdjson_type val_new, amazon_cellphone_row& data_new) {
	size_t index{};
	for (auto value: get_array(val_new)) {
		switch (index) {
			case 1:
				data_new.brand = std::string(std::string_view(value));
				break;
			case 5:
				data_new.rating = double(value);
				break;
			case 7:
				data_new.reviews = uint64_t(value);
				break;
			default:
				break;
		}
		++index;
	}
}

template<generic_document_or_value generic_type> inline void get_value(generic_type val_new, amazon_cellphone_row& data_new) {
	size_t index{};
	for (jsonifier::generic::value value: get_array(val_new)) {
		switch (index) {
			case 1:
				static_cast<void>(value.getString(data_new.brand));
				break;
			case 5:
				static_cast<void>(value.getDouble(data_new.rating));
				break;
			case 7:
				static_cast<void>(value.getUint64(data_new.reviews));
				break;
			default:
				break;
		}
		++index;
	}
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, stream_format_record& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
}

template<> struct jsonifier::core<amazon_cellphone_row> {
	using value_type				 = amazon_cellphone_row;
	static constexpr auto parseValue = createValue<&value_type::brand, &value_type::rating, &value_type::reviews>();
};

template<> struct jsonifier::core<amazon_brand> {
	using value_type				 = amazon_brand;
	static constexpr auto parseValue = createValue<&value_type::cumulative_rating, &value_type::reviews_count>();
};

template<> struct jsonifier::core<stream_format_record> {
	using value_type				 = stream_format_record;
	static constexpr auto parseValue = createValue<&value_type::id>();
};

namespace tests {

	static constexpr size_t stream_batch_size{ 1024 * 1024 };
	static constexpr size_t record_stream_target_bytes{ 4 * 1024 * 1024 };
	static constexpr size_t large_amazon_target_bytes{ 10 * 1024 * 1024 };
	static constexpr size_t stream_formats_target_bytes{ 16 * 1000 * 1000 };

	template<typename record_type_new, bool comma_new, uint64_t skip_new = 0> struct stream_test {
		using record_type = record_type_new;
		static constexpr bool comma{ comma_new };
		static constexpr uint64_t skip{ skip_new };
	};

	template<typename record_type> struct stream_sink {
		std::vector<record_type> records;

		void reset() {
			records.clear();
		}

		record_type& next() {
			return records.emplace_back();
		}

		void commit() {
		}

		const auto& output() const {
			return records;
		}
	};

	template<> struct stream_sink<amazon_cellphone_row> {
		std::map<std::string, amazon_brand> brands;
		amazon_cellphone_row row;

		void reset() {
			brands.clear();
		}

		amazon_cellphone_row& next() {
			return row;
		}

		void commit() {
			auto found = brands.find(row.brand);
			if (found == brands.end()) {
				brands.emplace(row.brand, amazon_brand{ row.rating * static_cast<double>(row.reviews), row.reviews });
			} else {
				found->second.cumulative_rating += row.rating * static_cast<double>(row.reviews);
				found->second.reviews_count += row.reviews;
			}
		}

		const auto& output() const {
			return brands;
		}
	};

	template<> struct stream_sink<stream_format_record> {
		stream_format_record record;
		uint64_t sum;

		void reset() {
			sum = 0;
		}

		stream_format_record& next() {
			return record;
		}

		void commit() {
			sum += record.id;
		}

		const auto& output() const {
			return sum;
		}
	};

	struct stream_input {
		std::string json;
	};

	inline stream_input load_stream_input(std::string_view test_name, size_t target_bytes, bool comma, bool skip_header = false) {
		const std::string sample{ benchmarksuite::file_handle::get(std::string{ json_path.operator std::string_view() } + "/" + std::string{ test_name } + (comma ? ".json" : ".ndjson")) };
		const std::string repeat{ skip_header ? sample.substr(sample.find('\n') + 1) : sample };
		std::string out{ sample };
		while (out.size() < target_bytes) {
			if (comma) {
				out += ',';
			}
			out += repeat;
		}
		out.reserve(out.size() + simdjson::SIMDJSON_PADDING);
		return stream_input{ std::move(out) };
	}

}
