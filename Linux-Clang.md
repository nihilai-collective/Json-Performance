# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the Clang 24.0.0 compiler).  

Latest Results: (Sep 23, 2026)
#### Using the following commits:
----
| Jsonifier: [9b1cd1d](https://github.com/nihilai-collective/jsonifier/commit/9b1cd1d)  
| Glaze: [76db773](https://github.com/stephenberry/glaze/commit/76db773)  
| Simdjson: [6913ee1](https://github.com/simdjson/simdjson/commit/6913ee1)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX2` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1345.06 | 0.522439 | 2.31508ms | 1811 | 30 | 1350.03 | 1284.03 | 2.21323 | 1(Win) |
| glaze | 1139.31 | 0.657386 | 7.07093ms | 1811 | 40 | 3972.43 | 1515.92 | 2.62198 | 2(Loss) |
| simdjson (ondemand) | 270.869 | 1.48913 | 15.3598ms | 1811 | 80 | 721226 | 6376.15 | 11.1679 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 820.763 | 0.527311 | 1.49595ms | 1811 | 30 | 3693.65 | 2104.27 | 3.65237 | 1(Win) |
| glaze | 728.941 | 0.153271 | 3.5313ms | 1798 | 40 | 519.969 | 2352.32 | 4.11237 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2221.44 | 0.0845232 | 1.30594ms | 3873 | 30 | 59.2517 | 1662.7 | 1.34614 | 1(Win) |
| glaze | 2046.53 | 0.101418 | 1.3471ms | 3873 | 30 | 100.51 | 1804.8 | 1.46499 | 2(Loss) |
| simdjson (ondemand) | 637.965 | 0.164474 | 2.56519ms | 3873 | 30 | 2720.31 | 5789.63 | 4.74731 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3736.55 | 0.743439 | 1.12784ms | 3873 | 30 | 1620.19 | 988.5 | 0.792469 | 1(Win) |
| glaze | 2709.43 | 0.228711 | 1.23838ms | 3873 | 30 | 291.633 | 1363.23 | 1.10211 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2413.29 | 0.419169 | 1.27648ms | 3862 | 30 | 1227.73 | 1526.17 | 1.23668 | 1(Win) |
| glaze | 1876.96 | 0.144264 | 1.39ms | 3862 | 30 | 240.409 | 1962.27 | 1.60355 | 2(Loss) |
| simdjson (ondemand) | 622.125 | 0.514356 | 13.5041ms | 3862 | 80 | 74180.1 | 5920.18 | 4.85891 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4581.15 | 0.426958 | 1.04962ms | 3862 | 30 | 353.482 | 803.967 | 0.641334 | 1(Win) |
| glaze | 2467.51 | 0.245486 | 1.31556ms | 3862 | 30 | 402.792 | 1492.63 | 1.2082 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3090.41 | 0.29095 | 1.99053ms | 905 | 40 | 26.4096 | 279.275 | 0.904724 | 1(Win) |
| glaze | 1894.23 | 1.36793 | 0.958102ms | 905 | 30 | 1165.41 | 455.633 | 1.53591 | 2(Loss) |
| simdjson (ondemand) | 225.22 | 0.364495 | 12.1507ms | 905 | 80 | 15608.3 | 3832.14 | 13.4096 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3817.79 | 0.492821 | 0.878401ms | 905 | 30 | 37.2368 | 226.067 | 0.727735 | 1(Win) |
| glaze | 1007.56 | 2.30863 | 2.47239ms | 905 | 40 | 15643.1 | 856.6 | 2.94948 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3881.15 | 0.348586 | 1.54061ms | 9578 | 30 | 2019.16 | 2353.5 | 0.773105 | 1(Win) |
| glaze | 3497.09 | 0.4675 | 1.64095ms | 9578 | 30 | 4473.21 | 2611.97 | 0.85821 | 2(Loss) |
| simdjson (ondemand) | 1591.5 | 0.111083 | 6.05696ms | 9578 | 40 | 1625.89 | 5739.43 | 1.90248 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5957.96 | 0.308929 | 2.99056ms | 9578 | 40 | 897.292 | 1533.12 | 0.499319 | 1(Win) |
| glaze | 4617.63 | 0.210185 | 1.46669ms | 9578 | 30 | 518.602 | 1978.13 | 0.646673 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 866.14 | 0.312359 | 705.469ms | 2090234 | 30 | 1.5504e+09 | 2.30148e+06 | 3.50815 | 1(Win) |
| glaze | 767.251 | 0.300782 | 787.124ms | 2090234 | 30 | 1.83206e+09 | 2.59811e+06 | 3.96037 | 2(Loss) |
| simdjson (ondemand) | 633.802 | 0.779559 | 937.777ms | 2090234 | 30 | 1.80344e+10 | 3.14515e+06 | 4.79422 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1661.63 | 1.11865 | 356.362ms | 2090234 | 30 | 5.403e+09 | 1.19967e+06 | 1.82853 | 1(Win) |
| glaze | 945.114 | 0.267188 | 635.471ms | 2090234 | 30 | 9.52745e+08 | 2.10917e+06 | 3.21472 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2190.79 | 0.276982 | 879.08ms | 6661897 | 30 | 1.9356e+09 | 2.89999e+06 | 1.387 | 1(Win) |
| glaze | 1967.82 | 0.257842 | 975.257ms | 6661897 | 30 | 2.079e+09 | 3.22859e+06 | 1.54419 | 2(Loss) |
| simdjson (ondemand) | 1906.05 | 0.567381 | 1008.87ms | 6661897 | 30 | 1.073e+10 | 3.33322e+06 | 1.59415 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3997.43 | 0.335284 | 483.873ms | 6661897 | 30 | 8.51885e+08 | 1.58934e+06 | 0.760063 | 1(Win) |
| glaze | 3137.13 | 0.272697 | 620.334ms | 6661897 | 30 | 9.14981e+08 | 2.02519e+06 | 0.968473 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1816.6 | 0.699575 | 81.5425ms | 500299 | 30 | 1.01281e+08 | 262645 | 1.67259 | 1(Tie) |
| glaze STATISTICAL TIE | 1791.12 | 0.996818 | 81.0154ms | 500299 | 30 | 2.11525e+08 | 266382 | 1.69636 | 1(Tie) |
| simdjson (ondemand) | 1050.96 | 0.899902 | 138.079ms | 500299 | 30 | 5.00728e+08 | 453989 | 2.89099 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6170.06 | 2.75515 | 56.0775ms | 500299 | 40 | 1.81564e+08 | 77328.6 | 0.492198 | 1(Win) |
| glaze | 5605.06 | 1.8283 | 26.5035ms | 500299 | 30 | 7.26633e+07 | 85123.5 | 0.541801 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3406.29 | 1.80103 | 119.833ms | 1439562 | 30 | 1.58075e+09 | 403041 | 0.89178 | 1(Win) |
| glaze | 2970.51 | 0.471225 | 141.603ms | 1439562 | 30 | 1.42291e+08 | 462168 | 1.02298 | 2(Loss) |
| simdjson (ondemand) | 2710.54 | 0.851347 | 152.854ms | 1439562 | 30 | 5.57808e+08 | 506495 | 1.12095 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9602.72 | 4.14157 | 43.211ms | 1439562 | 30 | 1.05177e+09 | 142967 | 0.316279 | 1(Win) |
| glaze | 5559.2 | 0.694578 | 779.016ms | 1439584 | 160 | 4.70773e+08 | 246959 | 0.545925 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1804.97 | 0.84401 | 50.3424ms | 56369 | 80 | 5.05505e+06 | 29783.1 | 1.6819 | 1(Win) |
| jsonifier | 1661.57 | 2.89929 | 10.7263ms | 56369 | 30 | 2.63966e+07 | 32353.5 | 1.82657 | 2(Loss) |
| simdjson (ondemand) | 1212.83 | 1.24904 | 33.3846ms | 56369 | 40 | 1.22602e+07 | 44324.3 | 2.50413 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 6049.23 | 0.347217 | 3.57465ms | 56369 | 30 | 28563 | 8886.7 | 0.500457 | 1(Tie) |
| glaze STATISTICAL TIE | 5969.3 | 2.11893 | 17.7724ms | 56369 | 80 | 2.9131e+06 | 9005.69 | 0.507324 | 1(Tie) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2393.46 | 0.977531 | 130.145ms | 94370 | 160 | 2.1617e+07 | 37601.7 | 1.26849 | 1(Win) |
| jsonifier | 2335.94 | 0.212562 | 14.1579ms | 94370 | 30 | 201205 | 38527.7 | 1.30008 | 2(Loss) |
| simdjson (ondemand) | 1887.94 | 2.40466 | 34.7887ms | 94370 | 40 | 5.25608e+07 | 47670.2 | 1.60811 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8626.97 | 0.399008 | 4.09812ms | 94370 | 30 | 51980 | 10432.2 | 0.351407 | 1(Win) |
| glaze | 5037.36 | 0.670932 | 6.37736ms | 94370 | 30 | 431064 | 17866.2 | 0.602207 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1378.77 | 1.02856 | 7.68073ms | 11812 | 40 | 282477 | 8170.18 | 2.19665 | 1(Win) |
| jsonifier | 1306.84 | 0.261757 | 8.22138ms | 11812 | 40 | 20363.7 | 8619.85 | 2.3181 | 2(Loss) |
| simdjson (ondemand) | 1036.43 | 0.6074 | 4.27201ms | 11812 | 30 | 130747 | 10868.8 | 2.92286 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4591.63 | 0.689069 | 1.62277ms | 11812 | 30 | 8573.54 | 2453.33 | 0.655492 | 1(Win) |
| glaze | 3871.29 | 1.3988 | 1.80451ms | 11812 | 30 | 49701.2 | 2909.83 | 0.777153 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2531.09 | 0.956595 | 22.1968ms | 31235 | 80 | 1.01394e+06 | 11768.8 | 1.19755 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2486.49 | 1.41465 | 4.50318ms | 31235 | 30 | 861645 | 11980 | 1.21934 | 1(Tie) |
| glaze | 2297.82 | 0.520804 | 214.102ms | 31235 | 640 | 2.9173e+06 | 12963.6 | 1.31934 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8757.46 | 0.615891 | 19.3915ms | 31235 | 160 | 70218.9 | 3401.44 | 0.343788 | 1(Win) |
| glaze | 5044.18 | 0.52146 | 6.1061ms | 31235 | 40 | 37931.9 | 5905.43 | 0.599138 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3334.54 | 1.14525 | 10.5728ms | 108313 | 30 | 3.77581e+06 | 30977.4 | 0.910571 | 1(Win) |
| glaze | 2271.14 | 1.84046 | 72.8579ms | 108313 | 80 | 5.60549e+07 | 45481.6 | 1.33717 | 2(Loss) |
| simdjson (ondemand) | 1475.56 | 3.114 | 108.044ms | 108313 | 80 | 3.80167e+08 | 70004.2 | 2.05829 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 6391.42 | 0.927481 | 30.1529ms | 108313 | 80 | 1.79749e+06 | 16161.5 | 0.474715 | 1(Tie) |
| glaze STATISTICAL TIE | 6195.25 | 2.30561 | 5.90298ms | 108313 | 30 | 4.4334e+06 | 16673.3 | 0.489617 | 1(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3409.04 | 2.6308 | 43.8738ms | 213963 | 40 | 9.91857e+07 | 59855.9 | 0.891037 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 2817.99 | 1.26635 | 23.0174ms | 213963 | 30 | 2.52248e+07 | 72410 | 1.07794 | 2(Tie) |
| glaze STATISTICAL TIE | 2815.82 | 2.63454 | 22.5035ms | 213963 | 30 | 1.09345e+08 | 72466 | 1.07848 | 2(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6776.39 | 3.84145 | 21.8907ms | 213963 | 40 | 5.35219e+07 | 30112 | 0.447945 | 1(Win) |
| glaze | 5310.09 | 3.77916 | 12.4363ms | 213963 | 30 | 6.32683e+07 | 38427.1 | 0.571796 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 810.061 | 0.379001 | 647.121ms | 1834197 | 30 | 2.00937e+09 | 2.15938e+06 | 3.75111 | 1(Win) |
| glaze | 675.782 | 0.692128 | 777.717ms | 1834197 | 30 | 9.62881e+09 | 2.58845e+06 | 4.49639 | 2(Loss) |
| simdjson (ondemand) | 191.277 | 0.25308 | 2760.02ms | 1834197 | 30 | 1.60695e+10 | 9.14498e+06 | 15.8872 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1130.65 | 0.499631 | 463.105ms | 1834197 | 30 | 1.79249e+09 | 1.5471e+06 | 2.68733 | 1(Win) |
| glaze | 621.454 | 0.334104 | 1964.51ms | 1833577 | 40 | 3.5351e+09 | 2.81378e+06 | 4.88987 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2914.17 | 0.714875 | 971.986ms | 9930848 | 30 | 1.61929e+10 | 3.24991e+06 | 1.04267 | 1(Win) |
| glaze | 2599.49 | 0.453689 | 1098.65ms | 9930848 | 30 | 8.19663e+09 | 3.64333e+06 | 1.16892 | 2(Loss) |
| simdjson (ondemand) | 899.154 | 0.350284 | 33186.3ms | 9930848 | 160 | 2.17803e+11 | 1.0533e+07 | 3.3797 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3522.95 | 0.517071 | 805.203ms | 9930228 | 30 | 5.79596e+09 | 2.68814e+06 | 0.862509 | 1(Win) |
| jsonifier | 3314.34 | 0.49157 | 856.578ms | 9930848 | 30 | 5.91932e+09 | 2.85752e+06 | 0.916836 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 829.069 | 0.453676 | 636.414ms | 1834197 | 30 | 2.74868e+09 | 2.10987e+06 | 3.6651 | 1(Win) |
| glaze | 677.669 | 0.434978 | 772.523ms | 1834197 | 30 | 3.78193e+09 | 2.58124e+06 | 4.48389 | 2(Loss) |
| simdjson (ondemand) | 572.515 | 0.267783 | 926.537ms | 1834197 | 30 | 2.00819e+09 | 3.05534e+06 | 5.30771 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1139.1 | 0.314266 | 464.489ms | 1834197 | 30 | 6.98687e+08 | 1.53562e+06 | 2.6675 | 1(Win) |
| glaze | 601.328 | 0.269268 | 872.516ms | 1833577 | 30 | 1.83936e+09 | 2.90795e+06 | 5.05366 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2927.73 | 0.536753 | 2244.58ms | 9930848 | 40 | 1.20593e+10 | 3.23486e+06 | 1.03791 | 1(Win) |
| simdjson (ondemand) | 2604.35 | 0.23571 | 11458.1ms | 9930848 | 160 | 1.17558e+10 | 3.63653e+06 | 1.16666 | 2(Loss) |
| glaze | 2566.6 | 0.257692 | 1105.93ms | 9930848 | 30 | 2.71256e+09 | 3.69001e+06 | 1.18397 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3273.66 | 0.440129 | 877.831ms | 9930848 | 30 | 4.86392e+09 | 2.89303e+06 | 0.928198 | 1(Win) |
| glaze | 2736.33 | 0.627921 | 1047.79ms | 9930228 | 30 | 1.41682e+10 | 3.46092e+06 | 1.11028 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1454.81 | 0.987852 | 129.304ms | 642697 | 30 | 5.19642e+08 | 421308 | 2.08854 | 1(Win) |
| glaze | 1398.23 | 0.775375 | 133.625ms | 642697 | 30 | 3.46575e+08 | 438356 | 2.17281 | 2(Loss) |
| simdjson (ondemand) | 1134.84 | 0.665691 | 164.422ms | 642697 | 30 | 3.87804e+08 | 540098 | 2.6773 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1921.89 | 1.00484 | 95.9031ms | 642697 | 30 | 3.08086e+08 | 318917 | 1.58078 | 1(Win) |
| glaze | 1525.92 | 1.28603 | 118.545ms | 642692 | 30 | 8.00504e+08 | 401672 | 1.99074 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2140 | 1.12332 | 165.004ms | 1225964 | 30 | 1.12994e+09 | 546342 | 1.41963 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2113.31 | 0.682413 | 170.988ms | 1225964 | 30 | 4.27608e+08 | 553242 | 1.43765 | 1(Tie) |
| jsonifier | 1918.85 | 1.68816 | 179.868ms | 1225964 | 30 | 3.17413e+09 | 609308 | 1.58342 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2031.94 | 0.845289 | 173.268ms | 1225964 | 30 | 7.09687e+08 | 575397 | 1.49531 | 1(Win) |
| glaze | 1731.91 | 0.420573 | 204.814ms | 1225970 | 30 | 2.41832e+08 | 675080 | 1.75439 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1181.42 | 0.66263 | 100.991ms | 409725 | 30 | 1.44093e+08 | 330742 | 2.57178 | 1(Win) |
| glaze | 969.325 | 0.596817 | 291.635ms | 409725 | 40 | 2.3152e+08 | 403109 | 3.13428 | 2(Loss) |
| simdjson (ondemand) | 892.512 | 1.32757 | 129.881ms | 409725 | 30 | 1.01342e+09 | 437803 | 3.40372 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3626.78 | 1.0857 | 38.9947ms | 409725 | 30 | 4.10469e+07 | 107739 | 0.837541 | 1(Win) |
| glaze | 3270.23 | 1.82401 | 37.77ms | 409725 | 30 | 1.42496e+08 | 119485 | 0.928786 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1688.3 | 1.01994 | 134.519ms | 785750 | 30 | 6.14803e+08 | 443847 | 1.79924 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1655.3 | 0.606579 | 325.25ms | 785750 | 40 | 3.01613e+08 | 452697 | 1.83551 | 1(Tie) |
| glaze | 1501.67 | 0.368628 | 152.996ms | 785750 | 30 | 1.01513e+08 | 499012 | 2.02342 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5828.34 | 1.05288 | 93.3458ms | 785750 | 40 | 7.32991e+07 | 128570 | 0.52117 | 1(Win) |
| glaze | 3798.47 | 1.50135 | 301.951ms | 785750 | 80 | 7.01789e+08 | 197277 | 0.799659 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6421.01 | 0.754622 | 12.8697ms | 264040 | 30 | 2.62732e+06 | 39216.3 | 0.47295 | 1(Win) |
| simdjson (ondemand) | 5616.89 | 0.870672 | 14.8752ms | 264040 | 30 | 4.57065e+06 | 44830.5 | 0.540753 | 2(Loss) |
| glaze | 3285.49 | 0.564222 | 1017.33ms | 264040 | 640 | 1.1968e+08 | 76642.6 | 0.924532 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8068.74 | 0.589732 | 15.4153ms | 399947 | 30 | 2.33144e+06 | 47271.2 | 0.376381 | 1(Win) |
| simdjson (ondemand) | 7129.06 | 0.801678 | 92.4473ms | 399947 | 80 | 1.47174e+07 | 53502 | 0.426073 | 2(Loss) |
| glaze | 4103.99 | 2.15572 | 65.2108ms | 399947 | 40 | 1.6056e+08 | 92938.6 | 0.739996 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2115.62 | 1.82523 | 87.2557ms | 264040 | 40 | 1.88782e+08 | 119024 | 1.43584 | 1(Win) |
| glaze | 1785.81 | 0.705939 | 942.932ms | 264040 | 320 | 3.17067e+08 | 141005 | 1.70115 | 2(Loss) |
| simdjson (ondemand) | 1212.07 | 2.07011 | 57.5929ms | 264040 | 30 | 5.54877e+08 | 207751 | 2.50382 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7688.69 | 0.622699 | 10.9008ms | 264040 | 30 | 1.24771e+06 | 32750.5 | 0.394879 | 1(Win) |
| glaze | 5868.17 | 2.13224 | 68.4444ms | 263923 | 80 | 6.69134e+07 | 42891.9 | 0.517415 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2161.05 | 0.85081 | 553.954ms | 399947 | 160 | 3.60794e+08 | 176497 | 1.4058 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2125.75 | 1.21075 | 559.469ms | 399947 | 160 | 7.55105e+08 | 179428 | 1.42891 | 1(Tie) |
| glaze | 1950.51 | 2.21723 | 1205.57ms | 399947 | 320 | 6.01559e+09 | 195548 | 1.55731 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9254.05 | 1.25317 | 13.421ms | 399947 | 30 | 8.00353e+06 | 41216.5 | 0.328159 | 1(Win) |
| glaze | 4896.75 | 1.91357 | 122.555ms | 399830 | 80 | 1.77629e+08 | 77869.4 | 0.620245 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2838.43 | 4.79512 | 47.2012ms | 466906 | 30 | 1.69755e+09 | 156874 | 1.07028 | 1(Tie) |
| glaze STATISTICAL TIE | 2751.69 | 1.16184 | 246.117ms | 466906 | 80 | 2.82775e+08 | 161819 | 1.10416 | 1(Tie) |
| simdjson (ondemand) | 1268.3 | 0.745294 | 1107.46ms | 466906 | 160 | 1.09544e+09 | 351081 | 2.39529 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4277.16 | 0.938152 | 243.096ms | 699405 | 80 | 1.71231e+08 | 155946 | 0.710176 | 1(Win) |
| glaze | 3810.84 | 0.994886 | 55.3248ms | 699405 | 30 | 9.09673e+07 | 175028 | 0.797303 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4302.64 | 0.979512 | 447.615ms | 631514 | 160 | 3.0077e+08 | 139974 | 0.705938 | 1(Win) |
| glaze | 2480.63 | 1.42689 | 73.6918ms | 631514 | 30 | 3.60034e+08 | 242784 | 1.2243 | 2(Loss) |
