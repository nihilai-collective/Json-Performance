# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [e2490ce](https://github.com/nihilai-collective/jsonifier/commit/e2490ce)  
| Glaze: [2518e75](https://github.com/stephenberry/glaze/commit/2518e75)  
| Simdjson: [9572dd0](https://github.com/simdjson/simdjson/commit/9572dd0)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 658.655 | 0.134641 | 2.66268ms | 1811 | 30 | 373.937 | 2622.17 | 3.49177 | 1(Win) |
| glaze | 463.59 | 0.125958 | 1.12695ms | 1811 | 30 | 660.603 | 3725.5 | 4.97843 | 2(Loss) |
| simdjson (ondemand) | 136.655 | 2.18565 | 3.30774ms | 1811 | 30 | 2.28913e+06 | 12638.4 | 17.0174 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 397.178 | 0.103062 | 2.87856ms | 1811 | 32 | 642.706 | 4348.44 | 5.82356 | 1(Win) |
| glaze | 275.65 | 0.248489 | 1.80443ms | 1798 | 30 | 7168.04 | 6220.6 | 8.41092 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1330.59 | 0.102496 | 0.965968ms | 3873 | 30 | 242.852 | 2775.9 | 1.7305 | 1(Win) |
| glaze | 1112.35 | 0.101546 | 1.02965ms | 3873 | 30 | 341.085 | 3320.53 | 2.07256 | 2(Loss) |
| simdjson (ondemand) | 304.408 | 0.0677293 | 3.1607ms | 3873 | 30 | 2026.09 | 12133.7 | 7.63847 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1738 | 0.111769 | 1.66551ms | 3873 | 32 | 180.544 | 2125.19 | 1.31856 | 1(Win) |
| glaze | 1032.58 | 0.340983 | 1.14025ms | 3873 | 30 | 4463.07 | 3577.03 | 2.23682 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1242.69 | 0.0950946 | 1.10984ms | 3862 | 30 | 238.303 | 2963.8 | 1.8547 | 1(Win) |
| glaze | 944.322 | 0.0815921 | 2.59513ms | 3862 | 32 | 324.065 | 3900.25 | 2.44638 | 2(Loss) |
| simdjson (ondemand) | 302.897 | 0.0602529 | 3.21115ms | 3862 | 30 | 1610.32 | 12159.6 | 7.67775 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1648.28 | 0.109385 | 0.907769ms | 3862 | 30 | 179.224 | 2234.5 | 1.39227 | 1(Win) |
| glaze | 993.211 | 0.415884 | 1.13392ms | 3862 | 30 | 7135.24 | 3708.27 | 2.32539 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 768.909 | 0.109632 | 0.65573ms | 905 | 30 | 45.4299 | 1122.47 | 2.93632 | 1(Win) |
| glaze | 475.62 | 0.212274 | 0.630764ms | 905 | 30 | 445.137 | 1814.63 | 4.7961 | 2(Loss) |
| simdjson (ondemand) | 95.6062 | 0.0691305 | 2.48126ms | 905 | 30 | 1168.39 | 9027.4 | 24.2917 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 829.534 | 0.0894395 | 0.503076ms | 905 | 30 | 25.9782 | 1040.43 | 2.71348 | 1(Win) |
| glaze | 312.73 | 0.166806 | 1.92196ms | 905 | 32 | 678.157 | 2759.81 | 7.35846 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1673.23 | 0.0711355 | 1.6849ms | 9578 | 30 | 452.409 | 5459.07 | 1.38436 | 1(Win) |
| glaze | 1413 | 0.0855093 | 1.82194ms | 9578 | 30 | 916.671 | 6464.47 | 1.64058 | 2(Loss) |
| simdjson (ondemand) | 718.662 | 1.21582 | 32.0793ms | 9578 | 128 | 3.05665e+06 | 12710.1 | 3.23568 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3162.55 | 0.125043 | 0.944307ms | 9578 | 30 | 391.306 | 2888.27 | 0.728169 | 1(Win) |
| glaze | 2288.89 | 0.143774 | 1.22135ms | 9578 | 30 | 987.597 | 3990.7 | 1.00971 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2587.36 | 0.631501 | 21.3789ms | 233995 | 30 | 8.89957e+06 | 86248.2 | 0.900659 | 1(Win) |
| simdjson (ondemand) | 2486.24 | 0.868242 | 22.0422ms | 233995 | 30 | 1.82192e+07 | 89756.1 | 0.93741 | 2(Loss) |
| glaze | 1274.86 | 0.625621 | 42.3174ms | 233995 | 30 | 3.59778e+07 | 175043 | 1.82888 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3138.81 | 0.963887 | 25.5825ms | 346753 | 30 | 3.09373e+07 | 105355 | 0.742518 | 1(Win) |
| jsonifier | 2826.7 | 0.670833 | 28.5606ms | 346753 | 30 | 1.8477e+07 | 116988 | 0.824547 | 2(Loss) |
| glaze | 1586.78 | 0.716491 | 50.2771ms | 346753 | 30 | 6.68882e+07 | 208403 | 1.46936 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1028.81 | 1.11261 | 51.6525ms | 233995 | 30 | 1.74722e+08 | 216905 | 2.26615 | 1(Win) |
| glaze | 926.003 | 0.632724 | 59.3687ms | 233995 | 30 | 6.9749e+07 | 240987 | 2.51783 | 2(Loss) |
| simdjson (ondemand) | 869.869 | 0.550253 | 62.0741ms | 233995 | 30 | 5.97793e+07 | 256539 | 2.68037 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2114.82 | 0.793335 | 25.836ms | 233995 | 30 | 2.10233e+07 | 105520 | 1.10215 | 1(Win) |
| glaze | 1870.37 | 0.7488 | 29.0474ms | 233995 | 30 | 2.39449e+07 | 119311 | 1.24628 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1224.76 | 0.554933 | 65.6474ms | 346753 | 30 | 6.73507e+07 | 270004 | 1.9036 | 1(Win) |
| glaze | 1146.61 | 0.479158 | 70.0148ms | 346753 | 30 | 5.72917e+07 | 288407 | 2.03355 | 2(Loss) |
| jsonifier | 902.369 | 0.315281 | 89.7283ms | 346753 | 30 | 4.00488e+07 | 366468 | 2.58399 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2227.1 | 0.558846 | 36.3596ms | 346753 | 30 | 2.06571e+07 | 148485 | 1.04666 | 1(Win) |
| glaze | 1734.34 | 0.747016 | 45.9965ms | 346753 | 30 | 6.08631e+07 | 190672 | 1.34421 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2523.15 | 0.904752 | 21.6627ms | 233995 | 30 | 1.92091e+07 | 88442.9 | 0.923555 | 1(Win) |
| simdjson (ondemand) | 1662.5 | 1.04921 | 32.3943ms | 233995 | 30 | 5.95025e+07 | 134229 | 1.40172 | 2(Loss) |
| glaze | 1281.45 | 0.516692 | 42.057ms | 233995 | 30 | 2.42881e+07 | 174142 | 1.81946 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2741.17 | 1.03176 | 29.1126ms | 346753 | 30 | 4.64779e+07 | 120638 | 0.850346 | 1(Win) |
| simdjson (ondemand) | 2216.54 | 0.810459 | 35.9805ms | 346753 | 30 | 4.38602e+07 | 149191 | 1.05178 | 2(Loss) |
| glaze | 1586.29 | 0.546815 | 50.4103ms | 346753 | 30 | 3.89832e+07 | 208467 | 1.46982 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1000.66 | 1.09785 | 53.2338ms | 233995 | 30 | 1.79825e+08 | 223007 | 2.3301 | 1(Win) |
| jsonifier | 962.582 | 0.576984 | 56.6542ms | 233995 | 30 | 5.36769e+07 | 231830 | 2.42219 | 2(Loss) |
| simdjson (ondemand) | 167.259 | 0.20317 | 320.125ms | 233995 | 30 | 2.20433e+08 | 1.33419e+06 | 13.9424 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2213.82 | 1.0183 | 24.9182ms | 233995 | 30 | 3.16087e+07 | 100801 | 1.05272 | 1(Win) |
| glaze | 1808.24 | 0.945576 | 29.903ms | 233995 | 30 | 4.08524e+07 | 123410 | 1.28902 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1180.19 | 0.55537 | 67.6714ms | 346753 | 30 | 7.2648e+07 | 280200 | 1.97567 | 1(Win) |
| jsonifier | 941.247 | 0.324616 | 85.3351ms | 346753 | 30 | 3.90207e+07 | 351331 | 2.47726 | 2(Loss) |
| simdjson (ondemand) | 267.417 | 0.214524 | 298.022ms | 346753 | 30 | 2.11123e+08 | 1.23661e+06 | 8.72043 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2500.25 | 0.987809 | 32.3743ms | 346753 | 30 | 5.12083e+07 | 132262 | 0.932245 | 1(Win) |
| glaze | 1666.47 | 0.782193 | 48.2106ms | 346753 | 30 | 7.22757e+07 | 198437 | 1.39902 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 677.057 | 0.842689 | 32.4697ms | 94651 | 30 | 3.78665e+07 | 133321 | 3.44341 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 672.129 | 0.842754 | 32.5625ms | 94651 | 30 | 3.84298e+07 | 134299 | 3.46853 | 1(Tie) |
| jsonifier | 634.103 | 0.56707 | 34.6029ms | 94651 | 30 | 1.9549e+07 | 142353 | 3.67683 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2764.06 | 1.10414 | 8.36312ms | 94651 | 30 | 3.90055e+06 | 32657.1 | 0.842421 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2683.59 | 1.31984 | 8.22066ms | 94651 | 30 | 5.91259e+06 | 33636.3 | 0.868081 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 931.267 | 0.789518 | 33.7663ms | 136024 | 30 | 3.62851e+07 | 139297 | 2.50341 | 1(Win) |
| glaze | 826.351 | 0.484267 | 38.3515ms | 136024 | 30 | 1.73378e+07 | 156982 | 2.82132 | 2(Loss) |
| jsonifier | 715.107 | 0.569795 | 43.8609ms | 136024 | 30 | 3.20514e+07 | 181403 | 3.26037 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3361.92 | 1.10296 | 22.0843ms | 136024 | 32 | 5.79595e+06 | 38585.8 | 0.692943 | 1(Win) |
| glaze | 1681.78 | 1.1035 | 18.8124ms | 136046 | 30 | 2.17422e+07 | 77146.6 | 1.38578 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 443.354 | 0.255597 | 1077.85ms | 2090234 | 30 | 3.96208e+09 | 4.49619e+06 | 5.26011 | 1(Win) |
| simdjson (ondemand) | 357.295 | 0.10975 | 1339.8ms | 2090234 | 30 | 1.12477e+09 | 5.57915e+06 | 6.5271 | 2(Loss) |
| glaze | 344.795 | 1.549 | 1363.86ms | 2090234 | 30 | 2.40597e+11 | 5.78141e+06 | 6.76376 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 914.422 | 0.124829 | 525.609ms | 2090234 | 30 | 2.22153e+08 | 2.17996e+06 | 2.55027 | 1(Win) |
| glaze | 741.344 | 0.118974 | 646.216ms | 2090234 | 30 | 3.07027e+08 | 2.6889e+06 | 3.14572 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1060.93 | 0.104383 | 1439.57ms | 6661897 | 30 | 1.17222e+09 | 5.98842e+06 | 2.19818 | 1(Win) |
| jsonifier | 931.257 | 0.188808 | 1647.27ms | 6661897 | 30 | 4.9776e+09 | 6.82227e+06 | 2.50426 | 2(Loss) |
| glaze | 896.626 | 0.137742 | 1693.53ms | 6661897 | 30 | 2.85779e+09 | 7.08576e+06 | 2.60097 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2101.25 | 0.19417 | 737.908ms | 6661897 | 30 | 1.03401e+09 | 3.02357e+06 | 1.10984 | 1(Win) |
| glaze | 1617.07 | 0.235765 | 954.562ms | 6661897 | 30 | 2.57407e+09 | 3.92889e+06 | 1.44216 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 913.96 | 0.39306 | 126.358ms | 500299 | 30 | 1.26312e+08 | 522039 | 2.55138 | 1(Win) |
| jsonifier | 829.469 | 0.175626 | 139.013ms | 500299 | 30 | 3.06167e+07 | 575214 | 2.81135 | 2(Loss) |
| simdjson (ondemand) | 601.242 | 0.214345 | 191.268ms | 500299 | 30 | 8.67982e+07 | 793561 | 3.87852 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1873.31 | 0.394087 | 62.3746ms | 500299 | 30 | 3.02235e+07 | 254695 | 1.24464 | 1(Win) |
| jsonifier | 1791.11 | 0.647785 | 63.8709ms | 500299 | 30 | 8.93304e+07 | 266384 | 1.30176 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1538.46 | 0.320605 | 214.447ms | 1439562 | 30 | 2.45557e+08 | 892371 | 1.51576 | 1(Win) |
| glaze | 1466.3 | 0.170103 | 225.474ms | 1439562 | 30 | 7.60954e+07 | 936282 | 1.59038 | 2(Loss) |
| jsonifier | 1264.44 | 0.21908 | 260.49ms | 1439562 | 30 | 1.69743e+08 | 1.08576e+06 | 1.84426 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3290.36 | 0.7482 | 99.5738ms | 1439562 | 30 | 2.92368e+08 | 417241 | 0.708615 | 1(Win) |
| glaze | 1863.21 | 0.52693 | 177.869ms | 1439584 | 30 | 4.5225e+08 | 736845 | 1.25152 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 914.838 | 1.34911 | 14.7014ms | 56369 | 30 | 1.88541e+07 | 58761.9 | 2.5472 | 1(Win) |
| glaze | 825.484 | 1.70128 | 15.9917ms | 56369 | 30 | 3.68244e+07 | 65122.6 | 2.82344 | 2(Loss) |
| simdjson (ondemand) | 672.581 | 1.31779 | 19.6046ms | 56369 | 30 | 3.32816e+07 | 79927.4 | 3.46524 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1873.24 | 2.19344 | 7.17155ms | 56369 | 30 | 1.18868e+07 | 28697.6 | 1.2431 | 1(Win) |
| jsonifier | 1749.72 | 0.980228 | 7.72752ms | 56369 | 30 | 2.72095e+06 | 30723.6 | 1.33097 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1140.44 | 1.20619 | 19.488ms | 94370 | 30 | 2.71816e+07 | 78915.1 | 2.04373 | 1(Win) |
| simdjson (ondemand) | 1073.58 | 0.635394 | 20.7285ms | 94370 | 30 | 8.51151e+06 | 83830 | 2.17076 | 2(Loss) |
| jsonifier | 891.112 | 1.20382 | 24.8984ms | 94370 | 30 | 4.43455e+07 | 100995 | 2.61588 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2482.04 | 1.3519 | 8.97639ms | 94370 | 30 | 7.20882e+06 | 36259.8 | 0.938452 | 1(Win) |
| glaze | 1674.66 | 1.24094 | 13.2357ms | 94370 | 30 | 1.33424e+07 | 53741.1 | 1.39129 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 790.013 | 1.84126 | 15.4049ms | 52708 | 30 | 4.11754e+07 | 63627.1 | 2.9486 | 1(Win) |
| glaze | 719.1 | 1.26548 | 17.4462ms | 52708 | 30 | 2.3475e+07 | 69901.7 | 3.24025 | 2(Loss) |
| jsonifier | 639.488 | 2.10551 | 19.6879ms | 52708 | 30 | 8.21724e+07 | 78604 | 3.6408 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2951.8 | 0.16272 | 4.46927ms | 52708 | 30 | 23034.6 | 17029 | 0.788311 | 1(Win) |
| glaze | 2811.49 | 0.415395 | 10.622ms | 52708 | 32 | 176503 | 17878.8 | 0.827824 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1096.8 | 0.957568 | 15.482ms | 70103 | 30 | 1.02207e+07 | 60955.1 | 2.12423 | 1(Win) |
| glaze | 795.632 | 1.2521 | 20.7479ms | 70103 | 30 | 3.32087e+07 | 84028.1 | 2.92866 | 2(Loss) |
| jsonifier | 549.594 | 2.27299 | 29.8073ms | 70103 | 30 | 2.29354e+08 | 121645 | 4.23923 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3048.59 | 2.4886 | 26.7249ms | 70103 | 64 | 1.9062e+07 | 21930 | 0.763441 | 1(Win) |
| glaze | 2249.31 | 1.16078 | 7.5124ms | 70103 | 30 | 3.57105e+06 | 29722.6 | 1.03534 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 658.227 | 0.20956 | 4.56733ms | 11812 | 30 | 38586.4 | 17113.9 | 3.53555 | 1(Win) |
| jsonifier | 644.12 | 0.0439791 | 4.65773ms | 11812 | 30 | 1774.71 | 17488.7 | 3.61291 | 2(Loss) |
| simdjson (ondemand) | 567.996 | 1.5819 | 5.05678ms | 11812 | 30 | 2.95283e+06 | 19832.5 | 4.09806 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2344.65 | 0.0844715 | 1.38383ms | 11812 | 30 | 494.12 | 4804.47 | 0.987112 | 1(Win) |
| glaze | 1259.43 | 0.143888 | 2.4002ms | 11812 | 30 | 4969 | 8944.37 | 1.84392 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1359.38 | 1.48103 | 5.55867ms | 31235 | 30 | 3.15973e+06 | 21912.9 | 1.71268 | 1(Win) |
| glaze | 1142.4 | 0.219921 | 6.69583ms | 31235 | 30 | 98650.6 | 26074.9 | 2.03847 | 2(Loss) |
| jsonifier | 1015.52 | 2.06567 | 16.8461ms | 31235 | 32 | 1.17483e+07 | 29332.7 | 2.29339 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2920.83 | 0.139693 | 2.85418ms | 31235 | 30 | 6088.88 | 10198.5 | 0.795515 | 1(Win) |
| glaze | 1912.02 | 0.221538 | 4.02786ms | 31235 | 30 | 35736.9 | 15579.3 | 1.21683 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1677.08 | 0.927776 | 15.5125ms | 108313 | 30 | 9.79624e+06 | 61592.2 | 1.38924 | 1(Win) |
| glaze | 985.757 | 1.18191 | 25.7471ms | 108313 | 30 | 4.60167e+07 | 104788 | 2.3647 | 2(Loss) |
| simdjson (ondemand) | 851.43 | 0.760956 | 29.5742ms | 108313 | 30 | 2.55684e+07 | 121320 | 2.73784 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1944.33 | 0.903662 | 12.9169ms | 108313 | 30 | 6.91443e+06 | 53126.5 | 1.19864 | 1(Win) |
| glaze | 1684.76 | 1.44056 | 14.7571ms | 108313 | 30 | 2.34026e+07 | 61311.4 | 1.38316 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1536.04 | 1.16241 | 32.0843ms | 213963 | 30 | 7.15338e+07 | 132842 | 1.51766 | 1(Win) |
| glaze | 1279.81 | 0.991598 | 38.4364ms | 213963 | 30 | 7.49856e+07 | 159438 | 1.82165 | 2(Loss) |
| jsonifier | 1150.19 | 0.9318 | 43.2536ms | 213963 | 30 | 8.19796e+07 | 177406 | 2.02659 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3039.68 | 1.41184 | 16.419ms | 213963 | 30 | 2.69473e+07 | 67129 | 0.766643 | 1(Win) |
| glaze | 1560.13 | 0.996739 | 31.532ms | 213963 | 30 | 5.0985e+07 | 130791 | 1.49413 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 432.785 | 0.135265 | 973.335ms | 1834197 | 30 | 8.96692e+08 | 4.04179e+06 | 5.3884 | 1(Win) |
| glaze | 338.293 | 0.117021 | 1240.24ms | 1834197 | 30 | 1.09839e+09 | 5.17074e+06 | 6.89368 | 2(Loss) |
| simdjson (ondemand) | 287.847 | 0.0629743 | 1460.07ms | 1834197 | 30 | 4.39355e+08 | 6.07692e+06 | 8.10184 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 557.832 | 0.0845037 | 755.394ms | 1834197 | 30 | 2.10648e+08 | 3.13576e+06 | 4.18052 | 1(Win) |
| glaze | 355.462 | 0.0449364 | 1183.5ms | 1833577 | 30 | 1.46599e+08 | 4.91933e+06 | 6.56069 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1397.4 | 0.0805588 | 1631.16ms | 9930848 | 30 | 8.94289e+08 | 6.77743e+06 | 1.66888 | 1(Win) |
| glaze | 1304.37 | 0.120026 | 1745.25ms | 9930848 | 30 | 2.27846e+09 | 7.2608e+06 | 1.78789 | 2(Loss) |
| jsonifier | 1287.24 | 0.105099 | 1767.22ms | 9930848 | 30 | 1.79379e+09 | 7.35744e+06 | 1.81167 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2060.04 | 0.188266 | 1109.44ms | 9930848 | 30 | 2.24743e+09 | 4.59738e+06 | 1.13206 | 1(Win) |
| glaze | 1203.44 | 0.159633 | 1878.53ms | 9930228 | 30 | 4.73407e+09 | 7.86925e+06 | 1.93776 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 798.243 | 0.237182 | 184.082ms | 642697 | 30 | 9.95011e+07 | 767841 | 2.92131 | 1(Win) |
| glaze | 641.759 | 0.228964 | 229.262ms | 642697 | 30 | 1.43458e+08 | 955068 | 3.63372 | 2(Loss) |
| simdjson (ondemand) | 590.05 | 0.118832 | 250.155ms | 642697 | 30 | 4.57117e+07 | 1.03877e+06 | 3.95222 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 892.894 | 0.25098 | 165.626ms | 642697 | 30 | 8.90455e+07 | 686446 | 2.61167 | 1(Win) |
| glaze | 598.682 | 0.253532 | 245.395ms | 642692 | 30 | 2.02116e+08 | 1.02378e+06 | 3.8952 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1085.34 | 0.28225 | 259.049ms | 1225964 | 30 | 2.77339e+08 | 1.07723e+06 | 2.14863 | 1(Win) |
| glaze | 985.973 | 0.170124 | 285.887ms | 1225964 | 30 | 1.22089e+08 | 1.1858e+06 | 2.3651 | 2(Loss) |
| jsonifier | 845.627 | 0.223618 | 332.991ms | 1225964 | 30 | 2.8677e+08 | 1.38261e+06 | 2.7577 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1501.29 | 1.16771 | 187.929ms | 1225964 | 30 | 2.48093e+09 | 778776 | 1.55322 | 1(Win) |
| glaze | 969.474 | 0.187365 | 290.019ms | 1225970 | 30 | 1.53174e+08 | 1.20599e+06 | 2.40545 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 517.278 | 0.186688 | 182.906ms | 409725 | 30 | 5.96614e+07 | 755386 | 4.50812 | 1(Win) |
| simdjson (ondemand) | 509.551 | 0.617309 | 183.246ms | 409725 | 30 | 6.72259e+08 | 766841 | 4.57633 | 2(Loss) |
| glaze | 410.288 | 0.42361 | 229.531ms | 409725 | 30 | 4.8827e+08 | 952365 | 5.68374 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1385.72 | 0.48516 | 68.0835ms | 409725 | 30 | 5.61472e+07 | 281980 | 1.68262 | 1(Win) |
| jsonifier | 1359.47 | 0.448432 | 69.4376ms | 409725 | 30 | 4.98379e+07 | 287423 | 1.71515 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 936.898 | 0.185443 | 192.998ms | 785750 | 30 | 6.59972e+07 | 799820 | 2.48901 | 1(Win) |
| glaze | 670.587 | 0.351799 | 269.352ms | 785750 | 30 | 4.63629e+08 | 1.11745e+06 | 3.47756 | 2(Loss) |
| jsonifier | 654.704 | 0.173455 | 275.362ms | 785750 | 30 | 1.18243e+08 | 1.14456e+06 | 3.56192 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1988.59 | 0.51759 | 91.1314ms | 785750 | 30 | 1.14123e+08 | 376825 | 1.17258 | 1(Win) |
| glaze | 1490.77 | 0.393615 | 121.42ms | 785750 | 30 | 1.17439e+08 | 502660 | 1.5642 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 693.826 | 0.343873 | 2873.38ms | 8587914 | 30 | 4.943e+10 | 1.18042e+07 | 3.3612 | 1(Win) |
| jsonifier | 664.867 | 0.495666 | 2970.84ms | 8587914 | 30 | 1.11842e+11 | 1.23184e+07 | 3.50755 | 2(Loss) |
| glaze | 625.842 | 0.343617 | 3133.37ms | 8587914 | 30 | 6.06619e+10 | 1.30865e+07 | 3.72634 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2178.06 | 0.280441 | 914.835ms | 8588126 | 30 | 3.33626e+09 | 3.76035e+06 | 1.07066 | 1(Win) |
| glaze | 2135.36 | 0.247175 | 923.936ms | 8588126 | 30 | 2.6964e+09 | 3.83555e+06 | 1.09208 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 773.621 | 0.211221 | 2908.48ms | 9804437 | 30 | 1.95518e+10 | 1.20863e+07 | 3.01449 | 1(Win) |
| glaze | 667.396 | 0.295009 | 3353.72ms | 9804437 | 30 | 5.12472e+10 | 1.401e+07 | 3.49433 | 2(Loss) |
| jsonifier | 633.149 | 0.166837 | 3583.6ms | 9804437 | 30 | 1.82113e+10 | 1.47678e+07 | 3.68334 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2455.73 | 0.218762 | 1041.9ms | 11078090 | 30 | 2.65724e+09 | 4.30213e+06 | 0.949585 | 1(Win) |
| glaze | 1858.93 | 0.246134 | 1370.33ms | 11078090 | 30 | 5.87044e+09 | 5.68332e+06 | 1.25446 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2570.8 | 1.0121 | 23.5922ms | 264040 | 30 | 2.94826e+07 | 97949.2 | 0.906443 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2507.08 | 2.40187 | 24.2401ms | 264040 | 30 | 1.74592e+08 | 100439 | 0.929597 | 1(Tie) |
| glaze | 1034.02 | 0.48465 | 59.0471ms | 264040 | 30 | 4.17891e+07 | 243524 | 2.25491 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3452.22 | 0.502314 | 27.1322ms | 399947 | 30 | 9.24018e+06 | 110485 | 0.675146 | 1(Win) |
| jsonifier | 2896.24 | 0.792634 | 32.1038ms | 399947 | 30 | 3.26891e+07 | 131695 | 0.804824 | 2(Loss) |
| glaze | 1303.18 | 0.542586 | 70.6941ms | 399947 | 30 | 7.56579e+07 | 292683 | 1.78901 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 899.046 | 0.55654 | 68.5204ms | 264040 | 30 | 7.28935e+07 | 280084 | 2.59346 | 1(Tie) |
| jsonifier STATISTICAL TIE | 882.054 | 1.02091 | 69.2515ms | 264040 | 30 | 2.54827e+08 | 285479 | 2.64279 | 1(Tie) |
| glaze | 798.134 | 0.520582 | 76.6633ms | 264040 | 30 | 8.0926e+07 | 315496 | 2.92135 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2345.95 | 0.701382 | 26.4515ms | 263923 | 30 | 1.69882e+07 | 107290 | 0.993601 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2296.76 | 0.835551 | 26.8217ms | 264040 | 30 | 2.51754e+07 | 109636 | 1.01486 | 1(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1202.46 | 1.24246 | 75.5531ms | 399947 | 30 | 4.65956e+08 | 317198 | 1.93907 | 1(Win) |
| glaze | 968.856 | 0.448081 | 95.4181ms | 399947 | 30 | 9.33516e+07 | 393680 | 2.40671 | 2(Loss) |
| jsonifier | 731.142 | 0.729417 | 126.405ms | 399947 | 30 | 4.34384e+08 | 521676 | 3.18895 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3117.2 | 0.790389 | 30.1243ms | 399947 | 30 | 2.80594e+07 | 122359 | 0.747712 | 1(Win) |
| glaze | 2062.24 | 0.60801 | 47.3686ms | 399830 | 30 | 3.79153e+07 | 184900 | 1.13046 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1387.68 | 0.515448 | 77.2476ms | 466906 | 30 | 8.20678e+07 | 320879 | 1.68027 | 1(Tie) |
| glaze STATISTICAL TIE | 1359.93 | 0.912369 | 78.1095ms | 466906 | 30 | 2.67726e+08 | 327427 | 1.71461 | 1(Tie) |
| simdjson (ondemand) | 662.744 | 0.562696 | 376.58ms | 466906 | 32 | 4.57368e+08 | 671868 | 3.51845 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2096.3 | 0.407685 | 77.7286ms | 699405 | 30 | 5.04803e+07 | 318182 | 1.11224 | 1(Win) |
| glaze | 1684.99 | 0.29599 | 95.576ms | 699405 | 30 | 4.1185e+07 | 395851 | 1.38387 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1663.87 | 0.387822 | 88.0741ms | 631514 | 30 | 5.91172e+07 | 361962 | 1.40141 | 1(Win) |
| glaze | 1543.76 | 0.348713 | 94.5538ms | 631514 | 30 | 5.55217e+07 | 390123 | 1.51048 | 2(Loss) |
