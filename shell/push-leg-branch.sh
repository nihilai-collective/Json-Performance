#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/push-leg-branch.sh

set -eo pipefail

if [ "$COMPILER" != "msvc" ]; then SUDO="sudo"; else SUDO=""; fi
$SUDO git config --global user.email "40668522+RealTimeChris@users.noreply.github.com"
$SUDO git config --global user.name "RealTimeChris"
$SUDO git checkout -b "$BRANCH_NAME"
$SUDO git add .
$SUDO git commit -m "$COMMIT_MSG"
$SUDO git push -f "https://${GITHUB_TOKEN}@github.com/nihilai-collective/Json-Performance.git" "$BRANCH_NAME"
