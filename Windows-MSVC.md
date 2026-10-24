# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

Latest Results: (Oct 24, 2026)
#### Using the following commits:
----
| Jsonifier: [cb40a92](https://github.com/nihilai-collective/jsonifier/commit/cb40a92)  
| simdjson(On Demand): [50f0739](https://github.com/simdjson/simdjson/commit/50f0739)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (AMD EPYC 7763 64-Core Processor-AVX2):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 10% and mean shift ≤ 5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **Stage-1 Only:** Both libraries execute only stage-1 parsing, identifying structural indices and nothing more.
* **No UTF-8 Validation:** Neither library performs UTF-8 validation in these tests.

---
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 206.231 | 0.1825 | 428.766ms | 905 | 40 | 2333.33 | 4185 | 0.119617 | 11.1861 | 1(Win) | true |
| simdjson (ondemand) | 84.553 | 0.0814192 | 1056.07ms | 905 | 40 | 2762.82 | 10207.5 | 0.0244858 | 27.4569 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 403.293 | 0.142075 | 436.688ms | 1811 | 40 | 1480.77 | 4282.5 | 0.174825 | 5.69311 | 1(Win) | true |
| simdjson (ondemand) | 164.623 | 0.249286 | 1062.11ms | 1811 | 4890 | 3.34473e+06 | 10491.3 | 0.0603474 | 14.1065 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 835.8 | 0.105115 | 452.951ms | 3862 | 30 | 643.678 | 4406.67 | 0.0755858 | 2.7617 | 1(Win) | true |
| simdjson (ondemand) | 363.105 | 0.112688 | 1040.58ms | 3862 | 30 | 3919.54 | 10143.3 | 0.196786 | 6.39759 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1592.41 | 0.332589 | 578.441ms | 9578 | 4890 | 1.77978e+06 | 5736.16 | 0.118638 | 1.45459 | 1(Win) | true |
| simdjson (ondemand) | 917.558 | 0.11902 | 1019.28ms | 9578 | 40 | 5615.38 | 9955 | 0.0502008 | 2.53549 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 835.652 | 0.144912 | 453.45ms | 3873 | 40 | 1641.03 | 4420 | 0.375657 | 2.76644 | 1(Win) | true |
| simdjson (ondemand) | 365.882 | 0.0656988 | 1031.1ms | 3873 | 80 | 3518.99 | 10095 | 0.197726 | 6.34925 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5321.49 | 0.195548 | 9570.26ms | 2090234 | 320 | 1.71703e+08 | 374595 | 0.0677773 | 0.438181 | 1(Win) | true |
| simdjson (ondemand) | 4099.43 | 0.104797 | 6180.04ms | 2090234 | 640 | 1.66196e+08 | 486263 | 0.0841171 | 0.568818 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8437.42 | 0.0796713 | 9573.01ms | 6661897 | 640 | 2.30335e+08 | 752989 | 0.0738438 | 0.276381 | 1(Win) | true |
| simdjson (ondemand) | 6312.31 | 0.0893451 | 6342.53ms | 6661897 | 320 | 2.58768e+08 | 1.00649e+06 | 0.00630324 | 0.369432 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3529.41 | 0.110889 | 6907.84ms | 500299 | 2560 | 5.75269e+07 | 135185 | 0.17581 | 0.660503 | 1(Win) | true |
| simdjson (ondemand) | 2973.28 | 0.130328 | 8213.52ms | 500299 | 1280 | 5.59854e+07 | 160470 | 0.118019 | 0.784056 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6133.7 | 0.183431 | 5708.15ms | 1439562 | 640 | 1.0788e+08 | 223825 | 0.0231015 | 0.380062 | 1(Win) | true |
| simdjson (ondemand) | 5109.9 | 0.106523 | 6857.34ms | 1439562 | 1280 | 1.04841e+08 | 268669 | 0.0922391 | 0.45629 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4151.17 | 0.0455599 | 1321.87ms | 56369 | 80 | 2784.81 | 12950 | 0.173444 | 0.560311 | 1(Win) | true |
| simdjson (ondemand) | 3362.49 | 0.182845 | 1606.91ms | 56369 | 4890 | 4.17863e+06 | 15987.5 | 0.0685897 | 0.691978 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5456.64 | 0.064568 | 1683.48ms | 94370 | 30 | 3402.3 | 16493.3 | 0.0202143 | 0.426601 | 1(Win) | true |
| simdjson (ondemand) | 4436.73 | 0.188811 | 2034.1ms | 94370 | 4890 | 7.17308e+06 | 20284.8 | 0.0656228 | 0.524649 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3650.74 | 0.074115 | 321.662ms | 11812 | 320 | 1673.59 | 3085.62 | 0.0202593 | 0.6314 | 1(Win) | true |
| simdjson (ondemand) | 3042.49 | 0.0957922 | 380.476ms | 11812 | 80 | 1006.33 | 3702.5 | 0 | 0.759559 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6334.51 | 0.0652486 | 483.852ms | 31235 | 80 | 753.165 | 4702.5 | 0.0531915 | 0.365384 | 1(Win) | true |
| simdjson (ondemand) | 5213.77 | 0.138743 | 586.034ms | 31235 | 30 | 1885.06 | 5713.33 | 0.290867 | 0.444009 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3850.18 | 0.167833 | 2690.16ms | 108313 | 4890 | 9.91431e+06 | 26828.7 | 0.117137 | 0.604845 | 1(Win) | true |
| simdjson (ondemand) | 3216.93 | 0.150919 | 3215.26ms | 108313 | 4890 | 1.14836e+07 | 32109.9 | 0.063717 | 0.724061 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5735.53 | 0.178068 | 3559.97ms | 213963 | 2560 | 1.02741e+07 | 35576.6 | 0.0294173 | 0.406104 | 1(Win) | true |
| simdjson (ondemand) | 4756.86 | 0.18839 | 4302.54ms | 213963 | 2560 | 1.67183e+07 | 42896.1 | 0.0263103 | 0.489808 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2800.59 | 0.170966 | 7938.26ms | 1834197 | 320 | 3.6489e+08 | 624593 | 0.134117 | 0.832647 | 1(Win) | true |
| simdjson (ondemand) | 2413.08 | 0.0774399 | 9257.39ms | 1834197 | 640 | 2.01677e+08 | 724892 | 0.0173918 | 0.966369 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7202.45 | 0.0678001 | 8295.07ms | 9930848 | 320 | 2.54345e+08 | 1.31494e+06 | 0.0220494 | 0.323779 | 1(Win) | true |
| simdjson (ondemand) | 5738.12 | 0.0941019 | 5123.58ms | 9930848 | 80 | 1.92983e+08 | 1.6505e+06 | 0.0167345 | 0.406409 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4033.11 | 0.138447 | 7777.54ms | 642697 | 1280 | 5.66639e+07 | 151973 | 0.0262245 | 0.578051 | 1(Win) | true |
| simdjson (ondemand) | 3337.23 | 0.0915908 | 9388.91ms | 642697 | 2560 | 7.24408e+07 | 183662 | 0.00589107 | 0.698586 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5806.2 | 0.174964 | 5160.56ms | 1225964 | 640 | 7.94413e+07 | 201366 | 0.00675123 | 0.401558 | 1(Win) | true |
| simdjson (ondemand) | 4637.49 | 0.150747 | 6445.73ms | 1225964 | 640 | 9.24422e+07 | 252113 | 0.126457 | 0.50276 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4343.05 | 0.096469 | 9018.21ms | 409725 | 4890 | 3.68366e+07 | 89969.9 | 0.0429914 | 0.53666 | 1(Win) | true |
| simdjson (ondemand) | 3533.48 | 0.117649 | 5657.97ms | 409725 | 2560 | 4.3331e+07 | 110583 | 0.0838235 | 0.659648 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6013.3 | 0.115931 | 6369.16ms | 785750 | 2560 | 5.34294e+07 | 124615 | 0.015044 | 0.387663 | 1(Win) | true |
| simdjson (ondemand) | 4916.99 | 0.101249 | 7791.6ms | 785750 | 2560 | 6.09524e+07 | 152400 | 0.0912546 | 0.47411 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5796.07 | 0.142441 | 4352.52ms | 264040 | 4890 | 1.87262e+07 | 43444.6 | 0.0364161 | 0.401948 | 1(Win) | true |
| simdjson (ondemand) | 4631.12 | 0.122016 | 5443.93ms | 264040 | 4890 | 2.15233e+07 | 54373 | 0.0702491 | 0.503187 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6486.03 | 0.129953 | 5886.51ms | 399947 | 4890 | 2.8558e+07 | 58806.3 | 0.149628 | 0.35931 | 1(Win) | true |
| simdjson (ondemand) | 5384.57 | 0.116522 | 7153.06ms | 399947 | 4890 | 3.33142e+07 | 70835.6 | 0.0535177 | 0.432833 | 2(Loss) | true |
