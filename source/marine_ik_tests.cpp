/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/marine_ik_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_marine_ik_tests(test_registry& registry) {
		run_tests_pair<"Marine IK Reverse Test", marine_ik_reverse>(registry);
		run_tests_pair<"Marine IK Test", marine_ik>(registry);
	}

	void run_marine_ik_small_tests(test_registry& registry) {
		run_tests_pair<"Marine IK Reverse Small Test", marine_ik_reverse>(registry);
		run_tests_pair<"Marine IK Small Test", marine_ik>(registry);
	}

}
