/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/discord_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view discord_tests() {
		return test_registry<json_tests<"Discord Test", discord_message>>::view();
	}

	test_suite_view discord_small_tests() {
		return test_registry<json_tests<"Discord Small Test", discord_message>>::view();
	}

}
