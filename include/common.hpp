/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/common.hpp
 */

#pragma once

#include <benchmarksuite>
#include <simdjson.h>
#include <jsonifier>

constexpr benchmarksuite::string_literal current_path{ benchmarksuite::get_current_path_impl() };
constexpr benchmarksuite::string_literal base_path{ BASE_PATH };
constexpr benchmarksuite::string_literal json_path{ base_path + "/json" };

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
