function Read-CsvWithHeaderComments {
    param([Parameter(Mandatory = $true)][string]$Path)

    $rawLines = Get-Content -LiteralPath $Path
    $meta = [ordered]@{}
    $dataStartIdx = -1

    for ($i = 0; $i -lt $rawLines.Count; $i++) {
        $line = $rawLines[$i]

        if ($line -match '^#\*{0,2}\s*CPU:\*{0,2}\s*(.+)$') {
            $meta.cpu = $Matches[1].Trim().Trim('*').Trim()
            continue
        }
        if ($line -match '^#\*{0,2}\s*OS:\*{0,2}\s*(.+)$') {
            $meta.os = $Matches[1].Trim().Trim('*').Trim()
            continue
        }
        if ($line -match '^#\*{0,2}\s*Compiler:\*{0,2}\s*(.+)$') {
            $meta.compiler = $Matches[1].Trim().Trim('*').Trim()
            continue
        }
        if ($line -match '^#') {
            continue
        }

        $dataStartIdx = $i
        break
    }

    if ($dataStartIdx -eq -1) {
        return [ordered]@{ meta = $meta; rows = @() }
    }

    $csvLines = $rawLines[$dataStartIdx..($rawLines.Count - 1)]
    $rows = $csvLines | ConvertFrom-Csv

    return [ordered]@{ meta = $meta; rows = $rows }
}

function Read-HarnessConfig {
    param([Parameter(Mandatory = $true)][string]$Path)

    $rawLines = Get-Content -LiteralPath $Path
    $configHeaderIdx = -1

    for ($i = 0; $i -lt $rawLines.Count; $i++) {
        if ($rawLines[$i] -match '^ClearCpuCachesBeforeIterations,') {
            $configHeaderIdx = $i
            break
        }
    }

    if ($configHeaderIdx -eq -1) {
        return $null
    }

    $configLines = $rawLines[$configHeaderIdx..($configHeaderIdx + 1)]
    $configRow = ($configLines | ConvertFrom-Csv)[0]

    return [ordered]@{
        clearCpuCachesBeforeIterations = [bool]::Parse($configRow.ClearCpuCachesBeforeIterations)
        measuredIterationCount         = [int]$configRow.MeasuredIterationCount
        maxIterationCount              = [int]$configRow.MaxIterationCount
        convergenceThreshold           = [double]$configRow.ConvergenceThreshold
        maxTimeInS                     = [double]$configRow.MaxTimeInS
        rseThreshold                   = [double]$configRow.RseThreshold
        maxK                           = [int]$configRow.MaxK
        minK                           = [int]$configRow.MinK
    }
}

function Read-ResultsCsv {
    param([Parameter(Mandatory = $true)][string]$Path)

    $csvData = Read-CsvWithHeaderComments -Path $Path
    $meta = $csvData.meta

    $rawLines = Get-Content -LiteralPath $Path
    $wtlHeaderIdx = -1

    for ($i = 0; $i -lt $rawLines.Count; $i++) {
        if ($rawLines[$i] -match '^Library,Wins,Ties,Losses') {
            $wtlHeaderIdx = $i
            break
        }
    }

    $wtl = [ordered]@{}
    if ($wtlHeaderIdx -ge 0) {
        $wtlLines = $rawLines[$wtlHeaderIdx..($rawLines.Count - 1)]
        $wtlRows = $wtlLines | ConvertFrom-Csv
        foreach ($row in $wtlRows) {
            $wtl[$row.Library] = [ordered]@{
                wins   = [int]$row.Wins
                ties   = [int]$row.Ties
                losses = [int]$row.Losses
            }
        }
    }

    $harness = Read-HarnessConfig -Path $Path

    return [ordered]@{ meta = $meta; wtl = $wtl; harness = $harness }
}

function Get-VerdictFromPosition {
    param([string]$Position)

    switch -Regex ($Position) {
        '^Win$'  { return 'win' }
        '^Loss$' { return 'loss' }
        '^Tie$'  { return 'tie' }
        default  { return $Position.ToLowerInvariant() }
    }
}

