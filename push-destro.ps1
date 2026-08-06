<#
.SYNOPSIS
    Mirrors every branch of the current repo into ../jp as fresh,
    single-commit orphan branches, force-pushed to origin.
    Pure git - no robocopy, no working-tree copying, no silent hangs.

.DESCRIPTION
    For each branch B in the source repo:
      1. Uses `git archive` to export B's exact tree as a tarball
         (this is atomic and never touches the working directory).
      2. In ../jp: wipes any existing branch B, creates a fresh orphan
         branch, extracts the tarball on top of a clean empty tree,
         commits once, force-pushes to origin.

    This never leaves things half-copied - git archive either succeeds
    completely or fails loudly, so there's no possibility of a silent
    partial mirror like robocopy could produce.

.NOTES
    Run from INSIDE the source repo. ../jp must already exist as a
    git repo with an 'origin' remote.
#>

param(
    [switch]$IncludeRemoteBranches
)

$ErrorActionPreference = "Stop"

function Write-Step($msg) {
    Write-Host ""
    Write-Host "==> $msg" -ForegroundColor Cyan
}

$sourceRepo = (Get-Location).Path
$targetRepo = (Resolve-Path (Join-Path $sourceRepo "..\jp")).Path

Write-Host "Source repo: $sourceRepo" -ForegroundColor Yellow
Write-Host "Target repo: $targetRepo" -ForegroundColor Yellow

Push-Location $sourceRepo
git rev-parse --is-inside-work-tree *> $null
if ($LASTEXITCODE -ne 0) { throw "Source repo is not a git repository." }

$dirtyCheck = git status --porcelain
if ($dirtyCheck) { throw "Source repo has uncommitted changes. Commit, stash, or discard them first." }
Pop-Location

Push-Location $targetRepo
git rev-parse --is-inside-work-tree *> $null
if ($LASTEXITCODE -ne 0) { throw "Target repo (../jp) is not a git repository." }
$targetHasOrigin = (git remote) -contains "origin"
Pop-Location
if (-not $targetHasOrigin) { throw "Target repo ../jp has no 'origin' remote configured." }

Push-Location $sourceRepo

$localBranches = git for-each-ref --format="%(refname:short)" refs/heads/ | Where-Object { $_.Trim() -ne "" }
$branches = @($localBranches)

if ($IncludeRemoteBranches) {
    $remoteBranches = git for-each-ref --format="%(refname:short)" refs/remotes/ |
        Where-Object { $_ -and $_ -notmatch "/HEAD$" } |
        ForEach-Object { ($_ -split "/", 2)[1] }
    $branches = @($branches + $remoteBranches) | Select-Object -Unique
}

if ($branches.Count -eq 0) { throw "No branches found in source repo." }

Write-Host ""
Write-Host "Branches to mirror ($($branches.Count)):" -ForegroundColor Yellow
$branches | ForEach-Object { Write-Host "  - $_" }

$tempRoot = Join-Path $env:TEMP "branch-mirror-$(Get-Random)"
New-Item -ItemType Directory -Path $tempRoot -Force *> $null

$succeeded = @()
$failed = @()

foreach ($branch in $branches) {
    Write-Step "Mirroring branch: $branch"

    $archivePath = Join-Path $tempRoot "$($branch -replace '[\\/]','_').tar"
    $extractPath = Join-Path $tempRoot "extract-$($branch -replace '[\\/]','_')"

    try {
        Write-Host "  Archiving '$branch' from source repo..."
        git archive --format=tar --output="$archivePath" $branch
        if ($LASTEXITCODE -ne 0) { throw "git archive failed for branch '$branch'." }

        $fileCount = (tar -tf $archivePath | Measure-Object).Count
        Write-Host "  Archive contains $fileCount entries."
        if ($fileCount -eq 0) { throw "Archive for branch '$branch' is empty - refusing to push an empty snapshot." }

        New-Item -ItemType Directory -Path $extractPath -Force *> $null
        tar -xf $archivePath -C $extractPath
        if ($LASTEXITCODE -ne 0) { throw "Failed to extract archive for branch '$branch'." }

        Pop-Location
        Push-Location $targetRepo

        $existingBranch = git for-each-ref --format="%(refname:short)" "refs/heads/$branch"
        $prevEap = $ErrorActionPreference
        $ErrorActionPreference = "Continue"

        if ($existingBranch) { git branch -D $branch 2>&1 | Out-Null }

        git checkout --orphan $branch 2>&1 | Out-Null
        $checkoutExit = $LASTEXITCODE

        git rm -rf --quiet . 2>&1 | Out-Null

        $ErrorActionPreference = $prevEap

        if ($checkoutExit -ne 0) { throw "Failed to create orphan branch '$branch' in target repo." }

        Get-ChildItem -Path $extractPath -Force | ForEach-Object {
            Copy-Item -Path $_.FullName -Destination $targetRepo -Recurse -Force
        }

        git add -A
        $stagedCount = (git diff --cached --name-only | Measure-Object).Count
        if ($stagedCount -eq 0) { throw "Nothing staged for branch '$branch' - refusing to commit empty." }

        git commit --quiet -m "Snapshot of '$branch' from source repo ($fileCount files)"
        if ($LASTEXITCODE -ne 0) { throw "Commit failed for branch '$branch'." }

        git push --force origin "$branch`:$branch"
        if ($LASTEXITCODE -ne 0) { throw "Force-push failed for branch '$branch'." }

        Pop-Location
        Push-Location $sourceRepo

        Write-Host "  Done: $branch ($fileCount files, $stagedCount staged)" -ForegroundColor Green
        $succeeded += $branch
    }
    catch {
        Write-Host "  FAILED: $branch - $($_.Exception.Message)" -ForegroundColor Red
        $failed += $branch
        if ((Get-Location).Path -ne $sourceRepo) {
            Pop-Location
            Push-Location $sourceRepo
        }
    }
}

Pop-Location

Remove-Item -Path $tempRoot -Recurse -Force -ErrorAction SilentlyContinue

Write-Host ""
Write-Host "=================================================" -ForegroundColor Cyan
Write-Host "Summary" -ForegroundColor Cyan
Write-Host "  Succeeded: $($succeeded.Count)" -ForegroundColor Green
$succeeded | ForEach-Object { Write-Host "    - $_" -ForegroundColor Green }
if ($failed.Count -gt 0) {
    Write-Host "  Failed: $($failed.Count)" -ForegroundColor Red
    $failed | ForEach-Object { Write-Host "    - $_" -ForegroundColor Red }
}
Write-Host "=================================================" -ForegroundColor Cyan