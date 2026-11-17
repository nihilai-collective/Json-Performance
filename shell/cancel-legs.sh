#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/cancel-legs.sh

set -eo pipefail
source "$(dirname "$0")/common.sh"

START=$(gh_retry gh run view "$GITHUB_RUN_ID" --repo "$GITHUB_REPOSITORY" --json createdAt -q .createdAt)
runs=$(gh_retry list_leg_runs "$START")
leg_names | while read -r leg; do
  echo "$runs" | filter_leg_runs "$GITHUB_RUN_ID" "$leg" | jq -r '.[] | select(.status != "completed") | .databaseId' |
  while read -r id; do
    cancel_run "$id" && echo "Cancelled $leg attempt (run $id)."
  done
done
