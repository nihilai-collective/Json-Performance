# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [55785b4](https://github.com/nihilai-collective/jsonifier/commit/55785b4)  
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

> Adaptive sampling on (AMD EPYC 9V45 96-Core Processor-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 957.145 | 0.553315 | 1.85548ms | 1811 | 30 | 2990.53 | 1804.43 | 2.54681 | 1(Win) |
| glaze | 902.4 | 0.183568 | 0.566567ms | 1811 | 30 | 370.3 | 1913.9 | 2.70379 | 2(Loss) |
| simdjson (ondemand) | 225.601 | 0.055862 | 1.97935ms | 1811 | 30 | 548.668 | 7655.57 | 10.935 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 736.107 | 0.0584793 | 0.711466ms | 1811 | 30 | 56.4782 | 2346.27 | 3.32588 | 1(Win) |
| glaze | 502.63 | 0.093594 | 0.947614ms | 1798 | 30 | 305.844 | 3411.47 | 4.88522 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1926.82 | 0.0778566 | 0.610033ms | 3873 | 30 | 66.823 | 1916.93 | 1.26718 | 1(Win) |
| glaze | 1584.66 | 0.039945 | 0.677525ms | 3873 | 30 | 26.0057 | 2330.83 | 1.54311 | 2(Loss) |
| simdjson (ondemand) | 450.765 | 0.0530622 | 2.16605ms | 3873 | 30 | 567.137 | 8194.03 | 5.47321 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2861.76 | 0.0808211 | 0.464783ms | 3873 | 30 | 32.6437 | 1290.67 | 0.84626 | 1(Win) |
| glaze | 2037.21 | 0.133227 | 1.19121ms | 3873 | 32 | 186.706 | 1813.06 | 1.19659 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1978.13 | 0.0556944 | 1.22917ms | 3862 | 32 | 34.4103 | 1861.91 | 1.23281 | 1(Win) |
| glaze | 1358.17 | 0.048401 | 0.755764ms | 3862 | 30 | 51.6828 | 2711.8 | 1.80422 | 2(Loss) |
| simdjson (ondemand) | 461.305 | 0.0297059 | 2.0237ms | 3862 | 30 | 168.754 | 7984.07 | 5.34809 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2800.12 | 0.0841819 | 0.44281ms | 3862 | 30 | 36.7816 | 1315.33 | 0.864181 | 1(Win) |
| glaze | 1967.56 | 0.118082 | 1.24534ms | 3862 | 32 | 156.346 | 1871.91 | 1.23977 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 985.246 | 0.177356 | 0.340905ms | 905 | 30 | 72.4138 | 876 | 2.42858 | 1(Win) |
| glaze | 940.784 | 0.115878 | 0.312352ms | 905 | 30 | 33.9034 | 917.4 | 2.55672 | 2(Loss) |
| simdjson (ondemand) | 149.846 | 0.0893311 | 1.50521ms | 905 | 30 | 794.202 | 5759.73 | 16.4398 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1157.25 | 0.74131 | 0.314646ms | 905 | 30 | 916.993 | 745.8 | 2.05985 | 1(Win) |
| glaze | 582.818 | 0.565386 | 0.467066ms | 905 | 30 | 2103.02 | 1480.87 | 4.16659 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3133.44 | 0.0332367 | 0.853892ms | 9578 | 30 | 28.1621 | 2915.1 | 0.782422 | 1(Win) |
| glaze | 2590.83 | 0.199625 | 2.13894ms | 9578 | 32 | 1585.08 | 3525.62 | 0.948378 | 2(Loss) |
| simdjson (ondemand) | 1075.52 | 0.0901708 | 2.17866ms | 9578 | 30 | 1759.4 | 8492.9 | 2.29424 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5252.61 | 0.880403 | 0.55514ms | 9578 | 30 | 7032.07 | 1739 | 0.462922 | 1(Win) |
| glaze | 4463.45 | 0.301602 | 0.585886ms | 9578 | 30 | 1142.88 | 2046.47 | 0.547066 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5775.66 | 1.07428 | 9.35483ms | 233995 | 30 | 5.16854e+06 | 38637.2 | 0.428346 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 5681.28 | 1.51731 | 9.50537ms | 233995 | 30 | 1.06559e+07 | 39279 | 0.435054 | 1(Tie) |
| glaze | 2177.49 | 0.436686 | 24.8422ms | 233995 | 30 | 6.00842e+06 | 102483 | 1.13669 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7608.74 | 0.566632 | 10.981ms | 346753 | 30 | 1.81944e+06 | 43461.8 | 0.325184 | 1(Win) |
| simdjson (ondemand) | 7254.99 | 0.537005 | 11.3217ms | 346753 | 30 | 1.7974e+06 | 45580.9 | 0.340773 | 2(Loss) |
| glaze | 2718.75 | 0.356075 | 29.5548ms | 346753 | 30 | 5.6274e+06 | 121633 | 0.91024 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1963.77 | 0.396843 | 27.6073ms | 233995 | 30 | 6.10087e+06 | 113636 | 1.26043 | 1(Win) |
| glaze | 1810.77 | 1.35352 | 29.6817ms | 233995 | 30 | 8.34716e+07 | 123238 | 1.36694 | 2(Loss) |
| simdjson (ondemand) | 1592.8 | 0.315616 | 34.375ms | 233995 | 30 | 5.8658e+06 | 140102 | 1.55366 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4739.93 | 0.809769 | 11.6176ms | 233995 | 30 | 4.36027e+06 | 47079.8 | 0.522029 | 1(Win) |
| glaze | 3879.31 | 0.600278 | 13.9975ms | 233995 | 30 | 3.5771e+06 | 57524.4 | 0.637909 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2370.02 | 0.40343 | 34.2356ms | 346753 | 30 | 9.50593e+06 | 139530 | 1.04444 | 1(Win) |
| jsonifier | 2319.04 | 0.953119 | 34.5726ms | 346753 | 30 | 5.54167e+07 | 142598 | 1.06737 | 2(Loss) |
| simdjson (ondemand) | 2248.27 | 0.458871 | 35.2707ms | 346753 | 30 | 1.36662e+07 | 147086 | 1.10098 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5654.18 | 0.603969 | 14.3553ms | 346753 | 30 | 3.74327e+06 | 58485.8 | 0.437661 | 1(Win) |
| glaze | 4251.62 | 0.505365 | 19.2299ms | 346753 | 30 | 4.63514e+06 | 77779.7 | 0.581952 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5649.19 | 1.83696 | 9.56456ms | 233995 | 30 | 1.57966e+07 | 39502.1 | 0.437953 | 1(Win) |
| simdjson (ondemand) | 4291.44 | 0.868683 | 12.6496ms | 233995 | 30 | 6.1214e+06 | 52000 | 0.57659 | 2(Loss) |
| glaze | 2158.18 | 0.647662 | 24.9678ms | 233995 | 30 | 1.34541e+07 | 103400 | 1.14685 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7534.83 | 0.990828 | 10.7902ms | 346753 | 30 | 5.67299e+06 | 43888.1 | 0.328365 | 1(Win) |
| simdjson (ondemand) | 5508.69 | 0.904796 | 14.5954ms | 346753 | 30 | 8.85049e+06 | 60030.5 | 0.449178 | 2(Loss) |
| glaze | 2591 | 0.868967 | 30.1064ms | 346753 | 30 | 3.69007e+07 | 127630 | 0.955307 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2007.92 | 0.305045 | 27.5322ms | 233995 | 30 | 3.44801e+06 | 111137 | 1.23272 | 1(Win) |
| jsonifier | 1818.85 | 0.416555 | 29.7954ms | 233995 | 30 | 7.83587e+06 | 122690 | 1.36057 | 2(Loss) |
| simdjson (ondemand) | 437.82 | 0.689354 | 123.6ms | 233995 | 30 | 3.70364e+08 | 509696 | 5.6545 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4644.28 | 0.794829 | 11.7042ms | 233995 | 30 | 4.37568e+06 | 48049.4 | 0.532763 | 1(Win) |
| glaze | 3838.72 | 0.502808 | 14.2588ms | 233995 | 30 | 2.5631e+06 | 58132.7 | 0.644602 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2465.28 | 0.366134 | 32.8462ms | 346753 | 30 | 7.23619e+06 | 134139 | 1.0039 | 1(Win) |
| jsonifier | 2237.37 | 0.367132 | 35.9572ms | 346753 | 30 | 8.83347e+06 | 147803 | 1.10616 | 2(Loss) |
| simdjson (ondemand) | 634.364 | 0.949817 | 124.655ms | 346753 | 30 | 7.35469e+08 | 521293 | 3.90251 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5817.93 | 0.908933 | 14.082ms | 346753 | 30 | 8.00735e+06 | 56839.7 | 0.425294 | 1(Win) |
| glaze | 4321.11 | 0.423395 | 18.8635ms | 346753 | 30 | 3.14966e+06 | 76528.9 | 0.572602 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1215.82 | 0.342862 | 18.0769ms | 94651 | 30 | 1.94391e+06 | 74243.3 | 2.03519 | 1(Win) |
| glaze STATISTICAL TIE | 1094.51 | 0.672728 | 20.0137ms | 94651 | 30 | 9.23438e+06 | 82471.5 | 2.26115 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1091.75 | 0.694988 | 19.9618ms | 94651 | 30 | 9.90564e+06 | 82680.5 | 2.26695 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6014.25 | 1.15666 | 3.88591ms | 94651 | 30 | 904106 | 15008.7 | 0.410903 | 1(Win) |
| glaze | 5549.32 | 2.30464 | 9.571ms | 94651 | 32 | 4.49705e+06 | 16266.2 | 0.445381 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1605.13 | 0.586924 | 19.5333ms | 136024 | 30 | 6.74984e+06 | 80817.3 | 1.54171 | 1(Win) |
| jsonifier STATISTICAL TIE | 1386.65 | 0.588388 | 22.8322ms | 136024 | 30 | 9.08965e+06 | 93551.2 | 1.78483 | 2(Tie) |
| glaze STATISTICAL TIE | 1383.6 | 0.65562 | 22.8981ms | 136024 | 30 | 1.13354e+07 | 93757.2 | 1.78881 | 2(Tie) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7218.76 | 0.319339 | 4.59084ms | 136024 | 30 | 98794 | 17970.2 | 0.342444 | 1(Win) |
| glaze | 5814.07 | 0.815813 | 5.68707ms | 136046 | 30 | 994293 | 22315.5 | 0.425299 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 770.571 | 0.153722 | 624.917ms | 2090234 | 30 | 4.74417e+08 | 2.58692e+06 | 3.21271 | 1(Win) |
| glaze | 666.692 | 0.239904 | 725.247ms | 2090234 | 30 | 1.5436e+09 | 2.98999e+06 | 3.7133 | 2(Loss) |
| simdjson (ondemand) | 490.42 | 0.256627 | 984.373ms | 2090234 | 30 | 3.26422e+09 | 4.06469e+06 | 5.04809 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1605.96 | 0.152198 | 296.151ms | 2090234 | 30 | 1.07069e+08 | 1.24126e+06 | 1.54141 | 1(Win) |
| glaze | 955.544 | 0.129612 | 510.265ms | 2090234 | 30 | 2.1933e+08 | 2.08614e+06 | 2.59082 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1988.47 | 0.150115 | 776.404ms | 6661897 | 30 | 6.90129e+08 | 3.19507e+06 | 1.24496 | 1(Win) |
| glaze | 1616.81 | 0.247968 | 943.904ms | 6661897 | 30 | 2.84833e+09 | 3.92952e+06 | 1.53117 | 2(Loss) |
| simdjson (ondemand) | 1462.43 | 0.166015 | 1050.15ms | 6661897 | 30 | 1.5605e+09 | 4.34434e+06 | 1.69281 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4059.14 | 0.33581 | 370.264ms | 6661897 | 30 | 8.28778e+08 | 1.56518e+06 | 0.609827 | 1(Win) |
| glaze | 2445.39 | 0.302969 | 622.748ms | 6661897 | 30 | 1.85873e+09 | 2.59806e+06 | 1.01225 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1567.66 | 0.322329 | 71.6517ms | 500299 | 30 | 2.88718e+07 | 304353 | 1.57908 | 1(Win) |
| glaze | 1331 | 0.37818 | 87.1242ms | 500299 | 30 | 5.51346e+07 | 358470 | 1.85985 | 2(Loss) |
| simdjson (ondemand) | 993.054 | 0.302097 | 116.808ms | 500299 | 30 | 6.32017e+07 | 480460 | 2.49284 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5194.06 | 0.474945 | 22.6498ms | 500299 | 30 | 5.71023e+06 | 91859.3 | 0.476442 | 1(Win) |
| glaze | 4178.68 | 0.648833 | 27.7382ms | 500299 | 30 | 1.64653e+07 | 114180 | 0.592212 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3169.45 | 0.579753 | 104.144ms | 1439562 | 30 | 1.89191e+08 | 433159 | 0.781062 | 1(Win) |
| glaze | 2636.76 | 0.418005 | 125.183ms | 1439562 | 30 | 1.42103e+08 | 520667 | 0.938878 | 2(Loss) |
| simdjson (ondemand) | 2604.4 | 0.280703 | 127.002ms | 1439562 | 30 | 6.56844e+07 | 527136 | 0.950524 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7167.18 | 0.348759 | 46.4151ms | 1439562 | 30 | 1.33887e+07 | 191550 | 0.345337 | 1(Win) |
| glaze | 6166.38 | 0.355045 | 53.4849ms | 1439584 | 30 | 1.87457e+07 | 222642 | 0.401397 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1485.13 | 0.785856 | 9.03401ms | 56369 | 30 | 2.42751e+06 | 36197.4 | 1.6657 | 1(Win) |
| glaze STATISTICAL TIE | 1350.99 | 0.543318 | 50.4703ms | 56369 | 64 | 2.99132e+06 | 39791.3 | 1.83132 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1332.05 | 1.34477 | 9.82516ms | 56369 | 30 | 8.83601e+06 | 40357 | 1.8573 | 2(Tie) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7040.71 | 0.043894 | 2.00988ms | 56369 | 30 | 336.961 | 7635.27 | 0.350391 | 1(Win) |
| glaze | 5970.49 | 0.129352 | 2.32236ms | 56369 | 30 | 4069.4 | 9003.9 | 0.413399 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2133.17 | 0.876114 | 10.3887ms | 94370 | 30 | 4.09882e+06 | 42189.9 | 1.15986 | 1(Win) |
| jsonifier | 2062.71 | 1.02228 | 10.8668ms | 94370 | 30 | 5.96832e+06 | 43631 | 1.19947 | 2(Loss) |
| glaze | 1445.29 | 1.37132 | 15.2405ms | 94370 | 30 | 2.18753e+07 | 62269.9 | 1.71216 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8600.97 | 1.8767 | 2.67604ms | 94370 | 30 | 1.15687e+06 | 10463.7 | 0.287092 | 1(Win) |
| glaze | 5788.1 | 0.0916597 | 3.94764ms | 94370 | 30 | 6093.59 | 15548.8 | 0.426996 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1663.84 | 0.774018 | 7.751ms | 52708 | 30 | 1.64042e+06 | 30211.1 | 1.48617 | 1(Win) |
| jsonifier | 1511.53 | 1.31692 | 8.53475ms | 52708 | 30 | 5.75383e+06 | 33255.2 | 1.63588 | 2(Loss) |
| glaze | 1167.39 | 1.15581 | 10.4938ms | 52708 | 30 | 7.43052e+06 | 43058.8 | 2.11934 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5999.35 | 0.320643 | 4.93238ms | 52708 | 32 | 23096 | 8378.62 | 0.411121 | 1(Win) |
| glaze | 5883.48 | 0.13468 | 2.25016ms | 52708 | 30 | 3972.03 | 8543.63 | 0.419389 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2042.37 | 1.19907 | 8.00816ms | 70103 | 30 | 4.62182e+06 | 32734.2 | 1.21076 | 1(Win) |
| glaze | 1547.25 | 0.821206 | 10.813ms | 70103 | 30 | 3.77725e+06 | 43209.1 | 1.59908 | 2(Loss) |
| jsonifier | 1456.7 | 0.47099 | 12.0662ms | 70103 | 30 | 1.40177e+06 | 45895.1 | 1.69801 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6923.5 | 0.180323 | 2.93803ms | 70103 | 30 | 9095.87 | 9656.3 | 0.356529 | 1(Win) |
| glaze | 5335.09 | 0.920156 | 3.27658ms | 70103 | 30 | 398872 | 12531.3 | 0.46296 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1117.37 | 1.62434 | 5.88292ms | 11812 | 32 | 858137 | 10081.5 | 2.2094 | 1(Win) |
| simdjson (ondemand) | 1068.3 | 0.56677 | 2.63018ms | 11812 | 30 | 107152 | 10544.6 | 2.31165 | 2(Loss) |
| glaze | 954.868 | 1.82393 | 2.92975ms | 11812 | 30 | 1.38899e+06 | 11797.2 | 2.5865 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4642.85 | 0.0658066 | 0.737817ms | 11812 | 30 | 76.4782 | 2426.27 | 0.527097 | 1(Win) |
| glaze | 3566.54 | 0.275398 | 0.882565ms | 11812 | 30 | 2269.84 | 3158.47 | 0.68793 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2551.37 | 1.82192 | 2.90017ms | 31235 | 30 | 1.35743e+06 | 11675.3 | 0.96783 | 1(Win) |
| jsonifier | 2400.82 | 1.43249 | 3.22088ms | 31235 | 30 | 947694 | 12407.4 | 1.02892 | 2(Loss) |
| glaze | 2012.51 | 0.15576 | 3.7632ms | 31235 | 30 | 15945.6 | 14801.4 | 1.22809 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7553.38 | 0.176888 | 1.08264ms | 31235 | 30 | 1459.89 | 3943.67 | 0.325384 | 1(Win) |
| glaze | 4922.45 | 0.558757 | 1.556ms | 31235 | 30 | 34299.5 | 6051.47 | 0.500494 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3304.71 | 0.597984 | 7.89216ms | 108313 | 30 | 1.04808e+06 | 31257 | 0.74834 | 1(Win) |
| glaze | 1662.62 | 0.311836 | 15.5634ms | 108313 | 30 | 1.12602e+06 | 62128 | 1.48841 | 2(Loss) |
| simdjson (ondemand) | 1584.42 | 0.881432 | 16.3344ms | 108313 | 30 | 9.90654e+06 | 65194.6 | 1.56183 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3890.96 | 0.611001 | 6.54009ms | 108313 | 30 | 789319 | 26547.5 | 0.635685 | 1(Win) |
| glaze | 2417.42 | 0.447982 | 10.5227ms | 108313 | 30 | 1.09926e+06 | 42729.6 | 1.02348 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3053.39 | 0.414038 | 16.4803ms | 213963 | 30 | 2.29676e+06 | 66827.8 | 0.810477 | 1(Win) |
| jsonifier | 2740.4 | 0.330741 | 18.3566ms | 213963 | 30 | 1.81948e+06 | 74460.3 | 0.903088 | 2(Loss) |
| glaze | 2474.4 | 1.04439 | 21.3172ms | 213963 | 30 | 2.22526e+07 | 82464.8 | 1.00022 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6073.71 | 0.510575 | 8.24997ms | 213963 | 30 | 882693 | 33595.8 | 0.407282 | 1(Win) |
| glaze | 3304.93 | 0.895869 | 14.8975ms | 213963 | 30 | 9.17835e+06 | 61741.5 | 0.748731 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 865.002 | 0.187648 | 482.96ms | 1834197 | 30 | 4.31983e+08 | 2.02222e+06 | 2.86212 | 1(Win) |
| glaze | 638.371 | 0.174125 | 659.987ms | 1834197 | 30 | 6.8295e+08 | 2.74014e+06 | 3.87808 | 2(Loss) |
| simdjson (ondemand) | 496.047 | 0.342542 | 842.176ms | 1834197 | 30 | 4.37718e+09 | 3.52633e+06 | 4.9907 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1037.23 | 0.393153 | 400.303ms | 1834197 | 30 | 1.31882e+09 | 1.68644e+06 | 2.38685 | 1(Win) |
| glaze | 607.635 | 0.227028 | 701.946ms | 1833577 | 30 | 1.28054e+09 | 2.87777e+06 | 4.07425 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3301.68 | 0.27086 | 690.462ms | 9930848 | 30 | 1.81098e+09 | 2.86848e+06 | 0.749786 | 1(Win) |
| glaze | 2509.54 | 0.384313 | 903.828ms | 9930848 | 30 | 6.3107e+09 | 3.77392e+06 | 0.986462 | 2(Loss) |
| simdjson (ondemand) | 2306.7 | 0.424166 | 991.144ms | 9930848 | 30 | 9.09875e+09 | 4.10577e+06 | 1.07317 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3627.4 | 0.320448 | 622.753ms | 9930848 | 30 | 2.1e+09 | 2.6109e+06 | 0.68243 | 1(Win) |
| glaze | 2297.69 | 0.274899 | 1000.11ms | 9930228 | 30 | 3.85126e+09 | 4.12161e+06 | 1.07741 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1552.18 | 0.229978 | 95.8998ms | 642697 | 30 | 2.47415e+07 | 394880 | 1.59487 | 1(Win) |
| glaze | 1358.24 | 0.240651 | 108.323ms | 642697 | 30 | 3.538e+07 | 451264 | 1.82261 | 2(Loss) |
| simdjson (ondemand) | 1008.96 | 0.452267 | 144.153ms | 642697 | 30 | 2.26454e+08 | 607483 | 2.45363 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1731.3 | 0.299023 | 85.1692ms | 642697 | 30 | 3.362e+07 | 354025 | 1.42982 | 1(Win) |
| glaze | 1442.07 | 0.358824 | 102.336ms | 642692 | 30 | 6.97782e+07 | 425029 | 1.71666 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2192.01 | 0.260853 | 128.838ms | 1225964 | 30 | 5.80746e+07 | 533379 | 1.12937 | 1(Win) |
| glaze | 2041.29 | 0.297833 | 140.001ms | 1225964 | 30 | 8.72995e+07 | 572760 | 1.21276 | 2(Loss) |
| simdjson (ondemand) | 1879.55 | 0.42067 | 148.495ms | 1225964 | 30 | 2.05425e+08 | 622048 | 1.31713 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2845.31 | 0.342832 | 98.5964ms | 1225964 | 30 | 5.95363e+07 | 410912 | 0.870004 | 1(Win) |
| glaze | 2261.58 | 0.341339 | 123.947ms | 1225970 | 30 | 9.34179e+07 | 516974 | 1.09463 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1029.62 | 0.291263 | 91.3874ms | 409725 | 30 | 3.6654e+07 | 379502 | 2.40422 | 1(Win) |
| jsonifier | 931.86 | 0.224515 | 101.38ms | 409725 | 30 | 2.65887e+07 | 419316 | 2.65654 | 2(Loss) |
| glaze | 683.178 | 0.447977 | 132.948ms | 409725 | 30 | 1.96948e+08 | 571950 | 3.62353 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3225.89 | 0.35112 | 29.3307ms | 409725 | 30 | 5.42647e+06 | 121128 | 0.767212 | 1(Win) |
| glaze | 2856.06 | 0.420697 | 33.3746ms | 409725 | 30 | 9.93828e+06 | 136812 | 0.866588 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1836.99 | 0.35426 | 98.6244ms | 785750 | 30 | 6.26501e+07 | 407923 | 1.34756 | 1(Win) |
| jsonifier | 1426.34 | 0.240679 | 126.466ms | 785750 | 30 | 4.79645e+07 | 525365 | 1.7356 | 2(Loss) |
| glaze | 1112.68 | 0.22633 | 164.252ms | 785750 | 30 | 6.96993e+07 | 673461 | 2.2249 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4863.13 | 0.505501 | 37.6851ms | 785750 | 30 | 1.82014e+07 | 154088 | 0.508933 | 1(Win) |
| glaze | 3953.13 | 0.397246 | 45.9037ms | 785750 | 30 | 1.70109e+07 | 189559 | 0.626134 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 896.203 | 1.31912 | 2145.96ms | 8587914 | 30 | 4.35965e+11 | 9.13863e+06 | 2.76245 | 1(Win) |
| glaze STATISTICAL TIE | 760.775 | 1.22956 | 2935.9ms | 8587914 | 30 | 5.25634e+11 | 1.07654e+07 | 3.25421 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 739.953 | 0.781863 | 2511.05ms | 8587914 | 30 | 2.24672e+11 | 1.10684e+07 | 3.34572 | 2(Tie) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3060.67 | 0.486828 | 670.98ms | 8588126 | 30 | 5.09137e+09 | 2.67597e+06 | 0.808775 | 1(Win) |
| jsonifier | 2804.79 | 0.4856 | 705.239ms | 8588126 | 30 | 6.03218e+09 | 2.9201e+06 | 0.8826 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 811.822 | 1.30102 | 2723.69ms | 9804437 | 30 | 6.73621e+11 | 1.15176e+07 | 3.04961 | 1(Tie) |
| glaze STATISTICAL TIE | 787.004 | 1.05079 | 3195.31ms | 9804437 | 30 | 4.67566e+11 | 1.18808e+07 | 3.14576 | 1(Tie) |
| jsonifier STATISTICAL TIE | 774.43 | 0.93776 | 2781.83ms | 9804437 | 30 | 3.8458e+11 | 1.20737e+07 | 3.1968 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3258.27 | 0.478172 | 774.302ms | 11078090 | 30 | 7.21186e+09 | 3.24249e+06 | 0.75974 | 1(Tie) |
| glaze STATISTICAL TIE | 3248.6 | 0.655726 | 774.44ms | 11078090 | 30 | 1.36428e+10 | 3.25213e+06 | 0.762031 | 1(Tie) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 6757.39 | 1.55064 | 9.24413ms | 264040 | 30 | 1.00167e+07 | 37264.1 | 0.366098 | 1(Win) |
| jsonifier | 6330.2 | 1.82595 | 9.61492ms | 264040 | 30 | 1.58271e+07 | 39778.8 | 0.39084 | 2(Loss) |
| glaze | 1979.08 | 0.556669 | 30.712ms | 264040 | 30 | 1.50497e+07 | 127235 | 1.25073 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 8489.19 | 0.647269 | 11.0438ms | 399947 | 30 | 2.53725e+06 | 44930 | 0.291442 | 1(Tie) |
| jsonifier STATISTICAL TIE | 8451.28 | 1.02022 | 11.3043ms | 399947 | 30 | 6.36022e+06 | 45131.5 | 0.292764 | 1(Tie) |
| glaze | 2730.92 | 1.14818 | 33.6304ms | 399947 | 30 | 7.71491e+07 | 139667 | 0.906402 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1939.53 | 0.734517 | 31.4931ms | 264040 | 30 | 2.72818e+07 | 129830 | 1.27613 | 1(Win) |
| jsonifier | 1734.13 | 0.66287 | 35.8757ms | 264040 | 30 | 2.77943e+07 | 145207 | 1.42735 | 2(Loss) |
| glaze | 1581.76 | 0.966768 | 38.8915ms | 264040 | 30 | 7.10602e+07 | 159195 | 1.56488 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7706.73 | 1.47503 | 8.16963ms | 264040 | 30 | 6.96826e+06 | 32673.8 | 0.320982 | 1(Win) |
| glaze | 5000.04 | 0.548365 | 12.6885ms | 263923 | 30 | 2.28596e+06 | 50338.9 | 0.494676 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2691.96 | 0.407094 | 34.5313ms | 399947 | 30 | 9.9811e+06 | 141688 | 0.919432 | 1(Win) |
| glaze | 1937.06 | 0.447284 | 47.6526ms | 399947 | 30 | 2.32706e+07 | 196907 | 1.27789 | 2(Loss) |
| jsonifier | 1745.84 | 0.381643 | 52.7343ms | 399947 | 30 | 2.08561e+07 | 218474 | 1.41784 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7411.49 | 0.629632 | 12.9146ms | 399947 | 30 | 3.14984e+06 | 51463.2 | 0.333828 | 1(Win) |
| glaze | 5345.4 | 0.516363 | 17.5793ms | 399830 | 30 | 4.07026e+06 | 71333.8 | 0.462886 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3317.01 | 0.412725 | 31.8918ms | 466906 | 30 | 9.20888e+06 | 134240 | 0.746227 | 1(Win) |
| jsonifier | 3038.6 | 0.415903 | 35.6677ms | 466906 | 30 | 1.11434e+07 | 146540 | 0.814572 | 2(Loss) |
| simdjson (ondemand) | 1353.38 | 0.416397 | 79.007ms | 466906 | 30 | 5.6306e+07 | 329010 | 1.82907 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5321.13 | 0.616108 | 30.2218ms | 699405 | 30 | 1.78931e+07 | 125350 | 0.465109 | 1(Win) |
| glaze | 3894.07 | 0.573474 | 41.1379ms | 699405 | 30 | 2.89468e+07 | 171287 | 0.635679 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5004.34 | 0.796123 | 29.1735ms | 631514 | 30 | 2.75394e+07 | 120347 | 0.494609 | 1(Win) |
| glaze | 2751.88 | 0.321761 | 52.7562ms | 631514 | 30 | 1.48763e+07 | 218853 | 0.899562 | 2(Loss) |
