# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.52.37029.0 compiler).  

Latest Results: (Nov 14, 2026)
#### Using the following commits:
----
| Jsonifier: [d4727ec](https://github.com/nihilai-collective/Jsonifier/commit/d4727ec)  
| Glaze: [a53ddd59](https://github.com/stephenberry/glaze/commit/a53ddd59)  
| simdjson: [449f38e63](https://github.com/simdjson/simdjson/commit/449f38e63)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |
| **Glaze** | utf8: `AVX2`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX2` |

> **Adaptive Sampling & Convergence (Intel(R) Core(TM) i9-14900KF-AVX2):**  
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

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 659.711 | 0.103987 | 132.203ms | 905 | 4890 | 9050.16 | 1308.26 | 0.0313641 | 4.54298 | 1(Win) | true |
| Glaze | 632.869 | 0.396594 | 139.709ms | 905 | 80 | 2340.19 | 1363.75 | 1.01852 | 4.7324 | 2(Loss) | true |
| Jsonifier (two-stage) | 264.601 | 0.200015 | 329.531ms | 905 | 1280 | 54481.5 | 3261.8 | 0.0407342 | 11.4206 | 3(Loss) | true |
| simdjson (ondemand) | 121.458 | 0.174851 | 711.762ms | 905 | 320 | 49400.4 | 7105.94 | 0.0483516 | 24.9701 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 740.051 | 0.160224 | 117.853ms | 905 | 4890 | 17074.2 | 1166.24 | 0.314949 | 4.04676 | 1(Win) | true |
| Glaze | 722.617 | 0.136135 | 124.66ms | 905 | 320 | 846.003 | 1194.38 | 0.314961 | 4.1318 | 2(Loss) | true |
| Jsonifier (two-stage) | 272.947 | 0.0792876 | 318.97ms | 905 | 4890 | 30737 | 3162.07 | 0.00849405 | 11.0647 | 3(Loss) | true |
| simdjson (ondemand) | 123.004 | 0.0986288 | 694.542ms | 905 | 30 | 1436.78 | 7016.67 | 0.142315 | 24.6274 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1130.74 | 0.29597 | 79.1392ms | 905 | 640 | 3266.21 | 763.281 | 0.0204666 | 2.62305 | 1(Win) | true |
| Glaze | 102.659 | 0.425691 | 896.33ms | 905 | 2560 | 3.27894e+06 | 8407.23 | 0.43445 | 29.5307 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1648.37 | 0.226743 | 60.6974ms | 905 | 1280 | 1804.12 | 523.594 | 0.327186 | 1.78307 | 1(Win) | true |
| Glaze | 552.575 | 0.10264 | 168.333ms | 905 | 2560 | 6579.38 | 1561.91 | 0.579343 | 5.43237 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 945.69 | 0.109254 | 186.432ms | 1811 | 2560 | 10191.8 | 1826.29 | 0.440801 | 3.17987 | 1(Win) | true |
| Jsonifier (two-stage) | 544.256 | 0.299654 | 314.115ms | 1811 | 30 | 2712.64 | 3173.33 | 0.527983 | 5.53648 | 2(Loss) | true |
| Glaze | 460.101 | 0.431602 | 346.782ms | 1811 | 80 | 20998.4 | 3753.75 | 0.166778 | 6.57744 | 3(Loss) | true |
| simdjson (ondemand) | 260.651 | 0.0565724 | 662.877ms | 1811 | 4890 | 68712.5 | 6626.11 | 0.152052 | 11.6246 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1204.08 | 0.2626 | 145.98ms | 1811 | 160 | 2270.05 | 1434.38 | 0.043554 | 2.47201 | 1(Win) | true |
| Jsonifier (two-stage) | 630.33 | 0.286301 | 276.544ms | 1811 | 40 | 2461.54 | 2740 | 0.121507 | 4.75363 | 2(Loss) | true |
| Glaze | 579.17 | 0.116697 | 300.102ms | 1811 | 2560 | 31001.7 | 2982.03 | 0.149109 | 5.1828 | 3(Loss) | true |
| simdjson (ondemand) | 282.538 | 0.165894 | 623.954ms | 1811 | 320 | 32907.4 | 6112.81 | 0.117719 | 10.7042 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 348.814 | 0.100009 | 497.773ms | 1811 | 2560 | 62772.7 | 4951.37 | 0.0953687 | 8.682 | 1(Win) | true |
| Glaze | 160.051 | 0.587224 | 1075.87ms | 1798 | 1280 | 5.06619e+06 | 10713.5 | 0.00802077 | 18.9462 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 552.232 | 0.228616 | 326.607ms | 1811 | 40 | 2044.87 | 3127.5 | 0.0266525 | 5.44104 | 1(Win) | true |
| Glaze | 437.268 | 0.109913 | 416.139ms | 1798 | 1280 | 23779.1 | 3921.41 | 0.0199187 | 6.91638 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1589.92 | 0.082682 | 233.882ms | 3862 | 4890 | 17939.2 | 2316.52 | 0.193541 | 1.89547 | 1(Win) | true |
| Glaze | 953.749 | 0.0692062 | 389.972ms | 3862 | 4890 | 34926.6 | 3861.7 | 0.0187585 | 3.16994 | 2(Loss) | true |
| Jsonifier (two-stage) | 877.449 | 0.104038 | 420.77ms | 3862 | 40 | 762.821 | 4197.5 | 0.258758 | 3.44182 | 3(Loss) | true |
| simdjson (ondemand) | 459.283 | 0.155526 | 813.702ms | 3862 | 640 | 99551.8 | 8019.22 | 0.318608 | 6.60154 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1993.55 | 0.432822 | 191.426ms | 3862 | 40 | 2557.69 | 1847.5 | 0.0451264 | 1.49957 | 1(Win) | true |
| Glaze | 1117.22 | 0.101112 | 338.085ms | 3862 | 30 | 333.333 | 3296.67 | 0.202634 | 2.69396 | 2(Loss) | true |
| Jsonifier (two-stage) | 988.828 | 0.077142 | 379.879ms | 3862 | 4890 | 40371.4 | 3724.7 | 0.293404 | 3.04976 | 3(Loss) | true |
| simdjson (ondemand) | 462.918 | 0.0701501 | 788.849ms | 3862 | 80 | 2492.09 | 7956.25 | 0.489422 | 6.54362 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 506.148 | 0.0483226 | 737.073ms | 3862 | 4890 | 60461.6 | 7276.71 | 0.265172 | 5.98763 | 1(Win) | true |
| Glaze | 436.334 | 0.224864 | 857.306ms | 3862 | 4890 | 1.76172e+06 | 8440.98 | 0.0165974 | 6.94576 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3915.9 | 0.187027 | 110.614ms | 3862 | 2560 | 7921.55 | 940.547 | 0.331153 | 0.753691 | 1(Win) | true |
| Glaze | 1569.52 | 0.146185 | 264.997ms | 3862 | 1280 | 15063 | 2346.64 | 0.397754 | 1.9183 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1011.87 | 0.0705891 | 913.204ms | 9578 | 2560 | 103948 | 9027.15 | 0.206845 | 2.99578 | 1(Win) | true |
| Glaze | 824.104 | 0.0930682 | 1127.87ms | 9578 | 1280 | 136207 | 11083.9 | 0.740212 | 3.68058 | 2(Loss) | true |
| Jsonifier (two-stage) | 790.26 | 0.0811079 | 1163.93ms | 9578 | 1280 | 112498 | 11558.6 | 0.0811743 | 3.83801 | 3(Loss) | true |
| simdjson (ondemand) | 752.413 | 0.212275 | 1241.12ms | 9578 | 40 | 26564.1 | 12140 | 0.027465 | 4.03355 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1736.77 | 0.0690036 | 730.513ms | 9578 | 4890 | 64405 | 5259.37 | 0.129237 | 1.74113 | 1(Win) | true |
| Glaze | 1245.47 | 0.0751286 | 954.51ms | 9578 | 2560 | 77720.4 | 7334.02 | 0.234335 | 2.4319 | 2(Loss) | true |
| Jsonifier (two-stage) | 1175.39 | 0.0771094 | 991.613ms | 9578 | 2560 | 91926.4 | 7771.29 | 0.132372 | 2.57581 | 3(Loss) | true |
| simdjson (ondemand) | 1081.03 | 0.0710219 | 1059.36ms | 9578 | 4890 | 176102 | 8449.59 | 0.0219407 | 2.80395 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1402.44 | 0.249169 | 647.036ms | 9578 | 320 | 84278.6 | 6513.12 | 0 | 2.15696 | 1(Win) | true |
| Glaze | 1045.74 | 0.279837 | 876.981ms | 9578 | 2560 | 1.5295e+06 | 8734.73 | 0.0790934 | 2.8978 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8544.83 | 0.254096 | 125.051ms | 9578 | 1280 | 9443.85 | 1068.98 | 0.313274 | 0.347054 | 1(Win) | true |
| Glaze | 3326.53 | 0.0830676 | 298.016ms | 9578 | 4890 | 25441.3 | 2745.89 | 0.0728215 | 0.90557 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1685.89 | 0.070807 | 221.902ms | 3873 | 4890 | 11767.9 | 2190.88 | 0.178847 | 1.78618 | 1(Win) | true |
| Glaze | 1015.77 | 0.14874 | 367.485ms | 3873 | 80 | 2340.19 | 3636.25 | 0.172176 | 2.97535 | 2(Loss) | true |
| Jsonifier (two-stage) | 916.382 | 0.0628228 | 405.526ms | 3873 | 4890 | 31353.5 | 4030.61 | 0.192773 | 3.2981 | 3(Loss) | true |
| simdjson (ondemand) | 457.883 | 0.0528509 | 812.581ms | 3873 | 4890 | 88879.1 | 8066.65 | 0.0163924 | 6.6206 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1946.71 | 0.258905 | 193.731ms | 3873 | 2560 | 61774.9 | 1897.34 | 0.0123513 | 1.53578 | 1(Win) | true |
| Glaze | 1156.84 | 0.14877 | 322.301ms | 3873 | 640 | 14439.7 | 3192.81 | 0 | 2.59571 | 2(Loss) | true |
| Jsonifier (two-stage) | 1019.53 | 0.0736571 | 363.832ms | 3873 | 2560 | 18228.9 | 3622.81 | 0.0625769 | 2.96009 | 3(Loss) | true |
| simdjson (ondemand) | 470.52 | 0.313187 | 779.795ms | 3873 | 80 | 48354.4 | 7850 | 1.19572 | 6.44029 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 516.275 | 0.0509406 | 719.365ms | 3873 | 4890 | 64948.8 | 7154.29 | 0.15649 | 5.86909 | 1(Win) | true |
| Glaze | 429.338 | 0.0986555 | 853.965ms | 3873 | 1280 | 92203.8 | 8602.97 | 0.0290682 | 7.06025 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4491.71 | 0.113801 | 96.5236ms | 3873 | 4890 | 4282.24 | 822.311 | 1.27565 | 0.65715 | 1(Win) | true |
| Glaze | 1554.78 | 0.165855 | 266.226ms | 3873 | 160 | 2483.88 | 2375.62 | 0.183824 | 1.93765 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 911.163 | 0.291829 | 5057.5ms | 94653 | 2560 | 2.13981e+08 | 99069.2 | 0.312506 | 3.33464 | 1(Win) | true |
| Glaze | 856.643 | 0.360561 | 5385.28ms | 94653 | 2560 | 3.69545e+08 | 105374 | 0.229844 | 3.547 | 2(Loss) | true |
| Jsonifier (two-stage) | 842.046 | 0.322488 | 5502.33ms | 94653 | 2560 | 3.05959e+08 | 107201 | 0.386462 | 3.60846 | 3(Loss) | true |
| simdjson (ondemand) | 726.372 | 0.263455 | 6361.87ms | 94653 | 2560 | 2.74411e+08 | 124273 | 0.197821 | 4.18326 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1480.33 | 0.159108 | 7728.57ms | 94653 | 4890 | 4.60304e+07 | 60978.5 | 0.132697 | 2.05189 | 1(Win) | true |
| Glaze | 1406.48 | 0.160766 | 8093.77ms | 94653 | 160 | 1.70337e+06 | 64180 | 0.0272596 | 2.15988 | 2(Loss) | true |
| Jsonifier (two-stage) | 1331.99 | 0.0344232 | 8445.67ms | 94653 | 4890 | 2.66122e+06 | 67769.6 | 0.0305013 | 2.28105 | 3(Loss) | true |
| simdjson (ondemand) | 1074.13 | 0.137121 | 5076.93ms | 94653 | 320 | 4.24927e+06 | 84038.4 | 0.0353386 | 2.82878 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11941.2 | 0.163073 | 774.523ms | 94653 | 160 | 24314.1 | 7559.38 | 0.107367 | 0.253549 | 1(Win) | true |
| Glaze | 4034.54 | 0.254945 | 2246.7ms | 94653 | 4890 | 1.59105e+07 | 22373.8 | 0.316674 | 0.752473 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12663.9 | 0.0675501 | 717.231ms | 94653 | 2560 | 59350.3 | 7127.97 | 0.0778791 | 0.238669 | 1(Win) | true |
| Glaze | 4535.66 | 0.111912 | 1985.51ms | 94653 | 320 | 158743 | 19901.9 | 0.00628121 | 0.668884 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1080.7 | 0.307607 | 5629.96ms | 124597 | 2560 | 2.92842e+08 | 109951 | 0.021925 | 2.81166 | 1(Win) | true |
| Jsonifier (two-stage) | 1068.49 | 0.340855 | 5688.37ms | 124597 | 2560 | 3.67837e+08 | 111208 | 0.104044 | 2.8438 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 959.003 | 0.325417 | 6333.34ms | 124597 | 2560 | 4.16195e+08 | 123905 | 0.256872 | 3.16847 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 953.466 | 0.222484 | 6368ms | 124597 | 2560 | 1.96808e+08 | 124624 | 0.294245 | 3.18698 | 3(Tie) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1695.34 | 0.0974386 | 8666.72ms | 124597 | 640 | 2.985e+06 | 70089.2 | 0.2138 | 1.79208 | 1(Win) | true |
| Jsonifier | 1659.63 | 0.0685284 | 8834.21ms | 124597 | 640 | 1.54068e+06 | 71597.2 | 0.0690098 | 1.83074 | 2(Loss) | true |
| Glaze | 1479.94 | 0.0448771 | 9764.58ms | 124597 | 1280 | 1.66183e+06 | 80290.5 | 0.0186857 | 2.05308 | 3(Loss) | true |
| simdjson (ondemand) | 1376.69 | 0.0476416 | 5184.97ms | 124597 | 2560 | 4.3287e+06 | 86312.3 | 0.0334791 | 2.20711 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12467.5 | 0.231392 | 1047.33ms | 136037 | 2560 | 1.4842e+06 | 10405.9 | 0.0540853 | 0.243188 | 1(Win) | true |
| Glaze | 4481.67 | 0.270423 | 2899.21ms | 136076 | 4890 | 2.99834e+07 | 28956.2 | 0.0643454 | 0.677546 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12616.9 | 0.0463355 | 1032.26ms | 136037 | 4890 | 111006 | 10282.7 | 0.012513 | 0.239883 | 1(Win) | true |
| Glaze | 5012.81 | 0.15812 | 2608.84ms | 136076 | 160 | 268097 | 25888.1 | 0.0603195 | 0.605449 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 723.165 | 1.24501 | 9157.18ms | 2251027 | 30 | 4.09782e+10 | 2.96854e+06 | 0.226098 | 4.20261 | 1(Win) | true |
| Jsonifier (two-stage) | 689.124 | 0.396125 | 9665.54ms | 2251027 | 160 | 2.43642e+10 | 3.11518e+06 | 0.542787 | 4.40997 | 2(Loss) | true |
| simdjson (ondemand) | 432.372 | 0.305391 | 7473.11ms | 2251027 | 80 | 1.83929e+10 | 4.96505e+06 | 0.0195076 | 7.02904 | 3(Loss) | true |
| Glaze | 408.983 | 0.415789 | 7894.75ms | 2251027 | 80 | 3.81055e+10 | 5.24899e+06 | 0.193936 | 7.4313 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 890.907 | 1.09981 | 9143.02ms | 2251027 | 40 | 2.80927e+10 | 2.40962e+06 | 0.0157676 | 3.41117 | 1(Win) | true |
| Jsonifier (two-stage) | 831.155 | 0.484587 | 9668.02ms | 2251027 | 160 | 2.50646e+10 | 2.58285e+06 | 0.451305 | 3.65634 | 2(Loss) | true |
| simdjson (ondemand) | 485.605 | 0.32465 | 7412.61ms | 2251027 | 30 | 6.1794e+09 | 4.42076e+06 | 0.609356 | 6.25864 | 3(Loss) | true |
| Glaze | 448.047 | 0.466497 | 7964.08ms | 2251027 | 80 | 3.9967e+10 | 4.79134e+06 | 0.147731 | 6.78316 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1178 | 0.101231 | 5236.57ms | 2090234 | 160 | 4.69513e+08 | 1.69219e+06 | 0.161997 | 2.57975 | 1(Win) | true |
| Glaze | 843.642 | 0.106855 | 7369.76ms | 2090234 | 80 | 5.09978e+08 | 2.36285e+06 | 0.267602 | 3.60234 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1420.83 | 0.194047 | 8900.73ms | 2090234 | 30 | 2.22351e+08 | 1.40298e+06 | 0.0180535 | 2.13888 | 1(Win) | true |
| Glaze | 1139.17 | 0.139808 | 5404.37ms | 2090234 | 30 | 1.79556e+08 | 1.74988e+06 | 0.017147 | 2.66798 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1566.68 | 0.470793 | 10153.9ms | 5373214 | 80 | 1.89696e+10 | 3.2708e+06 | 0.227141 | 1.93976 | 1(Win) | true |
| Jsonifier | 1485.68 | 0.703407 | 5193.97ms | 5373214 | 40 | 2.35446e+10 | 3.44912e+06 | 0.0404614 | 2.04563 | 2(Loss) | true |
| simdjson (ondemand) | 998.105 | 0.241978 | 7707.66ms | 5373214 | 80 | 1.23469e+10 | 5.13403e+06 | 0.113466 | 3.04486 | 3(Loss) | true |
| Glaze | 892.369 | 0.539003 | 8646.6ms | 5373214 | 30 | 2.87398e+10 | 5.74235e+06 | 0.0275073 | 3.40586 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1864.62 | 0.443452 | 10137.1ms | 5373214 | 80 | 1.18815e+10 | 2.74818e+06 | 0.113385 | 1.62982 | 1(Win) | true |
| Jsonifier | 1761.44 | 0.425625 | 5151.31ms | 5373214 | 80 | 1.22653e+10 | 2.90915e+06 | 0.0204139 | 1.72534 | 2(Loss) | true |
| simdjson (ondemand) | 1099.66 | 0.237148 | 7750.29ms | 5373214 | 40 | 4.88485e+09 | 4.65989e+06 | 0.144633 | 2.76365 | 3(Loss) | true |
| Glaze | 982.273 | 0.360748 | 8569.6ms | 5373214 | 40 | 1.41668e+10 | 5.21677e+06 | 0.414829 | 3.09389 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2688.96 | 0.15706 | 7402.76ms | 6661897 | 160 | 2.20331e+09 | 2.36273e+06 | 0.5043 | 1.13019 | 1(Win) | true |
| Glaze | 1386.47 | 0.22542 | 6710.97ms | 6661897 | 40 | 4.26798e+09 | 4.58236e+06 | 2.42476 | 2.19188 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4083.76 | 0.147093 | 9828.03ms | 6661897 | 80 | 4.18939e+08 | 1.55574e+06 | 0.0275668 | 0.744087 | 1(Win) | true |
| Glaze | 3130.5 | 0.152926 | 6304.2ms | 6661897 | 30 | 2.88968e+08 | 2.02948e+06 | 0.192126 | 0.97069 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1635.98 | 0.11633 | 7426.7ms | 500299 | 640 | 7.3666e+07 | 291642 | 0.0312445 | 1.8577 | 1(Win) | true |
| Jsonifier (two-stage) | 1309.47 | 0.1363 | 9402.54ms | 500299 | 40 | 9.86548e+06 | 364362 | 0.02997 | 2.32084 | 2(Loss) | true |
| Glaze | 883.56 | 0.0902797 | 6860.64ms | 500299 | 320 | 7.60532e+07 | 540000 | 0.222882 | 3.43977 | 3(Loss) | true |
| simdjson (ondemand) | 629.32 | 0.0735554 | 9640ms | 500299 | 640 | 1.99033e+08 | 758155 | 0.0209346 | 4.82927 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1947 | 0.0481955 | 7136.09ms | 500299 | 1280 | 1.78546e+07 | 245055 | 0.134228 | 1.56091 | 1(Win) | true |
| Jsonifier (two-stage) | 1497.89 | 0.0577909 | 9051.34ms | 500299 | 1280 | 4.33739e+07 | 318529 | 0.094339 | 2.02884 | 2(Loss) | true |
| Glaze | 994.134 | 0.0470969 | 6576.71ms | 500299 | 640 | 3.26989e+07 | 479938 | 0.0116565 | 3.05721 | 3(Loss) | true |
| simdjson (ondemand) | 725.819 | 0.176322 | 8777.22ms | 500299 | 40 | 5.37374e+07 | 657358 | 0.00874791 | 4.18723 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8608.89 | 0.0475163 | 5555.17ms | 500299 | 4890 | 3.39125e+06 | 55422 | 0.191707 | 0.352889 | 1(Win) | true |
| Glaze | 4225.53 | 0.140459 | 5825.65ms | 500299 | 320 | 8.04905e+06 | 112914 | 0.471303 | 0.719064 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8564.85 | 0.0439382 | 5574.22ms | 500299 | 2560 | 1.53371e+06 | 55707 | 0.245103 | 0.354662 | 1(Win) | true |
| Glaze | 4571.87 | 0.0526283 | 5332.15ms | 500299 | 2560 | 7.72238e+06 | 104360 | 0.0119014 | 0.66452 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2671.16 | 0.11164 | 5230.88ms | 1151920 | 160 | 3.3729e+07 | 411266 | 0.0736075 | 1.1377 | 1(Win) | true |
| Jsonifier | 2375.59 | 0.120464 | 5863.88ms | 1151920 | 160 | 4.96517e+07 | 462436 | 0.0517372 | 1.27929 | 2(Loss) | true |
| Glaze | 1635.11 | 0.0965397 | 8530.2ms | 1151920 | 160 | 6.73107e+07 | 671856 | 0.0635771 | 1.85867 | 3(Loss) | true |
| simdjson (ondemand) | 1360.8 | 0.230873 | 5088.69ms | 1151920 | 80 | 2.77903e+08 | 807288 | 0.00774138 | 2.23336 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3023.57 | 0.08354 | 5088.57ms | 1151920 | 640 | 5.89622e+07 | 363331 | 0.062447 | 1.00507 | 1(Win) | true |
| Jsonifier | 2658.87 | 0.18735 | 5702.5ms | 1151920 | 30 | 1.79754e+07 | 413167 | 0.0588601 | 1.14299 | 2(Loss) | true |
| Glaze | 1775.38 | 0.0484816 | 8330.92ms | 1151920 | 640 | 5.75968e+07 | 618774 | 0.0443725 | 1.71181 | 3(Loss) | true |
| simdjson (ondemand) | 1547.92 | 0.116017 | 9432.3ms | 1151920 | 320 | 2.16941e+08 | 709697 | 0.018277 | 1.96327 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4457.78 | 0.355245 | 7853.05ms | 1439562 | 40 | 4.78785e+07 | 307972 | 0.00730638 | 0.681382 | 1(Win) | true |
| Glaze | 1927.24 | 0.128584 | 9083.75ms | 1439584 | 320 | 2.68488e+08 | 712363 | 0.230134 | 1.57646 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13076 | 0.0817119 | 5366.87ms | 1439562 | 640 | 4.71043e+06 | 104992 | 0.0423961 | 0.232216 | 1(Win) | true |
| Glaze | 7191.23 | 0.152685 | 9764.38ms | 1439584 | 2560 | 2.17522e+08 | 190912 | 0.317932 | 0.422453 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1354.44 | 0.0382446 | 3982.38ms | 56369 | 4890 | 1.1267e+06 | 39689.9 | 0.213278 | 2.24251 | 1(Win) | true |
| Glaze | 1172.7 | 0.0414264 | 4585.24ms | 56369 | 4890 | 1.76347e+06 | 45840.9 | 0.0651929 | 2.59029 | 2(Loss) | true |
| Jsonifier (two-stage) | 1092.73 | 0.0372202 | 4912.6ms | 56369 | 4890 | 1.63953e+06 | 49195.7 | 0.205363 | 2.77984 | 3(Loss) | true |
| simdjson (ondemand) | 768.914 | 0.129511 | 7045.15ms | 56369 | 80 | 655884 | 69913.8 | 0.0232375 | 3.95138 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2099.61 | 0.0674342 | 3026.74ms | 56369 | 2560 | 763137 | 25603.6 | 0.0445296 | 1.44617 | 1(Win) | true |
| Glaze | 1886.17 | 0.0874471 | 3297.47ms | 56369 | 2560 | 1.59019e+06 | 28500.9 | 0.101113 | 1.60979 | 2(Loss) | true |
| Jsonifier (two-stage) | 1546.2 | 0.108094 | 3965.25ms | 56369 | 160 | 225981 | 34767.5 | 0.25592 | 1.96419 | 3(Loss) | true |
| simdjson (ondemand) | 998.69 | 0.0810189 | 5797.07ms | 56369 | 1280 | 2.43446e+06 | 53828.2 | 0.00914284 | 3.04198 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11278.4 | 0.151652 | 484.318ms | 56369 | 640 | 33439.3 | 4766.41 | 0.180624 | 0.268012 | 1(Win) | true |
| Glaze | 4172.06 | 0.125926 | 1293.47ms | 56369 | 640 | 168496 | 12885.2 | 0.0157667 | 0.727124 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11745.3 | 0.0577833 | 459.967ms | 56369 | 4890 | 34202.9 | 4576.93 | 0.0200369 | 0.256751 | 1(Win) | true |
| Glaze | 4715.47 | 0.0574383 | 1145.66ms | 56369 | 4890 | 209673 | 11400.3 | 0.298581 | 0.642178 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1573.57 | 0.0472258 | 5081.45ms | 83958 | 1280 | 739126 | 50883.3 | 0.0218071 | 1.93061 | 1(Win) | true |
| Glaze | 1470.85 | 0.0434141 | 5460.2ms | 83958 | 2560 | 1.42985e+06 | 54437 | 0.123199 | 2.06532 | 2(Loss) | true |
| Jsonifier | 1439.82 | 0.0523667 | 5555.77ms | 83958 | 1280 | 1.0855e+06 | 55610.2 | 0.210707 | 2.11001 | 3(Loss) | true |
| simdjson (ondemand) | 1114.85 | 0.0422732 | 7181.37ms | 83958 | 4890 | 4.50746e+06 | 71820.2 | 0.102777 | 2.72521 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2188.04 | 0.0390483 | 4115.22ms | 83958 | 2560 | 522703 | 36593.7 | 0.0472043 | 1.38817 | 1(Win) | true |
| Glaze | 2175 | 0.111588 | 4148.58ms | 83958 | 640 | 1.07998e+06 | 36813.1 | 0.00339541 | 1.39638 | 2(Loss) | true |
| Jsonifier | 1926.84 | 0.0309276 | 4624.38ms | 83958 | 4890 | 807669 | 41554.3 | 0.0480531 | 1.57645 | 3(Loss) | true |
| simdjson (ondemand) | 1434.97 | 0.0552423 | 5986.95ms | 83958 | 2560 | 2.43232e+06 | 55797.9 | 0.0348056 | 2.11714 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11537.2 | 0.0802457 | 784.213ms | 94370 | 4890 | 191611 | 7800.72 | 0.020365 | 0.262577 | 1(Win) | true |
| Glaze | 4048.48 | 0.10815 | 2248.92ms | 94370 | 1280 | 739856 | 22230.2 | 0.242604 | 0.749856 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12117.1 | 0.0664069 | 744.428ms | 94370 | 2560 | 62278.4 | 7427.38 | 0.582988 | 0.249543 | 1(Win) | true |
| Glaze | 4393.37 | 0.468642 | 2049.79ms | 94370 | 640 | 5.8984e+06 | 20485 | 0.190325 | 0.690222 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1080.83 | 0.152397 | 4716.58ms | 53331 | 4890 | 2.51482e+07 | 47056.8 | 0.207075 | 2.81048 | 1(Win) | true |
| Glaze | 1040.43 | 0.234868 | 4885.69ms | 53331 | 2560 | 3.37462e+07 | 48884.1 | 0.0401778 | 2.91981 | 2(Loss) | true |
| Jsonifier (two-stage) | 963.039 | 0.18506 | 5290.06ms | 53331 | 4890 | 4.67097e+07 | 52812.4 | 0.0550786 | 3.15448 | 3(Loss) | true |
| simdjson (ondemand) | 725.755 | 0.130921 | 6992.55ms | 53331 | 4890 | 4.1163e+07 | 70079.3 | 0.00352032 | 4.18634 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1682.5 | 0.0650593 | 3704.41ms | 53331 | 2560 | 990167 | 30229.1 | 0.0661178 | 1.80473 | 1(Win) | true |
| Glaze | 1589.1 | 0.0512172 | 3853.04ms | 53331 | 4890 | 1.31401e+06 | 32005.8 | 0.298402 | 1.9111 | 2(Loss) | true |
| Jsonifier (two-stage) | 1433.25 | 0.0542693 | 4231.22ms | 53331 | 4890 | 1.81358e+06 | 35486.2 | 0.0116809 | 2.11916 | 3(Loss) | true |
| simdjson (ondemand) | 957.433 | 0.0757517 | 5889.91ms | 53331 | 1280 | 2.07271e+06 | 53121.6 | 0.247243 | 3.17298 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11531.9 | 0.0987608 | 487.377ms | 58581 | 4890 | 111941 | 4844.58 | 0.135052 | 0.261818 | 1(Win) | true |
| Glaze | 5210.92 | 0.266973 | 1086.07ms | 58581 | 1280 | 1.04864e+06 | 10721.2 | 0.37082 | 0.581866 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12214.1 | 0.317449 | 461.48ms | 58581 | 2560 | 539729 | 4573.98 | 0.157386 | 0.246323 | 1(Win) | true |
| Glaze | 6291.18 | 0.162267 | 896.587ms | 58581 | 1280 | 265778 | 8880.23 | 0.819329 | 0.480499 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1161.53 | 0.65087 | 5464.7ms | 65103 | 640 | 7.74662e+07 | 53453 | 0.686056 | 2.61535 | 1(Win) | true |
| Glaze | 1101.21 | 0.335407 | 5782.54ms | 65103 | 4890 | 1.74871e+08 | 56381 | 1.24278 | 2.7586 | 2(Loss) | true |
| Jsonifier | 1084.94 | 0.548582 | 5754.53ms | 65103 | 2560 | 2.52299e+08 | 57226.4 | 0.128082 | 2.80011 | 3(Loss) | true |
| simdjson (ondemand) | 900.269 | 0.16472 | 6971.82ms | 65103 | 1280 | 1.6518e+07 | 68965 | 0.263963 | 3.37488 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1710.24 | 0.140561 | 4350.59ms | 65103 | 1280 | 3.33291e+06 | 36303 | 0.231014 | 1.77594 | 1(Win) | true |
| Jsonifier | 1620.33 | 0.359961 | 4715.08ms | 65103 | 40 | 760968 | 38317.5 | 0.0195771 | 1.87424 | 2(Loss) | true |
| Glaze | 1560.57 | 0.795125 | 4712.89ms | 65103 | 2560 | 2.56182e+08 | 39785 | 0.647429 | 1.94623 | 3(Loss) | true |
| simdjson (ondemand) | 1145.49 | 0.104491 | 6112.39ms | 65103 | 640 | 2.05285e+06 | 54201.1 | 0.264801 | 2.65209 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10978.4 | 0.151623 | 737.959ms | 78778 | 30 | 3229.89 | 6843.33 | 0 | 0.276242 | 1(Win) | true |
| Glaze | 3404.1 | 1.61512 | 2172.39ms | 78778 | 30 | 3.81183e+06 | 22070 | 2.28749 | 0.892105 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11209 | 0.125142 | 691.737ms | 78778 | 40 | 2814.1 | 6702.5 | 0.087108 | 0.269846 | 1(Win) | true |
| Glaze | 3675.62 | 0.768942 | 2013.26ms | 78778 | 4890 | 1.20794e+08 | 20439.7 | 1.79837 | 0.824932 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1371.51 | 0.202693 | 815.684ms | 11812 | 320 | 88690.3 | 8213.44 | 0.0799634 | 2.21062 | 1(Win) | true |
| Jsonifier (two-stage) | 1184.68 | 0.249033 | 941.752ms | 11812 | 80 | 44859.2 | 9508.75 | 0.0394529 | 2.5588 | 2(Loss) | true |
| Glaze | 976.814 | 0.137064 | 1161.55ms | 11812 | 640 | 159901 | 11532.2 | 0.0866387 | 3.10551 | 3(Loss) | true |
| simdjson (ondemand) | 599.311 | 0.194061 | 1889.32ms | 11812 | 80 | 106441 | 18796.2 | 0.0465302 | 5.06569 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1594.33 | 0.109599 | 796.46ms | 11812 | 1280 | 76755.8 | 7065.55 | 0.025425 | 1.90052 | 1(Win) | true |
| Jsonifier (two-stage) | 1345.13 | 0.109128 | 935.391ms | 11812 | 4890 | 408416 | 8374.52 | 0.248603 | 2.25361 | 2(Loss) | true |
| Glaze | 1144.48 | 0.0958013 | 1076.51ms | 11812 | 4890 | 434794 | 9842.74 | 0.292211 | 2.64961 | 3(Loss) | true |
| simdjson (ondemand) | 652.32 | 0.0592803 | 1823.9ms | 11812 | 4890 | 512455 | 17268.8 | 0.0476699 | 4.6528 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9253.29 | 0.119466 | 123.001ms | 11812 | 2560 | 5414.8 | 1217.38 | 0.0865607 | 0.322638 | 1(Win) | true |
| Glaze | 3356.42 | 0.198192 | 338.35ms | 11812 | 4890 | 216359 | 3356.2 | 0.203701 | 0.899508 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9795.48 | 0.696209 | 116.006ms | 11812 | 40 | 2564.1 | 1150 | 0.576369 | 0.304146 | 1(Win) | true |
| Glaze | 3853.25 | 0.0780778 | 293.926ms | 11812 | 4890 | 25477.5 | 2923.46 | 0.169278 | 0.778287 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2318.44 | 0.12849 | 1044.7ms | 25388 | 4890 | 880462 | 10443.2 | 0.0859029 | 1.30817 | 1(Win) | true |
| Jsonifier | 2209.24 | 0.143696 | 1096.31ms | 25388 | 640 | 158723 | 10959.4 | 0.0456022 | 1.3727 | 2(Loss) | true |
| Glaze | 1510.77 | 0.0729755 | 1600.37ms | 25388 | 4890 | 668843 | 16026.2 | 0.0247766 | 2.00847 | 3(Loss) | true |
| simdjson (ondemand) | 1211.88 | 0.1116 | 1994.77ms | 25388 | 2560 | 1.27266e+06 | 19978.8 | 0.177847 | 2.50502 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2544.86 | 0.103857 | 1040.33ms | 25388 | 4890 | 477428 | 9514.05 | 0.309981 | 1.1915 | 1(Win) | true |
| Jsonifier | 2444.8 | 0.0813697 | 1084.02ms | 25388 | 4890 | 317544 | 9903.42 | 0.0581843 | 1.24048 | 2(Loss) | true |
| Glaze | 1712.83 | 0.1082 | 1508.69ms | 25388 | 640 | 149715 | 14135.6 | 0.172735 | 1.77163 | 3(Loss) | true |
| simdjson (ondemand) | 1332.63 | 0.0954021 | 1927.71ms | 25388 | 2560 | 769122 | 18168.5 | 0.0760525 | 2.27744 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14328.7 | 0.215462 | 210.414ms | 31235 | 640 | 12840.7 | 2078.91 | 0.366931 | 0.210226 | 1(Win) | true |
| Glaze | 5186.96 | 0.133298 | 579.05ms | 31235 | 4890 | 286557 | 5742.86 | 0.193065 | 0.583753 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15528.5 | 0.146968 | 195.212ms | 31235 | 1280 | 10173.7 | 1918.28 | 0.146401 | 0.192277 | 1(Win) | true |
| Glaze | 5618.58 | 0.15602 | 533.518ms | 31235 | 4890 | 334579 | 5301.7 | 0.00622771 | 0.536963 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2232.17 | 0.124839 | 4639.12ms | 108313 | 2560 | 8.54373e+06 | 46275.7 | 0.127795 | 1.36089 | 1(Win) | true |
| Jsonifier (two-stage) | 1502.17 | 0.0333146 | 6877.97ms | 108313 | 2560 | 1.34349e+06 | 68764.3 | 0.065852 | 2.02256 | 2(Loss) | true |
| Glaze | 1406.53 | 0.0884667 | 7353.9ms | 108313 | 1280 | 5.40298e+06 | 73439.8 | 0.0559244 | 2.16014 | 3(Loss) | true |
| simdjson (ondemand) | 877.308 | 0.107274 | 6040.02ms | 108313 | 160 | 2.5525e+06 | 117741 | 0.0743708 | 3.46373 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2929.22 | 0.125219 | 3793.75ms | 108313 | 320 | 623948 | 35263.8 | 0.0922476 | 1.03688 | 1(Win) | true |
| Jsonifier (two-stage) | 1776.59 | 0.0440606 | 6071.1ms | 108313 | 2560 | 1.68007e+06 | 58142.4 | 0.00356064 | 1.71011 | 2(Loss) | true |
| Glaze | 1742.33 | 0.168358 | 6230.63ms | 108313 | 1280 | 1.2752e+07 | 59285.7 | 0.0754513 | 1.7435 | 3(Loss) | true |
| simdjson (ondemand) | 991.74 | 0.0924404 | 5479.88ms | 108313 | 640 | 5.93293e+06 | 104156 | 0.132189 | 3.06388 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13510.3 | 0.0868375 | 767.63ms | 108313 | 2560 | 112846 | 7645.66 | 0.0127711 | 0.224234 | 1(Win) | true |
| Glaze | 3953.39 | 0.128163 | 2653.91ms | 108313 | 4890 | 5.48347e+06 | 26128.3 | 1.1567 | 0.768012 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14023.3 | 0.0798667 | 734.976ms | 108313 | 2560 | 88599.7 | 7365.98 | 0.22376 | 0.216008 | 1(Win) | true |
| Glaze | 4410.22 | 0.140608 | 2342.2ms | 108313 | 4890 | 5.30358e+06 | 23421.8 | 0.0432259 | 0.688054 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2363.6 | 0.10406 | 7405.82ms | 183677 | 1280 | 7.61272e+06 | 74110.5 | 0.0658421 | 1.28534 | 1(Win) | true |
| Jsonifier | 2162.21 | 0.0880109 | 8085.96ms | 183677 | 320 | 1.62681e+06 | 81013.4 | 0.0212111 | 1.40522 | 2(Loss) | true |
| Glaze | 1799.24 | 0.120023 | 9720.35ms | 183677 | 640 | 8.73849e+06 | 97356.6 | 0.107735 | 1.68882 | 3(Loss) | true |
| simdjson (ondemand) | 1427.69 | 0.0916749 | 6295.34ms | 183677 | 1280 | 1.6194e+07 | 122694 | 0.067796 | 2.12845 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2780.11 | 0.124156 | 6586.77ms | 183677 | 80 | 489563 | 63007.5 | 0.15846 | 1.09282 | 1(Win) | true |
| Jsonifier | 2543.62 | 0.0418176 | 7158.72ms | 183677 | 4890 | 4.05539e+06 | 68865.6 | 0.0534001 | 1.19448 | 2(Loss) | true |
| Glaze | 2125.15 | 0.116029 | 8581.76ms | 183677 | 320 | 2.92696e+06 | 82426.2 | 0.171072 | 1.42975 | 3(Loss) | true |
| simdjson (ondemand) | 1597.99 | 0.0591475 | 5732.84ms | 183677 | 2560 | 1.07616e+07 | 109618 | 0.0221343 | 1.9016 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13647.8 | 0.0916796 | 1515.29ms | 213963 | 640 | 120249 | 14951.2 | 0.00209008 | 0.222311 | 1(Win) | true |
| Glaze | 4406.45 | 0.221367 | 4785.4ms | 213963 | 2560 | 2.69007e+07 | 46307.3 | 1.15655 | 0.689364 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13751.8 | 0.0457326 | 1478.16ms | 213963 | 4890 | 225174 | 14838.1 | 0.281253 | 0.220397 | 1(Win) | true |
| Glaze | 5116.63 | 0.945132 | 4118.42ms | 213963 | 80 | 1.13654e+07 | 39880 | 0.434427 | 0.593423 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 562.304 | 0.224577 | 9505.68ms | 1834197 | 40 | 1.95226e+09 | 3.11082e+06 | 0.952823 | 5.40417 | 1(Win) | true |
| Jsonifier | 459.478 | 0.270862 | 5746.34ms | 1834197 | 80 | 8.50645e+09 | 3.80699e+06 | 0.386569 | 6.61441 | 2(Loss) | true |
| Glaze | 318.825 | 0.334171 | 8253.8ms | 1834197 | 40 | 1.34458e+10 | 5.48648e+06 | 0.241132 | 9.53298 | 3(Loss) | true |
| simdjson (ondemand) | 196.982 | 0.241064 | 6232.46ms | 1834197 | 40 | 1.833e+10 | 8.88012e+06 | 0.0945043 | 15.4287 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 624.178 | 0.501004 | 9545.2ms | 1834197 | 40 | 7.88529e+09 | 2.80245e+06 | 0.0422428 | 4.86897 | 1(Win) | true |
| Jsonifier | 496.936 | 0.198991 | 5688.72ms | 1834197 | 80 | 3.92508e+09 | 3.52002e+06 | 0.213379 | 6.11603 | 2(Loss) | true |
| Glaze | 333.83 | 0.229626 | 8354.17ms | 1834197 | 80 | 1.15817e+10 | 5.23987e+06 | 0.464684 | 9.10402 | 3(Loss) | true |
| simdjson (ondemand) | 203.674 | 0.194806 | 6185.42ms | 1834197 | 30 | 8.39739e+09 | 8.58835e+06 | 0.0612083 | 14.9214 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 730.556 | 0.102656 | 7408.26ms | 1834197 | 80 | 4.83328e+08 | 2.39438e+06 | 0.195002 | 4.16001 | 1(Win) | true |
| Glaze | 666.594 | 0.0815347 | 8146.51ms | 1833577 | 160 | 7.31948e+08 | 2.62324e+06 | 0.241769 | 4.55923 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 824.503 | 0.0866557 | 6594.29ms | 1834197 | 160 | 5.40782e+08 | 2.12155e+06 | 0.0530258 | 3.68597 | 1(Win) | true |
| Glaze | 726.206 | 0.179469 | 7461.12ms | 1833577 | 80 | 1.494e+09 | 2.4079e+06 | 0.0109004 | 4.18514 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2047.13 | 0.250519 | 5170.16ms | 7351818 | 80 | 5.8894e+09 | 3.42492e+06 | 0.131599 | 1.48455 | 1(Win) | true |
| Jsonifier | 1958.74 | 0.178476 | 5426.18ms | 7351818 | 30 | 1.22438e+09 | 3.57946e+06 | 0.0666322 | 1.55163 | 2(Loss) | true |
| Glaze | 1123.89 | 0.345772 | 9360.04ms | 7351818 | 80 | 3.72227e+10 | 6.23834e+06 | 0.318518 | 2.7043 | 3(Loss) | true |
| simdjson (ondemand) | 700.433 | 0.274926 | 7079.68ms | 7351818 | 30 | 2.272e+10 | 1.00099e+07 | 0.320122 | 4.33935 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2042.11 | 1.02752 | 5823.33ms | 7351818 | 30 | 3.73368e+10 | 3.43333e+06 | 1.87719 | 1.48821 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2020.37 | 1.42382 | 5755.06ms | 7351818 | 40 | 9.76553e+10 | 3.47028e+06 | 1.1577 | 1.5041 | 1(Tie) | true |
| Glaze | 1112.84 | 0.643217 | 10283.2ms | 7351818 | 80 | 1.31381e+11 | 6.30034e+06 | 1.57551 | 2.73102 | 3(Loss) | true |
| simdjson (ondemand) | 649.756 | 0.615117 | 7858.07ms | 7351818 | 30 | 1.32168e+11 | 1.07906e+07 | 0.523538 | 4.6776 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2223 | 0.107462 | 6393.97ms | 9930848 | 80 | 1.67683e+09 | 4.26036e+06 | 0.836246 | 1.3672 | 1(Win) | true |
| Glaze | 1813.17 | 0.155405 | 7805.97ms | 9930228 | 40 | 2.63531e+09 | 5.223e+06 | 0.302752 | 1.67623 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 3080.51 | 0.599859 | 9544.66ms | 9930228 | 160 | 5.44116e+10 | 3.07423e+06 | 1.53377 | 0.986477 | 1(Win) | true |
| Jsonifier | 2853.82 | 0.875423 | 10359.2ms | 9930848 | 40 | 3.37611e+10 | 3.31864e+06 | 0.420811 | 1.06482 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 669.037 | 0.217812 | 8145.18ms | 1834197 | 160 | 5.18889e+09 | 2.61454e+06 | 0.28057 | 4.54256 | 1(Win) | true |
| Jsonifier (two-stage) | 581.156 | 0.434718 | 9329.74ms | 1834197 | 160 | 2.73931e+10 | 3.00991e+06 | 0.168249 | 5.22942 | 2(Loss) | true |
| simdjson (ondemand) | 352.465 | 0.493074 | 7453.75ms | 1834197 | 80 | 4.79044e+10 | 4.96284e+06 | 0.717808 | 8.62294 | 3(Loss) | true |
| Glaze | 320.616 | 0.261866 | 8237.25ms | 1834197 | 30 | 6.12351e+09 | 5.45583e+06 | 0.633505 | 9.47961 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 742.772 | 0.281993 | 8150.16ms | 1834197 | 160 | 7.05632e+09 | 2.355e+06 | 0.0233226 | 4.09163 | 1(Win) | true |
| Jsonifier (two-stage) | 642.353 | 0.215579 | 9273.38ms | 1834197 | 160 | 5.51413e+09 | 2.72316e+06 | 0.49794 | 4.73124 | 2(Loss) | true |
| simdjson (ondemand) | 379.171 | 0.194227 | 7332.36ms | 1834197 | 80 | 6.42292e+09 | 4.61329e+06 | 0.328509 | 8.01562 | 3(Loss) | true |
| Glaze | 336.781 | 0.429921 | 8238.81ms | 1834197 | 40 | 1.9945e+10 | 5.19396e+06 | 0.409176 | 9.02462 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 725.192 | 0.115993 | 7473.82ms | 1834197 | 40 | 3.13121e+08 | 2.41209e+06 | 0.0570066 | 4.19079 | 1(Win) | true |
| Glaze | 587.503 | 0.100437 | 9204.67ms | 1833577 | 160 | 1.42984e+09 | 2.97638e+06 | 0.268292 | 5.17305 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 806.065 | 0.15126 | 6732.18ms | 1834197 | 30 | 3.23236e+08 | 2.17008e+06 | 0.0951715 | 3.77032 | 1(Win) | true |
| Glaze | 738.35 | 0.165248 | 7314.55ms | 1833577 | 80 | 1.22528e+09 | 2.3683e+06 | 0.0821644 | 4.1162 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2086.81 | 0.469576 | 5027.36ms | 7351818 | 80 | 1.99124e+10 | 3.35978e+06 | 1.02247 | 1.45636 | 1(Win) | true |
| Jsonifier | 2009.1 | 0.374966 | 5219.96ms | 7351818 | 80 | 1.36981e+10 | 3.48974e+06 | 0.548955 | 1.51268 | 2(Loss) | true |
| simdjson (ondemand) | 1318.33 | 0.443285 | 8049.86ms | 7351818 | 40 | 2.22314e+10 | 5.31826e+06 | 1.09827 | 2.30542 | 3(Loss) | true |
| Glaze | 1127.56 | 0.405467 | 9321.49ms | 7351818 | 80 | 5.08522e+10 | 6.21806e+06 | 0.840408 | 2.6955 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2285.31 | 0.209135 | 5015.77ms | 7351818 | 30 | 1.23502e+09 | 3.06796e+06 | 0.326617 | 1.32981 | 1(Win) | true |
| Jsonifier | 2219.35 | 0.181307 | 5207.11ms | 7351818 | 40 | 1.31227e+09 | 3.15914e+06 | 0.346412 | 1.36938 | 2(Loss) | true |
| simdjson (ondemand) | 1401.23 | 0.24392 | 7915.29ms | 7351818 | 80 | 1.19167e+10 | 5.00364e+06 | 1.31457 | 2.16901 | 3(Loss) | true |
| Glaze | 1166.8 | 0.340784 | 9419.61ms | 7351818 | 80 | 3.35466e+10 | 6.00897e+06 | 0.170578 | 2.60476 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2431.71 | 0.129573 | 5866.17ms | 9930848 | 80 | 2.03736e+09 | 3.89471e+06 | 0.543381 | 1.24983 | 1(Win) | true |
| Glaze | 1272.05 | 0.268665 | 5215.68ms | 9930228 | 30 | 1.2002e+10 | 7.44483e+06 | 0.173109 | 2.38934 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3495.6 | 0.094504 | 8387.67ms | 9930848 | 160 | 1.04894e+09 | 2.70935e+06 | 0.0425791 | 0.869399 | 1(Win) | true |
| Glaze | 3333.75 | 0.119833 | 8830.65ms | 9930228 | 80 | 9.27033e+08 | 2.84071e+06 | 0.180307 | 0.911604 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 843.09 | 0.188559 | 6654.48ms | 461466 | 320 | 3.10009e+08 | 521994 | 0.0662563 | 3.60464 | 1(Win) | true |
| Jsonifier (two-stage) | 751.079 | 0.159496 | 7457.41ms | 461466 | 320 | 2.79483e+08 | 585941 | 0.479189 | 4.04619 | 2(Loss) | true |
| Glaze | 732.943 | 0.223063 | 7648.34ms | 461466 | 320 | 5.74042e+08 | 600440 | 0.339066 | 4.14637 | 3(Loss) | true |
| simdjson (ondemand) | 584.918 | 0.110888 | 9555.74ms | 461466 | 640 | 4.45493e+08 | 752393 | 0.0476999 | 5.19579 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1185.7 | 0.11396 | 5770.45ms | 461466 | 80 | 1.43128e+07 | 371162 | 0.0451081 | 2.56323 | 1(Win) | true |
| Jsonifier (two-stage) | 1020.4 | 0.0748593 | 6534.35ms | 461466 | 320 | 3.33565e+07 | 431290 | 0.220392 | 2.97833 | 2(Loss) | true |
| Glaze | 973.704 | 0.0751028 | 6778.09ms | 461466 | 320 | 3.68712e+07 | 451973 | 0.0195708 | 3.12131 | 3(Loss) | true |
| simdjson (ondemand) | 739.009 | 0.150195 | 8625.66ms | 461466 | 160 | 1.28001e+08 | 595511 | 0.143578 | 4.11255 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3816.16 | 0.295939 | 5895.4ms | 461466 | 320 | 3.72717e+07 | 115322 | 0.0620159 | 0.795653 | 1(Win) | true |
| Glaze | 2995.93 | 0.0886806 | 7515.64ms | 461466 | 2560 | 4.34423e+07 | 146895 | 0.106414 | 1.01429 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11282.1 | 0.12391 | 3929.83ms | 461466 | 640 | 1.49518e+06 | 39007.8 | 0.356028 | 0.269117 | 1(Win) | true |
| Glaze | 3223 | 0.0791163 | 6961.79ms | 461466 | 2560 | 2.98766e+07 | 136546 | 0.0121025 | 0.942811 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1157.21 | 0.162761 | 7626.83ms | 728486 | 640 | 6.11073e+08 | 600354 | 0.113943 | 2.62616 | 1(Win) | true |
| Jsonifier | 1052.75 | 0.129126 | 8393.17ms | 728486 | 640 | 4.64732e+08 | 659928 | 0.178111 | 2.88684 | 2(Loss) | true |
| Glaze | 995.091 | 0.156943 | 8867.17ms | 728486 | 640 | 7.68392e+08 | 698165 | 0.272494 | 3.05406 | 3(Loss) | true |
| simdjson (ondemand) | 893.458 | 0.351827 | 9903.05ms | 728486 | 30 | 2.2453e+08 | 777583 | 0.208342 | 3.40148 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1566.54 | 0.113199 | 6694.05ms | 728486 | 160 | 4.03237e+07 | 443485 | 0.201653 | 1.93989 | 1(Win) | true |
| Jsonifier | 1377.44 | 0.182155 | 7451.38ms | 728486 | 30 | 2.53222e+07 | 504370 | 0.0105731 | 2.20645 | 2(Loss) | true |
| Glaze | 1276.35 | 0.0503463 | 7957.67ms | 728486 | 640 | 4.80637e+07 | 544316 | 0.0206925 | 2.3812 | 3(Loss) | true |
| simdjson (ondemand) | 1110.73 | 0.0704572 | 8955.1ms | 728486 | 640 | 1.24296e+08 | 625480 | 0.120277 | 2.73608 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4103.67 | 0.228321 | 9852.08ms | 837491 | 640 | 1.26383e+08 | 194629 | 0.0558263 | 0.740038 | 1(Win) | true |
| Glaze | 2126.51 | 0.170353 | 9500.42ms | 837491 | 320 | 1.31002e+08 | 375589 | 0.115118 | 1.42839 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12813.8 | 0.0665735 | 6228.97ms | 837491 | 1280 | 2.20402e+06 | 62330.6 | 0.193396 | 0.237026 | 1(Win) | true |
| Glaze | 4361.95 | 0.0803114 | 9339.48ms | 837491 | 2560 | 5.53595e+07 | 183105 | 0.127887 | 0.696549 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6694.58 | 0.260471 | 6720.08ms | 466906 | 4890 | 1.46771e+08 | 66513 | 1.05035 | 0.453813 | 1(Win) | true |
| Jsonifier (two-stage) | 6452.25 | 0.622338 | 6865.44ms | 466906 | 4890 | 9.01983e+08 | 69011 | 0.413039 | 0.470861 | 2(Loss) | true |
| simdjson (ondemand) | 4248.24 | 0.056618 | 5504.18ms | 466906 | 1280 | 4.50774e+06 | 104814 | 0.0578739 | 0.715283 | 3(Loss) | true |
| Glaze | 2926.91 | 0.423681 | 7972.7ms | 466906 | 160 | 6.6472e+07 | 152132 | 0.633159 | 1.03829 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7105.66 | 0.784785 | 6553.36ms | 466906 | 40 | 9.67413e+06 | 62665 | 1.19048 | 0.427503 | 1(Win) | true |
| Jsonifier | 6655.8 | 0.666168 | 6700.77ms | 466906 | 4890 | 9.71261e+08 | 66900.5 | 0.401281 | 0.456459 | 2(Loss) | true |
| simdjson (ondemand) | 4156.69 | 0.631766 | 5551.39ms | 466906 | 2560 | 1.17251e+09 | 107123 | 1.51675 | 0.730653 | 3(Loss) | true |
| Glaze | 2930.25 | 0.376311 | 7926.71ms | 466906 | 2560 | 8.37107e+08 | 151958 | 0.722485 | 1.03699 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7682.43 | 0.0558379 | 7839.47ms | 631514 | 4890 | 9.36993e+06 | 78394.3 | 0.220798 | 0.39551 | 1(Win) | true |
| Jsonifier (two-stage) | 7647.27 | 0.136416 | 7878.47ms | 631514 | 320 | 3.69346e+06 | 78754.7 | 0.164402 | 0.397284 | 2(Loss) | true |
| simdjson (ondemand) | 5198.7 | 0.0462842 | 5926.08ms | 631514 | 1280 | 3.68004e+06 | 115848 | 0.0134893 | 0.584524 | 3(Loss) | true |
| Glaze | 3535 | 0.188899 | 8722.28ms | 631514 | 160 | 1.65717e+07 | 170370 | 0.0645237 | 0.859687 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7922.76 | 0.0349814 | 7742.52ms | 631514 | 4890 | 3.45777e+06 | 76016.3 | 0.148661 | 0.383502 | 1(Win) | true |
| Jsonifier | 7905.81 | 0.0846443 | 7791.33ms | 631514 | 640 | 2.66102e+06 | 76179.2 | 0.0244139 | 0.384331 | 2(Loss) | true |
| simdjson (ondemand) | 5360.31 | 0.0626435 | 5823.7ms | 631514 | 640 | 3.17043e+06 | 112355 | 0.0460103 | 0.566907 | 3(Loss) | true |
| Glaze | 3607.41 | 0.0536157 | 8594.96ms | 631514 | 2560 | 2.05116e+07 | 166950 | 0.0205156 | 0.842383 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1232.95 | 0.962785 | 9511.5ms | 466906 | 640 | 7.73763e+09 | 361148 | 0.0372804 | 2.46443 | 1(Win) | true |
| Glaze | 1051.4 | 1.04815 | 5467.11ms | 466906 | 640 | 1.26109e+10 | 423508 | 0.663302 | 2.89004 | 2(Loss) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 993.937 | 0.999145 | 5615.12ms | 466906 | 640 | 1.28227e+10 | 447992 | 6.14859 | 3.05684 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 900.657 | 1.07821 | 6348.94ms | 466906 | 160 | 4.54639e+09 | 494391 | 4.07621 | 3.37388 | -(Loss) | false |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2142.07 | 0.0651949 | 6179.79ms | 466906 | 1280 | 2.35086e+07 | 207872 | 0.0293815 | 1.41876 | 1(Win) | true |
| Glaze | 1751.82 | 0.144656 | 7383.57ms | 466906 | 80 | 1.08154e+07 | 254179 | 0.00442582 | 1.73483 | 2(Loss) | true |
| Jsonifier (two-stage) | 1656.93 | 0.103924 | 7754.23ms | 466906 | 640 | 4.99185e+07 | 268736 | 0.05806 | 1.83416 | 3(Loss) | true |
| simdjson (ondemand) | 1266.8 | 0.1541 | 9712.93ms | 466906 | 320 | 9.38863e+07 | 351498 | 0.18598 | 2.39875 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4581.36 | 0.849508 | 5028.3ms | 475954 | 2560 | 1.8135e+09 | 99076.5 | 0.0972103 | 0.663074 | 1(Win) | true |
| Jsonifier | 3721.01 | 1.02768 | 6392.43ms | 475954 | 640 | 1.00578e+09 | 121985 | 0.66002 | 0.815785 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15906.4 | 0.0693781 | 2879.51ms | 475954 | 1280 | 501694 | 28535.9 | 0.138724 | 0.190809 | 1(Win) | true |
| Glaze | 5629.47 | 0.193803 | 8083.79ms | 475954 | 4890 | 1.19406e+08 | 80630.2 | 0.43032 | 0.539634 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1486.84 | 0.342516 | 5144.45ms | 631514 | 640 | 1.23191e+09 | 405059 | 0.332458 | 2.04383 | 1(Win) | true |
| Glaze | 1428.01 | 0.48899 | 5372.02ms | 631514 | 320 | 1.36099e+09 | 421747 | 0.424175 | 2.12807 | 2(Loss) | true |
| Jsonifier | 1390.64 | 0.328976 | 5520.26ms | 631514 | 640 | 1.29911e+09 | 433081 | 0.137667 | 2.18524 | 3(Loss) | true |
| simdjson (ondemand) | 1248.22 | 0.294395 | 6131.35ms | 631514 | 640 | 1.29131e+09 | 482496 | 0.154232 | 2.43456 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2085.9 | 0.106548 | 8262.51ms | 631514 | 320 | 3.02843e+07 | 288729 | 0.0632762 | 1.45689 | 1(Win) | true |
| Glaze | 1938.93 | 0.0795441 | 8840.25ms | 631514 | 1280 | 7.81392e+07 | 310614 | 0.0823796 | 1.56744 | 2(Loss) | true |
| Jsonifier | 1885.52 | 0.138154 | 9017.42ms | 631514 | 160 | 3.11567e+07 | 319412 | 0.0686338 | 1.61185 | 3(Loss) | true |
| simdjson (ondemand) | 1636.97 | 0.126882 | 5054.49ms | 631514 | 640 | 1.39464e+08 | 367910 | 0.298433 | 1.8565 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4283.69 | 0.197158 | 8210.32ms | 716365 | 640 | 6.32763e+07 | 159484 | 0.415852 | 0.708965 | 1(Win) | true |
| Glaze | 1732.48 | 0.215103 | 5027.44ms | 716365 | 640 | 4.60475e+08 | 394337 | 0.388853 | 1.7534 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13417.1 | 0.0933874 | 5089.46ms | 716365 | 1280 | 2.89428e+06 | 50918.7 | 0.135971 | 0.226403 | 1(Win) | true |
| Glaze | 3181.18 | 0.319662 | 5389.18ms | 716365 | 1280 | 6.0323e+08 | 214756 | 0.742056 | 0.95531 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1310.47 | 0.189898 | 194.754ms | 2632 | 4890 | 64694.3 | 1915.4 | 0.522988 | 2.29654 | 1(Win) | true |
| Jsonifier | 1266.71 | 0.270875 | 200.122ms | 2632 | 640 | 18438.9 | 1981.56 | 0.377062 | 2.37684 | 2(Loss) | true |
| Glaze | 941.587 | 0.0834335 | 268.499ms | 2632 | 4890 | 24190.3 | 2665.79 | 0.459232 | 3.2019 | 3(Loss) | true |
| simdjson (ondemand) | 761.969 | 0.1178 | 332.604ms | 2632 | 4890 | 73637.8 | 3294.19 | 0.270434 | 3.9627 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1699.3 | 0.100998 | 182.053ms | 2632 | 4890 | 10883.5 | 1477.12 | 0.144752 | 1.7662 | 1(Win) | true |
| Jsonifier | 1680.51 | 0.131843 | 179.618ms | 2632 | 4890 | 18963.4 | 1493.64 | 0.275967 | 1.77989 | 2(Loss) | true |
| Glaze | 1603.32 | 0.865327 | 190.834ms | 2632 | 1280 | 234911 | 1565.55 | 0.233994 | 1.87171 | 3(Loss) | true |
| simdjson (ondemand) | 1212.78 | 1.80546 | 248.418ms | 2632 | 320 | 446821 | 2069.69 | 1.02196 | 2.47958 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9765.49 | 0.382949 | 28.4238ms | 2632 | 4890 | 4737.78 | 257.035 | 0.60287 | 0.289667 | 1(Win) | true |
| Glaze | 3592.53 | 0.144152 | 72.1744ms | 2632 | 4890 | 4960.45 | 698.691 | 0.00282391 | 0.824663 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11185 | 0.388677 | 24.8029ms | 2632 | 2560 | 1947.68 | 224.414 | 0.472193 | 0.248179 | 1(Win) | true |
| Glaze | 4160.34 | 0.552486 | 66.8598ms | 2632 | 30 | 333.333 | 603.333 | 0 | 0.708397 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1663.07 | 0.19761 | 199.608ms | 3370 | 160 | 2333.33 | 1932.5 | 0 | 1.81225 | 1(Win) | true |
| Jsonifier | 1345.42 | 0.180584 | 243.462ms | 3370 | 320 | 5954.55 | 2388.75 | 0.104548 | 2.24075 | 2(Loss) | true |
| Glaze | 1044.58 | 0.189781 | 305.577ms | 3370 | 640 | 21820.2 | 3076.72 | 0.470077 | 2.88836 | 3(Loss) | true |
| simdjson (ondemand) | 967.479 | 0.137713 | 334.538ms | 3370 | 2560 | 53575.9 | 3321.91 | 0.44369 | 3.11971 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2067.69 | 0.170107 | 183.822ms | 3370 | 4890 | 34185.5 | 1554.34 | 0.248218 | 1.45228 | 1(Win) | true |
| Glaze | 1719.61 | 0.0845432 | 218.325ms | 3370 | 4890 | 12208.6 | 1868.96 | 0.214189 | 1.74735 | 2(Loss) | true |
| Jsonifier | 1699.55 | 0.153439 | 224.723ms | 3370 | 2560 | 21552.7 | 1891.02 | 0.111672 | 1.77115 | 3(Loss) | true |
| simdjson (ondemand) | 1547.69 | 0.0955188 | 233.041ms | 3370 | 2560 | 10071.8 | 2076.56 | 0.157764 | 1.94425 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10193.8 | 0.24013 | 36.8665ms | 3643 | 4890 | 3275.26 | 340.818 | 1.72485 | 0.282545 | 1(Win) | true |
| Glaze | 3917.25 | 0.317275 | 91.8669ms | 3682 | 4890 | 39553.4 | 896.401 | 0.121557 | 0.758915 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11519.5 | 0.656515 | 32.6103ms | 3643 | 4890 | 19171.1 | 301.595 | 0.101573 | 0.246085 | 1(Win) | true |
| Glaze | 4454.99 | 0.138253 | 81.6388ms | 3682 | 4890 | 5806.74 | 788.2 | 0.01521 | 0.664608 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 679.587 | 0.151435 | 650.019ms | 4630 | 1280 | 123918 | 6497.34 | 0.510007 | 4.45899 | 1(Win) | true |
| Jsonifier (two-stage) | 641.87 | 0.0825985 | 691.443ms | 4630 | 2560 | 82651.9 | 6879.14 | 0.0748987 | 4.7211 | 2(Loss) | true |
| simdjson (ondemand) | 361.883 | 0.0828077 | 1228.52ms | 4630 | 1280 | 130670 | 12201.5 | 0.0326442 | 8.38366 | 3(Loss) | true |
| Glaze | 349.328 | 0.134646 | 1276.97ms | 4630 | 30 | 8689.66 | 12640 | 0.0790514 | 8.68444 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 858.762 | 0.0731077 | 639.579ms | 4630 | 4890 | 69095.8 | 5141.72 | 0.275757 | 3.52567 | 1(Win) | true |
| Jsonifier (two-stage) | 799.47 | 0.112541 | 683.173ms | 4630 | 1280 | 49452.8 | 5523.05 | 0.0325447 | 3.78846 | 2(Loss) | true |
| simdjson (ondemand) | 395.488 | 0.0719236 | 1248.64ms | 4630 | 2560 | 165074 | 11164.7 | 0.0276324 | 7.66904 | 3(Loss) | true |
| Glaze | 386.773 | 0.0680164 | 1272.27ms | 4630 | 2560 | 154354 | 11416.3 | 0.180678 | 7.84346 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1600.67 | 0.0769518 | 278.899ms | 4630 | 4890 | 22034.7 | 2758.55 | 0.265263 | 1.88622 | 1(Win) | true |
| Glaze | 1119.27 | 0.141882 | 386.084ms | 4630 | 80 | 2506.33 | 3945 | 0.381679 | 2.7028 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1653.75 | 0.318713 | 271.469ms | 4630 | 30 | 2172.41 | 2670 | 0 | 1.8094 | 1(Win) | true |
| Glaze | 1241.62 | 0.260005 | 359.675ms | 4630 | 320 | 27358.9 | 3556.25 | 0.0175716 | 2.43302 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1497.17 | 0.127079 | 746.912ms | 11579 | 160 | 14056.2 | 7375.62 | 0.413502 | 2.02649 | 1(Win) | true |
| Jsonifier | 1420.7 | 0.0559071 | 782.26ms | 11579 | 4890 | 92337.7 | 7772.64 | 0.505258 | 2.13364 | 2(Loss) | true |
| simdjson (ondemand) | 858.657 | 0.153829 | 1292.36ms | 11579 | 640 | 250473 | 12860.3 | 0.116774 | 3.53186 | 3(Loss) | true |
| Glaze | 777.573 | 0.0543187 | 1426.48ms | 11579 | 2560 | 152335 | 14201.4 | 0.137068 | 3.90314 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1791.54 | 0.075176 | 753.054ms | 11579 | 2560 | 54965.2 | 6163.75 | 0.0393077 | 1.69112 | 1(Win) | true |
| Jsonifier | 1725.21 | 0.0550428 | 772.438ms | 11579 | 4890 | 60697 | 6400.72 | 0.00507971 | 1.7559 | 2(Loss) | true |
| simdjson (ondemand) | 968.994 | 0.150744 | 1278.73ms | 11579 | 320 | 94434.9 | 11395.9 | 0.162052 | 3.12956 | 3(Loss) | true |
| Glaze | 856.887 | 0.231643 | 1414.89ms | 11579 | 320 | 285156 | 12886.9 | 0.0823803 | 3.54162 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4384.95 | 0.119603 | 325.092ms | 14795 | 1280 | 18958.1 | 3217.73 | 0.0121412 | 0.689193 | 1(Win) | true |
| Glaze | 2807.84 | 0.0862328 | 506.527ms | 14795 | 2560 | 48069.6 | 5025.08 | 0.0528319 | 1.07819 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4594.43 | 0.225365 | 309.517ms | 14795 | 4890 | 234233 | 3071.02 | 0.019307 | 0.654248 | 1(Win) | true |
| Glaze | 3127.11 | 0.094725 | 452.988ms | 14795 | 2560 | 46764.1 | 4512.03 | 0.0571716 | 0.967766 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 883.905 | 0.0709173 | 349.946ms | 3223 | 4890 | 29738.8 | 3477.4 | 0.197859 | 3.42004 | 1(Win) | true |
| Jsonifier (two-stage) | 750.21 | 0.113976 | 415.004ms | 3223 | 1280 | 27911.9 | 4097.11 | 0.199817 | 4.02971 | 2(Loss) | true |
| Glaze | 662.813 | 0.191219 | 467.886ms | 3223 | 640 | 50324.7 | 4637.34 | 0.0505153 | 4.56322 | 3(Loss) | true |
| simdjson (ondemand) | 560.981 | 0.151129 | 553.869ms | 3223 | 1280 | 87766.3 | 5479.14 | 0.350561 | 5.39669 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1213.23 | 0.116819 | 318.594ms | 3223 | 2560 | 22423.2 | 2533.48 | 0.0231225 | 2.48633 | 1(Win) | true |
| Jsonifier (two-stage) | 977.132 | 0.190189 | 383.76ms | 3223 | 1280 | 45813.5 | 3145.62 | 0.277393 | 3.09382 | 2(Loss) | true |
| Glaze | 850.849 | 0.158614 | 419.757ms | 3223 | 80 | 2626.58 | 3612.5 | 0 | 3.56096 | 3(Loss) | true |
| simdjson (ondemand) | 717.04 | 0.087262 | 484.263ms | 3223 | 2560 | 35819.9 | 4286.64 | 0.0855853 | 4.22143 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7200.45 | 0.205292 | 45.2363ms | 3223 | 2560 | 1966 | 426.875 | 0.146199 | 0.405001 | 1(Win) | true |
| Glaze | 3278.06 | 0.279757 | 97.451ms | 3223 | 1280 | 8807.64 | 937.656 | 0.586658 | 0.909417 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8021.87 | 0.262837 | 40.4839ms | 3223 | 2560 | 2596.47 | 383.164 | 0.193325 | 0.359643 | 1(Win) | true |
| Glaze | 4225.01 | 0.69054 | 76.1576ms | 3223 | 80 | 2018.99 | 727.5 | 0.692042 | 0.699488 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1327.61 | 0.319368 | 426.243ms | 5839 | 160 | 28710.3 | 4194.38 | 0.0149031 | 2.27901 | 1(Win) | true |
| Jsonifier | 1183.43 | 0.0870528 | 473.049ms | 5839 | 4890 | 82047.2 | 4705.38 | 0.12525 | 2.55607 | 2(Loss) | true |
| Glaze | 1015.35 | 0.0873522 | 550.66ms | 5839 | 2560 | 58752.9 | 5484.3 | 0.0484103 | 2.98245 | 3(Loss) | true |
| simdjson (ondemand) | 978.218 | 0.149136 | 576.531ms | 5839 | 80 | 5765.82 | 5692.5 | 0.175362 | 3.09657 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1702.54 | 0.135325 | 391.69ms | 5839 | 1280 | 25075.3 | 3270.7 | 0.270646 | 1.77181 | 1(Win) | true |
| Jsonifier | 1482.46 | 0.176149 | 440.733ms | 5839 | 160 | 7004.72 | 3756.25 | 0.166667 | 2.03919 | 2(Loss) | true |
| Glaze | 1257.26 | 0.185346 | 505.471ms | 5839 | 640 | 43129 | 4429.06 | 0.190867 | 2.40701 | 3(Loss) | true |
| simdjson (ondemand) | 1247.15 | 0.105453 | 503.851ms | 5839 | 160 | 3547.17 | 4465 | 0.140174 | 2.42366 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7953.57 | 0.128225 | 85.5335ms | 6938 | 4890 | 5564.19 | 831.902 | 0.263724 | 0.373941 | 1(Win) | true |
| Glaze | 4214.33 | 0.405001 | 162.087ms | 6960 | 640 | 26040.7 | 1575 | 0.699301 | 0.712335 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8555.65 | 0.199105 | 79.7415ms | 6938 | 1280 | 3034.84 | 773.359 | 0.273501 | 0.347325 | 1(Win) | true |
| Glaze | 5261.39 | 0.27818 | 133.019ms | 6960 | 320 | 3941.12 | 1261.56 | 0.859528 | 0.568382 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1207.03 | 0.301761 | 388.989ms | 4857 | 80 | 10727.8 | 3837.5 | 0.065189 | 2.50386 | 1(Win) | true |
| Jsonifier (two-stage) | 964.543 | 0.0919613 | 482.909ms | 4857 | 4890 | 95370.2 | 4802.27 | 0.0472904 | 3.13668 | 2(Loss) | true |
| Glaze | 941.744 | 0.135701 | 497.07ms | 4857 | 4890 | 217844 | 4918.53 | 0.350115 | 3.21199 | 3(Loss) | true |
| simdjson (ondemand) | 724.643 | 0.0764838 | 642.999ms | 4857 | 2560 | 61188.2 | 6392.11 | 0.174471 | 4.17856 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1914.79 | 0.190528 | 291.64ms | 4857 | 640 | 13595.4 | 2419.06 | 0.0645494 | 1.57515 | 1(Win) | true |
| Glaze | 1785.72 | 0.162795 | 302.741ms | 4857 | 1280 | 22824.4 | 2593.91 | 0.0783699 | 1.68953 | 2(Loss) | true |
| Jsonifier (two-stage) | 1308.8 | 0.0869683 | 410.491ms | 4857 | 4890 | 46325.7 | 3539.12 | 0.0204273 | 2.30881 | 3(Loss) | true |
| simdjson (ondemand) | 1063.91 | 0.147002 | 476.122ms | 4857 | 80 | 3276.9 | 4353.75 | 0.201381 | 2.84095 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9473.61 | 0.42335 | 51.4375ms | 4857 | 4890 | 20951.4 | 488.937 | 0.60528 | 0.307562 | 1(Win) | true |
| Glaze | 3623.38 | 0.185632 | 129.837ms | 4857 | 4890 | 27537.5 | 1278.36 | 0.801203 | 0.825149 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10459.2 | 0.22328 | 46.791ms | 4857 | 4890 | 4781.33 | 442.863 | 0.170458 | 0.278296 | 1(Win) | true |
| Glaze | 4528.91 | 0.913555 | 104.746ms | 4857 | 4890 | 426901 | 1022.76 | 1.57379 | 0.657957 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1303.24 | 0.1176 | 492.633ms | 6701 | 2560 | 85129.7 | 4903.59 | 0.0095584 | 2.32174 | 1(Win) | true |
| Jsonifier | 1202.35 | 0.160447 | 536.595ms | 6701 | 1280 | 93087.6 | 5315.08 | 0.0807778 | 2.51738 | 2(Loss) | true |
| Glaze | 1098.71 | 0.0786332 | 587.194ms | 6701 | 4890 | 102290 | 5816.44 | 0.353407 | 2.75466 | 3(Loss) | true |
| simdjson (ondemand) | 983.165 | 0.190485 | 661.118ms | 6701 | 160 | 24528.3 | 6500 | 0.0192271 | 3.07995 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1949.09 | 0.150493 | 400.21ms | 6701 | 80 | 1947.78 | 3278.75 | 0.719152 | 1.54621 | 1(Win) | true |
| Jsonifier (two-stage) | 1809.08 | 0.212314 | 439.962ms | 6701 | 40 | 2250 | 3532.5 | 0.586304 | 1.67462 | 2(Loss) | true |
| Jsonifier | 1691.75 | 0.876588 | 455.245ms | 6701 | 640 | 701746 | 3777.5 | 0.0248242 | 1.78613 | 3(Loss) | true |
| simdjson (ondemand) | 1399.14 | 0.100025 | 537.172ms | 6701 | 160 | 3339.62 | 4567.5 | 0.327332 | 2.16362 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8152.76 | 0.178849 | 88.8772ms | 7376 | 2560 | 6096.03 | 862.812 | 0.126927 | 0.364717 | 1(Win) | true |
| Glaze | 3465.73 | 0.255475 | 207.796ms | 7376 | 4890 | 131480 | 2029.67 | 0.403251 | 0.868095 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9060.08 | 1.304 | 85.4881ms | 7376 | 2560 | 262405 | 776.406 | 1.34611 | 0.327431 | 1(Win) | true |
| Glaze | 4268.06 | 0.638752 | 191.59ms | 7376 | 160 | 17732.3 | 1648.12 | 0.342466 | 0.700706 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1185.78 | 0.66891 | 141.315ms | 1691 | 30 | 2482.76 | 1360 | 1.21065 | 2.5399 | 1(Win) | true |
| Glaze STATISTICAL TIE | 907.69 | 0.517929 | 146.771ms | 1691 | 30 | 2540.23 | 1776.67 | 1.91205 | 3.29156 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 897.17 | 0.31417 | 167.877ms | 1691 | 40 | 1275.64 | 1797.5 | 1.23626 | 3.32784 | 2(Tie) | true |
| simdjson (ondemand) | 759.496 | 0.433369 | 225.341ms | 1691 | 30 | 2540.23 | 2123.33 | 0.791139 | 3.98253 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1780.72 | 0.201764 | 120.733ms | 1691 | 160 | 534.198 | 905.625 | 0.764951 | 1.67316 | 1(Win) | true |
| Glaze | 1639.35 | 0.616023 | 127.77ms | 1691 | 4890 | 179575 | 983.722 | 0.943082 | 1.81381 | 2(Loss) | true |
| Jsonifier (two-stage) | 1457.23 | 0.418559 | 147.373ms | 1691 | 30 | 643.678 | 1106.67 | 1.19048 | 2.04766 | 3(Loss) | true |
| simdjson (ondemand) | 852.134 | 0.222861 | 220.898ms | 1691 | 40 | 711.538 | 1892.5 | 0.569177 | 3.52519 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9643.89 | 1.70871 | 23.3858ms | 1996 | 4890 | 55624.2 | 197.382 | 0.0393937 | 0.285306 | 1(Win) | true |
| Glaze | 2951.22 | 0.867789 | 50.6175ms | 1996 | 80 | 2506.33 | 645 | 0.389105 | 1.00589 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11871.3 | 0.436307 | 18.8063ms | 1996 | 4890 | 2393.42 | 160.348 | 0.560995 | 0.227463 | 1(Win) | true |
| Glaze | 4968.44 | 1.65954 | 40.3439ms | 1996 | 2560 | 103490 | 383.125 | 0.491803 | 0.569362 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1326.82 | 0.204114 | 160.651ms | 2158 | 640 | 6415.08 | 1551.09 | 0.252474 | 2.26368 | 1(Win) | true |
| Glaze | 1301.65 | 0.204377 | 160.592ms | 2158 | 2560 | 26731.1 | 1581.09 | 0.108588 | 2.30662 | 2(Loss) | true |
| Jsonifier | 1079.33 | 0.178904 | 194.613ms | 2158 | 2560 | 29790.2 | 1906.76 | 0.124811 | 2.7866 | 3(Loss) | true |
| simdjson (ondemand) | 874.536 | 0.130864 | 238.962ms | 2158 | 1280 | 12139.3 | 2353.28 | 0.413361 | 3.44283 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1776.04 | 0.11775 | 140.807ms | 2158 | 4890 | 9103.83 | 1158.77 | 0.34739 | 1.68428 | 1(Win) | true |
| Glaze | 1751.86 | 0.120598 | 143.392ms | 2158 | 4890 | 9815.09 | 1174.76 | 0.278601 | 1.70705 | 2(Loss) | true |
| Jsonifier | 1460.12 | 0.158806 | 174.233ms | 2158 | 4890 | 24499.8 | 1409.49 | 0.0805492 | 2.05263 | 3(Loss) | true |
| simdjson (ondemand) | 1149.86 | 0.0885658 | 199.589ms | 2158 | 4890 | 12287.3 | 1789.82 | 0.273613 | 2.61612 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10164.3 | 0.340275 | 29.4556ms | 2866 | 2560 | 2143.39 | 268.906 | 0.87925 | 0.278426 | 1(Win) | true |
| Glaze | 3896.53 | 0.18683 | 73.374ms | 2866 | 4890 | 8398.38 | 701.452 | 1.41548 | 0.759743 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11779.6 | 0.795508 | 25.4524ms | 2866 | 640 | 2180.53 | 232.031 | 0.735294 | 0.232953 | 1(Win) | true |
| Glaze | 5181.48 | 0.509724 | 58.2281ms | 2866 | 320 | 2313.48 | 527.5 | 0.705882 | 0.556406 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1227.4 | 0.124707 | 344.026ms | 4390 | 4890 | 88480.3 | 3410.98 | 0.593425 | 2.462 | 1(Win) | true |
| Jsonifier (two-stage) | 1071.21 | 0.214049 | 394.69ms | 4390 | 4890 | 342228 | 3908.32 | 0.0840976 | 2.82325 | 2(Loss) | true |
| Glaze | 943.466 | 0.251142 | 448.782ms | 4390 | 40 | 4967.95 | 4437.5 | 0.0187829 | 3.2014 | 3(Loss) | true |
| simdjson (ondemand) | 589.718 | 0.127257 | 716.064ms | 4390 | 640 | 52237.5 | 7099.38 | 0.140659 | 5.14009 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1475.66 | 0.140969 | 333.403ms | 4390 | 4890 | 78219.1 | 2837.12 | 0.0492885 | 2.04532 | 1(Win) | true |
| Jsonifier (two-stage) | 1257.25 | 0.293316 | 386.216ms | 4390 | 30 | 2862.07 | 3330 | 0 | 2.40923 | 2(Loss) | true |
| Glaze | 1180.76 | 0.16873 | 399.548ms | 4390 | 1280 | 45814.2 | 3545.7 | 0.0418465 | 2.55947 | 3(Loss) | true |
| simdjson (ondemand) | 678.85 | 0.1211 | 667.635ms | 4390 | 4890 | 272758 | 6167.24 | 0.158805 | 4.46158 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9045.47 | 0.204788 | 48.7284ms | 4390 | 4890 | 4393.23 | 462.843 | 0.136798 | 0.322482 | 1(Win) | true |
| Glaze | 3396.43 | 0.19372 | 126.768ms | 4390 | 1280 | 7298.65 | 1232.66 | 0.330663 | 0.880765 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9279.46 | 0.309794 | 46.7753ms | 4390 | 1280 | 2500.58 | 451.172 | 0.190114 | 0.313926 | 1(Win) | true |
| Glaze | 3870.63 | 0.233004 | 111.229ms | 4390 | 1280 | 8130.22 | 1081.64 | 0.0795142 | 0.766366 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2113.5 | 0.127526 | 427.219ms | 9378 | 2560 | 74551.4 | 4231.64 | 0.253572 | 1.43195 | 1(Win) | true |
| Jsonifier | 1955.41 | 0.208524 | 464.437ms | 9378 | 80 | 7276.9 | 4573.75 | 0.245365 | 1.55036 | 2(Loss) | true |
| Glaze | 1451.53 | 0.202996 | 620.14ms | 9378 | 2560 | 400485 | 6161.48 | 0.200739 | 2.08674 | 3(Loss) | true |
| simdjson (ondemand) | 1193.15 | 0.105256 | 754.728ms | 9378 | 2560 | 159353 | 7495.74 | 0.0850163 | 2.53956 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2416.36 | 0.176553 | 418.447ms | 9378 | 80 | 3416.14 | 3701.25 | 0.101215 | 1.25023 | 1(Win) | true |
| Jsonifier | 2216.67 | 0.207301 | 455.275ms | 9378 | 4890 | 342082 | 4034.68 | 0.0386308 | 1.36481 | 2(Loss) | true |
| Glaze | 1718.13 | 0.178891 | 566.86ms | 9378 | 4890 | 424029 | 5205.4 | 0.261234 | 1.76191 | 3(Loss) | true |
| simdjson (ondemand) | 1374.81 | 0.304626 | 703.095ms | 9378 | 640 | 251333 | 6505.31 | 0.062488 | 2.20398 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12782.3 | 0.155144 | 88.8599ms | 11521 | 4890 | 8696.48 | 859.571 | 0.348673 | 0.232539 | 1(Win) | true |
| Glaze | 4627.06 | 0.188947 | 238.423ms | 11521 | 2560 | 51533.6 | 2374.57 | 0.0510221 | 0.650463 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15346.7 | 0.286247 | 74.0663ms | 11521 | 320 | 1343.95 | 715.938 | 0.21777 | 0.193037 | 1(Win) | true |
| Glaze | 6009.82 | 0.125315 | 184.147ms | 11521 | 4890 | 25666.9 | 1828.22 | 0.561771 | 0.49869 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2312.62 | 0.146609 | 196.525ms | 4669 | 1280 | 10199.2 | 1925.39 | 0.198429 | 1.30007 | 1(Win) | true |
| Jsonifier (two-stage) | 1479.46 | 0.25315 | 299.99ms | 4669 | 640 | 37151.7 | 3009.69 | 0.0311397 | 2.04094 | 2(Loss) | true |
| Glaze | 1376.42 | 0.283269 | 329.916ms | 4669 | 40 | 3358.97 | 3235 | 0.0514933 | 2.20019 | 3(Loss) | true |
| simdjson (ondemand) | 881.424 | 0.0995296 | 510.231ms | 4669 | 2560 | 64717.6 | 5051.72 | 0.24683 | 3.43586 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2677.69 | 0.177901 | 184.293ms | 4669 | 1280 | 11202 | 1662.89 | 0.164165 | 1.12375 | 1(Win) | true |
| Jsonifier (two-stage) | 1660.44 | 0.115254 | 287.272ms | 4669 | 1280 | 12227.2 | 2681.64 | 0.0902317 | 1.81741 | 2(Loss) | true |
| Glaze | 1620.68 | 0.140147 | 290.476ms | 4669 | 1280 | 18976.9 | 2747.42 | 0.331595 | 1.86097 | 3(Loss) | true |
| simdjson (ondemand) | 967.674 | 0.098333 | 475.441ms | 4669 | 4890 | 100114 | 4601.45 | 0.181291 | 3.12774 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10739.7 | 0.185608 | 43.7673ms | 4669 | 4890 | 2895.78 | 414.601 | 0.498815 | 0.270947 | 1(Win) | true |
| Glaze | 3338.78 | 0.274499 | 140.019ms | 4669 | 2560 | 34308 | 1333.63 | 0.859675 | 0.897407 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12451 | 0.27316 | 38.1481ms | 4669 | 2560 | 2442.93 | 357.617 | 0.251862 | 0.231211 | 1(Win) | true |
| Glaze | 5079.13 | 0.895897 | 107.712ms | 4669 | 30 | 1850.57 | 876.667 | 0 | 0.583951 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2336.54 | 0.121711 | 329.791ms | 7932 | 160 | 2484.28 | 3237.5 | 0.115964 | 1.29322 | 1(Win) | true |
| Jsonifier | 2129.36 | 0.158154 | 362.379ms | 7932 | 80 | 2525.32 | 3552.5 | 0.210674 | 1.42391 | 2(Loss) | true |
| Glaze | 1707.57 | 0.130049 | 444.464ms | 7932 | 2560 | 84969.1 | 4430 | 0.130332 | 1.77179 | 3(Loss) | true |
| simdjson (ondemand) | 1402.28 | 0.0679541 | 543.432ms | 7932 | 4890 | 65710.7 | 5394.46 | 0.103023 | 2.15941 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2553.38 | 0.0899401 | 314.285ms | 7932 | 4890 | 34717.5 | 2962.56 | 0.104854 | 1.18126 | 1(Win) | true |
| Jsonifier | 2267.17 | 0.16453 | 352.554ms | 7932 | 640 | 19287.1 | 3336.56 | 0.270876 | 1.33412 | 2(Loss) | true |
| Glaze | 1971.86 | 0.148415 | 400.751ms | 7932 | 80 | 2593.35 | 3836.25 | 0.227568 | 1.53722 | 3(Loss) | true |
| simdjson (ondemand) | 1590.3 | 0.193452 | 502.378ms | 7932 | 30 | 2540.23 | 4756.67 | 0.626741 | 1.91139 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10346.2 | 0.180678 | 87.7873ms | 9249 | 2560 | 6074.05 | 852.539 | 0.105495 | 0.287793 | 1(Win) | true |
| Glaze | 3309.77 | 3.77285 | 254.443ms | 9249 | 40 | 404385 | 2665 | 1.20253 | 0.909698 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11847.1 | 0.487195 | 78.5059ms | 9249 | 640 | 8420.75 | 744.531 | 0.0629195 | 0.250106 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 4201.66 | 0.675105 | 229.178ms | 9249 | 1280 | 257099 | 2099.3 | 3.50833 | 0.713468 | -(Loss) | false |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 462.584 | 0.118967 | 958.64ms | 4604 | 640 | 81605.8 | 9491.72 | 0.0345577 | 6.5568 | 1(Win) | true |
| Jsonifier | 353.033 | 0.0955669 | 1246.2ms | 4604 | 4890 | 690819 | 12437.1 | 0.258749 | 8.59367 | 2(Loss) | true |
| Glaze | 283.346 | 0.121878 | 1549.1ms | 4604 | 640 | 228278 | 15495.9 | 0.111039 | 10.7104 | 3(Loss) | true |
| simdjson (ondemand) | 164.941 | 0.10684 | 2669.11ms | 4604 | 640 | 517681 | 26619.8 | 0.00176087 | 18.4115 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 560.917 | 0.0708256 | 908.993ms | 4604 | 4890 | 150302 | 7827.75 | 0.00328693 | 5.40519 | 1(Win) | true |
| Jsonifier | 409.64 | 0.139526 | 1198.79ms | 4604 | 2560 | 572550 | 10718.5 | 0.166999 | 7.40294 | 2(Loss) | true |
| Glaze | 329.63 | 0.117413 | 1449.66ms | 4604 | 640 | 156541 | 13320.2 | 0.104291 | 9.20598 | 3(Loss) | true |
| simdjson (ondemand) | 175.438 | 0.0760081 | 2651.86ms | 4604 | 1280 | 463182 | 25027.1 | 0.0246668 | 17.3097 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1104.26 | 0.0952508 | 400.322ms | 4604 | 4890 | 70141.1 | 3976.16 | 0.273757 | 2.73793 | 1(Win) | true |
| Glaze | 903.44 | 0.118316 | 488.43ms | 4604 | 2560 | 84644 | 4860 | 0.0917121 | 3.35106 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1124.52 | 0.156122 | 395.199ms | 4604 | 1280 | 47563.5 | 3904.53 | 0.0400336 | 2.67568 | 1(Win) | true |
| Glaze | 985.813 | 0.107959 | 448.052ms | 4604 | 4890 | 113060 | 4453.91 | 0.018414 | 3.06977 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1655.63 | 0.131827 | 1057.02ms | 18245 | 2560 | 491371 | 10509.5 | 0.131378 | 1.8317 | 1(Win) | true |
| Jsonifier | 1396.2 | 0.0560936 | 1254.08ms | 18245 | 4890 | 238963 | 12462.3 | 0.0407992 | 2.17211 | 2(Loss) | true |
| Glaze | 976.705 | 0.0432168 | 1790.16ms | 18245 | 4890 | 289851 | 17814.8 | 0.0619829 | 3.10791 | 3(Loss) | true |
| simdjson (ondemand) | 629.32 | 0.0875398 | 2769.8ms | 18245 | 2560 | 1.49967e+06 | 27648.6 | 0.0320608 | 4.82533 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1988.16 | 0.0696102 | 1000.2ms | 18245 | 2560 | 95010.7 | 8751.72 | 0.101869 | 1.52517 | 1(Win) | true |
| Jsonifier | 1651.03 | 0.0685531 | 1198.08ms | 18245 | 80 | 4175.63 | 10538.8 | 0.082958 | 1.83681 | 2(Loss) | true |
| Glaze | 1101.47 | 0.0486071 | 1701.67ms | 18245 | 2560 | 150932 | 15796.9 | 0.0529459 | 2.75514 | 3(Loss) | true |
| simdjson (ondemand) | 667.236 | 0.0481635 | 2745.43ms | 18245 | 4890 | 771390 | 26077.4 | 0.206849 | 4.55094 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4186.54 | 0.0753947 | 563.772ms | 24579 | 2560 | 45618.4 | 5598.98 | 0.0111615 | 0.722931 | 1(Win) | true |
| Glaze | 3016.9 | 0.290259 | 780.709ms | 24579 | 1280 | 651012 | 7769.69 | 0.0422136 | 1.00407 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4355.77 | 0.0753129 | 543.155ms | 24579 | 2560 | 42051.1 | 5381.45 | 0.123971 | 0.693938 | 1(Win) | true |
| Glaze | 3479.21 | 0.148022 | 671.008ms | 24579 | 2560 | 254601 | 6737.27 | 0.0266778 | 0.871315 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 492.941 | 0.0700044 | 895.866ms | 4604 | 2560 | 99534.1 | 8907.19 | 0.0473859 | 6.15146 | 1(Win) | true |
| Jsonifier | 475.025 | 0.321048 | 933.447ms | 4604 | 640 | 563583 | 9243.12 | 0.118191 | 6.3846 | 2(Loss) | true |
| simdjson (ondemand) | 317.137 | 0.127975 | 1385.23ms | 4604 | 640 | 200912 | 13844.8 | 0.00112857 | 9.56901 | 3(Loss) | true |
| Glaze | 284.474 | 0.0658211 | 1550.76ms | 4604 | 4890 | 504690 | 15434.5 | 0.0871814 | 10.661 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 608.346 | 0.0502408 | 845.325ms | 4604 | 4890 | 64297.1 | 7217.46 | 0.0459374 | 4.9822 | 1(Win) | true |
| Jsonifier | 582.658 | 0.152963 | 879.226ms | 4604 | 4890 | 649720 | 7535.66 | 0.105347 | 5.20186 | 2(Loss) | true |
| simdjson (ondemand) | 368.596 | 0.0432257 | 1299.03ms | 4604 | 4890 | 129647 | 11912 | 0.274601 | 8.22987 | 3(Loss) | true |
| Glaze | 330.792 | 0.0873828 | 1448.68ms | 4604 | 4890 | 657841 | 13273.3 | 0.0193215 | 9.17372 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1080.76 | 0.0731997 | 409.398ms | 4604 | 4890 | 43245.3 | 4062.62 | 0.188092 | 2.79787 | 1(Win) | true |
| Glaze | 922.281 | 0.0715026 | 480.345ms | 4604 | 4890 | 56662.6 | 4760.72 | 0.152119 | 3.28156 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1118.31 | 0.201924 | 394.486ms | 4604 | 2560 | 160903 | 3926.21 | 0.018907 | 2.69967 | 1(Win) | true |
| Glaze | 981.361 | 0.0669866 | 448.962ms | 4604 | 4890 | 43923.6 | 4474.11 | 0.0722152 | 3.08412 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1804.96 | 0.117699 | 970.413ms | 18245 | 30 | 3862.07 | 9640 | 0.0692042 | 1.6781 | 1(Win) | true |
| Jsonifier | 1566.42 | 0.147397 | 1113.66ms | 18245 | 640 | 171564 | 11108 | 0.0295309 | 1.93597 | 2(Loss) | true |
| simdjson (ondemand) | 1178.81 | 0.0619163 | 1471.75ms | 18245 | 4890 | 408430 | 14760.4 | 0.124536 | 2.57407 | 3(Loss) | true |
| Glaze | 974.386 | 0.144168 | 1796.54ms | 18245 | 640 | 424174 | 17857.2 | 0.0174969 | 3.11516 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2170.55 | 0.110909 | 925.367ms | 18245 | 2560 | 202357 | 8016.29 | 0.0608741 | 1.39651 | 1(Win) | true |
| Jsonifier | 1899.9 | 0.0599203 | 1040.49ms | 18245 | 4890 | 147259 | 9158.26 | 0.287291 | 1.59568 | 2(Loss) | true |
| simdjson (ondemand) | 1366.3 | 0.091323 | 1389.87ms | 18245 | 40 | 5410.26 | 12735 | 0.0915272 | 2.22004 | 3(Loss) | true |
| Glaze | 1094.18 | 0.0627684 | 1702.98ms | 18245 | 2560 | 255056 | 15902.2 | 0.0319437 | 2.774 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4320.03 | 0.0809744 | 546.412ms | 24579 | 2560 | 49418.7 | 5425.98 | 0.134443 | 0.700568 | 1(Win) | true |
| Glaze | 3007.71 | 0.0861828 | 782.561ms | 24579 | 4890 | 220601 | 7793.44 | 0.165655 | 1.00734 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4569.51 | 0.0616337 | 517.183ms | 24579 | 4890 | 48880.5 | 5129.73 | 0.473531 | 0.662247 | 1(Win) | true |
| Glaze | 3479.2 | 0.0960298 | 676.508ms | 24579 | 4890 | 204687 | 6737.28 | 0.0274738 | 0.87059 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 971.444 | 0.0922792 | 504.616ms | 5094 | 2560 | 54516.7 | 5000.82 | 0.254511 | 3.1173 | 1(Win) | true |
| Jsonifier (two-stage) | 852.225 | 0.0818808 | 576.086ms | 5094 | 2560 | 55771.6 | 5700.39 | 0.269265 | 3.55278 | 2(Loss) | true |
| Glaze | 704.825 | 0.0604994 | 692.547ms | 5094 | 4890 | 85028.9 | 6892.52 | 0.0903738 | 4.29775 | 3(Loss) | true |
| simdjson (ondemand) | 553.778 | 0.064212 | 881.967ms | 5094 | 4890 | 155163 | 8772.49 | 0.0561325 | 5.47373 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1208.85 | 0.107055 | 497.889ms | 5094 | 2560 | 47383.3 | 4018.71 | 0.12165 | 2.50286 | 1(Win) | true |
| Jsonifier (two-stage) | 1034.14 | 0.101118 | 571.316ms | 5094 | 2560 | 57763 | 4697.62 | 0.340598 | 2.92691 | 2(Loss) | true |
| Glaze | 976.486 | 0.108409 | 590.816ms | 5094 | 160 | 4654.09 | 4975 | 0.100402 | 3.09954 | 3(Loss) | true |
| simdjson (ondemand) | 699.774 | 0.0803755 | 798.231ms | 5094 | 2560 | 79705.7 | 6942.27 | 0.142716 | 4.32839 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9187.74 | 0.963047 | 56.7394ms | 5094 | 80 | 2074.37 | 528.75 | 0.235849 | 0.317334 | 1(Win) | true |
| Glaze | 3397.21 | 0.455379 | 150.04ms | 5094 | 80 | 3392.41 | 1430 | 0.175131 | 0.885893 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11517.4 | 0.433039 | 44.3913ms | 5094 | 1280 | 4270.42 | 421.797 | 0.0185254 | 0.252314 | 1(Win) | true |
| Glaze | 4121.88 | 0.137673 | 124.435ms | 5094 | 640 | 1685.03 | 1178.59 | 0.435586 | 0.721271 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1312.57 | 0.0854203 | 589.366ms | 8051 | 4890 | 122091 | 5849.61 | 0.0508125 | 2.30789 | 1(Win) | true |
| Jsonifier | 1176.94 | 0.138914 | 656.114ms | 8051 | 2560 | 210245 | 6523.75 | 0.0623113 | 2.57478 | 2(Loss) | true |
| Glaze | 974.969 | 0.112347 | 793.348ms | 8051 | 1280 | 100195 | 7875.16 | 0.0793006 | 3.10848 | 3(Loss) | true |
| simdjson (ondemand) | 855.552 | 0.0674782 | 899.736ms | 8051 | 4890 | 179326 | 8974.36 | 0.0720928 | 3.54383 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1587.7 | 0.190646 | 584.917ms | 8051 | 320 | 27199.7 | 4835.94 | 0.187049 | 1.9054 | 1(Win) | true |
| Jsonifier | 1400.62 | 0.242604 | 646.468ms | 8051 | 320 | 56598.4 | 5481.88 | 0.0228076 | 2.16218 | 2(Loss) | true |
| Glaze | 1299.43 | 0.119645 | 687.226ms | 8051 | 4890 | 244396 | 5908.77 | 0.0491685 | 2.32982 | 3(Loss) | true |
| simdjson (ondemand) | 1076.86 | 0.175405 | 821.869ms | 8051 | 40 | 6256.41 | 7130 | 0.0935891 | 2.81339 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10981.3 | 0.51004 | 82.0979ms | 9255 | 320 | 5377.74 | 803.75 | 0.077821 | 0.270247 | 1(Win) | true |
| Glaze | 3814.57 | 0.221574 | 227.02ms | 9255 | 2560 | 67288.2 | 2313.83 | 0.25727 | 0.789538 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13350.2 | 0.221137 | 67.5466ms | 9255 | 2560 | 5471.95 | 661.133 | 0.0649504 | 0.221407 | 1(Win) | true |
| Glaze | 5056.67 | 0.241834 | 184.498ms | 9255 | 640 | 11403.5 | 1745.47 | 0.294538 | 0.59156 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5051.73 | 0.255255 | 57.5708ms | 2889 | 1280 | 2480.69 | 545.391 | 0.186567 | 0.5807 | 1(Win) | true |
| Jsonifier | 4967.06 | 0.502469 | 59.2266ms | 2889 | 320 | 2485.8 | 554.688 | 0.1693 | 0.591835 | 2(Loss) | true |
| simdjson (ondemand) | 3973.2 | 0.116306 | 71.8518ms | 2889 | 1280 | 832.584 | 693.438 | 0.202384 | 0.745095 | 3(Loss) | true |
| Glaze | 2915.52 | 0.842992 | 94.6254ms | 2889 | 40 | 2538.46 | 945 | 0.531915 | 1.02314 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5510.33 | 0 | 54.6901ms | 2889 | 30 | 0 | 500 | 0 | 0.531233 | 1(Win) | true |
| Jsonifier (two-stage) | 5374.27 | 0.39073 | 54.6922ms | 2889 | 4890 | 19620.9 | 512.658 | 0.130139 | 0.544027 | 2(Loss) | true |
| simdjson (ondemand) | 4172.27 | 0.227043 | 69.3063ms | 2889 | 2560 | 5754.47 | 660.352 | 0.183715 | 0.707069 | 3(Loss) | true |
| Glaze | 3133.65 | 0.265596 | 92.7775ms | 2889 | 1280 | 6979.84 | 879.219 | 0.464203 | 0.939967 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5606.61 | 0.219635 | 67.5917ms | 3808 | 1280 | 2590.64 | 647.734 | 1.03843 | 0.526555 | 1(Win) | true |
| Jsonifier (two-stage) | 5542.94 | 0.169127 | 67.3653ms | 3808 | 4890 | 6004.11 | 655.174 | 0.283706 | 0.533557 | 2(Loss) | true |
| simdjson (ondemand) | 4806.57 | 0.322843 | 77.8598ms | 3808 | 1280 | 7615.81 | 755.547 | 0.176093 | 0.617601 | 3(Loss) | true |
| Glaze | 3327.92 | 0.235314 | 112.436ms | 3808 | 160 | 1055.03 | 1091.25 | 0.228571 | 0.901142 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 6086.47 | 0.978685 | 67.8269ms | 3808 | 30 | 1022.99 | 596.667 | 0 | 0.485557 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 6046.35 | 0.454929 | 67.8213ms | 3808 | 160 | 1194.58 | 600.625 | 0.104167 | 0.483855 | 1(Tie) | true |
| simdjson (ondemand) | 4991.61 | 1.27035 | 79.8586ms | 3808 | 2560 | 218675 | 727.539 | 0.480147 | 0.592922 | 3(Loss) | true |
| Glaze | 3373 | 0.729477 | 115.692ms | 3808 | 30 | 1850.57 | 1076.67 | 0.615385 | 0.880427 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1793.47 | 0.120347 | 155.836ms | 2889 | 4890 | 16714.3 | 1536.22 | 0.104743 | 1.67463 | 1(Win) | true |
| Glaze | 1690.29 | 0.316307 | 168.844ms | 2889 | 80 | 2126.58 | 1630 | 0 | 1.78242 | 2(Loss) | true |
| Jsonifier (two-stage) | 1431.49 | 0.202364 | 197.126ms | 2889 | 2560 | 38835.4 | 1924.69 | 0.13413 | 2.10288 | 3(Loss) | true |
| simdjson (ondemand) | 1363.39 | 0.226888 | 204.062ms | 2889 | 4890 | 102798 | 2020.82 | 0.168003 | 2.20795 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2242.73 | 0.396841 | 142.78ms | 2889 | 4890 | 116220 | 1228.49 | 0.512192 | 1.33464 | 1(Win) | true |
| Glaze | 1964.8 | 0.325101 | 155.842ms | 2889 | 1280 | 26601.6 | 1402.27 | 0.184193 | 1.52497 | 2(Loss) | true |
| Jsonifier (two-stage) | 1666.25 | 0.300668 | 183.73ms | 2889 | 1280 | 31637.4 | 1653.52 | 0.0519456 | 1.80443 | 3(Loss) | true |
| simdjson (ondemand) | 1514.28 | 0.133823 | 197.893ms | 2889 | 1280 | 7588.44 | 1819.45 | 0.219468 | 1.98556 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10514.4 | 0.559655 | 29.123ms | 2963 | 2560 | 5791.32 | 268.75 | 0.555393 | 0.269454 | 1(Win) | true |
| Glaze | 4568.19 | 0.218254 | 61.5691ms | 2963 | 4890 | 8912.66 | 618.569 | 0.338067 | 0.644006 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12697.9 | 0.329276 | 24.5673ms | 2963 | 4890 | 2625.6 | 222.536 | 0.759041 | 0.218711 | 1(Win) | true |
| Glaze | 5964.62 | 0.568132 | 53.7902ms | 2963 | 320 | 2318.18 | 473.75 | 1.04439 | 0.494258 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1800.21 | 0.440061 | 215.941ms | 3808 | 4890 | 385376 | 2017.32 | 0.467714 | 1.6718 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1798.65 | 0.303522 | 221.717ms | 3808 | 320 | 12017.9 | 2019.06 | 1.44905 | 1.67208 | 1(Tie) | true |
| simdjson (ondemand) | 1694.37 | 0.429325 | 221.737ms | 3808 | 30 | 2540.23 | 2143.33 | 0.312012 | 1.77485 | 3(Loss) | true |
| Jsonifier | 1552.79 | 0.234364 | 234.69ms | 3808 | 80 | 2403.48 | 2338.75 | 0.160085 | 1.93919 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 2129.97 | 0.293255 | 200.724ms | 3808 | 40 | 1000 | 1705 | 0.294118 | 1.40526 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2126.85 | 0.385951 | 197.394ms | 3808 | 40 | 1737.18 | 1707.5 | 0.0488281 | 1.40894 | 1(Tie) | true |
| simdjson (ondemand) | 1931.7 | 0.340698 | 212.429ms | 3808 | 40 | 1641.03 | 1880 | 0.534759 | 1.5585 | 3(Loss) | true |
| Jsonifier | 1815.09 | 1.74374 | 228.737ms | 3808 | 640 | 779013 | 2000.78 | 0.16373 | 1.65636 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8045.71 | 0.626233 | 56.1286ms | 4300 | 320 | 3260.09 | 509.688 | 0.431034 | 0.366849 | 1(Win) | true |
| Glaze | 3317.13 | 1.03008 | 142.095ms | 4300 | 80 | 12973.1 | 1236.25 | 1.33197 | 0.897497 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9373.26 | 1.77192 | 50.674ms | 4300 | 40 | 2403.85 | 437.5 | 0.19084 | 0.310419 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3732.51 | 6.27047 | 111.63ms | 4300 | 4890 | 2.32083e+07 | 1098.67 | 2.76955 | 0.791913 | -(Loss) | false |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2852.03 | 0.0434092 | 7979.27ms | 466906 | 1280 | 5.8793e+06 | 156126 | 0.0133624 | 1.06554 | 1(Win) | true |
| Glaze | 1824.51 | 0.135773 | 6261.15ms | 466906 | 80 | 8.78379e+06 | 244052 | 0.134013 | 1.6657 | 2(Loss) | true |
| simdjson (ondemand) | 1439.49 | 0.113924 | 7869.62ms | 466906 | 1280 | 1.5896e+08 | 309330 | 0.218919 | 2.11103 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2863.74 | 0.0411856 | 7951.14ms | 466906 | 2560 | 1.04983e+07 | 155487 | 0.0472025 | 1.06109 | 1(Win) | true |
| Glaze | 1812.56 | 0.0691012 | 6258.87ms | 466906 | 640 | 1.84428e+07 | 245662 | 0.00273503 | 1.67669 | 2(Loss) | true |
| simdjson (ondemand) | 1441.77 | 0.11612 | 7904.49ms | 466906 | 320 | 4.11561e+07 | 308840 | 0.0797713 | 2.1077 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2699.67 | 0.609372 | 6270.95ms | 699405 | 1280 | 2.90142e+09 | 247069 | 0.54586 | 1.12562 | 1(Win) | true |
| Jsonifier | 2077.27 | 0.763251 | 8256.46ms | 699405 | 640 | 3.84404e+09 | 321097 | 0.444724 | 1.46237 | 2(Loss) | true |
| simdjson (ondemand) | 1324.59 | 0.436491 | 7117.86ms | 767297 | 640 | 3.7213e+09 | 552436 | 1.09316 | 2.29326 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3565.87 | 0.290569 | 9562.07ms | 699405 | 40 | 1.18164e+07 | 187052 | 0.271156 | 0.852209 | 1(Win) | true |
| Glaze | 2888.91 | 0.07224 | 5889.77ms | 699405 | 640 | 1.78043e+07 | 230884 | 0.0931687 | 1.05196 | 2(Loss) | true |
| simdjson (ondemand) | 1460.89 | 0.324822 | 6362.42ms | 767297 | 40 | 1.05888e+08 | 500895 | 0.191691 | 2.07953 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2932.9 | 0.0885265 | 5240.69ms | 631514 | 1280 | 4.22987e+07 | 205346 | 0.0642242 | 1.03619 | 1(Win) | true |
| Glaze | 2521.62 | 0.0409848 | 6246.3ms | 631514 | 1280 | 1.22648e+07 | 238838 | 0.131112 | 1.20519 | 2(Loss) | true |
