# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the Clang 23.1.6 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [c4ad752](https://github.com/nihilai-collective/Jsonifier/commit/c4ad752)  
| Glaze: [283c9664](https://github.com/stephenberry/glaze/commit/283c9664)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **Glaze** | utf8: `NEON64`, escape: `NEON`, float: `NEON`, struct-skip: `NEON64` |

> **How the sampling/convergence works (Apple M2 Pro (Virtual)-NEON):**  
> The iterations grow geometrically (100 → 200 → 400 ...) up to a max of 100000.  
> Scores come from a trailing window of `max(iterations/10, 30)` (capped at 100000) over at most 5s.  
> The epoch that counts is whichever one has the lowest (RSE + epoch-over-epoch mean shift).  
> Converged means RSE ≤ 10% and mean shift ≤ 5%. Ties get called using Welch's t-test with Bessel-corrected variance.

---

##### The Test Variants
* **Standard vs. (Reused):** Standard builds, parses/serializes, and tears everything down every iteration. `(Reused)` keeps the buffer/object around across iterations and clears it outside the timed region, so you just see the raw parse/format throughput.
* **Document Sizes:** "Small" tests cap minified payloads at 5 KiB (via `GenerateSmallJson.py`), so dispatch/setup/small-alloc latency dominates instead of bulk SIMD throughput.
* **Key Traversal Order:** Standard tests go in key order, `Reverse` tests go backwards, which hits single-pass forward-only decoders (simdjson On Demand) with an $O(N^2)$ penalty that hash/DOM-indexed ones dodge.

##### A Few Details
* **simdjson (ondemand):** Includes the harness mapping layer (`include/common.hpp`). On MSVC it uses `find_field` / `find_field_unordered` instead, because of some pretty severe compiler overhead when instantiating `object::for_each`.
* **simdjson (reflection):** Not in this run, since this toolchain does not support P2996 static reflection yet.
* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.
* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.

---
*Generated with BenchmarkSuite commit: [23af44c](https://github.com/nihilai-collective/benchmarksuite/commit/23af44c)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1262.14 | 0.477257 | 71.9163ms | 905 | 1280 | 13633.2 | 683.821 | 0.00422699 | 1(Win) | true |
| Glaze | 1168.41 | 0.155147 | 74.7297ms | 905 | 320 | 420.288 | 738.678 | 0.507193 | 2(Loss) | true |
| simdjson (ondemand) | 311.065 | 0.0306483 | 284.451ms | 905 | 1280 | 925.586 | 2774.58 | 0.151152 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1360.42 | 0.153655 | 66.7932ms | 905 | 4890 | 4646.74 | 634.416 | 0.238587 | 1(Win) | true |
| Glaze | 1326.89 | 0.128339 | 68.2408ms | 905 | 640 | 445.991 | 650.45 | 0.249487 | 2(Loss) | true |
| simdjson (ondemand) | 309.171 | 0.0513637 | 286.363ms | 905 | 320 | 657.906 | 2791.58 | 0.0253057 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1033.74 | 0.0653175 | 87.4205ms | 905 | 320 | 95.1673 | 834.909 | 0.151359 | 1(Win) | true |
| Glaze | 132.6 | 0.0780012 | 660.718ms | 905 | 80 | 2062.07 | 6508.86 | 0.0719654 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1263.78 | 0.0608422 | 79.29ms | 905 | 2560 | 441.979 | 682.93 | 0.0117815 | 1(Win) | true |
| Glaze | 769.893 | 0.054876 | 126.966ms | 905 | 640 | 242.204 | 1121.03 | 0.0294006 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 925.469 | 0.0870636 | 194.154ms | 1811 | 160 | 422.384 | 1866.19 | 0.0291453 | 1(Win) | true |
| Glaze | 800.021 | 0.045469 | 213.753ms | 1811 | 640 | 616.659 | 2158.82 | 0.0680608 | 2(Loss) | true |
| simdjson (ondemand) | 285.119 | 0.243132 | 603.761ms | 1811 | 4890 | 1.06066e+06 | 6057.49 | 0.547023 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1082.98 | 0.504077 | 177.259ms | 1811 | 40 | 2584.95 | 1594.78 | 2.85635 | 1(Win) | true |
| Glaze | 979.554 | 0.0648832 | 181.159ms | 1811 | 320 | 418.788 | 1763.15 | 0.0377377 | 2(Loss) | true |
| simdjson (ondemand) | 308.471 | 0.387779 | 548.241ms | 1811 | 160 | 75421.8 | 5598.91 | 0.513211 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 315.793 | 0.0423139 | 615.019ms | 1997 | 80 | 520.964 | 6030.81 | 0.0938047 | 1(Win) | true |
| Glaze | 226.269 | 0.0539605 | 771.612ms | 1798 | 80 | 1337.73 | 7578.16 | 0.0150125 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 956.353 | 0.148477 | 210.506ms | 1997 | 160 | 1398.81 | 1991.41 | 0.381521 | 1(Win) | true |
| Glaze | 661.749 | 0.370248 | 308.602ms | 1798 | 80 | 7363.23 | 2591.18 | 0.337857 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1094.91 | 0.101508 | 118.225ms | 1313 | 320 | 431.242 | 1143.63 | 0.0582365 | 1(Win) | true |
| Glaze | 676.029 | 0.0877072 | 182.639ms | 1313 | 320 | 844.539 | 1852.25 | 0.0820622 | 2(Loss) | true |
| simdjson (ondemand) | 306.028 | 0.0746143 | 416.702ms | 1313 | 40 | 372.831 | 4091.7 | 0.103569 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1449.17 | 0.428741 | 89.7694ms | 1313 | 1280 | 17566.6 | 864.061 | 0.0171761 | 1(Win) | true |
| Glaze | 860.4 | 0.110881 | 150.271ms | 1313 | 320 | 833.279 | 1455.34 | 0.0633844 | 2(Loss) | true |
| simdjson (ondemand) | 328.525 | 0.0876227 | 389.031ms | 1313 | 40 | 446.154 | 3811.5 | 0.0113704 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1265.35 | 0.205062 | 102.71ms | 1313 | 80 | 329.435 | 989.587 | 0.0037896 | 1(Win) | true |
| Glaze | 183.77 | 0.134027 | 687.714ms | 1313 | 2560 | 213504 | 6813.83 | 0.146214 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1526.93 | 0.104497 | 91.9296ms | 1313 | 640 | 469.979 | 820.058 | 0.0622663 | 1(Win) | true |
| Glaze | 856.769 | 0.223959 | 161.846ms | 1313 | 2560 | 27427.1 | 1461.51 | 0.259278 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1086.39 | 0.108138 | 345.832ms | 4215 | 40 | 640.379 | 3700.07 | 0.342831 | 1(Win) | true |
| Glaze | 798.296 | 0.127579 | 477.291ms | 4215 | 40 | 1650.76 | 5035.4 | 0.124958 | 2(Loss) | true |
| simdjson (ondemand) | 706.796 | 0.145251 | 573.783ms | 4215 | 4890 | 333698 | 5687.27 | 0.159623 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1636.18 | 0.0702177 | 304.104ms | 4215 | 80 | 238.075 | 2456.78 | 0.0610184 | 1(Win) | true |
| Glaze | 1079.08 | 0.230129 | 453.871ms | 4215 | 640 | 47033.5 | 3725.14 | 0.0165235 | 2(Loss) | true |
| simdjson (ondemand) | 854.229 | 0.144061 | 534.922ms | 4215 | 2560 | 117647 | 4705.69 | 0.22353 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 701.117 | 0.102239 | 539.069ms | 4215 | 30 | 1030.78 | 5733.33 | 0.412743 | 1(Win) | true |
| Glaze | 493.343 | 0.775144 | 863.106ms | 4215 | 40 | 159559 | 8147.95 | 0.718701 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3455.96 | 0.213281 | 130.492ms | 4215 | 4890 | 30093.3 | 1163.13 | 2.49272 | 1(Win) | true |
| Glaze | 2051.24 | 0.190342 | 210.809ms | 4215 | 30 | 417.402 | 1959.67 | 0.00340182 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1036.4 | 0.195681 | 117.287ms | 1213 | 80 | 381.64 | 1116.17 | 0.418344 | 1(Win) | true |
| Glaze | 651.974 | 0.244857 | 177.504ms | 1213 | 2560 | 48319.7 | 1774.31 | 0.077643 | 2(Loss) | true |
| simdjson (ondemand) | 276.182 | 0.0942729 | 427.915ms | 1213 | 40 | 623.687 | 4188.57 | 0.0583275 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1477.37 | 0.183017 | 80.4746ms | 1213 | 160 | 328.585 | 783.019 | 0.160695 | 1(Win) | true |
| Glaze | 794.647 | 0.266282 | 157.287ms | 1213 | 80 | 1202.11 | 1455.75 | 0.104647 | 2(Loss) | true |
| simdjson (ondemand) | 288.523 | 0.0667371 | 405.793ms | 1213 | 80 | 572.777 | 4009.41 | 0.0246235 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1179.84 | 0.154905 | 103.141ms | 1213 | 320 | 738.175 | 980.481 | 0.00254983 | 1(Win) | true |
| Glaze | 173.846 | 0.113 | 676.663ms | 1213 | 30 | 1696.17 | 6654.2 | 0 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1412.87 | 0.286979 | 92.5958ms | 1213 | 80 | 441.677 | 818.763 | 0.129938 | 1(Win) | true |
| Glaze | 829.086 | 0.0578132 | 155.858ms | 1213 | 1280 | 832.89 | 1395.28 | 0.114299 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7413.11 | 0.205367 | 6328.65ms | 466906 | 640 | 9.73864e+06 | 60066.1 | 0.935284 | 1(Win) | true |
| Jsonifier | 7263.25 | 0.137658 | 6200.79ms | 466906 | 1280 | 9.11609e+06 | 61305.4 | 0.146626 | 2(Loss) | true |
| Glaze | 1730.32 | 0.103998 | 6771.8ms | 466906 | 1280 | 9.16777e+07 | 257337 | 0.0241786 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7567.43 | 0.060112 | 6006.29ms | 466906 | 4890 | 6.11777e+06 | 58841.2 | 1.09817 | 1(Win) | true |
| Jsonifier | 7297.42 | 0.0635217 | 6214.16ms | 466906 | 4890 | 7.34638e+06 | 61018.3 | 0.113343 | 2(Loss) | true |
| Glaze | 1747.59 | 0.167606 | 6645.01ms | 466906 | 160 | 2.91797e+07 | 254794 | 0.155738 | 3(Loss) | true |
