import argparse
import os
import re
import glob
import pandas as pd
import matplotlib.pyplot as plt
from io import StringIO


# ── Earthy, consistent colors per library ─────────────────────────────────────

LIBRARY_COLORS = {
    "jsonifier": "steelblue",
    "glaze":     "seagreen",
    "simdjson":  "cadetblue",
}

FALLBACK_PALETTE = [
    "chocolate",
    "darkkhaki",
    "saddlebrown",
    "olivedrab",
    "darkgoldenrod",
    "indianred",
    "burlywood",
    "firebrick",
]

_dynamic_colors: dict = {}
_fallback_index = 0


def color_for(library_name: str) -> str:
    global _fallback_index
    key = library_name.strip().lower()
    for known, color in LIBRARY_COLORS.items():
        if known in key:
            return color
    if key not in _dynamic_colors:
        _dynamic_colors[key] = FALLBACK_PALETTE[_fallback_index % len(FALLBACK_PALETTE)]
        _fallback_index += 1
    return _dynamic_colors[key]


# ── CSV parsing ───────────────────────────────────────────────────────────────

def parse_csv(path: str):
    with open(path, "r", encoding="utf-8") as f:
        lines = f.readlines()
    header_idx = next(
        (i for i, l in enumerate(lines) if l.strip().lower().startswith("library,")),
        None,
    )
    if header_idx is None:
        return None
    content = "".join(lines[header_idx:])
    df = pd.read_csv(StringIO(content))
    df.columns = [c.strip() for c in df.columns]
    df["Library"] = df["Library"].str.strip()
    return df


def throughput_col(df):
    for col in df.columns:
        if "throughput" in col.lower() and "mb" in col.lower():
            return col
    return None


# ── Plotting ──────────────────────────────────────────────────────────────────

BG = "#0d1117"


def apply_theme():
    plt.rcParams.update({
        "figure.facecolor": BG,
        "axes.facecolor":   BG,
        "axes.edgecolor":   BG,
        "xtick.color":      "lightgray",
        "ytick.color":      "lightgray",
        "grid.color":       "#21262d",
        "text.color":       "white",
    })


def plot_results(df, test_name, op, out_path, is_cumulative=False):
    apply_theme()

    t_col = throughput_col(df)
    if t_col is None:
        print(f"  Skipping {os.path.basename(out_path)} — no throughput column")
        return

    df = df.copy().sort_values(t_col, ascending=False).reset_index(drop=True)

    if is_cumulative:
        slowest = df[t_col].min()
        if slowest <= 0:
            plt.close()
            return
        speeds       = [((s / slowest) - 1) * 100 + 100 for s in df[t_col]]
        y_label      = "Cumulative Speedup (%)"
        label_metric = "%"
    else:
        speeds       = df[t_col].tolist()
        y_label      = "Result Speed (MB/s)"
        label_metric = "MB/s"

    libraries     = df["Library"].tolist()
    num_libraries = len(libraries)
    max_libraries = max(2, num_libraries)
    width         = 0.8 / max_libraries

    fig, ax = plt.subplots(figsize=(10, 6))
    fig.patch.set_facecolor(BG)
    ax.set_facecolor(BG)

    for i, (library, speed) in enumerate(zip(libraries, speeds)):
        color = color_for(library)
        ax.bar(i, speed, label=f"{library} {op}", color=color, width=width)
        font_size = max(8, width * 30)
        ax.text(
            i, speed - 0.05 * speed,
            f"{speed:.2f}{label_metric}",
            ha='center', va='top',
            color='black', fontsize=font_size, fontweight='bold'
        )

    ax.set_xticks(range(num_libraries))
    ax.set_xticklabels(libraries, ha='center', color='lightgray')
    ax.set_title(
        f"{test_name} {'Cumulative Speedup (Relative to Slowest Library)' if is_cumulative else 'Result Speed Comparison'}",
        color='white'
    )
    ax.set_xlabel('Library Name', color='white')
    ax.set_ylabel(y_label, color='white')
    ax.tick_params(colors='lightgray')
    ax.yaxis.label.set_color('white')
    ax.xaxis.label.set_color('white')
    ax.title.set_color('white')

    legend = ax.legend(title='Library and Result Type', loc='best')
    legend.get_title().set_color('white')
    for text in legend.get_texts():
        text.set_color('white')
    legend.get_frame().set_facecolor('#161b22')
    legend.get_frame().set_edgecolor('#30363d')

    ax.yaxis.grid(True, color='#21262d')
    ax.set_axisbelow(True)

    plt.tight_layout()
    plt.savefig(out_path, facecolor=BG)
    plt.close()
    print(f"  Saved: {os.path.basename(out_path)}")


# ── File discovery and dispatch ───────────────────────────────────────────────

# Matches: "Double Test Read.csv", "String Test Write.csv" etc.
# The hyphen immediately before Read/Write (no space) is the delimiter.
CSV_PATTERN = re.compile(r"^(.+?)(?: (Read|Write))?\.csv$", re.IGNORECASE)


def parse_args():
    parser = argparse.ArgumentParser(
        description="Generate benchmark graphs from per-test CSV files."
    )
    parser.add_argument("input_directory",  help="Directory containing the CSV files")
    parser.add_argument("output_directory", help="Directory to write the PNG images")
    return parser.parse_args()


def main():
    args    = parse_args()
    in_dir  = args.input_directory
    out_dir = args.output_directory
    os.makedirs(out_dir, exist_ok=True)

    csv_files = sorted(glob.glob(os.path.join(in_dir, "*.csv")))
    if not csv_files:
        print(f"No CSV files found in {in_dir}")
        return

    for csv_path in csv_files:
        filename = os.path.basename(csv_path)
        m = CSV_PATTERN.match(filename)
        if not m:
            print(f"Skipping (unrecognised pattern): {filename}")
            continue

        test_name = m.group(1).strip()
        op        = m.group(2).capitalize() if m.group(2) else "Result"
        stem      = filename[:-4]

        df = parse_csv(csv_path)
        if df is None or df.empty:
            print(f"Skipping (empty/unparseable): {filename}")
            continue

        print(f"Processing: {filename}")

        plot_results(df, test_name, op,
                     os.path.join(out_dir, f"{stem}_Results.png"),
                     is_cumulative=False)


if __name__ == "__main__":
    main()