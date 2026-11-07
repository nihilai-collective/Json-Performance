/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/canada_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_canada_tests(test_registry& registry) {
		run_tests_pair<"Canada Test", canada_message>(registry);
	}

	void run_canada_small_tests(test_registry& registry) {
		run_tests_pair<"Canada Small Test", canada_message>(registry);
	}

}
