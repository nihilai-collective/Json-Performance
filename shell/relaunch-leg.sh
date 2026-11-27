#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/relaunch-leg.sh <leg> <attempt> <parent_run_id> <sha>

set -eo pipefail

awaitStatus=$(gh run view "$3" --repo "$GITHUB_REPOSITORY" --json jobs -q '.jobs[] | select(.name == "Await-Legs") | .status') || awaitStatus=unknown
if [ "$awaitStatus" = "completed" ]; then
  echo "Parent run $3 is no longer awaiting legs, so $1 will not be relaunched."
  exit 0
fi
bash "$(dirname "$0")/dispatch-leg.sh" "$1" $(( $2 + 1 )) "$3" "$4"
