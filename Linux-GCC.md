# Json-Performance: Stage-1 Parsing
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

Latest Results: (Nov 13, 2026)
#### Using the following commits:
----
| Jsonifier: [d4727ec](https://github.com/nihilai-collective/Jsonifier/commit/d4727ec)  
| simdjson: [449f38e63](https://github.com/simdjson/simdjson/commit/449f38e63)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (stage-1)** | `haswell` |

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
*Environment generated via BenchmarkSuite commit: [27950a9](https://github.com/nihilai-collective/benchmarksuite/commit/27950a9)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 987.605 | 0.177482 | 795.107ms | 905 | 1280 | 3079.27 | 873.907 | 0.0699492 | 5.54591 | 28.4133 | 2.51271 | 0.00474448 | 0.000155387 | 3.36671e-05 | 1(Win) | true |
| simdjson (stage-1) | 345.843 | 0.0315887 | 957.4ms | 905 | 4890 | 3038.88 | 2495.57 | 0.0549592 | 15.1308 | 76.4975 | 5.79563 | 0.00227864 | 0.000138065 | 1.51397e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2004.28 | 0.206301 | 799.452ms | 1811 | 320 | 1011.29 | 861.709 | 0.262157 | 2.71467 | 14.1883 | 1.25069 | 0.0032872 | 4.31391e-05 | 1.72557e-06 | 1(Win) | true |
| simdjson (stage-1) | 691.728 | 0.0582386 | 963.364ms | 1811 | 1280 | 2706.44 | 2496.8 | 0.0230035 | 7.56683 | 38.2275 | 2.89619 | 0.00110436 | 0.000101808 | 1.29417e-05 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4237.25 | 0.0641137 | 795.077ms | 3862 | 4890 | 1518.68 | 869.217 | 0.0466055 | 1.27139 | 6.65122 | 0.58493 | 0.00103605 | 3.65895e-05 | 4.81859e-06 | 1(Win) | true |
| simdjson (stage-1) | 1467.69 | 0.125077 | 961.267ms | 3862 | 320 | 3152.53 | 2509.44 | 0.0124545 | 3.5614 | 17.9259 | 1.35811 | 0.000706402 | 3.56033e-05 | 1.61833e-06 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6346.42 | 0.0566863 | 857.698ms | 9578 | 640 | 426.018 | 1439.28 | 0.0137891 | 0.84989 | 4.19044 | 0.318229 | 0.000842752 | 8.48298e-06 | 1.30507e-06 | 1(Win) | true |
| simdjson (stage-1) | 3502.85 | 0.0426756 | 967.764ms | 9578 | 4890 | 6055.85 | 2607.68 | 0.00674352 | 1.49274 | 7.31009 | 0.54761 | 0.000923854 | 1.40702e-05 | 1.1743e-06 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4236.65 | 0.114515 | 794.347ms | 3873 | 1280 | 1275.8 | 871.816 | 0.00412197 | 1.27227 | 6.62845 | 0.58172 | 0.000755229 | 4.84121e-05 | 1.02876e-05 | 1(Win) | true |
| simdjson (stage-1) | 1502.15 | 0.160272 | 954.671ms | 3873 | 30 | 465.913 | 2458.87 | 0.0596125 | 3.54778 | 17.875 | 1.35425 | 0.000860659 | 1.72132e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14369.2 | 0.113029 | 1339.14ms | 94653 | 40 | 2016.74 | 6282.07 | 0.16862 | 0.354312 | 1.71452 | 0.0716301 | 2.13939e-05 | 1.98092e-05 | 1.10932e-05 | 1(Win) | true |
| simdjson (stage-1) | 13466.4 | 0.04269 | 1388.86ms | 94653 | 40 | 327.549 | 6703.2 | 0.0034808 | 0.38493 | 2.00727 | 0.0771027 | 1.98092e-05 | 3.43359e-06 | 0 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14456.9 | 0.083545 | 1544.33ms | 124597 | 160 | 7544.4 | 8219.24 | 0.0300452 | 0.358008 | 1.71319 | 0.0635249 | 1.64029e-05 | 1.58009e-05 | 1.41456e-05 | 1(Win) | true |
| simdjson (stage-1) | 14032.9 | 0.0578188 | 1563.67ms | 124597 | 640 | 15340.4 | 8467.57 | 0.00623664 | 0.368244 | 1.83555 | 0.0691992 | 1.5199e-05 | 2.33252e-06 | 1.1161e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14128.9 | 0.0478537 | 8194.84ms | 2251027 | 640 | 3.38343e+06 | 151940 | 0.00499348 | 0.360871 | 1.70348 | 0.0747922 | 0.00139843 | 0.0243022 | 1.98382e-06 | 1(Win) | true |
| simdjson (stage-1) | 11407 | 0.031895 | 5016.06ms | 2251027 | 1280 | 4.61183e+06 | 188196 | 0.047683 | 0.450521 | 2.09408 | 0.0806446 | 0.00144378 | 0.0241193 | 7.26752e-07 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18672.6 | 0.0572913 | 7282.83ms | 5373214 | 640 | 1.58204e+07 | 274429 | 0.160406 | 0.273837 | 1.37324 | 0.0519539 | 0.000768053 | 0.0195647 | 2.1321e-06 | 1(Win) | true |
| simdjson (stage-1) | 15264.2 | 0.0582586 | 8826.34ms | 5373214 | 640 | 2.44805e+07 | 335707 | 0.0547238 | 0.33626 | 1.59197 | 0.0578107 | 0.000948089 | 0.0195707 | 7.35768e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10491.5 | 0.0397545 | 5279.4ms | 500299 | 4890 | 1.59833e+06 | 45477.1 | 0.0166023 | 0.488778 | 2.49765 | 0.106702 | 8.28911e-06 | 7.94617e-07 | 8.01157e-08 | 1(Win) | true |
| simdjson (stage-1) | 9488.36 | 0.026248 | 5725.39ms | 500299 | 320 | 55746.6 | 50285 | 0.0785278 | 0.53296 | 2.79453 | 0.112549 | 2.23804e-05 | 4.53479e-06 | 2.65466e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13646.8 | 0.0820283 | 8833.17ms | 1151920 | 1280 | 5.58114e+06 | 80499.4 | 0.0764056 | 0.373714 | 1.80279 | 0.0672851 | 0.000171498 | 0.00416838 | 2.4036e-06 | 1(Win) | true |
| simdjson (stage-1) | 13486.9 | 0.0552441 | 8908.19ms | 1151920 | 1280 | 2.59179e+06 | 81453.4 | 0.0453292 | 0.381687 | 1.92828 | 0.0731258 | 0.000438934 | 0.00452261 | 1.50699e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10980.1 | 0.152412 | 1209.61ms | 56369 | 320 | 17818 | 4895.93 | 0.0454027 | 0.468842 | 2.28846 | 0.097199 | 0.000102228 | 3.49261e-06 | 4.43506e-07 | 1(Win) | true |
| simdjson (stage-1) | 10249.6 | 0.0780098 | 1244.72ms | 56369 | 640 | 10713.7 | 5244.83 | 0.18671 | 0.504741 | 2.58342 | 0.102929 | 5.36365e-05 | 2.74419e-06 | 0 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12287.7 | 0.0364229 | 1378.89ms | 83958 | 4890 | 27545.1 | 6516.18 | 0.00936325 | 0.415523 | 2.1361 | 0.189369 | 2.49784e-05 | 2.79135e-06 | 7.79433e-08 | 1(Win) | true |
| simdjson (stage-1) | 11935.3 | 0.0669634 | 1395.88ms | 83958 | 80 | 1614.43 | 6708.52 | 0.101633 | 0.426915 | 2.17586 | 0.0843755 | 3.87098e-05 | 6.69978e-06 | 5.95536e-07 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16847.9 | 0.0423181 | 1023.35ms | 53331 | 4890 | 7980.52 | 3018.8 | 0.0745734 | 0.309743 | 1.50764 | 0.0627029 | 5.51174e-05 | 3.56611e-06 | 7.89912e-07 | 1(Win) | true |
| simdjson (stage-1) | 14912.6 | 0.0478919 | 1059.04ms | 53331 | 1280 | 3414.96 | 3410.56 | 0.0546715 | 0.350033 | 1.73931 | 0.0650843 | 5.46557e-05 | 2.43175e-06 | 1.46491e-07 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16080.4 | 0.0267922 | 1105.82ms | 65103 | 4890 | 5232.81 | 3861.05 | 0.0121543 | 0.324985 | 1.60621 | 0.0591372 | 3.11697e-05 | 4.56411e-06 | 2.28048e-06 | 1(Win) | true |
| simdjson (stage-1) | 15858.1 | 0.0271431 | 1107.11ms | 65103 | 640 | 722.769 | 3915.16 | 0.0379789 | 0.328203 | 1.67697 | 0.0621477 | 3.00965e-05 | 2.64005e-06 | 2.64005e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10033.1 | 0.0664415 | 827.235ms | 11812 | 4890 | 2721.21 | 1122.76 | 0.108917 | 0.530592 | 2.50364 | 0.11082 | 8.50059e-05 | 1.69319e-05 | 5.15922e-06 | 1(Win) | true |
| simdjson (stage-1) | 9367.71 | 0.0688818 | 832.77ms | 11812 | 1280 | 878.211 | 1202.51 | 0.0540177 | 0.567757 | 2.80596 | 0.116576 | 8.50565e-05 | 9.12737e-06 | 5.29123e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13343.2 | 0.142345 | 906.269ms | 25388 | 80 | 533.719 | 1814.55 | 0.103225 | 0.387489 | 1.91386 | 0.15917 | 4.82511e-05 | 4.43123e-06 | 4.92359e-07 | 1(Win) | true |
| simdjson (stage-1) | 13282.7 | 0.0491307 | 903.004ms | 25388 | 160 | 128.325 | 1822.82 | 0.0599672 | 0.396152 | 1.96975 | 0.0766504 | 4.89897e-05 | 7.1392e-06 | 0 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11079.7 | 0.0609363 | 1654.72ms | 108313 | 320 | 10327.8 | 9322.94 | 0.0397699 | 0.466648 | 2.36527 | 0.101105 | 1.95614e-05 | 1.55798e-06 | 1.15406e-07 | 1(Win) | true |
| simdjson (stage-1) | 10309.5 | 0.0427905 | 1722.83ms | 108313 | 160 | 2941.04 | 10019.4 | 0.0732415 | 0.501644 | 2.66308 | 0.108962 | 4.24695e-05 | 2.30813e-06 | 0 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13100.2 | 0.0267463 | 2065.75ms | 183677 | 2560 | 32743.2 | 13371.4 | 0.0189368 | 0.391869 | 2.07013 | 0.181601 | 1.26709e-05 | 9.08099e-07 | 2.2543e-07 | 1(Win) | true |
| simdjson (stage-1) | 12694.1 | 0.136848 | 2098.79ms | 183677 | 160 | 57056.7 | 13799.2 | 0.0152159 | 0.401933 | 2.12612 | 0.082313 | 3.40612e-05 | 2.07565e-06 | 7.48597e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8854.35 | 0.0859828 | 5271.61ms | 1834197 | 640 | 1.84664e+07 | 197556 | 0.00658165 | 0.578732 | 2.89621 | 0.126786 | 0.00184286 | 0.0377792 | 4.42973e-06 | 1(Win) | true |
| simdjson (stage-1) | 7035.47 | 0.13586 | 6558.29ms | 1834197 | 30 | 3.42302e+06 | 248630 | 0.0595484 | 0.731756 | 3.29419 | 0.16035 | 0.00522728 | 0.0375697 | 3.63465e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14351.3 | 0.0792741 | 6309.82ms | 7351818 | 640 | 9.59959e+07 | 488546 | 0.0128017 | 0.350886 | 1.58341 | 0.0601814 | 0.00170032 | 0.0211487 | 0.00011783 | 1(Win) | true |
| simdjson (stage-1) | 13607.1 | 0.0877971 | 6652.73ms | 7351818 | 640 | 1.30978e+08 | 515262 | 0.200804 | 0.375578 | 1.77309 | 0.066041 | 0.00104619 | 0.0211862 | 0.000190253 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12505.9 | 0.0433368 | 4248.2ms | 461466 | 2560 | 595392 | 35190.4 | 0.0288059 | 0.40952 | 2.04594 | 0.0861841 | 7.93328e-06 | 4.33655e-06 | 2.93308e-06 | 1(Win) | true |
| simdjson (stage-1) | 11667.9 | 0.0324081 | 4514.94ms | 461466 | 4890 | 730652 | 37717.9 | 0.166562 | 0.438667 | 2.34282 | 0.0920242 | 1.43138e-05 | 3.73089e-06 | 2.28356e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13273.9 | 0.0376333 | 5968.98ms | 728486 | 4890 | 1.89715e+06 | 52338.8 | 0.00485236 | 0.386049 | 1.84159 | 0.0690515 | 1.05022e-05 | 0.00106715 | 2.61573e-06 | 1(Win) | true |
| simdjson (stage-1) | 13061.3 | 0.0525261 | 6035.32ms | 728486 | 320 | 249789 | 53190.8 | 0.0473697 | 0.393171 | 1.96642 | 0.0748814 | 0.000221731 | 0.000726876 | 1.23973e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15343.7 | 0.133104 | 3652.2ms | 466906 | 30 | 44761.3 | 29020.1 | 0.0231969 | 0.335913 | 1.68483 | 0.0697443 | 2.70576e-05 | 6.63231e-05 | 6.44669e-05 | 1(Win) | true |
| simdjson (stage-1) | 13936.3 | 0.0308916 | 3922.82ms | 466906 | 4890 | 476376 | 31950.7 | 0.0529718 | 0.368248 | 1.92737 | 0.0728648 | 2.42426e-05 | 1.9635e-06 | 1.15366e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14772.3 | 0.0333512 | 4803.16ms | 631514 | 4890 | 904076 | 40769.6 | 0.0618588 | 0.34222 | 1.6894 | 0.0621333 | 8.67393e-06 | 3.58991e-06 | 2.2985e-06 | 1(Win) | true |
| simdjson (stage-1) | 14618.9 | 0.0363982 | 4844.04ms | 631514 | 2560 | 575616 | 41197.2 | 0.0256758 | 0.350646 | 1.77513 | 0.0659353 | 3.43551e-05 | 2.62823e-06 | 1.97875e-06 | 2(Loss) | true |
