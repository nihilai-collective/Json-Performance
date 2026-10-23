# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

Latest Results: (Oct 23, 2026)
#### Using the following commits:
----
| Jsonifier: [b975cd7](https://github.com/nihilai-collective/jsonifier/commit/b975cd7)  
| simdjson(On Demand): [70f83c9](https://github.com/simdjson/simdjson/commit/70f83c9)  

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
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 365.013 | 0.0423279 | 956.601ms | 905 | 1280 | 1282.17 | 2364.51 | 0.180297 | 14.3499 | 38 | 5.18895 | 0.00263381 | 0.000128626 | 1.46754e-05 | 1(Win) | true |
| simdjson (ondemand) | 235.469 | 0.0358932 | 1081.69ms | 905 | 1280 | 2215.47 | 3665.35 | 0.0112741 | 22.1304 | 86.8906 | 8.00663 | 0.00331664 | 0.000143301 | 1.46754e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 745.864 | 0.0325011 | 949.859ms | 1811 | 2560 | 1449.95 | 2315.58 | 0.153122 | 6.9812 | 18.4434 | 2.43622 | 0.0010953 | 9.27492e-05 | 5.82379e-06 | 1(Win) | true |
| simdjson (ondemand) | 463.886 | 0.088794 | 1092.87ms | 1811 | 640 | 6994.59 | 3723.12 | 0.0136413 | 11.118 | 43.2849 | 3.9481 | 0.000611713 | 6.64343e-05 | 7.76505e-06 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1507.74 | 0.0354126 | 965.349ms | 3862 | 80 | 59.8657 | 2442.79 | 0.0209757 | 3.41203 | 8.12791 | 0.957017 | 0.00054376 | 3.56033e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1007.06 | 0.0567384 | 1092.11ms | 3862 | 80 | 344.475 | 3657.26 | 0.0379238 | 5.17192 | 20.1543 | 1.77266 | 0.000517866 | 5.50233e-05 | 2.26567e-05 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2791.05 | 0.0335407 | 1045.85ms | 9578 | 160 | 192.787 | 3272.71 | 0.00630252 | 1.86813 | 4.6375 | 0.5237 | 0.000201634 | 2.21863e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2177.75 | 0.0703257 | 1136.54ms | 9578 | 40 | 348.035 | 4194.38 | 0.0800035 | 2.34623 | 8.14951 | 0.715389 | 0.00052203 | 1.04406e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1524.76 | 0.0376945 | 959.132ms | 3873 | 2560 | 2134.46 | 2422.4 | 0.0551637 | 3.41394 | 8.10483 | 0.9543 | 0.000518816 | 3.68134e-05 | 2.01717e-07 | 1(Win) | true |
| simdjson (ondemand) | 1015.26 | 0.127403 | 1086.94ms | 3873 | 320 | 6874.69 | 3638.08 | 0.0895848 | 5.12718 | 20.0971 | 1.76762 | 0.000766525 | 5.56739e-05 | 0 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 10702.8 | 0.106706 | 5048.22ms | 2090234 | 80 | 3.15981e+06 | 186251 | 0.168694 | 0.479208 | 2.14792 | 0.0827425 | 0.00252928 | 0.0250535 | 9.4487e-07 | 1(Win) | true |
| jsonifier | 10126.2 | 0.365037 | 5229.95ms | 2090234 | 640 | 3.30488e+08 | 196857 | 0.356123 | 0.498876 | 1.73348 | 0.193212 | 0.00592304 | 0.0252381 | 6.54083e-07 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 15873.8 | 0.382165 | 5224.96ms | 6661897 | 160 | 3.74333e+08 | 400237 | 0.0839172 | 0.320727 | 1.53963 | 0.0550758 | 0.00025039 | 0.0188324 | 1.69152e-06 | 1(Win) | true |
| jsonifier | 15541.4 | 0.264727 | 5297.11ms | 6661897 | 640 | 7.4954e+08 | 408798 | 0.236458 | 0.325869 | 1.23093 | 0.0834081 | 0.00241169 | 0.0188216 | 1.51538e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10338.7 | 0.0229089 | 5325.74ms | 500299 | 640 | 71535 | 46149.3 | 0.00400211 | 0.488983 | 2.49908 | 0.305176 | 2.69308e-05 | 1.16805e-06 | 1.21802e-07 | 1(Win) | true |
| simdjson (ondemand) | 9735.1 | 0.185548 | 5682.85ms | 500299 | 2560 | 2.11705e+07 | 49010.5 | 0.204646 | 0.527814 | 2.80271 | 0.112581 | 1.74443e-05 | 0.000262211 | 3.69935e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15341.5 | 0.307219 | 9646.75ms | 1439562 | 1280 | 9.67453e+07 | 89487.5 | 0.141906 | 0.328236 | 1.58772 | 0.127732 | 6.80361e-05 | 0.00560426 | 2.69396e-06 | 1(Win) | true |
| simdjson (ondemand) | 13604.1 | 0.107204 | 5652.38ms | 1439562 | 80 | 936337 | 100916 | 0.514721 | 0.377265 | 1.8607 | 0.069697 | 0.00040152 | 0.00685753 | 1.14271e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11206.2 | 0.0267027 | 1204.06ms | 56369 | 4890 | 8023.82 | 4797.12 | 0.0525906 | 0.46325 | 2.27632 | 0.265483 | 5.78535e-05 | 4.05232e-06 | 7.7999e-07 | 1(Win) | true |
| simdjson (ondemand) | 10231.2 | 0.0633959 | 1246.8ms | 56369 | 640 | 7101.19 | 5254.3 | 0.0439714 | 0.506645 | 2.59197 | 0.103053 | 3.52865e-05 | 2.93823e-06 | 0 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13539.4 | 0.0454999 | 1390.02ms | 94370 | 160 | 1463.55 | 6647.12 | 0.0102499 | 0.382882 | 1.86556 | 0.17193 | 2.36436e-05 | 1.66234e-05 | 1.4769e-05 | 1(Win) | true |
| simdjson (ondemand) | 12985.6 | 0.0467243 | 1411.72ms | 94370 | 2560 | 26845.3 | 6930.62 | 0.120122 | 0.398439 | 2.10263 | 0.0807354 | 2.13132e-05 | 1.92063e-06 | 2.40079e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10222.1 | 0.084593 | 831.069ms | 11812 | 160 | 139.044 | 1102 | 0.0362845 | 0.52245 | 2.48925 | 0.30342 | 8.46597e-05 | 1.79902e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9365.06 | 0.0451239 | 832.094ms | 11812 | 4890 | 1440.62 | 1202.85 | 0.0286418 | 0.567338 | 2.8173 | 0.117169 | 8.49713e-05 | 1.15303e-05 | 9.8683e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15397.2 | 0.0442984 | 913.38ms | 31235 | 320 | 235.033 | 1934.64 | 0.0555349 | 0.340785 | 1.63762 | 0.135169 | 6.01289e-05 | 9.10437e-06 | 4.00192e-07 | 1(Win) | true |
| simdjson (ondemand) | 13882.8 | 0.0873037 | 932.702ms | 31235 | 1280 | 4491.66 | 2145.68 | 0.062332 | 0.377652 | 1.89192 | 0.0727069 | 0.000209501 | 6.40307e-06 | 9.50456e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10857.9 | 0.0346727 | 1680.84ms | 108313 | 2560 | 27853.9 | 9513.39 | 0.10202 | 0.475453 | 2.37744 | 0.284952 | 2.00807e-05 | 4.21954e-06 | 2.44156e-06 | 1(Win) | true |
| simdjson (ondemand) | 10034.9 | 0.0213393 | 1753.11ms | 108313 | 4890 | 23594.4 | 10293.7 | 0.03259 | 0.514214 | 2.6713 | 0.109027 | 4.61078e-05 | 3.08694e-06 | 1.31407e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14148.5 | 0.166866 | 2170.2ms | 213963 | 80 | 46331.9 | 14422 | 0.0103997 | 0.364439 | 1.78818 | 0.160645 | 2.4128e-05 | 2.57054e-06 | 1.40211e-06 | 1(Win) | true |
| simdjson (ondemand) | 13529.3 | 0.113259 | 2236.59ms | 213963 | 80 | 23343.2 | 15082.2 | 0.00066303 | 0.381467 | 2.00336 | 0.0763824 | 3.51696e-05 | 2.51212e-06 | 2.10317e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7155.88 | 0.0897211 | 6436.31ms | 1834197 | 1280 | 6.15694e+07 | 244446 | 0.0752293 | 0.71381 | 3.29497 | 0.15753 | 0.00364107 | 0.0376078 | 8.47122e-05 | 1(Win) | true |
| jsonifier | 6581.53 | 0.174668 | 7013.3ms | 1834197 | 160 | 3.44812e+07 | 265778 | 0.0297975 | 0.771234 | 2.92608 | 0.383816 | 0.00788758 | 0.0378256 | 0.000136221 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 15044.8 | 0.0495962 | 8107.65ms | 9930848 | 640 | 6.23846e+07 | 629507 | 0.0555599 | 0.337907 | 1.67435 | 0.0611974 | 0.000491312 | 0.0197539 | 8.10406e-05 | 1(Win) | true |
| jsonifier | 13432.2 | 0.31868 | 9102.27ms | 9930848 | 30 | 1.51465e+08 | 705084 | 0.0665152 | 0.377762 | 1.34067 | 0.0979591 | 0.00378675 | 0.0197538 | 7.82108e-05 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11929 | 0.0269372 | 5888.62ms | 642697 | 4890 | 936739 | 51381.1 | 0.344259 | 0.427541 | 2.20469 | 0.271809 | 2.56508e-05 | 2.80821e-05 | 4.16923e-06 | 1(Win) | true |
| simdjson (ondemand) | 9225.71 | 0.0560934 | 7373.97ms | 642697 | 160 | 222207 | 66436.5 | 0.0857508 | 0.557863 | 2.65804 | 0.130169 | 0.000139782 | 0.00441651 | 1.09888e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14874.2 | 0.0820534 | 8579.64ms | 1225964 | 640 | 2.66232e+06 | 78603.8 | 0.0836039 | 0.341721 | 1.68025 | 0.158286 | 0.000206008 | 0.00355594 | 2.72337e-05 | 1(Win) | true |
| simdjson (ondemand) | 13025.6 | 0.0437135 | 9763.55ms | 1225964 | 4890 | 7.52835e+06 | 89759.5 | 0.0336204 | 0.394166 | 2.02815 | 0.0773156 | 2.06048e-05 | 0.00557398 | 2.09621e-05 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11909.7 | 0.0176582 | 4013.05ms | 409725 | 4890 | 164129 | 32809 | 0.0951896 | 0.430678 | 2.15719 | 0.248206 | 1.47493e-05 | 3.3196e-06 | 2.84993e-06 | 1(Win) | true |
| simdjson (ondemand) | 10774.1 | 0.0407527 | 4366.03ms | 409725 | 320 | 69902.1 | 36267.1 | 0.0678098 | 0.478168 | 2.46957 | 0.097463 | 2.96845e-05 | 8.92367e-07 | 4.19489e-07 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14799.3 | 0.0310425 | 5763.19ms | 785750 | 2560 | 632473 | 50634.2 | 0.0301536 | 0.34371 | 1.69625 | 0.145334 | 6.63876e-06 | 3.62094e-05 | 2.39769e-06 | 1(Win) | true |
| simdjson (ondemand) | 13616.7 | 0.121881 | 6236.24ms | 785750 | 4890 | 2.19993e+07 | 55031.8 | 0.0365957 | 0.373466 | 1.91404 | 0.0721515 | 0.000181783 | 0.00185923 | 4.9478e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15571.9 | 0.0974259 | 2359.95ms | 264040 | 80 | 19856.1 | 16170.6 | 0.0154625 | 0.331491 | 1.65668 | 0.164877 | 4.71993e-05 | 9.75231e-06 | 8.52144e-06 | 1(Win) | true |
| simdjson (ondemand) | 13138.8 | 0.021978 | 2639.21ms | 264040 | 2560 | 45419.7 | 19165.3 | 0.0350874 | 0.392156 | 1.99398 | 0.0756439 | 1.19847e-05 | 7.41187e-07 | 1.44983e-07 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16281.7 | 0.0615413 | 3088.88ms | 399947 | 160 | 33254.9 | 23426.2 | 0.112088 | 0.316687 | 1.54276 | 0.120081 | 8.90743e-06 | 7.34472e-07 | 7.81354e-08 | 1(Win) | true |
| simdjson (ondemand) | 14618.1 | 0.130024 | 3337.74ms | 399947 | 30 | 34529.7 | 26092.3 | 0.0614108 | 0.352597 | 1.77291 | 0.0655738 | 5.71742e-05 | 5.00066e-07 | 0 | 2(Loss) | true |
