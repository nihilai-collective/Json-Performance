/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/twitter_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view twitter_tests() {
		return test_registry<json_tests<"Twitter Partial Test", twitter_partial_message, test_flags::read>, json_tests<"Twitter Test", twitter_message>>::view();
	}

	test_suite_view twitter_small_tests() {
		return test_registry<json_tests<"Twitter Partial Small Test", twitter_partial_message, test_flags::read>, json_tests<"Twitter Small Test", twitter_message>>::view();
	}

}
