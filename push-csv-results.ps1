param(
    [Parameter(Mandatory = $false)]
    [string]$Project,

    [Parameter(Mandatory = $false)]
    [ValidateSet("main", "stage-1-parsing-main", "full-parsing-utf8-main", "correctness-validation-main")]
    [string]$Branch,

    [Parameter(Mandatory = $false)]
    [string]$CsvPath = ".\csv",

    [Parameter(Mandatory = $false)]
    [string]$RepoRoot = ".",

    [Parameter(Mandatory = $false)]
    [string[]]$CorrectnessFiles = @(
        "macOS-Clang.md",
        "macOS-GCC.md",
        "Linux-Clang.md",
        "Linux-GCC.md",
        "Windows-MSVC.md"
    ),

    [Parameter(Mandatory = $false)]
    [string]$KeyPath = "$env:USERPROFILE\downloads\NihilusKey.pem",

    [Parameter(Mandatory = $false)]
    [string]$RemoteHost = "ubuntu@18.217.89.240",

    [Parameter(Mandatory = $false)]
    [string]$RemoteRoot = "/var/www/html/csv-data"
)

$ErrorActionPreference = "Stop"

Import-Module (Join-Path $PSScriptRoot "Aggregate-Stats.psm1") -Force

if (-not (Test-Path $KeyPath)) {
    Write-Error "SSH key not found at '$KeyPath'. Pass -KeyPath explicitly if it's somewhere else."
    exit 1
}

if (-not $Project) {

    $folderName = Split-Path -Leaf (Resolve-Path $RepoRoot)

    $repoToProjectMap = @{
        "json-performance"     = "jsonifier"
        "stringint-benchmarks" = "void-numerics"
        "rtc-digit-count"      = "rtc-digit-count"
    }

    if ($repoToProjectMap.ContainsKey($folderName)) {
        $Project = $repoToProjectMap[$folderName]
        Write-Host "Auto-detected project from folder name '$folderName': $Project"
    } else {
        $validNames = $repoToProjectMap.Keys -join ', '
        Write-Error "Folder name '$folderName' does not match a known repo ($validNames). Pass -Project explicitly to override."
        exit 1
    }

} else {
    Write-Host "Using explicitly provided project: $Project"
}

if (-not $Branch) {

    $gitDir = Join-Path $RepoRoot ".git"
    if (-not (Test-Path $gitDir)) {
        Write-Error "No .git folder found under '$RepoRoot' and -Branch was not supplied. Either run this from inside the repo, pass -RepoRoot, or pass -Branch explicitly."
        exit 1
    }

    $headPath = Join-Path $gitDir "HEAD"
    if (-not (Test-Path $headPath)) {
        Write-Error "Found '$gitDir' but no HEAD file inside it - is this a valid git repo?"
        exit 1
    }

    $headContent = Get-Content $headPath -Raw

    if ($headContent -match '^ref:\s*refs/heads/(.+?)\s*$') {
        $detectedBranch = $Matches[1]
    } else {
        Write-Error "HEAD is detached (not pointing at a branch ref). Checked out a commit directly? Pass -Branch explicitly."
        exit 1
    }

    $validBranches = @("main", "stage-1-parsing-main", "full-parsing-utf8-main", "correctness-validation-main")
    if ($validBranches -notcontains $detectedBranch) {
        Write-Error "Detected git branch '$detectedBranch' is not one of the valid options ($($validBranches -join ', ')). Checkout the right branch, or pass -Branch explicitly to override."
        exit 1
    }

    $Branch = $detectedBranch
    Write-Host "Auto-detected branch from .git: $Branch"

} else {
    Write-Host "Using explicitly provided branch: $Branch"
}

if ($Branch -eq "correctness-validation-main") {

    Write-Host "Pushing correctness-validation-main .md files..."

    $correctnessRemoteDir = "$RemoteRoot/$Project/correctness-validation-main"
    $missing = @()
    $foundFiles = @()

    foreach ($fileName in $CorrectnessFiles) {
        $localFilePath = Join-Path $RepoRoot $fileName
        if (Test-Path $localFilePath) {
            $foundFiles += $localFilePath
        } else {
            $missing += $fileName
        }
    }

    if ($missing.Count -gt 0) {
        Write-Warning "Missing correctness files (skipped): $($missing -join ', ')"
    }

    if ($foundFiles.Count -eq 0) {
        Write-Error "No correctness .md files found under '$RepoRoot' - nothing to push."
        exit 1
    }

    Write-Host "Ensuring remote directory '$correctnessRemoteDir' exists..."
    ssh -i $KeyPath $RemoteHost "mkdir -p '$correctnessRemoteDir'"

    foreach ($filePath in $foundFiles) {
        $fileName = Split-Path $filePath -Leaf
        Write-Host "  Uploading $fileName..."
        scp -i $KeyPath $filePath "${RemoteHost}:${correctnessRemoteDir}/$fileName"
    }

    Write-Host "Done. $($foundFiles.Count) correctness file(s) pushed to $RemoteHost`:$correctnessRemoteDir"

} else {

    if (-not (Test-Path $CsvPath)) {
        Write-Error "CSV folder not found at '$CsvPath'. Run this from the repo root, or pass -CsvPath explicitly."
        exit 1
    }

    Write-Host "Aggregating stats.json for project '$Project' / branch '$Branch'..."

    $statsOutputPath = Join-Path $CsvPath "stats.json"
    $aggregationSucceeded = Write-LibraryStatsJson -Project $Project -Branch $Branch -CsvPath $CsvPath -OutputPath $statsOutputPath

    if (-not $aggregationSucceeded) {
        Write-Error "Stats aggregation failed - aborting before upload."
        exit 1
    }

    $remoteDir = "$RemoteRoot/$Project/$Branch"
    $tarName   = "csv-push-$Project-$Branch-$(Get-Date -Format 'yyyyMMdd-HHmmss').tar.gz"
    $tarPath   = Join-Path $env:TEMP $tarName

    Write-Host "Packing '$CsvPath' into '$tarPath'..."

    tar -czf $tarPath -C $CsvPath .

    if (-not (Test-Path $tarPath)) {
        Write-Error "Tar creation failed - '$tarPath' was not produced."
        exit 1
    }

    Write-Host "Ensuring remote directory '$remoteDir' exists..."
    ssh -i $KeyPath $RemoteHost "mkdir -p '$remoteDir'"

    Write-Host "Uploading archive to server..."
    $remoteTarPath = "/tmp/$tarName"
    scp -i $KeyPath $tarPath "${RemoteHost}:${remoteTarPath}"

    Write-Host "Extracting on server into '$remoteDir'..."
    ssh -i $KeyPath $RemoteHost "rm -rf '$remoteDir' && mkdir -p '$remoteDir' && tar -xzf '$remoteTarPath' -C '$remoteDir'"
    ssh -i $KeyPath $RemoteHost "rm -f '$remoteTarPath'"

    Write-Host "Cleaning up local temp archive..."
    Remove-Item $tarPath -Force

    Write-Host "Done. '$CsvPath' (including stats.json) pushed to $RemoteHost`:$remoteDir"
}