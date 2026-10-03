import json
import os
import sys

TARGET_MAX_BYTES = 5 * 1024
SOURCES = [
    "Canada Test",
    "CitmCatalog Test",
    "Discord Test",
    "Google Maps Response Test",
    "Instruments Test",
    "Marine IK Reverse Test",
    "Marine IK Test",
    "Mesh Test",
    "Random Test",
    "Twitter Partial Test",
    "Twitter Test",
]


def truncate(value, limit):
    if isinstance(value, list):
        return [truncate(item, limit) for item in value[:limit]]
    if isinstance(value, dict):
        items = list(value.items())
        if items and all(key.isdigit() for key, _ in items):
            items = items[:limit]
        return {key: truncate(item, limit) for key, item in items}
    return value


def minified(value):
    return json.dumps(value, ensure_ascii=False, separators=(",", ":"))


def shrink(document):
    for limit in range(16, 0, -1):
        candidate = truncate(document, limit)
        if len(minified(candidate).encode("utf-8")) <= TARGET_MAX_BYTES:
            return candidate, limit
    return truncate(document, 1), 1


def main(json_dir):
    for name in SOURCES:
        with open(os.path.join(json_dir, f"{name} (Minified).json"), encoding="utf-8") as source:
            document = json.load(source)
        small, limit = shrink(document)
        small_name = name.replace(" Test", " Small Test")
        minified_text = minified(small)
        prettified_text = json.dumps(small, ensure_ascii=False, indent=3)
        for suffix, text in (("Minified", minified_text), ("Prettified", prettified_text)):
            with open(os.path.join(json_dir, f"{small_name} ({suffix}).json"), "w", encoding="utf-8", newline="\n") as out:
                out.write(text)
        print(f"{small_name}: limit={limit}, minified={len(minified_text.encode('utf-8'))}B, prettified={len(prettified_text.encode('utf-8'))}B")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else os.path.join(os.path.dirname(os.path.abspath(__file__)), "json"))
