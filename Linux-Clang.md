# Json-Performance: Stage-1 Parsing
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

Latest Results: (Nov 17, 2026)
#### Using the following commits:
----
| Jsonifier: [79b3e67](https://github.com/nihilai-collective/Jsonifier/commit/79b3e67)  
| simdjson: [36c5b3cfc](https://github.com/simdjson/simdjson/commit/36c5b3cfc)  

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
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1198.05 | 0.0492712 | 780.303ms | 905 | 4890 | 616.091 | 720.402 | 0.292749 | 4.53714 | 22.9392 | 2.29503 | 0.00450689 | 5.89771e-05 | 4.97125e-06 | 1(Win) | true |
| simdjson (stage-1) | 448.728 | 0.0489501 | 913.063ms | 905 | 4890 | 4334.57 | 1923.38 | 0.00477054 | 11.6911 | 61.2597 | 4.91381 | 0.0029475 | 8.13477e-05 | 1.46878e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2314.71 | 0.105489 | 786.107ms | 1811 | 2560 | 1585.98 | 746.143 | 0.51225 | 2.33613 | 11.4666 | 1.15075 | 0.000836684 | 4.6806e-05 | 5.39239e-06 | 1(Win) | true |
| simdjson (stage-1) | 893.622 | 0.0855894 | 904.442ms | 1811 | 1280 | 3502.51 | 1932.7 | 0.111442 | 5.86527 | 30.6129 | 2.45555 | 0.00135284 | 9.01608e-05 | 2.15696e-05 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5256.69 | 0.133658 | 781.343ms | 3862 | 640 | 561.271 | 700.648 | 0.0955789 | 1.03616 | 5.31978 | 0.535474 | 0.00129467 | 3.35804e-05 | 6.06875e-06 | 1(Win) | true |
| simdjson (stage-1) | 1921.61 | 0.0510862 | 903.949ms | 3862 | 4890 | 4688.25 | 1916.67 | 0.0359382 | 2.7296 | 14.3553 | 1.15148 | 0.000646645 | 2.97058e-05 | 1.5356e-06 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6862.01 | 0.108718 | 846.198ms | 9578 | 1280 | 2680.75 | 1331.14 | 0.265514 | 0.767823 | 3.59626 | 0.338066 | 0.0010191 | 1.08484e-05 | 4.56776e-06 | 1(Win) | true |
| simdjson (stage-1) | 4382.16 | 0.0523256 | 927.499ms | 9578 | 40 | 47.584 | 2084.43 | 0.0818899 | 1.22195 | 5.95218 | 0.484861 | 0.000944874 | 1.56609e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4889.23 | 0.145607 | 780.582ms | 3873 | 640 | 774.392 | 755.453 | 0.0421754 | 1.11015 | 5.29176 | 0.530855 | 0.0007754 | 2.78369e-05 | 4.03434e-06 | 1(Win) | true |
| simdjson (stage-1) | 1926.94 | 0.0365836 | 904.151ms | 3873 | 4890 | 2404.58 | 1916.81 | 0.0238255 | 2.72288 | 14.3145 | 1.14821 | 0.000854798 | 3.33703e-05 | 3.32647e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16210.2 | 0.0214823 | 1272.44ms | 94653 | 4890 | 6997.81 | 5568.59 | 0.0280825 | 0.319779 | 1.76926 | 0.088946 | 2.1724e-05 | 1.97903e-06 | 5.31486e-07 | 1(Win) | true |
| simdjson (stage-1) | 13596.3 | 0.0743225 | 1378.92ms | 94653 | 40 | 973.926 | 6639.15 | 0.0917122 | 0.381502 | 1.81501 | 0.0771766 | 5.54658e-05 | 1.84886e-06 | 2.64123e-07 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16128.3 | 0.035963 | 1469.38ms | 124597 | 80 | 561.62 | 7367.5 | 0.0403964 | 0.321141 | 1.76336 | 0.0810052 | 2.37767e-05 | 1.7055e-06 | 1.00323e-07 | 1(Win) | true |
| simdjson (stage-1) | 14729.7 | 0.0290612 | 1520.51ms | 124597 | 2560 | 14070.1 | 8067.06 | 0.0226274 | 0.350973 | 1.64946 | 0.0692553 | 2.63412e-05 | 2.80279e-06 | 1.59577e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14160.5 | 0.0938104 | 8229.79ms | 2251027 | 640 | 1.29445e+07 | 151601 | 0.240952 | 0.357626 | 1.7439 | 0.0767384 | 0.00151847 | 0.02474 | 1.86651e-06 | 1(Win) | true |
| simdjson (stage-1) | 11462.9 | 0.153349 | 10074.5ms | 2251027 | 40 | 3.29906e+06 | 187277 | 0.699295 | 0.445487 | 1.89627 | 0.0806442 | 0.00166777 | 0.024297 | 7.21893e-07 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18355.4 | 0.113652 | 7381.85ms | 5373214 | 320 | 3.22141e+07 | 279170 | 0.122415 | 0.274969 | 1.42166 | 0.0539043 | 0.000791468 | 0.0195641 | 2.44558e-06 | 1(Win) | true |
| simdjson (stage-1) | 15350 | 0.127389 | 8823.65ms | 5373214 | 320 | 5.78716e+07 | 333830 | 0.0260702 | 0.332169 | 1.41698 | 0.0578105 | 0.00092991 | 0.0195773 | 2.72358e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10735.5 | 0.0202708 | 5176ms | 500299 | 2560 | 207776 | 44443.2 | 0.0724575 | 0.478129 | 2.53347 | 0.124274 | 2.08336e-05 | 2.14403e-06 | 1.66853e-06 | 1(Win) | true |
| simdjson (stage-1) | 9526.75 | 0.0701441 | 5747.6ms | 500299 | 1280 | 1.57965e+06 | 50082.4 | 0.0105752 | 0.539744 | 2.57778 | 0.112553 | 2.15637e-05 | 7.01268e-05 | 6.48987e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14810.7 | 0.173329 | 8232.45ms | 1151920 | 4890 | 8.0825e+07 | 74173 | 0.172166 | 0.343926 | 1.85059 | 0.0847481 | 0.000530078 | 0.00340018 | 1.93915e-06 | 1(Win) | true |
| simdjson (stage-1) | 13727 | 0.0704266 | 8870.69ms | 1151920 | 30 | 95298.7 | 80028.8 | 0.0263586 | 0.375068 | 1.73799 | 0.0731258 | 0.000374013 | 0.00620098 | 2.51754e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11461.4 | 0.0385726 | 1188.43ms | 56369 | 2560 | 8379.2 | 4690.32 | 0.00792087 | 0.449612 | 2.3284 | 0.115845 | 3.68387e-05 | 3.02139e-06 | 9.771e-07 | 1(Win) | true |
| simdjson (stage-1) | 10405.1 | 0.0376288 | 1235.41ms | 56369 | 40 | 151.177 | 5166.45 | 0.00483915 | 0.498899 | 2.37178 | 0.103621 | 7.05175e-05 | 3.54805e-06 | 0 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13408.4 | 0.0346782 | 1317.62ms | 83958 | 1280 | 5489 | 5971.53 | 0.0515332 | 0.386506 | 2.08926 | 0.0970248 | 3.76956e-05 | 1.32135e-06 | 2.79157e-08 | 1(Win) | true |
| simdjson (stage-1) | 12663.8 | 0.0183583 | 1351.25ms | 83958 | 160 | 215.566 | 6322.64 | 0.0590781 | 0.409367 | 1.97265 | 0.0848162 | 4.60051e-05 | 1.48884e-06 | 7.4442e-08 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17685.1 | 0.032171 | 1005.97ms | 53331 | 4890 | 4185.85 | 2875.89 | 0.182954 | 0.29518 | 1.56633 | 0.0780785 | 5.81697e-05 | 2.56146e-06 | 3.41273e-07 | 1(Win) | true |
| simdjson (stage-1) | 15474 | 0.0268479 | 1046.29ms | 53331 | 4890 | 3807.9 | 3286.84 | 0.141809 | 0.33726 | 1.56335 | 0.0662467 | 3.29347e-05 | 2.80304e-06 | 6.48034e-07 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17074.1 | 0.0383484 | 1080.77ms | 65103 | 80 | 155.564 | 3636.32 | 0.028867 | 0.304984 | 1.6557 | 0.0748967 | 3.12966e-05 | 2.30404e-06 | 1.92003e-07 | 1(Win) | true |
| simdjson (stage-1) | 16094.2 | 0.0341263 | 1101.08ms | 65103 | 30 | 51.9954 | 3857.73 | 0.0129627 | 0.324119 | 1.50202 | 0.0630693 | 5.7345e-05 | 2.56005e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10312.6 | 0.0592471 | 820.69ms | 11812 | 2560 | 1072.21 | 1092.33 | 0.0430732 | 0.517449 | 2.54004 | 0.128175 | 8.51888e-05 | 8.00298e-06 | 1.32281e-07 | 1(Win) | true |
| simdjson (stage-1) | 9556.65 | 0.0801476 | 827.123ms | 11812 | 2560 | 2284.85 | 1178.74 | 0.0280942 | 0.556614 | 2.58872 | 0.116577 | 8.53541e-05 | 1.05163e-05 | 2.14956e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15018.2 | 0.0574862 | 874.331ms | 25388 | 2560 | 2198.81 | 1612.17 | 0.0174 | 0.351137 | 1.88699 | 0.0881913 | 5.17592e-05 | 4.75434e-06 | 2.30793e-07 | 1(Win) | true |
| simdjson (stage-1) | 13805.1 | 0.0399774 | 888.217ms | 25388 | 80 | 39.3277 | 1753.84 | 0.010692 | 0.381661 | 1.77651 | 0.0766504 | 7.87774e-05 | 9.35481e-06 | 4.92359e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11478.6 | 0.026321 | 1623.85ms | 108313 | 2560 | 14362.5 | 8998.96 | 0.128582 | 0.450512 | 2.40346 | 0.118518 | 1.89591e-05 | 1.51831e-06 | 4.25561e-07 | 1(Win) | true |
| simdjson (stage-1) | 10073.6 | 0.0181241 | 1744.03ms | 108313 | 4890 | 16889.3 | 10254.1 | 0.0634332 | 0.5125 | 2.45259 | 0.108879 | 3.43623e-05 | 3.5193e-06 | 2.20334e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13368.7 | 0.0621301 | 2026.83ms | 183677 | 30 | 1988.19 | 13102.9 | 0.22795 | 0.379727 | 2.04089 | 0.0940401 | 2.95809e-05 | 7.25912e-07 | 1.81478e-07 | 1(Win) | true |
| simdjson (stage-1) | 12812.6 | 0.0210627 | 2088.37ms | 183677 | 4890 | 40548 | 13671.5 | 0.130427 | 0.399903 | 1.92758 | 0.0823348 | 2.94028e-05 | 2.75112e-06 | 1.85931e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8702.69 | 0.0853437 | 5357.15ms | 1834197 | 160 | 4.70813e+06 | 200998 | 0.00316244 | 0.582671 | 2.90983 | 0.136897 | 0.00249177 | 0.0376962 | 2.78732e-06 | 1(Win) | true |
| simdjson (stage-1) | 6883.24 | 0.203453 | 6712.48ms | 1834197 | 40 | 1.06929e+07 | 254128 | 0.117132 | 0.735878 | 3.04774 | 0.152978 | 0.0045623 | 0.0375565 | 4.11624e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15520 | 0.141967 | 5865.58ms | 7351818 | 80 | 3.29057e+07 | 451754 | 0.168191 | 0.324837 | 1.62913 | 0.0669813 | 0.00111229 | 0.0211596 | 7.58384e-05 | 1(Win) | true |
| simdjson (stage-1) | 13979.1 | 0.0976008 | 6512.37ms | 7351818 | 160 | 3.83406e+07 | 501552 | 0.366949 | 0.3649 | 1.58986 | 0.0660409 | 0.000865102 | 0.0211797 | 8.59626e-05 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13203.8 | 0.0217147 | 4065.68ms | 461466 | 4890 | 256151 | 33330.4 | 0.00639016 | 0.386726 | 2.09417 | 0.103752 | 1.0944e-05 | 3.3901e-06 | 2.8858e-06 | 1(Win) | true |
| simdjson (stage-1) | 11659 | 0.0272802 | 4518.13ms | 461466 | 1280 | 135724 | 37746.5 | 0.137337 | 0.440247 | 2.14083 | 0.092022 | 1.71938e-05 | 2.10775e-06 | 1.67774e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14500.9 | 0.0524327 | 5518.64ms | 728486 | 2560 | 1.61546e+06 | 47909.9 | 0.148172 | 0.34784 | 1.88741 | 0.0866016 | 0.000233667 | 3.87951e-06 | 3.38405e-06 | 1(Win) | true |
| simdjson (stage-1) | 13759.2 | 0.0218237 | 5785.75ms | 728486 | 4890 | 593777 | 50492.8 | 0.319456 | 0.371337 | 1.77437 | 0.0748814 | 5.63822e-06 | 1.16001e-05 | 3.94437e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16045 | 0.0429402 | 3485.12ms | 466906 | 640 | 90883.5 | 27751.7 | 0.0347044 | 0.315204 | 1.73857 | 0.0858482 | 2.13473e-05 | 5.78944e-07 | 1.03741e-07 | 1(Win) | true |
| simdjson (stage-1) | 13966.1 | 0.104568 | 3911.86ms | 466906 | 40 | 44459.4 | 31882.6 | 0.0481484 | 0.369083 | 1.74354 | 0.073925 | 2.17924e-05 | 3.39469e-05 | 3.36792e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15969.1 | 0.0397243 | 4506.37ms | 631514 | 2560 | 574590 | 37714 | 0.13825 | 0.316257 | 1.73716 | 0.0785035 | 2.25259e-05 | 1.21793e-06 | 8.41232e-07 | 1(Win) | true |
| simdjson (stage-1) | 15173 | 0.0213538 | 4693.9ms | 631514 | 2560 | 183913 | 39692.9 | 0.028649 | 0.337355 | 1.59418 | 0.0666589 | 2.32032e-05 | 3.81647e-07 | 6.49481e-08 | 2(Loss) | true |