function ConvertTo-TestRow {
    param([Parameter(Mandatory = $true)]$Row)

    return [ordered]@{
        lib           = $Row.Library
        mbps          = [double]$Row.'Throughput (MB/s)'
        rse           = [double]$Row.'RSE (%)'
        windowDuration = $Row.'Window Duration'
        fileSizeBytes = if ($Row.'File Size (Bytes)') { [long]$Row.'File Size (Bytes)' } else { $null }
        windowSamplesK = if ($Row.'Window Samples (k)') { [int]$Row.'Window Samples (k)' } else { $null }
        variance      = if ($Row.Variance) { [double]$Row.Variance } else { $null }
        latencyNs     = if ($Row.'Latency / Run (ns)') { [double]$Row.'Latency / Run (ns)' } else { $null }
        cyclesPerByte = if ($Row.'Cycles/Byte') { [double]$Row.'Cycles/Byte' } else { $null }
        verdict       = Get-VerdictFromPosition -Position $Row.Position
    }
}

function Get-JsonifierTestNameAndParams {
    param([Parameter(Mandatory = $true)][string]$FileBaseName)

    if ($FileBaseName -match '^(.+?)\s+(Read|Write)$') {
        return [ordered]@{
            name   = $Matches[1]
            params = [ordered]@{ operation = $Matches[2].ToLowerInvariant() }
        }
    }

    return [ordered]@{
        name   = $FileBaseName
        params = [ordered]@{}
    }
}

function Get-VoidNumericsTestNameAndParams {
    param([Parameter(Mandatory = $true)][string]$FileBaseName)

    if ($FileBaseName -match '^(int8|int16|int32|int64|uint8|uint16|uint32|uint64)-(mixed-sign|negative|positive)-integer_count\[(\d+)\]$') {
        return [ordered]@{
            name   = $FileBaseName
            params = [ordered]@{
                type  = $Matches[1]
                sign  = $Matches[2]
                count = [int]$Matches[3]
            }
        }
    }

    return [ordered]@{
        name   = $FileBaseName
        params = [ordered]@{}
    }
}

function Get-RtcDigitCountTestNameAndParams {
    param([Parameter(Mandatory = $true)][string]$FileBaseName)

    if ($FileBaseName -match '^(uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t)-integer_count\[(\d+)\]-digit_length\[(\d+-\d+)\]$') {
        return [ordered]@{
            name   = $FileBaseName
            params = [ordered]@{
                intType    = $Matches[1]
                count      = [int]$Matches[2]
                digitLength = $Matches[3]
            }
        }
    }

    if ($FileBaseName -match '^(uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t)-integer_count\[(\d+)\]$') {
        return [ordered]@{
            name   = $FileBaseName
            params = [ordered]@{
                intType = $Matches[1]
                count   = [int]$Matches[2]
            }
        }
    }

    return [ordered]@{
        name   = $FileBaseName
        params = [ordered]@{}
    }
}

$script:ProjectFilenameParsers = @{
    "jsonifier"       = Get-Item Function:Get-JsonifierTestNameAndParams
    "void-numerics"   = Get-Item Function:Get-VoidNumericsTestNameAndParams
    "rtc-digit-count" = Get-Item Function:Get-RtcDigitCountTestNameAndParams
}

function Get-PlatformKeyFromFolderName {
    param([Parameter(Mandatory = $true)][string]$FolderName)

    return $FolderName.ToLowerInvariant() -replace '[^a-z0-9]+', '-'
}

