# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-42-generic using the Clang 24.0.0 compiler).  

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
*Environment generated via BenchmarkSuite commit: [ed43ce8](https://github.com/nihilai-collective/benchmarksuite/commit/ed43ce8)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1965.71 | 0.119725 | 767.801ms | 905 | 640 | 176.85 | 439.066 | 0.0341751 | 2.87186 | 13.5039 | 2.2895 | 0.00110497 | 0.000170925 | 2.58978e-05 | 1(Win) | true |
| Glaze | 1583.85 | 0.186927 | 781.672ms | 905 | 1280 | 1328.09 | 544.923 | 0.00544831 | 3.44954 | 17.5934 | 2.2895 | 0.00111965 | 0.000125173 | 1.81285e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 623.747 | 0.328698 | 864.9ms | 905 | 160 | 3309.75 | 1383.69 | 0.0176128 | 8.49393 | 42.2243 | 5.0663 | 0.00120166 | 9.66851e-05 | 6.90608e-06 | 3(Loss) | true |
| simdjson (ondemand) | 282.847 | 0.221022 | 1035.55ms | 905 | 160 | 7277.58 | 3051.39 | 0.109086 | 18.1008 | 88.9459 | 9.47735 | 0.0211809 | 0.000151934 | 0 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2170.51 | 0.219741 | 765.475ms | 905 | 160 | 122.157 | 397.637 | 0.280562 | 2.65503 | 12.842 | 2.17127 | 0.0011326 | 0.000186464 | 2.76243e-05 | 1(Win) | true |
| Glaze | 1688.01 | 0.121288 | 777.198ms | 905 | 2560 | 984.519 | 511.298 | 0.134129 | 3.22884 | 16.9249 | 2.17127 | 0.00112224 | 0.000157977 | 9.92749e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 656.215 | 0.0679299 | 864.132ms | 905 | 4890 | 3903.34 | 1315.23 | 0.179213 | 7.89505 | 41.6022 | 4.94807 | 0.00115356 | 0.00013332 | 7.9088e-06 | 3(Loss) | true |
| simdjson (ondemand) | 278.652 | 0.0955267 | 1040.85ms | 905 | 40 | 350.174 | 3097.32 | 0.246111 | 18.0665 | 88.3271 | 9.35912 | 0.023674 | 0.000276243 | 0 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2208.94 | 0.314134 | 759.416ms | 905 | 160 | 241.034 | 390.719 | 0.357991 | 2.52978 | 9.30497 | 0.948066 | 0.00331492 | 2.76243e-05 | 0 | 1(Win) | true |
| Glaze | 213.981 | 0.0646337 | 1138.31ms | 905 | 2560 | 17398.2 | 4033.42 | 0.0263494 | 23.8407 | 112.526 | 22.8232 | 0.0767731 | 0.000544717 | 0.000308184 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4293.8 | 0.0955365 | 748.928ms | 905 | 2560 | 94.4044 | 201.005 | 0.58505 | 1.41748 | 5.79779 | 0.272928 | 0.00222462 | 4.70477e-05 | 7.76934e-06 | 1(Win) | true |
| Glaze | 942.512 | 0.0678374 | 824.963ms | 905 | 4890 | 1886.99 | 915.718 | 0.164683 | 5.60473 | 24.0597 | 3.14917 | 0.00113367 | 0.000190941 | 9.17421e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1299.45 | 0.142825 | 859.374ms | 1811 | 160 | 576.561 | 1329.11 | 0.0963065 | 4.01096 | 19.757 | 4.03368 | 0.00149434 | 6.55715e-05 | 6.90226e-06 | 1(Win) | true |
| Glaze | 936.862 | 0.124184 | 912.524ms | 1811 | 40 | 209.641 | 1843.5 | 0.0650512 | 5.51906 | 30.0607 | 4.67973 | 0.000593595 | 0.00015185 | 6.90226e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 739.171 | 0.108577 | 966.778ms | 1811 | 1280 | 8238.28 | 2336.54 | 0.119158 | 6.95113 | 32.9779 | 5.58863 | 0.000611282 | 0.00014883 | 5.00414e-05 | 3(Loss) | true |
| simdjson (ondemand) | 353.408 | 0.0641775 | 1229.74ms | 1811 | 640 | 6295.51 | 4887 | 0.158868 | 14.1444 | 71.2971 | 9.28272 | 0.000665206 | 5.52181e-05 | 4.31391e-06 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1429.78 | 0.0232606 | 844.861ms | 1811 | 640 | 50.5268 | 1207.95 | 0.0279476 | 3.65494 | 18.8421 | 3.83214 | 0.000823958 | 3.9688e-05 | 3.45113e-06 | 1(Win) | true |
| Glaze | 1006.99 | 0.127787 | 896.491ms | 1811 | 640 | 3074.25 | 1715.11 | 0.0589082 | 5.1308 | 29.0337 | 4.45334 | 0.00111558 | 6.21204e-05 | 2.58835e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 804.239 | 0.111326 | 951.33ms | 1811 | 160 | 914.491 | 2147.5 | 0.305235 | 6.41592 | 31.9172 | 5.3545 | 0.00143567 | 5.86692e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 360.557 | 0.0503911 | 1218.17ms | 1811 | 2560 | 14915.5 | 4790.1 | 0.00896136 | 13.8387 | 70.2253 | 9.04362 | 0.000585183 | 7.01011e-05 | 4.09822e-06 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 326.599 | 0.124414 | 1256.15ms | 1811 | 160 | 6925.73 | 5288.14 | 0.0270726 | 15.3009 | 64.5737 | 11.4793 | 0.0201546 | 7.59249e-05 | 0 | 1(Win) | true |
| Glaze | 292.346 | 0.0390416 | 1330.16ms | 1798 | 2560 | 13423.9 | 5865.33 | 0.0841587 | 17.3312 | 71.4494 | 12.2047 | 0.0209458 | 0.000243978 | 0.000124487 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 822.007 | 0.233344 | 953.626ms | 1811 | 640 | 15383.7 | 2101.08 | 0.0104102 | 6.26272 | 19.7101 | 1.14026 | 0.000660029 | 5.1767e-05 | 1.72557e-06 | 1(Win) | true |
| Glaze | 708.667 | 0.0755219 | 993.127ms | 1798 | 640 | 2137.08 | 2419.62 | 0.0147901 | 7.25876 | 26.4321 | 2.17241 | 0.00136871 | 0.000134698 | 7.12597e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3073.9 | 0.0641087 | 857.751ms | 3862 | 4890 | 2885.29 | 1198.18 | 0.0562202 | 1.69808 | 8.6375 | 1.03159 | 0.000317551 | 8.1969e-05 | 2.97588e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1671.31 | 0.125953 | 957.681ms | 3862 | 80 | 616.334 | 2203.71 | 0.00623908 | 3.08208 | 14.4604 | 1.73692 | 0.000424003 | 8.41533e-05 | 3.23666e-05 | 2(Loss) | true |
| Glaze | 1584.78 | 0.0886179 | 958.587ms | 3862 | 80 | 339.328 | 2324.04 | 0.147051 | 3.24718 | 15.6911 | 1.98628 | 0.00758027 | 1.942e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 784.575 | 0.10128 | 1207.6ms | 3862 | 40 | 904.189 | 4694.38 | 0.0643973 | 6.50369 | 28.2848 | 3.49948 | 0.0136328 | 0.000110047 | 5.826e-05 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3451.45 | 0.111706 | 840.617ms | 3862 | 1280 | 1818.8 | 1067.11 | 0.0980074 | 1.51739 | 8.13827 | 0.922321 | 0.000262574 | 2.44773e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1779.41 | 0.0554123 | 943.437ms | 3862 | 1280 | 1683.82 | 2069.84 | 0.0399119 | 2.89723 | 13.9612 | 1.62765 | 0.000271273 | 5.4821e-05 | 1.35535e-05 | 2(Loss) | true |
| Glaze | 1753.41 | 0.136608 | 943.037ms | 3862 | 640 | 5269.76 | 2100.53 | 0.0695994 | 2.92477 | 15.2165 | 1.88011 | 0.00207025 | 3.31758e-05 | 4.45041e-06 | 3(Loss) | true |
| simdjson (ondemand) | 792.22 | 0.0302185 | 1201.16ms | 3862 | 4890 | 9651.36 | 4649.08 | 0.094744 | 6.41136 | 27.7962 | 3.39203 | 0.0157628 | 3.75427e-05 | 1.6415e-06 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 942.481 | 0.0494929 | 1134.02ms | 3862 | 320 | 1197.06 | 3907.87 | 0.0406397 | 5.42147 | 26.1385 | 5.37183 | 0.00869773 | 5.90691e-05 | 1.53742e-05 | 1(Win) | true |
| Glaze | 864.063 | 0.0576842 | 1160.5ms | 3862 | 640 | 3869.25 | 4262.52 | 0.171661 | 5.9054 | 29.674 | 5.74029 | 0.00755802 | 4.32904e-05 | 5.66416e-06 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4775.79 | 0.0793483 | 837.231ms | 3862 | 4890 | 1831.13 | 771.2 | 0.13283 | 1.10312 | 5.36665 | 0.628949 | 0.00034355 | 3.33595e-05 | 2.11806e-06 | 1(Win) | true |
| Glaze | 2422.6 | 0.0898398 | 916.197ms | 3862 | 320 | 596.965 | 1520.31 | 0.100409 | 2.14784 | 8.65251 | 1.04868 | 0.00537934 | 2.50842e-05 | 0 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1830.69 | 0.0767852 | 1244.33ms | 9578 | 1280 | 18788.1 | 4989.53 | 0.12445 | 2.78441 | 14.1347 | 2.71633 | 0.00130206 | 4.72274e-05 | 1.3948e-05 | 1(Win) | true |
| Glaze | 1413.27 | 0.0810505 | 1388.09ms | 9578 | 2560 | 70251 | 6463.25 | 0.0725478 | 3.55856 | 17.8515 | 3.54249 | 0.0018105 | 3.25453e-05 | 3.58895e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1391.71 | 0.0756752 | 1400.77ms | 9578 | 1280 | 31576.7 | 6563.34 | 0.288232 | 3.62215 | 17.569 | 2.95573 | 0.00384165 | 1.90867e-05 | 7.34104e-07 | 3(Loss) | true |
| Jsonifier (two-stage) | 1317.46 | 0.158913 | 1436.88ms | 9578 | 160 | 19422.8 | 6933.26 | 0.0339732 | 3.85927 | 18.2644 | 3.08916 | 0.00147408 | 4.24149e-05 | 2.08812e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2884.43 | 0.0873049 | 1194.54ms | 9578 | 2560 | 19568.1 | 3166.76 | 0.372437 | 1.76814 | 9.90614 | 1.77532 | 0.000319295 | 2.39807e-05 | 2.65093e-06 | 1(Win) | true |
| Glaze | 2057.45 | 0.149424 | 1334.36ms | 9578 | 320 | 14082.4 | 4439.61 | 0.232047 | 2.45917 | 13.4938 | 2.55231 | 0.000714854 | 1.53346e-05 | 3.26269e-07 | 2(Loss) | true |
| simdjson (ondemand) | 1922.81 | 0.126354 | 1360.97ms | 9578 | 30 | 1080.88 | 4750.5 | 0.0610835 | 2.60537 | 13.4126 | 2.04281 | 0.00280504 | 2.08812e-05 | 0 | 3(Loss) | true |
| Jsonifier (two-stage) | 1800.75 | 0.0426559 | 1387.79ms | 9578 | 4890 | 22893.3 | 5072.49 | 0.183386 | 2.81213 | 14.075 | 2.16987 | 0.000114398 | 1.93439e-05 | 1.75077e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4065.85 | 0.0850566 | 970.64ms | 9578 | 2560 | 9347.65 | 2246.59 | 0.114157 | 1.23773 | 5.09313 | 1.00794 | 0.00204228 | 1.54978e-05 | 1.22351e-06 | 1(Win) | true |
| Glaze | 1914.71 | 0.126406 | 1222.36ms | 9578 | 320 | 11636.8 | 4770.6 | 0.0627803 | 2.64422 | 13.4191 | 2.62059 | 0.00118958 | 3.19743e-05 | 6.1991e-06 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11555.4 | 0.0687392 | 843.932ms | 9578 | 4890 | 1443.78 | 790.48 | 0.133193 | 0.451774 | 1.88557 | 0.21539 | 0.000771195 | 1.90664e-05 | 2.75427e-06 | 1(Win) | true |
| Glaze | 4244.91 | 0.0433948 | 979.669ms | 9578 | 2560 | 2232.17 | 2151.82 | 0.0850481 | 1.19595 | 4.99374 | 0.731781 | 0.000212523 | 1.64766e-05 | 2.03918e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3246.09 | 0.0878495 | 856.104ms | 3873 | 160 | 159.872 | 1137.86 | 0.0489097 | 1.61482 | 7.96334 | 1.03305 | 0.000292086 | 3.22747e-05 | 0 | 1(Win) | true |
| Glaze | 1753.4 | 0.159605 | 945.805ms | 3873 | 40 | 452.153 | 2106.53 | 0.0177987 | 2.88741 | 14.7317 | 1.87916 | 0.00386006 | 4.51846e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1588.05 | 0.0462724 | 971.854ms | 3873 | 4890 | 5663.95 | 2325.86 | 0.0112213 | 3.23091 | 14.2698 | 1.68784 | 0.000789906 | 8.67523e-05 | 2.65062e-05 | 3(Loss) | true |
| simdjson (ondemand) | 714.281 | 0.0252475 | 1257.06ms | 3873 | 4890 | 8334.97 | 5171.05 | 0.059271 | 7.06446 | 27.8567 | 3.5528 | 0.0151672 | 6.07742e-05 | 1.11939e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3538.71 | 0.0367504 | 837.902ms | 3873 | 4890 | 719.513 | 1043.77 | 0.0795745 | 1.47765 | 7.51975 | 0.938807 | 0.000263214 | 4.41418e-05 | 1.58404e-06 | 1(Win) | true |
| Glaze | 1887.37 | 0.0979085 | 935.652ms | 3873 | 1280 | 4699.26 | 1956.99 | 0.0310681 | 2.68328 | 14.3085 | 1.78492 | 0.00215535 | 5.02275e-05 | 4.23606e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1664.38 | 0.0458319 | 956.133ms | 3873 | 2560 | 2648.29 | 2219.19 | 0.233614 | 3.08094 | 13.8306 | 1.5936 | 0.000782057 | 4.26631e-05 | 4.23606e-06 | 3(Loss) | true |
| simdjson (ondemand) | 722.673 | 0.13584 | 1257.97ms | 3873 | 30 | 1446.07 | 5111 | 0.0313148 | 7.06066 | 27.4216 | 3.45624 | 0.0179878 | 1.72132e-05 | 0 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 912.033 | 0.0571586 | 1146.56ms | 3873 | 160 | 857.349 | 4049.83 | 0.0665594 | 5.49538 | 25.6907 | 5.22799 | 0.008506 | 3.71159e-05 | 0 | 1(Win) | true |
| Glaze | 818.958 | 0.0404633 | 1197.16ms | 3873 | 2560 | 8525.78 | 4510.1 | 0.0863826 | 6.131 | 29.6254 | 5.77072 | 0.00713917 | 0.000102876 | 3.87297e-05 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4469.61 | 0.0854425 | 844.643ms | 3873 | 2560 | 1276.28 | 826.377 | 0.000141809 | 1.1751 | 5.12962 | 0.557707 | 0.00770872 | 5.29507e-05 | 9.98499e-06 | 1(Win) | true |
| Glaze | 2327.79 | 0.181819 | 928.039ms | 3873 | 320 | 2663.41 | 1586.73 | 0.159861 | 2.19766 | 8.51175 | 1.0457 | 0.00464837 | 2.50129e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1665.53 | 0.0173742 | 6189.21ms | 94653 | 4890 | 433589 | 54197.7 | 0.097231 | 2.98337 | 13.5355 | 2.51991 | 0.0112691 | 1.24424e-05 | 5.54387e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1462.49 | 0.114794 | 6933.85ms | 94653 | 40 | 200811 | 61722.4 | 0.0740403 | 3.39391 | 15.1426 | 2.84751 | 0.0108422 | 6.33894e-06 | 3.43359e-06 | 2(Loss) | true |
| Glaze | 1398.98 | 0.0504615 | 7132.12ms | 94653 | 640 | 678491 | 64524.1 | 0.002998 | 3.55357 | 15.8308 | 3.1144 | 0.0162122 | 7.80813e-06 | 1.88187e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1191.98 | 0.0472784 | 8322.12ms | 94653 | 4890 | 6.26849e+06 | 75729.3 | 0.0397156 | 4.15913 | 16.9088 | 3.15894 | 0.0118901 | 1.90752e-05 | 6.93092e-06 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2755.95 | 0.0453173 | 5403.23ms | 94653 | 320 | 70502.7 | 32753.9 | 0.066649 | 1.80116 | 9.42523 | 1.60373 | 0.00596155 | 4.32501e-06 | 1.45267e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2306.56 | 0.0192935 | 5931.36ms | 94653 | 2560 | 145949 | 39135.4 | 0.0744654 | 2.15425 | 11.076 | 1.94077 | 0.00534252 | 5.07198e-06 | 9.61571e-07 | 2(Loss) | true |
| Glaze | 2134.01 | 0.0270819 | 6316.43ms | 94653 | 2560 | 335951 | 42299.9 | 0.0131759 | 2.36063 | 11.9446 | 2.23866 | 0.00961955 | 3.88756e-06 | 4.33326e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1665.03 | 0.078025 | 7629.98ms | 94653 | 640 | 1.14517e+06 | 54214.1 | 0.0235119 | 2.97983 | 12.9615 | 2.26998 | 0.00793088 | 3.81327e-06 | 4.62215e-07 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16235.5 | 0.0221006 | 1303.02ms | 94653 | 4890 | 7383.39 | 5559.92 | 0.0206048 | 0.307703 | 1.33038 | 0.183956 | 0.00012626 | 3.43521e-06 | 4.08337e-07 | 1(Win) | true |
| Glaze | 5279.74 | 0.0602857 | 2464.15ms | 94653 | 2560 | 271964 | 17097.1 | 0.00496451 | 0.94048 | 4.37485 | 0.66635 | 8.7144e-05 | 6.78465e-06 | 3.30153e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16395.4 | 0.0261653 | 1301.47ms | 94653 | 640 | 1328.17 | 5505.69 | 0.0153274 | 0.305121 | 1.32473 | 0.182699 | 0.000132788 | 1.43617e-06 | 1.98092e-07 | 1(Win) | true |
| Glaze | 5888.56 | 0.0675967 | 2284.32ms | 94653 | 1280 | 137439 | 15329.4 | 0.0150061 | 0.842381 | 4.32645 | 0.655341 | 5.4335e-05 | 4.15168e-06 | 1.27109e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1801.11 | 0.244044 | 7306.3ms | 124597 | 40 | 1.03688e+06 | 65973 | 0.0658926 | 2.76557 | 11.9304 | 2.17887 | 0.0111166 | 6.01941e-06 | 2.00647e-06 | 1(Win) | true |
| Jsonifier | 1696.99 | 0.0531018 | 7811.88ms | 124597 | 640 | 884816 | 70020.9 | 0.132802 | 2.95419 | 12.8612 | 2.56847 | 0.0103649 | 1.23398e-05 | 2.92192e-06 | 2(Loss) | true |
| Glaze | 1586.96 | 0.0340994 | 8371.55ms | 124597 | 1280 | 834427 | 74876 | 0.0353856 | 3.1397 | 13.9679 | 2.77763 | 0.016164 | 8.63409e-06 | 1.32302e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1545.09 | 0.072421 | 8391.29ms | 124597 | 320 | 992625 | 76904.7 | 0.00947512 | 3.20876 | 13.1398 | 2.41111 | 0.00920234 | 1.15623e-05 | 1.63026e-06 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2804.6 | 0.121643 | 6247.89ms | 124597 | 320 | 849953 | 42367.8 | 0.0237191 | 1.76452 | 8.84327 | 1.49371 | 0.00502024 | 3.411e-06 | 2.00647e-07 | 1(Win) | true |
| Jsonifier | 2411.64 | 0.111903 | 6956.29ms | 124597 | 40 | 121601 | 49271.5 | 0.225652 | 2.09719 | 9.74681 | 1.87996 | 0.00801966 | 1.14369e-05 | 5.41747e-06 | 2(Loss) | true |
| Glaze | 2191.49 | 0.0611767 | 7475.25ms | 124597 | 320 | 352095 | 54221.2 | 0.160547 | 2.27551 | 11.0209 | 2.1189 | 0.0106322 | 1.93123e-06 | 1.25404e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2144.87 | 0.0358193 | 7566.98ms | 124597 | 2560 | 1.00806e+06 | 55399.6 | 0.0261455 | 2.31328 | 10.1487 | 1.74025 | 0.00589933 | 5.40179e-06 | 9.59343e-07 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18415.1 | 0.0734022 | 1455.87ms | 136037 | 320 | 8557.26 | 7045.03 | 0.102704 | 0.271081 | 1.27847 | 0.214978 | 0.000329782 | 1.33236e-06 | 0 | 1(Win) | true |
| Glaze | 5295.04 | 0.101914 | 3192.37ms | 136076 | 1280 | 798549 | 24508.3 | 0.337174 | 0.936208 | 4.09525 | 0.69035 | 0.00135903 | 2.76155e-06 | 6.54506e-07 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18648.1 | 0.0845857 | 1450.59ms | 136037 | 80 | 2770.3 | 6957 | 0.0380766 | 0.26772 | 1.27457 | 0.214104 | 0.000303134 | 1.3783e-06 | 9.18868e-08 | 1(Win) | true |
| Glaze | 5819.29 | 0.0494339 | 2987.07ms | 136076 | 1280 | 155554 | 22300.3 | 0.0797068 | 0.860321 | 4.06236 | 0.682685 | 0.0014017 | 2.18169e-06 | 5.62645e-07 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1036.8 | 0.128154 | 6457.5ms | 2251027 | 30 | 2.1123e+08 | 2.07054e+06 | 0.223517 | 4.76805 | 25.8518 | 5.09982 | 0.00766973 | 0.0644162 | 0.000144038 | 1(Win) | true |
| Jsonifier (two-stage) | 901.542 | 0.332382 | 7425.2ms | 2251027 | 80 | 5.01134e+09 | 2.38119e+06 | 0.0645472 | 5.54931 | 28.5558 | 5.31794 | 0.0103128 | 0.101976 | 0.000819865 | 2(Loss) | true |
| Glaze | 835.116 | 0.245368 | 7980.69ms | 2251027 | 160 | 6.36536e+09 | 2.5706e+06 | 0.395029 | 5.94504 | 31.7323 | 5.89797 | 0.0101542 | 0.0638347 | 2.28729e-05 | 3(Loss) | true |
| simdjson (ondemand) | 687.817 | 0.428887 | 9688.86ms | 2251027 | 40 | 7.1674e+09 | 3.1211e+06 | 0.192697 | 7.20322 | 30.9924 | 5.56847 | 0.0142756 | 0.107599 | 0.0019701 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1269.71 | 0.230318 | 6449.8ms | 2251027 | 160 | 2.42622e+09 | 1.69074e+06 | 0.301467 | 3.91773 | 20.911 | 3.90242 | 0.00722181 | 0.0414772 | 0.000460829 | 1(Win) | true |
| Jsonifier (two-stage) | 1064.43 | 0.119347 | 7412.85ms | 2251027 | 80 | 4.63494e+08 | 2.01681e+06 | 0.0628268 | 4.65903 | 23.6726 | 4.137 | 0.00970748 | 0.0784217 | 0.00103442 | 2(Loss) | true |
| Glaze | 982.643 | 0.369181 | 8000.03ms | 2251027 | 30 | 1.95151e+09 | 2.18467e+06 | 0.413827 | 5.03372 | 26.7587 | 4.69658 | 0.0092258 | 0.0402999 | 0.000304439 | 3(Loss) | true |
| simdjson (ondemand) | 802.38 | 0.227903 | 9541.57ms | 2251027 | 160 | 5.94866e+09 | 2.67547e+06 | 0.131007 | 6.17626 | 26.0539 | 4.37655 | 0.0107288 | 0.0750086 | 0.00151994 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1892.03 | 0.0137476 | 6779.97ms | 2090234 | 80 | 1.67833e+06 | 1.05358e+06 | 0.477339 | 2.61944 | 7.97102 | 0.405689 | 0.000236062 | 0.0508356 | 0.000542559 | 1(Win) | true |
| Glaze | 936.676 | 0.511433 | 6663.6ms | 2090234 | 40 | 4.73858e+09 | 2.12817e+06 | 0.0721932 | 5.27657 | 9.34216 | 0.534088 | 0.000239865 | 0.0689776 | 0.00538324 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1890.17 | 0.0218798 | 6784.85ms | 2090234 | 40 | 2.12977e+06 | 1.05461e+06 | 0.00673819 | 2.62195 | 7.97085 | 0.405654 | 0.000232522 | 0.050766 | 0.000873778 | 1(Win) | true |
| Glaze | 975.128 | 0.301073 | 6361.62ms | 2090234 | 160 | 6.0608e+09 | 2.04425e+06 | 0.0294294 | 5.09345 | 9.33809 | 0.533136 | 0.000234929 | 0.0432556 | 0.00338416 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2042.46 | 0.308327 | 7861.75ms | 5373214 | 160 | 9.57427e+09 | 2.50888e+06 | 0.482184 | 2.42665 | 13.2939 | 2.80666 | 0.00330533 | 0.0381384 | 0.00158902 | 1(Win) | true |
| Jsonifier (two-stage) | 1972.08 | 0.141393 | 8094.96ms | 5373214 | 30 | 4.04948e+08 | 2.59843e+06 | 0.00948561 | 2.49917 | 12.753 | 2.27007 | 0.0046766 | 0.0623051 | 0.00486219 | 2(Loss) | true |
| Glaze | 1653.12 | 0.273894 | 9633.17ms | 5373214 | 160 | 1.15331e+10 | 3.09977e+06 | 0.0543246 | 2.99774 | 15.9996 | 2.99578 | 0.00478136 | 0.0403827 | 0.000952567 | 3(Loss) | true |
| simdjson (ondemand) | 1582.33 | 0.460411 | 10070ms | 5373214 | 40 | 8.89254e+09 | 3.23845e+06 | 0.368604 | 3.18735 | 13.6748 | 2.36575 | 0.00627657 | 0.0643824 | 0.00279302 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2396.82 | 0.218028 | 7835.26ms | 5373214 | 160 | 3.4765e+09 | 2.13796e+06 | 0.124443 | 2.06782 | 11.2503 | 2.31237 | 0.00302603 | 0.0279495 | 0.00272727 | 1(Win) | true |
| Jsonifier (two-stage) | 2340.88 | 0.347511 | 8007.19ms | 5373214 | 160 | 9.25907e+09 | 2.18904e+06 | 0.393603 | 2.13288 | 10.7095 | 1.77573 | 0.00436453 | 0.0521831 | 0.00314586 | 2(Loss) | true |
| Glaze | 1897.87 | 0.312616 | 9708.89ms | 5373214 | 30 | 2.13736e+09 | 2.70003e+06 | 0.0853299 | 2.61259 | 13.946 | 2.50104 | 0.00425477 | 0.0294713 | 0.000930331 | 3(Loss) | true |
| simdjson (ondemand) | 1838.93 | 0.304528 | 9867.64ms | 5373214 | 160 | 1.15216e+10 | 2.78657e+06 | 0.128274 | 2.75836 | 11.6049 | 1.86633 | 0.00478386 | 0.0506912 | 0.00155237 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5075.59 | 0.293057 | 7939.77ms | 6661897 | 320 | 4.30604e+09 | 1.25173e+06 | 0.179223 | 0.975976 | 2.94121 | 0.261245 | 7.5421e-05 | 0.0278513 | 0.0014878 | 1(Win) | true |
| Glaze | 3233.94 | 0.137689 | 6194.21ms | 6661897 | 40 | 2.92678e+08 | 1.96456e+06 | 0.288235 | 1.55432 | 4.2303 | 0.46931 | 7.6521e-05 | 0.0630781 | 0.00659194 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5097.95 | 0.290627 | 7910.77ms | 6661897 | 320 | 4.19786e+09 | 1.24624e+06 | 0.203555 | 0.971888 | 2.94116 | 0.261234 | 7.52512e-05 | 0.0278299 | 0.000262173 | 1(Win) | true |
| Glaze | 3902.7 | 0.129583 | 5115.98ms | 6661897 | 40 | 1.78001e+08 | 1.62792e+06 | 0.176032 | 1.29374 | 4.22891 | 0.468988 | 7.54515e-05 | 0.0244353 | 0.00154939 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2215.35 | 0.130815 | 5714.8ms | 500299 | 80 | 6.35007e+06 | 215371 | 0.120906 | 2.24718 | 9.99023 | 1.9313 | 0.0113058 | 0.00389787 | 7.79534e-06 | 1(Win) | true |
| Glaze | 1735.81 | 0.0787968 | 7239.55ms | 500299 | 1280 | 6.00459e+07 | 274871 | 0.0709948 | 2.86223 | 12.5474 | 2.36972 | 0.0144714 | 0.00218693 | 1.16618e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1659.81 | 0.162818 | 7592.45ms | 500299 | 40 | 8.76207e+06 | 287455 | 0.0499712 | 2.97954 | 13.3259 | 2.30987 | 0.014771 | 0.0358403 | 3.61784e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1022.98 | 0.305053 | 6040.53ms | 500299 | 640 | 1.29556e+09 | 466405 | 0.0538535 | 4.8459 | 18.84 | 2.88001 | 0.0173511 | 0.0298746 | 2.76959e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2703.94 | 0.179798 | 5494.2ms | 500299 | 640 | 6.44192e+07 | 176455 | 0.0477834 | 1.82876 | 8.84192 | 1.65267 | 0.00773923 | 0.0019683 | 5.85275e-06 | 1(Win) | true |
| Glaze | 2088.23 | 0.0874353 | 6994.93ms | 500299 | 160 | 6.38551e+06 | 228482 | 0.0471998 | 2.38038 | 11.4077 | 2.0943 | 0.00955657 | 0.000611672 | 2.77334e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1943.73 | 0.0853074 | 7361.33ms | 500299 | 160 | 7.01586e+06 | 245467 | 0.201826 | 2.54687 | 12.1697 | 2.0303 | 0.0109599 | 0.0268977 | 6.22128e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1158.68 | 0.316582 | 5730.32ms | 500299 | 80 | 1.35954e+08 | 411779 | 0.380737 | 4.27639 | 17.6803 | 2.5949 | 0.00939878 | 0.0125397 | 2.19869e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10080 | 0.0354762 | 5490.2ms | 500299 | 1280 | 360929 | 47333.5 | 0.0287438 | 0.496759 | 2.16592 | 0.353749 | 0.002458 | 0.00177689 | 1.13526e-06 | 1(Win) | true |
| Glaze | 5024.61 | 0.338899 | 5307.64ms | 500299 | 30 | 3.10682e+06 | 94957 | 0.248476 | 0.987054 | 4.19114 | 0.585072 | 0.00113959 | 0.0227993 | 8.46827e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10153.8 | 0.0444418 | 5466.58ms | 500299 | 640 | 279106 | 46989.7 | 0.103487 | 0.496207 | 2.16487 | 0.353511 | 0.00246663 | 0.00167549 | 1.70523e-06 | 1(Win) | true |
| Glaze | 5722.18 | 0.161052 | 9082.68ms | 500299 | 2560 | 4.61644e+07 | 83381.2 | 0.0470635 | 0.866104 | 4.17823 | 0.582038 | 0.00109754 | 0.00207864 | 8.73618e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3459.4 | 0.160778 | 8349.27ms | 1151920 | 40 | 1.04269e+07 | 317557 | 0.278748 | 1.45017 | 6.60638 | 1.04749 | 0.00620013 | 0.0520015 | 8.17765e-05 | 1(Win) | true |
| Jsonifier | 2817.39 | 0.0484135 | 5097.44ms | 1151920 | 160 | 5.70168e+06 | 389920 | 0.0105065 | 1.79238 | 7.48875 | 1.65231 | 0.00494547 | 0.0175555 | 6.76045e-06 | 2(Loss) | true |
| Glaze | 2598.68 | 0.0800204 | 5518.24ms | 1151920 | 40 | 4.57722e+06 | 422737 | 0.0330612 | 1.94318 | 8.626 | 1.67907 | 0.00765177 | 0.0131073 | 1.31303e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2205.68 | 0.342391 | 6463.76ms | 1151920 | 320 | 9.30586e+08 | 498059 | 0.260974 | 2.26971 | 8.86727 | 1.28389 | 0.00735068 | 0.0488452 | 0.000123953 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4006.62 | 0.240481 | 8219.4ms | 1151920 | 80 | 3.47809e+07 | 274185 | 0.0098874 | 1.25442 | 6.10523 | 0.926419 | 0.00466345 | 0.0451226 | 2.396e-05 | 1(Win) | true |
| Jsonifier | 3128.56 | 0.103824 | 9999.49ms | 1151920 | 80 | 1.06326e+07 | 351138 | 0.112727 | 1.60858 | 6.99061 | 1.53171 | 0.00359505 | 0.0119695 | 6.26237e-05 | 2(Loss) | true |
| Glaze | 2946.67 | 0.175598 | 5377.14ms | 1151920 | 30 | 1.28571e+07 | 372813 | 0.00169877 | 1.73862 | 8.12971 | 1.55929 | 0.00544245 | 0.00847154 | 4.19879e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2464.85 | 0.301011 | 6158.7ms | 1151920 | 640 | 1.15189e+09 | 445690 | 0.167787 | 2.01826 | 8.36175 | 1.15948 | 0.00421111 | 0.0357858 | 8.86563e-06 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14943.5 | 0.0490322 | 5123.72ms | 1439562 | 40 | 81167.3 | 91871.2 | 0.0569404 | 0.33194 | 1.34898 | 0.258005 | 0.000849408 | 0.0185194 | 8.69188e-05 | 1(Win) | true |
| Glaze | 5235.68 | 0.179362 | 6939.21ms | 1439584 | 160 | 3.53923e+07 | 262219 | 0.138471 | 0.942918 | 3.07321 | 0.528553 | 0.00100332 | 0.0625199 | 1.58032e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14846.4 | 0.0823358 | 5148.05ms | 1439562 | 30 | 173908 | 92472 | 0.219547 | 0.334055 | 1.34874 | 0.257954 | 0.000849217 | 0.018461 | 0.000224096 | 1(Win) | true |
| Glaze | 7038.59 | 0.228002 | 5213.93ms | 1439584 | 160 | 3.16446e+07 | 195052 | 0.296143 | 0.707364 | 3.06771 | 0.527269 | 0.00101241 | 0.01693 | 7.22431e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2200.92 | 0.0704098 | 3180.43ms | 56369 | 160 | 47321.3 | 24425.1 | 0.0164763 | 2.25699 | 9.41826 | 1.90558 | 0.0044253 | 5.54383e-06 | 4.43506e-07 | 1(Win) | true |
| Glaze | 1872.97 | 0.0957791 | 3606.94ms | 56369 | 640 | 483663 | 28701.9 | 0.000745807 | 2.68263 | 11.6099 | 2.33265 | 0.00812905 | 2.07894e-05 | 6.48628e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1707.27 | 0.0703199 | 3916.87ms | 56369 | 1280 | 627545 | 31487.6 | 0.0569395 | 2.93803 | 12.3718 | 2.28601 | 0.00937105 | 1.57583e-05 | 4.94787e-06 | 3(Loss) | true |
| simdjson (ondemand) | 948.723 | 0.0701568 | 6446.76ms | 56369 | 1280 | 2.02279e+06 | 56663.2 | 0.105312 | 5.24185 | 22.2516 | 3.62836 | 0.0115902 | 3.81277e-05 | 1.59385e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3117.34 | 0.101118 | 2852.17ms | 56369 | 160 | 48651 | 17244.7 | 0.0267402 | 1.60059 | 7.30401 | 1.42156 | 0.00371281 | 4.54594e-06 | 4.43506e-07 | 1(Win) | true |
| Glaze | 2867.7 | 0.0543822 | 3025.68ms | 56369 | 4890 | 508203 | 18745.9 | 0.211147 | 1.74706 | 9.18288 | 1.77481 | 0.00220476 | 1.86907e-05 | 9.85327e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2353.44 | 0.0457753 | 3442.24ms | 56369 | 1280 | 139942 | 22842.2 | 0.283943 | 2.1337 | 10.2651 | 1.80352 | 0.00400817 | 5.46067e-06 | 1.09491e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1121.37 | 0.0426115 | 5939.59ms | 56369 | 4890 | 2.04053e+06 | 47939.1 | 0.00152025 | 4.40853 | 19.9159 | 3.09586 | 0.00866822 | 1.08727e-05 | 2.81159e-06 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14190 | 0.0452472 | 1130.73ms | 56369 | 1280 | 3761.05 | 3788.42 | 0.0523249 | 0.353454 | 1.42135 | 0.238642 | 0.000177666 | 6.47242e-06 | 1.34438e-06 | 1(Win) | true |
| Glaze | 5044.02 | 0.114185 | 1831.12ms | 56369 | 1280 | 189563 | 10657.7 | 0.0651655 | 0.984481 | 3.49252 | 0.485498 | 0.000109421 | 7.48417e-06 | 2.21753e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14456.4 | 0.0303935 | 1127.29ms | 56369 | 2560 | 3270.13 | 3718.62 | 0.000703802 | 0.346862 | 1.41182 | 0.236478 | 0.000194665 | 3.87375e-06 | 7.13768e-07 | 1(Win) | true |
| Glaze | 5591.8 | 0.0548787 | 1719.49ms | 56369 | 4890 | 136112 | 9613.67 | 0.068832 | 0.890759 | 3.41113 | 0.467048 | 0.000122335 | 5.53612e-06 | 1.13915e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2492.09 | 0.142897 | 3959.3ms | 83958 | 160 | 337258 | 32129.1 | 0.017096 | 1.99225 | 8.83573 | 1.55572 | 0.00379081 | 3.49877e-06 | 2.23326e-07 | 1(Win) | true |
| Glaze | 2205.75 | 0.0359239 | 4385.2ms | 83958 | 1280 | 217665 | 36299.9 | 0.0415548 | 2.24678 | 10.569 | 2.16588 | 0.00496294 | 1.14455e-05 | 3.17309e-06 | 2(Loss) | true |
| Jsonifier | 1740.43 | 0.0310234 | 5351.39ms | 83958 | 4890 | 996084 | 46005 | 0.00207155 | 2.86901 | 9.82014 | 2.17521 | 0.00807893 | 9.02438e-06 | 2.86442e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1385.4 | 0.0380434 | 6523.56ms | 83958 | 4890 | 2.36398e+06 | 57794.8 | 0.0326079 | 3.59208 | 15.3548 | 2.45547 | 0.00763358 | 1.27949e-05 | 3.80948e-06 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3292.6 | 0.0199268 | 3583.8ms | 83958 | 4890 | 114824 | 24317.8 | 0.242493 | 1.52008 | 7.41025 | 1.22938 | 0.00213862 | 4.10664e-06 | 1.18133e-06 | 1(Win) | true |
| Glaze | 2910.86 | 0.0293321 | 3876.62ms | 83958 | 4890 | 318331 | 27506.9 | 0.0868254 | 1.71542 | 8.94778 | 1.79415 | 0.00357134 | 5.40488e-06 | 1.33478e-06 | 2(Loss) | true |
| Jsonifier | 2123.38 | 0.0295993 | 4901.21ms | 83958 | 1280 | 159457 | 37708.2 | 0.0183862 | 2.35269 | 8.39442 | 1.84901 | 0.00509826 | 4.19667e-06 | 6.79283e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1615.6 | 0.085016 | 6115.56ms | 83958 | 1280 | 2.27231e+06 | 49559.7 | 0.132612 | 3.07153 | 13.7831 | 2.09801 | 0.00650673 | 7.37906e-06 | 1.33065e-06 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15989.3 | 0.0220026 | 1318.3ms | 94370 | 4890 | 7500.09 | 5628.66 | 0.0284759 | 0.312429 | 1.2816 | 0.241676 | 0.000241262 | 3.10963e-06 | 4.81072e-07 | 1(Win) | true |
| Glaze | 4083.9 | 0.0492674 | 2965.78ms | 94370 | 4890 | 576429 | 22037.3 | 0.097583 | 1.22235 | 4.17739 | 0.678012 | 0.00150423 | 1.22197e-05 | 4.17146e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16315.3 | 0.0265463 | 1306.82ms | 94370 | 4890 | 10485.7 | 5516.2 | 0.0125661 | 0.306253 | 1.27585 | 0.240384 | 0.000242397 | 3.20715e-06 | 5.39581e-07 | 1(Win) | true |
| Glaze | 4443.16 | 0.0568489 | 2786.42ms | 94370 | 4890 | 648391 | 20255.4 | 0.142826 | 1.12055 | 4.12562 | 0.666091 | 0.00146857 | 3.9981e-06 | 1.11383e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1634.22 | 0.119172 | 3864.82ms | 53331 | 320 | 440192 | 31122.2 | 0.094103 | 3.07678 | 9.95219 | 1.79771 | 0.0129198 | 2.68371e-05 | 1.49421e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1556.94 | 0.155608 | 4034.45ms | 53331 | 320 | 826855 | 32666.8 | 0.00252556 | 3.21754 | 10.6834 | 1.89197 | 0.0125265 | 6.46903e-05 | 2.12119e-05 | 2(Loss) | true |
| Glaze | 1409.73 | 0.0588161 | 4368.2ms | 53331 | 2560 | 1.15271e+06 | 36078.1 | 0.0461102 | 3.536 | 11.7124 | 2.25125 | 0.022339 | 4.15668e-05 | 1.15142e-05 | 3(Loss) | true |
| simdjson (ondemand) | 964.523 | 0.0514147 | 6035.52ms | 53331 | 1280 | 940845 | 52731.1 | 0.0182044 | 5.19233 | 15.4787 | 2.77915 | 0.0157607 | 4.28046e-05 | 1.21148e-05 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2450.11 | 0.0479254 | 3306.29ms | 53331 | 640 | 63343.1 | 20758.4 | 0.0413257 | 2.06572 | 8.45262 | 1.38652 | 0.000610661 | 4.04608e-05 | 2.33213e-05 | 1(Win) | true |
| Jsonifier | 2244.38 | 0.0439964 | 3611ms | 53331 | 2560 | 254472 | 22661.2 | 0.0119373 | 2.22971 | 7.68005 | 1.28053 | 0.00925788 | 1.57771e-05 | 3.97722e-06 | 2(Loss) | true |
| Glaze | 1862.6 | 0.0571464 | 4086.29ms | 53331 | 2560 | 623360 | 27306.1 | 0.247091 | 2.67473 | 9.44264 | 1.7353 | 0.0181426 | 1.07524e-05 | 3.66959e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1151.21 | 0.0402249 | 5773.69ms | 53331 | 640 | 202126 | 44180 | 0.058906 | 4.39038 | 13.4772 | 2.3265 | 0.011424 | 1.49128e-05 | 4.04315e-06 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16238.8 | 0.112602 | 1093.18ms | 58581 | 160 | 2401.12 | 3440.34 | 0.251702 | 0.309063 | 1.07834 | 0.164524 | 3.55277e-05 | 1.02422e-05 | 5.76125e-06 | 1(Win) | true |
| Glaze | 4931.57 | 0.316218 | 1888.12ms | 58581 | 640 | 821288 | 11328.5 | 0.441053 | 1.00914 | 2.62725 | 0.382838 | 4.27293e-05 | 2.03511e-05 | 8.29514e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16540.6 | 0.0562323 | 1087.34ms | 58581 | 2560 | 9234.74 | 3377.58 | 0.0164084 | 0.303871 | 1.06903 | 0.162459 | 3.43608e-05 | 4.3076e-06 | 1.24694e-06 | 1(Win) | true |
| Glaze | 5490.69 | 0.202024 | 1769.35ms | 58581 | 2560 | 1.0817e+06 | 10174.9 | 0.440686 | 0.904959 | 2.55385 | 0.36587 | 5.14112e-05 | 6.72146e-06 | 1.08024e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1928.4 | 0.0865868 | 3989.75ms | 65103 | 2560 | 1.98953e+06 | 32196.1 | 0.00515612 | 2.61404 | 9.16544 | 1.57016 | 0.00822413 | 4.76349e-05 | 9.73217e-06 | 1(Win) | true |
| Jsonifier | 1532.63 | 0.0437606 | 4798.67ms | 65103 | 2560 | 804518 | 40510.2 | 0.149103 | 3.26065 | 9.70489 | 1.84987 | 0.0117593 | 5.4553e-05 | 3.25206e-05 | 2(Loss) | true |
| Glaze | 1487.91 | 0.0386182 | 4950.36ms | 65103 | 4890 | 1.26981e+06 | 41727.6 | 0.37339 | 3.37477 | 10.9554 | 2.113 | 0.022933 | 3.28094e-05 | 8.30523e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1257.66 | 0.0475055 | 5696.26ms | 65103 | 2560 | 1.40801e+06 | 49367.3 | 0.157321 | 3.95211 | 12.897 | 2.2801 | 0.00363529 | 7.37893e-05 | 3.11286e-05 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2481 | 0.0528771 | 3865.77ms | 65103 | 4890 | 856236 | 25025.1 | 0.126197 | 2.01681 | 7.34653 | 1.15779 | 0.0067593 | 1.93747e-05 | 4.9379e-06 | 1(Win) | true |
| Jsonifier | 1952.41 | 0.120423 | 4518.91ms | 65103 | 320 | 469272 | 31800.1 | 0.201303 | 2.56365 | 7.85688 | 1.42987 | 0.00863814 | 1.51203e-05 | 5.23209e-06 | 2(Loss) | true |
| Glaze | 1896.51 | 0.111446 | 4738.88ms | 65103 | 640 | 851921 | 32737.6 | 0.429233 | 2.65383 | 9.09351 | 1.69031 | 0.0186893 | 1.01042e-05 | 2.66405e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1385.17 | 0.0445329 | 5797.89ms | 65103 | 640 | 254999 | 44822.8 | 0.0282302 | 3.65311 | 11.2725 | 1.91362 | 0.00972687 | 1.74243e-05 | 6.76812e-06 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16688 | 0.0274899 | 1195.67ms | 78778 | 4890 | 7489.55 | 4501.94 | 0.0188466 | 0.305393 | 1.0924 | 0.183668 | 2.52061e-05 | 3.21631e-06 | 6.82719e-07 | 1(Win) | true |
| Glaze | 4710.88 | 0.0896103 | 2346.28ms | 78778 | 4890 | 998690 | 15947.9 | 0.111416 | 1.07402 | 3.02049 | 0.48883 | 0.000349913 | 1.02823e-05 | 2.85807e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16901.7 | 0.035335 | 1196.78ms | 78778 | 2560 | 6315.41 | 4445.04 | 0.101357 | 0.302106 | 1.08543 | 0.182132 | 3.5176e-05 | 1.18014e-05 | 7.54692e-06 | 1(Win) | true |
| Glaze | 5312.87 | 0.153641 | 2163.73ms | 78778 | 2560 | 1.20839e+06 | 14140.9 | 0.111066 | 0.95057 | 2.95713 | 0.474155 | 0.000362951 | 9.63447e-06 | 2.71729e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2396.61 | 0.0271817 | 1215.42ms | 11812 | 4890 | 7982.01 | 4700.3 | 0.0504277 | 2.10841 | 10.0226 | 1.75512 | 0.0047149 | 2.49824e-05 | 7.75614e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1802.81 | 0.0887598 | 1364.56ms | 11812 | 640 | 19686 | 6248.46 | 0.50971 | 2.7899 | 13.4821 | 2.29716 | 0.00517032 | 2.43397e-05 | 3.4393e-06 | 2(Loss) | true |
| Glaze | 1703.63 | 0.0509969 | 1408.3ms | 11812 | 1280 | 14554.4 | 6612.23 | 0.0896798 | 2.95559 | 13.7401 | 2.66551 | 0.00279853 | 1.23682e-05 | 3.30702e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1059.94 | 0.0261022 | 1814.35ms | 11812 | 4890 | 37631.3 | 10627.8 | 0.0736524 | 4.71702 | 20.3962 | 3.41472 | 0.00844247 | 3.42274e-05 | 8.82954e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2763.22 | 0.10631 | 1202.02ms | 11812 | 1280 | 24042.3 | 4076.7 | 0.092858 | 1.82723 | 9.02955 | 1.52531 | 0.00362436 | 1.69981e-05 | 2.44719e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1985.54 | 0.100852 | 1362.33ms | 11812 | 640 | 20952.6 | 5673.43 | 0.010439 | 2.54203 | 12.4981 | 2.06942 | 0.00463181 | 1.73288e-05 | 1.45509e-06 | 2(Loss) | true |
| Glaze | 1955.95 | 0.0329427 | 1373.47ms | 11812 | 4890 | 17601.8 | 5759.24 | 0.116365 | 2.5749 | 12.6005 | 2.41153 | 0.00114675 | 1.40407e-05 | 8.13702e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1114.28 | 0.0997969 | 1803.52ms | 11812 | 640 | 65143.7 | 10109.5 | 0.0874788 | 4.46918 | 19.5884 | 3.23315 | 0.0072425 | 1.53446e-05 | 1.05825e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11573.9 | 0.0584854 | 836.792ms | 11812 | 2560 | 829.518 | 973.296 | 0.137729 | 0.451055 | 2.08737 | 0.342195 | 0.00014498 | 1.38233e-05 | 1.52123e-06 | 1(Win) | true |
| Glaze | 3852.84 | 0.0939206 | 1040.5ms | 11812 | 4890 | 36873.7 | 2923.77 | 0.128128 | 1.32176 | 5.64951 | 0.825855 | 0.000428475 | 2.64886e-05 | 6.752e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12281.4 | 0.0890727 | 830.068ms | 11812 | 1280 | 854.377 | 917.223 | 0.019083 | 0.427595 | 2.04081 | 0.331612 | 0.000110917 | 8.06912e-06 | 3.30702e-07 | 1(Win) | true |
| Glaze | 4289.28 | 0.179504 | 1000.32ms | 11812 | 1280 | 28447 | 2626.27 | 0.0745433 | 1.19085 | 5.37437 | 0.765324 | 0.000420388 | 1.52123e-05 | 1.91807e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3447.3 | 0.0530169 | 1450.29ms | 25388 | 640 | 8873.76 | 7023.44 | 0.0168603 | 1.47432 | 7.17254 | 1.13997 | 0.00266471 | 4.55432e-06 | 1.84634e-07 | 1(Win) | true |
| Jsonifier | 2896.34 | 0.0325858 | 1575.21ms | 25388 | 2560 | 18995.6 | 8359.46 | 0.0331522 | 1.74731 | 7.861 | 1.64802 | 0.00464671 | 8.40087e-06 | 1.36937e-06 | 2(Loss) | true |
| Glaze | 2351.32 | 0.0846174 | 1771.87ms | 25388 | 30 | 2277.59 | 10297.2 | 0.0430354 | 2.15931 | 9.63755 | 1.89444 | 0.00566147 | 5.25183e-05 | 3.54498e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2158.8 | 0.0887667 | 1874.9ms | 25388 | 320 | 31716.2 | 11215.4 | 0.0914755 | 2.34877 | 10.1243 | 1.61965 | 0.00400694 | 7.26229e-06 | 7.38538e-07 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3739.24 | 0.0461486 | 1441.48ms | 25388 | 640 | 5714.61 | 6475.08 | 0.196762 | 1.36174 | 6.73783 | 1.03899 | 0.0025559 | 5.66212e-06 | 1.84634e-07 | 1(Win) | true |
| Jsonifier | 3113.18 | 0.0353197 | 1566.12ms | 25388 | 1280 | 9658.1 | 7777.22 | 0.0388705 | 1.63243 | 7.43075 | 1.54801 | 0.00428967 | 7.4777e-06 | 1.2309e-06 | 2(Loss) | true |
| Glaze | 2546.02 | 0.100096 | 1753.67ms | 25388 | 40 | 3624.32 | 9509.7 | 0.038572 | 1.99618 | 9.1043 | 1.77588 | 0.00502895 | 1.18166e-05 | 4.92359e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2277.11 | 0.076089 | 1872.87ms | 25388 | 640 | 41890.4 | 10632.7 | 0.0461641 | 2.21753 | 9.73644 | 1.53231 | 0.00355249 | 1.00318e-05 | 1.90789e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15365.3 | 0.0731799 | 940.632ms | 31235 | 1280 | 2576.3 | 1938.66 | 0.00261947 | 0.330902 | 1.4211 | 0.263519 | 8.40904e-05 | 4.52717e-06 | 3.25156e-07 | 1(Win) | true |
| Glaze | 5147.46 | 0.0755307 | 1328.98ms | 31235 | 1280 | 24454.3 | 5786.94 | 0.0574914 | 0.97403 | 3.70988 | 0.655771 | 0.00232149 | 6.57816e-06 | 1.0505e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16158.7 | 0.0620398 | 930.345ms | 31235 | 160 | 209.282 | 1843.47 | 0.0227102 | 0.314249 | 1.40173 | 0.258844 | 5.30255e-05 | 6.40307e-06 | 0 | 1(Win) | true |
| Glaze | 5617.93 | 0.0937385 | 1278.59ms | 31235 | 1280 | 31621.1 | 5302.31 | 0.111016 | 0.907726 | 3.58447 | 0.627565 | 0.00231819 | 2.10851e-05 | 1.21808e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2465.24 | 0.0138719 | 4911.44ms | 108313 | 2560 | 86488.2 | 41900.7 | 0.0330285 | 2.01468 | 8.80074 | 1.76934 | 0.00310623 | 9.71216e-06 | 3.10515e-06 | 1(Win) | true |
| Glaze | 2315.1 | 0.0197689 | 5218.52ms | 108313 | 4890 | 380448 | 44618.1 | 0.132241 | 2.17603 | 10.5545 | 1.88645 | 0.00286856 | 7.85235e-06 | 3.0454e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1964.77 | 0.0396368 | 6007.46ms | 108313 | 160 | 69479 | 52573.7 | 0.19858 | 2.5734 | 11.9302 | 2.08174 | 0.00313282 | 7.2706e-06 | 4.61625e-06 | 3(Loss) | true |
| simdjson (ondemand) | 772.2 | 0.0717724 | 7216.67ms | 108313 | 30 | 276527 | 133768 | 0.0703705 | 6.54506 | 28.4362 | 4.49507 | 0.00463656 | 9.2325e-06 | 1.53875e-06 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2938.34 | 0.014846 | 4444.41ms | 108313 | 4890 | 133194 | 35154.4 | 0.142689 | 1.71801 | 8.01784 | 1.58714 | 0.00268171 | 3.84027e-06 | 1.11583e-06 | 1(Win) | true |
| Glaze | 2625.98 | 0.0247491 | 4888.86ms | 108313 | 4890 | 463454 | 39335.9 | 0.082586 | 1.92158 | 9.83214 | 1.71939 | 0.00247879 | 1.46115e-05 | 8.02793e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2214.14 | 0.0925894 | 5598.83ms | 108313 | 160 | 298533 | 46652.6 | 0.227985 | 2.27041 | 11.1452 | 1.89929 | 0.00285267 | 5.94342e-06 | 2.30813e-06 | 3(Loss) | true |
| simdjson (ondemand) | 805.091 | 0.0290706 | 7030.45ms | 108313 | 1280 | 1.78069e+06 | 128303 | 0.104483 | 6.24978 | 27.7348 | 4.33441 | 0.00375347 | 1.39353e-05 | 5.91457e-06 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18172.5 | 0.019888 | 1316.63ms | 108313 | 4890 | 6249.19 | 5684.15 | 0.141818 | 0.274946 | 1.24715 | 0.328225 | 0.000221901 | 2.9038e-06 | 5.17322e-07 | 1(Win) | true |
| Glaze | 4523.73 | 0.214174 | 3047.44ms | 108313 | 640 | 1.53066e+06 | 22834.1 | 0.147232 | 1.0994 | 3.26324 | 0.411373 | 0.000269387 | 4.24118e-06 | 9.52102e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18376 | 0.0220471 | 1315.09ms | 108313 | 4890 | 7510.5 | 5621.21 | 0.0110089 | 0.272131 | 1.2424 | 0.327145 | 0.000213601 | 3.73265e-06 | 8.47729e-07 | 1(Win) | true |
| Glaze | 5437.92 | 0.0734473 | 2651.98ms | 108313 | 4890 | 951825 | 18995.4 | 0.0372939 | 0.929915 | 3.21806 | 0.400866 | 0.000266068 | 4.55017e-06 | 1.25366e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2967.72 | 0.0852655 | 6609.63ms | 183677 | 40 | 101314 | 59024.4 | 0.0102207 | 1.67175 | 7.81645 | 1.28951 | 0.00206395 | 1.21137e-05 | 9.25538e-06 | 1(Win) | true |
| Glaze | 2547.79 | 0.0750988 | 7615.6ms | 183677 | 320 | 853094 | 68752.9 | 0.0480938 | 1.96315 | 9.24411 | 1.73047 | 0.00317277 | 3.16452e-06 | 9.18732e-07 | 2(Loss) | true |
| Jsonifier | 2160.35 | 0.0971066 | 8785.71ms | 183677 | 80 | 495962 | 81083.1 | 0.0930277 | 2.30438 | 8.43071 | 1.89164 | 0.00258552 | 7.07764e-06 | 3.2666e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1280.47 | 0.0226264 | 7374.35ms | 183677 | 2560 | 2.45268e+06 | 136800 | 0.00251302 | 3.94319 | 17.2947 | 2.67458 | 0.00254748 | 1.11737e-05 | 4.91905e-06 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3384.33 | 0.0156253 | 6120.47ms | 183677 | 2560 | 167440 | 51758.5 | 0.0114895 | 1.49192 | 7.3557 | 1.18244 | 0.00159607 | 3.77276e-06 | 1.41638e-06 | 1(Win) | true |
| Glaze | 2766.77 | 0.0667615 | 7214.65ms | 183677 | 160 | 285849 | 63311.5 | 0.0626961 | 1.79467 | 8.81978 | 1.63257 | 0.00293174 | 2.34787e-06 | 3.06244e-07 | 2(Loss) | true |
| Jsonifier | 2352.52 | 0.0301917 | 8354.93ms | 183677 | 640 | 323444 | 74459.7 | 0.0469476 | 2.11134 | 7.96644 | 1.78375 | 0.00223349 | 7.1542e-06 | 2.54353e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1340.19 | 0.0693963 | 7160.14ms | 183677 | 40 | 329088 | 130704 | 0.0390346 | 3.77217 | 16.8784 | 2.5797 | 0.00210002 | 4.7638e-06 | 1.49719e-06 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20412.5 | 0.040509 | 1740.78ms | 213963 | 640 | 10494.7 | 9996.37 | 0.0115966 | 0.248582 | 1.11888 | 0.275211 | 0.000143541 | 8.39806e-07 | 2.11777e-07 | 1(Win) | true |
| Glaze | 4885.39 | 0.111812 | 4929.9ms | 213963 | 640 | 1.39585e+06 | 41767.6 | 0.0233115 | 1.03183 | 3.63928 | 0.597898 | 0.000662447 | 3.09633e-06 | 1.27066e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20648.8 | 0.0486336 | 1732.75ms | 213963 | 640 | 14782.2 | 9881.96 | 0.000901255 | 0.245654 | 1.11647 | 0.274664 | 0.000143936 | 1.02237e-06 | 2.33685e-07 | 1(Win) | true |
| Glaze | 5512.97 | 0.0503997 | 4449.11ms | 213963 | 4890 | 1.70166e+06 | 37012.9 | 0.0704074 | 0.913699 | 3.61276 | 0.591747 | 0.000657148 | 4.01423e-06 | 1.38586e-06 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 844.965 | 0.324964 | 6445.18ms | 1834197 | 160 | 7.2411e+09 | 2.07018e+06 | 0.123004 | 5.9733 | 26.9528 | 5.76284 | 0.0296707 | 0.0812824 | 2.72565e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 725.266 | 0.289505 | 7512.32ms | 1834197 | 160 | 7.80062e+09 | 2.41184e+06 | 0.703125 | 6.94382 | 31.0098 | 6.28738 | 0.0361627 | 0.144475 | 0.00129821 | 2(Loss) | true |
| Glaze | 685.823 | 0.76911 | 7873.6ms | 1834197 | 30 | 1.15443e+10 | 2.55055e+06 | 0.121151 | 7.36155 | 32.0074 | 6.49839 | 0.0359367 | 0.081411 | 0.00112362 | 3(Loss) | true |
| simdjson (ondemand) | 564.867 | 0.429489 | 9604.39ms | 1834197 | 80 | 1.41512e+10 | 3.09671e+06 | 0.117607 | 8.93799 | 36.8105 | 6.45866 | 0.0464829 | 0.146109 | 2.07039e-05 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 941.983 | 0.0785621 | 6467.61ms | 1834197 | 30 | 6.38489e+07 | 1.85696e+06 | 0.0594471 | 5.36387 | 23.9455 | 5.05704 | 0.0291953 | 0.0553268 | 1.32483e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 794.988 | 0.265648 | 7522.18ms | 1834197 | 160 | 5.46645e+09 | 2.20032e+06 | 0.466058 | 6.34582 | 28.0022 | 5.5822 | 0.0351841 | 0.118335 | 5.65847e-05 | 2(Loss) | true |
| Glaze | 754.078 | 0.272674 | 7875.98ms | 1834197 | 160 | 6.40127e+09 | 2.31969e+06 | 0.0375437 | 6.69933 | 28.993 | 5.79261 | 0.0343793 | 0.0580498 | 9.20021e-06 | 3(Loss) | true |
| simdjson (ondemand) | 617.51 | 0.212826 | 9491.87ms | 1834197 | 160 | 5.81532e+09 | 2.83271e+06 | 0.107946 | 8.17781 | 33.7836 | 5.75177 | 0.0418198 | 0.118082 | 0.00183893 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1196.36 | 0.262533 | 9249.73ms | 1834197 | 320 | 4.71506e+09 | 1.46212e+06 | 0.166406 | 4.20057 | 12.6312 | 0.909542 | 0.001611 | 0.0589648 | 8.98384e-06 | 1(Win) | true |
| Glaze | 644.889 | 0.23699 | 8543.11ms | 1833577 | 30 | 1.23883e+09 | 2.71153e+06 | 0.0172726 | 7.86632 | 16.0121 | 0.996547 | 0.0010101 | 0.0490611 | 0.000817782 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1203.47 | 0.223418 | 9230.91ms | 1834197 | 320 | 3.37448e+09 | 1.45349e+06 | 0.17846 | 4.197 | 12.631 | 0.909502 | 0.00160923 | 0.0588245 | 0.000160327 | 1(Win) | true |
| Glaze | 631.711 | 0.302253 | 8564.6ms | 1833577 | 80 | 5.60007e+09 | 2.76809e+06 | 0.489418 | 7.88929 | 16.0113 | 0.996381 | 0.00102205 | 0.0489845 | 3.01664e-05 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2599.66 | 0.138191 | 8556.17ms | 7351818 | 30 | 4.16715e+08 | 2.69698e+06 | 0.634749 | 1.94436 | 8.69472 | 1.60921 | 0.00931991 | 0.060623 | 0.000800963 | 1(Win) | true |
| Jsonifier | 2462.35 | 0.219943 | 8866.06ms | 7351818 | 160 | 6.27527e+09 | 2.84738e+06 | 0.221952 | 2.02454 | 9.56796 | 2.2097 | 0.00677098 | 0.0336238 | 3.60124e-05 | 2(Loss) | true |
| Glaze | 2141.62 | 0.265751 | 10208.7ms | 7351818 | 160 | 1.21109e+10 | 3.27381e+06 | 0.315771 | 2.35758 | 11.0336 | 2.24396 | 0.00921652 | 0.0330466 | 3.02587e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2070.5 | 0.405367 | 5101.57ms | 7351818 | 80 | 1.50739e+10 | 3.38625e+06 | 0.0859364 | 2.43308 | 10.0965 | 1.65089 | 0.0110841 | 0.0607792 | 0.000887032 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2761.27 | 0.725371 | 8562.87ms | 7351818 | 40 | 1.35691e+10 | 2.53913e+06 | 0.176572 | 1.81031 | 7.94431 | 1.4333 | 0.00907731 | 0.0540474 | 9.34497e-05 | 1(Win) | true |
| Jsonifier | 2653.13 | 0.608537 | 8901.11ms | 7351818 | 40 | 1.03444e+10 | 2.64263e+06 | 0.376488 | 1.88041 | 8.81777 | 2.03385 | 0.00657943 | 0.027102 | 2.54631e-05 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2271.35 | 0.229563 | 10245.6ms | 7351818 | 160 | 8.03421e+09 | 3.08681e+06 | 0.25342 | 2.2044 | 10.2819 | 2.06811 | 0.00893394 | 0.0271202 | 0.000893537 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2267.75 | 0.126927 | 5021.21ms | 7351818 | 30 | 4.61989e+08 | 3.09172e+06 | 0.190112 | 2.21968 | 9.34152 | 1.47446 | 0.00993012 | 0.0535093 | 7.79762e-05 | 3(Tie) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4968.43 | 0.537794 | 5925.53ms | 9930848 | 80 | 8.40728e+09 | 1.90619e+06 | 0.011519 | 0.997693 | 3.39917 | 0.427912 | 0.000514459 | 0.02472 | 0.000620716 | 1(Win) | true |
| Glaze | 3626.4 | 0.372775 | 8129.33ms | 9930228 | 160 | 1.51629e+10 | 2.61146e+06 | 0.00981274 | 1.37729 | 4.21671 | 0.484708 | 0.00111237 | 0.04127 | 0.00031584 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4972.88 | 0.321107 | 5932.44ms | 9930848 | 160 | 5.98377e+09 | 1.90449e+06 | 0.77993 | 0.996448 | 3.39914 | 0.427905 | 0.000520085 | 0.0247185 | 0.00133554 | 1(Win) | true |
| Glaze | 3998.28 | 0.393485 | 7394.83ms | 9930228 | 80 | 6.94895e+09 | 2.36857e+06 | 0.373884 | 1.25276 | 4.21647 | 0.484654 | 0.00111744 | 0.0220076 | 1.36339e-05 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 833.031 | 0.3583 | 6553.47ms | 1834197 | 160 | 9.05699e+09 | 2.09983e+06 | 0.145433 | 5.98502 | 26.5395 | 5.63511 | 0.0310072 | 0.0821187 | 0.00620655 | 1(Win) | true |
| Jsonifier (two-stage) | 722.238 | 0.290345 | 7531.4ms | 1834197 | 80 | 3.95593e+09 | 2.42195e+06 | 0.154813 | 6.85078 | 30.5821 | 6.18638 | 0.0368402 | 0.145489 | 0.00115589 | 2(Loss) | true |
| Glaze | 674.577 | 0.276158 | 8103.14ms | 1834197 | 160 | 8.20471e+09 | 2.59307e+06 | 0.285146 | 7.44082 | 31.9797 | 6.48927 | 0.0358662 | 0.0816524 | 0.00471734 | 3(Loss) | true |
| simdjson (ondemand) | 552.504 | 0.588284 | 9890.77ms | 1834197 | 30 | 1.04068e+10 | 3.166e+06 | 0.186258 | 8.9888 | 36.8024 | 6.44957 | 0.0462977 | 0.146347 | 0.00196066 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 935.309 | 0.299785 | 6540.17ms | 1834197 | 160 | 5.02946e+09 | 1.87021e+06 | 0.0618057 | 5.2988 | 23.5583 | 4.93991 | 0.0301928 | 0.0559092 | 0.00162855 | 1(Win) | true |
| Jsonifier (two-stage) | 798.848 | 0.369703 | 7518.27ms | 1834197 | 160 | 1.04856e+10 | 2.18969e+06 | 0.0735586 | 6.20594 | 27.6017 | 5.49123 | 0.0356393 | 0.11929 | 0.000699693 | 2(Loss) | true |
| Glaze | 751.737 | 0.0753524 | 8084.37ms | 1834197 | 40 | 1.22974e+08 | 2.32691e+06 | 0.176205 | 6.71661 | 28.9951 | 5.79289 | 0.0348792 | 0.058313 | 0.00378082 | 3(Loss) | true |
| simdjson (ondemand) | 593.458 | 0.275142 | 9893.55ms | 1834197 | 160 | 1.05231e+10 | 2.94752e+06 | 0.328934 | 8.31988 | 33.8028 | 5.75073 | 0.0418696 | 0.118946 | 0.0154083 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1217.49 | 0.0717081 | 9132.54ms | 1834197 | 30 | 3.18436e+07 | 1.43675e+06 | 0.304569 | 4.07482 | 12.6249 | 0.909544 | 0.00133141 | 0.060013 | 1.94454e-05 | 1(Win) | true |
| Glaze | 606.893 | 0.630993 | 8925.5ms | 1833577 | 30 | 9.91619e+09 | 2.88129e+06 | 0.096619 | 8.13445 | 16.0115 | 0.996581 | 0.00103044 | 0.0816086 | 0.0127153 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1215.74 | 0.0312176 | 9092.53ms | 1834197 | 40 | 8.06994e+06 | 1.43882e+06 | 0.142935 | 4.07678 | 12.6247 | 0.909504 | 0.00131919 | 0.0596185 | 3.82865e-05 | 1(Win) | true |
| Glaze | 639.087 | 0.314678 | 8505.12ms | 1833577 | 80 | 5.93066e+09 | 2.73615e+06 | 0.160678 | 7.81534 | 16.0106 | 0.996384 | 0.0011513 | 0.0489157 | 0.00492266 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2545.81 | 0.736478 | 8500.92ms | 7351818 | 40 | 1.64557e+10 | 2.75403e+06 | 0.00283744 | 1.95709 | 8.58855 | 1.58423 | 0.00941668 | 0.0607959 | 0.00388219 | 1(Win) | true |
| Jsonifier | 2424.96 | 0.637744 | 9109.89ms | 7351818 | 40 | 1.35998e+10 | 2.89128e+06 | 0.026463 | 2.07471 | 9.42892 | 2.18473 | 0.00699393 | 0.0340419 | 0.00905105 | 2(Loss) | true |
| Glaze | 2059.33 | 0.294903 | 5106.21ms | 7351818 | 80 | 8.06468e+09 | 3.40462e+06 | 0.781283 | 2.40909 | 11.0265 | 2.24182 | 0.00934836 | 0.0332972 | 0.00743128 | 3(Loss) | true |
| simdjson (ondemand) | 1927.75 | 0.294177 | 5437.01ms | 7351818 | 80 | 9.15795e+09 | 3.63702e+06 | 0.317855 | 2.57064 | 10.0943 | 1.64848 | 0.0110969 | 0.0607348 | 0.0173907 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2740.57 | 0.31744 | 8615.68ms | 7351818 | 160 | 1.05524e+10 | 2.55832e+06 | 0.836741 | 1.81268 | 7.8448 | 1.41075 | 0.00914686 | 0.0543361 | 0.0135157 | 1(Win) | true |
| Jsonifier | 2651.12 | 0.569518 | 8886.21ms | 7351818 | 40 | 9.07416e+09 | 2.64463e+06 | 0.0915381 | 1.87747 | 8.68428 | 2.01107 | 0.00673845 | 0.0274384 | 0.00309243 | 2(Loss) | true |
| Glaze | 2235.65 | 0.278559 | 5114.11ms | 7351818 | 80 | 6.10531e+09 | 3.13611e+06 | 0.508595 | 2.22773 | 10.2821 | 2.06811 | 0.00910527 | 0.0273722 | 0.00837457 | 3(Loss) | true |
| simdjson (ondemand) | 2138.21 | 0.773966 | 5315.95ms | 7351818 | 30 | 1.93221e+10 | 3.27903e+06 | 0.135216 | 2.32669 | 9.34641 | 1.47427 | 0.00996365 | 0.0535117 | 0.0148161 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4835.07 | 0.337581 | 6132.57ms | 9930848 | 160 | 6.99589e+09 | 1.95877e+06 | 0.446579 | 1.02478 | 3.41849 | 0.427912 | 0.000396534 | 0.0248022 | 0.00302271 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 2661.1 | 0.437151 | 5548.4ms | 9930228 | 80 | 1.9362e+10 | 3.55876e+06 | 3.11486 | 1.87691 | 4.21666 | 0.48473 | 0.00104567 | 0.0750094 | 0.0323429 | -(Loss) | false |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4855.95 | 0.46255 | 6070.68ms | 9930848 | 80 | 6.51074e+09 | 1.95035e+06 | 0.407018 | 1.01989 | 3.41846 | 0.427905 | 0.00039514 | 0.0247517 | 0.00044649 | 1(Win) | true |
| Glaze | 3803.4 | 0.317282 | 7747.36ms | 9930228 | 160 | 9.98587e+09 | 2.48993e+06 | 0.121835 | 1.30702 | 4.21632 | 0.484654 | 0.00108179 | 0.0219941 | 0.00532464 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1276.84 | 0.0602693 | 9030.43ms | 461466 | 160 | 6.90425e+06 | 344669 | 0.0628225 | 3.95586 | 17.3728 | 3.29348 | 0.0190656 | 0.0339589 | 1.01714e-05 | 1(Win) | true |
| Glaze | 1176.02 | 0.227806 | 9728.8ms | 461466 | 640 | 4.65111e+08 | 374218 | 0.161386 | 4.23369 | 19.1637 | 3.79023 | 0.0131792 | 0.0172142 | 1.98654e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1111.13 | 0.228053 | 5160.31ms | 461466 | 30 | 2.4476e+07 | 396072 | 0.1747 | 4.53151 | 18.8893 | 3.55541 | 0.0242432 | 0.0766976 | 0.00041202 | 3(Loss) | true |
| simdjson (ondemand) | 810.888 | 0.310376 | 7012.18ms | 461466 | 640 | 1.816e+09 | 542724 | 0.111378 | 6.10042 | 25.3612 | 4.4811 | 0.0114776 | 0.0781828 | 2.51745e-05 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1803.39 | 0.0531021 | 8119.42ms | 461466 | 40 | 671709 | 244033 | 0.12328 | 2.8024 | 12.9892 | 2.32175 | 0.0169197 | 0.00203189 | 3.25051e-06 | 1(Win) | true |
| Glaze | 1554.15 | 0.0827602 | 9085.85ms | 461466 | 1280 | 7.02984e+07 | 283169 | 0.0365907 | 3.25061 | 15.2175 | 2.90193 | 0.0111831 | 0.00181119 | 5.27361e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1504.88 | 0.0833779 | 9444.8ms | 461466 | 80 | 4.75628e+06 | 292441 | 0.0912085 | 3.35799 | 14.5155 | 2.58567 | 0.021941 | 0.0210851 | 1.36521e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1004.37 | 0.210706 | 6466.59ms | 461466 | 640 | 5.45545e+08 | 438175 | 0.0343804 | 4.91813 | 21.2596 | 3.55154 | 0.00348237 | 0.0306714 | 1.56295e-05 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14891.5 | 0.0568715 | 3790.21ms | 461466 | 160 | 45197 | 29552.9 | 0.0006556 | 0.339536 | 1.61334 | 0.264032 | 0.000561187 | 0.00516377 | 8.87118e-06 | 1(Win) | true |
| Glaze | 3637.21 | 0.219595 | 6819.4ms | 461466 | 40 | 2.82389e+06 | 120996 | 0.364224 | 1.36965 | 5.36869 | 0.791387 | 0.00996904 | 0.0368124 | 4.62114e-05 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14679.2 | 0.12796 | 3774.76ms | 461466 | 320 | 470944 | 29980.3 | 0.0158412 | 0.337888 | 1.61215 | 0.263764 | 0.000534323 | 0.00475174 | 1.76746e-06 | 1(Win) | true |
| Glaze | 3819.25 | 0.377663 | 6253.48ms | 461466 | 1280 | 2.42405e+08 | 115229 | 0.245299 | 1.29487 | 5.35473 | 0.788156 | 0.00997632 | 0.00486976 | 4.34925e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1651.48 | 0.0747721 | 5464.5ms | 728486 | 80 | 7.91521e+06 | 420675 | 0.265683 | 3.00139 | 12.5274 | 2.27484 | 0.0157832 | 0.0671369 | 1.63696e-05 | 1(Win) | true |
| Glaze | 1555.12 | 0.1542 | 5836.71ms | 728486 | 40 | 1.89821e+07 | 446743 | 0.0453765 | 3.22893 | 14.8029 | 2.94222 | 0.0103909 | 0.0247776 | 2.5052e-05 | 2(Loss) | true |
| Jsonifier | 1388.26 | 0.123722 | 6494.06ms | 728486 | 40 | 1.53341e+07 | 500440 | 0.120058 | 3.57507 | 13.953 | 2.8598 | 0.0129644 | 0.0350262 | 2.24095e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1240.24 | 0.349416 | 7237.76ms | 728486 | 40 | 1.53241e+08 | 560163 | 0.206231 | 3.96673 | 16.573 | 2.86171 | 0.00737348 | 0.0697007 | 3.77495e-05 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2210.41 | 0.129208 | 5009.68ms | 728486 | 80 | 1.31936e+07 | 314303 | 0.0510756 | 2.23861 | 9.75318 | 1.66001 | 0.0139647 | 0.0271306 | 1.92008e-05 | 1(Win) | true |
| Glaze | 1894.74 | 0.13587 | 5607.86ms | 728486 | 40 | 9.92775e+06 | 366667 | 0.170809 | 2.61586 | 12.305 | 2.38009 | 0.00890158 | 0.00802246 | 5.14766e-06 | 2(Loss) | true |
| Jsonifier | 1745.42 | 0.0813893 | 6025.27ms | 728486 | 30 | 3.14845e+06 | 398034 | 0.225868 | 2.84063 | 11.1787 | 2.24488 | 0.011393 | 0.0069385 | 9.1514e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1503.4 | 0.497751 | 6780.61ms | 728486 | 320 | 1.69303e+09 | 462111 | 0.138857 | 3.27423 | 13.9763 | 2.27311 | 0.0025684 | 0.0381649 | 1.25689e-05 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16327.6 | 0.0143958 | 5705.79ms | 837491 | 1280 | 63474.3 | 48916.9 | 0.0199485 | 0.309801 | 1.35599 | 0.257735 | 0.000455521 | 0.0139505 | 1.89461e-06 | 1(Win) | true |
| Glaze | 3867.92 | 0.371952 | 5505.22ms | 837491 | 1280 | 7.55073e+08 | 206492 | 0.0519753 | 1.29339 | 4.56909 | 0.770701 | 0.00621839 | 0.05766 | 1.84088e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16335.9 | 0.0696603 | 5696.77ms | 837491 | 80 | 92797.2 | 48891.9 | 0.00751714 | 0.309517 | 1.35533 | 0.257587 | 0.000453706 | 0.0137803 | 2.26868e-06 | 1(Win) | true |
| Glaze | 4527.73 | 0.107787 | 9561.58ms | 837491 | 160 | 5.78433e+06 | 176401 | 0.0190546 | 1.11262 | 4.56028 | 0.768648 | 0.00617878 | 0.0162759 | 1.64554e-05 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7860.27 | 0.0738133 | 6449.5ms | 466906 | 640 | 1.11901e+06 | 56649 | 0.016163 | 0.641819 | 3.06806 | 0.394199 | 0.000856657 | 4.31029e-06 | 2.5333e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 7745.07 | 0.0612531 | 6512.86ms | 466906 | 1280 | 1.58736e+06 | 57491.6 | 0.00772863 | 0.638589 | 3.05988 | 0.391891 | 0.000825745 | 1.77866e-06 | 3.89867e-07 | 2(Loss) | true |
| simdjson (ondemand) | 6689.2 | 0.0335758 | 7425.32ms | 466906 | 4890 | 2.44272e+06 | 66566.5 | 0.0719643 | 0.74306 | 3.50449 | 0.387152 | 0.000779127 | 2.04628e-06 | 8.05459e-07 | 3(Loss) | true |
| Glaze | 3396.23 | 0.0551344 | 7072.76ms | 466906 | 320 | 1.67209e+06 | 131109 | 0.0311595 | 1.47817 | 5.742 | 0.996486 | 0.00163852 | 1.21143e-06 | 1.87404e-07 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7915.28 | 0.0762851 | 6475.22ms | 466906 | 1280 | 2.3573e+06 | 56255.3 | 0.0596008 | 0.631242 | 3.03306 | 0.385971 | 0.000835589 | 4.20153e-06 | 2.65043e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 7885.26 | 0.0738255 | 6492.12ms | 466906 | 640 | 1.11229e+06 | 56469.4 | 0.071417 | 0.627888 | 3.0258 | 0.383921 | 0.000815558 | 1.49588e-06 | 2.07483e-07 | 2(Loss) | true |
| simdjson (ondemand) | 6802.35 | 0.0354554 | 7423.95ms | 466906 | 4890 | 2.63399e+06 | 65459.2 | 0.053449 | 0.728128 | 3.46316 | 0.378794 | 0.000780787 | 2.27403e-06 | 7.7699e-07 | 3(Loss) | true |
| Glaze | 3459.97 | 0.0290243 | 7006.56ms | 466906 | 640 | 892931 | 128694 | 0.057948 | 1.46008 | 5.69483 | 0.985925 | 0.00158573 | 7.95463e-06 | 5.14357e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8916.06 | 0.0246803 | 7519.59ms | 631514 | 4890 | 1.35904e+06 | 67547.7 | 0.0645681 | 0.556816 | 2.70539 | 0.303941 | 0.00059338 | 6.46546e-06 | 3.1984e-06 | 1(Win) | true |
| Jsonifier | 8902.92 | 0.0225468 | 7526.74ms | 631514 | 4890 | 1.13757e+06 | 67647.3 | 0.0455374 | 0.55679 | 2.70817 | 0.304625 | 0.000608879 | 2.94291e-06 | 8.07292e-07 | 2(Loss) | true |
| simdjson (ondemand) | 7977.86 | 0.192893 | 8262.4ms | 631514 | 320 | 6.7854e+06 | 75491.2 | 0.0416431 | 0.622732 | 2.92523 | 0.3017 | 0.000589511 | 3.73755e-05 | 2.32576e-06 | 3(Loss) | true |
| Glaze | 3944.37 | 0.0328189 | 8199.68ms | 631514 | 160 | 401770 | 152688 | 0.0441577 | 1.25777 | 5.34782 | 0.94472 | 0.00123228 | 1.64288e-06 | 6.53192e-07 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9038.91 | 0.0343171 | 7530.85ms | 631514 | 1280 | 669213 | 66629.6 | 0.0621344 | 0.548866 | 2.68042 | 0.298122 | 0.000582588 | 2.53607e-06 | 3.8474e-07 | 1(Win) | true |
| Jsonifier | 9022.36 | 0.0204355 | 7546.52ms | 631514 | 4890 | 909927 | 66751.8 | 0.105535 | 0.549509 | 2.683 | 0.298744 | 0.000609798 | 2.4005e-06 | 6.90391e-07 | 2(Loss) | true |
| simdjson (ondemand) | 8264.76 | 0.057952 | 8101.99ms | 631514 | 4890 | 8.72068e+06 | 72870.7 | 0.032025 | 0.609911 | 2.89708 | 0.296066 | 0.000582443 | 1.80153e-05 | 3.82047e-06 | 3(Loss) | true |
| Glaze | 3990.37 | 0.0317801 | 8132.6ms | 631514 | 640 | 1.47242e+06 | 150928 | 0.111332 | 1.24548 | 5.31321 | 0.937001 | 0.00118247 | 2.77112e-06 | 6.21027e-07 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1875.6 | 0.100036 | 6283.65ms | 466906 | 160 | 9.02429e+06 | 237405 | 0.073394 | 2.67618 | 8.30987 | 1.47955 | 0.0123235 | 0.0125957 | 9.745e-06 | 1(Win) | true |
| Glaze | 1830.43 | 0.0779323 | 6439.82ms | 466906 | 160 | 5.75055e+06 | 243264 | 0.0427183 | 2.76096 | 10.0687 | 1.80391 | 0.0126785 | 0.0106954 | 2.22877e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1676.29 | 0.0960311 | 7018.26ms | 466906 | 160 | 1.04113e+07 | 265632 | 0.129279 | 3.01413 | 9.31183 | 1.53721 | 0.0172856 | 0.0268933 | 1.20474e-05 | 3(Loss) | true |
| simdjson (ondemand) | 913.313 | 0.235527 | 6287.88ms | 466906 | 640 | 8.4388e+08 | 487540 | 0.192284 | 5.38401 | 18.3594 | 3.1722 | 0.0138056 | 0.0391201 | 3.64936e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2383.34 | 0.075293 | 5735.21ms | 466906 | 320 | 6.3321e+06 | 186829 | 0.191887 | 2.09653 | 6.83131 | 1.14053 | 0.00922253 | 0.00129238 | 4.36383e-06 | 1(Win) | true |
| Glaze | 2326.05 | 0.0847578 | 5832.4ms | 466906 | 640 | 1.68485e+07 | 191431 | 0.00380019 | 2.17236 | 8.58369 | 1.46218 | 0.00948821 | 0.000529506 | 2.85021e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2172.21 | 0.120009 | 6239.89ms | 466906 | 160 | 9.6828e+06 | 204988 | 0.0269516 | 2.28287 | 7.83445 | 1.19835 | 0.0100804 | 0.00418723 | 2.90476e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1034.78 | 0.200258 | 5911.06ms | 466906 | 640 | 4.75246e+08 | 430308 | 0.25255 | 4.77019 | 16.9552 | 2.84875 | 0.0100996 | 0.00813164 | 1.0846e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19474.3 | 0.0366263 | 3111.36ms | 475954 | 640 | 46641.5 | 23307.9 | 0.061114 | 0.254956 | 1.02008 | 0.152914 | 0.000272095 | 0.000346518 | 1.76291e-06 | 1(Win) | true |
| Glaze | 6026.17 | 0.216445 | 8324.87ms | 475954 | 4890 | 1.29972e+08 | 75322.3 | 0.223308 | 0.822138 | 2.36331 | 0.337089 | 0.000352427 | 0.0146181 | 2.24455e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19583.1 | 0.0232484 | 3102.48ms | 475954 | 1280 | 37167.3 | 23178.4 | 0.016429 | 0.253621 | 1.01889 | 0.152649 | 0.000276279 | 0.000272233 | 1.28032e-06 | 1(Win) | true |
| Glaze | 6807.8 | 0.220104 | 7449.13ms | 475954 | 2560 | 5.5133e+07 | 66674.2 | 0.152463 | 0.727471 | 2.35134 | 0.334375 | 0.000336784 | 0.00096342 | 2.11664e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2175.83 | 0.123341 | 7291.65ms | 631514 | 640 | 7.45949e+07 | 276795 | 0.0513621 | 2.27683 | 7.34063 | 1.15347 | 0.0119888 | 0.0312942 | 0.000331757 | 1(Win) | true |
| Glaze | 1997.56 | 0.0255872 | 7936.26ms | 631514 | 1280 | 7.61763e+06 | 301497 | 0.0337413 | 2.48626 | 9.08441 | 1.66272 | 0.0112347 | 0.0148158 | 0.000156641 | 2(Loss) | true |
| Jsonifier | 1532.54 | 0.110897 | 5054.52ms | 631514 | 30 | 5.69774e+06 | 392980 | 0.0685824 | 3.23392 | 7.97501 | 1.53283 | 0.0103869 | 0.0230008 | 0.000129161 | 3(Loss) | true |
| simdjson (ondemand) | 1234.87 | 0.17024 | 6300.54ms | 631514 | 160 | 1.10298e+08 | 487711 | 0.291341 | 4.05067 | 13.9087 | 2.36089 | 0.0101445 | 0.0377987 | 0.000607795 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2748.58 | 0.103187 | 6617.75ms | 631514 | 1280 | 6.54346e+07 | 219116 | 0.366634 | 1.81901 | 6.24753 | 0.903237 | 0.00941778 | 0.00970825 | 0.000113047 | 1(Win) | true |
| Glaze | 2507.55 | 0.0276187 | 7071.13ms | 631514 | 1280 | 5.63229e+06 | 240178 | 0.133945 | 1.97736 | 7.98887 | 1.41168 | 0.00707731 | 0.00203171 | 3.57066e-05 | 2(Loss) | true |
| Jsonifier | 1800.92 | 0.138707 | 9538.13ms | 631514 | 80 | 1.72133e+07 | 334417 | 0.0488224 | 2.77464 | 6.87926 | 1.28191 | 0.00778724 | 0.00554063 | 0.000160586 | 3(Loss) | true |
| simdjson (ondemand) | 1390.67 | 0.186807 | 5952.6ms | 631514 | 80 | 5.23594e+07 | 433071 | 0.415859 | 3.58539 | 12.8739 | 2.12262 | 0.00733927 | 0.0142884 | 2.29805e-05 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18784 | 0.0700797 | 4439.1ms | 716365 | 80 | 51971.8 | 36370.3 | 0.0429768 | 0.269313 | 1.02727 | 0.178567 | 0.000211484 | 0.00173007 | 5.04282e-06 | 1(Win) | true |
| Glaze | 4221.65 | 0.134554 | 8693.05ms | 716365 | 640 | 3.03442e+07 | 161827 | 0.0293976 | 1.18692 | 2.8173 | 0.463479 | 0.000535682 | 0.0465081 | 9.40141e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18661.9 | 0.0702936 | 4445.25ms | 716365 | 320 | 211904 | 36608.2 | 0.0735206 | 0.268933 | 1.02654 | 0.178404 | 0.000204788 | 0.00161266 | 1.12373e-05 | 1(Win) | true |
| Glaze | 5001.39 | 0.124089 | 7371.92ms | 716365 | 1280 | 3.67761e+07 | 136598 | 0.0643721 | 1.00311 | 2.80754 | 0.461218 | 0.000530484 | 0.00304977 | 5.85105e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2519.65 | 0.0437983 | 836.526ms | 2632 | 1280 | 243.678 | 996.199 | 0.177472 | 2.09584 | 8.04863 | 1.394 | 0.00113982 | 7.27227e-05 | 2.31525e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2174.03 | 0.0866799 | 850.178ms | 2632 | 4890 | 4897.65 | 1154.57 | 0.047127 | 2.39818 | 9.77166 | 1.71239 | 0.00076555 | 8.91187e-05 | 3.25551e-05 | 2(Loss) | true |
| Glaze | 1958.75 | 0.0845152 | 883.619ms | 2632 | 2560 | 3002.77 | 1281.46 | 0.219025 | 2.6705 | 11.3583 | 2.13336 | 0.00147108 | 8.07371e-05 | 2.55272e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1401.41 | 0.120441 | 934.9ms | 2632 | 1280 | 5956.67 | 1791.11 | 0.295381 | 3.65356 | 12.883 | 2.23442 | 0.00545925 | 8.01434e-05 | 3.38383e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2926.23 | 0.0544998 | 829.682ms | 2632 | 4890 | 1068.69 | 857.782 | 0.232143 | 1.82499 | 7.0266 | 1.13336 | 0.00177072 | 8.53115e-05 | 3.50414e-05 | 1(Win) | true |
| Glaze | 2496.21 | 0.14356 | 845.568ms | 2632 | 2560 | 5334.78 | 1005.55 | 0.100403 | 2.10763 | 9.47948 | 1.69947 | 0.00155122 | 9.75078e-05 | 2.79018e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2470.19 | 0.132785 | 845.807ms | 2632 | 320 | 582.583 | 1016.15 | 0.0218397 | 2.14766 | 8.74848 | 1.45175 | 0.00151619 | 6.8864e-05 | 8.31117e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1652.23 | 0.134136 | 898.69ms | 2632 | 320 | 1328.84 | 1519.21 | 0.037863 | 3.09672 | 11.4487 | 1.89552 | 0.00138678 | 4.03685e-05 | 1.06858e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9978.7 | 0.0589451 | 762.001ms | 2632 | 4890 | 107.505 | 251.543 | 0.816489 | 0.583779 | 1.89172 | 0.305091 | 0.000399597 | 3.00688e-05 | 6.99275e-06 | 1(Win) | true |
| Glaze | 3345.99 | 0.139262 | 813.309ms | 2632 | 2560 | 2794.01 | 750.172 | 0.00921748 | 1.57704 | 4.80851 | 0.75114 | 0.000382314 | 5.28353e-05 | 7.5691e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11930 | 0.0217747 | 759.785ms | 2632 | 4890 | 10.2637 | 210.4 | 0.159079 | 0.500003 | 1.68503 | 0.256459 | 0.000380172 | 2.68055e-05 | 9.32366e-07 | 1(Win) | true |
| Glaze | 3724.56 | 0.116338 | 802.037ms | 2632 | 4890 | 3005.88 | 673.924 | 0.182818 | 1.42943 | 4.3051 | 0.647417 | 0.000382348 | 5.92829e-05 | 5.36111e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2467.59 | 0.0634032 | 874.747ms | 3370 | 2560 | 1745.73 | 1302.44 | 0.155238 | 2.07463 | 8.5724 | 1.4543 | 0.000596254 | 5.40152e-05 | 9.50482e-06 | 1(Win) | true |
| Jsonifier | 2120.9 | 0.100692 | 898.129ms | 3370 | 80 | 186.252 | 1515.34 | 0.0255653 | 2.40452 | 8.81632 | 1.73947 | 0.0015319 | 1.11276e-05 | 0 | 2(Loss) | true |
| Glaze | 2050.34 | 0.0628954 | 917.241ms | 3370 | 1280 | 1244.1 | 1567.49 | 0.0692808 | 2.48342 | 10.7682 | 2.06172 | 0.00166798 | 3.08327e-05 | 2.31825e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1717.94 | 0.0644969 | 950.692ms | 3370 | 4890 | 7119.18 | 1870.78 | 0.178568 | 2.94974 | 10.454 | 1.7819 | 0.00404034 | 4.9638e-05 | 1.11048e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2926.33 | 0.0696371 | 866.97ms | 3370 | 1280 | 748.697 | 1098.26 | 0.0333512 | 1.76836 | 7.31039 | 1.16202 | 0.000726307 | 2.87463e-05 | 1.39095e-06 | 1(Win) | true |
| Glaze | 2511.31 | 0.115277 | 878.421ms | 3370 | 2560 | 5571.64 | 1279.77 | 0.403832 | 2.06139 | 9.29733 | 1.72285 | 0.00113838 | 6.43314e-05 | 2.2487e-05 | 2(Loss) | true |
| Jsonifier | 2379.87 | 0.061188 | 890.265ms | 3370 | 320 | 218.492 | 1350.44 | 0.0810575 | 2.15291 | 8.01528 | 1.53611 | 0.00144102 | 4.91469e-05 | 9.273e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2035.85 | 0.0897682 | 916.161ms | 3370 | 1280 | 2570.54 | 1578.65 | 0.0738915 | 2.51055 | 9.30179 | 1.5095 | 0.00146212 | 3.12964e-05 | 1.15912e-06 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11428.5 | 0.112199 | 774.432ms | 3643 | 4890 | 568.885 | 303.997 | 0.451592 | 0.494074 | 1.70519 | 0.288499 | 0.000275229 | 2.48677e-05 | 7.12912e-06 | 1(Win) | true |
| Glaze | 3569.8 | 0.124181 | 842.655ms | 3682 | 2560 | 3819.68 | 983.649 | 0.30568 | 1.44743 | 4.51358 | 0.753667 | 0.000274138 | 4.03144e-05 | 7.85069e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13239 | 0.0990574 | 766.383ms | 3643 | 160 | 10.8119 | 262.425 | 0.251817 | 0.434697 | 1.6146 | 0.266813 | 0.000274499 | 5.14686e-06 | 0 | 1(Win) | true |
| Glaze | 3902.76 | 0.196237 | 834.594ms | 3682 | 1280 | 3990.21 | 899.73 | 0.0475611 | 1.33735 | 4.19772 | 0.680608 | 0.000273077 | 4.20118e-05 | 1.2943e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 983.531 | 0.076841 | 1193.46ms | 4630 | 640 | 7616.43 | 4489.45 | 0.0663617 | 5.08588 | 23.7143 | 4.84709 | 0.00567461 | 4.11717e-05 | 1.01242e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 900.104 | 0.0727154 | 1242.19ms | 4630 | 640 | 8143.46 | 4905.56 | 0.0247426 | 5.55433 | 26.5156 | 5.13542 | 0.00482046 | 3.37473e-05 | 1.01242e-06 | 2(Loss) | true |
| Glaze | 771.759 | 0.0951364 | 1315.18ms | 4630 | 80 | 2370.18 | 5721.36 | 0.25823 | 6.47675 | 30.6186 | 5.93931 | 0.00310205 | 0.000102592 | 2.42981e-05 | 3(Loss) | true |
| simdjson (ondemand) | 672.708 | 0.0427411 | 1404.76ms | 4630 | 1280 | 10074.2 | 6563.79 | 0.140921 | 7.41903 | 31.568 | 5.72743 | 0.00247688 | 6.76633e-05 | 2.02484e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1251.36 | 0.0260875 | 1194.71ms | 4630 | 4890 | 4143.54 | 3528.57 | 0.091506 | 4.01412 | 19.316 | 3.8257 | 0.00299682 | 5.90971e-05 | 1.85948e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1114.42 | 0.0223448 | 1243.28ms | 4630 | 640 | 501.643 | 3962.15 | 0.0164026 | 4.50255 | 22.0942 | 4.10907 | 0.003478 | 4.52214e-05 | 7.76188e-06 | 2(Loss) | true |
| Glaze | 920.32 | 0.0346982 | 1324.27ms | 4630 | 4890 | 13552.1 | 4797.8 | 0.156221 | 5.48052 | 26.1348 | 4.89784 | 0.00212454 | 0.0001333 | 6.82399e-05 | 3(Loss) | true |
| simdjson (ondemand) | 796.915 | 0.0499488 | 1405.53ms | 4630 | 1280 | 9803.91 | 5540.76 | 0.0949582 | 6.26775 | 27.9734 | 4.90259 | 0.00218514 | 4.47152e-05 | 9.95545e-06 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1885.66 | 0.0576637 | 974.56ms | 4630 | 80 | 145.858 | 2341.62 | 0.0512202 | 2.67799 | 8.03089 | 0.459611 | 0.000215983 | 2.69978e-05 | 0 | 1(Win) | true |
| Glaze | 903.425 | 0.0237822 | 1237.29ms | 4630 | 4890 | 6606.79 | 4887.53 | 0.104664 | 5.55467 | 9.80691 | 0.686178 | 0.000249816 | 5.41944e-05 | 1.70048e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1911.75 | 0.0247611 | 973.172ms | 4630 | 4890 | 1599.37 | 2309.68 | 0.0298811 | 2.64262 | 7.91922 | 0.433694 | 0.000218191 | 2.48226e-05 | 3.79847e-06 | 1(Win) | true |
| Glaze | 979.499 | 0.0712225 | 1195.33ms | 4630 | 640 | 6597.34 | 4507.93 | 0.0180964 | 5.18017 | 9.27776 | 0.568036 | 0.000227794 | 4.96085e-05 | 1.51863e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2090.73 | 0.0284143 | 1279.32ms | 11579 | 2560 | 5765.82 | 5281.7 | 0.194488 | 2.42421 | 11.3665 | 2.0817 | 0.00205491 | 1.52822e-05 | 3.33983e-06 | 1(Win) | true |
| Jsonifier | 1900.3 | 0.0253384 | 1331.03ms | 11579 | 4890 | 10601.5 | 5810.98 | 0.135083 | 2.63619 | 12.0759 | 2.64185 | 0.00356703 | 7.38768e-05 | 3.73358e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1672.83 | 0.0268825 | 1406.1ms | 11579 | 4890 | 15398.7 | 6601.13 | 0.119828 | 2.99847 | 13.1783 | 2.28759 | 0.00141217 | 2.86994e-05 | 8.8306e-06 | 3(Loss) | true |
| Glaze | 1560.09 | 0.049853 | 1455.87ms | 11579 | 1280 | 15938.1 | 7078.18 | 0.0573618 | 3.20646 | 15.0958 | 2.92443 | 0.00416021 | 3.14416e-05 | 8.02908e-06 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2500.6 | 0.0241788 | 1287.62ms | 11579 | 4890 | 5574.84 | 4415.98 | 0.133626 | 2.00267 | 9.62182 | 1.677 | 0.00165703 | 2.6792e-05 | 9.30745e-06 | 1(Win) | true |
| Jsonifier | 2251.18 | 0.181386 | 1329.47ms | 11579 | 80 | 6333.15 | 4905.25 | 0.0453801 | 2.22282 | 10.332 | 2.23707 | 0.00326453 | 1.94317e-05 | 5.3977e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1875.86 | 0.0534997 | 1437.67ms | 11579 | 1280 | 12695.7 | 5886.69 | 0.105821 | 2.6633 | 11.8165 | 1.97513 | 0.00100127 | 2.41547e-05 | 6.67966e-06 | 3(Loss) | true |
| Glaze | 1771.92 | 0.129369 | 1461.37ms | 11579 | 320 | 20800 | 6232 | 0.0211152 | 2.81573 | 13.3211 | 2.51283 | 0.00367611 | 4.58805e-05 | 2.15908e-05 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4340.63 | 0.114597 | 1075.24ms | 14795 | 640 | 8880.78 | 3250.59 | 0.0365185 | 1.15807 | 2.98841 | 0.279709 | 0.000293596 | 1.44686e-05 | 2.85147e-06 | 1(Win) | true |
| Glaze | 3561.97 | 0.055154 | 1148.52ms | 14795 | 2560 | 12219.2 | 3961.19 | 0.134136 | 1.41465 | 4.44671 | 0.532883 | 0.000960972 | 5.5234e-05 | 3.25279e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4670.99 | 0.0663837 | 1052.19ms | 14795 | 2560 | 10293.8 | 3020.69 | 0.0640139 | 1.07594 | 2.95059 | 0.270903 | 0.000283061 | 1.35445e-05 | 3.48513e-06 | 1(Win) | true |
| Glaze | 3904.8 | 0.0421858 | 1102.65ms | 14795 | 2560 | 5948.46 | 3613.4 | 0.0114578 | 1.28574 | 4.24474 | 0.486786 | 0.000990411 | 1.6924e-05 | 5.12209e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1600.43 | 0.0524583 | 940.935ms | 3223 | 2560 | 2598.44 | 1920.54 | 0.0890436 | 3.16917 | 12.3097 | 2.3233 | 0.0010937 | 0.000166649 | 7.33255e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1324.35 | 0.131394 | 982.902ms | 3223 | 30 | 278.99 | 2320.9 | 0.0287327 | 3.81452 | 15.0599 | 2.65684 | 0.0014169 | 0.00013445 | 9.3081e-05 | 2(Loss) | true |
| Glaze | 1280.5 | 0.0314942 | 989.072ms | 3223 | 4890 | 2794.67 | 2400.38 | 0.0783711 | 3.93929 | 15.3183 | 2.91313 | 0.00157203 | 7.25867e-05 | 2.01771e-05 | 3(Loss) | true |
| simdjson (ondemand) | 938.344 | 0.0351684 | 1078.53ms | 3223 | 4890 | 6489.5 | 3275.66 | 0.124691 | 5.35305 | 19.7043 | 3.21378 | 0.00194138 | 0.000231402 | 0.000129501 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1991.85 | 0.0679485 | 925.477ms | 3223 | 1280 | 1407.27 | 1543.13 | 0.107973 | 2.56286 | 10.4006 | 1.85417 | 0.00148566 | 5.79332e-05 | 5.81756e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1587.93 | 0.0752195 | 960.279ms | 3223 | 2560 | 5426.98 | 1935.66 | 0.0138053 | 3.1964 | 13.1505 | 2.18771 | 0.00116836 | 8.22943e-05 | 3.24814e-05 | 2(Loss) | true |
| Glaze | 1554.76 | 0.0526231 | 970.115ms | 3223 | 2560 | 2770.67 | 1976.95 | 0.0264305 | 3.26326 | 13.4353 | 2.45206 | 0.00108691 | 9.40506e-05 | 4.09653e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1076.44 | 0.0477694 | 1058.8ms | 3223 | 4890 | 9098.04 | 2855.42 | 0.159627 | 4.678 | 17.695 | 2.72851 | 0.00146829 | 7.37288e-05 | 1.78929e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7574.49 | 0.133973 | 784.25ms | 3223 | 640 | 189.158 | 405.795 | 0.146918 | 0.734333 | 2.35216 | 0.408936 | 0.00031027 | 3.05422e-05 | 7.75675e-06 | 1(Win) | true |
| Glaze | 2748.19 | 0.155766 | 863.202ms | 3223 | 2560 | 7769.81 | 1118.44 | 0.235195 | 1.88191 | 5.18402 | 0.771958 | 0.000315966 | 0.000167618 | 7.11439e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8303.4 | 0.256001 | 781.766ms | 3223 | 2560 | 2298.97 | 370.173 | 0.204715 | 0.662663 | 2.19516 | 0.372014 | 0.000310997 | 3.11482e-05 | 1.27259e-05 | 1(Win) | true |
| Glaze | 3022.94 | 0.2462 | 848.665ms | 3223 | 1280 | 8021.36 | 1016.79 | 0.349449 | 1.71533 | 4.65095 | 0.652498 | 0.000403109 | 4.53285e-05 | 5.09037e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2296.53 | 0.0752357 | 994.707ms | 5839 | 160 | 532.478 | 2424.75 | 0.0149522 | 2.19789 | 8.93013 | 1.49204 | 0.00060691 | 2.24782e-05 | 1.07039e-06 | 1(Win) | true |
| Jsonifier | 1756.28 | 0.0529199 | 1069.85ms | 5839 | 1280 | 3603.61 | 3170.63 | 0.0512501 | 2.85703 | 10.0218 | 2.11526 | 0.00148048 | 3.86678e-05 | 8.29551e-06 | 2(Loss) | true |
| Glaze | 1697.03 | 0.053791 | 1077.35ms | 5839 | 1280 | 3987.74 | 3281.32 | 0.129235 | 2.96246 | 11.4355 | 2.20928 | 0.00186368 | 4.76323e-05 | 1.31123e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1665.74 | 0.245454 | 1089.24ms | 5839 | 320 | 21545.4 | 3342.97 | 0.00598235 | 3.06444 | 11.2355 | 1.76657 | 0.00104256 | 6.95753e-05 | 2.99709e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2684.41 | 0.126148 | 979.169ms | 5839 | 80 | 547.81 | 2074.39 | 0.0222908 | 1.88564 | 7.96284 | 1.25021 | 0.000627248 | 1.9267e-05 | 0 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1999.41 | 0.0506685 | 1049.95ms | 5839 | 2560 | 5097.87 | 2785.07 | 0.00283326 | 2.51699 | 10.3523 | 1.94622 | 0.0014176 | 2.93019e-05 | 5.15125e-06 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 1998.55 | 0.0352109 | 1052.32ms | 5839 | 2560 | 2464.01 | 2786.28 | 0.0136009 | 2.51479 | 8.96849 | 1.85631 | 0.00142917 | 3.74636e-05 | 7.29202e-06 | 2(Tie) | true |
| simdjson (ondemand) | 1855.87 | 0.109553 | 1074.3ms | 5839 | 640 | 6915.33 | 3000.49 | 0.235672 | 2.71061 | 10.2987 | 1.53194 | 0.000798778 | 2.97033e-05 | 8.56311e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10547.2 | 0.102025 | 805.405ms | 6938 | 160 | 65.5437 | 627.331 | 0.1045 | 0.510583 | 1.74013 | 0.317959 | 0.000144134 | 2.34217e-05 | 0 | 1(Win) | true |
| Glaze | 3368.34 | 0.155765 | 948.716ms | 6960 | 4890 | 46072 | 1970.58 | 0.0874003 | 1.51257 | 4.2148 | 0.71911 | 0.000348882 | 3.0146e-05 | 6.17023e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11236.2 | 0.116461 | 803.412ms | 6938 | 320 | 150.501 | 588.862 | 0.00318421 | 0.472654 | 1.66388 | 0.29951 | 0.000144134 | 1.71159e-05 | 5.40502e-06 | 1(Win) | true |
| Glaze | 3827.92 | 0.226503 | 923.864ms | 6960 | 2560 | 39489.6 | 1733.99 | 0.386425 | 1.33702 | 3.8717 | 0.645259 | 0.000311321 | 6.40939e-05 | 2.63223e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1987.07 | 0.0885998 | 982.412ms | 4857 | 1280 | 5459.89 | 2331.06 | 0.0435881 | 2.54487 | 9.74151 | 1.85176 | 0.00161992 | 6.59486e-05 | 2.60578e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1672.77 | 0.117452 | 1028.13ms | 4857 | 320 | 3384.83 | 2769.05 | 0.0445576 | 3.01382 | 11.9069 | 2.10542 | 0.00133699 | 4.05343e-05 | 1.22246e-05 | 2(Loss) | true |
| Glaze | 1662.59 | 0.0647228 | 1030.73ms | 4857 | 1280 | 4161.88 | 2786.01 | 0.114168 | 3.03768 | 11.9832 | 2.29512 | 0.000859584 | 2.87922e-05 | 2.41275e-06 | 3(Loss) | true |
| simdjson (ondemand) | 758.046 | 0.117761 | 1351.24ms | 4857 | 160 | 8284.5 | 6110.44 | 0.0760547 | 6.59175 | 22.8289 | 3.91497 | 0.00293648 | 0.000343576 | 0.000203315 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2687.17 | 0.0546869 | 949.44ms | 4857 | 4890 | 4345.32 | 1723.74 | 0.00877712 | 1.89797 | 7.29154 | 1.2901 | 0.00149983 | 6.42928e-05 | 2.4715e-05 | 1(Win) | true |
| Glaze | 2361.47 | 0.0658124 | 975.547ms | 4857 | 2560 | 4266.07 | 1961.49 | 0.0665394 | 2.15287 | 9.08421 | 1.64361 | 0.00128608 | 0.000129726 | 6.15252e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2111.1 | 0.103728 | 996.727ms | 4857 | 2560 | 13260.3 | 2194.12 | 0.123886 | 2.41357 | 9.79185 | 1.61355 | 0.00152961 | 0.000159644 | 0.000107368 | 3(Loss) | true |
| simdjson (ondemand) | 866.718 | 0.0336154 | 1310.14ms | 4857 | 4890 | 15782.2 | 5344.29 | 0.00976895 | 5.77534 | 20.8233 | 3.46181 | 0.00241319 | 5.51983e-05 | 1.73047e-05 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10234.6 | 0.292191 | 789.116ms | 4857 | 640 | 1119.2 | 452.581 | 0.0910609 | 0.527506 | 1.68396 | 0.289685 | 0.000215861 | 2.63795e-05 | 6.43401e-07 | 1(Win) | true |
| Glaze | 2990.73 | 0.252477 | 905.35ms | 4857 | 2560 | 39144 | 1548.78 | 0.145819 | 1.71184 | 4.14824 | 0.63043 | 0.0005789 | 5.68606e-05 | 1.35919e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11453 | 0.0929788 | 784.439ms | 4857 | 2560 | 361.997 | 404.435 | 0.0694932 | 0.47689 | 1.57175 | 0.261685 | 0.000206451 | 4.17407e-05 | 1.30289e-05 | 1(Win) | true |
| Glaze | 2606.19 | 0.147022 | 923.438ms | 4857 | 4890 | 33388.4 | 1777.31 | 0.0272532 | 1.9528 | 3.68582 | 0.525428 | 0.000247066 | 3.45674e-05 | 7.83134e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2286.94 | 0.0690802 | 1031.11ms | 6701 | 320 | 1192.42 | 2794.38 | 0.117285 | 2.2109 | 8.93971 | 1.50634 | 0.00112996 | 3.0779e-05 | 6.52888e-06 | 1(Win) | true |
| Glaze | 1966.61 | 0.195691 | 1077.93ms | 6701 | 160 | 6470.04 | 3249.54 | 0.0088482 | 2.65145 | 10.9902 | 2.15431 | 0.00181876 | 4.0106e-05 | 1.11924e-05 | 2(Loss) | true |
| Jsonifier | 1601.1 | 0.0529113 | 1153.06ms | 6701 | 2560 | 11417.7 | 3991.36 | 0.00184973 | 3.14002 | 10.0166 | 2.10088 | 0.0022274 | 0.000127954 | 7.77636e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1032.48 | 0.0593081 | 1374.78ms | 6701 | 1280 | 17248.5 | 6189.52 | 0.258956 | 4.85837 | 16.9522 | 2.86032 | 0.00195143 | 0.000108193 | 6.06253e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2792.28 | 0.0517465 | 1008.46ms | 6701 | 640 | 897.645 | 2288.66 | 0.118719 | 1.8194 | 7.51977 | 1.17535 | 0.00116167 | 2.07525e-05 | 1.63222e-06 | 1(Win) | true |
| Glaze | 2576.71 | 0.115372 | 1019.4ms | 6701 | 40 | 327.497 | 2480.12 | 0.00235209 | 1.96435 | 8.86703 | 1.67975 | 0.00163782 | 2.98463e-05 | 0 | 2(Loss) | true |
| Jsonifier | 1936.68 | 0.060433 | 1103.17ms | 6701 | 160 | 636.258 | 3299.76 | 0.00340945 | 2.59978 | 8.41158 | 1.73153 | 0.0016089 | 3.54425e-05 | 3.73079e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1176.35 | 0.067241 | 1307.28ms | 6701 | 640 | 8539.87 | 5432.52 | 0.332643 | 4.24816 | 15.4771 | 2.52768 | 0.00173715 | 1.86539e-05 | 4.66348e-07 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11406.2 | 0.0412461 | 807.117ms | 7376 | 4890 | 316.396 | 616.706 | 0.177523 | 0.466181 | 1.54176 | 0.279691 | 0.000135603 | 1.76608e-05 | 3.13292e-06 | 1(Win) | true |
| Glaze | 2470.84 | 0.169689 | 1034.45ms | 7376 | 4890 | 114122 | 2846.93 | 0.0279429 | 2.05644 | 4.57145 | 0.73929 | 0.000623228 | 2.92498e-05 | 5.43408e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12519.9 | 0.12992 | 800.672ms | 7376 | 640 | 341.013 | 561.85 | 0.0472992 | 0.427522 | 1.46204 | 0.261659 | 0.000135575 | 2.7115e-05 | 1.05918e-05 | 1(Win) | true |
| Glaze | 2633.46 | 0.327707 | 1014.27ms | 7376 | 1280 | 98077.4 | 2671.12 | 0.289504 | 1.919 | 4.2523 | 0.667028 | 0.000565919 | 2.52084e-05 | 2.64795e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1994.16 | 0.126691 | 819.859ms | 1691 | 160 | 167.95 | 808.694 | 0.0625618 | 2.62411 | 8.87167 | 1.54228 | 0.00279051 | 3.69604e-05 | 3.69604e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1818.49 | 0.161694 | 828.799ms | 1691 | 640 | 1315.92 | 886.812 | 0.0588831 | 2.89481 | 10.0958 | 1.72324 | 0.00059691 | 0.000167246 | 8.87049e-05 | 2(Loss) | true |
| Glaze | 1746.81 | 0.161649 | 822.434ms | 1691 | 160 | 356.341 | 923.206 | 0.061568 | 2.96648 | 10.4465 | 1.98581 | 0.00213631 | 0.000155234 | 2.95683e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1363.99 | 0.565835 | 852.271ms | 1691 | 160 | 7160.83 | 1182.31 | 0.0444242 | 3.76471 | 12.679 | 2.11712 | 0.000635719 | 0.000103489 | 3.69604e-05 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2625.86 | 0.0444214 | 810.131ms | 1691 | 4890 | 363.947 | 614.147 | 0.215503 | 2.0331 | 7.23418 | 1.13779 | 0.0020884 | 7.90907e-05 | 1.34236e-05 | 1(Win) | true |
| Glaze | 2315.49 | 0.0872837 | 819.599ms | 1691 | 640 | 236.509 | 696.467 | 0.0383485 | 2.31353 | 8.78238 | 1.57836 | 0.000927705 | 5.08205e-05 | 2.77203e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2266.33 | 0.208905 | 820.592ms | 1691 | 80 | 176.779 | 711.575 | 0.0912633 | 2.36208 | 8.53105 | 1.33353 | 0.000591366 | 2.21762e-05 | 1.47842e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1615.85 | 0.0579181 | 846.712ms | 1691 | 1280 | 427.687 | 998.03 | 0.0295025 | 3.2356 | 11.178 | 1.74571 | 0.000591366 | 7.11487e-05 | 1.66322e-05 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9532.84 | 0.0761529 | 751.96ms | 1996 | 2560 | 59.1956 | 199.682 | 0.211413 | 0.63671 | 1.6017 | 0.268537 | 0.000501002 | 2.87685e-05 | 8.02386e-06 | 1(Win) | true |
| Glaze | 3672.94 | 0.248105 | 789.223ms | 1996 | 2560 | 4232.56 | 518.259 | 0.650524 | 1.46262 | 3.81012 | 0.5997 | 0.000502959 | 5.55799e-05 | 1.29165e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12079.2 | 0.288401 | 751.366ms | 1996 | 160 | 33.0489 | 157.588 | 0.0873293 | 0.526312 | 1.36673 | 0.210922 | 0.000501002 | 1.56563e-05 | 9.39379e-06 | 1(Win) | true |
| Glaze | 4030.1 | 0.403021 | 781.851ms | 1996 | 640 | 2319.13 | 472.33 | 0.0571969 | 1.35432 | 3.25601 | 0.480461 | 0.000501785 | 4.61861e-05 | 1.40907e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2245.26 | 0.145809 | 834.854ms | 2158 | 80 | 142.899 | 916.612 | 0.181046 | 2.35494 | 8.36562 | 1.37952 | 0.000474977 | 0.00016798 | 5.7924e-06 | 1(Win) | true |
| Glaze | 1966.73 | 0.0913916 | 837.865ms | 2158 | 1280 | 1170.68 | 1046.42 | 0.0823557 | 2.64834 | 9.9393 | 1.91057 | 0.000468098 | 8.43518e-05 | 2.09975e-05 | 2(Loss) | true |
| Jsonifier | 1905.83 | 0.0738616 | 849.136ms | 2158 | 2560 | 1628.58 | 1079.86 | 0.0571872 | 2.73678 | 8.98888 | 1.71965 | 0.000474796 | 9.72037e-05 | 2.38937e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1712.99 | 0.100799 | 864.101ms | 2158 | 320 | 469.305 | 1201.43 | 0.00494228 | 2.99704 | 10.1849 | 1.67192 | 0.00046484 | 8.54379e-05 | 5.7924e-06 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2697.67 | 0.0619211 | 821.188ms | 2158 | 4890 | 1091.22 | 762.891 | 0.319112 | 1.94155 | 7.07785 | 1.06209 | 0.00049836 | 0.000118075 | 3.31671e-05 | 1(Win) | true |
| Glaze | 2321.58 | 0.0533005 | 840.944ms | 2158 | 640 | 142.882 | 886.478 | 0.0447498 | 2.25717 | 8.65477 | 1.595 | 0.000463392 | 4.2719e-05 | 4.3443e-06 | 2(Loss) | true |
| Jsonifier | 2257.18 | 0.0652072 | 843.673ms | 2158 | 640 | 226.226 | 911.772 | 0.131781 | 2.31952 | 7.76367 | 1.41427 | 0.000463392 | 7.67493e-05 | 1.08608e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1987.97 | 0.150278 | 853.923ms | 2158 | 160 | 387.255 | 1035.24 | 0.0114694 | 2.60262 | 9.0088 | 1.38091 | 0.000474977 | 3.76506e-05 | 2.8962e-06 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10831.1 | 0.241441 | 763.537ms | 2866 | 40 | 14.8487 | 252.35 | 0.191167 | 0.531385 | 1.50733 | 0.262038 | 0.000348918 | 0 | 0 | 1(Win) | true |
| Glaze | 3642.13 | 0.344256 | 817.316ms | 2866 | 1280 | 8543.1 | 750.449 | 0.290334 | 1.43883 | 4.19121 | 0.721563 | 0.000352735 | 2.64415e-05 | 5.45185e-06 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12657.5 | 0.0971134 | 761.811ms | 2866 | 4890 | 215.043 | 215.938 | 0.223517 | 0.470606 | 1.32275 | 0.220168 | 0.000349346 | 2.54732e-05 | 1.09171e-05 | 1(Win) | true |
| Glaze | 4134.63 | 0.345961 | 805.968ms | 2866 | 1280 | 6694.91 | 661.059 | 0.186246 | 1.27732 | 3.57397 | 0.584439 | 0.000351099 | 4.38874e-05 | 1.00859e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2240.89 | 0.039074 | 930.381ms | 4390 | 4890 | 2605.99 | 1868.29 | 0.0100631 | 2.26335 | 10.5515 | 1.87631 | 0.00155186 | 4.65363e-05 | 9.22342e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1685.77 | 0.0322105 | 997.676ms | 4390 | 4890 | 3129.23 | 2483.52 | 0.0504895 | 2.99151 | 14.0175 | 2.41936 | 0.00256658 | 6.40049e-05 | 1.79344e-05 | 2(Loss) | true |
| Glaze | 1656.72 | 0.0384997 | 998.867ms | 4390 | 4890 | 4628.63 | 2527.05 | 0.0356386 | 3.0437 | 13.7046 | 2.64009 | 0.00105296 | 3.1164e-05 | 6.47502e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1053.04 | 0.0351689 | 1149.7ms | 4390 | 4890 | 9560.25 | 3975.77 | 0.128113 | 4.76556 | 20.3667 | 3.40684 | 0.00389186 | 6.56353e-05 | 2.02636e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2618.98 | 0.1276 | 923.352ms | 4390 | 80 | 332.855 | 1598.58 | 0.167057 | 1.94404 | 9.32665 | 1.59294 | 0.00180524 | 2.2779e-05 | 0 | 1(Win) | true |
| Glaze | 1942.19 | 0.077072 | 983.997ms | 4390 | 640 | 1766.53 | 2155.62 | 0.0303078 | 2.60408 | 12.215 | 2.31139 | 0.000591187 | 3.73719e-05 | 1.17454e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1891.36 | 0.0344755 | 995.634ms | 4390 | 2560 | 1490.87 | 2213.55 | 0.048012 | 2.6761 | 12.7911 | 2.13599 | 0.00276463 | 4.03082e-05 | 8.45316e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1175.51 | 0.193735 | 1133.2ms | 4390 | 80 | 3808.76 | 3561.54 | 0.148682 | 4.3126 | 18.9834 | 3.09749 | 0.00332289 | 3.70159e-05 | 5.69476e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10335.8 | 0.322352 | 783.987ms | 4390 | 160 | 272.789 | 405.062 | 0.142155 | 0.529425 | 2.2622 | 0.375175 | 0.000234909 | 3.70159e-05 | 1.28132e-05 | 1(Win) | true |
| Glaze | 3167.71 | 0.260589 | 877.102ms | 4390 | 2560 | 30366.2 | 1321.66 | 0.0581907 | 1.61309 | 5.76378 | 0.85672 | 0.000551769 | 3.51474e-05 | 6.40661e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11184.3 | 0.179338 | 780.058ms | 4390 | 640 | 288.425 | 374.33 | 0.134169 | 0.493296 | 2.14077 | 0.346014 | 0.00022779 | 5.37443e-05 | 2.95416e-05 | 1(Win) | true |
| Glaze | 3981.59 | 0.0968848 | 850.435ms | 4390 | 4890 | 5075.02 | 1051.5 | 0.243671 | 1.29528 | 5.37927 | 0.771071 | 0.000548234 | 2.11486e-05 | 9.78241e-07 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3109.37 | 0.0381016 | 1033.6ms | 9378 | 2560 | 3074.7 | 2876.33 | 0.0182965 | 1.62043 | 7.48017 | 1.20836 | 0.0017302 | 1.85357e-05 | 2.58251e-06 | 1(Win) | true |
| Jsonifier | 2629.78 | 0.0425551 | 1112.41ms | 9378 | 320 | 670.248 | 3400.88 | 0.017272 | 1.91014 | 8.22318 | 1.73033 | 0.00308068 | 2.1993e-05 | 3.33227e-06 | 2(Loss) | true |
| Glaze | 2325.28 | 0.0347281 | 1127.83ms | 9378 | 1280 | 2283.71 | 3846.23 | 0.00452981 | 2.15632 | 9.70665 | 1.89966 | 0.00281127 | 6.52291e-05 | 3.56553e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2137.61 | 0.064179 | 1170.24ms | 9378 | 640 | 4614.55 | 4183.9 | 0.134412 | 2.34443 | 10.161 | 1.62519 | 0.00171945 | 3.36559e-05 | 9.33035e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3456.8 | 0.0950869 | 1033.07ms | 9378 | 1280 | 7746.8 | 2587.23 | 0.0350098 | 1.45954 | 6.90606 | 1.07571 | 0.00174844 | 3.83211e-05 | 1.56617e-05 | 1(Win) | true |
| Jsonifier | 2840.75 | 0.225422 | 1088.49ms | 9378 | 160 | 8058.77 | 3148.31 | 0.0384979 | 1.76621 | 7.64907 | 1.59768 | 0.00307168 | 1.4662e-05 | 0 | 2(Loss) | true |
| Glaze | 2548.7 | 0.0262585 | 1118.52ms | 9378 | 4890 | 4151.75 | 3509.06 | 0.03506 | 1.96827 | 9.00811 | 1.74579 | 0.00303619 | 2.1501e-05 | 3.68526e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2330.92 | 0.0820018 | 1162.09ms | 9378 | 640 | 6335.65 | 3836.92 | 0.059542 | 2.15037 | 9.52506 | 1.48273 | 0.00150785 | 1.31625e-05 | 6.66453e-07 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16406.7 | 0.151285 | 810.867ms | 11521 | 320 | 328.456 | 669.681 | 0.470944 | 0.321402 | 1.50803 | 0.276712 | 8.6798e-05 | 1.13922e-05 | 3.25493e-06 | 1(Win) | true |
| Glaze | 4774.32 | 0.25606 | 971.106ms | 11521 | 320 | 11111.9 | 2301.33 | 0.0462834 | 1.05695 | 3.86581 | 0.686833 | 0.0011593 | 2.76669e-05 | 1.19347e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17716.4 | 0.04411 | 805.901ms | 11521 | 4890 | 365.942 | 620.176 | 0.148693 | 0.299541 | 1.46014 | 0.265259 | 8.7153e-05 | 2.32349e-05 | 7.38404e-06 | 1(Win) | true |
| Glaze | 5424.36 | 0.0540633 | 943.506ms | 11521 | 4890 | 5864.04 | 2025.54 | 0.163325 | 0.940877 | 3.62026 | 0.633279 | 0.00117364 | 2.35899e-05 | 1.00821e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2469.14 | 0.060751 | 926.098ms | 4669 | 1280 | 1536.29 | 1803.34 | 0.0635569 | 2.05683 | 8.27094 | 1.65282 | 0.00133594 | 5.18714e-05 | 2.59357e-05 | 1(Win) | true |
| Glaze | 2048.87 | 0.0500535 | 967.49ms | 4669 | 4890 | 5786.26 | 2173.25 | 0.0972549 | 2.47085 | 10.1244 | 1.80403 | 0.000840071 | 4.95808e-05 | 1.34902e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1932.72 | 0.115928 | 976.602ms | 4669 | 80 | 570.661 | 2303.85 | 0.111645 | 2.66875 | 11.2643 | 1.92761 | 0.00129846 | 6.69308e-05 | 1.07089e-05 | 3(Loss) | true |
| simdjson (ondemand) | 668.093 | 0.0221234 | 1420.3ms | 4669 | 4890 | 10631.3 | 6664.8 | 0.0360758 | 7.46865 | 28.8743 | 4.58836 | 0.00334381 | 5.51871e-05 | 1.3315e-05 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2705 | 0.0485586 | 914.062ms | 4669 | 2560 | 1635.63 | 1646.1 | 0.0278754 | 1.88936 | 7.75541 | 1.52795 | 0.00141182 | 4.71026e-05 | 1.8657e-05 | 1(Win) | true |
| Glaze | 2302.22 | 0.0339036 | 947.328ms | 4669 | 4890 | 2102.59 | 1934.09 | 0.0242868 | 2.2024 | 9.35875 | 1.63097 | 0.000797717 | 3.39007e-05 | 6.70129e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2020.76 | 0.0320696 | 974.858ms | 4669 | 4890 | 2441.82 | 2203.48 | 0.0932991 | 2.50031 | 10.7959 | 1.81238 | 0.0011517 | 3.07033e-05 | 5.21212e-06 | 3(Loss) | true |
| simdjson (ondemand) | 697.073 | 0.0171997 | 1395.36ms | 4669 | 4890 | 5902.6 | 6387.71 | 0.0276876 | 7.16088 | 28.1086 | 4.41401 | 0.00289181 | 4.50257e-05 | 1.18696e-05 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12761.1 | 0.0270786 | 762.001ms | 4669 | 4890 | 43.655 | 348.929 | 0.0851336 | 0.442016 | 1.40544 | 0.361748 | 0.000214441 | 3.36817e-05 | 3.81054e-06 | 1(Win) | true |
| Glaze | 2357.11 | 0.202449 | 939.125ms | 4669 | 2560 | 37442.1 | 1889.05 | 0.00564488 | 2.15675 | 3.66331 | 0.503962 | 0.000223047 | 3.31308e-05 | 2.50991e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14518.7 | 0.0876986 | 759.761ms | 4669 | 80 | 5.78718 | 306.688 | 0.296651 | 0.395735 | 1.29964 | 0.336689 | 0.000214179 | 1.33862e-05 | 2.67723e-06 | 1(Win) | true |
| Glaze | 2599.87 | 0.15363 | 918.928ms | 4669 | 4890 | 33853.8 | 1712.67 | 0.216435 | 1.96923 | 3.1949 | 0.397516 | 0.00021834 | 4.48943e-05 | 1.05118e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2895.02 | 0.125127 | 997.386ms | 7932 | 40 | 427.587 | 2612.95 | 0.00829272 | 1.74799 | 7.39637 | 1.19276 | 0.00093293 | 2.52143e-05 | 0 | 1(Win) | true |
| Glaze | 2381.41 | 0.0715317 | 1055.72ms | 7932 | 1280 | 6608.53 | 3176.5 | 0.0735332 | 2.16533 | 8.95386 | 1.66919 | 0.00163539 | 4.26477e-05 | 1.77288e-05 | 2(Loss) | true |
| Jsonifier | 2072.95 | 0.0482581 | 1100.77ms | 7932 | 80 | 248.096 | 3649.18 | 0.0862464 | 2.47342 | 7.99521 | 1.79337 | 0.00156486 | 1.5759e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1131.98 | 0.0451521 | 1418.96ms | 7932 | 160 | 1456.68 | 6682.56 | 0.0673848 | 4.49557 | 17.5124 | 2.72428 | 0.00176027 | 2.9942e-05 | 7.09153e-06 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3119.47 | 0.0364513 | 986.749ms | 7932 | 4890 | 3820.67 | 2424.94 | 0.0216264 | 1.64937 | 7.13011 | 1.12695 | 0.000903384 | 2.00065e-05 | 1.52111e-06 | 1(Win) | true |
| Glaze | 2582.42 | 0.0305408 | 1034.74ms | 7932 | 2560 | 2048.87 | 2929.25 | 0.0278631 | 1.98424 | 8.50277 | 1.56732 | 0.00151197 | 2.42786e-05 | 5.22015e-06 | 2(Loss) | true |
| Jsonifier | 2219.68 | 0.052828 | 1085.32ms | 7932 | 80 | 259.3 | 3407.94 | 0.152718 | 2.30958 | 7.72882 | 1.72756 | 0.00138994 | 2.20625e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1153.35 | 0.0797877 | 1405.36ms | 7932 | 320 | 8763.18 | 6558.73 | 0.1269 | 4.33551 | 17.0616 | 2.62166 | 0.00185562 | 7.17032e-05 | 2.63962e-05 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14956.8 | 0.214786 | 822.94ms | 9249 | 30 | 48.1333 | 589.733 | 0.186178 | 0.355404 | 1.23148 | 0.293005 | 0.00010812 | 1.0812e-05 | 3.60399e-06 | 1(Win) | true |
| Glaze | 2392.83 | 0.228291 | 1122.4ms | 9249 | 320 | 22661.7 | 3686.23 | 0.0382481 | 2.0978 | 3.87674 | 0.64807 | 0.000326387 | 1.52043e-05 | 1.68937e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16194.4 | 0.0651116 | 798.518ms | 9249 | 4890 | 615.016 | 544.666 | 0.350928 | 0.330386 | 1.16791 | 0.2783 | 0.000108363 | 1.03477e-05 | 1.39295e-06 | 1(Win) | true |
| Glaze | 3008.83 | 0.145869 | 1043.74ms | 9249 | 4890 | 89419.5 | 2931.55 | 0.080701 | 1.67728 | 3.62258 | 0.590447 | 0.000345762 | 1.69366e-05 | 1.87938e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 783.33 | 0.059402 | 1312.07ms | 4604 | 1280 | 14190.3 | 5605.19 | 0.00698244 | 6.4152 | 25.3295 | 5.54301 | 0.0058105 | 8.16206e-05 | 2.91866e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 688.612 | 0.0248984 | 1389.27ms | 4604 | 4890 | 12324.6 | 6376.18 | 0.189078 | 7.28099 | 29.126 | 5.95265 | 0.00686719 | 0.000110067 | 5.0192e-05 | 2(Loss) | true |
| Glaze | 636.119 | 0.0356331 | 1441.12ms | 4604 | 2560 | 15486.1 | 6902.36 | 0.0317329 | 7.87318 | 33.7793 | 6.87989 | 0.00404523 | 5.21795e-05 | 1.08601e-05 | 3(Loss) | true |
| simdjson (ondemand) | 495.338 | 0.098328 | 1635.56ms | 4604 | 320 | 24309.3 | 8864.09 | 0.0392185 | 10.2462 | 39.9105 | 7.34492 | 0.00535675 | 0.000123534 | 8.6881e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 986.858 | 0.065282 | 1289.42ms | 4604 | 640 | 5399.19 | 4449.19 | 0.0796073 | 5.07478 | 20.0743 | 4.35225 | 0.00511376 | 4.7513e-05 | 1.11995e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 824.497 | 0.0639917 | 1376.47ms | 4604 | 640 | 7432.23 | 5325.32 | 0.0636293 | 6.06256 | 24.7024 | 4.94288 | 0.00523356 | 3.93679e-05 | 6.78758e-06 | 2(Loss) | true |
| Glaze | 734.306 | 0.0596716 | 1434.97ms | 4604 | 640 | 8147.65 | 5979.41 | 0.328686 | 6.80585 | 29.2706 | 5.84427 | 0.00550778 | 3.83498e-05 | 3.73317e-06 | 3(Loss) | true |
| simdjson (ondemand) | 562.281 | 0.0320522 | 1624.06ms | 4604 | 2560 | 16036.9 | 7808.76 | 0.0747599 | 9.0043 | 36.5083 | 6.56126 | 0.00407331 | 5.91368e-05 | 1.72235e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1532.94 | 0.0922406 | 1030.71ms | 4604 | 320 | 2233.65 | 2864.24 | 0.122047 | 3.34582 | 9.47415 | 0.659861 | 0.000492099 | 0.000213809 | 0.000139824 | 1(Win) | true |
| Glaze | 817.349 | 0.163206 | 1287.03ms | 4604 | 320 | 24596.7 | 5371.9 | 0.437271 | 6.23048 | 12.9859 | 1.08667 | 0.00154282 | 5.36219e-05 | 1.56114e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1575.02 | 0.0912975 | 1023.17ms | 4604 | 80 | 518.207 | 2787.71 | 0.0757216 | 3.25908 | 9.35447 | 0.630973 | 0.000562011 | 2.17202e-05 | 0 | 1(Win) | true |
| Glaze | 853.179 | 0.0674964 | 1260.03ms | 4604 | 2560 | 30888.2 | 5146.3 | 0.170402 | 5.96318 | 12.4472 | 0.970679 | 0.00083029 | 0.000136176 | 6.5585e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2527.39 | 0.0432319 | 1432.87ms | 18245 | 1280 | 11338.6 | 6884.48 | 0.0480591 | 2.01099 | 8.31949 | 1.54294 | 0.00138274 | 4.62027e-05 | 2.51781e-05 | 1(Win) | true |
| Jsonifier | 2125.14 | 0.0680955 | 1562.99ms | 18245 | 160 | 4973.61 | 8187.61 | 0.0834272 | 2.3908 | 9.15232 | 2.09718 | 0.00230577 | 1.26747e-05 | 1.02768e-06 | 2(Loss) | true |
| Glaze | 1878.57 | 0.0858381 | 1678.96ms | 18245 | 30 | 1896.34 | 9262.27 | 0.0737216 | 2.70451 | 11.8109 | 2.38679 | 0.00327578 | 8.95222e-05 | 3.65397e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1811.62 | 0.0735551 | 1708.41ms | 18245 | 320 | 15970.9 | 9604.55 | 0.212111 | 2.75342 | 10.9477 | 1.88342 | 0.00175065 | 1.02768e-05 | 1.02768e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2921.14 | 0.0809906 | 1437.71ms | 18245 | 640 | 14894.8 | 5956.51 | 0.0730284 | 1.72443 | 7.23568 | 1.29542 | 0.00128939 | 3.10873e-05 | 1.61859e-05 | 1(Win) | true |
| Jsonifier | 2439.59 | 0.0983263 | 1570.1ms | 18245 | 40 | 1967.22 | 7132.25 | 0.0301357 | 2.08831 | 8.00088 | 1.83465 | 0.00225952 | 2.19238e-05 | 6.85119e-06 | 2(Loss) | true |
| Glaze | 2085.55 | 0.0555067 | 1669.38ms | 18245 | 1280 | 27450.4 | 8343.03 | 0.0178167 | 2.40993 | 10.7216 | 2.13549 | 0.00314564 | 1.18611e-05 | 1.79844e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2002.19 | 0.029164 | 1719.78ms | 18245 | 4890 | 31410.9 | 8690.36 | 0.178286 | 2.50594 | 10.2001 | 1.70902 | 0.00190908 | 2.21144e-05 | 7.63298e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5175.86 | 0.0583274 | 1202.26ms | 24579 | 4890 | 34120.7 | 4528.79 | 0.453893 | 0.974093 | 2.97746 | 0.388503 | 0.000152598 | 1.43521e-05 | 4.77572e-06 | 1(Win) | true |
| Glaze | 3433.43 | 0.0632518 | 1434.88ms | 24579 | 4890 | 91185.8 | 6827.09 | 0.0398266 | 1.45777 | 3.73945 | 0.480451 | 0.000347122 | 1.7572e-05 | 5.72421e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5311.06 | 0.153678 | 1196.68ms | 24579 | 640 | 29442.3 | 4413.5 | 0.147376 | 0.954688 | 2.95752 | 0.383865 | 0.000159562 | 2.19318e-05 | 1.29684e-05 | 1(Win) | true |
| Glaze | 3940.14 | 0.0679428 | 1349.72ms | 24579 | 4890 | 79891.5 | 5949.12 | 0.166369 | 1.27876 | 3.59514 | 0.447659 | 0.000292209 | 1.15899e-05 | 3.62755e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 865.959 | 0.0974874 | 1253.55ms | 4604 | 40 | 977.31 | 5070.35 | 0.0983805 | 5.77872 | 23.4633 | 5.09731 | 0.00688532 | 5.97307e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 754.711 | 0.0616606 | 1345.97ms | 4604 | 160 | 2058.95 | 5817.74 | 0.206376 | 6.6222 | 28.0248 | 5.74718 | 0.0051667 | 8.55235e-05 | 3.80104e-05 | 2(Loss) | true |
| Glaze | 624.494 | 0.120785 | 1444.47ms | 4604 | 30 | 2163.52 | 7030.83 | 0.125795 | 7.99555 | 33.212 | 6.75738 | 0.00708804 | 5.79206e-05 | 2.17202e-05 | 3(Loss) | true |
| simdjson (ondemand) | 486.144 | 0.152984 | 1641.02ms | 4604 | 160 | 30545.9 | 9031.72 | 0.419731 | 10.2942 | 39.6615 | 7.28302 | 0.00828356 | 8.28084e-05 | 1.35752e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1069.1 | 0.072949 | 1252.25ms | 4604 | 640 | 5744.5 | 4106.93 | 0.180967 | 4.70649 | 19.2429 | 4.1309 | 0.0060104 | 3.19016e-05 | 2.37565e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 923.42 | 0.0922341 | 1321.33ms | 4604 | 160 | 3077.34 | 4754.84 | 0.0111741 | 5.5231 | 23.7363 | 4.76607 | 0.00513276 | 6.51607e-05 | 2.30778e-05 | 2(Loss) | true |
| Glaze | 737.124 | 0.0277818 | 1440.78ms | 4604 | 2560 | 7010.53 | 5956.55 | 0.0725108 | 6.77654 | 28.9544 | 5.77585 | 0.0056566 | 4.93796e-05 | 9.24807e-06 | 3(Loss) | true |
| simdjson (ondemand) | 541.166 | 0.0334423 | 1664.71ms | 4604 | 2560 | 18847 | 8113.44 | 0.0111974 | 9.22956 | 36.8392 | 6.62348 | 0.00781895 | 0.000118019 | 5.78641e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1545 | 0.0776407 | 1032.57ms | 4604 | 1280 | 6231.65 | 2841.89 | 0.0457101 | 3.25842 | 9.47176 | 0.660513 | 0.000570326 | 5.68459e-05 | 2.07021e-05 | 1(Win) | true |
| Glaze | 786.097 | 0.0629836 | 1310.13ms | 4604 | 2560 | 31682.1 | 5585.47 | 0.0600971 | 6.36565 | 12.912 | 1.07885 | 0.00188466 | 6.94878e-05 | 2.90169e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1615.68 | 0.0947422 | 1019.99ms | 4604 | 1280 | 8485.15 | 2717.57 | 0.0810778 | 3.11829 | 9.35209 | 0.631626 | 0.000512123 | 3.12228e-05 | 5.26037e-06 | 1(Win) | true |
| Glaze | 840.908 | 0.0510069 | 1273.02ms | 4604 | 4890 | 34684.9 | 5221.4 | 0.0157145 | 5.95232 | 12.437 | 0.970896 | 0.000941477 | 0.000143336 | 6.69374e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2641.9 | 0.046582 | 1411.78ms | 18245 | 640 | 6023.8 | 6586.09 | 0.0117658 | 1.88969 | 8.03322 | 1.48929 | 0.00155402 | 1.06193e-05 | 2.31228e-06 | 1(Win) | true |
| Jsonifier | 2163.33 | 0.0462542 | 1550.27ms | 18245 | 160 | 2214.45 | 8043.07 | 0.0932387 | 2.30721 | 8.72177 | 2.02615 | 0.00274493 | 2.43217e-05 | 1.13045e-05 | 2(Loss) | true |
| Glaze | 1864.96 | 0.0161032 | 1686.65ms | 18245 | 4890 | 11037.8 | 9329.82 | 0.0250868 | 2.67056 | 11.6773 | 2.35629 | 0.00357821 | 2.33809e-05 | 8.4512e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1786.09 | 0.144042 | 1712.02ms | 18245 | 40 | 7876.28 | 9741.85 | 0.0863224 | 2.79055 | 10.8094 | 1.85062 | 0.00197314 | 9.59167e-05 | 5.06988e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3119.03 | 0.0197498 | 1406.59ms | 18245 | 4890 | 5935.87 | 5578.59 | 0.00681594 | 1.60339 | 6.96251 | 1.24467 | 0.00135925 | 1.43693e-05 | 3.60914e-06 | 1(Win) | true |
| Jsonifier | 2497.36 | 0.0480757 | 1546.31ms | 18245 | 80 | 897.563 | 6967.26 | 0.0650836 | 1.99977 | 7.65919 | 1.78284 | 0.00227528 | 2.19238e-05 | 0 | 2(Loss) | true |
| Glaze | 2066.23 | 0.105902 | 1683.07ms | 18245 | 30 | 2385.96 | 8421.03 | 0.0265139 | 2.4138 | 10.6174 | 2.11269 | 0.00316251 | 9.13492e-06 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 2032.14 | 0.190931 | 1719.04ms | 18245 | 40 | 10690.4 | 8562.3 | 0.288134 | 2.50124 | 10.1709 | 1.70056 | 0.00193341 | 1.91833e-05 | 0 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5037.2 | 0.113645 | 1218.39ms | 24579 | 640 | 17899.1 | 4653.45 | 0.244113 | 0.993188 | 2.9786 | 0.388625 | 0.00013407 | 5.72135e-06 | 6.35705e-08 | 1(Win) | true |
| Glaze | 3527.27 | 0.0636105 | 1419.59ms | 24579 | 4890 | 87381.3 | 6645.47 | 0.379326 | 1.41563 | 3.7373 | 0.480532 | 0.000405121 | 1.12487e-05 | 2.9453e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5121.69 | 0.149207 | 1209.16ms | 24579 | 640 | 29844.3 | 4576.68 | 0.0202753 | 0.979921 | 2.95866 | 0.383987 | 0.000153205 | 1.01077e-05 | 3.55995e-06 | 1(Win) | true |
| Glaze | 3877.5 | 0.239047 | 1353.78ms | 24579 | 320 | 66825.2 | 6045.23 | 0.0105466 | 1.2878 | 3.59408 | 0.447374 | 0.000306537 | 5.33992e-06 | 2.54282e-07 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1676.03 | 0.065145 | 1022.72ms | 5094 | 160 | 570.477 | 2898.53 | 0.155276 | 3.00287 | 13.4749 | 2.44739 | 0.000906704 | 3.19003e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1516.35 | 0.0757489 | 1062.01ms | 5094 | 160 | 942.308 | 3203.76 | 0.10702 | 3.31849 | 14.5542 | 2.60954 | 0.00233854 | 3.43541e-05 | 0 | 2(Loss) | true |
| Glaze | 1251.38 | 0.0457242 | 1134.81ms | 5094 | 1280 | 4033.11 | 3882.12 | 0.144886 | 4.02181 | 16.6027 | 3.19984 | 0.00477308 | 3.71147e-05 | 4.601e-06 | 3(Loss) | true |
| simdjson (ondemand) | 832.133 | 0.0334386 | 1337.31ms | 5094 | 4890 | 18635.4 | 5838.03 | 0.0081692 | 6.01338 | 22.4761 | 3.82273 | 0.00600337 | 5.70863e-05 | 1.39303e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2143.86 | 0.0451484 | 1028.67ms | 5094 | 4890 | 5118.2 | 2266.01 | 0.211383 | 2.38204 | 10.9709 | 1.87809 | 0.000977011 | 3.15942e-05 | 2.08754e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1889.38 | 0.0571049 | 1061.61ms | 5094 | 320 | 689.885 | 2571.22 | 0.0767491 | 2.72193 | 12.2937 | 2.08697 | 0.001403 | 3.31272e-05 | 4.29427e-06 | 2(Loss) | true |
| Glaze | 1614.75 | 0.223926 | 1110.66ms | 5094 | 30 | 1361.57 | 3008.53 | 0.109808 | 3.11646 | 13.2758 | 2.46525 | 0.00443659 | 5.23492e-05 | 1.30873e-05 | 3(Loss) | true |
| simdjson (ondemand) | 975.603 | 0.0434695 | 1307.56ms | 5094 | 2560 | 11994.5 | 4979.5 | 0.150407 | 5.13938 | 19.8123 | 3.22065 | 0.00507429 | 3.48909e-05 | 8.35849e-06 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12763.5 | 0.0620648 | 779.679ms | 5094 | 1280 | 71.4296 | 380.617 | 0.0090322 | 0.436525 | 1.79093 | 0.301924 | 0.000263484 | 2.3005e-05 | 1.99377e-06 | 1(Win) | true |
| Glaze | 3404.08 | 0.140239 | 891.1ms | 5094 | 4890 | 19587 | 1427.12 | 0.290555 | 1.50787 | 5.8936 | 0.906165 | 0.000202492 | 4.49625e-05 | 9.07279e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14025.8 | 0.129028 | 772.54ms | 5094 | 160 | 31.9558 | 346.363 | 0.122855 | 0.396858 | 1.68178 | 0.276993 | 0.000196309 | 4.04888e-05 | 8.58854e-06 | 1(Win) | true |
| Glaze | 3685.81 | 0.194495 | 876.821ms | 5094 | 4890 | 32135.1 | 1318.03 | 1.17118 | 1.40385 | 5.4413 | 0.804084 | 0.000257812 | 3.80977e-05 | 5.62031e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2331.16 | 0.0841442 | 1075.61ms | 8051 | 640 | 4915.68 | 3293.65 | 0.0105802 | 2.19057 | 9.82859 | 1.68799 | 0.00101812 | 2.25127e-05 | 2.71705e-06 | 1(Win) | true |
| Jsonifier | 1663.31 | 0.0992336 | 1199.81ms | 8051 | 640 | 13429.3 | 4616.13 | 0.110327 | 3.03669 | 11.5586 | 2.3407 | 0.00432128 | 1.94075e-05 | 1.94075e-07 | 2(Loss) | true |
| Glaze | 1641.15 | 0.0393022 | 1219.05ms | 8051 | 2560 | 8655.2 | 4678.45 | 0.229375 | 3.061 | 13.1995 | 2.5721 | 0.0029973 | 3.01302e-05 | 1.00919e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1303.73 | 0.0387801 | 1335.12ms | 8051 | 4890 | 25506.8 | 5889.3 | 0.117192 | 3.86668 | 14.6966 | 2.44069 | 0.00383491 | 5.70494e-05 | 2.2073e-05 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2802.91 | 0.0757146 | 1072.49ms | 8051 | 1280 | 5506.18 | 2739.31 | 0.0806911 | 1.82958 | 8.41324 | 1.3602 | 0.000880908 | 2.10572e-05 | 1.5526e-06 | 1(Win) | true |
| Glaze | 2017.93 | 0.0332481 | 1185.3ms | 8051 | 4890 | 7825.81 | 3804.9 | 0.145049 | 2.50799 | 11.1053 | 2.1098 | 0.00285026 | 1.70437e-05 | 1.62563e-06 | 2(Loss) | true |
| Jsonifier | 1900.16 | 0.0342402 | 1207.77ms | 8051 | 2560 | 4900.43 | 4040.74 | 0.088637 | 2.65084 | 9.97975 | 1.98149 | 0.00404632 | 2.27068e-05 | 4.1241e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1504.66 | 0.0478511 | 1312.84ms | 8051 | 2560 | 15263.2 | 5102.82 | 0.128715 | 3.37494 | 13.2305 | 2.10533 | 0.00290526 | 8.75279e-05 | 4.99259e-05 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15677.6 | 0.0951321 | 797.7ms | 9255 | 4890 | 1402.68 | 562.986 | 0.337292 | 0.342505 | 1.45889 | 0.27866 | 0.000279869 | 5.94605e-05 | 2.91889e-05 | 1(Win) | true |
| Glaze | 3667.18 | 0.124087 | 994.601ms | 9255 | 2560 | 22834.1 | 2406.82 | 0.134414 | 1.38147 | 4.93593 | 0.85208 | 0.000228888 | 2.5493e-05 | 6.92193e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17096.7 | 0.162556 | 792.149ms | 9255 | 160 | 112.682 | 516.256 | 0.196946 | 0.314504 | 1.39946 | 0.265154 | 0.000267423 | 3.51162e-05 | 6.75311e-06 | 1(Win) | true |
| Glaze | 4344.84 | 0.225366 | 951.403ms | 9255 | 1280 | 26828.3 | 2031.44 | 0.332743 | 1.1827 | 4.61632 | 0.778498 | 0.000222008 | 8.4245e-05 | 3.86615e-05 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5474.61 | 0.228171 | 790.155ms | 2889 | 80 | 105.487 | 503.262 | 0.398298 | 0.985644 | 3.83281 | 0.446175 | 0.000696608 | 6.92281e-05 | 1.29803e-05 | 1(Win) | true |
| Jsonifier | 5374.98 | 0.0773742 | 810.685ms | 2889 | 320 | 50.3366 | 512.591 | 0.0921417 | 1.01462 | 3.82451 | 0.530287 | 0.000346141 | 2.37972e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 5337.59 | 0.0511987 | 788.105ms | 2889 | 640 | 44.6995 | 516.181 | 0.471198 | 1.01956 | 3.82451 | 0.530287 | 0.000346141 | 9.7352e-06 | 1.62253e-06 | 3(Loss) | true |
| Glaze | 3152.24 | 0.117432 | 828.933ms | 2889 | 320 | 337.118 | 874.034 | 0.153862 | 1.66925 | 6.80547 | 1.23364 | 0.000354794 | 3.89408e-05 | 1.94704e-05 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5644.42 | 0.0710948 | 788.362ms | 2889 | 1280 | 154.149 | 488.122 | 0.0929166 | 0.957355 | 3.75597 | 0.428522 | 0.000692281 | 2.46084e-05 | 7.03098e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 5584.09 | 0.153676 | 789.662ms | 2889 | 640 | 367.942 | 493.395 | 0.0433668 | 0.977367 | 3.67844 | 0.496366 | 0.000346141 | 4.54309e-05 | 2.21746e-05 | 2(Loss) | true |
| Jsonifier | 5481.46 | 0.150367 | 788.103ms | 2889 | 30 | 17.1368 | 502.633 | 0.0198913 | 0.976347 | 3.67844 | 0.496366 | 0.000346141 | 0 | 0 | 3(Loss) | true |
| Glaze | 3148.06 | 0.0688861 | 827.613ms | 2889 | 4890 | 1777.39 | 875.195 | 0.14401 | 1.66357 | 6.72897 | 1.21634 | 0.000350529 | 5.408e-05 | 2.63322e-05 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6633.65 | 0.132666 | 789.933ms | 3808 | 320 | 168.794 | 547.45 | 0.144056 | 0.806623 | 3.22348 | 0.354255 | 0.000530955 | 5.17004e-05 | 7.38577e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 6180.36 | 0.0412561 | 797.241ms | 3808 | 1280 | 75.2233 | 587.602 | 0.126812 | 0.872969 | 3.33981 | 0.418067 | 0.000263015 | 2.07212e-05 | 2.46192e-06 | 2(Loss) | true |
| Jsonifier | 6121.61 | 0.0346563 | 796.58ms | 3808 | 1280 | 54.1051 | 593.241 | 0.0407093 | 0.867024 | 3.33981 | 0.418067 | 0.000263015 | 1.88747e-05 | 3.0774e-06 | 3(Loss) | true |
| Glaze | 3358.63 | 0.0558104 | 846.079ms | 3808 | 4890 | 1780.77 | 1081.27 | 0.38251 | 1.54429 | 6.48057 | 1.20746 | 0.000309702 | 2.13199e-05 | 6.5517e-06 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6902.47 | 0.0648285 | 786.552ms | 3808 | 4890 | 568.886 | 526.129 | 0.0873394 | 0.784558 | 3.1657 | 0.340861 | 0.000525425 | 4.14046e-05 | 1.82588e-05 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 6413.39 | 0.0781329 | 793.577ms | 3808 | 4890 | 957.184 | 566.252 | 0.253362 | 0.838137 | 3.22899 | 0.392332 | 0.000264377 | 3.94176e-05 | 2.10514e-05 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6411.07 | 0.0742934 | 795.881ms | 3808 | 2560 | 453.392 | 566.457 | 0.0733576 | 0.841213 | 3.22899 | 0.392332 | 0.000264246 | 4.67765e-05 | 1.86696e-05 | 2(Tie) | true |
| Glaze | 3358.02 | 0.246236 | 845.858ms | 3808 | 30 | 212.74 | 1081.47 | 0.0769965 | 1.54693 | 6.42227 | 1.19433 | 0.000437675 | 0 | 0 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2497.21 | 0.175842 | 845.554ms | 2889 | 640 | 2408.84 | 1103.3 | 0.168528 | 2.11138 | 6.71513 | 1.14849 | 0.0016274 | 8.86985e-05 | 4.1645e-05 | 1(Win) | true |
| Glaze | 2360.23 | 0.142479 | 856.448ms | 2889 | 160 | 442.6 | 1167.33 | 0.0732973 | 2.21848 | 8.80166 | 1.50813 | 0.000700935 | 3.46141e-05 | 8.65351e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2109.95 | 0.0849183 | 877.323ms | 2889 | 1280 | 1573.85 | 1305.8 | 0.248609 | 2.44808 | 8.43302 | 1.32191 | 0.000694985 | 0.00014711 | 7.95042e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1018.73 | 0.0517385 | 1018.99ms | 2889 | 1280 | 2506.19 | 2704.51 | 0.00427508 | 4.96179 | 17.1018 | 2.87297 | 0.000480811 | 7.73408e-05 | 3.1369e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2804.89 | 0.0775132 | 847.146ms | 2889 | 2560 | 1484.07 | 982.272 | 0.0719912 | 1.86845 | 6.12842 | 0.99827 | 0.00142147 | 7.54478e-05 | 2.02817e-05 | 1(Win) | true |
| Glaze | 2639.25 | 0.136596 | 850.481ms | 2889 | 160 | 325.333 | 1043.92 | 0.156018 | 1.99385 | 8.16476 | 1.34995 | 0.000361284 | 1.29803e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 2370.29 | 0.0614535 | 870.505ms | 2889 | 4890 | 2495.12 | 1162.37 | 0.149596 | 2.1738 | 7.62513 | 1.12842 | 0.000695254 | 0.000131661 | 5.45047e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1061.42 | 0.0802019 | 1014.08ms | 2889 | 2560 | 11095 | 2595.73 | 0.0173241 | 4.76945 | 16.6591 | 2.76116 | 0.000354118 | 0.000128586 | 5.65183e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8645.77 | 0.100626 | 773.171ms | 2963 | 4890 | 528.911 | 326.835 | 0.144646 | 0.65172 | 1.48431 | 0.241984 | 0.000337634 | 9.35188e-05 | 4.27909e-05 | 1(Win) | true |
| Glaze | 3937.89 | 0.228533 | 815.801ms | 2963 | 4890 | 13150.5 | 717.576 | 0.0574501 | 1.3356 | 3.14175 | 0.465069 | 0.00033998 | 6.17707e-05 | 1.06287e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10364.4 | 0.120356 | 771.482ms | 2963 | 80 | 8.61377 | 272.637 | 0.19676 | 0.551772 | 1.30982 | 0.201822 | 0.000337496 | 8.43739e-06 | 0 | 1(Win) | true |
| Glaze | 4061.97 | 0.31101 | 815.726ms | 2963 | 2560 | 11983.4 | 695.657 | 0.317985 | 1.29474 | 2.73068 | 0.379346 | 0.000342505 | 4.7724e-05 | 6.45988e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2712.45 | 0.142387 | 877.711ms | 3808 | 160 | 581.478 | 1338.86 | 0.137986 | 1.92537 | 6.84454 | 1.02048 | 0.00076812 | 6.401e-05 | 2.62605e-05 | 1(Win) | true |
| Glaze | 2582.29 | 0.0824569 | 887.236ms | 3808 | 160 | 215.158 | 1406.34 | 0.144227 | 1.97877 | 8.30173 | 1.47059 | 0.000485819 | 4.92384e-05 | 0 | 2(Loss) | true |
| Jsonifier | 1822.29 | 0.0582307 | 944.429ms | 3808 | 160 | 215.469 | 1992.88 | 0.119033 | 2.79543 | 7.09165 | 1.34874 | 0.000791098 | 4.43146e-05 | 6.56513e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1325.05 | 0.0934521 | 1024.59ms | 3808 | 4890 | 32078.7 | 2740.72 | 0.0596888 | 3.82691 | 13.2902 | 2.19538 | 0.000340313 | 0.000142956 | 7.02965e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2975.37 | 0.224067 | 865.038ms | 3808 | 40 | 299.177 | 1220.55 | 0.162231 | 1.72658 | 6.23162 | 0.873687 | 0.00079438 | 5.90861e-05 | 0 | 1(Win) | true |
| Glaze | 2762.7 | 0.0790972 | 887.153ms | 3808 | 160 | 172.969 | 1314.51 | 0.084228 | 1.85547 | 7.88524 | 1.36371 | 0.000293789 | 3.93908e-05 | 0 | 2(Loss) | true |
| Jsonifier | 2024.02 | 0.106978 | 936.358ms | 3808 | 40 | 147.372 | 1794.25 | 0.0232277 | 2.57512 | 6.64653 | 1.23477 | 0.00052521 | 4.59559e-05 | 2.62605e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1362.95 | 0.0395373 | 1021.16ms | 3808 | 2560 | 2841.1 | 2664.51 | 0.0378819 | 3.70483 | 12.9548 | 2.11056 | 0.000300765 | 8.17563e-05 | 2.11315e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9753.29 | 0.0396799 | 788.226ms | 4300 | 320 | 8.90689 | 420.453 | 0.0647042 | 0.559792 | 1.39256 | 0.240233 | 0.000232558 | 3.85174e-05 | 9.44767e-06 | 1(Win) | true |
| Glaze | 2921.41 | 0.548193 | 894.981ms | 4300 | 640 | 37896.4 | 1403.7 | 0.024149 | 1.74694 | 3.73535 | 0.626745 | 0.000334302 | 4.17878e-05 | 4.36047e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11055.9 | 0.0305667 | 782.799ms | 4300 | 1280 | 16.4535 | 370.916 | 0.0967713 | 0.501551 | 1.27372 | 0.212791 | 0.000232922 | 2.1439e-05 | 4.36047e-06 | 1(Win) | true |
| Glaze | 3600.08 | 0.198065 | 863.203ms | 4300 | 4890 | 24890.7 | 1139.09 | 0.288753 | 1.43326 | 3.20907 | 0.50721 | 0.000299044 | 4.19461e-05 | 1.15566e-05 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3606.71 | 0.166733 | 6700.33ms | 466906 | 640 | 2.71183e+07 | 123458 | 0.0186472 | 1.37414 | 6.67783 | 0.888273 | 0.00168283 | 0.000338615 | 2.09558e-05 | 1(Win) | true |
| Glaze | 2381.08 | 0.0898237 | 9883.02ms | 466906 | 80 | 2.25726e+06 | 187006 | 0.123437 | 2.08352 | 7.74721 | 1.47693 | 0.00245355 | 0.000230319 | 1.526e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1773.4 | 0.110314 | 6645.75ms | 466906 | 640 | 4.91013e+07 | 251087 | 0.223093 | 2.79831 | 12.5708 | 1.66781 | 0.00407241 | 0.0769432 | 4.3722e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3589.08 | 0.117319 | 6650.48ms | 466906 | 40 | 847405 | 124064 | 0.25428 | 1.38179 | 6.6767 | 0.888018 | 0.00167282 | 0.000251228 | 2.2542e-05 | 1(Win) | true |
| Glaze | 2401.86 | 0.0329662 | 9891.01ms | 466906 | 1280 | 4.78093e+06 | 185388 | 0.0730933 | 2.08675 | 7.74608 | 1.47668 | 0.00253448 | 0.000251419 | 1.73098e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1747.51 | 0.14248 | 6692.81ms | 466906 | 640 | 8.43541e+07 | 254806 | 0.272704 | 2.83437 | 12.5709 | 1.66784 | 0.0043255 | 0.0919655 | 4.1423e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4493.06 | 0.119351 | 7915.8ms | 699405 | 640 | 2.00912e+07 | 148452 | 0.00217983 | 1.10265 | 4.42734 | 0.719482 | 0.00235284 | 0.000801992 | 1.03458e-05 | 1(Win) | true |
| Glaze | 3623.55 | 0.0470922 | 9809.73ms | 699405 | 1280 | 9.61827e+06 | 184075 | 0.0602992 | 1.37026 | 5.22158 | 1.16245 | 0.00217618 | 0.00132961 | 2.28017e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2261.51 | 0.132272 | 8505.74ms | 767297 | 320 | 5.86159e+07 | 323568 | 0.226001 | 2.17986 | 8.67133 | 1.18242 | 0.00301949 | 0.078896 | 9.49926e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4590.03 | 0.157007 | 7905.65ms | 699405 | 80 | 4.16442e+06 | 145316 | 0.298369 | 1.10047 | 4.42655 | 0.719304 | 0.00235729 | 0.000887129 | 2.52536e-05 | 1(Win) | true |
| Glaze | 3614.86 | 0.0441963 | 9823.28ms | 699405 | 2560 | 1.7025e+07 | 184518 | 0.0723223 | 1.37112 | 5.22079 | 1.16228 | 0.00218376 | 0.00135902 | 3.79396e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2232.99 | 0.0838983 | 8579.49ms | 767297 | 640 | 4.83773e+07 | 327701 | 0.106349 | 2.21245 | 8.67141 | 1.18244 | 0.00294017 | 0.0920959 | 0.000102513 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3455.81 | 0.141638 | 9389.62ms | 631514 | 160 | 9.74872e+06 | 174274 | 0.591639 | 1.43274 | 7.03023 | 1.23099 | 0.00388711 | 1.29055e-05 | 9.29314e-06 | 1(Win) | true |
| Glaze | 2581.57 | 0.0659214 | 6199.57ms | 631514 | 320 | 7.56835e+06 | 233292 | 0.474483 | 1.93412 | 8.44884 | 1.51664 | 0.00338292 | 1.58053e-05 | 1.27867e-05 | 2(Loss) | true |
