# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# shell/sweep_iterations.py

import glob
import math
import os
import re
import subprocess
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
BUILD = os.path.join(ROOT, "Build")
WINDOWS = os.name == "nt"
PODS = os.environ.get("SWEEP_PODS", "0 256 512 2048 4096 65536").split()
BLOCKS = os.environ.get("SWEEP_BLOCKS", "1 2 4 8").split()
TAPES = os.environ.get("SWEEP_TAPES", "").split() or [None]
SETTINGS = (("tunedSmallDocumentBytes", "pod"), ("tunedBlocksPerStep", "blocks"), ("tunedTapeStep", "tape"))


def config_header():
    found = glob.glob(os.path.join(BUILD, "_deps", "jsonifier-src", "include", "jsonifier-incl", "simd", "simd_config.hpp"))
    if not found:
        raise SystemExit("simd_config.hpp not found under Build/_deps/jsonifier-src")
    return found[0]


def configured(text, values):
    for name, key in SETTINGS:
        if values.get(key) is None:
            continue
        text, count = re.subn(r"(inline constexpr uint64_t " + name + r"\{ )\d+( \};)", lambda match: f"{match[1]}{values[key]}{match[2]}", text)
        if count == 0:
            raise SystemExit(f"{name} not found in simd_config.hpp")
    return text


def build():
    return subprocess.run(["cmake", "--build", BUILD, "--config", "Release"], capture_output=True, text=True)


def run():
    if WINDOWS:
        command = [os.path.join(BUILD, "Release", "Json-Performance.exe")]
    else:
        command = ["sudo", "-E", "env", f"PATH={os.environ['PATH']}", os.path.join(BUILD, "Json-Performance")]
    return subprocess.run(command, cwd=ROOT, capture_output=True, text=True)


def cells(line):
    return [cell.strip() for cell in line.strip().strip("|").split("|")]


def parse_table(path):
    lines = [line for line in open(path, encoding="utf-8", errors="replace") if line.startswith("|")]
    header = cells(lines[0])
    throughput, position = header.index("Throughput (MB/s)"), header.index("Position")
    rows = {}
    for line in lines[2:]:
        row = cells(line)
        library = "jsonifier" if row[0].startswith("Jsonifier") else "simdjson" if row[0].startswith("simdjson") else None
        if library:
            rows[library] = (float(row[throughput]), row[position])
    return rows


def collect():
    results = {}
    for path in sorted(glob.glob(os.path.join(ROOT, "csv", "*", "*.md"))):
        name = os.path.basename(path)[:-3]
        if name == "Results":
            continue
        rows = parse_table(path)
        if "jsonifier" in rows and "simdjson" in rows:
            platform = os.path.basename(os.path.dirname(path))
            results[name.replace("Package.json Corpus ", "").replace(" Test Read", "")] = (platform, rows)
    return results


def summarize(tag, results):
    deltas = {test: rows["jsonifier"][0] / rows["simdjson"][0] for test, (_, rows) in results.items()}
    losses = sum("Loss" in rows["jsonifier"][1] for _, rows in results.values())
    geomean = math.exp(sum(math.log(value) for value in deltas.values()) / len(deltas)) - 1
    return {"tag": tag, "losses": losses, "geomean": geomean, "deltas": {test: value - 1 for test, value in deltas.items()},
            "platform": next(iter(results.values()))[0]}


def write_report(entries):
    ranked = sorted(entries, key=lambda entry: (entry["losses"], -entry["geomean"]))
    tests = sorted(ranked[0]["deltas"], key=lambda test: int(test.split("-")[0]) if test[0].isdigit() else math.inf)
    platform = ranked[0]["platform"]
    lines = [f"# {platform}: pod cutoff x blocks per step{' x tape step' if TAPES[0] else ''}, Jsonifier vs simdjson", "", "Sorted by fewest losing tests (Welch verdict), then by geomean throughput delta.", "",
             "| Rank | Config | Losses | Geomean | " + " | ".join(tests) + " |", "| --- " * (len(tests) + 4) + "|"]
    for rank, entry in enumerate(ranked, 1):
        lines.append(f"| {rank} | {entry['tag']} | {entry['losses']} | {entry['geomean']:+.2%} | " +
                     " | ".join(f"{entry['deltas'].get(test, float('nan')):+.2%}" for test in tests) + " |")
    path = os.path.join(ROOT, f"Sweep-{platform}.md")
    with open(path, "w", encoding="utf-8") as out:
        out.write("\n".join(lines) + "\n")
    print(f"\nSaved {path}\n" + "\n".join(lines), flush=True)


def main():
    header = config_header()
    original = open(header, encoding="utf-8", newline="").read()
    entries = []
    try:
        for pod, blocks, tape in ((pod, blocks, tape) for pod in PODS for blocks in BLOCKS for tape in TAPES):
            tag = f"p{pod}-b{blocks}" + (f"-t{tape}" if tape else "")
            with open(header, "w", encoding="utf-8", newline="") as out:
                out.write(configured(original, {"pod": pod, "blocks": blocks, "tape": tape}))
            built = build()
            if built.returncode != 0:
                print(f"{tag}: BUILD FAILED\n{built.stdout[-2000:]}{built.stderr[-2000:]}", flush=True)
                continue
            ran = run()
            if ran.returncode != 0:
                print(f"{tag}: RUN FAILED (exit {ran.returncode})\n{ran.stdout[-2000:]}", flush=True)
                continue
            results = collect()
            if not results:
                print(f"{tag}: no result tables found", flush=True)
                continue
            entry = summarize(tag, results)
            entries.append(entry)
            ordered = sorted(entry["deltas"].items(), key=lambda item: int(item[0].split("-")[0]) if item[0][0].isdigit() else math.inf)
            deltas = "  ".join(f"{test} {value:+.2%}" for test, value in ordered)
            print(f"{tag}: {deltas} | geomean {entry['geomean']:+.2%} | losses {entry['losses']}", flush=True)
    finally:
        with open(header, "w", encoding="utf-8", newline="") as out:
            out.write(original)
    if not entries:
        raise SystemExit("no sweep configuration produced results")
    write_report(entries)
    restored = build()
    if restored.returncode != 0:
        raise SystemExit(f"rebuild with the original simd_config.hpp failed\n{restored.stdout[-2000:]}{restored.stderr[-2000:]}")


if __name__ == "__main__":
    main()
