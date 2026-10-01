# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 13, 2026)
#### Using the following commits:
----
| Jsonifier: [6bea81e](https://github.com/nihilai-collective/jsonifier/commit/6bea81e)  
| simdjson(On Demand): [15e7eb8](https://github.com/simdjson/simdjson/commit/15e7eb8)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. The first epoch is kept only as an initial fallback; every later epoch is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result, whether or not it met the convergence thresholds. A result counts as converged only if that retained epoch has RSE <= 5% AND mean shift <= 2.5%; non-converged results are still included in the rankings and in win/tie/loss tallying, so a result that did not meet these thresholds should be read with its reduced statistical confidence in mind. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (Both libraries are executing only 'stage-1' parsing, where they identify the structural indices, and neither of them are performing utf-8 validation in these tests)

#### Note:
 This is the commit of BenchmarkSuite that was used to generate these results: [e7faa83](https://github.com/nihilai-collective/benchmarksuite/commit/e7faa83).
 
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 385.795 | 0.0388977 | 951.182ms | 905 | 4890 | 3702.89 | 2237.13 | 0.0289895 | 13.3431 | 31.4486 | 4.25415 | 0.00232903 | 0.000201335 | 0.00012157 | 1(Win) | true |
| simdjson (ondemand) | 286.45 | 0.0298887 | 1028.57ms | 905 | 640 | 519.03 | 3013 | 0.0112002 | 17.8783 | 72.7757 | 8.01105 | 0.00331492 | 8.80525e-05 | 5.87017e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 780.953 | 0.054018 | 947.719ms | 1811 | 320 | 456.682 | 2211.53 | 0.00268486 | 6.58941 | 15.608 | 2.06461 | 0.000695403 | 0.000101808 | 4.31391e-05 | 1(Win) | true |
| simdjson (ondemand) | 570.503 | 0.060197 | 1028.53ms | 1811 | 320 | 1062.72 | 3027.33 | 0.0424439 | 8.97474 | 36.1761 | 3.95031 | 0.00111817 | 1.38045e-05 | 0 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1573.72 | 0.0605368 | 960.325ms | 3862 | 40 | 80.2917 | 2340.38 | 0.030275 | 3.26596 | 7.16235 | 0.945106 | 0.0006797 | 3.23666e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1220.31 | 0.0318382 | 1030.27ms | 3862 | 4890 | 4515.36 | 3018.17 | 0.0206692 | 4.1946 | 16.8467 | 1.77369 | 0.000519932 | 4.10904e-05 | 1.18082e-05 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3213.77 | 0.0466408 | 1014.55ms | 9578 | 4890 | 8593.32 | 2842.24 | 0.247566 | 1.58824 | 4.21863 | 0.560138 | 0.000269107 | 2.61335e-05 | 8.36956e-06 | 1(Win) | true |
| simdjson (ondemand) | 2790.82 | 0.0384547 | 1054.36ms | 9578 | 4890 | 7746.3 | 3272.98 | 0.00125397 | 1.82929 | 6.81583 | 0.715808 | 0.000418798 | 1.75504e-05 | 6.21311e-06 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1555.49 | 0.053833 | 965.845ms | 3873 | 4890 | 7990.35 | 2374.54 | 0.0169922 | 3.28675 | 7.14201 | 0.942423 | 0.000674324 | 7.58753e-05 | 4.45642e-05 | 1(Win) | true |
| simdjson (ondemand) | 1218.85 | 0.0368072 | 1032.83ms | 3873 | 4890 | 6083.69 | 3030.38 | 0.0926385 | 4.19676 | 16.7989 | 1.76866 | 0.000519616 | 4.96859e-05 | 2.36021e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12381.3 | 0.0232358 | 8659.84ms | 2090234 | 2560 | 3.58272e+06 | 161001 | 0.0448567 | 0.405259 | 1.79588 | 0.0788391 | 0.00305072 | 0.0255096 | 2.90301e-06 | 1(Win) | true |
| simdjson (ondemand) | 9813.16 | 0.11087 | 5284.24ms | 2090234 | 40 | 2.02892e+06 | 203136 | 0.120208 | 0.514157 | 1.9717 | 0.0905569 | 0.00323716 | 0.0250782 | 3.48047e-06 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19255.9 | 0.0334005 | 8645.76ms | 6661897 | 1280 | 1.55448e+07 | 329940 | 0.0365209 | 0.259868 | 1.37139 | 0.0511708 | 0.000312971 | 0.018823 | 1.15637e-05 | 1(Win) | true |
| simdjson (ondemand) | 16267.2 | 0.0526484 | 5076.62ms | 6661897 | 320 | 1.35298e+07 | 390558 | 0.0730778 | 0.309651 | 1.39081 | 0.0628889 | 0.000323083 | 0.0188506 | 3.29861e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10580.2 | 0.025883 | 5239.16ms | 500299 | 2560 | 348775 | 45096 | 0.165513 | 0.475437 | 2.54309 | 0.124322 | 1.48286e-05 | 1.71577e-05 | 1.50465e-05 | 1(Win) | true |
| simdjson (ondemand) | 9330.81 | 0.0179866 | 5861.82ms | 500299 | 2560 | 216550 | 51134.1 | 0.0177139 | 0.541141 | 2.60942 | 0.120404 | 4.01861e-05 | 2.12217e-05 | 1.93884e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14921.8 | 0.138597 | 5110.01ms | 1439562 | 160 | 2.60164e+06 | 92004.4 | 0.04665 | 0.335349 | 1.79117 | 0.0809365 | 0.000444575 | 0.00683624 | 3.14896e-05 | 1(Win) | true |
| simdjson (ondemand) | 13549.3 | 0.0743973 | 5624.26ms | 1439562 | 320 | 1.8184e+06 | 101324 | 0.0435171 | 0.371997 | 1.69727 | 0.0775125 | 0.000443225 | 0.00853247 | 3.61221e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11144.5 | 0.105412 | 1212.46ms | 56369 | 40 | 1034.17 | 4823.68 | 0.050644 | 0.449031 | 2.34233 | 0.116145 | 4.08026e-05 | 9.31363e-06 | 3.54805e-06 | 1(Win) | true |
| simdjson (ondemand) | 10189 | 0.0357731 | 1267.05ms | 56369 | 2560 | 9119.48 | 5276.04 | 0.000599707 | 0.499729 | 2.40395 | 0.111604 | 3.69011e-05 | 1.01799e-05 | 7.29706e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13402.2 | 0.0374958 | 1415.52ms | 94370 | 4890 | 31002.2 | 6715.2 | 0.00163261 | 0.3772 | 2.02571 | 0.0932712 | 2.25714e-05 | 5.87905e-06 | 3.8009e-06 | 1(Win) | true |
| simdjson (ondemand) | 12646.3 | 0.030066 | 1450.24ms | 94370 | 4890 | 22387.2 | 7116.57 | 0.0381878 | 0.400891 | 1.92591 | 0.0889902 | 2.50374e-05 | 6.04374e-06 | 4.06961e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10056 | 0.102801 | 848.652ms | 11812 | 640 | 848.743 | 1120.21 | 0.132544 | 0.519875 | 2.56434 | 0.129614 | 8.49242e-05 | 1.61382e-05 | 8.20141e-06 | 1(Win) | true |
| simdjson (ondemand) | 9167.43 | 0.177262 | 857.963ms | 11812 | 2560 | 12145.7 | 1228.79 | 0.00187555 | 0.565806 | 2.62437 | 0.125296 | 8.54534e-05 | 2.56625e-05 | 1.57745e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14898.4 | 0.0541254 | 939.672ms | 31235 | 2560 | 2998.09 | 1999.41 | 0.0069752 | 0.343003 | 1.82673 | 0.0844886 | 0.000204636 | 9.66714e-06 | 5.08994e-06 | 1(Win) | true |
| simdjson (ondemand) | 13765.3 | 0.0520076 | 953.11ms | 31235 | 80 | 101.329 | 2163.99 | 0.0606887 | 0.374154 | 1.72652 | 0.0806467 | 0.000233312 | 1.16056e-05 | 4.80231e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10999.5 | 0.0295052 | 1680.54ms | 108313 | 4890 | 37542 | 9390.87 | 0.0883614 | 0.459438 | 2.41515 | 0.118675 | 2.02605e-05 | 9.31935e-06 | 6.86868e-06 | 1(Win) | true |
| simdjson (ondemand) | 9789.47 | 0.0234577 | 1802.75ms | 108313 | 2560 | 15683.9 | 10551.7 | 0.101133 | 0.51804 | 2.4827 | 0.1168 | 5.37865e-05 | 1.17426e-05 | 9.69413e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14621.2 | 0.0205778 | 2132.06ms | 213963 | 4890 | 40329.2 | 13955.9 | 0.0193191 | 0.345767 | 1.93055 | 0.0880948 | 2.77756e-05 | 2.3206e-06 | 1.45755e-06 | 1(Win) | true |
| simdjson (ondemand) | 13294.3 | 0.0225056 | 2276.12ms | 213963 | 4890 | 58349.8 | 15348.8 | 0.12105 | 0.379707 | 1.83342 | 0.0842156 | 2.50478e-05 | 7.06695e-06 | 5.68395e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8793.14 | 0.0371703 | 5273.33ms | 1834197 | 1280 | 6.99853e+06 | 198931 | 0.196716 | 0.568827 | 2.91406 | 0.136771 | 0.00158524 | 0.0377027 | 3.83768e-06 | 1(Win) | true |
| simdjson (ondemand) | 6959.29 | 0.032667 | 6651.15ms | 1834197 | 640 | 4.31481e+06 | 251351 | 0.154896 | 0.724805 | 3.06088 | 0.158708 | 0.00372952 | 0.037665 | 2.94151e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16945.5 | 0.132142 | 7325.8ms | 9930848 | 160 | 8.72694e+07 | 558896 | 0.125155 | 0.295772 | 1.52869 | 0.0610401 | 0.000627604 | 0.0197454 | 0.000113652 | 1(Win) | true |
| simdjson (ondemand) | 14549.9 | 0.159133 | 8397.56ms | 9930848 | 80 | 8.58347e+07 | 650920 | 0.374344 | 0.345967 | 1.51941 | 0.0690103 | 0.000646618 | 0.0197549 | 0.000355284 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12589.5 | 0.0420374 | 5620.56ms | 642697 | 640 | 268070 | 48685.4 | 0.0540168 | 0.400948 | 2.21492 | 0.0986375 | 0.000169136 | 2.15231e-05 | 1.1441e-05 | 1(Win) | true |
| simdjson (ondemand) | 9836.89 | 0.0245516 | 6996.08ms | 642697 | 2560 | 599098 | 62308.7 | 0.0212919 | 0.509948 | 2.41934 | 0.126201 | 0.000146606 | 0.000114599 | 3.39955e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15079.5 | 0.124418 | 8523.32ms | 1225964 | 320 | 2.97781e+06 | 77533.7 | 0.0754546 | 0.332875 | 1.84153 | 0.0734166 | 1.8228e-05 | 0.00525076 | 1.18147e-05 | 1(Win) | true |
| simdjson (ondemand) | 13058 | 0.0297213 | 9729.94ms | 1225964 | 1280 | 906464 | 89536.9 | 0.124221 | 0.385781 | 1.85719 | 0.0851314 | 2.21917e-05 | 0.00615158 | 2.14321e-05 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11993 | 0.026449 | 3993.75ms | 409725 | 1280 | 95052.2 | 32581.1 | 0.0917255 | 0.42139 | 2.2227 | 0.109207 | 1.42016e-05 | 4.45993e-06 | 3.66099e-06 | 1(Win) | true |
| simdjson (ondemand) | 10736.2 | 0.0127318 | 4373.09ms | 409725 | 4890 | 104997 | 36395.1 | 0.0563303 | 0.470389 | 2.28901 | 0.105285 | 8.05917e-06 | 7.312e-06 | 5.22172e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14916.6 | 0.0336274 | 5786.91ms | 785750 | 1280 | 365279 | 50235.9 | 0.0147202 | 0.33764 | 1.84577 | 0.0838817 | 0.000364584 | 1.11647e-05 | 5.68824e-06 | 1(Win) | true |
| simdjson (ondemand) | 13573.3 | 0.0423558 | 6256.6ms | 785750 | 640 | 349951 | 55207.8 | 0.0208149 | 0.37148 | 1.74819 | 0.0799695 | 0.000258376 | 6.09231e-05 | 8.15503e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15262.6 | 0.132458 | 2387.42ms | 264040 | 160 | 76411.8 | 16498.3 | 0.0520236 | 0.331872 | 1.80414 | 0.0885927 | 1.3729e-05 | 9.94168e-07 | 2.84048e-07 | 1(Win) | true |
| simdjson (ondemand) | 13126.3 | 0.0723306 | 2660.59ms | 264040 | 160 | 30804.6 | 19183.4 | 0.0234633 | 0.385651 | 1.83129 | 0.0831276 | 8.23739e-06 | 2.91149e-06 | 2.39074e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15486.7 | 0.0400301 | 3204.74ms | 399947 | 2560 | 248830 | 24628.9 | 0.098224 | 0.324832 | 1.73686 | 0.0778504 | 1.78549e-05 | 4.42832e-06 | 3.54441e-06 | 1(Win) | true |
| simdjson (ondemand) | 14808.2 | 0.0205898 | 3315.25ms | 399947 | 2560 | 72001.8 | 25757.3 | 0.0639928 | 0.34175 | 1.61542 | 0.0732073 | 5.78788e-06 | 6.01642e-06 | 5.20088e-06 | 2(Loss) | true |