function Build-BenchmarkGroupStats {
    param(
        [Parameter(Mandatory = $true)][string]$Project,
        [Parameter(Mandatory = $true)][string]$GroupDirPath,
        [Parameter(Mandatory = $false)][string]$GroupName = $null
    )

    $parser = $script:ProjectFilenameParsers[$Project]

    $resultsPath = Join-Path $GroupDirPath "Results.csv"
    if (-not (Test-Path -LiteralPath $resultsPath)) {
        return $null
    }

    $resultsData = Read-ResultsCsv -Path $resultsPath

    $testFiles = Get-ChildItem -LiteralPath $GroupDirPath -Filter "*.csv" -File |
        Where-Object { $_.Name -ne "Results.csv" }

    $meta = [ordered]@{}
    if ($resultsData.meta.Count -gt 0) {
        $meta.cpu = $resultsData.meta.cpu
        $meta.os = $resultsData.meta.os
        $meta.compiler = $resultsData.meta.compiler
    }
    $tests = @()

    foreach ($testFile in $testFiles) {
        $fileBaseName = [System.IO.Path]::GetFileNameWithoutExtension($testFile.Name)
        $parsed = & $parser.ScriptBlock -FileBaseName $fileBaseName

        $csvData = Read-CsvWithHeaderComments -Path $testFile.FullName

        if ($meta.Count -eq 0 -and $csvData.meta.Count -gt 0) {
            $meta.cpu = $csvData.meta.cpu
            $meta.os = $csvData.meta.os
            $meta.compiler = $csvData.meta.compiler
        }

        $rows = @()
        foreach ($row in $csvData.rows) {
            $rows += ConvertTo-TestRow -Row $row
        }

        $testParams = $parsed.params
        if ($GroupName) {
            $testParams = [ordered]@{ group = $GroupName }
            foreach ($key in $parsed.params.Keys) {
                $testParams[$key] = $parsed.params[$key]
            }
        }

        $tests += [ordered]@{
            name   = $parsed.name
            params = $testParams
            rows   = $rows
        }
    }

    return [ordered]@{
        meta    = $meta
        harness = $resultsData.harness
        wtl     = $resultsData.wtl
        tests   = $tests
    }
}

function Merge-Wtl {
    param(
        [Parameter(Mandatory = $true)]$Into,
        [Parameter(Mandatory = $true)]$From
    )

    foreach ($libName in $From.Keys) {
        if (-not $Into.Contains($libName)) {
            $Into[$libName] = [ordered]@{ wins = 0; ties = 0; losses = 0 }
        }
        $Into[$libName].wins   += $From[$libName].wins
        $Into[$libName].ties   += $From[$libName].ties
        $Into[$libName].losses += $From[$libName].losses
    }
}

function Build-PlatformStats {
    param(
        [Parameter(Mandatory = $true)][string]$Project,
        [Parameter(Mandatory = $true)][string]$PlatformDirPath
    )

    $parser = $script:ProjectFilenameParsers[$Project]
    if (-not $parser) {
        Write-Error "No filename parser registered for project '$Project'."
        return $null
    }

    $directResultsPath = Join-Path $PlatformDirPath "Results.csv"

    $meta = [ordered]@{}
    $harness = $null
    $wtl = [ordered]@{}
    $tests = @()

    if (Test-Path -LiteralPath $directResultsPath) {
        $groupStats = Build-BenchmarkGroupStats -Project $Project -GroupDirPath $PlatformDirPath
        if ($groupStats) {
            $meta.cpu = $groupStats.meta.cpu
            $meta.os = $groupStats.meta.os
            $meta.compiler = $groupStats.meta.compiler
            $harness = $groupStats.harness
            Merge-Wtl -Into $wtl -From $groupStats.wtl
            $tests += $groupStats.tests
        }
    } else {
        $subDirs = Get-ChildItem -LiteralPath $PlatformDirPath -Directory
        $anyGroupFound = $false

        foreach ($subDir in $subDirs) {
            $groupStats = Build-BenchmarkGroupStats -Project $Project -GroupDirPath $subDir.FullName -GroupName $subDir.Name
            if (-not $groupStats) {
                continue
            }

            $anyGroupFound = $true

            if ($meta.Count -eq 0 -and $groupStats.meta.Count -gt 0) {
                $meta.cpu = $groupStats.meta.cpu
                $meta.os = $groupStats.meta.os
                $meta.compiler = $groupStats.meta.compiler
            }
            if (-not $harness -and $groupStats.harness) {
                $harness = $groupStats.harness
            }

            Merge-Wtl -Into $wtl -From $groupStats.wtl
            $tests += $groupStats.tests
        }

        if (-not $anyGroupFound) {
            Write-Warning "No Results.csv found directly in '$PlatformDirPath' or in any of its subfolders - skipping."
            return $null
        }
    }

    return [ordered]@{
        cpu      = $meta.cpu
        os       = $meta.os
        compiler = $meta.compiler
        harness  = $harness
        wtl      = $wtl
        tests    = $tests
    }
}

