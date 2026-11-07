/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/instruments_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_instruments_tests(test_registry& registry) {
		run_tests_pair<"Instruments Test", instruments_message>(registry);
	}

	void run_instruments_small_tests(test_registry& registry) {
		run_tests_pair<"Instruments Small Test", instruments_message>(registry);
	}

}
