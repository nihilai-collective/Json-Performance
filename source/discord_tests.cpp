/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/discord_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_discord_tests(test_registry& registry) {
		run_tests_pair<"Discord Test", discord_message>(registry);
	}

	void run_discord_small_tests(test_registry& registry) {
		run_tests_pair<"Discord Small Test", discord_message>(registry);
	}

}