function Build-LibraryStats {
    param(
        [Parameter(Mandatory = $true)][string]$Project,
        [Parameter(Mandatory = $true)][string]$Branch,
        [Parameter(Mandatory = $true)][string]$CsvPath
    )

    if (-not $script:ProjectFilenameParsers.ContainsKey($Project)) {
        Write-Error "Unknown project '$Project'. No filename parser registered."
        return $null
    }

    $platformDirs = Get-ChildItem -LiteralPath $CsvPath -Directory
    $platforms = [ordered]@{}
    $summary = [ordered]@{}

    foreach ($platformDir in $platformDirs) {
        Write-Host "  Aggregating platform '$($platformDir.Name)'..."

        $platformStats = Build-PlatformStats -Project $Project -PlatformDirPath $platformDir.FullName
        if (-not $platformStats) {
            continue
        }

        $platformKey = Get-PlatformKeyFromFolderName -FolderName $platformDir.Name
        $platforms[$platformKey] = $platformStats

        foreach ($libName in $platformStats.wtl.Keys) {
            if (-not $summary.Contains($libName)) {
                $summary[$libName] = [ordered]@{ wins = 0; ties = 0; losses = 0 }
            }
            $summary[$libName].wins   += $platformStats.wtl[$libName].wins
            $summary[$libName].ties   += $platformStats.wtl[$libName].ties
            $summary[$libName].losses += $platformStats.wtl[$libName].losses
        }
    }

    return [ordered]@{
        library     = $Project
        branch      = $Branch
        generatedAt = (Get-Date).ToUniversalTime().ToString("o")
        summary     = $summary
        platforms   = $platforms
    }
}

function Write-LibraryStatsJson {
    param(
        [Parameter(Mandatory = $true)][string]$Project,
        [Parameter(Mandatory = $true)][string]$Branch,
        [Parameter(Mandatory = $true)][string]$CsvPath,
        [Parameter(Mandatory = $true)][string]$OutputPath
    )

    Write-Host "Aggregating stats for project '$Project' / branch '$Branch'..."

    $stats = Build-LibraryStats -Project $Project -Branch $Branch -CsvPath $CsvPath
    if (-not $stats) {
        Write-Error "Aggregation produced no stats - aborting write."
        return $false
    }

    $statsJson = ConvertTo-Json -InputObject $stats -Depth 12
    $utf8NoBom = New-Object System.Text.UTF8Encoding($false)

    $resolvedOutputPath = [System.IO.Path]::GetFullPath((Join-Path (Get-Location) $OutputPath))
    $outputDir = Split-Path -Parent $resolvedOutputPath
    if (-not (Test-Path -LiteralPath $outputDir)) {
        New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
    }

    try {
        [System.IO.File]::WriteAllText($resolvedOutputPath, $statsJson, $utf8NoBom)
    } catch {
        Write-Error "Failed to write stats JSON to '$resolvedOutputPath': $_"
        return $false
    }

    $platformCount = $stats.platforms.Keys.Count
    $libraryCount = $stats.summary.Keys.Count
    Write-Host "Wrote stats JSON to '$resolvedOutputPath' ($platformCount platform(s), $libraryCount librar(y/ies) in summary)."
    return $true
}

Export-ModuleMember -Function `
    Read-CsvWithHeaderComments, `
    Read-HarnessConfig, `
    Read-ResultsCsv, `
    Build-PlatformStats, `
    Build-LibraryStats, `
    Write-LibraryStatsJson