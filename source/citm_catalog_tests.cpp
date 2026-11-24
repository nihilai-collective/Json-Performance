/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/citm_catalog_tests.cpp
 */

#include <tests.hpp>

namespace tests {

	test_suite_view citm_catalog_tests() {
		return test_registry<json_tests<"CitmCatalog Test", citm_catalog_message>>::view();
	}

	test_suite_view citm_catalog_small_tests() {
		return test_registry<json_tests<"CitmCatalog Small Test", citm_catalog_message>>::view();
	}

}
