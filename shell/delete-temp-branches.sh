#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/delete-temp-branches.sh

set -eo pipefail
source "$(dirname "$0")/common.sh"

sudo git fetch origin
leg_branch_bases | while read -r base; do
  for branch in $(git branch -r --list "origin/$base-${GITHUB_RUN_ID}-*" | sed 's#^ *origin/##'); do
    sudo git push origin --delete "$branch" || true
  done
done
