param(
    [Parameter(Mandatory = $false)]
    [string]$KeyPath = "$env:USERPROFILE\downloads\NihilusKey.pem",
    [Parameter(Mandatory = $false)]
    [string]$RemoteHost = "ubuntu@18.217.89.240",
    [Parameter(Mandatory = $false)]
    [string]$RemoteRoot = "/var/www/html/csv-data"
)
$ErrorActionPreference = "Stop"
$projects = [ordered]@{
    "jsonifier"       = [ordered]@{ displayName = "Jsonifier";       primaryLibs = @("jsonifier");                    branches = @("main", "stage-1-parsing-main", "stage-1-parsing-avx512-main", "full-parsing-utf8-main") }
    "void-numerics"   = [ordered]@{ displayName = "void-numerics";   primaryLibs = @("vn::to_chars", "vn::from_chars"); branches = @("main") }
    "rtc-digit-count" = [ordered]@{ displayName = "rtc-digit-count"; primaryLibs = @("rtc_digit_count");        branches = @("main") }
}
Write-Host "Pulling per-project stats.json to build summary.json..."
$summaryProjects = [ordered]@{}
foreach ($projectKey in $projects.Keys) {
    $totalWins = 0
    $totalTies = 0
    $totalLosses = 0
    $anyFound = $false
    $latestGeneratedAt = $null
    $projectBranches = $projects[$projectKey].branches
    foreach ($branch in $projectBranches) {
        $remotePath = "$RemoteRoot/$projectKey/$branch/stats.json"
        $tempPath = Join-Path $env:TEMP "summary-fetch-$projectKey-$branch.json"
        Write-Host "  Fetching $projectKey / $branch..."
        try {
            scp -i $KeyPath "${RemoteHost}:${remotePath}" $tempPath 2>$null
        } catch {
            Write-Warning "  Could not fetch stats.json for '$projectKey' / '$branch' - skipping."
            continue
        }
        if (-not (Test-Path $tempPath)) {
            Write-Warning "  No stats.json found on server for '$projectKey' / '$branch' - skipping."
            continue
        }
        $projectStats = Get-Content -LiteralPath $tempPath -Raw | ConvertFrom-Json
        Remove-Item $tempPath -Force
        $primaryLibs = $projects[$projectKey].primaryLibs
        $foundAnyLibThisBranch = $false
        foreach ($primaryLib in $primaryLibs) {
            $primaryStats = $projectStats.summary.$primaryLib
            if (-not $primaryStats) {
                Write-Warning "  No '$primaryLib' entry in summary for '$projectKey' / '$branch'."
                continue
            }
            $totalWins   += $primaryStats.wins
            $totalTies   += $primaryStats.ties
            $totalLosses += $primaryStats.losses
            $foundAnyLibThisBranch = $true
        }
        if (-not $foundAnyLibThisBranch) {
            Write-Warning "  None of the expected primary libs ($($primaryLibs -join ', ')) found for '$projectKey' / '$branch' - skipping this branch's totals."
            continue
        }
        $anyFound = $true
        if (-not $latestGeneratedAt -or $projectStats.generatedAt -gt $latestGeneratedAt) {
            $latestGeneratedAt = $projectStats.generatedAt
        }
    }
    if (-not $anyFound) {
        Write-Warning "No branches found at all for '$projectKey' - omitting from summary.json."
        continue
    }
    $summaryProjects[$projectKey] = [ordered]@{
        displayName = $projects[$projectKey].displayName
        primaryLibs = $projects[$projectKey].primaryLibs
        branches    = $projectBranches
        summary     = [ordered]@{
            wins   = $totalWins
            ties   = $totalTies
            losses = $totalLosses
        }
        generatedAt = $latestGeneratedAt
    }
}
$summary = [ordered]@{
    generatedAt = (Get-Date).ToUniversalTime().ToString("o")
    projects    = $summaryProjects
}
$summaryJson = ConvertTo-Json -InputObject $summary -Depth 8
$utf8NoBom = New-Object System.Text.UTF8Encoding($false)
$localSummaryPath = Join-Path $env:TEMP "summary.json"
[System.IO.File]::WriteAllText($localSummaryPath, $summaryJson, $utf8NoBom)
Write-Host "Uploading summary.json to $RemoteRoot/summary.json..."
scp -i $KeyPath $localSummaryPath "${RemoteHost}:${RemoteRoot}/summary.json"
Remove-Item $localSummaryPath -Force
Write-Host "Done. summary.json published with $($summaryProjects.Keys.Count) project(s)."