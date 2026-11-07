#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/merge-branches.sh

set -eo pipefail
source "$(dirname "$0")/common.sh"

mapfile -t BASES < <(leg_branch_bases)
RUN_TAG="${GITHUB_RUN_ID}-${GITHUB_RUN_ATTEMPT}"

sudo git config --global user.email "40668522+RealTimeChris@users.noreply.github.com"
sudo git config --global user.name "RealTimeChris"
sudo git fetch origin
sudo git checkout "$GITHUB_SHA"
for base in "${BASES[@]}"; do
  latest=$(git branch -r --list "origin/$base-${GITHUB_RUN_ID}-*" | sed 's/^ *//' | sort -V | tail -n 1)
  if [ -z "$latest" ]; then
    echo "No branch found for $base-${GITHUB_RUN_ID}" >&2
    exit 1
  fi
  sudo git merge "$latest" --no-ff
done
sudo git checkout --orphan newBranch
sudo git add .
sudo git commit -m "First commit."
sudo git branch -m "generic-parsing-$RUN_TAG"
sudo git push origin "generic-parsing-$RUN_TAG" -f
