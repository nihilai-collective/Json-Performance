# Json-Performance
Here's a few benchmarks on a few common operating system/compiler platforms. Although feel free to try it out on more and let us know if you do/what scores you get! Cheers! (Click each of the badges below to be taken to the respective benchmarks). Also we will add some instructions for building below.

### The Libraries
- [Jsonifier](https://github.com/nihilai-collective/Jsonifier)
- [Glaze](https://github.com/stephenberry/glaze)
- [SimdJson](https://github.com/simdjson/simdjson)

### The Branches
- [Full Parsing + Serializing](https://github.com/nihilai-collective/Json-Performance/)
- [Scalar Structural Parsing vs simdjson with simd](https://github.com/nihilai-collective/Json-Performance/tree/scalar-vs-simd-main)
- [Stage-1 Parsing](https://github.com/nihilai-collective/Json-Performance/tree/stage-1-parsing-main)
- [Stage-1 Parsing (AVX512)](https://github.com/nihilai-collective/Json-Performance/tree/stage-1-parsing-avx512-main)
- [Stage-1 + Stage-2 Parsing + Utf8 Validation](https://github.com/nihilai-collective/Json-Performance/tree/full-parsing-utf8-main)
- [Correctness Validation](https://github.com/nihilai-collective/Json-Performance/tree/correctness-validation-main)

> *"Anytime someone comes to you with one benchmark? They have gamed that benchmark."*  
> — Matt Kulukundis, CppCon 2017

### By OS/Compiler:
----
#### Linux/Clang:
----
[![Linux/Clang](https://img.shields.io/github/actions/workflow/status/nihilai-collective/Json-Performance/Benchmark.yml?style=plastic&logo=linux&logoColor=green&label=Clang&labelColor=pewter&color=blue&branch=benchmarking-newer)](/Linux-Clang.md)
#### Windows/MSVC:
----
[![Windows/MSVC](https://img.shields.io/github/actions/workflow/status/nihilai-collective/Json-Performance/Benchmark.yml?style=plastic&logo=Microsoft&logoColor=green&label=MSVC&labelColor=pewter&color=blue&branch=benchmarking-newer)](/Windows-MSVC.md)
#### Linux/GCC:
----
[![Linux/GCC](https://img.shields.io/github/actions/workflow/status/nihilai-collective/Json-Performance/Benchmark.yml?style=plastic&logo=linux&logoColor=green&label=GCC&labelColor=pewter&color=blue&branch=benchmarking-newer)](/Linux-GCC.md)
#### macOS/Clang:
----
[![macOS/Clang](https://img.shields.io/github/actions/workflow/status/nihilai-collective/Json-Performance/Benchmark.yml?style=plastic&logo=apple&logoColor=green&label=Clang&labelColor=pewter&color=blue&branch=benchmarking-newer)](/macOS-Clang.md)
#### macOS/GCC:
----
[![macOS/GCC](https://img.shields.io/github/actions/workflow/status/nihilai-collective/Json-Performance/Benchmark.yml?style=plastic&logo=apple&logoColor=green&label=GCC&labelColor=pewter&color=blue&branch=benchmarking-newer)](/macOS-GCC.md)

### Pre-requisites:
---
1. CMake 3.28 or later.
2. A C++20 compliant compiler.
3. Python3 and Seaborn for generating the graphs.

### Build Instructions:
---
1. Clone the repo.
2. Cd into the repo's folder and enter `cmake -S . -B ./Build -DCMAKE_BUILD_TYPE=RELEASE_OR_DEBUG -DCMAKE_CXX_COMPILER=PATH_TO_COMPILER_EXECUTABLE` (NOTE: Optionally set a manual installation path by setting `-DCMAKE_INSTALL_PREFIX=CUSTOM_INSTALLATION_PATH`)
3. Then enter `cmake --build ./Build --config=RELEASE_OR_DEBUG`
4. Then enter `cmake --install ./Build`
5. Run the executable from wherever it was installed to!

#### Note:
These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/RealTimeChris/benchmarksuite)
