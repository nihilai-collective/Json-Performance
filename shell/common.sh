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

run_exists() {
  gh run view "$1" --repo "$GITHUB_REPOSITORY" --json databaseId >/dev/null 2>&1
}

act_on_run() {
  local verb=$1 past=$2 id=$3 label=$4
  if gh run "$verb" "$id" --repo "$GITHUB_REPOSITORY" >/dev/null 2>&1; then
    echo "$past $label (run $id)."
  elif ! run_exists "$id"; then
    echo "Run $id ($label) no longer exists, skipping."
  else
    echo "Could not $verb $label (run $id)." >&2
  fi
  return 0
}

delete_run() {
  act_on_run delete Deleted "$1" "$2"
}

cancel_run() {
  act_on_run cancel Cancelled "$1" "$2"
}

list_leg_runs() {
  gh run list --repo "$GITHUB_REPOSITORY" --workflow Benchmark.yml --branch "$GITHUB_REF_NAME" \
    --event workflow_dispatch --created ">=$1" --limit 1000 --json databaseId,displayTitle,status,conclusion,createdAt
}

filter_leg_runs() {
  jq --arg p "$2 attempt " --arg s " for run $1" \
    '[.[] | select((.displayTitle | startswith($p)) and (.displayTitle | endswith($s)))]'
}
