/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/google_maps_response_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view google_maps_response_tests() {
		return test_registry<json_tests<"Google Maps Response Test", google_maps_response_message>>::view();
	}

	test_suite_view google_maps_response_small_tests() {
		return test_registry<json_tests<"Google Maps Response Small Test", google_maps_response_message>>::view();
	}

}
