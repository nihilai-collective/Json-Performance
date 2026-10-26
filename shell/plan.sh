#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/plan.sh

set -eo pipefail
source "$(dirname "$0")/common.sh"

echo "configs=$(jq -c --arg leg "$LEG" 'map(select(.name == $leg))' "$LEGS_FILE")" >> "$GITHUB_OUTPUT"
echo "legs=$(jq -c 'map(.name)' "$LEGS_FILE")" >> "$GITHUB_OUTPUT"
