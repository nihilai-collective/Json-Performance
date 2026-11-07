# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-42-generic using the GCC 16.2.1 compiler).  

Latest Results: (Nov 07, 2026)
#### Using the following commits:
----
| Jsonifier: [3e5ab01](https://github.com/nihilai-collective/Jsonifier/commit/3e5ab01)  
| Glaze: [0a363d40](https://github.com/stephenberry/glaze/commit/0a363d40)  
| simdjson: [dfe02cfe3](https://github.com/simdjson/simdjson/commit/dfe02cfe3)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |
| **simdjson (reflection)** | `haswell` |
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
* **simdjson (reflection):** C++26 static reflection API (P2996). Minified serialization only.
* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.
* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.

---
*Environment generated via BenchmarkSuite commit: [ed43ce8](https://github.com/nihilai-collective/benchmarksuite/commit/ed43ce8)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2364.16 | 0.0487088 | 763.021ms | 905 | 2560 | 80.9467 | 365.066 | 0.00749064 | 2.3834 | 11.7006 | 1.86961 | 0.00110584 | 0.000132079 | 6.47445e-06 | 1(Win) | true |
| Glaze | 1784.76 | 0.190675 | 785.451ms | 905 | 2560 | 2176.53 | 483.58 | 0.682023 | 3.10514 | 14.032 | 1.94917 | 0.00111102 | 0.000160566 | 0.000113519 | 2(Loss) | true |
| Jsonifier (two-stage) | 609.452 | 0.173538 | 867.96ms | 905 | 80 | 483.167 | 1416.15 | 0.0564593 | 8.70214 | 42.6718 | 4.65193 | 0.014337 | 0.000179558 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 224.153 | 0.07124 | 1120.52ms | 905 | 2560 | 19261.7 | 3850.38 | 0.038567 | 22.5278 | 105.526 | 9.82431 | 0.0795675 | 0.000154092 | 9.92749e-06 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2625.41 | 0.107429 | 756.971ms | 905 | 4890 | 609.891 | 328.739 | 0.106355 | 2.192 | 11.0331 | 1.73039 | 0.0011113 | 9.9199e-05 | 6.10107e-06 | 1(Win) | true |
| Glaze | 1820.96 | 0.136653 | 771.297ms | 905 | 30 | 12.5851 | 473.967 | 0.126752 | 3.01834 | 13.6652 | 2.06519 | 0.00220994 | 7.36648e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 620.7 | 0.128144 | 868.278ms | 905 | 160 | 507.987 | 1390.49 | 0.0881763 | 8.56749 | 41.9956 | 4.51271 | 0.013674 | 0.000220994 | 4.14365e-05 | 3(Loss) | true |
| simdjson (ondemand) | 220.936 | 0.050103 | 1123.73ms | 905 | 4890 | 18732.7 | 3906.45 | 0.423603 | 22.9367 | 104.842 | 9.68509 | 0.0909675 | 0.0001871 | 4.38373e-05 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1702.67 | 0.154019 | 775.988ms | 905 | 2560 | 1560.37 | 506.895 | 0.683091 | 3.20753 | 11.0895 | 1.10276 | 0.00446046 | 0.000151934 | 5.78384e-05 | 1(Win) | true |
| simdjson (reflection) | 252.951 | 0.0450308 | 1068.66ms | 905 | 640 | 1510.86 | 3412.03 | 0.0712961 | 20.2404 | 95.0641 | 21.1481 | 0.0590435 | 7.42403e-05 | 1.20856e-05 | 2(Loss) | true |
| Glaze | 193.562 | 0.0783825 | 1180.05ms | 905 | 640 | 7817.62 | 4458.9 | 0.289694 | 26.0165 | 111.264 | 23.5867 | 0.0904109 | 0.000245166 | 3.28039e-05 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 3245.95 | 0.0679471 | 754.852ms | 905 | 1280 | 41.7798 | 265.893 | 0.160462 | 1.79878 | 8.44972 | 1.05193 | 0.00110497 | 7.42403e-05 | 4.3163e-06 | 1(Win) | true |
| Jsonifier | 3170.21 | 0.0438321 | 755.288ms | 905 | 2560 | 36.4541 | 272.245 | 0.0476136 | 1.83735 | 7.77459 | 0.271824 | 0.0022121 | 5.00691e-05 | 6.90608e-06 | 2(Loss) | true |
| Glaze | 689.127 | 0.0145283 | 862.942ms | 905 | 640 | 21.189 | 1252.42 | 0.0508756 | 7.59386 | 22.0398 | 3.36685 | 0.0033529 | 3.28039e-05 | 0 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1212.67 | 0.0726775 | 872.086ms | 1811 | 2560 | 2742.79 | 1424.22 | 0.301427 | 4.33682 | 18.3898 | 3.6582 | 0.000756661 | 0.000221088 | 9.62003e-05 | 1(Win) | true |
| Glaze | 1064.94 | 0.0371851 | 892.257ms | 1811 | 4890 | 1778.41 | 1621.79 | 0.0902924 | 4.89452 | 25.5257 | 3.72336 | 0.000562118 | 0.000245941 | 3.5457e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 714.624 | 0.139321 | 983.134ms | 1811 | 80 | 906.997 | 2416.8 | 0.336281 | 7.19519 | 34.0083 | 5.08669 | 0.000911099 | 8.97294e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 295.438 | 0.0447081 | 1322.06ms | 1811 | 1280 | 8743.53 | 5845.9 | 0.0463785 | 16.9027 | 87.6963 | 11.5108 | 0.00155387 | 0.000104397 | 1.63929e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1313.99 | 0.117068 | 861.896ms | 1811 | 160 | 378.831 | 1314.39 | 0.121107 | 4.0344 | 17.4622 | 3.44671 | 0.00202581 | 0.000196715 | 4.83158e-05 | 1(Win) | true |
| Glaze | 1150.35 | 0.023049 | 877.497ms | 1811 | 4890 | 585.59 | 1501.38 | 0.213656 | 4.51651 | 24.7974 | 3.4804 | 0.000960276 | 0.000108855 | 7.56567e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 752.125 | 0.169244 | 970.34ms | 1811 | 30 | 453.114 | 2296.3 | 0.0319456 | 6.8469 | 33.0618 | 4.87521 | 0.00110436 | 0.000220872 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 306.059 | 0.0626809 | 1304.53ms | 1811 | 640 | 8007.17 | 5643.05 | 0.0458595 | 16.5056 | 86.7305 | 11.2993 | 0.00108538 | 0.000148399 | 5.00414e-05 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 348.148 | 0.103437 | 1235.39ms | 1811 | 320 | 8425.81 | 4960.84 | 0.0151207 | 14.6289 | 64.0215 | 11.233 | 0.0171608 | 6.21204e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 337.207 | 0.188746 | 1295.61ms | 1997 | 80 | 9090.96 | 5647.82 | 0.0729837 | 15.0833 | 64.671 | 11.8353 | 0.00614046 | 6.88533e-05 | 0 | 2(Loss) | true |
| Glaze | 301.691 | 0.0491046 | 1308.5ms | 1798 | 1280 | 9970.33 | 5683.66 | 0.0411023 | 16.8118 | 70.6413 | 12.4889 | 0.0229513 | 0.000179018 | 4.34511e-06 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 876.711 | 0.0526377 | 938.152ms | 1811 | 320 | 344.087 | 1969.98 | 0.0760849 | 5.87296 | 19.82 | 1.03424 | 0.00059532 | 2.58835e-05 | 1.72557e-06 | 1(Win) | true |
| simdjson (reflection) | 640.486 | 0.0218958 | 1046.03ms | 1997 | 4890 | 2072.84 | 2973.5 | 0.0104292 | 8.00514 | 25.2954 | 2.57787 | 0.000909442 | 7.43446e-05 | 8.39705e-06 | 2(Loss) | true |
| Glaze | 618.338 | 0.0489069 | 1023.8ms | 1798 | 4890 | 8994.49 | 2773.09 | 0.13392 | 8.28472 | 26.614 | 2.36263 | 0.000970517 | 0.000112372 | 2.71831e-05 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3307 | 0.0638434 | 842.163ms | 3862 | 160 | 80.8925 | 1113.72 | 0.0863471 | 1.59261 | 7.17763 | 0.899016 | 0.000258933 | 5.17866e-05 | 0 | 1(Win) | true |
| Glaze | 1731.68 | 0.0880642 | 942.708ms | 3862 | 80 | 280.658 | 2126.89 | 0.0135156 | 2.97785 | 14.674 | 1.82522 | 0.000258933 | 3.23666e-05 | 1.29467e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1606.21 | 0.0274731 | 962.486ms | 3862 | 4890 | 1940.65 | 2293.04 | 0.069999 | 3.20396 | 14.5137 | 1.63128 | 0.000261528 | 5.71877e-05 | 9.69014e-06 | 3(Loss) | true |
| simdjson (ondemand) | 724.814 | 0.0435628 | 1242.62ms | 3862 | 640 | 3136.05 | 5081.43 | 0.0825857 | 7.03158 | 32.3661 | 3.55956 | 0.00090748 | 3.84354e-05 | 0 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3649.71 | 0.045536 | 830.967ms | 3862 | 4890 | 1032.58 | 1009.15 | 0.00693785 | 1.43796 | 6.68514 | 0.786121 | 0.000260416 | 4.88743e-05 | 2.96529e-06 | 1(Win) | true |
| Glaze | 1834.35 | 0.0727682 | 926.429ms | 3862 | 1280 | 2732.45 | 2007.84 | 0.0527508 | 2.81039 | 14.1854 | 1.71129 | 0.000397301 | 4.71339e-05 | 7.0802e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1723.95 | 0.0429832 | 943.073ms | 3862 | 160 | 134.925 | 2136.43 | 0.0269214 | 2.99135 | 14.0127 | 1.51838 | 0.000260552 | 6.47333e-05 | 1.61833e-06 | 3(Loss) | true |
| simdjson (ondemand) | 744.139 | 0.0407886 | 1234.7ms | 3862 | 80 | 326.049 | 4949.46 | 0.0128785 | 6.8528 | 31.8708 | 3.45236 | 0.00105839 | 3.56033e-05 | 9.70999e-06 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 921.843 | 0.070286 | 1142.45ms | 3862 | 1280 | 10093.9 | 3995.36 | 0.0988059 | 5.49655 | 26.0891 | 5.35836 | 0.00719814 | 5.84623e-05 | 1.21375e-06 | 1(Win) | true |
| simdjson (reflection) | 909.263 | 0.0282584 | 1138.7ms | 3862 | 4890 | 6406.94 | 4050.63 | 0.171646 | 5.57554 | 27.2418 | 5.32677 | 0.00814967 | 4.0455e-05 | 9.00177e-07 | 2(Loss) | true |
| Glaze | 845.239 | 0.0423967 | 1178.99ms | 3862 | 2560 | 8737.16 | 4357.46 | 0.053991 | 5.97231 | 28.936 | 5.77395 | 0.0092518 | 5.50233e-05 | 1.5273e-05 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5283.71 | 0.0564952 | 824.605ms | 3862 | 4890 | 758.366 | 697.065 | 0.0254909 | 1.0089 | 5.21647 | 0.592439 | 0.000261157 | 3.20887e-05 | 1.48264e-06 | 1(Win) | true |
| simdjson (reflection) | 4004.68 | 0.0340307 | 831.098ms | 3862 | 4890 | 479.004 | 919.696 | 0.0408828 | 1.31928 | 6.79208 | 0.533661 | 0.000259992 | 2.22926e-05 | 1.6415e-06 | 2(Loss) | true |
| Glaze | 2711.62 | 0.0521395 | 899.262ms | 3862 | 640 | 320.982 | 1358.26 | 0.0277316 | 1.92023 | 8.25065 | 0.995857 | 0.00475871 | 2.79162e-05 | 4.04583e-07 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1798.47 | 0.127941 | 1254.92ms | 9578 | 80 | 3377.95 | 5078.91 | 0.10449 | 2.83697 | 14.1221 | 2.69179 | 0.00201503 | 1.6966e-05 | 0 | 1(Win) | true |
| Glaze | 1396.78 | 0.0264017 | 1388.82ms | 9578 | 4890 | 14577.1 | 6539.56 | 0.0559506 | 3.63164 | 17.5416 | 3.49301 | 0.00168303 | 2.57065e-05 | 1.60132e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1285.66 | 0.0444248 | 1456.22ms | 9578 | 1280 | 12751.4 | 7104.73 | 0.115294 | 3.88837 | 18.7991 | 3.07006 | 0.00169847 | 2.96089e-05 | 7.50418e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1235.09 | 0.0594978 | 1485.62ms | 9578 | 1280 | 24783.4 | 7395.63 | 0.065357 | 4.02664 | 19.6502 | 2.98538 | 0.0042813 | 2.2431e-05 | 2.85485e-06 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2760.81 | 0.102734 | 1216.31ms | 9578 | 1280 | 14788.1 | 3308.56 | 0.0952821 | 1.83855 | 10.0857 | 1.7914 | 0.000215337 | 3.279e-05 | 8.23828e-06 | 1(Win) | true |
| Glaze | 2030.61 | 0.0691121 | 1337.24ms | 9578 | 1280 | 12371.3 | 4498.31 | 0.169689 | 2.47984 | 13.3257 | 2.53238 | 0.00027325 | 1.68028e-05 | 2.03918e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1716.66 | 0.0623545 | 1430.79ms | 9578 | 640 | 7045.23 | 5320.95 | 0.0501807 | 2.92058 | 14.7394 | 2.16538 | 0.000192825 | 1.51715e-05 | 1.63134e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1638.25 | 0.0381352 | 1457.87ms | 9578 | 2560 | 11574 | 5575.65 | 0.00443494 | 3.04348 | 15.6373 | 2.09522 | 0.00258364 | 2.07996e-05 | 1.34586e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4193.96 | 0.221573 | 958.416ms | 9578 | 80 | 1863.05 | 2177.96 | 0.035022 | 1.22945 | 5.37764 | 1.07622 | 0.00220949 | 3.65421e-05 | 3.91522e-06 | 1(Win) | true |
| simdjson (reflection) | 3821.68 | 0.102814 | 982.303ms | 9578 | 1280 | 7729.56 | 2390.13 | 0.395279 | 1.32718 | 6.27208 | 1.17248 | 0.000614527 | 2.07181e-05 | 3.50739e-06 | 2(Loss) | true |
| Glaze | 1966.3 | 0.0321559 | 1206.47ms | 9578 | 2560 | 5712.3 | 4645.42 | 0.0656298 | 2.55836 | 12.8416 | 2.67833 | 0.00143787 | 3.27492e-05 | 3.79287e-06 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11181.4 | 0.109785 | 841.958ms | 9578 | 2560 | 2059.12 | 816.919 | 0.0290333 | 0.472831 | 2.23585 | 0.274588 | 0.000818934 | 2.40623e-05 | 3.79287e-06 | 1(Win) | true |
| simdjson (reflection) | 9521.44 | 0.10857 | 860.444ms | 9578 | 4890 | 5304.88 | 959.34 | 0.0258671 | 0.545916 | 3.07329 | 0.321257 | 0.000108463 | 3.85597e-05 | 1.19138e-05 | 2(Loss) | true |
| Glaze | 6129.42 | 0.0646215 | 911.258ms | 9578 | 160 | 148.383 | 1490.24 | 0.0125835 | 0.849759 | 4.44801 | 0.720192 | 0.000249269 | 1.04406e-05 | 0 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3357.29 | 0.0859524 | 846.48ms | 3873 | 160 | 143.072 | 1100.17 | 0.188394 | 1.53513 | 6.92073 | 0.830364 | 0.000264653 | 3.71159e-05 | 3.22747e-06 | 1(Win) | true |
| Glaze | 1866.76 | 0.0338496 | 934.213ms | 3873 | 4890 | 2193.49 | 1978.61 | 0.0615757 | 2.72353 | 12.8533 | 1.7906 | 0.000260363 | 4.63066e-05 | 7.02256e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1618.4 | 0.0876942 | 967.805ms | 3873 | 640 | 2563.57 | 2282.24 | 0.00985969 | 3.12089 | 14.3705 | 1.55797 | 0.000260618 | 3.0661e-05 | 4.03434e-07 | 3(Loss) | true |
| simdjson (ondemand) | 705.416 | 0.0417177 | 1259.52ms | 3873 | 1280 | 6107.37 | 5236.03 | 0.0195499 | 7.11175 | 32.0147 | 3.66357 | 0.00479058 | 3.73176e-05 | 2.82404e-06 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3703.26 | 0.0792241 | 834.805ms | 3873 | 160 | 99.8992 | 997.388 | 0.193881 | 1.40019 | 6.48954 | 0.731474 | 0.000417958 | 4.35709e-05 | 0 | 1(Win) | true |
| Glaze | 1969.09 | 0.0330421 | 925.5ms | 3873 | 320 | 122.928 | 1875.78 | 0.0481234 | 2.57645 | 12.4219 | 1.69171 | 0.000290473 | 1.53305e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1715.5 | 0.0798559 | 951.265ms | 3873 | 30 | 88.6851 | 2153.07 | 0.0340483 | 2.95283 | 13.9262 | 1.45908 | 0.000516396 | 6.88527e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 716.896 | 0.0331765 | 1246.3ms | 3873 | 4890 | 14287.4 | 5152.18 | 0.111307 | 7.07322 | 31.5598 | 3.56468 | 0.00721201 | 7.13344e-05 | 2.06981e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 924.616 | 0.0398701 | 1136.99ms | 3873 | 4890 | 12404.4 | 3994.72 | 0.0294348 | 5.50835 | 24.5371 | 5.12084 | 0.010714 | 0.000143038 | 5.12699e-05 | 1(Win) | true |
| simdjson (reflection) | 871.93 | 0.149581 | 1155.1ms | 3873 | 30 | 1204.51 | 4236.1 | 0.0943374 | 5.8583 | 27.5386 | 5.36303 | 0.0109562 | 4.3033e-05 | 0 | 2(Loss) | true |
| Glaze | 851.314 | 0.0621014 | 1176.28ms | 3873 | 320 | 2323.11 | 4338.68 | 0.101239 | 5.99502 | 28.8851 | 5.86186 | 0.00667603 | 5.56739e-05 | 1.12962e-05 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6284.09 | 0.11699 | 813.414ms | 3873 | 30 | 14.1851 | 587.767 | 0.0170164 | 0.864679 | 3.98502 | 0.476375 | 0.000774593 | 2.58198e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 4077.07 | 0.0365536 | 832.704ms | 3873 | 640 | 70.1843 | 905.941 | 0.023106 | 1.30068 | 6.77795 | 0.530338 | 0.000296927 | 1.8558e-05 | 4.03434e-07 | 2(Loss) | true |
| Glaze | 2697.49 | 0.0466938 | 896.458ms | 3873 | 4890 | 1998.96 | 1369.27 | 0.1082 | 1.92956 | 7.83946 | 0.993041 | 0.00407535 | 3.38456e-05 | 1.16163e-06 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1615.14 | 0.0313246 | 6465.44ms | 94653 | 1280 | 392309 | 55888.7 | 0.245821 | 3.08257 | 13.8375 | 2.4602 | 0.0101609 | 7.4202e-06 | 2.47615e-06 | 1(Win) | true |
| Glaze | 1406.17 | 0.0318952 | 7201.02ms | 94653 | 4890 | 2.04999e+06 | 64194.4 | 0.10574 | 3.53177 | 15.5304 | 3.09463 | 0.0133392 | 1.02279e-05 | 4.15899e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1403.13 | 0.0753075 | 7194.74ms | 94653 | 4890 | 1.14777e+07 | 64333.3 | 0.02459 | 3.51735 | 15.5498 | 2.74298 | 0.0100822 | 2.64339e-05 | 1.52835e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1302.33 | 0.0127556 | 7683.75ms | 94653 | 2560 | 200112 | 69313 | 0.0914131 | 3.80849 | 15.007 | 2.83031 | 0.010896 | 1.83029e-05 | 9.70238e-06 | 4(Loss) | true |
| simdjson (reflection) | 1269.12 | 0.0196629 | 7892.05ms | 94653 | 4890 | 956471 | 71126.8 | 0.0352903 | 3.94559 | 14.2811 | 2.70854 | 0.0107357 | 3.89389e-05 | 2.36879e-05 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2518.89 | 0.0180056 | 5631.15ms | 94653 | 2560 | 106587 | 35836.5 | 0.00133311 | 1.97561 | 9.87574 | 1.56541 | 0.00572492 | 4.59738e-06 | 1.2876e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2079.6 | 0.105913 | 6527.81ms | 94653 | 640 | 1.35265e+06 | 43406.4 | 0.123766 | 2.37882 | 11.624 | 1.85339 | 0.00603071 | 5.03484e-06 | 1.58474e-06 | 2(Loss) | true |
| Glaze | 2028.94 | 0.0878953 | 6592.74ms | 94653 | 1280 | 1.95736e+06 | 44490.2 | 0.258825 | 2.45444 | 11.7553 | 2.23439 | 0.00865147 | 3.72248e-06 | 4.9523e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1811.15 | 0.0256043 | 7124.16ms | 94653 | 640 | 104223 | 49840.1 | 0.0283953 | 2.73988 | 11.1444 | 1.95112 | 0.00724985 | 5.23293e-06 | 8.08876e-07 | 4(Loss) | true |
| simdjson (reflection) | 1609.75 | 0.0344651 | 7663.23ms | 94653 | 1280 | 478104 | 56075.9 | 0.0530561 | 3.09176 | 11.2344 | 2.00033 | 0.00669757 | 1.19763e-05 | 4.54786e-06 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20576.7 | 0.0730504 | 1192.57ms | 94653 | 30 | 308.093 | 4386.9 | 0.0205114 | 0.248373 | 1.20076 | 0.18066 | 0.000157769 | 1.40865e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 13428.3 | 0.0431191 | 1425.79ms | 94653 | 80 | 672.139 | 6722.25 | 0.162411 | 0.378996 | 2.045 | 0.302885 | 6.48421e-05 | 1.58474e-06 | 0 | 2(Loss) | true |
| Glaze | 7802.33 | 0.0462863 | 1909.6ms | 94653 | 2560 | 73411.9 | 11569.4 | 0.0475538 | 0.636328 | 3.46937 | 0.568635 | 8.93642e-05 | 6.85068e-06 | 1.62188e-06 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20481.5 | 0.0415 | 1188.37ms | 94653 | 160 | 535.258 | 4407.31 | 0.146558 | 0.245001 | 1.19515 | 0.179403 | 4.25898e-05 | 2.77329e-06 | 5.94276e-07 | 1(Win) | true |
| simdjson (reflection) | 13276.2 | 0.0402507 | 1425.66ms | 94653 | 1280 | 9586.84 | 6799.22 | 0.100083 | 0.376616 | 2.03945 | 0.301639 | 3.18185e-05 | 3.25201e-06 | 1.2876e-06 | 2(Loss) | true |
| Glaze | 9221.01 | 0.046195 | 1735.22ms | 94653 | 4890 | 100002 | 9789.4 | 0.0917658 | 0.537309 | 3.41879 | 0.557426 | 6.95123e-05 | 8.17322e-06 | 4.45282e-06 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1751.7 | 0.0711685 | 7547.33ms | 124597 | 640 | 1.49159e+06 | 67834 | 0.00885585 | 2.84296 | 12.2468 | 2.09638 | 0.010244 | 1.20012e-05 | 7.28599e-06 | 1(Win) | true |
| Jsonifier | 1726.75 | 0.0390539 | 7655.77ms | 124597 | 640 | 462239 | 68814.3 | 0.0633574 | 2.88329 | 12.4006 | 2.35708 | 0.0110102 | 4.38915e-06 | 7.90047e-07 | 2(Loss) | true |
| simdjson (ondemand) | 1652.57 | 0.0276894 | 7935.28ms | 124597 | 320 | 126846 | 71903.3 | 0.0130758 | 3.00195 | 11.7102 | 2.15788 | 0.00923949 | 2.08171e-06 | 1.00323e-07 | 3(Loss) | true |
| simdjson (reflection) | 1599.02 | 0.0164519 | 8198.66ms | 124597 | 4890 | 730881 | 74311 | 0.0186452 | 3.11016 | 11.2473 | 2.08755 | 0.00905591 | 8.7464e-06 | 3.56487e-06 | 4(Loss) | true |
| Glaze | 1588.79 | 0.118837 | 8216.88ms | 124597 | 80 | 631938 | 74789.7 | 0.126799 | 3.12259 | 13.8128 | 2.74786 | 0.0130074 | 4.91585e-06 | 1.40453e-06 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2586.66 | 0.0280298 | 6610.38ms | 124597 | 1280 | 212220 | 45937.6 | 0.172316 | 1.9218 | 9.26371 | 1.42405 | 0.00564294 | 7.9569e-06 | 3.14138e-06 | 1(Win) | true |
| Jsonifier | 2437.04 | 0.0427309 | 6966.28ms | 124597 | 640 | 277814 | 48757.9 | 0.0237678 | 2.03723 | 9.3926 | 1.68059 | 0.00801411 | 4.85315e-06 | 9.90694e-07 | 2(Loss) | true |
| simdjson (ondemand) | 2313.44 | 0.037677 | 7219.77ms | 124597 | 160 | 59920.3 | 51363 | 0.00781144 | 2.14557 | 8.81424 | 1.50155 | 0.00560768 | 3.36084e-06 | 1.40453e-06 | 3(Loss) | true |
| Glaze | 2123.88 | 0.0199066 | 7633.79ms | 124597 | 2560 | 317534 | 55947 | 0.0507203 | 2.33609 | 10.9518 | 2.10128 | 0.00954128 | 3.29186e-06 | 5.39239e-07 | 4(Loss) | true |
| simdjson (reflection) | 2016.35 | 0.0605447 | 7910.74ms | 124597 | 320 | 407365 | 58930.6 | 0.0606271 | 2.46407 | 8.91749 | 1.54791 | 0.00540801 | 2.90938e-06 | 8.02588e-07 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23116.1 | 0.0385687 | 1304.73ms | 136037 | 160 | 749.678 | 5612.32 | 0.0270537 | 0.220465 | 0.86847 | 0.125694 | 7.64957e-05 | 2.34311e-06 | 8.72924e-07 | 1(Win) | true |
| Glaze | 7071.26 | 0.0834496 | 2575.17ms | 136076 | 80 | 18763.2 | 18352.1 | 0.0085133 | 0.702791 | 3.79773 | 0.637739 | 0.000386273 | 3.76628e-06 | 9.18604e-07 | 2(Loss) | true |
| simdjson (reflection) | 620.937 | 0.182218 | 5518ms | 136037 | 1280 | 1.85528e+08 | 208934 | 0.00278018 | 7.97621 | 34.7861 | 7.15206 | 0.0267806 | 0.0292712 | 0.000122858 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23333 | 0.0343436 | 1300.36ms | 136037 | 1280 | 4667.4 | 5560.15 | 0.0676793 | 0.217655 | 0.864574 | 0.124826 | 2.75373e-05 | 2.21677e-06 | 5.91521e-07 | 1(Win) | true |
| Glaze | 8052.52 | 0.0139065 | 2363.79ms | 136076 | 2560 | 12858 | 16115.7 | 0.00916793 | 0.617457 | 3.76371 | 0.630104 | 5.94538e-05 | 5.10974e-06 | 2.97685e-06 | 2(Loss) | true |
| simdjson (reflection) | 621.626 | 0.231023 | 5541.87ms | 136037 | 320 | 7.439e+07 | 208703 | 0.0810231 | 7.96352 | 34.7839 | 7.15184 | 0.0269312 | 0.044048 | 1.33925e-05 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1133 | 0.36748 | 5884.32ms | 2251027 | 160 | 7.75698e+09 | 1.89475e+06 | 0.115626 | 4.37437 | 23.7126 | 4.83639 | 0.0074089 | 0.0648808 | 0.00269365 | 1(Win) | true |
| Jsonifier (two-stage) | 981.867 | 0.128651 | 6834.26ms | 2251027 | 30 | 2.3736e+08 | 2.18639e+06 | 0.0577604 | 5.01829 | 26.3686 | 5.07623 | 0.0104424 | 0.102632 | 0.00459079 | 2(Loss) | true |
| Glaze | 860.569 | 0.391949 | 7760.3ms | 2251027 | 80 | 7.64784e+09 | 2.49457e+06 | 0.24972 | 5.75384 | 30.3101 | 5.64287 | 0.00981579 | 0.0629083 | 0.00175819 | 3(Loss) | true |
| simdjson (ondemand) | 823.213 | 0.0886311 | 8222.2ms | 2251027 | 30 | 1.60262e+08 | 2.60777e+06 | 0.0665277 | 6.0257 | 29.7628 | 5.28924 | 0.014825 | 0.107512 | 0.000485216 | 4(Loss) | true |
| simdjson (reflection) | 808.707 | 0.268249 | 8237.86ms | 2251027 | 160 | 8.11291e+09 | 2.65454e+06 | 0.448654 | 6.12207 | 29.0562 | 5.38776 | 0.0104055 | 0.10338 | 0.00411151 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1423.33 | 0.0809856 | 5938.61ms | 2251027 | 80 | 1.19358e+08 | 1.50825e+06 | 0.702068 | 3.48055 | 18.7984 | 3.66342 | 0.0069043 | 0.041919 | 0.0024141 | 1(Win) | true |
| Jsonifier (two-stage) | 1201.26 | 0.283411 | 6743.88ms | 2251027 | 160 | 4.10433e+09 | 1.78708e+06 | 0.0642259 | 4.09637 | 21.5088 | 3.92014 | 0.00986704 | 0.0788813 | 0.000127731 | 2(Loss) | true |
| Glaze | 1022.47 | 0.456911 | 7791.4ms | 2251027 | 80 | 7.36226e+09 | 2.09957e+06 | 0.378922 | 4.85031 | 25.3567 | 4.46543 | 0.00903212 | 0.0399112 | 0.00286985 | 3(Loss) | true |
| simdjson (ondemand) | 995.099 | 0.089196 | 8047.52ms | 2251027 | 40 | 1.48108e+08 | 2.15732e+06 | 0.922178 | 4.97821 | 24.844 | 4.12107 | 0.0112011 | 0.0759191 | 0.000202541 | 4(Loss) | true |
| simdjson (reflection) | 951.367 | 0.264251 | 8173.15ms | 2251027 | 160 | 5.68879e+09 | 2.25649e+06 | 0.0667408 | 5.20751 | 24.1806 | 4.22568 | 0.0089147 | 0.0773906 | 0.00636686 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2124.62 | 0.0339704 | 5994.45ms | 2090234 | 40 | 4.06339e+06 | 938240 | 0.0182209 | 2.37568 | 7.66649 | 0.373371 | 0.000371908 | 0.0511996 | 8.82676e-05 | 1(Win) | true |
| Glaze | 1434.74 | 0.227148 | 8844.34ms | 2090234 | 320 | 3.18723e+09 | 1.38938e+06 | 0.0724866 | 3.48032 | 9.59419 | 0.598239 | 0.0115888 | 0.0696778 | 0.00601854 | 2(Loss) | true |
| simdjson (reflection) | 1046.31 | 0.0888081 | 6000.86ms | 2090326 | 30 | 8.58883e+07 | 1.90526e+06 | 0.0529167 | 4.85491 | 15.154 | 1.43489 | 0.0163716 | 0.0511917 | 0.000387882 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2127.02 | 0.0175502 | 5986.22ms | 2090234 | 30 | 811582 | 937182 | 0.00602552 | 2.37402 | 7.66632 | 0.373337 | 0.00032073 | 0.0510753 | 6.99443e-05 | 1(Win) | true |
| Glaze | 1528.33 | 0.137989 | 8288.79ms | 2090234 | 30 | 9.71786e+07 | 1.3043e+06 | 0.157699 | 3.28823 | 9.5901 | 0.597292 | 0.0115792 | 0.0439533 | 0.00206939 | 2(Loss) | true |
| simdjson (reflection) | 1032.85 | 0.204391 | 6019.8ms | 2090326 | 160 | 2.48998e+09 | 1.93009e+06 | 0.138939 | 4.88763 | 15.1539 | 1.43485 | 0.0163978 | 0.0510647 | 0.00269256 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2211.86 | 0.26846 | 7236.55ms | 5373214 | 160 | 6.18918e+09 | 2.31674e+06 | 0.523723 | 2.22245 | 11.8502 | 2.16762 | 0.00498924 | 0.0627326 | 2.05824e-05 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2195.63 | 0.391114 | 7351.94ms | 5373214 | 80 | 6.66576e+09 | 2.33387e+06 | 0.418451 | 2.26687 | 12.0352 | 2.54056 | 0.00343023 | 0.0384071 | 1.10897e-05 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1835.56 | 0.299739 | 8664.96ms | 5373214 | 160 | 1.12032e+10 | 2.79168e+06 | 0.210667 | 2.70012 | 13.2336 | 2.24874 | 0.00652193 | 0.0648953 | 2.09791e-05 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1822.22 | 0.255825 | 8751.27ms | 5373214 | 160 | 8.28079e+09 | 2.81212e+06 | 0.25883 | 2.72363 | 12.939 | 2.29043 | 0.00467071 | 0.0626752 | 4.08659e-05 | 3(Tie) | true |
| Glaze | 1624.19 | 0.320055 | 9811.05ms | 5373214 | 30 | 3.0589e+09 | 3.15498e+06 | 0.0920737 | 3.04888 | 15.9043 | 2.91961 | 0.00497217 | 0.0407764 | 0.00567247 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2642.88 | 0.41406 | 7211.39ms | 5373214 | 160 | 1.03124e+10 | 1.9389e+06 | 0.192345 | 1.86202 | 9.81667 | 1.68401 | 0.00470444 | 0.0524462 | 0.00023549 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2632.53 | 0.27625 | 7249.08ms | 5373214 | 160 | 4.62644e+09 | 1.94653e+06 | 0.232204 | 1.8983 | 10.0013 | 2.05676 | 0.00315473 | 0.0282886 | 0.000365566 | 1(Tie) | true |
| simdjson (ondemand) | 2193.73 | 0.314263 | 8477.19ms | 5373214 | 160 | 8.62206e+09 | 2.33589e+06 | 0.367496 | 2.2625 | 11.1726 | 1.75956 | 0.00513408 | 0.050815 | 1.25658e-05 | 3(Loss) | true |
| simdjson (reflection) | 2136.25 | 0.344048 | 8633.65ms | 5373214 | 40 | 2.72436e+09 | 2.39874e+06 | 0.0835445 | 2.32159 | 10.8949 | 1.80351 | 0.0040383 | 0.0513884 | 5.11333e-06 | 4(Loss) | true |
| Glaze | 1871.78 | 0.37673 | 9790.5ms | 5373214 | 80 | 8.50955e+09 | 2.73765e+06 | 0.404362 | 2.64816 | 13.8613 | 2.43529 | 0.00439311 | 0.0298506 | 0.00184079 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6075.43 | 0.283369 | 6666.07ms | 6661897 | 320 | 2.80993e+09 | 1.04573e+06 | 0.269206 | 0.834002 | 2.48092 | 0.117149 | 0.000104816 | 0.028094 | 5.81202e-05 | 1(Win) | true |
| Glaze | 3303.81 | 0.141502 | 6042.35ms | 6661897 | 30 | 2.22133e+08 | 1.92302e+06 | 0.189454 | 1.51733 | 4.33452 | 0.464361 | 0.00370651 | 0.0636545 | 0.000835513 | 2(Loss) | true |
| simdjson (reflection) | 388.289 | 0.536688 | 11305.7ms | 6661989 | 30 | 2.31346e+11 | 1.63625e+07 | 1.26039 | 12.9603 | 41.4337 | 5.69772 | 0.0242644 | 0.254667 | 0.0951252 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6055.25 | 0.319438 | 6665.54ms | 6661897 | 320 | 3.59463e+09 | 1.04922e+06 | 0.10742 | 0.833869 | 2.48087 | 0.117138 | 0.00011249 | 0.0280799 | 7.75961e-06 | 1(Win) | true |
| Glaze | 3900.73 | 0.408646 | 5078.1ms | 6661897 | 160 | 7.08791e+09 | 1.62874e+06 | 0.00324264 | 1.29053 | 4.33307 | 0.464028 | 0.00369678 | 0.024853 | 1.07693e-05 | 2(Loss) | true |
| simdjson (reflection) | 392.547 | 0.370763 | 11383.5ms | 6661989 | 30 | 1.08029e+11 | 1.6185e+07 | 0.404647 | 12.7991 | 41.4468 | 5.70449 | 0.0241629 | 0.255255 | 0.0884048 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2303.5 | 0.0718169 | 5481.05ms | 500299 | 160 | 3.54043e+06 | 207129 | 0.415939 | 2.15376 | 9.49596 | 1.72543 | 0.0112973 | 0.00775299 | 3.16311e-05 | 1(Win) | true |
| Glaze | 1808.35 | 0.0727874 | 6994.37ms | 500299 | 320 | 1.18021e+07 | 263845 | 0.061161 | 2.76191 | 11.6165 | 2.2607 | 0.013908 | 0.00534282 | 2.48914e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1776.47 | 0.100347 | 7063.41ms | 500299 | 40 | 2.90546e+06 | 268579 | 0.234764 | 2.79077 | 12.1942 | 2.10944 | 0.014137 | 0.0339882 | 3.49791e-05 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1430.5 | 0.145464 | 8701.4ms | 500299 | 80 | 1.88314e+07 | 333536 | 0.250155 | 3.47183 | 13.8648 | 2.22857 | 0.0170987 | 0.0417856 | 4.45983e-05 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1430.31 | 0.0940345 | 8809.48ms | 500299 | 160 | 1.57432e+07 | 333579 | 0.235805 | 3.49974 | 13.8125 | 2.38932 | 0.0180308 | 0.0318918 | 0.000135781 | 4(Tie) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2873.53 | 0.171565 | 5261.96ms | 500299 | 640 | 5.19356e+07 | 166040 | 0.192502 | 1.7254 | 8.3815 | 1.45418 | 0.00764153 | 0.00408359 | 2.32361e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2142.54 | 0.121798 | 6811.7ms | 500299 | 80 | 5.8853e+06 | 222690 | 0.186689 | 2.33192 | 11.0739 | 1.83744 | 0.0103332 | 0.0237303 | 4.14752e-06 | 2(Loss) | true |
| Glaze | 2127.28 | 0.0637217 | 6839.93ms | 500299 | 320 | 6.53632e+06 | 224287 | 0.00374116 | 2.34292 | 10.511 | 1.99289 | 0.00948955 | 0.00275603 | 3.61659e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1750.24 | 0.251543 | 8021.69ms | 500299 | 40 | 1.88083e+07 | 272604 | 0.0233941 | 2.85212 | 12.7257 | 1.94762 | 0.0086884 | 0.0246363 | 2.25365e-05 | 4(Loss) | true |
| simdjson (reflection) | 1658.25 | 0.304238 | 8369.81ms | 500299 | 640 | 4.90416e+08 | 287726 | 0.0074816 | 2.99141 | 12.6947 | 2.1169 | 0.0110891 | 0.0205994 | 6.18693e-06 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12418.3 | 0.0436999 | 4616.15ms | 500299 | 320 | 90207.6 | 38420.8 | 0.0289153 | 0.399716 | 1.81562 | 0.301808 | 0.00130882 | 0.00482951 | 1.4179e-06 | 1(Win) | true |
| simdjson (reflection) | 11154.2 | 0.0427258 | 5072.08ms | 500299 | 320 | 106884 | 42775.2 | 0.180585 | 0.44536 | 2.18113 | 0.197082 | 0.00109838 | 0.000261531 | 2.3486e-06 | 2(Loss) | true |
| Glaze | 6065.11 | 0.0483457 | 8743.49ms | 500299 | 320 | 462857 | 78666.7 | 0.229889 | 0.819924 | 3.7648 | 0.550473 | 0.00128659 | 0.0239016 | 1.87388e-06 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12459.2 | 0.0521152 | 4602.28ms | 500299 | 320 | 127456 | 38294.9 | 0.0553415 | 0.398642 | 1.81454 | 0.301562 | 0.00128867 | 0.0047546 | 1.04937e-05 | 1(Win) | true |
| simdjson (reflection) | 11270.5 | 0.0408702 | 4997.14ms | 500299 | 640 | 191587 | 42333.7 | 0.0435976 | 0.4418 | 2.18004 | 0.196834 | 0.00106931 | 7.15916e-05 | 1.77706e-06 | 2(Loss) | true |
| Glaze | 7035.34 | 0.0967079 | 7557.6ms | 500299 | 320 | 1.37646e+06 | 67817.9 | 0.0163002 | 0.703011 | 3.75128 | 0.547385 | 0.00131966 | 0.0015292 | 2.41106e-06 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3574.47 | 0.184875 | 8119.76ms | 1151920 | 40 | 1.29133e+07 | 307334 | 0.307295 | 1.40337 | 6.09156 | 0.950005 | 0.00610539 | 0.0550339 | 2.75627e-05 | 1(Win) | true |
| Jsonifier | 3262.1 | 0.084787 | 8831.88ms | 1151920 | 80 | 6.52228e+06 | 336764 | 0.00651007 | 1.52488 | 6.62759 | 1.3859 | 0.00476486 | 0.0192146 | 1.97713e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3028.1 | 0.190091 | 9532.3ms | 1151920 | 30 | 1.42675e+07 | 362787 | 0.164142 | 1.65738 | 6.78681 | 1.00165 | 0.00709902 | 0.0508149 | 4.41871e-05 | 3(Loss) | true |
| simdjson (reflection) | 2988.62 | 0.103963 | 9664.18ms | 1151920 | 80 | 1.16828e+07 | 367580 | 0.00712039 | 1.68468 | 6.76116 | 1.07047 | 0.00771268 | 0.0451069 | 0.000168914 | 4(Loss) | true |
| Glaze | 2581.7 | 0.108039 | 5546.44ms | 1151920 | 40 | 8.4539e+06 | 425517 | 0.0921669 | 1.92221 | 8.47802 | 1.61312 | 0.00754579 | 0.0150659 | 2.30919e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4155.43 | 0.230887 | 7930.47ms | 1151920 | 1280 | 4.76893e+08 | 264366 | 0.0336355 | 1.20177 | 5.6057 | 0.832037 | 0.00435747 | 0.0463383 | 5.38503e-05 | 1(Win) | true |
| Jsonifier | 3728.72 | 0.154618 | 8621.31ms | 1151920 | 40 | 8.30049e+06 | 294620 | 0.113308 | 1.33863 | 6.14426 | 1.26815 | 0.00352258 | 0.012247 | 7.5092e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3616.02 | 0.191025 | 8844.3ms | 1151920 | 30 | 1.01038e+07 | 303803 | 0.204354 | 1.38326 | 6.28949 | 0.878724 | 0.00399898 | 0.0367343 | 6.36618e-06 | 3(Loss) | true |
| simdjson (reflection) | 3459.43 | 0.0873382 | 9235.53ms | 1151920 | 160 | 1.23074e+07 | 317555 | 0.0388975 | 1.44759 | 6.2808 | 0.953606 | 0.00495847 | 0.033615 | 3.04383e-06 | 4(Loss) | true |
| Glaze | 2918.08 | 0.129538 | 5399.4ms | 1151920 | 80 | 1.90256e+07 | 376466 | 0.227155 | 1.71584 | 8.00111 | 1.49749 | 0.0055457 | 0.00987654 | 3.97163e-06 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20476.4 | 0.0870904 | 7571.86ms | 1439562 | 40 | 136382 | 67046.7 | 0.0809046 | 0.246974 | 0.702912 | 0.104859 | 0.000452256 | 0.0172193 | 0.000297017 | 1(Win) | true |
| Glaze | 5849.78 | 0.164917 | 6283.28ms | 1439584 | 160 | 2.39686e+07 | 234691 | 0.0942371 | 0.86181 | 3.12232 | 0.499155 | 0.000874675 | 0.0620742 | 9.68162e-07 | 2(Loss) | true |
| simdjson (reflection) | 569.869 | 0.534705 | 7484.01ms | 1439562 | 160 | 2.65496e+10 | 2.4091e+06 | 0.379917 | 8.72975 | 36.1164 | 6.49797 | 0.0162736 | 0.309191 | 0.000186337 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20490.1 | 0.0268527 | 7560.53ms | 1439562 | 320 | 103586 | 67001.9 | 0.0524093 | 0.24683 | 0.702676 | 0.104809 | 0.000443156 | 0.0171719 | 3.81192e-06 | 1(Win) | true |
| Glaze | 7909.66 | 0.24443 | 9357.63ms | 1439584 | 1280 | 2.30398e+08 | 173572 | 0.0120705 | 0.62981 | 3.11679 | 0.497885 | 0.000871593 | 0.0173604 | 9.32887e-06 | 2(Loss) | true |
| simdjson (reflection) | 574.1 | 0.506923 | 7487.56ms | 1439562 | 160 | 2.3512e+10 | 2.39135e+06 | 0.217549 | 8.66403 | 36.1166 | 6.49803 | 0.016372 | 0.309376 | 0.000299379 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2313.72 | 0.0462047 | 3065.68ms | 56369 | 640 | 73758.7 | 23234.3 | 0.035083 | 2.18758 | 9.17256 | 1.80052 | 0.00299866 | 3.44826e-05 | 1.73245e-05 | 1(Win) | true |
| Glaze | 1945.48 | 0.151718 | 3517.57ms | 56369 | 640 | 1.12482e+06 | 27632 | 0.0258521 | 2.59649 | 11.254 | 2.283 | 0.00505029 | 1.03947e-05 | 4.26875e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1847.39 | 0.0209875 | 3657.33ms | 56369 | 4890 | 182386 | 29099.2 | 0.0690708 | 2.72294 | 11.9995 | 2.13213 | 0.00512389 | 3.20703e-05 | 1.79253e-05 | 3(Loss) | true |
| simdjson (reflection) | 1511.58 | 0.051181 | 4309.56ms | 56369 | 2560 | 848156 | 35563.9 | 0.0500505 | 3.30487 | 13.9761 | 2.47645 | 0.00471602 | 1.07481e-05 | 4.58752e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1353.35 | 0.0265036 | 4719.96ms | 56369 | 2560 | 283736 | 39722.1 | 0.153248 | 3.69579 | 14.5317 | 2.68581 | 0.00907603 | 5.39276e-05 | 2.8717e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3282.15 | 0.0196409 | 2725.37ms | 56369 | 4890 | 50604.9 | 16378.8 | 0.0701133 | 1.5395 | 7.18527 | 1.34599 | 0.00167015 | 7.3174e-06 | 1.05208e-06 | 1(Win) | true |
| Glaze | 2788.54 | 0.15691 | 3024.7ms | 56369 | 1280 | 1.17122e+06 | 19278 | 0.0247266 | 1.79843 | 8.97515 | 1.75905 | 0.00217339 | 7.38715e-06 | 1.64929e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2489.45 | 0.262032 | 3284.49ms | 56369 | 30 | 96052 | 21594.2 | 0.0330444 | 2.03187 | 9.98751 | 1.67133 | 0.00261314 | 1.18268e-05 | 4.13939e-06 | 3(Loss) | true |
| simdjson (reflection) | 1748.3 | 0.104489 | 4219.53ms | 56369 | 640 | 660643 | 30748.5 | 0.0194128 | 2.85043 | 12.41 | 2.12395 | 0.00318119 | 7.59504e-06 | 9.42451e-07 | 4(Loss) | true |
| simdjson (ondemand) | 1691.31 | 0.0391048 | 4325.13ms | 56369 | 1280 | 197744 | 31784.6 | 0.0323547 | 2.97721 | 12.3217 | 2.18814 | 0.00861958 | 1.53287e-05 | 6.05663e-06 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15087.8 | 0.0924379 | 1098.31ms | 56369 | 640 | 6942.39 | 3562.99 | 0.0108769 | 0.338933 | 1.41828 | 0.224024 | 0.000198414 | 6.15365e-06 | 5.82102e-07 | 1(Win) | true |
| simdjson (reflection) | 13121.1 | 0.0776841 | 1149.68ms | 56369 | 30 | 303.895 | 4097.03 | 0.0268559 | 0.389458 | 1.6993 | 0.277457 | 0.000309863 | 1.59662e-05 | 5.91342e-06 | 2(Loss) | true |
| Glaze | 6348.57 | 0.044838 | 1592.36ms | 56369 | 4890 | 70490.6 | 8467.68 | 0.167296 | 0.797243 | 3.05274 | 0.465912 | 9.03592e-05 | 2.55801e-05 | 1.31546e-05 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15265.4 | 0.0700213 | 1095.28ms | 56369 | 1280 | 7782.8 | 3521.54 | 0.0970866 | 0.33491 | 1.40852 | 0.221789 | 0.000196584 | 5.68242e-06 | 5.12804e-07 | 1(Win) | true |
| simdjson (reflection) | 13336 | 0.0211547 | 1142.05ms | 56369 | 4890 | 3555.95 | 4031.03 | 0.00421462 | 0.382295 | 1.68962 | 0.275222 | 0.000140634 | 6.29071e-06 | 1.33143e-06 | 2(Loss) | true |
| Glaze | 7280.09 | 0.103587 | 1482.17ms | 56369 | 320 | 18722.6 | 7384.2 | 0.0431479 | 0.698237 | 2.97538 | 0.448722 | 5.2112e-05 | 6.81891e-06 | 1.60771e-06 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2511.23 | 0.0696174 | 3832.48ms | 83958 | 160 | 78833.1 | 31884.3 | 0.162688 | 2.01522 | 8.57729 | 1.44422 | 0.00488444 | 1.19852e-05 | 7.36976e-06 | 1(Win) | true |
| Glaze | 2412.04 | 0.137393 | 4077.27ms | 83958 | 4890 | 1.01718e+07 | 33195.4 | 0.15818 | 2.09288 | 9.99477 | 2.07658 | 0.00417018 | 3.93906e-05 | 2.1298e-05 | 2(Loss) | true |
| Jsonifier | 2238.89 | 0.0238668 | 4320.64ms | 83958 | 2560 | 186502 | 35762.6 | 0.0326019 | 2.25601 | 8.67056 | 1.83847 | 0.00500297 | 7.25344e-06 | 2.07042e-06 | 3(Loss) | true |
| simdjson (reflection) | 2161.38 | 0.0751498 | 4436.22ms | 83958 | 1280 | 992041 | 37045.2 | 0.0412059 | 2.29214 | 9.83799 | 1.67918 | 0.00310867 | 5.87161e-06 | 1.85174e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1915.28 | 0.0373899 | 4900.97ms | 83958 | 1280 | 312737 | 41805.1 | 0.115571 | 2.60082 | 10.2299 | 1.82425 | 0.00685113 | 1.56793e-05 | 5.50871e-06 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3367.23 | 0.10107 | 3487.05ms | 83958 | 40 | 23103.6 | 23778.8 | 0.106634 | 1.50361 | 7.22748 | 1.13521 | 0.00182978 | 6.25313e-06 | 2.97768e-07 | 1(Win) | true |
| Glaze | 3228.14 | 0.0908742 | 3584.74ms | 83958 | 320 | 162574 | 24803.3 | 0.0194694 | 1.55557 | 8.4835 | 1.72947 | 0.00195183 | 5.02483e-06 | 7.4442e-07 | 2(Loss) | true |
| Jsonifier | 2803.29 | 0.0232795 | 3947.74ms | 83958 | 1280 | 56590.8 | 28562.3 | 0.0151728 | 1.80341 | 7.33068 | 1.53186 | 0.00347293 | 4.2525e-06 | 1.05149e-06 | 3(Loss) | true |
| simdjson (reflection) | 2463.39 | 0.0749679 | 4368.17ms | 83958 | 1280 | 760006 | 32503.4 | 0.0145391 | 2.00724 | 8.8052 | 1.44685 | 0.00215928 | 5.38774e-06 | 1.2376e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2376.54 | 0.0238956 | 4500.53ms | 83958 | 1280 | 82962.3 | 33691.3 | 0.012511 | 2.09078 | 8.74275 | 1.48931 | 0.00582187 | 4.95039e-06 | 9.49135e-07 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20007.6 | 0.0264944 | 1190.6ms | 94370 | 4890 | 6945.34 | 4498.2 | 0.0715845 | 0.254851 | 0.906856 | 0.133952 | 0.00010537 | 4.2343e-06 | 1.27852e-06 | 1(Win) | true |
| Glaze | 5867.4 | 0.102945 | 2283.13ms | 94370 | 640 | 159575 | 15338.7 | 0.0381345 | 0.851957 | 3.65547 | 0.617802 | 0.000406876 | 3.72536e-06 | 1.2749e-06 | 2(Loss) | true |
| simdjson (reflection) | 525.015 | 0.190189 | 9165.24ms | 94370 | 2560 | 2.72106e+08 | 171420 | 0.295048 | 9.48475 | 38.6603 | 7.55199 | 0.026644 | 0.0178018 | 0.000118243 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20242.5 | 0.0192273 | 1185.89ms | 94370 | 4890 | 3573.42 | 4446 | 0.0279287 | 0.252017 | 0.901144 | 0.132669 | 0.000106061 | 2.39019e-06 | 4.59402e-07 | 1(Win) | true |
| Glaze | 7058.24 | 0.0421727 | 2023.12ms | 94370 | 4890 | 141399 | 12750.8 | 0.0396637 | 0.712747 | 3.60407 | 0.605966 | 0.000378719 | 7.87918e-06 | 3.69255e-06 | 2(Loss) | true |
| simdjson (reflection) | 519.693 | 0.220714 | 9255.96ms | 94370 | 2560 | 3.74002e+08 | 173176 | 0.102585 | 9.51228 | 38.6602 | 7.55203 | 0.0268038 | 0.011133 | 4.48244e-05 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1619.46 | 0.0329218 | 3903.75ms | 53331 | 4890 | 522752 | 31405.8 | 0.103204 | 3.12562 | 9.9387 | 1.7364 | 0.0114831 | 8.15603e-05 | 4.66086e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1580.83 | 0.0960571 | 3970.23ms | 53331 | 2560 | 2.44505e+06 | 32173.2 | 0.072349 | 3.1983 | 10.6742 | 1.80753 | 0.00942774 | 5.34618e-05 | 2.78845e-05 | 2(Loss) | true |
| simdjson (reflection) | 1521.85 | 0.061024 | 4089.07ms | 53331 | 2560 | 1.06477e+06 | 33420.1 | 0.0633679 | 3.32274 | 10.7486 | 1.93833 | 0.0117391 | 6.64702e-05 | 1.37921e-05 | 3(Loss) | true |
| Glaze | 1475.85 | 0.116473 | 4203.46ms | 53331 | 640 | 1.03111e+06 | 34461.7 | 0.263685 | 3.42601 | 11.6107 | 2.26962 | 0.0188641 | 8.94766e-05 | 4.37714e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1414 | 0.0615622 | 4351.03ms | 53331 | 1280 | 627621 | 35969.1 | 0.0209055 | 3.5774 | 10.6151 | 2.13696 | 0.0112446 | 5.051e-05 | 1.74324e-05 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2305.13 | 0.0156935 | 3442.18ms | 53331 | 2560 | 30693.7 | 22064.1 | 0.0135685 | 2.19605 | 8.49058 | 1.31622 | 0.000577994 | 9.31681e-06 | 4.06512e-06 | 1(Win) | true |
| Jsonifier | 2174.13 | 0.072181 | 3663.11ms | 53331 | 1280 | 364958 | 23393.4 | 0.0621689 | 2.32633 | 7.72052 | 1.23647 | 0.00834332 | 1.90877e-05 | 6.95831e-06 | 2(Loss) | true |
| Glaze | 1964.13 | 0.0476042 | 3947.35ms | 53331 | 4890 | 743051 | 25894.6 | 0.0521359 | 2.56664 | 9.38001 | 1.76737 | 0.0148038 | 2.29381e-05 | 1.10128e-05 | 3(Loss) | true |
| simdjson (reflection) | 1882.2 | 0.0224408 | 4042.03ms | 53331 | 4890 | 179811 | 27021.8 | 0.151396 | 2.68948 | 8.79562 | 1.49106 | 0.00884402 | 2.7877e-05 | 7.44664e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1749.65 | 0.0286604 | 4197.06ms | 53331 | 2560 | 177690 | 29069 | 0.0826954 | 2.89371 | 8.70426 | 1.71373 | 0.00994549 | 1.9952e-05 | 5.67652e-06 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14752.1 | 0.0407499 | 1120.51ms | 58581 | 2560 | 6096.78 | 3787.07 | 0.00311494 | 0.34609 | 1.0576 | 0.167614 | 3.43675e-05 | 1.8184e-05 | 7.68834e-06 | 1(Win) | true |
| simdjson (reflection) | 11157 | 0.0364712 | 1243.16ms | 58581 | 4890 | 16308.9 | 5007.35 | 0.0101483 | 0.455799 | 1.49673 | 0.21227 | 2.72847e-05 | 1.08322e-05 | 2.30747e-06 | 2(Loss) | true |
| Glaze | 7114.51 | 0.179516 | 1530.73ms | 58581 | 320 | 63588.6 | 7852.57 | 0.00449674 | 0.714984 | 2.43482 | 0.370786 | 0.000184573 | 1.76038e-05 | 9.65543e-06 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15060.2 | 0.0265036 | 1113.76ms | 58581 | 4890 | 4726.87 | 3709.6 | 0.0308828 | 0.339252 | 1.0484 | 0.165549 | 3.43328e-05 | 9.40442e-06 | 2.95328e-06 | 1(Win) | true |
| simdjson (reflection) | 11247.9 | 0.0272703 | 1239.51ms | 58581 | 4890 | 8971.34 | 4966.88 | 0.0471755 | 0.452884 | 1.4875 | 0.210171 | 3.40884e-05 | 7.42509e-06 | 2.07009e-06 | 2(Loss) | true |
| Glaze | 8493.26 | 0.066859 | 1403.42ms | 58581 | 4890 | 94578.7 | 6577.83 | 0.0606073 | 0.599246 | 2.36218 | 0.354176 | 4.94308e-05 | 1.58346e-05 | 8.02203e-06 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1930.84 | 0.0407474 | 3969.71ms | 65103 | 4890 | 839492 | 32155.4 | 0.00164636 | 2.61837 | 9.14132 | 1.49079 | 0.00665178 | 7.33461e-05 | 3.84918e-05 | 1(Win) | true |
| simdjson (reflection) | 1845.52 | 0.0481366 | 4120.61ms | 65103 | 2560 | 671363 | 33642.1 | 0.156237 | 2.73964 | 9.06214 | 1.59617 | 0.00899045 | 5.5081e-05 | 1.53963e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1692.73 | 0.0941568 | 4382.1ms | 65103 | 320 | 381664 | 36678.7 | 0.0814059 | 2.98894 | 8.9321 | 1.75274 | 0.00911815 | 5.5777e-05 | 3.01925e-05 | 3(Loss) | true |
| Jsonifier | 1651.9 | 0.0504303 | 4504.49ms | 65103 | 4890 | 1.75682e+06 | 37585.3 | 0.086071 | 3.06249 | 9.216 | 1.68865 | 0.0104733 | 0.00013066 | 7.19828e-05 | 4(Loss) | true |
| Glaze | 1536.33 | 0.0813038 | 4770.34ms | 65103 | 1280 | 1.38186e+06 | 40412.5 | 0.096509 | 3.29214 | 10.7722 | 2.11488 | 0.0169839 | 6.35891e-05 | 2.35444e-05 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2525.37 | 0.0513888 | 3747.17ms | 65103 | 2560 | 408629 | 24585.3 | 0.00991347 | 1.99996 | 7.36664 | 1.09203 | 0.00480674 | 2.15044e-05 | 9.06616e-06 | 1(Win) | true |
| Jsonifier | 2329.13 | 0.0197369 | 3871.08ms | 65103 | 4890 | 135357 | 26656.8 | 0.156295 | 2.16936 | 7.44511 | 1.29076 | 0.0013919 | 1.46441e-05 | 4.64264e-06 | 2(Loss) | true |
| simdjson (reflection) | 2217.15 | 0.0305344 | 4142.18ms | 65103 | 2560 | 187167 | 28003.1 | 0.0363653 | 2.27778 | 7.49697 | 1.24019 | 0.00780089 | 2.68625e-05 | 8.29215e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2076.52 | 0.0286281 | 4273.32ms | 65103 | 2560 | 187567 | 29899.5 | 0.0229818 | 2.43604 | 7.40184 | 1.41661 | 0.0082569 | 2.06164e-05 | 5.7841e-06 | 4(Loss) | true |
| Glaze | 1990.55 | 0.143443 | 4486.94ms | 65103 | 4890 | 9.78865e+06 | 31190.9 | 0.0636202 | 2.53913 | 8.96372 | 1.70898 | 0.0128344 | 2.24122e-05 | 8.1733e-06 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18359.8 | 0.0267089 | 1151.71ms | 78778 | 4890 | 5841.12 | 4092.02 | 0.00952754 | 0.277981 | 0.830308 | 0.124603 | 2.5502e-05 | 4.82057e-06 | 8.80007e-07 | 1(Win) | true |
| Glaze | 5050.5 | 0.0831473 | 2239.25ms | 78778 | 4890 | 748077 | 14875.5 | 0.0383206 | 0.999041 | 2.87286 | 0.449263 | 8.54852e-05 | 1.17256e-05 | 3.17737e-06 | 2(Loss) | true |
| simdjson (reflection) | 637.389 | 0.257757 | 6413.29ms | 78778 | 640 | 5.90747e+07 | 117869 | 0.215181 | 7.85718 | 29.286 | 6.61764 | 0.033375 | 0.00185412 | 6.81305e-05 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18646.6 | 0.0690712 | 1145.57ms | 78778 | 30 | 232.34 | 4029.07 | 0.0124083 | 0.274463 | 0.823669 | 0.123105 | 2.75034e-05 | 1.05782e-05 | 4.2313e-06 | 1(Win) | true |
| Glaze | 5867.83 | 0.234099 | 2026.64ms | 78778 | 640 | 574957 | 12803.5 | 0.0446001 | 0.864409 | 2.80596 | 0.434094 | 5.70829e-05 | 1.4122e-05 | 8.56838e-06 | 2(Loss) | true |
| simdjson (reflection) | 637.494 | 0.183512 | 6408.94ms | 78778 | 1280 | 5.98686e+07 | 117850 | 0.222242 | 7.82711 | 29.2852 | 6.61746 | 0.0331165 | 0.00522402 | 2.40986e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2429.15 | 0.0994527 | 1205.88ms | 11812 | 320 | 6806.46 | 4637.34 | 0.190143 | 2.10399 | 10.1299 | 1.63999 | 0.00289695 | 2.43397e-05 | 1.32281e-06 | 1(Win) | true |
| Glaze | 1869.69 | 0.0295347 | 1341.12ms | 11812 | 4890 | 15483.9 | 6024.95 | 0.089746 | 2.71654 | 13.1162 | 2.6258 | 0.00204376 | 2.43245e-05 | 5.05534e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1783.46 | 0.0222654 | 1371.82ms | 11812 | 2560 | 5063.14 | 6316.25 | 0.117496 | 2.85384 | 13.4695 | 2.17224 | 0.0064347 | 5.35076e-05 | 2.70183e-05 | 3(Loss) | true |
| simdjson (reflection) | 1383.34 | 0.0640248 | 1556.17ms | 11812 | 2560 | 69586.9 | 8143.2 | 0.0955693 | 3.66339 | 14.0902 | 2.43439 | 0.00655362 | 3.80638e-05 | 9.95413e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1111.46 | 0.055878 | 1763.9ms | 11812 | 320 | 10263.4 | 10135.2 | 0.0404985 | 4.56829 | 16.8868 | 2.9837 | 0.00818474 | 1.71965e-05 | 2.64561e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2836.53 | 0.121599 | 1186.84ms | 11812 | 30 | 699.609 | 3971.33 | 0.0771605 | 1.80319 | 9.15179 | 1.41102 | 0.00143357 | 1.69319e-05 | 0 | 1(Win) | true |
| Glaze | 2115.13 | 0.0856768 | 1329.57ms | 11812 | 320 | 6662.69 | 5325.82 | 0.103515 | 2.40888 | 12.1478 | 2.40069 | 0.000491555 | 4.36526e-05 | 1.19053e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1952.85 | 0.0394 | 1366.15ms | 11812 | 2560 | 13223.3 | 5768.38 | 0.131757 | 2.59631 | 12.4903 | 1.94302 | 0.00577326 | 1.82217e-05 | 2.14956e-06 | 3(Loss) | true |
| simdjson (reflection) | 1475.69 | 0.0400437 | 1555.75ms | 11812 | 1280 | 11960 | 7633.56 | 0.0516162 | 3.44254 | 13.4767 | 2.287 | 0.00557147 | 1.76595e-05 | 2.51333e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1180.61 | 0.0335085 | 1751.42ms | 11812 | 2560 | 26169 | 9541.54 | 0.0263335 | 4.27723 | 16.0273 | 2.78886 | 0.00683538 | 2.06689e-05 | 1.45509e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15521.5 | 0.0924509 | 805.863ms | 11812 | 2560 | 1152.5 | 725.754 | 0.0473331 | 0.344039 | 1.63275 | 0.257873 | 8.53211e-05 | 1.37241e-05 | 1.885e-06 | 1(Win) | true |
| simdjson (reflection) | 9402.96 | 0.108197 | 851.167ms | 11812 | 160 | 268.824 | 1198.01 | 0.112291 | 0.556597 | 2.39426 | 0.359888 | 0.000303187 | 2.06358e-05 | 0 | 2(Loss) | true |
| Glaze | 4572.82 | 0.0837507 | 985.78ms | 11812 | 2560 | 10896.7 | 2463.43 | 0.0232359 | 1.1239 | 4.61277 | 0.713681 | 8.63462e-05 | 5.00352e-05 | 3.70386e-06 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16952.5 | 0.0590522 | 797.073ms | 11812 | 640 | 98.5445 | 664.492 | 0.110875 | 0.316845 | 1.58297 | 0.24636 | 8.51888e-05 | 5.95263e-06 | 1.32281e-07 | 1(Win) | true |
| simdjson (reflection) | 10148.9 | 0.0609988 | 842.599ms | 11812 | 2560 | 1173.52 | 1109.95 | 0.0762158 | 0.51873 | 2.34456 | 0.348713 | 0.00011019 | 1.67335e-05 | 6.58097e-06 | 2(Loss) | true |
| Glaze | 5022.4 | 0.102304 | 961.24ms | 11812 | 4890 | 25746.7 | 2242.91 | 0.0119402 | 1.02475 | 4.35083 | 0.655943 | 9.40086e-05 | 2.3026e-05 | 5.0034e-06 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3396.38 | 0.0925472 | 1453.49ms | 25388 | 30 | 1305.79 | 7128.73 | 0.0636329 | 1.49749 | 7.1546 | 1.06797 | 0.00284124 | 3.93887e-06 | 0 | 1(Win) | true |
| Jsonifier | 3211.88 | 0.0855734 | 1495.13ms | 25388 | 80 | 3328.94 | 7538.23 | 0.055685 | 1.58352 | 7.24638 | 1.40068 | 0.0045233 | 1.03395e-05 | 3.44651e-06 | 2(Loss) | true |
| simdjson (reflection) | 2707.6 | 0.02029 | 1642.13ms | 25388 | 4890 | 16097.6 | 8942.18 | 0.0153308 | 1.8479 | 7.24355 | 1.15868 | 0.00308005 | 1.08661e-05 | 2.92395e-06 | 3(Loss) | true |
| Glaze | 2372.5 | 0.0208255 | 1758.89ms | 25388 | 4890 | 22087.4 | 10205.2 | 0.055285 | 2.13758 | 9.44553 | 1.81576 | 0.00609695 | 1.35726e-05 | 2.67424e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2227.62 | 0.0473595 | 1852.95ms | 25388 | 640 | 16957.7 | 10868.9 | 0.0316599 | 2.27725 | 8.57211 | 1.41996 | 0.00359471 | 9.78563e-06 | 2.27716e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3684.82 | 0.0314783 | 1453.48ms | 25388 | 320 | 1368.98 | 6570.72 | 0.0814506 | 1.3818 | 6.70817 | 0.963408 | 0.00266686 | 6.03139e-06 | 0 | 1(Win) | true |
| Jsonifier | 3463.96 | 0.0694741 | 1486.78ms | 25388 | 640 | 15091.7 | 6989.66 | 0.0415294 | 1.46787 | 6.80026 | 1.29624 | 0.00434316 | 6.83148e-06 | 1.84634e-07 | 2(Loss) | true |
| simdjson (reflection) | 2877.2 | 0.0381412 | 1642.79ms | 25388 | 2560 | 26372.1 | 8415.08 | 0.186709 | 1.75123 | 6.96672 | 1.09193 | 0.0028432 | 1.64786e-05 | 6.87763e-06 | 3(Loss) | true |
| Glaze | 2556.7 | 0.050924 | 1744.1ms | 25388 | 1280 | 29768 | 9469.96 | 0.0525399 | 1.96996 | 8.89747 | 1.69092 | 0.00526608 | 7.97005e-06 | 9.23172e-08 | 4(Loss) | true |
| simdjson (ondemand) | 2363.48 | 0.101999 | 1825.47ms | 25388 | 80 | 8734.43 | 10244.1 | 0.00463658 | 2.14903 | 8.18205 | 1.33161 | 0.00313485 | 7.87774e-06 | 0 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20936.2 | 0.0509746 | 879.607ms | 31235 | 320 | 168.324 | 1422.8 | 0.0241659 | 0.248969 | 0.670018 | 0.0973907 | 3.20154e-05 | 2.5012e-06 | 0 | 1(Win) | true |
| Glaze | 6638.89 | 0.0765625 | 1191.28ms | 31235 | 2560 | 30211 | 4486.9 | 0.0151025 | 0.76239 | 3.74887 | 0.630287 | 0.000701312 | 1.02299e-05 | 2.20106e-06 | 2(Loss) | true |
| simdjson (reflection) | 540.132 | 0.125027 | 6275.35ms | 31235 | 4890 | 2.32486e+07 | 55149.5 | 0.0724309 | 9.25136 | 38.4139 | 7.08252 | 0.0124912 | 7.76618e-05 | 3.32069e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21957.1 | 0.0484985 | 871.14ms | 31235 | 4890 | 2116.9 | 1356.65 | 0.0869637 | 0.237137 | 0.652025 | 0.0931648 | 3.21987e-05 | 4.4062e-06 | 6.87447e-07 | 1(Win) | true |
| Glaze | 7459.29 | 0.154565 | 1138.99ms | 31235 | 1280 | 48766.5 | 3993.41 | 0.163479 | 0.684475 | 3.62862 | 0.603938 | 0.000685179 | 5.57768e-06 | 8.00384e-07 | 2(Loss) | true |
| simdjson (reflection) | 535.198 | 0.131946 | 6336.91ms | 31235 | 4890 | 2.63727e+07 | 55657.9 | 0.0946827 | 9.29676 | 38.4564 | 7.09233 | 0.0124735 | 0.000108839 | 6.47706e-05 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3202.92 | 0.0665743 | 3976.92ms | 108313 | 320 | 147514 | 32250.3 | 0.0968465 | 1.57052 | 7.09962 | 1.51102 | 0.00220189 | 6.86667e-06 | 3.57759e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2241.56 | 0.0566719 | 5365.36ms | 108313 | 160 | 109123 | 46081.9 | 0.00212941 | 2.25589 | 9.9924 | 1.84466 | 0.00279306 | 7.03978e-06 | 3.17367e-06 | 2(Loss) | true |
| Glaze | 2221.26 | 0.0436887 | 5417.32ms | 108313 | 1280 | 528336 | 46503 | 0.00793358 | 2.25469 | 10.0688 | 1.92994 | 0.0030277 | 1.05957e-05 | 4.28446e-06 | 3(Loss) | true |
| simdjson (reflection) | 1633.01 | 0.0282779 | 7097.06ms | 108313 | 640 | 204767 | 63254.6 | 0.0324365 | 3.03981 | 13.3394 | 2.06294 | 0.00227385 | 1.00115e-05 | 5.61163e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1624.96 | 0.0479482 | 7093.13ms | 108313 | 640 | 594564 | 63567.8 | 0.224045 | 3.0712 | 14.1279 | 2.39375 | 0.00308683 | 1.53923e-05 | 5.90015e-06 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3852.94 | 0.0262704 | 3610.28ms | 108313 | 2560 | 126984 | 26809.5 | 0.00998701 | 1.30385 | 6.35418 | 1.33587 | 0.00194118 | 3.08351e-06 | 3.93103e-07 | 1(Win) | true |
| Jsonifier (two-stage) | 2528.91 | 0.0511045 | 5066.11ms | 108313 | 160 | 69716.2 | 40845.8 | 0.03093 | 1.99948 | 9.24752 | 1.66962 | 0.00256606 | 1.17137e-05 | 7.15519e-06 | 2(Loss) | true |
| Glaze | 2426.79 | 0.0739826 | 5162.36ms | 108313 | 320 | 317327 | 42564.6 | 0.136847 | 2.04546 | 9.37946 | 1.76707 | 0.00283524 | 3.51989e-06 | 7.78992e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1772.25 | 0.0624125 | 6774.51ms | 108313 | 320 | 423451 | 58284.7 | 0.00637536 | 2.82657 | 13.4414 | 2.23515 | 0.00291848 | 4.5874e-06 | 1.64454e-06 | 4(Loss) | true |
| simdjson (reflection) | 1683.68 | 0.0110854 | 7071.62ms | 108313 | 4890 | 226181 | 61350.9 | 0.0111312 | 2.94728 | 13.0284 | 1.98967 | 0.0021014 | 8.50372e-06 | 3.46266e-06 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19975.2 | 0.0312639 | 1257.73ms | 108313 | 1280 | 3345.61 | 5171.18 | 0.00977377 | 0.25504 | 1.09397 | 0.288867 | 0.000118299 | 4.23397e-06 | 1.08915e-06 | 1(Win) | true |
| simdjson (reflection) | 15426.3 | 0.0764546 | 1416.87ms | 108313 | 320 | 8386.78 | 6696.06 | 0.00826114 | 0.329585 | 1.49424 | 0.1938 | 0.000185314 | 2.6832e-06 | 1.15406e-06 | 2(Loss) | true |
| Glaze | 5600 | 0.05642 | 2599.1ms | 108313 | 4890 | 529616 | 18445.6 | 0.125627 | 0.893465 | 3.01741 | 0.39721 | 0.000273945 | 5.04295e-06 | 2.3827e-06 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20191.8 | 0.0206978 | 1253.19ms | 108313 | 2560 | 2870.12 | 5115.71 | 0.118619 | 0.252399 | 1.08874 | 0.287703 | 0.000114 | 4.82182e-06 | 1.94387e-06 | 1(Win) | true |
| simdjson (reflection) | 15676.3 | 0.0241038 | 1407.58ms | 108313 | 4890 | 12335.4 | 6589.27 | 0.11658 | 0.323546 | 1.48913 | 0.192645 | 0.000194551 | 4.20844e-06 | 1.78986e-06 | 2(Loss) | true |
| Glaze | 6258.09 | 0.0670915 | 2407.14ms | 108313 | 4890 | 599683 | 16505.9 | 0.0017877 | 0.805516 | 2.97166 | 0.386768 | 0.000273235 | 5.78495e-06 | 3.02275e-06 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3298.3 | 0.0380181 | 6073.67ms | 183677 | 2560 | 1.04363e+06 | 53108.5 | 0.0550282 | 1.50418 | 6.65087 | 1.13675 | 0.001603 | 1.04612e-05 | 6.37796e-06 | 1(Win) | true |
| Jsonifier | 2916.56 | 0.0313311 | 6767.52ms | 183677 | 640 | 226621 | 60059.9 | 0.0663506 | 1.70505 | 6.77817 | 1.54382 | 0.00213473 | 9.41701e-06 | 5.50389e-06 | 2(Loss) | true |
| simdjson (reflection) | 2630.16 | 0.0339536 | 7436.22ms | 183677 | 1280 | 654527 | 66599.9 | 0.101512 | 1.89708 | 8.4386 | 1.23784 | 0.00126616 | 1.85703e-05 | 1.2254e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2585.48 | 0.0348539 | 7532.26ms | 183677 | 4890 | 2.72671e+06 | 67750.8 | 0.0782273 | 1.91916 | 8.88126 | 1.4269 | 0.00182994 | 2.21158e-05 | 1.32234e-05 | 4(Loss) | true |
| Glaze | 2522.87 | 0.0115454 | 7687.82ms | 183677 | 4890 | 314232 | 69432 | 0.119472 | 1.96791 | 8.75598 | 1.71574 | 0.00319318 | 1.66125e-05 | 1.07128e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3696.13 | 0.0467906 | 5688.58ms | 183677 | 80 | 39339 | 47392.3 | 0.0994688 | 1.34288 | 6.20993 | 1.03315 | 0.00146126 | 3.47077e-06 | 6.80542e-07 | 1(Win) | true |
| Jsonifier | 3231.06 | 0.0943179 | 6395.4ms | 183677 | 80 | 209169 | 54213.7 | 0.0513444 | 1.53895 | 6.3364 | 1.43997 | 0.00201216 | 1.70136e-06 | 2.72217e-07 | 2(Loss) | true |
| simdjson (ondemand) | 2784.64 | 0.107287 | 7222.22ms | 183677 | 1280 | 5.83009e+06 | 62905 | 0.0582024 | 1.7806 | 8.51056 | 1.34102 | 0.00172736 | 2.10968e-05 | 1.42106e-05 | 3(Loss) | true |
| Glaze | 2702.37 | 0.0415073 | 7448.18ms | 183677 | 320 | 231643 | 64820.1 | 0.0365471 | 1.83727 | 8.36661 | 1.62376 | 0.00292305 | 4.98497e-06 | 2.50099e-06 | 4(Loss) | true |
| simdjson (reflection) | 2694.1 | 0.0333976 | 7454.72ms | 183677 | 1280 | 603564 | 65019.2 | 0.049851 | 1.85766 | 8.27981 | 1.19996 | 0.00140054 | 5.40181e-06 | 2.51801e-06 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26060.8 | 0.0117909 | 1522.75ms | 213963 | 4890 | 4167.75 | 7829.81 | 0.0338075 | 0.19497 | 0.625431 | 0.146184 | 5.54355e-05 | 1.63914e-06 | 2.16959e-07 | 1(Win) | true |
| Glaze | 5516.4 | 0.0994777 | 4462.64ms | 213963 | 1280 | 1.73312e+06 | 36989.9 | 0.0326229 | 0.901284 | 3.59323 | 0.575044 | 0.000545213 | 3.13649e-06 | 5.87864e-07 | 2(Loss) | true |
| simdjson (reflection) | 469.252 | 0.870394 | 5636.65ms | 213963 | 160 | 2.29202e+09 | 434844 | 0.553885 | 10.515 | 41.6028 | 8.47585 | 0.0355922 | 0.196487 | 4.60068e-05 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26221.3 | 0.0214638 | 1521.16ms | 213963 | 1280 | 3571.04 | 7781.89 | 0.0413048 | 0.194029 | 0.623014 | 0.145642 | 5.72967e-05 | 2.09586e-06 | 5.80562e-07 | 1(Win) | true |
| Glaze | 6434.92 | 0.0666104 | 3930.29ms | 213963 | 4890 | 2.18164e+06 | 31710 | 0.081286 | 0.770032 | 3.56743 | 0.569169 | 0.000535387 | 3.01927e-06 | 1.16604e-06 | 2(Loss) | true |
| simdjson (reflection) | 464.269 | 0.495163 | 5663.87ms | 213963 | 320 | 1.5156e+09 | 439511 | 0.0535776 | 10.6211 | 41.6464 | 8.48743 | 0.0361814 | 0.200803 | 0.00252481 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 840.263 | 0.324847 | 6462.08ms | 1834197 | 160 | 7.31712e+09 | 2.08176e+06 | 0.171583 | 5.96528 | 25.5055 | 5.55485 | 0.0300422 | 0.0820092 | 0.00582143 | 1(Win) | true |
| Jsonifier (two-stage) | 732.111 | 0.480142 | 7539.99ms | 1834197 | 30 | 3.9482e+09 | 2.38929e+06 | 1.15516 | 6.82477 | 28.8111 | 5.98128 | 0.0365154 | 0.144867 | 0.0106664 | 2(Loss) | true |
| Glaze | 640.886 | 0.157283 | 8540.4ms | 1834197 | 30 | 5.5286e+08 | 2.72939e+06 | 0.00719157 | 7.74991 | 32.3723 | 6.32381 | 0.0345905 | 0.0832507 | 0.0157502 | 3(Loss) | true |
| simdjson (reflection) | 623.039 | 0.286077 | 8721.64ms | 1834197 | 80 | 5.16081e+09 | 2.80757e+06 | 0.5736 | 7.94087 | 34.7418 | 6.46838 | 0.0363099 | 0.136221 | 0.0104938 | 4(Loss) | true |
| simdjson (ondemand) | 567.36 | 0.502902 | 9680.71ms | 1834197 | 40 | 9.61613e+09 | 3.0831e+06 | 0.0753169 | 8.70927 | 35.0045 | 6.11668 | 0.0430106 | 0.147659 | 0.0391509 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 939.701 | 0.2203 | 6452.14ms | 1834197 | 160 | 2.69068e+09 | 1.86147e+06 | 0.0226838 | 5.3181 | 22.5003 | 4.85436 | 0.0294247 | 0.0554567 | 0.00449072 | 1(Win) | true |
| Jsonifier (two-stage) | 786.634 | 0.276879 | 7651.87ms | 1834197 | 160 | 6.06524e+09 | 2.22369e+06 | 0.0614278 | 6.33225 | 25.8099 | 5.28155 | 0.035719 | 0.118527 | 0.0370753 | 2(Loss) | true |
| Glaze | 707.721 | 0.124959 | 8386.2ms | 1834197 | 30 | 2.86172e+08 | 2.47163e+06 | 0.131606 | 7.05302 | 29.3656 | 5.62365 | 0.033057 | 0.0595331 | 0.0133913 | 3(Loss) | true |
| simdjson (reflection) | 696.582 | 0.0842825 | 8439.36ms | 1834197 | 30 | 1.34383e+08 | 2.51116e+06 | 0.0356988 | 7.13936 | 31.7131 | 5.75221 | 0.0316802 | 0.112122 | 2.50609e-05 | 4(Loss) | true |
| simdjson (ondemand) | 639.888 | 0.151651 | 9295.17ms | 1834197 | 40 | 6.87438e+08 | 2.73364e+06 | 0.418859 | 7.78041 | 31.9847 | 5.41543 | 0.03838 | 0.118616 | 0.0329722 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1305.98 | 0.306917 | 8512.94ms | 1834197 | 160 | 2.70384e+09 | 1.3394e+06 | 0.300014 | 3.86599 | 13.1332 | 0.799078 | 0.00143739 | 0.0597599 | 1.06518e-05 | 1(Win) | true |
| Glaze | 980.531 | 0.296996 | 5557.75ms | 1833577 | 160 | 4.48846e+09 | 1.78336e+06 | 0.146764 | 5.1513 | 16.0488 | 1.05286 | 0.00100974 | 0.0495696 | 1.13065e-05 | 2(Loss) | true |
| simdjson (reflection) | 878.253 | 0.10539 | 6496.71ms | 1922245 | 30 | 1.45177e+08 | 2.08732e+06 | 0.413088 | 5.71085 | 18.1523 | 2.01851 | 0.0264218 | 0.0502048 | 8.28892e-06 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1302.28 | 0.253458 | 8512.92ms | 1834197 | 320 | 3.70889e+09 | 1.3432e+06 | 0.062599 | 3.87333 | 13.133 | 0.799039 | 0.00145293 | 0.059338 | 0.000212193 | 1(Win) | true |
| Glaze | 983.238 | 0.316662 | 5542.37ms | 1833577 | 40 | 1.26863e+09 | 1.77845e+06 | 0.106239 | 5.13823 | 16.048 | 1.05269 | 0.00100319 | 0.0495132 | 8.11256e-06 | 2(Loss) | true |
| simdjson (reflection) | 880.429 | 0.220626 | 6484.77ms | 1922245 | 160 | 3.37647e+09 | 2.08216e+06 | 0.183004 | 5.7322 | 18.1521 | 2.01847 | 0.0264412 | 0.0498814 | 1.24789e-05 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2577.4 | 0.644533 | 8441.58ms | 7351818 | 40 | 1.22964e+10 | 2.72028e+06 | 0.124103 | 1.91504 | 8.12466 | 1.53488 | 0.0105165 | 0.0608782 | 0.000122147 | 1(Win) | true |
| Jsonifier | 2486.68 | 0.27855 | 8761.65ms | 7351818 | 160 | 9.86911e+09 | 2.81952e+06 | 0.459337 | 1.9887 | 8.6837 | 2.00014 | 0.00768978 | 0.0339134 | 7.8087e-05 | 2(Loss) | true |
| simdjson (reflection) | 2259.47 | 0.0476513 | 9630.21ms | 7351818 | 30 | 6.55914e+07 | 3.10304e+06 | 0.278841 | 2.19242 | 9.6839 | 1.6517 | 0.00898285 | 0.0584989 | 0.00307576 | 3(Loss) | true |
| simdjson (ondemand) | 2135.62 | 0.290298 | 10200.3ms | 7351818 | 160 | 1.45328e+10 | 3.283e+06 | 0.678878 | 2.3212 | 9.74916 | 1.56369 | 0.0105142 | 0.0613554 | 0.00119176 | 4(Loss) | true |
| Glaze | 2024.66 | 0.356204 | 5194.8ms | 7351818 | 80 | 1.21723e+10 | 3.46292e+06 | 0.0876719 | 2.44901 | 11.2408 | 2.23983 | 0.00902624 | 0.0336528 | 4.73199e-05 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2822.74 | 0.303293 | 8407.98ms | 7351818 | 160 | 9.08013e+09 | 2.48384e+06 | 0.115452 | 1.75744 | 7.37608 | 1.36048 | 0.0102551 | 0.0542644 | 5.73158e-05 | 1(Win) | true |
| Jsonifier | 2710.39 | 0.100562 | 8772.55ms | 7351818 | 30 | 2.03008e+08 | 2.5868e+06 | 0.480046 | 1.83066 | 7.93404 | 1.82539 | 0.00752295 | 0.0272835 | 3.02329e-05 | 2(Loss) | true |
| simdjson (reflection) | 2473.92 | 0.298483 | 9423.06ms | 7351818 | 160 | 1.14493e+10 | 2.83407e+06 | 0.0971393 | 1.99998 | 8.92781 | 1.47286 | 0.00779215 | 0.0519889 | 0.000506923 | 3(Loss) | true |
| simdjson (ondemand) | 2337.42 | 0.2958 | 10071ms | 7351818 | 160 | 1.2596e+10 | 2.99956e+06 | 0.0822867 | 2.11884 | 8.9951 | 1.38863 | 0.0093837 | 0.0536911 | 0.000258127 | 4(Loss) | true |
| Glaze | 2156.49 | 0.633201 | 5232.07ms | 7351818 | 30 | 1.27145e+10 | 3.25123e+06 | 0.0981208 | 2.29532 | 10.4903 | 2.06513 | 0.008684 | 0.0276494 | 6.39071e-05 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6401.18 | 0.0236914 | 9442.08ms | 9930848 | 80 | 9.82938e+06 | 1.47954e+06 | 0.0199299 | 0.789123 | 2.51817 | 0.147587 | 0.00026464 | 0.0250083 | 1.52152e-05 | 1(Win) | true |
| Glaze | 3686.39 | 0.262899 | 8043.01ms | 9930228 | 30 | 1.36841e+09 | 2.56897e+06 | 0.0109291 | 1.36458 | 4.41555 | 0.474366 | 0.000788203 | 0.0417348 | 0.000895189 | 2(Loss) | true |
| simdjson (reflection) | 278.813 | 0.168714 | 10327.7ms | 10018896 | 30 | 1.00285e+11 | 3.42694e+07 | 0.0747127 | 13.1935 | 38.726 | 5.81007 | 0.0262429 | 0.267742 | 0.0966318 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6329.8 | 0.459474 | 9464.64ms | 9930848 | 160 | 7.56197e+09 | 1.49622e+06 | 0.0243911 | 0.794155 | 2.51813 | 0.14758 | 0.000258412 | 0.0249969 | 1.48256e-05 | 1(Win) | true |
| Glaze | 4031.26 | 0.450624 | 7304.95ms | 9930228 | 80 | 8.96511e+09 | 2.34919e+06 | 0.137047 | 1.24367 | 4.4153 | 0.474313 | 0.000790654 | 0.0224416 | 5.3171e-05 | 2(Loss) | true |
| simdjson (reflection) | 308.568 | 1.73355 | 9325.8ms | 10018896 | 30 | 8.64434e+12 | 3.09649e+07 | 0.30724 | 13.0329 | 38.7482 | 5.8157 | 0.0257823 | 0.291433 | 0.124182 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 850.76 | 0.25703 | 6401.6ms | 1834197 | 160 | 4.46853e+09 | 2.05607e+06 | 0.0402424 | 5.83035 | 25.0662 | 5.41578 | 0.0313741 | 0.0841529 | 1.55177e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 735.028 | 0.319527 | 7434.44ms | 1834197 | 160 | 9.25165e+09 | 2.37981e+06 | 0.374554 | 6.77368 | 28.374 | 5.86149 | 0.0376103 | 0.146008 | 0.000917251 | 2(Loss) | true |
| Glaze | 651.784 | 0.113109 | 8407.04ms | 1834197 | 30 | 2.7644e+08 | 2.68375e+06 | 0.153043 | 7.62371 | 32.3386 | 6.31657 | 0.0346938 | 0.0832496 | 9.84264e-05 | 3(Loss) | true |
| simdjson (reflection) | 612.298 | 0.24296 | 8894.44ms | 1834197 | 160 | 7.70826e+09 | 2.85682e+06 | 0.0157066 | 8.11802 | 34.7784 | 6.50821 | 0.0370435 | 0.136706 | 5.45232e-05 | 4(Loss) | true |
| simdjson (ondemand) | 581.068 | 0.661246 | 9370.66ms | 1834197 | 40 | 1.58498e+10 | 3.01036e+06 | 0.0546327 | 8.52316 | 34.4872 | 6.17598 | 0.044365 | 0.147937 | 5.40018e-05 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 963.985 | 0.102635 | 6405.69ms | 1834197 | 40 | 1.38739e+08 | 1.81458e+06 | 0.20022 | 5.14321 | 22.0916 | 4.72653 | 0.0303275 | 0.0574816 | 5.67278e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 810.354 | 0.344 | 7404.18ms | 1834197 | 160 | 8.82224e+09 | 2.1586e+06 | 0.767144 | 6.11675 | 25.3976 | 5.17157 | 0.0366808 | 0.119322 | 2.65511e-05 | 2(Loss) | true |
| Glaze | 712.91 | 0.0532466 | 8399.5ms | 1834197 | 30 | 5.12069e+07 | 2.45364e+06 | 0.0222273 | 6.94963 | 29.358 | 5.62481 | 0.0334629 | 0.0593953 | 4.55785e-05 | 3(Loss) | true |
| simdjson (reflection) | 683.162 | 0.290402 | 8642.99ms | 1834197 | 160 | 8.84634e+09 | 2.56049e+06 | 0.0663569 | 7.25704 | 31.7657 | 5.80433 | 0.0318554 | 0.112516 | 6.71581e-05 | 4(Loss) | true |
| simdjson (ondemand) | 646.287 | 0.10602 | 9213.04ms | 1834197 | 30 | 2.47022e+08 | 2.70658e+06 | 0.173782 | 7.66483 | 31.492 | 5.48289 | 0.0400184 | 0.118598 | 2.20442e-05 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1271.77 | 0.0393624 | 8767.79ms | 1834197 | 40 | 1.17247e+07 | 1.37543e+06 | 0.247054 | 3.9718 | 13.1198 | 0.79908 | 0.00297956 | 0.0620752 | 0.000381966 | 1(Win) | true |
| Glaze | 950.208 | 0.36294 | 5734.69ms | 1833577 | 160 | 7.13758e+09 | 1.84027e+06 | 0.301791 | 5.28129 | 16.0436 | 1.0529 | 0.000994814 | 0.0765909 | 8.10233e-06 | 2(Loss) | true |
| simdjson (reflection) | 873.488 | 0.618778 | 6485.49ms | 1922245 | 40 | 6.7458e+09 | 2.09871e+06 | 0.0545447 | 5.70923 | 18.1621 | 2.01852 | 0.0244603 | 0.0518567 | 4.33608e-05 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1273.32 | 0.0463377 | 8786.69ms | 1834197 | 40 | 1.62087e+07 | 1.37375e+06 | 0.00335406 | 3.96802 | 13.1196 | 0.79904 | 0.00299308 | 0.0620849 | 1.0277e-05 | 1(Win) | true |
| Glaze | 995.633 | 0.527881 | 5494.57ms | 1833577 | 80 | 6.87642e+09 | 1.75631e+06 | 0.126733 | 5.06741 | 16.0427 | 1.0527 | 0.000993223 | 0.0496552 | 1.1453e-05 | 2(Loss) | true |
| simdjson (reflection) | 890.26 | 0.0357027 | 6439.84ms | 1922245 | 30 | 1.62146e+07 | 2.05917e+06 | 0.0262464 | 5.6731 | 18.1619 | 2.01848 | 0.0244928 | 0.0517997 | 1.36299e-05 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2596.25 | 0.108168 | 8466.79ms | 7351818 | 40 | 3.4131e+08 | 2.70052e+06 | 0.253558 | 1.90076 | 8.01532 | 1.50501 | 0.0106402 | 0.0614285 | 7.10607e-05 | 1(Win) | true |
| Jsonifier | 2502.84 | 0.414903 | 8720.31ms | 7351818 | 80 | 1.0807e+10 | 2.80131e+06 | 0.0127303 | 1.97762 | 8.58053 | 1.96493 | 0.00777993 | 0.0342195 | 1.97553e-05 | 2(Loss) | true |
| simdjson (reflection) | 2218.92 | 0.155504 | 9855.34ms | 7351818 | 80 | 1.93143e+09 | 3.15975e+06 | 0.024511 | 2.24074 | 9.69253 | 1.66145 | 0.0091298 | 0.0586074 | 0.00283846 | 3(Loss) | true |
| simdjson (ondemand) | 2104.81 | 0.758559 | 5002.04ms | 7351818 | 30 | 1.91541e+10 | 3.33105e+06 | 0.668475 | 2.35046 | 9.62086 | 1.57883 | 0.0108895 | 0.0613415 | 0.00113513 | 4(Loss) | true |
| Glaze | 2020.03 | 0.400795 | 5222.95ms | 7351818 | 40 | 7.74069e+09 | 3.47086e+06 | 0.0244526 | 2.44998 | 11.2349 | 2.23772 | 0.00924585 | 0.0337894 | 1.78629e-05 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2800.94 | 0.727787 | 8479.32ms | 7351818 | 40 | 1.32755e+10 | 2.50317e+06 | 0.10259 | 1.76006 | 7.27344 | 1.33306 | 0.0104021 | 0.0549108 | 0.00226643 | 1(Win) | true |
| Jsonifier | 2741.39 | 0.34741 | 8702.54ms | 7351818 | 80 | 6.31574e+09 | 2.55755e+06 | 0.18825 | 1.80813 | 7.83795 | 1.79286 | 0.00759431 | 0.0275934 | 1.81299e-05 | 2(Loss) | true |
| simdjson (reflection) | 2463.45 | 0.0739876 | 9599.39ms | 7351818 | 80 | 3.5474e+08 | 2.84611e+06 | 0.0508664 | 2.01191 | 8.94094 | 1.48587 | 0.00792208 | 0.0521861 | 0.000172711 | 3(Loss) | true |
| simdjson (ondemand) | 2324.69 | 0.107818 | 10125.7ms | 7351818 | 160 | 1.69187e+09 | 3.01599e+06 | 0.00287915 | 2.14513 | 8.87269 | 1.40567 | 0.00977511 | 0.0536178 | 0.0018028 | 4(Loss) | true |
| Glaze | 2167.01 | 0.633574 | 5221.49ms | 7351818 | 30 | 1.26061e+10 | 3.23544e+06 | 0.164917 | 2.28681 | 10.4918 | 2.06539 | 0.00880772 | 0.027786 | 1.62499e-05 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6296.28 | 0.0895578 | 9566.85ms | 9930848 | 80 | 1.45178e+08 | 1.50419e+06 | 0.279354 | 0.797921 | 2.51581 | 0.147546 | 0.000455369 | 0.0250551 | 0.000103356 | 1(Win) | true |
| Glaze | 3100.74 | 0.161113 | 9738.88ms | 9930228 | 160 | 3.87407e+09 | 3.05418e+06 | 0.888647 | 1.61473 | 4.41436 | 0.474332 | 0.000747895 | 0.0757334 | 0.010646 | 2(Loss) | true |
| simdjson (reflection) | 384.6 | 0.331863 | 7360.63ms | 10018896 | 30 | 2.03919e+11 | 2.48434e+07 | 2.39656 | 13.0854 | 38.7063 | 5.81134 | 0.022614 | 0.313786 | 0.174933 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6296.08 | 0.144551 | 9564.15ms | 9930848 | 80 | 3.78236e+08 | 1.50424e+06 | 0.0275753 | 0.802103 | 2.51577 | 0.147539 | 0.000453426 | 0.0250556 | 0.000927892 | 1(Win) | true |
| Glaze | 4065.66 | 0.114195 | 7280.5ms | 9930228 | 160 | 1.13207e+09 | 2.32932e+06 | 0.0095778 | 1.23538 | 4.414 | 0.474254 | 0.000773152 | 0.0224146 | 0.000659096 | 2(Loss) | true |
| simdjson (reflection) | 337.05 | 1.44325 | 8499.08ms | 10018896 | 30 | 5.02178e+12 | 2.83482e+07 | 0.756754 | 13.0403 | 38.7295 | 5.81348 | 0.02332 | 0.289723 | 0.156223 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1170.31 | 0.0390522 | 9769.19ms | 461466 | 320 | 6.90114e+06 | 376045 | 0.0264749 | 4.24071 | 17.7273 | 3.22181 | 0.0195092 | 0.0424708 | 0.0001098 | 1(Win) | true |
| simdjson (reflection) | 1109.31 | 0.137903 | 5146.75ms | 461466 | 320 | 9.57786e+07 | 396721 | 0.0639288 | 4.44248 | 18.598 | 3.3051 | 0.0112303 | 0.0813799 | 6.41366e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1087.17 | 0.0983644 | 5248.17ms | 461466 | 30 | 4.75646e+06 | 404803 | 0.0408679 | 4.55901 | 19.0264 | 3.44721 | 0.0230413 | 0.0864332 | 0.000168232 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1050.42 | 0.0737919 | 5424.61ms | 461466 | 640 | 6.11717e+07 | 418964 | 0.103104 | 4.70984 | 19.7308 | 3.59259 | 0.0114141 | 0.0867513 | 6.67743e-05 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1046.73 | 0.206214 | 5455.15ms | 461466 | 640 | 4.81089e+08 | 420440 | 0.11375 | 4.73494 | 20.1568 | 3.94231 | 0.0242645 | 0.0354133 | 0.000149351 | 4(Tie) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1588.05 | 0.025151 | 8981.13ms | 461466 | 320 | 1.55457e+06 | 277124 | 0.0220813 | 3.12273 | 13.5302 | 2.29446 | 0.0170413 | 0.00733946 | 3.47669e-05 | 1(Win) | true |
| simdjson (reflection) | 1461.13 | 0.0926741 | 9711.49ms | 461466 | 1280 | 9.97304e+07 | 301197 | 0.206732 | 3.38638 | 14.9861 | 2.47355 | 0.00480904 | 0.0384716 | 7.24474e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1449.04 | 0.0516225 | 9658.78ms | 461466 | 1280 | 3.14635e+07 | 303710 | 0.0708192 | 3.41699 | 14.8392 | 2.52234 | 0.020268 | 0.0283002 | 5.44935e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1418.27 | 0.0975495 | 9715.21ms | 461466 | 1280 | 1.17279e+08 | 310299 | 0.0217433 | 3.49376 | 15.7479 | 2.69299 | 0.00398299 | 0.0305852 | 2.3126e-05 | 4(Loss) | true |
| Glaze | 1321.23 | 0.205859 | 5190.41ms | 461466 | 640 | 3.00915e+08 | 333091 | 0.0266496 | 3.75948 | 16.3205 | 3.08164 | 0.0216302 | 0.0115983 | 0.000103769 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17102.5 | 0.106886 | 3428.79ms | 461466 | 30 | 22694.7 | 25732.4 | 0.0538589 | 0.296139 | 1.43343 | 0.226608 | 0.000284022 | 0.0135774 | 2.99047e-05 | 1(Win) | true |
| simdjson (reflection) | 11217.1 | 0.107488 | 4723.83ms | 461466 | 2560 | 4.5528e+06 | 39233.7 | 0.130083 | 0.446313 | 2.24062 | 0.318281 | 0.00197491 | 0.0123655 | 2.4312e-05 | 2(Loss) | true |
| Glaze | 4508.78 | 0.339401 | 5415.41ms | 461466 | 320 | 3.51187e+07 | 97606.9 | 0.0626612 | 1.09737 | 4.65991 | 0.714374 | 0.00921849 | 0.0438323 | 9.04725e-06 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17068.4 | 0.199711 | 3381.61ms | 461466 | 30 | 79546.5 | 25783.9 | 0.182855 | 0.296033 | 1.43441 | 0.226342 | 0.000228691 | 0.0132037 | 3.62612e-05 | 1(Win) | true |
| simdjson (reflection) | 11145.4 | 0.0205753 | 4708.86ms | 461466 | 2560 | 168974 | 39486.2 | 0.342682 | 0.446321 | 2.23952 | 0.31803 | 0.00195849 | 0.00734834 | 1.97452e-05 | 2(Loss) | true |
| Glaze | 5134.14 | 0.0487644 | 9378.74ms | 461466 | 4890 | 8.54395e+06 | 85718.1 | 0.0575211 | 0.970638 | 4.64554 | 0.711034 | 0.009134 | 0.00946174 | 9.55725e-05 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1691.36 | 0.051848 | 5325.71ms | 728486 | 160 | 7.25694e+06 | 410757 | 0.104116 | 2.931 | 12.3393 | 2.11581 | 0.00737466 | 0.067709 | 5.63068e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1619.4 | 0.0960231 | 5543.81ms | 728486 | 640 | 1.08609e+08 | 429010 | 0.16374 | 3.05841 | 12.6036 | 2.19843 | 0.0154957 | 0.0773204 | 5.2356e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1568.45 | 0.118192 | 5743.54ms | 728486 | 640 | 1.75411e+08 | 442945 | 0.0626858 | 3.14649 | 13.0635 | 2.29957 | 0.00791847 | 0.0746505 | 9.96888e-05 | 3(Loss) | true |
| Jsonifier | 1524.89 | 0.115769 | 5913.8ms | 728486 | 30 | 8.34588e+06 | 455598 | 0.00122185 | 3.30801 | 13.3374 | 2.59283 | 0.0128454 | 0.0407815 | 0.00011906 | 4(Loss) | true |
| Glaze | 1407.48 | 0.0845761 | 6374.52ms | 728486 | 320 | 5.57706e+07 | 493605 | 0.0665035 | 3.54435 | 15.2072 | 2.98348 | 0.0146698 | 0.0323716 | 0.000115638 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2174.35 | 0.111383 | 5003.11ms | 728486 | 640 | 8.10592e+07 | 319516 | 0.0421251 | 2.27192 | 10.0547 | 1.58974 | 0.00325828 | 0.040397 | 4.94176e-05 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2113.04 | 0.144073 | 5164.25ms | 728486 | 640 | 1.43605e+08 | 328786 | 0.00536081 | 2.33353 | 9.95097 | 1.61266 | 0.0135782 | 0.0342449 | 6.32519e-06 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2111 | 0.148154 | 5068ms | 728486 | 320 | 7.60756e+07 | 329105 | 0.287404 | 2.32977 | 10.536 | 1.72844 | 0.0027779 | 0.0330144 | 2.46702e-05 | 2(Tie) | true |
| Jsonifier | 1939.37 | 0.0537533 | 5502.01ms | 728486 | 320 | 1.18654e+07 | 358229 | 0.0394625 | 2.57496 | 10.6798 | 2.00591 | 0.0112109 | 0.00912617 | 9.81917e-05 | 4(Loss) | true |
| Glaze | 1723.74 | 0.111721 | 6147.81ms | 728486 | 160 | 3.24405e+07 | 403040 | 0.203941 | 2.91626 | 12.7773 | 2.43869 | 0.013146 | 0.0106967 | 7.85362e-05 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19998.2 | 0.0929616 | 4783.35ms | 837491 | 4890 | 6.74053e+06 | 39938.3 | 0.113264 | 0.253529 | 0.835428 | 0.124885 | 0.000131564 | 0.0163366 | 1.24976e-05 | 1(Win) | true |
| Glaze | 4817.52 | 0.0762568 | 8905.39ms | 837491 | 1280 | 2.04588e+07 | 165789 | 0.122622 | 1.02807 | 4.43626 | 0.730113 | 0.0058552 | 0.056987 | 1.7184e-05 | 2(Loss) | true |
| simdjson (reflection) | 519.562 | 0.361007 | 9670.01ms | 837491 | 320 | 9.85523e+09 | 1.53725e+06 | 0.300973 | 9.56077 | 37.1915 | 7.13577 | 0.0292063 | 0.349374 | 0.00213672 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20161.2 | 0.114367 | 4785.33ms | 837491 | 40 | 82108 | 39615.3 | 0.0538381 | 0.250854 | 0.834776 | 0.124738 | 0.000130509 | 0.016086 | 4.82095e-05 | 1(Win) | true |
| Glaze | 5703.7 | 0.0994452 | 7595.03ms | 837491 | 640 | 1.24107e+07 | 140031 | 0.14796 | 0.866238 | 4.42726 | 0.728068 | 0.00587866 | 0.0214782 | 2.96626e-05 | 2(Loss) | true |
| simdjson (reflection) | 523.343 | 0.641414 | 9668.39ms | 837491 | 80 | 7.66575e+09 | 1.52614e+06 | 0.120079 | 9.48761 | 37.1996 | 7.13848 | 0.0294105 | 0.349979 | 0.0153982 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7813.82 | 0.0627878 | 6523.91ms | 466906 | 1280 | 1.63868e+06 | 56985.8 | 0.179909 | 0.640848 | 3.0836 | 0.37113 | 0.000781166 | 8.59213e-06 | 6.25628e-06 | 1(Win) | true |
| Jsonifier | 7793.5 | 0.0294355 | 6467.27ms | 466906 | 4890 | 1.38307e+06 | 57134.3 | 0.0621914 | 0.63915 | 3.08865 | 0.372371 | 0.000791107 | 6.71216e-06 | 5.01934e-06 | 2(Loss) | true |
| simdjson (reflection) | 7138.53 | 0.182078 | 7056.39ms | 466906 | 30 | 386971 | 62376.4 | 0.00443524 | 0.707812 | 3.57408 | 0.372508 | 0.00078574 | 2.95563e-05 | 2.17745e-05 | 3(Loss) | true |
| simdjson (ondemand) | 6946.75 | 0.0865507 | 7157.15ms | 466906 | 320 | 984886 | 64098.5 | 0.0470246 | 0.713138 | 3.61354 | 0.379473 | 0.00085325 | 2.89807e-06 | 1.42561e-06 | 4(Loss) | true |
| Glaze | 3196.14 | 0.120061 | 7517.62ms | 466906 | 320 | 8.95279e+06 | 139317 | 0.0191843 | 1.56678 | 6.44294 | 1.02708 | 0.00154157 | 4.1095e-06 | 2.16184e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7956.83 | 0.0382695 | 6536.87ms | 466906 | 2560 | 1.17415e+06 | 55961.5 | 0.152439 | 0.628581 | 3.05263 | 0.364133 | 0.000761612 | 7.07868e-06 | 5.59451e-06 | 1(Win) | true |
| Jsonifier | 7921.61 | 0.0367206 | 6527.53ms | 466906 | 2560 | 1.09066e+06 | 56210.3 | 0.0319731 | 0.630344 | 3.05732 | 0.36526 | 0.000793092 | 1.4917e-05 | 1.20156e-05 | 2(Loss) | true |
| simdjson (reflection) | 7087.23 | 0.0420233 | 7174.13ms | 466906 | 640 | 446135 | 62828 | 0.230686 | 0.700693 | 3.55903 | 0.36955 | 0.000779888 | 1.22147e-05 | 1.03741e-05 | 3(Loss) | true |
| simdjson (ondemand) | 7039.52 | 0.0127446 | 7130.16ms | 466906 | 1280 | 83183.2 | 63253.8 | 0.0173576 | 0.704836 | 3.5812 | 0.372919 | 0.000880218 | 1.72177e-06 | 8.34951e-07 | 4(Loss) | true |
| Glaze | 3233.7 | 0.0822421 | 7473.71ms | 466906 | 640 | 8.20781e+06 | 137699 | 0.00665925 | 1.55147 | 6.39921 | 1.01715 | 0.00148116 | 2.48477e-05 | 2.10796e-05 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8800.26 | 0.0342858 | 7614.97ms | 631514 | 2560 | 1.40943e+06 | 68436.5 | 0.237407 | 0.571041 | 2.72586 | 0.284695 | 0.000564059 | 6.55357e-06 | 5.21131e-06 | 1(Win) | true |
| Jsonifier | 8785.34 | 0.0587771 | 7656.83ms | 631514 | 640 | 1.03907e+06 | 68552.7 | 0.0500596 | 0.569981 | 2.72698 | 0.284971 | 0.000571249 | 1.48453e-06 | 5.49275e-07 | 2(Loss) | true |
| simdjson (reflection) | 8166.04 | 0.0463766 | 8120.71ms | 631514 | 640 | 748724 | 73751.7 | 0.110948 | 0.607207 | 3.01547 | 0.291368 | 0.000571264 | 2.77854e-06 | 1.34102e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8084.69 | 0.0248916 | 8209.76ms | 631514 | 2560 | 880207 | 74493.7 | 0.0577211 | 0.614657 | 3.04498 | 0.296603 | 0.000624155 | 4.22472e-06 | 2.46308e-06 | 4(Loss) | true |
| Glaze | 3817.27 | 0.109272 | 8505.25ms | 631514 | 320 | 9.51112e+06 | 157772 | 0.150068 | 1.30795 | 5.85921 | 0.962981 | 0.00140573 | 1.03867e-05 | 7.67501e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8842.23 | 0.0371912 | 7654.73ms | 631514 | 2560 | 1.64272e+06 | 68111.6 | 0.109375 | 0.563394 | 2.70429 | 0.27984 | 0.000565911 | 1.92741e-06 | 1.02865e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 8740.93 | 0.168622 | 7695.5ms | 631514 | 160 | 2.15973e+06 | 68901 | 0.010587 | 0.566099 | 2.70316 | 0.279574 | 0.000557559 | 3.10266e-05 | 2.82456e-05 | 2(Loss) | true |
| simdjson (reflection) | 8240.64 | 0.0331411 | 8217.6ms | 631514 | 2560 | 1.50182e+06 | 73084 | 0.0811383 | 0.605477 | 3.00507 | 0.289343 | 0.000601069 | 5.7612e-06 | 3.67173e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8140.96 | 0.0723341 | 8264.48ms | 631514 | 40 | 114541 | 73978.8 | 0.0815784 | 0.609102 | 3.02155 | 0.291851 | 0.000646502 | 3.52328e-06 | 1.5835e-06 | 4(Loss) | true |
| Glaze | 3835.03 | 0.083137 | 8416.07ms | 631514 | 640 | 1.09093e+07 | 157042 | 0.0133571 | 1.30142 | 5.82694 | 0.955664 | 0.0013584 | 2.05681e-05 | 1.84428e-05 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2002.97 | 0.10725 | 5872.5ms | 466906 | 640 | 3.63819e+07 | 222308 | 0.00974905 | 2.4707 | 7.78698 | 1.31592 | 0.0115295 | 0.0155826 | 0.000299666 | 1(Win) | true |
| Glaze | 1727.41 | 0.081185 | 6853.57ms | 466906 | 640 | 2.80286e+07 | 257771 | 0.10723 | 2.90515 | 10.4234 | 1.86935 | 0.013253 | 0.0140066 | 4.76608e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1672.61 | 0.149941 | 7022.84ms | 466906 | 320 | 5.09867e+07 | 266216 | 0.0161784 | 2.95893 | 8.91721 | 1.43085 | 0.0177109 | 0.0323514 | 0.000321565 | 3(Loss) | true |
| simdjson (ondemand) | 1501.46 | 0.298007 | 7751.83ms | 466906 | 160 | 1.24969e+08 | 296561 | 0.134185 | 3.29966 | 10.2095 | 1.8753 | 0.012406 | 0.042276 | 0.000303875 | 4(Loss) | true |
| simdjson (reflection) | 1481.52 | 0.196107 | 7898.85ms | 466906 | 160 | 5.55844e+07 | 300554 | 0.133139 | 3.34133 | 10.3141 | 1.60322 | 0.0138403 | 0.0442047 | 0.000983255 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2590.02 | 0.118732 | 5347.52ms | 466906 | 640 | 2.66667e+07 | 171920 | 0.206751 | 1.90557 | 6.35325 | 0.991411 | 0.00874265 | 0.00235338 | 2.90008e-05 | 1(Win) | true |
| Glaze | 2177.33 | 0.144739 | 6101.78ms | 466906 | 320 | 2.8037e+07 | 204506 | 0.137336 | 2.27672 | 8.99001 | 1.54366 | 0.00810241 | 0.00118947 | 3.45693e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2098.98 | 0.157541 | 6380.36ms | 466906 | 640 | 7.1484e+07 | 212139 | 0.0909266 | 2.35905 | 7.48952 | 1.108 | 0.0135091 | 0.00945124 | 7.77358e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1836.52 | 0.0795445 | 7103.53ms | 466906 | 1280 | 4.76102e+07 | 242457 | 0.0860838 | 2.70022 | 8.86629 | 1.57003 | 0.0093019 | 0.0106641 | 0.0001287 | 4(Loss) | true |
| simdjson (reflection) | 1732.77 | 0.358772 | 7484.11ms | 466906 | 80 | 6.7999e+07 | 256973 | 0.245588 | 2.84797 | 9.26678 | 1.35872 | 0.00984566 | 0.0332863 | 0.000146416 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17574.4 | 0.0953339 | 3368.88ms | 475954 | 40 | 24250.6 | 25827.6 | 0.0068407 | 0.283501 | 1.0044 | 0.148046 | 0.000314053 | 0.00245423 | 2.27963e-05 | 1(Win) | true |
| simdjson (reflection) | 10832.3 | 0.0269476 | 4964.6ms | 475954 | 4890 | 623501 | 41903 | 0.0887166 | 0.457227 | 1.30937 | 0.183999 | 0.000266887 | 0.00303841 | 2.72483e-05 | 2(Loss) | true |
| Glaze | 7802.03 | 0.198641 | 6629.27ms | 475954 | 1280 | 1.70948e+07 | 58177.8 | 0.416679 | 0.634702 | 2.22735 | 0.324874 | 0.000273137 | 0.0155187 | 4.67351e-05 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17582.5 | 0.0371475 | 3356.2ms | 475954 | 2560 | 235433 | 25815.7 | 0.0274527 | 0.282212 | 1.0033 | 0.147798 | 0.00027109 | 0.00205844 | 2.14413e-05 | 1(Win) | true |
| simdjson (reflection) | 10893.3 | 0.026753 | 4939.63ms | 475954 | 4890 | 607669 | 41668.5 | 0.00755745 | 0.455008 | 1.30829 | 0.183753 | 0.000263091 | 0.0018752 | 3.30538e-05 | 2(Loss) | true |
| Glaze | 8884.13 | 0.653577 | 5950.93ms | 475954 | 160 | 1.78408e+07 | 51091.7 | 0.272964 | 0.558405 | 2.21522 | 0.322105 | 0.000257509 | 0.00152876 | 2.59216e-05 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2185.55 | 0.153122 | 7268.7ms | 631514 | 160 | 2.84867e+07 | 275564 | 0.0392496 | 2.27234 | 7.04636 | 1.06946 | 0.012501 | 0.0378475 | 0.000284435 | 1(Win) | true |
| simdjson (ondemand) | 1942.57 | 0.155101 | 8142.07ms | 631514 | 160 | 3.69966e+07 | 310032 | 0.0227042 | 2.55733 | 7.92296 | 1.40264 | 0.0097588 | 0.044492 | 0.000157597 | 2(Loss) | true |
| simdjson (reflection) | 1929.31 | 0.064707 | 8197.88ms | 631514 | 1280 | 5.22247e+07 | 312164 | 0.381791 | 2.56646 | 8.00128 | 1.20209 | 0.0102498 | 0.0446429 | 0.000270924 | 3(Loss) | true |
| Jsonifier | 1877.84 | 0.0725119 | 8415.94ms | 631514 | 320 | 1.73068e+07 | 320719 | 0.0954443 | 2.65608 | 7.18837 | 1.33459 | 0.0107886 | 0.024343 | 0.000643988 | 4(Loss) | true |
| Glaze | 1845.82 | 0.106009 | 8574.22ms | 631514 | 320 | 3.82842e+07 | 326282 | 0.0607349 | 2.70652 | 9.28232 | 1.71397 | 0.0105711 | 0.0167899 | 0.000470328 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2726.69 | 0.0845728 | 6667.88ms | 631514 | 1280 | 4.46649e+07 | 220875 | 0.0493802 | 1.8175 | 5.99233 | 0.831389 | 0.00964462 | 0.0113332 | 4.20282e-05 | 1(Win) | true |
| simdjson (ondemand) | 2362.29 | 0.154736 | 7420.35ms | 631514 | 640 | 9.96003e+07 | 254947 | 0.0812101 | 2.10346 | 6.93071 | 1.17729 | 0.00699063 | 0.015016 | 6.12095e-05 | 2(Loss) | true |
| Jsonifier | 2255.66 | 0.0921873 | 7789.49ms | 631514 | 640 | 3.87741e+07 | 266999 | 0.0886849 | 2.22143 | 6.12932 | 1.09524 | 0.00858635 | 0.00525728 | 0.000114561 | 3(Loss) | true |
| simdjson (reflection) | 2239.31 | 0.0983645 | 7802.59ms | 631514 | 1280 | 8.95828e+07 | 268948 | 0.408738 | 2.2112 | 7.2239 | 1.02019 | 0.00726784 | 0.0361353 | 7.68664e-05 | 4(Loss) | true |
| Glaze | 2166.56 | 0.404047 | 7859.39ms | 631514 | 30 | 3.78453e+07 | 277980 | 0.261601 | 2.28001 | 8.22446 | 1.47445 | 0.00852729 | 0.00228857 | 0.000148532 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20857 | 0.0609669 | 4047.25ms | 716365 | 1280 | 510464 | 32755.4 | 0.115718 | 0.238585 | 0.716942 | 0.0983926 | 0.000173532 | 0.0057578 | 1.31938e-05 | 1(Win) | true |
| Glaze | 4968 | 0.137959 | 7442.21ms | 716365 | 2560 | 9.21396e+07 | 137516 | 0.268381 | 0.999171 | 2.7058 | 0.438037 | 0.000352698 | 0.0473652 | 4.49426e-05 | 2(Loss) | true |
| simdjson (reflection) | 529.329 | 0.244844 | 8232.77ms | 716365 | 320 | 3.19555e+09 | 1.29065e+06 | 0.193838 | 9.4251 | 30.5272 | 6.84573 | 0.0683267 | 0.28651 | 0.00174108 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21304.8 | 0.0837297 | 4038.47ms | 716365 | 80 | 57671.8 | 32066.9 | 0.0150099 | 0.237474 | 0.716184 | 0.0982209 | 0.00017095 | 0.00562435 | 1.204e-05 | 1(Win) | true |
| Glaze | 6385.2 | 0.136399 | 5904.3ms | 716365 | 2560 | 5.45232e+07 | 106994 | 0.161639 | 0.780963 | 2.69622 | 0.435824 | 0.000341351 | 0.0108891 | 3.93518e-05 | 2(Loss) | true |
| simdjson (reflection) | 524.527 | 0.229856 | 8264.47ms | 716365 | 320 | 2.86812e+09 | 1.30247e+06 | 0.207302 | 9.45837 | 30.5285 | 6.84575 | 0.0684245 | 0.287708 | 0.00532512 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2294.18 | 0.0500674 | 842.909ms | 2632 | 640 | 192.047 | 1094.1 | 0.256258 | 2.30806 | 8.20441 | 1.33093 | 0.00188604 | 3.56193e-05 | 3.56193e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2075.95 | 0.183113 | 856.989ms | 2632 | 320 | 1568.64 | 1209.12 | 0.245443 | 2.51729 | 10.1151 | 1.61892 | 0.000863174 | 2.84954e-05 | 9.49848e-06 | 2(Loss) | true |
| Glaze | 1996.2 | 0.045141 | 855.563ms | 2632 | 2560 | 824.796 | 1257.43 | 0.0980706 | 2.6156 | 11.0171 | 2.11968 | 0.000447022 | 4.37821e-05 | 1.32088e-05 | 3(Loss) | true |
| simdjson (reflection) | 1736.49 | 0.068553 | 879.204ms | 2632 | 640 | 628.435 | 1445.48 | 0.017082 | 2.99455 | 9.72302 | 1.67743 | 0.00174 | 4.33368e-05 | 1.24668e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1679.97 | 0.0538789 | 911.548ms | 2632 | 1280 | 829.498 | 1494.11 | 0.018252 | 3.09358 | 10.6679 | 1.88754 | 0.00205405 | 5.87718e-05 | 1.18731e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2682.43 | 0.0581099 | 834.285ms | 2632 | 640 | 189.232 | 935.745 | 0.0733576 | 1.99258 | 7.23632 | 1.07713 | 0.00155775 | 2.25589e-05 | 5.93655e-07 | 1(Win) | true |
| Glaze | 2535.29 | 0.0346295 | 837.483ms | 2632 | 4890 | 574.801 | 990.053 | 0.0415055 | 2.07685 | 9.23366 | 1.68351 | 0.000977664 | 5.25233e-05 | 2.04344e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2406.91 | 0.0848953 | 846.647ms | 2632 | 2560 | 2006.59 | 1042.86 | 0.323888 | 2.17093 | 9.1421 | 1.36398 | 0.000837499 | 5.44678e-05 | 2.25589e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1961.34 | 0.0535557 | 872.226ms | 2632 | 1280 | 601.297 | 1279.78 | 0.0466173 | 2.63436 | 9.10638 | 1.5114 | 0.00155152 | 2.90891e-05 | 4.45241e-06 | 4(Loss) | true |
| simdjson (reflection) | 1901.51 | 0.0514892 | 882.91ms | 2632 | 640 | 295.656 | 1320.04 | 0.011483 | 2.74339 | 9.08283 | 1.4924 | 0.000759878 | 3.68066e-05 | 1.48414e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11999.2 | 0.12023 | 747.644ms | 2632 | 1280 | 80.9667 | 209.187 | 0.0451695 | 0.508917 | 1.73936 | 0.290274 | 0.000380236 | 2.93859e-05 | 3.56193e-06 | 1(Win) | true |
| simdjson (reflection) | 7021.67 | 0.170765 | 766.43ms | 2632 | 160 | 59.622 | 357.475 | 0.315701 | 0.800304 | 2.73366 | 0.455547 | 0.000379939 | 9.49848e-06 | 0 | 2(Loss) | true |
| Glaze | 4721.01 | 0.0877623 | 784.383ms | 2632 | 640 | 139.347 | 531.681 | 0.0146961 | 1.15509 | 4.00798 | 0.653495 | 0.000381127 | 1.95906e-05 | 5.93655e-07 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14405.3 | 0.0747663 | 740.91ms | 2632 | 1280 | 21.7244 | 174.246 | 0.73392 | 0.435098 | 1.52546 | 0.240502 | 0.000379939 | 3.05732e-05 | 4.15559e-06 | 1(Win) | true |
| simdjson (reflection) | 7800.1 | 0.183794 | 760.963ms | 2632 | 80 | 27.9848 | 321.8 | 0.232522 | 0.732447 | 2.52356 | 0.406155 | 0.000379939 | 9.49848e-06 | 0 | 2(Loss) | true |
| Glaze | 5225.03 | 0.0810773 | 777.201ms | 2632 | 2560 | 388.359 | 480.394 | 0.228361 | 1.05064 | 3.59005 | 0.569529 | 0.000395968 | 4.61567e-05 | 9.49848e-06 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2446.99 | 0.0377783 | 869.437ms | 3370 | 4890 | 1203.9 | 1313.4 | 0.0929246 | 2.12567 | 8.51009 | 1.30712 | 0.000829586 | 5.73447e-05 | 2.05713e-05 | 1(Win) | true |
| Jsonifier | 2230.82 | 0.124325 | 882.912ms | 3370 | 1280 | 4106.39 | 1440.68 | 0.180307 | 2.31245 | 8.30148 | 1.52849 | 0.00154975 | 2.94418e-05 | 7.4184e-06 | 2(Loss) | true |
| simdjson (reflection) | 2192.54 | 0.0488645 | 883.107ms | 3370 | 1280 | 656.69 | 1465.82 | 0.047306 | 2.37151 | 7.87448 | 1.31573 | 0.00112226 | 4.82196e-05 | 1.11276e-05 | 3(Loss) | true |
| Glaze | 2096.47 | 0.0912704 | 888.714ms | 3370 | 40 | 78.3077 | 1533 | 0.0500359 | 2.4777 | 10.5264 | 2.03264 | 0.000793769 | 1.48368e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 2075.56 | 0.064668 | 916.555ms | 3370 | 640 | 641.724 | 1548.44 | 0.0218922 | 2.50376 | 8.75727 | 1.51217 | 0.00136128 | 2.73553e-05 | 8.3457e-06 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2854.67 | 0.0585617 | 860.416ms | 3370 | 4890 | 2125.62 | 1125.83 | 0.104088 | 1.82496 | 7.60772 | 1.08071 | 0.000595596 | 6.08642e-05 | 2.2331e-05 | 1(Win) | true |
| Jsonifier | 2528.46 | 0.0335285 | 872.4ms | 3370 | 4890 | 888.145 | 1271.08 | 0.0497347 | 2.0637 | 7.5454 | 1.33027 | 0.00147094 | 3.99289e-05 | 1.07407e-05 | 2(Loss) | true |
| Glaze | 2502.22 | 0.0425185 | 871.482ms | 3370 | 4890 | 1458.4 | 1284.41 | 0.00148091 | 2.07601 | 9.15015 | 1.69021 | 0.00107723 | 3.11906e-05 | 6.61436e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2363.35 | 0.100042 | 888.46ms | 3370 | 640 | 1184.53 | 1359.88 | 0.109619 | 2.18786 | 7.62226 | 1.23413 | 0.00107845 | 3.10645e-05 | 2.7819e-06 | 4(Loss) | true |
| simdjson (reflection) | 2329.37 | 0.0430198 | 884.898ms | 3370 | 4890 | 1722.77 | 1379.72 | 0.00749347 | 2.23373 | 7.44985 | 1.18635 | 0.00107395 | 5.67985e-05 | 1.80833e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13297.8 | 0.197264 | 756.79ms | 3643 | 640 | 169.994 | 261.264 | 0.05565 | 0.443269 | 1.30881 | 0.21658 | 0.000274499 | 2.35898e-05 | 1.71562e-06 | 1(Win) | true |
| Glaze | 4178.98 | 0.0930116 | 814.99ms | 3682 | 4890 | 2986.83 | 840.26 | 0.081315 | 1.26914 | 4.2208 | 0.702879 | 0.000274868 | 4.77646e-05 | 1.63288e-05 | 2(Loss) | true |
| simdjson (reflection) | 544.249 | 0.141133 | 1388.27ms | 3643 | 640 | 51947.3 | 6383.54 | 0.0845416 | 9.303 | 36.1202 | 7.58414 | 0.0145669 | 0.00011752 | 5.57576e-06 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18255 | 0.151138 | 745.62ms | 3643 | 4890 | 404.588 | 190.317 | 0.0934708 | 0.336943 | 1.13753 | 0.173759 | 0.000275117 | 3.01444e-05 | 8.13954e-06 | 1(Win) | true |
| Glaze | 4677.95 | 0.436047 | 805.639ms | 3682 | 320 | 3428.26 | 750.634 | 0.0237356 | 1.13829 | 3.92208 | 0.637161 | 0.000281776 | 4.32849e-05 | 9.33596e-06 | 2(Loss) | true |
| simdjson (reflection) | 543.268 | 0.0559687 | 1387.16ms | 3643 | 4890 | 62645.4 | 6395.07 | 0.113541 | 9.30417 | 36.1318 | 7.58688 | 0.0144655 | 0.000135341 | 5.3328e-05 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1052.83 | 0.0371664 | 1161.54ms | 4630 | 2560 | 6219.9 | 4193.93 | 0.294155 | 4.79095 | 21.7963 | 4.47495 | 0.00611417 | 0.000157178 | 8.42839e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 889.124 | 0.0219048 | 1239.48ms | 4630 | 4890 | 5786.63 | 4966.14 | 0.119039 | 5.67403 | 24.4903 | 4.77991 | 0.00684515 | 6.71357e-05 | 1.96107e-05 | 2(Loss) | true |
| Glaze | 755.705 | 0.0248706 | 1319.28ms | 4630 | 4890 | 10326.1 | 5842.9 | 0.00578739 | 6.72066 | 30.0426 | 5.72354 | 0.0065691 | 7.60577e-05 | 2.65009e-05 | 3(Loss) | true |
| simdjson (ondemand) | 754.809 | 0.042711 | 1323.9ms | 4630 | 1280 | 7990.56 | 5849.84 | 0.220953 | 6.6958 | 30.1464 | 5.45983 | 0.00213806 | 8.84179e-05 | 2.90227e-05 | 4(Loss) | true |
| simdjson (reflection) | 752.072 | 0.0646024 | 1325.12ms | 4630 | 640 | 9207.06 | 5871.13 | 0.0762421 | 6.71794 | 27.3756 | 5.12074 | 0.0086059 | 7.45815e-05 | 3.37473e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1360.8 | 0.0429463 | 1158.67ms | 4630 | 2560 | 4971.26 | 3244.8 | 0.124718 | 3.72644 | 17.5091 | 3.50216 | 0.0039902 | 5.14646e-05 | 1.31614e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1100.34 | 0.0453418 | 1235.82ms | 4630 | 2560 | 8475.07 | 4012.85 | 0.0502624 | 4.59704 | 20.1996 | 3.8067 | 0.00490897 | 3.34942e-05 | 6.41199e-06 | 2(Loss) | true |
| Glaze | 885.005 | 0.0744575 | 1337.77ms | 4630 | 640 | 8832.19 | 4989.25 | 0.129923 | 5.68029 | 25.6212 | 4.7216 | 0.00519438 | 3.64471e-05 | 4.38715e-06 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 865.773 | 0.031182 | 1351.66ms | 4630 | 2560 | 6474.44 | 5100.08 | 0.00788069 | 5.86581 | 27.154 | 4.79007 | 0.00159861 | 0.000118284 | 5.44175e-05 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 865.405 | 0.0895468 | 1352.03ms | 4630 | 80 | 1669.99 | 5102.25 | 0.256918 | 5.89426 | 24.6097 | 4.4959 | 0.00679266 | 3.7797e-05 | 8.09935e-06 | 4(Tie) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2055.45 | 0.0882636 | 948.754ms | 4630 | 1280 | 4601.71 | 2148.19 | 0.122047 | 2.50007 | 7.68618 | 0.409288 | 0.000226276 | 4.79212e-05 | 2.26107e-05 | 1(Win) | true |
| Glaze | 1582.74 | 0.049172 | 1012.51ms | 4630 | 1280 | 2408.75 | 2789.8 | 0.032523 | 3.24101 | 10.0009 | 0.718359 | 0.00021902 | 2.27794e-05 | 1.34989e-06 | 2(Loss) | true |
| simdjson (reflection) | 1058.17 | 0.0838132 | 1147.81ms | 4630 | 320 | 3914.09 | 4172.8 | 0.0956176 | 4.82266 | 15.4091 | 1.4527 | 0.000436015 | 1.2149e-05 | 2.69978e-06 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2083.3 | 0.0597578 | 944.149ms | 4630 | 1280 | 2053.32 | 2119.47 | 0.02308 | 2.45636 | 7.58337 | 0.385313 | 0.000222901 | 4.26903e-05 | 2.07546e-05 | 1(Win) | true |
| Glaze | 1588.35 | 0.114631 | 1010.15ms | 4630 | 160 | 1624.78 | 2779.94 | 0.0258482 | 3.23078 | 9.48315 | 0.60432 | 0.000236231 | 1.2149e-05 | 4.04968e-06 | 2(Loss) | true |
| simdjson (reflection) | 1070.89 | 0.0225715 | 1145.59ms | 4630 | 640 | 554.332 | 4123.2 | 0.0140193 | 4.76841 | 15.2991 | 1.42743 | 0.00043264 | 5.0621e-06 | 3.37473e-07 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2129.52 | 0.0480922 | 1260.77ms | 11579 | 1280 | 7960.48 | 5185.49 | 0.0113435 | 2.38306 | 10.497 | 1.92305 | 0.00287178 | 4.33166e-05 | 1.65305e-05 | 1(Win) | true |
| Jsonifier | 2069.72 | 0.0567547 | 1278.13ms | 11579 | 1280 | 11736.3 | 5335.3 | 0.17268 | 2.44521 | 10.8508 | 2.31859 | 0.0040003 | 3.71092e-05 | 1.65305e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1776.67 | 0.141013 | 1363.2ms | 11579 | 40 | 3072.64 | 6215.35 | 0.0512435 | 2.86508 | 12.5779 | 2.15891 | 0.00260169 | 1.07954e-05 | 4.31816e-06 | 3(Loss) | true |
| simdjson (reflection) | 1762.92 | 0.0235749 | 1363.91ms | 11579 | 4890 | 10663.2 | 6263.81 | 0.118885 | 2.84828 | 11.5389 | 2.03619 | 0.00442144 | 6.1196e-05 | 3.06598e-05 | 4(Loss) | true |
| Glaze | 1410.52 | 0.0483337 | 1511.26ms | 11579 | 640 | 9163.54 | 7828.73 | 0.125357 | 3.54573 | 15.4227 | 2.86976 | 0.00564708 | 2.52343e-05 | 8.2315e-06 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2610.06 | 0.0593038 | 1257.24ms | 11579 | 320 | 2014.46 | 4230.79 | 0.0121151 | 1.95929 | 8.80128 | 1.53908 | 0.00222655 | 2.42897e-05 | 3.77839e-06 | 1(Win) | true |
| Jsonifier | 2487.67 | 0.0894414 | 1280.01ms | 11579 | 640 | 10088.2 | 4438.93 | 0.0638119 | 2.01237 | 9.15684 | 1.9348 | 0.00324496 | 3.25212e-05 | 9.31104e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2022.79 | 0.0640604 | 1381.66ms | 11579 | 80 | 978.385 | 5459.09 | 0.0139656 | 2.52003 | 11.5814 | 1.92953 | 0.000593747 | 6.04543e-05 | 1.72726e-05 | 3(Loss) | true |
| simdjson (reflection) | 2003.5 | 0.0214059 | 1387.04ms | 11579 | 4890 | 6806.77 | 5511.65 | 0.0762879 | 2.53104 | 10.5881 | 1.81561 | 0.00326729 | 2.54321e-05 | 8.9189e-06 | 4(Loss) | true |
| Glaze | 1614.72 | 0.0887419 | 1526ms | 11579 | 30 | 1104.91 | 6838.7 | 0.0448227 | 3.15452 | 13.6881 | 2.47621 | 0.0053027 | 7.19694e-05 | 1.43939e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6241.53 | 0.0517841 | 965.823ms | 14795 | 160 | 219.26 | 2260.6 | 0.00608209 | 0.825101 | 2.48523 | 0.129638 | 6.80128e-05 | 1.81649e-05 | 8.4488e-07 | 1(Win) | true |
| Glaze | 3696.33 | 0.0379056 | 1126.24ms | 14795 | 4890 | 10237.8 | 3817.2 | 0.0772737 | 1.38271 | 4.54289 | 0.520784 | 6.93044e-05 | 4.00014e-05 | 2.083e-05 | 2(Loss) | true |
| simdjson (reflection) | 407.024 | 0.0690648 | 4215.01ms | 14795 | 2560 | 1.46738e+06 | 34665.3 | 0.0428807 | 12.2989 | 43.2166 | 6.07489 | 0.00860333 | 0.000140514 | 7.24485e-05 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6479.69 | 0.0574093 | 954.435ms | 14795 | 160 | 250.038 | 2177.51 | 0.147173 | 0.795993 | 2.44616 | 0.120649 | 6.75904e-05 | 1.35181e-05 | 0 | 1(Win) | true |
| Glaze | 4127.88 | 0.0449006 | 1076.36ms | 14795 | 2560 | 6030.05 | 3418.13 | 0.162381 | 1.23925 | 4.33721 | 0.47462 | 0.000125412 | 1.88778e-05 | 5.51812e-06 | 2(Loss) | true |
| simdjson (reflection) | 397.543 | 0.0746637 | 4302.47ms | 14795 | 2560 | 1.79772e+06 | 35492 | 0.0241023 | 12.6306 | 43.2068 | 6.07354 | 0.00844666 | 0.000309675 | 0.000179511 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1691.77 | 0.253161 | 925.58ms | 3223 | 40 | 846.233 | 1816.85 | 0.14791 | 3.09197 | 11.3863 | 2.04561 | 0.00176078 | 6.2054e-05 | 2.32702e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1433.68 | 0.0916709 | 950.461ms | 3223 | 160 | 618.019 | 2143.93 | 0.00699602 | 3.59965 | 13.8573 | 2.38939 | 0.00105104 | 3.49054e-05 | 5.81756e-06 | 2(Loss) | true |
| Glaze | 1363.92 | 0.0363411 | 960.769ms | 3223 | 2560 | 1717.03 | 2253.56 | 0.0247117 | 3.7773 | 14.6196 | 2.83339 | 0.00155002 | 7.33255e-05 | 2.41186e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1239.11 | 0.0329199 | 984.054ms | 3223 | 2560 | 1707.11 | 2480.57 | 0.0564863 | 4.15357 | 15.6354 | 2.64195 | 0.00201736 | 0.000119502 | 4.73889e-05 | 4(Loss) | true |
| simdjson (reflection) | 1179.01 | 0.077628 | 1002.79ms | 3223 | 320 | 1310.6 | 2607 | 0.0204935 | 4.34825 | 15.3605 | 2.67111 | 0.00111503 | 3.49054e-05 | 2.90878e-06 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2055.27 | 0.0573747 | 904.503ms | 3223 | 1280 | 942.394 | 1495.51 | 0.00720958 | 2.5528 | 9.88892 | 1.65622 | 0.00170624 | 8.84754e-05 | 3.02998e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1637.47 | 0.0465896 | 948.256ms | 3223 | 640 | 489.477 | 1877.1 | 0.0889877 | 3.16003 | 12.4123 | 2.01086 | 0.00116497 | 3.49054e-05 | 5.81756e-06 | 2(Loss) | true |
| Glaze | 1593.9 | 0.0653244 | 948.461ms | 3223 | 640 | 1015.61 | 1928.41 | 0.0207382 | 3.24079 | 13.0661 | 2.43376 | 0.00108643 | 2.6179e-05 | 2.90878e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1399.58 | 0.0263816 | 979.356ms | 3223 | 4890 | 1641.47 | 2196.15 | 0.271823 | 3.68191 | 14.1008 | 2.24884 | 0.00174106 | 0.000108055 | 4.6826e-05 | 4(Loss) | true |
| simdjson (reflection) | 1350.09 | 0.0567315 | 993.337ms | 3223 | 640 | 1067.64 | 2276.66 | 0.0549434 | 3.81825 | 13.8455 | 2.28343 | 0.00130265 | 6.4478e-05 | 1.11503e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7551.45 | 0.205545 | 778.078ms | 3223 | 30 | 20.9989 | 407.033 | 0.106575 | 0.736726 | 2.11418 | 0.354328 | 0.000320612 | 6.2054e-05 | 4.13693e-05 | 1(Win) | true |
| simdjson (reflection) | 6032.76 | 0.132783 | 789.162ms | 3223 | 40 | 18.3077 | 509.5 | 1.16487 | 0.907803 | 2.68104 | 0.320509 | 0.00031027 | 0 | 0 | 2(Loss) | true |
| Glaze | 3491.99 | 0.142693 | 824.383ms | 3223 | 1280 | 2019.25 | 880.213 | 0.0949712 | 1.5175 | 4.95222 | 0.755508 | 0.000311724 | 0.000121926 | 5.09037e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8608.43 | 0.0868869 | 771.3ms | 3223 | 160 | 15.3993 | 357.056 | 0.0683132 | 0.665283 | 1.96153 | 0.318027 | 0.00031027 | 1.16351e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6560.62 | 0.0442622 | 784.248ms | 3223 | 160 | 6.88046 | 468.506 | 0.0787696 | 0.841925 | 2.52249 | 0.283276 | 0.00031027 | 3.87837e-06 | 0 | 2(Loss) | true |
| Glaze | 3486.68 | 0.269313 | 823.664ms | 3223 | 1280 | 7214.77 | 881.553 | 0.154318 | 1.49269 | 4.40242 | 0.633572 | 0.000313906 | 7.85371e-05 | 3.66022e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2363.02 | 0.106142 | 973.054ms | 5839 | 80 | 500.506 | 2356.53 | 0.0562585 | 2.14138 | 8.39784 | 1.35914 | 0.000659359 | 3.8534e-05 | 1.9267e-05 | 1(Win) | true |
| Jsonifier | 2105.76 | 0.052388 | 1008.1ms | 5839 | 2560 | 4913.2 | 2644.42 | 0.146958 | 2.43201 | 8.78284 | 1.77102 | 0.000583563 | 9.52646e-05 | 4.92379e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2089.3 | 0.0536483 | 1011.74ms | 5839 | 1280 | 2616.96 | 2665.25 | 0.107781 | 2.45724 | 9.30725 | 1.49872 | 0.00110892 | 5.73996e-05 | 1.55206e-05 | 3(Loss) | true |
| simdjson (reflection) | 2012.97 | 0.10412 | 1019.13ms | 5839 | 80 | 663.686 | 2766.31 | 0.101566 | 2.55205 | 9.20363 | 1.52766 | 0.00106825 | 2.14078e-05 | 0 | 4(Loss) | true |
| Glaze | 1744.33 | 0.0257799 | 1060.22ms | 5839 | 4890 | 3312.02 | 3192.35 | 0.131907 | 2.93703 | 11.2009 | 2.14044 | 0.00221797 | 6.15003e-05 | 2.84737e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2803.22 | 0.184935 | 962.879ms | 5839 | 30 | 404.878 | 1986.47 | 0.0922061 | 1.84441 | 7.55694 | 1.14163 | 0.000713593 | 0.000125592 | 2.85437e-05 | 1(Win) | true |
| Jsonifier | 2389.13 | 0.103913 | 994.828ms | 5839 | 30 | 175.978 | 2330.77 | 0.10001 | 2.15492 | 7.9428 | 1.55369 | 0.000605126 | 5.70874e-06 | 5.70874e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2368.61 | 0.0500516 | 993.413ms | 5839 | 2560 | 3544.61 | 2350.96 | 0.0233004 | 2.15691 | 8.37558 | 1.26666 | 0.000903141 | 5.28504e-05 | 2.16754e-05 | 3(Loss) | true |
| simdjson (reflection) | 2283.54 | 0.0393606 | 1006.33ms | 5839 | 4890 | 4504.98 | 2438.54 | 0.0683513 | 2.25121 | 8.23668 | 1.28627 | 0.000829273 | 5.22893e-05 | 1.46746e-05 | 4(Loss) | true |
| Glaze | 1948.02 | 0.0312283 | 1049.11ms | 5839 | 4890 | 3896.7 | 2858.55 | 0.0473433 | 2.61998 | 10.3408 | 1.91985 | 0.00198864 | 2.92442e-05 | 3.25713e-06 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14920 | 0.0341349 | 779.045ms | 6938 | 640 | 14.6658 | 443.47 | 0.106644 | 0.371009 | 1.06054 | 0.165033 | 0.000144134 | 1.03596e-05 | 9.00836e-07 | 1(Win) | true |
| Glaze | 3225.02 | 0.16654 | 942.639ms | 6960 | 4890 | 57451.2 | 2058.15 | 0.103879 | 1.60281 | 4.27385 | 0.704167 | 0.000428801 | 6.58745e-05 | 2.78248e-05 | 2(Loss) | true |
| simdjson (reflection) | 494.171 | 0.21042 | 2094.91ms | 6938 | 640 | 508005 | 13389.3 | 0.129796 | 10.1021 | 38.9721 | 7.31234 | 0.00879396 | 8.22013e-05 | 4.00872e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16725.5 | 0.133098 | 773.474ms | 6938 | 30 | 8.31724 | 395.6 | 0.0168492 | 0.335399 | 0.987028 | 0.148025 | 0.000144134 | 3.36312e-05 | 3.36312e-05 | 1(Win) | true |
| Glaze | 3536.7 | 0.175312 | 922.852ms | 6960 | 4890 | 52936.2 | 1876.77 | 0.261148 | 1.45867 | 3.91135 | 0.627299 | 0.000347825 | 2.37407e-05 | 9.40225e-06 | 2(Loss) | true |
| simdjson (reflection) | 486.354 | 0.140308 | 2104.95ms | 6938 | 1280 | 466379 | 13604.5 | 0.07352 | 10.2285 | 38.9896 | 7.31623 | 0.00993532 | 0.00014785 | 7.45442e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1956.29 | 0.0950556 | 979.23ms | 4857 | 640 | 3241.94 | 2367.74 | 0.0295553 | 2.62359 | 9.50484 | 1.71279 | 0.00127072 | 7.07741e-05 | 3.60305e-05 | 1(Win) | true |
| Glaze | 1794.21 | 0.159477 | 1004.3ms | 4857 | 80 | 1356.06 | 2581.64 | 0.0528044 | 2.86676 | 11.5075 | 2.27239 | 0.000702594 | 8.23554e-05 | 2.57361e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1647.65 | 0.0410367 | 1022.5ms | 4857 | 2560 | 3407.15 | 2811.27 | 0.162041 | 3.09962 | 11.9938 | 2.00268 | 0.00101199 | 8.58136e-05 | 4.43143e-05 | 3(Loss) | true |
| simdjson (reflection) | 1496.68 | 0.114975 | 1047.84ms | 4857 | 640 | 8103.32 | 3094.85 | 0.0367176 | 3.421 | 12.7089 | 2.23368 | 0.00180185 | 3.21701e-05 | 4.82551e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1325.95 | 0.0265681 | 1092.78ms | 4857 | 4890 | 4212.21 | 3493.34 | 0.00694283 | 3.85585 | 13.9876 | 2.63105 | 0.00133495 | 8.90499e-05 | 2.93886e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2576.13 | 0.0383005 | 943.984ms | 4857 | 2560 | 1214.08 | 1798.04 | 0.164141 | 2.02496 | 7.38254 | 1.21968 | 0.00127136 | 5.04266e-05 | 1.29485e-05 | 1(Win) | true |
| Glaze | 2518.72 | 0.131024 | 947.227ms | 4857 | 160 | 928.955 | 1839.03 | 0.006117 | 2.01696 | 8.55322 | 1.59234 | 0.00125206 | 2.18756e-05 | 5.14721e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2047.08 | 0.0548402 | 992.558ms | 4857 | 640 | 985.475 | 2262.74 | 0.0787139 | 2.5184 | 9.86864 | 1.50813 | 0.00123211 | 8.55724e-05 | 4.11777e-05 | 3(Loss) | true |
| simdjson (reflection) | 1752.23 | 0.0412631 | 1031.9ms | 4857 | 2560 | 3045.91 | 2643.48 | 0.0278024 | 2.92263 | 11.5178 | 1.94173 | 0.00119576 | 6.28925e-05 | 1.40744e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1598.71 | 0.173853 | 1052.06ms | 4857 | 40 | 1014.89 | 2897.32 | 0.0129413 | 3.21314 | 11.7146 | 2.12724 | 0.00238316 | 5.14721e-05 | 1.54416e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9586.03 | 0.1089 | 781.633ms | 4857 | 2560 | 708.854 | 483.203 | 0.035315 | 0.578321 | 1.6714 | 0.278361 | 0.000206532 | 4.56815e-05 | 1.70501e-05 | 1(Win) | true |
| simdjson (reflection) | 7352.52 | 0.0994332 | 801.478ms | 4857 | 320 | 125.567 | 629.987 | 0.180234 | 0.735579 | 2.07227 | 0.337039 | 0.000205888 | 2.76663e-05 | 6.43401e-07 | 2(Loss) | true |
| Glaze | 4052.11 | 0.0960872 | 850.015ms | 4857 | 1280 | 1544.24 | 1143.11 | 0.106457 | 1.29453 | 3.70393 | 0.603871 | 0.000207175 | 4.03734e-05 | 6.27316e-06 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11213 | 0.116516 | 773.096ms | 4857 | 320 | 74.1328 | 413.091 | 0.000756487 | 0.496814 | 1.54128 | 0.245419 | 0.000205888 | 1.9302e-05 | 1.2868e-06 | 1(Win) | true |
| simdjson (reflection) | 8381.78 | 0.0405789 | 789.997ms | 4857 | 640 | 32.1843 | 552.627 | 0.0810808 | 0.649053 | 1.94173 | 0.303891 | 0.000205888 | 2.2519e-05 | 3.21701e-07 | 2(Loss) | true |
| Glaze | 4877.52 | 0.0801793 | 828.621ms | 4857 | 4890 | 2835.12 | 949.663 | 0.142417 | 1.07887 | 3.23286 | 0.496603 | 0.000209341 | 5.27984e-05 | 1.85679e-05 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2157.35 | 0.0471755 | 1039.38ms | 6701 | 4890 | 9549.48 | 2962.23 | 0.153977 | 2.36684 | 9.1655 | 1.46202 | 0.00068442 | 6.06691e-05 | 3.05482e-05 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1992.17 | 0.160648 | 1066.67ms | 6701 | 40 | 1062.28 | 3207.85 | 0.114691 | 2.57339 | 9.6311 | 1.63483 | 0.00139531 | 0.000179078 | 6.34234e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1985.75 | 0.0480436 | 1063.72ms | 6701 | 1280 | 3059.92 | 3218.21 | 0.0558901 | 2.57609 | 10.5832 | 2.13968 | 0.000305458 | 4.62851e-05 | 7.81133e-06 | 2(Tie) | true |
| Jsonifier | 1948.39 | 0.140484 | 1071.36ms | 6701 | 640 | 13588 | 3279.92 | 0.116721 | 2.62576 | 9.11237 | 1.80242 | 0.00128852 | 6.22575e-05 | 3.56756e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1751.1 | 0.0570504 | 1109.95ms | 6701 | 2560 | 11097.2 | 3649.45 | 0.313893 | 2.89074 | 10.5678 | 1.92598 | 0.00121874 | 7.98621e-05 | 3.88818e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2679.45 | 0.0390268 | 1006.8ms | 6701 | 4890 | 4236.65 | 2385.03 | 0.0311706 | 1.91449 | 7.62513 | 1.10357 | 0.000892764 | 4.76381e-05 | 1.77003e-05 | 1(Win) | true |
| Glaze | 2613 | 0.0858769 | 1015.67ms | 6701 | 160 | 705.789 | 2445.69 | 0.0898734 | 1.96868 | 8.4862 | 1.65811 | 0.00102783 | 1.95866e-05 | 2.79809e-06 | 2(Loss) | true |
| Jsonifier | 2378.23 | 0.0718172 | 1035.08ms | 6701 | 2560 | 9533.89 | 2687.12 | 0.0191124 | 2.15098 | 7.57574 | 1.44531 | 0.00134268 | 5.54372e-05 | 1.81876e-05 | 3(Loss) | true |
| simdjson (reflection) | 2300.57 | 0.0725017 | 1053.62ms | 6701 | 320 | 1297.94 | 2777.82 | 0.165884 | 2.23417 | 8.76466 | 1.42277 | 0.000735431 | 2.09857e-05 | 3.26444e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2092.19 | 0.0828414 | 1072.54ms | 6701 | 640 | 4097.83 | 3054.49 | 0.224878 | 2.43852 | 8.96001 | 1.56887 | 0.00196986 | 3.82406e-05 | 3.73079e-06 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14759 | 0.07492 | 783.513ms | 7376 | 2560 | 326.411 | 476.612 | 0.0388635 | 0.370726 | 1.15727 | 0.180992 | 0.000135734 | 2.87567e-05 | 1.22865e-05 | 1(Win) | true |
| Glaze | 3147.96 | 0.341799 | 967.19ms | 7376 | 640 | 37334 | 2234.56 | 0.00594322 | 1.62063 | 4.11253 | 0.684111 | 0.000139388 | 5.63483e-05 | 1.6735e-05 | 2(Loss) | true |
| simdjson (reflection) | 490.348 | 0.080977 | 2185.99ms | 7376 | 4890 | 659881 | 14345.5 | 0.0356595 | 10.2589 | 40.1205 | 8.20757 | 0.0125973 | 0.00018706 | 0.000107989 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16669.7 | 0.0953438 | 777.765ms | 7376 | 320 | 51.799 | 421.981 | 0.0118475 | 0.3335 | 1.07402 | 0.161605 | 0.000135575 | 1.48285e-05 | 4.23671e-06 | 1(Win) | true |
| Glaze | 3616.07 | 0.133298 | 933.274ms | 7376 | 4890 | 32879.4 | 1945.29 | 0.345976 | 1.42456 | 3.79799 | 0.61307 | 0.000211375 | 4.7271e-05 | 1.93797e-05 | 2(Loss) | true |
| simdjson (reflection) | 504.295 | 0.125281 | 2142.89ms | 7376 | 2560 | 781781 | 13948.8 | 0.191612 | 9.9339 | 39.1755 | 8.01878 | 0.013427 | 0.000194518 | 0.000108089 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1983.11 | 0.23005 | 820.815ms | 1691 | 30 | 104.993 | 813.2 | 0.213605 | 2.69042 | 9.07688 | 1.55884 | 0.000591366 | 0.000216834 | 0.000118273 | 1(Win) | true |
| Glaze | 1937.52 | 0.104847 | 818.053ms | 1691 | 320 | 243.703 | 832.334 | 0.00788507 | 2.73832 | 10.0727 | 1.97575 | 0.00114023 | 0.000125665 | 4.25044e-05 | 2(Loss) | true |
| Jsonifier | 1892.56 | 0.0925897 | 823.616ms | 1691 | 4890 | 3043.85 | 852.107 | 0.22181 | 2.82232 | 8.90597 | 1.44293 | 0.00178039 | 0.000128553 | 6.80857e-05 | 3(Loss) | true |
| simdjson (reflection) | 1790.75 | 0.29647 | 824.418ms | 1691 | 40 | 285.126 | 900.55 | 0.230806 | 2.95296 | 9.87995 | 1.72028 | 0.000591366 | 4.43525e-05 | 4.43525e-05 | 4(Loss) | true |
| Jsonifier (two-stage) | 1726.44 | 0.14394 | 835.968ms | 1691 | 80 | 144.623 | 934.1 | 0.16566 | 3.06045 | 10.3572 | 1.65464 | 0.000753992 | 4.43525e-05 | 0 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 2371.08 | 0.0625871 | 815.413ms | 1691 | 640 | 115.97 | 680.139 | 0.228062 | 2.22729 | 8.57363 | 1.60201 | 0.00114762 | 3.78844e-05 | 2.77203e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2368.15 | 0.0746208 | 811.646ms | 1691 | 1280 | 330.52 | 680.98 | 0.0286729 | 2.27121 | 7.80012 | 1.23655 | 0.000592752 | 0.000137677 | 4.48145e-05 | 1(Tie) | true |
| Jsonifier | 2331.45 | 0.117496 | 818.151ms | 1691 | 40 | 26.4205 | 691.7 | 0.0144592 | 2.33371 | 7.3974 | 1.06801 | 0.0017741 | 1.47842e-05 | 1.47842e-05 | 3(Loss) | true |
| Jsonifier (two-stage) | 2043.61 | 0.173741 | 826.901ms | 1691 | 40 | 75.1891 | 789.125 | 0.0643759 | 2.55924 | 8.84565 | 1.27912 | 0.000591366 | 5.91366e-05 | 0 | 4(Loss) | true |
| simdjson (reflection) | 1988.74 | 0.233419 | 826.192ms | 1691 | 2560 | 9171.62 | 810.898 | 0.0748512 | 2.66987 | 9.03075 | 1.48374 | 0.000595062 | 0.000124972 | 3.09543e-05 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8667.2 | 0.143843 | 747.768ms | 1996 | 80 | 7.98418 | 219.625 | 0.514874 | 0.704997 | 1.46743 | 0.248998 | 0.000501002 | 1.25251e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6586.34 | 0.0653731 | 755.343ms | 1996 | 320 | 11.423 | 289.012 | 0.460651 | 0.884109 | 1.87926 | 0.273547 | 0.000501002 | 9.39379e-06 | 0 | 2(Loss) | true |
| Glaze | 4584.9 | 0.325929 | 771.84ms | 1996 | 1280 | 2343.79 | 415.175 | 0.347287 | 1.22322 | 3.57716 | 0.596694 | 0.00248113 | 4.42291e-05 | 2.03532e-05 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10155.8 | 0.290181 | 747.249ms | 1996 | 30 | 8.87471 | 187.433 | 0.0888415 | 0.624916 | 1.30661 | 0.210421 | 0.000501002 | 3.34001e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 7723.81 | 0.117398 | 752.254ms | 1996 | 160 | 13.3937 | 246.45 | 0.249148 | 0.781588 | 1.71743 | 0.233968 | 0.000501002 | 0 | 0 | 2(Loss) | true |
| Glaze | 5784.61 | 0.566476 | 760.712ms | 1996 | 160 | 555.976 | 329.069 | 0.987287 | 0.993847 | 2.96042 | 0.462926 | 0.00149674 | 6.26253e-06 | 0 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2344.5 | 0.238316 | 823.375ms | 2158 | 4890 | 21400.2 | 877.813 | 0.103214 | 2.26398 | 7.49954 | 1.25672 | 0.000466614 | 0.000145082 | 4.70025e-05 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2198.88 | 0.202096 | 827.899ms | 2158 | 4890 | 17495.5 | 935.945 | 0.0847393 | 2.41255 | 8.14747 | 1.38788 | 0.000469173 | 0.00011618 | 2.71023e-05 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2185.67 | 0.298137 | 827.163ms | 2158 | 2560 | 20174.6 | 941.602 | 0.0350012 | 2.43246 | 8.48147 | 1.29472 | 0.000474615 | 0.00013051 | 6.31734e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1996.18 | 0.205819 | 832.75ms | 2158 | 4890 | 22018.2 | 1030.98 | 0.006501 | 2.65121 | 9.67563 | 1.88879 | 0.000520629 | 0.000106703 | 4.76659e-05 | 4(Tie) | true |
| Jsonifier STATISTICAL TIE | 1991.09 | 0.186387 | 835.282ms | 2158 | 4890 | 18149.3 | 1033.62 | 0.107635 | 2.65943 | 8.68119 | 1.54171 | 0.000879308 | 9.3626e-05 | 2.53018e-05 | 4(Tie) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2865.99 | 0.186378 | 814.299ms | 2158 | 80 | 143.296 | 718.087 | 0.0191518 | 1.86866 | 6.37998 | 0.980074 | 0.000463392 | 5.7924e-05 | 2.31696e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2645.47 | 0.0956012 | 816.835ms | 2158 | 320 | 177 | 777.944 | 0.313944 | 2.02953 | 7.29703 | 1.00046 | 0.00046484 | 3.33063e-05 | 2.8962e-06 | 2(Loss) | true |
| simdjson (reflection) | 2453.28 | 0.261685 | 827.875ms | 2158 | 4890 | 23565.4 | 838.89 | 0.830104 | 2.18517 | 7.36284 | 1.17841 | 0.000466898 | 8.21597e-05 | 1.00449e-05 | 3(Loss) | true |
| Jsonifier | 2401.77 | 0.304529 | 827.583ms | 2158 | 2560 | 17431.6 | 856.881 | 0.28778 | 2.22369 | 7.43883 | 1.23633 | 0.00065617 | 0.000108789 | 2.57038e-05 | 4(Loss) | true |
| Glaze | 2295.82 | 0.252267 | 828.476ms | 2158 | 640 | 3272.87 | 896.425 | 0.173558 | 2.28901 | 8.56024 | 1.60797 | 0.000540865 | 0.000105711 | 4.41671e-05 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10958.5 | 0.215621 | 755.161ms | 2866 | 4890 | 1414.3 | 249.417 | 0.434199 | 0.550543 | 1.14515 | 0.188765 | 0.000349061 | 0.000109099 | 5.97228e-05 | 1(Win) | true |
| Glaze | 3798.38 | 0.43007 | 807.126ms | 2866 | 640 | 6129.34 | 719.578 | 0.0334286 | 1.41473 | 4.0157 | 0.667132 | 0.000360912 | 4.63407e-05 | 1.79911e-05 | 2(Loss) | true |
| simdjson (reflection) | 528.114 | 0.0622207 | 1261.75ms | 2866 | 4890 | 50707.8 | 5175.45 | 0.0221977 | 9.65375 | 35.7282 | 7.50593 | 0.00806237 | 0.000170392 | 7.35654e-05 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13851.4 | 0.138653 | 745.252ms | 2866 | 40 | 2.99423 | 197.325 | 0.283754 | 0.449154 | 0.963364 | 0.146546 | 0.000348918 | 0 | 0 | 1(Win) | true |
| Glaze | 4455.63 | 0.443148 | 794.23ms | 2866 | 2560 | 18917.9 | 613.434 | 0.217104 | 1.22139 | 3.3709 | 0.529658 | 0.000349464 | 3.42104e-05 | 1.64918e-05 | 2(Loss) | true |
| simdjson (reflection) | 525.855 | 0.0860859 | 1261.76ms | 2866 | 2560 | 51253.5 | 5197.69 | 0.119307 | 9.69298 | 35.7654 | 7.51466 | 0.00853637 | 0.000164237 | 5.23378e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2278.59 | 0.0371722 | 915.7ms | 4390 | 640 | 298.549 | 1837.38 | 0.296333 | 2.2858 | 10.4321 | 1.70866 | 0.00164614 | 2.7406e-05 | 4.98292e-06 | 1(Win) | true |
| Glaze | 1833.07 | 0.050022 | 960.26ms | 4390 | 4890 | 6382.67 | 2283.95 | 0.0359682 | 2.81815 | 13.0267 | 2.59021 | 0.00058783 | 2.64591e-05 | 1.00619e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1669.13 | 0.0395575 | 982.229ms | 4390 | 4890 | 4814.13 | 2508.28 | 0.255029 | 3.07469 | 13.8091 | 2.24579 | 0.00345137 | 5.72504e-05 | 1.34159e-05 | 3(Loss) | true |
| simdjson (reflection) | 1369.11 | 0.0511302 | 1037.55ms | 4390 | 4890 | 11954.1 | 3057.92 | 0.159891 | 3.76786 | 14.1729 | 2.44898 | 0.00380638 | 5.9859e-05 | 2.16611e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1134.44 | 0.0802484 | 1101.49ms | 4390 | 1280 | 11226.6 | 3690.48 | 0.0189925 | 4.50241 | 16.8497 | 2.94989 | 0.00241298 | 5.33884e-05 | 2.3135e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2669.41 | 0.0938232 | 910.642ms | 4390 | 160 | 346.45 | 1568.38 | 0.175649 | 1.99399 | 9.26788 | 1.43736 | 0.00140091 | 3.13212e-05 | 1.42369e-06 | 1(Win) | true |
| Glaze | 2107.28 | 0.0383767 | 951.089ms | 4390 | 4890 | 2842.68 | 1986.74 | 0.0227908 | 2.4463 | 11.6367 | 2.27198 | 0.000842312 | 1.73754e-05 | 3.77322e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1906.73 | 0.0869092 | 977.901ms | 4390 | 640 | 2330.56 | 2195.71 | 0.0282432 | 2.7268 | 12.6421 | 1.9738 | 0.00323213 | 3.34567e-05 | 6.05068e-06 | 3(Loss) | true |
| simdjson (reflection) | 1495.72 | 0.143484 | 1028.22ms | 4390 | 320 | 5161.67 | 2799.08 | 0.0207614 | 3.43001 | 13.0998 | 2.19772 | 0.00359624 | 1.92198e-05 | 5.69476e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1244.99 | 0.0385822 | 1092.03ms | 4390 | 4890 | 8231.58 | 3362.8 | 0.170263 | 4.11058 | 15.7219 | 2.69362 | 0.00275757 | 3.61018e-05 | 4.47196e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12924.2 | 0.249992 | 758.627ms | 4390 | 80 | 52.4644 | 323.938 | 0.664232 | 0.443798 | 1.77472 | 0.285194 | 0.00022779 | 6.54897e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 8331.6 | 0.249499 | 780.428ms | 4390 | 30 | 47.1552 | 502.5 | 0.232713 | 0.669894 | 2.52346 | 0.390888 | 0.00022779 | 6.83371e-05 | 4.55581e-05 | 2(Loss) | true |
| Glaze | 3909.92 | 0.206665 | 842.459ms | 4390 | 2560 | 12536.3 | 1070.77 | 0.0423362 | 1.357 | 4.76492 | 0.751481 | 0.000229303 | 3.48804e-05 | 1.20124e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14255.9 | 0.0621549 | 755.836ms | 4390 | 640 | 21.324 | 293.677 | 0.415117 | 0.404382 | 1.66743 | 0.260137 | 0.00022779 | 1.06777e-05 | 1.06777e-06 | 1(Win) | true |
| simdjson (reflection) | 8913.41 | 0.170826 | 776.672ms | 4390 | 80 | 51.5038 | 469.7 | 0.238942 | 0.624539 | 2.40979 | 0.364692 | 0.00022779 | 2.84738e-06 | 0 | 2(Loss) | true |
| Glaze | 4152.21 | 0.331256 | 830.519ms | 4390 | 2560 | 28558.7 | 1008.29 | 0.276852 | 1.28001 | 4.36743 | 0.663098 | 0.000229837 | 2.7762e-05 | 1.11226e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3227.03 | 0.0828996 | 1014.07ms | 9378 | 1280 | 6756.6 | 2771.45 | 0.00109937 | 1.60936 | 7.33579 | 1.10845 | 0.00147661 | 1.92438e-05 | 1.99936e-06 | 1(Win) | true |
| Jsonifier | 3013.81 | 0.0511216 | 1027.36ms | 9378 | 4890 | 11254 | 2967.53 | 0.14665 | 1.70922 | 7.4678 | 1.45063 | 0.00251686 | 5.59984e-05 | 2.50772e-05 | 2(Loss) | true |
| simdjson (reflection) | 2688.71 | 0.144863 | 1071.2ms | 9378 | 30 | 696.575 | 3326.33 | 0.0380945 | 1.9405 | 7.37695 | 1.18693 | 0.00234947 | 1.77721e-05 | 1.06633e-05 | 3(Loss) | true |
| Glaze | 2334.78 | 0.101738 | 1114.71ms | 9378 | 640 | 9720.14 | 3830.58 | 0.0232857 | 2.18753 | 9.47121 | 1.81009 | 0.00368665 | 9.83019e-06 | 1.66613e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2284.7 | 0.036902 | 1123.64ms | 9378 | 4890 | 10204 | 3914.54 | 0.125883 | 2.23955 | 8.58947 | 1.41128 | 0.00120776 | 3.29274e-05 | 1.53298e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3507.51 | 0.0729885 | 1014.74ms | 9378 | 1280 | 4433.45 | 2549.83 | 0.109171 | 1.47188 | 6.78951 | 0.981126 | 0.00162498 | 1.34957e-05 | 2.08267e-06 | 1(Win) | true |
| Jsonifier | 3299.88 | 0.11068 | 1028.16ms | 9378 | 1280 | 11517.9 | 2710.27 | 0.0370271 | 1.55519 | 6.92237 | 1.32363 | 0.00241723 | 2.01602e-05 | 2.91573e-06 | 2(Loss) | true |
| simdjson (reflection) | 2884.14 | 0.0488267 | 1061.37ms | 9378 | 320 | 733.589 | 3100.94 | 0.0340738 | 1.77815 | 6.8746 | 1.06931 | 0.00219763 | 1.4662e-05 | 1.66613e-06 | 3(Loss) | true |
| Glaze | 2593.16 | 0.129343 | 1104.34ms | 9378 | 30 | 596.99 | 3448.9 | 0.0222244 | 2.01172 | 8.81926 | 1.66112 | 0.00368593 | 3.19898e-05 | 1.42177e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2481.98 | 0.0378192 | 1116.39ms | 9378 | 4890 | 9081.53 | 3603.4 | 0.310516 | 2.07105 | 8.07315 | 1.29367 | 0.00136712 | 2.78466e-05 | 6.01852e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 25597.2 | 0.184093 | 770.944ms | 11521 | 320 | 199.812 | 429.238 | 0.154106 | 0.219998 | 0.741689 | 0.110841 | 8.6798e-05 | 6.7811e-06 | 1.08498e-06 | 1(Win) | true |
| Glaze | 5674.69 | 0.131095 | 929.945ms | 11521 | 2560 | 16493.2 | 1936.19 | 0.102675 | 0.90978 | 3.90947 | 0.664179 | 0.000216351 | 4.28904e-05 | 1.38673e-05 | 2(Loss) | true |
| simdjson (reflection) | 522.241 | 0.17484 | 2843.1ms | 11521 | 2560 | 3.46388e+06 | 21038.7 | 0.505456 | 9.58963 | 38.2767 | 7.05729 | 0.010832 | 0.000159593 | 9.57152e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 29988.9 | 0.171985 | 761.811ms | 11521 | 2560 | 1016.44 | 366.379 | 0.0468272 | 0.18986 | 0.691781 | 0.0991235 | 8.70015e-05 | 1.34944e-05 | 6.03517e-06 | 1(Win) | true |
| Glaze | 7021.02 | 0.111293 | 884.575ms | 11521 | 4890 | 14833 | 1564.91 | 0.493713 | 0.742004 | 3.64795 | 0.607847 | 0.000264512 | 2.46904e-05 | 1.58863e-05 | 2(Loss) | true |
| simdjson (reflection) | 519.521 | 0.126845 | 2857.24ms | 11521 | 4890 | 3.51908e+06 | 21148.9 | 0.317751 | 9.63582 | 38.2433 | 7.04635 | 0.0121152 | 0.000249069 | 0.000160993 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3273.17 | 0.31266 | 871.309ms | 4669 | 30 | 542.723 | 1360.37 | 0.0636678 | 1.63424 | 6.43992 | 1.37117 | 0.00122796 | 4.28357e-05 | 1.42786e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2191.16 | 0.0797685 | 937.768ms | 4669 | 4890 | 12849.1 | 2032.13 | 0.0248803 | 2.35069 | 9.30628 | 1.69758 | 0.00109468 | 0.000120185 | 8.26493e-05 | 2(Loss) | true |
| Glaze | 2087.1 | 0.139498 | 948.921ms | 4669 | 1280 | 11337.2 | 2133.45 | 0.107409 | 2.46743 | 9.56672 | 1.81174 | 0.000984552 | 9.92249e-05 | 5.63892e-05 | 3(Loss) | true |
| simdjson (reflection) | 1572.15 | 0.251656 | 1024.44ms | 4669 | 1280 | 65025.7 | 2832.25 | 0.450149 | 3.24025 | 12.8377 | 2.00621 | 0.000813377 | 0.000172849 | 0.000121312 | 4(Loss) | true |
| simdjson (ondemand) | 1468.94 | 0.0616755 | 1049.15ms | 4669 | 4890 | 17091.3 | 3031.24 | 0.438159 | 3.48329 | 14.0268 | 2.39238 | 0.00143338 | 0.000134289 | 8.80804e-05 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3540.78 | 0.524228 | 864.379ms | 4669 | 40 | 1738.41 | 1257.55 | 0.0756008 | 1.49314 | 5.99058 | 1.26087 | 0.00102806 | 0.000182052 | 7.49625e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2326.31 | 0.0893735 | 947.482ms | 4669 | 2560 | 7491.53 | 1914.06 | 0.99638 | 2.20318 | 8.85736 | 1.58706 | 0.0011026 | 0.000106253 | 6.1158e-05 | 2(Loss) | true |
| Glaze | 2292.61 | 0.209523 | 931.047ms | 4669 | 640 | 10598.2 | 1942.2 | 0.108403 | 2.24536 | 8.88263 | 1.65282 | 0.000990576 | 2.81109e-05 | 6.35843e-06 | 3(Loss) | true |
| simdjson (reflection) | 1609.84 | 0.393118 | 1041.74ms | 4669 | 1280 | 151334 | 2765.92 | 1.05872 | 3.18613 | 12.541 | 1.92889 | 0.000893024 | 0.00022037 | 0.000163813 | 4(Loss) | true |
| simdjson (ondemand) | 1593.47 | 0.0568534 | 1063.49ms | 4669 | 160 | 403.826 | 2794.35 | 0.71329 | 3.22302 | 13.3127 | 2.23345 | 0.0014698 | 1.60634e-05 | 0 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11898.6 | 0.268825 | 782.35ms | 4669 | 1280 | 1295.4 | 374.22 | 0.502721 | 0.472671 | 1.25701 | 0.317841 | 0.000217358 | 7.26199e-05 | 4.66842e-05 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 7308.65 | 0.686158 | 817.259ms | 4669 | 640 | 11184.1 | 609.237 | 4.0459 | 0.747989 | 1.68344 | 0.226387 | 0.0002366 | 0.000142228 | 0.00011646 | -(Loss) | false |
| Glaze | 3603.67 | 0.144155 | 879.295ms | 4669 | 4890 | 15514.1 | 1235.6 | 0.429907 | 1.44543 | 3.46177 | 0.499465 | 0.000223245 | 0.000160218 | 9.17158e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13802.6 | 0.066293 | 780.976ms | 4669 | 320 | 14.6357 | 322.6 | 0.0735664 | 0.413292 | 1.1495 | 0.292996 | 0.000214179 | 2.34258e-05 | 1.33862e-06 | 1(Win) | true |
| simdjson (reflection) | 8579.19 | 0.0905588 | 813.68ms | 4669 | 160 | 35.3458 | 519.013 | 0.424481 | 0.639453 | 1.57721 | 0.201542 | 0.000214179 | 1.87406e-05 | 1.33862e-06 | 2(Loss) | true |
| Glaze | 4350.01 | 0.172433 | 854.128ms | 4669 | 1280 | 3987.67 | 1023.61 | 0.292452 | 1.20884 | 2.95716 | 0.386378 | 0.000219031 | 3.86525e-05 | 1.99119e-05 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3283.26 | 0.0773581 | 966.023ms | 7932 | 2560 | 8132.14 | 2303.97 | 0.0450446 | 1.56647 | 6.22126 | 1.04476 | 0.000703145 | 6.78127e-05 | 4.01361e-05 | 1(Win) | true |
| Jsonifier | 2850.14 | 0.123127 | 1008.93ms | 7932 | 40 | 427.169 | 2654.1 | 0.35666 | 1.80292 | 6.37179 | 1.45386 | 0.000961296 | 1.5759e-05 | 3.15179e-06 | 2(Loss) | true |
| simdjson (reflection) | 2560.31 | 0.110017 | 1031.82ms | 7932 | 4890 | 51666.4 | 2954.54 | 0.213829 | 1.98594 | 8.13971 | 1.20601 | 0.000457416 | 6.65421e-05 | 3.84145e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2379.3 | 0.1568 | 1058.38ms | 7932 | 640 | 15905.3 | 3179.32 | 0.0122849 | 2.15773 | 8.83586 | 1.4318 | 0.000937067 | 5.55503e-05 | 3.17149e-05 | 4(Loss) | true |
| Glaze | 2342.69 | 0.342638 | 1077.78ms | 7932 | 160 | 19585.1 | 3228.99 | 0.0125829 | 2.18075 | 8.47832 | 1.65003 | 0.00169172 | 0.000113464 | 8.82501e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3513.39 | 0.0866598 | 978.128ms | 7932 | 320 | 1114.03 | 2153.06 | 0.304124 | 1.46726 | 5.95701 | 0.979702 | 0.000668573 | 5.20045e-05 | 3.15179e-05 | 1(Win) | true |
| Jsonifier | 2975.21 | 0.0727121 | 997.655ms | 7932 | 4890 | 16713 | 2542.53 | 0.19761 | 1.72573 | 6.10918 | 1.38918 | 0.000980471 | 4.25653e-05 | 2.23784e-05 | 2(Loss) | true |
| simdjson (reflection) | 2655.76 | 0.0622585 | 1026.7ms | 7932 | 2560 | 8050.57 | 2848.36 | 0.506627 | 1.92718 | 7.96508 | 1.16049 | 0.000588449 | 4.18105e-05 | 2.00434e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2542.94 | 0.122098 | 1038.81ms | 7932 | 1280 | 16885.9 | 2974.72 | 0.0302195 | 2.01434 | 8.41553 | 1.33825 | 0.000965531 | 3.52607e-05 | 2.04866e-05 | 4(Loss) | true |
| Glaze | 2482.36 | 0.111474 | 1048.36ms | 7932 | 1280 | 14770.4 | 3047.32 | 0.137142 | 2.05263 | 8.07527 | 1.55648 | 0.00205044 | 4.02838e-05 | 1.98957e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21001.3 | 0.230022 | 776.116ms | 9249 | 30 | 28 | 420 | 0.395257 | 0.264313 | 0.726673 | 0.164775 | 0.00010812 | 1.802e-05 | 0 | 1(Win) | true |
| Glaze | 2838.84 | 0.12654 | 1049.58ms | 9249 | 4890 | 75591.3 | 3107.09 | 0.197673 | 1.81057 | 3.79479 | 0.625365 | 0.000329135 | 5.62046e-05 | 2.61124e-05 | 2(Loss) | true |
| simdjson (reflection) | 520.344 | 0.176969 | 2434.64ms | 9249 | 640 | 575947 | 16951.4 | 0.133122 | 9.64955 | 40.7763 | 8.32101 | 0.0131945 | 0.000153902 | 9.25776e-05 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24212.3 | 0.300556 | 766.393ms | 9249 | 80 | 95.9089 | 364.3 | 0.29596 | 0.23197 | 0.657152 | 0.147908 | 0.00010812 | 2.1624e-05 | 1.3515e-05 | 1(Win) | true |
| Glaze | 2893.06 | 0.202607 | 1042.17ms | 9249 | 1280 | 48841.8 | 3048.86 | 0.163191 | 1.79375 | 3.52752 | 0.565359 | 0.000379011 | 2.42425e-05 | 1.15722e-05 | 2(Loss) | true |
| simdjson (reflection) | 520.054 | 0.150468 | 2441.37ms | 9249 | 640 | 416830 | 16960.8 | 0.230046 | 9.69367 | 40.7874 | 8.32303 | 0.0143825 | 0.000296316 | 0.000198332 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 841.23 | 0.0970745 | 1266.11ms | 4604 | 40 | 1026.86 | 5219.4 | 0.244003 | 6.0694 | 23.3345 | 5.00065 | 0.00616855 | 2.17202e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 720.093 | 0.105459 | 1356.99ms | 4604 | 30 | 1240.46 | 6097.43 | 0.0125752 | 7.07194 | 26.6568 | 5.32276 | 0.00607443 | 0.000304083 | 0.000152042 | 2(Loss) | true |
| Glaze | 651.379 | 0.0539626 | 1411.45ms | 4604 | 1280 | 16935.5 | 6740.65 | 0.309344 | 7.80353 | 33.3243 | 6.80713 | 0.00603263 | 0.000218899 | 0.000135412 | 3(Loss) | true |
| simdjson (reflection) | 628.434 | 0.0418318 | 1439.31ms | 4604 | 2560 | 21867.8 | 6986.76 | 0.584303 | 8.04129 | 29.0747 | 5.57146 | 0.00502679 | 7.66148e-05 | 3.13077e-05 | 4(Loss) | true |
| simdjson (ondemand) | 548.851 | 0.0588905 | 1543.16ms | 4604 | 1280 | 28409.4 | 7999.83 | 0.0164386 | 9.26353 | 36.2589 | 6.74414 | 0.00651132 | 0.000360929 | 0.000239432 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1046.88 | 0.0602136 | 1257.32ms | 4604 | 2560 | 16327 | 4194.1 | 0.103358 | 4.89878 | 18.9029 | 3.99587 | 0.00498149 | 0.000181822 | 0.000107244 | 1(Win) | true |
| Jsonifier (two-stage) | 859.103 | 0.0603699 | 1344.77ms | 4604 | 80 | 761.572 | 5110.81 | 0.15653 | 5.93711 | 22.4411 | 4.36425 | 0.00504181 | 6.24457e-05 | 5.43006e-06 | 2(Loss) | true |
| Glaze | 761.466 | 0.0911596 | 1402.82ms | 4604 | 4890 | 135109 | 5766.13 | 0.0640145 | 6.67687 | 28.8123 | 5.77031 | 0.00544503 | 0.000108379 | 5.22796e-05 | 3(Loss) | true |
| simdjson (reflection) | 714.464 | 0.157993 | 1452.05ms | 4604 | 1280 | 120670 | 6145.47 | 0.124467 | 7.1008 | 27.2059 | 5.11316 | 0.00233391 | 0.000110298 | 3.86892e-05 | 4(Loss) | true |
| simdjson (ondemand) | 617.42 | 0.0578253 | 1552.72ms | 4604 | 2560 | 43289.7 | 7111.39 | 0.0123521 | 8.22959 | 33.5301 | 6.10735 | 0.00509526 | 0.000197943 | 0.000102323 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1515.79 | 0.0962987 | 1044.05ms | 4918 | 40 | 355.138 | 3094.2 | 0.144565 | 3.44356 | 11.3813 | 1.3477 | 0.000625254 | 5.08337e-06 | 5.08337e-06 | 1(Win) | true |
| Jsonifier | 1385.21 | 0.453896 | 1056.52ms | 4604 | 320 | 66237.3 | 3169.71 | 0.137524 | 3.76535 | 9.57407 | 0.569505 | 0.000496172 | 5.63369e-05 | 2.5114e-05 | 2(Loss) | true |
| Glaze | 1178.77 | 0.126395 | 1108.01ms | 4604 | 640 | 14185.8 | 3724.83 | 0.0224054 | 4.36085 | 12.7743 | 1.08645 | 0.000458161 | 4.00467e-05 | 5.09068e-06 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1550.5 | 0.118149 | 1037.54ms | 4918 | 40 | 510.921 | 3024.95 | 0.00606107 | 3.36982 | 11.2666 | 1.32168 | 0.000706588 | 1.01667e-05 | 0 | 1(Win) | true |
| Jsonifier | 1426.33 | 0.116892 | 1038.31ms | 4604 | 4890 | 63316 | 3078.34 | 0.189083 | 3.61191 | 9.44961 | 0.539966 | 0.000490371 | 8.59038e-05 | 4.86818e-05 | 2(Loss) | true |
| Glaze | 1273.29 | 0.114237 | 1077.98ms | 4604 | 1280 | 19862.6 | 3448.31 | 0.0322272 | 4.0676 | 12.2183 | 0.967204 | 0.000576435 | 4.66646e-05 | 2.00233e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2560.91 | 0.120923 | 1418.82ms | 18245 | 30 | 2025.07 | 6794.37 | 0.0147159 | 1.9872 | 7.71203 | 1.39008 | 0.00145428 | 3.28857e-05 | 1.82698e-06 | 1(Win) | true |
| Jsonifier | 2248.98 | 0.0483184 | 1512.11ms | 18245 | 2560 | 35775.1 | 7736.74 | 0.0314245 | 2.25474 | 7.96379 | 1.81003 | 0.00191891 | 5.81709e-05 | 3.32069e-05 | 2(Loss) | true |
| simdjson (reflection) | 2240.92 | 0.0645641 | 1540.6ms | 18245 | 2560 | 64336.4 | 7764.57 | 0.234615 | 2.25528 | 8.34771 | 1.44111 | 0.00140437 | 8.36488e-05 | 5.96696e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1998.49 | 0.124056 | 1619.42ms | 18245 | 40 | 4666.36 | 8706.45 | 0.0457725 | 2.54278 | 10.2727 | 1.76087 | 0.00183886 | 4.52179e-05 | 3.69964e-05 | 4(Loss) | true |
| Glaze | 1814.16 | 0.0268287 | 1696.82ms | 18245 | 4890 | 32377.5 | 9591.1 | 0.261955 | 2.79506 | 12.1724 | 2.39934 | 0.0033675 | 5.47087e-05 | 3.33341e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2999.68 | 0.125368 | 1417.25ms | 18245 | 640 | 33844.9 | 5800.55 | 0.146565 | 1.69894 | 6.65185 | 1.14936 | 0.00137598 | 4.34194e-05 | 2.7833e-05 | 1(Win) | true |
| Jsonifier | 2608.22 | 0.0319259 | 1514.74ms | 18245 | 4890 | 22181.7 | 6671.13 | 0.155662 | 1.95536 | 6.90348 | 1.56925 | 0.00179362 | 2.87722e-05 | 1.54565e-05 | 2(Loss) | true |
| simdjson (reflection) | 2529.17 | 0.0461006 | 1532.05ms | 18245 | 2560 | 25750.4 | 6879.63 | 0.0195986 | 2.00871 | 7.91274 | 1.33291 | 0.000531781 | 4.46184e-05 | 2.72121e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2244.66 | 0.0669054 | 1619.1ms | 18245 | 320 | 8607.16 | 7751.64 | 0.1202 | 2.26498 | 9.44692 | 1.57084 | 0.00101346 | 4.52179e-05 | 2.39792e-05 | 4(Loss) | true |
| Glaze | 2006.92 | 0.0249625 | 1693.16ms | 18245 | 4890 | 22904.1 | 8669.92 | 0.121895 | 2.52658 | 11.048 | 2.14059 | 0.00341054 | 3.83218e-05 | 2.13858e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6531.82 | 0.145268 | 1094.83ms | 24579 | 4890 | 132895 | 3588.64 | 0.393067 | 0.787435 | 1.88991 | 0.106026 | 0.000104076 | 2.83631e-05 | 1.43854e-05 | 1(Win) | true |
| Glaze | 3374.03 | 0.113034 | 1432.69ms | 24579 | 2560 | 157867 | 6947.29 | 0.0619949 | 1.49834 | 3.92612 | 0.475854 | 0.000238564 | 3.2866e-05 | 1.58291e-05 | 2(Loss) | true |
| simdjson (reflection) | 525.651 | 0.10609 | 5278.2ms | 24893 | 4890 | 1.12257e+07 | 45162.7 | 0.141372 | 9.60629 | 36.8659 | 6.06448 | 0.0072327 | 8.40242e-05 | 4.99151e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6728.13 | 0.0815718 | 1082.8ms | 24579 | 4890 | 39493.8 | 3483.93 | 0.347025 | 0.768629 | 1.86908 | 0.101184 | 9.75278e-05 | 1.91029e-05 | 8.51143e-06 | 1(Win) | true |
| Glaze | 3795.82 | 0.119944 | 1353.19ms | 24579 | 2560 | 140448 | 6175.31 | 0.0608259 | 1.33968 | 3.77273 | 0.441597 | 0.000249053 | 1.00441e-05 | 2.73353e-06 | 2(Loss) | true |
| simdjson (reflection) | 520.126 | 0.144576 | 5295.72ms | 24893 | 2560 | 1.11473e+07 | 45642.4 | 0.0556113 | 9.69403 | 36.8706 | 6.06564 | 0.00802904 | 0.000135361 | 8.35294e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 918.708 | 0.174401 | 1211.49ms | 4604 | 160 | 11115.7 | 4779.23 | 0.224782 | 5.55724 | 21.8779 | 4.6262 | 0.00664639 | 0.000544364 | 0.000305441 | 1(Win) | true |
| Jsonifier (two-stage) | 768.461 | 0.0998602 | 1312.44ms | 4604 | 40 | 1302.18 | 5713.65 | 0.172106 | 6.75493 | 25.9333 | 5.13249 | 0.00598936 | 3.25804e-05 | 0 | 2(Loss) | true |
| Glaze | 673.331 | 0.0249277 | 1391.02ms | 4604 | 4890 | 12920.7 | 6520.89 | 0.164688 | 7.57267 | 32.0817 | 6.54084 | 0.00708959 | 7.32892e-05 | 3.1581e-05 | 3(Loss) | true |
| simdjson (reflection) | 630.728 | 0.0448428 | 1434.96ms | 4604 | 4890 | 47652.1 | 6961.35 | 0.017297 | 8.04444 | 29.1036 | 5.59362 | 0.00446891 | 0.000280809 | 0.000178293 | 4(Loss) | true |
| simdjson (ondemand) | 562.575 | 0.0645701 | 1516.09ms | 4604 | 80 | 2031.72 | 7804.68 | 0.0585844 | 9.0421 | 34.7144 | 6.58406 | 0.00689618 | 5.97307e-05 | 0 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1181.25 | 0.133661 | 1214.2ms | 4604 | 30 | 740.483 | 3717 | 0.0673038 | 4.42688 | 17.6757 | 3.67181 | 0.0056907 | 4.34405e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 910.938 | 0.0323426 | 1313.83ms | 4604 | 4890 | 11883.7 | 4819.99 | 0.230801 | 5.60163 | 21.7326 | 4.17832 | 0.00480777 | 0.000116641 | 6.05413e-05 | 2(Loss) | true |
| Glaze | 772.591 | 0.0499579 | 1387.3ms | 4604 | 2560 | 20635.7 | 5683.1 | 0.0763057 | 6.59516 | 27.9251 | 5.58819 | 0.00669747 | 7.88207e-05 | 3.1138e-05 | 3(Loss) | true |
| simdjson (reflection) | 712.944 | 0.0603763 | 1452.48ms | 4604 | 4890 | 67608.7 | 6158.58 | 0.0174498 | 7.15158 | 26.8792 | 5.05799 | 0.00194847 | 0.000231016 | 0.000126279 | 4(Loss) | true |
| simdjson (ondemand) | 614.521 | 0.0294351 | 1552.58ms | 4604 | 4890 | 21629 | 7144.94 | 0.094348 | 8.29179 | 33.3677 | 6.24609 | 0.0043039 | 0.000113043 | 5.06806e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1496.31 | 0.224943 | 1062.39ms | 4918 | 30 | 1491.43 | 3134.5 | 0.175159 | 3.42393 | 11.3863 | 1.34953 | 0.000711671 | 8.13339e-05 | 4.74448e-05 | 1(Win) | true |
| Jsonifier | 1269.78 | 0.125145 | 1081.94ms | 4604 | 4890 | 91568.3 | 3457.84 | 0.226119 | 4.03755 | 9.55148 | 0.56994 | 0.000317498 | 0.000281786 | 0.000199391 | 2(Loss) | true |
| Glaze | 1205.41 | 0.0737498 | 1100.5ms | 4604 | 2560 | 18474.1 | 3642.51 | 0.0408955 | 4.23938 | 12.7285 | 1.08666 | 0.000656359 | 0.000139739 | 7.24574e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1515.36 | 0.134367 | 1052.3ms | 4918 | 1280 | 22138.1 | 3095.1 | 0.0675008 | 3.38744 | 11.2717 | 1.32351 | 0.000676882 | 0.00016092 | 0.000117871 | 1(Win) | true |
| Jsonifier | 1311.8 | 0.496127 | 1086.45ms | 4604 | 320 | 88241.6 | 3347.1 | 0.438298 | 3.83771 | 9.42702 | 0.5404 | 0.000325804 | 0.000516535 | 0.000393001 | 2(Loss) | true |
| Glaze | 1286.28 | 0.129335 | 1072.12ms | 4604 | 1280 | 24948.1 | 3413.49 | 0.610232 | 4.01874 | 12.2024 | 0.968289 | 0.000813491 | 8.63719e-05 | 4.19133e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2658.81 | 0.0414011 | 1393.67ms | 18245 | 4890 | 35896 | 6544.19 | 0.0648154 | 1.91567 | 7.54887 | 1.3464 | 0.00153402 | 0.000107938 | 6.92125e-05 | 1(Win) | true |
| Jsonifier | 2362.51 | 0.051253 | 1475.02ms | 18245 | 1280 | 18238.4 | 7364.95 | 0.0172935 | 2.14952 | 7.84193 | 1.76289 | 0.00204846 | 2.91604e-05 | 1.63572e-05 | 2(Loss) | true |
| simdjson (reflection) | 2267.08 | 0.150779 | 1510.66ms | 18245 | 320 | 42853.6 | 7674.99 | 0.167667 | 2.23983 | 8.35418 | 1.44664 | 0.00138839 | 2.70622e-05 | 9.76295e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2084.52 | 0.107522 | 1593.46ms | 18245 | 40 | 3222.03 | 8347.15 | 0.0945327 | 2.48416 | 9.75201 | 1.69203 | 0.00207454 | 4.24774e-05 | 2.05536e-05 | 4(Loss) | true |
| Glaze | 1855.85 | 0.0941556 | 1703.43ms | 18245 | 320 | 24937 | 9375.64 | 0.227234 | 2.73484 | 11.7558 | 2.30617 | 0.00336942 | 3.7339e-05 | 2.141e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3118.44 | 0.0514256 | 1394.81ms | 18245 | 2560 | 21077.2 | 5579.65 | 0.0636645 | 1.63282 | 6.48886 | 1.10562 | 0.00125377 | 1.95045e-05 | 6.05902e-06 | 1(Win) | true |
| Jsonifier | 2739.86 | 0.0690875 | 1479.8ms | 18245 | 640 | 12319.9 | 6350.6 | 0.207546 | 1.85187 | 6.78175 | 1.52206 | 0.00183081 | 2.03823e-05 | 8.22143e-06 | 2(Loss) | true |
| simdjson (reflection) | 2540.19 | 0.168217 | 1529.4ms | 18245 | 160 | 21243 | 6849.79 | 0.0126845 | 2.00115 | 7.80049 | 1.31268 | 0.000901959 | 2.15813e-05 | 7.87887e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2214.02 | 0.0276397 | 1632.8ms | 18245 | 4890 | 23072.7 | 7858.89 | 0.196443 | 2.28675 | 9.41058 | 1.60663 | 0.00119067 | 3.17761e-05 | 1.45374e-05 | 4(Loss) | true |
| Glaze | 2031.72 | 0.0458394 | 1681.11ms | 18245 | 4890 | 75361.1 | 8564.08 | 0.154051 | 2.48963 | 10.7482 | 2.07657 | 0.00317224 | 2.82902e-05 | 9.25822e-06 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6262.95 | 0.246004 | 1111.83ms | 24579 | 640 | 54254.3 | 3742.7 | 0.0133611 | 0.825502 | 1.8862 | 0.105497 | 6.25534e-05 | 1.65283e-05 | 6.67491e-06 | 1(Win) | true |
| Glaze | 3226.12 | 0.133672 | 1468.84ms | 24579 | 1280 | 120743 | 7265.81 | 0.034138 | 1.57671 | 3.90728 | 0.475081 | 0.000331552 | 1.85626e-05 | 5.08564e-06 | 2(Loss) | true |
| simdjson (reflection) | 532.442 | 0.0909699 | 5225.91ms | 24893 | 4890 | 8.04478e+06 | 44586.7 | 0.034209 | 9.4776 | 36.868 | 6.06874 | 0.00791687 | 7.51191e-05 | 3.17925e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6484.69 | 0.0834382 | 1094.15ms | 24579 | 4890 | 44482.5 | 3614.72 | 0.583655 | 0.787912 | 1.86537 | 0.100655 | 6.39813e-05 | 1.81794e-05 | 7.72934e-06 | 1(Win) | true |
| Glaze | 3836.95 | 0.0982619 | 1346.55ms | 24579 | 2560 | 92250.1 | 6109.11 | 0.490417 | 1.3363 | 3.76179 | 0.442166 | 0.000381677 | 2.48084e-05 | 1.24916e-05 | 2(Loss) | true |
| simdjson (reflection) | 526.651 | 0.0935947 | 5257.49ms | 24893 | 4890 | 8.70403e+06 | 45076.9 | 0.565286 | 9.53346 | 36.8644 | 6.06753 | 0.00970081 | 0.000143855 | 8.36628e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1550.53 | 0.05799 | 1046.64ms | 5094 | 4890 | 16142.5 | 3133.13 | 0.129652 | 3.31624 | 13.881 | 2.38614 | 0.00137967 | 0.000103333 | 6.41117e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1505.7 | 0.132159 | 1065.91ms | 5094 | 40 | 727.276 | 3226.43 | 0.141597 | 3.46525 | 14.8324 | 2.53082 | 0.00230173 | 2.45387e-05 | 0 | 2(Loss) | true |
| Glaze | 1240.85 | 0.181292 | 1128.39ms | 5094 | 320 | 16120.8 | 3915.07 | 0.0926768 | 4.13741 | 17.3055 | 3.29368 | 0.00563776 | 3.12868e-05 | 2.45387e-06 | 3(Loss) | true |
| simdjson (reflection) | 1225.01 | 0.143707 | 1134.84ms | 5094 | 30 | 974.355 | 3965.7 | 0.0412035 | 4.172 | 15.9492 | 2.68532 | 0.00307551 | 4.58055e-05 | 1.30873e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1146.54 | 0.163899 | 1164.77ms | 5094 | 320 | 15432.8 | 4237.11 | 0.0661864 | 4.44707 | 16.7878 | 2.91814 | 0.00433844 | 7.05487e-05 | 2.45387e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1917.44 | 0.164712 | 1045.01ms | 5094 | 30 | 522.455 | 2533.6 | 0.0407686 | 2.6951 | 11.3963 | 1.8247 | 0.00106007 | 7.19801e-05 | 3.27182e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1812.3 | 0.126925 | 1066.48ms | 5094 | 1280 | 14816.9 | 2680.58 | 0.059653 | 2.84535 | 12.6038 | 2.01865 | 0.00172752 | 2.89863e-05 | 6.59477e-06 | 2(Loss) | true |
| Glaze | 1565.49 | 0.218955 | 1101.77ms | 5094 | 320 | 14773.3 | 3103.19 | 0.129437 | 3.26911 | 14.1241 | 2.59443 | 0.00556476 | 2.63791e-05 | 4.90773e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1418.64 | 0.0442211 | 1134.39ms | 5094 | 4890 | 11213.5 | 3424.42 | 0.174231 | 3.59755 | 14.0731 | 2.31646 | 0.00308334 | 8.33813e-05 | 3.59298e-05 | 4(Loss) | true |
| simdjson (reflection) | 1375.93 | 0.063441 | 1161.76ms | 5094 | 4890 | 24534.1 | 3530.7 | 0.0051543 | 3.69246 | 15.0112 | 2.45151 | 0.00243777 | 6.77247e-05 | 2.31637e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14886.5 | 0.114698 | 758.48ms | 5094 | 320 | 44.8324 | 326.337 | 0.0344854 | 0.387871 | 1.59658 | 0.259521 | 0.000196309 | 2.26983e-05 | 1.8404e-06 | 1(Win) | true |
| simdjson (reflection) | 8447.26 | 0.279552 | 788.24ms | 5094 | 30 | 77.5414 | 575.1 | 0.495107 | 0.654391 | 2.39321 | 0.352179 | 0.000196309 | 0 | 0 | 2(Loss) | true |
| Glaze | 4267.55 | 0.119052 | 846.831ms | 5094 | 320 | 587.737 | 1138.36 | 0.167723 | 1.2293 | 5.1598 | 0.828426 | 0.000197536 | 3.86484e-05 | 4.29427e-06 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16726.5 | 0.0744348 | 756.427ms | 5094 | 640 | 29.9118 | 290.439 | 0.464262 | 0.350834 | 1.5 | 0.236945 | 0.000196309 | 7.66834e-06 | 3.6808e-06 | 1(Win) | true |
| simdjson (reflection) | 9019.92 | 0.167405 | 788.557ms | 5094 | 160 | 130.068 | 538.587 | 0.0811651 | 0.615153 | 2.29388 | 0.329211 | 0.000197536 | 6.13467e-05 | 3.06733e-05 | 2(Loss) | true |
| Glaze | 4942.47 | 0.302359 | 827.773ms | 5094 | 80 | 706.587 | 982.913 | 0.0165352 | 1.06643 | 4.69925 | 0.724382 | 0.000196309 | 0.000137417 | 0.000105516 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2216.58 | 0.0570595 | 1082.25ms | 8051 | 2560 | 10000.7 | 3463.9 | 0.0569814 | 2.31474 | 9.90573 | 1.61024 | 0.00138793 | 3.58069e-05 | 1.49923e-05 | 1(Win) | true |
| Jsonifier | 1961.17 | 0.201928 | 1133.5ms | 8051 | 160 | 9999.58 | 3915.03 | 0.116194 | 2.63434 | 10.9424 | 2.07328 | 0.00194852 | 2.63942e-05 | 8.53931e-06 | 2(Loss) | true |
| simdjson (reflection) | 1869.8 | 0.117077 | 1156.85ms | 8051 | 80 | 1849.01 | 4106.34 | 0.089271 | 2.73243 | 10.5956 | 1.71606 | 0.00198423 | 3.26046e-05 | 1.5526e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1757.75 | 0.0594446 | 1178.24ms | 8051 | 2560 | 17260.4 | 4368.11 | 0.228325 | 2.90079 | 11.154 | 1.86908 | 0.0027615 | 5.19637e-05 | 1.83886e-05 | 4(Loss) | true |
| Glaze | 1603.55 | 0.0401778 | 1215.92ms | 8051 | 2560 | 9474.28 | 4788.14 | 0.0391521 | 3.17778 | 13.527 | 2.59744 | 0.00418402 | 4.44918e-05 | 8.0056e-06 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2653.62 | 0.043291 | 1081.1ms | 8051 | 4890 | 7672.29 | 2893.42 | 0.196016 | 1.93551 | 8.49572 | 1.28618 | 0.000938216 | 2.93121e-05 | 9.39816e-06 | 1(Win) | true |
| Jsonifier | 2279.59 | 0.0522986 | 1130.6ms | 8051 | 160 | 496.46 | 3368.16 | 0.0726072 | 2.24666 | 9.38393 | 1.72078 | 0.00182431 | 2.01838e-05 | 1.5526e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2156.94 | 0.0689951 | 1151.5ms | 8051 | 2560 | 15441.9 | 3559.69 | 0.0187723 | 2.3815 | 9.44914 | 1.49087 | 0.00226893 | 3.73595e-05 | 1.25179e-05 | 3(Loss) | true |
| simdjson (reflection) | 2104.97 | 0.103234 | 1175.32ms | 8051 | 40 | 567.174 | 3647.57 | 0.0399649 | 2.43116 | 10.0354 | 1.57471 | 0.00146876 | 2.17364e-05 | 3.1052e-06 | 4(Loss) | true |
| Glaze | 1946.91 | 0.14157 | 1186.23ms | 8051 | 40 | 1246.83 | 3943.7 | 0.117349 | 2.62543 | 11.5245 | 2.15725 | 0.00395293 | 6.21041e-06 | 0 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24111.9 | 0.07761 | 767.88ms | 9255 | 1280 | 103.308 | 366.054 | 0.030102 | 0.233266 | 0.93128 | 0.143922 | 0.00010805 | 1.28309e-05 | 2.448e-06 | 1(Win) | true |
| Glaze | 4425.79 | 0.139435 | 935.68ms | 9255 | 1280 | 9897.5 | 1994.28 | 0.112283 | 1.16638 | 4.80702 | 0.812318 | 0.000112777 | 3.11487e-05 | 9.45435e-06 | 2(Loss) | true |
| simdjson (reflection) | 529.443 | 0.139605 | 2419.35ms | 9255 | 2560 | 1.38662e+06 | 16670.8 | 0.254512 | 9.50827 | 38.0083 | 7.298 | 0.0194357 | 0.000101676 | 4.42751e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 27770.8 | 0.29115 | 759.675ms | 9255 | 40 | 34.2506 | 317.825 | 0.211931 | 0.209441 | 0.871745 | 0.130416 | 0.00010805 | 1.35062e-05 | 2.70124e-06 | 1(Win) | true |
| Glaze | 5393.32 | 0.118 | 897.687ms | 9255 | 2560 | 9546.46 | 1636.52 | 0.100556 | 0.960887 | 4.47315 | 0.737007 | 0.000281056 | 1.63763e-05 | 3.75642e-06 | 2(Loss) | true |
| simdjson (reflection) | 527.533 | 0.189661 | 2416.25ms | 9255 | 1280 | 1.2889e+06 | 16731.2 | 0.0698099 | 9.53756 | 38.0067 | 7.29627 | 0.0198595 | 9.43747e-05 | 4.72717e-05 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5528.85 | 0.336372 | 781.268ms | 2889 | 80 | 224.779 | 498.325 | 0.392848 | 1.02439 | 3.8875 | 0.513326 | 0.000354794 | 8.65351e-06 | 8.65351e-06 | 1(Win) | true |
| simdjson (ondemand) | 5484.97 | 0.113138 | 774.864ms | 2889 | 4890 | 1579.32 | 502.311 | 0.111677 | 1.00522 | 3.93146 | 0.43233 | 0.00069667 | 3.88612e-05 | 1.86166e-05 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 5419.39 | 0.131539 | 777.222ms | 2889 | 320 | 143.104 | 508.391 | 0.25204 | 1.02036 | 3.89547 | 0.427484 | 0.000719323 | 1.18986e-05 | 5.40845e-06 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 5401.44 | 0.211259 | 774.746ms | 2889 | 4890 | 5678.27 | 510.08 | 0.0250992 | 1.02544 | 3.8875 | 0.513327 | 0.000349751 | 4.62936e-05 | 1.91828e-05 | 3(Tie) | true |
| Glaze | 3166.15 | 0.0946637 | 814.588ms | 2889 | 160 | 108.572 | 870.194 | 0.0783485 | 1.7031 | 7.24922 | 1.24264 | 0.000348304 | 8.65351e-06 | 0 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5727.96 | 0.11506 | 782.279ms | 2889 | 640 | 196.031 | 481.003 | 0.0188444 | 0.976924 | 3.75251 | 0.481135 | 0.000349386 | 1.78479e-05 | 2.70422e-06 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5721.38 | 0.1181 | 779.329ms | 2889 | 320 | 103.502 | 481.556 | 0.132208 | 0.961786 | 3.75251 | 0.481135 | 0.000349386 | 1.29803e-05 | 1.08169e-06 | 1(Tie) | true |
| simdjson (ondemand) | 5638 | 0.380174 | 775.043ms | 2889 | 2560 | 8835.9 | 488.678 | 0.685428 | 0.985522 | 3.85877 | 0.415023 | 0.000693498 | 3.1369e-05 | 7.03098e-06 | 3(Loss) | true |
| simdjson (reflection) | 5500.89 | 0.288726 | 779.664ms | 2889 | 4890 | 10226.1 | 500.858 | 0.00379301 | 0.994457 | 3.83005 | 0.411215 | 0.00071833 | 2.28637e-05 | 1.21043e-05 | 4(Loss) | true |
| Glaze | 3180.11 | 0.203043 | 815.086ms | 2889 | 40 | 123.779 | 866.375 | 0.0163543 | 1.70066 | 7.17965 | 1.22603 | 0.000346141 | 0 | 0 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6618.27 | 0.0769172 | 783.694ms | 3808 | 640 | 114.007 | 548.722 | 0.365243 | 0.825113 | 3.33456 | 0.343487 | 0.00052521 | 1.31303e-05 | 1.64128e-06 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 6454.64 | 0.318513 | 783.108ms | 3808 | 4890 | 15704.1 | 562.632 | 0.0936599 | 0.842157 | 3.3083 | 0.340074 | 0.000547067 | 2.26087e-05 | 7.89426e-06 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 6425.3 | 0.185156 | 785.41ms | 3808 | 2560 | 2803.64 | 565.202 | 1.17355 | 0.854523 | 3.35189 | 0.395746 | 0.000263221 | 9.95027e-06 | 2.66708e-06 | 2(Tie) | true |
| Jsonifier (two-stage) | 6368.14 | 0.224345 | 784.736ms | 3808 | 4890 | 8004.05 | 570.275 | 0.00816407 | 0.857142 | 3.35189 | 0.395746 | 0.000262981 | 2.72271e-05 | 1.03646e-05 | 4(Loss) | true |
| Glaze | 3565.88 | 0.053574 | 828.814ms | 3808 | 1280 | 381.047 | 1018.43 | 0.0287751 | 1.49478 | 6.58508 | 1.20746 | 0.000538545 | 2.11315e-05 | 1.64128e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 6626.69 | 0.270454 | 783.221ms | 3808 | 40 | 87.8712 | 548.025 | 0.401345 | 0.834867 | 3.24947 | 0.371324 | 0.000262605 | 1.31303e-05 | 0 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 6622.16 | 0.0819206 | 780.435ms | 3808 | 640 | 129.17 | 548.4 | 0.197912 | 0.821314 | 3.25919 | 0.327731 | 0.000539161 | 1.88747e-05 | 4.1032e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 6603.74 | 0.458583 | 780.363ms | 3808 | 2560 | 16281.3 | 549.929 | 0.207337 | 0.829834 | 3.27994 | 0.330357 | 0.000538545 | 1.96954e-05 | 6.35997e-06 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6603.57 | 0.105504 | 782.016ms | 3808 | 320 | 107.727 | 549.944 | 0.0295572 | 0.822938 | 3.24947 | 0.371324 | 0.000262605 | 1.06683e-05 | 3.28256e-06 | 1(Tie) | true |
| Glaze | 3629.5 | 0.195214 | 826.92ms | 3808 | 40 | 152.61 | 1000.58 | 0.0258118 | 1.48001 | 6.53151 | 1.19433 | 0.000558036 | 5.2521e-05 | 0 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2828.2 | 0.143198 | 825.766ms | 2889 | 40 | 77.8404 | 974.175 | 0.16653 | 1.9212 | 6.07407 | 0.997923 | 0.00162686 | 0 | 0 | 1(Win) | true |
| Glaze | 2379.98 | 0.0902926 | 845.641ms | 2889 | 2560 | 2797 | 1157.64 | 0.0439191 | 2.21568 | 8.85739 | 1.54552 | 0.000449577 | 4.1645e-05 | 1.44676e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2323.66 | 0.126021 | 854.592ms | 2889 | 80 | 178.618 | 1185.7 | 0.021089 | 2.2944 | 7.82451 | 1.17688 | 0.000346141 | 2.59605e-05 | 8.65351e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2021.83 | 0.059289 | 865.037ms | 2889 | 4890 | 3192.01 | 1362.71 | 0.0412754 | 2.60498 | 8.9242 | 1.58221 | 0.000347132 | 0.000193386 | 0.000136333 | 4(Loss) | true |
| simdjson (reflection) | 1839.5 | 0.137703 | 881.097ms | 2889 | 1280 | 5444.96 | 1497.78 | 0.616005 | 2.84941 | 9.42991 | 1.39218 | 0.000356417 | 6.73352e-05 | 1.54141e-05 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3161.16 | 0.128507 | 826.174ms | 2889 | 30 | 37.6333 | 871.567 | 0.305029 | 1.72425 | 5.54656 | 0.859813 | 0.000692281 | 3.46141e-05 | 3.46141e-05 | 1(Win) | true |
| Glaze | 2591.41 | 0.0518268 | 841.495ms | 2889 | 1280 | 388.634 | 1063.19 | 0.0216083 | 2.04343 | 8.32399 | 1.40222 | 0.000346141 | 4.78647e-05 | 2.24451e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2527.99 | 0.064198 | 850.078ms | 2889 | 4890 | 2393.85 | 1089.86 | 0.163901 | 2.07679 | 7.29491 | 1.03773 | 0.00034883 | 6.80248e-05 | 3.20658e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2151.41 | 0.10474 | 863.517ms | 2889 | 2560 | 4605.88 | 1280.63 | 0.132709 | 2.44165 | 8.54483 | 1.48183 | 0.000349926 | 7.20675e-05 | 1.79831e-05 | 4(Loss) | true |
| simdjson (reflection) | 2036.35 | 0.108855 | 871.531ms | 2889 | 2560 | 5553 | 1352.99 | 0.116082 | 2.56581 | 8.91866 | 1.25788 | 0.000354253 | 8.09915e-05 | 1.6631e-05 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8740.29 | 0.102825 | 758.274ms | 2963 | 40 | 4.42051 | 323.3 | 0.10321 | 0.664065 | 1.48093 | 0.235235 | 0.000337496 | 5.06244e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6602.91 | 0.0349397 | 775.312ms | 2963 | 320 | 7.15454 | 427.953 | 0.0241031 | 0.839737 | 1.90786 | 0.288221 | 0.000337496 | 1.68748e-05 | 5.27337e-06 | 2(Loss) | true |
| Glaze | 5482.33 | 0.103013 | 778.189ms | 2963 | 2560 | 721.701 | 515.427 | 0.115177 | 1.01344 | 2.95376 | 0.455957 | 0.000342637 | 8.71425e-05 | 4.83832e-05 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10285.3 | 0.0867729 | 756.695ms | 2963 | 640 | 36.373 | 274.736 | 0.121286 | 0.569964 | 1.3132 | 0.196423 | 0.000338023 | 1.79295e-05 | 8.43739e-06 | 1(Win) | true |
| simdjson (reflection) | 7617.91 | 0.117001 | 764.725ms | 2963 | 30 | 5.65057 | 370.933 | 0.116686 | 0.757194 | 1.75363 | 0.251434 | 0.000337496 | 2.24997e-05 | 0 | 2(Loss) | true |
| Glaze | 6484.4 | 0.108707 | 770.508ms | 2963 | 2560 | 574.486 | 435.775 | 0.201014 | 0.863506 | 2.5316 | 0.365179 | 0.000338023 | 4.19233e-05 | 2.08298e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2943.36 | 0.176329 | 852.266ms | 3808 | 40 | 189.328 | 1233.83 | 0.00607829 | 1.80887 | 6.34611 | 0.900735 | 0.000262605 | 1.96954e-05 | 6.56513e-06 | 1(Win) | true |
| simdjson (ondemand) | 2545.62 | 0.0765401 | 867.758ms | 3808 | 160 | 190.769 | 1426.61 | 0.293071 | 2.04431 | 7.12237 | 1.21586 | 0.000262605 | 3.77495e-05 | 4.92384e-06 | 2(Loss) | true |
| Glaze | 2401.2 | 0.153518 | 882.072ms | 3808 | 2560 | 13800.5 | 1512.41 | 0.156789 | 2.18477 | 8.38157 | 1.51576 | 0.00026558 | 6.70874e-05 | 3.21076e-05 | 3(Loss) | true |
| Jsonifier | 2376.19 | 0.0451493 | 886.799ms | 3808 | 40 | 19.0455 | 1528.33 | 0.00708787 | 2.22891 | 6.13944 | 1.14128 | 0.00052521 | 3.93908e-05 | 2.62605e-05 | 4(Loss) | true |
| simdjson (reflection) | 2353.71 | 0.121895 | 884.053ms | 3808 | 2560 | 9055.13 | 1542.92 | 0.0547313 | 2.21883 | 7.50604 | 1.07169 | 0.000271017 | 7.08828e-05 | 2.6876e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3217.34 | 0.106838 | 845.625ms | 3808 | 160 | 232.689 | 1128.76 | 0.213633 | 1.65789 | 5.94433 | 0.795168 | 0.000262605 | 1.80541e-05 | 4.92384e-06 | 1(Win) | true |
| simdjson (ondemand) | 2757.89 | 0.0871422 | 864.953ms | 3808 | 160 | 210.677 | 1316.8 | 0.0398535 | 1.9271 | 6.83456 | 1.13971 | 0.000262605 | 3.44669e-05 | 9.84769e-06 | 2(Loss) | true |
| Jsonifier | 2665.88 | 0.107469 | 877.355ms | 3808 | 40 | 85.7308 | 1362.25 | 0.30065 | 1.99223 | 5.73897 | 1.0365 | 0.00026917 | 1.31303e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 2613.49 | 0.119974 | 876.577ms | 3808 | 2560 | 7114.84 | 1389.56 | 0.239378 | 1.99457 | 7.11817 | 0.969801 | 0.00026917 | 9.43737e-05 | 3.94933e-05 | 4(Loss) | true |
| Glaze | 2573.82 | 0.152016 | 875.157ms | 3808 | 40 | 184.025 | 1410.97 | 0.044276 | 2.06119 | 7.97637 | 1.4073 | 0.000288866 | 1.31303e-05 | 0 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12304.7 | 0.0374152 | 765.06ms | 4300 | 1280 | 19.9022 | 333.271 | 0.0447539 | 0.464613 | 1.07186 | 0.163488 | 0.000232922 | 1.5625e-05 | 2.90698e-06 | 1(Win) | true |
| Glaze | 3304.72 | 0.457008 | 856.169ms | 4300 | 1280 | 41164.7 | 1240.89 | 0.61514 | 1.59143 | 3.58302 | 0.601163 | 0.000234012 | 0.000124092 | 8.04869e-05 | 2(Loss) | true |
| simdjson (reflection) | 563.369 | 0.253865 | 1475.66ms | 4300 | 320 | 109272 | 7279.07 | 0.0571947 | 9.14377 | 33.6544 | 7.45395 | 0.00982703 | 7.99419e-05 | 3.63372e-06 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14563.8 | 0.118662 | 758.976ms | 4300 | 80 | 8.93101 | 281.575 | 0.256819 | 0.40659 | 0.952093 | 0.135581 | 0.000232558 | 4.65116e-05 | 0 | 1(Win) | true |
| Glaze | 4022.39 | 0.250728 | 833.998ms | 4300 | 4890 | 31951 | 1019.49 | 0.12407 | 1.31894 | 3.03163 | 0.47721 | 0.000234841 | 2.40167e-05 | 8.17996e-06 | 2(Loss) | true |
| simdjson (reflection) | 554.676 | 0.0660161 | 1478.95ms | 4300 | 4890 | 116484 | 7393.14 | 0.148046 | 9.18874 | 33.6629 | 7.45605 | 0.0105598 | 0.000109954 | 4.84139e-05 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3077.75 | 0.0433822 | 7796.74ms | 466906 | 2560 | 1.00845e+07 | 144676 | 0.0984518 | 1.63056 | 6.3903 | 1.26004 | 0.00195419 | 0.00389122 | 2.15431e-05 | 1(Win) | true |
| Glaze | 2539 | 0.0468758 | 9427.6ms | 466906 | 2560 | 1.7301e+07 | 175374 | 0.494242 | 1.98718 | 8.75459 | 1.96144 | 0.00259225 | 0.00276627 | 3.59389e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1868.12 | 0.0898337 | 6311.27ms | 466906 | 1280 | 5.86866e+07 | 238355 | 0.271823 | 2.67369 | 11.9921 | 1.52297 | 0.00472091 | 0.0963705 | 0.000133586 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3071.07 | 0.0602182 | 7790.68ms | 466906 | 1280 | 9.75768e+06 | 144991 | 0.0305179 | 1.63286 | 6.38917 | 1.25978 | 0.00193539 | 0.00392011 | 3.53959e-05 | 1(Win) | true |
| Glaze | 2539.52 | 0.0726181 | 9404.92ms | 466906 | 80 | 1.29699e+06 | 175339 | 0.0102862 | 1.98889 | 8.75348 | 1.96119 | 0.00262483 | 0.00274547 | 1.66254e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1858.86 | 0.0914196 | 6329.1ms | 466906 | 640 | 3.06921e+07 | 239543 | 0.00370809 | 2.69178 | 11.9921 | 1.52296 | 0.00482606 | 0.102621 | 0.000140801 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3958.31 | 0.0784168 | 9023.12ms | 699405 | 1280 | 2.23494e+07 | 168507 | 0.121589 | 1.27474 | 4.79634 | 1.19843 | 0.00190422 | 0.00166546 | 3.34626e-05 | 1(Win) | true |
| Glaze | 3197.87 | 0.267168 | 5532.56ms | 699405 | 80 | 2.48423e+07 | 208578 | 0.115459 | 1.57734 | 6.28763 | 1.35583 | 0.00201618 | 0.00153809 | 3.90153e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2414.88 | 0.134813 | 7927.74ms | 767297 | 1280 | 2.13604e+08 | 303018 | 0.138306 | 2.0626 | 8.04425 | 1.07997 | 0.00364463 | 0.0981694 | 9.31211e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3927.1 | 0.0868396 | 9067.86ms | 699405 | 640 | 1.39229e+07 | 169847 | 0.21354 | 1.28214 | 4.79553 | 1.19825 | 0.00190704 | 0.00171599 | 3.57961e-05 | 1(Win) | true |
| Glaze | 3197.69 | 0.0621714 | 5514.85ms | 699405 | 640 | 1.07633e+07 | 208590 | 0.0659894 | 1.57306 | 6.28688 | 1.35566 | 0.00211087 | 0.00138321 | 2.15138e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2410.33 | 0.126295 | 7939.55ms | 767297 | 1280 | 1.88172e+08 | 303590 | 0.185458 | 2.0641 | 8.04419 | 1.07996 | 0.00375073 | 0.0987903 | 0.000135274 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2923.65 | 0.123219 | 5460.73ms | 631514 | 1280 | 8.24672e+07 | 205995 | 0.310599 | 1.71131 | 8.26232 | 1.35263 | 0.00488999 | 3.16427e-05 | 2.50638e-05 | 1(Win) | true |
| Glaze | 2154.17 | 0.0676256 | 7314.93ms | 631514 | 1280 | 4.5755e+07 | 279578 | 0.108544 | 2.32061 | 9.80794 | 1.64391 | 0.00937229 | 1.08902e-05 | 9.41809e-06 | 2(Loss) | true |
