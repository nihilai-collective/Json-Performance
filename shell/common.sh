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

list_leg_runs() {
  gh run list --repo "$GITHUB_REPOSITORY" --workflow Benchmark.yml --branch "$GITHUB_REF_NAME" \
    --event workflow_dispatch --created ">=$1" --limit 1000 --json databaseId,displayTitle,status,conclusion,createdAt
}

filter_leg_runs() {
  jq --arg p "$2 attempt " --arg s " for run $1" \
    '[.[] | select((.displayTitle | startswith($p)) and (.displayTitle | endswith($s)))]'
}
