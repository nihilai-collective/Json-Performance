# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 14, 2026)
#### Using the following commits:
----
| Jsonifier: [181f2db](https://github.com/nihilai-collective/jsonifier/commit/181f2db)  
| Glaze: [b91062d](https://github.com/stephenberry/glaze/commit/b91062d)  
| Simdjson: [f9c973a](https://github.com/simdjson/simdjson/commit/f9c973a)  

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

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 561.599 | 0.120949 | 2.80731ms | 1811 | 30 | 415.057 | 3075.33 | 4.10099 | 1(Win) |
| glaze | 482.117 | 0.116974 | 1.18065ms | 1811 | 30 | 526.782 | 3582.33 | 4.78724 | 2(Loss) |
| simdjson (ondemand) | 152.719 | 0.292412 | 3.03854ms | 1811 | 30 | 32806.5 | 11309 | 15.2227 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 367.435 | 0.086389 | 1.50568ms | 1811 | 30 | 494.668 | 4700.43 | 6.29834 | 1(Win) |
| glaze | 274.259 | 0.199533 | 1.8301ms | 1798 | 30 | 4668.81 | 6252.13 | 8.45502 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1312.39 | 0.106943 | 1.07914ms | 3873 | 30 | 271.766 | 2814.4 | 1.75164 | 1(Win) |
| glaze | 985.226 | 0.103525 | 1.21974ms | 3873 | 30 | 451.895 | 3748.97 | 2.34394 | 2(Loss) |
| simdjson (ondemand) | 347.614 | 0.0624971 | 2.87799ms | 3873 | 30 | 1322.95 | 10625.5 | 6.68576 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1420.55 | 0.214845 | 1.02497ms | 3873 | 30 | 936.162 | 2600.1 | 1.61923 | 1(Win) |
| glaze | 1097.59 | 0.157354 | 1.13539ms | 3873 | 30 | 841.178 | 3365.17 | 2.09889 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1338.59 | 0.106493 | 1.05837ms | 3862 | 30 | 257.568 | 2751.47 | 1.7177 | 1(Win) |
| glaze | 786.38 | 0.0827786 | 1.43077ms | 3862 | 30 | 450.938 | 4683.6 | 2.94189 | 2(Loss) |
| simdjson (ondemand) | 353.012 | 0.0648817 | 2.84806ms | 3862 | 30 | 1374.71 | 10433.3 | 6.58322 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1605.77 | 0.141982 | 0.91821ms | 3862 | 30 | 318.161 | 2293.67 | 1.42969 | 1(Win) |
| glaze | 1040.71 | 0.156976 | 1.17995ms | 3862 | 30 | 925.862 | 3539 | 2.21694 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 564.741 | 0.136245 | 0.751049ms | 905 | 30 | 130.064 | 1528.27 | 4.0274 | 1(Win) |
| glaze | 441.802 | 0.18617 | 0.779565ms | 905 | 30 | 396.809 | 1953.53 | 5.18074 | 2(Loss) |
| simdjson (ondemand) | 116.866 | 0.0725864 | 2.10042ms | 905 | 30 | 862.097 | 7385.2 | 19.8572 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 682.417 | 0.246968 | 0.665241ms | 905 | 30 | 292.685 | 1264.73 | 3.32258 | 1(Win) |
| glaze | 289.639 | 0.134015 | 1.02986ms | 905 | 30 | 478.42 | 2979.83 | 7.9474 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1826.17 | 0.0543362 | 3.52289ms | 9578 | 32 | 236.371 | 5001.88 | 1.26708 | 1(Win) |
| glaze | 1441.84 | 0.102444 | 1.876ms | 9578 | 30 | 1263.59 | 6335.17 | 1.60732 | 2(Loss) |
| simdjson (ondemand) | 785.444 | 0.0674139 | 3.1516ms | 9578 | 30 | 1843.91 | 11629.5 | 2.95954 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3251.45 | 0.164386 | 1.10028ms | 9578 | 30 | 639.803 | 2809.3 | 0.707931 | 1(Win) |
| glaze | 2195.06 | 0.198238 | 1.30858ms | 9578 | 30 | 2041.53 | 4161.3 | 1.05268 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2775.92 | 0.544601 | 19.797ms | 233995 | 30 | 5.75012e+06 | 80389.5 | 0.83954 | 1(Win) |
| simdjson (ondemand) | 2624.1 | 0.660837 | 20.8497ms | 233995 | 30 | 9.47463e+06 | 85040.5 | 0.888158 | 2(Loss) |
| glaze | 1460.74 | 0.433485 | 37.107ms | 233995 | 30 | 1.31564e+07 | 152768 | 1.59603 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3496.54 | 0.665808 | 23.1224ms | 346753 | 30 | 1.18955e+07 | 94576.2 | 0.666531 | 1(Win) |
| simdjson (ondemand) | 3268.96 | 0.898922 | 24.3975ms | 346753 | 30 | 2.48077e+07 | 101160 | 0.713053 | 2(Loss) |
| glaze | 1816.78 | 0.405668 | 44.4459ms | 346753 | 30 | 1.63568e+07 | 182020 | 1.28331 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1276.34 | 0.440667 | 42.8111ms | 233995 | 30 | 1.78084e+07 | 174840 | 1.82659 | 1(Win) |
| glaze | 947.746 | 0.415356 | 58.3948ms | 233995 | 30 | 2.8694e+07 | 235459 | 2.46005 | 2(Loss) |
| simdjson (ondemand) | 838.621 | 0.580286 | 69.6255ms | 233995 | 30 | 7.15298e+07 | 266098 | 2.78014 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2124.65 | 0.580941 | 25.9914ms | 233995 | 30 | 1.11693e+07 | 105032 | 1.09709 | 1(Win) |
| glaze | 1884.83 | 0.73489 | 29.3311ms | 233995 | 30 | 2.2711e+07 | 118395 | 1.23666 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1258.75 | 0.350197 | 64.0169ms | 346753 | 30 | 2.53925e+07 | 262712 | 1.85218 | 1(Win) |
| glaze | 1217.83 | 0.342758 | 66.1805ms | 346753 | 30 | 2.59874e+07 | 271540 | 1.91442 | 2(Loss) |
| simdjson (ondemand) | 1178.3 | 0.694159 | 67.5758ms | 346753 | 30 | 1.13859e+08 | 280649 | 1.97873 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1989.86 | 0.689066 | 40.5479ms | 346753 | 30 | 3.93403e+07 | 166187 | 1.17148 | 1(Win) |
| glaze | 1647.54 | 0.589698 | 50.1612ms | 346753 | 30 | 4.20292e+07 | 200718 | 1.41506 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2736.84 | 0.803137 | 19.8967ms | 233995 | 30 | 1.28652e+07 | 81537.6 | 0.851504 | 1(Win) |
| simdjson (ondemand) | 1961.82 | 0.581588 | 27.6036ms | 233995 | 30 | 1.31294e+07 | 113749 | 1.18821 | 2(Loss) |
| glaze | 1441.88 | 0.508606 | 37.5149ms | 233995 | 30 | 1.85883e+07 | 154767 | 1.61694 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3423.51 | 0.605582 | 23.7174ms | 346753 | 30 | 1.02651e+07 | 96593.7 | 0.680768 | 1(Win) |
| simdjson (ondemand) | 2587.64 | 0.571124 | 30.9593ms | 346753 | 30 | 1.59814e+07 | 127796 | 0.900855 | 2(Loss) |
| glaze | 1796.83 | 0.380134 | 44.7423ms | 346753 | 30 | 1.46832e+07 | 184040 | 1.29752 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1142.72 | 0.419524 | 48.0591ms | 233995 | 30 | 2.01358e+07 | 195284 | 2.04021 | 1(Win) |
| glaze | 932.666 | 0.383983 | 57.874ms | 233995 | 30 | 2.53225e+07 | 239266 | 2.5 | 2(Loss) |
| simdjson (ondemand) | 222.327 | 0.192694 | 241.69ms | 233995 | 30 | 1.12225e+08 | 1.00373e+06 | 10.4887 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2130.81 | 0.728712 | 25.5429ms | 233995 | 30 | 1.74726e+07 | 104728 | 1.09387 | 1(Win) |
| glaze | 1883.95 | 0.900805 | 28.2624ms | 233995 | 30 | 3.41552e+07 | 118450 | 1.23721 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1275.85 | 0.351939 | 63.2257ms | 346753 | 30 | 2.49629e+07 | 259191 | 1.82747 | 1(Win) |
| jsonifier | 1215.96 | 0.292167 | 66.2801ms | 346753 | 30 | 1.89403e+07 | 271958 | 1.91744 | 2(Loss) |
| simdjson (ondemand) | 325.319 | 0.0923602 | 245.283ms | 346753 | 30 | 2.64432e+07 | 1.01651e+06 | 7.16798 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2155.75 | 0.644026 | 37.4997ms | 346753 | 30 | 2.92801e+07 | 153399 | 1.08131 | 1(Win) |
| glaze | 1621 | 0.613079 | 49.6387ms | 346753 | 30 | 4.69279e+07 | 204004 | 1.43824 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 648.551 | 0.506546 | 34.0892ms | 94651 | 30 | 1.49115e+07 | 139181 | 3.59479 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 617.311 | 0.588146 | 35.4278ms | 94651 | 30 | 2.21888e+07 | 146225 | 3.77676 | 2(Tie) |
| glaze STATISTICAL TIE | 607.009 | 1.90823 | 35.5114ms | 94651 | 30 | 2.4157e+08 | 148707 | 3.84066 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2791.43 | 1.20135 | 8.11763ms | 94651 | 30 | 4.52749e+06 | 32336.9 | 0.834371 | 1(Tie) |
| glaze STATISTICAL TIE | 2712.04 | 1.02166 | 8.46396ms | 94651 | 30 | 3.4689e+06 | 33283.6 | 0.858513 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 866.655 | 0.567201 | 36.5974ms | 136024 | 30 | 2.16239e+07 | 149682 | 2.69004 | 1(Win) |
| jsonifier | 811.333 | 0.390971 | 39.0602ms | 136024 | 30 | 1.17231e+07 | 159888 | 2.87364 | 2(Loss) |
| glaze | 737.993 | 0.360917 | 43.0226ms | 136024 | 30 | 1.20743e+07 | 175778 | 3.15919 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3311.97 | 1.31884 | 9.85103ms | 136024 | 30 | 8.00503e+06 | 39167.8 | 0.703398 | 1(Win) |
| glaze | 1803.23 | 0.833174 | 17.6834ms | 136046 | 30 | 1.07811e+07 | 71950.8 | 1.29229 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 455.418 | 0.155024 | 1053.15ms | 2090234 | 30 | 1.3813e+09 | 4.37708e+06 | 5.1208 | 1(Win) |
| glaze | 385.038 | 0.133171 | 1245.2ms | 2090234 | 30 | 1.42601e+09 | 5.17716e+06 | 6.05685 | 2(Loss) |
| simdjson (ondemand) | 304.674 | 0.129142 | 1571.34ms | 2090234 | 30 | 2.14179e+09 | 6.54274e+06 | 7.6545 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 662.94 | 0.0946691 | 721.392ms | 2090234 | 30 | 2.43097e+08 | 3.00691e+06 | 3.51776 | 1(Win) |
| glaze | 653.786 | 0.0759388 | 734.477ms | 2090234 | 30 | 1.6083e+08 | 3.04901e+06 | 3.56705 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1148.57 | 0.0781272 | 1333.46ms | 6661897 | 30 | 5.60282e+08 | 5.53147e+06 | 2.03045 | 1(Win) |
| glaze | 981.02 | 0.175232 | 1560.17ms | 6661897 | 30 | 3.86357e+09 | 6.4762e+06 | 2.37722 | 2(Loss) |
| simdjson (ondemand) | 913.428 | 0.122319 | 1672.35ms | 6661897 | 30 | 2.17148e+09 | 6.95543e+06 | 2.55311 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1862.63 | 0.219268 | 824.018ms | 6661897 | 30 | 1.67809e+09 | 3.41092e+06 | 1.25202 | 1(Win) |
| glaze | 1428.37 | 0.211821 | 1074.56ms | 6661897 | 30 | 2.663e+09 | 4.44792e+06 | 1.63259 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1006.88 | 0.325913 | 114.313ms | 500299 | 30 | 7.15531e+07 | 473863 | 2.31589 | 1(Win) |
| glaze | 845.109 | 0.189615 | 136.207ms | 500299 | 30 | 3.43798e+07 | 564569 | 2.75929 | 2(Loss) |
| simdjson (ondemand) | 513.879 | 0.0860264 | 223.669ms | 500299 | 30 | 1.91392e+07 | 928473 | 4.53804 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2001.74 | 0.372415 | 58.2173ms | 500299 | 30 | 2.36385e+07 | 238354 | 1.16477 | 1(Win) |
| jsonifier | 1795.95 | 0.505191 | 64.7031ms | 500299 | 30 | 5.40386e+07 | 265666 | 1.29825 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1665.03 | 0.372719 | 198.45ms | 1439562 | 30 | 2.83335e+08 | 824532 | 1.40051 | 1(Win) |
| glaze | 1469.92 | 1.45973 | 219.613ms | 1439562 | 30 | 5.57625e+09 | 933979 | 1.58641 | 2(Loss) |
| simdjson (ondemand) | 1327.39 | 0.210605 | 248.481ms | 1439562 | 30 | 1.42339e+08 | 1.03427e+06 | 1.75682 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3272.44 | 0.509997 | 103.592ms | 1439562 | 30 | 1.37332e+08 | 419526 | 0.712505 | 1(Win) |
| glaze | 2097.35 | 0.192952 | 160.557ms | 1439584 | 30 | 4.78577e+07 | 654585 | 1.11183 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 935.236 | 1.0247 | 14.4072ms | 56369 | 30 | 1.04078e+07 | 57480.3 | 2.49181 | 1(Win) |
| glaze | 801.852 | 0.774277 | 16.6953ms | 56369 | 30 | 8.08363e+06 | 67041.9 | 2.90677 | 2(Loss) |
| simdjson (ondemand) | 657.815 | 0.828202 | 19.9268ms | 56369 | 30 | 1.37426e+07 | 81721.6 | 3.54359 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1983.4 | 1.19398 | 6.86694ms | 56369 | 30 | 3.14174e+06 | 27103.7 | 1.17419 | 1(Win) |
| jsonifier | 1691.94 | 0.952458 | 8.00481ms | 56369 | 30 | 2.74742e+06 | 31772.8 | 1.37681 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1083.25 | 0.748945 | 20.5715ms | 94370 | 30 | 1.16153e+07 | 83081.5 | 2.15138 | 1(Tie) |
| glaze STATISTICAL TIE | 1077.82 | 0.842248 | 20.5986ms | 94370 | 30 | 1.48381e+07 | 83500.5 | 2.16244 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1066.13 | 0.683869 | 20.8716ms | 94370 | 30 | 9.99805e+06 | 84415.9 | 2.18644 | 1(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2524.25 | 1.21104 | 9.02929ms | 94370 | 30 | 5.59294e+06 | 35653.5 | 0.922936 | 1(Win) |
| glaze | 1747.53 | 1.14925 | 12.6937ms | 94370 | 30 | 1.05092e+07 | 51500.2 | 1.33335 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 846.057 | 0.935277 | 15.1526ms | 52708 | 30 | 9.26309e+06 | 59412.4 | 2.7541 | 1(Win) |
| jsonifier | 776.534 | 1.11241 | 16.487ms | 52708 | 30 | 1.55554e+07 | 64731.6 | 2.99893 | 2(Loss) |
| glaze | 712.069 | 0.87068 | 17.6713ms | 52708 | 30 | 1.1333e+07 | 70591.8 | 3.27257 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2597.47 | 0.159732 | 5.13234ms | 52708 | 30 | 28665.3 | 19352 | 0.896076 | 1(Tie) |
| glaze STATISTICAL TIE | 2583.78 | 1.84061 | 5.04085ms | 52708 | 30 | 3.8467e+06 | 19454.5 | 0.900708 | 1(Tie) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1076.82 | 1.02382 | 15.6419ms | 70103 | 30 | 1.21215e+07 | 62085.9 | 2.16396 | 1(Win) |
| glaze | 806.557 | 1.01226 | 20.5015ms | 70103 | 30 | 2.11208e+07 | 82889.9 | 2.88953 | 2(Loss) |
| jsonifier | 701.789 | 1.30228 | 53.9122ms | 70103 | 32 | 4.92516e+07 | 95264.3 | 3.31861 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2951.74 | 0.137978 | 5.92865ms | 70103 | 30 | 29299.4 | 22649.5 | 0.788639 | 1(Win) |
| glaze | 2428.72 | 1.14638 | 7.12723ms | 70103 | 30 | 2.98744e+06 | 27527 | 0.958944 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 729.598 | 0.0578435 | 4.16977ms | 11812 | 30 | 2392.82 | 15439.7 | 3.18897 | 1(Win) |
| glaze | 586.734 | 0.273624 | 5.13827ms | 11812 | 30 | 82792.9 | 19199.2 | 3.96725 | 2(Loss) |
| simdjson (ondemand) | 542.075 | 1.20708 | 12.2364ms | 11812 | 32 | 2.01351e+06 | 20780.9 | 4.29508 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2550.94 | 0.171742 | 1.35361ms | 11812 | 30 | 1725.51 | 4415.93 | 0.906685 | 1(Win) |
| glaze | 1224.99 | 0.335897 | 2.53113ms | 11812 | 30 | 28622.8 | 9195.8 | 1.89606 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1304.63 | 1.37987 | 5.80105ms | 31235 | 30 | 2.97786e+06 | 22832.5 | 1.78482 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1281.07 | 1.24225 | 5.97081ms | 31235 | 30 | 2.50308e+06 | 23252.4 | 1.81763 | 1(Tie) |
| glaze | 1095.52 | 1.05648 | 6.88458ms | 31235 | 30 | 2.47563e+06 | 27190.8 | 2.12605 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2909.26 | 0.114952 | 2.86266ms | 31235 | 30 | 4155.96 | 10239 | 0.798888 | 1(Win) |
| glaze | 1967.37 | 1.80036 | 3.92474ms | 31235 | 30 | 2.22919e+06 | 15141 | 1.18247 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1803.1 | 1.0306 | 14.2338ms | 108313 | 30 | 1.04573e+07 | 57287.6 | 1.29246 | 1(Win) |
| glaze | 1009.88 | 0.762675 | 25.0408ms | 108313 | 30 | 1.82568e+07 | 102285 | 2.30817 | 2(Loss) |
| simdjson (ondemand) | 797.895 | 0.550242 | 31.6159ms | 108313 | 30 | 1.52229e+07 | 129460 | 2.92188 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1875.44 | 1.10187 | 13.5499ms | 108313 | 30 | 1.10494e+07 | 55078 | 1.24269 | 1(Win) |
| glaze | 1744.46 | 0.989887 | 14.5387ms | 108313 | 30 | 1.0307e+07 | 59213.4 | 1.33584 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1497.58 | 0.705875 | 33.209ms | 213963 | 30 | 2.77506e+07 | 136254 | 1.55658 | 1(Tie) |
| glaze STATISTICAL TIE | 1463.06 | 1.78717 | 33.6995ms | 213963 | 30 | 1.86383e+08 | 139469 | 1.59328 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1428.17 | 1.05717 | 34.4492ms | 213963 | 30 | 6.84431e+07 | 142876 | 1.63228 | 1(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2257.84 | 0.687493 | 22.1358ms | 213963 | 30 | 1.1581e+07 | 90374.4 | 1.0323 | 1(Win) |
| glaze | 1639.56 | 0.628455 | 30.0236ms | 213963 | 30 | 1.83524e+07 | 124455 | 1.42168 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 464.323 | 0.185819 | 903.286ms | 1834197 | 30 | 1.47013e+09 | 3.76726e+06 | 5.02254 | 1(Win) |
| glaze | 352.996 | 0.0948713 | 1190.45ms | 1834197 | 30 | 6.63048e+08 | 4.95538e+06 | 6.60657 | 2(Loss) |
| simdjson (ondemand) | 271.262 | 0.0835841 | 1555.69ms | 1834197 | 30 | 8.71529e+08 | 6.44847e+06 | 8.5972 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 389.392 | 0.0606582 | 1076.56ms | 1833577 | 30 | 2.226e+08 | 4.49068e+06 | 5.989 | 1(Win) |
| jsonifier | 386.988 | 0.0445598 | 1087.74ms | 1834197 | 30 | 1.21704e+08 | 4.5201e+06 | 6.02625 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1482.03 | 0.574615 | 1526.9ms | 9930848 | 30 | 4.04516e+10 | 6.39044e+06 | 1.57354 | 1(Win) |
| glaze | 1332.85 | 0.0950298 | 1708.36ms | 9930848 | 30 | 1.36789e+09 | 7.10566e+06 | 1.74969 | 2(Loss) |
| simdjson (ondemand) | 1304 | 0.168578 | 1741.27ms | 9930848 | 30 | 4.49717e+09 | 7.26286e+06 | 1.78837 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1548.6 | 0.277012 | 1465.99ms | 9930848 | 30 | 8.61012e+09 | 6.11569e+06 | 1.50587 | 1(Win) |
| glaze | 1269.23 | 0.145776 | 1795.43ms | 9930228 | 30 | 3.54917e+09 | 7.46136e+06 | 1.83732 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 833.999 | 0.316523 | 176.917ms | 642697 | 30 | 1.62335e+08 | 734921 | 2.79611 | 1(Win) |
| glaze | 661.455 | 0.240498 | 222.516ms | 642697 | 30 | 1.48989e+08 | 926630 | 3.52554 | 2(Loss) |
| simdjson (ondemand) | 498.714 | 0.0998204 | 296.208ms | 642697 | 30 | 4.51511e+07 | 1.22901e+06 | 4.67606 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 679.371 | 0.570733 | 213.738ms | 642697 | 30 | 7.95402e+08 | 902193 | 3.4324 | 1(Win) |
| glaze | 611.559 | 0.419091 | 240.82ms | 642692 | 30 | 5.29257e+08 | 1.00222e+06 | 3.81317 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1199.81 | 0.111928 | 234.841ms | 1225964 | 30 | 3.56884e+07 | 974461 | 1.94362 | 1(Win) |
| glaze | 1008.75 | 0.231638 | 278.788ms | 1225964 | 30 | 2.16238e+08 | 1.15903e+06 | 2.31179 | 2(Loss) |
| simdjson (ondemand) | 905.916 | 0.312532 | 309.445ms | 1225964 | 30 | 4.88079e+08 | 1.29059e+06 | 2.5742 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1226.09 | 0.188519 | 230.492ms | 1225964 | 30 | 9.69484e+07 | 953576 | 1.90189 | 1(Win) |
| glaze | 1009.49 | 0.203992 | 277.263ms | 1225970 | 30 | 1.67456e+08 | 1.15818e+06 | 2.31008 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 584.275 | 0.435852 | 160.549ms | 409725 | 30 | 2.54888e+08 | 668768 | 3.99115 | 1(Win) |
| simdjson (ondemand) | 494.837 | 0.117462 | 190.393ms | 409725 | 30 | 2.58093e+07 | 789642 | 4.71267 | 2(Loss) |
| glaze | 414.423 | 0.279171 | 227.128ms | 409725 | 30 | 2.07855e+08 | 942864 | 5.62708 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1343.91 | 0.485014 | 70.8506ms | 409725 | 30 | 5.96588e+07 | 290752 | 1.73501 | 1(Win) |
| jsonifier | 1213.33 | 0.409261 | 77.4512ms | 409725 | 30 | 5.21136e+07 | 322044 | 1.92166 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 897.807 | 0.114043 | 201.217ms | 785750 | 30 | 2.71809e+07 | 834645 | 2.59745 | 1(Win) |
| jsonifier | 790.913 | 0.0700027 | 228.76ms | 785750 | 30 | 1.31966e+07 | 947448 | 2.94843 | 2(Loss) |
| glaze | 615.956 | 0.102928 | 291.19ms | 785750 | 30 | 4.70395e+07 | 1.21656e+06 | 3.78604 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1847.47 | 0.340586 | 98.5233ms | 785750 | 30 | 5.72515e+07 | 405608 | 1.26212 | 1(Win) |
| glaze | 1590.43 | 0.315568 | 114.846ms | 785750 | 30 | 6.63204e+07 | 471161 | 1.46618 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 669.537 | 0.552741 | 2945.38ms | 8587914 | 30 | 1.37148e+11 | 1.22324e+07 | 3.48311 | 1(Win) |
| simdjson (ondemand) | 570.764 | 0.457759 | 3446.01ms | 8587914 | 30 | 1.29437e+11 | 1.43493e+07 | 4.08585 | 2(Loss) |
| glaze | 552.597 | 0.667388 | 3550.49ms | 8587914 | 30 | 2.93519e+11 | 1.4821e+07 | 4.22022 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2034.03 | 0.255597 | 967.313ms | 8588126 | 30 | 3.17771e+09 | 4.02662e+06 | 1.14645 | 1(Win) |
| jsonifier | 1963.48 | 0.290574 | 1001.98ms | 8588126 | 30 | 4.40736e+09 | 4.17131e+06 | 1.18764 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 643.013 | 0.840008 | 3473.51ms | 9804437 | 30 | 4.47605e+11 | 1.45413e+07 | 3.62678 | 1(Win) |
| simdjson (ondemand) | 613.219 | 0.591289 | 3494.02ms | 9804437 | 30 | 2.43856e+11 | 1.52478e+07 | 3.80295 | 2(Loss) |
| glaze | 556.688 | 0.594937 | 4038.9ms | 9804437 | 30 | 2.99561e+11 | 1.67962e+07 | 4.18918 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2208.9 | 0.191263 | 1159.55ms | 11078090 | 30 | 2.5105e+09 | 4.78287e+06 | 1.05572 | 1(Win) |
| glaze | 1982.13 | 0.208265 | 1281.69ms | 11078090 | 30 | 3.69675e+09 | 5.33006e+06 | 1.17653 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2781.17 | 0.640612 | 22.2314ms | 264040 | 30 | 1.00924e+07 | 90540.3 | 0.838079 | 1(Win) |
| simdjson (ondemand) | 2647.87 | 0.740175 | 23.1597ms | 264040 | 30 | 1.4864e+07 | 95098.4 | 0.880231 | 2(Loss) |
| glaze | 1104.19 | 0.445366 | 55.285ms | 264040 | 30 | 3.09462e+07 | 228048 | 2.11163 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3595.48 | 0.544554 | 25.9839ms | 399947 | 30 | 1.00114e+07 | 106083 | 0.648254 | 1(Win) |
| simdjson (ondemand) | 3528.43 | 0.628547 | 26.4446ms | 399947 | 30 | 1.38496e+07 | 108099 | 0.660599 | 2(Loss) |
| glaze | 1506.06 | 0.399938 | 61.2135ms | 399947 | 30 | 3.07772e+07 | 253257 | 1.54802 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 953.743 | 0.41376 | 64.9903ms | 264040 | 30 | 3.5801e+07 | 264021 | 2.44438 | 1(Win) |
| simdjson (ondemand) | 868.383 | 0.382016 | 71.9043ms | 264040 | 30 | 3.68131e+07 | 289974 | 2.68502 | 2(Loss) |
| glaze | 818.4 | 0.371034 | 74.9826ms | 264040 | 30 | 3.90982e+07 | 307683 | 2.84909 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2387.47 | 0.677385 | 69.525ms | 264040 | 32 | 1.63337e+07 | 105471 | 0.976314 | 1(Win) |
| glaze | 2199.04 | 0.594415 | 28.1654ms | 263923 | 30 | 1.38864e+07 | 114458 | 1.05995 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1222.63 | 0.328921 | 77.5365ms | 399947 | 30 | 3.15877e+07 | 311966 | 1.90709 | 1(Win) |
| glaze | 1021.46 | 0.307563 | 91.2178ms | 399947 | 30 | 3.95688e+07 | 373406 | 2.28274 | 2(Loss) |
| jsonifier | 976.281 | 0.407073 | 95.7725ms | 399947 | 30 | 7.5879e+07 | 390686 | 2.38845 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2909.09 | 0.607073 | 31.8087ms | 399947 | 30 | 1.90062e+07 | 131113 | 0.801187 | 1(Win) |
| glaze | 2150.71 | 0.526002 | 42.8873ms | 399830 | 30 | 2.60906e+07 | 177294 | 1.08396 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1403.22 | 0.320536 | 76.3627ms | 466906 | 30 | 3.10374e+07 | 317325 | 1.6617 | 1(Win) |
| jsonifier | 1218.31 | 0.326765 | 87.8838ms | 466906 | 30 | 4.27896e+07 | 365488 | 1.91381 | 2(Loss) |
| simdjson (ondemand) | 639.501 | 0.167981 | 167.911ms | 466906 | 30 | 4.10409e+07 | 696287 | 3.6464 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1938.64 | 0.378392 | 84.8247ms | 699405 | 30 | 5.08472e+07 | 344058 | 1.20268 | 1(Win) |
| glaze | 1831.85 | 0.539533 | 87.6902ms | 699405 | 30 | 1.15781e+08 | 364116 | 1.27293 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2311.01 | 0.350438 | 63.2564ms | 631514 | 30 | 2.5021e+07 | 260604 | 1.00897 | 1(Win) |
| glaze | 1460.92 | 0.21989 | 99.4545ms | 631514 | 30 | 2.46516e+07 | 412245 | 1.59617 | 2(Loss) |
