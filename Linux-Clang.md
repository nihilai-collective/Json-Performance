# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 23, 2026)
#### Using the following commits:
----
| Jsonifier: [b975cd7](https://github.com/nihilai-collective/jsonifier/commit/b975cd7)  
| Glaze: [628bec1](https://github.com/stephenberry/glaze/commit/628bec1)  
| Simdjson: [70f83c9](https://github.com/simdjson/simdjson/commit/70f83c9)  

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
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1954.11 | 0.0812536 | 771.99ms | 905 | 2560 | 329.703 | 441.671 | 0.178952 | 2.83161 | 13.4884 | 2.29171 | 0.0011067 | 0.000139416 | 1.89917e-05 | 1(Win) | true |
| glaze | 1614.19 | 0.0377547 | 782.4ms | 905 | 4890 | 199.269 | 534.68 | 0.0574474 | 3.37321 | 17.5779 | 2.29171 | 0.00110633 | 0.000110497 | 2.16927e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 317.381 | 0.0553483 | 999.086ms | 905 | 2560 | 5799.42 | 2719.37 | 0.137759 | 16.1506 | 45.9083 | 7.03757 | 0.0164611 | 0.000226174 | 6.69026e-05 | 3(Loss) | true |
| simdjson (ondemand) | 225.805 | 0.0485121 | 1116.11ms | 905 | 2560 | 8801.81 | 3822.22 | 0.0124871 | 22.5107 | 90.6972 | 10.8055 | 0.0281759 | 0.000142869 | 2.41713e-05 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2153 | 0.127833 | 764.957ms | 905 | 2560 | 672.261 | 400.871 | 0.193441 | 2.58625 | 12.8387 | 2.17127 | 0.0011149 | 0.000124309 | 1.76968e-05 | 1(Win) | true |
| glaze | 1702.9 | 0.217248 | 777.93ms | 905 | 2560 | 3103.64 | 506.828 | 0.00739951 | 3.20469 | 16.9215 | 2.17127 | 0.00111404 | 0.000164451 | 5.87017e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 321.183 | 0.0853916 | 995.483ms | 905 | 160 | 842.447 | 2687.18 | 0.401655 | 16.1703 | 45.2983 | 6.91713 | 0.019192 | 8.9779e-05 | 6.90608e-06 | 3(Loss) | true |
| simdjson (ondemand) | 227.619 | 0.0649915 | 1113.2ms | 905 | 1280 | 7773.28 | 3791.76 | 0.0753328 | 22.4263 | 90.0906 | 10.6851 | 0.0280059 | 0.000178695 | 5.61119e-05 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2364.15 | 0.182779 | 761.488ms | 905 | 1280 | 569.916 | 365.068 | 0.0823227 | 2.37758 | 8.81989 | 0.919338 | 0.00338743 | 4.40262e-05 | 3.45304e-06 | 1(Win) | true |
| glaze | 216.861 | 0.0268809 | 1128.8ms | 905 | 4890 | 5596.65 | 3979.85 | 0.0873769 | 23.5393 | 111.354 | 22.737 | 0.0760829 | 0.000271611 | 8.38333e-05 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5083.58 | 0.222314 | 746.654ms | 905 | 4890 | 696.623 | 169.777 | 0.00187685 | 1.23686 | 5.34917 | 0.272929 | 0.00220994 | 4.29335e-05 | 4.74528e-06 | 1(Win) | true |
| glaze | 870.003 | 0.076543 | 837.666ms | 905 | 4890 | 2819.53 | 992.037 | 0.245075 | 6.0544 | 24.4983 | 3.14917 | 0.00114339 | 8.13477e-05 | 2.37264e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1224.57 | 0.049227 | 868.505ms | 1811 | 4890 | 2357.15 | 1410.38 | 0.0317153 | 4.24444 | 19.7035 | 4.06074 | 0.000558731 | 0.000103661 | 1.62605e-05 | 1(Win) | true |
| glaze | 1015.93 | 0.0409037 | 898.082ms | 1811 | 4890 | 2364.52 | 1700.02 | 0.0032022 | 5.10705 | 26.471 | 4.27002 | 0.0006546 | 7.28337e-05 | 6.88815e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 405.688 | 0.0396424 | 1157.76ms | 1811 | 2560 | 7291.44 | 4257.22 | 0.056526 | 12.56 | 34.6886 | 6.28493 | 0.000604164 | 0.00010224 | 1.74714e-05 | 3(Loss) | true |
| simdjson (ondemand) | 262.773 | 0.0179719 | 1390.78ms | 1811 | 4890 | 6822.93 | 6572.61 | 0.00339641 | 19.3563 | 69.3401 | 9.582 | 0.00134206 | 0.000202805 | 7.76893e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1331.1 | 0.094081 | 857.615ms | 1811 | 2560 | 3814.69 | 1297.5 | 0.0203859 | 3.91242 | 18.6256 | 3.80784 | 0.000903765 | 0.000107416 | 1.704e-05 | 1(Win) | true |
| glaze | 1085.37 | 0.0659144 | 882.27ms | 1811 | 4890 | 5379.62 | 1591.26 | 0.0203876 | 4.8237 | 25.4843 | 4.04583 | 0.00210845 | 0.000153346 | 5.02496e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 416.377 | 0.0293814 | 1145.46ms | 1811 | 4890 | 7263.03 | 4147.93 | 0.0356973 | 12.2546 | 33.6013 | 6.03203 | 0.000578153 | 9.75633e-05 | 1.11791e-05 | 3(Loss) | true |
| simdjson (ondemand) | 265.496 | 0.0201761 | 1382.04ms | 1811 | 4890 | 8423.73 | 6505.19 | 0.0584724 | 19.1452 | 68.2419 | 9.32413 | 0.00156406 | 0.000100048 | 1.78414e-05 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 339.704 | 0.0200472 | 1240.91ms | 1811 | 4890 | 5079.86 | 5084.14 | 0.0716221 | 14.9999 | 62.6963 | 11.1033 | 0.0187255 | 0.000107162 | 1.8406e-05 | 1(Win) | true |
| glaze | 306.202 | 0.033159 | 1295.93ms | 1798 | 4890 | 16860.7 | 5599.92 | 0.0558766 | 16.571 | 70.6162 | 12.1902 | 0.0197493 | 0.000291621 | 0.000133072 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 830.804 | 0.0557121 | 945.436ms | 1811 | 2560 | 3433.83 | 2078.84 | 0.124247 | 6.20352 | 19.3755 | 1.25069 | 0.000569437 | 7.61406e-05 | 4.961e-06 | 1(Win) | true |
| glaze | 658.747 | 0.128243 | 1010.83ms | 1798 | 1280 | 14263.4 | 2602.98 | 0.0949929 | 7.79284 | 27.3215 | 2.17242 | 0.00125834 | 6.64801e-05 | 8.69021e-06 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3087.93 | 0.0541984 | 854.064ms | 3862 | 4890 | 2043.49 | 1192.74 | 0.00458509 | 1.69166 | 8.57147 | 1.01321 | 0.000507435 | 5.80879e-05 | 1.86919e-05 | 1(Win) | true |
| glaze | 1764.08 | 0.0316541 | 941.473ms | 3862 | 4890 | 2135.78 | 2087.83 | 0.0228383 | 2.92157 | 14.0241 | 1.72839 | 0.000262958 | 4.00314e-05 | 4.65974e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 897.601 | 0.0256779 | 1147.57ms | 3862 | 4890 | 5428.57 | 4103.26 | 0.0493387 | 5.68088 | 15.8273 | 2.06603 | 0.000280908 | 6.1265e-05 | 1.46146e-05 | 3(Loss) | true |
| simdjson (ondemand) | 585.809 | 0.0260581 | 1356.53ms | 3862 | 2560 | 6871.31 | 6287.18 | 0.0995145 | 8.69307 | 27.4467 | 3.60409 | 0.0131068 | 6.01817e-05 | 1.55765e-05 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3463.57 | 0.0757107 | 836.898ms | 3862 | 2560 | 1659.33 | 1063.38 | 0.00741977 | 1.51314 | 8.08933 | 0.903418 | 0.000518473 | 3.36815e-05 | 2.93323e-06 | 1(Win) | true |
| glaze | 1831.9 | 0.0355792 | 927.07ms | 3862 | 4890 | 2502.21 | 2010.53 | 0.0343006 | 2.81322 | 13.5334 | 1.62118 | 0.000290492 | 4.87684e-05 | 1.00078e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 928.202 | 0.0496528 | 1125.92ms | 3862 | 640 | 2484.32 | 3967.98 | 0.0283994 | 5.49993 | 15.3338 | 1.95624 | 0.000292514 | 3.43896e-05 | 1.61833e-06 | 3(Loss) | true |
| simdjson (ondemand) | 593.398 | 0.0289295 | 1350.13ms | 3862 | 2560 | 8253.81 | 6206.78 | 0.0460599 | 8.6409 | 26.9669 | 3.4956 | 0.0164394 | 0.000109237 | 5.38096e-05 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 960.689 | 0.165878 | 1108.57ms | 3862 | 30 | 1213.27 | 3833.8 | 0.130589 | 5.32134 | 25.4329 | 5.2579 | 0.00698257 | 8.63111e-05 | 0 | 1(Win) | true |
| glaze | 865.195 | 0.114648 | 1146.99ms | 3862 | 40 | 952.767 | 4256.95 | 0.0528827 | 5.90113 | 28.7644 | 5.63775 | 0.00806577 | 0.000181253 | 3.23666e-05 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5234.88 | 0.30237 | 818.864ms | 3862 | 30 | 135.771 | 703.567 | 0.0142113 | 1.02586 | 5.11626 | 0.579751 | 0.000362506 | 7.768e-05 | 0 | 1(Win) | true |
| glaze | 2339.46 | 0.314268 | 907.077ms | 3862 | 30 | 734.368 | 1574.33 | 0.0444435 | 2.21811 | 8.50311 | 0.951321 | 0.00517866 | 7.768e-05 | 1.72622e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1817.35 | 0.0782879 | 1230.11ms | 9578 | 160 | 2477.31 | 5026.15 | 0.0933493 | 2.80501 | 14.2432 | 2.72155 | 0.00139969 | 1.43558e-05 | 6.52537e-07 | 1(Win) | true |
| glaze | 1423.26 | 0.0255146 | 1375.16ms | 9578 | 4890 | 13111.9 | 6417.86 | 0.394867 | 3.58947 | 17.5228 | 3.49478 | 0.00184579 | 1.90664e-05 | 2.88237e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1134.75 | 0.0902042 | 1522.95ms | 9578 | 30 | 1581.7 | 8049.6 | 0.0972187 | 4.47898 | 18.2937 | 3.26185 | 0.00253358 | 9.04851e-05 | 3.82822e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1101.65 | 0.113515 | 1564.05ms | 9578 | 640 | 56695.6 | 8291.46 | 0.11076 | 4.59268 | 17.5476 | 3.01055 | 0.00403692 | 3.37688e-05 | 1.32139e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2869.53 | 0.0357353 | 1180.49ms | 9578 | 2560 | 3312.56 | 3183.21 | 0.075584 | 1.79498 | 10.0262 | 1.78451 | 0.000421498 | 2.1289e-05 | 3.62974e-06 | 1(Win) | true |
| glaze | 1987.34 | 0.0642548 | 1328.83ms | 9578 | 2560 | 22328.4 | 4596.25 | 0.0498617 | 2.58215 | 13.1194 | 2.49541 | 0.000221699 | 3.9764e-05 | 1.87604e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1493.8 | 0.0248099 | 1485.4ms | 9578 | 2560 | 5891.92 | 6114.81 | 0.0287258 | 3.41161 | 14.1607 | 2.35383 | 0.000122188 | 5.48539e-05 | 1.21127e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1412.77 | 0.0734397 | 1515.06ms | 9578 | 2560 | 57718 | 6465.54 | 0.267312 | 3.58058 | 13.3755 | 2.08749 | 0.00282389 | 2.9201e-05 | 8.85003e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4260.34 | 0.105571 | 947.034ms | 9578 | 2560 | 13115.6 | 2144.03 | 0.138511 | 1.20385 | 4.98987 | 1.00167 | 0.00140455 | 3.70723e-05 | 1.89236e-05 | 1(Win) | true |
| glaze | 2029.14 | 0.0429721 | 1179.26ms | 9578 | 2560 | 9579.4 | 4501.56 | 0.0362593 | 2.5247 | 12.6117 | 2.59261 | 0.000856618 | 5.02046e-05 | 2.34506e-05 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11990.1 | 0.0928974 | 825.288ms | 9578 | 2560 | 1282.18 | 761.817 | 0.0274761 | 0.446084 | 1.8435 | 0.215389 | 0.000747277 | 2.27164e-05 | 7.13712e-06 | 1(Win) | true |
| glaze | 5655.09 | 0.128524 | 911.952ms | 9578 | 30 | 129.289 | 1615.23 | 0.0907198 | 0.917906 | 4.3791 | 0.710482 | 0.000208812 | 1.39208e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3396.45 | 0.0690533 | 836.267ms | 3873 | 160 | 90.2261 | 1087.48 | 0.149075 | 1.54509 | 8.52337 | 1.03305 | 0.000258198 | 2.90473e-05 | 3.22747e-06 | 1(Win) | true |
| glaze | 1970.16 | 0.0288344 | 914.686ms | 3873 | 640 | 187.023 | 1874.76 | 0.125857 | 2.67132 | 13.0594 | 1.62097 | 0.000258198 | 8.51246e-05 | 3.46953e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 931.203 | 0.0522649 | 1129.36ms | 3873 | 1280 | 5500.93 | 3966.46 | 0.10039 | 5.48111 | 15.5029 | 1.99152 | 0.00119618 | 6.33391e-05 | 1.57339e-05 | 3(Loss) | true |
| simdjson (ondemand) | 548.347 | 0.0667079 | 1406.15ms | 3873 | 640 | 12921.6 | 6735.84 | 0.0295904 | 9.24157 | 26.9644 | 3.65841 | 0.0147257 | 8.18971e-05 | 3.87297e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3720.57 | 0.0779371 | 826.841ms | 3873 | 2560 | 1532.51 | 992.746 | 0.044522 | 1.41173 | 8.0865 | 0.938807 | 0.000259408 | 5.73885e-05 | 1.25065e-05 | 1(Win) | true |
| glaze | 2026.24 | 0.0533925 | 906.284ms | 3873 | 80 | 75.7816 | 1822.88 | 0.00137148 | 2.55439 | 12.6292 | 1.52672 | 0.000413116 | 2.90473e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 947.734 | 0.054516 | 1117.27ms | 3873 | 40 | 180.563 | 3897.28 | 0.000213825 | 5.39847 | 15.0728 | 1.89724 | 0.00171056 | 5.16396e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 555.744 | 0.0239709 | 1394.23ms | 3873 | 2560 | 6497.62 | 6646.19 | 0.00677034 | 9.14711 | 26.543 | 3.55952 | 0.0170019 | 5.52705e-05 | 1.08927e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 933.077 | 0.0397543 | 1131.89ms | 3873 | 2560 | 6339.69 | 3958.5 | 0.0426807 | 5.45981 | 24.8965 | 5.11671 | 0.00668399 | 6.61632e-05 | 2.40043e-05 | 1(Win) | true |
| glaze | 858.967 | 0.0415537 | 1166.12ms | 3873 | 640 | 2043.35 | 4300.02 | 0.00537759 | 5.94403 | 28.9184 | 5.69688 | 0.0059446 | 6.25323e-05 | 2.58198e-05 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5691.12 | 0.0377821 | 822.308ms | 3873 | 2560 | 153.926 | 649.007 | 0.382113 | 0.948933 | 4.92151 | 0.557707 | 0.000260719 | 3.70151e-05 | 4.1352e-06 | 1(Win) | true |
| glaze | 2575.61 | 0.0820792 | 904.848ms | 3873 | 320 | 443.354 | 1434.06 | 0.14166 | 2.01941 | 8.46347 | 0.946037 | 0.00399238 | 3.87297e-05 | 0 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 976.801 | 0.273541 | 6332.74ms | 2090234 | 40 | 1.24648e+09 | 2.04075e+06 | 0.479763 | 5.12609 | 25.1202 | 5.2287 | 0.0161085 | 0.067739 | 1.38501e-05 | 1(Win) | true |
| jsonifier (two-stage) | 891.842 | 0.193129 | 6976.22ms | 2090234 | 80 | 1.49073e+09 | 2.23515e+06 | 0.16229 | 5.66306 | 27.5679 | 5.51077 | 0.0193947 | 0.107546 | 3.26578e-05 | 2(Loss) | true |
| glaze | 800.007 | 0.108941 | 7752.12ms | 2090234 | 30 | 2.21058e+08 | 2.49173e+06 | 0.112321 | 6.313 | 29.9123 | 5.98286 | 0.018332 | 0.0663355 | 5.22748e-05 | 3(Loss) | true |
| simdjson (ondemand) | 651.344 | 0.126211 | 9518.23ms | 2090234 | 160 | 2.38718e+09 | 3.06045e+06 | 0.0284363 | 7.7434 | 31.1376 | 5.64392 | 0.0255893 | 0.114136 | 0.000535221 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1214.23 | 0.309274 | 6291.96ms | 2090234 | 40 | 1.03118e+09 | 1.6417e+06 | 0.116879 | 4.14088 | 19.8329 | 3.938 | 0.0156178 | 0.043357 | 1.19963e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1067.8 | 0.155764 | 6980.89ms | 2090234 | 160 | 1.35289e+09 | 1.86682e+06 | 0.222908 | 4.73692 | 22.3276 | 4.23696 | 0.0188447 | 0.0820641 | 3.926e-05 | 2(Loss) | true |
| glaze | 944.394 | 0.250224 | 7737.5ms | 2090234 | 40 | 1.11584e+09 | 2.11077e+06 | 0.101018 | 5.33137 | 24.5658 | 4.68485 | 0.0175652 | 0.0420245 | 2.54995e-05 | 3(Loss) | true |
| simdjson (ondemand) | 761.318 | 0.150511 | 9356.37ms | 2090234 | 160 | 2.48494e+09 | 2.61836e+06 | 0.368696 | 6.63393 | 25.8422 | 4.35972 | 0.0216573 | 0.0796341 | 4.4388e-05 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1612.47 | 0.159757 | 7905.22ms | 2090234 | 30 | 1.17017e+08 | 1.23624e+06 | 0.0709334 | 3.12077 | 7.87999 | 0.405686 | 0.000235396 | 0.050535 | 1.86263e-05 | 1(Win) | true |
| glaze | 957.303 | 0.0640318 | 6488.76ms | 2090234 | 160 | 2.84447e+08 | 2.08231e+06 | 0.0173308 | 5.25006 | 9.34197 | 0.534057 | 0.000243744 | 0.0698211 | 3.61592e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1596.35 | 0.148238 | 7907.86ms | 2090234 | 320 | 1.09648e+09 | 1.24872e+06 | 0.199656 | 3.1446 | 7.87983 | 0.405651 | 0.000236023 | 0.0504403 | 1.01364e-05 | 1(Win) | true |
| glaze | 992.987 | 0.0628762 | 6264.19ms | 2090234 | 40 | 6.37287e+07 | 2.00748e+06 | 0.407167 | 5.08755 | 9.33804 | 0.533131 | 0.000233718 | 0.0436333 | 2.45786e-05 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2623.56 | 0.24138 | 7564.09ms | 6661897 | 30 | 1.02503e+09 | 2.42163e+06 | 0.0441189 | 1.90376 | 9.51132 | 1.77135 | 0.0058269 | 0.0566152 | 0.000791481 | 1(Win) | true |
| jsonifier | 2603.58 | 0.155684 | 7578.78ms | 6661897 | 160 | 2.30921e+09 | 2.44021e+06 | 0.133582 | 1.92739 | 9.96259 | 2.13064 | 0.00524647 | 0.0342155 | 0.000502483 | 2(Loss) | true |
| glaze | 1973.12 | 0.125516 | 10057.6ms | 6661897 | 80 | 1.3067e+09 | 3.21991e+06 | 0.121369 | 2.5594 | 12.3181 | 2.44199 | 0.00639549 | 0.0359627 | 8.27054e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1908.62 | 0.138743 | 10270.9ms | 6661897 | 160 | 3.41272e+09 | 3.32873e+06 | 0.150096 | 2.61968 | 10.6151 | 1.81034 | 0.00728002 | 0.058361 | 0.00753603 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3105.39 | 0.254072 | 7562.88ms | 6661897 | 40 | 1.08079e+09 | 2.04589e+06 | 0.111389 | 1.60936 | 7.87118 | 1.37246 | 0.00558317 | 0.0484036 | 0.000558632 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3101.02 | 0.170596 | 7549.9ms | 6661897 | 80 | 9.77272e+08 | 2.04877e+06 | 0.034693 | 1.62114 | 8.32317 | 1.73184 | 0.00504635 | 0.0260123 | 0.000996343 | 1(Tie) | true |
| glaze | 2252.97 | 0.105154 | 9978.78ms | 6661897 | 160 | 1.40688e+09 | 2.81995e+06 | 0.202959 | 2.23904 | 10.6695 | 2.04272 | 0.00613668 | 0.0270111 | 0.00199983 | 3(Loss) | true |
| simdjson (ondemand) | 2220.88 | 0.134088 | 10107.7ms | 6661897 | 160 | 2.35422e+09 | 2.8607e+06 | 0.05825 | 2.24993 | 8.95557 | 1.40776 | 0.00604549 | 0.0473071 | 0.00675994 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4649.53 | 0.1166 | 8651.02ms | 6661897 | 40 | 1.0154e+08 | 1.36643e+06 | 0.0176451 | 1.06984 | 2.5412 | 0.127288 | 7.37628e-05 | 0.0278189 | 0.00125534 | 1(Win) | true |
| glaze | 3109.48 | 0.285872 | 6471.43ms | 6661897 | 30 | 1.02349e+09 | 2.04319e+06 | 0.744461 | 1.60155 | 4.19679 | 0.469317 | 7.65047e-05 | 0.0634237 | 0.0133319 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4662.66 | 0.0586934 | 8659.29ms | 6661897 | 160 | 1.02336e+08 | 1.36259e+06 | 0.0960006 | 1.068 | 2.54115 | 0.127277 | 7.3593e-05 | 0.0277984 | 0.00152582 | 1(Win) | true |
| glaze | 3798.42 | 0.0761473 | 5215.77ms | 6661897 | 160 | 2.59549e+08 | 1.67261e+06 | 0.149096 | 1.31009 | 4.19539 | 0.468987 | 7.47873e-05 | 0.0247285 | 0.00217963 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2471.41 | 0.0974473 | 5138.94ms | 500299 | 1280 | 4.53023e+07 | 193057 | 0.139005 | 2.03479 | 9.05629 | 1.72149 | 0.0111273 | 0.00634176 | 6.01906e-05 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1818.81 | 0.269616 | 6922.14ms | 500299 | 320 | 1.60076e+08 | 262326 | 0.0351785 | 2.75482 | 12.4248 | 2.14791 | 0.0137313 | 0.0326688 | 0.000220162 | 2(Tie) | true |
| glaze STATISTICAL TIE | 1818.43 | 0.0743268 | 6921.88ms | 500299 | 320 | 1.21704e+07 | 262381 | 0.0117388 | 2.76119 | 12.3951 | 2.34786 | 0.0138528 | 0.00498398 | 0.0001773 | 2(Tie) | true |
| simdjson (ondemand) | 1214.82 | 0.149303 | 5103.04ms | 500299 | 320 | 1.10034e+08 | 392752 | 0.245807 | 4.14326 | 14.7062 | 2.41017 | 0.0167325 | 0.0301812 | 0.000466427 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3059.19 | 0.0913489 | 10025.4ms | 500299 | 1280 | 2.59814e+07 | 155964 | 0.0935157 | 1.65144 | 7.90981 | 1.44407 | 0.00849261 | 0.0036691 | 4.31508e-05 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2161.35 | 0.106996 | 6697.88ms | 500299 | 640 | 3.5705e+07 | 220752 | 0.119656 | 2.31379 | 11.273 | 1.86945 | 0.0103396 | 0.0237849 | 0.000161741 | 2(Tie) | true |
| glaze STATISTICAL TIE | 2160.65 | 0.19436 | 6743.19ms | 500299 | 160 | 2.94731e+07 | 220823 | 0.105276 | 2.33194 | 11.2553 | 2.07345 | 0.00964766 | 0.00315291 | 8.00396e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1408.29 | 0.104652 | 9643.66ms | 500299 | 1280 | 1.60908e+08 | 338795 | 0.313416 | 3.58052 | 13.5496 | 2.12609 | 0.00856021 | 0.0152714 | 0.000242282 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10697.8 | 0.0632101 | 5250.34ms | 500299 | 160 | 127165 | 44600.2 | 0.0109292 | 0.472711 | 2.16192 | 0.352701 | 0.00184087 | 0.00359404 | 3.77274e-06 | 1(Win) | true |
| glaze | 5429.21 | 0.206718 | 9540.53ms | 500299 | 640 | 2.11214e+07 | 87880.6 | 0.237755 | 0.917226 | 3.64324 | 0.515256 | 0.00171417 | 0.0238622 | 6.4121e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10649.1 | 0.0454078 | 5232.72ms | 500299 | 4890 | 2.02398e+06 | 44804.2 | 0.106453 | 0.471719 | 2.16091 | 0.352473 | 0.00181424 | 0.00350737 | 5.53575e-06 | 1(Win) | true |
| glaze | 6380.1 | 0.0831117 | 8248.58ms | 500299 | 2560 | 9.88938e+06 | 74782.9 | 0.0644148 | 0.783959 | 3.63047 | 0.512286 | 0.00171733 | 0.00190609 | 2.78138e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4276.28 | 0.272742 | 8471.77ms | 1439562 | 320 | 2.45349e+08 | 321044 | 0.627983 | 1.17614 | 5.23459 | 0.790142 | 0.004547 | 0.0572756 | 8.22255e-05 | 1(Win) | true |
| jsonifier | 3779.62 | 0.0662113 | 9491.33ms | 1439562 | 320 | 1.85088e+07 | 363230 | 0.000883557 | 1.32666 | 5.74363 | 1.20102 | 0.00362157 | 0.0213785 | 0.000210259 | 2(Loss) | true |
| simdjson (ondemand) | 3059.25 | 0.0895333 | 5829.82ms | 1439562 | 640 | 1.03319e+08 | 448762 | 0.0569421 | 1.63299 | 5.97112 | 0.878011 | 0.00566304 | 0.0519432 | 0.000132274 | 3(Loss) | true |
| glaze | 2981.88 | 0.116834 | 5973.14ms | 1439562 | 80 | 2.31479e+07 | 460406 | 0.0376657 | 1.68218 | 7.45068 | 1.44296 | 0.00605497 | 0.0180511 | 5.99141e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4909.57 | 0.173489 | 8319.6ms | 1439562 | 160 | 3.76562e+07 | 279632 | 0.0646146 | 1.02244 | 4.83471 | 0.69356 | 0.00354565 | 0.0500395 | 3.59875e-05 | 1(Win) | true |
| jsonifier | 4269.81 | 0.129972 | 9348.09ms | 1439562 | 30 | 5.23918e+06 | 321531 | 0.228021 | 1.18298 | 5.34667 | 1.1049 | 0.00270906 | 0.0153867 | 7.86813e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3504.23 | 0.205068 | 5497.34ms | 1439562 | 160 | 1.03274e+08 | 391776 | 0.32877 | 1.42285 | 5.57095 | 0.779674 | 0.00317233 | 0.0396269 | 5.9024e-05 | 3(Loss) | true |
| glaze | 3248.76 | 0.115903 | 5942.75ms | 1439562 | 160 | 3.83828e+07 | 422583 | 0.0622957 | 1.52886 | 7.05326 | 1.34737 | 0.00460267 | 0.0130042 | 8.42313e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17517.3 | 0.153261 | 8692.14ms | 1439562 | 30 | 432824 | 78372.5 | 0.346428 | 0.282872 | 0.881839 | 0.127121 | 0.000541206 | 0.0163576 | 3.17458e-05 | 1(Win) | true |
| glaze | 5548.62 | 0.122751 | 6539.24ms | 1439584 | 320 | 2.9519e+07 | 247430 | 0.053961 | 0.895247 | 2.7519 | 0.504909 | 0.000939427 | 0.060372 | 0.000132339 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17756.6 | 0.0790795 | 8600.5ms | 1439562 | 4890 | 1.82801e+07 | 77316.2 | 0.0662859 | 0.279988 | 0.88147 | 0.127038 | 0.000539677 | 0.0161404 | 1.87526e-05 | 1(Win) | true |
| glaze | 7586.12 | 0.110656 | 9713.9ms | 1439584 | 640 | 2.56662e+07 | 180974 | 0.0613048 | 0.6636 | 2.74647 | 0.503639 | 0.000942666 | 0.0153478 | 8.46154e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2235.79 | 0.22973 | 3148.97ms | 56369 | 30 | 91532.6 | 24044.2 | 0.0621464 | 2.22754 | 9.30589 | 1.86053 | 0.00431029 | 0.000140739 | 0.000108807 | 1(Win) | true |
| glaze | 1923.9 | 0.0288666 | 3553.9ms | 56369 | 4890 | 318137 | 27942 | 0.244451 | 2.60584 | 11.6315 | 2.30947 | 0.00673447 | 0.000121936 | 9.30619e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1795.29 | 0.0453152 | 3739.6ms | 56369 | 2560 | 471349 | 29943.8 | 0.0760857 | 2.78956 | 12.1162 | 2.21432 | 0.00599072 | 9.73704e-05 | 7.36012e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1438.4 | 0.128587 | 4521.84ms | 56369 | 80 | 184759 | 37373.1 | 0.037608 | 3.51731 | 14.2367 | 2.34795 | 0.00638649 | 7.31785e-05 | 5.67688e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3267.42 | 0.079769 | 2750.13ms | 56369 | 320 | 55117.5 | 16452.6 | 0.092813 | 1.52259 | 7.14283 | 1.37423 | 0.00226044 | 3.56468e-05 | 2.63886e-05 | 1(Win) | true |
| glaze | 2941.78 | 0.0613172 | 2934.59ms | 56369 | 1280 | 160707 | 18273.8 | 0.0816672 | 1.69602 | 9.14545 | 1.7497 | 0.00236417 | 2.24386e-05 | 1.55643e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2496.36 | 0.0916937 | 3259.84ms | 56369 | 320 | 124766 | 21534.4 | 0.112752 | 1.98999 | 9.9675 | 1.73118 | 0.00221797 | 3.60349e-05 | 2.44483e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1784.06 | 0.144023 | 4164.27ms | 56369 | 80 | 150667 | 30132.3 | 0.0883138 | 2.7821 | 11.8498 | 1.81923 | 0.00636875 | 1.5301e-05 | 7.31785e-06 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14391 | 0.0984692 | 1124.96ms | 56369 | 4890 | 66161.8 | 3735.5 | 0.0414627 | 0.348837 | 1.40254 | 0.237666 | 0.000167509 | 2.60843e-05 | 1.54656e-05 | 1(Win) | true |
| glaze | 5983.66 | 0.0864186 | 1653.35ms | 56369 | 4890 | 294761 | 8984.07 | 0.260782 | 0.829842 | 3.10878 | 0.487609 | 0.000127429 | 3.66196e-05 | 2.18325e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14815 | 0.045759 | 1109.57ms | 56369 | 2560 | 7057.79 | 3628.59 | 0.0779901 | 0.338854 | 1.39359 | 0.235626 | 0.000145172 | 1.68602e-05 | 1.07827e-05 | 1(Win) | true |
| glaze | 6205.68 | 0.114255 | 1616.44ms | 56369 | 4890 | 479029 | 8662.65 | 0.224151 | 0.805893 | 3.02988 | 0.469833 | 0.0001171 | 2.57905e-05 | 1.62565e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2808.25 | 0.0872921 | 3968.27ms | 94370 | 320 | 250437 | 32047.8 | 0.102398 | 1.79168 | 7.82934 | 1.34392 | 0.0031044 | 3.98034e-05 | 3.09619e-05 | 1(Win) | true |
| glaze | 2458.66 | 0.0252348 | 4421.19ms | 94370 | 4890 | 417233 | 36604.6 | 0.118123 | 2.04293 | 9.44917 | 1.92833 | 0.00518091 | 4.30451e-05 | 3.06868e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2239.53 | 0.0283079 | 4764.66ms | 94370 | 2560 | 331291 | 40186.2 | 0.0565969 | 2.23881 | 9.04741 | 1.43017 | 0.00436653 | 8.73225e-05 | 6.9002e-05 | 3(Loss) | true |
| jsonifier | 2127.76 | 0.0296579 | 4986.92ms | 94370 | 4890 | 769505 | 42297.1 | 0.111906 | 2.35327 | 8.45504 | 1.84913 | 0.00494964 | 9.4522e-05 | 7.72727e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3688.84 | 0.0604038 | 3545.92ms | 94370 | 640 | 138994 | 24397.4 | 0.0853212 | 1.35717 | 6.54403 | 1.05511 | 0.00153972 | 2.18886e-05 | 1.70208e-05 | 1(Win) | true |
| glaze | 3319.12 | 0.040527 | 3826.3ms | 94370 | 4890 | 590501 | 27115.1 | 0.213575 | 1.50498 | 7.97099 | 1.59546 | 0.00271185 | 2.76876e-05 | 1.91237e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2808.97 | 0.0311866 | 4353.13ms | 94370 | 2560 | 255592 | 32039.5 | 0.00130087 | 1.78416 | 7.61402 | 1.11215 | 0.00411588 | 1.95913e-05 | 1.39701e-05 | 3(Loss) | true |
| jsonifier | 2581.4 | 0.0287828 | 4586.76ms | 94370 | 2560 | 257789 | 34864.2 | 0.142197 | 1.94078 | 7.17648 | 1.56182 | 0.00403849 | 3.76179e-05 | 3.02582e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18267.5 | 0.027371 | 1234.93ms | 94370 | 4890 | 8892 | 4926.69 | 0.0866581 | 0.278322 | 0.943658 | 0.148903 | 0.000119897 | 1.04211e-05 | 6.80002e-06 | 1(Win) | true |
| glaze | 5058.73 | 0.0963213 | 2532.76ms | 94370 | 1280 | 375872 | 17790.7 | 0.0732881 | 0.985732 | 3.39019 | 0.637639 | 0.00132707 | 3.09536e-05 | 2.26916e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18691.4 | 0.0252698 | 1227.44ms | 94370 | 640 | 947.479 | 4814.96 | 0.0951853 | 0.272942 | 0.938307 | 0.147695 | 7.9077e-05 | 6.88778e-06 | 4.08962e-06 | 1(Win) | true |
| glaze | 5873.15 | 0.0366912 | 2279.08ms | 94370 | 4890 | 154582 | 15323.7 | 0.0277596 | 0.860581 | 3.33675 | 0.625209 | 0.00132644 | 1.49392e-05 | 1.03235e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2692.64 | 0.035612 | 1156.02ms | 11812 | 4890 | 10854 | 4183.55 | 0.00867699 | 1.87996 | 9.27053 | 1.62001 | 0.0029057 | 4.00792e-05 | 1.9096e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1969.59 | 0.058659 | 1320.4ms | 11812 | 160 | 1800.87 | 5719.36 | 0.00142063 | 2.58822 | 12.6041 | 2.15895 | 0.00422081 | 2.27523e-05 | 4.23298e-06 | 2(Loss) | true |
| glaze | 1833.48 | 0.160801 | 1359.04ms | 11812 | 160 | 15616.7 | 6143.93 | 0.0883222 | 2.77285 | 13.4657 | 2.6523 | 0.00173605 | 1.58737e-05 | 4.76211e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1341.32 | 0.0313701 | 1587.2ms | 11812 | 2560 | 17768.7 | 8398.31 | 0.052703 | 3.77014 | 16.4517 | 2.87386 | 0.00300684 | 4.16023e-05 | 2.08011e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3106.19 | 0.0673473 | 1151.43ms | 11812 | 160 | 954.448 | 3626.57 | 0.041551 | 1.64671 | 8.40984 | 1.41678 | 0.00236835 | 1.79902e-05 | 1.05825e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2165.33 | 0.0589266 | 1314.4ms | 11812 | 1280 | 12029.1 | 5202.35 | 0.126771 | 2.34624 | 11.7431 | 1.95564 | 0.00383647 | 1.72626e-05 | 4.36526e-06 | 2(Loss) | true |
| glaze | 2024.68 | 0.0418831 | 1343.19ms | 11812 | 2560 | 13901.1 | 5563.73 | 0.0304405 | 2.50389 | 12.3822 | 2.40975 | 0.00197859 | 2.41082e-05 | 1.11116e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1457.56 | 0.148089 | 1577.5ms | 11812 | 160 | 20958.5 | 7728.54 | 0.0682191 | 3.47239 | 15.5942 | 2.68227 | 0.00226094 | 1.37572e-05 | 3.17474e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11776.4 | 0.0970454 | 831.424ms | 11812 | 2560 | 2206.03 | 956.557 | 0.0466952 | 0.445922 | 2.01079 | 0.339578 | 8.5751e-05 | 2.58609e-05 | 9.9872e-06 | 1(Win) | true |
| glaze | 4005.46 | 0.452719 | 1021.08ms | 11812 | 160 | 25937 | 2812.36 | 0.061819 | 1.26978 | 5.2406 | 0.808754 | 0.000524361 | 2.38105e-05 | 8.46597e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12323.7 | 0.0688069 | 829.585ms | 11812 | 320 | 126.584 | 914.075 | 0.00136752 | 0.429353 | 1.96461 | 0.328903 | 9.18028e-05 | 1.508e-05 | 5.55579e-06 | 1(Win) | true |
| glaze | 4453.12 | 0.135307 | 986.775ms | 11812 | 4890 | 57288.9 | 2529.64 | 0.147875 | 1.14429 | 4.96444 | 0.74763 | 0.000662579 | 3.75169e-05 | 1.66203e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4313.27 | 0.0373623 | 1435.54ms | 31235 | 4890 | 32557.1 | 6906.13 | 0.227324 | 1.17023 | 5.72336 | 0.870562 | 0.00180944 | 2.32946e-05 | 1.26097e-05 | 1(Win) | true |
| jsonifier | 3626.64 | 0.0565804 | 1571.33ms | 31235 | 320 | 6911.23 | 8213.67 | 0.00323384 | 1.40134 | 6.14388 | 1.24341 | 0.00320024 | 1.93093e-05 | 1.14055e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3171.74 | 0.0355195 | 1683.27ms | 31235 | 2560 | 28488.1 | 9391.7 | 0.141527 | 1.58936 | 7.00909 | 1.12175 | 0.00142031 | 2.02097e-05 | 1.11303e-05 | 3(Loss) | true |
| glaze | 2569.77 | 0.0276488 | 1901.6ms | 31235 | 4890 | 50229.3 | 11591.7 | 0.335708 | 1.95556 | 8.19209 | 1.62683 | 0.00540895 | 1.75593e-05 | 7.83689e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4659.12 | 0.0412965 | 1441.16ms | 31235 | 2560 | 17846 | 6393.49 | 0.285625 | 1.08671 | 5.40772 | 0.795806 | 0.00179284 | 1.13429e-05 | 5.13997e-06 | 1(Win) | true |
| jsonifier | 3833.08 | 0.0604907 | 1576.42ms | 31235 | 640 | 14143.1 | 7771.3 | 0.106555 | 1.32338 | 5.82837 | 1.16875 | 0.00318778 | 7.35353e-06 | 3.20154e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3387.34 | 0.160382 | 1668.24ms | 31235 | 160 | 31827.1 | 8793.93 | 0.00447732 | 1.4757 | 6.6859 | 1.0494 | 0.000818593 | 2.06099e-05 | 1.26061e-05 | 3(Loss) | true |
| glaze | 2766.46 | 0.0385056 | 1875.14ms | 31235 | 1280 | 22003.6 | 10767.6 | 0.117991 | 1.83133 | 7.79046 | 1.53712 | 0.00533449 | 8.87926e-06 | 3.45166e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19170.2 | 0.0875799 | 891.31ms | 31235 | 1280 | 2370.54 | 1553.87 | 0.0413112 | 0.2706 | 0.917112 | 0.128382 | 3.23405e-05 | 1.11303e-05 | 5.55267e-06 | 1(Win) | true |
| glaze | 4872.36 | 0.110523 | 1349.03ms | 31235 | 1280 | 58441 | 6113.67 | 0.164861 | 1.03635 | 3.60067 | 0.652473 | 0.00225646 | 2.76633e-05 | 1.65329e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19036.8 | 0.46249 | 887.982ms | 31235 | 160 | 8379.51 | 1564.76 | 0.0771482 | 0.267142 | 0.900208 | 0.124476 | 4.44213e-05 | 4.40211e-06 | 1.60077e-06 | 1(Win) | true |
| glaze | 5556.95 | 0.054777 | 1275.37ms | 31235 | 4890 | 42161.6 | 5360.5 | 0.00825423 | 0.910436 | 3.47809 | 0.625004 | 0.00227978 | 1.81028e-05 | 8.6029e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2698.2 | 0.0986864 | 4611.86ms | 108313 | 80 | 114187 | 38283.1 | 0.0263755 | 1.8731 | 8.30938 | 1.66307 | 0.00262399 | 9.46331e-06 | 4.84706e-06 | 1(Win) | true |
| glaze | 2427.34 | 0.0247552 | 5009.62ms | 108313 | 4890 | 542680 | 42555 | 0.0672128 | 2.07618 | 10.0311 | 1.80699 | 0.00247564 | 4.3068e-05 | 3.18436e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1995.37 | 0.0220366 | 5933.12ms | 108313 | 2560 | 333154 | 51767.5 | 0.0487172 | 2.52358 | 11.4504 | 2.0047 | 0.00280851 | 3.85782e-05 | 2.94971e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1695.31 | 0.0612504 | 6841.65ms | 108313 | 4890 | 6.81069e+06 | 60930.1 | 0.0715032 | 2.96234 | 14.2193 | 2.0317 | 0.0031206 | 5.99244e-05 | 4.54243e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3189.78 | 0.0283774 | 4171.01ms | 108313 | 2560 | 216185 | 32383.2 | 0.478119 | 1.56857 | 7.5075 | 1.47836 | 0.00221238 | 1.99653e-05 | 1.50641e-05 | 1(Win) | true |
| glaze | 2746.02 | 0.0903864 | 4711.78ms | 108313 | 320 | 369921 | 37616.4 | 0.0158533 | 1.84139 | 9.32467 | 1.64478 | 0.00218548 | 8.07844e-06 | 5.62606e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2283.4 | 0.0492241 | 5488.86ms | 108313 | 160 | 79336.7 | 45237.6 | 0.0333958 | 2.21491 | 10.6531 | 1.82136 | 0.00247933 | 1.48297e-05 | 1.14252e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1905.27 | 0.0148449 | 6375.13ms | 108313 | 4890 | 316745 | 54215.6 | 0.0633462 | 2.64878 | 13.4779 | 1.86523 | 0.00236843 | 2.11309e-05 | 1.62711e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18628.5 | 0.07869 | 1298.14ms | 108313 | 40 | 761.563 | 5545.02 | 0.0678244 | 0.273496 | 1.23505 | 0.322731 | 0.000193652 | 6.23194e-06 | 3.23138e-06 | 1(Win) | true |
| glaze | 4812.95 | 0.518331 | 2895.35ms | 108313 | 640 | 7.92014e+06 | 21462 | 0.047627 | 1.0473 | 2.73703 | 0.384617 | 0.000277278 | 1.40507e-05 | 9.79511e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18596.9 | 0.0308109 | 1298.03ms | 108313 | 4890 | 14321.8 | 5554.44 | 0.0693203 | 0.272707 | 1.23039 | 0.321679 | 0.000180072 | 5.0354e-06 | 2.72821e-06 | 1(Win) | true |
| glaze | 6600.3 | 0.106941 | 2312.17ms | 108313 | 2560 | 717076 | 15650.1 | 0.0241953 | 0.76743 | 2.69241 | 0.374221 | 0.000295941 | 3.31793e-06 | 1.36324e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3449.79 | 0.0404842 | 6652.17ms | 213963 | 4890 | 2.80396e+06 | 59148.8 | 0.075888 | 1.45114 | 6.60083 | 1.06883 | 0.00158121 | 3.7381e-05 | 2.88508e-05 | 1(Win) | true |
| simdjson (ondemand) | 3114.92 | 0.0388229 | 7297.46ms | 213963 | 640 | 413944 | 65507.7 | 0.0024139 | 1.61661 | 7.80475 | 1.05223 | 0.00157851 | 8.60254e-06 | 5.56463e-06 | 2(Loss) | true |
| glaze | 3000.67 | 0.0182197 | 7564.54ms | 213963 | 2560 | 392976 | 68001.9 | 0.0789061 | 1.68407 | 7.92416 | 1.45949 | 0.0029044 | 9.08451e-06 | 5.23418e-06 | 3(Loss) | true |
| jsonifier | 2760.63 | 0.021796 | 8139.65ms | 213963 | 640 | 166110 | 73914.7 | 0.0198368 | 1.8312 | 6.83397 | 1.51732 | 0.00181525 | 9.82208e-06 | 5.89325e-06 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3883.46 | 0.0323887 | 6216.87ms | 213963 | 4890 | 1.41624e+06 | 52543.6 | 0.160242 | 1.28899 | 6.19933 | 0.976361 | 0.00126284 | 6.72e-06 | 4.30956e-06 | 1(Win) | true |
| simdjson (ondemand) | 3464.81 | 0.0527121 | 6868.4ms | 213963 | 160 | 154191 | 58892.5 | 0.0189364 | 1.45902 | 7.45568 | 0.973795 | 0.00112449 | 5.34555e-06 | 3.35923e-06 | 2(Loss) | true |
| glaze | 3280.49 | 0.0334269 | 7140.09ms | 213963 | 1280 | 553350 | 62201.3 | 0.0696119 | 1.53514 | 7.55695 | 1.37548 | 0.00256227 | 6.34602e-06 | 4.08219e-06 | 3(Loss) | true |
| jsonifier | 2989.32 | 0.0414006 | 7728.35ms | 213963 | 640 | 511124 | 68260.1 | 0.0240384 | 1.68004 | 6.42841 | 1.42395 | 0.00162993 | 6.32411e-06 | 3.69515e-06 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22975.3 | 0.0674571 | 1638.48ms | 213963 | 160 | 5742.9 | 8881.33 | 0.214316 | 0.221003 | 0.738604 | 0.166192 | 8.67849e-05 | 2.04475e-06 | 7.59477e-07 | 1(Win) | true |
| glaze | 5585.34 | 0.119433 | 4406.39ms | 213963 | 4890 | 9.30964e+06 | 36533.3 | 0.156128 | 0.893055 | 3.00447 | 0.570973 | 0.000650317 | 1.46433e-05 | 8.72903e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23179.1 | 0.0189659 | 1622.32ms | 213963 | 4890 | 13631.3 | 8803.23 | 0.0193853 | 0.219016 | 0.736296 | 0.165669 | 8.64177e-05 | 3.20278e-06 | 2.096e-06 | 1(Win) | true |
| glaze | 6698.01 | 0.0600536 | 3827.86ms | 213963 | 640 | 214212 | 30464.4 | 0.174106 | 0.755153 | 2.9783 | 0.564888 | 0.000653822 | 2.68008e-06 | 1.24876e-06 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 851.47 | 0.133277 | 6407.35ms | 1834197 | 160 | 1.19945e+09 | 2.05436e+06 | 0.0594812 | 5.90381 | 26.405 | 5.74259 | 0.0290033 | 0.0813469 | 0.00260618 | 1(Win) | true |
| jsonifier (two-stage) | 738.203 | 0.161668 | 7393.63ms | 1834197 | 30 | 4.40262e+08 | 2.36957e+06 | 0.155099 | 6.77657 | 30.4961 | 6.32049 | 0.03447 | 0.144867 | 0.0149387 | 2(Loss) | true |
| glaze | 699.758 | 0.118074 | 7796.35ms | 1834197 | 160 | 1.39389e+09 | 2.49976e+06 | 0.598175 | 7.18775 | 30.7704 | 6.4498 | 0.0345208 | 0.0814778 | 0.00423105 | 3(Loss) | true |
| simdjson (ondemand) | 615.492 | 0.0869006 | 8871.65ms | 1834197 | 160 | 9.75919e+08 | 2.842e+06 | 0.0502826 | 8.2053 | 34.7873 | 6.13802 | 0.044417 | 0.146377 | 0.00769278 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 946.622 | 0.37372 | 6424.9ms | 1834197 | 40 | 1.90762e+09 | 1.84786e+06 | 0.0876835 | 5.33184 | 23.4091 | 5.03589 | 0.0284093 | 0.0551337 | 0.00203543 | 1(Win) | true |
| jsonifier (two-stage) | 823.385 | 0.065437 | 7293ms | 1834197 | 160 | 3.0921e+08 | 2.12443e+06 | 0.0989341 | 6.12391 | 27.501 | 5.61404 | 0.0337167 | 0.118594 | 0.00436402 | 2(Loss) | true |
| glaze | 766.229 | 0.273139 | 7779.78ms | 1834197 | 80 | 3.11053e+09 | 2.2829e+06 | 0.03251 | 6.55213 | 27.7719 | 5.74383 | 0.0328693 | 0.0581869 | 0.00390723 | 3(Loss) | true |
| simdjson (ondemand) | 676.278 | 0.156521 | 8753.38ms | 1834197 | 40 | 6.55614e+08 | 2.58655e+06 | 0.0540289 | 7.46154 | 31.7747 | 5.42977 | 0.0399932 | 0.118858 | 0.00856885 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 845.804 | 0.172338 | 6531.7ms | 1834197 | 80 | 1.01626e+09 | 2.06812e+06 | 0.765306 | 5.99032 | 12.5137 | 0.907936 | 0.00152745 | 0.0591191 | 0.00165562 | 1(Win) | true |
| glaze | 612.594 | 0.207802 | 8868.51ms | 1833577 | 80 | 2.81477e+09 | 2.85448e+06 | 0.190785 | 8.24783 | 15.5348 | 0.949896 | 0.000982519 | 0.0486803 | 0.00125016 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 833.8 | 0.10296 | 6522.9ms | 1834197 | 160 | 7.46493e+08 | 2.0979e+06 | 0.338755 | 5.98433 | 12.5135 | 0.907899 | 0.00140168 | 0.0590701 | 2.24621e-05 | 1(Win) | true |
| glaze | 612.7 | 0.159796 | 8915.71ms | 1833577 | 80 | 1.66388e+09 | 2.85398e+06 | 0.10495 | 8.25086 | 15.534 | 0.94973 | 0.000974155 | 0.0485562 | 0.00107808 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3400.43 | 0.206038 | 8583.8ms | 9930848 | 80 | 2.63443e+09 | 2.78517e+06 | 0.0753218 | 1.46251 | 6.99631 | 1.56674 | 0.00486202 | 0.0294536 | 0.000192513 | 1(Win) | true |
| jsonifier (two-stage) | 3284.44 | 0.159422 | 8940.12ms | 9930848 | 160 | 3.38117e+09 | 2.88353e+06 | 0.0469432 | 1.51378 | 6.6254 | 1.20877 | 0.00674082 | 0.0538509 | 0.000520431 | 2(Loss) | true |
| simdjson (ondemand) | 2878.55 | 0.159705 | 10265ms | 9930848 | 40 | 1.10439e+09 | 3.29013e+06 | 0.112487 | 1.73947 | 7.46681 | 1.17958 | 0.00778193 | 0.0533482 | 0.000860642 | 3(Loss) | true |
| glaze | 2716.23 | 0.262433 | 5272.51ms | 9930848 | 80 | 6.69834e+09 | 3.48675e+06 | 0.0936776 | 1.85881 | 8.53138 | 1.76058 | 0.00700236 | 0.028832 | 0.000246982 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3703.1 | 0.114633 | 8532.63ms | 9930848 | 160 | 1.37525e+09 | 2.55753e+06 | 0.181508 | 1.34345 | 6.44295 | 1.43624 | 0.00470472 | 0.0246232 | 0.000270928 | 1(Win) | true |
| jsonifier (two-stage) | 3604.26 | 0.0943293 | 8908.89ms | 9930848 | 160 | 9.83001e+08 | 2.62767e+06 | 0.0550982 | 1.38802 | 6.07218 | 1.07837 | 0.0066268 | 0.0490625 | 0.000577086 | 2(Loss) | true |
| simdjson (ondemand) | 3136.14 | 0.111048 | 10137.3ms | 9930848 | 40 | 4.49849e+08 | 3.01989e+06 | 0.519689 | 1.59758 | 6.90998 | 1.04883 | 0.00701181 | 0.047792 | 0.00141334 | 3(Loss) | true |
| glaze | 2874.48 | 0.218509 | 5270.89ms | 9930848 | 80 | 4.14652e+09 | 3.29478e+06 | 0.113287 | 1.74367 | 7.97713 | 1.6301 | 0.00671249 | 0.024481 | 0.0011418 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6119.1 | 0.176455 | 9868.82ms | 9930848 | 80 | 5.96703e+08 | 1.54774e+06 | 0.0079658 | 0.823522 | 2.45732 | 0.16772 | 0.000256708 | 0.0248169 | 0.000104314 | 1(Win) | true |
| glaze | 3685.84 | 0.231738 | 8041.67ms | 9930228 | 80 | 2.83615e+09 | 2.56935e+06 | 0.244489 | 1.3696 | 4.09969 | 0.480834 | 0.00109385 | 0.041539 | 0.000743904 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6060.33 | 0.267724 | 9904.66ms | 9930848 | 80 | 1.40038e+09 | 1.56275e+06 | 0.286681 | 0.829323 | 2.45729 | 0.167713 | 0.000269942 | 0.0247959 | 5.14646e-05 | 1(Win) | true |
| glaze | 4022.36 | 0.374079 | 7326.46ms | 9930228 | 40 | 3.10273e+09 | 2.35439e+06 | 0.0411046 | 1.25202 | 4.0994 | 0.480769 | 0.00109415 | 0.0222656 | 9.03882e-05 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 860.509 | 0.113308 | 6350.6ms | 1834197 | 80 | 4.24418e+08 | 2.03278e+06 | 0.00576522 | 5.77152 | 25.9296 | 5.60181 | 0.0298076 | 0.0827633 | 7.5762e-05 | 1(Win) | true |
| jsonifier (two-stage) | 747.967 | 0.229477 | 7325.68ms | 1834197 | 30 | 8.64028e+08 | 2.33864e+06 | 0.0483566 | 6.62581 | 30.0381 | 6.18528 | 0.0351434 | 0.145621 | 3.86727e-05 | 2(Loss) | true |
| glaze | 690.908 | 0.302439 | 7851.93ms | 1834197 | 40 | 2.34524e+09 | 2.53178e+06 | 0.111564 | 7.18465 | 30.7408 | 6.43958 | 0.0342181 | 0.0819095 | 6.05578e-05 | 3(Loss) | true |
| simdjson (ondemand) | 611.662 | 0.113462 | 8959.28ms | 1834197 | 40 | 4.21147e+08 | 2.85979e+06 | 1.2673 | 8.13362 | 34.7794 | 6.13156 | 0.0443442 | 0.146641 | 0.000884229 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 967.905 | 0.194708 | 6367.24ms | 1834197 | 80 | 9.90566e+08 | 1.80723e+06 | 0.016293 | 5.16113 | 22.9664 | 4.90765 | 0.0290787 | 0.0561472 | 6.12666e-05 | 1(Win) | true |
| jsonifier (two-stage) | 826.952 | 0.0816627 | 7347.66ms | 1834197 | 160 | 4.77418e+08 | 2.11527e+06 | 0.11597 | 6.00328 | 27.0745 | 5.49074 | 0.0341525 | 0.119433 | 0.00048175 | 2(Loss) | true |
| glaze | 761.685 | 0.159953 | 7880.38ms | 1834197 | 160 | 2.15898e+09 | 2.29652e+06 | 0.168765 | 6.54832 | 27.7732 | 5.74391 | 0.0331936 | 0.0587031 | 0.00102863 | 3(Loss) | true |
| simdjson (ondemand) | 673.236 | 0.105104 | 8829.93ms | 1834197 | 30 | 2.23725e+08 | 2.59824e+06 | 0.169876 | 7.36238 | 31.798 | 5.43388 | 0.0399778 | 0.118819 | 0.000222804 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 858.864 | 0.839489 | 6398.66ms | 1834197 | 160 | 4.67728e+10 | 2.03667e+06 | 0.124641 | 5.84111 | 12.5219 | 0.907973 | 0.00159213 | 0.0597473 | 0.000157392 | 1(Win) | true |
| glaze | 585.466 | 0.301869 | 9274.71ms | 1833577 | 30 | 2.43867e+09 | 2.98674e+06 | 0.0766815 | 8.50129 | 15.5344 | 0.950099 | 0.0010173 | 0.0758409 | 0.000599975 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 857.136 | 0.6888 | 6349.35ms | 1834197 | 160 | 3.16154e+10 | 2.04078e+06 | 0.364202 | 5.82784 | 12.5218 | 0.907936 | 0.00157171 | 0.0596486 | 0.000314508 | 1(Win) | true |
| glaze | 619.988 | 0.346747 | 8893.74ms | 1833577 | 40 | 3.82577e+09 | 2.82044e+06 | 0.234672 | 8.08846 | 15.5335 | 0.949903 | 0.00104979 | 0.048644 | 0.000678973 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3363.9 | 0.90589 | 8771.15ms | 9930848 | 80 | 5.2039e+10 | 2.81542e+06 | 0.078436 | 1.47644 | 6.89816 | 1.54719 | 0.00497182 | 0.0296868 | 0.0052986 | 1(Win) | true |
| jsonifier (two-stage) | 3279.95 | 0.715025 | 9105.81ms | 9930848 | 40 | 1.70507e+10 | 2.88748e+06 | 0.120029 | 1.52025 | 6.54098 | 1.18395 | 0.00693368 | 0.0542718 | 0.00117811 | 2(Loss) | true |
| simdjson (ondemand) | 2768.18 | 1.08352 | 5087.44ms | 9930848 | 40 | 5.49697e+10 | 3.42131e+06 | 0.622545 | 1.81553 | 7.46505 | 1.17847 | 0.00779173 | 0.053385 | 0.00464214 | 3(Loss) | true |
| glaze | 2660.1 | 0.658704 | 5470.71ms | 9930848 | 40 | 2.19997e+10 | 3.56031e+06 | 1.50786 | 1.89007 | 8.52659 | 1.75869 | 0.00712386 | 0.0289823 | 0.001323 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 3631.8 | 1.28102 | 8746.49ms | 9930848 | 40 | 4.46379e+10 | 2.60774e+06 | 1.07232 | 1.3672 | 6.35087 | 1.41897 | 0.00482065 | 0.0248123 | 0.00514691 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3555.34 | 0.606214 | 9095.58ms | 9930848 | 160 | 4.17237e+10 | 2.66382e+06 | 1.80643 | 1.4075 | 5.9936 | 1.05565 | 0.00676376 | 0.0493579 | 0.000551209 | 1(Tie) | true |
| simdjson (ondemand) | 3017.02 | 1.1471 | 5044.64ms | 9930848 | 40 | 5.18657e+10 | 3.13912e+06 | 0.398735 | 1.65247 | 6.91448 | 1.04968 | 0.00697458 | 0.0478223 | 0.00208493 | 3(Loss) | true |
| glaze | 2761.98 | 0.788536 | 5485.52ms | 9930848 | 80 | 5.84877e+10 | 3.42899e+06 | 0.913324 | 1.80839 | 7.97833 | 1.6301 | 0.00694883 | 0.0245823 | 0.00602974 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6053.54 | 0.251724 | 9862.36ms | 9930848 | 160 | 2.48155e+09 | 1.5645e+06 | 0.518248 | 0.825978 | 2.45246 | 0.16772 | 0.000213147 | 0.0248665 | 0.000442552 | 1(Win) | true |
| glaze | 3027.9 | 0.616623 | 9953.42ms | 9930228 | 40 | 1.48777e+10 | 3.12765e+06 | 0.761111 | 1.63529 | 4.1355 | 0.48086 | 0.00103707 | 0.0754798 | 0.0108242 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6146.08 | 0.190429 | 9800.21ms | 9930848 | 40 | 3.44433e+08 | 1.54095e+06 | 0.00786412 | 0.817839 | 2.45242 | 0.167713 | 0.000212499 | 0.024845 | 0.000100087 | 1(Win) | true |
| glaze | 4044.05 | 0.200045 | 7312.78ms | 9930228 | 160 | 3.51124e+09 | 2.34176e+06 | 0.555667 | 1.24806 | 4.13511 | 0.480771 | 0.00101858 | 0.0222526 | 0.00087533 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1554.53 | 0.220156 | 5116.09ms | 642697 | 320 | 2.41118e+08 | 394283 | 0.253792 | 3.22698 | 16.3802 | 3.34005 | 0.00861411 | 0.0244829 | 3.46246e-05 | 1(Win) | true |
| jsonifier | 1386.43 | 0.0882573 | 5718.85ms | 642697 | 160 | 2.43578e+07 | 442088 | 0.350934 | 3.61537 | 18.7874 | 3.613 | 0.00971831 | 0.0161715 | 2.89697e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1196.52 | 0.198703 | 6643.25ms | 642697 | 640 | 6.6307e+08 | 512255 | 0.658271 | 4.21774 | 21.1707 | 3.84034 | 0.0109152 | 0.0512491 | 8.08507e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1169.16 | 0.50825 | 6761.28ms | 642697 | 640 | 4.54359e+09 | 524242 | 0.13378 | 4.29644 | 20.7881 | 3.45378 | 0.0112287 | 0.0661155 | 7.31002e-05 | 4(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1785.69 | 0.0741252 | 9671.01ms | 642697 | 320 | 2.07148e+07 | 343242 | 0.176626 | 2.81118 | 15.1595 | 3.06767 | 0.00798913 | 0.00392033 | 6.39882e-06 | 1(Win) | true |
| jsonifier | 1495.92 | 0.0895654 | 5775.32ms | 642697 | 40 | 5.38689e+06 | 409731 | 0.0692109 | 3.37709 | 17.6712 | 3.35742 | 0.00927175 | 0.0143508 | 7.36739e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1311.92 | 0.588742 | 6319.64ms | 642697 | 640 | 4.84206e+09 | 467197 | 0.432152 | 3.84104 | 19.5327 | 3.17249 | 0.00987226 | 0.0229641 | 1.13949e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1282.49 | 0.0459337 | 6582.56ms | 642697 | 320 | 1.54211e+07 | 477916 | 0.149902 | 3.93237 | 20.0542 | 3.58478 | 0.0105416 | 0.0454824 | 1.04978e-05 | 4(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1751.03 | 0.0637465 | 9135.44ms | 642697 | 1280 | 6.37304e+07 | 350036 | 0.318993 | 2.88834 | 7.47823 | 0.699198 | 4.56244e-05 | 0.00501643 | 5.33895e-05 | 1(Win) | true |
| glaze | 986.991 | 0.419569 | 7965.8ms | 642692 | 640 | 4.34476e+09 | 620997 | 0.221825 | 5.05567 | 9.68594 | 0.702803 | 0.000190826 | 0.0431293 | 7.51575e-05 | 2(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1754.2 | 0.207527 | 9096.41ms | 642697 | 320 | 1.6825e+08 | 349403 | 0.0202376 | 2.88901 | 7.47746 | 0.699024 | 4.40332e-05 | 0.00493905 | 2.45985e-05 | 1(Win) | true |
| glaze | 1049.84 | 0.160865 | 7503.77ms | 642692 | 160 | 1.41124e+08 | 583821 | 0.0262264 | 4.7944 | 9.6841 | 0.702395 | 0.000186997 | 0.00191585 | 0.000145919 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2224.5 | 0.173701 | 6755.61ms | 1225964 | 640 | 5.33429e+08 | 525587 | 0.0340598 | 2.25322 | 11.8575 | 2.05836 | 0.00493497 | 0.0553133 | 3.34813e-05 | 1(Tie) | true |
| glaze STATISTICAL TIE | 2215.3 | 0.522979 | 6876.74ms | 1225964 | 160 | 1.21893e+09 | 527771 | 0.526499 | 2.26668 | 11.7373 | 2.48571 | 0.0048645 | 0.0285935 | 3.17403e-05 | 1(Tie) | true |
| simdjson (ondemand) | 2205.63 | 0.23963 | 6923.94ms | 1225964 | 40 | 6.45403e+07 | 530085 | 0.305632 | 2.28144 | 11.5334 | 1.83329 | 0.00473609 | 0.0617827 | 2.83858e-05 | 3(Loss) | true |
| jsonifier | 1934.11 | 0.259068 | 7739.13ms | 1225964 | 320 | 7.84824e+08 | 604502 | 0.181546 | 2.59072 | 13.2793 | 2.69426 | 0.00553498 | 0.0235202 | 1.90947e-05 | 4(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE | 2456.3 | 0.444236 | 6539.97ms | 1225964 | 30 | 1.34135e+08 | 475989 | 0.169422 | 2.04804 | 11.097 | 2.34288 | 0.00438319 | 0.0116915 | 1.06311e-05 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2446.8 | 0.351476 | 6487.96ms | 1225964 | 320 | 9.02612e+08 | 477837 | 0.209683 | 2.04964 | 10.8753 | 1.68582 | 0.0039755 | 0.0360626 | 4.98536e-05 | 1(Tie) | true |
| jsonifier (two-stage) | 2364.6 | 0.200314 | 6762.61ms | 1225964 | 640 | 6.27829e+08 | 494447 | 0.0541347 | 2.13012 | 11.2722 | 1.92441 | 0.00475382 | 0.0508764 | 2.16131e-05 | 3(Loss) | true |
| jsonifier | 2069.67 | 0.196218 | 7663.35ms | 1225964 | 40 | 4.91462e+07 | 564906 | 0.0903478 | 2.42733 | 12.694 | 2.5603 | 0.00531506 | 0.0208976 | 2.64894e-05 | 4(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4099.97 | 0.249175 | 7488.91ms | 1225964 | 640 | 3.23135e+08 | 285166 | 0.178157 | 1.23015 | 4.0341 | 0.363571 | 3.1033e-05 | 0.0113062 | 3.14574e-05 | 1(Win) | true |
| glaze | 1695.29 | 0.379905 | 8855.69ms | 1225970 | 80 | 5.4918e+08 | 689663 | 0.0463616 | 2.96103 | 6.13889 | 0.609038 | 0.000253106 | 0.0341448 | 1.14297e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4134.98 | 0.0336244 | 7497.18ms | 1225964 | 40 | 361558 | 282751 | 0.021086 | 1.22194 | 4.03384 | 0.363516 | 3.13019e-05 | 0.0110966 | 8.95214e-06 | 1(Win) | true |
| glaze | 1761.68 | 0.247117 | 8506.93ms | 1225970 | 320 | 8.60722e+08 | 663672 | 0.230299 | 2.85491 | 6.13737 | 0.608707 | 0.000252071 | 0.00992288 | 3.51023e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1705.08 | 0.0735393 | 6107.22ms | 409725 | 40 | 1.13604e+06 | 229165 | 0.00957371 | 2.96335 | 13.4537 | 2.49239 | 0.012892 | 0.0253335 | 4.77149e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1421.84 | 0.240742 | 7241.16ms | 409725 | 320 | 1.40067e+08 | 274815 | 0.0338806 | 3.55319 | 15.9102 | 2.9098 | 0.01476 | 0.0538795 | 3.14388e-05 | 2(Loss) | true |
| glaze | 1196.4 | 0.239225 | 8549.56ms | 409725 | 80 | 4.88355e+07 | 326600 | 0.171765 | 4.2052 | 17.1501 | 3.43165 | 0.0254337 | 0.0123268 | 7.51724e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1073.6 | 0.115307 | 9499.44ms | 409725 | 1280 | 2.25432e+08 | 363956 | 0.055401 | 4.69739 | 18.4884 | 3.34088 | 0.0137516 | 0.0605175 | 0.000184642 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2626.59 | 0.0984565 | 5224.87ms | 409725 | 40 | 858126 | 148765 | 0.0808919 | 1.9238 | 10.0044 | 1.72579 | 0.00719946 | 0.0016148 | 5.67454e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2027.69 | 0.280312 | 6345.51ms | 409725 | 320 | 9.33718e+07 | 192704 | 0.0968424 | 2.4824 | 12.4633 | 2.14399 | 0.00880211 | 0.0116216 | 4.4748e-05 | 2(Loss) | true |
| glaze | 1510.18 | 0.0728772 | 8066.74ms | 409725 | 1280 | 4.55118e+07 | 258741 | 0.0688532 | 3.32868 | 14.1999 | 2.7661 | 0.0204146 | 0.00117135 | 2.24655e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1395.73 | 0.0782498 | 8484.05ms | 409725 | 640 | 3.07135e+07 | 279957 | 0.146202 | 3.61915 | 15.4181 | 2.64064 | 0.00579841 | 0.0126055 | 1.40224e-05 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14392.2 | 0.0528935 | 3467.04ms | 409725 | 2560 | 527932 | 27149.8 | 0.0205113 | 0.34868 | 1.70961 | 0.290519 | 0.000380705 | 0.000502384 | 4.89848e-06 | 1(Win) | true |
| glaze | 3433.79 | 0.375574 | 6216.53ms | 409725 | 1280 | 2.33797e+08 | 113794 | 0.0177565 | 1.45857 | 5.49029 | 0.863145 | 0.0108633 | 0.0304593 | 2.7078e-05 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14471.7 | 0.0804203 | 3465.61ms | 409725 | 320 | 150879 | 27000.6 | 0.0740639 | 0.347723 | 1.70827 | 0.290217 | 0.000378325 | 0.000457815 | 7.9474e-06 | 1(Win) | true |
| glaze | 3842.75 | 0.383826 | 5637.11ms | 409725 | 1280 | 1.94976e+08 | 101684 | 1.37825 | 1.31339 | 5.47384 | 0.859369 | 0.010816 | 0.00145039 | 2.49443e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2413.11 | 0.194427 | 8152.57ms | 785750 | 320 | 1.16648e+08 | 310533 | 0.00066016 | 2.07748 | 8.96228 | 1.5448 | 0.00872818 | 0.0536058 | 1.50811e-05 | 1(Win) | true |
| jsonifier | 2195.14 | 0.128551 | 8912.55ms | 785750 | 640 | 1.23247e+08 | 341368 | 0.0613642 | 2.29572 | 9.6271 | 1.9536 | 0.00715234 | 0.0277057 | 2.83348e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1935.27 | 0.0950069 | 5035.11ms | 785750 | 320 | 4.33059e+07 | 387207 | 0.0671066 | 2.60206 | 10.2449 | 1.77026 | 0.00817939 | 0.0548908 | 3.68159e-05 | 3(Loss) | true |
| glaze | 1835.27 | 0.166475 | 5287.79ms | 785750 | 320 | 1.47848e+08 | 408305 | 0.119438 | 2.74946 | 11.7672 | 2.33247 | 0.0133945 | 0.0192634 | 4.41855e-05 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3331.9 | 0.184443 | 7217.05ms | 785750 | 320 | 5.50626e+07 | 224901 | 0.0489134 | 1.50096 | 7.16118 | 1.14463 | 0.0053424 | 0.0207642 | 1.22972e-05 | 1(Win) | true |
| jsonifier | 2905.93 | 0.0632354 | 7976.91ms | 785750 | 640 | 1.70176e+07 | 257869 | 0.0804158 | 1.73801 | 7.82924 | 1.55424 | 0.00426348 | 0.00364041 | 2.30075e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2461.24 | 0.250014 | 9087.21ms | 785750 | 80 | 4.63531e+07 | 304460 | 0.087222 | 2.04342 | 8.64833 | 1.4062 | 0.00382752 | 0.0217077 | 2.66465e-05 | 3(Loss) | true |
| glaze | 2218.25 | 0.249402 | 5029.96ms | 785750 | 640 | 4.54287e+08 | 337812 | 0.181619 | 2.26868 | 10.2299 | 1.98564 | 0.0105955 | 0.00594711 | 3.81403e-06 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18725.9 | 0.0554667 | 4775.54ms | 785750 | 160 | 78825.3 | 40016.6 | 0.000421698 | 0.270045 | 1.00864 | 0.151452 | 0.000227187 | 0.00539394 | 9.71206e-06 | 1(Win) | true |
| glaze | 3993.59 | 0.188312 | 9999.43ms | 785750 | 640 | 7.99056e+07 | 187638 | 0.132953 | 1.25056 | 4.39975 | 0.80026 | 0.00642986 | 0.0535862 | 3.42825e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18779.5 | 0.0202659 | 4769.37ms | 785750 | 1280 | 83703.5 | 39902.6 | 0.0596742 | 0.2692 | 1.0082 | 0.151359 | 0.000199472 | 0.00508347 | 4.01487e-06 | 1(Win) | true |
| glaze | 4659.09 | 0.0403328 | 8648.74ms | 785750 | 2560 | 1.07727e+07 | 160836 | 0.024554 | 1.08479 | 4.39068 | 0.798136 | 0.00641454 | 0.0110532 | 4.95019e-05 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 6995.09 | 0.0292126 | 4353.96ms | 264040 | 4890 | 540757 | 35997.9 | 0.0257689 | 0.72171 | 3.38793 | 0.446167 | 0.00119995 | 9.35596e-06 | 6.71259e-06 | 1(Win) | true |
| jsonifier | 6944.53 | 0.0278025 | 4386.54ms | 264040 | 4890 | 496969 | 36259.9 | 0.027473 | 0.726525 | 3.40139 | 0.449777 | 0.00125075 | 9.2909e-06 | 7.00768e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5617.71 | 0.0409824 | 5221.91ms | 264040 | 2560 | 863884 | 44824 | 0.0260069 | 0.897414 | 4.13828 | 0.458675 | 0.000695135 | 1.1532e-05 | 8.74187e-06 | 3(Loss) | true |
| glaze | 3448.95 | 0.0605231 | 8046.63ms | 264040 | 80 | 156206 | 73010.1 | 0.0638032 | 1.466 | 6.4884 | 1.20317 | 0.00304263 | 2.31972e-06 | 1.56226e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7166.62 | 0.0322812 | 4409.61ms | 264040 | 2560 | 329344 | 35136.3 | 0.165186 | 0.704213 | 3.32873 | 0.43223 | 0.00119364 | 5.50639e-06 | 3.71777e-06 | 1(Win) | true |
| jsonifier | 7140.51 | 0.0516653 | 4402.97ms | 264040 | 320 | 106226 | 35264.7 | 0.0119705 | 0.708377 | 3.34139 | 0.435586 | 0.00122332 | 3.88199e-06 | 2.46175e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5756.69 | 0.0592721 | 5203.9ms | 264040 | 4890 | 3.28703e+06 | 43741.8 | 0.00308975 | 0.876722 | 4.0658 | 0.443745 | 0.000714881 | 3.62389e-06 | 1.69848e-06 | 3(Loss) | true |
| glaze | 3516.38 | 0.0284523 | 7979.84ms | 264040 | 1280 | 531363 | 71610 | 0.0252866 | 1.44215 | 6.40557 | 1.18437 | 0.00294635 | 1.83743e-05 | 1.42201e-05 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 9073.41 | 0.0429998 | 4970.95ms | 399947 | 2560 | 836442 | 42037 | 0.232721 | 0.554513 | 2.77646 | 0.312639 | 0.000754807 | 6.50184e-06 | 4.97625e-06 | 1(Win) | true |
| jsonifier | 9055.39 | 0.0416976 | 4961ms | 399947 | 2560 | 789682 | 42120.7 | 0.0903793 | 0.556491 | 2.77925 | 0.313289 | 0.000770343 | 1.38446e-05 | 1.11167e-05 | 2(Loss) | true |
| simdjson (ondemand) | 7418.08 | 0.0360181 | 5880.32ms | 399947 | 2560 | 878019 | 51417.5 | 0.019236 | 0.678195 | 3.16623 | 0.320976 | 0.000415143 | 4.07085e-06 | 2.69469e-06 | 3(Loss) | true |
| glaze | 4436.06 | 0.0223352 | 9385.41ms | 399947 | 1280 | 472061 | 85981.5 | 0.0527071 | 1.13937 | 5.6002 | 1.05148 | 0.00205299 | 5.8621e-06 | 3.96342e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 9272.32 | 0.0309824 | 4937.98ms | 399947 | 4890 | 794268 | 41135.2 | 0.0429202 | 0.543273 | 2.73792 | 0.303608 | 0.000736882 | 5.11162e-06 | 3.83589e-06 | 1(Win) | true |
| jsonifier | 9197.24 | 0.0513975 | 5046.1ms | 399947 | 2560 | 1.16309e+06 | 41471.1 | 0.0151561 | 0.545261 | 2.74049 | 0.304188 | 0.000771865 | 3.22504e-06 | 2.05105e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7532.74 | 0.0219687 | 5870.91ms | 399947 | 4890 | 605085 | 50634.8 | 0.15081 | 0.669374 | 3.13268 | 0.314311 | 0.000447331 | 8.85854e-06 | 6.97434e-06 | 3(Loss) | true |
| glaze | 4492.45 | 0.0598672 | 9366.39ms | 399947 | 80 | 206683 | 84902.2 | 0.106568 | 1.12514 | 5.54606 | 1.03925 | 0.00201927 | 1.84399e-06 | 1.00013e-06 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2034.26 | 0.0541927 | 6731.07ms | 264040 | 640 | 2.87996e+06 | 123783 | 0.0704893 | 2.4839 | 8.05106 | 1.45498 | 0.0110222 | 5.29039e-05 | 1.36876e-05 | 1(Win) | true |
| glaze | 1945.48 | 0.0526044 | 7029.13ms | 264040 | 320 | 1.48347e+06 | 129432 | 0.101558 | 2.59783 | 9.98349 | 1.79699 | 0.00973498 | 4.12106e-05 | 2.18362e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1873.16 | 0.0372164 | 7259.73ms | 264040 | 2560 | 6.40764e+06 | 134429 | 0.180844 | 2.6832 | 9.12544 | 1.52606 | 0.0129966 | 0.00213937 | 5.48242e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1754.52 | 0.0471602 | 7721.02ms | 264040 | 2560 | 1.17277e+07 | 143520 | 0.0704393 | 2.87405 | 10.1037 | 1.53932 | 0.0109931 | 0.00195729 | 9.13687e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2594.75 | 0.0470211 | 6070.55ms | 264040 | 640 | 1.33265e+06 | 97045.4 | 0.00232178 | 1.93807 | 7.72915 | 1.20562 | 0.00419021 | 7.07753e-05 | 1.39479e-05 | 1(Win) | true |
| jsonifier | 2590.27 | 0.0279738 | 6153.6ms | 264040 | 2560 | 1.89317e+06 | 97212.9 | 0.105452 | 1.95096 | 6.64347 | 1.13208 | 0.00804588 | 3.27572e-05 | 2.14205e-05 | 2(Loss) | true |
| glaze | 2419.19 | 0.0483919 | 6404.12ms | 264040 | 640 | 1.62377e+06 | 104088 | 0.0854953 | 2.07816 | 8.56603 | 1.4707 | 0.00692397 | 1.14566e-05 | 7.65746e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2164.54 | 0.0547847 | 7103.13ms | 264040 | 2560 | 1.03985e+07 | 116334 | 0.0648508 | 2.31879 | 8.76108 | 1.23227 | 0.00759576 | 0.000139062 | 2.24398e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20594.4 | 0.063632 | 1968.12ms | 264040 | 320 | 19370.6 | 12227 | 0.017536 | 0.246132 | 1.02545 | 0.155601 | 2.2712e-05 | 6.05969e-06 | 2.79314e-06 | 1(Win) | true |
| glaze | 6019.6 | 0.155276 | 4940.73ms | 263923 | 2560 | 1.07911e+07 | 41812.8 | 0.208034 | 0.839237 | 2.25774 | 0.340118 | 0.000472951 | 0.00071421 | 2.39801e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20563.5 | 0.0244621 | 1967.39ms | 264040 | 4890 | 43877.2 | 12245.4 | 0.136695 | 0.245585 | 1.02343 | 0.155151 | 1.98535e-05 | 1.20241e-05 | 5.43699e-06 | 1(Win) | true |
| glaze | 6892.77 | 0.302622 | 4388.94ms | 263923 | 1280 | 1.56306e+07 | 36516 | 0.029587 | 0.732517 | 2.23442 | 0.33478 | 0.00044485 | 1.28885e-05 | 7.09546e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2609.26 | 0.0561351 | 7879.94ms | 399947 | 2560 | 1.72378e+07 | 146179 | 0.11898 | 1.92233 | 6.55423 | 1.02785 | 0.00899451 | 0.00370486 | 6.77287e-05 | 1(Win) | true |
| simdjson (ondemand) | 2501.61 | 0.108522 | 8190.78ms | 399947 | 640 | 1.75218e+07 | 152470 | 0.00772123 | 2.00294 | 7.11799 | 1.03749 | 0.00764591 | 0.00410175 | 9.0262e-05 | 2(Loss) | true |
| glaze | 2339.63 | 0.118576 | 8721.83ms | 399947 | 80 | 2.98946e+06 | 163025 | 0.154816 | 2.15928 | 8.43776 | 1.52859 | 0.00772524 | 0.000719095 | 4.44746e-05 | 3(Loss) | true |
| jsonifier | 1981.59 | 0.0386427 | 5108.31ms | 399947 | 1280 | 7.08147e+06 | 192481 | 0.0515595 | 2.55151 | 7.04539 | 1.38115 | 0.00770209 | 0.00225861 | 5.60816e-05 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3227.25 | 0.10375 | 7287.26ms | 399947 | 640 | 9.62264e+06 | 118187 | 0.123294 | 1.5583 | 5.63101 | 0.81605 | 0.00686476 | 0.000169186 | 8.92306e-06 | 1(Win) | true |
| simdjson (ondemand) | 3082.93 | 0.0550307 | 7525.84ms | 399947 | 1280 | 5.93332e+06 | 123720 | 0.167957 | 1.63557 | 6.23009 | 0.834119 | 0.00537232 | 0.000318073 | 3.00723e-05 | 2(Loss) | true |
| glaze | 2707.25 | 0.0451719 | 8421.19ms | 399947 | 640 | 2.59218e+06 | 140888 | 0.0168158 | 1.86801 | 7.50808 | 1.31536 | 0.00745204 | 1.44121e-05 | 6.92279e-06 | 3(Loss) | true |
| jsonifier | 2292.98 | 0.0145785 | 9692.64ms | 399947 | 2560 | 1.50546e+06 | 166342 | 0.0825916 | 2.20287 | 6.11909 | 1.16876 | 0.00591741 | 0.000312881 | 4.76421e-05 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22846.7 | 0.0513037 | 2422.37ms | 399947 | 1280 | 93899.5 | 16694.7 | 0.0896749 | 0.221393 | 0.773475 | 0.105709 | 2.24815e-05 | 1.09995e-05 | 5.95977e-06 | 1(Win) | true |
| glaze | 5573.28 | 0.354749 | 7680.88ms | 399830 | 160 | 9.42524e+06 | 68417.1 | 0.0531474 | 0.902662 | 2.52477 | 0.458635 | 0.000725371 | 0.00529355 | 1.0692e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22957.7 | 0.0478424 | 2416.69ms | 399947 | 30 | 1895.38 | 16614 | 0.0865988 | 0.220834 | 0.772177 | 0.105416 | 2.45866e-05 | 2.0086e-05 | 1.39185e-05 | 1(Win) | true |
| glaze | 6433.12 | 0.105726 | 6684.72ms | 399830 | 2560 | 1.00534e+07 | 59272.6 | 0.052782 | 0.786075 | 2.5091 | 0.454951 | 0.000719135 | 4.67542e-05 | 2.66178e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1015.29 | 0.110383 | 1171.9ms | 4630 | 320 | 7374.63 | 4349.02 | 0.0986108 | 5.02192 | 22.751 | 4.62506 | 0.00789552 | 3.84719e-05 | 1.2824e-05 | 1(Win) | true |
| jsonifier (two-stage) | 940.371 | 0.0582345 | 1208.46ms | 4630 | 1280 | 9570.49 | 4695.5 | 0.0195039 | 5.42595 | 25.3015 | 4.92009 | 0.00738188 | 0.00013482 | 6.69884e-05 | 2(Loss) | true |
| glaze | 763.209 | 0.0400746 | 1311.86ms | 4630 | 2560 | 13761.1 | 5785.46 | 0.0435886 | 6.65374 | 28.9333 | 5.69611 | 0.00521379 | 8.20059e-05 | 3.63627e-05 | 3(Loss) | true |
| simdjson (ondemand) | 719.214 | 0.0563575 | 1360.29ms | 4630 | 2560 | 30647 | 6139.36 | 0.107362 | 7.09955 | 30.4257 | 5.39741 | 0.00475516 | 0.000165531 | 9.8964e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1251.58 | 0.0783271 | 1177.87ms | 4630 | 80 | 610.884 | 3527.95 | 0.0113393 | 4.0894 | 18.4883 | 3.63132 | 0.00738661 | 3.50972e-05 | 1.34989e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1159.91 | 0.0320507 | 1214.81ms | 4630 | 4890 | 7279.4 | 3806.76 | 0.0752303 | 4.40469 | 21.0391 | 3.927 | 0.00586594 | 4.26665e-05 | 1.02912e-05 | 2(Loss) | true |
| glaze | 903.978 | 0.0296686 | 1315.82ms | 4630 | 4890 | 10269.5 | 4884.54 | 0.00697057 | 5.63839 | 24.5791 | 4.68121 | 0.00449531 | 7.08459e-05 | 2.82235e-05 | 3(Loss) | true |
| simdjson (ondemand) | 835.521 | 0.0977167 | 1364.26ms | 4630 | 1280 | 34134.6 | 5284.74 | 0.011027 | 6.12345 | 27.2855 | 4.65659 | 0.00234054 | 0.000111197 | 5.83828e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1639.29 | 0.225161 | 999.835ms | 4630 | 40 | 1471.28 | 2693.55 | 0.0884048 | 3.13105 | 7.9095 | 0.449244 | 0.000215983 | 8.09935e-05 | 0 | 1(Win) | true |
| glaze | 967.155 | 0.0893144 | 1195ms | 4630 | 30 | 498.809 | 4565.47 | 0.0167956 | 5.28389 | 9.73866 | 0.675162 | 0.000223182 | 2.87977e-05 | 0 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1659.14 | 0.0969699 | 999.208ms | 4630 | 640 | 4262.36 | 2661.33 | 0.0587355 | 3.10853 | 7.83888 | 0.432398 | 0.00036987 | 5.16334e-05 | 1.65362e-05 | 1(Win) | true |
| glaze | 1012.98 | 0.0721614 | 1170.79ms | 4630 | 1280 | 12664.2 | 4358.92 | 0.0455093 | 5.06994 | 9.25205 | 0.565876 | 0.000219526 | 5.02835e-05 | 2.63229e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2675.34 | 0.0614875 | 1266.73ms | 14795 | 320 | 3365.07 | 5273.94 | 0.0449344 | 1.90418 | 8.72977 | 1.57479 | 0.00236228 | 1.4363e-05 | 3.59074e-06 | 1(Win) | true |
| jsonifier | 2562.04 | 0.0718995 | 1292.42ms | 14795 | 1280 | 20068.8 | 5507.18 | 0.00451095 | 1.98543 | 9.20061 | 1.93991 | 0.00363008 | 6.84881e-05 | 4.48314e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2067.43 | 0.0401465 | 1426.13ms | 14795 | 2560 | 19217.7 | 6824.7 | 0.0218464 | 2.45813 | 10.5114 | 1.75708 | 0.00172596 | 1.54983e-05 | 5.88776e-06 | 3(Loss) | true |
| glaze | 1874.75 | 0.0448425 | 1488.31ms | 14795 | 1280 | 14579.2 | 7526.13 | 0.0313393 | 2.70752 | 12.0105 | 2.34742 | 0.00489703 | 1.92738e-05 | 6.86465e-06 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3253.35 | 0.0986337 | 1266.42ms | 14795 | 40 | 731.946 | 4336.95 | 0.0488293 | 1.57351 | 7.39878 | 1.26448 | 0.00166103 | 1.68976e-05 | 0 | 1(Win) | true |
| jsonifier | 3065.66 | 0.122704 | 1298.05ms | 14795 | 40 | 1275.74 | 4602.48 | 0.000905318 | 1.66499 | 7.87225 | 1.63028 | 0.00321392 | 4.05542e-05 | 1.01386e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2394.95 | 0.0251022 | 1428.23ms | 14795 | 4890 | 10694.7 | 5891.39 | 0.0759876 | 2.12361 | 9.46644 | 1.51477 | 0.000618362 | 1.55223e-05 | 4.07754e-06 | 3(Loss) | true |
| glaze | 2110.95 | 0.025427 | 1501.97ms | 14795 | 4890 | 14124.6 | 6684.01 | 0.200742 | 2.40787 | 10.6621 | 2.03359 | 0.0044612 | 1.86046e-05 | 5.33536e-06 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3935.18 | 0.0855304 | 1101.09ms | 14795 | 1280 | 12037.9 | 3585.51 | 0.0452137 | 1.29809 | 2.56925 | 0.143968 | 6.86465e-05 | 9.13527e-06 | 1.74257e-06 | 1(Win) | true |
| glaze | 3405.1 | 0.0555298 | 1154.86ms | 14795 | 2560 | 13553.8 | 4143.67 | 0.0399866 | 1.49867 | 4.39682 | 0.530788 | 0.000948589 | 1.54719e-05 | 4.27721e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4474.51 | 0.0869998 | 1055.06ms | 14795 | 2560 | 19267.1 | 3153.33 | 0.171081 | 1.14343 | 2.53187 | 0.135451 | 6.82769e-05 | 1.40197e-05 | 4.59404e-06 | 1(Win) | true |
| glaze | 3690.78 | 0.0888626 | 1120.95ms | 14795 | 4890 | 56434 | 3822.94 | 0.0628903 | 1.38238 | 4.20433 | 0.486313 | 0.0010113 | 9.55112e-06 | 2.69532e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1920 | 0.100874 | 994.922ms | 5092 | 640 | 4165.94 | 2529.23 | 0.0179741 | 2.67439 | 10.9813 | 2.06304 | 0.00104637 | 2.05592e-05 | 1.53427e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1536.41 | 0.0941266 | 1058.24ms | 5092 | 160 | 1416.15 | 3160.69 | 0.000988717 | 3.33556 | 13.7777 | 2.43323 | 0.00124092 | 3.43676e-05 | 0 | 2(Loss) | true |
| glaze | 1502.71 | 0.0516188 | 1066.22ms | 5092 | 2560 | 7123.31 | 3231.56 | 0.0473497 | 3.40741 | 14.2203 | 2.73743 | 0.00138031 | 4.83295e-05 | 1.72605e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1232 | 0.0329906 | 1138.78ms | 5092 | 4890 | 8268.81 | 3941.64 | 0.0202261 | 4.14694 | 15.5226 | 2.64336 | 0.00191945 | 6.14059e-05 | 2.36146e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2361.41 | 0.0827537 | 985.687ms | 5092 | 640 | 1853.49 | 2056.45 | 0.0538993 | 2.18407 | 9.34643 | 1.66006 | 0.00103318 | 2.02524e-05 | 9.20562e-07 | 1(Win) | true |
| jsonifier (two-stage) | 1832.65 | 0.0556833 | 1048.61ms | 5092 | 320 | 696.656 | 2649.78 | 0.00318433 | 2.8034 | 12.1426 | 2.03024 | 0.0011863 | 2.33209e-05 | 0 | 2(Loss) | true |
| glaze | 1770.95 | 0.047581 | 1058.04ms | 5092 | 4890 | 8324.19 | 2742.1 | 0.0325391 | 2.90244 | 12.5309 | 2.32542 | 0.000613417 | 9.75507e-05 | 4.78316e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1436.72 | 0.0376353 | 1140.74ms | 5092 | 2560 | 4142.54 | 3380.01 | 0.0204169 | 3.56573 | 13.8274 | 2.23095 | 0.00185677 | 5.60008e-05 | 1.51893e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8719.41 | 0.0439763 | 793.121ms | 5092 | 1280 | 76.7803 | 556.931 | 0.115735 | 0.62155 | 2.29517 | 0.398075 | 0.000196386 | 1.59564e-05 | 3.37539e-06 | 1(Win) | true |
| glaze | 3487.24 | 0.393018 | 882.469ms | 5092 | 320 | 9584.9 | 1392.54 | 0.354474 | 1.49103 | 4.5978 | 0.70169 | 0.000199455 | 3.49813e-05 | 5.52337e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9487.66 | 0.0766376 | 789.132ms | 5092 | 4890 | 752.404 | 511.834 | 0.00923166 | 0.574261 | 2.18873 | 0.373724 | 0.000196748 | 3.53817e-05 | 1.1486e-05 | 1(Win) | true |
| glaze | 3987.64 | 0.173816 | 861.506ms | 5092 | 2560 | 11470 | 1217.79 | 0.04451 | 1.30988 | 4.10075 | 0.593087 | 0.000199302 | 2.91511e-05 | 6.36722e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3115.77 | 0.0893349 | 1100.39ms | 11724 | 80 | 822.151 | 3588.47 | 0.0661403 | 1.64207 | 6.8051 | 1.0969 | 0.000492579 | 2.66547e-05 | 1.17281e-05 | 1(Win) | true |
| jsonifier | 2627.91 | 0.0400776 | 1168.89ms | 11724 | 4890 | 14218.2 | 4254.66 | 0.00924889 | 1.94145 | 7.41726 | 1.52107 | 0.000880598 | 1.89254e-05 | 7.50039e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2597.16 | 0.0476675 | 1174.93ms | 11724 | 1280 | 5390.25 | 4305.04 | 0.0792578 | 1.96514 | 7.47356 | 1.18304 | 0.000860681 | 1.79253e-05 | 3.59839e-06 | 3(Loss) | true |
| glaze | 2328.88 | 0.0453263 | 1222.48ms | 11724 | 2560 | 12122.7 | 4800.97 | 0.0120811 | 2.1894 | 9.12828 | 1.77465 | 0.00130065 | 2.11239e-05 | 7.36337e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3643.26 | 0.133452 | 1093.28ms | 11724 | 40 | 670.943 | 3068.93 | 0.00298702 | 1.40747 | 6.09493 | 0.92187 | 0.000648243 | 3.19857e-05 | 2.13238e-06 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 2993.89 | 0.104117 | 1177.01ms | 11724 | 160 | 2419.05 | 3734.57 | 0.0242606 | 1.70847 | 6.7436 | 1.00486 | 0.000815635 | 1.59928e-05 | 0 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 2989.4 | 0.0543395 | 1164.7ms | 11724 | 80 | 330.45 | 3740.18 | 0.102163 | 1.71061 | 6.70684 | 1.34596 | 0.000888135 | 1.91914e-05 | 7.46332e-06 | 2(Tie) | true |
| glaze | 2627.22 | 0.0495815 | 1207.26ms | 11724 | 2560 | 11398.3 | 4255.78 | 0.0376001 | 1.94147 | 8.39449 | 1.5957 | 0.00121102 | 2.00244e-05 | 5.7974e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16690.2 | 0.0898041 | 802.948ms | 11724 | 1280 | 463.266 | 669.906 | 0.0818008 | 0.322108 | 1.14057 | 0.179034 | 0.000131474 | 1.22612e-05 | 4.86449e-06 | 1(Win) | true |
| glaze | 3876.17 | 0.152771 | 1032.22ms | 11746 | 4890 | 95316.1 | 2889.93 | 0.0589523 | 1.32234 | 3.54359 | 0.650094 | 0.000557593 | 1.78279e-05 | 4.40475e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18281.4 | 0.0821839 | 798.545ms | 11724 | 640 | 161.69 | 611.597 | 0.105656 | 0.29519 | 1.0934 | 0.168287 | 8.54284e-05 | 1.19946e-05 | 4.79785e-06 | 1(Win) | true |
| glaze | 4425.45 | 0.169482 | 992.257ms | 11746 | 2560 | 47114.3 | 2531.23 | 0.323811 | 1.1602 | 3.30192 | 0.594592 | 0.000516133 | 1.31694e-05 | 2.09513e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2085.7 | 0.0405428 | 963.614ms | 4857 | 4890 | 3964.31 | 2220.83 | 0.0601981 | 2.47146 | 9.30039 | 1.75417 | 0.000684526 | 4.52618e-05 | 1.28417e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1791.87 | 0.0874781 | 1001.03ms | 4857 | 160 | 818.164 | 2585 | 0.0517676 | 2.86752 | 11.3607 | 2.00371 | 0.000654982 | 2.57361e-05 | 1.2868e-06 | 2(Loss) | true |
| glaze | 1774.1 | 0.0789893 | 997.099ms | 4857 | 1280 | 5444.13 | 2610.9 | 0.121514 | 2.89146 | 11.7941 | 2.23657 | 0.000282614 | 6.30533e-05 | 2.73446e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1458.43 | 0.0943043 | 1057.07ms | 4857 | 2560 | 22965 | 3176.01 | 0.175054 | 3.50766 | 13.3585 | 2.21598 | 0.000474106 | 8.0023e-05 | 3.33764e-05 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2754.24 | 0.0520148 | 937.241ms | 4857 | 4890 | 3741.93 | 1681.77 | 0.0681294 | 1.88094 | 7.16553 | 1.25963 | 0.000484869 | 5.25036e-05 | 1.59574e-05 | 1(Win) | true |
| glaze | 2538.24 | 0.20771 | 947.171ms | 4857 | 80 | 1149.42 | 1824.89 | 0.0226092 | 2.03782 | 8.87173 | 1.58678 | 0.00109893 | 4.37513e-05 | 2.57361e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2246.53 | 0.0782213 | 975.107ms | 4857 | 1280 | 3329.45 | 2061.85 | 0.0094718 | 2.31375 | 9.39572 | 1.54334 | 0.000767417 | 4.02126e-05 | 1.49591e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1933.31 | 0.0390106 | 1006.82ms | 4857 | 4890 | 4271.78 | 2395.89 | 0.107021 | 2.65988 | 10.818 | 1.6609 | 0.00117411 | 4.63565e-05 | 1.11997e-05 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10189.1 | 0.111003 | 775.976ms | 4857 | 2560 | 651.888 | 454.602 | 0.00464027 | 0.551349 | 1.67078 | 0.291126 | 0.00041057 | 4.88985e-05 | 1.71306e-05 | 1(Win) | true |
| glaze | 3756.62 | 0.25729 | 857.687ms | 4857 | 4890 | 49214.8 | 1233.02 | 0.0812328 | 1.40114 | 3.80276 | 0.633725 | 0.000209046 | 5.21247e-05 | 1.37259e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12039.5 | 0.112114 | 766.872ms | 4857 | 30 | 5.58161 | 384.733 | 0.155709 | 0.470791 | 1.54437 | 0.260037 | 0.000205888 | 0 | 0 | 1(Win) | true |
| glaze | 4137.12 | 0.159597 | 844.202ms | 4857 | 4890 | 15613.4 | 1119.62 | 0.140383 | 1.27548 | 3.32777 | 0.524398 | 0.000230435 | 4.29882e-05 | 1.3347e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2556.47 | 0.0417033 | 1005.78ms | 7376 | 4890 | 6438.87 | 2751.57 | 0.048543 | 2.01548 | 8.06033 | 1.34572 | 0.00017622 | 4.11715e-05 | 1.99897e-05 | 1(Win) | true |
| glaze | 2233.63 | 0.181658 | 1055.7ms | 7376 | 30 | 981.857 | 3149.27 | 0.0423558 | 2.33477 | 9.90401 | 1.95567 | 0.00059201 | 3.61533e-05 | 4.51916e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2132.35 | 0.0725449 | 1064.79ms | 7376 | 1280 | 7330.73 | 3298.84 | 0.0429549 | 2.39832 | 9.26166 | 1.48143 | 0.000292651 | 4.10961e-05 | 1.6735e-05 | 3(Loss) | true |
| jsonifier | 1999.2 | 0.0538831 | 1089.38ms | 7376 | 2560 | 9201.88 | 3518.57 | 0.0902949 | 2.57869 | 8.67625 | 1.80057 | 0.00172503 | 9.44258e-05 | 5.26412e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3160.67 | 0.189329 | 984.52ms | 7376 | 40 | 710.199 | 2225.57 | 0.0220868 | 1.62977 | 6.74024 | 1.03823 | 0.000454176 | 3.05043e-05 | 0 | 1(Win) | true |
| glaze | 2932.7 | 0.0449855 | 1000.31ms | 7376 | 4890 | 5693.27 | 2398.58 | 0.136415 | 1.76687 | 7.96773 | 1.52576 | 0.0011235 | 2.45088e-05 | 8.51155e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2794.62 | 0.116159 | 1012.38ms | 7376 | 80 | 683.904 | 2517.09 | 0.0699724 | 1.83939 | 7.56847 | 1.11185 | 0.000891405 | 2.88097e-05 | 3.38937e-06 | 3(Loss) | true |
| jsonifier | 2382.99 | 0.151342 | 1054.72ms | 7376 | 40 | 798.317 | 2951.88 | 0.0172237 | 2.15547 | 7.31087 | 1.48387 | 0.00164046 | 3.38937e-05 | 3.38937e-06 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13972.8 | 0.0695329 | 785.438ms | 7376 | 4890 | 599.187 | 503.427 | 0.376298 | 0.393183 | 1.20255 | 0.192381 | 0.000135769 | 2.11818e-05 | 6.7926e-06 | 1(Win) | true |
| glaze | 3279.86 | 0.120608 | 950.936ms | 7376 | 4890 | 32718.6 | 2144.7 | 0.179949 | 1.57643 | 3.90428 | 0.704176 | 0.000357929 | 9.17417e-05 | 5.30932e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16643 | 0.0680322 | 775.489ms | 7376 | 1280 | 105.831 | 422.657 | 0.0570837 | 0.336691 | 1.11931 | 0.173807 | 0.000135787 | 2.10777e-05 | 1.05918e-05 | 1(Win) | true |
| glaze | 3653.07 | 0.321281 | 925.583ms | 7376 | 640 | 24494.9 | 1925.59 | 0.18356 | 1.41087 | 3.5884 | 0.632593 | 0.000341055 | 1.4193e-05 | 1.27101e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2471.23 | 0.0334288 | 900.466ms | 4390 | 4890 | 1568.38 | 1694.15 | 0.10602 | 2.09647 | 9.8303 | 1.74556 | 0.0011601 | 4.08066e-05 | 1.84468e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1863.71 | 0.0780015 | 960.864ms | 4390 | 160 | 491.248 | 2246.4 | 0.0189227 | 2.82064 | 13.1838 | 2.28747 | 0.0018992 | 3.13212e-05 | 4.27107e-06 | 2(Loss) | true |
| glaze | 1736.02 | 0.144372 | 969.701ms | 4390 | 640 | 7758.24 | 2411.62 | 0.0305256 | 2.95712 | 13.628 | 2.66674 | 0.000843892 | 3.666e-05 | 1.77961e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1331.85 | 0.109089 | 1050.09ms | 4390 | 80 | 940.733 | 3143.46 | 0.080658 | 3.84536 | 16.4011 | 2.8533 | 0.00138667 | 2.2779e-05 | 0 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2920.76 | 0.0870483 | 895.312ms | 4390 | 2560 | 3985.62 | 1433.4 | 0.0908832 | 1.77758 | 8.63212 | 1.46447 | 0.00122073 | 2.96306e-05 | 1.15675e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2070.81 | 0.0403881 | 963.346ms | 4390 | 640 | 426.71 | 2021.73 | 0.00293693 | 2.49275 | 11.9847 | 2.00615 | 0.00188141 | 2.17113e-05 | 3.55923e-07 | 2(Loss) | true |
| glaze | 2033.78 | 0.0426026 | 962.224ms | 4390 | 4890 | 3761 | 2058.55 | 0.0293799 | 2.54038 | 12.1239 | 2.3328 | 0.000841241 | 3.33534e-05 | 1.11333e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1502.45 | 0.0512497 | 1031.86ms | 4390 | 1280 | 2610.48 | 2786.53 | 0.0959773 | 3.41466 | 15.0155 | 2.5451 | 0.000591543 | 4.39564e-05 | 1.10336e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10919.6 | 0.0591092 | 766.171ms | 4390 | 1280 | 65.7406 | 383.404 | 0.356021 | 0.510283 | 2.182 | 0.375171 | 0.000227968 | 1.40589e-05 | 2.3135e-06 | 1(Win) | true |
| glaze | 3731.82 | 0.646257 | 844.764ms | 4390 | 160 | 8410.45 | 1121.88 | 0.449226 | 1.40372 | 5.36128 | 0.84123 | 0.000484055 | 1.56606e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11966.7 | 0.0420511 | 760.696ms | 4390 | 1280 | 27.7041 | 349.856 | 0.250368 | 0.472445 | 2.06196 | 0.346925 | 0.00022779 | 7.29641e-06 | 2.3135e-06 | 1(Win) | true |
| glaze | 4107.7 | 0.168668 | 831.759ms | 4390 | 4890 | 14451.3 | 1019.22 | 0.0222076 | 1.28587 | 4.9549 | 0.749886 | 0.000465177 | 3.06981e-05 | 5.4502e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4084.89 | 0.111739 | 1006.87ms | 11521 | 1280 | 11562.2 | 2689.74 | 0.0311465 | 1.25745 | 5.98958 | 0.928392 | 0.001027 | 1.58678e-05 | 5.15363e-06 | 1(Win) | true |
| jsonifier | 3333.66 | 0.0721419 | 1068.57ms | 11521 | 1280 | 7236.42 | 3295.87 | 0.0257595 | 1.53328 | 6.43746 | 1.30805 | 0.00242512 | 9.49353e-06 | 1.96652e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3106.47 | 0.0596462 | 1093.43ms | 11521 | 4890 | 21763.1 | 3536.9 | 0.0354617 | 1.64992 | 7.06874 | 1.12968 | 0.000408945 | 1.52296e-05 | 4.89903e-06 | 3(Loss) | true |
| glaze | 2509.97 | 0.0813953 | 1169.69ms | 11521 | 320 | 4062.49 | 4377.45 | 0.0739752 | 2.03244 | 8.34337 | 1.65081 | 0.00392707 | 2.60394e-05 | 1.05785e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4554.02 | 0.0447012 | 1009.96ms | 11521 | 2560 | 2977.62 | 2412.65 | 0.053611 | 1.12922 | 5.53268 | 0.821196 | 0.00095054 | 1.06124e-05 | 1.59356e-06 | 1(Win) | true |
| jsonifier | 3644.6 | 0.0798563 | 1066.46ms | 11521 | 1280 | 7418.36 | 3014.67 | 0.329121 | 1.4164 | 5.9809 | 1.20111 | 0.00237501 | 1.62746e-05 | 8.0695e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3513.65 | 0.0584994 | 1072.25ms | 11521 | 2560 | 8566.58 | 3127.03 | 0.0239652 | 1.46624 | 6.51879 | 1.0079 | 0.000255105 | 1.47828e-05 | 2.13605e-06 | 3(Loss) | true |
| glaze | 2736.23 | 0.0605947 | 1162.33ms | 11521 | 1280 | 7577.98 | 4015.48 | 0.113382 | 1.86548 | 7.75766 | 1.52122 | 0.00415329 | 1.06463e-05 | 2.03433e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20354.8 | 0.118975 | 785.346ms | 11521 | 320 | 131.98 | 539.788 | 0.132977 | 0.266719 | 0.994792 | 0.141134 | 8.6798e-05 | 1.13922e-05 | 4.88239e-06 | 1(Win) | true |
| glaze | 4705.48 | 0.232023 | 973.015ms | 11521 | 2560 | 75140.6 | 2334.99 | 0.11139 | 1.10175 | 3.75228 | 0.683969 | 0.00115068 | 3.77707e-05 | 2.06823e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22474.5 | 0.100603 | 777.097ms | 11521 | 320 | 77.4052 | 488.878 | 0.0633227 | 0.243248 | 0.947314 | 0.130371 | 8.6798e-05 | 2.71244e-06 | 0 | 1(Win) | true |
| glaze | 5367.87 | 0.124734 | 939.627ms | 11521 | 1280 | 8343.63 | 2046.86 | 0.0658071 | 0.960425 | 3.50794 | 0.629807 | 0.00117198 | 1.60034e-05 | 5.42488e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2762.67 | 0.121669 | 893.502ms | 4669 | 80 | 307.639 | 1611.74 | 0.196603 | 1.87721 | 7.74984 | 1.53887 | 0.00111373 | 1.07089e-05 | 0 | 1(Win) | true |
| glaze | 2169.38 | 0.0812136 | 940.325ms | 4669 | 320 | 889.172 | 2052.53 | 0.00959091 | 2.37748 | 9.70358 | 1.7357 | 0.000817225 | 1.33862e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 1900.67 | 0.0724291 | 969.93ms | 4669 | 160 | 460.662 | 2342.71 | 0.0557893 | 2.71507 | 10.843 | 1.86592 | 0.00254203 | 2.00792e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1591.17 | 0.0325573 | 1021.11ms | 4669 | 4890 | 4059 | 2798.38 | 0.00623786 | 3.22202 | 13.7393 | 1.98522 | 0.00106796 | 4.10838e-05 | 9.15406e-06 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2991.2 | 0.132587 | 883.222ms | 4669 | 80 | 311.635 | 1488.6 | 0.331946 | 1.73752 | 7.29043 | 1.42643 | 0.00110837 | 5.35447e-06 | 0 | 1(Win) | true |
| glaze | 2449.08 | 0.12378 | 919.536ms | 4669 | 80 | 405.164 | 1818.11 | 0.0130647 | 2.11173 | 8.93939 | 1.5635 | 0.000597023 | 7.76398e-05 | 6.42536e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2045.31 | 0.174676 | 963.503ms | 4669 | 30 | 433.826 | 2177.03 | 0.0658822 | 2.53373 | 10.375 | 1.75198 | 0.00218462 | 6.42536e-05 | 4.28357e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1736.93 | 0.0550639 | 1002.49ms | 4669 | 2560 | 5101.02 | 2563.55 | 0.0206884 | 2.9558 | 12.9576 | 1.81174 | 0.00125136 | 3.01189e-05 | 2.84456e-06 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12792.4 | 0.24177 | 773.32ms | 4669 | 40 | 28.3276 | 348.075 | 0.0932836 | 0.440287 | 1.41551 | 0.363247 | 0.000214179 | 0 | 0 | 1(Win) | true |
| glaze | 3501.27 | 0.265837 | 869.786ms | 4669 | 320 | 3657.45 | 1271.74 | 0.0454387 | 1.49092 | 3.17498 | 0.482116 | 0.000214179 | 2.40951e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14489 | 0.0389093 | 765.076ms | 4669 | 4890 | 69.9175 | 307.316 | 0.0663277 | 0.395285 | 1.29942 | 0.33626 | 0.000214398 | 4.68215e-05 | 1.51984e-05 | 1(Win) | true |
| glaze | 4117.75 | 0.264752 | 843.588ms | 4669 | 4890 | 40079 | 1081.34 | 0.0224082 | 1.27325 | 2.70786 | 0.37567 | 0.000429146 | 2.56664e-05 | 9.02266e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3414.91 | 0.0536048 | 995.064ms | 9249 | 4890 | 9374.46 | 2582.94 | 0.0302959 | 1.50382 | 6.27192 | 0.994378 | 0.00066099 | 1.69587e-05 | 2.71958e-06 | 1(Win) | true |
| simdjson (ondemand) | 2918.51 | 0.065437 | 1044.53ms | 9249 | 160 | 625.798 | 3022.28 | 0.00206794 | 1.75603 | 7.56644 | 1.03038 | 0.000664937 | 1.55422e-05 | 0 | 2(Loss) | true |
| glaze | 2804.67 | 0.0562502 | 1054.64ms | 9249 | 2560 | 8011.52 | 3144.95 | 0.0906912 | 1.82625 | 7.67856 | 1.41583 | 0.00141548 | 2.72411e-05 | 1.18678e-05 | 3(Loss) | true |
| jsonifier | 2658.62 | 0.0366638 | 1067.08ms | 9249 | 2560 | 3787.86 | 3317.72 | 0.019788 | 1.92617 | 6.46394 | 1.4354 | 0.00130318 | 2.10749e-05 | 4.5613e-06 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3669.23 | 0.0396104 | 982.62ms | 9249 | 4890 | 4433.7 | 2403.92 | 0.144487 | 1.40018 | 6.03568 | 0.936858 | 0.000610026 | 1.7622e-05 | 5.63815e-06 | 1(Win) | true |
| simdjson (ondemand) | 3179.53 | 0.045093 | 1019.54ms | 9249 | 320 | 500.761 | 2774.16 | 0.0679722 | 1.61481 | 7.1718 | 0.942805 | 0.000621013 | 1.72316e-05 | 3.37874e-07 | 2(Loss) | true |
| glaze | 3043.1 | 0.0415402 | 1030.6ms | 9249 | 2560 | 3711.38 | 2898.54 | 0.197701 | 1.68503 | 7.29246 | 1.3289 | 0.00152808 | 2.1455e-05 | 8.53133e-06 | 3(Loss) | true |
| jsonifier | 2814.84 | 0.0288937 | 1066.36ms | 9249 | 4890 | 4008.64 | 3133.58 | 0.0169692 | 1.82298 | 6.22837 | 1.37788 | 0.00125065 | 1.75556e-05 | 2.67536e-06 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22622.2 | 0.0830537 | 762.672ms | 9249 | 640 | 67.1148 | 389.906 | 0.117152 | 0.247732 | 0.829279 | 0.182939 | 0.00010812 | 5.40599e-06 | 5.06812e-07 | 1(Win) | true |
| glaze | 4050.71 | 0.101227 | 954.626ms | 9249 | 4890 | 23758.8 | 2177.53 | 0.153873 | 1.27601 | 3.22565 | 0.619202 | 0.000375722 | 1.89044e-05 | 3.58188e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24648.7 | 0.12337 | 762.395ms | 9249 | 160 | 31.1849 | 357.85 | 0.0209629 | 0.22831 | 0.777057 | 0.170937 | 0.00010812 | 1.82452e-05 | 6.75749e-06 | 1(Win) | true |
| glaze | 4690.93 | 0.193516 | 922.255ms | 9249 | 1280 | 16947.8 | 1880.34 | 0.394889 | 1.1121 | 2.96994 | 0.56071 | 0.00037597 | 4.89918e-06 | 5.06812e-07 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 816.604 | 0.0612884 | 1277.51ms | 4604 | 1280 | 13900 | 5376.8 | 0.0659663 | 6.23577 | 24.4559 | 5.40964 | 0.00508593 | 7.72087e-05 | 3.0035e-05 | 1(Win) | true |
| jsonifier (two-stage) | 732.346 | 0.0731886 | 1342.83ms | 4604 | 640 | 12322.7 | 5995.41 | 0.0436081 | 6.94498 | 28.0615 | 5.85296 | 0.0056907 | 0.000121837 | 7.22877e-05 | 2(Loss) | true |
| glaze | 650.241 | 0.036206 | 1414.57ms | 4604 | 2560 | 15301.1 | 6752.45 | 0.15978 | 7.82599 | 32.7965 | 6.86881 | 0.00852621 | 8.86627e-05 | 4.36102e-05 | 3(Loss) | true |
| simdjson (ondemand) | 592.003 | 0.0298066 | 1487.51ms | 4604 | 2560 | 12510.8 | 7416.71 | 0.00684207 | 8.58509 | 35.3486 | 6.5543 | 0.00775735 | 0.000122007 | 6.007e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1001.97 | 0.060083 | 1274.97ms | 4604 | 80 | 554.572 | 4382.1 | 0.0142605 | 5.09639 | 20.0382 | 4.39162 | 0.00441464 | 5.15856e-05 | 5.43006e-06 | 1(Win) | true |
| jsonifier (two-stage) | 875.318 | 0.037006 | 1336.24ms | 4604 | 2560 | 8821.09 | 5016.14 | 0.0352347 | 5.80312 | 23.8521 | 4.88249 | 0.00450619 | 5.3537e-05 | 1.5866e-05 | 2(Loss) | true |
| glaze | 764.612 | 0.0473078 | 1405.59ms | 4604 | 2560 | 18892.7 | 5742.41 | 0.00418334 | 6.65654 | 28.2772 | 5.82016 | 0.00783999 | 6.15973e-05 | 2.28232e-05 | 3(Loss) | true |
| simdjson (ondemand) | 674.668 | 0.0846029 | 1480.58ms | 4604 | 640 | 19401.7 | 6507.96 | 0.00309707 | 7.53283 | 32.1383 | 5.80148 | 0.00499226 | 4.14042e-05 | 4.41192e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1288.71 | 0.145219 | 1079.66ms | 4604 | 640 | 15666.9 | 3407.06 | 0.334759 | 3.96879 | 9.39205 | 0.656386 | 0.000482936 | 3.39379e-05 | 7.12695e-06 | 1(Win) | true |
| glaze | 823.008 | 0.111842 | 1267.23ms | 4604 | 320 | 11392.7 | 5334.96 | 0.0307618 | 6.18728 | 12.2815 | 1.00825 | 0.000438477 | 2.64715e-05 | 2.71503e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1309.96 | 0.0571209 | 1092.61ms | 4604 | 4890 | 17924.8 | 3351.79 | 0.532564 | 3.92166 | 9.27433 | 0.629019 | 0.000695225 | 4.47286e-05 | 1.73673e-05 | 1(Win) | true |
| glaze | 849.801 | 0.096397 | 1248.91ms | 4604 | 320 | 7938.05 | 5166.76 | 0.00114919 | 5.99611 | 11.7194 | 0.886187 | 0.00066111 | 3.32591e-05 | 1.42539e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3253.77 | 0.0636948 | 1473.52ms | 24579 | 640 | 13475.5 | 7204.07 | 0.0408456 | 1.56133 | 6.22243 | 1.13145 | 0.00128203 | 2.46018e-05 | 1.55112e-05 | 1(Win) | true |
| jsonifier | 3020.67 | 0.0397498 | 1525.45ms | 24579 | 2560 | 24357.5 | 7759.99 | 0.163256 | 1.68103 | 6.59946 | 1.50332 | 0.00186189 | 2.37595e-05 | 9.36076e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2764 | 0.089914 | 1593.68ms | 24579 | 80 | 4651.54 | 8480.59 | 0.0201973 | 1.83842 | 7.70341 | 1.2841 | 0.00154298 | 4.22108e-05 | 3.40738e-05 | 3(Loss) | true |
| glaze | 2290.01 | 0.0635821 | 1762.95ms | 24579 | 640 | 27108.4 | 10235.9 | 0.0603174 | 2.21761 | 9.40596 | 1.91798 | 0.00372682 | 9.53558e-06 | 2.92424e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3786.27 | 0.0502527 | 1468.5ms | 24579 | 1280 | 12388.9 | 6190.88 | 0.068577 | 1.34462 | 5.43659 | 0.950446 | 0.00107256 | 1.5543e-05 | 7.24704e-06 | 1(Win) | true |
| jsonifier | 3467.44 | 0.104824 | 1526.01ms | 24579 | 160 | 8034.37 | 6760.13 | 0.0619981 | 1.46802 | 5.77802 | 1.31474 | 0.0017904 | 6.86562e-06 | 1.27141e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3094.68 | 0.0243471 | 1599.93ms | 24579 | 4890 | 16630.3 | 7574.42 | 0.125939 | 1.6413 | 7.05346 | 1.13312 | 0.00120229 | 1.88283e-05 | 8.20359e-06 | 3(Loss) | true |
| glaze | 2533.96 | 0.0368366 | 1778.97ms | 24579 | 2560 | 29725.5 | 9250.49 | 0.123599 | 2.00309 | 8.60569 | 1.73134 | 0.00360915 | 1.71481e-05 | 7.51721e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7299.04 | 0.0917616 | 1065.79ms | 24579 | 1280 | 11115.5 | 3211.43 | 0.0330254 | 0.701206 | 1.91513 | 0.122218 | 9.04609e-05 | 6.54776e-06 | 1.20784e-06 | 1(Win) | true |
| glaze | 4013.78 | 0.270062 | 1330.12ms | 24579 | 160 | 39798.7 | 5839.97 | 0.010166 | 1.26744 | 3.51548 | 0.470036 | 0.000258605 | 1.95797e-05 | 9.66272e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7552.23 | 0.0478618 | 1052.07ms | 24579 | 2560 | 5649.31 | 3103.77 | 0.0755828 | 0.678422 | 1.89609 | 0.117784 | 0.000101761 | 9.59915e-06 | 3.33745e-06 | 1(Win) | true |
| glaze | 4496.87 | 0.0821342 | 1259.15ms | 24579 | 2560 | 46924.1 | 5212.6 | 0.127543 | 1.13654 | 3.37418 | 0.43765 | 0.000227948 | 1.39219e-05 | 6.11866e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 910.295 | 0.10704 | 1218.76ms | 4604 | 40 | 1066.25 | 4823.4 | 0.0145147 | 5.60682 | 22.4088 | 4.95721 | 0.00695591 | 4.88705e-05 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 798.279 | 0.047733 | 1287.77ms | 4604 | 1280 | 8822.86 | 5500.23 | 0.0330275 | 6.37642 | 26.8123 | 5.57081 | 0.00606012 | 7.22877e-05 | 3.05441e-05 | 2(Loss) | true |
| glaze | 664.393 | 0.0341217 | 1417.13ms | 4604 | 2560 | 13017.3 | 6608.61 | 0.0188946 | 7.64444 | 31.8777 | 6.66692 | 0.0088398 | 0.000108432 | 4.94645e-05 | 3(Loss) | true |
| simdjson (ondemand) | 595.568 | 0.0833663 | 1472.12ms | 4604 | 80 | 3021.89 | 7372.31 | 0.0144141 | 8.53885 | 34.4802 | 6.35534 | 0.00867181 | 0.000105886 | 5.97307e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1132.73 | 0.0956349 | 1221.32ms | 4604 | 320 | 4397.47 | 3876.23 | 0.0938484 | 4.51004 | 18.2152 | 3.99001 | 0.00524137 | 3.32591e-05 | 5.43006e-06 | 1(Win) | true |
| jsonifier (two-stage) | 967.898 | 0.0288889 | 1294.58ms | 4604 | 4890 | 8398.14 | 4536.34 | 0.0467983 | 5.28058 | 22.6158 | 4.60339 | 0.00477232 | 6.33396e-05 | 2.23865e-05 | 2(Loss) | true |
| glaze | 767.008 | 0.0259536 | 1400.32ms | 4604 | 4890 | 10793.8 | 5724.47 | 0.117398 | 6.63577 | 27.6722 | 5.68984 | 0.00831046 | 6.0186e-05 | 1.93217e-05 | 3(Loss) | true |
| simdjson (ondemand) | 677.343 | 0.167518 | 1484.28ms | 4604 | 30 | 3537.51 | 6482.27 | 0.0169665 | 7.52606 | 32.2622 | 5.82385 | 0.00614683 | 0.000152042 | 6.51607e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1428.25 | 0.139459 | 1044.84ms | 4604 | 80 | 1470.44 | 3074.2 | 0.166172 | 3.5903 | 9.33167 | 0.646612 | 0.000491421 | 1.08601e-05 | 0 | 1(Win) | true |
| glaze | 814.014 | 0.0891417 | 1276.71ms | 4604 | 640 | 14796.2 | 5393.91 | 0.103638 | 6.25235 | 12.2048 | 0.998698 | 0.000861683 | 4.14042e-05 | 9.84199e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1432.2 | 0.055497 | 1044.17ms | 4604 | 2560 | 7410.4 | 3065.71 | 0.17488 | 3.58004 | 9.26477 | 0.630539 | 0.000641171 | 4.5901e-05 | 1.55266e-05 | 1(Win) | true |
| glaze | 837.863 | 0.082047 | 1256.41ms | 4604 | 640 | 11831.2 | 5240.38 | 0.0208672 | 6.07782 | 11.7157 | 0.887056 | 0.000718465 | 3.02047e-05 | 1.22176e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3524.16 | 0.0641424 | 1414.03ms | 24579 | 80 | 1456.13 | 6651.34 | 0.012593 | 1.44383 | 6.01282 | 1.08401 | 0.00111528 | 6.61133e-06 | 5.08564e-07 | 1(Win) | true |
| jsonifier | 3126.77 | 0.0757548 | 1494.8ms | 24579 | 640 | 20641.2 | 7496.66 | 0.10474 | 1.62374 | 6.32154 | 1.45344 | 0.0021286 | 1.15698e-05 | 4.9585e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2791.41 | 0.0337228 | 1587.29ms | 24579 | 2560 | 20529.1 | 8397.32 | 0.0176799 | 1.81132 | 7.49965 | 1.23825 | 0.00168446 | 3.55041e-05 | 1.88328e-05 | 3(Loss) | true |
| glaze | 2336.37 | 0.0384396 | 1754.85ms | 24579 | 1280 | 19037.6 | 10032.8 | 0.136801 | 2.172 | 9.14598 | 1.85878 | 0.00354396 | 1.62423e-05 | 8.45488e-06 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4146.55 | 0.0635278 | 1417.4ms | 24579 | 40 | 515.871 | 5652.98 | 0.059373 | 1.22866 | 5.22763 | 0.903088 | 0.000878799 | 7.1199e-06 | 0 | 1(Win) | true |
| jsonifier | 3599.02 | 0.0267715 | 1497.62ms | 24579 | 4890 | 14866.7 | 6512.99 | 0.0746056 | 1.41282 | 5.53652 | 1.27251 | 0.00183334 | 1.80962e-05 | 8.47815e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3075.27 | 0.0235377 | 1603.29ms | 24579 | 4890 | 15739.8 | 7622.21 | 0.0968269 | 1.65105 | 7.10611 | 1.14358 | 0.00119037 | 1.94107e-05 | 9.202e-06 | 3(Loss) | true |
| glaze | 2571.61 | 0.0785308 | 1750.28ms | 24579 | 30 | 1537.17 | 9115.07 | 0.0245076 | 1.97526 | 8.41165 | 1.68888 | 0.00346366 | 4.06851e-06 | 0 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6627.57 | 0.078429 | 1094.34ms | 24579 | 2560 | 19697.6 | 3536.79 | 0.0719743 | 0.770752 | 1.91647 | 0.122259 | 0.000105082 | 1.20148e-05 | 5.11743e-06 | 1(Win) | true |
| glaze | 3991.83 | 0.180201 | 1329.96ms | 24579 | 640 | 71660.3 | 5872.08 | 0.0214954 | 1.27719 | 3.52301 | 0.470402 | 0.000332474 | 1.15063e-05 | 4.51351e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6767.3 | 0.0477804 | 1086.79ms | 24579 | 4890 | 13393.9 | 3463.77 | 0.065644 | 0.755763 | 1.89743 | 0.117824 | 0.00010321 | 1.29627e-05 | 5.03364e-06 | 1(Win) | true |
| glaze | 4435.84 | 0.108669 | 1266.99ms | 24579 | 2560 | 84416.5 | 5284.31 | 0.00362942 | 1.14826 | 3.38122 | 0.437813 | 0.000318441 | 1.91029e-05 | 8.67738e-06 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 984.829 | 0.0740076 | 848.402ms | 1181 | 4890 | 3503 | 1143.64 | 0.313252 | 5.31202 | 21.0703 | 4.25995 | 0.00553532 | 0.000118786 | 3.60168e-05 | 1(Win) | true |
| glaze | 893.275 | 0.0804009 | 854.441ms | 1181 | 4890 | 5025.28 | 1260.85 | 0.173366 | 5.84288 | 23.337 | 4.90601 | 0.00435837 | 9.83534e-05 | 3.11683e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 889.211 | 0.179589 | 859.852ms | 1181 | 640 | 3311.53 | 1266.62 | 0.170562 | 5.85481 | 23.9534 | 4.54615 | 0.00333669 | 9.26122e-05 | 1.98455e-05 | 3(Loss) | true |
| simdjson (ondemand) | 789.59 | 0.0767046 | 873.161ms | 1181 | 640 | 766.16 | 1426.42 | 0.0898513 | 6.61039 | 28.1397 | 5.07705 | 0.00384341 | 8.5997e-05 | 3.17528e-05 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1229.98 | 0.066331 | 838.701ms | 1181 | 4890 | 1804.05 | 915.701 | 0.240942 | 4.30129 | 17.1804 | 3.48518 | 0.00223494 | 6.38951e-05 | 2.28568e-05 | 1(Win) | true |
| jsonifier | 1211.03 | 0.0622923 | 839.579ms | 1181 | 2560 | 859.212 | 930.028 | 0.648718 | 4.42614 | 17.8662 | 3.51143 | 0.00401011 | 0.000158433 | 8.56663e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1057.35 | 0.0696319 | 857.183ms | 1181 | 640 | 352.095 | 1065.2 | 0.0805954 | 4.96811 | 20.7502 | 3.79763 | 0.0023497 | 7.14437e-05 | 1.98455e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1043.54 | 0.0685758 | 851.867ms | 1181 | 4890 | 2678.77 | 1079.3 | 0.0225049 | 5.0699 | 21.9119 | 3.66385 | 0.00178629 | 8.51935e-05 | 2.51078e-05 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1755.99 | 0.107104 | 795.57ms | 1181 | 2560 | 1208.12 | 641.398 | 0.00499423 | 3.08184 | 7.94412 | 0.788315 | 0.000850378 | 6.84669e-05 | 3.34065e-05 | 1(Win) | true |
| glaze | 962.111 | 0.0582507 | 847.264ms | 1181 | 4890 | 2273.84 | 1170.64 | 0.656165 | 5.45306 | 10.1101 | 0.918715 | 0.00148915 | 9.71413e-05 | 4.05188e-05 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1823.88 | 0.0612434 | 792.285ms | 1181 | 80 | 11.4424 | 617.525 | 0.210962 | 3.00068 | 7.68755 | 0.726503 | 0.000857324 | 6.35055e-05 | 2.11685e-05 | 1(Win) | true |
| glaze | 989.97 | 0.2689 | 842.183ms | 1181 | 160 | 1497.47 | 1137.7 | 0.0967799 | 5.38972 | 9.53514 | 0.788315 | 0.00139712 | 7.93819e-05 | 3.70449e-05 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1731.79 | 0.119792 | 870.583ms | 2496 | 160 | 433.786 | 1374.52 | 0.0068201 | 3.00457 | 12.3305 | 2.23998 | 0.00244641 | 4.00641e-05 | 1.252e-05 | 1(Win) | true |
| simdjson (ondemand) | 1568.14 | 0.0799283 | 886.238ms | 2496 | 1280 | 1884.21 | 1517.95 | 0.215389 | 3.33054 | 14.0841 | 2.44671 | 0.00170366 | 5.35231e-05 | 2.12841e-05 | 2(Loss) | true |
| jsonifier | 1514.96 | 0.0648651 | 893.154ms | 2496 | 4890 | 5079.47 | 1571.25 | 0.187329 | 3.42578 | 13.7292 | 2.91547 | 0.00220631 | 6.00552e-05 | 1.91718e-05 | 3(Loss) | true |
| glaze | 1490.05 | 0.119467 | 891.213ms | 2496 | 1280 | 4662.19 | 1597.51 | 0.0774533 | 3.52018 | 14.4591 | 3.06611 | 0.00213717 | 0.000200947 | 9.82823e-05 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2053.98 | 0.067323 | 864.844ms | 2496 | 2560 | 1558.35 | 1158.91 | 0.269596 | 2.56313 | 10.8149 | 1.88582 | 0.00216049 | 3.50561e-05 | 6.88602e-06 | 1(Win) | true |
| simdjson (ondemand) | 2040.35 | 0.0955558 | 861.954ms | 2496 | 160 | 198.845 | 1166.65 | 0.0868623 | 2.5662 | 11.0361 | 1.75801 | 0.000816306 | 5.00801e-06 | 0 | 2(Loss) | true |
| glaze | 1906.49 | 0.138136 | 874.757ms | 2496 | 80 | 237.971 | 1248.56 | 0.0410641 | 2.74025 | 11.5465 | 2.39383 | 0.00189804 | 5.50881e-05 | 0 | 3(Loss) | true |
| jsonifier | 1755.17 | 0.0719597 | 889.563ms | 2496 | 2560 | 2438.21 | 1356.21 | 0.0188046 | 2.96372 | 12.2137 | 2.56133 | 0.00179256 | 5.10191e-05 | 1.6902e-05 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4277.49 | 0.10963 | 791.578ms | 2496 | 640 | 238.206 | 556.487 | 0.00112313 | 1.27049 | 3.90465 | 0.365385 | 0.000400641 | 8.76402e-06 | 1.252e-06 | 1(Win) | true |
| glaze | 1644.33 | 0.122667 | 876.221ms | 2507 | 320 | 1017.97 | 1454 | 0.226828 | 3.15835 | 6.74551 | 0.87874 | 0.000801506 | 2.49302e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4412.74 | 0.093141 | 789.738ms | 2496 | 1280 | 323.121 | 539.432 | 0.235658 | 1.23766 | 3.78325 | 0.336138 | 0.000400641 | 4.06901e-05 | 2.97351e-05 | 1(Win) | true |
| glaze | 1770.81 | 0.0664641 | 869.729ms | 2507 | 2560 | 2061.49 | 1350.15 | 0.139402 | 2.95447 | 6.06183 | 0.724771 | 0.000804155 | 2.55535e-05 | 1.0907e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2253.57 | 0.108288 | 952.126ms | 4926 | 80 | 407.661 | 2084.6 | 0.1951 | 2.28809 | 10.1931 | 1.7903 | 0.00443311 | 2.53756e-05 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 1803.01 | 0.0307874 | 1006.48ms | 4926 | 4890 | 3146.65 | 2605.53 | 0.049533 | 2.84663 | 12.7836 | 2.22331 | 0.00418164 | 5.02737e-05 | 2.01759e-05 | 2(Loss) | true |
| glaze | 1404.57 | 0.041891 | 1096.8ms | 4926 | 4890 | 9599.56 | 3344.65 | 0.0968517 | 3.6409 | 15.364 | 3.01786 | 0.00235029 | 2.60709e-05 | 3.86082e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1141.77 | 0.0607727 | 1161.3ms | 4926 | 4890 | 30574.4 | 4114.49 | 0.115792 | 4.47157 | 16.8453 | 2.9527 | 0.00436173 | 5.8452e-05 | 2.21271e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2816.61 | 0.0419693 | 948.383ms | 4926 | 4890 | 2396.11 | 1667.89 | 0.210932 | 1.84175 | 8.52558 | 1.40134 | 0.00393426 | 2.9309e-05 | 6.76682e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2146.17 | 0.0565864 | 1005.16ms | 4926 | 2560 | 3927.59 | 2188.93 | 0.104537 | 2.40326 | 11.1159 | 1.83435 | 0.00381014 | 3.68739e-05 | 1.07053e-05 | 2(Loss) | true |
| glaze | 1800.47 | 0.131206 | 1041.72ms | 4926 | 640 | 7500.82 | 2609.21 | 0.0186204 | 2.849 | 12.7107 | 2.42712 | 0.0020459 | 1.83973e-05 | 6.34389e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1395.12 | 0.0552128 | 1115.75ms | 4926 | 2560 | 8848.87 | 3367.32 | 0.0944474 | 3.65978 | 14.3902 | 2.4056 | 0.00405382 | 3.99665e-05 | 1.01502e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12198.7 | 0.0823943 | 772.738ms | 4926 | 640 | 64.4375 | 385.108 | 0.035311 | 0.457907 | 1.90176 | 0.330899 | 0.000203956 | 1.01502e-05 | 6.34389e-07 | 1(Win) | true |
| glaze | 3240.52 | 0.248847 | 888.993ms | 4926 | 4890 | 63640.4 | 1449.7 | 0.490947 | 1.60699 | 6.02883 | 0.981324 | 0.00035997 | 3.40001e-05 | 7.47256e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13781.6 | 0.164478 | 767.567ms | 4926 | 40 | 12.5737 | 340.875 | 0.316363 | 0.409293 | 1.78583 | 0.30471 | 0.000203004 | 1.01502e-05 | 0 | 1(Win) | true |
| glaze | 3884.1 | 0.27979 | 856.975ms | 4926 | 2560 | 29316.6 | 1209.5 | 0.0809018 | 1.34913 | 5.49797 | 0.867235 | 0.000358588 | 3.29882e-05 | 1.01502e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3195.94 | 0.0998218 | 1026.25ms | 9463 | 2560 | 20340 | 2823.78 | 0.338999 | 1.61511 | 7.27275 | 1.17944 | 0.00216307 | 2.47675e-05 | 7.47153e-06 | 1(Win) | true |
| jsonifier | 2570.99 | 0.0522449 | 1090.04ms | 9463 | 1280 | 4304.82 | 3510.17 | 0.0777713 | 1.98838 | 7.95118 | 1.59326 | 0.00270858 | 1.29617e-05 | 2.88954e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2086.85 | 0.0730548 | 1180.97ms | 9463 | 1280 | 12775.6 | 4324.51 | 0.234195 | 2.46048 | 9.37345 | 1.56642 | 0.00211787 | 2.27036e-05 | 5.69653e-06 | 3(Loss) | true |
| glaze | 2064.2 | 0.0379262 | 1184.9ms | 9463 | 2560 | 7038.39 | 4371.98 | 0.116448 | 2.47104 | 10.8388 | 2.11751 | 0.00246581 | 2.9721e-05 | 8.70991e-06 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3720.44 | 0.0402314 | 1028.36ms | 9463 | 2560 | 2438.03 | 2425.68 | 0.135907 | 1.38295 | 6.40463 | 0.976963 | 0.00212922 | 2.57169e-05 | 8.25584e-06 | 1(Win) | true |
| jsonifier | 2931.24 | 0.0684236 | 1088.23ms | 9463 | 40 | 177.512 | 3078.78 | 0.158631 | 1.74838 | 7.08274 | 1.39068 | 0.00255204 | 5.28374e-06 | 0 | 2(Loss) | true |
| glaze STATISTICAL TIE | 2502.04 | 0.0815546 | 1148.41ms | 9463 | 2560 | 22151.6 | 3606.9 | 0.101384 | 2.0406 | 9.45926 | 1.8101 | 0.00275093 | 1.94012e-05 | 3.88024e-06 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2499.68 | 0.107092 | 1138.46ms | 9463 | 640 | 9567.19 | 3610.31 | 0.0530749 | 2.05325 | 8.13896 | 1.29039 | 0.00254313 | 1.12279e-05 | 6.60467e-07 | 3(Tie) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21162.3 | 0.110831 | 780.14ms | 9463 | 4890 | 1092.36 | 426.449 | 0.00706471 | 0.262847 | 1.10937 | 0.17299 | 0.000105977 | 1.18209e-05 | 3.84665e-06 | 1(Win) | true |
| glaze | 4085.03 | 0.347084 | 959.987ms | 9463 | 1280 | 75256.8 | 2209.19 | 0.00714294 | 1.27344 | 4.7411 | 0.878263 | 0.000300678 | 2.07222e-05 | 5.03606e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24364.9 | 0.124136 | 771.685ms | 9463 | 160 | 33.8251 | 370.394 | 0.282591 | 0.233804 | 1.04829 | 0.158618 | 0.000105675 | 4.62327e-06 | 0 | 1(Win) | true |
| glaze | 4783.57 | 0.100611 | 925.902ms | 9463 | 2560 | 9223.34 | 1886.59 | 0.0471062 | 1.08615 | 4.41477 | 0.80334 | 0.000302659 | 2.88129e-05 | 1.49431e-05 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 5241.92 | 0.130101 | 788.51ms | 2821 | 160 | 71.3361 | 513.231 | 0.12803 | 1.03826 | 3.90429 | 0.536335 | 0.000720046 | 1.10776e-05 | 6.64658e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 5238.89 | 0.214532 | 786.814ms | 2821 | 1280 | 1553.53 | 513.527 | 0.00684556 | 1.04516 | 4.20099 | 0.470756 | 0.000359192 | 2.43708e-05 | 4.98493e-06 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 5238.03 | 0.132904 | 790.265ms | 2821 | 160 | 74.5533 | 513.612 | 0.0657542 | 1.03987 | 3.90429 | 0.536335 | 0.00077765 | 4.65261e-05 | 1.77242e-05 | 1(Tie) | true |
| glaze | 3235.91 | 0.0364248 | 819.367ms | 2821 | 1280 | 117.387 | 831.395 | 0.0177569 | 1.64554 | 6.51719 | 1.20489 | 0.000354484 | 1.27393e-05 | 0 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 5675.02 | 0.197367 | 788.317ms | 2821 | 80 | 70.034 | 474.062 | 0.176353 | 0.986906 | 3.75328 | 0.501241 | 0.000970401 | 1.77242e-05 | 0 | 1(Win) | true |
| jsonifier | 5560.26 | 0.164712 | 783.919ms | 2821 | 2560 | 1625.95 | 483.847 | 0.21429 | 0.984064 | 3.75328 | 0.501241 | 0.000717554 | 3.57254e-05 | 7.33893e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5225.05 | 0.119141 | 782.918ms | 2821 | 320 | 120.42 | 514.888 | 0.335112 | 1.04303 | 4.11875 | 0.451967 | 0.000707861 | 3.54484e-05 | 1.77242e-05 | 3(Loss) | true |
| glaze | 3279.51 | 0.0541839 | 821.366ms | 2821 | 640 | 126.447 | 820.341 | 0.0346775 | 1.62074 | 6.43672 | 1.18646 | 0.000355038 | 1.32932e-05 | 0 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 6721.77 | 0.0740631 | 795.406ms | 4147 | 4890 | 928.566 | 588.37 | 0.0109188 | 0.806674 | 3.17724 | 0.381963 | 0.000482917 | 1.91826e-05 | 4.58606e-06 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 6715.29 | 0.229867 | 795.018ms | 4147 | 80 | 146.616 | 588.938 | 0.0956023 | 0.806568 | 3.17724 | 0.381963 | 0.000482276 | 6.02845e-05 | 1.20569e-05 | 1(Tie) | true |
| simdjson (ondemand) | 6457.95 | 0.0943263 | 798.837ms | 4147 | 320 | 106.781 | 612.406 | 0.212729 | 0.835327 | 3.26139 | 0.338799 | 0.000723415 | 1.88389e-05 | 0 | 3(Loss) | true |
| glaze | 4123.51 | 0.059695 | 836.61ms | 4147 | 4890 | 1602.95 | 959.108 | 0.279856 | 1.27968 | 5.58934 | 1.05329 | 0.000244196 | 2.42124e-05 | 1.56321e-05 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 7036.34 | 0.0853273 | 792.477ms | 4147 | 320 | 73.6038 | 562.066 | 0.306517 | 0.771247 | 3.07451 | 0.35809 | 0.000482276 | 9.04268e-06 | 7.53557e-07 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 7022.17 | 0.179801 | 792.613ms | 4147 | 80 | 82.0354 | 563.2 | 0.101991 | 0.770864 | 3.07451 | 0.35809 | 0.000482276 | 1.80854e-05 | 0 | 1(Tie) | true |
| simdjson (ondemand) | 6728.8 | 0.0645688 | 799.787ms | 4147 | 1280 | 184.352 | 587.755 | 0.21209 | 0.803323 | 3.20545 | 0.326019 | 0.000241327 | 2.78816e-05 | 2.63745e-06 | 3(Loss) | true |
| glaze | 4187.71 | 0.111357 | 836.051ms | 4147 | 1280 | 1415.65 | 944.402 | 0.206796 | 1.25874 | 5.53436 | 1.04075 | 0.000246225 | 6.59362e-06 | 1.88389e-07 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2651.08 | 0.0472261 | 841.201ms | 2821 | 640 | 146.996 | 1014.8 | 0.0052353 | 1.98578 | 6.3318 | 1.11202 | 0.00177242 | 3.98795e-05 | 2.21553e-06 | 1(Win) | true |
| glaze | 2460.42 | 0.0673444 | 849.311ms | 2821 | 640 | 347.032 | 1093.44 | 0.0653471 | 2.12717 | 8.56753 | 1.47891 | 0.000658565 | 2.65863e-05 | 1.66164e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2334.08 | 0.185875 | 854.495ms | 2821 | 640 | 2937.63 | 1152.62 | 0.0615064 | 2.24246 | 8.10528 | 1.28713 | 0.000466922 | 5.09571e-05 | 1.66164e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2266.1 | 0.152658 | 855.116ms | 2821 | 80 | 262.77 | 1187.2 | 0.0990704 | 2.30678 | 8.81992 | 1.23999 | 0.000363346 | 5.76037e-05 | 8.86211e-06 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2922.73 | 0.11946 | 842.146ms | 2821 | 2560 | 3095.38 | 920.479 | 0.307978 | 1.81396 | 5.82028 | 0.979795 | 0.00178294 | 7.32508e-05 | 3.82178e-05 | 1(Win) | true |
| glaze | 2721.08 | 0.0872172 | 843.615ms | 2821 | 4890 | 3636.11 | 988.694 | 0.0163595 | 1.94916 | 7.98901 | 1.33676 | 0.000839888 | 5.87907e-05 | 1.42084e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2664.55 | 0.0609788 | 844.164ms | 2821 | 4890 | 1853.64 | 1009.67 | 0.231137 | 1.98864 | 7.40908 | 1.11875 | 0.000358761 | 6.09655e-05 | 1.19611e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2479.3 | 0.14729 | 848.508ms | 2821 | 80 | 204.354 | 1085.11 | 0.134961 | 2.15663 | 8.42361 | 1.14002 | 0.000358915 | 3.10174e-05 | 8.86211e-06 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8657.45 | 0.13019 | 762.159ms | 2821 | 1280 | 209.505 | 310.752 | 0.133068 | 0.670636 | 1.5296 | 0.243531 | 0.000354484 | 7.14507e-05 | 4.01564e-05 | 1(Win) | true |
| glaze | 4760.03 | 0.167584 | 786.341ms | 2819 | 4890 | 4380.7 | 564.788 | 0.0255025 | 1.14786 | 2.98617 | 0.462576 | 0.000391443 | 4.42513e-05 | 6.67396e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10321.9 | 0.115269 | 754.768ms | 2821 | 4890 | 441.388 | 260.642 | 0.0482653 | 0.57028 | 1.34739 | 0.202411 | 0.000354774 | 2.97216e-05 | 6.0893e-06 | 1(Win) | true |
| glaze | 5560.49 | 0.199086 | 776.052ms | 2819 | 2560 | 2371.85 | 483.484 | 0.188298 | 0.994392 | 2.53494 | 0.367152 | 0.000356537 | 2.68823e-05 | 6.78986e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3176.26 | 0.047404 | 860.014ms | 4147 | 4890 | 1703.63 | 1245.14 | 0.330128 | 1.65107 | 6.0164 | 0.893899 | 0.000242223 | 3.67871e-05 | 5.81888e-06 | 1(Win) | true |
| simdjson (ondemand) | 3130.42 | 0.0635446 | 858.558ms | 4147 | 2560 | 1649.91 | 1263.37 | 0.323468 | 1.67044 | 6.40342 | 0.862069 | 0.000252347 | 3.44752e-05 | 5.74587e-06 | 2(Loss) | true |
| glaze | 2873.07 | 0.114331 | 872.111ms | 4147 | 80 | 198.15 | 1376.54 | 0.0299755 | 1.84595 | 7.66144 | 1.34555 | 0.000470219 | 1.20569e-05 | 0 | 3(Loss) | true |
| jsonifier | 2309.72 | 0.0401927 | 907.044ms | 4147 | 4890 | 2316.08 | 1712.28 | 0.103325 | 2.24783 | 6.11385 | 1.19774 | 0.000485284 | 5.62163e-05 | 1.75059e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3505.6 | 0.14424 | 856.907ms | 4147 | 640 | 1694.72 | 1128.16 | 0.0602109 | 1.49203 | 5.5428 | 0.779359 | 0.000318001 | 2.48674e-05 | 1.13034e-06 | 1(Win) | true |
| simdjson (ondemand) | 3363.86 | 0.0901662 | 856.291ms | 4147 | 320 | 359.609 | 1175.7 | 0.185714 | 1.55731 | 6.13383 | 0.794068 | 0.000254702 | 3.9185e-05 | 6.02845e-06 | 2(Loss) | true |
| glaze | 3098.77 | 0.077452 | 869.589ms | 4147 | 320 | 312.683 | 1276.28 | 0.118369 | 1.71529 | 7.2679 | 1.24885 | 0.00029238 | 3.01423e-05 | 3.76778e-06 | 3(Loss) | true |
| jsonifier | 2476.13 | 0.0497106 | 902.685ms | 4147 | 2560 | 1613.83 | 1597.2 | 0.288516 | 2.0933 | 5.76513 | 1.10779 | 0.000484443 | 4.10688e-05 | 9.89043e-06 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11482.1 | 0.0480908 | 766.882ms | 4147 | 320 | 8.78016 | 344.441 | 0.0752466 | 0.490812 | 1.12949 | 0.166626 | 0.000241138 | 2.0346e-05 | 0 | 1(Win) | true |
| glaze | 4018.4 | 0.332158 | 830.291ms | 4145 | 4890 | 52208.6 | 983.721 | 0.100819 | 1.32563 | 3.34451 | 0.613028 | 0.000244215 | 9.9758e-05 | 5.34312e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13631.2 | 0.0811395 | 760.809ms | 4147 | 320 | 17.7342 | 290.134 | 0.207447 | 0.430436 | 1.01278 | 0.139619 | 0.000241138 | 2.10996e-05 | 0 | 1(Win) | true |
| glaze | 4760.81 | 0.305769 | 817.881ms | 4145 | 1280 | 8250.58 | 830.317 | 0.118506 | 1.12 | 2.75972 | 0.479856 | 0.000243139 | 1.77171e-05 | 2.63872e-06 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3553.44 | 0.335001 | 6796.45ms | 466906 | 1280 | 2.25561e+08 | 125309 | 0.0292368 | 1.41608 | 6.27688 | 0.891848 | 0.00208746 | 0.00189324 | 1.92758e-06 | 1(Win) | true |
| glaze | 2763.89 | 0.11121 | 8658.65ms | 466906 | 320 | 1.02719e+07 | 161105 | 0.151436 | 1.83211 | 7.38345 | 1.50349 | 0.00239839 | 0.000452567 | 2.91279e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1318.31 | 0.590317 | 8820.58ms | 466906 | 1280 | 5.08866e+09 | 337762 | 0.168105 | 3.78591 | 14.6038 | 2.35641 | 0.00682104 | 0.0936766 | 7.26525e-06 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3611.6 | 0.0864675 | 6784.79ms | 466906 | 40 | 454595 | 123290 | 0.129526 | 1.39857 | 6.27575 | 0.891595 | 0.0021038 | 0.00191286 | 7.65679e-06 | 1(Win) | true |
| glaze | 2819.08 | 0.0931212 | 8634.02ms | 466906 | 40 | 865369 | 157951 | 0.0223854 | 1.82455 | 7.38232 | 1.50325 | 0.00236766 | 0.000406399 | 1.79372e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1314.63 | 0.538475 | 8881.52ms | 466906 | 1280 | 4.25788e+09 | 338709 | 0.0154126 | 3.80053 | 14.6038 | 2.35643 | 0.0070604 | 0.0973137 | 7.82244e-06 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5031.44 | 0.279726 | 7147.93ms | 699405 | 160 | 2.20018e+07 | 132567 | 0.179585 | 0.992019 | 3.99376 | 0.688616 | 0.00240965 | 2.01689e-05 | 1.00979e-06 | 1(Win) | true |
| glaze | 3962.33 | 0.10821 | 8992.29ms | 699405 | 80 | 2.65452e+06 | 168337 | 0.0773974 | 1.26888 | 4.78928 | 1.13545 | 0.00193436 | 0.00137433 | 8.04255e-07 | 2(Loss) | true |
| simdjson (ondemand) | 1556.41 | 0.348098 | 6189.01ms | 767297 | 160 | 4.28552e+08 | 470154 | 0.178137 | 3.23303 | 13.8272 | 2.1877 | 0.00827704 | 0.0792383 | 5.51367e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5029.1 | 0.0509428 | 7148.08ms | 699405 | 2560 | 1.16865e+07 | 132629 | 0.0808002 | 0.990751 | 3.99302 | 0.688448 | 0.00243342 | 2.23974e-05 | 2.20835e-06 | 1(Win) | true |
| glaze | 3973.33 | 0.0568596 | 8989.47ms | 699405 | 1280 | 1.16618e+07 | 167871 | 0.0851419 | 1.27185 | 4.78853 | 1.13529 | 0.00195923 | 0.00120907 | 1.08798e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1479.63 | 0.973346 | 6416.97ms | 767297 | 640 | 1.48297e+10 | 494549 | 0.290445 | 3.38509 | 13.8274 | 2.18775 | 0.00838075 | 0.0874742 | 1.31305e-05 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3621.55 | 0.143804 | 8971.9ms | 631514 | 320 | 1.83008e+07 | 166298 | 0.0830702 | 1.38221 | 7.0246 | 1.20969 | 0.0038682 | 2.48411e-06 | 1.69236e-06 | 1(Win) | true |
| glaze | 2619.17 | 0.209846 | 6045.04ms | 631514 | 40 | 9.31323e+06 | 229942 | 0.0616875 | 1.9158 | 8.56761 | 1.52634 | 0.00210427 | 3.08782e-06 | 1.97937e-06 | 2(Loss) | true |
