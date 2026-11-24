/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/apache_builds_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view apache_builds_tests() {
		return test_registry<json_tests<"Apache Builds Test", apache_builds_message>>::view();
	}

	test_suite_view apache_builds_small_tests() {
		return test_registry<json_tests<"Apache Builds Small Test", apache_builds_message>>::view();
	}

}
