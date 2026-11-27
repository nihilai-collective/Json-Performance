# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/common.sh

LEGS_FILE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/legs.json"

leg_names() {
  jq -r '.[].name' "$LEGS_FILE"
}

leg_branch_bases() {
  jq -r '.[].branch_base' "$LEGS_FILE"
}

RATE_LIMIT_FLOOR=100
RETRY_TRIES=5
RETRY_BASE_SECONDS=60

await_rate_budget() {
  local remaining reset wait
  read -r remaining reset < <(gh api rate_limit --jq '.resources.core | "\(.remaining) \(.reset)"' 2>/dev/null) || return 0
  [ "$remaining" -ge "$RATE_LIMIT_FLOOR" ] && return 0
  wait=$(( reset - $(date +%s) + 1 ))
  echo "Only $remaining REST requests left, sleeping ${wait}s until the window resets." >&2
  [ "$wait" -gt 0 ] && sleep "$wait"
  return 0
}

gh_retry() {
  local try
  for try in $(seq 1 "$RETRY_TRIES"); do
    await_rate_budget
    "$@" && return 0
    echo "Try $try of $RETRY_TRIES failed for: $1 $2 $3" >&2
    [ "$try" -lt "$RETRY_TRIES" ] && sleep $(( RETRY_BASE_SECONDS * 2 ** (try - 1) ))
  done
  return 1
}

delete_run() {
  await_rate_budget
  gh run delete "$1" --repo "$GITHUB_REPOSITORY" >/dev/null 2>&1
  local status=$?
  sleep 1
  return $status
}

cancel_run() {
  await_rate_budget
  gh run cancel "$1" --repo "$GITHUB_REPOSITORY" >/dev/null 2>&1
  local status=$?
  sleep 1
  return $status
}

passed_cpu_check() {
  local passed
  passed=$(gh_retry gh run view "$1" --repo "$GITHUB_REPOSITORY" --json jobs     -q '[.jobs[].steps[]? | select(.name == "Reject non-target CPU runners") | .conclusion] | any(. == "success")') || return 1
  [ "$passed" = "true" ]
}

list_leg_runs() {
  gh run list --repo "$GITHUB_REPOSITORY" --workflow Benchmark.yml --branch "$GITHUB_REF_NAME" \
    --event workflow_dispatch --created ">=$1" --limit 1000 --json databaseId,displayTitle,status,conclusion,createdAt
}

filter_leg_runs() {
  jq --arg p "$2 attempt " --arg s " for run $1" \
    '[.[] | select((.displayTitle | startswith($p)) and (.displayTitle | endswith($s)))]'
}
