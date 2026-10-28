#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/delete-failed-attempts.sh

set -eo pipefail
source "$(dirname "$0")/common.sh"

START=$(gh run view "$GITHUB_RUN_ID" --repo "$GITHUB_REPOSITORY" --json createdAt -q .createdAt)
runs=$(list_leg_runs "$START")
leg_names | while read -r leg; do
  legRuns=$(echo "$runs" | filter_leg_runs "$GITHUB_RUN_ID" "$leg")
  if [ "$(echo "$legRuns" | jq '[.[] | select(.status == "completed" and .conclusion == "success")] | length')" = "0" ]; then
    echo "$leg never succeeded, keeping its failed attempts."
    continue
  fi
  echo "$legRuns" | jq -r '.[] | select(.status == "completed" and (.conclusion == "failure" or .conclusion == "cancelled")) | .databaseId' |
  while read -r id; do
    gh run delete "$id" --repo "$GITHUB_REPOSITORY" >/dev/null 2>&1 && echo "Deleted failed $leg attempt (run $id)."
  done
done
