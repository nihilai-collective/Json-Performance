#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/dispatch-leg.sh <leg> <attempt> <parent_run_id> <sha>

set -eo pipefail

for try in 1 2 3 4 5; do
  gh workflow run Benchmark.yml \
    --repo "$GITHUB_REPOSITORY" \
    --ref "$GITHUB_REF_NAME" \
    -f leg="$1" \
    -f attempt="$2" \
    -f parent_run_id="$3" \
    -f sha="$4" && exit 0
  echo "Dispatch try $try failed, retrying." >&2
  sleep $(( try * 10 ))
done
exit 1
