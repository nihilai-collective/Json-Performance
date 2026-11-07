/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/pod_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_pod_test_suite(test_registry& registry) {
		run_pod_tests<"Bool Test", bool, true>(registry);
		run_pod_tests<"Double Test", double, true>(registry);
		run_pod_tests<"Int64 Test", int64_t, true>(registry);
		run_pod_tests<"String Test", std::string, true>(registry);
		run_pod_tests<"Uint64 Test", uint64_t, true>(registry);
	}

}
