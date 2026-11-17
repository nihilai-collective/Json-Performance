/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * source/main.cpp
 */

#include <tests.hpp>

int32_t main(int32_t argc, char** argv) {
	try {
		tests::test_function(tests::test_selection{ argc, argv });
	} catch (std::exception& error) {
		std::cout << "Error: " << error.what() << std::endl;
		return 1;
	} 
	return 0;
};