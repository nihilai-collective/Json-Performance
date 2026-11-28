#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/prune-leg-attempts.sh <leg> <parent_run_id>

set -eo pipefail
source "$(dirname "$0")/common.sh"

START=$(gh_retry gh run view "$2" --repo "$GITHUB_REPOSITORY" --json createdAt -q .createdAt)
runs=$(gh_retry list_leg_runs "$START")
echo "$runs" | filter_leg_runs "$2" "$1" |
  jq -r '[.[] | select(.status == "completed" and (.conclusion == "failure" or .conclusion == "cancelled"))] | sort_by(.createdAt) | .[:-1][] | .databaseId' | tr -d '\r' |
  while read -r id; do
    delete_run "$id" && echo "Deleted older failed $1 attempt (run $id)."
  done
