# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [f5d1ca8](https://github.com/nihilai-collective/jsonifier/commit/f5d1ca8)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10.000000% AND mean shift < 5.000000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

Every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. Parser instances are reused.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1020.3 | 0.459373 | 1061.44ms | 905 | 40 | 603.99 | 845.9 | 2.32204 | 1(Win) |
| glaze | 741.267 | 0.60019 | 1135.09ms | 905 | 80 | 3906.75 | 1164.33 | 3.22594 | 2(Loss) |
| simdjson (ondemand) | 107.829 | 1.1996 | 1758.44ms | 905 | 320 | 2.95021e+06 | 8004.14 | 22.8499 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 875.241 | 0.0945279 | 1249.4ms | 905 | 160 | 139.021 | 986.1 | 2.71851 | 1(Win) |
| glaze | 107.473 | 2.53473 | 1728ms | 905 | 4890 | 2.02614e+08 | 8030.61 | 22.9193 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 694.657 | 0.155054 | 1230.5ms | 1811 | 320 | 4755.68 | 2486.27 | 3.50878 | 1(Win) |
| glaze | 514.903 | 0.497796 | 1305.74ms | 1811 | 160 | 44607.7 | 3354.23 | 4.75279 | 2(Loss) |
| simdjson (ondemand) | 130.229 | 0.655867 | 2254.9ms | 1811 | 4890 | 3.69968e+07 | 13262.1 | 18.9553 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 168.113 | 1.82711 | 1960.04ms | 1811 | 4890 | 1.72295e+08 | 10273.5 | 14.6647 | 1(Win) |
| glaze | 158.01 | 0.035039 | 2084.29ms | 1798 | 80 | 1156.66 | 10851.9 | 15.6125 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1487.75 | 0.309404 | 1222.78ms | 3862 | 160 | 9387.22 | 2475.61 | 1.63872 | 1(Win) |
| glaze | 884.463 | 0.133822 | 1397.69ms | 3862 | 160 | 4968.7 | 4164.21 | 2.77424 | 2(Loss) |
| simdjson (ondemand) | 309.227 | 0.0590636 | 2187.42ms | 3862 | 40 | 1979.57 | 11910.6 | 7.98143 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 453.629 | 0.0815602 | 1807.91ms | 3862 | 40 | 1754.05 | 8119.18 | 5.43176 | 1(Tie) |
| jsonifier STATISTICAL TIE | 442.482 | 1.74473 | 1784.63ms | 3862 | 4890 | 1.03133e+08 | 8323.7 | 5.5691 | 1(Tie) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 762.193 | 0.717656 | 2142.83ms | 9578 | 4890 | 3.61711e+07 | 11984.2 | 3.23669 | 1(Win) |
| glaze | 738.132 | 1.30421 | 2235.05ms | 9578 | 40 | 1.04193e+06 | 12374.9 | 3.34386 | 2(Loss) |
| simdjson (ondemand) | 524.753 | 0.562595 | 2666.81ms | 9578 | 4890 | 4.68966e+07 | 17406.9 | 4.70642 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1320.09 | 0.094048 | 1686.12ms | 9578 | 30 | 1270.46 | 6919.43 | 1.86517 | 1(Win) |
| glaze | 1063.98 | 0.071842 | 1854.47ms | 9578 | 40 | 1521.59 | 8585 | 2.3166 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1656.64 | 0.311521 | 1194.41ms | 3873 | 640 | 30874 | 2229.56 | 1.46909 | 1(Win) |
| glaze | 974.637 | 0.251723 | 1354.48ms | 3873 | 40 | 3640.11 | 3789.7 | 2.51474 | 2(Loss) |
| simdjson (ondemand) | 288.843 | 0.699645 | 2200.7ms | 3873 | 4890 | 3.91413e+07 | 12787.5 | 8.54542 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 457.686 | 0.213237 | 1795.91ms | 3873 | 40 | 11845.2 | 8070.12 | 5.38159 | 1(Win) |
| glaze | 441.376 | 0.11623 | 1829.99ms | 3873 | 40 | 3784.17 | 8368.33 | 5.58433 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 475.957 | 0.111081 | 6289.48ms | 2090234 | 40 | 8.65748e+08 | 4.1882e+06 | 5.20154 | 1(Win) |
| glaze | 371.203 | 0.0919092 | 8151.81ms | 2090234 | 30 | 7.30813e+08 | 5.37011e+06 | 6.66941 | 2(Loss) |
| simdjson (ondemand) | 300.889 | 0.0747193 | 9960.88ms | 2090234 | 80 | 1.96034e+09 | 6.62503e+06 | 8.22802 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 675.045 | 0.0283905 | 9183.23ms | 2090234 | 30 | 2.10858e+07 | 2.95299e+06 | 3.66737 | 1(Win) |
| glaze | 609.067 | 0.0825239 | 10183.6ms | 2090234 | 30 | 2.18847e+08 | 3.27288e+06 | 4.06475 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1226.52 | 0.0695239 | 7799.27ms | 6661897 | 30 | 3.89076e+08 | 5.17991e+06 | 2.01849 | 1(Win) |
| glaze | 972.06 | 0.0325629 | 9824.3ms | 6661897 | 40 | 1.81182e+08 | 6.53589e+06 | 2.5469 | 2(Loss) |
| simdjson (ondemand) | 900.842 | 0.0384367 | 10593.1ms | 6661897 | 40 | 2.93934e+08 | 7.0526e+06 | 2.74822 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2136.63 | 0.016734 | 9255.26ms | 6661897 | 160 | 3.96148e+07 | 2.9735e+06 | 1.15868 | 1(Win) |
| glaze | 1541.94 | 0.025706 | 6198.3ms | 6661897 | 80 | 8.97477e+07 | 4.12033e+06 | 1.60557 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 963.954 | 0.100606 | 6420.57ms | 500299 | 640 | 1.58698e+08 | 494964 | 2.56777 | 1(Win) |
| glaze | 859.462 | 0.094876 | 7186.27ms | 500299 | 640 | 1.77541e+08 | 555141 | 2.88005 | 2(Loss) |
| simdjson (ondemand) | 605.876 | 0.105094 | 5019.36ms | 500299 | 160 | 1.09589e+08 | 787492 | 4.08565 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5685.71 | 0.128466 | 9432.24ms | 500299 | 4890 | 5.68295e+07 | 83916.1 | 0.435107 | 1(Win) |
| glaze | 2261.3 | 0.156471 | 5659.4ms | 500299 | 640 | 6.97576e+07 | 210995 | 1.09444 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2079.66 | 0.221815 | 8604.68ms | 1439562 | 640 | 1.37227e+09 | 660144 | 1.19023 | 1(Win) |
| glaze | 1562.62 | 0.108163 | 5603.02ms | 1439562 | 160 | 1.44487e+08 | 878569 | 1.58413 | 2(Loss) |
| simdjson (ondemand) | 1526.9 | 0.0945627 | 5728.06ms | 1439562 | 160 | 1.15664e+08 | 899122 | 1.62119 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13067.5 | 0.145129 | 5907.17ms | 1439562 | 2560 | 5.95143e+07 | 105060 | 0.189347 | 1(Win) |
| glaze | 3151.6 | 0.0990224 | 5683.23ms | 1439584 | 640 | 1.19086e+08 | 435619 | 0.78541 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1103.58 | 0.295819 | 5813.83ms | 56369 | 2560 | 5.31575e+07 | 48712 | 2.24157 | 1(Win) |
| glaze | 823.021 | 0.223079 | 7481.64ms | 56369 | 2560 | 5.43522e+07 | 65317.5 | 3.00622 | 2(Loss) |
| simdjson (ondemand) | 754.722 | 0.148144 | 8060.4ms | 56369 | 4890 | 5.44485e+07 | 71228.5 | 3.27856 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6336.76 | 0.456608 | 1865.43ms | 56369 | 30 | 45014.7 | 8483.47 | 0.389015 | 1(Win) |
| glaze | 2615.4 | 0.128758 | 3097.04ms | 56369 | 30 | 21012.4 | 20554.3 | 0.944971 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1453.38 | 0.171588 | 7145.61ms | 94370 | 4890 | 5.52069e+07 | 61923.4 | 1.70235 | 1(Win) |
| simdjson (ondemand) | 1209.77 | 0.156968 | 8400.28ms | 94370 | 4890 | 6.66801e+07 | 74393 | 2.04537 | 2(Loss) |
| glaze | 1189.59 | 0.258282 | 8512.91ms | 94370 | 1280 | 4.88731e+07 | 75654.7 | 2.0793 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9950.19 | 0.0792746 | 1925.78ms | 94370 | 40 | 2056.52 | 9044.88 | 0.247754 | 1(Win) |
| glaze | 2665.06 | 0.384647 | 4324.1ms | 94370 | 2560 | 4.31935e+07 | 33769.7 | 0.927875 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 897.336 | 0.660912 | 2205.2ms | 11812 | 4890 | 3.36615e+07 | 12553.6 | 2.75073 | 1(Win) |
| glaze | 766.661 | 0.622863 | 2410.98ms | 11812 | 4890 | 4.09576e+07 | 14693.3 | 3.22079 | 2(Loss) |
| simdjson (ondemand) | 652.494 | 0.539768 | 2672.48ms | 11812 | 4890 | 4.24636e+07 | 17264.2 | 3.78391 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4444.24 | 0.54368 | 1240.27ms | 11812 | 1280 | 243080 | 2534.7 | 0.548874 | 1(Win) |
| glaze | 1833.39 | 0.286061 | 1609.24ms | 11812 | 30 | 9267.77 | 6144.23 | 1.34219 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1924.04 | 0.107297 | 2589.8ms | 31235 | 80 | 22075.9 | 15482 | 1.28367 | 1(Win) |
| simdjson (ondemand) | 1563.95 | 0.483396 | 2845.77ms | 31235 | 4890 | 4.14526e+07 | 19046.6 | 1.57982 | 2(Loss) |
| glaze | 1424.86 | 0.851389 | 3021.84ms | 31235 | 1280 | 4.05512e+07 | 20905.9 | 1.73429 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10007.5 | 0.31885 | 1277.24ms | 31235 | 4890 | 440470 | 2976.58 | 0.244285 | 1(Win) |
| glaze | 2707.23 | 0.828216 | 2040.03ms | 31235 | 4890 | 4.06096e+07 | 11003.1 | 0.911294 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1427.33 | 0.185589 | 8192.48ms | 108313 | 2560 | 4.61805e+07 | 72369.9 | 1.73327 | 1(Win) |
| glaze | 1067.69 | 0.215214 | 5451.11ms | 108313 | 1280 | 5.54904e+07 | 96746.2 | 2.31772 | 2(Loss) |
| simdjson (ondemand) | 876.934 | 0.179147 | 6524.95ms | 108313 | 1280 | 5.69973e+07 | 117791 | 2.82197 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9757.41 | 0.0951462 | 2078.75ms | 108313 | 80 | 8116.43 | 10586.4 | 0.252782 | 1(Win) |
| glaze | 1449.16 | 0.299815 | 8057.93ms | 108313 | 1280 | 5.84582e+07 | 71279.4 | 1.70744 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1587 | 0.131366 | 7040.6ms | 213963 | 2560 | 7.30342e+07 | 128576 | 1.55944 | 1(Win) |
| jsonifier STATISTICAL TIE | 1511.54 | 0.361126 | 7384.78ms | 213963 | 320 | 7.6051e+07 | 134995 | 1.63732 | 2(Tie) |
| glaze STATISTICAL TIE | 1511.21 | 0.124077 | 7373.11ms | 213963 | 2560 | 7.18539e+07 | 135025 | 1.63768 | 2(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14478.7 | 0.626609 | 2372.54ms | 213963 | 4890 | 3.81348e+07 | 14093.2 | 0.170533 | 1(Win) |
| glaze | 1690.42 | 0.126707 | 6665.73ms | 213963 | 2560 | 5.98866e+07 | 120710 | 1.4639 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 459.638 | 0.0654132 | 5727ms | 1834197 | 80 | 4.95772e+08 | 3.80566e+06 | 5.38614 | 1(Win) |
| glaze | 358.468 | 0.0736937 | 7342.13ms | 1834197 | 40 | 5.17264e+08 | 4.87973e+06 | 6.90638 | 2(Loss) |
| simdjson (ondemand) | 297.807 | 0.0691309 | 8834.14ms | 1834197 | 40 | 6.59516e+08 | 5.87369e+06 | 8.31318 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 439.538 | 0.0269183 | 5988.68ms | 1834197 | 80 | 9.18089e+07 | 3.9797e+06 | 5.63247 | 1(Win) |
| glaze | 397.608 | 0.0275389 | 6616.27ms | 1833577 | 80 | 1.17347e+08 | 4.39788e+06 | 6.22648 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1801.96 | 0.0758594 | 7895.53ms | 9930848 | 80 | 1.27173e+09 | 5.25584e+06 | 1.3739 | 1(Win) |
| glaze STATISTICAL TIE | 1404.49 | 0.0647622 | 10120.8ms | 9930848 | 80 | 1.52571e+09 | 6.74325e+06 | 1.76273 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1402.32 | 0.0882003 | 10141.8ms | 9930848 | 40 | 1.41931e+09 | 6.75364e+06 | 1.76544 | 2(Tie) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2302.23 | 0.058547 | 6192.01ms | 9930848 | 30 | 1.74023e+08 | 4.11375e+06 | 1.07534 | 1(Win) |
| glaze | 1655.74 | 0.0318411 | 8596.94ms | 9930228 | 80 | 2.65339e+08 | 5.71962e+06 | 1.49524 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 461.709 | 0.0644457 | 5711.68ms | 1834197 | 80 | 4.76905e+08 | 3.78859e+06 | 5.36197 | 1(Win) |
| glaze | 352.625 | 0.102592 | 7448.96ms | 1834197 | 30 | 7.76985e+08 | 4.96058e+06 | 7.0208 | 2(Loss) |
| simdjson (ondemand) | 295.237 | 0.0579254 | 8903.46ms | 1834197 | 30 | 3.53355e+08 | 5.92483e+06 | 8.3855 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 439.047 | 0.0589522 | 5993.84ms | 1834197 | 30 | 1.65497e+08 | 3.98414e+06 | 5.63884 | 1(Win) |
| glaze | 392.436 | 0.0943449 | 6695.65ms | 1833577 | 30 | 5.30175e+08 | 4.45585e+06 | 6.30852 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1801.62 | 0.0763836 | 7896.68ms | 9930848 | 80 | 1.28985e+09 | 5.25683e+06 | 1.37415 | 1(Win) |
| glaze | 1413.56 | 0.0678667 | 10086.2ms | 9930848 | 40 | 8.27021e+08 | 6.69995e+06 | 1.75141 | 2(Loss) |
| simdjson (ondemand) | 1393.08 | 0.0403748 | 10226ms | 9930848 | 80 | 6.02739e+08 | 6.79844e+06 | 1.77715 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2311.28 | 0.0494013 | 6169.85ms | 9930848 | 30 | 1.22932e+08 | 4.09765e+06 | 1.07114 | 1(Win) |
| glaze | 1535.09 | 0.0548839 | 9275.73ms | 9930228 | 30 | 3.43924e+08 | 6.16916e+06 | 1.61273 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 722.829 | 0.0896283 | 5404.48ms | 642697 | 320 | 1.84834e+08 | 847951 | 3.42459 | 1(Win) |
| jsonifier | 711.06 | 0.142199 | 5484.1ms | 642697 | 160 | 2.40388e+08 | 861986 | 3.48137 | 2(Loss) |
| simdjson (ondemand) | 557.558 | 0.108546 | 7013.89ms | 642697 | 160 | 2.27812e+08 | 1.0993e+06 | 4.43987 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 734.406 | 0.104897 | 5329.49ms | 642697 | 80 | 6.13139e+07 | 834584 | 3.37066 | 1(Win) |
| glaze | 626.425 | 0.0573216 | 6229.07ms | 642692 | 160 | 5.03298e+07 | 978440 | 3.95177 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1102.03 | 0.0687519 | 6748.64ms | 1225964 | 320 | 1.70252e+08 | 1.06093e+06 | 2.2463 | 1(Win) |
| simdjson (ondemand) | 1016.68 | 0.0658526 | 7301.58ms | 1225964 | 320 | 1.83518e+08 | 1.14999e+06 | 2.43486 | 2(Loss) |
| jsonifier | 1006.32 | 0.0798712 | 7391.1ms | 1225964 | 320 | 2.75558e+08 | 1.16183e+06 | 2.45997 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1405.96 | 0.0889142 | 5309.35ms | 1225964 | 80 | 4.37362e+07 | 831581 | 1.76068 | 1(Win) |
| glaze | 1020.86 | 0.0497813 | 7282.9ms | 1225970 | 320 | 1.04018e+08 | 1.14528e+06 | 2.42493 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 790.48 | 0.163431 | 6434.33ms | 409725 | 160 | 1.04423e+08 | 494313 | 3.13138 | 1(Win) |
| glaze | 578.145 | 0.0925061 | 8697.34ms | 409725 | 640 | 2.50169e+08 | 675859 | 4.28155 | 2(Loss) |
| simdjson (ondemand) | 552.813 | 0.0612204 | 9116.83ms | 409725 | 640 | 1.1984e+08 | 706829 | 4.47774 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3426.63 | 0.138794 | 6377.72ms | 409725 | 2560 | 6.41258e+07 | 114032 | 0.722111 | 1(Win) |
| glaze | 1661.49 | 0.219035 | 6358.86ms | 409725 | 640 | 1.69823e+08 | 235177 | 1.4896 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1179.19 | 0.184284 | 8234.77ms | 785750 | 80 | 1.09716e+08 | 635480 | 2.0992 | 1(Win) |
| simdjson (ondemand) | 998.74 | 0.0555573 | 9652.78ms | 785750 | 640 | 1.11205e+08 | 750295 | 2.47847 | 2(Loss) |
| glaze | 947.031 | 0.0909095 | 5077.47ms | 785750 | 160 | 8.27902e+07 | 791262 | 2.61383 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6031.05 | 0.128214 | 6889.89ms | 785750 | 2560 | 6.49668e+07 | 124249 | 0.410314 | 1(Win) |
| glaze | 2273.6 | 0.136325 | 8679.93ms | 785750 | 640 | 1.29203e+08 | 329588 | 1.08866 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2836.67 | 0.16814 | 5012.51ms | 264040 | 2560 | 5.70298e+07 | 88768.9 | 0.872286 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2830.32 | 0.237428 | 5033.15ms | 264040 | 1280 | 5.7114e+07 | 88968.2 | 0.874331 | 1(Tie) |
| glaze | 1873.41 | 0.135288 | 7353.64ms | 264040 | 2560 | 8.46506e+07 | 134412 | 1.32106 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3729.62 | 0.16066 | 5691.56ms | 399947 | 2560 | 6.91081e+07 | 102267 | 0.663473 | 1(Win) |
| jsonifier | 3678.65 | 0.161291 | 5771.49ms | 399947 | 2560 | 7.15961e+07 | 103684 | 0.672719 | 2(Loss) |
| glaze | 2433.15 | 0.234314 | 8464.85ms | 399947 | 640 | 8.63463e+07 | 156760 | 1.01719 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1062.5 | 0.167971 | 6331.67ms | 264040 | 640 | 1.01421e+08 | 236996 | 2.32943 | 1(Win) |
| simdjson (ondemand) | 946.799 | 0.174138 | 7050.13ms | 264040 | 640 | 1.37275e+08 | 265957 | 2.61406 | 2(Loss) |
| glaze | 934.225 | 0.144939 | 7155.38ms | 264040 | 640 | 9.76753e+07 | 269537 | 2.64945 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7291.23 | 0.289015 | 4433.35ms | 264040 | 4890 | 4.8718e+07 | 34535.8 | 0.338978 | 1(Win) |
| glaze | 2785.06 | 0.188342 | 5147.21ms | 263923 | 2560 | 7.41684e+07 | 90373.9 | 0.888248 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1360 | 0.227772 | 7419.67ms | 399947 | 320 | 1.30582e+08 | 280456 | 1.81996 | 1(Win) |
| glaze | 1168.07 | 0.147328 | 8592.17ms | 399947 | 1280 | 2.96243e+08 | 326539 | 2.11889 | 2(Loss) |
| jsonifier | 1122.78 | 0.098977 | 8950.79ms | 399947 | 1280 | 1.4471e+08 | 339711 | 2.20389 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9805.75 | 0.246543 | 4902.39ms | 399947 | 4890 | 4.49716e+07 | 38897.5 | 0.252141 | 1(Win) |
| glaze | 2653.39 | 0.123345 | 7886.28ms | 399830 | 2560 | 8.04323e+07 | 143706 | 0.932565 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1665.36 | 0.1407 | 7076.94ms | 466906 | 640 | 9.05756e+07 | 267375 | 1.48624 | 1(Win) |
| glaze | 1436.08 | 0.213719 | 8187.72ms | 466906 | 320 | 1.40521e+08 | 310065 | 1.72358 | 2(Loss) |
| simdjson (ondemand) | 684 | 0.141314 | 8417.62ms | 466906 | 160 | 1.35406e+08 | 650988 | 3.61894 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2131.33 | 0.0905838 | 8273.75ms | 699405 | 1280 | 1.02865e+08 | 312952 | 1.16132 | 1(Tie) |
| glaze STATISTICAL TIE | 2127.42 | 0.221061 | 8378.66ms | 699405 | 160 | 7.68593e+07 | 313528 | 1.16346 | 1(Tie) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2414.64 | 0.115759 | 6618.73ms | 631514 | 1280 | 1.06703e+08 | 249420 | 1.02504 | 1(Win) |
| glaze | 1499.39 | 0.13858 | 5233.96ms | 631514 | 320 | 9.91482e+07 | 401668 | 1.65092 | 2(Loss) |
