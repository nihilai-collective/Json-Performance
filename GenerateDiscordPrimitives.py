# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Nihilai Collective Corp
# https://github.com/nihilai-collective/json-performance
# GenerateDiscordPrimitives.py

import json
import os

json_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "json")

with open(os.path.join(json_dir, "Discord Test (Minified).json"), encoding="utf-8") as source:
    document = json.load(source)

primitives = {"String": [], "Int64": [], "Bool": []}


def collect(value):
    if isinstance(value, dict):
        for member in value.values():
            collect(member)
    elif isinstance(value, list):
        for element in value:
            collect(element)
    elif isinstance(value, bool):
        primitives["Bool"].append(value)
    elif isinstance(value, int):
        primitives["Int64"].append(value)
    elif isinstance(value, str):
        primitives["String"].append(value)
    elif value is not None:
        raise TypeError(f"unexpected value in Discord document: {value!r}")


collect(document)

for kind, values in primitives.items():
    with open(os.path.join(json_dir, f"Discord {kind} Test.json"), "w", encoding="utf-8", newline="") as output:
        for value in values:
            output.write("[START]" + json.dumps(value, ensure_ascii=False) + "[END]\r\n")
    print(f"Discord {kind} Test: {len(values)} values")
