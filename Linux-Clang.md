# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1019-azure using the Clang 24.0.0 compiler).  

Latest Results: (Nov 14, 2026)
#### Using the following commits:
----
| Jsonifier: [d4727ec](https://github.com/nihilai-collective/Jsonifier/commit/d4727ec)  
| Glaze: [a53ddd59](https://github.com/stephenberry/glaze/commit/a53ddd59)  
| simdjson: [449f38e63](https://github.com/simdjson/simdjson/commit/449f38e63)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX512` |
| **simdjson (ondemand)** | `icelake` |
| **Glaze** | utf8: `AVX512BW`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX512BW` |

> **Adaptive Sampling & Convergence (AMD EPYC 9V45 96-Core Processor-AVX512):**  
> Iterations scale geometrically (100 → 200 → 400 ...) up to a maximum of 100000.  
> Scores evaluate a trailing window of `max(iterations/10, 30)` (cap: 100000) over at most 5s.  
> Canonical epochs are chosen by minimum (RSE + epoch-over-epoch mean shift).  
> Converged: RSE ≤ 5% and mean shift ≤ 2.5%. Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Test Variants
* **Standard vs. (Reused):** Standard measures full instantiation, parsing/serialization, and teardown per iteration. `(Reused)` holds the buffer/object across iterations and clears it outside the timed region to isolate raw parse/format throughput.
* **Document Sizes:** "Small" tests cap minified payloads at 5 KiB (via `GenerateSmallJson.py`) to highlight dispatch, setup, and small-allocation latency rather than bulk vector throughput.
* **Key Traversal Order:** Standard tests provide keys in sequential order. Tests labeled `Reverse` parse keys backwards to highlight the $O(N^2)$ penalty inherent to single-pass forward-only decoders (e.g., simdjson On Demand) versus hash/DOM-indexed alternatives.

##### Implementation Details
* **simdjson (ondemand):** Includes the harness mapping layer (`include/common.hpp`). On MSVC, uses `find_field` / `find_field_unordered` due to severe compiler overhead when instantiating `object::for_each`.
* **simdjson (reflection):** Absent from this run; current toolchain lacks P2996 static reflection support.
* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.
* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.

---
*Environment generated via BenchmarkSuite commit: [27950a9](https://github.com/nihilai-collective/benchmarksuite/commit/27950a9)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1853.87 | 0.218629 | 49.3377ms | 905 | 2560 | 2652.11 | 465.552 | 0.644246 | 1.26243 | 1(Win) | true |
| Glaze | 1556.63 | 0.071011 | 59.5192ms | 905 | 160 | 24.8025 | 554.45 | 0.0180391 | 1.51941 | 2(Loss) | true |
| Jsonifier (two-stage) | 526.407 | 0.0201512 | 167.2ms | 905 | 320 | 34.9306 | 1639.56 | 0.0543505 | 4.6279 | 3(Loss) | true |
| simdjson (ondemand) | 262.854 | 0.0417242 | 329.878ms | 905 | 40 | 75.0763 | 3283.47 | 0.0900165 | 9.34552 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1927.81 | 0.066748 | 48.2023ms | 905 | 320 | 28.5755 | 447.697 | 0.0788137 | 1.21378 | 1(Win) | true |
| Glaze | 1507.27 | 0.0380906 | 59.9311ms | 905 | 320 | 15.2231 | 572.609 | 0.00163721 | 1.5683 | 2(Loss) | true |
| Jsonifier (two-stage) | 529.368 | 0.0285602 | 164.51ms | 905 | 160 | 34.6917 | 1630.39 | 0.0782635 | 4.6032 | 3(Loss) | true |
| simdjson (ondemand) | 257.655 | 0.0471462 | 340.24ms | 905 | 30 | 74.823 | 3349.73 | 0.0984183 | 9.5361 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2243.1 | 0.0733408 | 40.9349ms | 905 | 320 | 25.4824 | 384.769 | 0.0308532 | 1.02979 | 1(Win) | true |
| Glaze | 211.44 | 0.128221 | 415.614ms | 905 | 40 | 1095.73 | 4081.9 | 0.0310217 | 11.6373 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4161.26 | 0.0643417 | 27.9544ms | 905 | 1280 | 22.7951 | 207.407 | 0.138431 | 0.521811 | 1(Win) | true |
| Glaze | 985.443 | 0.128328 | 97.1155ms | 905 | 80 | 101.058 | 875.825 | 0.0542052 | 2.4372 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1401.5 | 0.265715 | 125.776ms | 1811 | 2560 | 27449 | 1232.33 | 0.00367685 | 1.72992 | 1(Win) | true |
| Glaze | 902.66 | 0.0703237 | 195.856ms | 1811 | 80 | 144.838 | 1913.35 | 0.185195 | 2.70651 | 2(Loss) | true |
| Jsonifier (two-stage) | 509.46 | 0.0751845 | 343.443ms | 1811 | 30 | 194.892 | 3390.07 | 0.0206443 | 4.82188 | 3(Loss) | true |
| simdjson (ondemand) | 315.572 | 0.0567681 | 584.073ms | 1811 | 30 | 289.582 | 5472.93 | 0.0663433 | 7.81136 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1496.3 | 0.0884908 | 118.581ms | 1811 | 40 | 41.7308 | 1154.25 | 0.0187677 | 1.61897 | 1(Win) | true |
| Glaze | 927.304 | 0.0494339 | 188.476ms | 1811 | 30 | 25.431 | 1862.5 | 0.103695 | 2.63481 | 2(Loss) | true |
| Jsonifier (two-stage) | 519.257 | 0.319299 | 338.894ms | 1811 | 640 | 72185.2 | 3326.11 | 0.111365 | 4.73027 | 3(Loss) | true |
| simdjson (ondemand) | 317.417 | 0.101779 | 546.601ms | 1811 | 4890 | 149970 | 5441.13 | 0.00534948 | 7.76232 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 334.428 | 0.0299911 | 524.929ms | 1811 | 160 | 383.828 | 5164.36 | 0.137171 | 7.36606 | 1(Win) | true |
| Glaze | 285.197 | 0.116999 | 607.366ms | 1798 | 4890 | 241970 | 6012.37 | 0.133381 | 8.64382 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 860.927 | 0.310842 | 209.06ms | 1811 | 2560 | 99545.9 | 2006.1 | 0.232214 | 2.83967 | 1(Win) | true |
| Glaze | 604.137 | 0.0303814 | 294.632ms | 1798 | 40 | 29.7429 | 2838.28 | 0.0243633 | 4.05979 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2872.51 | 0.0421072 | 131.205ms | 3862 | 80 | 23.3188 | 1282.19 | 0.041903 | 0.843371 | 1(Win) | true |
| Glaze | 1430.89 | 0.0392508 | 262.353ms | 3862 | 80 | 81.6581 | 2573.99 | 0.00534219 | 1.71224 | 2(Loss) | true |
| Jsonifier (two-stage) | 927.263 | 0.0369486 | 401.96ms | 3862 | 40 | 86.1538 | 3972 | 0.0176265 | 2.6543 | 3(Loss) | true |
| simdjson (ondemand) | 687.513 | 0.155701 | 539.078ms | 3862 | 2560 | 178110 | 5357.12 | 0.140096 | 3.58384 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3064.29 | 0.0428279 | 123.538ms | 3862 | 80 | 21.1986 | 1201.94 | 0.0945494 | 0.790494 | 1(Win) | true |
| Glaze | 1489.52 | 0.0170835 | 251.238ms | 3862 | 160 | 28.55 | 2472.67 | 0.0381818 | 1.64416 | 2(Loss) | true |
| Jsonifier (two-stage) | 945.273 | 0.0453132 | 396.106ms | 3862 | 40 | 124.687 | 3896.32 | 0.0395515 | 2.60331 | 3(Loss) | true |
| simdjson (ondemand) | 698.885 | 0.0397625 | 533.581ms | 3862 | 40 | 175.638 | 5269.95 | 0.12098 | 3.52515 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 911.295 | 0.0589313 | 410.731ms | 3862 | 40 | 226.913 | 4041.6 | 0.0280338 | 2.70043 | 1(Win) | true |
| Glaze | 820.971 | 0.209063 | 455.051ms | 3862 | 1280 | 112598 | 4486.26 | 0.0215194 | 2.99849 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4766.37 | 0.053266 | 85.6145ms | 3862 | 160 | 27.1063 | 772.725 | 0.0743567 | 0.502285 | 1(Win) | true |
| Glaze | 2577.12 | 0.0934261 | 152.886ms | 3862 | 40 | 71.3103 | 1429.15 | 0.0478368 | 0.942666 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1801.78 | 0.225414 | 509.556ms | 9578 | 1280 | 167154 | 5069.59 | 0.0753007 | 1.36714 | 1(Win) | true |
| Glaze | 1447.13 | 0.0361782 | 637.538ms | 9578 | 40 | 208.589 | 6312.02 | 0.00330047 | 1.70411 | 2(Loss) | true |
| simdjson (ondemand) | 1291.19 | 0.242242 | 709.646ms | 9578 | 640 | 187953 | 7074.34 | 0.00726605 | 1.91042 | 3(Loss) | true |
| Jsonifier (two-stage) | 1083.88 | 0.106839 | 847.965ms | 9578 | 2560 | 207534 | 8427.39 | 0.0285307 | 2.27735 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2727.36 | 0.0565571 | 467.968ms | 9578 | 30 | 107.637 | 3349.13 | 0.0258706 | 0.90102 | 1(Win) | true |
| Glaze | 2027.54 | 0.0463824 | 597.97ms | 9578 | 30 | 130.99 | 4505.1 | 0.148942 | 1.21385 | 2(Loss) | true |
| simdjson (ondemand) | 1617.06 | 0.203485 | 697.664ms | 9578 | 2560 | 338223 | 5648.72 | 0.00864336 | 1.52351 | 3(Loss) | true |
| Jsonifier (two-stage) | 1347.55 | 0.133965 | 808.971ms | 9578 | 2560 | 211098 | 6778.43 | 0.0156772 | 1.83028 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4629.65 | 0.0811469 | 199.469ms | 9578 | 80 | 205.063 | 1973 | 0.0126695 | 0.527964 | 1(Win) | true |
| Glaze | 1863.05 | 0.23862 | 467.829ms | 9578 | 1280 | 175196 | 4902.86 | 0.151112 | 1.32147 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12933.6 | 0.113233 | 79.1692ms | 9578 | 160 | 102.324 | 706.244 | 0.170507 | 0.18457 | 1(Win) | true |
| Glaze | 5370.68 | 0.069437 | 185.241ms | 9578 | 160 | 223.147 | 1700.77 | 0.847155 | 0.454108 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3065.96 | 0.275098 | 123.207ms | 3873 | 2560 | 28117.5 | 1204.71 | 0.0131304 | 0.790504 | 1(Win) | true |
| Glaze | 1449.87 | 0.0812725 | 259.046ms | 3873 | 30 | 128.602 | 2547.53 | 0.0143951 | 1.69012 | 2(Loss) | true |
| Jsonifier (two-stage) | 901.005 | 0.0534998 | 415.1ms | 3873 | 40 | 192.4 | 4099.4 | 0.00406547 | 2.73187 | 3(Loss) | true |
| simdjson (ondemand) | 665.317 | 0.0245136 | 561.803ms | 3873 | 80 | 148.164 | 5551.61 | 0.000225159 | 3.70361 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3292.78 | 0.0244753 | 116.041ms | 3873 | 320 | 24.1199 | 1121.72 | 0.0136528 | 0.734323 | 1(Win) | true |
| Glaze | 1500.57 | 0.0420583 | 249.867ms | 3873 | 40 | 42.8692 | 2461.45 | 0.151223 | 1.63311 | 2(Loss) | true |
| Jsonifier (two-stage) | 909.826 | 0.116508 | 409.272ms | 3873 | 4890 | 109395 | 4059.66 | 0.0625009 | 2.70349 | 3(Loss) | true |
| simdjson (ondemand) | 664.628 | 0.0524012 | 562.182ms | 3873 | 80 | 678.437 | 5557.36 | 0.112815 | 3.70789 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 935.983 | 0.173587 | 399.373ms | 3873 | 2560 | 120125 | 3946.21 | 0.0928572 | 2.62805 | 1(Win) | true |
| Glaze | 844.228 | 0.361658 | 444.273ms | 3873 | 320 | 80116.6 | 4375.1 | 0.101181 | 2.9154 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5111.81 | 0.0275484 | 81.1699ms | 3873 | 640 | 25.3582 | 722.558 | 0.0481995 | 0.467192 | 1(Win) | true |
| Glaze | 2657.76 | 0.0751074 | 148.992ms | 3873 | 30 | 32.6851 | 1389.73 | 0.050344 | 0.91297 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1655.46 | 0.754027 | 5279.62ms | 94653 | 80 | 1.35236e+07 | 54527.4 | 0.254602 | 1.4948 | 1(Win) | true |
| Jsonifier (two-stage) | 1555.19 | 0.0639252 | 5893.29ms | 94653 | 2560 | 3.52441e+06 | 58043.1 | 0.100208 | 1.59122 | 2(Loss) | true |
| Glaze | 1494.25 | 0.102527 | 6145.37ms | 94653 | 640 | 2.45515e+06 | 60410.4 | 0.0395008 | 1.65619 | 3(Loss) | true |
| simdjson (ondemand) | 1082.3 | 0.0533001 | 8241.11ms | 94653 | 2560 | 5.05911e+06 | 83404.4 | 0.0509971 | 2.2868 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2490.86 | 0.0794324 | 4866.17ms | 94653 | 2560 | 2.12132e+06 | 36239.8 | 0.25498 | 0.993241 | 1(Win) | true |
| Jsonifier (two-stage) | 2192.9 | 0.0601586 | 5382.68ms | 94653 | 2560 | 1.56988e+06 | 41163.9 | 0.0709359 | 1.12829 | 2(Loss) | true |
| Glaze | 1911.8 | 0.062395 | 5905.29ms | 94653 | 4890 | 4.24418e+06 | 47216.4 | 0.364456 | 1.29428 | 3(Loss) | true |
| simdjson (ondemand) | 1442.8 | 0.0796005 | 7547.5ms | 94653 | 1280 | 3.17468e+06 | 62564.7 | 0.175169 | 1.71522 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18132.3 | 0.152793 | 500.92ms | 94653 | 4890 | 282928 | 4978.3 | 0.344443 | 0.135841 | 1(Win) | true |
| Glaze | 5465.49 | 0.225806 | 1699.56ms | 94653 | 320 | 445071 | 16516 | 0.45389 | 0.4523 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17460.5 | 0.16546 | 518.814ms | 94653 | 4890 | 357807 | 5169.84 | 0.431478 | 0.14101 | 1(Win) | true |
| Glaze | 6026.51 | 0.292614 | 1547.47ms | 94653 | 320 | 614718 | 14978.5 | 0.406654 | 0.410109 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1950.19 | 0.174595 | 6177ms | 124597 | 320 | 3.6214e+06 | 60930.1 | 0.0780306 | 1.26895 | 1(Win) | true |
| Jsonifier | 1715.26 | 0.154194 | 6807.32ms | 124597 | 640 | 7.30244e+06 | 69275.1 | 0.405924 | 1.44282 | 2(Loss) | true |
| Glaze | 1617.71 | 0.0886739 | 7232.79ms | 124597 | 1280 | 5.43023e+06 | 73452.8 | 0.0316419 | 1.52986 | 3(Loss) | true |
| simdjson (ondemand) | 1417.43 | 0.0902328 | 8423.32ms | 124597 | 1280 | 7.32403e+06 | 83831.2 | 0.163187 | 1.74612 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2733.7 | 0.0943624 | 5669.51ms | 124597 | 1280 | 2.15339e+06 | 43466.8 | 0.369655 | 0.9051 | 1(Win) | true |
| Jsonifier | 2328.64 | 0.231903 | 6308.9ms | 124597 | 160 | 2.24048e+06 | 51027.5 | 0.0127031 | 1.06264 | 2(Loss) | true |
| Glaze | 2123.32 | 0.11727 | 6650.94ms | 124597 | 640 | 2.75638e+06 | 55961.9 | 0.27059 | 1.16545 | 3(Loss) | true |
| simdjson (ondemand) | 1774.13 | 0.0617994 | 7827.06ms | 124597 | 2560 | 4.38585e+06 | 66976.6 | 0.0972775 | 1.39488 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19774.1 | 0.249961 | 671.716ms | 136037 | 30 | 8068.4 | 6560.87 | 0.121575 | 0.124689 | 1(Win) | true |
| Glaze | 5917.3 | 0.256714 | 2146.54ms | 136076 | 320 | 1.0143e+06 | 21931 | 0.122265 | 0.417898 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18867.1 | 0.221226 | 684.368ms | 136037 | 1280 | 296201 | 6876.27 | 1.10786 | 0.130709 | 1(Win) | true |
| Glaze | 6732.9 | 0.0260583 | 1967.08ms | 136076 | 30 | 756.782 | 19274.3 | 0.171506 | 0.367248 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1007.75 | 0.0660805 | 6701.34ms | 2251027 | 80 | 1.58525e+08 | 2.13025e+06 | 0.463701 | 2.45674 | 1(Win) | true |
| Jsonifier (two-stage) | 923.635 | 0.424926 | 7362.31ms | 2251027 | 30 | 2.92623e+09 | 2.32424e+06 | 0.838294 | 2.68045 | 2(Loss) | true |
| Glaze | 766.57 | 0.101556 | 8746.38ms | 2251027 | 40 | 3.23541e+08 | 2.80046e+06 | 0.0529291 | 3.2297 | 3(Loss) | true |
| simdjson (ondemand) | 750.193 | 0.146216 | 8995.13ms | 2251027 | 30 | 5.25201e+08 | 2.86159e+06 | 0.0529694 | 3.30019 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1231.06 | 0.21626 | 6714.01ms | 2251027 | 30 | 4.26654e+08 | 1.74381e+06 | 0.718159 | 2.01107 | 1(Win) | true |
| Jsonifier (two-stage) | 1128.81 | 0.0403309 | 7179.87ms | 2251027 | 160 | 9.41268e+07 | 1.90177e+06 | 0.182163 | 2.19324 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 911.803 | 0.313296 | 8701.59ms | 2251027 | 160 | 8.7054e+09 | 2.3544e+06 | 0.153503 | 2.71525 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 907.731 | 0.0458403 | 8753.6ms | 2251027 | 80 | 9.40226e+07 | 2.36496e+06 | 0.268009 | 2.72742 | 3(Tie) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2089.29 | 0.0263875 | 6091.87ms | 2090234 | 80 | 5.07083e+06 | 954107 | 0.161773 | 1.18495 | 1(Win) | true |
| Glaze | 1003.83 | 0.0441292 | 6186.5ms | 2090234 | 160 | 1.2287e+08 | 1.9858e+06 | 0.058319 | 2.46633 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2063.94 | 0.049136 | 6099.09ms | 2090234 | 80 | 1.80172e+07 | 965825 | 0.0059117 | 1.19951 | 1(Win) | true |
| Glaze | 1024.68 | 0.0181266 | 6082.31ms | 2090234 | 80 | 9.94802e+06 | 1.94539e+06 | 0.00674692 | 2.41613 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2051.13 | 0.123934 | 7823.26ms | 5373214 | 30 | 2.87597e+08 | 2.49828e+06 | 0.0498284 | 1.20702 | 1(Win) | true |
| Jsonifier | 1957.61 | 0.373069 | 8138.28ms | 5373214 | 80 | 7.62926e+09 | 2.61763e+06 | 0.67354 | 1.26468 | 2(Loss) | true |
| simdjson (ondemand) | 1702.4 | 0.108453 | 9351.07ms | 5373214 | 30 | 3.19709e+08 | 3.01005e+06 | 0.234209 | 1.4543 | 3(Loss) | true |
| Glaze | 1601.19 | 0.0473738 | 10104.4ms | 5373214 | 160 | 3.67771e+08 | 3.2003e+06 | 0.386161 | 1.54622 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2459.85 | 0.0337713 | 7750.56ms | 5373214 | 160 | 7.91895e+07 | 2.08317e+06 | 0.21806 | 1.00647 | 1(Win) | true |
| Jsonifier | 2334.01 | 0.0419429 | 8134.79ms | 5373214 | 160 | 1.35675e+08 | 2.19549e+06 | 0.151981 | 1.06074 | 2(Loss) | true |
| simdjson (ondemand) | 2024.77 | 0.0635111 | 9231.48ms | 5373214 | 30 | 7.75062e+07 | 2.5308e+06 | 0.0544683 | 1.22274 | 3(Loss) | true |
| Glaze | 1857.31 | 0.17536 | 10092.1ms | 5373214 | 30 | 7.02234e+08 | 2.75899e+06 | 0.231743 | 1.333 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5726.03 | 0.0401601 | 7005.96ms | 6661897 | 160 | 3.17686e+07 | 1.10954e+06 | 0.0211179 | 0.432357 | 1(Win) | true |
| Glaze | 3286.37 | 0.0870718 | 6088.28ms | 6661897 | 30 | 8.50038e+07 | 1.93322e+06 | 0.0779318 | 0.753318 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5732.94 | 0.0414146 | 6991.56ms | 6661897 | 320 | 6.7406e+07 | 1.10821e+06 | 0.119417 | 0.431832 | 1(Win) | true |
| Glaze | 3571.89 | 0.0425686 | 5540.99ms | 6661897 | 80 | 4.58636e+07 | 1.77869e+06 | 0.186841 | 0.693118 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2219.47 | 0.084582 | 5535.31ms | 500299 | 640 | 2.1159e+07 | 214971 | 0.444917 | 1.11527 | 1(Win) | true |
| Jsonifier (two-stage) | 1853.34 | 0.0933058 | 6588.84ms | 500299 | 1280 | 7.38543e+07 | 257439 | 0.76289 | 1.33561 | 2(Loss) | true |
| Glaze | 1566.89 | 0.0818938 | 7867.87ms | 500299 | 320 | 1.98992e+07 | 304503 | 0.00827543 | 1.5799 | 3(Loss) | true |
| simdjson (ondemand) | 1144.42 | 0.0985851 | 5313.64ms | 500299 | 160 | 2.7029e+07 | 416911 | 0.057826 | 2.16314 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2706.14 | 0.233349 | 5537.53ms | 500299 | 80 | 1.35413e+07 | 176311 | 0.0596817 | 0.914685 | 1(Win) | true |
| Jsonifier (two-stage) | 2249.07 | 0.238848 | 6311.91ms | 500299 | 30 | 7.70223e+06 | 212142 | 0.527893 | 1.10063 | 2(Loss) | true |
| Glaze | 1818.42 | 0.176041 | 7695.31ms | 500299 | 160 | 3.41367e+07 | 262383 | 0.00794464 | 1.36137 | 3(Loss) | true |
| simdjson (ondemand) | 1306.18 | 0.143264 | 5157.51ms | 500299 | 80 | 2.19089e+07 | 365281 | 0.200112 | 1.89531 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11107.3 | 0.115424 | 4347.94ms | 500299 | 1280 | 3.14663e+06 | 42955.9 | 0.00430329 | 0.222753 | 1(Win) | true |
| Glaze | 3908.09 | 0.046936 | 6255.21ms | 500299 | 2560 | 8.40588e+06 | 122086 | 0.034598 | 0.633316 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11147.1 | 0.0957903 | 4290.8ms | 500299 | 2560 | 4.30348e+06 | 42802.4 | 0.0132503 | 0.221928 | 1(Win) | true |
| Glaze | 4262.34 | 0.0813111 | 5745.26ms | 500299 | 640 | 5.30206e+06 | 111939 | 0.0908582 | 0.580721 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3901.27 | 0.0475403 | 7183.35ms | 1151920 | 1280 | 2.29386e+07 | 281589 | 0.101928 | 0.634514 | 1(Win) | true |
| Jsonifier | 3186.42 | 0.102893 | 8734.41ms | 1151920 | 160 | 2.0134e+07 | 344762 | 0.161282 | 0.776883 | 2(Loss) | true |
| Glaze | 2486.56 | 0.0765968 | 5670.04ms | 1151920 | 160 | 1.83226e+07 | 441798 | 0.0272194 | 0.995586 | 3(Loss) | true |
| simdjson (ondemand) | 2444.28 | 0.107248 | 5716.85ms | 1151920 | 80 | 1.85872e+07 | 449440 | 0.065297 | 1.01281 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4477.94 | 0.180684 | 7030.95ms | 1151920 | 1280 | 2.51501e+08 | 245326 | 0.159636 | 0.552805 | 1(Win) | true |
| Jsonifier | 3635.21 | 0.116735 | 8509.18ms | 1151920 | 320 | 3.98232e+07 | 302199 | 0.120643 | 0.680993 | 2(Loss) | true |
| Glaze | 2746.71 | 0.0398178 | 5569.57ms | 1151920 | 640 | 1.62313e+07 | 399953 | 0.00747292 | 0.901308 | 3(Loss) | true |
| simdjson (ondemand) | 2725.11 | 0.144904 | 5471.15ms | 1151920 | 40 | 1.36489e+07 | 403124 | 0.00552177 | 0.908448 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18070.3 | 0.0731161 | 7621.43ms | 1439562 | 1280 | 3.94972e+06 | 75974.1 | 0.042404 | 0.136952 | 1(Win) | true |
| Glaze | 5464.75 | 0.105347 | 6393.05ms | 1439584 | 1280 | 8.96587e+07 | 251227 | 0.0234687 | 0.452969 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17727.9 | 0.096826 | 7742.32ms | 1439562 | 640 | 3.5984e+06 | 77441.3 | 0.115764 | 0.139594 | 1(Win) | true |
| Glaze | 6508.6 | 0.140138 | 5371.75ms | 1439584 | 320 | 2.79613e+07 | 210935 | 0.0659167 | 0.380343 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2252.36 | 0.107246 | 2393.45ms | 56369 | 2560 | 1.6773e+06 | 23867.3 | 0.0381011 | 1.09785 | 1(Win) | true |
| Jsonifier (two-stage) | 1881.88 | 0.053728 | 2861.45ms | 56369 | 4890 | 1.15188e+06 | 28566 | 0.0828085 | 1.31434 | 2(Loss) | true |
| Glaze | 1636.5 | 0.109461 | 3286.51ms | 56369 | 1280 | 1.65491e+06 | 32849.1 | 0.217255 | 1.51142 | 3(Loss) | true |
| simdjson (ondemand) | 878.297 | 0.0402522 | 6117.92ms | 56369 | 4890 | 2.96815e+06 | 61206.7 | 0.119881 | 2.81767 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3023.33 | 0.130049 | 2095.02ms | 56369 | 2560 | 1.36886e+06 | 17780.9 | 0.0649458 | 0.817695 | 1(Win) | true |
| Jsonifier (two-stage) | 2356.61 | 0.144361 | 2606.48ms | 56369 | 640 | 694044 | 22811.4 | 0.0715822 | 1.04936 | 2(Loss) | true |
| Glaze | 2069.82 | 0.0806805 | 2928.85ms | 56369 | 2560 | 1.12406e+06 | 25972.1 | 0.141706 | 1.19497 | 3(Loss) | true |
| simdjson (ondemand) | 994.039 | 0.0518306 | 5753.96ms | 56369 | 2560 | 2.01134e+06 | 54080 | 0.0501686 | 2.48934 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16711.4 | 0.0658531 | 327.34ms | 56369 | 30 | 134.626 | 3216.83 | 0.0735172 | 0.146966 | 1(Win) | true |
| Glaze | 3819.24 | 0.0975614 | 1408.3ms | 56369 | 2560 | 482751 | 14075.5 | 0.0646345 | 0.647081 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16955.8 | 0.0603916 | 320.668ms | 56369 | 30 | 109.982 | 3170.47 | 0.0420371 | 0.144873 | 1(Win) | true |
| Glaze | 4100.18 | 0.153027 | 1320.66ms | 56369 | 40 | 16101.6 | 13111 | 0.0708556 | 0.602627 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2684.98 | 0.0688598 | 3021.39ms | 83958 | 2560 | 1.07948e+06 | 29820.9 | 0.0118873 | 0.9213 | 1(Win) | true |
| Jsonifier | 2134.5 | 0.0541408 | 3757.38ms | 83958 | 4890 | 2.01693e+06 | 37511.7 | 0.0682063 | 1.15904 | 2(Loss) | true |
| Glaze | 1987.79 | 0.140958 | 4012.59ms | 83958 | 640 | 2.06319e+06 | 40280.1 | 0.0739853 | 1.24466 | 3(Loss) | true |
| simdjson (ondemand) | 1278.4 | 0.0455079 | 6278.99ms | 83958 | 4890 | 3.97257e+06 | 62631.7 | 0.0129964 | 1.9358 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3367.3 | 0.0571997 | 2717.23ms | 83958 | 4890 | 904600 | 23778.3 | 0.0449723 | 0.734398 | 1(Win) | true |
| Jsonifier | 2555.28 | 0.0944346 | 3470.29ms | 83958 | 1280 | 1.12078e+06 | 31334.6 | 0.123135 | 0.968109 | 2(Loss) | true |
| Glaze | 2446.7 | 0.0605931 | 3596.88ms | 83958 | 2560 | 1.00658e+06 | 32725.1 | 0.0337476 | 1.0111 | 3(Loss) | true |
| simdjson (ondemand) | 1444.65 | 0.0508319 | 5896.89ms | 83958 | 2560 | 2.03195e+06 | 55424.4 | 0.031526 | 1.71289 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19337.8 | 0.118922 | 468.553ms | 94370 | 4890 | 149793 | 4654.01 | 0.0409331 | 0.127301 | 1(Win) | true |
| Glaze | 3453.16 | 0.101461 | 2608.11ms | 94370 | 1280 | 895036 | 26062.6 | 0.0216713 | 0.716261 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19840 | 0.035094 | 457.643ms | 94370 | 30 | 76.0276 | 4536.2 | 0.0646232 | 0.12408 | 1(Win) | true |
| Glaze | 3666.7 | 0.140352 | 2458.55ms | 94370 | 640 | 759511 | 24544.8 | 0.143681 | 0.674511 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1798.99 | 0.0635991 | 2843.29ms | 53331 | 4890 | 1.58092e+06 | 28271.6 | 0.131901 | 1.37494 | 1(Win) | true |
| Jsonifier | 1746.93 | 0.0913193 | 2917.93ms | 53331 | 2560 | 1.80957e+06 | 29114.2 | 0.0324948 | 1.41598 | 2(Loss) | true |
| Glaze | 1469.59 | 0.0748769 | 3485.96ms | 53331 | 2560 | 1.71912e+06 | 34608.7 | 0.314163 | 1.68338 | 3(Loss) | true |
| simdjson (ondemand) | 1012.47 | 0.0524378 | 5005.22ms | 53331 | 2560 | 1.77633e+06 | 50233.9 | 0.187571 | 2.44393 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2380.79 | 0.0697212 | 2605.84ms | 53331 | 4890 | 1.08481e+06 | 21362.8 | 0.061555 | 1.03861 | 1(Win) | true |
| Jsonifier | 2317.84 | 0.0943754 | 2705.88ms | 53331 | 4890 | 2.09709e+06 | 21943 | 0.223965 | 1.06688 | 2(Loss) | true |
| Glaze | 1856.88 | 0.0709135 | 3265.06ms | 53331 | 4890 | 1.84484e+06 | 27390.2 | 0.122819 | 1.33205 | 3(Loss) | true |
| simdjson (ondemand) | 1137.89 | 0.104303 | 4957.79ms | 53331 | 640 | 1.39102e+06 | 44697.2 | 0.167397 | 2.17437 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17216.7 | 0.171637 | 327.412ms | 58581 | 2560 | 79409.8 | 3244.94 | 0.00568161 | 0.142678 | 1(Win) | true |
| Glaze | 5957.55 | 0.106681 | 941.091ms | 58581 | 2560 | 256207 | 9377.55 | 0.159757 | 0.414354 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17592.6 | 0.243607 | 320.56ms | 58581 | 1280 | 76602.8 | 3175.61 | 0.0211283 | 0.139618 | 1(Win) | true |
| Glaze | 6686.43 | 0.356872 | 871.797ms | 58581 | 4890 | 4.3477e+06 | 8355.31 | 0.0448737 | 0.369142 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2261.12 | 0.0586386 | 2754.76ms | 65103 | 4890 | 1.26774e+06 | 27458.5 | 0.0414242 | 1.09377 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1660.38 | 0.0807488 | 3745.39ms | 65103 | 2560 | 2.33399e+06 | 37393.3 | 0.00103316 | 1.48994 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1654.86 | 0.150158 | 3767.54ms | 65103 | 640 | 2.03123e+06 | 37518.1 | 0.194602 | 1.49503 | 2(Tie) | true |
| simdjson (ondemand) | 1278.29 | 0.0627465 | 4875.39ms | 65103 | 2560 | 2.37774e+06 | 48570.5 | 0.110529 | 1.93566 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2912.82 | 0.103172 | 2574.16ms | 65103 | 2560 | 1.23806e+06 | 21315.1 | 0.0730467 | 0.848902 | 1(Win) | true |
| Jsonifier | 2039.23 | 0.0571062 | 3526.25ms | 65103 | 4890 | 1.47823e+06 | 30446.3 | 0.0523869 | 1.21306 | 2(Loss) | true |
| Glaze | 2026.6 | 0.150963 | 3584.92ms | 65103 | 640 | 1.36895e+06 | 30636.1 | 0.0725537 | 1.22063 | 3(Loss) | true |
| simdjson (ondemand) | 1370.9 | 0.0731711 | 5007.58ms | 65103 | 2560 | 2.81131e+06 | 45289.2 | 0.00790814 | 1.80487 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17315.7 | 0.082973 | 439.219ms | 78778 | 40 | 518.397 | 4338.75 | 0.0334086 | 0.142114 | 1(Win) | true |
| Glaze | 5116.21 | 0.0748415 | 1473.35ms | 78778 | 4890 | 590618 | 14684.4 | 0.122391 | 0.483065 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17673.1 | 0.0768287 | 432.719ms | 78778 | 30 | 320 | 4251 | 0.0258696 | 0.139275 | 1(Win) | true |
| Glaze | 5900.91 | 0.0832745 | 1284.93ms | 78778 | 40 | 4496.32 | 12731.7 | 0.00130905 | 0.418795 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2451.6 | 0.100467 | 462.137ms | 11812 | 40 | 852.42 | 4594.88 | 0.123717 | 1.00465 | 1(Win) | true |
| Jsonifier (two-stage) | 1854.4 | 0.0788262 | 612.25ms | 11812 | 40 | 917.156 | 6074.65 | 0.06279 | 1.32933 | 2(Loss) | true |
| Glaze | 1672.04 | 0.0446005 | 681.591ms | 11812 | 80 | 722.306 | 6737.15 | 0.0192923 | 1.47503 | 3(Loss) | true |
| simdjson (ondemand) | 969.886 | 0.120999 | 1162.45ms | 11812 | 4890 | 965775 | 11614.6 | 0.061635 | 2.5467 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2753.14 | 0.0287389 | 450.417ms | 11812 | 80 | 110.617 | 4091.62 | 0.0610631 | 0.893739 | 1(Win) | true |
| Jsonifier (two-stage) | 2040.68 | 0.0551809 | 596.412ms | 11812 | 40 | 371.138 | 5520.12 | 0.279554 | 1.20744 | 2(Loss) | true |
| Glaze | 1848.68 | 0.176382 | 650.709ms | 11812 | 1280 | 147857 | 6093.43 | 0.056868 | 1.33366 | 3(Loss) | true |
| simdjson (ondemand) | 1022.56 | 0.217128 | 1143.36ms | 11812 | 1280 | 732331 | 11016.2 | 0.0926112 | 2.41476 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12969.5 | 0.071092 | 90.0192ms | 11812 | 80 | 30.5024 | 868.562 | 0.113823 | 0.184944 | 1(Win) | true |
| Glaze | 3215.23 | 0.147498 | 353.395ms | 11812 | 4890 | 130589 | 3503.58 | 0.0106562 | 0.76444 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13558.9 | 0.0521359 | 85.7676ms | 11812 | 160 | 30.0188 | 830.806 | 0.0971386 | 0.176743 | 1(Win) | true |
| Glaze | 3528.96 | 0.212246 | 324.535ms | 11812 | 30 | 1377.06 | 3192.1 | 0.197753 | 0.695993 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3554.31 | 0.102696 | 684.255ms | 25388 | 4890 | 239312 | 6811.97 | 0.058654 | 0.69381 | 1(Win) | true |
| Jsonifier | 3128.62 | 0.129392 | 781.03ms | 25388 | 40 | 4010.75 | 7738.85 | 0.0751054 | 0.78876 | 2(Loss) | true |
| Glaze | 2468.95 | 0.154324 | 984.497ms | 25388 | 1280 | 293162 | 9806.55 | 0.0505099 | 1.00014 | 3(Loss) | true |
| simdjson (ondemand) | 1973.03 | 0.134018 | 1231.32ms | 25388 | 1280 | 346198 | 12271.4 | 0.0234993 | 1.25204 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3828.15 | 0.0589402 | 671.239ms | 25388 | 40 | 555.856 | 6324.7 | 0.0231841 | 0.644156 | 1(Win) | true |
| Jsonifier | 3360.86 | 0.0261793 | 762.183ms | 25388 | 40 | 142.276 | 7204.07 | 0.00381743 | 0.734047 | 2(Loss) | true |
| Glaze | 2645.4 | 0.053441 | 958.08ms | 25388 | 30 | 717.702 | 9152.43 | 0.0440879 | 0.933195 | 3(Loss) | true |
| simdjson (ondemand) | 2075.52 | 0.0837378 | 1208.64ms | 25388 | 4890 | 466610 | 11665.4 | 0.0178979 | 1.1899 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 13254.6 | 17.2406 | 186.923ms | 31235 | 40 | 6.00503e+06 | 2247.38 | 3.01054 | 0.184621 | -(Win) | false |
| Glaze | 5250.59 | 0.085945 | 573.417ms | 31235 | 40 | 950.974 | 5673.27 | 0.0836489 | 0.469242 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20361.5 | 0.0363308 | 149.345ms | 31235 | 160 | 45.1993 | 1462.96 | 0.0602739 | 0.119491 | 1(Win) | true |
| Glaze | 5722.01 | 0.0765806 | 524.31ms | 31235 | 30 | 476.809 | 5205.87 | 0.0256056 | 0.430566 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2815.39 | 0.0563346 | 3684.72ms | 108313 | 4890 | 2.08902e+06 | 36689.5 | 0.169677 | 0.878759 | 1(Win) | true |
| Jsonifier (two-stage) | 2376.59 | 0.0618267 | 4351.97ms | 108313 | 4890 | 3.53114e+06 | 43463.7 | 0.0390132 | 1.04111 | 2(Loss) | true |
| Glaze | 1749.58 | 0.0806123 | 5998.43ms | 108313 | 640 | 1.4497e+06 | 59040.1 | 0.00375553 | 1.41447 | 3(Loss) | true |
| simdjson (ondemand) | 717.783 | 0.0837882 | 7369.13ms | 108313 | 1280 | 1.86102e+07 | 143909 | 0.0467539 | 3.4486 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3220.49 | 0.137072 | 3385.51ms | 108313 | 640 | 1.23706e+06 | 32074.4 | 0.0457642 | 0.768143 | 1(Win) | true |
| Jsonifier (two-stage) | 2641.77 | 0.0618629 | 4077.24ms | 108313 | 4890 | 2.86115e+06 | 39100.8 | 0.0127402 | 0.936545 | 2(Loss) | true |
| Glaze | 1878.8 | 0.0622799 | 5649.14ms | 108313 | 2560 | 3.00149e+06 | 54979.5 | 0.000655069 | 1.31715 | 3(Loss) | true |
| simdjson (ondemand) | 737.416 | 0.045615 | 7255.14ms | 108313 | 1280 | 5.22589e+06 | 140077 | 0.00559711 | 3.35673 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21768.7 | 0.0518159 | 481.555ms | 108313 | 30 | 181.361 | 4745.13 | 0.0217814 | 0.113084 | 1(Win) | true |
| Glaze | 3918.77 | 0.13139 | 2640.68ms | 108313 | 640 | 767656 | 26359.1 | 0.00809663 | 0.631166 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22146 | 0.0266625 | 474.712ms | 108313 | 80 | 123.726 | 4664.29 | 0.0431656 | 0.111176 | 1(Win) | true |
| Glaze | 4190.81 | 0.0665984 | 2481.41ms | 108313 | 30 | 8083.79 | 24648.1 | 0.0519041 | 0.590126 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3746.94 | 0.0786944 | 4680.88ms | 183677 | 4890 | 6.6184e+06 | 46749.6 | 0.083361 | 0.660351 | 1(Win) | true |
| Jsonifier | 2276.09 | 0.043812 | 7704.87ms | 183677 | 4890 | 5.5594e+06 | 76960.2 | 0.0128982 | 1.08737 | 2(Loss) | true |
| Glaze | 2268.18 | 0.0781481 | 7745.43ms | 183677 | 640 | 2.33115e+06 | 77228.4 | 0.0177182 | 1.09117 | 3(Loss) | true |
| simdjson (ondemand) | 1182.01 | 0.0409248 | 7571.32ms | 183677 | 2560 | 9.41635e+06 | 148195 | 0.15774 | 2.0942 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4190.57 | 0.0468301 | 4353.99ms | 183677 | 4890 | 1.8738e+06 | 41800.6 | 0.00923286 | 0.590431 | 1(Win) | true |
| Jsonifier | 2430.18 | 0.053232 | 7386.8ms | 183677 | 2560 | 3.76894e+06 | 72080.3 | 0.017894 | 1.01841 | 2(Loss) | true |
| Glaze | 2394.12 | 0.107931 | 7583.37ms | 183677 | 320 | 1.99555e+06 | 73165.9 | 0.0546061 | 1.03376 | 3(Loss) | true |
| simdjson (ondemand) | 1220.99 | 0.0569277 | 7421.99ms | 183677 | 2560 | 1.70754e+07 | 143464 | 0.00343686 | 2.0273 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 25230.3 | 0.135569 | 814.82ms | 213963 | 2560 | 307747 | 8087.52 | 0.0774031 | 0.0978206 | 1(Win) | true |
| Glaze | 3878.68 | 0.0405993 | 5266.31ms | 213963 | 4890 | 2.23077e+06 | 52608.4 | 0.0573892 | 0.638003 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 25519.3 | 0.11452 | 806.436ms | 213963 | 2560 | 214656 | 7995.96 | 0.235418 | 0.0967099 | 1(Win) | true |
| Glaze | 4122.37 | 0.038082 | 4954.11ms | 213963 | 4890 | 1.73753e+06 | 49498.4 | 0.0324744 | 0.600268 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 867.085 | 0.0385644 | 6241ms | 1834197 | 30 | 1.81578e+07 | 2.01737e+06 | 0.16394 | 2.85526 | 1(Win) | true |
| Jsonifier (two-stage) | 792.852 | 0.0588476 | 7059ms | 1834197 | 30 | 5.05693e+07 | 2.20625e+06 | 0.166835 | 3.12261 | 2(Loss) | true |
| Glaze | 679.315 | 0.050727 | 7993.22ms | 1834197 | 160 | 2.72991e+08 | 2.57499e+06 | 0.030877 | 3.64452 | 3(Loss) | true |
| simdjson (ondemand) | 621.015 | 0.120913 | 8759.47ms | 1834197 | 80 | 9.27952e+08 | 2.81672e+06 | 0.0690063 | 3.98656 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 975.857 | 0.089618 | 6283.57ms | 1834197 | 30 | 7.74162e+07 | 1.7925e+06 | 0.202551 | 2.537 | 1(Win) | true |
| Jsonifier (two-stage) | 866.852 | 0.225145 | 7522.69ms | 1834197 | 30 | 6.19225e+08 | 2.01791e+06 | 0.772309 | 2.85604 | 2(Loss) | true |
| Glaze | 749.349 | 0.0373743 | 7997ms | 1834197 | 40 | 3.0446e+07 | 2.33433e+06 | 0.000603318 | 3.3039 | 3(Loss) | true |
| simdjson (ondemand) | 690.704 | 0.0504622 | 8621.95ms | 1834197 | 30 | 4.89961e+07 | 2.53253e+06 | 0.00328383 | 3.58443 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1254.85 | 0.117501 | 8787.66ms | 1834197 | 30 | 8.04842e+07 | 1.39397e+06 | 0.0828777 | 1.97294 | 1(Win) | true |
| Glaze | 667.234 | 0.0552845 | 8197.79ms | 1833577 | 40 | 8.39669e+07 | 2.62072e+06 | 0.0317017 | 3.71052 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1256.21 | 0.0363344 | 8794.01ms | 1834197 | 160 | 4.09565e+07 | 1.39246e+06 | 0.163565 | 1.9708 | 1(Win) | true |
| Glaze | 664.579 | 0.0632587 | 8143.45ms | 1833577 | 160 | 4.43268e+08 | 2.63119e+06 | 0.370154 | 3.72534 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2782.37 | 0.116222 | 7863.93ms | 7351818 | 160 | 1.37232e+09 | 2.51988e+06 | 0.55611 | 0.889808 | 1(Win) | true |
| Jsonifier | 2569.69 | 0.237291 | 8526.12ms | 7351818 | 30 | 1.25751e+09 | 2.72844e+06 | 0.353582 | 0.963446 | 2(Loss) | true |
| simdjson (ondemand) | 2249.12 | 0.0539216 | 9716.38ms | 7351818 | 160 | 4.52074e+08 | 3.11733e+06 | 0.110742 | 1.10077 | 3(Loss) | true |
| Glaze | 2152.54 | 0.0782262 | 10082.1ms | 7351818 | 80 | 5.19377e+08 | 3.2572e+06 | 0.287616 | 1.15016 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3059.58 | 0.144885 | 7930.87ms | 7351818 | 40 | 4.40931e+08 | 2.29157e+06 | 0.11448 | 0.809186 | 1(Win) | true |
| Jsonifier | 2805.92 | 0.101953 | 8487.61ms | 7351818 | 40 | 2.59596e+08 | 2.49874e+06 | 0.0845513 | 0.882338 | 2(Loss) | true |
| simdjson (ondemand) | 2472.22 | 0.108405 | 9547.76ms | 7351818 | 80 | 7.5615e+08 | 2.83601e+06 | 0.0673547 | 1.00143 | 3(Loss) | true |
| Glaze | 2330.21 | 0.0652234 | 10139.7ms | 7351818 | 80 | 3.08102e+08 | 3.00884e+06 | 0.111118 | 1.06246 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5332.72 | 0.0869672 | 5520.55ms | 9930848 | 30 | 7.15661e+07 | 1.77598e+06 | 0.0492591 | 0.464249 | 1(Win) | true |
| Glaze | 3647.05 | 0.203712 | 8063.07ms | 9930228 | 80 | 2.23852e+09 | 2.59668e+06 | 0.285253 | 0.678817 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5329.07 | 0.0651202 | 5517.65ms | 9930848 | 80 | 1.0715e+08 | 1.77719e+06 | 0.144424 | 0.464563 | 1(Win) | true |
| Glaze | 3903.43 | 0.302405 | 7569.34ms | 9930228 | 160 | 8.61234e+09 | 2.42612e+06 | 0.515486 | 0.634251 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 859.62 | 0.489052 | 6242.3ms | 1834197 | 30 | 2.97105e+09 | 2.03488e+06 | 1.35035 | 2.88004 | 1(Win) | true |
| Jsonifier (two-stage) | 805.797 | 0.0643387 | 6795.25ms | 1834197 | 80 | 1.56055e+08 | 2.1708e+06 | 0.537635 | 3.07243 | 2(Loss) | true |
| Glaze | 688.644 | 0.0595634 | 8018ms | 1834197 | 40 | 9.15634e+07 | 2.5401e+06 | 0.345769 | 3.59508 | 3(Loss) | true |
| simdjson (ondemand) | 612.798 | 0.0949619 | 8861.38ms | 1834197 | 40 | 2.93911e+08 | 2.85449e+06 | 0.030721 | 4.03992 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 976.336 | 0.108974 | 6288.66ms | 1834197 | 80 | 3.04952e+08 | 1.79162e+06 | 0.730049 | 2.53575 | 1(Win) | true |
| Jsonifier (two-stage) | 881.788 | 0.121794 | 6901.25ms | 1834197 | 40 | 2.33492e+08 | 1.98373e+06 | 0.00665795 | 2.80766 | 2(Loss) | true |
| Glaze | 744.023 | 0.0746181 | 8050.15ms | 1834197 | 160 | 4.92411e+08 | 2.35104e+06 | 0.363994 | 3.32756 | 3(Loss) | true |
| simdjson (ondemand) | 683.031 | 0.191672 | 8635.73ms | 1834197 | 40 | 9.63808e+08 | 2.56098e+06 | 0.233784 | 3.62453 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1259.68 | 0.0240151 | 8758.45ms | 1834197 | 320 | 3.55871e+07 | 1.38863e+06 | 0.0322638 | 1.96538 | 1(Win) | true |
| Glaze | 657.227 | 0.0276088 | 8251.51ms | 1833577 | 160 | 8.63341e+07 | 2.66062e+06 | 0.136873 | 3.76698 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1258.76 | 0.0569679 | 8817.7ms | 1834197 | 80 | 5.01365e+07 | 1.38964e+06 | 0.168268 | 1.96679 | 1(Win) | true |
| Glaze | 670.653 | 0.0221779 | 8092.85ms | 1833577 | 160 | 5.3501e+07 | 2.60736e+06 | 0.0711509 | 3.6916 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2808.91 | 0.084158 | 7752.58ms | 7351818 | 80 | 3.53017e+08 | 2.49607e+06 | 0.192477 | 0.881392 | 1(Win) | true |
| Jsonifier | 2623.17 | 0.0882834 | 8287.68ms | 7351818 | 40 | 2.22718e+08 | 2.67281e+06 | 0.068345 | 0.943811 | 2(Loss) | true |
| simdjson (ondemand) | 2237.59 | 0.102846 | 9817.54ms | 7351818 | 30 | 3.11546e+08 | 3.13339e+06 | 0.439861 | 1.10644 | 3(Loss) | true |
| Glaze | 2146.51 | 0.0912205 | 10202.4ms | 7351818 | 160 | 1.42045e+09 | 3.26634e+06 | 0.0442099 | 1.15338 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3088 | 0.136304 | 7742.73ms | 7351818 | 40 | 3.83103e+08 | 2.27048e+06 | 0.139357 | 0.801734 | 1(Win) | true |
| Jsonifier | 2864.59 | 0.136128 | 8278.62ms | 7351818 | 40 | 4.44034e+08 | 2.44755e+06 | 0.0645104 | 0.864265 | 2(Loss) | true |
| simdjson (ondemand) | 2438.51 | 0.134756 | 9697.25ms | 7351818 | 40 | 6.00475e+08 | 2.87521e+06 | 0.0830712 | 1.01527 | 3(Loss) | true |
| Glaze | 2322.13 | 0.0474258 | 10095.5ms | 7351818 | 160 | 3.28069e+08 | 3.01931e+06 | 0.42869 | 1.06616 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5290.64 | 0.0556445 | 5558.47ms | 9930848 | 40 | 3.96881e+07 | 1.7901e+06 | 0.205118 | 0.467952 | 1(Win) | true |
| Glaze | 3029.08 | 0.23109 | 9679.05ms | 9930228 | 80 | 4.17589e+09 | 3.12643e+06 | 0.391164 | 0.817275 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5302.59 | 0.0801112 | 5547.37ms | 9930848 | 40 | 8.18925e+07 | 1.78607e+06 | 0.0580328 | 0.466887 | 1(Win) | true |
| Glaze | 3918.77 | 0.12488 | 7529.9ms | 9930228 | 30 | 2.7323e+08 | 2.41662e+06 | 0.0449599 | 0.631762 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1290.81 | 0.108805 | 8800.6ms | 461466 | 320 | 4.40357e+07 | 340939 | 0.0221371 | 1.91775 | 1(Win) | true |
| Glaze | 1104.72 | 0.0866902 | 5068.37ms | 461466 | 320 | 3.81647e+07 | 398369 | 0.288477 | 2.2409 | 2(Loss) | true |
| Jsonifier (two-stage) | 1068.42 | 0.385141 | 5127.07ms | 461466 | 40 | 1.00669e+08 | 411907 | 0.46364 | 2.31707 | 3(Loss) | true |
| simdjson (ondemand) | 779.072 | 0.159282 | 7198.48ms | 461466 | 320 | 2.59063e+08 | 564888 | 0.132383 | 3.17766 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1745.07 | 0.0968211 | 8191.86ms | 461466 | 640 | 3.81568e+07 | 252189 | 0.0250737 | 1.41856 | 1(Win) | true |
| Jsonifier (two-stage) | 1455.75 | 0.0981323 | 9611.96ms | 461466 | 1280 | 1.12652e+08 | 302310 | 0.787276 | 1.70048 | 2(Loss) | true |
| Glaze | 1381.3 | 0.0671527 | 9858.02ms | 461466 | 320 | 1.46481e+07 | 318605 | 0.447233 | 1.7922 | 3(Loss) | true |
| simdjson (ondemand) | 965.606 | 0.123452 | 6583.79ms | 461466 | 160 | 5.06523e+07 | 455764 | 0.0866825 | 2.56378 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13385.9 | 0.0934578 | 3300.54ms | 461466 | 2560 | 2.41688e+06 | 32876.9 | 0.0874108 | 0.184765 | 1(Win) | true |
| Glaze | 3024.39 | 0.0947063 | 7458.08ms | 461466 | 640 | 1.21546e+07 | 145513 | 0.236391 | 0.818405 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13433.1 | 0.408984 | 3324.09ms | 461466 | 160 | 2.87248e+06 | 32761.4 | 0.0328595 | 0.184106 | 1(Win) | true |
| Glaze | 3206.34 | 0.0896461 | 6987.58ms | 461466 | 2560 | 3.87583e+07 | 137256 | 0.311406 | 0.771996 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1802.76 | 0.175039 | 9817.94ms | 728486 | 40 | 1.82011e+07 | 385376 | 0.0275695 | 1.37317 | 1(Win) | true |
| Jsonifier | 1445.88 | 0.412441 | 5967.46ms | 728486 | 40 | 1.57095e+08 | 480495 | 0.333315 | 1.71218 | 2(Loss) | true |
| Glaze | 1410.36 | 0.24656 | 6294.08ms | 728486 | 30 | 4.42536e+07 | 492596 | 0.498877 | 1.7553 | 3(Loss) | true |
| simdjson (ondemand) | 1254.09 | 0.132068 | 7053.69ms | 728486 | 80 | 4.28223e+07 | 553980 | 0.0290788 | 1.97405 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2403.59 | 0.0455747 | 9196.82ms | 728486 | 1280 | 2.22115e+07 | 289042 | 0.0936173 | 1.02992 | 1(Win) | true |
| Jsonifier | 1830.73 | 0.251231 | 5619.69ms | 728486 | 40 | 3.63581e+07 | 379488 | 0.311946 | 1.35225 | 2(Loss) | true |
| Glaze | 1672.94 | 0.323068 | 6133.66ms | 728486 | 30 | 5.39999e+07 | 415281 | 0.470754 | 1.47981 | 3(Loss) | true |
| simdjson (ondemand) | 1559.56 | 0.171421 | 6638.94ms | 728486 | 30 | 1.74939e+07 | 445470 | 0.267836 | 1.58736 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17348 | 0.235384 | 4629.71ms | 837491 | 320 | 3.75808e+06 | 46039.6 | 0.104074 | 0.142611 | 1(Win) | true |
| Glaze | 3520.19 | 0.119202 | 5828.04ms | 837491 | 640 | 4.6814e+07 | 226889 | 0.0411769 | 0.703185 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17321.2 | 0.207612 | 4520.33ms | 837491 | 320 | 2.93266e+06 | 46110.8 | 0.150149 | 0.142835 | 1(Win) | true |
| Glaze | 3903.63 | 0.268931 | 5252.53ms | 837491 | 80 | 2.42212e+07 | 204603 | 0.0428635 | 0.634144 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10580.5 | 0.106159 | 4226.79ms | 466906 | 1280 | 2.55489e+06 | 42084.6 | 0.0763207 | 0.233838 | 1(Win) | true |
| Jsonifier (two-stage) | 10533.9 | 0.0814777 | 4231.61ms | 466906 | 2560 | 3.0367e+06 | 42271 | 0.0260488 | 0.234851 | 2(Loss) | true |
| simdjson (ondemand) | 8346.43 | 0.093088 | 5422.78ms | 466906 | 2560 | 6.31372e+06 | 53349.3 | 0.0474963 | 0.296466 | 3(Loss) | true |
| Glaze | 3429.03 | 0.0759568 | 6722.57ms | 466906 | 640 | 6.22629e+06 | 129855 | 0.30934 | 0.721871 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 10822.7 | 0.201693 | 4202.89ms | 466906 | 160 | 1.10177e+06 | 41143 | 0.0656577 | 0.228611 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 10820.7 | 0.0604542 | 4178.67ms | 466906 | 4890 | 3.02629e+06 | 41150.4 | 0.0280054 | 0.228641 | 1(Tie) | true |
| simdjson (ondemand) | 8418.08 | 0.0904682 | 5457.85ms | 466906 | 4890 | 1.11978e+07 | 52895.2 | 0.715985 | 0.293935 | 3(Loss) | true |
| Glaze | 3460.66 | 0.0662201 | 6622.58ms | 466906 | 2560 | 1.85849e+07 | 128668 | 0.168551 | 0.715276 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11628.5 | 0.339293 | 5317.33ms | 631514 | 80 | 2.47035e+06 | 51791.6 | 0.173568 | 0.212728 | 1(Win) | true |
| Jsonifier (two-stage) | 11510.1 | 0.0963502 | 5246.01ms | 631514 | 1280 | 3.25326e+06 | 52324.2 | 0.0805205 | 0.214927 | 2(Loss) | true |
| simdjson (ondemand) | 9615.43 | 0.123815 | 6295.98ms | 631514 | 640 | 3.84905e+06 | 62634.6 | 0.181952 | 0.257306 | 3(Loss) | true |
| Glaze | 4246.97 | 0.0391948 | 7254.27ms | 631514 | 2560 | 7.90868e+06 | 141809 | 0.0661617 | 0.582852 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 11892.3 | 0.243275 | 5239.06ms | 631514 | 160 | 2.42855e+06 | 50642.6 | 0.0857607 | 0.208043 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 11860.5 | 0.0653855 | 5166.02ms | 631514 | 4890 | 5.39057e+06 | 50778.6 | 0.207834 | 0.208608 | 1(Tie) | true |
| simdjson (ondemand) | 9729.87 | 0.12149 | 6241.6ms | 631514 | 640 | 3.61923e+06 | 61897.9 | 0.00785758 | 0.254328 | 3(Loss) | true |
| Glaze | 4279.38 | 0.059213 | 7220.79ms | 631514 | 1280 | 8.88893e+06 | 140735 | 0.062644 | 0.578439 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1784.83 | 0.0603119 | 6364.93ms | 466906 | 1280 | 2.89787e+07 | 249478 | 0.0791757 | 1.38687 | 1(Win) | true |
| Jsonifier | 1777.9 | 0.0615365 | 6463.56ms | 466906 | 1280 | 3.04032e+07 | 250451 | 0.127796 | 1.39231 | 2(Loss) | true |
| Glaze | 1729.18 | 0.0841798 | 6607.43ms | 466906 | 640 | 3.0073e+07 | 257508 | 0.130653 | 1.43159 | 3(Loss) | true |
| simdjson (ondemand) | 938.849 | 0.134776 | 6032.99ms | 466906 | 80 | 3.26877e+07 | 474279 | 0.0887 | 2.63683 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2206.64 | 0.285474 | 5638.43ms | 466906 | 40 | 1.32736e+07 | 201789 | 0.0290317 | 1.12179 | 1(Win) | true |
| Glaze | 2164.65 | 0.0751839 | 5909.93ms | 466906 | 640 | 1.53079e+07 | 205704 | 0.0502381 | 1.1436 | 2(Loss) | true |
| Jsonifier | 2150.22 | 0.144575 | 6050.28ms | 466906 | 320 | 2.86836e+07 | 207084 | 0.0777008 | 1.15124 | 3(Loss) | true |
| simdjson (ondemand) | 1029.93 | 0.0891738 | 5835.96ms | 466906 | 160 | 2.37815e+07 | 432337 | 0.0244079 | 2.40367 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17322.5 | 0.158561 | 2624.54ms | 475954 | 1280 | 2.2096e+06 | 26203.2 | 0.00120752 | 0.142769 | 1(Win) | true |
| Glaze | 5811.07 | 0.0989282 | 7808.87ms | 475954 | 2560 | 1.52862e+07 | 78110.5 | 0.0560618 | 0.425865 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18361.7 | 0.681907 | 2564.49ms | 475954 | 40 | 1.13662e+06 | 24720.3 | 0.0874023 | 0.134681 | 1(Win) | true |
| Glaze | 6510.67 | 0.0503967 | 6969.05ms | 475954 | 4890 | 6.0366e+06 | 69717.1 | 0.303383 | 0.380114 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2319.51 | 0.144883 | 6724.1ms | 631514 | 320 | 4.52853e+07 | 259649 | 0.0851042 | 1.06721 | 1(Win) | true |
| Glaze | 1944.57 | 0.327146 | 8043.7ms | 631514 | 30 | 3.07981e+07 | 309713 | 0.100981 | 1.27304 | 2(Loss) | true |
| Jsonifier | 1681.71 | 0.089415 | 9187.03ms | 631514 | 1280 | 1.31248e+08 | 358122 | 0.0671219 | 1.47204 | 3(Loss) | true |
| simdjson (ondemand) | 1242.39 | 0.123619 | 6363.65ms | 631514 | 160 | 5.74574e+07 | 484759 | 0.147352 | 1.99261 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2859.53 | 0.0694276 | 6333.06ms | 631514 | 1280 | 2.73686e+07 | 210615 | 0.0393203 | 0.865659 | 1(Win) | true |
| Glaze | 2188.95 | 0.293269 | 7725.15ms | 631514 | 40 | 2.60427e+07 | 275136 | 0.246969 | 1.13092 | 2(Loss) | true |
| Jsonifier | 1956.14 | 0.0979848 | 8711.34ms | 631514 | 320 | 2.91229e+07 | 307882 | 0.323782 | 1.26553 | 3(Loss) | true |
| simdjson (ondemand) | 1357.54 | 0.0582206 | 5975.78ms | 631514 | 640 | 4.26967e+07 | 443639 | 0.0459801 | 1.82361 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16845.5 | 0.152274 | 4138.56ms | 716365 | 1280 | 4.88163e+06 | 40555.7 | 0.170929 | 0.146873 | 1(Win) | true |
| Glaze | 4536.89 | 0.170524 | 7595.12ms | 716365 | 1280 | 8.43979e+07 | 150583 | 0.79542 | 0.545546 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16919.6 | 0.204653 | 4064.41ms | 716365 | 320 | 2.18513e+06 | 40378 | 0.0180217 | 0.146227 | 1(Win) | true |
| Glaze | 5548.23 | 0.346051 | 6354.62ms | 716365 | 30 | 5.44704e+06 | 123134 | 0.192642 | 0.446132 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2651.03 | 0.0363706 | 97.9441ms | 2632 | 320 | 37.9484 | 946.828 | 0.0822499 | 0.908031 | 1(Win) | true |
| Jsonifier (two-stage) | 2535.71 | 0.0604082 | 101.618ms | 2632 | 320 | 114.424 | 989.891 | 0.109665 | 0.949855 | 2(Loss) | true |
| Glaze | 2101.47 | 0.0845105 | 123.115ms | 2632 | 80 | 81.515 | 1194.44 | 0.114201 | 1.15289 | 3(Loss) | true |
| simdjson (ondemand) | 1566.91 | 0.148237 | 164.725ms | 2632 | 40 | 225.558 | 1601.92 | 0.114055 | 1.55433 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2993.53 | 0.104598 | 92.8636ms | 2632 | 40 | 30.7692 | 838.5 | 0.0476815 | 0.801814 | 1(Win) | true |
| Jsonifier (two-stage) | 2968.6 | 0.0289763 | 92.945ms | 2632 | 640 | 38.4179 | 845.539 | 0.053746 | 0.808305 | 2(Loss) | true |
| Glaze | 2459.05 | 0.0879574 | 109.687ms | 2632 | 40 | 32.2436 | 1020.75 | 0.0505908 | 0.981858 | 3(Loss) | true |
| simdjson (ondemand) | 1766.62 | 0.160497 | 154.328ms | 2632 | 30 | 156.006 | 1420.83 | 0.0468988 | 1.3734 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12436.1 | 0.111581 | 22.6604ms | 2632 | 320 | 16.2306 | 201.838 | 0.132975 | 0.174408 | 1(Win) | true |
| Glaze | 4018.2 | 0.149622 | 65.4377ms | 2632 | 40 | 34.9429 | 624.675 | 0.0120077 | 0.589723 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14117.9 | 0.0816914 | 20.2815ms | 2632 | 1280 | 27.002 | 177.794 | 0.467972 | 0.150332 | 1(Win) | true |
| Glaze | 4334.95 | 0.0650889 | 60.8601ms | 2632 | 320 | 45.4536 | 579.031 | 0.0205042 | 0.546125 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3161.28 | 0.333634 | 104.327ms | 3370 | 2560 | 29451.9 | 1016.64 | 0.0060705 | 0.762593 | 1(Win) | true |
| Jsonifier | 2333.02 | 0.0562124 | 139.893ms | 3370 | 80 | 47.9707 | 1377.56 | 0.0899134 | 1.04095 | 2(Loss) | true |
| Glaze | 2296.41 | 0.104801 | 142.54ms | 3370 | 40 | 86.0506 | 1399.53 | 0.114788 | 1.05734 | 3(Loss) | true |
| simdjson (ondemand) | 1919.73 | 0.0753055 | 170.774ms | 3370 | 160 | 254.303 | 1674.13 | 0.0526115 | 1.2696 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3603.21 | 0.084778 | 98.2962ms | 3370 | 80 | 45.7443 | 891.95 | 0.0897716 | 0.667125 | 1(Win) | true |
| Glaze | 2732.73 | 0.0418755 | 127.016ms | 3370 | 160 | 38.8066 | 1176.07 | 0.0356186 | 0.885888 | 2(Loss) | true |
| Jsonifier | 2631.26 | 0.0287505 | 132.492ms | 3370 | 320 | 39.4614 | 1221.42 | 0.0829638 | 0.920691 | 3(Loss) | true |
| simdjson (ondemand) | 2189.41 | 0.0675822 | 159.024ms | 3370 | 320 | 314.934 | 1467.92 | 0.0749922 | 1.11037 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13107 | 0.343648 | 28.7628ms | 3643 | 30 | 24.892 | 265.067 | 0.012577 | 0.170766 | 1(Win) | true |
| Glaze | 4459.88 | 0.0863895 | 82.0199ms | 3682 | 80 | 37.0112 | 787.337 | 0.339312 | 0.538019 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15508.8 | 0.0669232 | 24.8115ms | 3643 | 1280 | 28.7691 | 224.017 | 0.0788787 | 0.141495 | 1(Win) | true |
| Glaze | 4816.28 | 0.138344 | 76.1115ms | 3682 | 80 | 81.3867 | 729.075 | 0.171745 | 0.496721 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1068.9 | 0.328353 | 414.408ms | 4630 | 640 | 117748 | 4130.91 | 0.1201 | 2.30201 | 1(Win) | true |
| Jsonifier (two-stage) | 1004.65 | 0.142591 | 442.241ms | 4630 | 40 | 1570.99 | 4395.07 | 0.00322341 | 2.44991 | 2(Loss) | true |
| Glaze | 766.426 | 0.0944433 | 582.226ms | 4630 | 40 | 1184.2 | 5761.18 | 0.1015 | 3.21612 | 3(Loss) | true |
| simdjson (ondemand) | 733.31 | 0.226502 | 606.924ms | 4630 | 1280 | 238091 | 6021.34 | 0.0129374 | 3.36105 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1337.02 | 0.0991674 | 410.257ms | 4630 | 40 | 429.026 | 3302.5 | 0.420637 | 1.83752 | 1(Win) | true |
| Jsonifier (two-stage) | 1207.62 | 0.139207 | 442.184ms | 4630 | 4890 | 126688 | 3656.37 | 0.19588 | 2.03537 | 2(Loss) | true |
| Glaze | 905.395 | 0.11022 | 575.562ms | 4630 | 4890 | 141292 | 4876.89 | 0.78339 | 2.72013 | 3(Loss) | true |
| simdjson (ondemand) | 833.705 | 0.122605 | 611.453ms | 4630 | 40 | 1686.6 | 5296.25 | 0.0425009 | 2.95418 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2030 | 0.0222418 | 221.396ms | 4630 | 160 | 37.4481 | 2175.13 | 0.00086201 | 1.2057 | 1(Win) | true |
| Glaze | 1018.24 | 0.0400571 | 445.511ms | 4630 | 80 | 241.385 | 4336.41 | 0.00259424 | 2.4167 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2043.71 | 0.0439228 | 223.593ms | 4630 | 30 | 27.0161 | 2160.53 | 0.0926555 | 1.19683 | 1(Win) | true |
| Glaze | 999.905 | 0.0261244 | 432.517ms | 4630 | 30 | 39.9264 | 4415.93 | 0.0686435 | 2.4607 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2266.7 | 0.457048 | 490.944ms | 11579 | 320 | 158646 | 4871.67 | 0.272271 | 1.08645 | 1(Win) | true |
| Jsonifier | 2070.86 | 0.139805 | 543.512ms | 11579 | 30 | 1667.27 | 5332.37 | 0.0249983 | 1.18977 | 2(Loss) | true |
| simdjson (ondemand) | 1716.43 | 0.225387 | 651.779ms | 11579 | 40 | 8410.2 | 6433.45 | 0.152301 | 1.43596 | 3(Loss) | true |
| Glaze | 1581.39 | 0.192652 | 698.983ms | 11579 | 1280 | 231645 | 6982.86 | 0.0146431 | 1.55989 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2764.98 | 0.0822517 | 492.416ms | 11579 | 30 | 323.72 | 3993.73 | 0.0992237 | 0.889714 | 1(Win) | true |
| Jsonifier | 2498.17 | 0.0564242 | 549.551ms | 11579 | 30 | 186.616 | 4420.27 | 0.339696 | 0.985439 | 2(Loss) | true |
| simdjson (ondemand) | 1875.82 | 0.190814 | 678.872ms | 11579 | 2560 | 323014 | 5886.8 | 0.274797 | 1.31336 | 3(Loss) | true |
| Glaze | 1814.86 | 0.0492974 | 712.717ms | 11579 | 30 | 269.913 | 6084.53 | 0.157529 | 1.35855 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5737.17 | 0.0705175 | 252.257ms | 14795 | 30 | 90.2299 | 2459.33 | 0.0664578 | 0.427257 | 1(Win) | true |
| Glaze | 3328 | 0.0507686 | 440.818ms | 14795 | 80 | 370.631 | 4239.66 | 0.0592267 | 0.739374 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5894.26 | 0.0239428 | 243.448ms | 14795 | 160 | 52.5583 | 2393.79 | 0.0857117 | 0.415408 | 1(Win) | true |
| Glaze | 3690.94 | 0.0716855 | 383.678ms | 14795 | 30 | 225.289 | 3822.77 | 0.0514726 | 0.666203 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1783.81 | 0.33253 | 175.629ms | 3223 | 1280 | 42023.8 | 1723.1 | 0.0612164 | 1.36654 | 1(Win) | true |
| Jsonifier (two-stage) | 1597.16 | 0.236641 | 194.854ms | 3223 | 2560 | 53093.8 | 1924.47 | 0.0612555 | 1.52843 | 2(Loss) | true |
| Glaze | 1382.75 | 0.0457575 | 227.238ms | 3223 | 320 | 331.062 | 2222.88 | 0.0775213 | 1.76942 | 3(Loss) | true |
| simdjson (ondemand) | 1086.48 | 0.138822 | 287.295ms | 3223 | 40 | 616.948 | 2829.03 | 0.369864 | 2.25693 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2240.71 | 0.146469 | 158.558ms | 3223 | 40 | 161.474 | 1371.75 | 0.229108 | 1.08439 | 1(Win) | true |
| Jsonifier (two-stage) | 1934.19 | 0.181882 | 178.665ms | 3223 | 4890 | 40851.9 | 1589.14 | 0.0201404 | 1.25921 | 2(Loss) | true |
| Glaze | 1578.06 | 0.543592 | 209.886ms | 3223 | 1280 | 143493 | 1947.77 | 0.32272 | 1.54819 | 3(Loss) | true |
| simdjson (ondemand) | 1235.27 | 0.11828 | 280.48ms | 3223 | 30 | 259.857 | 2488.27 | 0.229885 | 1.98258 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10611.7 | 0.214614 | 31.8425ms | 3223 | 80 | 30.9139 | 289.65 | 0.00863036 | 0.212512 | 1(Win) | true |
| Glaze | 2629.78 | 0.640248 | 110.078ms | 3223 | 30 | 1679.96 | 1168.8 | 0.320439 | 0.916682 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11884.7 | 0.73124 | 28.3066ms | 3223 | 40 | 143.061 | 258.625 | 0.0741648 | 0.189901 | 1(Win) | true |
| Glaze | 3258.1 | 0.349889 | 101.355ms | 3223 | 30 | 326.869 | 943.4 | 0.84434 | 0.738401 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2730.51 | 0.11878 | 218.565ms | 5839 | 30 | 176.033 | 2039.37 | 0.0474228 | 0.895456 | 1(Win) | true |
| Jsonifier | 1913.17 | 0.23646 | 290.146ms | 5839 | 2560 | 121262 | 2910.62 | 0.361364 | 1.28156 | 2(Loss) | true |
| simdjson (ondemand) | 1897.36 | 0.135757 | 296.442ms | 5839 | 40 | 634.984 | 2934.88 | 0.0746209 | 1.29387 | 3(Loss) | true |
| Glaze | 1850.06 | 0.177572 | 309.534ms | 5839 | 30 | 856.99 | 3009.9 | 0.0786913 | 1.32575 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3190.75 | 0.106559 | 199.737ms | 5839 | 30 | 103.752 | 1745.2 | 0.112817 | 0.764098 | 1(Win) | true |
| Jsonifier | 2303.05 | 0.0665015 | 269.054ms | 5839 | 80 | 206.835 | 2417.89 | 0.342896 | 1.06402 | 2(Loss) | true |
| simdjson (ondemand) | 2144.57 | 0.0760432 | 279.001ms | 5839 | 80 | 311.895 | 2596.56 | 0.0746736 | 1.14198 | 3(Loss) | true |
| Glaze | 2095.68 | 0.0584799 | 286.775ms | 5839 | 160 | 386.333 | 2657.14 | 0.0574255 | 1.16971 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12513.1 | 0.215784 | 55.2568ms | 6938 | 40 | 52.0763 | 528.775 | 0.191057 | 0.187925 | 1(Win) | true |
| Glaze | 4422.2 | 0.168682 | 156.258ms | 6960 | 30 | 192.309 | 1500.97 | 0.0644444 | 0.549981 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14339.5 | 0.250594 | 48.3159ms | 6938 | 40 | 53.4814 | 461.425 | 0.0921909 | 0.1629 | 1(Win) | true |
| Glaze | 4901.56 | 0.171596 | 139.136ms | 6960 | 80 | 431.969 | 1354.17 | 0.0646568 | 0.495463 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2049.02 | 0.242645 | 228.838ms | 4857 | 2560 | 77024.2 | 2260.59 | 0.0304043 | 1.19268 | 1(Win) | true |
| Jsonifier (two-stage) | 1769.85 | 0.210748 | 265.21ms | 4857 | 2560 | 77881.1 | 2617.17 | 0.108536 | 1.38475 | 2(Loss) | true |
| Glaze | 1697.45 | 0.161037 | 276.826ms | 4857 | 160 | 3089.69 | 2728.79 | 0.0858159 | 1.44445 | 3(Loss) | true |
| simdjson (ondemand) | 819.891 | 0.0537126 | 568.156ms | 4857 | 80 | 736.658 | 5649.52 | 0.374437 | 3.00562 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2689.13 | 0.0369406 | 197.315ms | 4857 | 160 | 64.7797 | 1722.49 | 0.278716 | 0.906794 | 1(Win) | true |
| Glaze | 2237.84 | 0.164527 | 230.868ms | 4857 | 80 | 927.775 | 2069.85 | 0.00845543 | 1.09306 | 2(Loss) | true |
| Jsonifier (two-stage) | 2168.08 | 0.0627087 | 236.866ms | 4857 | 80 | 143.592 | 2136.45 | 0 | 1.12781 | 3(Loss) | true |
| simdjson (ondemand) | 897.638 | 0.169282 | 541.213ms | 4857 | 2560 | 195342 | 5160.2 | 0.0158944 | 2.7431 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14667.9 | 0.0944592 | 34.1085ms | 4857 | 320 | 28.4733 | 315.791 | 0.0761396 | 0.154811 | 1(Win) | true |
| Glaze | 3812.46 | 0.0910318 | 125.13ms | 4857 | 80 | 97.8593 | 1214.96 | 0.362431 | 0.635848 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15330.4 | 0.0467743 | 32.6572ms | 4857 | 1280 | 25.5655 | 302.145 | 0.110012 | 0.147769 | 1(Win) | true |
| Glaze | 4241.27 | 0.104048 | 113.037ms | 4857 | 40 | 51.6506 | 1092.12 | 0.134876 | 0.569822 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2370.2 | 0.0761978 | 273.752ms | 6701 | 80 | 337.663 | 2696.21 | 0.0319791 | 1.03392 | 1(Win) | true |
| Glaze | 1888.68 | 0.0997451 | 338.885ms | 6701 | 40 | 455.625 | 3383.62 | 0.0238839 | 1.30049 | 2(Loss) | true |
| Jsonifier | 1777.57 | 0.0994816 | 363.059ms | 6701 | 40 | 511.651 | 3595.12 | 0.0368691 | 1.38283 | 3(Loss) | true |
| simdjson (ondemand) | 1109.51 | 0.220753 | 582.853ms | 6701 | 1280 | 206938 | 5759.82 | 0.394616 | 2.22124 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2884.27 | 0.137856 | 256.632ms | 6701 | 30 | 279.885 | 2215.67 | 0.121711 | 0.848296 | 1(Win) | true |
| Glaze | 2430.8 | 0.12063 | 290.785ms | 6701 | 30 | 301.724 | 2629 | 0.142208 | 1.00801 | 2(Loss) | true |
| Jsonifier | 2128.77 | 0.0892557 | 341.408ms | 6701 | 40 | 287.179 | 3002 | 0.108698 | 1.15302 | 3(Loss) | true |
| simdjson (ondemand) | 1218.22 | 0.112207 | 555.209ms | 6701 | 4890 | 169425 | 5245.82 | 0.137759 | 2.02142 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13744.6 | 0.140921 | 53.9242ms | 7376 | 80 | 41.6125 | 511.788 | 0.10024 | 0.170685 | 1(Win) | true |
| Glaze | 3500.14 | 0.132496 | 215.184ms | 7376 | 160 | 1134.48 | 2009.72 | 0.246599 | 0.69832 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15410.8 | 0.0637361 | 50.059ms | 7376 | 1280 | 108.335 | 456.452 | 0.220938 | 0.151429 | 1(Win) | true |
| Glaze | 3798.12 | 0.0786913 | 191.94ms | 7376 | 80 | 169.922 | 1852.05 | 0.0782304 | 0.643104 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2354.17 | 0.164169 | 72.636ms | 1691 | 40 | 50.5891 | 685.025 | 0.388978 | 1.01271 | 1(Win) | true |
| Jsonifier (two-stage) | 2185.67 | 0.208763 | 77.1289ms | 1691 | 30 | 71.1782 | 737.833 | 0.099489 | 1.09164 | 2(Loss) | true |
| Glaze | 1974.21 | 0.20474 | 85.7446ms | 1691 | 30 | 83.9126 | 816.867 | 0.368611 | 1.21206 | 3(Loss) | true |
| simdjson (ondemand) | 1368.04 | 0.340012 | 121.522ms | 1691 | 1280 | 20563.2 | 1178.82 | 0.0231906 | 1.76603 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3069.21 | 0.19755 | 61.0385ms | 1691 | 30 | 32.323 | 525.433 | 0.114322 | 0.765622 | 1(Win) | true |
| Jsonifier (two-stage) | 2916.25 | 0.0921364 | 63.3411ms | 1691 | 640 | 166.142 | 552.992 | 0.0873854 | 0.809513 | 2(Loss) | true |
| Glaze | 2346.83 | 0.153198 | 76.8358ms | 1691 | 30 | 33.2471 | 687.167 | 0.00970261 | 1.01315 | 3(Loss) | true |
| simdjson (ondemand) | 1717.29 | 0.210516 | 101.955ms | 1691 | 80 | 312.653 | 939.075 | 0.410944 | 1.39969 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15275.2 | 0.175181 | 14.8506ms | 1996 | 640 | 30.4999 | 124.616 | 0.0100319 | 0.128902 | 1(Win) | true |
| Glaze | 4650.71 | 0.178107 | 44.2742ms | 1996 | 160 | 85.0289 | 409.3 | 0.168252 | 0.499631 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17064.4 | 0.353332 | 13.6123ms | 1996 | 80 | 12.4278 | 111.55 | 0.357302 | 0.112901 | 1(Win) | true |
| Glaze | 5292.56 | 0.109509 | 38.6561ms | 1996 | 320 | 49.6412 | 359.663 | 0.053899 | 0.434065 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2642.37 | 0.0864432 | 80.7593ms | 2158 | 160 | 72.5264 | 778.856 | 0.0441158 | 0.906047 | 1(Win) | true |
| Glaze | 2096.17 | 0.148331 | 102.513ms | 2158 | 160 | 339.34 | 981.806 | 0.197586 | 1.14942 | 2(Loss) | true |
| Jsonifier | 1786.33 | 0.152532 | 117.272ms | 2158 | 30 | 92.6448 | 1152.1 | 0.351315 | 1.35419 | 3(Loss) | true |
| simdjson (ondemand) | 1763.4 | 0.475561 | 121.438ms | 2158 | 1280 | 39429.7 | 1167.08 | 0.0513028 | 1.37131 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3451.62 | 0.0916081 | 67.3475ms | 2158 | 160 | 47.7358 | 596.25 | 0.154896 | 0.685119 | 1(Win) | true |
| Glaze | 2460.97 | 0.225573 | 92.8754ms | 2158 | 30 | 106.754 | 836.267 | 0.554939 | 0.97507 | 2(Loss) | true |
| Jsonifier | 2252.47 | 0.0524423 | 101.537ms | 2158 | 320 | 73.4677 | 913.675 | 0.00478858 | 1.06911 | 3(Loss) | true |
| simdjson (ondemand) | 2194.24 | 0.113471 | 103.766ms | 2158 | 160 | 181.227 | 937.925 | 0.184907 | 1.09566 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16157.6 | 0.110513 | 20.3749ms | 2866 | 640 | 22.3669 | 169.161 | 0.278802 | 0.13018 | 1(Win) | true |
| Glaze | 4571.29 | 0.138346 | 63.1088ms | 2866 | 80 | 54.7391 | 597.913 | 0.0857884 | 0.517852 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18706.5 | 0.0816569 | 17.1535ms | 2866 | 2560 | 36.4413 | 146.111 | 0.199571 | 0.109427 | 1(Win) | true |
| Glaze | 5201.53 | 0.257068 | 55.674ms | 2866 | 30 | 54.7402 | 525.467 | 0.435799 | 0.452338 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2463.34 | 0.131632 | 170.674ms | 4390 | 40 | 200.199 | 1699.58 | 0.0171582 | 0.98992 | 1(Win) | true |
| Jsonifier (two-stage) | 1925.83 | 0.0981622 | 221.99ms | 4390 | 30 | 136.616 | 2173.93 | 0.259987 | 1.27036 | 2(Loss) | true |
| Glaze | 1669.96 | 0.14559 | 251.802ms | 4390 | 40 | 532.897 | 2507.03 | 0.0441896 | 1.46671 | 3(Loss) | true |
| simdjson (ondemand) | 1025.28 | 0.1745 | 412.13ms | 4390 | 2560 | 129980 | 4083.42 | 0.201629 | 2.39888 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2849.7 | 0.0693447 | 166.889ms | 4390 | 160 | 166.065 | 1469.15 | 0.141887 | 0.853712 | 1(Win) | true |
| Jsonifier (two-stage) | 2118.74 | 0.0891402 | 218.737ms | 4390 | 40 | 124.103 | 1976 | 0.0657462 | 1.1531 | 2(Loss) | true |
| Glaze | 1841.44 | 0.235115 | 244.25ms | 4390 | 80 | 2285.95 | 2273.56 | 0.39244 | 1.32942 | 3(Loss) | true |
| simdjson (ondemand) | 1093.51 | 0.100419 | 402.687ms | 4390 | 80 | 1182.52 | 3828.62 | 0.365631 | 2.24781 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12308.8 | 0.301257 | 36.6696ms | 4390 | 30 | 31.4989 | 340.133 | 0.107685 | 0.186317 | 1(Win) | true |
| Glaze | 2904.89 | 0.199648 | 146.48ms | 4390 | 4890 | 40486.5 | 1441.24 | 0.0726852 | 0.837268 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13119.9 | 0.0723318 | 34.5431ms | 4390 | 320 | 17.0482 | 319.106 | 0.117378 | 0.174043 | 1(Win) | true |
| Glaze | 3070.99 | 0.0871434 | 139.246ms | 4390 | 320 | 451.64 | 1363.28 | 0.31203 | 0.790736 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3671.49 | 0.0607927 | 248.443ms | 9378 | 80 | 175.441 | 2435.95 | 0.133596 | 0.667116 | 1(Win) | true |
| Jsonifier | 3155.7 | 0.0892057 | 287.901ms | 9378 | 160 | 1022.67 | 2834.1 | 0.151494 | 0.777362 | 2(Loss) | true |
| Glaze | 2534.96 | 0.0505279 | 356.184ms | 9378 | 80 | 254.233 | 3528.09 | 0.204014 | 0.969608 | 3(Loss) | true |
| simdjson (ondemand) | 2058.67 | 0.317409 | 438.759ms | 9378 | 640 | 121693 | 4344.34 | 0.0376349 | 1.19507 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4019.71 | 0.050286 | 244.218ms | 9378 | 160 | 200.284 | 2224.93 | 0.0297674 | 0.608833 | 1(Win) | true |
| Jsonifier | 3443.59 | 0.0354816 | 282.541ms | 9378 | 80 | 67.9353 | 2597.16 | 0.193586 | 0.711808 | 2(Loss) | true |
| Glaze | 2751.64 | 0.0325031 | 342.535ms | 9378 | 80 | 89.2847 | 3250.26 | 0.0572702 | 0.892746 | 3(Loss) | true |
| simdjson (ondemand) | 2158.24 | 0.134347 | 431.498ms | 9378 | 4890 | 151559 | 4143.91 | 0.105713 | 1.13967 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18551.2 | 0.0473815 | 62.1603ms | 11521 | 320 | 25.2003 | 592.269 | 0.0537895 | 0.12776 | 1(Win) | true |
| Glaze | 5116.85 | 0.102113 | 218.656ms | 11521 | 40 | 192.307 | 2147.28 | 0.0135813 | 0.478073 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19726.9 | 0.0699804 | 58.7604ms | 11521 | 160 | 24.3072 | 556.969 | 0.00336632 | 0.119874 | 1(Win) | true |
| Glaze | 5644.09 | 0.0779086 | 197.847ms | 11521 | 80 | 184.015 | 1946.69 | 0.0648117 | 0.43311 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2822.29 | 0.0903347 | 162.849ms | 4669 | 160 | 324.994 | 1577.69 | 0.101914 | 0.862563 | 1(Win) | true |
| Jsonifier (two-stage) | 2254.27 | 0.0907164 | 200.446ms | 4669 | 30 | 96.323 | 1975.23 | 0.147034 | 1.08384 | 2(Loss) | true |
| Glaze | 1694.73 | 0.0400862 | 267.216ms | 4669 | 160 | 177.483 | 2627.38 | 0.112167 | 1.44667 | 3(Loss) | true |
| simdjson (ondemand) | 671.193 | 0.12838 | 667.071ms | 4669 | 2560 | 185690 | 6634.02 | 0.0894031 | 3.67284 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3093.82 | 0.134907 | 148.739ms | 4669 | 40 | 150.794 | 1439.22 | 0.413438 | 0.785297 | 1(Win) | true |
| Jsonifier (two-stage) | 2504.45 | 0.0494222 | 185.87ms | 4669 | 160 | 123.534 | 1777.92 | 0.273098 | 0.97404 | 2(Loss) | true |
| Glaze | 1830.39 | 0.0959612 | 252.083ms | 4669 | 40 | 217.977 | 2432.65 | 0.149817 | 1.33813 | 3(Loss) | true |
| simdjson (ondemand) | 700.454 | 0.137595 | 643.403ms | 4669 | 2560 | 195854 | 6356.89 | 0.113336 | 3.51938 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19930.8 | 0.0820412 | 24.8235ms | 4669 | 640 | 21.5001 | 223.408 | 0.0875007 | 0.110162 | 1(Win) | true |
| Glaze | 3930.45 | 0.0967902 | 116.814ms | 4669 | 160 | 192.374 | 1132.88 | 0.0408087 | 0.615999 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21720.5 | 0.467769 | 23.1415ms | 4669 | 30 | 27.5862 | 205 | 0.0162628 | 0.0994646 | 1(Win) | true |
| Glaze | 4325.31 | 0.0825214 | 106.132ms | 4669 | 320 | 230.938 | 1029.45 | 0.0348971 | 0.558397 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3623.21 | 0.0787669 | 214.061ms | 7932 | 30 | 81.131 | 2087.8 | 0.113229 | 0.674466 | 1(Win) | true |
| Glaze | 2126.88 | 0.201178 | 362.212ms | 7932 | 2560 | 131063 | 3556.64 | 0.131023 | 1.15559 | 2(Loss) | true |
| Jsonifier | 2045.03 | 0.343366 | 366.612ms | 7932 | 640 | 103243 | 3698.99 | 0.461333 | 1.20179 | 3(Loss) | true |
| simdjson (ondemand) | 1102.66 | 0.133841 | 690.209ms | 7932 | 2560 | 215825 | 6860.28 | 0.135942 | 2.23652 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3925.76 | 0.0639321 | 199.842ms | 7932 | 80 | 121.408 | 1926.9 | 0.247119 | 0.621765 | 1(Win) | true |
| Glaze | 2274.14 | 0.0702213 | 345.565ms | 7932 | 30 | 163.678 | 3326.33 | 0.160594 | 1.07972 | 2(Loss) | true |
| Jsonifier | 2230.42 | 0.236973 | 344.56ms | 7932 | 2560 | 165360 | 3391.53 | 0.228027 | 1.10161 | 3(Loss) | true |
| simdjson (ondemand) | 1156.26 | 0.195001 | 663.91ms | 7932 | 1280 | 208325 | 6542.28 | 0.261834 | 2.1322 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19720.1 | 0.142966 | 45.7912ms | 9249 | 80 | 32.7138 | 447.288 | 0.147896 | 0.118226 | 1(Win) | true |
| Glaze | 3919.54 | 0.169286 | 227.941ms | 9249 | 4890 | 70969.3 | 2250.4 | 0.150639 | 0.624464 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23765.2 | 0.0414966 | 40.1625ms | 9249 | 1280 | 30.3628 | 371.153 | 0.434247 | 0.0969295 | 1(Win) | true |
| Glaze | 4269.51 | 0.046917 | 210.598ms | 9249 | 320 | 300.638 | 2065.93 | 0.0976601 | 0.572651 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 927.329 | 0.0924189 | 480.836ms | 4604 | 30 | 574.441 | 4734.8 | 0.16166 | 2.65474 | 1(Win) | true |
| Jsonifier (two-stage) | 833.293 | 0.208428 | 529.18ms | 4604 | 2560 | 308766 | 5269.12 | 0.387703 | 2.9554 | 2(Loss) | true |
| Glaze | 666.635 | 0.213335 | 660.732ms | 4604 | 1280 | 252713 | 6586.39 | 0.137106 | 3.69642 | 3(Loss) | true |
| simdjson (ondemand) | 544.86 | 0.0853615 | 804.26ms | 4604 | 40 | 1892.71 | 8058.43 | 0.0657094 | 4.53044 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1123.85 | 0.0526017 | 475.103ms | 4604 | 80 | 337.867 | 3906.86 | 0.0776874 | 2.18807 | 1(Win) | true |
| Jsonifier (two-stage) | 997.815 | 0.198927 | 519.226ms | 4604 | 2560 | 196155 | 4400.33 | 0.064717 | 2.46603 | 2(Loss) | true |
| Glaze | 765.747 | 0.184676 | 655.788ms | 4604 | 30 | 3363.89 | 5733.9 | 0.00465092 | 3.21907 | 3(Loss) | true |
| simdjson (ondemand) | 586.744 | 0.10217 | 828.978ms | 4604 | 4890 | 285844 | 7483.19 | 0.370693 | 4.20288 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1589.42 | 0.0580007 | 280.695ms | 4604 | 30 | 77.0161 | 2762.47 | 0.119601 | 1.54243 | 1(Win) | true |
| Glaze | 858.203 | 0.0374267 | 518.504ms | 4604 | 40 | 146.661 | 5116.18 | 0.00439762 | 2.8695 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1609.15 | 0.0504624 | 277.346ms | 4604 | 40 | 75.8359 | 2728.6 | 0.0794689 | 1.52472 | 1(Win) | true |
| Glaze | 874.482 | 0.0571119 | 508.036ms | 4604 | 30 | 246.685 | 5020.93 | 0.0199126 | 2.81794 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2881.48 | 0.102367 | 606.616ms | 18245 | 4890 | 186848 | 6038.49 | 0.0880253 | 0.855321 | 1(Win) | true |
| Jsonifier | 2415.63 | 0.1127 | 772.555ms | 18245 | 4890 | 322240 | 7202.99 | 0.224306 | 1.02101 | 2(Loss) | true |
| simdjson (ondemand) | 1971.96 | 0.0741651 | 936.471ms | 18245 | 30 | 1284.73 | 8823.6 | 0.00793264 | 1.25204 | 3(Loss) | true |
| Glaze | 1818.19 | 0.154075 | 959.032ms | 18245 | 2560 | 556562 | 9569.83 | 0.0413089 | 1.35795 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3370.62 | 0.114561 | 619.003ms | 18245 | 4890 | 171022 | 5162.19 | 0.355046 | 0.730634 | 1(Win) | true |
| Jsonifier | 2760.32 | 0.135865 | 717.328ms | 18245 | 2560 | 187770 | 6303.54 | 0.00749151 | 0.893236 | 2(Loss) | true |
| simdjson (ondemand) | 2099.71 | 0.162129 | 921.654ms | 18245 | 40 | 7220.23 | 8286.77 | 0.036316 | 1.17456 | 3(Loss) | true |
| Glaze | 1990.48 | 0.19387 | 952.511ms | 18245 | 1280 | 367622 | 8741.5 | 0.0520057 | 1.2401 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5628.92 | 0.137201 | 423.368ms | 24579 | 80 | 2611.44 | 4164.27 | 0.0871258 | 0.436953 | 1(Win) | true |
| Glaze | 3756.54 | 0.238287 | 633.192ms | 24579 | 1280 | 282986 | 6239.89 | 0.357945 | 0.655801 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5689.36 | 0.142075 | 419.578ms | 24579 | 80 | 2741.13 | 4120.04 | 0.37488 | 0.432468 | 1(Win) | true |
| Glaze | 4278.27 | 0.118869 | 557.951ms | 24579 | 30 | 1272.48 | 5478.93 | 0.109998 | 0.576076 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 977.438 | 0.0867711 | 471.879ms | 4604 | 30 | 455.789 | 4492.07 | 0.0822996 | 2.51792 | 1(Win) | true |
| Jsonifier (two-stage) | 895.031 | 0.149218 | 499.059ms | 4604 | 4890 | 262026 | 4905.66 | 0.333574 | 2.75064 | 2(Loss) | true |
| Glaze | 643.081 | 0.170162 | 686.748ms | 4604 | 80 | 10798.3 | 6827.62 | 0.200324 | 3.8342 | 3(Loss) | true |
| simdjson (ondemand) | 543.296 | 0.186971 | 821.686ms | 4604 | 1280 | 292250 | 8081.62 | 0.1134 | 4.54256 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1236.1 | 0.244122 | 446.216ms | 4604 | 2560 | 192493 | 3552.07 | 0.0309665 | 1.98823 | 1(Win) | true |
| Jsonifier (two-stage) | 1085.78 | 0.0989535 | 490.201ms | 4604 | 40 | 640.49 | 4043.85 | 0.116774 | 2.26524 | 2(Loss) | true |
| Glaze | 760.97 | 0.308487 | 669.392ms | 4604 | 640 | 202763 | 5769.89 | 0.346183 | 3.23887 | 3(Loss) | true |
| simdjson (ondemand) | 575.89 | 0.196196 | 850.582ms | 4604 | 1280 | 286405 | 7624.23 | 0.161242 | 4.28331 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1564.86 | 0.0332207 | 290.259ms | 4604 | 320 | 278.028 | 2805.82 | 0.0190488 | 1.56751 | 1(Win) | true |
| Glaze | 861.77 | 0.123561 | 529.962ms | 4604 | 30 | 1188.97 | 5095 | 0.111344 | 2.85825 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1604.13 | 0.0521161 | 278.549ms | 4604 | 40 | 81.3942 | 2737.12 | 0.0368256 | 1.52827 | 1(Win) | true |
| Glaze | 856.358 | 0.0633276 | 524.997ms | 4604 | 40 | 421.703 | 5127.2 | 0.0539897 | 2.87585 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3071.56 | 0.0859506 | 600.742ms | 18245 | 80 | 1896.52 | 5664.8 | 0.267271 | 0.802211 | 1(Win) | true |
| Jsonifier | 2524.9 | 0.311372 | 703.596ms | 18245 | 640 | 294673 | 6891.29 | 0.186482 | 0.976718 | 2(Loss) | true |
| simdjson (ondemand) | 1853.08 | 0.103337 | 944.533ms | 18245 | 4890 | 460380 | 9389.64 | 0.529209 | 1.33202 | 3(Loss) | true |
| Glaze | 1828.61 | 0.0884003 | 971.02ms | 18245 | 30 | 2122.64 | 9515.33 | 0.150407 | 1.35014 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3615.88 | 0.305426 | 570.613ms | 18245 | 1280 | 276492 | 4812.05 | 0.36361 | 0.680844 | 1(Win) | true |
| Jsonifier | 2924.83 | 0.0597713 | 711.844ms | 18245 | 30 | 379.31 | 5949 | 0.0504541 | 0.842717 | 2(Loss) | true |
| simdjson (ondemand) | 2095.8 | 0.399444 | 958.811ms | 18245 | 320 | 351923 | 8302.2 | 0.0423278 | 1.17713 | 3(Loss) | true |
| Glaze | 1961.56 | 0.152081 | 962.728ms | 18245 | 2560 | 465876 | 8870.36 | 0.490306 | 1.25838 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5752.8 | 0.15256 | 417.289ms | 24579 | 80 | 3091.28 | 4074.6 | 0.140087 | 0.427628 | 1(Win) | true |
| Glaze | 3850.44 | 0.105831 | 611.33ms | 24579 | 4890 | 202974 | 6087.71 | 0.00349589 | 0.640283 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5785.98 | 0.183684 | 419.763ms | 24579 | 2560 | 141762 | 4051.23 | 0.141048 | 0.425231 | 1(Win) | true |
| Glaze | 4340.71 | 0.0507613 | 548.934ms | 24579 | 80 | 601.123 | 5400.12 | 0.0189774 | 0.567646 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1834.91 | 0.180321 | 268.006ms | 5094 | 4890 | 111453 | 2647.56 | 0.242368 | 1.33619 | 1(Win) | true |
| Jsonifier (two-stage) | 1523.73 | 0.512663 | 320.077ms | 5094 | 640 | 170980 | 3188.25 | 0.279494 | 1.61034 | 2(Loss) | true |
| Glaze | 1259.49 | 0.0736136 | 397.894ms | 5094 | 160 | 1289.94 | 3857.14 | 0.0050234 | 1.95264 | 3(Loss) | true |
| simdjson (ondemand) | 839.748 | 0.230694 | 580.584ms | 5094 | 1280 | 227984 | 5785.09 | 0.221708 | 2.93369 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2180.95 | 0.575785 | 284.449ms | 5094 | 640 | 105276 | 2227.48 | 0.203417 | 1.12208 | 1(Win) | true |
| Jsonifier (two-stage) | 1828.9 | 0.282526 | 317.4ms | 5094 | 160 | 9011 | 2656.24 | 0.400508 | 1.33936 | 2(Loss) | true |
| Glaze | 1581.43 | 0.0576544 | 359.045ms | 5094 | 80 | 250.942 | 3071.91 | 0.13079 | 1.55205 | 3(Loss) | true |
| simdjson (ondemand) | 961.324 | 0.182876 | 554.039ms | 5094 | 2560 | 218642 | 5053.47 | 0.141447 | 2.56074 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14323.1 | 0.0503305 | 36.6523ms | 5094 | 1280 | 37.3006 | 339.173 | 0.270147 | 0.159814 | 1(Win) | true |
| Glaze | 3366.84 | 0.263401 | 146.562ms | 5094 | 40 | 577.785 | 1442.9 | 0.388899 | 0.721942 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16069.4 | 0.0480242 | 32.7718ms | 5094 | 1280 | 26.9803 | 302.314 | 0.148631 | 0.138896 | 1(Win) | true |
| Glaze | 3781.83 | 0.0734597 | 132.866ms | 5094 | 160 | 142.473 | 1284.57 | 0.0384518 | 0.641902 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2517.3 | 0.102594 | 308.8ms | 8051 | 40 | 391.682 | 3050.1 | 0.0054646 | 0.975515 | 1(Win) | true |
| Jsonifier | 2004.99 | 0.06652 | 389.34ms | 8051 | 30 | 194.671 | 3829.47 | 0.476463 | 1.22694 | 2(Loss) | true |
| Glaze | 1728.25 | 0.127117 | 450.42ms | 8051 | 30 | 956.782 | 4442.67 | 0.0593089 | 1.42351 | 3(Loss) | true |
| simdjson (ondemand) | 1322.45 | 0.112833 | 582.904ms | 8051 | 4890 | 209857 | 5805.9 | 0.0292505 | 1.86341 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2966.92 | 0.195517 | 304.13ms | 8051 | 2560 | 65538.1 | 2587.88 | 0.12986 | 0.825639 | 1(Win) | true |
| Jsonifier | 2214.3 | 0.0372754 | 396.575ms | 8051 | 160 | 267.295 | 3467.47 | 0.0736666 | 1.11001 | 2(Loss) | true |
| Glaze | 2067.73 | 0.0939482 | 421.674ms | 8051 | 30 | 365.099 | 3713.27 | 0.152839 | 1.18863 | 3(Loss) | true |
| simdjson (ondemand) | 1507.48 | 0.113179 | 557.708ms | 8051 | 4890 | 162494 | 5093.28 | 0.260343 | 1.63307 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17731.5 | 0.418716 | 52.3939ms | 9255 | 4890 | 21242.9 | 497.774 | 0.755328 | 0.132047 | 1(Win) | true |
| Glaze | 3853.37 | 0.340664 | 231.436ms | 9255 | 1280 | 77935.2 | 2290.53 | 0.159608 | 0.635019 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19540.8 | 0.155907 | 50.1454ms | 9255 | 640 | 317.378 | 451.683 | 0.263947 | 0.119185 | 1(Win) | true |
| Glaze | 4301.53 | 0.226629 | 207.208ms | 9255 | 4890 | 105742 | 2051.89 | 0.0143019 | 0.567509 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6371.53 | 0.346622 | 45.6612ms | 2889 | 1280 | 2875.61 | 432.418 | 0.0803336 | 0.363966 | 1(Win) | true |
| Jsonifier | 6157.83 | 0.182644 | 48.2964ms | 2889 | 40 | 26.7122 | 447.425 | 0.0950783 | 0.377735 | 2(Loss) | true |
| Jsonifier (two-stage) | 5985.12 | 0.339339 | 48.2904ms | 2889 | 1280 | 3123.4 | 460.336 | 0.232981 | 0.389107 | 3(Loss) | true |
| Glaze | 3077.47 | 0.248724 | 92.7631ms | 2889 | 4890 | 24246.6 | 895.269 | 0.08131 | 0.780553 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6646.15 | 0.3572 | 44.6476ms | 2889 | 4890 | 10722.2 | 414.55 | 0.223595 | 0.346543 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6554.6 | 0.477815 | 45.2807ms | 2889 | 2560 | 10326.7 | 420.341 | 0.590603 | 0.352943 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 6479.28 | 0.624194 | 45.8477ms | 2889 | 2560 | 18035.2 | 425.227 | 0.0141488 | 0.357205 | 2(Tie) | true |
| Glaze | 3144.96 | 0.327546 | 91.2548ms | 2889 | 2560 | 21079 | 876.057 | 0.120401 | 0.762903 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7474.91 | 0.146253 | 51.8814ms | 3808 | 80 | 40.391 | 485.837 | 0.125912 | 0.31294 | 1(Win) | true |
| Jsonifier | 7243.82 | 0.164396 | 52.5077ms | 3808 | 1280 | 869.464 | 501.337 | 0.511083 | 0.323007 | 2(Loss) | true |
| Jsonifier (two-stage) | 7205.33 | 0.122046 | 53.7567ms | 3808 | 1280 | 484.329 | 504.015 | 0.458103 | 0.3249 | 3(Loss) | true |
| Glaze | 3778.55 | 0.372565 | 100.82ms | 3808 | 2560 | 32823.9 | 961.108 | 0.623738 | 0.637146 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7739.35 | 0.0501644 | 50.5119ms | 3808 | 640 | 35.4615 | 469.238 | 0.0546397 | 0.300991 | 1(Win) | true |
| simdjson (ondemand) | 7709.06 | 0.106272 | 50.4787ms | 3808 | 160 | 40.1003 | 471.081 | 0.00928628 | 0.301224 | 2(Loss) | true |
| Jsonifier (two-stage) | 7569.97 | 0.319518 | 50.8758ms | 3808 | 4890 | 11489.6 | 479.737 | 0.371388 | 0.30872 | 3(Loss) | true |
| Glaze | 3828.52 | 0.0850545 | 99.157ms | 3808 | 160 | 104.147 | 948.562 | 0.0013178 | 0.628422 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2225.53 | 0.0331744 | 127.458ms | 2889 | 640 | 107.948 | 1237.98 | 0.0359838 | 1.08869 | 1(Win) | true |
| Jsonifier (two-stage) | 2212.04 | 0.147828 | 128.184ms | 2889 | 30 | 101.706 | 1245.53 | 0.352019 | 1.09553 | 2(Loss) | true |
| Glaze | 2146.94 | 0.496998 | 135.366ms | 2889 | 30 | 1220.36 | 1283.3 | 0.178905 | 1.13029 | 3(Loss) | true |
| simdjson (ondemand) | 1020.8 | 0.054774 | 280.418ms | 2889 | 80 | 174.847 | 2699.04 | 0.0542154 | 2.40241 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2435.29 | 0.0709175 | 121.252ms | 2889 | 160 | 102.996 | 1131.35 | 0.0684553 | 0.993188 | 1(Win) | true |
| Jsonifier (two-stage) | 2411.65 | 0.0285732 | 122.149ms | 2889 | 640 | 68.1964 | 1142.44 | 0.000820607 | 1.00323 | 2(Loss) | true |
| Glaze | 2267.91 | 0.343723 | 128.771ms | 2889 | 40 | 697.464 | 1214.85 | 0.234048 | 1.06688 | 3(Loss) | true |
| simdjson (ondemand) | 1061.51 | 0.0549718 | 269.045ms | 2889 | 80 | 162.861 | 2595.51 | 0.0293863 | 2.30681 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12291.6 | 0.119517 | 25.4657ms | 2963 | 640 | 48.3154 | 229.892 | 0.104097 | 0.17921 | 1(Win) | true |
| Glaze | 5215.16 | 0.129144 | 57.262ms | 2963 | 160 | 78.3424 | 541.831 | 0.0727231 | 0.452339 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14973.4 | 0.105976 | 21.4217ms | 2963 | 1280 | 51.1975 | 188.717 | 0.0868601 | 0.142871 | 1(Win) | true |
| Glaze | 5743.04 | 0.0665431 | 52.3244ms | 2963 | 320 | 34.3033 | 492.028 | 0.199191 | 0.408292 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2829.98 | 0.0739932 | 133.42ms | 3808 | 160 | 144.255 | 1283.26 | 0.0637619 | 0.857072 | 1(Win) | true |
| Glaze | 2341.68 | 0.0557899 | 158.787ms | 3808 | 160 | 119.776 | 1550.85 | 0.0346704 | 1.03929 | 2(Loss) | true |
| Jsonifier | 1946.33 | 0.141651 | 193.28ms | 3808 | 30 | 209.568 | 1865.87 | 0.0572001 | 1.25355 | 3(Loss) | true |
| simdjson (ondemand) | 1331 | 0.106785 | 277.283ms | 3808 | 30 | 254.671 | 2728.47 | 0.0488436 | 1.8432 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3076.22 | 0.130351 | 125.974ms | 3808 | 80 | 189.442 | 1180.54 | 0.10918 | 0.786699 | 1(Win) | true |
| Glaze | 2514.45 | 0.0693171 | 153.743ms | 3808 | 80 | 80.1821 | 1444.29 | 0.0597537 | 0.966689 | 2(Loss) | true |
| Jsonifier | 2083.44 | 0.124923 | 183.77ms | 3808 | 40 | 189.661 | 1743.08 | 0.0358433 | 1.17142 | 3(Loss) | true |
| simdjson (ondemand) | 1364.75 | 0.197482 | 273.519ms | 3808 | 2560 | 70694.6 | 2661 | 0.0945501 | 1.79458 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10869.4 | 0.0549614 | 40.5246ms | 4300 | 1280 | 55.037 | 377.28 | 0.202721 | 0.212427 | 1(Win) | true |
| Glaze | 4073.1 | 0.141464 | 104.153ms | 4300 | 30 | 60.8552 | 1006.8 | 0.122651 | 0.592915 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13110.8 | 0.183246 | 33.825ms | 4300 | 160 | 52.5619 | 312.781 | 0.105793 | 0.173161 | 1(Win) | true |
| Glaze | 4811.2 | 0.0597407 | 90.6357ms | 4300 | 160 | 41.4849 | 852.344 | 0.12377 | 0.498779 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4508.7 | 0.135731 | 5277.39ms | 466906 | 320 | 5.74992e+06 | 98759.2 | 0.122617 | 0.548912 | 1(Win) | true |
| Glaze | 2854.56 | 0.0766011 | 8218.61ms | 466906 | 640 | 9.13755e+06 | 155988 | 0.02445 | 0.867155 | 2(Loss) | true |
| simdjson (ondemand) | 1793.34 | 0.117792 | 6305.14ms | 466906 | 640 | 5.47457e+07 | 248295 | 0.479765 | 1.38028 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4588.63 | 0.358422 | 5283.27ms | 466906 | 80 | 9.67768e+06 | 97039 | 0.0588899 | 0.539343 | 1(Win) | true |
| Glaze | 2829.96 | 0.116109 | 8058.5ms | 466906 | 2560 | 8.54421e+07 | 157344 | 0.102296 | 0.8747 | 2(Loss) | true |
| simdjson (ondemand) | 1910.7 | 0.136155 | 5979.61ms | 466906 | 320 | 3.22173e+07 | 233043 | 0.0742644 | 1.29558 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6007.63 | 0.302783 | 5733.38ms | 699405 | 40 | 4.52036e+06 | 111026 | 0.127622 | 0.412007 | 1(Win) | true |
| Glaze | 3810.04 | 0.0618667 | 9003.47ms | 699405 | 2560 | 3.00297e+07 | 175065 | 0.144934 | 0.649687 | 2(Loss) | true |
| simdjson (ondemand) | 2407.57 | 0.088831 | 7575.71ms | 767297 | 1280 | 9.33057e+07 | 303938 | 0.0601213 | 1.02819 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6016.36 | 0.205065 | 5816.03ms | 699405 | 80 | 4.13488e+06 | 110865 | 0.135656 | 0.411399 | 1(Win) | true |
| Glaze | 3791.48 | 0.0926904 | 9406.63ms | 699405 | 320 | 8.50865e+06 | 175922 | 0.286866 | 0.652895 | 2(Loss) | true |
| simdjson (ondemand) | 2562.8 | 0.145176 | 7583.36ms | 767297 | 80 | 1.3746e+07 | 285528 | 0.0656277 | 0.965665 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3992.27 | 0.133972 | 7598.77ms | 631514 | 160 | 6.53547e+06 | 150856 | 0.0141463 | 0.620009 | 1(Win) | true |
| Glaze | 2609.41 | 0.275574 | 5873.59ms | 631514 | 40 | 1.61815e+07 | 230802 | 0.129919 | 0.948696 | 2(Loss) | true |
