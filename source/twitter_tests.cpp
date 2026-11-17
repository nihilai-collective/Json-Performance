/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/twitter_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_twitter_tests(test_registry& registry) {
		run_parse_tests<"Twitter Partial Test", twitter_partial_message>(registry);
		run_tests_pair<"Twitter Test", twitter_message>(registry);
	}

	void run_twitter_small_tests(test_registry& registry) {
		run_parse_tests<"Twitter Partial Small Test", twitter_partial_message>(registry);
		run_tests_pair<"Twitter Small Test", twitter_message>(registry);
	}

}
