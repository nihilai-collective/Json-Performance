/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/citm_catalog_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	void run_citm_catalog_tests(test_registry& registry) {
		run_tests_pair<"CitmCatalog Test", citm_catalog_message>(registry);
	}

	void run_citm_catalog_small_tests(test_registry& registry) {
		run_tests_pair<"CitmCatalog Small Test", citm_catalog_message>(registry);
	}

}
