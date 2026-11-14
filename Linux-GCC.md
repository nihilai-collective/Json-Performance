# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

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
*Environment generated via BenchmarkSuite commit: [27950a9](https://github.com/nihilai-collective/benchmarksuite/commit/27950a9)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2268.33 | 0.538687 | 772.083ms | 905 | 640 | 2688.67 | 380.489 | 0.485689 | 2.49589 | 11.7072 | 1.86961 | 0.00114123 | 0.000105318 | 1.20856e-05 | 1(Win) | true |
| Glaze | 1825.68 | 0.0870141 | 790.025ms | 905 | 640 | 108.295 | 472.742 | 0.402533 | 3.06092 | 14.032 | 1.94917 | 0.00110497 | 8.80525e-05 | 1.72652e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 599.179 | 0.177058 | 876.446ms | 905 | 2560 | 16651.6 | 1440.43 | 0.184557 | 8.70384 | 42.8906 | 4.43094 | 0.00836801 | 0.000167472 | 2.63294e-05 | 3(Loss) | true |
| simdjson (ondemand) | 228.057 | 0.0857843 | 1120.54ms | 905 | 30 | 316.189 | 3784.47 | 0.0246561 | 22.4229 | 105.526 | 9.82431 | 0.0788582 | 0 | 0 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2463.53 | 0.214521 | 768.201ms | 905 | 640 | 361.493 | 350.341 | 1.10182 | 2.31272 | 11.0365 | 1.73039 | 0.00110843 | 0.000155387 | 6.90608e-06 | 1(Win) | true |
| Glaze | 1874.95 | 0.13773 | 777.114ms | 905 | 4890 | 1965.56 | 460.318 | 0.424516 | 2.96269 | 13.6652 | 2.06519 | 0.0011348 | 0.0001053 | 2.55341e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 601.431 | 0.115376 | 878.73ms | 905 | 4890 | 13404.9 | 1435.04 | 0.185619 | 8.69245 | 42.2144 | 4.29171 | 0.00850784 | 0.000147556 | 1.69474e-05 | 3(Loss) | true |
| simdjson (ondemand) | 222.558 | 0.159312 | 1120.1ms | 905 | 40 | 1526.74 | 3877.97 | 0.063352 | 22.9635 | 104.842 | 9.68508 | 0.0879282 | 0.000276243 | 0 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1709.19 | 0.149045 | 776.96ms | 905 | 2560 | 1450.07 | 504.961 | 0.0428377 | 3.21961 | 11.0895 | 1.10276 | 0.00443759 | 0.000108771 | 3.06457e-05 | 1(Win) | true |
| simdjson (reflection) | 249.992 | 0.0493538 | 1070.05ms | 905 | 320 | 929.046 | 3452.41 | 0.199642 | 20.4777 | 94.537 | 21.0276 | 0.061913 | 0.000203729 | 3.45304e-06 | 2(Loss) | true |
| Glaze | 199.821 | 0.125608 | 1167.23ms | 905 | 320 | 9418.91 | 4319.24 | 0.110674 | 25.9952 | 110.857 | 23.4553 | 0.0890746 | 0.000379834 | 0.000100138 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3222.24 | 0.0695377 | 756.518ms | 905 | 1280 | 44.4049 | 267.849 | 0.0218804 | 1.80883 | 7.77459 | 0.271824 | 0.00221426 | 5.09323e-05 | 1.72652e-06 | 1(Win) | true |
| simdjson (reflection) | 2955.19 | 0.120407 | 761.352ms | 905 | 4890 | 604.694 | 292.054 | 0.121811 | 1.97349 | 8.44862 | 1.05083 | 0.00110881 | 0.000101459 | 1.9659e-05 | 2(Loss) | true |
| Glaze | 674.999 | 0.0280105 | 861.124ms | 905 | 160 | 20.5235 | 1278.63 | 0.00342151 | 7.73132 | 22.0398 | 3.36685 | 0.00782459 | 0.000234807 | 0 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1272.01 | 0.145021 | 860.244ms | 1811 | 640 | 2481.4 | 1357.78 | 0.151788 | 4.17244 | 18.4506 | 3.64992 | 0.000748033 | 9.23178e-05 | 1.89812e-05 | 1(Win) | true |
| Glaze | 1076.1 | 0.0858257 | 883.178ms | 1811 | 320 | 607.174 | 1604.96 | 0.0227758 | 4.93087 | 25.5257 | 3.72336 | 0.00228465 | 0.00010526 | 5.86692e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 711.524 | 0.108355 | 971.311ms | 1811 | 2560 | 17709 | 2427.33 | 0.129892 | 7.33621 | 33.6726 | 5.05577 | 0.000593163 | 7.85133e-05 | 1.2726e-05 | 3(Loss) | true |
| simdjson (ondemand) | 302.94 | 0.0507689 | 1299.76ms | 1811 | 2560 | 21446.7 | 5701.14 | 0.180298 | 16.9368 | 87.8056 | 11.5378 | 0.00111342 | 0.000159831 | 7.39836e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1384.58 | 0.0613252 | 854.112ms | 1811 | 320 | 187.254 | 1247.39 | 0.328108 | 3.79076 | 17.4357 | 3.42021 | 0.000819644 | 4.31391e-05 | 1.72557e-06 | 1(Win) | true |
| Glaze | 1149.19 | 0.0389082 | 879.955ms | 1811 | 320 | 109.418 | 1502.89 | 0.142428 | 4.60121 | 24.7973 | 3.4804 | 0.00101808 | 0.000100083 | 3.10602e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 735.496 | 0.0419593 | 972.435ms | 1811 | 640 | 621.315 | 2348.22 | 0.24056 | 7.00225 | 32.608 | 4.81171 | 0.00109142 | 0.000107848 | 2.41579e-05 | 3(Loss) | true |
| simdjson (ondemand) | 309.336 | 0.102263 | 1295.62ms | 1811 | 1280 | 41727.4 | 5583.27 | 0.000783585 | 16.4389 | 86.7305 | 11.2993 | 0.00060136 | 0.000132006 | 2.24324e-05 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 352.947 | 0.0397706 | 1266.96ms | 1997 | 2560 | 11789.6 | 5395.95 | 0.110375 | 14.6868 | 64.2799 | 11.7476 | 0.00285135 | 8.78271e-05 | 2.26903e-05 | 1(Win) | true |
| Jsonifier | 336.797 | 0.0533269 | 1236.1ms | 1811 | 4890 | 36568 | 5128.02 | 0.207414 | 15.3526 | 64.1872 | 11.2772 | 0.0171596 | 7.28337e-05 | 2.8456e-05 | 2(Loss) | true |
| Glaze | 325.904 | 0.076572 | 1251.34ms | 1798 | 320 | 5193.86 | 5261.38 | 0.0197746 | 15.9237 | 69.1713 | 11.7558 | 0.0218003 | 0.0001599 | 8.3426e-05 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 878.05 | 0.0362724 | 933.337ms | 1811 | 320 | 162.893 | 1966.98 | 0.128363 | 5.88099 | 19.82 | 1.03424 | 0.000600497 | 5.34925e-05 | 3.45113e-06 | 1(Win) | true |
| Glaze | 705.699 | 0.104453 | 991.384ms | 1798 | 640 | 4122.52 | 2429.8 | 0.171798 | 7.28127 | 26.614 | 2.36263 | 0.000897699 | 0.00013296 | 2.95467e-05 | 2(Loss) | true |
| simdjson (reflection) | 650.304 | 0.0939568 | 1048ms | 1997 | 640 | 4845.75 | 2928.61 | 0.0273092 | 8.02291 | 25.2954 | 2.57787 | 0.00125814 | 5.32048e-05 | 2.34727e-06 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3399.28 | 0.051212 | 826.6ms | 3862 | 4890 | 1505.57 | 1083.49 | 0.0815043 | 1.56845 | 7.20119 | 0.899016 | 0.000260363 | 6.97372e-05 | 3.19298e-05 | 1(Win) | true |
| Glaze | 1777.49 | 0.109007 | 926.458ms | 3862 | 40 | 204.071 | 2072.07 | 0.0889594 | 2.95449 | 14.6657 | 1.82108 | 0.000297773 | 4.53133e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1633.36 | 0.159633 | 944.706ms | 3862 | 80 | 1036.56 | 2254.91 | 0.0338036 | 3.21034 | 14.8019 | 1.67582 | 0.000278353 | 1.61833e-05 | 3.23666e-06 | 3(Loss) | true |
| simdjson (ondemand) | 726.33 | 0.0362463 | 1226.37ms | 3862 | 4890 | 16519.4 | 5070.82 | 0.00990436 | 7.10111 | 32.3825 | 3.56526 | 0.000651304 | 7.36556e-05 | 2.86468e-05 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3671.47 | 0.0493304 | 834.32ms | 3862 | 1280 | 313.46 | 1003.16 | 0.137655 | 1.43919 | 6.70662 | 0.786171 | 0.000329128 | 7.22181e-05 | 2.12406e-05 | 1(Win) | true |
| Glaze | 1838.52 | 0.10297 | 932.061ms | 3862 | 2560 | 10893 | 2003.29 | 0.240534 | 2.80295 | 14.1854 | 1.71129 | 0.000325386 | 4.11663e-05 | 1.08226e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1742.85 | 0.0407357 | 943.905ms | 3862 | 4890 | 3623.79 | 2113.25 | 0.0727739 | 2.95861 | 14.3084 | 1.56551 | 0.000263964 | 4.74976e-05 | 1.3132e-05 | 3(Loss) | true |
| simdjson (ondemand) | 727.743 | 0.111972 | 1238.14ms | 3862 | 320 | 10276.3 | 5060.98 | 0.0774288 | 6.99639 | 31.8708 | 3.45236 | 0.00103816 | 4.3695e-05 | 2.02292e-05 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 969.402 | 0.0450861 | 1101.76ms | 3862 | 4890 | 14348.7 | 3799.34 | 0.113498 | 5.35852 | 26.1261 | 5.37002 | 0.00753337 | 7.75741e-05 | 2.85409e-05 | 1(Win) | true |
| simdjson (reflection) | 962.89 | 0.0304445 | 1096.03ms | 3862 | 320 | 433.948 | 3825.04 | 0.100918 | 5.30769 | 27.1207 | 5.31409 | 0.00771702 | 2.75117e-05 | 0 | 2(Loss) | true |
| Glaze | 940.455 | 0.0434313 | 1112.1ms | 3862 | 1280 | 3703.09 | 3916.28 | 0.0361341 | 5.49554 | 28.6515 | 5.68799 | 0.00696025 | 0.000115913 | 6.41264e-05 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5185.56 | 0.0815401 | 830.524ms | 3862 | 4890 | 1640.15 | 710.258 | 0.152046 | 1.03517 | 5.21647 | 0.592439 | 0.000996072 | 5.09394e-05 | 1.84801e-05 | 1(Win) | true |
| simdjson (reflection) | 4001.51 | 0.0708696 | 835.228ms | 3862 | 40 | 17.0199 | 920.425 | 0.00996016 | 1.32092 | 6.79208 | 0.533661 | 0.000258933 | 3.884e-05 | 6.47333e-06 | 2(Loss) | true |
| Glaze | 2726.53 | 0.200567 | 897.821ms | 3862 | 30 | 220.213 | 1350.83 | 0.135535 | 1.91548 | 8.25065 | 0.995857 | 0.00495426 | 1.72622e-05 | 0 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1875.01 | 0.0511045 | 1214.35ms | 9578 | 4890 | 30308.8 | 4871.6 | 0.0401153 | 2.75481 | 14.0135 | 2.70024 | 0.000976783 | 1.99844e-05 | 3.75776e-06 | 1(Win) | true |
| Glaze | 1446.68 | 0.0289088 | 1360.45ms | 9578 | 4890 | 16291.9 | 6313.97 | 0.0748866 | 3.57455 | 17.6163 | 3.5213 | 0.00142035 | 2.36782e-05 | 5.48718e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1363.02 | 0.0385815 | 1399.42ms | 9578 | 4890 | 32689.9 | 6701.51 | 0.0510952 | 3.78523 | 18.7442 | 3.07517 | 0.000840094 | 3.2368e-05 | 1.44759e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1303.21 | 0.045436 | 1436.26ms | 9578 | 2560 | 25963.4 | 7009.08 | 0.134271 | 3.9339 | 19.5259 | 2.98048 | 0.00344923 | 3.04245e-05 | 1.15825e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2784.64 | 0.0392414 | 1205.47ms | 9578 | 4890 | 8102.35 | 3280.24 | 0.0373727 | 1.8438 | 9.90228 | 1.76373 | 0.000209986 | 1.72088e-05 | 4.16343e-06 | 1(Win) | true |
| Glaze | 1912.68 | 0.048531 | 1365.98ms | 9578 | 4890 | 26267.1 | 4775.65 | 0.216368 | 2.66171 | 13.3648 | 2.54239 | 0.000153257 | 3.0361e-05 | 9.92817e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1741.19 | 0.0678219 | 1409.05ms | 9578 | 2560 | 32407.1 | 5246.02 | 0.15385 | 2.92949 | 14.7119 | 2.15995 | 0.000111665 | 2.06773e-05 | 6.6885e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1683.99 | 0.0309798 | 1418.26ms | 9578 | 4890 | 13808.2 | 5424.21 | 0.0448629 | 3.02451 | 15.4449 | 2.05199 | 0.00308811 | 3.81754e-05 | 1.5821e-05 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4323.16 | 0.348287 | 941.133ms | 9578 | 40 | 2166.11 | 2112.88 | 0.0563685 | 1.21502 | 5.37764 | 1.07622 | 0.00253445 | 6.26436e-05 | 3.13218e-05 | 1(Win) | true |
| simdjson (reflection) | 4194.54 | 0.0928007 | 942.76ms | 9578 | 1280 | 5227.5 | 2177.66 | 0.0346319 | 1.25325 | 6.23815 | 1.16235 | 0.000562569 | 3.24637e-05 | 7.58574e-06 | 2(Loss) | true |
| Glaze | 2202.42 | 0.11425 | 1143.48ms | 9578 | 640 | 14369.5 | 4147.39 | 0.0050481 | 2.36104 | 12.677 | 2.62539 | 0.000875052 | 2.83854e-05 | 8.80925e-06 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11023.8 | 0.126241 | 833.795ms | 9578 | 2560 | 2801.07 | 828.596 | 0.0442006 | 0.481174 | 2.23585 | 0.274588 | 0.000820321 | 1.54162e-05 | 4.40463e-06 | 1(Win) | true |
| simdjson (reflection) | 9526.21 | 0.111925 | 854.034ms | 9578 | 2560 | 2948.52 | 958.859 | 0.214254 | 0.55383 | 3.07329 | 0.321257 | 0.000105711 | 3.03838e-05 | 1.50899e-05 | 2(Loss) | true |
| Glaze | 5810.94 | 0.0803756 | 909.114ms | 9578 | 80 | 127.701 | 1571.91 | 0.121519 | 0.892786 | 4.44801 | 0.720192 | 0.000254489 | 1.30507e-05 | 0 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3499.97 | 0.0845619 | 829.594ms | 3873 | 2560 | 2038.72 | 1055.32 | 0.0136936 | 1.5063 | 6.92332 | 0.830365 | 0.000266771 | 8.94615e-05 | 4.37726e-05 | 1(Win) | true |
| Glaze | 1906.5 | 0.0783578 | 920.146ms | 3873 | 30 | 69.1368 | 1937.37 | 0.0740384 | 2.70913 | 12.8533 | 1.7906 | 0.000516396 | 5.16396e-05 | 2.58198e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1611.49 | 0.13221 | 957.523ms | 3873 | 30 | 275.482 | 2292.03 | 0.0611185 | 3.19462 | 14.5771 | 1.55797 | 0.00129099 | 3.44264e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 722.346 | 0.0277986 | 1248.85ms | 3873 | 4890 | 9880.04 | 5113.31 | 0.00760074 | 7.04077 | 32.0147 | 3.66357 | 0.00477402 | 7.89906e-05 | 2.99383e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3818.31 | 0.0714935 | 820.317ms | 3873 | 320 | 153.051 | 967.334 | 0.137753 | 1.38097 | 6.4898 | 0.731474 | 0.000274335 | 4.9219e-05 | 2.82404e-05 | 1(Win) | true |
| Glaze | 2016.23 | 0.0898109 | 905.173ms | 3873 | 40 | 108.276 | 1831.92 | 0.127077 | 2.56474 | 12.4219 | 1.69171 | 0.000277563 | 3.22747e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1725.78 | 0.0412673 | 943.164ms | 3873 | 4890 | 3814.56 | 2140.24 | 0.0235551 | 2.98344 | 14.1327 | 1.45908 | 0.000323143 | 0.000126617 | 4.95803e-05 | 3(Loss) | true |
| simdjson (ondemand) | 733.05 | 0.0221221 | 1233.91ms | 3873 | 4890 | 6075.6 | 5038.65 | 0.0445248 | 6.94857 | 31.5598 | 3.56468 | 0.00719274 | 7.00144e-05 | 3.07303e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 947.949 | 0.0407856 | 1125.67ms | 3873 | 4890 | 12349.5 | 3896.39 | 0.0191312 | 5.36643 | 24.5474 | 5.13581 | 0.00677893 | 0.000106289 | 4.11321e-05 | 1(Win) | true |
| simdjson (reflection) | 896.152 | 0.192041 | 1146.68ms | 3873 | 40 | 2505.99 | 4121.6 | 0.0161776 | 5.69886 | 27.488 | 5.36251 | 0.010528 | 0.000154919 | 0.000109734 | 2(Loss) | true |
| Glaze | 860.904 | 0.0408089 | 1170.27ms | 3873 | 2560 | 7847.59 | 4290.35 | 0.155888 | 5.88682 | 28.8727 | 5.8629 | 0.00661874 | 0.000155524 | 8.09894e-05 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6352.97 | 0.0609187 | 814.86ms | 3873 | 4890 | 613.41 | 581.394 | 0.0780214 | 0.852004 | 3.98502 | 0.476375 | 0.000259095 | 3.36872e-05 | 6.81135e-06 | 1(Win) | true |
| simdjson (reflection) | 4126.57 | 0.0188789 | 828.632ms | 3873 | 640 | 18.2747 | 895.073 | 0.0221651 | 1.28175 | 6.77795 | 0.530338 | 0.000263846 | 2.54163e-05 | 2.4206e-06 | 2(Loss) | true |
| Glaze | 2682.24 | 0.264083 | 896.921ms | 3873 | 320 | 4231.83 | 1377.05 | 0.185288 | 1.93963 | 7.8394 | 0.993029 | 0.00406823 | 0.000117803 | 8.31074e-05 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1654.99 | 0.0149269 | 6216.14ms | 94653 | 4890 | 324135 | 54542.9 | 0.0272458 | 3.04441 | 13.8341 | 2.46038 | 0.0086667 | 3.31768e-05 | 2.54832e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1434.87 | 0.0701923 | 7045.44ms | 94653 | 1280 | 2.49594e+06 | 62910.4 | 0.0874676 | 3.49041 | 15.6443 | 2.74241 | 0.0094189 | 2.82776e-05 | 2.07006e-05 | 2(Loss) | true |
| Glaze | 1406.21 | 0.04341 | 7189.29ms | 94653 | 2560 | 1.98788e+06 | 64192.6 | 0.0171169 | 3.59149 | 15.5412 | 3.09743 | 0.0150719 | 2.79021e-05 | 1.85752e-05 | 3(Loss) | true |
| simdjson (reflection) | 1398.7 | 0.0881176 | 7199.88ms | 94653 | 80 | 258723 | 64537.2 | 0.18372 | 3.6058 | 14.1503 | 2.60995 | 0.00836305 | 1.76962e-05 | 1.05649e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1355.14 | 0.146285 | 7397.54ms | 94653 | 40 | 379807 | 66611.7 | 0.132635 | 3.71907 | 14.5333 | 2.90227 | 0.0113818 | 1.34703e-05 | 8.45192e-06 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2541.9 | 0.0475992 | 5549.37ms | 94653 | 640 | 182865 | 35512 | 0.0255789 | 1.9755 | 9.86479 | 1.56058 | 0.00583241 | 9.60746e-06 | 4.72119e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2067.99 | 0.0352983 | 6381.84ms | 94653 | 2560 | 607746 | 43650.3 | 0.105127 | 2.42663 | 11.7149 | 1.85192 | 0.00654394 | 1.02389e-05 | 5.80657e-06 | 2(Loss) | true |
| Glaze | 2030.53 | 0.0465418 | 6421.13ms | 94653 | 4890 | 2.09337e+06 | 44455.4 | 0.354342 | 2.47504 | 11.754 | 2.2347 | 0.0090867 | 2.08036e-05 | 1.29674e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1919.17 | 0.0603737 | 6733.42ms | 94653 | 160 | 129020 | 47034.9 | 0.00688366 | 2.6353 | 10.6728 | 2.02224 | 0.00719714 | 7.72559e-06 | 4.22596e-06 | 4(Loss) | true |
| simdjson (reflection) | 1807.95 | 0.0693986 | 6978.36ms | 94653 | 640 | 768386 | 49928.6 | 0.0577148 | 2.78986 | 11.1051 | 1.90139 | 0.0043762 | 1.70854e-05 | 1.04163e-05 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20045.8 | 0.0629484 | 1201.48ms | 94653 | 320 | 2571.25 | 4503.1 | 0.0685414 | 0.254477 | 1.20076 | 0.18066 | 6.01209e-05 | 2.21203e-06 | 4.29199e-07 | 1(Win) | true |
| simdjson (reflection) | 13443.6 | 0.0281901 | 1413.7ms | 94653 | 2560 | 9172.08 | 6714.56 | 0.124231 | 0.37801 | 2.045 | 0.302885 | 3.33248e-05 | 5.64149e-06 | 2.85583e-06 | 2(Loss) | true |
| Glaze | 7757.31 | 0.068111 | 1918.8ms | 94653 | 2560 | 160813 | 11636.5 | 0.0036186 | 0.645363 | 3.47139 | 0.569279 | 4.72697e-05 | 7.14369e-06 | 3.94533e-06 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20109.3 | 0.107944 | 1188.37ms | 94653 | 320 | 7513.15 | 4488.87 | 0.0777526 | 0.251308 | 1.19516 | 0.179403 | 4.99192e-05 | 1.02348e-06 | 2.31107e-07 | 1(Win) | true |
| simdjson (reflection) | 13585.7 | 0.0825525 | 1407.75ms | 94653 | 320 | 9627.53 | 6644.35 | 0.0188094 | 0.374673 | 2.03945 | 0.301639 | 4.18304e-05 | 2.47615e-06 | 7.59353e-07 | 2(Loss) | true |
| Glaze | 9343.56 | 0.277126 | 1713.71ms | 94653 | 40 | 28672.1 | 9661 | 0.0562715 | 0.54219 | 3.41879 | 0.557426 | 2.72046e-05 | 3.011e-05 | 2.77329e-05 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1835.28 | 0.0303073 | 7210.96ms | 124597 | 4890 | 1.88284e+06 | 64744.7 | 0.149951 | 2.76777 | 12.2897 | 2.09035 | 0.00801094 | 7.21278e-05 | 6.35456e-05 | 1(Win) | true |
| simdjson (reflection) | 1822.48 | 0.0416553 | 7288.55ms | 124597 | 1280 | 944145 | 65199.5 | 0.084496 | 2.78243 | 11.06 | 1.99381 | 0.00613539 | 2.81031e-05 | 2.24223e-05 | 2(Loss) | true |
| Jsonifier | 1785.38 | 0.0328619 | 7396.78ms | 124597 | 1280 | 612283 | 66554.6 | 0.0593157 | 2.84048 | 12.3539 | 2.33568 | 0.00923137 | 2.81846e-05 | 2.41968e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1762.4 | 0.0745825 | 7496.16ms | 124597 | 320 | 809156 | 67422.4 | 0.0282745 | 2.88597 | 11.343 | 2.21421 | 0.0078089 | 9.20468e-05 | 8.24659e-05 | 4(Loss) | true |
| Glaze | 1660.22 | 0.0390301 | 7936.83ms | 124597 | 1280 | 998838 | 71571.9 | 0.0350579 | 3.0741 | 13.7786 | 2.74168 | 0.0129661 | 1.73434e-05 | 1.35374e-05 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2601.6 | 0.0261684 | 6616.18ms | 124597 | 2560 | 365702 | 45673.7 | 0.0730696 | 1.93027 | 9.32803 | 1.41992 | 0.00523687 | 1.14745e-05 | 8.11993e-06 | 1(Win) | true |
| simdjson (ondemand) | 2435.55 | 0.0808743 | 6861.47ms | 124597 | 640 | 996370 | 48787.7 | 0.0206197 | 2.05728 | 8.45642 | 1.55536 | 0.00546107 | 9.07927e-06 | 5.68081e-06 | 2(Loss) | true |
| Jsonifier | 2384.97 | 0.079646 | 6976.97ms | 124597 | 160 | 251940 | 49822.4 | 0.0410375 | 2.11882 | 9.41571 | 1.67292 | 0.00798575 | 2.6686e-05 | 1.94126e-05 | 3(Loss) | true |
| simdjson (reflection) | 2309.85 | 0.185734 | 7175.94ms | 124597 | 80 | 730334 | 51442.8 | 0.0287295 | 2.17486 | 8.77216 | 1.46003 | 0.00334599 | 8.72814e-06 | 3.71197e-06 | 4(Loss) | true |
| Glaze | 2135.68 | 0.0865016 | 7617ms | 124597 | 320 | 741213 | 55638.1 | 0.0218985 | 2.3556 | 10.9291 | 2.09469 | 0.0104897 | 5.41747e-06 | 2.15695e-06 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23688.2 | 0.127051 | 1285.13ms | 136037 | 30 | 1452.53 | 5476.77 | 0.138351 | 0.219161 | 0.86847 | 0.125694 | 7.17942e-05 | 4.90063e-06 | 3.43044e-06 | 1(Win) | true |
| Glaze | 7289.94 | 0.0540341 | 2528.64ms | 136076 | 2560 | 236859 | 17801.5 | 0.178139 | 0.698165 | 3.79973 | 0.638342 | 0.000113413 | 1.80764e-05 | 1.58919e-05 | 2(Loss) | true |
| simdjson (reflection) | 636.887 | 0.133047 | 5367.72ms | 136037 | 640 | 4.70089e+07 | 203702 | 0.0571742 | 7.90545 | 34.719 | 7.11326 | 0.0266514 | 0.0108771 | 0.000275798 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23208 | 0.0587913 | 1302.69ms | 136037 | 2560 | 27650.7 | 5590.1 | 0.0185071 | 0.21775 | 0.864574 | 0.124826 | 3.36851e-05 | 2.21964e-06 | 9.07382e-07 | 1(Win) | true |
| Glaze | 8197.84 | 0.0290912 | 2325.12ms | 136076 | 2560 | 54290.8 | 15830 | 0.0575187 | 0.616223 | 3.76371 | 0.630104 | 4.01373e-05 | 5.87907e-06 | 3.35865e-06 | 2(Loss) | true |
| simdjson (reflection) | 627.418 | 0.356711 | 5504.5ms | 136037 | 320 | 1.74094e+08 | 206776 | 0.0459616 | 7.98366 | 34.7199 | 7.11323 | 0.0272444 | 0.0265638 | 0.000178789 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1170.25 | 0.139799 | 5733.39ms | 2251027 | 30 | 1.97301e+08 | 1.83443e+06 | 0.148843 | 4.31498 | 23.9637 | 4.83815 | 0.00729843 | 0.0646184 | 6.95831e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1012.63 | 0.151536 | 6685.08ms | 2251027 | 30 | 3.09609e+08 | 2.11998e+06 | 0.218155 | 4.95816 | 26.4052 | 5.07665 | 0.0105539 | 0.102681 | 0.000366262 | 2(Loss) | true |
| Glaze | 879.903 | 0.108901 | 7602.82ms | 2251027 | 80 | 5.64733e+08 | 2.43976e+06 | 0.0196621 | 5.68219 | 30.3119 | 5.64348 | 0.00993485 | 0.0632559 | 0.00115396 | 3(Loss) | true |
| simdjson (reflection) | 815.49 | 0.0953281 | 8206.03ms | 2251027 | 160 | 1.0076e+09 | 2.63246e+06 | 0.173212 | 6.12074 | 29.7225 | 5.43739 | 0.0105148 | 0.103625 | 0.00192488 | 4(Loss) | true |
| simdjson (ondemand) | 748.58 | 0.563003 | 8847.96ms | 2251027 | 160 | 4.17086e+10 | 2.86776e+06 | 1.0767 | 6.70722 | 30.7419 | 5.87589 | 0.0143891 | 0.10911 | 0.0012843 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1460.13 | 0.161234 | 5759.78ms | 2251027 | 30 | 1.68583e+08 | 1.47024e+06 | 0.169507 | 3.45632 | 19.0389 | 3.66309 | 0.00689996 | 0.0416081 | 0.000136219 | 1(Win) | true |
| Jsonifier (two-stage) | 1191.39 | 0.328924 | 6817.5ms | 2251027 | 160 | 5.62035e+09 | 1.80188e+06 | 0.00140962 | 4.1649 | 21.544 | 3.91993 | 0.00986941 | 0.0786829 | 0.000251863 | 2(Loss) | true |
| Glaze | 1042.38 | 0.153681 | 7581.05ms | 2251027 | 40 | 4.00689e+08 | 2.05946e+06 | 0.0993467 | 4.79971 | 25.3559 | 4.46529 | 0.00884341 | 0.0392385 | 0.00152227 | 3(Loss) | true |
| simdjson (reflection) | 962.445 | 0.2136 | 8133.55ms | 2251027 | 40 | 9.07967e+08 | 2.23051e+06 | 0.0544283 | 5.19826 | 24.8459 | 4.27487 | 0.00912756 | 0.0773351 | 0.00121191 | 4(Loss) | true |
| simdjson (ondemand) | 902.673 | 0.301486 | 8640.7ms | 2251027 | 160 | 8.22537e+09 | 2.37821e+06 | 0.781616 | 5.54661 | 25.8226 | 4.70772 | 0.0110298 | 0.0759939 | 0.000523769 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2031.7 | 1.09163 | 6162.92ms | 2090234 | 160 | 1.83545e+10 | 981151 | 0.438371 | 2.48337 | 7.66658 | 0.373395 | 0.00031463 | 0.0512681 | 6.18113e-05 | 1(Win) | true |
| Glaze | 1428.27 | 0.237303 | 8875.01ms | 2090234 | 160 | 1.75508e+09 | 1.39568e+06 | 0.0305321 | 3.48081 | 9.59413 | 0.598214 | 0.0115659 | 0.0699955 | 0.00088372 | 2(Loss) | true |
| simdjson (reflection) | 1019.59 | 0.670475 | 6053.54ms | 2090326 | 80 | 1.37477e+10 | 1.95518e+06 | 0.903383 | 5.00034 | 15.154 | 1.43489 | 0.0163984 | 0.0510921 | 0.00396639 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2063.81 | 0.518394 | 6177.13ms | 2090234 | 320 | 8.0227e+09 | 965884 | 0.0356812 | 2.45129 | 7.66632 | 0.373336 | 0.000315162 | 0.0511459 | 0.00020832 | 1(Win) | true |
| Glaze | 1518.34 | 0.258169 | 8407.85ms | 2090234 | 160 | 1.83815e+09 | 1.31288e+06 | 0.510799 | 3.32414 | 9.5901 | 0.597292 | 0.0115698 | 0.0438979 | 0.000203258 | 2(Loss) | true |
| simdjson (reflection) | 1037 | 0.54553 | 6033.19ms | 2090326 | 40 | 4.39912e+09 | 1.92236e+06 | 0.223272 | 4.90546 | 15.1539 | 1.43485 | 0.0163124 | 0.0508669 | 0.000227536 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2285.94 | 0.783071 | 6992.01ms | 5373214 | 30 | 9.24402e+09 | 2.24165e+06 | 0.0747341 | 2.20817 | 12.0777 | 2.54016 | 0.00342967 | 0.0383608 | 0.000114481 | 1(Win) | true |
| Jsonifier (two-stage) | 2187.95 | 0.681428 | 7224.98ms | 5373214 | 160 | 4.07525e+10 | 2.34206e+06 | 1.61286 | 2.29334 | 11.8653 | 2.16767 | 0.00493088 | 0.0627858 | 0.000164229 | 2(Loss) | true |
| simdjson (reflection) | 1798.5 | 0.543682 | 8841.36ms | 5373214 | 160 | 3.83935e+10 | 2.8492e+06 | 0.290379 | 2.79355 | 13.2173 | 2.31135 | 0.00466951 | 0.0627291 | 0.000155733 | 3(Loss) | true |
| simdjson (ondemand) | 1717.41 | 0.226174 | 9339.75ms | 5373214 | 160 | 7.28662e+09 | 2.98374e+06 | 0.057797 | 2.93639 | 13.6421 | 2.49435 | 0.00636792 | 0.064898 | 0.000274163 | 4(Loss) | true |
| Glaze | 1599.12 | 0.317899 | 10011.5ms | 5373214 | 160 | 1.66037e+10 | 3.20444e+06 | 0.386713 | 3.15678 | 15.9031 | 2.91921 | 0.00471263 | 0.0406742 | 0.00164064 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2791.9 | 0.343537 | 6920.73ms | 5373214 | 160 | 6.36115e+09 | 1.83541e+06 | 0.176088 | 1.80791 | 10.0444 | 2.05643 | 0.00314501 | 0.0280967 | 0.000544883 | 1(Win) | true |
| Jsonifier (two-stage) | 2672.22 | 0.606581 | 7269.17ms | 5373214 | 30 | 4.05904e+09 | 1.91762e+06 | 1.10836 | 1.87324 | 9.8315 | 1.68393 | 0.00466384 | 0.0524867 | 0.000120164 | 2(Loss) | true |
| simdjson (reflection) | 2113.26 | 0.625609 | 8728.81ms | 5373214 | 40 | 9.20514e+09 | 2.42483e+06 | 0.856099 | 2.37238 | 11.1739 | 1.82411 | 0.00403143 | 0.0514256 | 0.000145081 | 3(Loss) | true |
| simdjson (ondemand) | 2023.4 | 0.633054 | 9128.81ms | 5373214 | 40 | 1.02813e+10 | 2.53252e+06 | 0.136957 | 2.493 | 11.5823 | 2.00523 | 0.00495751 | 0.0512532 | 0.000182377 | 4(Loss) | true |
| Glaze | 1793.81 | 0.913845 | 9942.58ms | 5373214 | 80 | 5.45194e+10 | 2.85666e+06 | 1.2013 | 2.81431 | 13.8602 | 2.43499 | 0.0042179 | 0.0298044 | 0.000222355 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6057.22 | 0.0815092 | 6675.6ms | 6661897 | 80 | 5.84726e+07 | 1.04888e+06 | 0.141701 | 0.832427 | 2.48092 | 0.117149 | 9.82059e-05 | 0.0279692 | 0.000148179 | 1(Win) | true |
| Glaze | 3235.67 | 0.241111 | 6168.06ms | 6661897 | 40 | 8.96525e+08 | 1.96351e+06 | 1.30845 | 1.55594 | 4.3345 | 0.464357 | 0.00371115 | 0.0633642 | 0.00741069 | 2(Loss) | true |
| simdjson (reflection) | 265.199 | 0.439159 | 7146.48ms | 6661989 | 30 | 3.32069e+11 | 2.3957e+07 | 1.25482 | 13.7014 | 41.3171 | 5.67132 | 0.0253993 | 0.181532 | 0.0689669 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6063.29 | 0.0387139 | 6717.59ms | 6661897 | 320 | 5.26579e+07 | 1.04783e+06 | 0.00452236 | 0.832193 | 2.48087 | 0.117138 | 0.000104322 | 0.027952 | 7.58694e-05 | 1(Win) | true |
| Glaze | 3924.52 | 0.0670146 | 5060.42ms | 6661897 | 80 | 9.41571e+07 | 1.61887e+06 | 0.0638811 | 1.28491 | 4.33307 | 0.464028 | 0.00370311 | 0.0248572 | 0.000301928 | 2(Loss) | true |
| simdjson (reflection) | 387.939 | 0.319593 | 11565ms | 6661989 | 40 | 1.09581e+11 | 1.63772e+07 | 0.444055 | 12.9617 | 41.3255 | 5.67482 | 0.0241921 | 0.256284 | 0.105937 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2369.73 | 0.0959526 | 5468.96ms | 500299 | 30 | 1.11969e+06 | 201341 | 0.214449 | 2.13156 | 9.6841 | 1.72307 | 0.0102385 | 0.00685717 | 8.1951e-05 | 1(Win) | true |
| Glaze | 1817.44 | 0.169185 | 6971.17ms | 500299 | 30 | 5.91814e+06 | 262524 | 0.0362756 | 2.77922 | 11.6164 | 2.26096 | 0.0139762 | 0.00536939 | 8.83472e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1791.48 | 0.482113 | 7059.09ms | 500299 | 640 | 1.05515e+09 | 266329 | 0.308448 | 2.82026 | 12.4106 | 2.10465 | 0.0141155 | 0.0435427 | 0.0001939 | 3(Loss) | true |
| simdjson (ondemand) | 1430.32 | 0.383676 | 8753.81ms | 500299 | 1280 | 2.09668e+09 | 333578 | 0.00360988 | 3.53254 | 14.2457 | 2.43024 | 0.016296 | 0.0369765 | 0.000218957 | 4(Loss) | true |
| simdjson (reflection) | 1404.44 | 0.803431 | 8959.41ms | 500299 | 80 | 5.95991e+08 | 339724 | 0.184229 | 3.59715 | 14.2443 | 2.44673 | 0.017745 | 0.024718 | 8.23508e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2929.05 | 0.109376 | 5271.13ms | 500299 | 30 | 952295 | 162893 | 0.171223 | 1.72438 | 8.56693 | 1.45078 | 0.00720856 | 0.00409468 | 1.95217e-05 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2152.19 | 0.159364 | 6830.06ms | 500299 | 30 | 3.74457e+06 | 221692 | 0.052262 | 2.34732 | 10.5102 | 1.99256 | 0.00935527 | 0.00280033 | 1.91885e-05 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2149.92 | 0.355222 | 6819.43ms | 500299 | 640 | 3.97734e+08 | 221925 | 0.0400718 | 2.3351 | 11.29 | 1.83227 | 0.00991487 | 0.0311602 | 3.05442e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1734.02 | 0.399821 | 8034.68ms | 500299 | 1280 | 1.54914e+09 | 275154 | 0.985899 | 2.91349 | 13.1091 | 2.15034 | 0.00883992 | 0.0139295 | 2.73571e-05 | 4(Loss) | true |
| simdjson (reflection) | 1682.55 | 0.0855348 | 8398.08ms | 500299 | 80 | 4.70652e+06 | 283571 | 0.0758409 | 3.00228 | 13.1292 | 2.17396 | 0.0104877 | 0.0137749 | 2.72337e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12450.1 | 0.114175 | 4644.37ms | 500299 | 320 | 612645 | 38322.8 | 0.130927 | 0.406043 | 1.81572 | 0.301818 | 0.00154085 | 0.00256639 | 1.04875e-05 | 1(Win) | true |
| simdjson (reflection) | 11129.1 | 0.0173791 | 5056.46ms | 500299 | 4890 | 271455 | 42871.4 | 0.159013 | 0.45419 | 2.18113 | 0.197082 | 0.00109876 | 0.00170862 | 1.03276e-05 | 2(Loss) | true |
| Glaze | 5935.15 | 0.160523 | 8874.21ms | 500299 | 2560 | 4.26297e+07 | 80389.3 | 0.40959 | 0.843521 | 3.76516 | 0.550621 | 0.00162713 | 0.0219276 | 3.09549e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12499.8 | 0.14749 | 4571.92ms | 500299 | 80 | 253552 | 38170.4 | 0.0110373 | 0.404368 | 1.81463 | 0.301572 | 0.0015092 | 0.00217133 | 1.32671e-05 | 1(Win) | true |
| simdjson (reflection) | 11365.5 | 0.0380969 | 4956.34ms | 500299 | 1280 | 327395 | 41979.9 | 0.0509953 | 0.444755 | 2.18004 | 0.196834 | 0.00110444 | 0.000996167 | 9.42874e-06 | 2(Loss) | true |
| Glaze | 7167.9 | 0.0335374 | 7421.76ms | 500299 | 1280 | 637890 | 66563.8 | 0.0415699 | 0.705271 | 3.75128 | 0.547385 | 0.0015815 | 0.000883528 | 2.03238e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3573.5 | 0.132745 | 8110.16ms | 1151920 | 320 | 5.329e+07 | 307417 | 0.0969349 | 1.4041 | 6.18085 | 0.947784 | 0.00589799 | 0.056016 | 0.000103791 | 1(Win) | true |
| Jsonifier | 3420.22 | 0.0808681 | 8610.73ms | 1151920 | 30 | 2.02401e+06 | 321194 | 0.205917 | 1.47663 | 6.67157 | 1.38546 | 0.00461872 | 0.0181101 | 0.000117659 | 2(Loss) | true |
| simdjson (ondemand) | 3024.3 | 0.0479973 | 9651.95ms | 1151920 | 320 | 9.727e+06 | 363244 | 0.25512 | 1.67039 | 6.95889 | 1.0905 | 0.00714583 | 0.0508411 | 0.000223203 | 3(Loss) | true |
| simdjson (reflection) | 2951.32 | 0.0423764 | 9855.29ms | 1151920 | 320 | 7.96177e+06 | 372225 | 0.0322237 | 1.71073 | 6.95213 | 1.09603 | 0.00754989 | 0.0435454 | 8.1101e-05 | 4(Loss) | true |
| Glaze | 2595.62 | 0.547432 | 5515.73ms | 1151920 | 160 | 8.58903e+08 | 423235 | 0.0902809 | 1.94598 | 8.47791 | 1.61298 | 0.00756687 | 0.0136403 | 6.00356e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4144.47 | 0.262915 | 7986.9ms | 1151920 | 160 | 7.77064e+07 | 265066 | 0.0223857 | 1.21105 | 5.69544 | 0.829868 | 0.00441638 | 0.0472447 | 2.90819e-05 | 1(Win) | true |
| Jsonifier | 3843.56 | 0.324249 | 8342.84ms | 1151920 | 640 | 5.49684e+08 | 285817 | 0.926966 | 1.31425 | 6.18604 | 1.26727 | 0.00338246 | 0.0122483 | 2.17205e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3476.97 | 0.577346 | 9158.66ms | 1151920 | 1280 | 4.25917e+09 | 315952 | 0.959127 | 1.45223 | 6.45956 | 0.967552 | 0.00405687 | 0.0363991 | 1.56647e-05 | 3(Loss) | true |
| simdjson (reflection) | 3413.01 | 0.165365 | 9256.79ms | 1151920 | 1280 | 3.62633e+08 | 321874 | 0.0663535 | 1.48038 | 6.469 | 0.978381 | 0.0048165 | 0.03339 | 2.30146e-05 | 4(Loss) | true |
| Glaze | 2902.07 | 0.284492 | 5409.27ms | 1151920 | 640 | 7.42246e+08 | 378542 | 0.229566 | 1.73857 | 7.99631 | 1.49618 | 0.00551454 | 0.00892446 | 2.51116e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20053.6 | 0.0864786 | 7972.53ms | 1439562 | 80 | 280405 | 68460.4 | 0.0990285 | 0.251919 | 0.703086 | 0.104897 | 0.000444858 | 0.0188311 | 5.77433e-06 | 1(Win) | true |
| Glaze | 5749.81 | 0.118721 | 6326.35ms | 1439584 | 640 | 5.14281e+07 | 238772 | 0.00861496 | 0.875412 | 3.1224 | 0.499162 | 0.000870322 | 0.0615474 | 1.30886e-05 | 2(Loss) | true |
| simdjson (reflection) | 556.406 | 1.1891 | 7776.9ms | 1439562 | 80 | 6.88665e+10 | 2.4674e+06 | 0.0276395 | 9.03032 | 35.7848 | 6.43753 | 0.0159097 | 0.309561 | 0.00132322 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20117.6 | 0.0907382 | 8036.67ms | 1439562 | 40 | 153373 | 68242.3 | 0.104079 | 0.2512 | 0.702708 | 0.104812 | 0.000437216 | 0.0186873 | 4.1332e-06 | 1(Win) | true |
| Glaze | 7933.48 | 0.226126 | 9402.2ms | 1439584 | 320 | 4.90003e+07 | 173051 | 0.563618 | 0.636806 | 3.11679 | 0.497885 | 0.000869335 | 0.0175168 | 1.54906e-05 | 2(Loss) | true |
| simdjson (reflection) | 553.255 | 0.839221 | 7800.26ms | 1439562 | 160 | 6.93879e+10 | 2.48145e+06 | 1.15002 | 9.0745 | 35.7826 | 6.43685 | 0.0158844 | 0.309344 | 0.0067948 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2292.11 | 0.0397905 | 3081.74ms | 56369 | 640 | 55737.5 | 23453.3 | 0.050218 | 2.20746 | 9.42132 | 1.80171 | 0.00265541 | 2.19813e-05 | 1.35824e-05 | 1(Win) | true |
| Glaze | 1956.62 | 0.155331 | 3515.52ms | 56369 | 640 | 1.16564e+06 | 27474.8 | 0.426978 | 2.6013 | 11.2196 | 2.27575 | 0.00582848 | 9.00872e-05 | 6.79673e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1847.45 | 0.0586013 | 3658.68ms | 56369 | 320 | 93046.2 | 29098.2 | 0.132628 | 2.73841 | 12.2726 | 2.12839 | 0.00444853 | 1.02006e-05 | 4.93401e-06 | 3(Loss) | true |
| simdjson (reflection) | 1573.57 | 0.0557427 | 4195.99ms | 56369 | 640 | 232095 | 34162.9 | 0.0341445 | 3.21041 | 13.7996 | 2.40327 | 0.00446428 | 6.07881e-05 | 3.10454e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1339.85 | 0.0215338 | 4749.69ms | 56369 | 4890 | 365019 | 40122.1 | 0.00970326 | 3.77103 | 15.0255 | 2.78814 | 0.00854286 | 5.2078e-05 | 3.32022e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3203.66 | 0.0185246 | 2758.76ms | 56369 | 4890 | 47249.3 | 16780.1 | 0.0893247 | 1.58088 | 7.42678 | 1.34424 | 0.00184735 | 1.74246e-05 | 9.07328e-06 | 1(Win) | true |
| Glaze | 2813.03 | 0.102241 | 3013.22ms | 56369 | 2560 | 977277 | 19110.2 | 0.0159718 | 1.80001 | 8.95624 | 1.756 | 0.00210162 | 2.90011e-05 | 1.54881e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2452.76 | 0.0164057 | 3285.58ms | 56369 | 4890 | 63222.3 | 21917.2 | 0.0168688 | 2.0643 | 10.2707 | 1.66993 | 0.00216581 | 1.79978e-05 | 9.31998e-06 | 3(Loss) | true |
| simdjson (reflection) | 1814.11 | 0.0338221 | 4087.21ms | 56369 | 2560 | 257153 | 29633 | 0.012615 | 2.78755 | 12.2458 | 2.05253 | 0.00369679 | 3.494e-05 | 2.20922e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1632.76 | 0.0963915 | 4462.47ms | 56369 | 4890 | 4.92515e+06 | 32924.3 | 0.0312761 | 3.10862 | 12.8392 | 2.29495 | 0.00851334 | 7.94611e-05 | 5.24226e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14889.3 | 0.0466336 | 1105.36ms | 56369 | 2560 | 7257.2 | 3610.49 | 0.0168318 | 0.343348 | 1.41947 | 0.224485 | 0.000177506 | 2.92991e-05 | 1.87104e-05 | 1(Win) | true |
| simdjson (reflection) | 13028.3 | 0.106037 | 1155.75ms | 56369 | 80 | 1531.47 | 4126.24 | 0.123145 | 0.392038 | 1.69984 | 0.277546 | 0.000161658 | 1.90708e-05 | 1.50792e-05 | 2(Loss) | true |
| Glaze | 6276.78 | 0.0864505 | 1596.01ms | 56369 | 1280 | 70170 | 8564.53 | 0.055631 | 0.808625 | 3.0545 | 0.466338 | 8.29495e-05 | 1.70057e-05 | 8.66223e-06 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15183.4 | 0.0403401 | 1095.04ms | 56369 | 2560 | 5222.2 | 3540.54 | 0.00343135 | 0.336881 | 1.40929 | 0.222197 | 0.000182662 | 9.55617e-06 | 4.38655e-06 | 1(Win) | true |
| simdjson (reflection) | 13345 | 0.0638876 | 1148.18ms | 56369 | 40 | 264.933 | 4028.3 | 0.011586 | 0.38298 | 1.68962 | 0.275222 | 0.000173854 | 1.19747e-05 | 5.76558e-06 | 2(Loss) | true |
| Glaze | 7181.64 | 0.0757971 | 1491.95ms | 56369 | 1280 | 41204.9 | 7485.43 | 0.0711501 | 0.707217 | 2.97538 | 0.448722 | 4.81759e-05 | 2.83705e-05 | 1.67839e-05 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2577.23 | 0.037412 | 3871.48ms | 83958 | 4890 | 660616 | 31067.7 | 0.0253656 | 1.95553 | 8.76062 | 1.44207 | 0.00256496 | 2.19873e-05 | 1.16598e-05 | 1(Win) | true |
| Glaze | 2420.16 | 0.0878152 | 4062.55ms | 83958 | 320 | 270100 | 33084 | 0.0342522 | 2.09026 | 9.97514 | 2.07256 | 0.00422726 | 2.00249e-05 | 9.97523e-06 | 2(Loss) | true |
| simdjson (reflection) | 2255.45 | 0.0200374 | 4301.78ms | 83958 | 4890 | 247427 | 35500 | 0.0597502 | 2.23766 | 9.73046 | 1.63279 | 0.00296765 | 2.15659e-05 | 1.25684e-05 | 3(Loss) | true |
| Jsonifier | 2227.46 | 0.0347251 | 4366.87ms | 83958 | 160 | 24929.4 | 35946.1 | 0.00716401 | 2.27213 | 8.89125 | 1.83539 | 0.00461682 | 2.38214e-05 | 1.54095e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1906.46 | 0.107181 | 4957.96ms | 83958 | 320 | 648410 | 41998.5 | 0.295615 | 2.65473 | 10.5582 | 1.89162 | 0.00600289 | 1.54467e-05 | 6.96033e-06 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3308.05 | 0.0655251 | 3532.48ms | 83958 | 320 | 80490.8 | 24204.2 | 0.233419 | 1.52513 | 7.41656 | 1.1339 | 0.00166274 | 7.81641e-06 | 3.49877e-06 | 1(Win) | true |
| Glaze | 3223.15 | 0.0508081 | 3571.7ms | 83958 | 2560 | 407820 | 24841.7 | 0.0517779 | 1.5662 | 8.47109 | 1.7268 | 0.0021639 | 1.46744e-05 | 7.84898e-06 | 2(Loss) | true |
| Jsonifier | 2768.23 | 0.061255 | 3985.68ms | 83958 | 30 | 9417.24 | 28924.1 | 0.0718608 | 1.82952 | 7.54458 | 1.52686 | 0.00375505 | 7.54345e-06 | 1.19107e-06 | 3(Loss) | true |
| simdjson (reflection) | 2582.21 | 0.0328586 | 4233.85ms | 83958 | 1280 | 132877 | 31007.8 | 0.0811441 | 1.95913 | 8.69532 | 1.39921 | 0.00239295 | 1.23201e-05 | 6.08563e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2320.34 | 0.0504949 | 4580.84ms | 83958 | 1280 | 388620 | 34507.2 | 0.074442 | 2.16744 | 9.09111 | 1.56117 | 0.00568727 | 1.2255e-05 | 5.83439e-06 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20448.3 | 0.0547397 | 1182.12ms | 94370 | 2560 | 14859.4 | 4401.26 | 0.016248 | 0.251112 | 0.900244 | 0.134153 | 0.000112605 | 2.38589e-05 | 1.60811e-05 | 1(Win) | true |
| Glaze | 5947.07 | 0.060543 | 2268.23ms | 94370 | 4890 | 410486 | 15133.2 | 0.266421 | 0.848875 | 3.65836 | 0.618332 | 0.000338629 | 1.11903e-05 | 5.593e-06 | 2(Loss) | true |
| simdjson (reflection) | 558.33 | 0.13188 | 8668.78ms | 94370 | 2560 | 1.15687e+08 | 161192 | 0.337803 | 9.00698 | 38.8295 | 7.53837 | 0.0220025 | 0.0110758 | 0.000190474 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20741.3 | 0.0607745 | 1173.6ms | 94370 | 640 | 4450.61 | 4339.09 | 0.000432116 | 0.246997 | 0.894532 | 0.132871 | 0.000118831 | 8.44416e-06 | 4.58634e-06 | 1(Win) | true |
| Glaze | 7121.87 | 0.0571304 | 2012.49ms | 94370 | 1280 | 66715.3 | 12636.9 | 0.0359989 | 0.711647 | 3.60407 | 0.605966 | 0.000303327 | 7.2272e-06 | 3.61774e-06 | 2(Loss) | true |
| simdjson (reflection) | 560.819 | 0.172497 | 8603.11ms | 94370 | 1280 | 9.80836e+07 | 160477 | 0.166733 | 8.98391 | 38.8305 | 7.53866 | 0.02249 | 0.00883082 | 0.000318974 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1674.46 | 0.132076 | 3813.07ms | 53331 | 320 | 515000 | 30374.2 | 0.0537379 | 3.02008 | 9.88142 | 1.72508 | 0.0102726 | 8.97696e-05 | 6.19949e-05 | 1(Win) | true |
| simdjson (reflection) | 1568.58 | 0.0515381 | 4003.55ms | 53331 | 4890 | 1.36557e+06 | 32424.6 | 0.0010739 | 3.24649 | 10.8557 | 1.89887 | 0.0104248 | 0.00021453 | 0.000152507 | 2(Loss) | true |
| Jsonifier (two-stage) | 1557.99 | 0.0393161 | 4028.24ms | 53331 | 4890 | 805523 | 32644.8 | 0.177115 | 3.24359 | 10.6981 | 1.80514 | 0.0105456 | 0.000136325 | 9.08897e-05 | 3(Loss) | true |
| Glaze | 1475.76 | 0.135616 | 4183.89ms | 53331 | 640 | 1.39807e+06 | 34464 | 0.16485 | 3.42557 | 11.6363 | 2.27576 | 0.0190042 | 0.000162136 | 0.000108315 | 4(Loss) | true |
| simdjson (ondemand) | 1433.02 | 0.0296309 | 4292.42ms | 53331 | 2560 | 283131 | 35491.8 | 0.0594865 | 3.52929 | 11.1025 | 2.05143 | 0.00497948 | 4.64815e-05 | 2.8031e-05 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2253.22 | 0.0496752 | 3571.03ms | 53331 | 2560 | 321863 | 22572.3 | 0.130389 | 2.2444 | 7.66137 | 1.22524 | 0.00743122 | 4.80197e-05 | 3.03163e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2048.13 | 0.0636333 | 3825.34ms | 53331 | 2560 | 639224 | 24832.6 | 0.110667 | 2.46893 | 8.52551 | 1.31658 | 0.00756815 | 5.84278e-05 | 3.62345e-05 | 2(Loss) | true |
| Glaze | 1961.04 | 0.0694963 | 3945.53ms | 53331 | 2560 | 831671 | 25935.5 | 0.0934047 | 2.5802 | 9.40842 | 1.77389 | 0.0155394 | 3.17592e-05 | 1.84285e-05 | 3(Loss) | true |
| simdjson (reflection) | 1875.19 | 0.0376671 | 4031.3ms | 53331 | 4890 | 510389 | 27122.8 | 0.125171 | 2.69079 | 8.97521 | 1.4671 | 0.00897948 | 9.40992e-05 | 6.58081e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1627.88 | 0.0234754 | 4410.04ms | 53331 | 4890 | 263056 | 31243.3 | 0.041879 | 3.10228 | 9.22399 | 1.63447 | 0.00955507 | 7.82435e-05 | 4.88365e-05 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14809.4 | 0.0597783 | 1117.59ms | 58581 | 2560 | 13018.6 | 3772.41 | 0.0138321 | 0.344129 | 1.05758 | 0.167614 | 3.77482e-05 | 2.16981e-05 | 1.26161e-05 | 1(Win) | true |
| simdjson (reflection) | 10983.8 | 0.0371777 | 1250.98ms | 58581 | 4890 | 17485.8 | 5086.35 | 0.0153652 | 0.461892 | 1.4967 | 0.212253 | 5.64475e-05 | 2.30747e-05 | 1.33631e-05 | 2(Loss) | true |
| Glaze | 7002.93 | 0.0560184 | 1543.9ms | 58581 | 4890 | 97661.5 | 7977.69 | 0.048834 | 0.722872 | 2.43244 | 0.370342 | 3.37428e-05 | 5.34697e-05 | 3.77748e-05 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15032 | 0.0770536 | 1112.22ms | 58581 | 1280 | 10497.3 | 3716.56 | 0.11481 | 0.339934 | 1.04838 | 0.165549 | 3.42074e-05 | 3.24337e-05 | 2.1258e-05 | 1(Win) | true |
| simdjson (reflection) | 11311.9 | 0.0622788 | 1239.99ms | 58581 | 30 | 283.821 | 4938.8 | 0.0445254 | 0.4508 | 1.4875 | 0.210171 | 5.12111e-05 | 1.36563e-05 | 7.96618e-06 | 2(Loss) | true |
| Glaze | 8582.1 | 0.14436 | 1397.64ms | 58581 | 1280 | 113040 | 6509.73 | 0.0125309 | 0.592245 | 2.36218 | 0.354176 | 3.14602e-05 | 1.39897e-05 | 7.66834e-06 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1890.26 | 0.076472 | 4008.26ms | 65103 | 640 | 403779 | 32845.8 | 0.0210212 | 2.69519 | 9.14603 | 1.56905 | 0.00956993 | 8.18655e-05 | 6.50412e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1877.54 | 0.0277302 | 4040.35ms | 65103 | 4890 | 411186 | 33068.3 | 0.0591732 | 2.72462 | 9.1684 | 1.4953 | 0.00942755 | 3.17383e-05 | 2.12185e-05 | 2(Loss) | true |
| Jsonifier | 1712.56 | 0.0396649 | 4368.79ms | 65103 | 1280 | 264688 | 36254 | 0.125832 | 2.99686 | 9.2139 | 1.68492 | 0.00902756 | 7.22533e-05 | 6.05051e-05 | 3(Loss) | true |
| Glaze | 1683.09 | 0.045509 | 4433.22ms | 65103 | 2560 | 721471 | 36888.6 | 0.109614 | 3.04789 | 10.7766 | 2.11952 | 0.0126895 | 2.92385e-05 | 2.05024e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1617.77 | 0.0938311 | 4611.97ms | 65103 | 160 | 207482 | 38378.1 | 0.0320556 | 3.18513 | 9.4824 | 1.72497 | 0.0107073 | 3.28326e-05 | 2.20804e-05 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2383.53 | 0.0527622 | 3942.08ms | 65103 | 4890 | 923664 | 26048.3 | 0.0441661 | 2.12297 | 7.39511 | 1.0931 | 0.00684274 | 4.78022e-05 | 2.92191e-05 | 1(Win) | true |
| Jsonifier | 2262.48 | 0.0194703 | 3973.71ms | 65103 | 4890 | 139600 | 27442 | 0.108493 | 2.2365 | 7.42154 | 1.27603 | 0.00272898 | 3.11949e-05 | 1.95537e-05 | 2(Loss) | true |
| simdjson (reflection) | 2224.17 | 0.0390633 | 4114.14ms | 65103 | 2560 | 304399 | 27914.7 | 0.0351333 | 2.27115 | 7.6383 | 1.22 | 0.00749577 | 6.10151e-05 | 3.75307e-05 | 3(Loss) | true |
| Glaze | 2007.55 | 0.0572444 | 4451.32ms | 65103 | 2560 | 802370 | 30926.7 | 0.0398995 | 2.51761 | 8.9377 | 1.70282 | 0.0123772 | 5.05389e-05 | 3.19746e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1943.75 | 0.0246406 | 4483.69ms | 65103 | 4890 | 302923 | 31941.9 | 0.031816 | 2.60361 | 7.82981 | 1.35344 | 0.00780063 | 2.89929e-05 | 1.48074e-05 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18610.1 | 0.14703 | 1146.3ms | 78778 | 640 | 22547.8 | 4036.97 | 0.504104 | 0.277334 | 0.830156 | 0.124578 | 2.57448e-05 | 5.83126e-06 | 2.97513e-06 | 1(Win) | true |
| Glaze | 5182.85 | 0.0760991 | 2199.36ms | 78778 | 4890 | 595033 | 14495.6 | 0.494164 | 0.991233 | 2.87931 | 0.451129 | 8.85276e-05 | 2.59277e-05 | 1.94822e-05 | 2(Loss) | true |
| simdjson (reflection) | 625.728 | 0.319998 | 6487.14ms | 78778 | 320 | 4.72372e+07 | 120066 | 0.0341103 | 8.06109 | 29.3527 | 6.61225 | 0.0412764 | 0.000285851 | 0.000160459 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18553.7 | 0.0401622 | 1146.25ms | 78778 | 4890 | 12932.7 | 4049.24 | 0.146252 | 0.274511 | 0.823656 | 0.123105 | 2.55487e-05 | 1.20968e-05 | 6.66624e-06 | 1(Win) | true |
| Glaze | 6225.03 | 0.114758 | 1948.6ms | 78778 | 2560 | 491056 | 12068.8 | 0.00945985 | 0.813237 | 2.80596 | 0.434093 | 4.59956e-05 | 2.31366e-05 | 1.26641e-05 | 2(Loss) | true |
| simdjson (reflection) | 639.228 | 0.169841 | 6370.62ms | 78778 | 1280 | 5.1003e+07 | 117530 | 0.258191 | 7.89539 | 29.3753 | 6.6079 | 0.0327612 | 0.000751429 | 0.000162452 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2494.38 | 0.0712099 | 1181.49ms | 11812 | 1280 | 13237.8 | 4516.08 | 0.0608737 | 2.05387 | 10.1043 | 1.61179 | 0.00251545 | 2.74483e-05 | 8.06912e-06 | 1(Win) | true |
| Glaze | 1915.76 | 0.0641108 | 1319.73ms | 11812 | 1280 | 18190.2 | 5880.08 | 0.0420869 | 2.66604 | 13.1048 | 2.62318 | 0.0015412 | 4.09409e-05 | 1.508e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1807.81 | 0.0661231 | 1365.98ms | 11812 | 1280 | 21729.9 | 6231.19 | 0.0237158 | 2.81275 | 13.5533 | 2.14396 | 0.00647646 | 3.4856e-05 | 1.7924e-05 | 3(Loss) | true |
| simdjson (reflection) | 1501.82 | 0.0494262 | 1488.16ms | 11812 | 160 | 2199.11 | 7500.77 | 0.0658699 | 3.38538 | 13.4896 | 2.16128 | 0.00432293 | 1.64028e-05 | 4.23298e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1114.57 | 0.0463406 | 1756.26ms | 11812 | 2560 | 56156.2 | 10106.9 | 0.0727085 | 4.56556 | 17.7466 | 3.1963 | 0.00840694 | 7.69543e-05 | 4.34873e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2902.3 | 0.0794047 | 1176.24ms | 11812 | 1280 | 12158.1 | 3881.34 | 0.13373 | 1.78286 | 9.20166 | 1.40019 | 0.00134324 | 3.49883e-05 | 8.73053e-06 | 1(Win) | true |
| Glaze | 2184.13 | 0.0371917 | 1301.87ms | 11812 | 4890 | 17992.4 | 5157.56 | 0.023845 | 2.35539 | 12.0412 | 2.3786 | 0.000781552 | 2.89643e-05 | 5.88636e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1985.18 | 0.0317973 | 1360.81ms | 11812 | 4890 | 15919.7 | 5674.44 | 0.0817279 | 2.56429 | 12.65 | 1.9321 | 0.00597886 | 3.12669e-05 | 1.09244e-05 | 3(Loss) | true |
| simdjson (reflection) | 1605.3 | 0.0371376 | 1497.86ms | 11812 | 4890 | 33210.2 | 7017.25 | 0.0949041 | 3.16752 | 12.9909 | 2.03844 | 0.00318549 | 3.06264e-05 | 1.16862e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1181.74 | 0.0588419 | 1749.5ms | 11812 | 1280 | 40270.7 | 9532.42 | 0.0761621 | 4.32177 | 17.0123 | 3.02938 | 0.00760575 | 2.83742e-05 | 1.09132e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15747.8 | 0.146801 | 804.104ms | 11812 | 160 | 176.435 | 715.325 | 0.0559499 | 0.339719 | 1.63021 | 0.257365 | 8.73053e-05 | 1.58737e-05 | 1.05825e-06 | 1(Win) | true |
| simdjson (reflection) | 9955.48 | 0.0743417 | 843.948ms | 11812 | 2560 | 1811.45 | 1131.52 | 0.0353633 | 0.530317 | 2.37246 | 0.355409 | 0.000107643 | 2.99616e-05 | 1.16738e-05 | 2(Loss) | true |
| Glaze | 4580.49 | 0.140199 | 989.647ms | 11812 | 4890 | 58133.1 | 2459.3 | 0.0908623 | 1.12693 | 4.61895 | 0.71512 | 9.44414e-05 | 3.61145e-05 | 1.53392e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16964.6 | 0.193376 | 796.301ms | 11812 | 1280 | 2110.45 | 664.017 | 0.00494176 | 0.318274 | 1.58297 | 0.24636 | 9.28611e-05 | 1.90484e-05 | 7.67228e-06 | 1(Win) | true |
| simdjson (reflection) | 10130.9 | 0.116995 | 840.628ms | 11812 | 80 | 135.387 | 1111.92 | 0.239996 | 0.517821 | 2.34456 | 0.348713 | 0.000111116 | 4.33881e-05 | 1.58737e-05 | 2(Loss) | true |
| Glaze | 5051.16 | 0.333889 | 963.712ms | 11812 | 640 | 35485.3 | 2230.14 | 0.1997 | 1.02592 | 4.35083 | 0.655943 | 9.35225e-05 | 4.11393e-05 | 2.64561e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3368.84 | 0.0625729 | 1465.34ms | 25388 | 160 | 3235.86 | 7187.01 | 0.0369454 | 1.51048 | 7.15669 | 1.05042 | 0.00272397 | 6.67146e-05 | 4.57893e-05 | 1(Win) | true |
| Jsonifier | 3297.5 | 0.0402454 | 1472.31ms | 25388 | 4890 | 42700.2 | 7342.5 | 0.0883024 | 1.53924 | 7.18635 | 1.38278 | 0.00407029 | 2.5655e-05 | 1.28154e-05 | 2(Loss) | true |
| simdjson (reflection) | 2971.34 | 0.0343131 | 1552.75ms | 25388 | 4890 | 38228 | 8148.49 | 0.0549912 | 1.71017 | 6.98204 | 1.03545 | 0.00197134 | 2.13376e-05 | 1.09386e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2264.31 | 0.0909881 | 1824.21ms | 25388 | 1280 | 121161 | 10692.8 | 0.149806 | 2.27356 | 8.98031 | 1.52058 | 0.00393521 | 4.34506e-05 | 2.8126e-05 | 4(Loss) | true |
| Glaze | 2258.92 | 0.0357833 | 1805.11ms | 25388 | 4890 | 71932.3 | 10718.3 | 0.0250527 | 2.23665 | 9.40986 | 1.80814 | 0.00546924 | 3.06491e-05 | 1.51514e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3615 | 0.0360057 | 1466.46ms | 25388 | 2560 | 14887.5 | 6697.61 | 0.0973455 | 1.40646 | 6.77734 | 0.960533 | 0.00270617 | 1.03395e-05 | 2.43102e-06 | 1(Win) | true |
| Jsonifier | 3532.35 | 0.0398332 | 1476.57ms | 25388 | 4890 | 36452.6 | 6854.33 | 0.132457 | 1.43847 | 6.807 | 1.29301 | 0.00403223 | 1.81317e-05 | 8.90072e-06 | 2(Loss) | true |
| simdjson (reflection) | 3167.62 | 0.0271807 | 1555.93ms | 25388 | 4890 | 21106.7 | 7643.55 | 0.0327646 | 1.60389 | 6.74823 | 0.977824 | 0.00141667 | 1.50305e-05 | 5.03434e-06 | 3(Loss) | true |
| Glaze | 2424.13 | 0.0349662 | 1792.69ms | 25388 | 1280 | 15611.8 | 9987.86 | 0.0693039 | 2.09357 | 8.93158 | 1.6984 | 0.00532797 | 1.10473e-05 | 2.83106e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2372.7 | 0.0323903 | 1819.88ms | 25388 | 2560 | 27966.8 | 10204.4 | 0.158073 | 2.14024 | 8.61978 | 1.43887 | 0.0035352 | 1.72326e-05 | 6.75454e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21154.7 | 0.0993488 | 874.143ms | 31235 | 1280 | 2504.98 | 1408.1 | 0.00704577 | 0.245788 | 0.668225 | 0.0968465 | 3.25156e-05 | 1.44569e-05 | 3.82684e-06 | 1(Win) | true |
| Glaze | 6677.36 | 0.061234 | 1184.37ms | 31235 | 4890 | 36489.5 | 4461.05 | 0.164713 | 0.763722 | 3.75185 | 0.631087 | 0.000722264 | 2.16055e-05 | 1.15426e-05 | 2(Loss) | true |
| simdjson (reflection) | 532.752 | 0.182482 | 6366.32ms | 31235 | 2560 | 2.66509e+07 | 55913.5 | 0.0511116 | 9.43606 | 38.2381 | 7.0414 | 0.0151276 | 0.000142681 | 9.24819e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21907.9 | 0.0670295 | 871.951ms | 31235 | 4890 | 4061.82 | 1359.69 | 0.0464218 | 0.237467 | 0.652025 | 0.0931648 | 3.2454e-05 | 9.23797e-06 | 3.85625e-06 | 1(Win) | true |
| Glaze | 7381.97 | 0.113507 | 1137.48ms | 31235 | 2560 | 53706.3 | 4035.24 | 0.070668 | 0.689967 | 3.62862 | 0.603938 | 0.000691194 | 1.94218e-05 | 1.05301e-05 | 2(Loss) | true |
| simdjson (reflection) | 530.156 | 0.178949 | 6367.79ms | 31235 | 2560 | 2.58806e+07 | 56187.2 | 0.109048 | 9.44212 | 38.2539 | 7.04537 | 0.0151338 | 0.00011498 | 7.80124e-05 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3205.58 | 0.0464021 | 3973.65ms | 108313 | 640 | 143088 | 32223.6 | 0.0277815 | 1.57824 | 7.40082 | 1.50827 | 0.0021865 | 2.10328e-05 | 1.49884e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2236.67 | 0.0915003 | 5377.51ms | 108313 | 80 | 142854 | 46182.7 | 0.0450723 | 2.2598 | 10.3059 | 1.84188 | 0.0026802 | 9.34791e-06 | 6.46275e-06 | 2(Loss) | true |
| Glaze | 2223.56 | 0.0866913 | 5386.48ms | 108313 | 320 | 518995 | 46454.8 | 0.0481613 | 2.27373 | 10.0551 | 1.92674 | 0.00312301 | 1.53202e-05 | 9.14595e-06 | 3(Loss) | true |
| simdjson (reflection) | 1686.88 | 0.0436804 | 6887.49ms | 108313 | 320 | 228937 | 61234.6 | 0.0443011 | 2.99629 | 13.097 | 2.03448 | 0.00224139 | 6.48295e-05 | 5.10961e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1446.95 | 0.0454775 | 7900.57ms | 108313 | 4890 | 5.15413e+06 | 71388.3 | 0.0234845 | 3.48509 | 14.907 | 2.64241 | 0.00276354 | 3.12602e-05 | 2.03549e-05 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3827.07 | 0.0242558 | 3625.7ms | 108313 | 2560 | 109723 | 26990.7 | 5.49958e-05 | 1.31979 | 6.65907 | 1.33399 | 0.00193041 | 7.51944e-06 | 4.42872e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2509.8 | 0.020175 | 5040.91ms | 108313 | 4890 | 337148 | 41156.8 | 0.0950973 | 2.01269 | 9.56858 | 1.66868 | 0.00255955 | 1.7049e-05 | 1.23685e-05 | 2(Loss) | true |
| Glaze | 2485.62 | 0.0462291 | 5076.99ms | 108313 | 1280 | 472424 | 41557.1 | 0.0533079 | 2.03362 | 9.37268 | 1.76545 | 0.00276017 | 2.3478e-05 | 1.68565e-05 | 3(Loss) | true |
| simdjson (reflection) | 1718.86 | 0.0244119 | 6938.82ms | 108313 | 2560 | 550968 | 60095.3 | 0.142297 | 2.93031 | 12.7902 | 1.96247 | 0.0025147 | 2.3377e-05 | 1.63913e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1552.15 | 0.0627597 | 7623.3ms | 108313 | 80 | 139555 | 66549.8 | 0.145431 | 3.25657 | 14.2468 | 2.49171 | 0.00289774 | 4.03922e-06 | 1.38488e-06 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20267.8 | 0.041823 | 1247.03ms | 108313 | 2560 | 11631 | 5096.52 | 0.0499978 | 0.251215 | 1.0938 | 0.288839 | 0.000108612 | 5.44213e-06 | 2.71205e-06 | 1(Win) | true |
| simdjson (reflection) | 15583 | 0.108762 | 1408.56ms | 108313 | 320 | 16632.6 | 6628.71 | 0.108406 | 0.326187 | 1.49385 | 0.193716 | 0.000183554 | 9.54987e-06 | 4.38544e-06 | 2(Loss) | true |
| Glaze | 5637.65 | 0.131815 | 2577.03ms | 108313 | 1280 | 746631 | 18322.4 | 0.0539349 | 0.886635 | 3.01787 | 0.397404 | 0.000247056 | 2.11771e-05 | 1.46205e-05 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20499.9 | 0.0844767 | 1245.58ms | 108313 | 640 | 11596.1 | 5038.81 | 0.0656036 | 0.248398 | 1.08875 | 0.287694 | 0.000109434 | 6.60701e-06 | 4.12577e-06 | 1(Win) | true |
| simdjson (reflection) | 15531.2 | 0.0895633 | 1401.7ms | 108313 | 640 | 22708.6 | 6650.82 | 0.0408011 | 0.327118 | 1.48913 | 0.192645 | 0.000177783 | 1.61136e-05 | 1.08915e-05 | 2(Loss) | true |
| Glaze | 6577.11 | 0.0531397 | 2313.15ms | 108313 | 4890 | 340595 | 15705.3 | 0.0147906 | 0.769572 | 2.97166 | 0.386768 | 0.000255185 | 1.09997e-05 | 7.62578e-06 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3353.85 | 0.0339599 | 5985.77ms | 183677 | 640 | 201342 | 52228.9 | 0.0923114 | 1.50688 | 6.8462 | 1.13769 | 0.00161743 | 1.32451e-05 | 9.23836e-06 | 1(Win) | true |
| Jsonifier | 2900.19 | 0.0983187 | 6789.14ms | 183677 | 40 | 141055 | 60398.8 | 0.019237 | 1.7431 | 6.95664 | 1.54562 | 0.00211472 | 3.48438e-05 | 2.77661e-05 | 2(Loss) | true |
| simdjson (reflection) | 2715.13 | 0.0162565 | 7202.97ms | 183677 | 4890 | 537886 | 64515.6 | 0.0474494 | 1.86363 | 8.30585 | 1.22227 | 0.00130592 | 2.13253e-05 | 1.4938e-05 | 3(Loss) | true |
| Glaze | 2558.16 | 0.0162981 | 7568.58ms | 183677 | 4890 | 609030 | 68474.2 | 0.129159 | 1.97478 | 8.7666 | 1.71796 | 0.00328375 | 2.42156e-05 | 1.75421e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2338.89 | 0.0335012 | 8248.71ms | 183677 | 2560 | 1.61158e+06 | 74893.7 | 0.0700786 | 2.15687 | 9.38318 | 1.58251 | 0.00163168 | 3.02629e-05 | 2.09182e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3742.75 | 0.0141899 | 5613.31ms | 183677 | 4890 | 215674 | 46802 | 0.0471319 | 1.35054 | 6.40735 | 1.03452 | 0.00140378 | 1.23984e-05 | 1.00737e-05 | 1(Win) | true |
| Jsonifier | 3173.45 | 0.0149459 | 6453.05ms | 183677 | 4890 | 332813 | 55198 | 0.00962598 | 1.59284 | 6.51762 | 1.44243 | 0.00204436 | 1.19519e-05 | 7.56418e-06 | 2(Loss) | true |
| simdjson (reflection) | 2769.74 | 0.0192907 | 7258.88ms | 183677 | 2560 | 381040 | 63243.5 | 0.0465376 | 1.82438 | 8.13458 | 1.1818 | 0.00140424 | 1.08313e-05 | 7.27542e-06 | 3(Loss) | true |
| Glaze | 2750.47 | 0.0883262 | 7289.86ms | 183677 | 40 | 126571 | 63686.6 | 0.0459229 | 1.8386 | 8.3632 | 1.62297 | 0.00312301 | 5.71656e-06 | 1.36108e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2494.86 | 0.0420438 | 7956.25ms | 183677 | 2560 | 2.23081e+06 | 70211.6 | 0.0832201 | 2.0204 | 8.99342 | 1.49403 | 0.00175338 | 1.60672e-05 | 1.22306e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26010.9 | 0.0231955 | 1519.9ms | 213963 | 4890 | 16191.2 | 7844.82 | 0.0441749 | 0.195789 | 0.625482 | 0.146194 | 5.5274e-05 | 4.29044e-06 | 2.77364e-06 | 1(Win) | true |
| Glaze | 5513.14 | 0.153693 | 4464.8ms | 213963 | 640 | 2.07094e+06 | 37011.8 | 0.109364 | 0.91499 | 3.5942 | 0.575291 | 0.000542624 | 9.69794e-06 | 5.68147e-06 | 2(Loss) | true |
| simdjson (reflection) | 472.24 | 0.25225 | 5542.61ms | 213963 | 640 | 7.60318e+08 | 432092 | 0.0903985 | 10.5626 | 41.6914 | 8.45658 | 0.0394036 | 0.203035 | 0.000665492 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26583.2 | 0.11127 | 1515.18ms | 213963 | 40 | 2917.95 | 7675.95 | 0.258365 | 0.194821 | 0.623014 | 0.145637 | 5.81876e-05 | 1.51895e-06 | 7.01056e-07 | 1(Win) | true |
| Glaze | 6348.78 | 0.072744 | 3964.15ms | 213963 | 4890 | 2.67301e+06 | 32140.2 | 0.136643 | 0.793943 | 3.56743 | 0.569169 | 0.000526276 | 7.08511e-06 | 4.75303e-06 | 2(Loss) | true |
| simdjson (reflection) | 476.481 | 0.237939 | 5553.27ms | 213963 | 640 | 6.64507e+08 | 428246 | 0.498712 | 10.4926 | 41.6907 | 8.45599 | 0.0418418 | 0.204248 | 0.000688181 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 855.896 | 0.0680093 | 6412.8ms | 1834197 | 160 | 3.09105e+08 | 2.04374e+06 | 0.018011 | 5.86722 | 25.8828 | 5.55398 | 0.0301936 | 0.082353 | 0.0028913 | 1(Win) | true |
| Jsonifier (two-stage) | 722.648 | 0.065 | 7625.79ms | 1834197 | 160 | 3.96082e+08 | 2.42058e+06 | 0.928629 | 6.95253 | 29.3424 | 5.98071 | 0.0368552 | 0.14529 | 0.0222914 | 2(Loss) | true |
| Glaze | 644.696 | 0.438977 | 8322.05ms | 1834197 | 40 | 5.67448e+09 | 2.71326e+06 | 0.491059 | 7.7368 | 32.3736 | 6.32381 | 0.0345806 | 0.0837062 | 0.00606429 | 3(Loss) | true |
| simdjson (reflection) | 620.652 | 0.0565425 | 8767.06ms | 1834197 | 40 | 1.01579e+08 | 2.81837e+06 | 0.0998789 | 8.13161 | 34.8333 | 6.48953 | 0.0370935 | 0.135875 | 0.00846875 | 4(Loss) | true |
| simdjson (ondemand) | 515.522 | 0.349963 | 5064.47ms | 1834197 | 80 | 1.12806e+10 | 3.39312e+06 | 0.3396 | 9.84682 | 38.0357 | 7.35418 | 0.0418221 | 0.147086 | 0.0382246 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 952.453 | 0.10658 | 6501.86ms | 1834197 | 40 | 1.53255e+08 | 1.83655e+06 | 0.0704267 | 5.28521 | 22.8799 | 4.85497 | 0.0294873 | 0.0557447 | 0.00235787 | 1(Win) | true |
| Jsonifier (two-stage) | 809.845 | 0.149814 | 7467.78ms | 1834197 | 30 | 3.14134e+08 | 2.15995e+06 | 0.0576796 | 6.20809 | 26.3402 | 5.28156 | 0.0359092 | 0.119045 | 0.00519304 | 2(Loss) | true |
| Glaze | 714.139 | 0.148012 | 8343.17ms | 1834197 | 160 | 2.10301e+09 | 2.44942e+06 | 0.032158 | 7.03866 | 29.3656 | 5.62362 | 0.0329781 | 0.0599391 | 0.00245458 | 3(Loss) | true |
| simdjson (reflection) | 691.038 | 0.0754897 | 8504.01ms | 1834197 | 40 | 1.46057e+08 | 2.5313e+06 | 0.00859563 | 7.31846 | 31.8035 | 5.77319 | 0.0321438 | 0.111769 | 0.00023558 | 4(Loss) | true |
| simdjson (ondemand) | 578.218 | 0.0843846 | 10094.5ms | 1834197 | 40 | 2.60672e+08 | 3.0252e+06 | 0.145121 | 8.73813 | 35.013 | 6.65235 | 0.0370686 | 0.118575 | 0.0178394 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1281.95 | 0.0619018 | 8654.53ms | 1834197 | 30 | 2.14033e+07 | 1.36451e+06 | 0.00128738 | 3.93897 | 13.1332 | 0.799079 | 0.00241239 | 0.0601046 | 0.000150438 | 1(Win) | true |
| Glaze | 982.489 | 0.396184 | 5601.1ms | 1833577 | 30 | 1.49162e+09 | 1.7798e+06 | 0.447468 | 5.13249 | 16.0488 | 1.05286 | 0.00101432 | 0.0497809 | 0.000177904 | 2(Loss) | true |
| simdjson (reflection) | 884.199 | 0.0870705 | 6449.98ms | 1922245 | 40 | 1.30353e+08 | 2.07328e+06 | 0.00550626 | 5.71186 | 18.1523 | 2.01851 | 0.0263275 | 0.0506918 | 0.000170049 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1279.5 | 0.0274637 | 8656.65ms | 1834197 | 320 | 4.51109e+07 | 1.36712e+06 | 0.00296235 | 3.94577 | 13.133 | 0.799039 | 0.00253089 | 0.0597589 | 0.000469647 | 1(Win) | true |
| Glaze | 986.741 | 0.181265 | 5525.83ms | 1833577 | 160 | 1.65097e+09 | 1.77213e+06 | 0.0229942 | 5.119 | 16.048 | 1.05269 | 0.00101142 | 0.0495565 | 5.90581e-05 | 2(Loss) | true |
| simdjson (reflection) | 884.142 | 0.016399 | 6458.3ms | 1922245 | 80 | 9.24907e+06 | 2.07342e+06 | 0.00304036 | 5.71319 | 18.1521 | 2.01847 | 0.0263056 | 0.0503143 | 3.24295e-05 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2624.08 | 0.0528087 | 8314.44ms | 7351818 | 160 | 3.18541e+08 | 2.67188e+06 | 0.0705665 | 1.91502 | 8.25799 | 1.535 | 0.0105262 | 0.0611643 | 0.000817912 | 1(Win) | true |
| Jsonifier | 2574.87 | 0.0470043 | 8493.41ms | 7351818 | 160 | 2.62104e+08 | 2.72295e+06 | 0.214024 | 1.95566 | 8.73357 | 1.99994 | 0.00751357 | 0.0342788 | 0.000425166 | 2(Loss) | true |
| simdjson (reflection) | 2264.47 | 0.0521155 | 9633.23ms | 7351818 | 40 | 1.04148e+08 | 3.0962e+06 | 0.110246 | 2.22883 | 9.70637 | 1.65689 | 0.00913207 | 0.0584193 | 0.000163245 | 3(Loss) | true |
| Glaze | 2064.82 | 0.0671593 | 5104.93ms | 7351818 | 80 | 4.16033e+08 | 3.39557e+06 | 0.0682708 | 2.44156 | 11.2406 | 2.23967 | 0.00901098 | 0.0335089 | 0.00049848 | 4(Loss) | true |
| simdjson (ondemand) | 1962.74 | 0.0832013 | 5377.06ms | 7351818 | 30 | 2.64999e+08 | 3.57216e+06 | 0.0281589 | 2.56825 | 10.5051 | 1.87229 | 0.0102592 | 0.0615029 | 0.000344473 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2863.98 | 0.0448151 | 8320.13ms | 7351818 | 160 | 1.92583e+08 | 2.44807e+06 | 0.0166554 | 1.75797 | 7.50891 | 1.36065 | 0.0102989 | 0.0544172 | 0.000402307 | 1(Win) | true |
| Jsonifier | 2797.32 | 0.0569717 | 8480.47ms | 7351818 | 160 | 3.26244e+08 | 2.50641e+06 | 0.125618 | 1.80422 | 7.98439 | 1.8255 | 0.00729958 | 0.0275711 | 0.000488041 | 2(Loss) | true |
| simdjson (reflection) | 2477.26 | 0.0596989 | 9409.51ms | 7351818 | 30 | 8.56446e+07 | 2.83024e+06 | 0.0744414 | 2.03785 | 8.95052 | 1.47812 | 0.00795844 | 0.0520235 | 0.000213213 | 3(Loss) | true |
| Glaze | 2224.2 | 0.0740685 | 5091.45ms | 7351818 | 40 | 2.18056e+08 | 3.15225e+06 | 0.0927065 | 2.27002 | 10.49 | 2.06508 | 0.0085384 | 0.0275529 | 0.000124605 | 4(Loss) | true |
| simdjson (ondemand) | 2138.44 | 0.0469278 | 5277.19ms | 7351818 | 40 | 9.46927e+07 | 3.27867e+06 | 0.0708148 | 2.35991 | 9.75061 | 1.69725 | 0.0091096 | 0.0537476 | 0.000216484 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6386.49 | 0.0186747 | 9414.9ms | 9930848 | 320 | 2.45417e+07 | 1.48294e+06 | 0.0760196 | 0.790612 | 2.51819 | 0.147587 | 0.000353391 | 0.024989 | 0.000189429 | 1(Win) | true |
| Glaze | 3653.91 | 0.241802 | 8038.22ms | 9930228 | 80 | 3.14205e+09 | 2.5918e+06 | 0.256216 | 1.37967 | 4.41557 | 0.474372 | 0.000799093 | 0.0416671 | 0.00260969 | 2(Loss) | true |
| simdjson (reflection) | 273.03 | 0.113973 | 10540.3ms | 10018896 | 30 | 4.77244e+10 | 3.49953e+07 | 0.310674 | 13.5594 | 38.7655 | 5.79716 | 0.0262764 | 0.268324 | 0.111487 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6381.83 | 0.0415222 | 9396.28ms | 9930848 | 160 | 6.07522e+07 | 1.48402e+06 | 0.0155282 | 0.792319 | 2.51816 | 0.14758 | 0.000359036 | 0.0249858 | 0.000615677 | 1(Win) | true |
| Glaze | 4057.68 | 0.181548 | 7266.36ms | 9930228 | 80 | 1.43627e+09 | 2.3339e+06 | 0.128465 | 1.24418 | 4.4153 | 0.474313 | 0.000796453 | 0.0223812 | 0.000414142 | 2(Loss) | true |
| simdjson (reflection) | 308.654 | 1.9939 | 9343.8ms | 10018896 | 30 | 1.14294e+13 | 3.09562e+07 | 0.630312 | 13.1675 | 38.7853 | 5.80152 | 0.0259537 | 0.291642 | 0.129552 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 861.412 | 0.150285 | 6294.6ms | 1834197 | 40 | 3.7253e+08 | 2.03065e+06 | 0.00611261 | 5.83633 | 25.449 | 5.41699 | 0.03149 | 0.0841036 | 9.78494e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 737.414 | 0.135142 | 7405.25ms | 1834197 | 40 | 4.11064e+08 | 2.37211e+06 | 0.219733 | 6.81125 | 28.907 | 5.86207 | 0.0376877 | 0.147789 | 0.000220137 | 2(Loss) | true |
| Glaze | 660.812 | 0.0653024 | 8254.69ms | 1834197 | 30 | 8.96428e+07 | 2.64709e+06 | 0.100364 | 7.64257 | 32.3366 | 6.31554 | 0.0348532 | 0.0839919 | 3.24211e-05 | 3(Loss) | true |
| simdjson (reflection) | 623.973 | 0.0650478 | 8766.06ms | 1834197 | 40 | 1.3301e+08 | 2.80337e+06 | 0.00757781 | 8.10163 | 34.8564 | 6.51703 | 0.0370526 | 0.136536 | 0.00135055 | 4(Loss) | true |
| simdjson (ondemand) | 524.098 | 0.0661283 | 5029.5ms | 1834197 | 40 | 1.94851e+08 | 3.3376e+06 | 0.36554 | 9.62842 | 37.4491 | 7.33897 | 0.0425116 | 0.148786 | 0.000176658 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 975.552 | 0.0629995 | 6299.9ms | 1834197 | 80 | 1.02083e+08 | 1.79306e+06 | 0.0432303 | 5.17821 | 22.4717 | 4.72702 | 0.0306659 | 0.0570952 | 3.93565e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 823.805 | 0.0330409 | 7356.85ms | 1834197 | 160 | 7.87528e+07 | 2.12335e+06 | 0.173487 | 6.1296 | 25.9312 | 5.17251 | 0.0366105 | 0.120704 | 5.56715e-05 | 2(Loss) | true |
| Glaze | 723.232 | 0.0641825 | 8282.45ms | 1834197 | 40 | 9.63897e+07 | 2.41863e+06 | 0.0214862 | 6.98338 | 29.3558 | 5.62414 | 0.0336529 | 0.0598081 | 3.18259e-05 | 3(Loss) | true |
| simdjson (reflection) | 694.034 | 0.0250374 | 8543.68ms | 1834197 | 160 | 6.37133e+07 | 2.52038e+06 | 0.00612148 | 7.27825 | 31.8444 | 5.81342 | 0.0319422 | 0.112362 | 0.000753293 | 4(Loss) | true |
| simdjson (ondemand) | 572.169 | 0.0743607 | 10242.3ms | 1834197 | 30 | 1.55043e+08 | 3.05718e+06 | 0.0217099 | 8.80983 | 34.453 | 6.64592 | 0.0372044 | 0.118953 | 0.000145513 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1271.75 | 0.0598368 | 8731.26ms | 1834197 | 320 | 2.1676e+08 | 1.37545e+06 | 0.00662257 | 3.96565 | 13.1198 | 0.79908 | 0.00291226 | 0.0618482 | 2.16495e-05 | 1(Win) | true |
| Glaze | 960.003 | 0.271794 | 5674.79ms | 1833577 | 160 | 3.92151e+09 | 1.82149e+06 | 0.265382 | 5.23699 | 16.0435 | 1.05288 | 0.00100569 | 0.0765555 | 2.89291e-05 | 2(Loss) | true |
| simdjson (reflection) | 889.731 | 0.0104599 | 6418.6ms | 1922245 | 80 | 3.71577e+06 | 2.06039e+06 | 0.0350942 | 5.67481 | 18.1621 | 2.01852 | 0.0244581 | 0.0518748 | 5.32841e-05 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1270.01 | 0.103474 | 8741ms | 1834197 | 30 | 6.09338e+07 | 1.37733e+06 | 0.115409 | 3.97539 | 13.1197 | 0.79904 | 0.00299713 | 0.061835 | 7.56007e-05 | 1(Win) | true |
| Glaze | 1006.91 | 0.264785 | 5418.86ms | 1833577 | 160 | 3.38317e+09 | 1.73663e+06 | 0.286461 | 5.01117 | 16.0427 | 1.0527 | 0.00100195 | 0.0495036 | 1.17223e-05 | 2(Loss) | true |
| simdjson (reflection) | 890.417 | 0.0101982 | 6409.5ms | 1922245 | 40 | 1.76333e+06 | 2.05881e+06 | 0.0270298 | 5.67228 | 18.1619 | 2.01848 | 0.0244728 | 0.0519406 | 6.08403e-05 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2644.28 | 0.0690522 | 8290.87ms | 7351818 | 160 | 5.36352e+08 | 2.65147e+06 | 0.149365 | 1.89097 | 8.14826 | 1.50512 | 0.0107143 | 0.0614255 | 0.000182436 | 1(Win) | true |
| Jsonifier | 2608.01 | 0.0714895 | 8374.71ms | 7351818 | 160 | 5.90983e+08 | 2.68835e+06 | 0.0101051 | 1.92948 | 8.62411 | 1.96535 | 0.00768858 | 0.0346312 | 0.000242375 | 2(Loss) | true |
| simdjson (reflection) | 2269.95 | 0.035681 | 9625.87ms | 7351818 | 40 | 4.8584e+07 | 3.08872e+06 | 0.0217526 | 2.22446 | 9.71204 | 1.6637 | 0.00904363 | 0.0586496 | 0.000173243 | 3(Loss) | true |
| Glaze | 2059.15 | 0.13201 | 5144.02ms | 7351818 | 80 | 1.61628e+09 | 3.40492e+06 | 0.164582 | 2.44847 | 11.2347 | 2.23762 | 0.00904362 | 0.0338939 | 0.000412697 | 4(Loss) | true |
| simdjson (ondemand) | 1936.39 | 0.0867142 | 5470.56ms | 7351818 | 40 | 3.94316e+08 | 3.62078e+06 | 0.11564 | 2.60174 | 10.3588 | 1.86883 | 0.0103692 | 0.0617506 | 0.000167448 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2902.39 | 0.141888 | 8248.41ms | 7351818 | 40 | 4.69929e+08 | 2.41568e+06 | 0.027943 | 1.72511 | 7.40591 | 1.33312 | 0.0104629 | 0.0546594 | 0.000125455 | 1(Win) | true |
| Jsonifier | 2853.7 | 0.043568 | 8373.14ms | 7351818 | 80 | 9.16641e+07 | 2.4569e+06 | 0.0631409 | 1.76916 | 7.88138 | 1.79323 | 0.00751715 | 0.027857 | 0.000288939 | 2(Loss) | true |
| simdjson (reflection) | 2485.78 | 0.0690645 | 9438.75ms | 7351818 | 40 | 1.51787e+08 | 2.82054e+06 | 0.00736734 | 2.03028 | 8.96023 | 1.48803 | 0.00784052 | 0.0521438 | 8.04631e-05 | 3(Loss) | true |
| Glaze | 2208.51 | 0.131833 | 5156.42ms | 7351818 | 40 | 7.00643e+08 | 3.17465e+06 | 0.161958 | 2.28329 | 10.4912 | 2.06524 | 0.00872886 | 0.0278544 | 0.000329816 | 4(Loss) | true |
| simdjson (ondemand) | 2093.84 | 0.113619 | 5387.24ms | 7351818 | 40 | 5.78981e+08 | 3.34851e+06 | 0.19251 | 2.40052 | 9.61118 | 1.69576 | 0.00908581 | 0.0537446 | 0.00010309 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6296.21 | 0.0567295 | 9528.95ms | 9930848 | 160 | 1.16507e+08 | 1.50421e+06 | 0.003219 | 0.79925 | 2.51578 | 0.147546 | 0.000458831 | 0.0249905 | 0.000211577 | 1(Win) | true |
| Glaze | 3151.51 | 0.240844 | 9357.46ms | 9930228 | 30 | 1.57135e+09 | 3.00497e+06 | 0.0847554 | 1.59533 | 4.41437 | 0.474336 | 0.000695781 | 0.0757416 | 0.00806365 | 2(Loss) | true |
| simdjson (reflection) | 386.862 | 0.265972 | 7509.79ms | 10018896 | 30 | 1.29456e+11 | 2.46981e+07 | 1.00246 | 13.0261 | 38.7489 | 5.79802 | 0.0228246 | 0.3133 | 0.151331 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6316.29 | 0.0474116 | 9551.53ms | 9930848 | 30 | 1.51614e+07 | 1.49942e+06 | 0.118671 | 0.799481 | 2.51575 | 0.147539 | 0.000481416 | 0.0249818 | 0.000140794 | 1(Win) | true |
| Glaze | 4076.75 | 0.144576 | 7244.48ms | 9930228 | 80 | 9.02347e+08 | 2.32298e+06 | 0.0899124 | 1.24202 | 4.414 | 0.474254 | 0.000781265 | 0.0224149 | 0.000249594 | 2(Loss) | true |
| simdjson (reflection) | 333.581 | 1.51384 | 8626.27ms | 10018896 | 30 | 5.6405e+12 | 2.8643e+07 | 0.420014 | 13.279 | 38.772 | 5.80014 | 0.0234416 | 0.289026 | 0.143406 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1194.32 | 0.0572243 | 9617.23ms | 461466 | 80 | 3.55702e+06 | 368483 | 0.0552501 | 4.22977 | 17.8094 | 3.2223 | 0.0195459 | 0.0398549 | 2.10741e-05 | 1(Win) | true |
| simdjson (reflection) | 1170.46 | 0.0716117 | 9826.24ms | 461466 | 640 | 4.63994e+07 | 375995 | 0.0546484 | 4.29063 | 18.5842 | 3.24556 | 0.0100896 | 0.0567621 | 0.000279392 | 2(Loss) | true |
| Jsonifier (two-stage) | 1090.45 | 0.205844 | 5238.94ms | 461466 | 40 | 2.76059e+07 | 403582 | 0.126468 | 4.61646 | 19.2173 | 3.44868 | 0.0221796 | 0.0853488 | 0.000457943 | 3(Loss) | true |
| Glaze | 1064.14 | 0.153034 | 5372.3ms | 461466 | 160 | 6.40875e+07 | 413561 | 0.00531031 | 4.74634 | 20.1525 | 3.94161 | 0.024413 | 0.0322765 | 6.41299e-05 | 4(Loss) | true |
| simdjson (ondemand) | 977.784 | 0.0844196 | 5828.21ms | 461466 | 640 | 9.23975e+07 | 450088 | 0.0679617 | 5.14019 | 20.2893 | 3.60155 | 0.0119902 | 0.089572 | 0.000431671 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1613.14 | 0.0382368 | 8838.26ms | 461466 | 640 | 6.96434e+06 | 272815 | 0.0825099 | 3.11988 | 13.62 | 2.29702 | 0.0172007 | 0.00569957 | 2.5784e-05 | 1(Win) | true |
| simdjson (reflection) | 1525.62 | 0.0768558 | 9151.81ms | 461466 | 1280 | 6.29142e+07 | 288465 | 0.017374 | 3.26549 | 14.9756 | 2.41374 | 0.00394558 | 0.0266572 | 4.20332e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1455.36 | 0.081032 | 9637.95ms | 461466 | 320 | 1.92134e+07 | 302392 | 0.0119675 | 3.46407 | 15.0203 | 2.52168 | 0.0194175 | 0.0247374 | 2.45684e-05 | 3(Loss) | true |
| Glaze | 1330.64 | 0.102221 | 5159.6ms | 461466 | 640 | 7.31511e+07 | 330734 | 0.0608781 | 3.79677 | 16.323 | 3.08259 | 0.0219469 | 0.0100825 | 1.28497e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1286.15 | 0.172106 | 5243.8ms | 461466 | 320 | 1.10979e+08 | 342176 | 0.189015 | 3.90124 | 16.3005 | 2.70005 | 0.00425201 | 0.0319603 | 5.28953e-05 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17737.2 | 0.028317 | 3240.06ms | 461466 | 1280 | 63185.2 | 24811.6 | 0.00332179 | 0.285397 | 1.43325 | 0.226587 | 0.000208485 | 0.00612447 | 4.20365e-06 | 1(Win) | true |
| simdjson (reflection) | 11477 | 0.018102 | 4620.08ms | 461466 | 2560 | 123343 | 38345.2 | 0.0551213 | 0.44073 | 2.24062 | 0.318281 | 0.00203938 | 0.00673245 | 4.33655e-06 | 2(Loss) | true |
| Glaze | 4602.44 | 0.0576571 | 5328.03ms | 461466 | 320 | 972655 | 95620.7 | 0.0542638 | 1.09907 | 4.66003 | 0.714445 | 0.00913699 | 0.0473421 | 1.06996e-05 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17826.9 | 0.0444996 | 3225.43ms | 461466 | 80 | 9654.52 | 24686.8 | 0.00648079 | 0.284169 | 1.43424 | 0.22632 | 0.000209143 | 0.00593253 | 2.16159e-05 | 1(Win) | true |
| simdjson (reflection) | 11372 | 0.0287042 | 4639.54ms | 461466 | 2560 | 315889 | 38699.2 | 0.0287552 | 0.444601 | 2.23952 | 0.31803 | 0.00191028 | 0.010006 | 2.4229e-05 | 2(Loss) | true |
| Glaze | 5207 | 0.0250356 | 9254.71ms | 461466 | 4890 | 2.18942e+06 | 84518.6 | 0.0470519 | 0.970463 | 4.64554 | 0.711034 | 0.00908777 | 0.0126704 | 2.48328e-05 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1802.45 | 1.01602 | 9923.92ms | 728486 | 640 | 9.81527e+09 | 385441 | 0.718993 | 2.79548 | 12.2299 | 2.05024 | 0.00316979 | 0.0329835 | 0.000179242 | 1(Win) | true |
| Jsonifier (two-stage) | 1721.09 | 0.876568 | 5230.67ms | 728486 | 640 | 8.01281e+09 | 403661 | 0.326141 | 2.93576 | 12.6176 | 2.17075 | 0.00895997 | 0.0371435 | 0.000243339 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1547.67 | 0.706238 | 5811.91ms | 728486 | 640 | 6.43231e+09 | 448893 | 0.544325 | 3.30535 | 13.3042 | 2.56503 | 0.00905989 | 0.0149588 | 0.000226141 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1544.35 | 0.674967 | 5852.07ms | 728486 | 640 | 5.90061e+09 | 449859 | 0.165551 | 3.27561 | 13.3239 | 2.28022 | 0.00364486 | 0.0411555 | 0.000140499 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1521.87 | 0.576306 | 5917.48ms | 728486 | 640 | 4.42971e+09 | 456504 | 0.733072 | 3.35412 | 15.0927 | 2.95279 | 0.00968148 | 0.00918945 | 0.000196797 | 3(Tie) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2383.25 | 0.294797 | 9375.59ms | 728486 | 640 | 4.72638e+08 | 291508 | 0.521815 | 2.11513 | 9.92385 | 1.57253 | 0.00724395 | 0.013803 | 0.000126407 | 1(Win) | true |
| simdjson (reflection) | 2350.72 | 0.440241 | 9467.48ms | 728486 | 40 | 6.77147e+07 | 295543 | 0.0255019 | 2.14222 | 10.022 | 1.54434 | 0.00232698 | 0.0232365 | 0.000294584 | 2(Loss) | true |
| Jsonifier | 2026.92 | 0.188507 | 5280.63ms | 728486 | 640 | 2.67182e+08 | 342757 | 0.096129 | 2.50926 | 10.6014 | 1.96469 | 0.00807091 | 0.00395668 | 0.000108502 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1911.77 | 1.20714 | 5450.47ms | 728486 | 320 | 6.15796e+09 | 363401 | 0.666049 | 2.64673 | 10.8529 | 1.72342 | 0.00208123 | 0.0274706 | 0.000189481 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1907.58 | 0.19413 | 5532.38ms | 728486 | 320 | 1.59961e+08 | 364199 | 0.185897 | 2.65995 | 12.599 | 2.38206 | 0.00868915 | 0.00392014 | 0.000120052 | 4(Tie) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21490.3 | 0.0937656 | 4546.87ms | 837491 | 640 | 777221 | 37165.4 | 0.121093 | 0.237635 | 0.835238 | 0.124859 | 0.000139766 | 0.00599574 | 2.57391e-05 | 1(Win) | true |
| Glaze | 4844.08 | 0.397708 | 8980.1ms | 837491 | 1280 | 5.50397e+08 | 164880 | 1.60093 | 1.03818 | 4.43688 | 0.73033 | 0.00588968 | 0.0492155 | 0.000138031 | 2(Loss) | true |
| simdjson (reflection) | 525.004 | 1.26263 | 9677.28ms | 837491 | 160 | 5.90343e+10 | 1.52131e+06 | 0.0504923 | 9.66806 | 37.3301 | 7.15622 | 0.0245811 | 0.329959 | 0.00142833 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21902.3 | 0.249953 | 4649.93ms | 837491 | 40 | 332323 | 36466.2 | 0.540511 | 0.235057 | 0.834832 | 0.124744 | 0.00013236 | 0.00397207 | 1.42688e-05 | 1(Win) | true |
| Glaze | 5529.1 | 0.638922 | 7827.81ms | 837491 | 2560 | 2.18066e+09 | 144453 | 0.091264 | 0.913284 | 4.42726 | 0.728068 | 0.00588083 | 0.010057 | 6.41686e-05 | 2(Loss) | true |
| simdjson (reflection) | 518.099 | 1.89267 | 9747.25ms | 837491 | 80 | 6.81041e+10 | 1.54159e+06 | 0.986328 | 9.8251 | 37.0578 | 7.06715 | 0.0248138 | 0.323419 | 0.00157463 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7944.76 | 0.0545655 | 6357.02ms | 466906 | 2560 | 2.39427e+06 | 56046.5 | 0.309061 | 0.639129 | 3.09231 | 0.372797 | 0.000883809 | 6.70387e-06 | 5.1946e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 7916.46 | 0.0523716 | 6375.96ms | 466906 | 2560 | 2.22141e+06 | 56246.9 | 0.0241391 | 0.638483 | 3.09231 | 0.372797 | 0.000885909 | 1.74562e-05 | 1.26464e-05 | 2(Loss) | true |
| simdjson (reflection) | 6954.41 | 0.104527 | 7144.45ms | 466906 | 80 | 358330 | 64027.9 | 0.0187773 | 0.726699 | 3.57682 | 0.373581 | 0.00101262 | 7.28198e-06 | 6.23787e-06 | 3(Loss) | true |
| simdjson (ondemand) | 6683.98 | 0.0261759 | 7425.12ms | 466906 | 2560 | 778455 | 66618.4 | 0.0443439 | 0.75808 | 3.6079 | 0.3742 | 0.000812398 | 1.88876e-05 | 1.63e-05 | 4(Loss) | true |
| Glaze | 3239.33 | 0.0617476 | 7398.58ms | 466906 | 1280 | 9.22146e+06 | 137460 | 0.0754244 | 1.56777 | 6.45079 | 1.02937 | 0.0015759 | 7.20836e-06 | 5.02309e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8089.92 | 0.0272316 | 6428.08ms | 466906 | 2560 | 575117 | 55040.9 | 0.15734 | 0.624325 | 3.05908 | 0.364988 | 0.000873718 | 2.76337e-06 | 1.44652e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 8079.55 | 0.0396072 | 6419.06ms | 466906 | 1280 | 609877 | 55111.5 | 0.0373421 | 0.62527 | 3.05793 | 0.364714 | 0.000870496 | 1.6699e-06 | 4.5847e-07 | 2(Loss) | true |
| simdjson (reflection) | 7073.53 | 0.020455 | 7096.42ms | 466906 | 2560 | 424449 | 62949.7 | 0.0815624 | 0.714513 | 3.55191 | 0.367929 | 0.00100136 | 1.15371e-06 | 3.48872e-07 | 3(Loss) | true |
| simdjson (ondemand) | 6819.21 | 0.0274961 | 7322.95ms | 466906 | 1280 | 412613 | 65297.3 | 0.152171 | 0.738417 | 3.56518 | 0.364907 | 0.000793742 | 1.41724e-06 | 4.33371e-07 | 4(Loss) | true |
| Glaze | 3253.71 | 0.0397158 | 7436.91ms | 466906 | 2560 | 7.56255e+06 | 136852 | 0.0487667 | 1.55 | 6.4004 | 1.01743 | 0.00151032 | 5.60873e-06 | 3.6778e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8903.35 | 0.0407312 | 7510.31ms | 631514 | 1280 | 971681 | 67644.1 | 0.0629751 | 0.567061 | 2.72812 | 0.284768 | 0.000626382 | 4.4808e-06 | 2.88122e-06 | 1(Win) | true |
| Jsonifier | 8892.46 | 0.0246553 | 7514.53ms | 631514 | 4890 | 1.36349e+06 | 67726.9 | 0.0108932 | 0.567723 | 2.73018 | 0.285305 | 0.000639179 | 2.80075e-06 | 1.48052e-06 | 2(Loss) | true |
| simdjson (reflection) | 8406.38 | 0.0551086 | 7925.58ms | 631514 | 640 | 997623 | 71643 | 0.0303976 | 0.600955 | 3.00764 | 0.2896 | 0.000718432 | 1.27669e-05 | 2.25401e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8172.18 | 0.0178494 | 8116.48ms | 631514 | 4890 | 846149 | 73696.2 | 0.0325638 | 0.617909 | 3.03105 | 0.290151 | 0.000569002 | 1.52385e-05 | 3.42897e-06 | 4(Loss) | true |
| Glaze | 3818.83 | 0.0810722 | 8408.39ms | 631514 | 320 | 5.23118e+06 | 157708 | 0.08009 | 1.3209 | 5.85695 | 0.962476 | 0.00136849 | 1.59834e-06 | 6.13605e-07 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8990.87 | 0.0461752 | 7504.39ms | 631514 | 1280 | 1.22459e+06 | 66985.6 | 0.0109818 | 0.566439 | 2.7061 | 0.279964 | 0.000639773 | 6.13357e-06 | 5.25523e-06 | 1(Win) | true |
| Jsonifier | 8979.29 | 0.0315459 | 7535.48ms | 631514 | 4890 | 2.18916e+06 | 67072 | 0.0910309 | 0.566746 | 2.70704 | 0.280165 | 0.000666018 | 7.00721e-06 | 6.15135e-06 | 2(Loss) | true |
| simdjson (reflection) | 8279.04 | 0.0445223 | 8058.98ms | 631514 | 2560 | 2.68535e+06 | 72745 | 0.100469 | 0.610698 | 2.9944 | 0.286683 | 0.000760376 | 8.27562e-06 | 6.47625e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8111.12 | 0.048122 | 8211.65ms | 631514 | 4890 | 6.24312e+06 | 74251 | 0.0320494 | 0.624145 | 3.00402 | 0.284383 | 0.00061825 | 1.0579e-05 | 8.40289e-06 | 4(Loss) | true |
| Glaze | 3873.02 | 0.0374821 | 8361.72ms | 631514 | 2560 | 8.6967e+06 | 155501 | 0.0330885 | 1.3095 | 5.83003 | 0.956731 | 0.0013767 | 9.15521e-06 | 7.90635e-06 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2010.02 | 0.0663275 | 5870.35ms | 466906 | 1280 | 2.76347e+07 | 221528 | 0.174385 | 2.50164 | 7.81669 | 1.31328 | 0.0116596 | 0.0175915 | 0.000241457 | 1(Win) | true |
| Glaze | 1732.71 | 0.0530436 | 6769.05ms | 466906 | 1280 | 2.37838e+07 | 256982 | 0.0663008 | 2.90572 | 10.4261 | 1.86976 | 0.013275 | 0.0135572 | 0.000105242 | 2(Loss) | true |
| Jsonifier (two-stage) | 1700.03 | 0.132811 | 6940.11ms | 466906 | 320 | 3.87228e+07 | 261923 | 0.0167837 | 2.9529 | 9.02194 | 1.43031 | 0.0166498 | 0.0357262 | 0.000158055 | 3(Loss) | true |
| simdjson (reflection) | 1599.16 | 0.22426 | 7331.06ms | 466906 | 160 | 6.23881e+07 | 278445 | 0.00531777 | 3.14043 | 10.1544 | 1.52944 | 0.0132208 | 0.0318827 | 0.000479178 | 4(Loss) | true |
| simdjson (ondemand) | 1138.84 | 0.0922371 | 5082.49ms | 466906 | 640 | 8.32386e+07 | 390991 | 0.209894 | 4.37729 | 13.1716 | 2.75795 | 0.0140834 | 0.0510765 | 0.000236584 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2603.14 | 0.106557 | 5293.06ms | 466906 | 640 | 2.12623e+07 | 171053 | 0.156189 | 1.9263 | 6.38775 | 0.989802 | 0.0089482 | 0.00125823 | 6.32655e-05 | 1(Win) | true |
| Glaze | 2213.06 | 0.0998977 | 6015.74ms | 466906 | 640 | 2.58562e+07 | 201204 | 0.0258332 | 2.27191 | 8.98747 | 1.54305 | 0.00814616 | 0.000560953 | 1.25059e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2146.44 | 0.0654064 | 6309.96ms | 466906 | 1280 | 2.35651e+07 | 207448 | 0.368403 | 2.33842 | 7.59415 | 1.10742 | 0.0124993 | 0.00599198 | 7.98558e-05 | 3(Loss) | true |
| simdjson (reflection) | 1853.34 | 0.116556 | 7036.54ms | 466906 | 640 | 5.01877e+07 | 240256 | 0.294402 | 2.71372 | 9.10785 | 1.2843 | 0.00933185 | 0.0185975 | 1.5685e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1325.85 | 0.0747759 | 9460.05ms | 466906 | 1280 | 8.07246e+07 | 335843 | 0.24006 | 3.76804 | 11.8187 | 2.45214 | 0.0106542 | 0.0147757 | 1.82987e-05 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17544.2 | 0.0270665 | 3352.83ms | 475954 | 4890 | 239793 | 25872.1 | 0.195801 | 0.284613 | 1.00434 | 0.14801 | 0.000259644 | 0.00280959 | 1.86731e-06 | 1(Win) | true |
| simdjson (reflection) | 11121.6 | 0.102662 | 4875.09ms | 475954 | 30 | 52666.8 | 40812.9 | 0.0285939 | 0.454946 | 1.30937 | 0.183999 | 0.000285252 | 0.00247356 | 3.66282e-05 | 2(Loss) | true |
| Glaze | 7766.25 | 0.140747 | 6622.29ms | 475954 | 2560 | 1.73231e+07 | 58445.9 | 0.20351 | 0.646933 | 2.22758 | 0.324922 | 0.000271589 | 0.0148227 | 3.06293e-06 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17565.3 | 0.147725 | 3353.1ms | 475954 | 640 | 932630 | 25841 | 0.202073 | 0.283626 | 1.00324 | 0.147762 | 0.000260428 | 0.00279602 | 4.80614e-06 | 1(Win) | true |
| simdjson (reflection) | 10884.4 | 0.0465586 | 4904.1ms | 475954 | 160 | 60317.4 | 41702.4 | 0.0314679 | 0.456221 | 1.30829 | 0.183753 | 0.000273818 | 0.00370983 | 1.60205e-06 | 2(Loss) | true |
| Glaze | 8761.98 | 0.208924 | 5948.7ms | 475954 | 2560 | 2.99877e+07 | 51804 | 0.105805 | 0.57546 | 2.21522 | 0.322105 | 0.000261165 | 0.00100797 | 2.4638e-06 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2159.17 | 0.392828 | 7299.75ms | 631514 | 640 | 7.6838e+08 | 278930 | 0.309598 | 2.33027 | 7.12857 | 1.07055 | 0.0121015 | 0.03937 | 0.000143188 | 1(Win) | true |
| simdjson (reflection) | 2060.53 | 0.705207 | 7650.68ms | 631514 | 160 | 6.79766e+08 | 292283 | 0.682548 | 2.44309 | 7.88765 | 1.14835 | 0.00990408 | 0.0368318 | 0.00013526 | 2(Loss) | true |
| Jsonifier | 1947.67 | 0.0270949 | 8149.45ms | 631514 | 1280 | 8.98506e+06 | 309220 | 0.043139 | 2.59264 | 7.29255 | 1.33469 | 0.00963699 | 0.0264002 | 0.000288717 | 3(Loss) | true |
| Glaze | 1830.98 | 0.0633558 | 8580.48ms | 631514 | 320 | 1.38971e+07 | 328928 | 0.181041 | 2.73395 | 9.28801 | 1.71561 | 0.0107344 | 0.0209411 | 3.96814e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1490.87 | 0.599342 | 5245.76ms | 631514 | 160 | 9.37897e+08 | 403964 | 0.117365 | 3.37099 | 10.1108 | 2.05452 | 0.0106921 | 0.0500496 | 0.000119059 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2722.16 | 0.164154 | 6689ms | 631514 | 160 | 2.11037e+07 | 221243 | 0.0478917 | 1.84949 | 6.07669 | 0.833152 | 0.00947309 | 0.0147536 | 8.16589e-05 | 1(Win) | true |
| simdjson (reflection) | 2352.61 | 0.304625 | 7447.69ms | 631514 | 640 | 3.89205e+08 | 255996 | 0.623156 | 2.1292 | 7.1133 | 0.967306 | 0.00742122 | 0.0223807 | 5.30026e-05 | 2(Loss) | true |
| Jsonifier | 2327.34 | 0.22966 | 7538.39ms | 631514 | 640 | 2.26047e+08 | 258775 | 0.11683 | 2.16944 | 6.23465 | 1.09536 | 0.00746303 | 0.00640605 | 4.72302e-05 | 3(Loss) | true |
| Glaze | 2257.41 | 0.085085 | 7716.28ms | 631514 | 1280 | 6.59571e+07 | 266792 | 0.13221 | 2.23831 | 8.23282 | 1.47676 | 0.00629815 | 0.00548702 | 3.12196e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1740.99 | 0.354748 | 9798.64ms | 631514 | 320 | 4.81906e+08 | 345928 | 0.0885255 | 2.89456 | 9.11501 | 1.82989 | 0.00813683 | 0.0183452 | 2.94629e-05 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20969.8 | 0.0850593 | 4110.38ms | 716365 | 160 | 122870 | 32579.2 | 0.0972614 | 0.241474 | 0.716025 | 0.0983605 | 0.000184421 | 0.0076338 | 8.65481e-06 | 1(Win) | true |
| Glaze | 5078.95 | 0.473088 | 7325.3ms | 716365 | 1280 | 5.1834e+08 | 134512 | 0.305923 | 0.998999 | 2.70614 | 0.438118 | 0.000371069 | 0.0489601 | 6.66265e-05 | 2(Loss) | true |
| simdjson (reflection) | 515.275 | 0.378238 | 8467.05ms | 716365 | 160 | 4.02384e+09 | 1.32585e+06 | 0.0507152 | 9.7576 | 30.5979 | 6.83611 | 0.0701478 | 0.288981 | 0.000873882 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20989.1 | 0.122402 | 4092.61ms | 716365 | 80 | 126984 | 32549.3 | 0.130899 | 0.241003 | 0.715267 | 0.0981888 | 0.000177703 | 0.0075465 | 1.19527e-05 | 1(Win) | true |
| Glaze | 6543.64 | 0.170487 | 5744.81ms | 716365 | 1280 | 4.0553e+07 | 104403 | 0.104953 | 0.776612 | 2.69622 | 0.435824 | 0.000335361 | 0.00611656 | 2.53079e-05 | 2(Loss) | true |
| simdjson (reflection) | 510.571 | 0.361927 | 8481.27ms | 716365 | 160 | 3.75248e+09 | 1.33807e+06 | 0.0639609 | 9.78733 | 30.5956 | 6.83535 | 0.0704912 | 0.290488 | 0.000958066 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2393.64 | 0.114198 | 839.005ms | 2632 | 160 | 229.451 | 1048.64 | 0.24077 | 2.19536 | 8.22112 | 1.33093 | 0.000759878 | 4.03685e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2039.32 | 0.171735 | 868.962ms | 2632 | 2560 | 11438.2 | 1230.84 | 0.00660077 | 2.55753 | 10.2044 | 1.61854 | 0.00130218 | 5.46163e-05 | 1.12794e-05 | 2(Loss) | true |
| Glaze | 2017.17 | 0.159694 | 857.366ms | 2632 | 80 | 315.901 | 1244.35 | 0.028135 | 2.588 | 11.0171 | 2.11968 | 0.000617401 | 3.79939e-05 | 3.79939e-05 | 3(Loss) | true |
| simdjson (reflection) | 1770.82 | 0.0811301 | 877.284ms | 2632 | 160 | 211.596 | 1417.46 | 0.0441123 | 2.93796 | 9.48556 | 1.56155 | 0.00228438 | 0.00018997 | 5.46163e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1647.66 | 0.0708086 | 926.941ms | 2632 | 640 | 744.709 | 1523.41 | 0.0581211 | 3.15886 | 10.6071 | 1.96884 | 0.00254441 | 5.46163e-05 | 7.71752e-06 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2867 | 0.0520842 | 827.628ms | 2632 | 320 | 66.5392 | 875.503 | 0.0203413 | 1.84937 | 7.25342 | 1.07713 | 0.000762253 | 1.66223e-05 | 0 | 1(Win) | true |
| Glaze | 2558.61 | 0.0480059 | 835.581ms | 2632 | 640 | 141.949 | 981.028 | 0.0703486 | 2.05859 | 9.23366 | 1.68351 | 0.000978937 | 2.84954e-05 | 5.93655e-07 | 2(Loss) | true |
| Jsonifier (two-stage) | 2382.88 | 0.0878546 | 848.393ms | 2632 | 320 | 274.06 | 1053.38 | 0.12416 | 2.20742 | 9.23252 | 1.3636 | 0.00076819 | 4.39305e-05 | 4.74924e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2000.01 | 0.059585 | 864.531ms | 2632 | 2560 | 1431.6 | 1255.03 | 0.204596 | 2.61287 | 8.89894 | 1.57181 | 0.00180842 | 4.27432e-05 | 7.86593e-06 | 4(Loss) | true |
| simdjson (reflection) | 1979.04 | 0.0789316 | 866.906ms | 2632 | 2560 | 2565.7 | 1268.33 | 0.00113955 | 2.64343 | 8.59271 | 1.32409 | 0.0021094 | 4.11106e-05 | 7.12386e-06 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12339 | 0.520624 | 745.951ms | 2632 | 40 | 44.866 | 203.425 | 0.0859528 | 0.501938 | 1.73936 | 0.290274 | 0.000379939 | 1.8997e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 7229.56 | 0.1477 | 766.275ms | 2632 | 640 | 168.301 | 347.195 | 0.0454742 | 0.78154 | 2.73594 | 0.455927 | 0.000379939 | 4.92734e-05 | 2.55272e-05 | 2(Loss) | true |
| Glaze | 4556.26 | 0.0365544 | 783.148ms | 2632 | 4890 | 198.31 | 550.907 | 0.150254 | 1.19484 | 4.15274 | 0.68503 | 0.000389962 | 3.69839e-05 | 1.181e-05 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13723.7 | 0.242782 | 745.322ms | 2632 | 40 | 7.88718 | 182.9 | 0.218221 | 0.451966 | 1.52546 | 0.240502 | 0.000379939 | 0 | 0 | 1(Win) | true |
| simdjson (reflection) | 8122.62 | 0.0600042 | 762.525ms | 2632 | 2560 | 88.0202 | 309.022 | 0.0360129 | 0.705745 | 2.52356 | 0.406155 | 0.000379939 | 3.56193e-05 | 1.52866e-05 | 2(Loss) | true |
| Glaze | 5243.68 | 0.101088 | 772.38ms | 2632 | 2560 | 599.431 | 478.685 | 0.0980731 | 1.04563 | 3.59005 | 0.569529 | 0.000380681 | 1.91454e-05 | 5.49131e-06 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2515.96 | 0.306476 | 857.411ms | 3370 | 40 | 613.067 | 1277.4 | 0.0313038 | 2.11236 | 8.49377 | 1.29021 | 0.000608309 | 3.7092e-05 | 0 | 1(Win) | true |
| Jsonifier | 2282.66 | 0.0534867 | 875.299ms | 3370 | 4890 | 2773.17 | 1407.95 | 0.0298155 | 2.27687 | 8.32611 | 1.52255 | 0.00104677 | 4.22348e-05 | 1.72337e-05 | 2(Loss) | true |
| simdjson (reflection) | 2232.18 | 0.0697933 | 872.139ms | 3370 | 4890 | 4937.86 | 1439.8 | 0.0363463 | 2.34533 | 7.72107 | 1.23324 | 0.00170638 | 4.11425e-05 | 1.20758e-05 | 3(Loss) | true |
| Glaze | 2084.65 | 0.151677 | 887.563ms | 3370 | 640 | 3499.58 | 1541.69 | 0.152906 | 2.48694 | 10.6392 | 2.05697 | 0.000500742 | 5.79562e-05 | 1.7155e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2071.16 | 0.112781 | 907.414ms | 3370 | 1280 | 3920.3 | 1551.73 | 0.348453 | 2.52556 | 8.59703 | 1.55134 | 0.00195243 | 4.6365e-05 | 1.18231e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2945.58 | 0.201058 | 843.325ms | 3370 | 80 | 384.992 | 1091.09 | 0.373726 | 1.81714 | 7.6635 | 1.07745 | 0.000593472 | 5.19288e-05 | 2.59644e-05 | 1(Win) | true |
| Jsonifier | 2592.02 | 0.136842 | 861.986ms | 3370 | 80 | 230.309 | 1239.91 | 0.160037 | 2.01625 | 7.56944 | 1.32433 | 0.00102745 | 1.48368e-05 | 0 | 2(Loss) | true |
| simdjson (reflection) | 2515.78 | 0.0959291 | 863.847ms | 3370 | 160 | 240.289 | 1277.49 | 0.247919 | 2.113 | 7.02463 | 1.04807 | 0.00166172 | 2.7819e-05 | 1.8546e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2508.47 | 0.0904343 | 860.676ms | 3370 | 160 | 214.797 | 1281.21 | 0.0575295 | 2.08382 | 7.26291 | 1.24125 | 0.00140764 | 2.04006e-05 | 1.8546e-06 | 4(Loss) | true |
| Glaze | 2502.43 | 0.0688615 | 868.283ms | 3370 | 320 | 250.288 | 1284.31 | 0.0180091 | 2.08526 | 9.15015 | 1.69021 | 0.0010599 | 1.8546e-05 | 1.20549e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14676.1 | 0.176503 | 746.043ms | 3643 | 4890 | 853.706 | 236.727 | 0.455465 | 0.405135 | 1.30058 | 0.213835 | 0.000274667 | 2.53729e-05 | 7.29752e-06 | 1(Win) | true |
| Glaze | 4118.47 | 0.403309 | 816.754ms | 3682 | 640 | 7567.47 | 852.605 | 0.369534 | 1.3002 | 4.21564 | 0.702607 | 0.00027244 | 3.35246e-05 | 5.94106e-06 | 2(Loss) | true |
| simdjson (reflection) | 547.68 | 0.0589337 | 1376.91ms | 3643 | 4890 | 68344.1 | 6343.55 | 0.0414783 | 9.24841 | 36.0807 | 7.55861 | 0.0140967 | 0.000218364 | 0.000103232 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18444 | 0.175397 | 742.647ms | 3643 | 30 | 3.27471 | 188.367 | 0.373002 | 0.340864 | 1.13752 | 0.173758 | 0.000274499 | 9.14997e-06 | 9.14997e-06 | 1(Win) | true |
| Glaze | 4562.65 | 0.0967561 | 805.1ms | 3682 | 4890 | 2711.43 | 769.603 | 0.0887794 | 1.17372 | 3.92205 | 0.637154 | 0.000273758 | 3.12691e-05 | 1.18301e-05 | 2(Loss) | true |
| simdjson (reflection) | 545.406 | 0.0808168 | 1381.87ms | 3643 | 2560 | 67845.6 | 6369.99 | 0.0529363 | 9.29693 | 36.1073 | 7.56506 | 0.0144528 | 0.000215954 | 0.000105725 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1104.84 | 0.0497347 | 1126.96ms | 4630 | 2560 | 10114 | 3996.53 | 0.0212045 | 4.6753 | 21.73 | 4.43866 | 0.00491774 | 0.000159709 | 7.90531e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 916.162 | 0.0495621 | 1209.61ms | 4630 | 2560 | 14606.8 | 4819.57 | 0.0121641 | 5.58343 | 24.4181 | 4.75896 | 0.0056223 | 7.05319e-05 | 2.48043e-05 | 2(Loss) | true |
| Glaze | 770.369 | 0.11332 | 1303.37ms | 4630 | 1280 | 53999.2 | 5731.68 | 0.263678 | 6.59841 | 30.1328 | 5.74687 | 0.00542285 | 8.89241e-05 | 3.29036e-05 | 3(Loss) | true |
| simdjson (reflection) | 749.807 | 0.107387 | 1320.45ms | 4630 | 320 | 12797.3 | 5888.87 | 0.261609 | 6.78347 | 27.8104 | 5.11426 | 0.00949784 | 4.52214e-05 | 1.34989e-05 | 4(Loss) | true |
| simdjson (ondemand) | 671.766 | 0.0561006 | 1392.55ms | 4630 | 1280 | 17404.9 | 6572.99 | 0.0242292 | 7.58288 | 30.8244 | 5.94255 | 0.00684969 | 0.000230832 | 0.000114572 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1420.9 | 0.0712848 | 1126.57ms | 4630 | 640 | 3140.56 | 3107.54 | 0.0461366 | 3.67301 | 17.449 | 3.46739 | 0.00361231 | 3.88094e-05 | 8.09935e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1135.38 | 0.0967536 | 1203.72ms | 4630 | 320 | 4530.7 | 3889.03 | 0.12728 | 4.58401 | 20.103 | 3.78099 | 0.00405508 | 0.000116091 | 4.92711e-05 | 2(Loss) | true |
| Glaze | 909.672 | 0.0702224 | 1310.7ms | 4630 | 2560 | 29742.9 | 4853.96 | 0.0350589 | 5.60493 | 25.6907 | 4.73845 | 0.00426574 | 6.49636e-05 | 1.83923e-05 | 3(Loss) | true |
| simdjson (reflection) | 869.313 | 0.0306485 | 1339.34ms | 4630 | 4890 | 11850.5 | 5079.31 | 0.152609 | 5.87052 | 25.2689 | 4.52743 | 0.00622936 | 0.000123274 | 5.56078e-05 | 4(Loss) | true |
| simdjson (ondemand) | 747.481 | 0.0775524 | 1416.46ms | 4630 | 80 | 1678.96 | 5907.19 | 0.0590034 | 6.81579 | 27.8927 | 5.2743 | 0.00302106 | 4.31965e-05 | 0 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2090.32 | 0.0901408 | 936.355ms | 4630 | 1280 | 4640.77 | 2112.36 | 0.453181 | 2.50829 | 7.69287 | 0.4108 | 0.000219695 | 2.10921e-05 | 2.53105e-06 | 1(Win) | true |
| Glaze | 1473.15 | 0.0780056 | 1029.27ms | 4630 | 640 | 3498.62 | 2997.32 | 0.0900514 | 3.50269 | 9.97883 | 0.714039 | 0.000216658 | 5.73704e-05 | 1.68737e-05 | 2(Loss) | true |
| simdjson (reflection) | 1086.19 | 0.0289163 | 1121.22ms | 4630 | 80 | 110.541 | 4065.12 | 0 | 4.79023 | 15.3685 | 1.44384 | 0.000647948 | 6.2095e-05 | 3.23974e-05 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2113.73 | 0.0986638 | 931.807ms | 4630 | 80 | 339.834 | 2088.96 | 0.190048 | 2.47558 | 7.58315 | 0.385097 | 0.000431965 | 6.74946e-05 | 0 | 1(Win) | true |
| Glaze | 1623.37 | 0.141021 | 993.971ms | 4630 | 1280 | 18832.3 | 2719.97 | 0.0646967 | 3.15751 | 9.48315 | 0.60432 | 0.000254455 | 5.50081e-05 | 2.95289e-05 | 2(Loss) | true |
| simdjson (reflection) | 1091.88 | 0.0217422 | 1127.13ms | 4630 | 80 | 61.8456 | 4043.95 | 0.00803605 | 4.76789 | 15.2991 | 1.42743 | 0.00086933 | 1.88985e-05 | 2.69978e-06 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2216.45 | 0.0517399 | 1230.6ms | 11579 | 2560 | 17010.5 | 4982.12 | 0.130331 | 2.31206 | 10.7821 | 2.30771 | 0.0041596 | 4.54082e-05 | 2.48632e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2144.85 | 0.102828 | 1249.38ms | 11579 | 640 | 17937.1 | 5148.42 | 0.045757 | 2.37196 | 10.5071 | 1.92271 | 0.00316251 | 0.000186895 | 0.000113082 | 2(Loss) | true |
| simdjson (reflection) | 1780.84 | 0.0282932 | 1355.68ms | 11579 | 4890 | 15051 | 6200.79 | 0.0259364 | 2.8535 | 11.8459 | 2.06244 | 0.0044789 | 4.43649e-05 | 2.08579e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1606.11 | 0.0721505 | 1423.5ms | 11579 | 320 | 7874.49 | 6875.38 | 0.0854222 | 3.16514 | 13.0288 | 2.38881 | 0.0024125 | 2.69885e-05 | 1.13352e-05 | 4(Loss) | true |
| Glaze | 1472.12 | 0.053403 | 1475.37ms | 11579 | 1280 | 20540 | 7501.16 | 0.0228246 | 3.47862 | 15.2628 | 2.83522 | 0.00493728 | 4.56106e-05 | 1.8892e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2734.71 | 0.130635 | 1229.26ms | 11579 | 30 | 834.754 | 4037.93 | 0.173879 | 1.90511 | 9.08084 | 1.92236 | 0.0035812 | 0.000109393 | 5.18179e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2610.24 | 0.109348 | 1247.45ms | 11579 | 320 | 6847.81 | 4230.48 | 0.0381755 | 1.95534 | 8.8081 | 1.53787 | 0.00241412 | 1.56533e-05 | 3.77839e-06 | 2(Loss) | true |
| simdjson (reflection) | 2002.17 | 0.129746 | 1401.29ms | 11579 | 40 | 2048.28 | 5515.32 | 0.0464074 | 2.54561 | 10.9242 | 1.8455 | 0.0028651 | 3.02271e-05 | 4.31816e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1783.8 | 0.0483348 | 1449.58ms | 11579 | 4890 | 43780.5 | 6190.5 | 0.084338 | 2.85974 | 11.987 | 2.14647 | 0.00168186 | 5.64452e-05 | 2.7834e-05 | 4(Loss) | true |
| Glaze | 1668.34 | 0.0534453 | 1475.74ms | 11579 | 2560 | 32035.4 | 6618.89 | 0.0342886 | 3.08822 | 13.5416 | 2.44529 | 0.00469094 | 7.3375e-05 | 3.17452e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6079.19 | 0.209232 | 963.906ms | 14795 | 160 | 3773.25 | 2320.97 | 0.0272051 | 0.853848 | 2.48719 | 0.129976 | 6.75904e-05 | 1.4363e-05 | 0 | 1(Win) | true |
| Glaze | 3645.15 | 0.150381 | 1127.33ms | 14795 | 2560 | 86741.6 | 3870.79 | 0.0168155 | 1.39337 | 4.54566 | 0.521798 | 6.95442e-05 | 5.04288e-05 | 2.46335e-05 | 2(Loss) | true |
| simdjson (reflection) | 413.77 | 0.0428751 | 4165.1ms | 14795 | 4890 | 1.04528e+06 | 34100.1 | 0.110673 | 12.2286 | 43.0959 | 6.05766 | 0.00840245 | 0.000183061 | 0.000112803 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6303.3 | 0.219689 | 954.485ms | 14795 | 2560 | 61908.7 | 2238.45 | 0.324604 | 0.826978 | 2.4461 | 0.120581 | 6.84089e-05 | 5.15905e-05 | 3.11021e-05 | 1(Win) | true |
| Glaze | 4138.21 | 0.188959 | 1075.36ms | 14795 | 320 | 13282.8 | 3409.6 | 0.157669 | 1.24284 | 4.33721 | 0.47462 | 0.000197279 | 1.49966e-05 | 6.97026e-06 | 2(Loss) | true |
| simdjson (reflection) | 413.733 | 0.0446235 | 4155.25ms | 14795 | 4890 | 1.13247e+06 | 34103.2 | 0.101305 | 12.2573 | 43.0785 | 6.05408 | 0.0086222 | 0.000315684 | 0.000212751 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1731.62 | 0.0840909 | 908.583ms | 3223 | 80 | 178.239 | 1775.04 | 0.00352118 | 2.98774 | 11.5662 | 2.04561 | 0.00110146 | 6.2054e-05 | 2.32702e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1432.85 | 0.0731753 | 943.283ms | 3223 | 4890 | 12049.1 | 2145.16 | 0.176738 | 3.63977 | 14.1272 | 2.39497 | 0.00122103 | 0.000132801 | 5.13944e-05 | 2(Loss) | true |
| Glaze | 1349.51 | 0.0946264 | 961.307ms | 3223 | 2560 | 11891.3 | 2277.63 | 0.00475092 | 3.80605 | 14.6196 | 2.83339 | 0.00157001 | 0.000116715 | 5.99936e-05 | 3(Loss) | true |
| simdjson (reflection) | 1231.27 | 0.0781971 | 985.882ms | 3223 | 4890 | 18634 | 2496.36 | 0.0923909 | 4.1764 | 15.359 | 2.60658 | 0.00111196 | 0.00016351 | 7.84241e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1151.17 | 0.105799 | 996.418ms | 3223 | 1280 | 10214.4 | 2670.06 | 0.236919 | 4.45673 | 15.7322 | 2.72603 | 0.00225891 | 9.52626e-05 | 3.80565e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2127.41 | 0.100812 | 896.004ms | 3223 | 160 | 339.44 | 1444.81 | 0.0212011 | 2.49005 | 10.0689 | 1.65622 | 0.00108788 | 7.56283e-05 | 3.87837e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1661.41 | 0.0470102 | 939.359ms | 3223 | 4890 | 3698.8 | 1850.05 | 0.0169353 | 3.12136 | 12.6292 | 2.00528 | 0.00111634 | 0.000115923 | 4.49225e-05 | 2(Loss) | true |
| Glaze | 1574.99 | 0.117209 | 949.946ms | 3223 | 80 | 418.578 | 1951.56 | 0.103229 | 3.28017 | 13.0661 | 2.43376 | 0.00119066 | 5.81756e-05 | 7.75675e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1424.76 | 0.0489741 | 968.257ms | 3223 | 4890 | 5458.6 | 2157.34 | 0.102368 | 3.64159 | 14.1849 | 2.33509 | 0.00183821 | 0.000131849 | 5.39324e-05 | 4(Loss) | true |
| simdjson (reflection) | 1342.24 | 0.333292 | 989.314ms | 3223 | 40 | 2330.08 | 2289.97 | 0.0374682 | 3.83705 | 14.1112 | 2.27087 | 0.00268383 | 7.75675e-05 | 0 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7568.16 | 0.0760335 | 768.5ms | 3223 | 4890 | 466.293 | 406.135 | 0.266503 | 0.739384 | 2.07633 | 0.343779 | 0.000310333 | 6.49092e-05 | 3.55954e-05 | 1(Win) | true |
| simdjson (reflection) | 6084.62 | 0.113631 | 778.304ms | 3223 | 4890 | 1611.22 | 505.158 | 0.0181099 | 0.902674 | 2.6829 | 0.320509 | 0.000311158 | 4.89199e-05 | 2.47455e-05 | 2(Loss) | true |
| Glaze | 3402.2 | 0.122351 | 821.723ms | 3223 | 2560 | 3127.94 | 903.442 | 0.101755 | 1.55413 | 4.94663 | 0.755818 | 0.000310997 | 0.000106655 | 6.01148e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8127.65 | 0.0537921 | 765.842ms | 3223 | 2560 | 105.942 | 378.177 | 0.0630475 | 0.690017 | 1.97642 | 0.319888 | 0.000310634 | 4.64193e-05 | 2.23007e-05 | 1(Win) | true |
| simdjson (reflection) | 6604.76 | 0.673899 | 775.453ms | 3223 | 40 | 393.42 | 465.375 | 0.05548 | 0.848208 | 2.52249 | 0.283276 | 0.000318027 | 0.000279243 | 0.000124108 | 2(Loss) | true |
| Glaze | 4086.11 | 0.174321 | 804.487ms | 3223 | 640 | 1100.48 | 752.23 | 0.504476 | 1.31418 | 4.40242 | 0.633571 | 0.000312209 | 4.65405e-05 | 2.23007e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2422.52 | 0.123058 | 964.4ms | 5839 | 80 | 640.107 | 2298.64 | 0.00924375 | 2.16412 | 8.49752 | 1.35366 | 0.000648656 | 1.49854e-05 | 4.28156e-06 | 1(Win) | true |
| Jsonifier | 2159.47 | 0.0867303 | 990.896ms | 5839 | 1280 | 6402.29 | 2578.65 | 0.0643313 | 2.42236 | 8.8659 | 1.76828 | 0.000640761 | 6.30191e-05 | 3.29145e-05 | 2(Loss) | true |
| simdjson (reflection) | 2101.34 | 0.0681899 | 1001.02ms | 5839 | 1280 | 4179.61 | 2649.98 | 0.0468678 | 2.44424 | 9.11441 | 1.47371 | 0.000571454 | 4.02734e-05 | 1.08377e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1993.1 | 0.0381972 | 1010.68ms | 5839 | 4890 | 5569.21 | 2793.9 | 0.0391166 | 2.57783 | 9.27659 | 1.53057 | 0.0010731 | 6.64736e-05 | 2.84036e-05 | 4(Loss) | true |
| Glaze | 1752.92 | 0.0749753 | 1051.24ms | 5839 | 1280 | 7261.01 | 3176.69 | 0.00238548 | 2.91775 | 11.2009 | 2.14044 | 0.00166057 | 3.22455e-05 | 1.25771e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2788.13 | 0.104716 | 955.978ms | 5839 | 320 | 1399.69 | 1997.22 | 0.249718 | 1.88662 | 7.67066 | 1.13855 | 0.000603164 | 7.1716e-05 | 3.53228e-05 | 1(Win) | true |
| Jsonifier | 2454.64 | 0.126893 | 983.552ms | 5839 | 30 | 248.599 | 2268.57 | 0.0807494 | 2.14124 | 8.03939 | 1.55335 | 0.000799224 | 8.56311e-05 | 2.2835e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2428.63 | 0.0790694 | 983.033ms | 5839 | 160 | 525.885 | 2292.86 | 0.0160851 | 2.12067 | 8.42199 | 1.31427 | 0.000791017 | 5.35194e-05 | 3.21117e-06 | 3(Loss) | true |
| simdjson (reflection) | 2341.17 | 0.15341 | 1002.6ms | 5839 | 80 | 1065.14 | 2378.51 | 0.0173398 | 2.19961 | 8.44914 | 1.29217 | 0.000629389 | 4.06748e-05 | 4.28156e-06 | 4(Loss) | true |
| Glaze | 1970.9 | 0.078373 | 1037.72ms | 5839 | 2560 | 12552.2 | 2825.36 | 0.213757 | 2.60335 | 10.3408 | 1.91985 | 0.00141218 | 4.23473e-05 | 1.46509e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15132.4 | 0.0838387 | 779.441ms | 6938 | 640 | 86.0047 | 437.247 | 0.0906845 | 0.365709 | 1.04036 | 0.159988 | 0.000144134 | 1.23865e-05 | 4.50418e-07 | 1(Win) | true |
| Glaze | 3029.27 | 0.147861 | 953.07ms | 6960 | 4890 | 51328.8 | 2191.15 | 0.32822 | 1.70246 | 4.30421 | 0.71092 | 0.00033757 | 6.39647e-05 | 2.5533e-05 | 2(Loss) | true |
| simdjson (reflection) | 488.095 | 0.188107 | 2101.35ms | 6938 | 640 | 416152 | 13556 | 0.19724 | 10.3821 | 39.0824 | 7.32733 | 0.00775935 | 6.84635e-05 | 3.42318e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16355.4 | 0.0844576 | 773.978ms | 6938 | 80 | 9.33924 | 404.55 | 0.241591 | 0.340511 | 0.993946 | 0.14889 | 0.000144134 | 1.6215e-05 | 7.20669e-06 | 1(Win) | true |
| Glaze | 3375.29 | 0.527825 | 935.763ms | 6960 | 320 | 34476.8 | 1966.52 | 0.103239 | 1.5339 | 3.91135 | 0.627299 | 0.000413524 | 2.82866e-05 | 1.16739e-05 | 2(Loss) | true |
| simdjson (reflection) | 504.235 | 0.137002 | 2046.98ms | 6938 | 1280 | 413679 | 13122 | 0.0687124 | 10.1852 | 38.7287 | 7.25555 | 0.0079724 | 8.47912e-05 | 4.11006e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2024.83 | 0.189117 | 959.938ms | 4857 | 40 | 748.656 | 2287.6 | 0.0510256 | 2.58966 | 9.75685 | 1.73687 | 0.000488985 | 4.11777e-05 | 0 | 1(Win) | true |
| Glaze | 1807.97 | 0.0749886 | 982.683ms | 4857 | 4890 | 18049 | 2561.99 | 0.00676957 | 2.87942 | 11.4674 | 2.26539 | 0.000372031 | 8.04607e-05 | 3.49884e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1682.22 | 0.0407938 | 1008.21ms | 4857 | 4890 | 6169.78 | 2753.51 | 0.231982 | 3.09882 | 12.0465 | 1.97447 | 0.00104506 | 6.05034e-05 | 2.56413e-05 | 3(Loss) | true |
| simdjson (reflection) | 1509.69 | 0.0981056 | 1036.88ms | 4857 | 1280 | 11597.4 | 3068.18 | 0.0193227 | 3.41835 | 12.9135 | 2.19807 | 0.00114831 | 3.77998e-05 | 1.33506e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1258.3 | 0.0549246 | 1098.83ms | 4857 | 2560 | 10465 | 3681.15 | 0.0516728 | 4.12653 | 14.3801 | 2.73317 | 0.00197653 | 0.000124981 | 5.90321e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2664.95 | 0.0523375 | 925.734ms | 4857 | 4890 | 4046.64 | 1738.12 | 0.264128 | 1.9725 | 7.63661 | 1.24254 | 0.000438134 | 8.79131e-05 | 4.08408e-05 | 1(Win) | true |
| Glaze | 2568.12 | 0.285132 | 933.968ms | 4857 | 40 | 1057.93 | 1803.65 | 0.111935 | 2.05228 | 8.64484 | 1.61067 | 0.000936792 | 9.7797e-05 | 3.08833e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2060.47 | 0.311138 | 977.086ms | 4857 | 30 | 1467.69 | 2248.03 | 0.0845898 | 2.55158 | 10.1126 | 1.51554 | 0.00115298 | 0.000123533 | 6.86295e-05 | 3(Loss) | true |
| simdjson (reflection) | 1768.03 | 0.11928 | 1021.82ms | 4857 | 160 | 1562.46 | 2619.86 | 0.202232 | 2.95718 | 11.7313 | 1.90838 | 0.00153001 | 7.8495e-05 | 2.18756e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1544.12 | 0.0398091 | 1047.77ms | 4857 | 4890 | 6973.51 | 2999.77 | 0.00560104 | 3.36283 | 11.9693 | 2.20445 | 0.00238553 | 9.00604e-05 | 2.53887e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10225.1 | 0.420924 | 770.12ms | 4857 | 1280 | 4653.88 | 453.001 | 0.189202 | 0.547577 | 1.67037 | 0.276302 | 0.000207014 | 3.49045e-05 | 1.25463e-05 | 1(Win) | true |
| simdjson (reflection) | 7829.61 | 0.175065 | 783.553ms | 4857 | 30 | 32.1793 | 591.6 | 0.0563761 | 0.705785 | 2.06485 | 0.334569 | 0.000205888 | 3.43147e-05 | 1.37259e-05 | 2(Loss) | true |
| Glaze | 3769.99 | 0.133113 | 851.994ms | 4857 | 4890 | 13080 | 1228.65 | 0.309492 | 1.39977 | 3.69673 | 0.602636 | 0.000209846 | 7.84818e-05 | 3.28411e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11294.8 | 0.345817 | 771.639ms | 4857 | 40 | 80.4513 | 410.1 | 0.469218 | 0.493406 | 1.54766 | 0.245831 | 0.000211036 | 5.14721e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 8483.53 | 0.25963 | 778.946ms | 4857 | 4890 | 9826.54 | 545.998 | 0.033556 | 0.649983 | 1.94173 | 0.303891 | 0.000206309 | 5.57036e-05 | 3.34306e-05 | 2(Loss) | true |
| Glaze | 4754.59 | 0.424078 | 822.294ms | 4857 | 320 | 5461.99 | 974.216 | 0.00994489 | 1.12528 | 3.23286 | 0.496603 | 0.000208462 | 3.41003e-05 | 5.14721e-06 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2171.81 | 0.0956268 | 1022.69ms | 6701 | 1280 | 10134.5 | 2942.5 | 0.0267701 | 2.39806 | 9.24101 | 1.44844 | 0.00058655 | 4.94329e-05 | 2.4833e-05 | 1(Win) | true |
| Glaze | 2070.7 | 0.0565067 | 1032.43ms | 6701 | 2560 | 7785.5 | 3086.19 | 0.0423689 | 2.51646 | 10.4195 | 2.10775 | 0.000245649 | 6.54053e-05 | 3.44515e-05 | 2(Loss) | true |
| simdjson (reflection) | 2044.27 | 0.0754918 | 1042.66ms | 6701 | 2560 | 14257.5 | 3126.09 | 0.0201639 | 2.55047 | 9.82182 | 1.61871 | 0.000968605 | 0.00011717 | 6.38897e-05 | 3(Loss) | true |
| Jsonifier | 1975.44 | 0.0536578 | 1048.38ms | 6701 | 320 | 964.2 | 3235.01 | 0.0716254 | 2.64131 | 9.25131 | 1.79719 | 0.00149744 | 1.67885e-05 | 1.86539e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1710.32 | 0.0432417 | 1100.74ms | 6701 | 4890 | 12765.5 | 3736.47 | 0.199403 | 3.03202 | 10.8505 | 1.99985 | 0.00128321 | 7.09841e-05 | 3.43629e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2683.53 | 0.0475685 | 988.519ms | 6701 | 4890 | 6274.99 | 2381.4 | 0.109653 | 1.94463 | 7.77272 | 1.10297 | 0.000754 | 6.07302e-05 | 2.53907e-05 | 1(Win) | true |
| Glaze | 2675.01 | 0.0766782 | 984.16ms | 6701 | 2560 | 8590.4 | 2388.99 | 0.0124252 | 1.95679 | 8.42934 | 1.64632 | 0.000922145 | 2.94965e-05 | 8.62744e-06 | 2(Loss) | true |
| Jsonifier | 2405.64 | 0.0619444 | 1017.59ms | 6701 | 2560 | 6932.09 | 2656.5 | 0.0147464 | 2.16818 | 7.7475 | 1.44561 | 0.00147681 | 4.47111e-05 | 1.50397e-05 | 3(Loss) | true |
| simdjson (reflection) | 2345.88 | 0.163422 | 1031.72ms | 6701 | 80 | 1585.53 | 2724.16 | 0.30515 | 2.23086 | 8.90375 | 1.39606 | 0.00120877 | 0.000154828 | 6.71542e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2083.81 | 0.0504396 | 1053.73ms | 6701 | 2560 | 6125.57 | 3066.78 | 0.0755262 | 2.48951 | 9.03985 | 1.60364 | 0.00152426 | 8.70905e-05 | 2.86221e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14880.3 | 0.146905 | 771.375ms | 7376 | 80 | 38.5816 | 472.725 | 0.0264494 | 0.376144 | 1.15415 | 0.180721 | 0.000135575 | 2.37256e-05 | 8.47343e-06 | 1(Win) | true |
| Glaze | 3434.76 | 0.575318 | 933.311ms | 7376 | 160 | 22211.8 | 2047.97 | 0.0542925 | 1.52608 | 4.12107 | 0.686145 | 0.000148285 | 2.9657e-05 | 1.69469e-06 | 2(Loss) | true |
| simdjson (reflection) | 523.688 | 0.0653576 | 2083.87ms | 7376 | 4890 | 376875 | 13432.2 | 0.251498 | 9.77704 | 39.4154 | 8.02847 | 0.0127122 | 0.000155149 | 9.32389e-05 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15978.7 | 0.16312 | 763.423ms | 7376 | 1280 | 660.055 | 440.229 | 0.161932 | 0.35208 | 1.07335 | 0.161876 | 0.000135893 | 4.56506e-05 | 2.74327e-05 | 1(Win) | true |
| Glaze | 3922.64 | 0.131385 | 908.742ms | 7376 | 4890 | 27144.6 | 1793.26 | 0.259411 | 1.33525 | 3.79799 | 0.61307 | 0.00015745 | 4.45817e-05 | 2.08491e-05 | 2(Loss) | true |
| simdjson (reflection) | 524.764 | 0.129297 | 2086.05ms | 7376 | 1280 | 384507 | 13404.7 | 0.128519 | 9.76098 | 39.4227 | 8.03037 | 0.012254 | 0.000113014 | 6.16442e-05 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2143.74 | 0.115243 | 796.333ms | 1691 | 30 | 22.5471 | 752.267 | 0.0221602 | 2.54177 | 8.88232 | 1.44412 | 0.000591366 | 7.88488e-05 | 0 | 1(Win) | true |
| Glaze | 1973.89 | 0.102483 | 806.022ms | 1691 | 4890 | 3428.09 | 816.997 | 0.114897 | 2.72876 | 10.0727 | 1.97575 | 0.0011242 | 0.000160237 | 6.65136e-05 | 2(Loss) | true |
| simdjson (reflection) | 1828.68 | 0.282444 | 821.393ms | 1691 | 40 | 248.163 | 881.875 | 0.25864 | 2.94509 | 9.87226 | 1.64281 | 0.0015819 | 0.000221762 | 7.39208e-05 | 3(Loss) | true |
| Jsonifier (two-stage) | 1725.17 | 0.125076 | 819.859ms | 1691 | 160 | 218.722 | 934.788 | 0.160207 | 3.06276 | 10.4181 | 1.65405 | 0.000591366 | 0.00017741 | 4.06564e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1568.74 | 0.203041 | 830.133ms | 1691 | 80 | 348.532 | 1028 | 0.024325 | 3.41445 | 10.6268 | 1.71023 | 0.000591366 | 0.000162626 | 2.95683e-05 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2655.08 | 0.0460324 | 792.287ms | 1691 | 320 | 25.0155 | 607.388 | 0.0257183 | 2.07049 | 7.37138 | 1.06919 | 0.000591366 | 3.14163e-05 | 0 | 1(Win) | true |
| Glaze | 2461.54 | 0.154966 | 795.785ms | 1691 | 160 | 164.916 | 655.144 | 0.356471 | 2.24264 | 8.57363 | 1.60201 | 0.00130101 | 3.69604e-05 | 3.69604e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2133.84 | 0.305722 | 809.229ms | 1691 | 640 | 3416.6 | 755.755 | 0.28883 | 2.53867 | 8.90834 | 1.27853 | 0.000605226 | 8.13128e-05 | 2.49483e-05 | 3(Loss) | true |
| simdjson (reflection) | 2054.17 | 0.2804 | 816.323ms | 1691 | 30 | 145.375 | 785.067 | 0.57413 | 2.64098 | 9.01183 | 1.40568 | 0.00118273 | 0.000512517 | 0.000236546 | 4(Loss) | true |
| simdjson (ondemand) | 1827.6 | 0.090012 | 825.376ms | 1691 | 640 | 403.745 | 882.395 | 0.589528 | 2.94821 | 9.27025 | 1.3696 | 0.000593214 | 8.13128e-05 | 2.95683e-05 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8630.36 | 0.170491 | 744.295ms | 1996 | 80 | 11.3125 | 220.562 | 0.243103 | 0.705029 | 1.46693 | 0.248998 | 0.000507265 | 1.25251e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6710.43 | 0.0391273 | 755.468ms | 1996 | 1280 | 15.7685 | 283.668 | 0.168006 | 0.878466 | 1.87926 | 0.273547 | 0.000502568 | 3.36611e-05 | 7.43675e-06 | 2(Loss) | true |
| Glaze | 5355.14 | 0.262309 | 761.418ms | 1996 | 320 | 278.199 | 355.459 | 0.277914 | 1.07398 | 3.45541 | 0.568637 | 0.000501002 | 2.50501e-05 | 1.56563e-06 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10106.2 | 0.0638677 | 743.244ms | 1996 | 640 | 9.26165 | 188.353 | 0.204489 | 0.61708 | 1.30611 | 0.210421 | 0.000501002 | 2.42673e-05 | 8.61097e-06 | 1(Win) | true |
| simdjson (reflection) | 7662.89 | 0.1679 | 746.674ms | 1996 | 320 | 55.6657 | 248.409 | 0.175169 | 0.783234 | 1.71743 | 0.233968 | 0.000501002 | 1.09594e-05 | 3.13126e-06 | 2(Loss) | true |
| Glaze | 6001.47 | 0.243959 | 755.319ms | 1996 | 2560 | 1532.78 | 317.178 | 0.287532 | 0.966448 | 2.96068 | 0.462978 | 0.000505895 | 4.38377e-05 | 1.70262e-05 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2260.71 | 0.587717 | 824.004ms | 2158 | 320 | 9160.1 | 910.347 | 0.132336 | 2.40627 | 8.08156 | 1.31511 | 0.00077763 | 0.000140466 | 7.2405e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2123.81 | 0.173031 | 828.791ms | 2158 | 80 | 224.911 | 969.025 | 0.0721854 | 2.52796 | 8.74189 | 1.34106 | 0.00139597 | 4.63392e-05 | 0 | 2(Loss) | true |
| Glaze | 2008.53 | 0.0815316 | 822.83ms | 2158 | 2560 | 1786.65 | 1024.65 | 0.0549653 | 2.66345 | 9.71733 | 1.89852 | 0.000477873 | 8.59809e-05 | 3.20392e-05 | 3(Loss) | true |
| Jsonifier | 1979.15 | 0.322084 | 826.102ms | 2158 | 4890 | 54851.8 | 1039.85 | 0.206138 | 2.69951 | 8.66172 | 1.52641 | 0.000471826 | 8.23492e-05 | 3.00399e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1896.23 | 0.209921 | 843.054ms | 2158 | 80 | 415.26 | 1085.33 | 0.204588 | 2.82913 | 8.6367 | 1.36098 | 0.000474977 | 5.7924e-05 | 0 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2688.25 | 0.0606438 | 809.067ms | 2158 | 640 | 137.949 | 765.566 | 0.121087 | 2.01623 | 7.34662 | 1 | 0.000463392 | 5.21316e-05 | 3.62025e-06 | 1(Win) | true |
| simdjson (reflection) | 2543.31 | 0.232413 | 811.632ms | 2158 | 2560 | 9054.55 | 809.193 | 0.0756354 | 2.12089 | 7.32947 | 1.1126 | 0.000465564 | 0.000105711 | 3.72886e-05 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2445.92 | 0.114747 | 820.498ms | 2158 | 80 | 74.5745 | 841.413 | 0.0520229 | 2.20868 | 8.49861 | 1.59546 | 0.000463392 | 3.47544e-05 | 0 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 2444.29 | 0.110695 | 823.781ms | 2158 | 80 | 69.493 | 841.975 | 0.33665 | 2.20949 | 7.43513 | 1.22289 | 0.000469184 | 4.63392e-05 | 0 | 3(Tie) | true |
| simdjson (ondemand) | 2245.66 | 0.23212 | 822.878ms | 2158 | 4890 | 22128.2 | 916.446 | 0.33138 | 2.37655 | 7.53197 | 1.08434 | 0.000467846 | 7.69477e-05 | 3.23142e-05 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11332 | 0.0773803 | 751.555ms | 2866 | 2560 | 89.1743 | 241.196 | 0.178304 | 0.531963 | 1.13084 | 0.185276 | 0.000348918 | 2.65778e-05 | 1.43111e-05 | 1(Win) | true |
| Glaze | 3740.31 | 0.809841 | 805.197ms | 2866 | 80 | 2801.73 | 730.75 | 0.405331 | 1.45437 | 4.08758 | 0.682484 | 0.000348918 | 5.23378e-05 | 3.48918e-05 | 2(Loss) | true |
| simdjson (reflection) | 555.987 | 0.0740229 | 1228.22ms | 2866 | 4890 | 64753.8 | 4916 | 0.0183192 | 9.3144 | 34.8503 | 7.30461 | 0.00900509 | 0.000160617 | 7.89883e-05 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14324.6 | 0.265304 | 737.142ms | 2866 | 640 | 164.003 | 190.806 | 0.172264 | 0.435375 | 0.963015 | 0.146546 | 0.000348918 | 2.88948e-05 | 8.72296e-06 | 1(Win) | true |
| Glaze | 4508.61 | 0.253936 | 783.266ms | 2866 | 4890 | 11588.5 | 606.225 | 0.644217 | 1.223 | 3.3709 | 0.529658 | 0.000349489 | 3.03252e-05 | 1.44134e-05 | 2(Loss) | true |
| simdjson (reflection) | 534.934 | 0.258902 | 1243.47ms | 2866 | 320 | 55997.9 | 5109.48 | 0.032793 | 9.70135 | 35.7449 | 7.47767 | 0.00839803 | 0.000380539 | 0.000203899 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2264.4 | 0.0705767 | 903.708ms | 4390 | 2560 | 4358.98 | 1848.89 | 0.0574339 | 2.32245 | 10.5599 | 1.71595 | 0.000942839 | 5.9528e-05 | 2.87407e-05 | 1(Win) | true |
| Glaze | 1857.27 | 0.0371717 | 946.962ms | 4390 | 640 | 449.35 | 2254.19 | 0.0436185 | 2.82351 | 13.1419 | 2.61298 | 0.000631763 | 2.98975e-05 | 8.18622e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1698.56 | 0.125937 | 973.712ms | 4390 | 80 | 770.838 | 2464.81 | 0.100006 | 3.08457 | 14.0483 | 2.25285 | 0.00321185 | 7.97267e-05 | 8.54214e-06 | 3(Loss) | true |
| simdjson (reflection) | 1462.63 | 0.0711932 | 1010.41ms | 4390 | 2560 | 10631.1 | 2862.41 | 0.108142 | 3.57114 | 13.8018 | 2.22642 | 0.00253684 | 4.94732e-05 | 1.28132e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1103.18 | 0.0809677 | 1100.74ms | 4390 | 640 | 6042.81 | 3795.05 | 0.012765 | 4.69538 | 17.7738 | 3.16993 | 0.00242561 | 6.94049e-05 | 2.38468e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2616.22 | 0.120054 | 902.068ms | 4390 | 1280 | 4724.4 | 1600.26 | 0.142024 | 2.01962 | 9.39385 | 1.44465 | 0.000944085 | 3.25669e-05 | 1.28132e-05 | 1(Win) | true |
| Glaze | 2163.23 | 0.0848668 | 934.352ms | 4390 | 4890 | 13191.9 | 1935.36 | 0.00242902 | 2.42327 | 11.6973 | 2.28428 | 0.000603575 | 3.47509e-05 | 1.2065e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1886.54 | 0.0550395 | 971.073ms | 4390 | 2560 | 3819.32 | 2219.21 | 0.0277154 | 2.78066 | 12.8804 | 1.98087 | 0.0031791 | 9.90354e-05 | 4.5736e-05 | 3(Loss) | true |
| simdjson (reflection) | 1602.64 | 0.0834319 | 1001.87ms | 4390 | 4890 | 23229 | 2612.33 | 0.0853404 | 3.25201 | 12.7442 | 1.97791 | 0.00253667 | 4.50457e-05 | 1.50463e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1214.28 | 0.101029 | 1091.74ms | 4390 | 30 | 364.006 | 3447.83 | 0.0793397 | 4.29399 | 16.4374 | 2.87403 | 0.00309795 | 8.35232e-05 | 0 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13391 | 0.0548568 | 747.727ms | 4390 | 1280 | 37.6507 | 312.645 | 0.0571908 | 0.434583 | 1.75262 | 0.279043 | 0.000227968 | 2.72281e-05 | 8.54214e-06 | 1(Win) | true |
| simdjson (reflection) | 8272.95 | 0.21247 | 772.825ms | 4390 | 80 | 92.4897 | 506.062 | 0.131084 | 0.672483 | 2.52346 | 0.390888 | 0.00022779 | 1.99317e-05 | 5.69476e-06 | 2(Loss) | true |
| Glaze | 3813.33 | 0.154557 | 835.695ms | 4390 | 4890 | 14080.1 | 1097.89 | 0.126996 | 1.39603 | 4.77084 | 0.754215 | 0.000231657 | 6.90359e-05 | 3.47043e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14332.3 | 0.109818 | 745.868ms | 4390 | 160 | 16.4653 | 292.113 | 0.34351 | 0.409066 | 1.67859 | 0.261503 | 0.00022779 | 1.99317e-05 | 2.84738e-06 | 1(Win) | true |
| simdjson (reflection) | 8693.62 | 0.0975467 | 770.428ms | 4390 | 4890 | 1079.1 | 481.575 | 0.652004 | 0.642041 | 2.4098 | 0.364693 | 0.000227977 | 3.12571e-05 | 1.44873e-05 | 2(Loss) | true |
| Glaze | 4194.83 | 0.246789 | 823.015ms | 4390 | 4890 | 29666.1 | 998.045 | 0.405622 | 1.27822 | 4.36743 | 0.663098 | 0.000231843 | 3.64278e-05 | 1.7981e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3198.07 | 0.0831927 | 1009.17ms | 9378 | 160 | 866.035 | 2796.55 | 0.0782826 | 1.63417 | 7.43549 | 1.11175 | 0.00173611 | 1.73278e-05 | 6.66453e-07 | 1(Win) | true |
| Jsonifier | 3041.27 | 0.0994821 | 1025.88ms | 9378 | 640 | 5477.48 | 2940.73 | 0.00196596 | 1.71424 | 7.50299 | 1.4534 | 0.00272863 | 1.23294e-05 | 3.33227e-07 | 2(Loss) | true |
| simdjson (reflection) | 2882.9 | 0.0452929 | 1035.14ms | 9378 | 4890 | 9654.52 | 3102.28 | 0.0707841 | 1.80669 | 7.16272 | 1.07262 | 0.00110924 | 3.05942e-05 | 1.07941e-05 | 3(Loss) | true |
| Glaze | 2224.99 | 0.0334614 | 1126.79ms | 9378 | 320 | 578.895 | 4019.59 | 0.0569412 | 2.33886 | 9.4982 | 1.81542 | 0.00365017 | 3.33227e-05 | 1.49952e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2221.77 | 0.0582185 | 1135.61ms | 9378 | 160 | 878.748 | 4025.42 | 0.154249 | 2.34234 | 9.04905 | 1.51962 | 0.00127692 | 2.7991e-05 | 1.19962e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3470.85 | 0.0818208 | 1011.97ms | 9378 | 4890 | 21736.3 | 2576.77 | 0.0640228 | 1.50083 | 6.88878 | 0.984432 | 0.00162862 | 2.32455e-05 | 5.32072e-06 | 1(Win) | true |
| Jsonifier | 3320.62 | 0.104876 | 1022.26ms | 9378 | 4890 | 39016 | 2693.34 | 0.0572984 | 1.56602 | 6.95628 | 1.3264 | 0.0026782 | 2.29838e-05 | 1.01181e-05 | 2(Loss) | true |
| simdjson (reflection) | 3173.3 | 0.142712 | 1024.66ms | 9378 | 40 | 647.112 | 2818.38 | 0.206514 | 1.64699 | 6.656 | 0.953935 | 0.00110898 | 2.66581e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2438.77 | 0.0299879 | 1119.3ms | 9378 | 320 | 387.009 | 3667.24 | 0.0528606 | 2.13615 | 8.39646 | 1.37577 | 0.00130292 | 1.66613e-05 | 5.33163e-06 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 2435.64 | 0.144349 | 1119.64ms | 9378 | 640 | 17980.6 | 3671.96 | 0.0925942 | 2.1349 | 8.81926 | 1.66112 | 0.00393741 | 1.34957e-05 | 2.4992e-06 | 4(Tie) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23767.1 | 0.0667312 | 764.862ms | 11521 | 2560 | 243.626 | 462.289 | 0.00650593 | 0.235808 | 0.745769 | 0.111883 | 8.68997e-05 | 1.83768e-05 | 7.18796e-06 | 1(Win) | true |
| Glaze | 5860.32 | 0.0815196 | 915.222ms | 11521 | 4890 | 11422.7 | 1874.86 | 0.13167 | 0.891551 | 3.91028 | 0.664873 | 0.000255637 | 2.34301e-05 | 8.30705e-06 | 2(Loss) | true |
| simdjson (reflection) | 522.018 | 0.229021 | 2857.57ms | 11521 | 1280 | 2.97419e+06 | 21047.7 | 0.244473 | 9.71486 | 38.0656 | 7.00417 | 0.0104523 | 9.07989e-05 | 5.0587e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 29838.9 | 0.485576 | 759.728ms | 11521 | 4890 | 15632.9 | 368.22 | 0.301745 | 0.190213 | 0.693256 | 0.0993838 | 8.7366e-05 | 1.83536e-05 | 9.60281e-06 | 1(Win) | true |
| Glaze | 7120.35 | 0.0985005 | 875.072ms | 11521 | 4890 | 11297 | 1543.08 | 0.194583 | 0.736993 | 3.64795 | 0.607847 | 0.000255832 | 2.44419e-05 | 1.28511e-05 | 2(Loss) | true |
| simdjson (reflection) | 518.508 | 0.163961 | 2856.38ms | 11521 | 2560 | 3.09024e+06 | 21190.2 | 0.0540089 | 9.77634 | 38.0693 | 7.00504 | 0.011036 | 0.000116025 | 7.37444e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3283.28 | 0.141587 | 855.323ms | 4669 | 40 | 147.481 | 1356.17 | 0.0325777 | 1.61549 | 6.79824 | 1.38231 | 0.000481902 | 1.60634e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2216.97 | 0.0277675 | 921.474ms | 4669 | 640 | 199.06 | 2008.47 | 0.0337747 | 2.37048 | 9.67016 | 1.71022 | 0.00109833 | 2.40951e-05 | 4.3505e-06 | 2(Loss) | true |
| Glaze | 2130.16 | 0.162407 | 928.831ms | 4669 | 160 | 1843.96 | 2090.31 | 0.131983 | 2.46688 | 9.56672 | 1.81174 | 0.000963804 | 0.000133862 | 7.89784e-05 | 3(Loss) | true |
| simdjson (reflection) | 1667.14 | 0.121467 | 995.141ms | 4669 | 1280 | 13472 | 2670.87 | 0.0489126 | 3.1311 | 12.6492 | 1.97987 | 0.00128139 | 9.57111e-05 | 5.00308e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1340.92 | 0.0475998 | 1055.31ms | 4669 | 2560 | 6395.81 | 3320.64 | 0.00249393 | 3.86549 | 14.9235 | 2.67188 | 0.00149473 | 5.12857e-05 | 1.92426e-05 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3639.39 | 0.0557567 | 844.327ms | 4669 | 4890 | 2275.59 | 1223.48 | 0.152904 | 1.46229 | 6.29921 | 1.26087 | 0.000519153 | 5.44863e-05 | 2.54912e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2353.22 | 0.0979419 | 917.409ms | 4669 | 40 | 137.379 | 1892.17 | 0.665455 | 2.23647 | 9.17113 | 1.58856 | 0.0011994 | 2.14179e-05 | 5.35447e-06 | 2(Loss) | true |
| Glaze | 2339.71 | 0.0416855 | 917.679ms | 4669 | 640 | 402.785 | 1903.1 | 0.0921986 | 2.24887 | 8.88263 | 1.65282 | 0.00099158 | 1.80713e-05 | 2.34258e-06 | 3(Loss) | true |
| simdjson (reflection) | 1712.07 | 0.0595253 | 991.001ms | 4669 | 4890 | 11719.7 | 2600.78 | 0.103434 | 3.04702 | 12.3804 | 1.90876 | 0.0012573 | 4.35365e-05 | 2.08047e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1444.26 | 0.0332297 | 1036.96ms | 4669 | 4890 | 5132.38 | 3083.03 | 0.0913743 | 3.61195 | 14.1311 | 2.51296 | 0.00149075 | 4.30547e-05 | 1.45852e-05 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12187.9 | 0.0585765 | 760.405ms | 4669 | 640 | 29.31 | 365.337 | 0.0555684 | 0.468333 | 1.25958 | 0.318269 | 0.000214513 | 2.14179e-05 | 5.01981e-06 | 1(Win) | true |
| simdjson (reflection) | 8326.32 | 0.164853 | 810.776ms | 4669 | 80 | 62.1766 | 534.775 | 0.0373849 | 0.665324 | 1.64575 | 0.218034 | 0.000214179 | 3.4804e-05 | 1.07089e-05 | 2(Loss) | true |
| Glaze | 3909.31 | 0.277974 | 840.639ms | 4669 | 4890 | 49019 | 1139 | 0.163269 | 1.36109 | 3.46932 | 0.501403 | 0.000217639 | 5.54499e-05 | 2.44838e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13548.3 | 0.0425739 | 755.453ms | 4669 | 320 | 6.26488 | 328.653 | 0.0694603 | 0.426256 | 1.14971 | 0.292782 | 0.000214179 | 1.13782e-05 | 4.01585e-06 | 1(Win) | true |
| simdjson (reflection) | 8769.15 | 0.0260096 | 807.584ms | 4669 | 1280 | 22.326 | 507.77 | 0.0601228 | 0.635118 | 1.57721 | 0.201542 | 0.000214346 | 2.45971e-05 | 1.12109e-05 | 2(Loss) | true |
| Glaze | 4592.54 | 0.189786 | 823.231ms | 4669 | 640 | 2166.97 | 969.552 | 0.00112811 | 1.16874 | 2.95716 | 0.386378 | 0.000214513 | 7.69704e-06 | 3.34654e-06 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3374.69 | 0.0571256 | 952.07ms | 7932 | 4890 | 8018.03 | 2241.55 | 0.381936 | 1.54763 | 6.40545 | 1.04564 | 0.000659981 | 4.18692e-05 | 2.12955e-05 | 1(Win) | true |
| Jsonifier | 2821.65 | 0.0511161 | 992.551ms | 7932 | 4890 | 9183.01 | 2680.9 | 0.113142 | 1.83118 | 6.55774 | 1.45411 | 0.00107001 | 3.34386e-05 | 1.43345e-05 | 2(Loss) | true |
| simdjson (reflection) | 2635.82 | 0.0504686 | 1019.57ms | 7932 | 4890 | 10258.6 | 2869.91 | 0.372198 | 1.96095 | 8.02496 | 1.18898 | 0.00070992 | 2.30487e-05 | 7.83758e-06 | 3(Loss) | true |
| Glaze | 2399.72 | 0.0972432 | 1042.01ms | 7932 | 1280 | 12027.4 | 3152.26 | 0.0488231 | 2.16903 | 8.47839 | 1.65004 | 0.00176678 | 3.64426e-05 | 1.80243e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2166.15 | 0.0932091 | 1081.58ms | 7932 | 640 | 6780.89 | 3492.17 | 0.072133 | 2.38067 | 9.36372 | 1.59632 | 0.000795433 | 1.41831e-05 | 5.90961e-07 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3633.79 | 0.123409 | 949.635ms | 7932 | 40 | 263.999 | 2081.72 | 0.0332367 | 1.47201 | 6.14183 | 0.980585 | 0.000658724 | 2.83661e-05 | 0 | 1(Win) | true |
| Jsonifier | 2991.97 | 0.155161 | 986.634ms | 7932 | 640 | 9849.04 | 2528.28 | 0.00673675 | 1.73442 | 6.29501 | 1.38944 | 0.000969372 | 2.40324e-05 | 4.92467e-06 | 2(Loss) | true |
| simdjson (reflection) | 2700.76 | 0.0744419 | 1013.14ms | 7932 | 2560 | 11129.3 | 2800.89 | 0.138255 | 1.92166 | 7.86674 | 1.14713 | 0.000774996 | 0.000119423 | 7.74651e-05 | 3(Loss) | true |
| Glaze | 2550.1 | 0.129677 | 1026.55ms | 7932 | 40 | 591.881 | 2966.38 | 0.231788 | 2.04919 | 8.07526 | 1.55648 | 0.00223147 | 2.20625e-05 | 3.15179e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2338.62 | 0.0569373 | 1064.77ms | 7932 | 80 | 271.351 | 3234.62 | 0.0301517 | 2.23131 | 8.89725 | 1.50277 | 0.000803707 | 5.67322e-05 | 3.46697e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21007.1 | 0.0798841 | 768.078ms | 9249 | 320 | 36.0023 | 419.884 | 0.0513271 | 0.268229 | 0.719537 | 0.162937 | 0.00017806 | 1.52043e-05 | 3.04087e-06 | 1(Win) | true |
| Glaze | 2972.79 | 0.182203 | 1023.68ms | 9249 | 2560 | 74819.3 | 2967.09 | 0.264543 | 1.74319 | 3.79046 | 0.62396 | 0.000327696 | 2.20463e-05 | 5.95504e-06 | 2(Loss) | true |
| simdjson (reflection) | 522.51 | 0.176265 | 2425.51ms | 9249 | 640 | 566645 | 16881.1 | 0.183946 | 9.80367 | 40.8551 | 8.30068 | 0.0142196 | 7.55149e-05 | 3.93624e-05 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24152.2 | 0.371776 | 762.785ms | 9249 | 4890 | 9014.66 | 365.206 | 0.209072 | 0.236219 | 0.657152 | 0.1478 | 0.000108695 | 1.0414e-05 | 1.94571e-06 | 1(Win) | true |
| Glaze | 2964.26 | 0.201417 | 1028.61ms | 9249 | 2560 | 91957.7 | 2975.63 | 0.260496 | 1.75739 | 3.52752 | 0.565359 | 0.000339479 | 1.66825e-05 | 8.57356e-06 | 2(Loss) | true |
| simdjson (reflection) | 526.317 | 0.0686576 | 2419.39ms | 9249 | 4890 | 647411 | 16759 | 0.243974 | 9.74524 | 40.8871 | 8.30856 | 0.0134386 | 0.000109999 | 6.15332e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 865.307 | 0.09155 | 1230.26ms | 4604 | 640 | 13811.1 | 5074.17 | 0.0959512 | 5.995 | 23.9126 | 5.12067 | 0.00669798 | 9.06141e-05 | 5.32825e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 752.81 | 0.0837968 | 1303.08ms | 4604 | 30 | 716.599 | 5832.43 | 0.0542646 | 6.89206 | 27.8065 | 5.54887 | 0.00458297 | 7.24008e-05 | 0 | 2(Loss) | true |
| Glaze | 654.508 | 0.0734098 | 1394.84ms | 4604 | 1280 | 31042.7 | 6708.43 | 0.0830122 | 7.89547 | 33.6911 | 6.93245 | 0.00431062 | 4.34405e-05 | 7.63602e-06 | 3(Loss) | true |
| simdjson (reflection) | 625.208 | 0.0366402 | 1430.21ms | 4604 | 4890 | 32377.8 | 7022.81 | 0.087655 | 8.26151 | 31.2866 | 6.03535 | 0.00524373 | 8.21283e-05 | 4.3174e-05 | 4(Loss) | true |
| simdjson (ondemand) | 497.868 | 0.0623155 | 1609.79ms | 4604 | 640 | 19329.2 | 8819.05 | 0.0140518 | 10.3873 | 37.8301 | 7.69483 | 0.00662976 | 5.39612e-05 | 2.10415e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1067.01 | 0.0724686 | 1216.23ms | 4604 | 1280 | 11382.6 | 4114.97 | 0.0165012 | 4.87183 | 19.6227 | 4.13081 | 0.00478626 | 5.87125e-05 | 1.34055e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 893.371 | 0.0759021 | 1297.62ms | 4604 | 40 | 556.64 | 4914.77 | 0.0395223 | 5.81685 | 23.4844 | 4.55387 | 0.00330691 | 9.2311e-05 | 0 | 2(Loss) | true |
| Glaze | 760.358 | 0.0565215 | 1385.51ms | 4604 | 1280 | 13635.6 | 5774.54 | 0.0707348 | 6.81705 | 29.1901 | 5.89346 | 0.00451425 | 3.83498e-05 | 1.05207e-05 | 3(Loss) | true |
| simdjson (reflection) | 720.78 | 0.0530987 | 1423.99ms | 4604 | 1280 | 13391.9 | 6091.62 | 0.13676 | 7.1905 | 27.1212 | 5.09514 | 0.00484277 | 9.01051e-05 | 3.15622e-05 | 4(Loss) | true |
| simdjson (ondemand) | 542.789 | 0.0705639 | 1638.2ms | 4604 | 1280 | 41704.6 | 8089.18 | 0.0964602 | 9.51701 | 33.0174 | 6.61569 | 0.0160504 | 7.00817e-05 | 1.54417e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1522.15 | 0.0675108 | 1031.9ms | 4918 | 80 | 346.177 | 3081.28 | 0.022723 | 3.42895 | 11.3817 | 1.34994 | 0.00075488 | 4.06669e-05 | 0 | 1(Win) | true |
| Jsonifier | 1412.53 | 0.131624 | 1034.96ms | 4604 | 4890 | 81857.8 | 3108.42 | 0.0828801 | 3.68754 | 9.5745 | 0.570157 | 0.000622292 | 5.40563e-05 | 2.59843e-05 | 2(Loss) | true |
| Glaze | 1250.17 | 0.0842623 | 1073.21ms | 4604 | 2560 | 22420.1 | 3512.09 | 0.0320759 | 4.15584 | 12.8553 | 1.10686 | 0.000455192 | 7.20332e-05 | 3.41924e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1539.37 | 0.100024 | 1029.36ms | 4918 | 160 | 1486.01 | 3046.81 | 0.207573 | 3.39264 | 11.2666 | 1.32168 | 0.000744713 | 3.1771e-05 | 1.01667e-05 | 1(Win) | true |
| Jsonifier | 1469.62 | 0.12031 | 1021.73ms | 4604 | 4890 | 63178.8 | 2987.66 | 0.0165529 | 3.54905 | 9.45091 | 0.539966 | 0.000530525 | 3.69111e-05 | 1.63457e-05 | 2(Loss) | true |
| Glaze | 1353.81 | 0.169648 | 1047.32ms | 4604 | 640 | 19374.5 | 3243.22 | 0.088532 | 3.84772 | 12.2183 | 0.967203 | 0.000561672 | 2.47747e-05 | 9.50261e-06 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2611.39 | 0.0821679 | 1399.21ms | 18245 | 640 | 19183.6 | 6663.04 | 0.0446223 | 1.98257 | 7.75314 | 1.39414 | 0.00154863 | 3.14298e-05 | 1.69567e-05 | 1(Win) | true |
| Jsonifier | 2349.18 | 0.0897713 | 1468.24ms | 18245 | 640 | 28295.1 | 7406.75 | 0.237918 | 2.20277 | 8.01315 | 1.8148 | 0.00186669 | 0.000179073 | 0.000131885 | 2(Loss) | true |
| simdjson (reflection) | 2312.4 | 0.0633014 | 1482.89ms | 18245 | 1280 | 29040.2 | 7524.57 | 0.0982644 | 2.22235 | 8.33927 | 1.43261 | 0.00146979 | 5.01422e-05 | 2.57776e-05 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1840.1 | 0.0453811 | 1679.37ms | 18245 | 2560 | 47140.8 | 9455.92 | 0.0406491 | 2.79472 | 10.2286 | 1.89784 | 0.00199498 | 8.28352e-05 | 5.07631e-05 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1839.76 | 0.0530222 | 1682.63ms | 18245 | 1280 | 32187.7 | 9457.62 | 0.0761701 | 2.80818 | 12.0684 | 2.37534 | 0.0034912 | 6.3502e-05 | 3.79813e-05 | 4(Tie) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3058.81 | 0.035583 | 1394.83ms | 18245 | 4890 | 20034.4 | 5688.42 | 0.0329721 | 1.68748 | 6.68369 | 1.15106 | 0.00130239 | 3.83891e-05 | 1.97269e-05 | 1(Win) | true |
| Jsonifier | 2716.96 | 0.0530915 | 1468.43ms | 18245 | 2560 | 29594.5 | 6404.13 | 0.0517267 | 1.90304 | 6.95051 | 1.57331 | 0.001776 | 4.41902e-05 | 2.40006e-05 | 2(Loss) | true |
| simdjson (reflection) | 2626.01 | 0.176372 | 1502.06ms | 18245 | 30 | 4097.1 | 6625.93 | 0.205676 | 2.00228 | 7.87268 | 1.31746 | 0.000813008 | 5.48095e-06 | 1.82698e-06 | 3(Loss) | true |
| Glaze | 2014.21 | 0.0457765 | 1682.68ms | 18245 | 2560 | 40031.8 | 8638.52 | 0.0327402 | 2.55017 | 10.9605 | 2.12179 | 0.00340337 | 3.89233e-05 | 2.27588e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1998.34 | 0.0888091 | 1696.24ms | 18245 | 640 | 38268.8 | 8707.13 | 0.00109464 | 2.5565 | 9.566 | 1.74244 | 0.00178773 | 3.10873e-05 | 1.57577e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6320.32 | 0.091033 | 1103.87ms | 24579 | 4890 | 55738.7 | 3708.73 | 0.088129 | 0.823186 | 1.89031 | 0.106026 | 0.000101022 | 1.40859e-05 | 5.97381e-06 | 1(Win) | true |
| Glaze | 3137.34 | 0.151533 | 1479.46ms | 24579 | 1280 | 164070 | 7471.41 | 0.0523285 | 1.64147 | 3.92176 | 0.474796 | 0.000280982 | 2.38707e-05 | 1.12838e-05 | 2(Loss) | true |
| simdjson (reflection) | 527.225 | 0.129537 | 5245.48ms | 24893 | 2560 | 8.70946e+06 | 45027.9 | 0.112029 | 9.758 | 36.801 | 6.03877 | 0.0070804 | 7.38316e-05 | 4.48168e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6438.12 | 0.0949243 | 1093.64ms | 24579 | 4890 | 58408.2 | 3640.87 | 0.0520576 | 0.807678 | 1.86948 | 0.101184 | 0.000104558 | 1.43854e-05 | 6.26501e-06 | 1(Win) | true |
| Glaze | 3660.51 | 0.0807846 | 1373.45ms | 24579 | 4890 | 130862 | 6403.58 | 0.15178 | 1.41534 | 3.77273 | 0.441597 | 0.000267249 | 1.43688e-05 | 6.26501e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.532 | 0.139694 | 5237.21ms | 24893 | 2560 | 1.00788e+07 | 44916.6 | 0.1234 | 9.64083 | 36.7977 | 6.03708 | 0.00725508 | 0.000100665 | 5.93791e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 950.516 | 0.0317679 | 1185.35ms | 4604 | 4890 | 10530.3 | 4619.3 | 0.182198 | 5.45472 | 23.0854 | 4.8662 | 0.00441796 | 4.75269e-05 | 1.66566e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 781.197 | 0.0376151 | 1288.73ms | 4604 | 160 | 715.145 | 5620.5 | 0.0155704 | 6.64677 | 26.8285 | 5.30115 | 0.00457754 | 2.17202e-05 | 0 | 2(Loss) | true |
| Glaze | 650.377 | 0.132948 | 1403.32ms | 4604 | 320 | 25778.2 | 6751.04 | 0.135351 | 7.96253 | 33.7815 | 6.94574 | 0.005333 | 3.66529e-05 | 1.08601e-05 | 3(Loss) | true |
| simdjson (reflection) | 637.535 | 0.134734 | 1422.03ms | 4604 | 40 | 3444.13 | 6887.02 | 0.0265061 | 8.13087 | 31.0805 | 5.98219 | 0.00502281 | 5.43006e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 486.125 | 0.0367024 | 1634.45ms | 4604 | 2560 | 28132.2 | 9032.08 | 0.0858224 | 10.5993 | 37.6409 | 7.66421 | 0.00870931 | 6.99969e-05 | 2.8423e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1182.11 | 0.120049 | 1176.91ms | 4604 | 320 | 6362.47 | 3714.31 | 0.0228055 | 4.40418 | 18.6979 | 3.86187 | 0.00312568 | 5.70156e-05 | 5.43006e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 946.614 | 0.0458433 | 1271.4ms | 4604 | 2560 | 11574.9 | 4638.34 | 0.0727149 | 5.47785 | 22.5654 | 4.32146 | 0.00238091 | 7.1015e-05 | 1.48478e-05 | 2(Loss) | true |
| Glaze | 739.592 | 0.0620833 | 1402.56ms | 4604 | 4890 | 66427.2 | 5936.68 | 0.276464 | 6.98417 | 29.5996 | 5.96271 | 0.00606119 | 5.0725e-05 | 1.84778e-05 | 3(Loss) | true |
| simdjson (reflection) | 714.434 | 0.0440792 | 1437.74ms | 4604 | 4890 | 35885.8 | 6145.72 | 0.103631 | 7.24953 | 27.0929 | 5.08338 | 0.00833911 | 0.000131876 | 5.97862e-05 | 4(Loss) | true |
| simdjson (ondemand) | 535.736 | 0.0439427 | 1654.73ms | 4604 | 4890 | 63423.8 | 8195.67 | 0.0677515 | 9.64215 | 33.119 | 6.65388 | 0.0144605 | 0.000103316 | 3.86434e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1521.82 | 0.0726751 | 1032.97ms | 4918 | 160 | 802.684 | 3081.96 | 0.105767 | 3.43042 | 11.3867 | 1.35177 | 0.000758693 | 4.8292e-05 | 1.52501e-05 | 1(Win) | true |
| Jsonifier | 1387.9 | 0.138904 | 1040.66ms | 4604 | 4890 | 94426.3 | 3163.56 | 0.10858 | 3.74607 | 9.55039 | 0.570591 | 0.000317275 | 6.3384e-05 | 2.97154e-05 | 2(Loss) | true |
| Glaze | 1220.46 | 0.0965756 | 1086.45ms | 4604 | 2560 | 30902.8 | 3597.59 | 0.00266027 | 4.27181 | 12.8371 | 1.11838 | 0.000655425 | 4.4798e-05 | 2.16354e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 1548.25 | 0.0647105 | 1029.17ms | 4918 | 4890 | 18791.1 | 3029.33 | 0.00329293 | 3.36215 | 11.2717 | 1.32351 | 0.000532579 | 4.9108e-05 | 2.17057e-05 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1449.15 | 0.125056 | 1029.49ms | 4604 | 4890 | 70204.4 | 3029.86 | 0.185154 | 3.58835 | 9.4268 | 0.5404 | 0.000316787 | 6.4228e-05 | 3.04261e-05 | 1(Tie) | true |
| Glaze | 1242.74 | 0.0555026 | 1079.39ms | 4604 | 4890 | 18803.9 | 3533.1 | 0.0614508 | 4.18177 | 12.2024 | 0.968289 | 0.000778375 | 3.23805e-05 | 1.27923e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2704.9 | 0.179898 | 1372.08ms | 18245 | 30 | 4017.53 | 6432.7 | 0.248829 | 1.91735 | 7.5521 | 1.34267 | 0.00167169 | 4.01937e-05 | 3.65397e-05 | 1(Win) | true |
| Jsonifier | 2504.8 | 0.0424457 | 1422.21ms | 18245 | 2560 | 22256 | 6946.57 | 0.0302568 | 2.06627 | 7.85547 | 1.76355 | 0.00206022 | 0.000112809 | 7.83391e-05 | 2(Loss) | true |
| simdjson (reflection) | 2342.52 | 0.0592982 | 1476.51ms | 18245 | 1280 | 24832.1 | 7427.8 | 0.109053 | 2.19294 | 8.35566 | 1.43393 | 0.00141597 | 2.45358e-05 | 1.32742e-05 | 3(Loss) | true |
| Glaze | 1877.32 | 0.0956522 | 1675.2ms | 18245 | 40 | 3143.84 | 9268.4 | 0.287606 | 2.75637 | 11.7916 | 2.3134 | 0.00386681 | 1.64429e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1849.46 | 0.0407048 | 1677.85ms | 18245 | 2560 | 37543 | 9408.05 | 0.151254 | 2.79389 | 9.96431 | 1.84237 | 0.00232429 | 3.50695e-05 | 1.75562e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3177.93 | 0.0650331 | 1379.27ms | 18245 | 1280 | 16228.5 | 5475.19 | 0.00540763 | 1.62026 | 6.49 | 1.10112 | 0.00129959 | 2.59489e-05 | 9.24911e-06 | 1(Win) | true |
| Jsonifier | 2901.11 | 0.0898203 | 1421.04ms | 18245 | 1280 | 37146.6 | 5997.63 | 0.0040773 | 1.78533 | 6.79397 | 1.52239 | 0.00172162 | 3.02737e-05 | 1.15186e-05 | 2(Loss) | true |
| simdjson (reflection) | 2619.36 | 0.0943246 | 1488.38ms | 18245 | 4890 | 191979 | 6642.75 | 0.16855 | 1.96882 | 7.79907 | 1.29983 | 0.000824777 | 4.51478e-05 | 2.17893e-05 | 3(Loss) | true |
| Glaze | 2037.31 | 0.0482205 | 1660.66ms | 18245 | 2560 | 43418.7 | 8540.56 | 0.113829 | 2.52714 | 10.7784 | 2.08249 | 0.00344097 | 1.81771e-05 | 6.76555e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1989.9 | 0.0502035 | 1713.32ms | 18245 | 80 | 1541.64 | 8744.05 | 0.0145792 | 2.60225 | 9.62938 | 1.75777 | 0.0014689 | 1.50726e-05 | 0 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6477.03 | 0.176772 | 1087.75ms | 24579 | 640 | 26193 | 3619 | 0.131683 | 0.796214 | 1.88584 | 0.105497 | 9.05244e-05 | 1.39219e-05 | 5.40349e-06 | 1(Win) | true |
| Glaze | 3251.88 | 0.0716579 | 1449.33ms | 24579 | 4890 | 130465 | 7208.24 | 0.0848443 | 1.58763 | 3.91013 | 0.475528 | 0.000379079 | 3.11171e-05 | 1.72059e-05 | 2(Loss) | true |
| simdjson (reflection) | 527.131 | 0.127959 | 5221.64ms | 24893 | 2560 | 8.50156e+06 | 45035.9 | 0.201614 | 9.62573 | 36.8175 | 6.04676 | 0.00737274 | 0.000283918 | 0.000191507 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6646.81 | 0.16293 | 1082.49ms | 24579 | 640 | 21129.2 | 3526.56 | 0.14993 | 0.784653 | 1.86501 | 0.100655 | 7.32968e-05 | 1.91347e-05 | 1.0362e-05 | 1(Win) | true |
| Glaze | 3566.16 | 0.117662 | 1384.18ms | 24579 | 2560 | 153124 | 6572.99 | 0.321891 | 1.44526 | 3.76179 | 0.442166 | 0.000330392 | 4.44676e-05 | 2.87816e-05 | 2(Loss) | true |
| simdjson (reflection) | 534.169 | 0.181255 | 5179.44ms | 24893 | 1280 | 8.30587e+06 | 44442.5 | 0.146691 | 9.5775 | 36.8094 | 6.04411 | 0.00780324 | 9.20188e-05 | 5.73078e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1562.66 | 0.0412935 | 1038.74ms | 5094 | 4890 | 8058.67 | 3108.82 | 0.00319772 | 3.33925 | 13.9425 | 2.38182 | 0.000728352 | 6.59583e-05 | 2.66965e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1487.43 | 0.0759777 | 1054.57ms | 5094 | 1280 | 7881.88 | 3266.06 | 0.0551667 | 3.50233 | 15.0086 | 2.52866 | 0.00202873 | 5.88928e-05 | 2.10112e-05 | 2(Loss) | true |
| simdjson (reflection) | 1268.13 | 0.107653 | 1112.31ms | 5094 | 1280 | 21769.7 | 3830.84 | 0.22527 | 4.07615 | 15.9246 | 2.62093 | 0.00303252 | 6.16534e-05 | 2.37718e-05 | 3(Loss) | true |
| Glaze | 1241.88 | 0.0930315 | 1125.26ms | 5094 | 640 | 8476.11 | 3911.82 | 0.105658 | 4.18678 | 17.254 | 3.28328 | 0.00617945 | 8.49652e-05 | 4.41696e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1061.1 | 0.0894922 | 1190.33ms | 5094 | 80 | 1342.96 | 4578.26 | 0.0281141 | 4.89899 | 17.3865 | 2.92442 | 0.00421084 | 5.15312e-05 | 0 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1928.51 | 0.039423 | 1034.64ms | 5094 | 2560 | 2524.71 | 2519.05 | 0.122794 | 2.71597 | 11.4798 | 1.8247 | 0.000572595 | 4.66235e-05 | 6.28803e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1809.6 | 0.0623801 | 1052.29ms | 5094 | 320 | 897.417 | 2684.58 | 0.16862 | 2.89224 | 12.7809 | 2.01649 | 0.00146005 | 4.96908e-05 | 3.6808e-06 | 2(Loss) | true |
| Glaze | 1597.57 | 0.120224 | 1086.6ms | 5094 | 640 | 8553.82 | 3040.88 | 0.171172 | 3.26756 | 14.0726 | 2.58402 | 0.00517367 | 3.58878e-05 | 1.28828e-05 | 3(Loss) | true |
| simdjson (reflection) | 1405.94 | 0.0941913 | 1138.48ms | 5094 | 2560 | 27117.3 | 3455.35 | 0.113336 | 3.70811 | 15.1869 | 2.42638 | 0.00306749 | 7.53031e-05 | 2.29283e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1299.71 | 0.118219 | 1156.59ms | 5094 | 80 | 1562.03 | 3737.76 | 0.0230806 | 4.00984 | 14.6211 | 2.319 | 0.00299617 | 3.19003e-05 | 0 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13448.1 | 0.110605 | 756.777ms | 5094 | 640 | 102.171 | 361.242 | 0.0731519 | 0.426232 | 1.61622 | 0.263055 | 0.000196309 | 1.44165e-05 | 1.22693e-06 | 1(Win) | true |
| simdjson (reflection) | 8087.71 | 0.21479 | 780.93ms | 5094 | 4890 | 8139.64 | 600.667 | 0.0287885 | 0.683082 | 2.41186 | 0.355516 | 0.00019651 | 5.56812e-05 | 2.48899e-05 | 2(Loss) | true |
| Glaze | 4235.48 | 0.188079 | 842.705ms | 5094 | 160 | 744.585 | 1146.98 | 0.0691555 | 1.26015 | 5.15764 | 0.82764 | 0.000196309 | 8.46584e-05 | 5.5212e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16607.7 | 0.560801 | 749.69ms | 5094 | 4890 | 13159.1 | 292.516 | 0.416146 | 0.352097 | 1.4998 | 0.236749 | 0.000196871 | 2.8222e-05 | 1.11603e-05 | 1(Win) | true |
| simdjson (reflection) | 9089.11 | 0.100235 | 776.099ms | 5094 | 80 | 22.9619 | 534.487 | 0.170433 | 0.609016 | 2.29388 | 0.329211 | 0.000196309 | 5.39851e-05 | 1.22693e-05 | 2(Loss) | true |
| Glaze | 4882.08 | 0.0947783 | 820.815ms | 5094 | 4890 | 4349.46 | 995.072 | 0.0470367 | 1.09612 | 4.69925 | 0.724382 | 0.000197795 | 4.21122e-05 | 1.31274e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2198.95 | 0.0418148 | 1077.39ms | 8051 | 4890 | 10424.1 | 3491.68 | 0.0424555 | 2.35273 | 10.0946 | 1.62464 | 0.00130411 | 7.21881e-05 | 3.34778e-05 | 1(Win) | true |
| Jsonifier | 1920.37 | 0.0513771 | 1126.25ms | 8051 | 2560 | 10802.1 | 3998.2 | 0.127975 | 2.70778 | 11.0467 | 2.07987 | 0.00158511 | 4.70633e-05 | 2.00383e-05 | 2(Loss) | true |
| simdjson (reflection) | 1909.61 | 0.0603617 | 1136.75ms | 8051 | 2560 | 15079 | 4020.72 | 0.0905034 | 2.68794 | 10.5814 | 1.67557 | 0.00207588 | 4.18232e-05 | 1.88738e-05 | 3(Loss) | true |
| Glaze | 1622.67 | 0.0678669 | 1201.54ms | 8051 | 1280 | 13199.8 | 4731.73 | 0.0401705 | 3.19714 | 13.5512 | 2.60241 | 0.00377049 | 3.0858e-05 | 7.4719e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1610.54 | 0.113328 | 1203.61ms | 8051 | 30 | 875.689 | 4767.37 | 0.0139859 | 3.22654 | 11.5321 | 1.87281 | 0.00303482 | 3.72625e-05 | 4.14027e-06 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2654.41 | 0.0578016 | 1068.86ms | 8051 | 4890 | 13669.5 | 2892.56 | 0.119807 | 1.96339 | 8.70004 | 1.30344 | 0.000745909 | 3.43414e-05 | 1.42242e-05 | 1(Win) | true |
| Jsonifier | 2258.39 | 0.0501285 | 1123.6ms | 8051 | 160 | 464.722 | 3399.79 | 0.00735394 | 2.31002 | 9.48826 | 1.72736 | 0.00160229 | 3.26046e-05 | 6.98671e-06 | 2(Loss) | true |
| simdjson (reflection) | 2109.35 | 0.0676746 | 1158.8ms | 8051 | 2560 | 15534.4 | 3640 | 0.0922268 | 2.43028 | 10.1243 | 1.55422 | 0.0013249 | 7.67083e-05 | 3.6098e-05 | 3(Loss) | true |
| Glaze | 1997.14 | 0.0881963 | 1167.84ms | 8051 | 1280 | 14716.2 | 3844.52 | 0.0826995 | 2.60793 | 11.5381 | 2.15998 | 0.00353159 | 3.90091e-05 | 1.58171e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1948.04 | 0.11518 | 1191.04ms | 8051 | 320 | 6594.91 | 3941.42 | 0.00991176 | 2.6714 | 9.89368 | 1.51223 | 0.00218995 | 4.46373e-05 | 2.17364e-05 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24797.3 | 0.372483 | 755.353ms | 9255 | 4890 | 8595.42 | 355.936 | 0.136317 | 0.2303 | 0.930524 | 0.143814 | 0.000108337 | 1.52463e-05 | 4.50759e-06 | 1(Win) | true |
| Glaze | 4516.69 | 0.179556 | 924.878ms | 9255 | 640 | 7879.4 | 1954.14 | 0.00799519 | 1.16379 | 4.81026 | 0.812966 | 0.000111595 | 1.26621e-05 | 2.19476e-06 | 2(Loss) | true |
| simdjson (reflection) | 516.345 | 0.598373 | 2445.44ms | 9255 | 2560 | 2.67829e+07 | 17093.7 | 0.00909655 | 9.83568 | 38.0793 | 7.28266 | 0.0203276 | 0.000181912 | 9.02384e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 28376.3 | 0.18153 | 750.363ms | 9255 | 160 | 51.0107 | 311.044 | 0.223538 | 0.20481 | 0.871637 | 0.130308 | 0.000108725 | 2.70124e-05 | 9.45435e-06 | 1(Win) | true |
| Glaze | 5355.15 | 0.0988261 | 887.021ms | 9255 | 4890 | 12973.6 | 1648.18 | 0.293582 | 0.982375 | 4.47315 | 0.737007 | 0.000181674 | 3.07356e-05 | 1.28378e-05 | 2(Loss) | true |
| simdjson (reflection) | 516.241 | 0.0979666 | 2451.71ms | 9255 | 4890 | 1.37187e+06 | 17097.1 | 0.0663099 | 9.85527 | 38.0823 | 7.28282 | 0.0216418 | 0.000136708 | 8.64177e-05 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5759.12 | 0.21473 | 776.011ms | 2889 | 160 | 168.845 | 478.4 | 0.449993 | 0.967904 | 3.82139 | 0.497058 | 0.000346141 | 1.08169e-05 | 2.16338e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 5712.04 | 0.268357 | 777.433ms | 2889 | 4890 | 8193.07 | 482.343 | 0.0410436 | 0.976203 | 3.82139 | 0.497058 | 0.000346778 | 2.81726e-05 | 7.92796e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5625.24 | 0.279158 | 774.987ms | 2889 | 4890 | 9141.61 | 489.786 | 0.329898 | 0.994596 | 3.89893 | 0.416407 | 0.000389532 | 3.1995e-05 | 7.50325e-06 | 3(Loss) | true |
| simdjson (reflection) | 5575 | 0.230413 | 777.877ms | 2889 | 80 | 103.732 | 494.2 | 0.0606673 | 1.00031 | 3.87712 | 0.422291 | 0.000346141 | 2.16338e-05 | 1.29803e-05 | 4(Loss) | true |
| Glaze | 3136.44 | 0.151312 | 809.327ms | 2889 | 80 | 141.338 | 878.438 | 0.0726247 | 1.71815 | 7.24922 | 1.24264 | 0.000346141 | 8.65351e-06 | 0 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6008.18 | 0.168591 | 767.684ms | 2889 | 160 | 95.6305 | 458.569 | 0.200754 | 0.945189 | 3.75666 | 0.480789 | 0.000346141 | 1.51436e-05 | 0 | 1(Win) | true |
| Jsonifier | 5876.43 | 0.228949 | 765.222ms | 2889 | 80 | 92.1797 | 468.85 | 0.101414 | 0.957087 | 3.75666 | 0.480789 | 0.000346141 | 3.46141e-05 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 5802.79 | 0.179554 | 767.915ms | 2889 | 160 | 116.287 | 474.8 | 0.0342367 | 0.963004 | 3.82451 | 0.399446 | 0.000400225 | 2.16338e-06 | 0 | 3(Loss) | true |
| simdjson (reflection) | 5738.96 | 0.153002 | 768.654ms | 2889 | 160 | 86.3267 | 480.081 | 0.0169214 | 0.972945 | 3.81239 | 0.406023 | 0.000361284 | 6.49013e-06 | 0 | 4(Loss) | true |
| Glaze | 3175.71 | 0.235132 | 806.05ms | 2889 | 40 | 166.456 | 867.575 | 0.125672 | 1.69578 | 7.17965 | 1.22603 | 0.000372101 | 0 | 0 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6558.22 | 0.131609 | 784.871ms | 3808 | 320 | 169.958 | 553.747 | 0.131318 | 0.842442 | 3.302 | 0.383403 | 0.000262605 | 1.55922e-05 | 8.20641e-07 | 1(Win) | true |
| Jsonifier | 6493.23 | 0.288514 | 785.7ms | 3808 | 4890 | 12732.6 | 559.289 | 0.14411 | 0.8462 | 3.302 | 0.383403 | 0.000263786 | 2.56161e-05 | 7.35724e-06 | 2(Loss) | true |
| simdjson (reflection) | 6422.62 | 0.19755 | 773.72ms | 3808 | 80 | 99.8188 | 565.438 | 0.250432 | 0.859569 | 3.29333 | 0.335872 | 0.000285583 | 1.64128e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 6286.22 | 0.255546 | 779.203ms | 3808 | 4890 | 10657.7 | 577.707 | 0.154247 | 0.876598 | 3.30987 | 0.331408 | 0.000366788 | 3.45844e-05 | 1.6433e-05 | 4(Loss) | true |
| Glaze | 3500.88 | 0.0757559 | 821.083ms | 3808 | 4890 | 3019.82 | 1037.34 | 0.0327969 | 1.52874 | 6.58508 | 1.20746 | 0.000352771 | 1.63793e-05 | 6.12208e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 6854.92 | 0.125857 | 771.241ms | 3808 | 4890 | 2173.96 | 529.779 | 0.11798 | 0.802783 | 3.25341 | 0.31854 | 0.000314804 | 2.48642e-05 | 1.22979e-05 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 6851.09 | 0.14727 | 772.506ms | 3808 | 160 | 97.5038 | 530.075 | 0.157747 | 0.808805 | 3.24422 | 0.323529 | 0.00026917 | 6.56513e-06 | 0 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 6669.72 | 0.0995247 | 782.153ms | 3808 | 640 | 187.94 | 544.489 | 0.263265 | 0.828928 | 3.25289 | 0.371061 | 0.000262605 | 2.70811e-05 | 1.23096e-05 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6653 | 0.175224 | 779.688ms | 3808 | 2560 | 2341.99 | 545.858 | 0.0822204 | 0.828995 | 3.25289 | 0.371061 | 0.000263323 | 4.20578e-05 | 2.02083e-05 | 3(Tie) | true |
| Glaze | 3565.89 | 0.0962162 | 822.752ms | 3808 | 160 | 153.63 | 1018.42 | 0.131158 | 1.50122 | 6.53151 | 1.19433 | 0.000344669 | 2.95431e-05 | 0 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2894.02 | 0.378918 | 817.046ms | 2889 | 1280 | 16656.8 | 952.02 | 0.016251 | 1.85372 | 6.11873 | 0.996539 | 0.000352631 | 5.30028e-05 | 9.19436e-06 | 1(Win) | true |
| Glaze | 2375.69 | 0.0723441 | 835.023ms | 2889 | 4890 | 3442.17 | 1159.73 | 0.0136929 | 2.24389 | 8.85739 | 1.54552 | 0.0003506 | 5.58497e-05 | 1.86873e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2312.3 | 0.140981 | 851.541ms | 2889 | 80 | 225.746 | 1191.53 | 0.050381 | 2.3041 | 7.92593 | 1.17653 | 0.000601419 | 8.65351e-05 | 1.29803e-05 | 3(Loss) | true |
| simdjson (reflection) | 1923.67 | 0.0990232 | 868.108ms | 2889 | 2560 | 5149.31 | 1432.25 | 0.0955571 | 2.74661 | 9.23226 | 1.30772 | 0.000350873 | 0.000126422 | 6.3414e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1314.76 | 0.210807 | 931.92ms | 2889 | 640 | 12489.7 | 2095.56 | 0.110549 | 3.96704 | 12.0893 | 2.41502 | 0.0014446 | 0.000220665 | 0.000118986 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3193.15 | 0.0496016 | 816.147ms | 2889 | 1280 | 234.454 | 862.835 | 0.159195 | 1.68366 | 5.5919 | 0.858429 | 0.000691199 | 6.54422e-05 | 2.13634e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2575.94 | 0.0991961 | 838.739ms | 2889 | 160 | 180.108 | 1069.58 | 0.0642366 | 2.07875 | 7.39633 | 1.03738 | 0.000346141 | 3.46141e-05 | 2.16338e-06 | 2(Loss) | true |
| Glaze | 2548.54 | 0.173243 | 833.111ms | 2889 | 2560 | 8979.67 | 1081.07 | 0.022578 | 2.0888 | 8.32399 | 1.40222 | 0.000361014 | 6.88225e-05 | 2.6907e-05 | 3(Loss) | true |
| simdjson (reflection) | 2163.31 | 0.163048 | 858.888ms | 2889 | 320 | 1379.88 | 1273.59 | 0.0791915 | 2.45998 | 8.72378 | 1.17411 | 0.000347222 | 0.000116822 | 5.30028e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1382.13 | 0.218005 | 931.596ms | 2889 | 40 | 755.43 | 1993.42 | 0.00627101 | 3.82021 | 11.7082 | 2.3136 | 0.00205954 | 0.000181724 | 6.05746e-05 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8941.14 | 0.0874633 | 751.927ms | 2963 | 80 | 6.1125 | 316.038 | 0.202124 | 0.648536 | 1.48059 | 0.233885 | 0.000337496 | 1.26561e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6736.54 | 0.066055 | 762.69ms | 2963 | 1280 | 98.2677 | 419.464 | 0.111501 | 0.838752 | 1.92035 | 0.289909 | 0.00033855 | 2.71579e-05 | 5.27337e-06 | 2(Loss) | true |
| Glaze | 5788.04 | 0.192993 | 769.309ms | 2963 | 640 | 568.15 | 488.203 | 0.463008 | 0.964609 | 3.02396 | 0.469119 | 0.000337496 | 8.17373e-05 | 2.68942e-05 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10293 | 0.144711 | 746.202ms | 2963 | 640 | 101.01 | 274.531 | 0.00683029 | 0.586264 | 1.31455 | 0.195748 | 0.00033855 | 2.47848e-05 | 4.2187e-06 | 1(Win) | true |
| simdjson (reflection) | 7563.65 | 0.132222 | 757.45ms | 2963 | 2560 | 624.671 | 373.595 | 0.15826 | 0.754338 | 1.75363 | 0.251435 | 0.000338419 | 3.16402e-05 | 1.25243e-05 | 2(Loss) | true |
| Glaze | 6727.48 | 0.186437 | 758.825ms | 2963 | 2560 | 1569.87 | 420.029 | 0.00223194 | 0.840972 | 2.53156 | 0.365171 | 0.000338682 | 4.71967e-05 | 1.58201e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2914.08 | 0.0837474 | 845.993ms | 3808 | 1280 | 1394.25 | 1246.22 | 0.00714712 | 1.82449 | 6.42332 | 0.900473 | 0.000264451 | 2.0516e-05 | 4.1032e-06 | 1(Win) | true |
| simdjson (reflection) | 2558.32 | 0.192895 | 866.981ms | 3808 | 640 | 4798.51 | 1419.52 | 0.160633 | 2.0676 | 7.35662 | 1.00762 | 0.000275325 | 3.73392e-05 | 2.87224e-06 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2378.58 | 0.0954834 | 872.839ms | 3808 | 160 | 340.043 | 1526.79 | 0.00163745 | 2.22481 | 8.38157 | 1.51576 | 0.000490743 | 7.22164e-05 | 1.47715e-05 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 2375.82 | 0.153783 | 874.211ms | 3808 | 30 | 165.771 | 1528.57 | 0.0806206 | 2.22621 | 6.24133 | 1.14102 | 0.00121674 | 0.000122549 | 5.2521e-05 | 3(Tie) | true |
| simdjson (ondemand) | 1710.65 | 0.0740512 | 935.636ms | 3808 | 160 | 395.416 | 2122.93 | 0.0612738 | 3.07932 | 9.52363 | 1.84769 | 0.00158548 | 9.19118e-05 | 2.29779e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3279.72 | 0.0514319 | 842.698ms | 3808 | 320 | 103.785 | 1107.29 | 0.00338654 | 1.65814 | 6.02153 | 0.794905 | 0.000262605 | 5.17004e-05 | 8.20641e-07 | 1(Win) | true |
| simdjson (reflection) | 2767.43 | 0.235287 | 863.801ms | 3808 | 80 | 762.652 | 1312.26 | 0.284005 | 1.92179 | 6.9698 | 0.90625 | 0.000265888 | 0.000177258 | 5.58036e-05 | 2(Loss) | true |
| Jsonifier | 2726.62 | 0.0618197 | 866.351ms | 3808 | 40 | 27.1179 | 1331.9 | 0.127475 | 1.98292 | 5.84086 | 1.03624 | 0.000262605 | 0.000118172 | 0 | 3(Loss) | true |
| Glaze | 2570.61 | 0.137857 | 870.179ms | 3808 | 30 | 113.789 | 1412.73 | 0.303451 | 2.06136 | 7.97637 | 1.4073 | 0.000262605 | 8.7535e-06 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1769.95 | 0.0899429 | 935.843ms | 3808 | 160 | 544.912 | 2051.81 | 0.223167 | 2.97916 | 9.23398 | 1.77075 | 0.00158055 | 4.92384e-05 | 1.64128e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12088.9 | 0.0653317 | 753.599ms | 4300 | 640 | 31.4334 | 339.22 | 0.588408 | 0.471178 | 1.06419 | 0.16186 | 0.000232558 | 2.68895e-05 | 1.81686e-06 | 1(Win) | true |
| Glaze | 3647.69 | 0.206637 | 834.809ms | 4300 | 4890 | 26389.1 | 1124.22 | 0.577605 | 1.46325 | 3.57698 | 0.599535 | 0.000301232 | 9.39269e-05 | 3.39563e-05 | 2(Loss) | true |
| simdjson (reflection) | 549.554 | 0.184224 | 1480.47ms | 4300 | 640 | 120945 | 7462.05 | 0.372194 | 9.34218 | 34.0658 | 7.50628 | 0.00980196 | 0.000193314 | 9.15698e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14341 | 0.103218 | 750.363ms | 4300 | 40 | 3.48462 | 285.95 | 0.0291341 | 0.410244 | 0.951395 | 0.134884 | 0.000232558 | 2.90698e-05 | 0 | 1(Win) | true |
| Glaze | 4249.08 | 0.274444 | 819.389ms | 4300 | 2560 | 17959.5 | 965.103 | 0.677184 | 1.26281 | 3.03163 | 0.477209 | 0.000233285 | 5.07812e-05 | 2.33467e-05 | 2(Loss) | true |
| simdjson (reflection) | 553.611 | 0.128988 | 1479.46ms | 4300 | 1280 | 116851 | 7407.37 | 0.036205 | 9.34268 | 34.0716 | 7.50791 | 0.0103156 | 0.000334302 | 0.000213481 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3285.84 | 0.102639 | 7354.47ms | 466906 | 1280 | 2.47628e+07 | 135513 | 0.167503 | 1.54446 | 6.31273 | 1.26005 | 0.0018468 | 0.00198381 | 4.45335e-05 | 1(Win) | true |
| Glaze | 2494.17 | 0.120093 | 9518.8ms | 466906 | 320 | 1.47092e+07 | 178527 | 0.227267 | 2.03421 | 8.75464 | 1.96145 | 0.00256937 | 0.00370289 | 3.91808e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1878.31 | 1.14447 | 6350.69ms | 466906 | 160 | 1.17774e+09 | 237062 | 0.175991 | 2.69398 | 11.9921 | 1.52294 | 0.00493318 | 0.078269 | 0.000220909 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3301.85 | 0.101078 | 7329.83ms | 466906 | 320 | 5.94577e+06 | 134857 | 0.0567271 | 1.54601 | 6.31155 | 1.25978 | 0.00184325 | 0.00171222 | 3.45359e-05 | 1(Win) | true |
| Glaze | 2494.6 | 0.165256 | 9560.33ms | 466906 | 640 | 5.56865e+07 | 178496 | 0.0427356 | 2.03605 | 8.75349 | 1.96119 | 0.00261625 | 0.0035695 | 3.42916e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1856.43 | 0.407818 | 6388.77ms | 466906 | 1280 | 1.22474e+09 | 239857 | 0.0768105 | 2.73459 | 11.9918 | 1.52286 | 0.00487851 | 0.0948458 | 0.000272561 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4170.51 | 0.0780277 | 8577.91ms | 699405 | 2560 | 3.98673e+07 | 159933 | 0.045487 | 1.22219 | 4.79602 | 1.19835 | 0.00192184 | 0.00108175 | 2.18137e-05 | 1(Win) | true |
| Glaze | 3217.5 | 0.130015 | 5561.8ms | 699405 | 30 | 2.17934e+06 | 207305 | 0.111296 | 1.59826 | 6.2876 | 1.35582 | 0.00200852 | 0.00134166 | 7.17276e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2429.99 | 0.282621 | 7914.8ms | 767297 | 160 | 1.1589e+08 | 301133 | 0.577646 | 2.07853 | 8.04354 | 1.07977 | 0.00368105 | 0.0999357 | 4.22995e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4167.45 | 0.296777 | 8619.3ms | 699405 | 160 | 3.60992e+07 | 160051 | 0.0219062 | 1.22176 | 4.79552 | 1.19825 | 0.00196256 | 0.000983059 | 1.02498e-05 | 1(Win) | true |
| Glaze | 3180.09 | 0.0677249 | 5556.1ms | 699405 | 320 | 6.45693e+06 | 209744 | 0.19944 | 1.59938 | 6.2869 | 1.35566 | 0.00195399 | 0.0012893 | 3.41228e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2405.96 | 0.996484 | 7906.74ms | 767297 | 160 | 1.46964e+09 | 304141 | 0.657457 | 2.11303 | 8.04405 | 1.07991 | 0.00360279 | 0.0931552 | 8.34911e-05 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2987.25 | 0.172631 | 5335.06ms | 631514 | 160 | 1.93813e+07 | 201610 | 0.0129692 | 1.69651 | 8.25722 | 1.35256 | 0.00540275 | 9.17438e-06 | 4.93853e-06 | 1(Win) | true |
| Glaze | 2171.5 | 0.0606996 | 7258.97ms | 631514 | 1280 | 3.62766e+07 | 277347 | 0.449344 | 2.32337 | 9.80782 | 1.64384 | 0.00964837 | 1.15682e-05 | 9.66056e-06 | 2(Loss) | true |
