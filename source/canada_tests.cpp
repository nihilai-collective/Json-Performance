/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/canada_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view canada_tests() {
		return test_registry<json_tests<"Canada Test", canada_message>>::view();
	}

	test_suite_view canada_small_tests() {
		return test_registry<json_tests<"Canada Small Test", canada_message>>::view();
	}

}
