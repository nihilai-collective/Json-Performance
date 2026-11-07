#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/await-legs.sh

set -eo pipefail
source "$(dirname "$0")/common.sh"

declare -A BASES=()
while IFS=$'\t' read -r name base; do
  BASES["$name"]=$base
done < <(jq -r '.[] | [.name, .branch_base] | @tsv' "$LEGS_FILE")
declare -A IDLE_POLLS=()
START=$(date -u -d '-10 minutes' +%Y-%m-%dT%H:%M:%SZ)

prune_failed_attempts() {
  for leg in "${!BASES[@]}"; do
    echo "$runs" | filter_leg_runs "$GITHUB_RUN_ID" "$leg" |
      jq -r '[.[] | select(.status == "completed" and (.conclusion == "failure" or .conclusion == "cancelled"))] | sort_by(.createdAt) | .[:-1][] | .databaseId' |
    while read -r id; do
      gh run delete "$id" --repo "$GITHUB_REPOSITORY" >/dev/null 2>&1 && echo "Deleted older failed $leg attempt (run $id)."
    done
  done
}

while true; do
  pending=0
  runs=$(list_leg_runs "$START") || { sleep 30; continue; }
  prune_failed_attempts
  for leg in "${!BASES[@]}"; do
    if [ -n "$(git ls-remote --heads "https://x-access-token:${GH_TOKEN}@github.com/${GITHUB_REPOSITORY}.git" "refs/heads/${BASES[$leg]}-${GITHUB_RUN_ID}-*")" ]; then
      continue
    fi
    pending=1
    active=$(echo "$runs" | filter_leg_runs "$GITHUB_RUN_ID" "$leg" | jq '[.[] | select(.status != "completed")] | length')
    if [ "$active" != "0" ]; then
      IDLE_POLLS[$leg]=0
      continue
    fi
    IDLE_POLLS[$leg]=$(( ${IDLE_POLLS[$leg]:-0} + 1 ))
    if [ "${IDLE_POLLS[$leg]}" -ge 6 ]; then
      echo "$leg has no queued or running attempt and no temp branch, so its retry chain has ended." >&2
      exit 1
    fi
  done
  [ "$pending" = "0" ] && break
  sleep 30
done
