/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/marine_ik_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view marine_ik_tests() {
		return test_registry<json_tests<"Marine IK Reverse Test", marine_ik_reverse>, json_tests<"Marine IK Test", marine_ik>>::view();
	}

	test_suite_view marine_ik_small_tests() {
		return test_registry<json_tests<"Marine IK Reverse Small Test", marine_ik_reverse>, json_tests<"Marine IK Small Test", marine_ik>>::view();
	}

}
