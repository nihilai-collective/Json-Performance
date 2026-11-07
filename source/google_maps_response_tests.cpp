/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/google_maps_response_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_google_maps_response_tests(test_registry& registry) {
		run_tests_pair<"Google Maps Response Test", google_maps_response_message>(registry);
	}

	void run_google_maps_response_small_tests(test_registry& registry) {
		run_tests_pair<"Google Maps Response Small Test", google_maps_response_message>(registry);
	}

}
