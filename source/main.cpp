// MIT License @ /License.md
// Copyright (c) 2026 Nihilai Collective Corp
// https://github.com/nihilai-collective/json-performance
// source/main.cpp

#include "tests.hpp"

int32_t main() {
	try {
		return tests::test_function();
	} catch (std::runtime_error& error) {
		std::cout << error.what() << std::endl;
	} catch (std::out_of_range& error) {
		std::cout << error.what() << std::endl;
	}
	return 0;
};