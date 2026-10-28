# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 28, 2026)
#### Using the following commits:
----
| Jsonifier: [9f4382a](https://github.com/nihilai-collective/jsonifier/commit/9f4382a)  
| simdjson(On Demand): [41ad75c](https://github.com/simdjson/simdjson/commit/41ad75c)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 5% and mean shift ≤ 2.5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **Stage-1 Only:** Both libraries execute only stage-1 parsing, identifying structural indices and nothing more.
* **No UTF-8 Validation:** Neither library performs UTF-8 validation in these tests.

---
*Environment generated via BenchmarkSuite commit: [35ec835](https://github.com/nihilai-collective/benchmarksuite/commit/35ec835)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 982.757 | 0.0433726 | 813.365ms | 905 | 2560 | 371.43 | 878.219 | 0.0719156 | 5.37765 | 26.8486 | 2.72376 | 0.00443715 | 0.000107907 | 1.03591e-05 | 1(Win) | true |
| simdjson (ondemand) | 372.046 | 0.0358894 | 958.768ms | 905 | 2560 | 1774.5 | 2319.81 | 6.73548e-05 | 13.8164 | 71.8906 | 7.34807 | 0.00315953 | 0.000113087 | 5.56802e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1916.68 | 0.0320215 | 814.145ms | 1811 | 4890 | 407.125 | 901.091 | 0.0252043 | 2.75369 | 13.4241 | 1.36002 | 0.00367014 | 5.28468e-05 | 1.4228e-05 | 1(Win) | true |
| simdjson (ondemand) | 714.796 | 0.0303415 | 970.095ms | 1811 | 2560 | 1375.9 | 2416.22 | 0.0806888 | 7.196 | 35.8426 | 3.6582 | 0.0105162 | 6.77285e-05 | 2.28637e-05 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4189.73 | 0.125331 | 830.156ms | 3862 | 80 | 97.1082 | 879.075 | 0.0540049 | 1.2625 | 6.3392 | 0.636717 | 0.00103897 | 7.44433e-05 | 1.61833e-05 | 1(Win) | true |
| simdjson (ondemand) | 1578.7 | 0.0274173 | 959.471ms | 3862 | 2560 | 1047.4 | 2332.98 | 0.0778472 | 3.25628 | 16.8465 | 1.72191 | 0.000777508 | 2.16452e-05 | 5.9676e-06 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6180.43 | 0.0517651 | 873.003ms | 9578 | 2560 | 1498.4 | 1477.94 | 0.00581503 | 0.840652 | 4.09459 | 0.379516 | 0.0011459 | 1.43966e-05 | 3.87444e-06 | 1(Win) | true |
| simdjson (ondemand) | 3644.81 | 0.0458316 | 979.858ms | 9578 | 160 | 211.082 | 2506.11 | 0.0129666 | 1.4096 | 6.95667 | 0.714867 | 0.000903764 | 1.37033e-05 | 1.30507e-06 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3856.18 | 0.146461 | 820.114ms | 3873 | 30 | 59.0402 | 957.833 | 0.0626806 | 1.36718 | 6.31578 | 0.633359 | 0.000774593 | 3.44264e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1594.59 | 0.0219288 | 954.013ms | 3873 | 2560 | 660.487 | 2316.32 | 0.00527873 | 3.2273 | 16.7986 | 1.71702 | 0.000902078 | 4.00408e-05 | 1.41202e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16004.9 | 0.0524223 | 1296.97ms | 94653 | 1280 | 11189.4 | 5640.04 | 0.132539 | 0.323363 | 1.74585 | 0.0888615 | 3.20579e-05 | 2.88884e-06 | 1.16379e-06 | 1(Win) | true |
| simdjson (ondemand) | 13311.7 | 0.0506431 | 1409.23ms | 94653 | 1280 | 15095.6 | 6781.09 | 0.0875094 | 0.384131 | 1.83919 | 0.0772929 | 2.11958e-05 | 1.83235e-06 | 4.9523e-07 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15921.5 | 0.0153004 | 1479.06ms | 124597 | 4890 | 6376.15 | 7463.16 | 0.0967003 | 0.319169 | 1.74772 | 0.080941 | 1.79031e-05 | 1.42463e-06 | 4.00473e-07 | 1(Win) | true |
| simdjson (ondemand) | 14450.9 | 0.0576134 | 1548.23ms | 124597 | 640 | 14363.3 | 8222.7 | 0.00606136 | 0.351218 | 1.67343 | 0.0693436 | 1.64781e-05 | 2.03155e-06 | 7.39885e-07 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14333.9 | 0.0383286 | 8109.83ms | 2251027 | 160 | 527224 | 149767 | 0.108971 | 0.352526 | 1.71665 | 0.0767402 | 0.00154003 | 0.0250197 | 3.51784e-06 | 1(Win) | true |
| simdjson (ondemand) | 11928.8 | 0.0151454 | 9638.14ms | 2251027 | 640 | 475454 | 179963 | 0.0645055 | 0.423761 | 1.91973 | 0.080649 | 0.000950565 | 0.0250115 | 7.49658e-07 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17898.9 | 0.0347106 | 7526.44ms | 5373214 | 1280 | 1.264e+07 | 286291 | 0.0609943 | 0.281792 | 1.39435 | 0.053905 | 0.000812852 | 0.0195713 | 2.15435e-06 | 1(Win) | true |
| simdjson (ondemand) | 15013.2 | 0.0295084 | 8887.92ms | 5373214 | 80 | 811523 | 341318 | 0.0274888 | 0.336343 | 1.44043 | 0.0578126 | 0.000930149 | 0.0196085 | 3.53606e-07 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10616.4 | 0.03602 | 5244.13ms | 500299 | 640 | 167715 | 44941.9 | 0.0339594 | 0.476861 | 2.50767 | 0.12427 | 2.65935e-05 | 4.84086e-06 | 4.0507e-06 | 1(Win) | true |
| simdjson (ondemand) | 9485.46 | 0.0909538 | 5827.16ms | 500299 | 30 | 62792.2 | 50300.4 | 0.0464989 | 0.542972 | 2.60137 | 0.112573 | 6.0697e-05 | 4.48399e-05 | 4.2308e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14663.5 | 0.0188097 | 8242.67ms | 1151920 | 4890 | 971045 | 74917.6 | 0.00434147 | 0.344502 | 1.83489 | 0.0847412 | 0.0004447 | 1.0891e-05 | 7.68345e-07 | 1(Win) | true |
| simdjson (ondemand) | 13677.9 | 0.0110913 | 8778.77ms | 1151920 | 2560 | 203148 | 80316 | 0.0173382 | 0.369528 | 1.76148 | 0.0731354 | 0.000116664 | 2.71222e-05 | 4.51556e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11385.6 | 0.0188369 | 1203.23ms | 56369 | 4890 | 3868.05 | 4721.53 | 0.00264068 | 0.448487 | 2.30884 | 0.115915 | 3.59376e-05 | 3.15987e-06 | 6.92922e-07 | 1(Win) | true |
| simdjson (ondemand) | 10191.1 | 0.0133318 | 1258.77ms | 56369 | 4890 | 2418.39 | 5274.96 | 0.00553106 | 0.50031 | 2.39639 | 0.103816 | 3.53318e-05 | 2.50323e-06 | 2.97485e-07 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12887.3 | 0.0136133 | 1353.34ms | 83958 | 4890 | 3498.13 | 6212.99 | 0.0171668 | 0.39485 | 2.07254 | 0.0968461 | 3.85016e-05 | 1.98512e-06 | 3.70231e-07 | 1(Win) | true |
| simdjson (ondemand) | 12356.2 | 0.036366 | 1378.14ms | 83958 | 1280 | 7108.19 | 6480.05 | 0.0754753 | 0.412243 | 1.99693 | 0.0849354 | 2.39145e-05 | 5.22955e-06 | 3.47086e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17616.6 | 0.0263718 | 1021.76ms | 53331 | 4890 | 2834.67 | 2887.07 | 0.0224071 | 0.290847 | 1.54526 | 0.078041 | 3.79349e-05 | 3.19416e-06 | 5.44502e-07 | 1(Win) | true |
| simdjson (ondemand) | 15118.2 | 0.0252051 | 1068.2ms | 53331 | 2560 | 1840.67 | 3364.19 | 0.0251669 | 0.338376 | 1.58801 | 0.0664342 | 3.61466e-05 | 2.78332e-06 | 4.17499e-07 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15716.9 | 0.130081 | 1130.84ms | 65103 | 30 | 792.161 | 3950.33 | 0.12504 | 0.325448 | 1.64034 | 0.074866 | 4.65928e-05 | 2.04804e-06 | 5.12009e-07 | 1(Win) | true |
| simdjson (ondemand) | 15653 | 0.0218298 | 1127.51ms | 65103 | 2560 | 1919.32 | 3966.47 | 0.0123776 | 0.326202 | 1.52653 | 0.063223 | 3.09486e-05 | 1.99204e-06 | 1.92003e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10063.9 | 0.15279 | 839.343ms | 11812 | 40 | 116.994 | 1119.33 | 0.0186089 | 0.520198 | 2.53082 | 0.128513 | 8.46597e-05 | 4.23298e-06 | 4.23298e-06 | 1(Win) | true |
| simdjson (ondemand) | 9298.26 | 0.0130718 | 840.552ms | 11812 | 1280 | 32.1016 | 1211.5 | 0.00141868 | 0.561785 | 2.61895 | 0.117508 | 8.46597e-05 | 4.69597e-06 | 8.59825e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14323.4 | 0.0448939 | 898.494ms | 25388 | 2560 | 1474.28 | 1690.37 | 0.0264666 | 0.361543 | 1.88034 | 0.0883489 | 6.45451e-05 | 4.75434e-06 | 1.38476e-07 | 1(Win) | true |
| simdjson (ondemand) | 13493.3 | 0.0301474 | 908.418ms | 25388 | 4890 | 1430.96 | 1794.36 | 0.00301123 | 0.383009 | 1.80258 | 0.0770837 | 3.96384e-05 | 5.58208e-06 | 4.67187e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10975.6 | 0.0217797 | 1675.08ms | 108313 | 2560 | 10756 | 9411.39 | 0.0133749 | 0.463011 | 2.38017 | 0.118555 | 1.90565e-05 | 2.84188e-06 | 1.49307e-06 | 1(Win) | true |
| simdjson (ondemand) | 9820.41 | 0.018473 | 1782.17ms | 108313 | 2560 | 9665.37 | 10518.4 | 0.0106855 | 0.516805 | 2.47503 | 0.108907 | 3.33921e-05 | 1.30914e-06 | 1.98355e-07 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13569.6 | 0.0374852 | 2021.98ms | 183677 | 640 | 14985.6 | 12908.9 | 0.0445111 | 0.373578 | 2.0259 | 0.0940293 | 2.40402e-05 | 1.02081e-06 | 2.21176e-07 | 1(Win) | true |
| simdjson (ondemand) | 12707.8 | 0.0228251 | 2115.5ms | 183677 | 2560 | 25341.5 | 13784.2 | 0.0825272 | 0.400675 | 1.95141 | 0.0823893 | 2.91102e-05 | 4.10027e-06 | 3.12412e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8769.71 | 0.0674641 | 5315.01ms | 1834197 | 160 | 2.89726e+06 | 199462 | 0.0343259 | 0.575971 | 2.88154 | 0.136889 | 0.00174982 | 0.037717 | 2.8657e-06 | 1(Win) | true |
| simdjson (ondemand) | 6882.44 | 0.0383867 | 6687.84ms | 1834197 | 640 | 6.09183e+06 | 254158 | 0.0459628 | 0.734634 | 3.06269 | 0.152795 | 0.00444315 | 0.0377109 | 2.17227e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14896.8 | 0.0639127 | 6089.7ms | 7351818 | 640 | 5.79103e+07 | 470653 | 0.0166802 | 0.338123 | 1.60545 | 0.0669819 | 0.00125516 | 0.0211573 | 7.75488e-06 | 1(Win) | true |
| simdjson (ondemand) | 13681.3 | 0.0311811 | 6634.05ms | 7351818 | 320 | 8.17085e+06 | 512469 | 0.0177924 | 0.369744 | 1.61331 | 0.0660424 | 0.00094779 | 0.0211836 | 1.41887e-06 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12817.1 | 0.0194963 | 4165.36ms | 461466 | 2560 | 114722 | 34336 | 0.0421846 | 0.39562 | 2.07052 | 0.103735 | 2.3369e-05 | 2.06035e-06 | 1.72768e-06 | 1(Win) | true |
| simdjson (ondemand) | 11378.5 | 0.110022 | 4584.43ms | 461466 | 40 | 72431.5 | 38677.2 | 0.0382078 | 0.444318 | 2.16441 | 0.0920459 | 2.47581e-05 | 2.97963e-06 | 1.57108e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14899.1 | 0.018292 | 5404.83ms | 728486 | 2560 | 186247 | 46629.7 | 0.00572799 | 0.339486 | 1.87179 | 0.0865906 | 0.000169225 | 3.57441e-06 | 1.94431e-06 | 1(Win) | true |
| simdjson (ondemand) | 13441.2 | 0.168064 | 5811.09ms | 728486 | 40 | 301839 | 51687.1 | 0.107648 | 0.381268 | 1.7979 | 0.0748965 | 0.000251995 | 3.47982e-05 | 3.17096e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15916.4 | 0.131654 | 3528.68ms | 466906 | 40 | 54262.1 | 27976 | 0.205468 | 0.317833 | 1.71555 | 0.085816 | 8.42782e-05 | 7.49616e-07 | 1.07088e-07 | 1(Win) | true |
| simdjson (ondemand) | 13650.1 | 0.0569918 | 3972.15ms | 466906 | 320 | 110602 | 32620.7 | 0.245139 | 0.370942 | 1.76697 | 0.0738972 | 1.78636e-05 | 9.23633e-07 | 1.00395e-07 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15797.6 | 0.00881738 | 4553.2ms | 631514 | 4890 | 55255.2 | 38123.5 | 0.00209991 | 0.320281 | 1.72 | 0.0784797 | 2.45215e-05 | 1.01389e-06 | 7.6908e-07 | 1(Win) | true |
| simdjson (ondemand) | 14989.6 | 0.0324201 | 4741.21ms | 631514 | 2560 | 434366 | 40178.6 | 0.0879925 | 0.337745 | 1.61772 | 0.0666748 | 2.04927e-05 | 1.427e-06 | 3.21648e-07 | 2(Loss) | true |
