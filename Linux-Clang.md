# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1989.91 | 0.240554 | 777.086ms | 905 | 2560 | 2786.72 | 433.725 | 0.438358 | 2.80708 | 13.5039 | 2.2895 | 0.00114166 | 0.000126036 | 4.14365e-05 | 1(Win) | true |
| Glaze | 1598.31 | 0.221955 | 800.695ms | 905 | 320 | 459.68 | 539.994 | 0.00115741 | 3.45395 | 17.5934 | 2.2895 | 0.00115677 | 0.000103591 | 6.90608e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 623.766 | 0.105762 | 871.69ms | 905 | 4890 | 10471.9 | 1383.65 | 0.571164 | 8.3596 | 42.2243 | 5.0663 | 0.00117841 | 0.000188455 | 6.10107e-05 | 3(Loss) | true |
| simdjson (ondemand) | 290.279 | 0.199401 | 1042.92ms | 905 | 160 | 5623.92 | 2973.26 | 0.276554 | 17.9877 | 88.9459 | 9.47735 | 0.0211533 | 0.000200276 | 0.000103591 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2124 | 0.17248 | 773.148ms | 905 | 4890 | 2402.02 | 406.345 | 0.0203087 | 2.63889 | 12.842 | 2.17127 | 0.00111559 | 0.00012044 | 2.44043e-05 | 1(Win) | true |
| Glaze | 1670.88 | 0.283489 | 781.47ms | 905 | 2560 | 5489.3 | 516.538 | 0.284624 | 3.27995 | 16.9249 | 2.17127 | 0.00114209 | 0.000102728 | 2.3308e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 638.849 | 0.166271 | 870.167ms | 905 | 1280 | 6458.66 | 1350.99 | 0.0324311 | 8.1469 | 41.6032 | 4.94827 | 0.00127072 | 0.000146754 | 3.62569e-05 | 3(Loss) | true |
| simdjson (ondemand) | 289.074 | 0.131664 | 1033.73ms | 905 | 1280 | 19779.7 | 2985.65 | 0.154151 | 17.723 | 88.3271 | 9.35912 | 0.0183132 | 0.000132942 | 2.15815e-05 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2249.35 | 0.617037 | 766.749ms | 905 | 40 | 224.215 | 383.7 | 0.0694505 | 2.48776 | 9.3105 | 0.950276 | 0.00436464 | 5.52486e-05 | 5.52486e-05 | 1(Win) | true |
| Glaze | 215.69 | 0.143741 | 1138.72ms | 905 | 2560 | 84690.8 | 4001.46 | 0.0273068 | 23.7823 | 112.617 | 22.8608 | 0.0770213 | 0.000800242 | 0.000466592 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4599.26 | 0.201638 | 756.243ms | 905 | 4890 | 700.123 | 187.655 | 0.288949 | 1.34893 | 5.79779 | 0.272929 | 0.00221446 | 3.977e-05 | 9.94249e-06 | 1(Win) | true |
| Glaze | 881.641 | 0.105816 | 839.601ms | 905 | 4890 | 5247.22 | 978.942 | 0.101973 | 6.0178 | 24.0597 | 3.14917 | 0.0013106 | 0.000188681 | 9.64874e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1317.7 | 0.0670535 | 866.229ms | 1811 | 160 | 123.585 | 1310.69 | 0.0424574 | 4.03042 | 20.0121 | 4.07123 | 0.000565986 | 8.28272e-05 | 1.03534e-05 | 1(Win) | true |
| Glaze | 894.301 | 0.0950475 | 929.044ms | 1811 | 30 | 101.082 | 1931.23 | 0.191955 | 5.77405 | 30.0745 | 4.68526 | 0.00266888 | 1.8406e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 750.386 | 0.158012 | 969.668ms | 1811 | 2560 | 33859.9 | 2301.62 | 0.240808 | 6.87654 | 32.9415 | 5.57703 | 0.000732287 | 0.000187871 | 8.02388e-05 | 3(Loss) | true |
| simdjson (ondemand) | 359.973 | 0.125748 | 1225.97ms | 1811 | 4890 | 177995 | 4797.88 | 0.164311 | 14.1401 | 71.2479 | 9.26671 | 0.000648502 | 0.000187674 | 7.73505e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1444.11 | 0.185551 | 852.631ms | 1811 | 80 | 393.961 | 1195.96 | 0.114055 | 3.69335 | 19.0972 | 3.86969 | 0.00138736 | 3.45113e-05 | 0 | 1(Win) | true |
| Glaze | 949.264 | 0.129613 | 916.682ms | 1811 | 1280 | 7118.2 | 1819.41 | 0.167441 | 5.44114 | 29.0337 | 4.45334 | 0.00112119 | 0.000174714 | 6.1689e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 808.435 | 0.161135 | 945.877ms | 1811 | 4890 | 57947.4 | 2136.35 | 0.784267 | 6.3867 | 31.9299 | 5.35892 | 0.000580298 | 0.000106258 | 2.75526e-05 | 3(Loss) | true |
| simdjson (ondemand) | 368.975 | 0.175652 | 1209.52ms | 1811 | 1280 | 86528.3 | 4680.82 | 0.0732174 | 13.803 | 70.2253 | 9.04362 | 0.00121048 | 9.40433e-05 | 2.32951e-05 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 339.659 | 0.170776 | 1257.65ms | 1811 | 160 | 12064.9 | 5084.82 | 0.0289995 | 15.2927 | 64.0276 | 11.3992 | 0.0175421 | 0.000176008 | 6.55715e-05 | 1(Win) | true |
| Glaze | 305.168 | 0.14546 | 1303.96ms | 1798 | 2560 | 171012 | 5618.89 | 0.0706102 | 16.6504 | 71.2742 | 12.1413 | 0.0206886 | 0.000229856 | 0.000122966 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 895.766 | 0.376992 | 944.561ms | 1811 | 40 | 2113.35 | 1928.08 | 0.156646 | 5.87798 | 19.6096 | 1.14025 | 0.000552181 | 9.66317e-05 | 4.14136e-05 | 1(Win) | true |
| Glaze | 613.666 | 0.180432 | 1033.3ms | 1798 | 640 | 16267.5 | 2794.2 | 0.023156 | 8.36163 | 26.4321 | 2.17241 | 0.00074562 | 0.000158162 | 7.73429e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3133.58 | 0.217669 | 857.781ms | 3862 | 1280 | 8378.1 | 1175.36 | 0.142046 | 1.69921 | 8.62869 | 1.02745 | 0.000334388 | 4.63248e-05 | 1.43627e-05 | 1(Win) | true |
| Glaze | 1706.01 | 0.11768 | 952.835ms | 3862 | 2560 | 16523.7 | 2158.9 | 0.508871 | 3.04642 | 15.6911 | 1.98628 | 0.000278555 | 9.4369e-05 | 4.04583e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1658.59 | 0.168736 | 965.615ms | 3862 | 1280 | 17971 | 2220.61 | 0.219964 | 3.12662 | 14.4516 | 1.73278 | 0.000279162 | 5.05729e-05 | 1.03169e-05 | 3(Loss) | true |
| simdjson (ondemand) | 779.685 | 0.100131 | 1215.3ms | 3862 | 2560 | 57275.3 | 4723.82 | 0.073435 | 6.57457 | 28.2849 | 3.4995 | 0.0134101 | 9.9932e-05 | 3.73228e-05 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3473.71 | 0.114719 | 841.474ms | 3862 | 40 | 59.1788 | 1060.28 | 0.0668512 | 1.51236 | 8.13827 | 0.92232 | 0.000265407 | 2.58933e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1778.48 | 0.100866 | 948.548ms | 3862 | 40 | 174.533 | 2070.93 | 0.134985 | 2.95293 | 13.9612 | 1.62765 | 0.000783273 | 2.58933e-05 | 0 | 2(Loss) | true |
| Glaze | 1756.81 | 0.301847 | 942.315ms | 3862 | 320 | 12814.5 | 2096.47 | 0.169046 | 2.96789 | 15.2165 | 1.88011 | 0.00230693 | 2.34658e-05 | 7.2825e-06 | 3(Loss) | true |
| simdjson (ondemand) | 792.962 | 0.115889 | 1203.4ms | 3862 | 4890 | 141683 | 4644.72 | 0.00847139 | 6.45752 | 27.7962 | 3.39203 | 0.0160111 | 6.29065e-05 | 1.58855e-05 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 897.979 | 0.16064 | 1151.03ms | 3862 | 30 | 1302.33 | 4101.53 | 0.0968054 | 5.6872 | 26.4037 | 5.40963 | 0.00780252 | 1.72622e-05 | 0 | 1(Win) | true |
| Glaze | 892.259 | 0.184994 | 1158.62ms | 3862 | 640 | 37319.7 | 4127.82 | 0.0683332 | 5.72155 | 29.5873 | 5.69575 | 0.00725013 | 0.000130276 | 6.47333e-05 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5108.84 | 0.297898 | 829.074ms | 3862 | 80 | 368.982 | 720.925 | 0.0832957 | 1.04947 | 5.36665 | 0.628949 | 0.00026217 | 2.58933e-05 | 0 | 1(Win) | true |
| Glaze | 2154.62 | 0.192469 | 934.788ms | 3862 | 4890 | 52931.4 | 1709.39 | 0.140228 | 2.42149 | 8.65251 | 1.04868 | 0.00510983 | 6.76192e-05 | 2.86468e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1788.52 | 0.0684811 | 1250.21ms | 9578 | 4890 | 59815.5 | 5107.18 | 0.123526 | 2.8528 | 14.0799 | 2.70854 | 0.00126585 | 4.9043e-05 | 1.9835e-05 | 1(Win) | true |
| Glaze | 1418.37 | 0.05083 | 1391.66ms | 9578 | 4890 | 52398.2 | 6439.97 | 0.0982458 | 3.58551 | 17.8633 | 3.53947 | 0.00132273 | 5.24592e-05 | 1.94293e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1412.01 | 0.209434 | 1399.93ms | 9578 | 160 | 29369.1 | 6469.02 | 0.0389507 | 3.60238 | 17.5818 | 2.96628 | 0.00379907 | 1.56609e-05 | 3.26269e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1343.19 | 0.119284 | 1432.76ms | 9578 | 640 | 42113.2 | 6800.43 | 0.16289 | 3.78751 | 18.2534 | 3.09835 | 0.00161731 | 3.40951e-05 | 1.28876e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2871.88 | 0.208 | 1201.57ms | 9578 | 80 | 3501.36 | 3180.6 | 0.0401029 | 1.81742 | 9.85467 | 1.77427 | 0.000374556 | 5.08979e-05 | 3.26269e-05 | 1(Win) | true |
| Glaze | 2000.91 | 0.102345 | 1344.45ms | 9578 | 1280 | 27940.6 | 4565.06 | 0.106097 | 2.54968 | 13.4357 | 2.53978 | 0.000161829 | 2.60199e-05 | 6.85164e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1960.56 | 0.0953089 | 1354.31ms | 9578 | 4890 | 96419.2 | 4659.01 | 0.102709 | 2.59717 | 13.3493 | 2.03247 | 0.00232501 | 3.47593e-05 | 1.18498e-05 | 3(Loss) | true |
| Jsonifier (two-stage) | 1813.26 | 0.0828632 | 1382.72ms | 9578 | 4890 | 85204.1 | 5037.49 | 0.0215309 | 2.81506 | 14.0902 | 2.17739 | 0.00012185 | 3.73641e-05 | 1.43051e-05 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4127.09 | 0.142525 | 966.377ms | 9578 | 2560 | 25473.4 | 2213.25 | 0.0278938 | 1.25589 | 5.06786 | 1.0023 | 0.00170904 | 4.51882e-05 | 2.17376e-05 | 1(Win) | true |
| Glaze | 1938.29 | 0.118276 | 1215.88ms | 9578 | 4890 | 151919 | 4712.55 | 0.127737 | 2.63739 | 13.3883 | 2.61067 | 0.00106411 | 7.92332e-05 | 4.67798e-05 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11808.7 | 0.0986706 | 846.604ms | 9578 | 4890 | 2848.58 | 773.52 | 0.248578 | 0.452113 | 1.88557 | 0.21539 | 0.00063805 | 2.29522e-05 | 1.00563e-05 | 1(Win) | true |
| Glaze | 4535.17 | 0.280785 | 965.327ms | 9578 | 30 | 959.472 | 2014.1 | 0.137176 | 1.13885 | 4.99374 | 0.731781 | 0.000539431 | 6.61238e-05 | 6.9604e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3216.25 | 0.324793 | 846.802ms | 3873 | 640 | 8904.07 | 1148.41 | 0.012655 | 1.62687 | 7.96282 | 1.03305 | 0.000343322 | 6.97941e-05 | 2.86438e-05 | 1(Win) | true |
| Glaze | 1856.74 | 0.0848467 | 928.113ms | 3873 | 4890 | 13930.6 | 1989.28 | 0.141071 | 2.78172 | 14.7798 | 1.89078 | 0.000415228 | 6.56847e-05 | 2.15429e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1591.98 | 0.13322 | 965.067ms | 3873 | 1280 | 12228.3 | 2320.12 | 0.103571 | 3.22937 | 14.2523 | 1.68319 | 0.0010102 | 9.1983e-05 | 3.83262e-05 | 3(Loss) | true |
| simdjson (ondemand) | 718.597 | 0.0818078 | 1249.25ms | 3873 | 1280 | 22632.1 | 5139.99 | 0.0120517 | 7.09742 | 27.8567 | 3.5528 | 0.016116 | 8.81503e-05 | 3.2073e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3536.08 | 0.178813 | 833.275ms | 3873 | 1280 | 4465.4 | 1044.54 | 0.0553031 | 1.49663 | 7.51975 | 0.938807 | 0.000289464 | 5.44636e-05 | 2.38026e-05 | 1(Win) | true |
| Glaze | 1926.59 | 0.086106 | 919.739ms | 3873 | 4890 | 13325.8 | 1917.16 | 0.346644 | 2.68232 | 14.3085 | 1.78492 | 0.00229828 | 6.3731e-05 | 2.31797e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1662.8 | 0.0660604 | 955.048ms | 3873 | 4890 | 10529.5 | 2221.3 | 0.141096 | 3.10018 | 13.8136 | 1.58895 | 0.00162749 | 7.15456e-05 | 2.96743e-05 | 3(Loss) | true |
| simdjson (ondemand) | 724.435 | 0.0558277 | 1242.53ms | 3873 | 2560 | 20741.3 | 5098.57 | 0.211551 | 7.03376 | 27.4216 | 3.45624 | 0.0180411 | 6.05151e-05 | 1.90623e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 945.007 | 0.0910722 | 1124.56ms | 3873 | 1280 | 16218.4 | 3908.52 | 0.0305928 | 5.40763 | 25.5391 | 5.18487 | 0.0082 | 6.17254e-05 | 1.89614e-05 | 1(Win) | true |
| Glaze | 877.542 | 0.0878765 | 1166.49ms | 3873 | 2560 | 35022.3 | 4209.01 | 0.0430439 | 5.82539 | 29.5293 | 5.73974 | 0.00680896 | 0.000107011 | 5.96074e-05 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4338.75 | 0.490311 | 833.198ms | 3873 | 160 | 2787.58 | 851.3 | 0.550518 | 1.24736 | 5.12962 | 0.557707 | 0.00970501 | 8.5528e-05 | 2.09786e-05 | 1(Win) | true |
| Glaze | 2200.77 | 0.0964424 | 928.435ms | 3873 | 1280 | 3353.45 | 1678.31 | 0.273567 | 2.36683 | 8.51175 | 1.0457 | 0.00427963 | 0.000109532 | 5.86997e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1719.12 | 0.0261454 | 6025.69ms | 94653 | 4890 | 921631 | 52508.5 | 0.00525566 | 2.93531 | 13.5427 | 2.52189 | 0.00832954 | 3.26302e-05 | 2.14539e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1471.65 | 0.0461474 | 6901.23ms | 94653 | 2560 | 2.05115e+06 | 61338.2 | 0.0488554 | 3.41575 | 15.1324 | 2.84929 | 0.0120871 | 4.41167e-05 | 2.76751e-05 | 2(Loss) | true |
| Glaze | 1454.77 | 0.187928 | 6977.75ms | 94653 | 80 | 1.08781e+06 | 62049.6 | 0.0546636 | 3.47183 | 15.8336 | 3.11426 | 0.0155456 | 1.90168e-05 | 1.04328e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1201.18 | 0.0542588 | 8248.02ms | 94653 | 1280 | 2.12817e+06 | 75149.8 | 0.00646667 | 4.19104 | 16.8629 | 3.14901 | 0.0115101 | 9.0396e-05 | 6.42148e-05 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2801.43 | 0.170689 | 5228.16ms | 94653 | 160 | 483996 | 32222.2 | 0.0719548 | 1.80399 | 9.4442 | 1.60825 | 0.00530556 | 1.20176e-05 | 6.33894e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2299.67 | 0.0469901 | 5948.73ms | 94653 | 2560 | 870940 | 39252.6 | 0.0536618 | 2.1858 | 11.0724 | 1.94418 | 0.00573613 | 2.03168e-05 | 1.29833e-05 | 2(Loss) | true |
| Glaze | 2208.51 | 0.0733579 | 6137.52ms | 94653 | 640 | 575364 | 40872.8 | 0.2387 | 2.288 | 11.9412 | 2.23915 | 0.00816127 | 1.1803e-05 | 6.91671e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1648.99 | 0.0463398 | 7465.25ms | 94653 | 2560 | 1.64733e+06 | 54741.5 | 0.10029 | 3.03955 | 12.9087 | 2.25938 | 0.00722144 | 2.24628e-05 | 1.09487e-05 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16402.2 | 0.0475158 | 1294.14ms | 94653 | 4890 | 33438.6 | 5503.4 | 0.0110262 | 0.309855 | 1.3301 | 0.183903 | 0.000168375 | 8.55995e-06 | 4.63862e-06 | 1(Win) | true |
| Glaze | 5647.94 | 0.0711708 | 2353.27ms | 94653 | 2560 | 331232 | 15982.5 | 0.0317685 | 0.891253 | 4.37627 | 0.666677 | 9.13864e-05 | 1.23147e-05 | 6.94973e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16711.6 | 0.0367995 | 1285.22ms | 94653 | 4890 | 19320.9 | 5401.54 | 0.108317 | 0.30324 | 1.32453 | 0.182678 | 0.000154721 | 4.98862e-06 | 2.31823e-06 | 1(Win) | true |
| Glaze | 6318.66 | 0.0427831 | 2174.29ms | 94653 | 4890 | 182672 | 14286 | 0.0238596 | 0.793699 | 4.32645 | 0.655341 | 5.57888e-05 | 9.28804e-06 | 5.50715e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1877.11 | 0.100326 | 7071.68ms | 124597 | 2560 | 1.03254e+07 | 63302.1 | 0.0578117 | 2.69327 | 11.8992 | 2.17477 | 0.00847599 | 9.73388e-05 | 7.44776e-05 | 1(Win) | true |
| Jsonifier | 1743.64 | 0.0284049 | 7605.4ms | 124597 | 4890 | 1.8323e+06 | 68147.7 | 0.0436466 | 2.899 | 12.8326 | 2.56221 | 0.0107817 | 2.5952e-05 | 1.71301e-05 | 2(Loss) | true |
| Glaze | 1605.96 | 0.0264439 | 8188.25ms | 124597 | 4890 | 1.872e+06 | 73990 | 0.211327 | 3.14561 | 13.9579 | 2.77552 | 0.0154185 | 5.39539e-05 | 3.84471e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1560.33 | 0.0240522 | 8393.5ms | 124597 | 4890 | 1.64059e+06 | 76153.5 | 0.077952 | 3.23701 | 13.0985 | 2.40354 | 0.00901166 | 2.35852e-05 | 1.42037e-05 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2854.26 | 0.0547567 | 6189.74ms | 124597 | 1280 | 665139 | 41630.8 | 0.0612734 | 1.76779 | 8.82096 | 1.49136 | 0.00448423 | 9.39905e-06 | 4.74655e-06 | 1(Win) | true |
| Jsonifier | 2483.76 | 0.152908 | 6829.31ms | 124597 | 160 | 856203 | 47840.7 | 0.0111164 | 2.02291 | 9.71164 | 1.87017 | 0.00815815 | 1.08349e-05 | 5.3673e-06 | 2(Loss) | true |
| Glaze | 2207.89 | 0.106261 | 7434.93ms | 124597 | 320 | 1.04654e+06 | 53818.3 | 0.0473634 | 2.28192 | 11.0249 | 2.11922 | 0.0103175 | 1.97136e-05 | 1.17629e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2109.14 | 0.109966 | 7647.29ms | 124597 | 1280 | 4.91283e+06 | 56338 | 0.145152 | 2.39605 | 10.1119 | 1.73241 | 0.00572737 | 1.19259e-05 | 6.5461e-06 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18986.3 | 0.123553 | 1430.65ms | 136037 | 4890 | 348534 | 6833.07 | 0.013824 | 0.267179 | 1.27855 | 0.214993 | 0.000253609 | 4.2437e-06 | 1.84149e-06 | 1(Win) | true |
| Glaze | 5265.71 | 0.0709995 | 3225.2ms | 136076 | 4890 | 1.49716e+06 | 24644.8 | 0.266774 | 0.95002 | 4.09562 | 0.69046 | 0.00154604 | 7.29473e-06 | 3.76008e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19098.1 | 0.0954569 | 1429.81ms | 136037 | 30 | 1261.44 | 6793.07 | 0.222281 | 0.26638 | 1.27457 | 0.214104 | 0.000291342 | 1.47019e-06 | 9.80126e-07 | 1(Win) | true |
| Glaze | 5813.51 | 0.0799857 | 2981.15ms | 136076 | 1280 | 408057 | 22322.5 | 0.0064821 | 0.867668 | 4.06236 | 0.682685 | 0.00144943 | 7.09622e-06 | 3.65719e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1028.38 | 0.590775 | 6503.99ms | 2251027 | 30 | 4.56264e+09 | 2.0875e+06 | 0.0418827 | 4.86945 | 25.8492 | 5.09964 | 0.00770534 | 0.064215 | 9.86957e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 896.601 | 0.344235 | 7529.08ms | 2251027 | 80 | 5.43455e+09 | 2.39432e+06 | 0.39312 | 5.6009 | 28.56 | 5.31878 | 0.0103408 | 0.102434 | 0.000133206 | 2(Loss) | true |
| Glaze | 803.232 | 0.308308 | 8372.12ms | 2251027 | 80 | 5.43173e+09 | 2.67264e+06 | 0.176739 | 6.24517 | 31.7339 | 5.89826 | 0.0101862 | 0.0637727 | 0.000246782 | 3(Loss) | true |
| simdjson (ondemand) | 793.022 | 0.114372 | 8455.39ms | 2251027 | 80 | 7.66863e+08 | 2.70704e+06 | 0.27304 | 6.33169 | 31.2887 | 5.42082 | 0.0145135 | 0.108403 | 0.00239099 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1246.32 | 0.463907 | 6526.44ms | 2251027 | 160 | 1.02161e+10 | 1.72247e+06 | 0.156853 | 4.01392 | 20.9103 | 3.90218 | 0.00719734 | 0.0414073 | 5.04992e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1069.8 | 0.55742 | 7493.71ms | 2251027 | 40 | 5.00476e+09 | 2.00668e+06 | 0.268507 | 4.71497 | 23.672 | 4.13676 | 0.00971139 | 0.0786322 | 9.32796e-05 | 2(Loss) | true |
| simdjson (ondemand) | 950.543 | 0.129333 | 8240.07ms | 2251027 | 80 | 6.82536e+08 | 2.25844e+06 | 0.0497231 | 5.27671 | 26.3443 | 4.22811 | 0.0108914 | 0.0754164 | 0.00172214 | 3(Loss) | true |
| Glaze | 935.551 | 0.384256 | 8338.21ms | 2251027 | 160 | 1.2439e+10 | 2.29463e+06 | 0.0292213 | 5.34115 | 26.7582 | 4.69635 | 0.00924205 | 0.0401423 | 0.000305119 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1938.6 | 0.0410698 | 6543.11ms | 2090234 | 320 | 5.707e+07 | 1.02827e+06 | 0.145422 | 2.60063 | 7.89149 | 0.405686 | 0.000237699 | 0.051073 | 7.01447e-05 | 1(Win) | true |
| Glaze | 958.459 | 0.0766799 | 6487.84ms | 2090234 | 160 | 4.06936e+08 | 2.0798e+06 | 0.155352 | 5.22798 | 9.3422 | 0.534101 | 0.000241277 | 0.0694802 | 0.00185313 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1909.47 | 0.277389 | 6600.33ms | 2090234 | 320 | 2.68345e+09 | 1.04396e+06 | 0.270519 | 2.63182 | 7.8911 | 0.405653 | 0.000234343 | 0.0511386 | 4.25012e-05 | 1(Win) | true |
| Glaze | 998.514 | 0.0657672 | 6222.87ms | 2090234 | 40 | 6.8954e+07 | 1.99637e+06 | 0.0444763 | 5.05777 | 9.33809 | 0.533136 | 0.000234101 | 0.0432797 | 0.00023721 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2114.9 | 0.104307 | 7591.23ms | 5373214 | 80 | 5.10982e+08 | 2.42295e+06 | 0.277314 | 2.34239 | 12.7527 | 2.26971 | 0.00465014 | 0.0624185 | 0.00128056 | 1(Win) | true |
| Jsonifier | 1978.86 | 0.496532 | 8109.11ms | 5373214 | 30 | 4.9597e+09 | 2.58952e+06 | 0.0982226 | 2.53752 | 13.2945 | 2.80678 | 0.00331066 | 0.0382239 | 0.00104038 | 2(Loss) | true |
| simdjson (ondemand) | 1774.45 | 0.502527 | 9118.75ms | 5373214 | 40 | 8.42405e+09 | 2.88783e+06 | 0.307116 | 2.84485 | 13.7965 | 2.30358 | 0.00630309 | 0.0647621 | 0.000814238 | 3(Loss) | true |
| Glaze | 1614.31 | 0.526718 | 10067.1ms | 5373214 | 30 | 8.38633e+09 | 3.1743e+06 | 0.0162655 | 3.10983 | 16.0013 | 2.99613 | 0.0049432 | 0.0407041 | 0.000467113 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2486.9 | 0.567871 | 7601.72ms | 5373214 | 40 | 5.47658e+09 | 2.06051e+06 | 0.0951068 | 1.99347 | 10.7099 | 1.77585 | 0.00441456 | 0.0522701 | 0.000725613 | 1(Win) | true |
| Jsonifier | 2337.86 | 0.0821041 | 8009.11ms | 5373214 | 160 | 5.18182e+08 | 2.19188e+06 | 0.0474331 | 2.14206 | 11.2504 | 2.31238 | 0.00299655 | 0.0280505 | 0.00202775 | 2(Loss) | true |
| simdjson (ondemand) | 2105.11 | 0.631042 | 8985.19ms | 5373214 | 30 | 7.07874e+09 | 2.43422e+06 | 0.371856 | 2.3989 | 11.7272 | 1.80438 | 0.00486158 | 0.050696 | 0.000461096 | 3(Loss) | true |
| Glaze | 1839.9 | 0.485703 | 10049.1ms | 5373214 | 30 | 5.48963e+09 | 2.78509e+06 | 0.650328 | 2.73022 | 13.9467 | 2.50128 | 0.00458118 | 0.0296887 | 0.000869368 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4930.57 | 1.17709 | 8056.95ms | 6661897 | 160 | 3.68077e+10 | 1.28855e+06 | 0.805883 | 1.02403 | 2.92475 | 0.261245 | 7.50002e-05 | 0.0280622 | 0.00013267 | 1(Win) | true |
| Glaze | 3180.13 | 0.640603 | 6269.13ms | 6661897 | 160 | 2.62061e+10 | 1.9978e+06 | 1.1331 | 1.58937 | 4.23031 | 0.469317 | 8.66608e-05 | 0.0631054 | 0.00512381 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5081.9 | 1.05034 | 8031.35ms | 6661897 | 40 | 6.89708e+09 | 1.25018e+06 | 0.38521 | 0.991145 | 2.92469 | 0.261234 | 7.4746e-05 | 0.0280316 | 0.000176076 | 1(Win) | true |
| Glaze | 3912.79 | 0.673024 | 5124.39ms | 6661897 | 40 | 4.77688e+09 | 1.62372e+06 | 0.154292 | 1.29378 | 4.22891 | 0.468988 | 8.43453e-05 | 0.0244618 | 0.000223634 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2206.32 | 0.231048 | 5761.72ms | 500299 | 320 | 7.9887e+07 | 216253 | 0.680303 | 2.28988 | 9.95813 | 1.92721 | 0.0116295 | 0.00620371 | 5.11069e-05 | 1(Win) | true |
| Glaze | 1755.53 | 0.185501 | 7148.74ms | 500299 | 640 | 1.62672e+08 | 271782 | 0.455659 | 2.87823 | 12.546 | 2.36884 | 0.0144989 | 0.00398617 | 4.36583e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1646.44 | 0.367506 | 7676.71ms | 500299 | 640 | 7.25902e+08 | 289791 | 0.389244 | 3.05825 | 13.3013 | 2.30666 | 0.0150853 | 0.0367713 | 7.82844e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1119.15 | 0.263054 | 5611.63ms | 500299 | 640 | 8.04925e+08 | 426326 | 0.0992776 | 4.50371 | 18.931 | 2.86726 | 0.0159908 | 0.0303676 | 0.00012743 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2683.07 | 0.196313 | 5585.61ms | 500299 | 640 | 7.79957e+07 | 177827 | 0.00237761 | 1.88133 | 8.80544 | 1.6479 | 0.00900578 | 0.00299199 | 2.0316e-05 | 1(Win) | true |
| Glaze | 2115.65 | 0.083971 | 6886.51ms | 500299 | 1280 | 4.59031e+07 | 225521 | 0.10431 | 2.38093 | 11.3989 | 2.0915 | 0.00968341 | 0.00184302 | 2.1926e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1936.63 | 0.249081 | 7445.6ms | 500299 | 1280 | 4.82012e+08 | 246368 | 0.209064 | 2.60162 | 12.1486 | 2.02831 | 0.0114281 | 0.0249122 | 3.79539e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1291.36 | 0.571186 | 5249.7ms | 500299 | 30 | 1.3361e+08 | 369472 | 0.197163 | 3.9117 | 17.7712 | 2.5822 | 0.00876309 | 0.0211124 | 9.20116e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9993.36 | 0.0346688 | 5569.84ms | 500299 | 4890 | 1.33974e+06 | 47743.9 | 0.0498111 | 0.50222 | 2.16603 | 0.353759 | 0.00247928 | 0.00238085 | 3.56204e-05 | 1(Win) | true |
| Glaze | 4987.89 | 0.524971 | 5453.01ms | 500299 | 80 | 2.01738e+07 | 95656.1 | 0.91799 | 1.01347 | 4.19185 | 0.585246 | 0.00114117 | 0.0260445 | 1.47162e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10005.4 | 0.04578 | 5555.44ms | 500299 | 4890 | 2.33049e+06 | 47686.3 | 0.224047 | 0.502003 | 2.16498 | 0.353521 | 0.00249869 | 0.00229708 | 2.95435e-05 | 1(Win) | true |
| Glaze | 5762.05 | 0.249689 | 9151.42ms | 500299 | 640 | 2.7358e+07 | 82804.3 | 0.741874 | 0.871608 | 4.17823 | 0.582038 | 0.00112219 | 0.0013433 | 1.14463e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3316.78 | 0.469188 | 8768.11ms | 1151920 | 320 | 7.72782e+08 | 331212 | 0.437486 | 1.51456 | 6.59643 | 1.04638 | 0.00625207 | 0.0548166 | 0.000166594 | 1(Win) | true |
| Jsonifier | 2867.63 | 0.327757 | 10031.1ms | 1151920 | 30 | 4.7296e+07 | 383089 | 0.119802 | 1.76364 | 7.4864 | 1.6518 | 0.00490737 | 0.0197574 | 6.06234e-05 | 2(Loss) | true |
| Glaze | 2557.33 | 0.0814868 | 5552.4ms | 1151920 | 320 | 3.921e+07 | 429572 | 0.0745308 | 1.97034 | 8.62633 | 1.67911 | 0.00757752 | 0.0147046 | 0.000245031 | 3(Loss) | true |
| simdjson (ondemand) | 2336.47 | 0.520101 | 6147.66ms | 1151920 | 320 | 1.91359e+09 | 470178 | 0.224264 | 2.1475 | 8.90876 | 1.27886 | 0.00711119 | 0.0502015 | 5.48188e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3831.8 | 0.459116 | 8542.92ms | 1151920 | 640 | 1.10883e+09 | 286695 | 0.166737 | 1.31826 | 6.09434 | 0.92517 | 0.00477088 | 0.0456296 | 2.45338e-05 | 1(Win) | true |
| Jsonifier | 3167.26 | 0.540934 | 9951.75ms | 1151920 | 160 | 5.63229e+08 | 346847 | 0.299746 | 1.59562 | 6.98705 | 1.53088 | 0.00365659 | 0.0126132 | 5.3693e-05 | 2(Loss) | true |
| Glaze | 2880.41 | 0.0600345 | 5433.84ms | 1151920 | 320 | 1.6776e+07 | 381389 | 0.111804 | 1.75427 | 8.12599 | 1.55827 | 0.00548451 | 0.00971193 | 4.38887e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2684.99 | 0.498895 | 5783.99ms | 1151920 | 320 | 1.3333e+09 | 409147 | 0.321819 | 1.86976 | 8.40339 | 1.15457 | 0.0042194 | 0.0354017 | 2.10437e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15354.9 | 0.218465 | 5180.47ms | 1439562 | 30 | 1.14459e+06 | 89409.4 | 0.0264397 | 0.329095 | 1.34917 | 0.258045 | 0.000855978 | 0.0184824 | 1.28743e-05 | 1(Win) | true |
| Glaze | 5195.67 | 0.645879 | 7095.98ms | 1439584 | 320 | 9.32061e+08 | 264238 | 0.640209 | 0.967654 | 3.07289 | 0.528478 | 0.0010004 | 0.063341 | 2.35094e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14678 | 0.527625 | 5302.72ms | 1439562 | 1280 | 3.11737e+08 | 93532.8 | 0.811091 | 0.344394 | 1.34878 | 0.257958 | 0.000826903 | 0.0183321 | 6.57372e-06 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 6880.08 | 0.822116 | 5347.53ms | 1439584 | 320 | 8.61199e+08 | 199546 | 3.02552 | 0.733149 | 3.06771 | 0.527269 | 0.00100356 | 0.0177984 | 1.74161e-05 | -(Loss) | false |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2221.04 | 0.0490266 | 3178.41ms | 56369 | 4890 | 688555 | 24203.8 | 0.0150445 | 2.27939 | 9.35049 | 1.89418 | 0.00482017 | 4.7623e-05 | 2.52681e-05 | 1(Win) | true |
| Glaze | 1966.9 | 0.0514301 | 3485.95ms | 56369 | 4890 | 966179 | 27331.1 | 0.0745948 | 2.57322 | 11.633 | 2.33826 | 0.00561398 | 6.18297e-05 | 3.63657e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1730.48 | 0.0333758 | 3867.13ms | 56369 | 4890 | 525676 | 31065.1 | 0.0587407 | 2.92515 | 12.2764 | 2.27964 | 0.00755534 | 5.22376e-05 | 2.97594e-05 | 3(Loss) | true |
| simdjson (ondemand) | 948.931 | 0.0507327 | 6433.72ms | 56369 | 4890 | 4.03922e+06 | 56650.8 | 0.08814 | 5.28771 | 21.9235 | 3.62648 | 0.0113514 | 0.000108143 | 6.5385e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3174.85 | 0.0902199 | 2814.63ms | 56369 | 1280 | 298710 | 16932.4 | 0.0146656 | 1.59666 | 7.22391 | 1.40743 | 0.00355386 | 1.16143e-05 | 4.97558e-06 | 1(Win) | true |
| Glaze | 2966.09 | 0.0820835 | 2926.72ms | 56369 | 2560 | 566583 | 18124.1 | 0.0895041 | 1.70754 | 9.19944 | 1.77892 | 0.00237044 | 1.352e-05 | 5.68935e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2389.16 | 0.0371963 | 3350.62ms | 56369 | 4890 | 342530 | 22500.6 | 0.0873623 | 2.11931 | 10.1417 | 1.79114 | 0.00271294 | 2.86855e-05 | 1.70727e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1112.05 | 0.0837218 | 5993.33ms | 56369 | 4890 | 8.00979e+06 | 48341.2 | 0.0495381 | 4.51584 | 19.5776 | 3.09391 | 0.00936469 | 0.000103314 | 6.93103e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14480.5 | 0.0874529 | 1117.24ms | 56369 | 2560 | 26983.7 | 3712.41 | 0.048084 | 0.352821 | 1.42142 | 0.238677 | 0.000220838 | 8.81469e-06 | 3.3263e-06 | 1(Win) | true |
| Glaze | 4935.57 | 0.0809043 | 1837.91ms | 56369 | 4890 | 379715 | 10891.9 | 0.0508476 | 1.02491 | 3.48779 | 0.484202 | 0.000110566 | 1.09307e-05 | 4.98468e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14939.7 | 0.0893204 | 1104.75ms | 56369 | 1280 | 13222.4 | 3598.32 | 0.0635683 | 0.342291 | 1.41182 | 0.236478 | 0.000185247 | 9.07802e-06 | 4.17173e-06 | 1(Win) | true |
| Glaze | 5423.2 | 0.0912873 | 1738.7ms | 56369 | 4890 | 400406 | 9912.54 | 0.126382 | 0.935977 | 3.41113 | 0.467048 | 0.000113625 | 2.18143e-05 | 1.12319e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2519.18 | 0.0372128 | 3929.31ms | 83958 | 4890 | 684068 | 31783.6 | 0.0280837 | 2.00994 | 8.75913 | 1.54904 | 0.00425355 | 1.72157e-05 | 8.91233e-06 | 1(Win) | true |
| Glaze | 2188.99 | 0.0389228 | 4403.83ms | 83958 | 4890 | 991185 | 36577.9 | 0.0605765 | 2.30755 | 10.5709 | 2.16641 | 0.00638816 | 6.18505e-05 | 3.80485e-05 | 2(Loss) | true |
| Jsonifier | 1693.59 | 0.0820575 | 5493.71ms | 83958 | 1280 | 1.92645e+06 | 47277.6 | 0.0813859 | 2.98805 | 9.80381 | 2.1723 | 0.00865633 | 3.08655e-05 | 1.83779e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1379.42 | 0.0538649 | 6571.96ms | 83958 | 4890 | 4.78029e+06 | 58045.3 | 0.15769 | 3.65216 | 15.1337 | 2.45407 | 0.00809657 | 4.775e-05 | 2.75213e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3385.99 | 0.0410378 | 3470.47ms | 83958 | 4890 | 460500 | 23647 | 0.0562307 | 1.49519 | 7.33266 | 1.22247 | 0.00166989 | 1.13359e-05 | 5.10285e-06 | 1(Win) | true |
| Glaze | 2966.56 | 0.0361998 | 3810.58ms | 83958 | 4890 | 466807 | 26990.3 | 0.0896667 | 1.70601 | 8.94217 | 1.79286 | 0.00351461 | 1.54498e-05 | 8.12316e-06 | 2(Loss) | true |
| Jsonifier | 2082.12 | 0.0419121 | 4951.97ms | 83958 | 4890 | 1.27028e+06 | 38455.2 | 0.0335938 | 2.42935 | 8.37882 | 1.84644 | 0.00514519 | 2.27789e-05 | 1.38837e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1618.66 | 0.0650973 | 6102.84ms | 83958 | 4890 | 5.07047e+06 | 49466 | 0.0507767 | 3.10169 | 13.5606 | 2.09705 | 0.00627483 | 2.06793e-05 | 1.175e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16044.2 | 0.0397728 | 1311.04ms | 94370 | 4890 | 24339.4 | 5609.38 | 0.0319045 | 0.317365 | 1.28166 | 0.241708 | 0.000239541 | 7.94419e-06 | 4.08261e-06 | 1(Win) | true |
| Glaze | 4339.3 | 0.0711008 | 2832.37ms | 94370 | 2560 | 556696 | 20740.3 | 0.00961009 | 1.16636 | 4.17651 | 0.677854 | 0.0015444 | 1.08656e-05 | 4.67326e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16306.2 | 0.060834 | 1303.21ms | 94370 | 30 | 338.202 | 5519.27 | 0.116426 | 0.312499 | 1.27585 | 0.240384 | 0.00023807 | 2.47254e-06 | 0 | 1(Win) | true |
| Glaze | 4490.46 | 0.090023 | 2763.81ms | 94370 | 2560 | 833363 | 20042.1 | 0.0889329 | 1.12046 | 4.12562 | 0.666091 | 0.00156796 | 1.33534e-05 | 6.62701e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1772.07 | 0.131476 | 3656.05ms | 53331 | 1280 | 1.82263e+06 | 28701.1 | 0.0515911 | 2.85533 | 10.6192 | 1.88423 | 0.00171479 | 0.000132076 | 8.11559e-05 | 1(Win) | true |
| Jsonifier | 1653.88 | 0.0835094 | 3824.77ms | 53331 | 2560 | 1.68834e+06 | 30752.1 | 0.217266 | 3.05974 | 9.89229 | 1.7817 | 0.0122946 | 0.000131182 | 6.76275e-05 | 2(Loss) | true |
| Glaze | 1440.89 | 0.0693667 | 4288.94ms | 53331 | 2560 | 1.53477e+06 | 35298 | 0.082342 | 3.51051 | 11.6953 | 2.24686 | 0.0226939 | 9.19449e-05 | 5.27294e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1011.51 | 0.0799281 | 5845.77ms | 53331 | 4890 | 7.89823e+06 | 50281.9 | 0.112668 | 5.00009 | 15.3877 | 2.76721 | 0.00855108 | 0.000120028 | 7.56973e-05 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2272.53 | 0.111812 | 3568.85ms | 53331 | 2560 | 1.6031e+06 | 22380.5 | 0.105512 | 2.22838 | 7.62723 | 1.26672 | 0.00845743 | 7.25715e-05 | 4.59322e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2079.98 | 0.148252 | 3561.61ms | 53331 | 1280 | 1.68209e+06 | 24452.3 | 0.0561109 | 2.43484 | 8.41381 | 1.38311 | 0.00804649 | 7.34358e-05 | 4.78439e-05 | 2(Loss) | true |
| Glaze | 1902.72 | 0.170904 | 4042.24ms | 53331 | 320 | 667828 | 26730.4 | 0.18535 | 2.66293 | 9.4282 | 1.73168 | 0.0185684 | 2.00399e-05 | 9.90278e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1140.52 | 0.170872 | 5748.84ms | 53331 | 1280 | 7.43197e+06 | 44594 | 0.0401771 | 4.43376 | 13.4213 | 2.32267 | 0.0109981 | 5.5813e-05 | 2.943e-05 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16545.8 | 0.182491 | 1081.96ms | 58581 | 4890 | 185665 | 3376.53 | 0.0141679 | 0.308571 | 1.077 | 0.164456 | 4.54093e-05 | 2.29769e-05 | 1.27731e-05 | 1(Win) | true |
| Glaze | 5335.59 | 0.174519 | 1805.02ms | 58581 | 2560 | 854823 | 10470.7 | 0.067673 | 0.958129 | 2.62659 | 0.382599 | 8.01441e-05 | 6.55476e-05 | 4.21225e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16780.2 | 0.342615 | 1075.59ms | 58581 | 1280 | 166549 | 3329.35 | 0.0103024 | 0.302488 | 1.06791 | 0.162339 | 3.52343e-05 | 1.3683e-05 | 7.13489e-06 | 1(Win) | true |
| Glaze | 5962.52 | 0.177046 | 1679.98ms | 58581 | 2560 | 704476 | 9369.73 | 0.0796206 | 0.850409 | 2.55385 | 0.36587 | 3.78149e-05 | 2.62991e-05 | 1.31695e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1913.2 | 0.0931277 | 4009.03ms | 65103 | 2560 | 2.33818e+06 | 32451.9 | 0.129567 | 2.64348 | 9.08906 | 1.55637 | 0.00817248 | 0.0001184 | 5.4451e-05 | 1(Win) | true |
| Jsonifier | 1539.86 | 0.116591 | 4799.27ms | 65103 | 1280 | 2.82868e+06 | 40320 | 0.150145 | 3.28562 | 9.70233 | 1.84918 | 0.0109327 | 0.000167103 | 7.90214e-05 | 2(Loss) | true |
| Glaze | 1485.41 | 0.0949656 | 4943.31ms | 65103 | 1280 | 2.01675e+06 | 41797.9 | 0.396577 | 3.4049 | 10.9298 | 2.10766 | 0.0229861 | 0.000102026 | 5.07609e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1267.29 | 0.162267 | 5654.34ms | 65103 | 320 | 2.02238e+06 | 48992.1 | 0.0653082 | 3.9908 | 12.8391 | 2.27451 | 0.00341766 | 0.000246004 | 0.000155811 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2503.73 | 0.176502 | 3818.68ms | 65103 | 1280 | 2.45211e+06 | 24797.9 | 0.0139011 | 2.0148 | 7.28426 | 1.14738 | 0.00598235 | 4.57328e-05 | 2.75045e-05 | 1(Win) | true |
| Jsonifier | 1964.94 | 0.186954 | 4520.42ms | 65103 | 640 | 2.23335e+06 | 31597.5 | 0.0134486 | 2.57586 | 7.85405 | 1.42919 | 0.0078239 | 4.91049e-05 | 2.80565e-05 | 2(Loss) | true |
| Glaze | 1917.3 | 0.0525116 | 4641.4ms | 65103 | 4890 | 1.41398e+06 | 32382.6 | 0.0619475 | 2.63955 | 9.08224 | 1.68838 | 0.0179217 | 3.51339e-05 | 1.95537e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1365.46 | 0.0666027 | 5860.79ms | 65103 | 4890 | 4.48475e+06 | 45469.8 | 0.0718436 | 3.70472 | 11.2426 | 1.91551 | 0.0095141 | 4.31313e-05 | 2.19096e-05 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16327.2 | 0.172361 | 1215.48ms | 78778 | 4890 | 307589 | 4601.43 | 0.00517878 | 0.314169 | 1.09159 | 0.183579 | 2.63171e-05 | 4.92726e-05 | 3.41593e-05 | 1(Win) | true |
| Glaze | 4645.32 | 0.13889 | 2372.05ms | 78778 | 4890 | 2.46734e+06 | 16172.9 | 0.0621915 | 1.08966 | 3.01834 | 0.488296 | 0.000347984 | 2.87676e-05 | 1.26472e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16421 | 0.334177 | 1209.01ms | 78778 | 4890 | 1.14307e+06 | 4575.15 | 0.392801 | 0.31059 | 1.08476 | 0.182069 | 2.83134e-05 | 2.33007e-05 | 1.28808e-05 | 1(Win) | true |
| Glaze | 5205.04 | 0.161422 | 2198.5ms | 78778 | 4890 | 2.65458e+06 | 14433.8 | 0.0736263 | 0.970187 | 2.95713 | 0.474155 | 0.00035545 | 2.63405e-05 | 1.38724e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2466.02 | 0.233115 | 1200.35ms | 11812 | 160 | 18143.1 | 4568 | 0.0301098 | 2.07206 | 9.98112 | 1.74729 | 0.00365677 | 1.11116e-05 | 5.29123e-07 | 1(Win) | true |
| Jsonifier (two-stage) | 1859.7 | 0.126605 | 1355.95ms | 11812 | 2560 | 150558 | 6057.33 | 0.0581633 | 2.73563 | 13.4227 | 2.2914 | 0.0046251 | 5.48965e-05 | 2.6853e-05 | 2(Loss) | true |
| Glaze | 1804.26 | 0.0800003 | 1371.3ms | 11812 | 4890 | 121995 | 6243.45 | 0.0491451 | 2.81772 | 13.6889 | 2.65442 | 0.00105032 | 6.00928e-05 | 2.80468e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1062.66 | 0.0856097 | 1810.88ms | 11812 | 4890 | 402733 | 10600.6 | 0.0862305 | 4.77391 | 20.5059 | 3.40817 | 0.00800742 | 7.35795e-05 | 3.53355e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2812.61 | 0.0847976 | 1191.51ms | 11812 | 40 | 461.374 | 4005.1 | 0.083158 | 1.81688 | 9.06231 | 1.53242 | 0.00313241 | 5.07958e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2047.69 | 0.197342 | 1350.79ms | 11812 | 1280 | 150857 | 5501.22 | 0.210452 | 2.48764 | 12.5033 | 2.07653 | 0.00423622 | 2.96309e-05 | 1.14423e-05 | 2(Loss) | true |
| Glaze | 2021.09 | 0.0754211 | 1354.06ms | 11812 | 2560 | 45237.7 | 5573.62 | 0.0624764 | 2.51919 | 12.6057 | 2.41246 | 0.00121477 | 2.94655e-05 | 1.00864e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1129.48 | 0.0774629 | 1797.44ms | 11812 | 4890 | 291870 | 9973.47 | 0.0741534 | 4.49311 | 19.6587 | 3.21834 | 0.00735156 | 4.31262e-05 | 1.8594e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11742.1 | 0.0957817 | 836.6ms | 11812 | 4890 | 4128.82 | 959.348 | 0.234633 | 0.449114 | 2.09118 | 0.342618 | 0.000109088 | 2.6177e-05 | 9.48742e-06 | 1(Win) | true |
| Glaze | 3733.83 | 0.202185 | 1040.54ms | 11812 | 1280 | 47626.1 | 3016.96 | 0.33767 | 1.37366 | 5.63986 | 0.82357 | 0.000398099 | 4.12716e-05 | 2.09004e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12458.1 | 0.127413 | 822.435ms | 11812 | 2560 | 3397.89 | 904.217 | 0.49671 | 0.424716 | 2.04462 | 0.332035 | 8.88265e-05 | 2.28846e-05 | 1.0351e-05 | 1(Win) | true |
| Glaze | 4240.08 | 0.108752 | 1003.47ms | 11812 | 4890 | 40821.2 | 2656.74 | 0.371903 | 1.21188 | 5.37437 | 0.765324 | 0.00040673 | 3.57856e-05 | 1.51833e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3415.21 | 0.054504 | 1452.9ms | 25388 | 4890 | 73010.9 | 7089.42 | 0.0846479 | 1.4875 | 7.13321 | 1.13475 | 0.00291492 | 2.257e-05 | 9.81092e-06 | 1(Win) | true |
| Jsonifier | 2923.82 | 0.0584088 | 1570.14ms | 25388 | 4890 | 114399 | 8280.91 | 0.00843682 | 1.73995 | 7.8389 | 1.64377 | 0.0042974 | 2.24169e-05 | 9.50484e-06 | 2(Loss) | true |
| Glaze | 2411.31 | 0.137285 | 1753.3ms | 25388 | 320 | 60805.6 | 10041 | 0.0937667 | 2.10419 | 9.60627 | 1.88735 | 0.00464725 | 6.03139e-06 | 7.38538e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2173.79 | 0.205415 | 1868.66ms | 25388 | 640 | 335017 | 11138.1 | 0.0798573 | 2.33337 | 10.1943 | 1.62014 | 0.00361865 | 1.42784e-05 | 6.03139e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3675.07 | 0.124735 | 1455.3ms | 25388 | 640 | 43220.2 | 6588.15 | 0.0248377 | 1.38319 | 6.73732 | 1.04171 | 0.0029744 | 8.12392e-06 | 1.7848e-06 | 1(Win) | true |
| Jsonifier | 3096.74 | 0.0525838 | 1566.96ms | 25388 | 4890 | 82653.7 | 7818.52 | 0.214925 | 1.64119 | 7.443 | 1.55073 | 0.00448818 | 1.437e-05 | 5.09878e-06 | 2(Loss) | true |
| Glaze | 2580.51 | 0.0642629 | 1735.28ms | 25388 | 2560 | 93069.3 | 9382.59 | 0.285834 | 1.97206 | 9.10391 | 1.77568 | 0.0046068 | 2.07098e-05 | 9.73947e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2299.69 | 0.0685986 | 1852.36ms | 25388 | 2560 | 133534 | 10528.3 | 0.049478 | 2.20542 | 9.75788 | 1.5232 | 0.0031925 | 2.29101e-05 | 9.00093e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15701 | 0.159437 | 928.837ms | 31235 | 320 | 2927.93 | 1897.21 | 0.001153 | 0.329131 | 1.41972 | 0.26307 | 5.22251e-05 | 8.30399e-06 | 3.80182e-06 | 1(Win) | true |
| Glaze | 5207.74 | 0.0884955 | 1314.11ms | 31235 | 1280 | 32797.2 | 5719.95 | 0.163648 | 0.977917 | 3.70312 | 0.653946 | 0.00233492 | 1.56325e-05 | 6.22799e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16248.6 | 0.0656219 | 919.532ms | 31235 | 2560 | 3705 | 1833.26 | 0.0197057 | 0.318337 | 1.40173 | 0.258844 | 4.80481e-05 | 6.71572e-06 | 2.81385e-06 | 1(Win) | true |
| Glaze | 5679.23 | 0.0487722 | 1264.36ms | 31235 | 4890 | 32000.6 | 5245.08 | 0.156777 | 0.897272 | 3.58448 | 0.627566 | 0.00227849 | 1.81617e-05 | 8.8255e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2463.73 | 0.0637491 | 4945.81ms | 108313 | 640 | 457197 | 41926.4 | 0.0612789 | 2.053 | 8.73898 | 1.75646 | 0.00296914 | 3.67858e-05 | 2.38747e-05 | 1(Win) | true |
| Glaze | 2333.44 | 0.116452 | 5188.91ms | 108313 | 640 | 1.70075e+06 | 44267.5 | 0.185465 | 2.16733 | 10.5346 | 1.88219 | 0.00281976 | 3.28908e-05 | 2.04558e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1828.97 | 0.0612963 | 6410.68ms | 108313 | 4890 | 5.8604e+06 | 56477.5 | 0.0475905 | 2.76411 | 11.8155 | 2.07091 | 0.00302439 | 2.85509e-05 | 1.68205e-05 | 3(Loss) | true |
| simdjson (ondemand) | 764.452 | 0.131147 | 7295.82ms | 108313 | 640 | 2.00981e+07 | 135123 | 0.00896715 | 6.5525 | 28.4796 | 4.48485 | 0.00433652 | 7.77261e-05 | 4.80234e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2895.95 | 0.155268 | 4512.85ms | 108313 | 80 | 245376 | 35668.9 | 0.00227784 | 1.74762 | 7.95652 | 1.57473 | 0.00259179 | 6.57816e-06 | 3.46219e-06 | 1(Win) | true |
| Glaze | 2632.58 | 0.0684779 | 4847.56ms | 108313 | 2560 | 1.84816e+06 | 39237.3 | 0.0326137 | 1.91752 | 9.81131 | 1.71501 | 0.00248723 | 1.50713e-05 | 8.66268e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2046.88 | 0.0594069 | 5978.61ms | 108313 | 2560 | 2.30086e+06 | 50464.8 | 0.262059 | 2.46593 | 11.0341 | 1.88943 | 0.00274707 | 1.48189e-05 | 9.35512e-06 | 3(Loss) | true |
| simdjson (ondemand) | 796.079 | 0.193324 | 7142.03ms | 108313 | 320 | 2.01359e+07 | 129755 | 0.247553 | 6.29107 | 27.7973 | 4.32843 | 0.00374557 | 5.88861e-05 | 4.13732e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18259.8 | 0.0795062 | 1321.76ms | 108313 | 4890 | 98918.9 | 5656.97 | 0.0898322 | 0.278145 | 1.2473 | 0.328252 | 0.000217838 | 6.05494e-06 | 2.93401e-06 | 1(Win) | true |
| Glaze | 4887.02 | 0.0758745 | 2867.95ms | 108313 | 4890 | 1.25769e+06 | 21136.7 | 0.00749635 | 1.03654 | 3.26353 | 0.411382 | 0.000318423 | 1.19079e-05 | 6.1229e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18686.2 | 0.0646234 | 1304.69ms | 108313 | 4890 | 62403.3 | 5527.89 | 0.0633494 | 0.27229 | 1.2424 | 0.327145 | 0.000205847 | 5.76607e-06 | 2.77164e-06 | 1(Win) | true |
| Glaze | 5099.14 | 0.130249 | 2773.48ms | 108313 | 2560 | 1.7822e+06 | 20257.4 | 0.179239 | 0.992516 | 3.21806 | 0.400866 | 0.000314612 | 7.28502e-06 | 3.58481e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2805.84 | 0.0610459 | 6995.37ms | 183677 | 4890 | 7.1024e+06 | 62429.8 | 0.106228 | 1.80176 | 7.75 | 1.28316 | 0.00187874 | 4.11187e-05 | 2.81892e-05 | 1(Win) | true |
| Glaze | 2543.9 | 0.0819735 | 7655.2ms | 183677 | 2560 | 8.15634e+06 | 68858 | 0.120186 | 1.98602 | 9.22145 | 1.7258 | 0.00317376 | 1.65797e-05 | 9.07036e-06 | 2(Loss) | true |
| Jsonifier | 2159.04 | 0.078275 | 8891.69ms | 183677 | 1280 | 5.16232e+06 | 81132.5 | 0.0126266 | 2.34619 | 8.42061 | 1.88919 | 0.00249701 | 3.02161e-05 | 2.10713e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1270.61 | 0.0764367 | 7477.24ms | 183677 | 2560 | 2.8427e+07 | 137862 | 0.0323737 | 3.95832 | 17.312 | 2.66701 | 0.00250109 | 5.48071e-05 | 3.40548e-05 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3123.79 | 0.0543787 | 6552.51ms | 183677 | 2560 | 2.38036e+06 | 56075.4 | 0.0468945 | 1.61894 | 7.28992 | 1.17634 | 0.00159773 | 1.62692e-05 | 1.06441e-05 | 1(Win) | true |
| Glaze | 2756.38 | 0.0915454 | 7295.93ms | 183677 | 4890 | 1.65506e+07 | 63550 | 0.138338 | 1.83481 | 8.80643 | 1.62996 | 0.00294072 | 1.72527e-05 | 1.13552e-05 | 2(Loss) | true |
| Jsonifier | 2327.6 | 0.0651474 | 8462.85ms | 183677 | 4890 | 1.17542e+07 | 75256.9 | 0.0142801 | 2.17121 | 7.95927 | 1.78205 | 0.00224209 | 2.73887e-05 | 1.78004e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1320.14 | 0.0585566 | 7282.47ms | 183677 | 2560 | 1.54548e+07 | 132689 | 0.0692095 | 3.80907 | 16.9149 | 2.57604 | 0.00223339 | 3.28596e-05 | 2.37382e-05 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20240.9 | 0.0513548 | 1750.66ms | 213963 | 4890 | 131065 | 10081.1 | 0.05229 | 0.250874 | 1.119 | 0.27523 | 0.00019114 | 8.03227e-06 | 4.95088e-06 | 1(Win) | true |
| Glaze | 4952.49 | 0.0511315 | 4869.97ms | 213963 | 4890 | 2.17028e+06 | 41201.7 | 0.120057 | 1.01923 | 3.64005 | 0.598024 | 0.000659208 | 7.74726e-05 | 2.49771e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20555.4 | 0.0489426 | 1734.62ms | 213963 | 4890 | 115428 | 9926.9 | 0.0970447 | 0.247616 | 1.11647 | 0.274664 | 0.000181966 | 8.81792e-06 | 5.90378e-06 | 1(Win) | true |
| Glaze | 5761.16 | 0.158336 | 4294ms | 213963 | 640 | 2.0128e+06 | 35418.4 | 0.0345897 | 0.871063 | 3.61276 | 0.591747 | 0.000661709 | 7.62398e-06 | 3.61482e-06 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 831.275 | 0.0825196 | 6559.01ms | 1834197 | 160 | 4.82434e+08 | 2.10427e+06 | 0.00237844 | 6.04264 | 26.9526 | 5.76305 | 0.0298908 | 0.0816069 | 0.000456412 | 1(Win) | true |
| Jsonifier (two-stage) | 721.722 | 0.175824 | 7629.31ms | 1834197 | 40 | 7.26385e+08 | 2.42368e+06 | 0.144108 | 6.91895 | 31.0105 | 6.2879 | 0.0365773 | 0.145291 | 0.000851912 | 2(Loss) | true |
| Glaze | 669.701 | 0.0832979 | 8141.8ms | 1834197 | 160 | 7.57388e+08 | 2.61195e+06 | 0.024171 | 7.50868 | 32.0054 | 6.49715 | 0.0353598 | 0.0816454 | 0.000962761 | 3(Loss) | true |
| simdjson (ondemand) | 574.528 | 0.158009 | 9570.65ms | 1834197 | 160 | 3.70298e+09 | 3.04463e+06 | 0.61893 | 8.75735 | 37.2666 | 6.30541 | 0.046048 | 0.146998 | 0.00127585 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 921.19 | 0.103869 | 6569.73ms | 1834197 | 80 | 3.11212e+08 | 1.89888e+06 | 0.057756 | 5.44204 | 23.9458 | 5.05706 | 0.0293476 | 0.0553313 | 0.000241495 | 1(Win) | true |
| Jsonifier (two-stage) | 767.729 | 0.742163 | 7795.61ms | 1834197 | 160 | 4.57503e+10 | 2.27844e+06 | 0.131008 | 6.57323 | 28.0015 | 5.58184 | 0.0357543 | 0.119106 | 0.000301586 | 2(Loss) | true |
| Glaze | 734.449 | 0.179106 | 8109.82ms | 1834197 | 30 | 5.45896e+08 | 2.38169e+06 | 0.0416713 | 6.85869 | 28.9905 | 5.79182 | 0.0339813 | 0.0581276 | 0.000904538 | 3(Loss) | true |
| simdjson (ondemand) | 633.026 | 0.45432 | 9278.15ms | 1834197 | 30 | 4.72817e+09 | 2.76328e+06 | 0.323646 | 7.977 | 34.2442 | 5.59991 | 0.0412643 | 0.118391 | 0.00107393 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1153.28 | 0.46042 | 9664.46ms | 1834197 | 30 | 1.46303e+09 | 1.51674e+06 | 0.124252 | 4.38058 | 12.5639 | 0.909542 | 0.00163928 | 0.0586708 | 0.000163468 | 1(Win) | true |
| Glaze | 640.785 | 0.209812 | 8525.28ms | 1833577 | 80 | 2.62257e+09 | 2.7289e+06 | 0.365528 | 7.89873 | 16.012 | 0.996538 | 0.00107222 | 0.0493935 | 0.000283878 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1132.3 | 0.752978 | 9652.73ms | 1834197 | 160 | 2.16498e+10 | 1.54484e+06 | 0.718526 | 4.49525 | 12.5637 | 0.909502 | 0.00167447 | 0.0583678 | 0.000498256 | 1(Win) | true |
| Glaze | 641.663 | 0.31594 | 8509.82ms | 1833577 | 160 | 1.18608e+10 | 2.72516e+06 | 0.169162 | 7.99149 | 16.0113 | 0.996381 | 0.00111013 | 0.04935 | 0.00119472 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2531.92 | 0.360472 | 8707.33ms | 7351818 | 160 | 1.59423e+10 | 2.76914e+06 | 0.377712 | 1.98442 | 8.69475 | 1.60943 | 0.00994309 | 0.0608119 | 0.00102725 | 1(Win) | true |
| Jsonifier | 2462.57 | 0.155278 | 8877.81ms | 7351818 | 40 | 7.8179e+08 | 2.84712e+06 | 0.130256 | 2.04205 | 9.56894 | 2.21009 | 0.00677754 | 0.0337493 | 0.000790186 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2078.42 | 0.699764 | 5037.09ms | 7351818 | 30 | 1.67166e+10 | 3.37335e+06 | 0.140303 | 2.4227 | 10.2109 | 1.61272 | 0.0110423 | 0.0608957 | 0.00136052 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 2063.49 | 0.122122 | 5133.64ms | 7351818 | 40 | 6.88707e+08 | 3.39777e+06 | 0.551852 | 2.43097 | 11.0334 | 2.24384 | 0.00986429 | 0.0331853 | 0.000848008 | 3(Tie) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2761.95 | 0.35273 | 8659.13ms | 7351818 | 160 | 1.28281e+10 | 2.53851e+06 | 0.364473 | 1.82619 | 7.94452 | 1.43335 | 0.0097498 | 0.054217 | 0.000728301 | 1(Win) | true |
| Jsonifier | 2637.21 | 0.571862 | 9040.96ms | 7351818 | 40 | 9.24573e+09 | 2.65858e+06 | 0.168305 | 1.91477 | 8.81804 | 2.0339 | 0.0066163 | 0.0271687 | 0.000964704 | 2(Loss) | true |
| simdjson (ondemand) | 2318.1 | 0.112073 | 10170.6ms | 7351818 | 40 | 4.59609e+08 | 3.02457e+06 | 0.0905766 | 2.17705 | 9.45645 | 1.4366 | 0.00986644 | 0.053637 | 0.00136287 | 3(Loss) | true |
| Glaze | 2217.92 | 0.111785 | 5148.84ms | 7351818 | 40 | 4.99486e+08 | 3.16117e+06 | 0.915428 | 2.27072 | 10.2813 | 2.06793 | 0.00941035 | 0.0272544 | 0.00318922 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5034.85 | 0.176727 | 5956.71ms | 9930848 | 30 | 3.31535e+08 | 1.88105e+06 | 0.183862 | 0.999385 | 3.38769 | 0.427912 | 0.000545757 | 0.0246516 | 0.000199755 | 1(Win) | true |
| Glaze | 3654.62 | 0.216658 | 8114.9ms | 9930228 | 80 | 2.52159e+09 | 2.5913e+06 | 0.0358901 | 1.38445 | 4.21673 | 0.484712 | 0.00107237 | 0.0413375 | 0.00329146 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4913.7 | 0.440564 | 6033.05ms | 9930848 | 160 | 1.1537e+10 | 1.92743e+06 | 0.258786 | 1.02269 | 3.38766 | 0.427905 | 0.000531428 | 0.0246217 | 0.000207886 | 1(Win) | true |
| Glaze | 3997.63 | 0.431942 | 7433.49ms | 9930228 | 80 | 8.37632e+09 | 2.36895e+06 | 0.165073 | 1.2661 | 4.21647 | 0.484654 | 0.0010538 | 0.0220311 | 0.000231878 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 845.282 | 0.0891004 | 6469.27ms | 1834197 | 80 | 2.71981e+08 | 2.0694e+06 | 0.0439614 | 5.95571 | 26.5404 | 5.63525 | 0.0310143 | 0.0824489 | 0.000409341 | 1(Win) | true |
| Jsonifier (two-stage) | 732.553 | 0.124044 | 7499.54ms | 1834197 | 80 | 7.01868e+08 | 2.38785e+06 | 0.228471 | 6.82868 | 30.584 | 6.18683 | 0.0366712 | 0.146256 | 0.000846263 | 2(Loss) | true |
| Glaze | 664.119 | 0.119489 | 8218.49ms | 1834197 | 80 | 7.92402e+08 | 2.63391e+06 | 0.0389242 | 7.54013 | 31.9798 | 6.48941 | 0.0356913 | 0.0821346 | 0.000927736 | 3(Loss) | true |
| simdjson (ondemand) | 560.691 | 0.506527 | 9706.98ms | 1834197 | 160 | 3.99549e+10 | 3.11977e+06 | 0.0356086 | 8.97437 | 37.2161 | 6.29552 | 0.0460608 | 0.147241 | 0.000973232 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 948.934 | 0.102623 | 6470.75ms | 1834197 | 40 | 1.43143e+08 | 1.84336e+06 | 0.26293 | 5.31957 | 23.559 | 4.94008 | 0.0302794 | 0.0561369 | 0.000378572 | 1(Win) | true |
| Jsonifier (two-stage) | 807.913 | 0.437065 | 7570.44ms | 1834197 | 30 | 2.68644e+09 | 2.16512e+06 | 0.575955 | 6.24678 | 27.604 | 5.49183 | 0.035715 | 0.120273 | 0.000295043 | 2(Loss) | true |
| Glaze | 731.746 | 0.0613815 | 8191.07ms | 1834197 | 160 | 3.44482e+08 | 2.39048e+06 | 0.222726 | 6.89562 | 28.993 | 5.79232 | 0.0343368 | 0.0586249 | 0.000980991 | 3(Loss) | true |
| simdjson (ondemand) | 625.116 | 0.533371 | 9547.14ms | 1834197 | 30 | 6.68268e+09 | 2.79824e+06 | 0.432587 | 8.0694 | 34.223 | 5.59901 | 0.0411475 | 0.119028 | 0.000610403 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1130.43 | 0.583699 | 9817.22ms | 1834197 | 320 | 2.61054e+10 | 1.54739e+06 | 0.184974 | 4.46665 | 12.5598 | 0.909544 | 0.00140574 | 0.0596402 | 0.000178789 | 1(Win) | true |
| Glaze | 628.507 | 0.336535 | 8649ms | 1833577 | 160 | 1.40268e+10 | 2.7822e+06 | 0.187504 | 7.99938 | 16.0115 | 0.996585 | 0.000996297 | 0.0818108 | 0.000793129 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1153.94 | 0.31162 | 9645.7ms | 1834197 | 160 | 3.57021e+09 | 1.51587e+06 | 1.21036 | 4.36269 | 12.5596 | 0.909504 | 0.00138702 | 0.0596734 | 0.000263146 | 1(Win) | true |
| Glaze | 656.216 | 0.372778 | 8390.82ms | 1833577 | 30 | 2.96024e+09 | 2.66473e+06 | 0.556393 | 7.7086 | 16.0106 | 0.996384 | 0.000999031 | 0.0492379 | 0.00049488 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2601.01 | 0.143678 | 8432.11ms | 7351818 | 160 | 2.39997e+09 | 2.69558e+06 | 0.251164 | 1.92884 | 8.58849 | 1.58424 | 0.00994156 | 0.0609998 | 0.00194242 | 1(Win) | true |
| Jsonifier | 2461.01 | 0.179023 | 8908.24ms | 7351818 | 30 | 7.80375e+08 | 2.84893e+06 | 0.102874 | 2.04056 | 9.42873 | 2.18473 | 0.00690747 | 0.0341681 | 0.00262666 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2077.16 | 0.128659 | 5108.37ms | 7351818 | 40 | 7.54381e+08 | 3.3754e+06 | 0.126624 | 2.41948 | 11.0264 | 2.24172 | 0.00949356 | 0.0333348 | 0.00188878 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2072.49 | 0.131741 | 5153.13ms | 7351818 | 80 | 1.58904e+09 | 3.38301e+06 | 1.29285 | 2.41429 | 10.1985 | 1.61033 | 0.0111121 | 0.0609595 | 0.00497848 | 3(Tie) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2818.83 | 0.619571 | 8719.7ms | 7351818 | 30 | 7.1245e+09 | 2.48729e+06 | 0.319887 | 1.78155 | 7.84504 | 1.41081 | 0.00970429 | 0.0544137 | 0.00171535 | 1(Win) | true |
| Jsonifier | 2669.57 | 0.504741 | 8902.43ms | 7351818 | 30 | 5.27187e+09 | 2.62636e+06 | 0.248612 | 1.88643 | 8.68479 | 2.01123 | 0.00667912 | 0.0275031 | 0.0017093 | 2(Loss) | true |
| simdjson (ondemand) | 2292.22 | 0.168057 | 5009.69ms | 7351818 | 30 | 7.92701e+08 | 3.05871e+06 | 0.714555 | 2.19535 | 9.45137 | 1.43645 | 0.00986308 | 0.0535843 | 0.00251752 | 3(Loss) | true |
| Glaze | 2225.59 | 0.193745 | 5102.79ms | 7351818 | 30 | 1.11758e+09 | 3.15028e+06 | 0.063977 | 2.25685 | 10.2817 | 2.06802 | 0.00919606 | 0.0274235 | 0.0019003 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5014.66 | 0.0888346 | 5890.95ms | 9930848 | 160 | 4.50376e+08 | 1.88862e+06 | 0.0331226 | 1.00689 | 3.40693 | 0.427912 | 0.000489601 | 0.0246876 | 0.00156171 | 1(Win) | true |
| Glaze | 2879.63 | 0.21373 | 5036.42ms | 9930228 | 80 | 3.95246e+09 | 3.28868e+06 | 1.21217 | 1.74527 | 4.21669 | 0.484737 | 0.00107413 | 0.0752439 | 0.0217339 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5023.78 | 0.0680537 | 5875.76ms | 9930848 | 80 | 1.31676e+08 | 1.88519e+06 | 0.0943237 | 1.00509 | 3.40689 | 0.427905 | 0.00051521 | 0.0246522 | 0.00111161 | 1(Win) | true |
| Glaze | 4075.12 | 0.0943429 | 7275.85ms | 9930228 | 160 | 7.69088e+08 | 2.32391e+06 | 0.157139 | 1.24032 | 4.21632 | 0.484654 | 0.00108185 | 0.0220135 | 0.00192174 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1266.14 | 0.127664 | 9099.03ms | 461466 | 80 | 1.57521e+07 | 347582 | 0.0343598 | 3.99895 | 17.3631 | 3.29407 | 0.0186719 | 0.0364685 | 6.25723e-05 | 1(Win) | true |
| Glaze | 1183.12 | 0.0775379 | 9720.9ms | 461466 | 320 | 2.66197e+07 | 371974 | 0.0879926 | 4.27034 | 19.1676 | 3.7914 | 0.013674 | 0.0326973 | 8.53462e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1101.86 | 0.11546 | 5183.77ms | 461466 | 80 | 1.70132e+07 | 399406 | 0.0752458 | 4.58453 | 18.839 | 3.55535 | 0.0251145 | 0.0777181 | 8.15065e-05 | 3(Loss) | true |
| simdjson (ondemand) | 825.243 | 0.124063 | 6895.47ms | 461466 | 160 | 7.00356e+07 | 533283 | 0.0134643 | 6.10067 | 25.2998 | 4.47819 | 0.0108109 | 0.0812863 | 0.000126987 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1766.82 | 0.0503943 | 8254.37ms | 461466 | 320 | 5.04208e+06 | 249085 | 0.00432852 | 2.86377 | 12.982 | 2.32283 | 0.0168196 | 0.00417747 | 1.26702e-05 | 1(Win) | true |
| Glaze | 1536.17 | 0.0459884 | 9232.85ms | 461466 | 1280 | 2.2218e+07 | 286484 | 0.267922 | 3.28982 | 15.2234 | 2.90401 | 0.0116302 | 0.00791946 | 5.68975e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1492.69 | 0.101953 | 9478.73ms | 461466 | 160 | 1.44565e+07 | 294829 | 0.0398122 | 3.38487 | 14.4747 | 2.58805 | 0.0224392 | 0.0267538 | 2.12096e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1025.01 | 0.108709 | 6355.82ms | 461466 | 640 | 1.39424e+08 | 429351 | 0.0121499 | 4.88076 | 21.1934 | 3.54764 | 0.00340877 | 0.0282894 | 5.22113e-05 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14668.2 | 0.0848086 | 3774ms | 461466 | 640 | 414368 | 30002.9 | 0.0377658 | 0.344478 | 1.61411 | 0.264108 | 0.000500247 | 0.00756095 | 4.22566e-06 | 1(Win) | true |
| Glaze | 3667.42 | 0.116008 | 6570.33ms | 461466 | 2560 | 4.96104e+07 | 120000 | 0.0292616 | 1.37283 | 5.36925 | 0.791549 | 0.00994509 | 0.0390602 | 1.66326e-05 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14725.5 | 0.0380981 | 3763.26ms | 461466 | 4890 | 633950 | 29886.1 | 0.0243136 | 0.343289 | 1.61296 | 0.263851 | 0.000497109 | 0.00734272 | 1.15006e-05 | 1(Win) | true |
| Glaze | 4003.73 | 0.128756 | 6025.23ms | 461466 | 2560 | 5.1277e+07 | 109919 | 0.143675 | 1.25579 | 5.35474 | 0.788156 | 0.00993031 | 0.0127783 | 3.1927e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1699.84 | 0.0337299 | 5308.2ms | 728486 | 640 | 1.21629e+07 | 408709 | 0.0894229 | 2.97115 | 12.498 | 2.27534 | 0.0154185 | 0.0706515 | 2.80183e-05 | 1(Win) | true |
| Glaze | 1546.96 | 0.0628583 | 5812.45ms | 728486 | 640 | 5.10023e+07 | 449099 | 0.00641347 | 3.26447 | 14.8121 | 2.94434 | 0.0105721 | 0.032284 | 0.000102132 | 2(Loss) | true |
| Jsonifier | 1391.72 | 0.0357516 | 6442.52ms | 728486 | 640 | 2.0385e+07 | 499194 | 0.117502 | 3.62921 | 13.9451 | 2.85952 | 0.0128095 | 0.038391 | 3.50213e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1254.05 | 0.0851134 | 7148ms | 728486 | 640 | 1.42294e+08 | 553994 | 0.147036 | 4.00202 | 16.5315 | 2.85935 | 0.00716196 | 0.0749455 | 0.000201677 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2281.05 | 0.0346309 | 9723.56ms | 728486 | 640 | 7.11999e+06 | 304569 | 0.117206 | 2.21417 | 9.72193 | 1.66003 | 0.0136271 | 0.0329987 | 2.37457e-05 | 1(Win) | true |
| Glaze | 1917.02 | 0.188954 | 5567.51ms | 728486 | 80 | 3.7514e+07 | 362406 | 0.0188533 | 2.63495 | 12.3121 | 2.38198 | 0.00896247 | 0.0111791 | 1.98528e-05 | 2(Loss) | true |
| Jsonifier | 1748.68 | 0.056139 | 5998.29ms | 728486 | 320 | 1.59185e+07 | 397294 | 0.090503 | 2.88865 | 11.1652 | 2.24348 | 0.0113621 | 0.0099614 | 3.17525e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1550.34 | 0.139132 | 6586.88ms | 728486 | 320 | 1.24391e+08 | 448120 | 0.114971 | 3.24071 | 13.9343 | 2.27057 | 0.00258567 | 0.0319817 | 3.19112e-05 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15830.6 | 0.0245664 | 5841.65ms | 837491 | 4890 | 751206 | 50452.5 | 0.0569628 | 0.319818 | 1.35618 | 0.257756 | 0.00044693 | 0.0170789 | 5.74532e-06 | 1(Win) | true |
| Glaze | 3924.64 | 0.237346 | 5436.17ms | 837491 | 160 | 3.73287e+07 | 203507 | 0.266141 | 1.28268 | 4.56906 | 0.770696 | 0.00620895 | 0.0562821 | 6.86575e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15890.3 | 0.107661 | 5816.16ms | 837491 | 320 | 937050 | 50263 | 0.0767616 | 0.318305 | 1.35555 | 0.257614 | 0.00044877 | 0.016882 | 1.628e-05 | 1(Win) | true |
| Glaze | 4491.5 | 0.0769409 | 9517.06ms | 837491 | 2560 | 4.79217e+07 | 177823 | 0.106341 | 1.12373 | 4.56028 | 0.768648 | 0.00622463 | 0.017905 | 3.19108e-05 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8201.63 | 0.0495689 | 6183.66ms | 466906 | 2560 | 1.85403e+06 | 54291.2 | 0.0527405 | 0.614862 | 3.05668 | 0.391276 | 0.00108896 | 3.53892e-06 | 1.65233e-06 | 1(Win) | true |
| Jsonifier | 8134.58 | 0.0322781 | 6220.21ms | 466906 | 4890 | 1.52656e+06 | 54738.7 | 0.106931 | 0.620227 | 3.06689 | 0.393921 | 0.00114982 | 3.33308e-06 | 1.35338e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6818.62 | 0.0780045 | 7304.68ms | 466906 | 320 | 830338 | 65303 | 0.0094024 | 0.74154 | 3.47898 | 0.3803 | 0.000808688 | 1.50525e-05 | 2.25554e-06 | 3(Loss) | true |
| Glaze | 3477.87 | 0.110732 | 7041.28ms | 466906 | 40 | 803974 | 128031 | 0.101142 | 1.48099 | 5.7431 | 0.996706 | 0.00169863 | 9.37019e-06 | 5.99692e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8326.58 | 0.0762357 | 6186.01ms | 466906 | 1280 | 2.12742e+06 | 53476.5 | 0.0103087 | 0.605532 | 3.02291 | 0.383405 | 0.00108391 | 4.0091e-06 | 2.11331e-06 | 1(Win) | true |
| Jsonifier | 8264.04 | 0.0371375 | 6236.41ms | 466906 | 4890 | 1.95798e+06 | 53881.2 | 0.0888979 | 0.609971 | 3.03245 | 0.385832 | 0.00112993 | 3.55646e-06 | 1.7029e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6921.54 | 0.0920676 | 7308.86ms | 466906 | 640 | 2.24516e+06 | 64332 | 0.117883 | 0.728972 | 3.43715 | 0.371826 | 0.000791069 | 7.8375e-06 | 3.20595e-06 | 3(Loss) | true |
| Glaze | 3448.31 | 0.0742109 | 7011.67ms | 466906 | 320 | 2.93854e+06 | 129129 | 0.0970952 | 1.4672 | 5.69568 | 0.986075 | 0.00163759 | 1.43832e-05 | 9.85878e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9371.77 | 0.112523 | 7194.72ms | 631514 | 80 | 418306 | 64263.1 | 0.0192216 | 0.539615 | 2.70824 | 0.304923 | 0.000869339 | 6.9278e-06 | 4.90884e-06 | 1(Win) | true |
| Jsonifier | 9332.94 | 0.033193 | 7199.67ms | 631514 | 4890 | 2.24352e+06 | 64530.4 | 0.0213155 | 0.537501 | 2.70765 | 0.304774 | 0.000828813 | 4.90333e-06 | 3.00605e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8088.91 | 0.221223 | 8197.41ms | 631514 | 1280 | 3.47263e+07 | 74454.9 | 0.156493 | 0.624741 | 2.90901 | 0.297687 | 0.000557668 | 0.00140643 | 1.58721e-06 | 3(Loss) | true |
| Glaze | 3988.28 | 0.0276294 | 8093.59ms | 631514 | 1280 | 2.22817e+06 | 151007 | 0.0269534 | 1.26896 | 5.34998 | 0.945575 | 0.00128034 | 2.99751e-06 | 1.44618e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9674.16 | 0.111017 | 7101.86ms | 631514 | 80 | 382130 | 62254.3 | 0.00526095 | 0.522707 | 2.68037 | 0.298201 | 0.000787374 | 4.43379e-06 | 2.17731e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 9641.59 | 0.0371113 | 7081.66ms | 631514 | 4890 | 2.62779e+06 | 62464.7 | 0.0149879 | 0.523307 | 2.67948 | 0.29797 | 0.000783458 | 1.13953e-05 | 7.56484e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8294.65 | 0.097502 | 8127.35ms | 631514 | 320 | 1.60379e+06 | 72608.1 | 0.0057676 | 0.608404 | 2.87775 | 0.29091 | 0.000573963 | 3.86967e-06 | 1.04907e-06 | 3(Loss) | true |
| Glaze | 4040.92 | 0.0764143 | 8045.74ms | 631514 | 160 | 2.07527e+06 | 149040 | 0.0464132 | 1.25336 | 5.31461 | 0.9373 | 0.0011691 | 3.4639e-06 | 1.15793e-06 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1836.31 | 0.0583627 | 6398.4ms | 466906 | 640 | 1.2818e+07 | 242485 | 0.250078 | 2.75385 | 8.31705 | 1.47308 | 0.0121145 | 0.0148243 | 3.87257e-05 | 1(Win) | true |
| Glaze | 1828.13 | 0.126603 | 6393.57ms | 466906 | 640 | 6.08571e+07 | 243570 | 0.0682584 | 2.75972 | 10.0645 | 1.80276 | 0.0125169 | 0.0107994 | 3.60418e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1692.56 | 0.126952 | 6892.89ms | 466906 | 320 | 3.56942e+07 | 263078 | 0.121232 | 2.96884 | 9.25619 | 1.53472 | 0.0171041 | 0.0278745 | 0.000165317 | 3(Loss) | true |
| simdjson (ondemand) | 932.52 | 0.145659 | 6170.85ms | 466906 | 160 | 7.73995e+07 | 477498 | 0.0461105 | 5.38851 | 18.198 | 3.17399 | 0.0140242 | 0.0394664 | 8.08514e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2317.89 | 0.0973459 | 5863.81ms | 466906 | 1280 | 4.47628e+07 | 192104 | 0.0499492 | 2.18046 | 6.83481 | 1.13322 | 0.00889911 | 0.00262865 | 8.4474e-05 | 1(Win) | true |
| Glaze | 2304.91 | 0.123082 | 5849.34ms | 466906 | 160 | 9.04609e+06 | 193186 | 0.00760659 | 2.19292 | 8.57808 | 1.46085 | 0.00956044 | 0.00104511 | 8.37963e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2253.29 | 0.0796939 | 6052ms | 466906 | 1280 | 3.17456e+07 | 197611 | 0.607601 | 2.24189 | 7.78353 | 1.19749 | 0.00993829 | 0.00768706 | 4.85995e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1055.52 | 0.217964 | 5826.08ms | 466906 | 80 | 6.76368e+07 | 421854 | 0.300505 | 4.75633 | 16.7911 | 2.85008 | 0.0100122 | 0.0101927 | 3.42949e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19477.1 | 0.0850084 | 3086.9ms | 475954 | 4890 | 1.91917e+06 | 23304.5 | 0.00616214 | 0.259654 | 1.01992 | 0.152899 | 0.000287488 | 0.000879462 | 2.97841e-06 | 1(Win) | true |
| Glaze | 6219.99 | 0.348161 | 8093.8ms | 475954 | 640 | 4.13134e+07 | 72975.2 | 0.0699064 | 0.810974 | 2.36357 | 0.337163 | 0.000364991 | 0.0118293 | 2.31049e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19567 | 0.181857 | 3077.63ms | 475954 | 1280 | 2.27799e+06 | 23197.5 | 0.402926 | 0.257965 | 1.01871 | 0.152632 | 0.000281079 | 0.000735917 | 2.48022e-06 | 1(Win) | true |
| Glaze | 6896.44 | 0.138558 | 7361.84ms | 475954 | 4890 | 4.06679e+07 | 65817.3 | 0.0193264 | 0.732049 | 2.35134 | 0.334375 | 0.000344866 | 0.00183827 | 4.8904e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2189.05 | 0.0886508 | 7237.95ms | 631514 | 640 | 3.80715e+07 | 275123 | 0.082861 | 2.30735 | 7.30199 | 1.15229 | 0.0122009 | 0.0348996 | 9.65364e-05 | 1(Win) | true |
| Glaze | 2022.95 | 0.0497179 | 7805.61ms | 631514 | 640 | 1.40216e+07 | 297712 | 0.0324049 | 2.49703 | 9.09149 | 1.66455 | 0.0114079 | 0.0187992 | 5.89481e-05 | 2(Loss) | true |
| Jsonifier | 1577.69 | 0.0968327 | 9976.52ms | 631514 | 320 | 4.37239e+07 | 381735 | 0.0920038 | 3.20506 | 7.97122 | 1.53396 | 0.0103473 | 0.0256684 | 0.000334118 | 3(Loss) | true |
| simdjson (ondemand) | 1233.92 | 0.123486 | 6326.3ms | 631514 | 320 | 1.16245e+08 | 488084 | 0.129942 | 4.06628 | 13.7943 | 2.36388 | 0.0101586 | 0.0412706 | 0.000180533 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2735.83 | 0.132541 | 6670.77ms | 631514 | 320 | 2.7242e+07 | 220138 | 0.126319 | 1.84414 | 6.21056 | 0.902752 | 0.00955894 | 0.011461 | 1.84378e-05 | 1(Win) | true |
| Glaze | 2522.37 | 0.0432525 | 7094.85ms | 631514 | 1280 | 1.36515e+07 | 238767 | 0.0849169 | 2.00176 | 7.99565 | 1.41349 | 0.00726629 | 0.00348358 | 8.76985e-06 | 2(Loss) | true |
| Jsonifier | 1885.42 | 0.237402 | 9090.75ms | 631514 | 320 | 1.84023e+08 | 319430 | 0.0731588 | 2.6755 | 6.87648 | 1.28305 | 0.00583835 | 0.00646907 | 8.53653e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1385.07 | 0.167392 | 5980.53ms | 631514 | 160 | 8.47641e+07 | 434823 | 0.283004 | 3.61582 | 12.7512 | 2.12312 | 0.00758401 | 0.0136452 | 0.00014197 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18159 | 0.151058 | 4533.58ms | 716365 | 1280 | 4.13414e+06 | 37622.1 | 0.0978899 | 0.278162 | 1.02706 | 0.178553 | 0.000217005 | 0.00530255 | 8.84348e-06 | 1(Win) | true |
| Glaze | 4478.06 | 0.186859 | 8240.5ms | 716365 | 1280 | 1.04022e+08 | 152561 | 0.0735972 | 1.12389 | 2.81749 | 0.463529 | 0.000564553 | 0.0459144 | 6.76571e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18198.8 | 0.120244 | 4512.54ms | 716365 | 2560 | 5.21617e+06 | 37539.8 | 0.101372 | 0.277806 | 1.0263 | 0.17838 | 0.000212617 | 0.00521627 | 1.74563e-05 | 1(Win) | true |
| Glaze | 5459.25 | 0.161929 | 6817.18ms | 716365 | 2560 | 1.05122e+08 | 125142 | 0.0701746 | 0.923347 | 2.80754 | 0.461218 | 0.000553969 | 0.0050711 | 2.1516e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2436.41 | 0.0951816 | 836.755ms | 2632 | 4890 | 4702.01 | 1030.23 | 0.161146 | 2.15848 | 8.04027 | 1.39666 | 0.000847521 | 5.82729e-05 | 1.56948e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2172.05 | 0.253698 | 852.055ms | 2632 | 1280 | 11002.1 | 1155.62 | 0.0110883 | 2.40903 | 9.75418 | 1.71505 | 0.000838538 | 4.83829e-05 | 2.07779e-06 | 2(Loss) | true |
| Glaze | 1940.78 | 0.0732308 | 883.972ms | 2632 | 4890 | 4386.47 | 1293.33 | 0.0875752 | 2.68714 | 11.3583 | 2.13336 | 0.00208695 | 4.63075e-05 | 6.75965e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1369.45 | 0.306911 | 948.824ms | 2632 | 640 | 20252.8 | 1832.91 | 0.160094 | 3.76919 | 12.8526 | 2.22796 | 0.00526809 | 8.01434e-05 | 5.93655e-06 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2915.26 | 0.0976207 | 827.009ms | 2632 | 4890 | 3454.69 | 861.01 | 0.262991 | 1.81802 | 7.01406 | 1.13336 | 0.000799038 | 4.45982e-05 | 6.21577e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2542.35 | 0.137727 | 841.659ms | 2632 | 2560 | 4733.48 | 987.305 | 0.341933 | 2.08963 | 8.72682 | 1.45175 | 0.000762698 | 9.79531e-05 | 3.1909e-05 | 2(Loss) | true |
| Glaze | 2491.76 | 0.297802 | 840.2ms | 2632 | 40 | 359.977 | 1007.35 | 0.0314455 | 2.10935 | 9.47948 | 1.69947 | 0.00165274 | 1.8997e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1618.26 | 0.085112 | 919.591ms | 2632 | 4890 | 8522.53 | 1551.1 | 0.119664 | 3.20621 | 11.4669 | 1.89894 | 0.00142015 | 7.0549e-05 | 1.49956e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10775.4 | 0.233531 | 757.837ms | 2632 | 160 | 47.349 | 232.944 | 0.390562 | 0.551422 | 1.87804 | 0.301292 | 0.000536664 | 4.74924e-06 | 0 | 1(Win) | true |
| Glaze | 3452.87 | 0.136809 | 806.458ms | 2632 | 4890 | 4836.7 | 726.953 | 0.269153 | 1.54754 | 4.84461 | 0.760639 | 0.000387787 | 8.30583e-05 | 1.67049e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12445.3 | 0.172698 | 750.432ms | 2632 | 160 | 19.4112 | 201.688 | 0.360764 | 0.487835 | 1.67819 | 0.255699 | 0.000379939 | 2.37462e-05 | 0 | 1(Win) | true |
| Glaze | 3503.83 | 0.150757 | 800.673ms | 2632 | 4890 | 5703.62 | 716.38 | 0.138488 | 1.52646 | 4.30509 | 0.647417 | 0.000387787 | 4.43651e-05 | 3.03019e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2616.81 | 0.113469 | 860.357ms | 3370 | 4890 | 9496.75 | 1228.17 | 0.1769 | 2.00154 | 8.08902 | 1.36499 | 0.000769268 | 5.65558e-05 | 1.32287e-05 | 1(Win) | true |
| Jsonifier | 2094.71 | 0.295118 | 886.302ms | 3370 | 640 | 13121.5 | 1534.28 | 0.0570991 | 2.47942 | 8.80979 | 1.74154 | 0.00137658 | 9.41209e-05 | 1.90096e-05 | 2(Loss) | true |
| Glaze | 2029.23 | 0.0928449 | 914.811ms | 3370 | 4890 | 10573.6 | 1583.79 | 0.0386424 | 2.54144 | 10.7682 | 2.06172 | 0.00214493 | 6.28061e-05 | 1.51705e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1720.64 | 0.101489 | 951.989ms | 3370 | 2560 | 9199.33 | 1867.84 | 0.201296 | 3.0045 | 10.3193 | 1.75312 | 0.00420843 | 7.5459e-05 | 2.3878e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3043.92 | 0.163206 | 849.464ms | 3370 | 2560 | 7601.6 | 1055.84 | 0.400385 | 1.72703 | 7.21543 | 1.1457 | 0.000894496 | 4.32353e-05 | 5.10015e-06 | 1(Win) | true |
| Glaze | 2488.74 | 0.37333 | 872.844ms | 3370 | 640 | 14875.4 | 1291.37 | 0.0223892 | 2.09459 | 9.29733 | 1.72285 | 0.00109792 | 3.38464e-05 | 6.02745e-06 | 2(Loss) | true |
| Jsonifier | 2349.13 | 0.118586 | 882.324ms | 3370 | 4890 | 12871.2 | 1368.12 | 0.0188482 | 2.21441 | 8.00445 | 1.53591 | 0.00142549 | 4.59971e-05 | 5.70413e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1982.9 | 0.29321 | 911.786ms | 3370 | 40 | 903.395 | 1620.8 | 0.00617017 | 2.61567 | 9.31573 | 1.51217 | 0.00212166 | 7.4184e-05 | 0 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10542 | 0.221543 | 763.01ms | 3643 | 4890 | 2606.76 | 329.562 | 0.744786 | 0.539504 | 1.77272 | 0.307165 | 0.000433697 | 3.97434e-05 | 8.64476e-06 | 1(Win) | true |
| Glaze | 3514.39 | 0.125511 | 833.917ms | 3682 | 4890 | 7690.18 | 999.157 | 0.34016 | 1.49974 | 4.54407 | 0.759384 | 0.000389059 | 4.02111e-05 | 4.44322e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13103.4 | 0.353711 | 755.83ms | 3643 | 640 | 562.89 | 265.139 | 0.325769 | 0.445212 | 1.6146 | 0.266813 | 0.000275786 | 2.14452e-05 | 8.57809e-07 | 1(Win) | true |
| Glaze | 3839 | 0.126975 | 822.689ms | 3682 | 4890 | 6595.97 | 914.673 | 0.197134 | 1.37761 | 4.19772 | 0.680608 | 0.000274313 | 3.31575e-05 | 2.99917e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1012.27 | 0.0521945 | 1170.4ms | 4630 | 4890 | 25347.3 | 4362.01 | 0.0176557 | 5.04114 | 23.3475 | 4.76458 | 0.00590856 | 9.22233e-05 | 3.3612e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 905.992 | 0.0881624 | 1224.83ms | 4630 | 2560 | 47262.8 | 4873.68 | 0.00578716 | 5.63179 | 26.1857 | 5.06091 | 0.00609105 | 8.74055e-05 | 3.32411e-05 | 2(Loss) | true |
| simdjson (ondemand) | 749.168 | 0.0469591 | 1331.07ms | 4630 | 4890 | 37458.7 | 5893.88 | 0.204892 | 6.79324 | 31.3572 | 5.46501 | 0.00272001 | 9.20908e-05 | 4.07673e-05 | 3(Loss) | true |
| Glaze | 742.522 | 0.0695487 | 1329.45ms | 4630 | 2560 | 43788.7 | 5946.64 | 0.0289572 | 6.85064 | 30.2754 | 5.85788 | 0.00459849 | 6.12513e-05 | 1.74642e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1272.56 | 0.0652055 | 1166.08ms | 4630 | 4890 | 25031.4 | 3469.79 | 0.325467 | 4.01719 | 18.9857 | 3.75356 | 0.00399983 | 5.20744e-05 | 8.03862e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1119.09 | 0.0775505 | 1223.7ms | 4630 | 2560 | 23968.3 | 3945.61 | 0.0875155 | 4.5595 | 21.8346 | 4.05184 | 0.00378746 | 5.35738e-05 | 1.11366e-05 | 2(Loss) | true |
| Glaze | 879.724 | 0.168879 | 1329.47ms | 4630 | 80 | 5747.88 | 5019.2 | 0.00647555 | 5.79907 | 25.8063 | 4.82376 | 0.00321274 | 2.96976e-05 | 5.39957e-06 | 3(Loss) | true |
| simdjson (ondemand) | 857.638 | 0.114568 | 1355.45ms | 4630 | 1280 | 44533.7 | 5148.45 | 0.0346768 | 5.94911 | 28.4181 | 4.78294 | 0.000597496 | 0.000160637 | 8.94303e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1834.56 | 0.15433 | 979.262ms | 4630 | 1280 | 17660.7 | 2406.85 | 0.114483 | 2.75782 | 7.95032 | 0.458316 | 0.000334098 | 2.2442e-05 | 0 | 1(Win) | true |
| Glaze | 974.276 | 0.0289556 | 1191.48ms | 4630 | 4890 | 8421.16 | 4532.1 | 0.0172165 | 5.23115 | 9.78164 | 0.680778 | 0.000229675 | 5.28694e-05 | 1.12187e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1902.54 | 0.096034 | 969.938ms | 4630 | 2560 | 12716.9 | 2320.85 | 0.0877335 | 2.66588 | 7.83974 | 0.433262 | 0.000226107 | 3.06257e-05 | 6.15888e-06 | 1(Win) | true |
| Glaze | 1005.61 | 0.0294793 | 1168.97ms | 4630 | 4890 | 8193 | 4390.87 | 0.00923778 | 5.05664 | 9.27775 | 0.568036 | 0.000231927 | 4.05023e-05 | 1.30296e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2171.01 | 0.0600945 | 1252.11ms | 11579 | 4890 | 45687.3 | 5086.38 | 0.0982889 | 2.34061 | 11.1648 | 2.03826 | 0.00197927 | 3.01123e-05 | 7.01149e-06 | 1(Win) | true |
| Jsonifier | 1912.35 | 0.0551178 | 1319.55ms | 11579 | 4890 | 49533.8 | 5774.37 | 0.0698278 | 2.65154 | 11.951 | 2.61465 | 0.00426377 | 5.3743e-05 | 2.69333e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1780.55 | 0.054801 | 1363.85ms | 11579 | 4890 | 56483.5 | 6201.8 | 0.0293623 | 2.84503 | 13.006 | 2.16495 | 0.00133202 | 2.53615e-05 | 6.07545e-06 | 3(Loss) | true |
| Glaze | 1469.17 | 0.053134 | 1489.08ms | 11579 | 4890 | 77992.6 | 7516.22 | 0.124521 | 3.44204 | 14.9296 | 2.88825 | 0.004445 | 8.13298e-05 | 3.92608e-05 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2628.26 | 0.190039 | 1258.01ms | 11579 | 320 | 20400.5 | 4201.48 | 0.0350445 | 1.94062 | 9.43372 | 1.63727 | 0.00156722 | 1.83522e-05 | 2.42897e-06 | 1(Win) | true |
| Jsonifier | 2302.9 | 0.117689 | 1313.71ms | 11579 | 1280 | 40763.7 | 4795.08 | 0.212664 | 2.21046 | 10.2157 | 2.21219 | 0.0033343 | 1.80823e-05 | 2.02414e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2009.77 | 0.0547864 | 1392.37ms | 11579 | 4890 | 44310.1 | 5494.44 | 0.0165441 | 2.52266 | 11.9826 | 1.92158 | 0.000490398 | 2.96531e-05 | 8.24778e-06 | 3(Loss) | true |
| Glaze | 1663.09 | 0.0453305 | 1496.71ms | 11579 | 4890 | 44299.6 | 6639.8 | 0.191205 | 3.03805 | 13.1734 | 2.48139 | 0.00420751 | 2.17409e-05 | 4.71554e-06 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4484.18 | 0.0719232 | 1058.25ms | 14795 | 4890 | 25044.3 | 3146.53 | 0.059882 | 1.12614 | 2.9756 | 0.279892 | 0.000329299 | 1.37392e-05 | 2.9303e-06 | 1(Win) | true |
| Glaze | 3598.63 | 0.144737 | 1133.97ms | 14795 | 1280 | 41221.8 | 3920.83 | 0.198642 | 1.40313 | 4.44738 | 0.532815 | 0.000950226 | 1.23036e-05 | 1.37293e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4706.42 | 0.128692 | 1035.55ms | 14795 | 640 | 9526.41 | 2997.95 | 0.0468248 | 1.06922 | 2.93667 | 0.270902 | 0.000276698 | 9.08246e-06 | 1.0561e-07 | 1(Win) | true |
| Glaze | 3816.65 | 0.240982 | 1114.34ms | 14795 | 320 | 25397.1 | 3696.86 | 0.0201989 | 1.33962 | 4.24475 | 0.486786 | 0.000950912 | 1.03498e-05 | 1.68976e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1639.02 | 0.154301 | 923.799ms | 3223 | 2560 | 21435.2 | 1875.32 | 0.151996 | 3.15083 | 11.9299 | 2.25225 | 0.00115273 | 5.42972e-05 | 1.40591e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1370.4 | 0.213127 | 960.404ms | 3223 | 1280 | 29249.3 | 2242.92 | 0.321658 | 3.72829 | 14.6758 | 2.58672 | 0.00111067 | 4.48437e-05 | 2.42398e-06 | 2(Loss) | true |
| Glaze | 1334.94 | 0.109539 | 967.567ms | 3223 | 4890 | 31106.1 | 2302.5 | 0.11067 | 3.85345 | 15.0828 | 2.86658 | 0.00148428 | 6.86528e-05 | 1.40224e-05 | 3(Loss) | true |
| simdjson (ondemand) | 975.319 | 0.236198 | 1055.93ms | 3223 | 40 | 2216.36 | 3151.47 | 0.0193069 | 5.25323 | 19.4729 | 3.17251 | 0.0028157 | 0.000139621 | 5.42972e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1985.47 | 0.152319 | 914.989ms | 3223 | 4890 | 27189.9 | 1548.09 | 0.103353 | 2.60669 | 10.3317 | 1.84642 | 0.00109051 | 5.58359e-05 | 1.21824e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1621.37 | 0.212726 | 947.483ms | 3223 | 1280 | 20816.6 | 1895.74 | 0.015003 | 3.18499 | 13.0773 | 2.18089 | 0.00108425 | 5.42972e-05 | 1.33319e-05 | 2(Loss) | true |
| Glaze | 1603.26 | 0.152286 | 952.385ms | 3223 | 40 | 340.951 | 1917.15 | 0.0182596 | 3.22381 | 13.4353 | 2.45206 | 0.00112473 | 0.000124108 | 6.2054e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1117.14 | 0.233937 | 1036.79ms | 3223 | 1280 | 53028.9 | 2751.39 | 0 | 4.59126 | 17.7017 | 2.73689 | 0.00157704 | 0.000106413 | 4.12077e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7479.14 | 0.269835 | 774.572ms | 3223 | 1280 | 1574.08 | 410.969 | 0.0475475 | 0.743852 | 2.35774 | 0.410177 | 0.000450134 | 2.32702e-05 | 2.18159e-06 | 1(Win) | true |
| Glaze | 2765.18 | 0.22988 | 845.984ms | 3223 | 2560 | 16715.4 | 1111.57 | 0.104788 | 1.89792 | 5.21719 | 0.779088 | 0.000318027 | 5.13885e-05 | 6.18116e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8435.56 | 0.207201 | 767.838ms | 3223 | 4890 | 2787.32 | 364.373 | 0.141102 | 0.672533 | 2.19516 | 0.372014 | 0.000311349 | 2.70931e-05 | 3.29939e-06 | 1(Win) | true |
| Glaze | 3054.13 | 0.396394 | 832.967ms | 3223 | 1280 | 20370.9 | 1006.4 | 0.402719 | 1.72233 | 4.65106 | 0.65252 | 0.000317299 | 8.36274e-05 | 2.08463e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2343.33 | 0.101288 | 974.021ms | 5839 | 4890 | 28329.5 | 2376.33 | 0.0976889 | 2.19751 | 8.7652 | 1.46189 | 0.000625615 | 4.60902e-05 | 1.35189e-05 | 1(Win) | true |
| Jsonifier | 1802.79 | 0.539467 | 1044.93ms | 5839 | 640 | 177704 | 3088.82 | 0.166095 | 2.84243 | 9.8486 | 2.08032 | 0.00144048 | 3.8534e-05 | 4.28156e-06 | 2(Loss) | true |
| Glaze | 1773.63 | 0.226216 | 1048.49ms | 5839 | 320 | 16141.6 | 3139.6 | 0.0473014 | 2.88827 | 11.2622 | 2.17503 | 0.00197112 | 1.44502e-05 | 2.14078e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1727.54 | 0.134226 | 1061.05ms | 5839 | 2560 | 47921.5 | 3223.37 | 0.194668 | 2.96245 | 11.1934 | 1.75989 | 0.00102991 | 3.49883e-05 | 8.63001e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2686.7 | 0.155269 | 964.187ms | 5839 | 2560 | 26512.3 | 2072.62 | 0.107071 | 1.92007 | 7.9262 | 1.24645 | 0.00078881 | 2.42175e-05 | 1.73938e-06 | 1(Win) | true |
| Jsonifier | 2030.87 | 0.179287 | 1030.05ms | 5839 | 4890 | 118173 | 2741.93 | 0.147196 | 2.52544 | 8.96695 | 1.85631 | 0.00140722 | 3.49879e-05 | 8.26542e-06 | 2(Loss) | true |
| Glaze | 2002.96 | 0.105722 | 1036.38ms | 5839 | 4890 | 42244.8 | 2780.13 | 0.119729 | 2.56138 | 10.3523 | 1.94622 | 0.00149565 | 3.70193e-05 | 6.75943e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1926.06 | 0.0930671 | 1049.15ms | 5839 | 4890 | 35403 | 2891.14 | 0.166775 | 2.66041 | 10.3017 | 1.53639 | 0.000996018 | 3.00147e-05 | 2.76681e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10359.1 | 0.240169 | 799.069ms | 6938 | 2560 | 6024.19 | 638.724 | 0.146318 | 0.519799 | 1.73595 | 0.316085 | 0.000198803 | 1.97621e-05 | 2.70251e-06 | 1(Win) | true |
| Glaze | 3492.11 | 0.223764 | 929.339ms | 6960 | 2560 | 46308.8 | 1900.74 | 0.00731678 | 1.48166 | 4.23262 | 0.722414 | 0.000296336 | 3.5246e-05 | 3.47971e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11302.6 | 0.159639 | 793.053ms | 6938 | 4890 | 4270.75 | 585.407 | 0.0483703 | 0.478417 | 1.66388 | 0.29951 | 0.000144664 | 1.57692e-05 | 1.47376e-06 | 1(Win) | true |
| Glaze | 3783.18 | 0.23932 | 911.71ms | 6960 | 2560 | 45133.7 | 1754.49 | 0.407913 | 1.3571 | 3.8717 | 0.645259 | 0.000293923 | 2.78938e-05 | 2.80621e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2020.29 | 0.160831 | 965.612ms | 4857 | 1280 | 17404.5 | 2292.74 | 0.0792528 | 2.54009 | 9.4721 | 1.78938 | 0.00096671 | 2.34841e-05 | 3.53871e-06 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1776 | 0.191621 | 1001.32ms | 4857 | 40 | 999.067 | 2608.1 | 0.0230105 | 2.89236 | 11.5715 | 2.04694 | 0.0012971 | 0.000164711 | 0.000113239 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1768.48 | 0.101476 | 1002.03ms | 4857 | 320 | 2260.55 | 2619.19 | 0.088689 | 2.90465 | 11.8779 | 2.27033 | 0.000230338 | 3.92475e-05 | 0 | 2(Tie) | true |
| simdjson (ondemand) | 772.025 | 0.102379 | 1339.97ms | 4857 | 2560 | 96590.5 | 5999.8 | 0.070779 | 6.58716 | 22.8636 | 3.9649 | 0.00359878 | 3.99713e-05 | 9.16847e-06 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2624.2 | 0.123457 | 939.271ms | 4857 | 4890 | 23221.2 | 1765.11 | 0.146831 | 1.96897 | 7.40416 | 1.31213 | 0.000873615 | 3.54936e-05 | 7.53661e-06 | 1(Win) | true |
| Glaze | 2533.78 | 0.0936754 | 944.263ms | 4857 | 4890 | 14340.3 | 1828.1 | 0.182667 | 2.0416 | 8.92506 | 1.60984 | 0.00119782 | 4.51355e-05 | 6.02087e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2165.28 | 0.10576 | 976.18ms | 4857 | 4890 | 25029.9 | 2139.22 | 0.0453427 | 2.37871 | 9.68376 | 1.60552 | 0.00077345 | 3.26306e-05 | 4.2525e-06 | 3(Loss) | true |
| simdjson (ondemand) | 865.241 | 0.10179 | 1298.86ms | 4857 | 2560 | 76017.8 | 5353.42 | 0.0965341 | 5.88647 | 20.6695 | 3.47622 | 0.0035823 | 3.81215e-05 | 4.02126e-06 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9730.08 | 0.375077 | 784.384ms | 4857 | 2560 | 8161.77 | 476.049 | 0.158618 | 0.563973 | 1.69014 | 0.291744 | 0.000260175 | 2.60578e-05 | 5.30806e-06 | 1(Win) | true |
| Glaze | 2789.35 | 0.134568 | 903.231ms | 4857 | 4890 | 24418.6 | 1660.6 | 0.0779233 | 1.85804 | 4.17954 | 0.637225 | 0.00021313 | 3.25043e-05 | 4.42092e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11668.9 | 0.302655 | 776.678ms | 4857 | 2560 | 3694.95 | 396.951 | 0.0849968 | 0.476312 | 1.57175 | 0.261684 | 0.000207014 | 2.75054e-05 | 4.66466e-06 | 1(Win) | true |
| Glaze | 3181.64 | 0.219548 | 878.887ms | 4857 | 2560 | 26153.9 | 1455.85 | 0.271841 | 1.62709 | 3.68581 | 0.525428 | 0.000211116 | 2.31624e-05 | 1.68893e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2340.77 | 0.203994 | 1009ms | 6701 | 640 | 19850.7 | 2730.12 | 0.0878709 | 2.19413 | 8.88002 | 1.50291 | 0.000674106 | 3.14785e-05 | 7.92792e-06 | 1(Win) | true |
| Glaze | 1977.92 | 0.119765 | 1062.04ms | 6701 | 2560 | 38331.8 | 3230.95 | 0.175976 | 2.58903 | 10.9672 | 2.14938 | 0.000918123 | 4.37784e-05 | 1.32909e-05 | 2(Loss) | true |
| Jsonifier | 1643.13 | 0.229827 | 1134.69ms | 6701 | 2560 | 204538 | 3889.26 | 0.2733 | 3.0965 | 9.94165 | 2.08506 | 0.00191535 | 6.6921e-05 | 3.36937e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1049.27 | 0.0695596 | 1350.31ms | 6701 | 4890 | 87766.1 | 6090.48 | 0.0432903 | 4.84293 | 16.9299 | 2.88763 | 0.00250202 | 7.83389e-05 | 2.1576e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2845.75 | 0.116539 | 991.131ms | 6701 | 4890 | 33492.1 | 2245.66 | 0.10024 | 1.80914 | 7.47023 | 1.17505 | 0.000893314 | 4.14125e-05 | 1.17798e-05 | 1(Win) | true |
| Glaze | 2634.38 | 0.102246 | 1004.88ms | 6701 | 4890 | 30083.5 | 2425.84 | 0.117806 | 1.95207 | 8.86704 | 1.67975 | 0.00112 | 4.13515e-05 | 1.17493e-05 | 2(Loss) | true |
| Jsonifier | 1966.04 | 0.141221 | 1092.97ms | 6701 | 4890 | 103039 | 3250.48 | 0.140383 | 2.60477 | 8.42337 | 1.73556 | 0.00154035 | 4.05885e-05 | 1.35804e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1171.21 | 0.122426 | 1310.91ms | 6701 | 1280 | 57116.9 | 5456.36 | 0.0315672 | 4.34466 | 15.3855 | 2.54216 | 0.00264571 | 7.77636e-05 | 3.03126e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11128 | 0.2067 | 799.284ms | 7376 | 4890 | 8348.31 | 632.127 | 0.552802 | 0.48387 | 1.54338 | 0.28064 | 0.00033708 | 2.096e-05 | 6.04403e-06 | 1(Win) | true |
| Glaze | 2850.81 | 0.407262 | 988.151ms | 7376 | 640 | 64629.8 | 2467.47 | 0.0579078 | 1.80084 | 4.56331 | 0.737799 | 0.000659868 | 3.81304e-05 | 1.2922e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12751.3 | 0.201127 | 790.176ms | 7376 | 4890 | 6019.79 | 551.654 | 0.279501 | 0.426244 | 1.46204 | 0.261659 | 0.000136323 | 2.10709e-05 | 3.90921e-06 | 1(Win) | true |
| Glaze | 2998.07 | 0.150772 | 973.909ms | 7376 | 4890 | 61193.6 | 2346.27 | 0.316138 | 1.71462 | 4.25231 | 0.667029 | 0.000566115 | 2.67545e-05 | 6.65398e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2015.17 | 0.23219 | 812.848ms | 1691 | 4890 | 16883.4 | 800.261 | 0.575472 | 2.63979 | 8.78001 | 1.51508 | 0.00179236 | 0.000105575 | 2.63636e-05 | 1(Win) | true |
| Glaze | 1915.22 | 0.158726 | 818.517ms | 1691 | 4890 | 8734.85 | 842.023 | 0.0303477 | 2.77205 | 10.1928 | 1.93318 | 0.000653042 | 0.000204862 | 7.8486e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1766.21 | 0.144757 | 827.222ms | 1691 | 30 | 52.4092 | 913.067 | 0.305721 | 2.99367 | 10.1023 | 1.7327 | 0.000591366 | 3.94244e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1382.42 | 0.165989 | 854.667ms | 1691 | 4890 | 18334.7 | 1166.55 | 0.0563076 | 3.79146 | 12.4778 | 2.09107 | 0.000603097 | 0.000124562 | 2.08006e-05 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2537.27 | 0.259986 | 807.223ms | 1691 | 2560 | 6990.27 | 635.591 | 0.138597 | 2.12528 | 7.22176 | 1.12892 | 0.00178357 | 9.9331e-05 | 2.67963e-05 | 1(Win) | true |
| Glaze | 2347.53 | 0.154009 | 809.755ms | 1691 | 4890 | 5473.51 | 686.963 | 0.0304175 | 2.28603 | 8.78238 | 1.57836 | 0.00069803 | 8.96119e-05 | 1.58423e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2092.43 | 0.209665 | 819.115ms | 1691 | 4890 | 12768.7 | 770.712 | 0.394538 | 2.54816 | 8.53578 | 1.34477 | 0.00101306 | 8.62258e-05 | 9.3119e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1590.19 | 0.285254 | 846.124ms | 1691 | 1280 | 10711.8 | 1014.13 | 0.0355264 | 3.30948 | 11.0562 | 1.73803 | 0.000603378 | 6.69907e-05 | 6.46807e-06 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9369.37 | 0.827055 | 751.506ms | 1996 | 640 | 1806.96 | 203.166 | 0.00615299 | 0.649669 | 1.60671 | 0.267034 | 0.000785947 | 4.2272e-05 | 2.34845e-06 | 1(Win) | true |
| Glaze | 3950.4 | 0.29437 | 780.024ms | 1996 | 2560 | 5150.72 | 481.859 | 0.0711256 | 1.38864 | 3.79459 | 0.596193 | 0.000984195 | 5.36229e-05 | 5.67541e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12430.7 | 0.556516 | 745.006ms | 1996 | 1280 | 929.593 | 153.131 | 0.130437 | 0.516725 | 1.35671 | 0.20992 | 0.000501393 | 2.70071e-05 | 2.34845e-06 | 1(Win) | true |
| Glaze | 4363.5 | 0.512906 | 775.994ms | 1996 | 320 | 1602.06 | 436.241 | 1.07642 | 1.26688 | 3.25601 | 0.480461 | 0.000502568 | 2.50501e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2226.31 | 0.808634 | 828.011ms | 2158 | 320 | 17880.8 | 924.413 | 0.0540592 | 2.37142 | 8.25626 | 1.36237 | 0.000470633 | 7.38531e-05 | 0 | 1(Win) | true |
| Glaze | 1946.69 | 0.221822 | 842.697ms | 2158 | 2560 | 14078.6 | 1057.19 | 0.239043 | 2.69767 | 9.8772 | 1.8962 | 0.000483484 | 0.000113133 | 2.96861e-05 | 2(Loss) | true |
| Jsonifier | 1862.71 | 0.294295 | 846.277ms | 2158 | 4890 | 51699.4 | 1104.86 | 0.109358 | 2.80505 | 8.92586 | 1.70621 | 0.000476375 | 9.66585e-05 | 2.15112e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1746.8 | 0.156904 | 856.018ms | 2158 | 4890 | 16710.6 | 1178.17 | 0.0367459 | 2.99204 | 9.9101 | 1.62836 | 0.000474195 | 0.000114853 | 2.02793e-05 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2703.43 | 0.195543 | 820.963ms | 2158 | 30 | 66.4782 | 761.267 | 0.170477 | 1.93692 | 7.02873 | 1.05839 | 0.000463392 | 6.17856e-05 | 0 | 1(Win) | true |
| Glaze | 2335.89 | 0.214229 | 831.557ms | 2158 | 2560 | 9120.01 | 881.048 | 0.169388 | 2.26491 | 8.59314 | 1.58248 | 0.000477692 | 4.52531e-05 | 3.07721e-06 | 2(Loss) | true |
| Jsonifier | 2260.33 | 0.318095 | 838.901ms | 2158 | 80 | 671.063 | 910.5 | 0.230112 | 2.34076 | 7.76089 | 1.41427 | 0.000463392 | 3.47544e-05 | 1.15848e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1979.32 | 0.30855 | 849.179ms | 2158 | 1280 | 13174.4 | 1039.76 | 0.0304964 | 2.65606 | 8.91336 | 1.37489 | 0.000474977 | 9.48506e-05 | 3.11342e-05 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10593.9 | 0.3871 | 761.25ms | 2866 | 40 | 39.8974 | 258 | 0.360453 | 0.551614 | 1.49826 | 0.259944 | 0.000348918 | 0 | 0 | 1(Win) | true |
| Glaze | 3644.86 | 0.274149 | 810.241ms | 2866 | 2560 | 10819.4 | 749.886 | 0.446584 | 1.46448 | 4.21738 | 0.728542 | 0.000356687 | 5.2474e-05 | 1.15852e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12299.1 | 0.357022 | 754.362ms | 2866 | 4890 | 3078.25 | 222.23 | 0.0893135 | 0.487539 | 1.32275 | 0.220168 | 0.000349703 | 2.38321e-05 | 1.92654e-06 | 1(Win) | true |
| Glaze | 3981.04 | 0.222625 | 803.521ms | 2866 | 4890 | 11423.9 | 686.561 | 0.155399 | 1.32705 | 3.57397 | 0.584439 | 0.000354912 | 2.85414e-05 | 3.71038e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2274.65 | 0.0838356 | 918.511ms | 4390 | 4890 | 11643 | 1840.56 | 0.00204276 | 2.27396 | 10.4692 | 1.85672 | 0.00160171 | 5.62256e-05 | 2.22666e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1716.1 | 0.0916949 | 983.352ms | 4390 | 4890 | 24470.4 | 2439.61 | 0.157411 | 2.97924 | 13.9068 | 2.39977 | 0.00258945 | 7.40202e-05 | 2.39436e-05 | 2(Loss) | true |
| Glaze | 1704.04 | 0.0679617 | 983.74ms | 4390 | 4890 | 13633.6 | 2456.89 | 0.00527421 | 3.00455 | 13.7622 | 2.65148 | 0.000732283 | 3.80582e-05 | 9.27e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1074.03 | 0.0744537 | 1126.11ms | 4390 | 4890 | 41188.5 | 3898.05 | 0.000593861 | 4.74214 | 20.4023 | 3.38474 | 0.00319228 | 6.51229e-05 | 1.41612e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2676.03 | 0.154579 | 914.742ms | 4390 | 1280 | 7486.15 | 1564.49 | 0.00933721 | 1.94035 | 9.24442 | 1.57335 | 0.00148971 | 2.90077e-05 | 8.7201e-06 | 1(Win) | true |
| Glaze | 1977.24 | 0.128855 | 969.274ms | 4390 | 640 | 4764.21 | 2117.41 | 0.00280422 | 2.60717 | 12.2453 | 2.31754 | 0.000695829 | 1.74402e-05 | 1.77961e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1936.23 | 0.116878 | 980.664ms | 4390 | 2560 | 16350.2 | 2162.26 | 0.0704782 | 2.64728 | 12.6804 | 2.1164 | 0.00258943 | 4.17319e-05 | 5.5168e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1156.77 | 0.14968 | 1120.09ms | 4390 | 640 | 18782.1 | 3619.25 | 0.0878456 | 4.42223 | 19.0875 | 3.08907 | 0.00292141 | 4.1287e-05 | 8.18622e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10682.9 | 0.319107 | 768.629ms | 4390 | 640 | 1000.93 | 391.902 | 0.457797 | 0.524675 | 2.25535 | 0.37221 | 0.000248078 | 4.73377e-05 | 6.76253e-06 | 1(Win) | true |
| Glaze | 3650.95 | 0.137494 | 846.994ms | 4390 | 4890 | 12156.2 | 1146.72 | 0.0528673 | 1.43517 | 5.76629 | 0.856948 | 0.000556107 | 4.44867e-05 | 5.31045e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11612.1 | 0.118 | 765.336ms | 4390 | 4890 | 885.073 | 360.54 | 0.239291 | 0.485523 | 2.14055 | 0.346014 | 0.000229188 | 2.40368e-05 | 3.12106e-06 | 1(Win) | true |
| Glaze | 3992.43 | 0.308018 | 832.668ms | 4390 | 1280 | 13354.2 | 1048.64 | 0.220936 | 1.31711 | 5.37927 | 0.771071 | 0.000529969 | 4.28887e-05 | 1.74402e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3229.36 | 0.132231 | 1020.13ms | 9378 | 640 | 8582.85 | 2769.45 | 0.0594447 | 1.58976 | 7.42845 | 1.19919 | 0.00163898 | 1.64947e-05 | 9.9968e-07 | 1(Win) | true |
| Jsonifier | 2673.11 | 0.256582 | 1070.86ms | 9378 | 320 | 23582.3 | 3345.75 | 0.152571 | 1.91317 | 8.18469 | 1.72116 | 0.00333427 | 1.79942e-05 | 2.66581e-06 | 2(Loss) | true |
| Glaze | 2355.2 | 0.0974126 | 1117.95ms | 9378 | 2560 | 35029.6 | 3797.37 | 0.179715 | 2.16963 | 9.73363 | 1.90499 | 0.0027829 | 4.22781e-05 | 2.08683e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2159.78 | 0.0586457 | 1152.51ms | 9378 | 4890 | 28839 | 4140.95 | 0.0927086 | 2.36138 | 10.2046 | 1.62018 | 0.00150886 | 3.55878e-05 | 1.06851e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3571.29 | 0.0930285 | 1017.37ms | 9378 | 2560 | 13894.5 | 2504.3 | 0.0499828 | 1.42503 | 6.85434 | 1.06654 | 0.00151539 | 1.81192e-05 | 2.74912e-06 | 1(Win) | true |
| Jsonifier | 2876.13 | 0.113191 | 1073.9ms | 9378 | 2560 | 31715.1 | 3109.59 | 0.194889 | 1.77422 | 7.61058 | 1.58851 | 0.00337738 | 2.77828e-05 | 8.03909e-06 | 2(Loss) | true |
| Glaze | 2588.4 | 0.0729054 | 1102.7ms | 9378 | 2560 | 16244.9 | 3455.25 | 0.0996582 | 1.97564 | 9.00811 | 1.74579 | 0.00300387 | 1.39122e-05 | 2.29093e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2315.26 | 0.0817197 | 1151.05ms | 9378 | 2560 | 25510.2 | 3862.88 | 0.111999 | 2.19016 | 9.51823 | 1.46758 | 0.00143862 | 2.37007e-05 | 5.49824e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15690.1 | 0.145266 | 802.79ms | 11521 | 4890 | 5060.16 | 700.268 | 0.146447 | 0.340711 | 1.50959 | 0.277146 | 0.000113157 | 1.20701e-05 | 2.14776e-06 | 1(Win) | true |
| Glaze | 4790.52 | 0.199114 | 966.211ms | 11521 | 640 | 13347.4 | 2293.55 | 0.0639293 | 1.07938 | 3.86781 | 0.687441 | 0.00118018 | 1.57321e-05 | 2.57682e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17601.7 | 0.0843856 | 793.644ms | 11521 | 4890 | 1356.81 | 624.219 | 0.0217296 | 0.305945 | 1.46012 | 0.265255 | 8.74193e-05 | 7.8278e-06 | 1.54426e-06 | 1(Win) | true |
| Glaze | 5361.55 | 0.0719497 | 937.614ms | 11521 | 4890 | 10630.8 | 2049.27 | 0.0645148 | 0.963302 | 3.62026 | 0.633279 | 0.00115823 | 1.84424e-05 | 4.70378e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2482.47 | 0.124253 | 913.85ms | 4669 | 4890 | 24288.7 | 1793.66 | 0.0443038 | 2.08378 | 8.21889 | 1.63654 | 0.00130894 | 3.54336e-05 | 5.47491e-06 | 1(Win) | true |
| Glaze | 2067.26 | 0.159207 | 950.635ms | 4669 | 4890 | 57503.1 | 2153.92 | 0.259548 | 2.49571 | 10.1178 | 1.80253 | 0.00080017 | 4.55951e-05 | 1.36216e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1861.84 | 0.195173 | 974.047ms | 4669 | 4890 | 106540 | 2391.56 | 0.269996 | 2.79889 | 11.1099 | 1.90383 | 0.00125616 | 4.37993e-05 | 1.68627e-05 | 3(Loss) | true |
| simdjson (ondemand) | 658.551 | 0.0737404 | 1414.93ms | 4669 | 4890 | 121559 | 6761.37 | 0.0465105 | 7.72036 | 28.9383 | 4.58492 | 0.00357069 | 7.88388e-05 | 2.89513e-05 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2707.94 | 0.138982 | 903.104ms | 4669 | 2560 | 13369.8 | 1644.31 | 0.04101 | 1.91207 | 7.75027 | 1.52195 | 0.00129762 | 1.64817e-05 | 2.17525e-06 | 1(Win) | true |
| Glaze | 2322.6 | 0.119563 | 935.291ms | 4669 | 160 | 840.651 | 1917.12 | 0.0495288 | 2.22414 | 9.35875 | 1.63097 | 0.000797815 | 3.74813e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1941.65 | 0.385347 | 969.76ms | 4669 | 1280 | 99957.9 | 2293.25 | 0.0179843 | 2.65195 | 10.7278 | 1.80852 | 0.00116041 | 2.39278e-05 | 2.00792e-06 | 3(Loss) | true |
| simdjson (ondemand) | 687.901 | 0.0889487 | 1392.33ms | 4669 | 4890 | 162100 | 6472.89 | 0.143828 | 7.39958 | 28.1793 | 4.41208 | 0.00306455 | 5.75523e-05 | 2.4002e-05 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12272.8 | 0.211162 | 768.739ms | 4669 | 4890 | 2870.1 | 362.81 | 0.105099 | 0.458776 | 1.4093 | 0.362176 | 0.00028798 | 1.85271e-05 | 2.93455e-06 | 1(Win) | true |
| Glaze | 2255.08 | 0.222796 | 935.539ms | 4669 | 2560 | 49542.5 | 1974.52 | 0.0159625 | 2.28854 | 3.69265 | 0.510388 | 0.000224971 | 3.12902e-05 | 2.34258e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14417 | 0.210087 | 762.123ms | 4669 | 4890 | 2058.76 | 308.852 | 0.121049 | 0.398399 | 1.29964 | 0.336689 | 0.000214573 | 1.53298e-05 | 1.40158e-06 | 1(Win) | true |
| Glaze | 2602.08 | 0.216757 | 906.078ms | 4669 | 2560 | 35220.1 | 1711.21 | 0.272501 | 1.9904 | 3.1949 | 0.397516 | 0.000220202 | 1.89916e-05 | 6.69308e-07 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2810.18 | 0.181308 | 1006.89ms | 7932 | 4890 | 116477 | 2691.83 | 0.0913169 | 1.82509 | 7.31493 | 1.18079 | 0.000892737 | 2.58331e-05 | 7.14148e-06 | 1(Win) | true |
| Glaze | 2333.33 | 0.102422 | 1060.72ms | 7932 | 40 | 441.023 | 3241.95 | 0.304953 | 2.19434 | 8.94995 | 1.66831 | 0.00233863 | 3.46697e-05 | 0 | 2(Loss) | true |
| Jsonifier | 2081.94 | 0.189275 | 1100.08ms | 7932 | 4890 | 231273 | 3633.41 | 0.122724 | 2.45567 | 7.95386 | 1.78366 | 0.00141922 | 3.10925e-05 | 1.11118e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1096.61 | 0.0829434 | 1428.94ms | 7932 | 4890 | 160079 | 6898.12 | 0.0523998 | 4.63714 | 17.5501 | 2.72227 | 0.00211465 | 4.45505e-05 | 1.68869e-05 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2974.61 | 0.108954 | 998.622ms | 7932 | 30 | 230.309 | 2543.03 | 0.148337 | 1.72675 | 7.09002 | 1.12468 | 0.000895108 | 1.68095e-05 | 0 | 1(Win) | true |
| Glaze | 2577.45 | 0.107111 | 1036.2ms | 7932 | 4890 | 48324.1 | 2934.89 | 0.0108405 | 1.98879 | 8.50277 | 1.56732 | 0.00148641 | 2.11151e-05 | 3.73832e-06 | 2(Loss) | true |
| Jsonifier | 2169.79 | 0.196254 | 1092.58ms | 7932 | 4890 | 228917 | 3486.3 | 0.182072 | 2.35977 | 7.72882 | 1.72756 | 0.00140973 | 3.46246e-05 | 1.41283e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1142.35 | 0.0676413 | 1405.54ms | 7932 | 4890 | 98107.1 | 6621.92 | 0.0623501 | 4.45322 | 17.1033 | 2.62053 | 0.00191044 | 3.27167e-05 | 1.32259e-05 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14388.9 | 0.191609 | 794.967ms | 9249 | 4890 | 6746.47 | 613.011 | 0.240275 | 0.374956 | 1.22759 | 0.292897 | 0.000168105 | 1.21828e-05 | 2.58692e-06 | 1(Win) | true |
| Glaze | 2633.65 | 0.13224 | 1075.96ms | 9249 | 4890 | 95920.3 | 3349.17 | 0.209878 | 1.94397 | 3.88215 | 0.648827 | 0.000344436 | 2.79475e-05 | 9.90545e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16039.5 | 0.217609 | 788.064ms | 9249 | 4890 | 7002.73 | 549.925 | 0.125588 | 0.338717 | 1.16791 | 0.2783 | 0.000109071 | 2.85666e-05 | 1.1011e-05 | 1(Win) | true |
| Glaze | 2721.24 | 0.110873 | 1062.11ms | 9249 | 4890 | 63156.2 | 3241.37 | 0.132167 | 1.88607 | 3.62255 | 0.590443 | 0.000372914 | 9.86123e-06 | 2.14471e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 808.092 | 0.0829041 | 1289.62ms | 4604 | 4890 | 99222.5 | 5433.44 | 0.188108 | 6.32467 | 24.6127 | 5.38814 | 0.00596876 | 0.000145601 | 7.41331e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 703.729 | 0.227042 | 1364.7ms | 4604 | 640 | 128425 | 6239.22 | 0.0618935 | 7.22855 | 28.3278 | 5.79453 | 0.00715377 | 5.12462e-05 | 8.14509e-06 | 2(Loss) | true |
| Glaze | 627.787 | 0.108215 | 1440.13ms | 4604 | 1280 | 73320.7 | 6993.96 | 0.0677718 | 8.09646 | 33.8239 | 6.88532 | 0.00483157 | 8.22994e-05 | 3.12228e-05 | 3(Loss) | true |
| simdjson (ondemand) | 501.747 | 0.0872611 | 1619.81ms | 4604 | 2560 | 149273 | 8750.85 | 0.000785632 | 10.1162 | 40.6659 | 7.28693 | 0.00676569 | 0.00016952 | 7.34755e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 994.052 | 0.159445 | 1277.23ms | 4604 | 1280 | 63486.9 | 4416.99 | 0.16692 | 5.13601 | 20.0226 | 4.34079 | 0.0053632 | 6.07488e-05 | 2.37565e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 837.106 | 0.0968255 | 1356.86ms | 4604 | 4890 | 126124 | 5245.11 | 0.0233689 | 6.12703 | 24.0706 | 4.82124 | 0.00605146 | 0.000141159 | 7.82195e-05 | 2(Loss) | true |
| Glaze | 733.053 | 0.0567632 | 1430.98ms | 4604 | 4890 | 56525.3 | 5989.63 | 0.166463 | 6.94231 | 29.3108 | 5.84948 | 0.00464778 | 7.71535e-05 | 3.52676e-05 | 3(Loss) | true |
| simdjson (ondemand) | 557.429 | 0.078399 | 1628.85ms | 4604 | 2560 | 97623 | 7876.72 | 0.164341 | 9.10978 | 37.4058 | 6.53685 | 0.00474019 | 8.49295e-05 | 2.64715e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1338.2 | 0.105932 | 1066.26ms | 4604 | 2560 | 30926.1 | 3281.07 | 0.12643 | 3.8248 | 9.44309 | 0.661165 | 0.000574314 | 5.05674e-05 | 2.34171e-05 | 1(Win) | true |
| Glaze | 791.178 | 0.0729744 | 1296.01ms | 4604 | 4890 | 80199.6 | 5549.59 | 0.13483 | 6.4448 | 12.9939 | 1.08775 | 0.00154143 | 8.77249e-05 | 3.75774e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1395.62 | 0.109129 | 1051.88ms | 4604 | 2560 | 30175.4 | 3146.06 | 0.231413 | 3.66174 | 9.31951 | 0.631408 | 0.000595016 | 5.45551e-05 | 2.57928e-05 | 1(Win) | true |
| Glaze | 827.061 | 0.0909481 | 1267.06ms | 4604 | 2560 | 59679.3 | 5308.82 | 0.0129592 | 6.16577 | 12.4472 | 0.970679 | 0.000826048 | 7.09302e-05 | 2.66412e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2470.63 | 0.13738 | 1447.33ms | 18245 | 1280 | 119820 | 7042.66 | 0.022058 | 2.05732 | 8.13944 | 1.5083 | 0.00176071 | 8.47835e-06 | 1.2846e-06 | 1(Win) | true |
| Jsonifier | 2163.41 | 0.0963797 | 1549.25ms | 18245 | 4890 | 293826 | 8042.76 | 0.265116 | 2.34554 | 8.96706 | 2.05733 | 0.00224655 | 2.17557e-05 | 8.75383e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1865.76 | 0.0716648 | 1677.85ms | 18245 | 2560 | 114348 | 9325.84 | 0.0498031 | 2.72033 | 11.1304 | 1.86665 | 0.00162746 | 2.78758e-05 | 9.91282e-06 | 3(Loss) | true |
| Glaze | 1781.91 | 0.143784 | 1726.36ms | 18245 | 160 | 31539.8 | 9764.7 | 0.00204824 | 2.84982 | 11.8155 | 2.3863 | 0.00418368 | 2.29515e-05 | 1.19896e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2883.38 | 0.170993 | 1443.51ms | 18245 | 1280 | 136285 | 6034.51 | 0.0954013 | 1.76855 | 7.06879 | 1.26385 | 0.00147703 | 2.23948e-05 | 1.02768e-05 | 1(Win) | true |
| Jsonifier | 2479.66 | 0.110344 | 1537.47ms | 18245 | 4890 | 293163 | 7016.99 | 0.230058 | 2.0506 | 7.89515 | 1.81255 | 0.00208697 | 1.99175e-05 | 7.95803e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2076.92 | 0.0762312 | 1680.94ms | 18245 | 2560 | 104413 | 8377.69 | 0.00833618 | 2.44468 | 10.2774 | 1.67091 | 0.00127629 | 1.75562e-05 | 5.54518e-06 | 3(Loss) | true |
| Glaze | 1966.91 | 0.0658063 | 1718.99ms | 18245 | 2560 | 86754.6 | 8846.24 | 0.320206 | 2.56969 | 10.7213 | 2.13483 | 0.00363102 | 1.59076e-05 | 4.41045e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5290.38 | 0.088371 | 1185.91ms | 24579 | 4890 | 74969.4 | 4430.76 | 0.120225 | 0.964267 | 2.97258 | 0.388625 | 0.000170029 | 1.38196e-05 | 4.32644e-06 | 1(Win) | true |
| Glaze | 3649.68 | 0.120787 | 1388.37ms | 24579 | 2560 | 154062 | 6422.57 | 0.0564037 | 1.39774 | 3.73734 | 0.480044 | 0.000341866 | 9.96468e-06 | 2.32032e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5353.32 | 0.0777005 | 1181.54ms | 24579 | 4890 | 56602.9 | 4378.66 | 0.124875 | 0.952996 | 2.95264 | 0.383986 | 0.000183399 | 8.37831e-06 | 1.70561e-06 | 1(Win) | true |
| Glaze | 3994.89 | 0.0896262 | 1326.41ms | 24579 | 4890 | 135238 | 5867.58 | 0.243495 | 1.27456 | 3.59514 | 0.447659 | 0.000231115 | 7.70438e-06 | 8.65287e-07 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 880.365 | 0.0623543 | 1237.78ms | 4604 | 4890 | 47291.9 | 4987.38 | 0.152638 | 5.76919 | 22.9963 | 4.99805 | 0.00779637 | 5.79206e-05 | 1.63457e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 755.913 | 0.084417 | 1325.18ms | 4604 | 2560 | 61549.9 | 5808.49 | 0.215738 | 6.72941 | 27.4233 | 5.62272 | 0.00726016 | 6.81303e-05 | 2.36717e-05 | 2(Loss) | true |
| Glaze | 640.685 | 0.0491986 | 1426.96ms | 4604 | 4890 | 55590 | 6853.16 | 0.0659142 | 7.93629 | 32.7744 | 6.65574 | 0.00840032 | 6.80035e-05 | 1.93217e-05 | 3(Loss) | true |
| simdjson (ondemand) | 511.091 | 0.0576489 | 1602.15ms | 4604 | 4890 | 119940 | 8590.87 | 0.0392217 | 9.92318 | 39.4932 | 7.03316 | 0.00788636 | 7.85305e-05 | 2.55402e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1105.32 | 0.238071 | 1231.19ms | 4604 | 320 | 28619 | 3972.33 | 0.0410034 | 4.6192 | 18.7609 | 4.03019 | 0.00626697 | 3.12228e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 903.706 | 0.125449 | 1323ms | 4604 | 1280 | 47551.2 | 4858.57 | 0.180251 | 5.64845 | 23.1844 | 4.65465 | 0.00646669 | 3.56348e-05 | 1.69689e-06 | 2(Loss) | true |
| Glaze | 745.772 | 0.151782 | 1421.81ms | 4604 | 160 | 12776.7 | 5887.48 | 0.0408873 | 6.82441 | 28.6464 | 5.70873 | 0.00597985 | 7.33058e-05 | 1.90052e-05 | 3(Loss) | true |
| simdjson (ondemand) | 550.077 | 0.111657 | 1639.05ms | 4604 | 1280 | 101672 | 7982 | 0.0187077 | 9.23389 | 37.2391 | 6.50429 | 0.00938094 | 6.27851e-05 | 1.98537e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1491.12 | 0.0912954 | 1031.93ms | 4604 | 4890 | 35338.8 | 2944.57 | 0.0357447 | 3.4376 | 9.43788 | 0.661382 | 0.00066169 | 3.4557e-05 | 6.17406e-06 | 1(Win) | true |
| Glaze | 818.039 | 0.0586803 | 1276.52ms | 4604 | 4890 | 48508.3 | 5367.37 | 0.0926676 | 6.22561 | 12.939 | 1.08384 | 0.00185306 | 4.8815e-05 | 7.95076e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1569.87 | 0.149652 | 1014.03ms | 4604 | 30 | 525.568 | 2796.87 | 0.0620125 | 3.26971 | 9.31429 | 0.631625 | 0.000521286 | 4.34405e-05 | 1.44802e-05 | 1(Win) | true |
| Glaze | 832.108 | 0.0839521 | 1265.35ms | 4604 | 2560 | 50235.9 | 5276.62 | 0.101909 | 6.11899 | 12.437 | 0.970896 | 0.00103154 | 8.72204e-05 | 2.60473e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2655.39 | 0.0877103 | 1398.44ms | 18245 | 4890 | 161526 | 6552.63 | 0.0102441 | 1.92671 | 7.91954 | 1.46676 | 0.00176951 | 7.37407e-05 | 4.43296e-05 | 1(Win) | true |
| Jsonifier | 2255.89 | 0.0898092 | 1511.48ms | 18245 | 4890 | 234639 | 7713.03 | 0.201448 | 2.25223 | 8.65854 | 2.01233 | 0.00232965 | 1.92338e-05 | 5.68271e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1878.5 | 0.122043 | 1670.67ms | 18245 | 1280 | 163570 | 9262.6 | 0.00719407 | 2.70271 | 10.8384 | 1.8036 | 0.00215376 | 2.4022e-05 | 1.20752e-05 | 3(Loss) | true |
| Glaze | 1822.85 | 0.0670493 | 1693.75ms | 18245 | 2560 | 104860 | 9545.35 | 0.0355994 | 2.7838 | 11.5172 | 2.32007 | 0.00371148 | 2.6527e-05 | 1.11118e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3130.61 | 0.059363 | 1402.24ms | 18245 | 4890 | 53231.7 | 5557.95 | 0.0290288 | 1.62747 | 6.84988 | 1.22247 | 0.00141295 | 1.06257e-05 | 2.62279e-06 | 1(Win) | true |
| Jsonifier | 2586.26 | 0.210593 | 1506.09ms | 18245 | 1280 | 256947 | 6727.79 | 0.175872 | 1.96705 | 7.58898 | 1.7681 | 0.00204559 | 2.60345e-05 | 7.40785e-06 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2024.84 | 0.0626606 | 1689.47ms | 18245 | 2560 | 74222.8 | 8593.19 | 0.0359258 | 2.50947 | 10.4897 | 2.08556 | 0.00351479 | 1.07906e-05 | 1.39165e-06 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2023.24 | 0.0582906 | 1700.96ms | 18245 | 4890 | 122885 | 8599.96 | 0.147087 | 2.5115 | 10.3714 | 1.69235 | 0.0017471 | 2.85592e-05 | 1.31027e-05 | 3(Tie) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5151.44 | 0.0801794 | 1197.16ms | 24579 | 4890 | 65088.8 | 4550.26 | 0.0893794 | 0.989479 | 2.97263 | 0.388626 | 0.000154179 | 1.05831e-05 | 2.93698e-06 | 1(Win) | true |
| Glaze | 3543.41 | 0.0782501 | 1406.17ms | 24579 | 4890 | 131028 | 6615.2 | 0.126761 | 1.43473 | 3.74088 | 0.481387 | 0.000380701 | 1.25799e-05 | 3.69411e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5300.22 | 0.083435 | 1182.99ms | 24579 | 4890 | 66580.4 | 4422.53 | 0.267308 | 0.964288 | 2.95268 | 0.383987 | 0.000125625 | 2.35208e-05 | 1.0658e-05 | 1(Win) | true |
| Glaze | 3989.47 | 0.121402 | 1331.74ms | 24579 | 2560 | 130254 | 5875.56 | 0.0203463 | 1.27911 | 3.59408 | 0.447374 | 0.00029716 | 9.63093e-06 | 2.95603e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1714.1 | 0.110864 | 1019.61ms | 5094 | 2560 | 25273.4 | 2834.15 | 0.0728854 | 2.99133 | 13.4653 | 2.44739 | 0.000726805 | 6.17301e-05 | 2.4692e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1539.36 | 0.109404 | 1051.76ms | 5094 | 2560 | 30517.1 | 3155.86 | 0.0716035 | 3.32953 | 14.5024 | 2.60954 | 0.00171303 | 5.2068e-05 | 2.25449e-05 | 2(Loss) | true |
| Glaze | 1291.32 | 0.0848576 | 1111.39ms | 5094 | 2560 | 26090 | 3762.07 | 0.258434 | 3.95863 | 16.5124 | 3.18198 | 0.00335413 | 5.88928e-05 | 1.65636e-05 | 3(Loss) | true |
| simdjson (ondemand) | 839.881 | 0.0620262 | 1315.85ms | 5094 | 4890 | 62942.2 | 5784.17 | 0.0934918 | 6.06232 | 22.4329 | 3.82293 | 0.00645974 | 8.07317e-05 | 2.85833e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2168.37 | 0.118351 | 1019.59ms | 5094 | 2560 | 17998.6 | 2240.41 | 0.20417 | 2.37442 | 10.9613 | 1.87809 | 0.000561476 | 3.48909e-05 | 6.05798e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1881.53 | 0.0701219 | 1052.75ms | 5094 | 4890 | 16029.2 | 2581.95 | 0.0100398 | 2.73105 | 12.2419 | 2.08697 | 0.00115 | 4.72909e-05 | 1.24851e-05 | 2(Loss) | true |
| Glaze | 1692.2 | 0.0685137 | 1080.3ms | 5094 | 4890 | 18918.2 | 2870.84 | 0.0415751 | 3.03108 | 13.1688 | 2.44366 | 0.00351566 | 3.6251e-05 | 5.62031e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1005.1 | 0.143123 | 1279.05ms | 5094 | 1280 | 61252.9 | 4833.36 | 0.027907 | 5.07182 | 19.511 | 3.16804 | 0.0042682 | 6.74814e-05 | 2.20848e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13185.9 | 0.303912 | 768.051ms | 5094 | 40 | 50.1481 | 368.425 | 0.0158357 | 0.425697 | 1.787 | 0.301139 | 0.000196309 | 6.38005e-05 | 3.43541e-05 | 1(Win) | true |
| Glaze | 3468.59 | 0.298245 | 877.726ms | 5094 | 1280 | 22334.1 | 1400.57 | 0.300921 | 1.49877 | 5.91578 | 0.911465 | 0.000210266 | 5.78192e-05 | 1.74838e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14638.1 | 0.233442 | 762.669ms | 5094 | 160 | 96.0346 | 331.875 | 0.13541 | 0.387765 | 1.67825 | 0.2766 | 0.000196309 | 9.81547e-06 | 0 | 1(Win) | true |
| Glaze | 3853.01 | 0.167239 | 860.959ms | 5094 | 4890 | 21742.2 | 1260.84 | 0.179063 | 1.3546 | 5.4413 | 0.804084 | 0.000237257 | 3.99845e-05 | 7.46698e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2332.98 | 0.0634362 | 1069.18ms | 8051 | 4890 | 21313.9 | 3291.09 | 0.0559098 | 2.19438 | 9.85244 | 1.69892 | 0.000866155 | 2.72293e-05 | 5.9437e-06 | 1(Win) | true |
| Jsonifier | 1688.8 | 0.105799 | 1193.13ms | 8051 | 4890 | 113140 | 4546.45 | 0.128647 | 3.01905 | 11.5931 | 2.3489 | 0.00381342 | 2.76611e-05 | 7.06132e-06 | 2(Loss) | true |
| Glaze | 1651.63 | 0.179317 | 1198.45ms | 8051 | 640 | 44473 | 4648.76 | 0.0874132 | 3.08379 | 13.2242 | 2.57732 | 0.00279352 | 2.19305e-05 | 1.5526e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1291.92 | 0.123368 | 1332.9ms | 8051 | 1280 | 68808.5 | 5943.1 | 0.034874 | 3.93873 | 14.6692 | 2.44082 | 0.00397641 | 4.92951e-05 | 2.0669e-05 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2798.4 | 0.0816591 | 1072.92ms | 8051 | 4890 | 24546.9 | 2743.72 | 0.102039 | 1.83345 | 8.43709 | 1.37113 | 0.00048111 | 2.16158e-05 | 2.94645e-06 | 1(Win) | true |
| Glaze | 2063.92 | 0.103225 | 1168.32ms | 8051 | 2560 | 37750.6 | 3720.12 | 0.0701665 | 2.48827 | 11.1189 | 2.11253 | 0.00289987 | 2.34831e-05 | 3.20224e-06 | 2(Loss) | true |
| Jsonifier | 1937.74 | 0.10597 | 1197.21ms | 8051 | 4890 | 86214.8 | 3962.36 | 0.0380731 | 2.63537 | 10.0143 | 1.98969 | 0.00373948 | 3.62972e-05 | 1.46561e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1511.64 | 0.0599279 | 1306.33ms | 8051 | 4890 | 45307.2 | 5079.26 | 0.0879732 | 3.37284 | 13.095 | 2.08247 | 0.00282844 | 3.61956e-05 | 9.90617e-06 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14819.3 | 0.210309 | 791.63ms | 9255 | 2560 | 4016.57 | 595.594 | 0.380793 | 0.366103 | 1.46321 | 0.279525 | 0.000354918 | 8.39918e-06 | 1.43504e-06 | 1(Win) | true |
| Glaze | 3987.99 | 0.0851483 | 960.087ms | 9255 | 4890 | 17366.3 | 2213.21 | 0.00893631 | 1.29209 | 4.949 | 0.854889 | 0.000382063 | 4.75728e-05 | 2.05714e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16908.6 | 0.183816 | 783.604ms | 9255 | 4890 | 4502.06 | 521.998 | 0.078829 | 0.323272 | 1.39751 | 0.264938 | 0.00027788 | 8.66165e-06 | 2.29799e-06 | 1(Win) | true |
| Glaze | 4610.3 | 0.177482 | 925.009ms | 9255 | 2560 | 29555.8 | 1914.47 | 0.0373048 | 1.11827 | 4.61632 | 0.778498 | 0.000384632 | 1.6925e-05 | 2.95448e-06 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5637.74 | 0.169816 | 778.136ms | 2889 | 40 | 27.5487 | 488.7 | 0.00682128 | 0.968562 | 3.75389 | 0.514365 | 0.000354794 | 1.7307e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 5577.54 | 0.298466 | 776.303ms | 2889 | 40 | 86.9481 | 493.975 | 0.30777 | 0.980036 | 3.78262 | 0.433714 | 0.000536518 | 3.46141e-05 | 0 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5564.53 | 0.244981 | 779.453ms | 2889 | 4890 | 7194.71 | 495.13 | 0.0644553 | 0.984639 | 3.75389 | 0.514365 | 0.000355272 | 5.18857e-05 | 1.50065e-05 | 2(Tie) | true |
| Glaze | 3109.93 | 0.103415 | 817.27ms | 2889 | 2560 | 2148.83 | 885.925 | 0.0903517 | 1.69963 | 6.80547 | 1.23364 | 0.000357633 | 2.78535e-05 | 3.51549e-06 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5835.36 | 0.312274 | 772.053ms | 2889 | 640 | 1391.27 | 472.15 | 0.130558 | 0.95724 | 3.67809 | 0.496366 | 0.000432676 | 1.46028e-05 | 5.40845e-07 | 1(Win) | true |
| Jsonifier (two-stage) | 5783.09 | 0.170482 | 772.877ms | 2889 | 4890 | 3225.84 | 476.417 | 0.202396 | 0.963329 | 3.67809 | 0.496366 | 0.000391018 | 5.89642e-05 | 2.52704e-05 | 2(Loss) | true |
| simdjson (ondemand) | 5715.84 | 0.289054 | 770.6ms | 2889 | 2560 | 4969.73 | 482.023 | 0.0607348 | 0.969236 | 3.70578 | 0.416062 | 0.000711751 | 3.47493e-05 | 9.59999e-06 | 3(Loss) | true |
| Glaze | 3163.94 | 0.133024 | 813.626ms | 2889 | 4890 | 6561.61 | 870.802 | 0.242654 | 1.68316 | 6.72897 | 1.21634 | 0.00039654 | 2.02446e-05 | 4.60105e-06 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6824.22 | 0.35611 | 785.531ms | 3808 | 160 | 574.615 | 532.163 | 0.0822794 | 0.814008 | 3.18592 | 0.3448 | 0.000426733 | 2.29779e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6689.21 | 0.298772 | 781.441ms | 3808 | 4890 | 12865.7 | 542.903 | 0.18853 | 0.826106 | 3.28624 | 0.405987 | 0.000269049 | 3.46381e-05 | 1.29423e-05 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 6635.58 | 0.348913 | 781.919ms | 3808 | 320 | 1166.87 | 547.291 | 0.127494 | 0.819626 | 3.28625 | 0.405992 | 0.000276556 | 3.77495e-05 | 3.28256e-06 | 2(Tie) | true |
| Glaze | 3351.39 | 0.124461 | 839.555ms | 3808 | 4890 | 8894.47 | 1083.61 | 0.362657 | 1.57557 | 6.48057 | 1.20746 | 0.000524834 | 3.70547e-05 | 1.09016e-05 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6962.85 | 0.281947 | 776.512ms | 3808 | 30 | 64.8747 | 521.567 | 0.095957 | 0.796446 | 3.22873 | 0.392332 | 0.000262605 | 7.87815e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6853.66 | 0.0940046 | 781.884ms | 3808 | 4890 | 1213.27 | 529.876 | 0.510049 | 0.799669 | 3.12763 | 0.331408 | 0.000595721 | 4.01694e-05 | 1.87959e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 6741.2 | 0.24405 | 774.694ms | 3808 | 2560 | 4425.03 | 538.716 | 0.256463 | 0.815859 | 3.22886 | 0.392359 | 0.000374315 | 4.0314e-05 | 1.50793e-05 | 3(Loss) | true |
| Glaze | 3407.13 | 0.318869 | 834.074ms | 3808 | 640 | 7393.02 | 1065.88 | 0.00806194 | 1.56427 | 6.42227 | 1.19433 | 0.000731601 | 5.74449e-06 | 0 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2446.81 | 0.238837 | 842.547ms | 2889 | 40 | 289.307 | 1126.03 | 0.121962 | 2.17919 | 6.76186 | 1.14573 | 0.00139322 | 0.000242298 | 0 | 1(Win) | true |
| Glaze | 2431.88 | 0.148482 | 839.861ms | 2889 | 4890 | 13837.8 | 1132.94 | 0.377295 | 2.15583 | 8.73659 | 1.49533 | 0.000357679 | 6.54057e-05 | 1.98199e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2174.55 | 0.260851 | 855.798ms | 2889 | 2560 | 27962.8 | 1267.01 | 0.174156 | 2.41682 | 8.1163 | 1.27137 | 0.00069823 | 4.1645e-05 | 5.13802e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1028.61 | 0.250077 | 995.838ms | 2889 | 30 | 1346.05 | 2678.53 | 0.0298582 | 4.98967 | 16.9013 | 2.86743 | 0.000403831 | 0.000196146 | 0.00011538 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2701.41 | 0.239125 | 849.059ms | 2889 | 30 | 178.438 | 1019.9 | 0.0587947 | 1.94828 | 6.15265 | 0.991 | 0.00138456 | 4.61521e-05 | 0 | 1(Win) | true |
| Glaze | 2651.13 | 0.247294 | 842.123ms | 2889 | 1280 | 8454.16 | 1039.24 | 0.0586021 | 1.98455 | 8.16476 | 1.34995 | 0.000491087 | 8.81577e-05 | 4.32676e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2380.59 | 0.260251 | 858.769ms | 2889 | 4890 | 44362.8 | 1157.34 | 0.299367 | 2.1996 | 7.54863 | 1.1253 | 0.000700421 | 6.98652e-05 | 1.86166e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1048.82 | 0.0898324 | 1010.3ms | 2889 | 4890 | 27231.4 | 2626.92 | 0.0297321 | 4.88957 | 16.4929 | 2.76359 | 0.000804264 | 0.000101789 | 4.78509e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8626.23 | 0.115102 | 758.561ms | 2963 | 40 | 5.68654 | 327.575 | 0.190433 | 0.659627 | 1.47992 | 0.23996 | 0.000337496 | 0 | 0 | 1(Win) | true |
| Glaze | 4355.64 | 0.301882 | 793.867ms | 2963 | 2560 | 9819.12 | 648.754 | 0.0840449 | 1.24651 | 3.24232 | 0.491394 | 0.000344747 | 4.65375e-05 | 8.43739e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10109 | 0.242658 | 760.561ms | 2963 | 4890 | 2249.79 | 279.526 | 1.06363 | 0.575138 | 1.30948 | 0.201823 | 0.000338117 | 3.24382e-05 | 4.14105e-06 | 1(Win) | true |
| Glaze | 4432.9 | 0.469401 | 798.35ms | 2963 | 640 | 5730.02 | 637.447 | 0.537338 | 1.2065 | 2.73068 | 0.379345 | 0.000337496 | 4.32416e-05 | 2.63669e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2646.51 | 0.240618 | 870.741ms | 3808 | 4890 | 53310.4 | 1372.22 | 0.0522222 | 1.97039 | 6.81828 | 1.02574 | 0.000586592 | 4.44656e-05 | 1.18682e-05 | 1(Win) | true |
| Glaze | 2507.93 | 0.193002 | 880.481ms | 3808 | 2560 | 19995.3 | 1448.05 | 0.12033 | 2.07289 | 8.39995 | 1.49133 | 0.000516491 | 5.27262e-05 | 2.15418e-05 | 2(Loss) | true |
| Jsonifier | 1853.81 | 0.264581 | 934.719ms | 3808 | 2560 | 68773.9 | 1958.99 | 0.231903 | 2.78163 | 7.09743 | 1.35163 | 0.000554035 | 8.86292e-05 | 4.35965e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1309.62 | 0.0789125 | 1015.3ms | 3808 | 4890 | 23415.4 | 2773 | 0.102798 | 3.91608 | 13.1767 | 2.19984 | 0.000555874 | 5.0534e-05 | 1.05257e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3010.13 | 0.229999 | 862.112ms | 3808 | 4890 | 37651.6 | 1206.46 | 0.0876698 | 1.73902 | 6.17358 | 0.871324 | 0.000531493 | 3.68399e-05 | 8.6461e-06 | 1(Win) | true |
| Glaze | 2726.78 | 0.214297 | 877.402ms | 3808 | 2560 | 20852.8 | 1331.82 | 0.182737 | 1.91116 | 7.88524 | 1.36371 | 0.00043494 | 2.0516e-05 | 2.66708e-06 | 2(Loss) | true |
| Jsonifier | 1999.5 | 0.212311 | 925.832ms | 3808 | 4890 | 72711.9 | 1816.25 | 0.050386 | 2.58562 | 6.63944 | 1.23477 | 0.000532191 | 4.26398e-05 | 6.06838e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1355.34 | 0.172011 | 1012.75ms | 3808 | 1280 | 27190.9 | 2679.48 | 0.0120141 | 3.78539 | 12.8288 | 2.1124 | 0.000544085 | 4.12372e-05 | 8.00125e-06 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9502.63 | 0.23543 | 780.114ms | 4300 | 160 | 165.155 | 431.544 | 0.449533 | 0.582314 | 1.38465 | 0.23907 | 0.000238372 | 2.32558e-05 | 1.16279e-05 | 1(Win) | true |
| Glaze | 3157.35 | 0.26905 | 866.765ms | 4300 | 2560 | 31260.7 | 1298.81 | 0.43209 | 1.65227 | 3.75209 | 0.629768 | 0.000349291 | 2.73438e-05 | 2.72529e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10727.6 | 0.102615 | 772.12ms | 4300 | 30 | 4.61609 | 382.267 | 0.0348675 | 0.522605 | 1.2686 | 0.212326 | 0.000232558 | 0 | 0 | 1(Win) | true |
| Glaze | 3793.69 | 0.275788 | 842.442ms | 4300 | 2560 | 22751.2 | 1080.95 | 0.14483 | 1.38349 | 3.20907 | 0.507209 | 0.00023601 | 1.53525e-05 | 3.99709e-06 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3674.16 | 0.0850192 | 6599.41ms | 466906 | 1280 | 1.3589e+07 | 121191 | 0.213795 | 1.36026 | 6.67782 | 0.888273 | 0.00196203 | 0.00065803 | 1.87303e-05 | 1(Win) | true |
| Glaze | 2653.73 | 0.0477663 | 8946.07ms | 466906 | 2560 | 1.64448e+07 | 167793 | 0.0143564 | 1.90125 | 7.7472 | 1.47693 | 0.00239906 | 0.000656647 | 2.34698e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1763.57 | 0.087243 | 6677.84ms | 466906 | 640 | 3.10538e+07 | 252485 | 0.000912173 | 2.8474 | 12.571 | 1.66785 | 0.00397908 | 0.0820926 | 3.33445e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3720.94 | 0.051082 | 6483.56ms | 466906 | 2560 | 9.56597e+06 | 119668 | 0.0322525 | 1.34395 | 6.67669 | 0.888018 | 0.00190439 | 0.000573571 | 7.45181e-06 | 1(Win) | true |
| Glaze | 2658.8 | 0.033515 | 8946.25ms | 466906 | 2560 | 8.06507e+06 | 167473 | 0.0973602 | 1.89457 | 7.74607 | 1.47668 | 0.00239246 | 0.000619661 | 2.45608e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1736.87 | 0.0641787 | 6752.25ms | 466906 | 1280 | 3.46511e+07 | 256367 | 0.0879041 | 2.88743 | 12.571 | 1.66789 | 0.00386556 | 0.101424 | 3.28342e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4615.53 | 0.0382108 | 7804.55ms | 699405 | 2560 | 7.80598e+06 | 144513 | 0.0231011 | 1.09263 | 4.43454 | 0.719483 | 0.0029623 | 0.00108081 | 1.69005e-06 | 1(Win) | true |
| Glaze | 3527.82 | 0.0358194 | 5024.71ms | 699405 | 1280 | 5.87072e+06 | 189070 | 0.113285 | 1.43231 | 5.22155 | 1.16244 | 0.00224342 | 0.000732009 | 9.53936e-07 | 2(Loss) | true |
| simdjson (ondemand) | 2313.92 | 0.0605229 | 8321.61ms | 767297 | 1280 | 4.68898e+07 | 316238 | 0.354612 | 2.15544 | 8.67131 | 1.18243 | 0.00303423 | 0.0821672 | 4.80889e-06 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4605.97 | 0.052724 | 7793.09ms | 699405 | 1280 | 7.46177e+06 | 144813 | 0.00436913 | 1.09436 | 4.43374 | 0.719304 | 0.00289605 | 0.00107679 | 4.45691e-06 | 1(Win) | true |
| Glaze | 3538.91 | 0.105384 | 5006.53ms | 699405 | 160 | 6.31227e+06 | 188477 | 0.0196714 | 1.42781 | 5.2208 | 1.16228 | 0.00225935 | 0.000701141 | 3.47617e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2291.82 | 0.139841 | 8372.64ms | 767297 | 320 | 6.37947e+07 | 319288 | 0.498877 | 2.18072 | 8.67091 | 1.18232 | 0.00336919 | 0.0923796 | 2.16262e-06 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3536.49 | 0.199451 | 8974.7ms | 631514 | 160 | 1.84593e+07 | 170299 | 0.233286 | 1.40058 | 7.07843 | 1.22888 | 0.00445103 | 2.30597e-06 | 7.52161e-07 | 1(Win) | true |
| Glaze | 2634.85 | 0.135335 | 6040.28ms | 631514 | 80 | 7.65538e+06 | 228574 | 0.0112886 | 1.91768 | 8.44884 | 1.51664 | 0.00304633 | 2.09813e-06 | 9.50098e-07 | 2(Loss) | true |
