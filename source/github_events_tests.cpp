/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/github_events_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_github_events_tests(test_registry& registry) {
		run_tests_pair<"Github Events Test", github_events_message>(registry);
	}

	void run_github_events_small_tests(test_registry& registry) {
		run_tests_pair<"Github Events Small Test", github_events_message>(registry);
	}

}
