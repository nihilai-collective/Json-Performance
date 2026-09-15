# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [e2490ce](https://github.com/nihilai-collective/jsonifier/commit/e2490ce)  
| Glaze: [2518e75](https://github.com/stephenberry/glaze/commit/2518e75)  
| Simdjson: [9572dd0](https://github.com/simdjson/simdjson/commit/9572dd0)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (INTEL(R) XEON(R) PLATINUM 8573C-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 651.639 | 0.129817 | 2.67144ms | 1811 | 30 | 355.145 | 2650.4 | 3.30289 | 1(Win) |
| glaze | 604.002 | 0.172933 | 1.13339ms | 1811 | 30 | 733.564 | 2859.43 | 3.57003 | 2(Loss) |
| simdjson (ondemand) | 146.122 | 0.0755683 | 3.34537ms | 1811 | 30 | 2393.35 | 11819.6 | 14.9544 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 456.93 | 0.057144 | 1.85384ms | 1811 | 30 | 139.959 | 3779.8 | 4.73046 | 1(Win) |
| glaze | 273.818 | 2.22288 | 8.26373ms | 1798 | 64 | 1.24014e+06 | 6262.22 | 7.92017 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1311.08 | 0.147433 | 1.2933ms | 3873 | 30 | 517.545 | 2817.2 | 1.65376 | 1(Win) |
| glaze | 1118.31 | 0.0445567 | 1.24476ms | 3873 | 30 | 64.9713 | 3302.83 | 1.94099 | 2(Loss) |
| simdjson (ondemand) | 312.488 | 0.0376511 | 3.33188ms | 3873 | 30 | 594.162 | 11819.9 | 7.00015 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1748.67 | 0.212778 | 1.90073ms | 3873 | 32 | 646.37 | 2112.22 | 1.22202 | 1(Win) |
| glaze | 815.793 | 0.12236 | 3.15156ms | 3873 | 32 | 982.12 | 4527.59 | 2.66155 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1300.97 | 0.0894964 | 1.27937ms | 3862 | 30 | 192.585 | 2831.03 | 1.65864 | 1(Win) |
| glaze | 1070.34 | 0.0569492 | 1.27533ms | 3862 | 30 | 115.206 | 3441.03 | 2.02248 | 2(Loss) |
| simdjson (ondemand) | 292.858 | 2.02168 | 3.4802ms | 3862 | 30 | 1.93935e+06 | 12576.4 | 7.46948 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1782.63 | 0.0992821 | 1.06598ms | 3862 | 30 | 126.231 | 2066.1 | 1.1967 | 1(Win) |
| glaze | 810.284 | 0.10758 | 1.56038ms | 3862 | 30 | 717.357 | 4545.43 | 2.68367 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 724.056 | 0.121005 | 0.873391ms | 905 | 30 | 62.4138 | 1192 | 2.94608 | 1(Win) |
| glaze | 538.424 | 0.0249328 | 0.843137ms | 905 | 30 | 4.79195 | 1602.97 | 3.99131 | 2(Loss) |
| simdjson (ondemand) | 122.462 | 0.0656674 | 2.17825ms | 905 | 30 | 642.562 | 7047.7 | 17.7784 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 967.031 | 0.086748 | 0.753382ms | 905 | 30 | 17.9828 | 892.5 | 2.18785 | 1(Win) |
| glaze | 214.786 | 0.11348 | 1.46199ms | 905 | 30 | 623.803 | 4018.3 | 10.1084 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1907.18 | 0.111155 | 1.5928ms | 9578 | 30 | 850.254 | 4789.43 | 1.13849 | 1(Win) |
| jsonifier | 1863.85 | 0.0724812 | 1.84252ms | 9578 | 30 | 378.53 | 4900.77 | 1.16443 | 2(Loss) |
| simdjson (ondemand) | 803.184 | 0.439019 | 3.31518ms | 9578 | 30 | 74783.6 | 11372.6 | 2.72222 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3239.88 | 0.0885361 | 1.4715ms | 9578 | 30 | 186.92 | 2819.33 | 0.668783 | 1(Win) |
| glaze | 1943.96 | 0.145571 | 1.62273ms | 9578 | 30 | 1403.61 | 4698.8 | 1.11894 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3920.81 | 0.365856 | 14.4294ms | 233995 | 30 | 1.30077e+06 | 56915.5 | 0.558987 | 1(Win) |
| jsonifier | 3782.25 | 0.558809 | 14.9795ms | 233995 | 30 | 3.26108e+06 | 59000.6 | 0.579505 | 2(Loss) |
| glaze | 1351.88 | 0.682899 | 40.292ms | 233995 | 30 | 3.81219e+07 | 165071 | 1.62204 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 4995.34 | 0.464868 | 16.7341ms | 346753 | 30 | 2.84113e+06 | 66199.6 | 0.438786 | 1(Tie) |
| jsonifier STATISTICAL TIE | 4966.54 | 0.694856 | 16.7118ms | 346753 | 30 | 6.42161e+06 | 66583.5 | 0.441357 | 1(Tie) |
| glaze | 1707.04 | 0.65296 | 47.1163ms | 346753 | 30 | 4.80005e+07 | 193721 | 1.28457 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1295.05 | 0.317739 | 42.7293ms | 233995 | 30 | 8.99296e+06 | 172314 | 1.69324 | 1(Win) |
| glaze STATISTICAL TIE | 1058.67 | 0.513713 | 51.8458ms | 233995 | 30 | 3.51763e+07 | 210787 | 2.07137 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1043.98 | 0.527656 | 51.8508ms | 233995 | 30 | 3.81637e+07 | 213754 | 2.10048 | 2(Tie) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2778.02 | 0.381955 | 20.3604ms | 233995 | 30 | 2.82415e+06 | 80328.8 | 0.788674 | 1(Win) |
| glaze | 2438.91 | 0.546518 | 22.7308ms | 233995 | 30 | 7.50156e+06 | 91497.8 | 0.89884 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1460.82 | 0.439243 | 54.6198ms | 346753 | 30 | 2.96603e+07 | 226372 | 1.5011 | 1(Win) |
| jsonifier | 1410.39 | 1.08128 | 56.9119ms | 346753 | 30 | 1.92824e+08 | 234467 | 1.55484 | 2(Loss) |
| glaze | 1307.34 | 0.631217 | 61.037ms | 346753 | 30 | 7.6479e+07 | 252948 | 1.67741 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3291.59 | 0.357329 | 24.9265ms | 346753 | 30 | 3.86624e+06 | 100465 | 0.666004 | 1(Win) |
| glaze | 2440.87 | 0.373581 | 33.1772ms | 346753 | 30 | 7.68498e+06 | 135480 | 0.898114 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3687.13 | 0.534463 | 15.4584ms | 233995 | 30 | 3.139e+06 | 60522.6 | 0.594472 | 1(Win) |
| simdjson (ondemand) | 2467.13 | 0.689877 | 22.1484ms | 233995 | 30 | 1.16814e+07 | 90451.4 | 0.888622 | 2(Loss) |
| glaze | 1322.72 | 0.670026 | 40.7979ms | 233995 | 30 | 3.83338e+07 | 168709 | 1.6578 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4903.67 | 0.52314 | 17.0762ms | 346753 | 30 | 3.73384e+06 | 67437.1 | 0.447032 | 1(Win) |
| simdjson (ondemand) | 3283.81 | 0.598762 | 24.5083ms | 346753 | 30 | 1.09072e+07 | 100703 | 0.667663 | 2(Loss) |
| glaze | 1698.51 | 0.416369 | 47.3053ms | 346753 | 30 | 1.97144e+07 | 194694 | 1.29106 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1206.97 | 0.429166 | 45.3634ms | 233995 | 30 | 1.88882e+07 | 184888 | 1.81673 | 1(Win) |
| glaze | 1133.42 | 0.285743 | 48.6103ms | 233995 | 30 | 9.49524e+06 | 196887 | 1.93474 | 2(Loss) |
| simdjson (ondemand) | 235.896 | 0.203774 | 227.703ms | 233995 | 30 | 1.11478e+08 | 945987 | 9.29746 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2627.19 | 0.429946 | 21.2391ms | 233995 | 30 | 4.00111e+06 | 84940.7 | 0.834247 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2625.12 | 0.441195 | 21.3085ms | 233995 | 30 | 4.21986e+06 | 85007.6 | 0.834422 | 1(Tie) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1346.63 | 0.439009 | 59.964ms | 346753 | 30 | 3.48669e+07 | 245568 | 1.62849 | 1(Tie) |
| glaze STATISTICAL TIE | 1335.15 | 0.25924 | 60.4656ms | 346753 | 30 | 1.23682e+07 | 247680 | 1.64246 | 1(Tie) |
| simdjson (ondemand) | 346.987 | 0.064315 | 229.77ms | 346753 | 30 | 1.12709e+07 | 953031 | 6.32072 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3355.35 | 0.364751 | 24.9586ms | 346753 | 30 | 3.87684e+06 | 98555.9 | 0.653076 | 1(Win) |
| glaze | 2459.07 | 0.335185 | 33.1597ms | 346753 | 30 | 6.0952e+06 | 134477 | 0.891521 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 738.32 | 0.38781 | 29.9711ms | 94651 | 30 | 6.74404e+06 | 122259 | 2.96952 | 1(Win) |
| jsonifier | 697.503 | 0.46609 | 31.2828ms | 94651 | 30 | 1.09149e+07 | 129413 | 3.14337 | 2(Loss) |
| glaze | 683.623 | 0.357311 | 32.5444ms | 94651 | 30 | 6.67779e+06 | 132041 | 3.20736 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3269.15 | 0.0349679 | 7.56696ms | 94651 | 30 | 2796.67 | 27611.5 | 0.6683 | 1(Tie) |
| glaze STATISTICAL TIE | 3212.91 | 0.99342 | 7.43172ms | 94651 | 30 | 2.3369e+06 | 28094.8 | 0.681613 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1014.53 | 0.314517 | 31.237ms | 136024 | 30 | 4.85191e+06 | 127865 | 2.16119 | 1(Win) |
| jsonifier | 892.014 | 0.571214 | 35.9373ms | 136024 | 30 | 2.07018e+07 | 145427 | 2.45805 | 2(Loss) |
| glaze | 827.148 | 0.448472 | 38.039ms | 136024 | 30 | 1.48407e+07 | 156831 | 2.65098 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3866.78 | 0.88741 | 8.6578ms | 136024 | 30 | 2.65889e+06 | 33547.9 | 0.565341 | 1(Win) |
| glaze | 2956.35 | 1.2355 | 11.0024ms | 136046 | 30 | 8.81988e+06 | 43886.4 | 0.741081 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 494.788 | 0.155286 | 966.3ms | 2090234 | 30 | 1.17419e+09 | 4.0288e+06 | 4.4327 | 1(Win) |
| glaze | 425.871 | 0.113355 | 1130.68ms | 2090234 | 30 | 8.44567e+08 | 4.68077e+06 | 5.15012 | 2(Loss) |
| simdjson (ondemand) | 331.577 | 0.130283 | 1446.26ms | 2090234 | 30 | 1.84042e+09 | 6.01188e+06 | 6.61481 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 983.549 | 0.092068 | 490.179ms | 2090234 | 30 | 1.04457e+08 | 2.02675e+06 | 2.22958 | 1(Win) |
| glaze | 534.007 | 0.0624325 | 896.246ms | 2090234 | 30 | 1.62944e+08 | 3.73291e+06 | 4.10693 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1247.35 | 0.153685 | 1229.17ms | 6661897 | 30 | 1.83824e+09 | 5.09341e+06 | 1.75831 | 1(Win) |
| glaze | 1058.21 | 0.125472 | 1426.78ms | 6661897 | 30 | 1.70244e+09 | 6.00381e+06 | 2.07262 | 2(Loss) |
| simdjson (ondemand) | 992.335 | 0.109779 | 1542.94ms | 6661897 | 30 | 1.48197e+09 | 6.40235e+06 | 2.21002 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1908.54 | 0.229625 | 800.222ms | 6661897 | 30 | 1.75289e+09 | 3.32887e+06 | 1.14912 | 1(Win) |
| glaze | 1332.11 | 0.0833039 | 1150.4ms | 6661897 | 30 | 4.73555e+08 | 4.76935e+06 | 1.64634 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1140.41 | 0.400201 | 101.179ms | 500299 | 30 | 8.41039e+07 | 418378 | 1.92307 | 1(Win) |
| glaze | 984.563 | 0.273749 | 116.944ms | 500299 | 30 | 5.27958e+07 | 484603 | 2.22749 | 2(Loss) |
| simdjson (ondemand) | 648.548 | 0.181379 | 176.434ms | 500299 | 30 | 5.3416e+07 | 735678 | 3.38142 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2831.62 | 1.87336 | 40.0457ms | 500299 | 30 | 2.98919e+08 | 168498 | 0.774194 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2787.24 | 1.07857 | 42.6502ms | 500299 | 30 | 1.02266e+08 | 171181 | 0.786318 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2135.33 | 0.841 | 156.046ms | 1439562 | 30 | 8.77088e+08 | 642932 | 1.02695 | 1(Win) |
| glaze | 1704.98 | 0.169741 | 193.994ms | 1439562 | 30 | 5.60424e+07 | 805214 | 1.28611 | 2(Loss) |
| simdjson (ondemand) | 1683.16 | 0.172827 | 196.084ms | 1439562 | 30 | 5.96144e+07 | 815651 | 1.3028 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3583.19 | 0.696744 | 93.1844ms | 1439562 | 30 | 2.1379e+08 | 383142 | 0.611574 | 1(Win) |
| glaze | 2969.4 | 0.452386 | 111.518ms | 1439584 | 30 | 1.31243e+08 | 462348 | 0.738317 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1003.74 | 0.840523 | 13.4528ms | 56369 | 30 | 6.07933e+06 | 53557.2 | 2.18332 | 1(Win) |
| glaze | 963.729 | 0.612442 | 14.1019ms | 56369 | 30 | 3.50125e+06 | 55780.9 | 2.27406 | 2(Loss) |
| simdjson (ondemand) | 751.855 | 0.672731 | 17.6407ms | 56369 | 30 | 6.94091e+06 | 71500 | 2.91553 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3467.22 | 1.54012 | 4.12178ms | 56369 | 30 | 1.71061e+06 | 15504.6 | 0.630762 | 1(Win) |
| jsonifier | 3179.07 | 1.12839 | 4.78694ms | 56369 | 30 | 1.09224e+06 | 16909.9 | 0.685675 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1384.96 | 0.55813 | 16.7061ms | 94370 | 30 | 3.94628e+06 | 64982.7 | 1.58262 | 1(Win) |
| glaze | 1295.72 | 0.386715 | 17.4726ms | 94370 | 30 | 2.16447e+06 | 69458.3 | 1.6917 | 2(Loss) |
| simdjson (ondemand) | 1255.35 | 0.535372 | 18.0152ms | 94370 | 30 | 4.41949e+06 | 71691.9 | 1.74614 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4163.25 | 0.869423 | 5.88943ms | 94370 | 30 | 1.05971e+06 | 21617.3 | 0.524602 | 1(Win) |
| glaze | 3147.73 | 1.02287 | 7.44338ms | 94370 | 30 | 2.56589e+06 | 28591.4 | 0.695719 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1054.12 | 0.570128 | 12.5392ms | 52708 | 30 | 2.21737e+06 | 47685.5 | 2.07847 | 1(Win) |
| jsonifier | 866.47 | 1.02819 | 14.6723ms | 52708 | 30 | 1.06737e+07 | 58012.7 | 2.52854 | 2(Loss) |
| glaze | 778.055 | 0.76774 | 16.0524ms | 52708 | 30 | 7.38044e+06 | 64605 | 2.81644 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3671.48 | 1.76994 | 3.84314ms | 52708 | 30 | 1.76161e+06 | 13691 | 0.595495 | 1(Win) |
| jsonifier | 3412.93 | 0.543424 | 4.33638ms | 52708 | 30 | 192176 | 14728.2 | 0.640915 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1331.74 | 0.753378 | 13.1849ms | 70103 | 30 | 4.29123e+06 | 50201.6 | 1.64523 | 1(Win) |
| jsonifier | 943.852 | 0.617532 | 18.4833ms | 70103 | 30 | 5.73992e+06 | 70832.5 | 2.32114 | 2(Loss) |
| glaze | 912.765 | 0.65083 | 18.3108ms | 70103 | 30 | 6.8173e+06 | 73245 | 2.40105 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3781.24 | 0.431419 | 4.88396ms | 70103 | 30 | 174552 | 17680.8 | 0.578061 | 1(Win) |
| glaze | 3586.81 | 2.45179 | 5.06767ms | 70103 | 30 | 6.26536e+06 | 18639.3 | 0.610123 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 771.361 | 0.0873614 | 4.18599ms | 11812 | 30 | 4883.06 | 14603.8 | 2.83634 | 1(Win) |
| glaze | 713.861 | 0.358998 | 4.39593ms | 11812 | 30 | 96277.6 | 15780.1 | 3.06563 | 2(Loss) |
| simdjson (ondemand) | 670.168 | 1.10786 | 4.93856ms | 11812 | 30 | 1.04034e+06 | 16808.9 | 3.26565 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3028.09 | 0.176992 | 1.36135ms | 11812 | 30 | 1300.58 | 3720.1 | 0.712202 | 1(Win) |
| glaze | 2749.41 | 0.117467 | 1.45192ms | 11812 | 30 | 694.902 | 4097.17 | 0.786844 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1604.93 | 1.00969 | 5.25122ms | 31235 | 30 | 1.05358e+06 | 18560.4 | 1.36376 | 1(Win) |
| jsonifier | 1397.58 | 1.14605 | 5.6612ms | 31235 | 30 | 1.79002e+06 | 21314 | 1.56648 | 2(Loss) |
| glaze | 1171.46 | 1.137 | 6.70293ms | 31235 | 30 | 2.50767e+06 | 25428.2 | 1.86951 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4041.85 | 0.805445 | 2.24441ms | 31235 | 30 | 105710 | 7369.9 | 0.53478 | 1(Win) |
| glaze | 3690.67 | 0.109861 | 2.44048ms | 31235 | 30 | 2358.76 | 8071.17 | 0.591019 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2055.95 | 0.654935 | 13.1064ms | 108313 | 30 | 3.24829e+06 | 50242.2 | 1.0659 | 1(Win) |
| glaze | 1306.88 | 0.555958 | 19.6149ms | 108313 | 30 | 5.79292e+06 | 79039.8 | 1.67737 | 2(Loss) |
| simdjson (ondemand) | 1058.17 | 0.468157 | 24.375ms | 108313 | 30 | 6.26549e+06 | 97616.9 | 2.07191 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2284.46 | 0.843493 | 10.6272ms | 108313 | 30 | 4.36393e+06 | 45216.5 | 0.958956 | 1(Win) |
| jsonifier | 2029.67 | 1.60252 | 118.574ms | 108313 | 128 | 8.51385e+07 | 50892.7 | 1.07938 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1939.65 | 0.495771 | 26.0022ms | 213963 | 30 | 8.16047e+06 | 105200 | 1.13032 | 1(Win) |
| jsonifier | 1764.72 | 0.506033 | 28.8867ms | 213963 | 30 | 1.02709e+07 | 115628 | 1.24244 | 2(Loss) |
| glaze | 1663.88 | 0.355065 | 30.2707ms | 213963 | 30 | 5.68814e+06 | 122636 | 1.31769 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3203.42 | 1.90095 | 16.687ms | 213963 | 30 | 4.39856e+07 | 63697.8 | 0.68219 | 1(Win) |
| glaze | 2863.89 | 1.15121 | 16.4494ms | 213963 | 30 | 2.01834e+07 | 71249.5 | 0.765368 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 533.126 | 0.140242 | 790.74ms | 1834197 | 30 | 6.35201e+08 | 3.28108e+06 | 4.11394 | 1(Win) |
| glaze | 382.159 | 0.0796905 | 1099.06ms | 1834197 | 30 | 3.99153e+08 | 4.57723e+06 | 5.73927 | 2(Loss) |
| simdjson (ondemand) | 351.025 | 0.0835785 | 1199.04ms | 1834197 | 30 | 5.20387e+08 | 4.9832e+06 | 6.24831 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 629.866 | 0.563743 | 666.208ms | 1834197 | 30 | 7.35327e+09 | 2.77714e+06 | 3.48185 | 1(Win) |
| glaze | 343.668 | 0.0328373 | 1223.04ms | 1833577 | 30 | 8.37486e+07 | 5.08815e+06 | 6.38208 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1882.86 | 0.118138 | 1211.16ms | 9930848 | 30 | 1.05934e+09 | 5.03001e+06 | 1.16488 | 1(Win) |
| simdjson (ondemand) | 1679.36 | 0.106317 | 1351.41ms | 9930848 | 30 | 1.07849e+09 | 5.63953e+06 | 1.30605 | 2(Loss) |
| glaze | 1512.16 | 0.195669 | 1508.33ms | 9930848 | 30 | 4.50549e+09 | 6.26309e+06 | 1.45047 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1757.19 | 0.279278 | 1301.58ms | 9930848 | 30 | 6.79722e+09 | 5.38975e+06 | 1.24817 | 1(Win) |
| glaze | 1202.85 | 0.271149 | 1880.28ms | 9930228 | 30 | 1.36721e+10 | 7.87316e+06 | 1.82338 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 944.378 | 0.341994 | 156.001ms | 642697 | 30 | 1.47801e+08 | 649024 | 2.3221 | 1(Win) |
| glaze | 808.96 | 0.121707 | 183.547ms | 642697 | 30 | 2.55101e+07 | 757669 | 2.7108 | 2(Loss) |
| simdjson (ondemand) | 682.247 | 0.327775 | 215.941ms | 642697 | 30 | 2.60136e+08 | 898389 | 3.21394 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1073.68 | 0.317454 | 137.622ms | 642697 | 30 | 9.85245e+07 | 570862 | 2.04223 | 1(Win) |
| glaze | 838.178 | 0.274211 | 176.024ms | 642692 | 30 | 1.20622e+08 | 731252 | 2.61589 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1277.6 | 0.270879 | 221.652ms | 1225964 | 30 | 1.84348e+08 | 915130 | 1.7164 | 1(Win) |
| glaze | 1258.75 | 0.117992 | 224.631ms | 1225964 | 30 | 3.60331e+07 | 928831 | 1.74204 | 2(Loss) |
| simdjson (ondemand) | 1250.28 | 0.122773 | 226.312ms | 1225964 | 30 | 3.95428e+07 | 935129 | 1.75379 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1275.71 | 0.14036 | 220.903ms | 1225970 | 30 | 4.96436e+07 | 916493 | 1.71881 | 1(Win) |
| jsonifier | 1071.39 | 0.0969209 | 262.63ms | 1225964 | 30 | 3.35597e+07 | 1.09127e+06 | 2.04669 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 649.062 | 0.278452 | 144.864ms | 409725 | 30 | 8.43013e+07 | 602014 | 3.3789 | 1(Win) |
| simdjson (ondemand) | 607.011 | 0.14706 | 155.76ms | 409725 | 30 | 2.68846e+07 | 643718 | 3.61269 | 2(Loss) |
| glaze | 486.773 | 0.215219 | 194.087ms | 409725 | 30 | 8.95396e+07 | 802723 | 4.50511 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1944.08 | 0.394634 | 49.4788ms | 409725 | 30 | 1.88742e+07 | 200992 | 1.12793 | 1(Win) |
| glaze | 1909.3 | 0.350814 | 120.211ms | 409725 | 32 | 1.64945e+07 | 204653 | 1.14822 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1112.85 | 0.176895 | 162.655ms | 785750 | 30 | 4.25643e+07 | 673358 | 1.97038 | 1(Win) |
| jsonifier | 941.465 | 0.25216 | 193.714ms | 785750 | 30 | 1.20847e+08 | 795940 | 2.32942 | 2(Loss) |
| glaze | 772.838 | 0.262046 | 232.248ms | 785750 | 30 | 1.93673e+08 | 969608 | 2.83742 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2876.04 | 0.381163 | 63.7074ms | 785750 | 30 | 2.95885e+07 | 260550 | 0.762262 | 1(Win) |
| glaze | 2183.18 | 1.14372 | 82.7186ms | 785750 | 30 | 4.62331e+08 | 343237 | 1.00415 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 748.746 | 0.133909 | 2635.27ms | 8587914 | 30 | 6.43642e+09 | 1.09384e+07 | 2.92935 | 1(Win) |
| simdjson (ondemand) | 683.763 | 0.304995 | 2881.64ms | 8587914 | 30 | 4.00378e+10 | 1.19779e+07 | 3.20757 | 2(Loss) |
| glaze | 632.869 | 0.47488 | 3070.93ms | 8587914 | 30 | 1.13302e+11 | 1.29412e+07 | 3.46567 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2229.4 | 0.128784 | 887.772ms | 8588126 | 30 | 6.71529e+08 | 3.67376e+06 | 0.983693 | 1(Win) |
| glaze | 2161.92 | 0.262191 | 906.813ms | 8588126 | 30 | 2.95988e+09 | 3.78842e+06 | 1.01439 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 771.608 | 0.390173 | 2932.96ms | 9804437 | 30 | 6.70636e+10 | 1.21179e+07 | 2.84248 | 1(Win) |
| jsonifier | 729.383 | 0.162135 | 3048.87ms | 9804437 | 30 | 1.29601e+10 | 1.28194e+07 | 3.00712 | 2(Loss) |
| glaze | 667.718 | 0.234587 | 3387.38ms | 9804437 | 30 | 3.23735e+10 | 1.40033e+07 | 3.28484 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2469.18 | 0.124497 | 1035.36ms | 11078090 | 30 | 8.51256e+08 | 4.2787e+06 | 0.888208 | 1(Win) |
| glaze | 2282.09 | 0.233923 | 1107.09ms | 11078090 | 30 | 3.5183e+09 | 4.62949e+06 | 0.961053 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 4094.85 | 0.705367 | 15.4908ms | 264040 | 30 | 5.64437e+06 | 61493.9 | 0.535191 | 1(Tie) |
| jsonifier STATISTICAL TIE | 4094.44 | 0.649482 | 15.6969ms | 264040 | 30 | 4.78636e+06 | 61500 | 0.535348 | 1(Tie) |
| glaze | 1280.46 | 0.47754 | 47.6967ms | 264040 | 30 | 2.64575e+07 | 196655 | 1.71254 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5562.37 | 0.453587 | 17.3415ms | 399947 | 30 | 2.9022e+06 | 68571.3 | 0.394084 | 1(Win) |
| simdjson (ondemand) | 5387.63 | 0.490836 | 17.771ms | 399947 | 30 | 3.62246e+06 | 70795.4 | 0.406846 | 2(Loss) |
| glaze | 1720.45 | 0.332667 | 54.2083ms | 399947 | 30 | 1.63177e+07 | 221697 | 1.27461 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1102.07 | 0.351327 | 56.153ms | 264040 | 30 | 1.93317e+07 | 228487 | 1.98957 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1087.12 | 1.69308 | 57.2397ms | 264040 | 30 | 4.6138e+08 | 231629 | 2.01694 | 1(Tie) |
| glaze | 938.67 | 1.10353 | 64.6852ms | 264040 | 30 | 2.62909e+08 | 268261 | 2.33608 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4018.3 | 1.42327 | 15.854ms | 264040 | 30 | 2.38645e+07 | 62665.4 | 0.545136 | 1(Win) |
| glaze | 3145.91 | 1.79395 | 19.4354ms | 263923 | 30 | 6.1802e+07 | 80007.5 | 0.69659 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1530.67 | 0.352528 | 61.0171ms | 399947 | 30 | 2.31498e+07 | 249184 | 1.43261 | 1(Win) |
| glaze | 1185.22 | 0.435195 | 78.4933ms | 399947 | 30 | 5.88435e+07 | 321814 | 1.85026 | 2(Loss) |
| jsonifier | 1134.16 | 0.326851 | 81.8164ms | 399947 | 30 | 3.62475e+07 | 336302 | 1.93346 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4569.73 | 0.958937 | 21.0769ms | 399947 | 30 | 1.92188e+07 | 83466.5 | 0.479678 | 1(Win) |
| glaze | 3518.16 | 0.752305 | 27.0756ms | 399830 | 30 | 1.99448e+07 | 108383 | 0.62294 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1871.51 | 0.232988 | 57.9952ms | 466906 | 30 | 9.2185e+06 | 237923 | 1.17172 | 1(Win) |
| jsonifier | 1741.23 | 0.262598 | 62.0574ms | 466906 | 30 | 1.35285e+07 | 255725 | 1.25918 | 2(Loss) |
| simdjson (ondemand) | 796.146 | 0.283018 | 138.071ms | 466906 | 30 | 7.51659e+07 | 559289 | 2.75365 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2698.33 | 0.300656 | 60.5627ms | 699405 | 30 | 1.65703e+07 | 247192 | 0.812393 | 1(Win) |
| glaze | 2075.39 | 0.169721 | 77.9107ms | 699405 | 30 | 8.9259e+06 | 321388 | 1.05661 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2818.39 | 0.435852 | 51.9321ms | 631514 | 30 | 2.60235e+07 | 213689 | 0.777992 | 1(Win) |
| glaze | 1640.09 | 0.366172 | 88.0748ms | 631514 | 30 | 5.42406e+07 | 367211 | 1.33716 | 2(Loss) |
