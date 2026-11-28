/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/text_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view text_test_suite() {
		return test_registry<raw_test<test_types::minify, "Minify Test", minify_libraries>>::view();
	}

}
