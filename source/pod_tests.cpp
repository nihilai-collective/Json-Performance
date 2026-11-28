/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/pod_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view pod_test_suite() {
		return test_registry<pod_tests<"Bool Test", bool>, pod_tests<"Double Test", double>, pod_tests<"Int64 Test", int64_t>, pod_tests<"String Test", std::string>,
			pod_tests<"Uint64 Test", uint64_t>>::view();
	}

}
