/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/github_events_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view github_events_tests() {
		return test_registry<json_tests<"Github Events Test", github_events_message>>::view();
	}

	test_suite_view github_events_small_tests() {
		return test_registry<json_tests<"Github Events Small Test", github_events_message>>::view();
	}

}
