/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/random_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_random_tests(test_registry& registry) {
		run_tests_pair<"Random Test", random_message>(registry);
	}

	void run_random_small_tests(test_registry& registry) {
		run_tests_pair<"Random Small Test", random_message>(registry);
	}

}
