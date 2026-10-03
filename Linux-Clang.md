# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [dded0f9](https://github.com/nihilai-collective/jsonifier/commit/dded0f9)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX512BW` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (INTEL(R) XEON(R) PLATINUM 8573C-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10.000000% AND mean shift < 5.000000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 1340.65 | 0.532491 | 478.046ms | 905 | 4890 | 57464.6 | 643.775 | 1.55896 | 1(Win) |
| glaze | 1068.7 | 0.555795 | 489.217ms | 905 | 4890 | 98520.5 | 807.596 | 1.98106 | 2(Loss) |
| simdjson (ondemand) | 143.404 | 0.311451 | 1017.64ms | 905 | 320 | 112435 | 6018.47 | 15.1698 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 933.704 | 0.418114 | 502.967ms | 905 | 160 | 2389.94 | 924.356 | 2.27751 | 1(Win) |
| glaze | 132.663 | 0.571857 | 1062.02ms | 905 | 640 | 885832 | 6505.77 | 16.4622 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 904.654 | 0.149292 | 613.803ms | 1811 | 30 | 243.706 | 1909.13 | 2.38597 | 1(Win) |
| glaze | 639.972 | 0.0820236 | 690.854ms | 1811 | 320 | 1567.99 | 2698.72 | 3.38861 | 2(Loss) |
| simdjson (ondemand) | 185.608 | 0.142766 | 1364.92ms | 1811 | 40 | 7059.14 | 9305.12 | 11.7784 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 221.702 | 0.203469 | 1198.22ms | 1811 | 320 | 80397.9 | 7790.19 | 9.85137 | 1(Win) |
| glaze | 207.09 | 0.246514 | 1253.76ms | 1798 | 40 | 16665.1 | 8280.02 | 10.556 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1977.59 | 0.295471 | 602.462ms | 3862 | 80 | 2422.55 | 1862.41 | 1.08864 | 1(Win) |
| glaze | 1261.12 | 0.111005 | 701.632ms | 3862 | 80 | 840.785 | 2920.49 | 1.71953 | 2(Loss) |
| simdjson (ondemand) | 383.85 | 1.56867 | 1329.13ms | 3862 | 4890 | 1.10784e+08 | 9595.13 | 5.69516 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 633.86 | 0.204051 | 991.739ms | 3862 | 40 | 5623.12 | 5810.57 | 3.43868 | 1(Win) |
| glaze | 582.385 | 0.236065 | 1048.47ms | 3862 | 40 | 8915.16 | 6324.15 | 3.7454 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 988.716 | 1.59858 | 1306.49ms | 9578 | 4890 | 1.06656e+08 | 9238.54 | 2.21017 | 1(Win) |
| glaze | 904.435 | 0.733289 | 1423.44ms | 9578 | 320 | 1.75507e+06 | 10099.4 | 2.41674 | 2(Loss) |
| simdjson (ondemand) | 683.527 | 1.2811 | 1704.63ms | 9578 | 4890 | 1.43322e+08 | 13363.5 | 3.20118 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1639.75 | 1.35355 | 977.927ms | 9578 | 40 | 227407 | 5570.52 | 1.32877 | 1(Win) |
| glaze | 1356.46 | 0.248376 | 1121.05ms | 9578 | 80 | 22379.3 | 6733.94 | 1.60904 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2190.26 | 0.156042 | 582.291ms | 3873 | 80 | 553.956 | 1686.36 | 0.982591 | 1(Win) |
| glaze | 1338.05 | 0.373736 | 684.669ms | 3873 | 2560 | 272472 | 2760.43 | 1.62051 | 2(Loss) |
| simdjson (ondemand) | 406.336 | 0.842939 | 1325.77ms | 3873 | 320 | 1.87874e+06 | 9089.97 | 5.37904 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 626.803 | 0.282811 | 996.337ms | 3873 | 40 | 11109.3 | 5892.73 | 3.47812 | 1(Win) |
| glaze | 579.458 | 0.193118 | 1068.49ms | 3873 | 30 | 4545.89 | 6374.2 | 3.76461 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 631.727 | 0.0663049 | 9845.93ms | 2090234 | 40 | 1.75098e+08 | 3.15548e+06 | 3.47193 | 1(Win) |
| glaze | 473.735 | 0.0851128 | 6310.3ms | 2090234 | 80 | 1.02612e+09 | 4.20784e+06 | 4.62995 | 2(Loss) |
| simdjson (ondemand) | 421.122 | 0.185372 | 7092.76ms | 2090234 | 40 | 3.07981e+09 | 4.73355e+06 | 5.20846 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1079.57 | 0.0782306 | 5755.1ms | 2090234 | 30 | 6.25981e+07 | 1.84648e+06 | 2.03145 | 1(Win) |
| glaze | 634.979 | 0.063118 | 9759.25ms | 2090234 | 30 | 1.17787e+08 | 3.13932e+06 | 3.45414 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1661.16 | 0.0507644 | 5739.76ms | 6661897 | 80 | 3.01566e+08 | 3.82461e+06 | 1.32035 | 1(Win) |
| simdjson (ondemand) | 1258.08 | 0.163396 | 7590.9ms | 6661897 | 30 | 2.04259e+09 | 5.04997e+06 | 1.74339 | 2(Loss) |
| glaze | 1204.94 | 0.0611825 | 7912.77ms | 6661897 | 80 | 8.32552e+08 | 5.27271e+06 | 1.82033 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3659.12 | 0.135849 | 5401.58ms | 6661897 | 30 | 1.66909e+08 | 1.73629e+06 | 0.599348 | 1(Win) |
| glaze | 1992.77 | 0.0662783 | 9933.84ms | 6661897 | 40 | 1.78601e+08 | 3.18817e+06 | 1.10059 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1234.29 | 0.067512 | 9941.25ms | 500299 | 1280 | 8.71767e+07 | 386558 | 1.77691 | 1(Win) |
| glaze | 1204.5 | 0.119831 | 5099.32ms | 500299 | 320 | 7.20991e+07 | 396116 | 1.82083 | 2(Loss) |
| simdjson (ondemand) | 885.793 | 0.179579 | 6945.12ms | 500299 | 160 | 1.49702e+08 | 538639 | 2.4758 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6972.66 | 0.115231 | 7202.98ms | 500299 | 4890 | 3.04024e+07 | 68427.6 | 0.314414 | 1(Win) |
| glaze | 3643.75 | 0.284691 | 6896.44ms | 500299 | 1280 | 1.77877e+08 | 130943 | 0.601674 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2420.39 | 0.106383 | 7281.38ms | 1439562 | 640 | 2.33033e+08 | 567212 | 0.90591 | 1(Win) |
| simdjson (ondemand) | 2172.96 | 0.182742 | 8114.52ms | 1439562 | 160 | 2.13282e+08 | 631798 | 1.00909 | 2(Loss) |
| glaze | 2001.5 | 0.0878501 | 8790.47ms | 1439562 | 320 | 1.16195e+08 | 685924 | 1.0956 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13553.6 | 0.135366 | 5402.5ms | 1439562 | 2560 | 4.81293e+07 | 101292 | 0.161661 | 1(Win) |
| glaze | 3710.53 | 0.136763 | 9586.22ms | 1439584 | 640 | 1.63878e+08 | 370000 | 0.590834 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1406.64 | 0.165416 | 4207.41ms | 56369 | 4890 | 1.95425e+07 | 38217.1 | 1.55767 | 1(Win) |
| glaze | 1195.3 | 0.199643 | 4880.02ms | 56369 | 4890 | 3.94225e+07 | 44974.2 | 1.83348 | 2(Loss) |
| simdjson (ondemand) | 1025.45 | 0.128518 | 5632.55ms | 56369 | 4890 | 2.21965e+07 | 52423.3 | 2.13744 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7442.3 | 0.527685 | 1147.12ms | 56369 | 320 | 464907 | 7223.26 | 0.293249 | 1(Win) |
| glaze | 4065.83 | 1.22622 | 1751.34ms | 56369 | 30 | 788574 | 13221.8 | 0.537926 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1697.64 | 0.20548 | 5673.41ms | 94370 | 2560 | 3.03779e+07 | 53013.8 | 1.29104 | 1(Win) |
| simdjson (ondemand) | 1657.11 | 0.197776 | 5829.89ms | 94370 | 2560 | 2.95361e+07 | 54310.5 | 1.32257 | 2(Loss) |
| jsonifier | 1486.82 | 0.160423 | 6437.9ms | 94370 | 2560 | 2.41392e+07 | 60530.7 | 1.47432 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10694.9 | 0.202303 | 1279.27ms | 94370 | 80 | 23185 | 8415.04 | 0.204258 | 1(Win) |
| glaze | 3353.16 | 0.251152 | 3056.97ms | 94370 | 4890 | 2.222e+07 | 26839.9 | 0.653093 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1201.31 | 0.383755 | 1360.46ms | 11812 | 160 | 207189 | 9377.11 | 1.81972 | 1(Win) |
| glaze | 1139.33 | 0.58125 | 1415.65ms | 11812 | 40 | 132110 | 9887.25 | 1.91925 | 2(Loss) |
| simdjson (ondemand) | 968.038 | 0.215737 | 1574.99ms | 11812 | 30 | 18907.5 | 11636.7 | 2.25984 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5670.09 | 0.367098 | 617.931ms | 11812 | 1280 | 68083.3 | 1986.7 | 0.380106 | 1(Win) |
| glaze | 2658.01 | 2.22546 | 847.923ms | 11812 | 160 | 1.4233e+06 | 4238.06 | 0.818524 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2298.12 | 0.238384 | 1724.31ms | 31235 | 80 | 76380.9 | 12961.9 | 0.951967 | 1(Win) |
| jsonifier | 1985.56 | 0.996625 | 1872.61ms | 31235 | 4890 | 1.09318e+08 | 15002.3 | 1.10193 | 2(Loss) |
| glaze | 1662.69 | 0.727473 | 2184.12ms | 31235 | 1280 | 2.17422e+07 | 17915.5 | 1.31675 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11773.4 | 0.168254 | 680.717ms | 31235 | 160 | 2899.56 | 2530.12 | 0.183649 | 1(Win) |
| glaze | 3588.33 | 0.88358 | 1271.51ms | 31235 | 40 | 215203 | 8301.35 | 0.608535 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1839.97 | 0.130123 | 5999.33ms | 108313 | 4890 | 2.60952e+07 | 56139.7 | 1.19124 | 1(Win) |
| glaze | 1561.04 | 0.17962 | 6983.81ms | 108313 | 2560 | 3.61646e+07 | 66171 | 1.40425 | 2(Loss) |
| simdjson (ondemand) | 1310.31 | 0.117444 | 8243.7ms | 108313 | 4890 | 4.19166e+07 | 78832.9 | 1.6731 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11249 | 0.190759 | 1346ms | 108313 | 40 | 12273.4 | 9182.62 | 0.194243 | 1(Win) |
| glaze | 3651.93 | 0.477399 | 3197.59ms | 108313 | 2560 | 4.66787e+07 | 28285.1 | 0.599775 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2403.54 | 0.136622 | 8870.9ms | 213963 | 2560 | 3.44397e+07 | 84896.1 | 0.912135 | 1(Win) |
| jsonifier | 1971.02 | 0.214776 | 5498.76ms | 213963 | 640 | 3.16407e+07 | 103525 | 1.11235 | 2(Loss) |
| glaze | 1940.87 | 0.2203 | 5566.28ms | 213963 | 640 | 3.43315e+07 | 105134 | 1.12956 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13641.9 | 1.46972 | 1870.21ms | 213963 | 2560 | 1.2372e+08 | 14957.7 | 0.160401 | 1(Win) |
| glaze | 3484.75 | 0.212958 | 6235.18ms | 213963 | 2560 | 3.98073e+07 | 58555.4 | 0.628974 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 559.303 | 0.10361 | 9717.93ms | 1834197 | 40 | 4.2001e+08 | 3.12751e+06 | 3.92152 | 1(Win) |
| simdjson (ondemand) | 442.445 | 0.147612 | 5959.49ms | 1834197 | 40 | 1.36231e+09 | 3.95355e+06 | 4.95738 | 2(Loss) |
| glaze | 434.769 | 0.16267 | 6002.28ms | 1834197 | 30 | 1.28503e+09 | 4.02335e+06 | 5.04491 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 554.067 | 0.0568699 | 9790.79ms | 1834197 | 80 | 2.57883e+08 | 3.15707e+06 | 3.95859 | 1(Win) |
| glaze | 418.902 | 0.0383504 | 6288.86ms | 1833577 | 40 | 1.02512e+08 | 4.17433e+06 | 5.23598 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2174.4 | 0.0988101 | 6593.14ms | 9930848 | 80 | 1.48179e+09 | 4.35559e+06 | 1.00873 | 1(Win) |
| simdjson (ondemand) | 2120.14 | 0.106217 | 6724.48ms | 9930848 | 30 | 6.75395e+08 | 4.46707e+06 | 1.03455 | 2(Loss) |
| glaze | 1738.48 | 0.14439 | 8208.22ms | 9930848 | 30 | 1.85621e+09 | 5.44774e+06 | 1.26169 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4118.8 | 0.10485 | 7146.77ms | 9930848 | 80 | 4.65006e+08 | 2.29941e+06 | 0.532491 | 1(Win) |
| glaze | 2274.19 | 0.055088 | 6270.09ms | 9930228 | 80 | 4.20989e+08 | 4.16421e+06 | 0.964458 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 569.126 | 0.0723643 | 9557.01ms | 1834197 | 160 | 7.91489e+08 | 3.07353e+06 | 3.85383 | 1(Win) |
| simdjson (ondemand) | 438.817 | 0.162408 | 5983.12ms | 1834197 | 30 | 1.25737e+09 | 3.98623e+06 | 4.9984 | 2(Loss) |
| glaze | 432.156 | 0.124023 | 6089.02ms | 1834197 | 80 | 2.01608e+09 | 4.04768e+06 | 5.07543 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 552.039 | 0.0702386 | 9838.43ms | 1834197 | 30 | 1.48602e+08 | 3.16866e+06 | 3.97318 | 1(Win) |
| glaze | 407.09 | 0.0450673 | 6458.16ms | 1833577 | 40 | 1.49899e+08 | 4.29545e+06 | 5.38798 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2166.74 | 0.0886297 | 6550.26ms | 9930848 | 80 | 1.20062e+09 | 4.37098e+06 | 1.0123 | 1(Win) |
| simdjson (ondemand) | 2100.71 | 0.18471 | 6780.55ms | 9930848 | 30 | 2.08038e+09 | 4.50837e+06 | 1.04411 | 2(Loss) |
| glaze | 1714.69 | 0.119301 | 8346.37ms | 9930848 | 40 | 1.7368e+09 | 5.52334e+06 | 1.2792 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4204.11 | 0.138409 | 7043.27ms | 9930848 | 30 | 2.91661e+08 | 2.25275e+06 | 0.521667 | 1(Win) |
| glaze | 1944.03 | 0.0925871 | 7309.67ms | 9930228 | 30 | 6.10291e+08 | 4.87144e+06 | 1.12821 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 898.124 | 0.143302 | 8774.94ms | 642697 | 160 | 1.53025e+08 | 682449 | 2.4415 | 1(Win) |
| glaze | 894.112 | 0.108756 | 8766.73ms | 642697 | 320 | 1.77863e+08 | 685511 | 2.45246 | 2(Loss) |
| simdjson (ondemand) | 840.783 | 0.0972547 | 9321.36ms | 642697 | 320 | 1.60848e+08 | 728991 | 2.60793 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 831.571 | 0.0561364 | 9437.36ms | 642697 | 640 | 1.09568e+08 | 737067 | 2.63749 | 1(Win) |
| glaze | 669.032 | 0.0654067 | 5819.61ms | 642692 | 320 | 1.14896e+08 | 916128 | 3.27758 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1529.69 | 0.0948092 | 9769.29ms | 1225964 | 320 | 1.68035e+08 | 764319 | 1.43345 | 1(Win) |
| glaze | 1421.98 | 0.13212 | 5221.93ms | 1225964 | 160 | 1.88812e+08 | 822215 | 1.54203 | 2(Loss) |
| jsonifier | 1230.71 | 0.1202 | 6043.98ms | 1225964 | 160 | 2.08628e+08 | 949997 | 1.7817 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1868.42 | 0.0913581 | 8029.8ms | 1225964 | 320 | 1.0458e+08 | 625752 | 1.17358 | 1(Win) |
| glaze | 1156.93 | 0.0791892 | 6404.11ms | 1225970 | 320 | 2.0494e+08 | 1.01058e+06 | 1.89541 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1000.66 | 0.0676622 | 10040.6ms | 409725 | 1280 | 8.93532e+07 | 390485 | 2.1917 | 1(Win) |
| glaze | 774.384 | 0.189804 | 6462.14ms | 409725 | 160 | 1.46758e+08 | 504587 | 2.8322 | 2(Loss) |
| simdjson (ondemand) | 737.432 | 0.151601 | 6788.51ms | 409725 | 320 | 2.0649e+08 | 529872 | 2.9735 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4595.14 | 0.106791 | 8879.21ms | 409725 | 4890 | 4.03244e+07 | 85034.3 | 0.477117 | 1(Win) |
| glaze | 2335.12 | 0.184115 | 8821.33ms | 409725 | 2560 | 2.42989e+08 | 167334 | 0.938982 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1338.87 | 0.111177 | 7143.15ms | 785750 | 640 | 2.47801e+08 | 559689 | 1.6377 | 1(Win) |
| jsonifier | 1250.7 | 0.0848677 | 7686.65ms | 785750 | 640 | 1.65474e+08 | 599146 | 1.75338 | 2(Loss) |
| glaze | 1190.37 | 0.0907674 | 8026.4ms | 785750 | 640 | 2.08951e+08 | 629510 | 1.8422 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8132.9 | 0.154474 | 9603.41ms | 785750 | 2560 | 5.18593e+07 | 92138 | 0.269574 | 1(Win) |
| glaze | 2629.79 | 0.260718 | 7357.28ms | 785750 | 1280 | 7.06442e+08 | 284946 | 0.833571 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5089 | 0.180588 | 5333.29ms | 264040 | 2560 | 2.04406e+07 | 49480.9 | 0.430672 | 1(Win) |
| jsonifier | 4629.28 | 0.120311 | 5830.12ms | 264040 | 4890 | 2.09426e+07 | 54394.7 | 0.47346 | 2(Loss) |
| glaze | 2332.26 | 0.104577 | 5715.85ms | 264040 | 2560 | 3.26359e+07 | 107967 | 0.940143 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 6537.24 | 0.248566 | 6210.51ms | 399947 | 1280 | 2.69222e+07 | 58345.6 | 0.335308 | 1(Win) |
| jsonifier | 6198.47 | 0.122848 | 6531.35ms | 399947 | 4890 | 2.79437e+07 | 61534.4 | 0.353647 | 2(Loss) |
| glaze | 3036.77 | 0.20909 | 6592.06ms | 399947 | 640 | 4.41396e+07 | 125600 | 0.722074 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1384.27 | 0.181853 | 9513.53ms | 264040 | 640 | 7.0036e+07 | 181907 | 1.58407 | 1(Win) |
| simdjson (ondemand) | 1330.21 | 0.123993 | 9878.6ms | 264040 | 1280 | 7.05189e+07 | 189300 | 1.64852 | 2(Loss) |
| glaze | 1208.41 | 0.109718 | 5405.05ms | 264040 | 1280 | 6.69081e+07 | 208380 | 1.81471 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8688.15 | 0.235939 | 3276.92ms | 264040 | 4890 | 2.28663e+07 | 28983 | 0.252062 | 1(Win) |
| glaze | 4180.48 | 0.360187 | 6398.91ms | 263923 | 1280 | 6.01962e+07 | 60207.5 | 0.524297 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1927.99 | 0.0910431 | 5162.36ms | 399947 | 1280 | 4.15241e+07 | 197833 | 1.1374 | 1(Win) |
| glaze | 1480.58 | 0.20137 | 6634.44ms | 399947 | 320 | 8.61154e+07 | 257614 | 1.48118 | 2(Loss) |
| jsonifier | 1320.26 | 0.152399 | 7446.37ms | 399947 | 640 | 1.24059e+08 | 288896 | 1.66105 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12311.2 | 0.604434 | 3511.13ms | 399947 | 640 | 2.2443e+07 | 30981.5 | 0.177939 | 1(Win) |
| glaze | 3258.69 | 0.232374 | 6155.98ms | 399830 | 2560 | 1.89269e+08 | 117012 | 0.672742 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 781.585 | 0.278478 | 979.444ms | 4630 | 30 | 7425.29 | 5649.43 | 2.7909 | 1(Win) |
| glaze | 541.875 | 0.764306 | 1220.91ms | 4630 | 320 | 1.24122e+06 | 8148.58 | 4.03219 | 2(Loss) |
| simdjson (ondemand) | 523.5 | 0.207695 | 1271.61ms | 4630 | 40 | 12275.6 | 8434.6 | 4.17552 | 3(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 987.532 | 2.4936 | 846.604ms | 4630 | 4890 | 6.07888e+07 | 4471.26 | 2.19933 | 1(Win) |
| glaze | 643.792 | 0.0935993 | 1103.32ms | 4630 | 40 | 1648.45 | 6858.6 | 3.38316 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1843.19 | 0.678433 | 1177.87ms | 14795 | 320 | 863086 | 7654.99 | 1.18477 | 1(Win) |
| simdjson (ondemand) | 1480 | 0.616815 | 1358.84ms | 14795 | 80 | 276637 | 9533.55 | 1.4772 | 2(Loss) |
| glaze | 1258.17 | 0.137724 | 1540.29ms | 14795 | 30 | 7156.39 | 11214.4 | 1.73708 | 3(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3845.31 | 0.151518 | 795.183ms | 14795 | 80 | 2472.77 | 3669.3 | 0.565777 | 1(Win) |
| glaze | 2317.95 | 0.212069 | 1044.47ms | 14795 | 80 | 13331.1 | 6087.11 | 0.94096 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1047.4 | 0.353223 | 873.535ms | 5092 | 2560 | 686582 | 4636.36 | 2.08042 | 1(Win) |
| glaze | 904.687 | 0.378091 | 956.342ms | 5092 | 320 | 131803 | 5367.72 | 2.41003 | 2(Loss) |
| simdjson (ondemand) | 830.079 | 0.36932 | 1021.31ms | 5092 | 40 | 18672.5 | 5850.18 | 2.62829 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4864.07 | 0.272085 | 515.786ms | 5092 | 640 | 4722.44 | 998.364 | 0.437664 | 1(Win) |
| glaze | 2220.75 | 0.702164 | 637.071ms | 5092 | 640 | 150881 | 2186.7 | 0.96823 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1743 | 0.581317 | 1068.98ms | 11724 | 40 | 55621.4 | 6414.73 | 1.25226 | 1(Win) |
| jsonifier | 1605.08 | 0.838298 | 1113.29ms | 11724 | 640 | 2.18242e+06 | 6965.95 | 1.36035 | 2(Loss) |
| glaze | 1523.89 | 0.118627 | 1165.79ms | 11724 | 80 | 6060.4 | 7337.07 | 1.43333 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10624.8 | 0.869485 | 528.229ms | 11724 | 30 | 2511.61 | 1052.33 | 0.200785 | 1(Win) |
| glaze | 2967.09 | 0.875097 | 805.397ms | 11746 | 80 | 87321.1 | 3775.36 | 0.731238 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1103.78 | 0.379082 | 837.434ms | 4857 | 30 | 7592.12 | 4196.5 | 1.97273 | 1(Win) |
| jsonifier | 1046.71 | 2.12334 | 854.253ms | 4857 | 160 | 1.41268e+06 | 4425.29 | 2.08084 | 2(Loss) |
| simdjson (ondemand) | 957.39 | 0.587916 | 902.728ms | 4857 | 1280 | 1.03562e+06 | 4838.15 | 2.27612 | 3(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4524.98 | 0.519846 | 519.021ms | 4857 | 40 | 1132.69 | 1023.65 | 0.471587 | 1(Win) |
| glaze | 2308.68 | 0.885727 | 619.807ms | 4857 | 1280 | 404221 | 2006.34 | 0.931307 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1445.38 | 0.455842 | 903.253ms | 7376 | 1280 | 629964 | 4866.75 | 1.50558 | 1(Tie) |
| glaze STATISTICAL TIE | 1443.58 | 0.143166 | 910.681ms | 7376 | 160 | 7786.81 | 4872.81 | 1.5097 | 1(Tie) |
| jsonifier | 1114.14 | 0.0750179 | 1060.77ms | 7376 | 80 | 1794.67 | 6313.69 | 1.95846 | 3(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6821.64 | 0.61019 | 520.173ms | 7376 | 40 | 1583.64 | 1031.17 | 0.312771 | 1(Win) |
| glaze | 2017.45 | 0.657294 | 762.119ms | 7376 | 1280 | 672306 | 3486.74 | 1.07437 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1209.44 | 0.352794 | 761.748ms | 4390 | 30 | 4474.31 | 3461.63 | 1.79845 | 1(Win) |
| glaze | 1124.28 | 0.385269 | 796.82ms | 4390 | 320 | 65865.4 | 3723.82 | 1.93467 | 2(Loss) |
| simdjson (ondemand) | 964.024 | 0.744648 | 849.911ms | 4390 | 640 | 669322 | 4342.87 | 2.25943 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4932.41 | 0.277901 | 496.094ms | 4390 | 80 | 445.124 | 848.8 | 0.429869 | 1(Win) |
| glaze | 2193.41 | 0.826504 | 609.134ms | 4390 | 640 | 159280 | 1908.73 | 0.983732 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2356.38 | 0.730744 | 892.809ms | 11521 | 160 | 185756 | 4662.79 | 0.924768 | 1(Win) |
| jsonifier | 2049.14 | 0.367874 | 955.413ms | 11521 | 30 | 11672.3 | 5361.9 | 1.06437 | 2(Loss) |
| glaze | 1720.96 | 0.296449 | 1059.65ms | 11521 | 30 | 10746.4 | 6384.4 | 1.26844 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11748.5 | 0.609802 | 509.015ms | 11521 | 160 | 5203.7 | 935.206 | 0.18081 | 1(Win) |
| glaze | 2911.47 | 1.30032 | 789.135ms | 11521 | 160 | 385283 | 3773.79 | 0.746653 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1688.14 | 0.235902 | 678.439ms | 4669 | 30 | 1161.48 | 2637.63 | 1.28566 | 1(Win) |
| glaze | 1472.98 | 0.161654 | 719.123ms | 4669 | 160 | 3820.72 | 3022.92 | 1.47472 | 2(Loss) |
| simdjson (ondemand) | 1220.99 | 0.652922 | 787.684ms | 4669 | 80 | 45356.2 | 3646.8 | 1.78115 | 3(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8844.68 | 0.530923 | 464.825ms | 4669 | 30 | 214.323 | 503.433 | 0.23414 | 1(Win) |
| glaze | 2351.46 | 0.197417 | 604.178ms | 4669 | 320 | 4471.92 | 1893.59 | 0.907241 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2275.61 | 0.815385 | 815.869ms | 9249 | 160 | 159824 | 3876.12 | 0.956034 | 1(Win) |
| glaze | 1844.26 | 0.470906 | 890.183ms | 9249 | 160 | 81158.2 | 4782.69 | 1.18185 | 2(Loss) |
| jsonifier | 1778.26 | 0.0710805 | 916.501ms | 9249 | 80 | 994.466 | 4960.2 | 1.22556 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14224.6 | 0.61787 | 484.236ms | 9249 | 320 | 4697.37 | 620.091 | 0.147066 | 1(Win) |
| glaze | 2334.43 | 0.439187 | 790.931ms | 9249 | 2560 | 704961 | 3778.45 | 0.92787 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 626.082 | 0.172903 | 1132.71ms | 4604 | 30 | 4410.97 | 7013 | 3.48774 | 1(Win) |
| glaze | 439.184 | 0.225721 | 1430.41ms | 4604 | 30 | 15277.1 | 9997.43 | 4.97884 | 2(Loss) |
| simdjson (ondemand) | 412.167 | 0.435423 | 1480.57ms | 4604 | 30 | 64546 | 10652.8 | 5.30615 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 848.724 | 0.310407 | 935.37ms | 4604 | 320 | 82518.2 | 5173.32 | 2.56072 | 1(Win) |
| glaze | 553.112 | 0.116013 | 1224.73ms | 4604 | 30 | 2544.37 | 7938.2 | 3.94651 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2052.21 | 0.0756242 | 1574.8ms | 24579 | 30 | 2238.34 | 11422 | 1.06571 | 1(Win) |
| simdjson (ondemand) | 1935.52 | 0.391687 | 1619.6ms | 24579 | 30 | 67504.5 | 12110.6 | 1.1302 | 2(Loss) |
| glaze | 1572.51 | 0.176352 | 1939.34ms | 24579 | 40 | 27641.6 | 14906.3 | 1.3919 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4606.4 | 0.531885 | 929.006ms | 24579 | 640 | 468836 | 5088.65 | 0.472941 | 1(Win) |
| glaze | 2256.32 | 1.77733 | 1408.81ms | 24579 | 4890 | 1.66714e+08 | 10388.7 | 0.968574 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 690.979 | 0.102944 | 1061.66ms | 4604 | 160 | 6846.39 | 6354.34 | 3.15736 | 1(Win) |
| glaze | 441.365 | 0.141585 | 1425.29ms | 4604 | 80 | 15870.9 | 9948.05 | 4.95404 | 2(Loss) |
| simdjson (ondemand) | 415.003 | 0.368729 | 1482.25ms | 4604 | 640 | 974007 | 10580 | 5.2693 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 837.332 | 0.501546 | 937.7ms | 4604 | 30 | 20750 | 5243.7 | 2.60568 | 1(Win) |
| glaze | 549.587 | 0.560714 | 1246.34ms | 4604 | 320 | 642140 | 7989.12 | 3.97358 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2150.94 | 0.0927201 | 1514.5ms | 24579 | 30 | 3062.96 | 10897.7 | 1.01624 | 1(Win) |
| simdjson (ondemand) | 1989.85 | 0.46416 | 1621.38ms | 24579 | 160 | 478347 | 11780 | 1.09913 | 2(Loss) |
| glaze | 1561.14 | 0.103443 | 1945.63ms | 24579 | 80 | 19299.2 | 15014.9 | 1.40218 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4706.5 | 0.151403 | 925.773ms | 24579 | 160 | 9097.45 | 4980.43 | 0.462637 | 1(Win) |
| glaze | 2413.45 | 0.736294 | 1402.48ms | 24579 | 80 | 409113 | 9712.38 | 0.905562 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 734.492 | 0.455472 | 564.296ms | 1181 | 2560 | 124879 | 1533.43 | 2.93205 | 1(Win) |
| glaze | 582.324 | 0.246427 | 606.588ms | 1181 | 640 | 14538.7 | 1934.13 | 3.71226 | 2(Loss) |
| simdjson (ondemand) | 510.982 | 0.397945 | 634.662ms | 1181 | 2560 | 196959 | 2204.17 | 4.23639 | 3(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 849.917 | 0.124404 | 545.852ms | 1181 | 40 | 108.712 | 1325.17 | 2.50322 | 1(Win) |
| glaze | 639.118 | 0.07713 | 591.062ms | 1181 | 160 | 295.601 | 1762.26 | 3.34988 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1053.49 | 0.206695 | 667.471ms | 2496 | 80 | 1744.94 | 2259.51 | 2.05645 | 1(Win) |
| simdjson (ondemand) | 1034.46 | 0.483704 | 644.135ms | 2496 | 1280 | 158573 | 2301.07 | 2.0939 | 2(Loss) |
| glaze | 1009.42 | 0.249936 | 647.385ms | 2496 | 30 | 1042.14 | 2358.17 | 2.1473 | 3(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2022.14 | 0.203448 | 533.925ms | 2496 | 160 | 917.692 | 1177.16 | 1.05757 | 1(Win) |
| glaze | 1068.89 | 0.172921 | 643.357ms | 2507 | 320 | 4787.33 | 2236.78 | 1.99648 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1147.12 | 0.412623 | 829.435ms | 4926 | 30 | 8566.42 | 4095.3 | 1.89823 | 1(Win) |
| glaze | 815.725 | 0.303679 | 1001.56ms | 4926 | 40 | 12234.7 | 5759.05 | 2.67434 | 2(Loss) |
| simdjson (ondemand) | 724.137 | 0.158925 | 1052.54ms | 4926 | 80 | 8503.97 | 6487.45 | 3.01469 | 3(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4100.53 | 0.481688 | 532.875ms | 4926 | 640 | 19490.4 | 1145.66 | 0.52134 | 1(Win) |
| glaze | 2094.8 | 1.52837 | 633.865ms | 4926 | 80 | 93983.1 | 2242.6 | 1.03343 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1354.89 | 0.202563 | 1081.39ms | 9463 | 30 | 5461.22 | 6660.77 | 1.61169 | 1(Win) |
| simdjson (ondemand) | 1333.15 | 0.422728 | 1090.92ms | 9463 | 320 | 262043 | 6769.4 | 1.63755 | 2(Loss) |
| glaze | 1219.42 | 0.193754 | 1166.06ms | 9463 | 80 | 16449.2 | 7400.75 | 1.79035 | 3(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7460.06 | 0.662135 | 548.15ms | 9463 | 40 | 2566.41 | 1209.72 | 0.286727 | 1(Win) |
| glaze | 2679.03 | 0.734219 | 756.077ms | 9463 | 160 | 97875.4 | 3368.61 | 0.810618 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3752.71 | 2.9359 | 474.266ms | 2821 | 80 | 35439.6 | 716.9 | 0.562114 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3526.78 | 1.75182 | 497.389ms | 2821 | 40 | 7143.12 | 762.825 | 0.59922 | 1(Tie) |
| glaze | 2196.11 | 0.672409 | 530.885ms | 2821 | 160 | 10856.4 | 1225.04 | 0.97157 | 3(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5932.37 | 0.303102 | 484.465ms | 4147 | 160 | 653.294 | 666.663 | 0.354485 | 1(Win) |
| jsonifier | 4447.35 | 0.538286 | 502.15ms | 4147 | 4890 | 112047 | 889.268 | 0.477624 | 2(Loss) |
| glaze | 2912.66 | 0.335135 | 548.647ms | 4147 | 80 | 1656.6 | 1357.83 | 0.737756 | 3(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1580.05 | 0.399622 | 594.731ms | 2821 | 40 | 1851.92 | 1702.67 | 1.36546 | 1(Tie) |
| glaze STATISTICAL TIE | 1570.71 | 0.245613 | 587.042ms | 2821 | 40 | 707.908 | 1712.8 | 1.37386 | 1(Tie) |
| jsonifier | 1506.71 | 0.827021 | 589.476ms | 2821 | 2560 | 558240 | 1785.56 | 1.43183 | 3(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4543.2 | 0.275621 | 473.219ms | 2821 | 160 | 426.212 | 592.163 | 0.459801 | 1(Win) |
| glaze | 2484.81 | 1.04024 | 520.841ms | 2819 | 1280 | 162135 | 1081.94 | 0.846677 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2285.5 | 0.295335 | 598.148ms | 4147 | 40 | 1044.71 | 1730.42 | 0.942766 | 1(Win) |
| glaze | 1951.84 | 0.257725 | 618.656ms | 4147 | 30 | 818.116 | 2026.23 | 1.10837 | 2(Loss) |
| jsonifier | 1356.71 | 0.587993 | 707.054ms | 4147 | 1280 | 376052 | 2915.05 | 1.60022 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6521.64 | 0.506267 | 476.14ms | 4147 | 320 | 3016.23 | 606.425 | 0.320806 | 1(Win) |
| glaze | 1976.7 | 1.17787 | 620.932ms | 4145 | 320 | 177548 | 1999.79 | 1.08888 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2535.49 | 0.15524 | 9142.15ms | 466906 | 640 | 4.75688e+07 | 175618 | 0.864905 | 1(Win) |
| glaze | 1796.48 | 0.105444 | 6393.52ms | 466906 | 640 | 4.37154e+07 | 247860 | 1.22076 | 2(Loss) |
| simdjson (ondemand) | 918.844 | 0.112146 | 6215ms | 466906 | 320 | 9.45132e+07 | 484605 | 2.38607 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3057.71 | 0.140846 | 5706.93ms | 699405 | 640 | 6.04137e+07 | 218138 | 0.717201 | 1(Win) |
| glaze | 2725.93 | 0.10839 | 6350.58ms | 699405 | 640 | 4.50179e+07 | 244689 | 0.804531 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3593.51 | 0.115105 | 8760.17ms | 631514 | 1280 | 4.76351e+07 | 167596 | 0.610179 | 1(Win) |
| glaze | 1800.66 | 0.222001 | 8686.59ms | 631514 | 80 | 4.41063e+07 | 334465 | 1.21798 | 2(Loss) |
