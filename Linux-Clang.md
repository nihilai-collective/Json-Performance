# Json-Performance: Stage-1 Parsing
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1181.47 | 0.153988 | 778.603ms | 905 | 320 | 404.928 | 730.513 | 0.00171116 | 4.60225 | 22.9392 | 2.29503 | 0.00450276 | 0.000131215 | 2.41713e-05 | 1(Win) | true |
| simdjson (stage-1) | 449.47 | 0.127228 | 906.692ms | 905 | 1280 | 7639.65 | 1920.21 | 0.0997795 | 11.6798 | 61.2597 | 4.91381 | 0.00221081 | 0.000108771 | 1.55387e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2214.77 | 0.348472 | 789.358ms | 1811 | 320 | 2363.01 | 779.812 | 0.137664 | 2.447 | 11.4666 | 1.15075 | 0.00101808 | 3.10602e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 902.545 | 0.0399079 | 904.146ms | 1811 | 160 | 93.3119 | 1913.59 | 0.0114327 | 5.82693 | 30.6129 | 2.45555 | 0.00133559 | 7.59249e-05 | 0 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4976.57 | 0.127635 | 781.654ms | 3862 | 4890 | 4363.29 | 740.086 | 0.221002 | 1.09433 | 5.31978 | 0.535474 | 0.00121815 | 4.71799e-05 | 1.57266e-05 | 1(Win) | true |
| simdjson (stage-1) | 1915.16 | 0.0725445 | 907.835ms | 3862 | 320 | 622.835 | 1923.12 | 0.131632 | 2.74707 | 14.3553 | 1.15148 | 0.000641669 | 3.3985e-05 | 8.90083e-06 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7029.23 | 0.103059 | 841.581ms | 9578 | 1280 | 2295.69 | 1299.47 | 0.0508362 | 0.755747 | 3.59626 | 0.338066 | 0.00102987 | 1.10931e-05 | 1.95761e-06 | 1(Win) | true |
| simdjson (stage-1) | 4297.26 | 0.0418143 | 924.046ms | 9578 | 1280 | 1011.17 | 2125.61 | 0.00701956 | 1.22163 | 5.95218 | 0.484861 | 0.00087856 | 1.01143e-05 | 3.26269e-07 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5068.33 | 0.127266 | 778.67ms | 3873 | 4890 | 4206.25 | 728.756 | 0.202872 | 1.08024 | 5.29176 | 0.530855 | 0.000769841 | 2.76678e-05 | 1.79524e-06 | 1(Win) | true |
| simdjson (stage-1) | 1932.52 | 0.0373002 | 904.245ms | 3873 | 4890 | 2485.28 | 1911.27 | 0.00837318 | 2.71816 | 14.3145 | 1.14821 | 0.000621945 | 4.93163e-05 | 1.41507e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16292.8 | 0.0548548 | 1276.21ms | 94653 | 80 | 738.921 | 5540.38 | 0.0428855 | 0.318544 | 1.76926 | 0.0889459 | 2.11298e-05 | 3.82978e-06 | 2.24504e-06 | 1(Win) | true |
| simdjson (stage-1) | 13620.4 | 0.0245379 | 1377.77ms | 94653 | 40 | 105.785 | 6627.4 | 0.0155943 | 0.380575 | 1.81501 | 0.0771766 | 1.90168e-05 | 2.11298e-06 | 0 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15898.7 | 0.0568606 | 1466.78ms | 124597 | 160 | 2889.57 | 7473.86 | 0.159811 | 0.325816 | 1.76336 | 0.0810052 | 9.15953e-05 | 1.75566e-06 | 7.02264e-07 | 1(Win) | true |
| simdjson (stage-1) | 14741.4 | 0.0273253 | 1521.99ms | 124597 | 2560 | 12419.6 | 8060.65 | 0.0176124 | 0.351031 | 1.64946 | 0.0692553 | 2.46106e-05 | 1.98766e-06 | 9.43667e-07 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14278.6 | 0.0229672 | 8106.72ms | 2251027 | 2560 | 3.05245e+06 | 150347 | 0.167334 | 0.357046 | 1.7439 | 0.0767384 | 0.00152989 | 0.0248706 | 1.88247e-06 | 1(Win) | true |
| simdjson (stage-1) | 11465.9 | 0.0310113 | 9968.85ms | 2251027 | 640 | 2.15759e+06 | 187229 | 0.142635 | 0.447819 | 1.89627 | 0.0806442 | 0.00173416 | 0.0244882 | 1.32578e-06 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18355.2 | 0.050257 | 7331.19ms | 5373214 | 640 | 1.25986e+07 | 279174 | 0.0154326 | 0.274664 | 1.42166 | 0.0539043 | 0.000789868 | 0.0195626 | 3.57764e-06 | 1(Win) | true |
| simdjson (stage-1) | 15514.3 | 0.0404189 | 8698.31ms | 5373214 | 80 | 1.42582e+06 | 330295 | 0.0190131 | 0.331497 | 1.41698 | 0.0578105 | 0.000929546 | 0.019574 | 9.80326e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10777.1 | 0.0259873 | 5144.11ms | 500299 | 640 | 84715.5 | 44272 | 0.0226848 | 0.477998 | 2.53347 | 0.124274 | 2.16402e-05 | 4.185e-07 | 1.24925e-08 | 1(Win) | true |
| simdjson (stage-1) | 9575.93 | 0.040741 | 5720.32ms | 500299 | 160 | 65929.7 | 49825.2 | 0.0411019 | 0.538064 | 2.57778 | 0.112553 | 2.04128e-05 | 2.12373e-06 | 1.64901e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14878.5 | 0.0295431 | 8097.66ms | 1151920 | 1280 | 609040 | 73835 | 0.167644 | 0.341455 | 1.85059 | 0.0847481 | 0.000535529 | 1.82257e-05 | 1.30896e-07 | 1(Win) | true |
| simdjson (stage-1) | 13806.7 | 0.0164591 | 8694.21ms | 1151920 | 4890 | 838650 | 79566.7 | 0.00481507 | 0.371048 | 1.73799 | 0.0731258 | 0.000252162 | 4.51367e-06 | 4.28555e-07 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11485 | 0.076411 | 1185.06ms | 56369 | 1280 | 16373.6 | 4680.7 | 0.0155249 | 0.452399 | 2.32839 | 0.115844 | 8.50146e-05 | 3.09068e-06 | 1.03947e-06 | 1(Win) | true |
| simdjson (stage-1) | 10431.4 | 0.0210767 | 1229.77ms | 56369 | 4890 | 5769.09 | 5153.42 | 0.00579385 | 0.497312 | 2.37178 | 0.103621 | 3.48601e-05 | 2.04249e-06 | 6.16737e-08 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13346.6 | 0.0471698 | 1316.78ms | 83958 | 4890 | 39158.2 | 5999.19 | 0.0262016 | 0.387092 | 2.08926 | 0.0970248 | 3.68161e-05 | 2.8157e-06 | 1.15697e-06 | 1(Win) | true |
| simdjson (stage-1) | 12610.8 | 0.0934905 | 1349.67ms | 83958 | 4890 | 172299 | 6349.21 | 0.0174809 | 0.409473 | 1.97265 | 0.0848163 | 4.38894e-05 | 2.18485e-06 | 5.45603e-07 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17740.2 | 0.059707 | 1004.59ms | 53331 | 2560 | 7501.27 | 2866.96 | 0.00876013 | 0.294407 | 1.56633 | 0.0780785 | 3.81462e-05 | 3.37661e-06 | 9.59515e-07 | 1(Win) | true |
| simdjson (stage-1) | 15451.1 | 0.0519368 | 1046.21ms | 53331 | 1280 | 3741.12 | 3291.71 | 0.030892 | 0.337255 | 1.56335 | 0.0662467 | 3.35903e-05 | 3.14955e-06 | 8.05699e-07 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17075.6 | 0.0301399 | 1082.54ms | 65103 | 160 | 192.157 | 3636.02 | 0.0469043 | 0.305083 | 1.6557 | 0.0748967 | 3.09126e-05 | 3.64807e-06 | 7.68014e-07 | 1(Win) | true |
| simdjson (stage-1) | 16149.8 | 0.043239 | 1100.01ms | 65103 | 1280 | 3536.96 | 3844.45 | 0.117381 | 0.322123 | 1.50202 | 0.0630693 | 2.94725e-05 | 2.40004e-06 | 3.84007e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10233.4 | 0.148425 | 822.78ms | 11812 | 1280 | 3416.91 | 1100.79 | 0.142074 | 0.520994 | 2.54004 | 0.128175 | 8.57179e-05 | 6.74632e-06 | 4.62983e-07 | 1(Win) | true |
| simdjson (stage-1) | 9490.54 | 0.0751527 | 835.284ms | 11812 | 4890 | 3891.02 | 1186.95 | 0.0615907 | 0.558902 | 2.58874 | 0.116581 | 8.55946e-05 | 9.21042e-06 | 1.78322e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14996.7 | 0.0378685 | 877.241ms | 25388 | 320 | 119.611 | 1614.48 | 0.034272 | 0.352173 | 1.88699 | 0.0881913 | 5.00975e-05 | 5.29285e-06 | 8.61628e-07 | 1(Win) | true |
| simdjson (stage-1) | 13833 | 0.0656696 | 889.981ms | 25388 | 2560 | 3382.15 | 1750.3 | 0.0441414 | 0.380563 | 1.77651 | 0.0766504 | 3.96195e-05 | 5.03129e-06 | 3.53883e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11418.7 | 0.108195 | 1631.38ms | 108313 | 160 | 15327.1 | 9046.14 | 0.0611131 | 0.452618 | 2.40346 | 0.118518 | 5.86841e-05 | 2.48123e-06 | 9.80953e-07 | 1(Win) | true |
| simdjson (stage-1) | 10068.3 | 0.0282564 | 1745.21ms | 108313 | 30 | 252.116 | 10259.4 | 0.00844822 | 0.51395 | 2.45259 | 0.108879 | 9.29405e-05 | 1.53875e-06 | 0 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13609.1 | 0.0545825 | 2014.19ms | 183677 | 160 | 7897.23 | 12871.3 | 0.0387824 | 0.379605 | 2.04089 | 0.0940401 | 2.34447e-05 | 3.47077e-06 | 2.24579e-06 | 1(Win) | true |
| simdjson (stage-1) | 12913.3 | 0.0370526 | 2080.57ms | 183677 | 640 | 16167.9 | 13565 | 0.0541889 | 0.399774 | 1.92758 | 0.0823348 | 2.66603e-05 | 1.74389e-06 | 1.01231e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8769.42 | 0.0469552 | 5304.31ms | 1834197 | 1280 | 1.12286e+07 | 199469 | 0.224468 | 0.580963 | 2.90983 | 0.136897 | 0.00243167 | 0.0377043 | 3.16726e-06 | 1(Win) | true |
| simdjson (stage-1) | 6950.3 | 0.062105 | 6639.29ms | 1834197 | 1280 | 3.12714e+07 | 251676 | 0.163301 | 0.737297 | 3.04774 | 0.152978 | 0.00462363 | 0.0376875 | 2.40526e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15518 | 0.0635401 | 5851.05ms | 7351818 | 640 | 5.27465e+07 | 451813 | 0.164742 | 0.32565 | 1.62913 | 0.0669813 | 0.0011457 | 0.0211473 | 6.34176e-06 | 1(Win) | true |
| simdjson (stage-1) | 13971.2 | 0.0912174 | 6491.67ms | 7351818 | 320 | 6.70542e+07 | 501834 | 0.15245 | 0.365089 | 1.58986 | 0.0660409 | 0.000836977 | 0.0211816 | 0.000157626 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13192.4 | 0.0466546 | 4056.6ms | 461466 | 640 | 155024 | 33359.2 | 0.0279705 | 0.387229 | 2.09417 | 0.103752 | 3.05887e-05 | 1.52029e-06 | 1.11736e-06 | 1(Win) | true |
| simdjson (stage-1) | 11635.3 | 0.0306163 | 4510.68ms | 461466 | 4890 | 655751 | 37823.5 | 0.0940896 | 0.440192 | 2.14083 | 0.092022 | 7.6829e-06 | 5.61162e-06 | 4.94113e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14379.3 | 0.0975204 | 5521.65ms | 728486 | 160 | 355205 | 48315.3 | 0.305643 | 0.351319 | 1.88741 | 0.0866016 | 0.000357574 | 1.5014e-06 | 1.08959e-06 | 1(Win) | true |
| simdjson (stage-1) | 13782.7 | 0.0513843 | 5761.87ms | 728486 | 1280 | 858711 | 50406.7 | 0.0956485 | 0.371385 | 1.77437 | 0.0748814 | 1.10632e-05 | 2.87626e-06 | 2.34969e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16160.1 | 0.0393792 | 3480.41ms | 466906 | 4890 | 575719 | 27554 | 0.101065 | 0.314982 | 1.73857 | 0.0858482 | 2.21013e-05 | 1.79005e-06 | 1.33761e-06 | 1(Win) | true |
| simdjson (stage-1) | 14041.4 | 0.0264913 | 3908.22ms | 466906 | 640 | 45167.3 | 31711.6 | 0.0943852 | 0.367015 | 1.74354 | 0.073925 | 5.7292e-06 | 2.73409e-06 | 2.23211e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16009.5 | 0.0605804 | 4503.15ms | 631514 | 1280 | 664788 | 37618.8 | 0.0632533 | 0.316192 | 1.73716 | 0.0785035 | 2.53038e-05 | 2.69565e-06 | 2.2837e-06 | 1(Win) | true |
| simdjson (stage-1) | 15215.4 | 0.0375037 | 4689.62ms | 631514 | 2560 | 564143 | 39582.2 | 0.0949827 | 0.337967 | 1.59418 | 0.0666589 | 2.14471e-05 | 6.35996e-06 | 5.70492e-06 | 2(Loss) | true |
