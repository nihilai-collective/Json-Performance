// MIT License @ /License.md
// Copyright (c) 2026 Nihilai Collective Corp
// https://github.com/nihilai-collective/json-performance
// source/common.hpp

#pragma once

#include <benchmarksuite>
#include <simdjson.h>
#include <jsonifier>

constexpr benchmarksuite::string_literal current_path{ benchmarksuite::get_current_path_impl() };
constexpr benchmarksuite::string_literal base_path{ BASE_PATH };
constexpr benchmarksuite::string_literal json_path{ base_path + "/json" };
