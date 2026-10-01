# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 405.476 | 0.0690703 | 936.244ms | 905 | 40 | 86.459 | 2128.55 | 0.0258459 | 12.7108 | 38.7149 | 5.57459 | 0.00220994 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 236.375 | 0.16127 | 1091.1ms | 905 | 30 | 1040.22 | 3651.3 | 0.0493218 | 21.63 | 86.4486 | 8.00663 | 0.00331492 | 0.000626151 | 0.000294659 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 822.405 | 0.0696597 | 937.615ms | 1811 | 1280 | 2739.3 | 2100.07 | 0.116082 | 6.26383 | 18.5798 | 2.55936 | 0.000642342 | 0.000115613 | 2.63149e-05 | 1(Win) | true |
| simdjson (ondemand) | 465.846 | 0.0561971 | 1100.4ms | 1811 | 320 | 1389.09 | 3707.46 | 0.0908658 | 10.9766 | 43.0641 | 3.94811 | 0.00108711 | 7.59249e-05 | 8.62783e-06 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1661.26 | 0.0547592 | 950.871ms | 3862 | 2560 | 3773.16 | 2217.05 | 0.00218472 | 3.09814 | 8.19187 | 0.995599 | 0.000518271 | 3.36815e-05 | 3.23666e-06 | 1(Win) | true |
| simdjson (ondemand) | 1002.33 | 0.0468652 | 1097.71ms | 3862 | 2560 | 7591.74 | 3674.51 | 0.0982582 | 5.06588 | 20.0508 | 1.77266 | 0.000519889 | 4.05595e-05 | 7.18135e-06 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2956.81 | 0.0311247 | 1043.32ms | 9578 | 4890 | 4520.86 | 3089.24 | 0.0161092 | 1.72905 | 4.6848 | 0.579975 | 0.00458581 | 2.51087e-05 | 7.1312e-06 | 1(Win) | true |
| simdjson (ondemand) | 2260.71 | 0.0508573 | 1135.64ms | 9578 | 160 | 675.595 | 4040.45 | 0.144577 | 2.26021 | 8.10775 | 0.715389 | 0.000522682 | 2.08812e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1668.13 | 0.053892 | 949.281ms | 3873 | 30 | 42.7172 | 2214.2 | 0.0812274 | 3.08549 | 8.1686 | 0.99277 | 0.000516396 | 1.72132e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1005.43 | 0.0825978 | 1097.14ms | 3873 | 640 | 5892.56 | 3673.62 | 0.0862462 | 5.07831 | 19.9938 | 1.76762 | 0.000772173 | 7.74593e-05 | 3.02576e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 10333.9 | 0.0945253 | 5121.94ms | 2090234 | 320 | 1.06392e+07 | 192900 | 0.0834403 | 0.486832 | 2.14792 | 0.0827425 | 0.00242839 | 0.0246661 | 2.45038e-06 | 1(Win) | true |
| jsonifier | 10149.5 | 0.0605282 | 5244.82ms | 2090234 | 1280 | 1.80893e+07 | 196403 | 0.0236785 | 0.497261 | 1.73349 | 0.193215 | 0.00595295 | 0.0252203 | 8.51056e-07 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 16102.4 | 0.0646952 | 5124.69ms | 6661897 | 320 | 2.085e+07 | 394554 | 0.0531848 | 0.314251 | 1.53963 | 0.0550758 | 0.000308589 | 0.0188475 | 1.56206e-06 | 1(Win) | true |
| jsonifier | 15746.8 | 0.0393466 | 5242.13ms | 6661897 | 640 | 1.61289e+07 | 403465 | 0.000502292 | 0.32024 | 1.23092 | 0.0834078 | 0.00241387 | 0.0188367 | 1.87564e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10352.6 | 0.0554237 | 5347.17ms | 500299 | 40 | 26098.5 | 46087.4 | 0.00240491 | 0.488711 | 2.49913 | 0.30519 | 4.08256e-05 | 1.05437e-05 | 9.29444e-06 | 1(Win) | true |
| simdjson (ondemand) | 9727.52 | 0.0213689 | 5646.58ms | 500299 | 1280 | 140614 | 49048.7 | 0.018625 | 0.520829 | 2.8027 | 0.112581 | 1.93603e-05 | 6.2853e-06 | 5.24218e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15825.5 | 0.0706646 | 9533.58ms | 1439562 | 160 | 601268 | 86750.5 | 0.0759434 | 0.320568 | 1.58772 | 0.127731 | 6.3409e-05 | 0.00812107 | 8.74832e-06 | 1(Win) | true |
| simdjson (ondemand) | 13488 | 0.0380321 | 5616.7ms | 1439562 | 1280 | 1.91812e+06 | 101785 | 0.0313025 | 0.376511 | 1.86069 | 0.069697 | 0.000400506 | 0.00805967 | 1.62159e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11214.4 | 0.0280934 | 1210.22ms | 56369 | 4890 | 8868.41 | 4793.62 | 0.0681367 | 0.456359 | 2.27634 | 0.265483 | 3.68409e-05 | 3.7113e-06 | 8.09013e-07 | 1(Win) | true |
| simdjson (ondemand) | 10546.5 | 0.118876 | 1247.69ms | 56369 | 160 | 5874.62 | 5097.23 | 0.449807 | 0.490262 | 2.59192 | 0.103053 | 5.42186e-05 | 4.87857e-06 | 1.33052e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13095.2 | 0.067444 | 1421.74ms | 94370 | 2560 | 55001.1 | 6872.62 | 0.0658317 | 0.387656 | 1.86583 | 0.171993 | 2.36974e-05 | 1.7799e-06 | 2.69054e-07 | 1(Win) | true |
| simdjson (ondemand) | 12484.1 | 0.0405247 | 1442.54ms | 94370 | 640 | 5462.28 | 7209.03 | 0.00765158 | 0.407153 | 2.1026 | 0.0807355 | 2.31138e-05 | 2.23522e-06 | 6.29172e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10260.3 | 0.0582925 | 835.93ms | 11812 | 640 | 262.139 | 1097.9 | 0.0132337 | 0.520229 | 2.48933 | 0.30342 | 8.46597e-05 | 1.77256e-05 | 5.82035e-06 | 1(Win) | true |
| simdjson (ondemand) | 9413.42 | 0.187201 | 840.724ms | 11812 | 40 | 200.738 | 1196.67 | 0.0257725 | 0.555924 | 2.81705 | 0.117169 | 8.46597e-05 | 1.05825e-05 | 2.11649e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15199.4 | 0.0518044 | 926.25ms | 31235 | 4890 | 5040.46 | 1959.81 | 0.0152242 | 0.340931 | 1.63765 | 0.135169 | 4.61178e-05 | 6.95303e-06 | 1.14574e-06 | 1(Win) | true |
| simdjson (ondemand) | 13668.3 | 0.0434663 | 953.165ms | 31235 | 2560 | 2297.2 | 2179.35 | 0.0293321 | 0.378583 | 1.89182 | 0.072707 | 0.00022402 | 8.22895e-06 | 2.9264e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10887 | 0.0580359 | 1700.04ms | 108313 | 320 | 9702.62 | 9487.97 | 0.0628493 | 0.474998 | 2.37742 | 0.284934 | 2.08885e-05 | 2.39468e-06 | 7.50141e-07 | 1(Win) | true |
| simdjson (ondemand) | 9769.74 | 0.0586158 | 1782.33ms | 108313 | 320 | 12290.6 | 10573 | 0.00437455 | 0.519193 | 2.67128 | 0.109027 | 6.15404e-05 | 2.07731e-06 | 1.73109e-07 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13932.7 | 0.0253233 | 2221.06ms | 213963 | 1280 | 17605.8 | 14645.5 | 0.0227141 | 0.363775 | 1.78817 | 0.160635 | 1.43534e-05 | 1.25241e-06 | 4.81976e-07 | 1(Win) | true |
| simdjson (ondemand) | 13327.7 | 0.0168197 | 2279.99ms | 213963 | 4890 | 32427.5 | 15310.3 | 0.0643742 | 0.381301 | 2.00334 | 0.0763824 | 2.44524e-05 | 1.86279e-06 | 1.01311e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7058.65 | 0.034178 | 6529.16ms | 1834197 | 320 | 2.29557e+06 | 247813 | 0.0282361 | 0.715107 | 3.29497 | 0.15753 | 0.00375484 | 0.0376506 | 1.72589e-06 | 1(Win) | true |
| jsonifier | 6522.38 | 0.0557788 | 7097.35ms | 1834197 | 1280 | 2.86436e+07 | 268189 | 0.162004 | 0.773925 | 2.92609 | 0.383819 | 0.00801018 | 0.0378303 | 1.77743e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 14998.8 | 0.0580674 | 8147.04ms | 9930848 | 320 | 4.30205e+07 | 631437 | 0.0509327 | 0.338515 | 1.67435 | 0.0611974 | 0.000488269 | 0.0197518 | 2.4827e-05 | 1(Win) | true |
| jsonifier | 13158.7 | 0.0857119 | 9272.26ms | 9930848 | 320 | 1.21782e+08 | 719739 | 0.105385 | 0.381812 | 1.34067 | 0.0979598 | 0.00386072 | 0.0197562 | 3.64908e-05 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11833.1 | 0.0197231 | 5953.29ms | 642697 | 4890 | 510354 | 51797.2 | 0.0458914 | 0.42711 | 2.20472 | 0.271819 | 4.10094e-05 | 0.000309092 | 2.51019e-06 | 1(Win) | true |
| simdjson (ondemand) | 9188.22 | 0.0458288 | 7397.06ms | 642697 | 640 | 598145 | 66707.5 | 0.0421161 | 0.554211 | 2.65803 | 0.130169 | 6.77346e-05 | 0.00133481 | 2.48465e-06 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14778.2 | 0.0857732 | 8679.08ms | 1225964 | 320 | 1.47356e+06 | 79114.8 | 0.0325345 | 0.34166 | 1.68027 | 0.158291 | 0.00019553 | 0.00566034 | 1.57784e-06 | 1(Win) | true |
| simdjson (ondemand) | 12761.5 | 0.0366073 | 5076.22ms | 1225964 | 80 | 89986.5 | 91617.1 | 0.0219576 | 0.396206 | 2.02815 | 0.0773155 | 2.132e-05 | 0.00614844 | 1.52941e-06 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11795.4 | 0.0416844 | 4059.95ms | 409725 | 2560 | 488146 | 33127 | 0.192268 | 0.429805 | 2.15725 | 0.248223 | 2.68539e-05 | 1.63982e-06 | 1.03251e-06 | 1(Win) | true |
| simdjson (ondemand) | 10645.1 | 0.0778447 | 4376.76ms | 409725 | 30 | 24494.5 | 36706.6 | 0.00681029 | 0.475369 | 2.46956 | 0.097463 | 0.000119836 | 1.82236e-05 | 1.54575e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14706.4 | 0.0844064 | 5827.28ms | 785750 | 40 | 73988.7 | 50953.9 | 0.0755177 | 0.343901 | 1.69624 | 0.145331 | 1.33948e-05 | 0.000169997 | 4.77251e-07 | 1(Win) | true |
| simdjson (ondemand) | 13561.2 | 0.0425454 | 6253.03ms | 785750 | 160 | 88430.2 | 55257 | 0.0598925 | 0.372774 | 1.91404 | 0.0721515 | 0.000253388 | 0.000594384 | 1.40232e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15429.2 | 0.0399829 | 2374.31ms | 264040 | 2560 | 109005 | 16320.3 | 0.133102 | 0.329347 | 1.65667 | 0.164869 | 1.5201e-05 | 6.38516e-06 | 5.34661e-06 | 1(Win) | true |
| simdjson (ondemand) | 13150.6 | 0.0277203 | 2644.76ms | 264040 | 2560 | 72125.2 | 19148.1 | 0.14631 | 0.387731 | 1.99397 | 0.075644 | 1.1467e-05 | 2.56827e-06 | 1.78566e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16144.2 | 0.0506325 | 3095.44ms | 399947 | 1280 | 183165 | 23625.8 | 0.0165068 | 0.312816 | 1.54283 | 0.120098 | 1.24821e-05 | 2.06277e-06 | 1.49434e-06 | 1(Win) | true |
| simdjson (ondemand) | 14604.3 | 0.014424 | 3366ms | 399947 | 4890 | 69394 | 26116.9 | 0.00151933 | 0.347624 | 1.7729 | 0.0655738 | 7.26425e-06 | 2.6164e-06 | 1.943e-06 | 2(Loss) | true |
