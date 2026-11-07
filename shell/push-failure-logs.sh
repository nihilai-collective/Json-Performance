#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/push-failure-logs.sh

set -o pipefail

LOG_BRANCH="failure-logs-${BRANCH_NAME}"
LOG_DIR="$(mktemp -d)"

{
  echo "Run: $GITHUB_SERVER_URL/$GITHUB_REPOSITORY/actions/runs/$GITHUB_RUN_ID"
  echo "Attempt: $ATTEMPT"
  echo "Sha: $SHA"
  date -u
} > "$LOG_DIR/info.txt"
for LOG in build.log run.log; do
  [ -f "$RUNNER_TEMP/$LOG" ] && cp "$RUNNER_TEMP/$LOG" "$LOG_DIR/$LOG"
done

set -e
cd "$LOG_DIR"
git init -q -b "$LOG_BRANCH"
git config user.email "40668522+RealTimeChris@users.noreply.github.com"
git config user.name "RealTimeChris"
git add .
git commit -q -m "Failure logs for $BRANCH_NAME"
git push -f "https://x-access-token:${GITHUB_TOKEN}@github.com/nihilai-collective/Json-Performance.git" "$LOG_BRANCH"
echo "Failure logs pushed to branch $LOG_BRANCH"
