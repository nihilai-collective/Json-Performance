/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/random_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view random_tests() {
		return test_registry<json_tests<"Random Test", random_message>>::view();
	}

	test_suite_view random_small_tests() {
		return test_registry<json_tests<"Random Small Test", random_message>>::view();
	}

}
