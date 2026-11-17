/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/apache_builds_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_apache_builds_tests(test_registry& registry) {
		run_tests_pair<"Apache Builds Test", apache_builds_message>(registry);
	}

	void run_apache_builds_small_tests(test_registry& registry) {
		run_tests_pair<"Apache Builds Small Test", apache_builds_message>(registry);
	}

}
