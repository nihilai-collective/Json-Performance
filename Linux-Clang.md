# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 400.886 | 0.16092 | 928.588ms | 905 | 2560 | 30726.5 | 2152.92 | 0.0748786 | 13.0871 | 30.5381 | 4.47182 | 0.00222419 | 0.00013769 | 3.4962e-05 | 1(Win) | true |
| simdjson (ondemand) | 278.232 | 0.0340855 | 1038.63ms | 905 | 40 | 44.7179 | 3102 | 0.029022 | 19.0885 | 72.7724 | 8.23204 | 0.00220994 | 0.00019337 | 5.52486e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 770.315 | 0.0239317 | 939.102ms | 1811 | 80 | 23.0323 | 2242.07 | 0.0267681 | 6.8035 | 15.1055 | 2.12535 | 0.000552181 | 3.45113e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 584.389 | 0.0563768 | 1009.54ms | 1811 | 30 | 83.2828 | 2955.4 | 0.0563622 | 8.95356 | 36.1745 | 4.06074 | 0.00276091 | 0 | 0 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1621.69 | 0.028195 | 935.51ms | 3862 | 80 | 32.8036 | 2271.14 | 0.0313818 | 3.22994 | 6.94899 | 0.892543 | 0.000517866 | 9.70999e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1131.61 | 0.215078 | 1037.59ms | 3862 | 160 | 7840.51 | 3254.74 | 0.00460845 | 4.59936 | 16.8459 | 1.82548 | 0.000590691 | 3.07483e-05 | 6.47333e-06 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3062.5 | 0.141372 | 1009.86ms | 9578 | 4890 | 86942.4 | 2982.63 | 0.0644378 | 1.70761 | 4.11255 | 0.539048 | 0.000121145 | 1.36646e-05 | 1.70807e-06 | 1(Win) | true |
| simdjson (ondemand) | 2846.67 | 0.0447044 | 1034.96ms | 9578 | 80 | 164.614 | 3208.76 | 0.0432223 | 1.83145 | 6.81551 | 0.736688 | 0.000420234 | 1.17457e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1583.62 | 0.0396745 | 945.595ms | 3873 | 30 | 25.6885 | 2332.37 | 0.0114346 | 3.36666 | 6.92925 | 0.890008 | 0.000542215 | 6.02461e-05 | 4.3033e-05 | 1(Win) | true |
| simdjson (ondemand) | 1246.07 | 0.0501683 | 1008.3ms | 3873 | 40 | 88.4558 | 2964.18 | 0.00477952 | 4.18842 | 16.7981 | 1.82029 | 0.000516396 | 2.58198e-05 | 6.45494e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12778.4 | 0.0682961 | 8399.54ms | 2090234 | 30 | 340527 | 155998 | 0.216499 | 0.402824 | 1.78805 | 0.0788353 | 0.00283731 | 0.0253357 | 6.72971e-06 | 1(Win) | true |
| simdjson (ondemand) | 10144.2 | 0.0480418 | 5240.23ms | 2090234 | 1280 | 1.14079e+07 | 196507 | 0.361232 | 0.506664 | 1.97169 | 0.0905574 | 0.00311167 | 0.0245621 | 2.28294e-06 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19452.9 | 0.0262811 | 8578.07ms | 6661897 | 1280 | 9.43022e+06 | 326598 | 0.208706 | 0.25932 | 1.34405 | 0.0511706 | 0.000314968 | 0.0187974 | 8.80134e-06 | 1(Win) | true |
| simdjson (ondemand) | 16602.2 | 0.0667681 | 10015.8ms | 6661897 | 160 | 1.04454e+07 | 382678 | 0.0591054 | 0.308644 | 1.39081 | 0.0628891 | 0.000306607 | 0.0188402 | 1.63148e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10638.4 | 0.033502 | 5216.88ms | 500299 | 1280 | 288973 | 44849 | 0.00631324 | 0.477494 | 2.54303 | 0.124306 | 2.59282e-05 | 1.06374e-05 | 1.29922e-06 | 1(Win) | true |
| simdjson (ondemand) | 9466.49 | 0.0259964 | 5807.34ms | 500299 | 2560 | 439490 | 50401.2 | 0.0714835 | 0.539823 | 2.60941 | 0.120406 | 1.57086e-05 | 5.23984e-06 | 4.30524e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14730.8 | 0.272349 | 5201.26ms | 1439562 | 1280 | 8.24652e+07 | 93197.6 | 0.0199544 | 0.342606 | 1.76758 | 0.0809309 | 0.000424008 | 0.00685981 | 3.28116e-06 | 1(Win) | true |
| simdjson (ondemand) | 13705.7 | 0.124766 | 5512.25ms | 1439562 | 2560 | 3.99847e+07 | 100168 | 0.0655448 | 0.371529 | 1.69727 | 0.0775132 | 0.000403131 | 0.00990637 | 8.25718e-07 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11146.7 | 0.151301 | 1202.76ms | 56369 | 320 | 17038 | 4822.73 | 0.00213827 | 0.456739 | 2.34194 | 0.11611 | 6.44193e-05 | 4.26875e-06 | 4.98944e-07 | 1(Win) | true |
| simdjson (ondemand) | 10101.1 | 0.0256662 | 1253.23ms | 56369 | 80 | 149.265 | 5321.98 | 0.029133 | 0.504539 | 2.40389 | 0.111622 | 9.51321e-05 | 3.54805e-06 | 0 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13908.6 | 0.0343444 | 1374.35ms | 94370 | 80 | 395.099 | 6470.7 | 0.0200946 | 0.372704 | 2.0013 | 0.0931864 | 0.000150339 | 2.38423e-06 | 2.64915e-07 | 1(Win) | true |
| simdjson (ondemand) | 12859.9 | 0.025969 | 1423.44ms | 94370 | 4890 | 16151.5 | 6998.38 | 0.00717045 | 0.397493 | 1.92588 | 0.0890008 | 3.77815e-05 | 1.26119e-06 | 7.15107e-08 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10026.2 | 0.206685 | 833.611ms | 11812 | 30 | 161.775 | 1123.53 | 0.219065 | 0.522096 | 2.56282 | 0.129445 | 8.46597e-05 | 1.69319e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9401.18 | 0.103547 | 842.894ms | 11812 | 640 | 985.234 | 1198.23 | 0.0450084 | 0.56371 | 2.62411 | 0.125381 | 8.46597e-05 | 3.4393e-06 | 1.32281e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15279.2 | 0.0539425 | 919.342ms | 31235 | 2560 | 2831.31 | 1949.59 | 0.143894 | 0.341403 | 1.80259 | 0.0844246 | 0.000218067 | 3.51419e-06 | 1.00048e-07 | 1(Win) | true |
| simdjson (ondemand) | 14292.6 | 0.0434254 | 931.619ms | 31235 | 80 | 65.5302 | 2084.16 | 0.0365988 | 0.374166 | 1.72643 | 0.0806787 | 0.000214503 | 7.20346e-06 | 1.20058e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11020.3 | 0.0987799 | 1666.73ms | 108313 | 160 | 13716.1 | 9373.17 | 0.154401 | 0.468983 | 2.41498 | 0.118656 | 1.92728e-05 | 1.7888e-06 | 3.46219e-07 | 1(Win) | true |
| simdjson (ondemand) | 9975.95 | 0.0355727 | 1780.23ms | 108313 | 30 | 407.013 | 10354.4 | 0.0141666 | 0.518459 | 2.48268 | 0.11681 | 6.7705e-05 | 2.15425e-06 | 0 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14757.8 | 0.018227 | 2107.54ms | 213963 | 4890 | 31057.8 | 13826.6 | 0.0359889 | 0.344871 | 1.90697 | 0.0880573 | 2.6707e-05 | 6.10736e-07 | 2.29384e-08 | 1(Win) | true |
| simdjson (ondemand) | 13554.9 | 0.0325095 | 2235.27ms | 213963 | 2560 | 61312.3 | 15053.7 | 0.113943 | 0.379061 | 1.8334 | 0.0842202 | 2.36661e-05 | 1.62302e-06 | 9.74906e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8703.97 | 0.301079 | 5385.38ms | 1834197 | 640 | 2.34313e+08 | 200969 | 0.12122 | 0.585755 | 2.91031 | 0.136766 | 0.00183319 | 0.0376968 | 3.69797e-06 | 1(Win) | true |
| simdjson (ondemand) | 7013.21 | 0.198308 | 6611.61ms | 1834197 | 1280 | 3.13148e+08 | 249419 | 0.309481 | 0.729316 | 3.06088 | 0.158708 | 0.00364501 | 0.0376932 | 1.15684e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16990.2 | 0.285068 | 7210.34ms | 9930848 | 320 | 8.08018e+08 | 557426 | 0.184557 | 0.295878 | 1.50228 | 0.0610393 | 0.000637255 | 0.019741 | 1.01757e-05 | 1(Win) | true |
| simdjson (ondemand) | 14985.9 | 0.0707883 | 8230.52ms | 9930848 | 160 | 3.2022e+07 | 631979 | 0.376974 | 0.340566 | 1.51941 | 0.0690104 | 0.000638585 | 0.0197513 | 6.39736e-06 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12470.6 | 0.369207 | 5624.58ms | 642697 | 160 | 5.26863e+06 | 49149.5 | 0.269368 | 0.402923 | 2.20707 | 0.0986251 | 6.91617e-05 | 0.000401307 | 9.48153e-06 | 1(Win) | true |
| simdjson (ondemand) | 9949.36 | 0.0711016 | 7688.8ms | 642697 | 40 | 76743.4 | 61604.3 | 0.252213 | 0.517954 | 2.41934 | 0.126203 | 0.000411819 | 1.78933e-05 | 8.2854e-06 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15087.1 | 0.246231 | 8514.28ms | 1225964 | 2560 | 9.32114e+07 | 77494.7 | 0.123534 | 0.33455 | 1.81417 | 0.0734101 | 1.88933e-05 | 0.00473934 | 8.84827e-07 | 1(Win) | true |
| simdjson (ondemand) | 13373.1 | 0.088236 | 9690.52ms | 1225964 | 30 | 178528 | 87427.1 | 0.0135751 | 0.384939 | 1.85719 | 0.0851323 | 2.1806e-05 | 0.00855955 | 1.35947e-06 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11796.3 | 0.0521784 | 4053.78ms | 409725 | 160 | 47796.5 | 33124.4 | 0.0139456 | 0.428761 | 2.22262 | 0.109188 | 2.46812e-05 | 6.25419e-07 | 2.28812e-07 | 1(Win) | true |
| simdjson (ondemand) | 10680.3 | 0.0979295 | 4370.33ms | 409725 | 40 | 51345.6 | 36585.4 | 0.0195167 | 0.473378 | 2.28901 | 0.105288 | 0.000106901 | 6.10165e-07 | 1.22033e-07 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15125.6 | 0.165715 | 5737.27ms | 785750 | 30 | 202202 | 49541.7 | 0.574381 | 0.337246 | 1.82229 | 0.0838715 | 0.00048459 | 0.000213342 | 8.48446e-08 | 1(Win) | true |
| simdjson (ondemand) | 13618.1 | 0.121281 | 6252.84ms | 785750 | 2560 | 1.14015e+07 | 55026 | 0.100078 | 0.37253 | 1.74818 | 0.0799708 | 0.00024621 | 0.000171892 | 9.97753e-07 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14611.9 | 0.0422827 | 2448.92ms | 264040 | 640 | 33980.5 | 17233 | 0.00521319 | 0.347138 | 1.80266 | 0.0885624 | 8.39125e-06 | 7.04202e-07 | 1.65695e-07 | 1(Win) | true |
| simdjson (ondemand) | 13284.9 | 0.0232664 | 2619.02ms | 264040 | 4890 | 95102.7 | 18954.5 | 0.0183159 | 0.385494 | 1.83128 | 0.0831314 | 8.36383e-06 | 1.56914e-06 | 1.01459e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15404.4 | 0.0350656 | 3216.16ms | 399947 | 4890 | 368626 | 24760.4 | 0.0254903 | 0.327605 | 1.71225 | 0.0778304 | 1.30488e-05 | 6.67266e-07 | 2.49522e-07 | 1(Win) | true |
| simdjson (ondemand) | 15082.4 | 0.0598559 | 3279.04ms | 399947 | 160 | 36660.3 | 25289 | 0.0288086 | 0.341732 | 1.61541 | 0.0732098 | 2.08465e-05 | 5.15693e-07 | 1.09389e-07 | 2(Loss) | true |
