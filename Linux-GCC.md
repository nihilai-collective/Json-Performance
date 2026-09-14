# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 14, 2026)
#### Using the following commits:
----
| Jsonifier: [fde86fb](https://github.com/nihilai-collective/jsonifier/commit/fde86fb)  
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

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 662.622 | 0.0938139 | 4.73406ms | 1811 | 64 | 382.666 | 2606.47 | 3.4713 | 1(Win) |
| glaze | 464.619 | 0.121574 | 2.55519ms | 1811 | 32 | 653.548 | 3717.25 | 4.96911 | 2(Loss) |
| simdjson (ondemand) | 135.244 | 2.09616 | 3.31346ms | 1811 | 30 | 2.14968e+06 | 12770.3 | 17.1956 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 399.302 | 0.0844475 | 2.82296ms | 1811 | 32 | 426.931 | 4325.31 | 5.79062 | 1(Win) |
| glaze | 254.37 | 0.409398 | 1.81419ms | 1798 | 30 | 22848.7 | 6741 | 9.11418 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1249.55 | 0.591089 | 1.06286ms | 3873 | 30 | 9158.34 | 2955.93 | 1.84254 | 1(Win) |
| glaze | 1092.39 | 0.0784791 | 2.37335ms | 3873 | 32 | 225.319 | 3381.19 | 2.11165 | 2(Loss) |
| simdjson (ondemand) | 304.205 | 0.159923 | 3.18891ms | 3873 | 30 | 11311.2 | 12141.8 | 7.64348 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1361.02 | 0.0527685 | 0.885129ms | 3873 | 30 | 61.523 | 2713.83 | 1.69073 | 1(Win) |
| glaze | 984.52 | 2.13825 | 2.62628ms | 3873 | 32 | 205927 | 3751.66 | 2.34672 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1132.52 | 0.0684835 | 1.03033ms | 3862 | 30 | 148.809 | 3252.13 | 2.03639 | 1(Win) |
| glaze | 962.69 | 0.0874755 | 1.10843ms | 3862 | 30 | 336.006 | 3825.83 | 2.39904 | 2(Loss) |
| simdjson (ondemand) | 302.655 | 0.0622362 | 3.11505ms | 3862 | 30 | 1720.82 | 12169.3 | 7.68156 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1643.14 | 0.122855 | 0.809757ms | 3862 | 30 | 227.5 | 2241.5 | 1.39609 | 1(Win) |
| glaze | 844.771 | 0.137666 | 1.21573ms | 3862 | 30 | 1080.74 | 4359.87 | 2.73761 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 765.567 | 0.206541 | 0.500859ms | 905 | 30 | 162.654 | 1127.37 | 2.94818 | 1(Win) |
| glaze | 425.195 | 0.110086 | 0.673572ms | 905 | 30 | 149.799 | 2029.83 | 5.38471 | 2(Loss) |
| simdjson (ondemand) | 98.9746 | 0.0793591 | 2.27535ms | 905 | 30 | 1436.7 | 8720.17 | 23.4685 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 805.032 | 0.128247 | 0.463499ms | 905 | 30 | 56.7138 | 1072.1 | 2.80273 | 1(Win) |
| glaze | 247.711 | 0.146408 | 1.01065ms | 905 | 30 | 780.648 | 3484.2 | 9.31263 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1701.4 | 0.0716528 | 1.64304ms | 9578 | 30 | 443.941 | 5368.7 | 1.36169 | 1(Win) |
| glaze | 1298.95 | 0.055676 | 2.01352ms | 9578 | 30 | 459.857 | 7032.07 | 1.78605 | 2(Loss) |
| simdjson (ondemand) | 686.897 | 0.0794666 | 3.39949ms | 9578 | 30 | 3350.09 | 13297.9 | 3.38619 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2778.49 | 0.087016 | 0.975929ms | 9578 | 30 | 245.5 | 3287.5 | 0.830229 | 1(Win) |
| glaze | 2320.98 | 0.129252 | 1.20846ms | 9578 | 30 | 776.257 | 3935.53 | 0.995479 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2496.19 | 1.984 | 21.5182ms | 233995 | 30 | 9.43763e+07 | 89398.2 | 0.93375 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2444.45 | 0.60909 | 22.2369ms | 233995 | 30 | 9.27548e+06 | 91290.6 | 0.953607 | 1(Tie) |
| glaze | 1277.64 | 0.64478 | 47.0382ms | 233995 | 30 | 3.80487e+07 | 174662 | 1.82489 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3130.68 | 1.09699 | 26.4328ms | 346753 | 30 | 4.02801e+07 | 105629 | 0.744506 | 1(Win) |
| jsonifier | 2754.77 | 0.740948 | 29.5195ms | 346753 | 30 | 2.37338e+07 | 120043 | 0.846165 | 2(Loss) |
| glaze | 1596.45 | 0.477764 | 50.1568ms | 346753 | 30 | 2.93819e+07 | 207141 | 1.46043 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1085.83 | 0.643196 | 50.1678ms | 233995 | 30 | 5.24201e+07 | 205516 | 2.1471 | 1(Win) |
| glaze | 920.934 | 0.344635 | 58.7387ms | 233995 | 30 | 2.09217e+07 | 242314 | 2.53178 | 2(Loss) |
| simdjson (ondemand) | 866.174 | 0.601975 | 62.8547ms | 233995 | 30 | 7.21574e+07 | 257633 | 2.69174 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2134.56 | 0.81763 | 25.6859ms | 233995 | 30 | 2.19195e+07 | 104544 | 1.09189 | 1(Win) |
| glaze | 1880.55 | 0.609948 | 28.8695ms | 233995 | 30 | 1.57164e+07 | 118665 | 1.23948 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1213.67 | 0.421842 | 65.9897ms | 346753 | 30 | 3.9633e+07 | 272470 | 1.9211 | 1(Tie) |
| glaze STATISTICAL TIE | 1205.5 | 0.326427 | 66.3867ms | 346753 | 30 | 2.40548e+07 | 274318 | 1.93414 | 1(Tie) |
| jsonifier | 905.453 | 0.490851 | 88.3005ms | 346753 | 30 | 9.64116e+07 | 365220 | 2.57511 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2232.93 | 0.714625 | 35.7487ms | 346753 | 30 | 3.36023e+07 | 148097 | 1.04374 | 1(Win) |
| glaze | 1789.66 | 0.69092 | 44.686ms | 346753 | 30 | 4.88964e+07 | 184778 | 1.30264 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2492.63 | 1.73962 | 21.6976ms | 233995 | 30 | 7.27659e+07 | 89525.8 | 0.934981 | 1(Win) |
| simdjson (ondemand) | 1686.06 | 0.728082 | 32.1471ms | 233995 | 30 | 2.78579e+07 | 132353 | 1.38262 | 2(Loss) |
| glaze | 1281.71 | 0.598436 | 41.9292ms | 233995 | 30 | 3.25681e+07 | 174108 | 1.81914 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2729.81 | 0.891567 | 29.5322ms | 346753 | 30 | 3.4995e+07 | 121140 | 0.853858 | 1(Win) |
| simdjson (ondemand) | 2237.06 | 0.591392 | 35.9541ms | 346753 | 30 | 2.29275e+07 | 147823 | 1.04204 | 2(Loss) |
| glaze | 1594.37 | 0.385522 | 50.4928ms | 346753 | 30 | 1.91814e+07 | 207411 | 1.4624 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1003.66 | 0.341221 | 54.2756ms | 233995 | 30 | 1.72675e+07 | 222341 | 2.32299 | 1(Win) |
| jsonifier | 955.279 | 0.584728 | 56.8418ms | 233995 | 30 | 5.59733e+07 | 233602 | 2.44067 | 2(Loss) |
| simdjson (ondemand) | 187.167 | 0.366618 | 286.575ms | 233995 | 30 | 5.73193e+08 | 1.19228e+06 | 12.4593 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2248.67 | 1.07978 | 24.2555ms | 233995 | 30 | 3.44475e+07 | 99238.9 | 1.03649 | 1(Win) |
| glaze | 1827.87 | 0.737093 | 29.4212ms | 233995 | 30 | 2.42935e+07 | 122085 | 1.2752 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1189.77 | 0.510956 | 67.269ms | 346753 | 30 | 6.05061e+07 | 277943 | 1.95968 | 1(Win) |
| jsonifier | 914.004 | 0.478885 | 87.4634ms | 346753 | 30 | 9.00591e+07 | 361803 | 2.55106 | 2(Loss) |
| simdjson (ondemand) | 272.811 | 0.295492 | 291.143ms | 346753 | 30 | 3.84884e+08 | 1.21216e+06 | 8.54803 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2533.45 | 0.786231 | 31.7122ms | 346753 | 30 | 3.15964e+07 | 130529 | 0.919939 | 1(Win) |
| glaze | 1707.45 | 0.589237 | 46.8108ms | 346753 | 30 | 3.90702e+07 | 193674 | 1.36541 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 674.793 | 0.694967 | 32.4818ms | 94651 | 30 | 2.59274e+07 | 133769 | 3.45453 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 666.431 | 0.681318 | 32.751ms | 94651 | 30 | 2.55483e+07 | 135447 | 3.49784 | 1(Tie) |
| jsonifier | 628.861 | 0.46792 | 35.3743ms | 94651 | 30 | 1.35333e+07 | 143539 | 3.70733 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2848.23 | 1.54938 | 8.40092ms | 94651 | 30 | 7.23334e+06 | 31692 | 0.817504 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2833.72 | 1.46868 | 7.86053ms | 94651 | 30 | 6.56617e+06 | 31854.3 | 0.821835 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 928.521 | 0.698949 | 34.1021ms | 136024 | 30 | 2.86062e+07 | 139709 | 2.51057 | 1(Win) |
| glaze | 810.585 | 0.564359 | 38.9506ms | 136024 | 30 | 2.44718e+07 | 160036 | 2.87605 | 2(Loss) |
| jsonifier | 689.298 | 0.500943 | 45.8497ms | 136024 | 30 | 2.66633e+07 | 188195 | 3.38238 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3328.26 | 1.29775 | 9.61218ms | 136024 | 30 | 7.6754e+06 | 38976.1 | 0.699586 | 1(Win) |
| glaze | 1647.9 | 0.973916 | 19.2846ms | 136046 | 30 | 1.76389e+07 | 78732.5 | 1.41399 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 447.315 | 0.08289 | 1070.53ms | 2090234 | 30 | 4.09345e+08 | 4.45638e+06 | 5.2135 | 1(Win) |
| glaze | 358.569 | 0.0936489 | 1333.97ms | 2090234 | 30 | 8.1315e+08 | 5.55933e+06 | 6.50389 | 2(Loss) |
| simdjson (ondemand) | 356.654 | 0.163903 | 1341.62ms | 2090234 | 30 | 2.51763e+09 | 5.58918e+06 | 6.53875 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 882.428 | 0.59971 | 539.481ms | 2090234 | 30 | 5.50599e+09 | 2.259e+06 | 2.64275 | 1(Win) |
| glaze | 739.95 | 0.0656707 | 649.795ms | 2090234 | 30 | 9.38966e+07 | 2.69397e+06 | 3.15166 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1059.52 | 0.115714 | 1440.12ms | 6661897 | 30 | 1.44433e+09 | 5.99635e+06 | 2.20107 | 1(Win) |
| jsonifier | 1000.39 | 0.0890704 | 1535.5ms | 6661897 | 30 | 9.59949e+08 | 6.35082e+06 | 2.33119 | 2(Loss) |
| glaze | 843.979 | 0.484339 | 1805.55ms | 6661897 | 30 | 3.98798e+10 | 7.52777e+06 | 2.76322 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2109.95 | 0.073835 | 723.591ms | 6661897 | 30 | 1.48285e+08 | 3.01111e+06 | 1.10527 | 1(Win) |
| glaze | 1635.83 | 0.0722669 | 938.845ms | 6661897 | 30 | 2.36331e+08 | 3.88383e+06 | 1.42562 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 922.923 | 0.337745 | 124.891ms | 500299 | 30 | 9.14594e+07 | 516969 | 2.5266 | 1(Win) |
| jsonifier | 818.369 | 0.346421 | 139.847ms | 500299 | 30 | 1.22374e+08 | 583016 | 2.84942 | 2(Loss) |
| simdjson (ondemand) | 592.172 | 0.112955 | 195.632ms | 500299 | 30 | 2.48483e+07 | 805716 | 3.93796 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1850.21 | 0.652139 | 61.9853ms | 500299 | 30 | 8.48435e+07 | 257874 | 1.26013 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1838.51 | 0.377592 | 62.9632ms | 500299 | 30 | 2.88066e+07 | 259516 | 1.26819 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1513.87 | 0.122663 | 218.798ms | 1439562 | 30 | 3.71221e+07 | 906864 | 1.54039 | 1(Win) |
| glaze | 1451.24 | 0.225906 | 229.318ms | 1439562 | 30 | 1.37012e+08 | 946001 | 1.60689 | 2(Loss) |
| jsonifier | 1254.8 | 0.180563 | 263.214ms | 1439562 | 30 | 1.17082e+08 | 1.0941e+06 | 1.85844 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3223.27 | 0.843335 | 100.945ms | 1439562 | 30 | 3.8707e+08 | 425926 | 0.723404 | 1(Win) |
| glaze | 1887.61 | 0.274683 | 173.856ms | 1439584 | 30 | 1.19739e+08 | 727320 | 1.23539 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 829.524 | 0.609146 | 16.4492ms | 56369 | 30 | 4.67505e+06 | 64805.4 | 2.80969 | 1(Win) |
| jsonifier | 789.116 | 1.46578 | 17.0199ms | 56369 | 30 | 2.9913e+07 | 68123.9 | 2.95355 | 2(Loss) |
| simdjson (ondemand) | 662.996 | 0.740378 | 20.1886ms | 56369 | 30 | 1.08115e+07 | 81083 | 3.51558 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1883.83 | 1.14215 | 7.21271ms | 56369 | 30 | 3.18688e+06 | 28536.4 | 1.23626 | 1(Win) |
| jsonifier | 1751.96 | 0.962129 | 7.71902ms | 56369 | 30 | 2.61469e+06 | 30684.3 | 1.32955 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1107.16 | 1.3968 | 19.9448ms | 94370 | 30 | 3.86759e+07 | 81287.7 | 2.10513 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1081.7 | 0.99343 | 20.9189ms | 94370 | 30 | 2.0495e+07 | 83200.5 | 2.15476 | 1(Tie) |
| jsonifier | 811.792 | 0.569233 | 27.8313ms | 94370 | 30 | 1.19476e+07 | 110864 | 2.87154 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2407.68 | 1.67434 | 9.24613ms | 94370 | 30 | 1.17511e+07 | 37379.7 | 0.96759 | 1(Win) |
| glaze | 1678.85 | 1.1178 | 13.2451ms | 94370 | 30 | 1.0772e+07 | 53607.1 | 1.38749 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 812.014 | 2.42408 | 14.8781ms | 52708 | 30 | 6.75527e+07 | 61903.2 | 2.86803 | 1(Win) |
| glaze | 709.004 | 0.902616 | 18.0197ms | 52708 | 30 | 1.22852e+07 | 70897 | 3.28661 | 2(Loss) |
| jsonifier | 616.57 | 1.37471 | 20.5895ms | 52708 | 30 | 3.7682e+07 | 81525.7 | 3.77703 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3004.15 | 0.13151 | 4.56422ms | 52708 | 30 | 14526.1 | 16732.3 | 0.77446 | 1(Win) |
| glaze | 2776.31 | 0.839754 | 22.5274ms | 52708 | 64 | 1.47945e+06 | 18105.4 | 0.837992 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1098.11 | 1.01691 | 15.2252ms | 70103 | 30 | 1.14992e+07 | 60882.1 | 2.12171 | 1(Win) |
| glaze | 801.021 | 1.40664 | 20.7011ms | 70103 | 30 | 4.13498e+07 | 83462.7 | 2.90906 | 2(Loss) |
| jsonifier | 515.206 | 1.6257 | 32.3791ms | 70103 | 30 | 1.3351e+08 | 129765 | 4.52154 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3094.04 | 1.63722 | 5.67655ms | 70103 | 30 | 3.75455e+06 | 21607.8 | 0.752325 | 1(Win) |
| glaze | 2236.75 | 1.29436 | 7.45889ms | 70103 | 30 | 4.49025e+06 | 29889.6 | 1.03985 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 657.071 | 0.255424 | 10.4153ms | 11812 | 32 | 61361.5 | 17144 | 3.54157 | 1(Win) |
| jsonifier | 637.339 | 0.0795132 | 4.7734ms | 11812 | 30 | 5925.24 | 17674.7 | 3.65155 | 2(Loss) |
| simdjson (ondemand) | 570.151 | 0.104089 | 11.6979ms | 11812 | 32 | 13534.1 | 19757.6 | 4.08297 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2470.46 | 0.646121 | 1.42292ms | 11812 | 30 | 26040 | 4559.8 | 0.936773 | 1(Win) |
| glaze | 1270.47 | 0.128231 | 2.48328ms | 11812 | 30 | 3878.16 | 8866.67 | 1.8281 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1338.6 | 1.93649 | 5.70279ms | 31235 | 30 | 5.57097e+06 | 22253.1 | 1.73938 | 1(Win) |
| glaze | 1132.53 | 1.06145 | 6.88817ms | 31235 | 30 | 2.33831e+06 | 26302.2 | 2.05617 | 2(Loss) |
| jsonifier | 1031.41 | 1.0081 | 7.44405ms | 31235 | 30 | 2.54298e+06 | 28880.8 | 2.25817 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2928.13 | 0.104611 | 2.83516ms | 31235 | 30 | 3397.65 | 10173.1 | 0.79358 | 1(Win) |
| glaze | 1875.72 | 0.256469 | 4.1008ms | 31235 | 30 | 49766.6 | 15880.8 | 1.24039 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1665.02 | 0.806815 | 15.6249ms | 108313 | 30 | 7.51612e+06 | 62038.6 | 1.39951 | 1(Win) |
| glaze | 964.955 | 0.805864 | 26.7546ms | 108313 | 30 | 2.23251e+07 | 107047 | 2.41559 | 2(Loss) |
| simdjson (ondemand) | 845.909 | 0.831996 | 29.7358ms | 108313 | 30 | 3.09655e+07 | 122112 | 2.75534 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1942.57 | 0.653173 | 13.1928ms | 108313 | 30 | 3.61898e+06 | 53174.6 | 1.19949 | 1(Win) |
| glaze | 1737.96 | 0.636074 | 14.6969ms | 108313 | 30 | 4.28763e+06 | 59434.8 | 1.34076 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1516.63 | 0.844462 | 32.9352ms | 213963 | 30 | 3.87258e+07 | 134543 | 1.53693 | 1(Win) |
| glaze | 1318.69 | 1.41769 | 37.7067ms | 213963 | 30 | 1.44369e+08 | 154738 | 1.76797 | 2(Loss) |
| jsonifier | 1137.11 | 0.746963 | 44.2757ms | 213963 | 30 | 5.39002e+07 | 179447 | 2.05014 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3125.95 | 0.983194 | 16.2161ms | 213963 | 30 | 1.2357e+07 | 65276.5 | 0.745376 | 1(Win) |
| glaze | 1631.59 | 0.657183 | 30.5087ms | 213963 | 30 | 2.02651e+07 | 125063 | 1.42864 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 435.077 | 0.0900842 | 973.195ms | 1834197 | 30 | 3.9353e+08 | 4.0205e+06 | 5.36013 | 1(Win) |
| glaze | 329.152 | 0.123073 | 1274ms | 1834197 | 30 | 1.28335e+09 | 5.31435e+06 | 7.08509 | 2(Loss) |
| simdjson (ondemand) | 289.242 | 0.106955 | 1448.53ms | 1834197 | 30 | 1.25513e+09 | 6.04762e+06 | 8.06266 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 553.3 | 0.290756 | 765.496ms | 1834197 | 30 | 2.53483e+09 | 3.16144e+06 | 4.21482 | 1(Win) |
| glaze | 354.777 | 0.0462889 | 1185.24ms | 1833577 | 30 | 1.56158e+08 | 4.92883e+06 | 6.57335 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1429.01 | 0.0952148 | 1600.04ms | 9930848 | 30 | 1.19463e+09 | 6.62753e+06 | 1.63196 | 1(Win) |
| glaze | 1285.14 | 0.0996314 | 1771.8ms | 9930848 | 30 | 1.61729e+09 | 7.36949e+06 | 1.81463 | 2(Loss) |
| jsonifier | 1157.12 | 0.156787 | 1970ms | 9930848 | 30 | 4.94031e+09 | 8.1848e+06 | 2.01537 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2069.9 | 0.482235 | 1116.03ms | 9930848 | 30 | 1.46054e+10 | 4.57549e+06 | 1.12666 | 1(Win) |
| glaze | 1178.8 | 0.216967 | 1925.47ms | 9930228 | 30 | 9.11471e+09 | 8.03374e+06 | 1.97827 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 800.888 | 0.179196 | 184.928ms | 642697 | 30 | 5.64219e+07 | 765305 | 2.91166 | 1(Win) |
| glaze | 647.778 | 0.144692 | 227.327ms | 642697 | 30 | 5.62301e+07 | 946194 | 3.59992 | 2(Loss) |
| simdjson (ondemand) | 599.033 | 0.12645 | 246.185ms | 642697 | 30 | 5.02193e+07 | 1.02319e+06 | 3.89288 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 844.626 | 0.1637 | 175.156ms | 642697 | 30 | 4.23354e+07 | 725675 | 2.76089 | 1(Win) |
| glaze | 599.674 | 0.225355 | 246.043ms | 642692 | 30 | 1.59159e+08 | 1.02209e+06 | 3.88872 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1102.15 | 0.16543 | 255.888ms | 1225964 | 30 | 9.23885e+07 | 1.0608e+06 | 2.11582 | 1(Win) |
| glaze | 979.717 | 0.631279 | 285.239ms | 1225964 | 30 | 1.70262e+09 | 1.19338e+06 | 2.38025 | 2(Loss) |
| jsonifier | 756.825 | 0.391892 | 369.485ms | 1225964 | 30 | 1.09956e+09 | 1.54484e+06 | 3.08132 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1515.22 | 0.281768 | 186.14ms | 1225964 | 30 | 1.4181e+08 | 771616 | 1.53899 | 1(Win) |
| glaze | 971.686 | 0.155702 | 289.623ms | 1225970 | 30 | 1.05297e+08 | 1.20324e+06 | 2.39995 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 507.94 | 0.196837 | 184.837ms | 409725 | 30 | 6.87852e+07 | 769272 | 4.59097 | 1(Win) |
| jsonifier | 503.482 | 0.335841 | 185.73ms | 409725 | 30 | 2.03801e+08 | 776084 | 4.63151 | 2(Loss) |
| glaze | 409.457 | 0.166189 | 231.238ms | 409725 | 30 | 7.54557e+07 | 954298 | 5.69531 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1364 | 0.398005 | 69.5248ms | 409725 | 30 | 3.89989e+07 | 286469 | 1.70943 | 1(Win) |
| glaze | 1207.47 | 0.404955 | 78.3991ms | 409725 | 30 | 5.15186e+07 | 323605 | 1.93102 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 930.636 | 0.152447 | 193.62ms | 785750 | 30 | 4.52031e+07 | 805202 | 2.50576 | 1(Win) |
| glaze | 672.347 | 0.185075 | 268.571ms | 785750 | 30 | 1.27644e+08 | 1.11453e+06 | 3.46843 | 2(Loss) |
| jsonifier | 638.617 | 0.169391 | 281.962ms | 785750 | 30 | 1.1852e+08 | 1.17339e+06 | 3.65164 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1995.75 | 0.409107 | 90.6343ms | 785750 | 30 | 7.07868e+07 | 375473 | 1.16837 | 1(Win) |
| glaze | 1503.11 | 0.306619 | 120.04ms | 785750 | 30 | 7.00985e+07 | 498534 | 1.55134 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 706.05 | 0.200071 | 2789.76ms | 8587914 | 30 | 1.61582e+10 | 1.15998e+07 | 3.30297 | 1(Win) |
| jsonifier | 682.71 | 0.140387 | 2892.7ms | 8587914 | 30 | 8.50899e+09 | 1.19964e+07 | 3.4159 | 2(Loss) |
| glaze | 639.155 | 0.17084 | 3083.67ms | 8587914 | 30 | 1.43768e+10 | 1.28139e+07 | 3.64871 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2218.91 | 0.281237 | 898.083ms | 8588126 | 30 | 3.23286e+09 | 3.69113e+06 | 1.05093 | 1(Win) |
| glaze | 2022.79 | 0.47718 | 963.436ms | 8588126 | 30 | 1.11991e+10 | 4.049e+06 | 1.15285 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 773.467 | 0.172004 | 2943.74ms | 9804437 | 30 | 1.29706e+10 | 1.20887e+07 | 3.01509 | 1(Win) |
| glaze | 663.436 | 0.219547 | 3413.51ms | 9804437 | 30 | 2.87226e+10 | 1.40936e+07 | 3.51515 | 2(Loss) |
| jsonifier | 626.502 | 0.134362 | 3612.86ms | 9804437 | 30 | 1.20636e+10 | 1.49245e+07 | 3.72239 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2481.17 | 0.222831 | 1045.11ms | 11078090 | 30 | 2.70078e+09 | 4.25803e+06 | 0.939847 | 1(Win) |
| glaze | 1779.13 | 1.26309 | 1385.63ms | 11078090 | 30 | 1.68774e+11 | 5.93825e+06 | 1.31072 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2589.13 | 1.14841 | 23.8464ms | 264040 | 30 | 3.74234e+07 | 97255.9 | 0.900072 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2555.3 | 0.584009 | 24.2888ms | 264040 | 30 | 9.93614e+06 | 98543.6 | 0.912026 | 1(Tie) |
| glaze | 1035.1 | 0.530363 | 58.3245ms | 264040 | 30 | 4.99395e+07 | 243270 | 2.25238 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3428.38 | 0.730838 | 27.1729ms | 399947 | 30 | 1.9833e+07 | 111253 | 0.679804 | 1(Win) |
| jsonifier | 2913.99 | 0.820644 | 31.9251ms | 399947 | 30 | 3.46147e+07 | 130893 | 0.799872 | 2(Loss) |
| glaze | 1285.89 | 0.637731 | 71.1483ms | 399947 | 30 | 1.07348e+08 | 296619 | 1.81317 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 893.218 | 0.632428 | 68.5223ms | 264040 | 30 | 9.53604e+07 | 281911 | 2.61005 | 1(Win) |
| simdjson (ondemand) | 862 | 0.452289 | 70.9669ms | 264040 | 30 | 5.23695e+07 | 292121 | 2.70482 | 2(Loss) |
| glaze | 772.837 | 1.87569 | 76.9448ms | 264040 | 30 | 1.12049e+09 | 325823 | 3.017 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2327.69 | 0.841411 | 27.121ms | 263923 | 30 | 2.48337e+07 | 108131 | 1.00133 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2319.33 | 0.748861 | 26.4524ms | 264040 | 30 | 1.98306e+07 | 108569 | 1.00491 | 1(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1223.22 | 0.590181 | 75.2269ms | 399947 | 30 | 1.01599e+08 | 311817 | 1.90612 | 1(Win) |
| glaze | 959.045 | 1.62364 | 95.2183ms | 399947 | 30 | 1.25091e+09 | 397707 | 2.43129 | 2(Loss) |
| jsonifier | 806.678 | 0.456009 | 114.495ms | 399947 | 30 | 1.39467e+08 | 472827 | 2.88998 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3063.88 | 1.73925 | 30.126ms | 399947 | 30 | 1.4064e+08 | 124489 | 0.760809 | 1(Win) |
| glaze | 2058.68 | 0.783694 | 45.1233ms | 399830 | 30 | 6.32106e+07 | 185220 | 1.13239 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1379.14 | 0.336037 | 77.9849ms | 466906 | 30 | 3.53133e+07 | 322865 | 1.69065 | 1(Win) |
| glaze | 1347 | 0.375341 | 80.0219ms | 466906 | 30 | 4.61843e+07 | 330568 | 1.73103 | 2(Loss) |
| simdjson (ondemand) | 663.658 | 0.240458 | 162.446ms | 466906 | 30 | 7.80857e+07 | 670943 | 3.51356 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2066.08 | 0.370625 | 78.2557ms | 699405 | 30 | 4.29493e+07 | 322836 | 1.12853 | 1(Win) |
| glaze | 1673.5 | 0.344204 | 96.7217ms | 699405 | 30 | 5.64626e+07 | 398569 | 1.39336 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1663.64 | 0.354498 | 87.4513ms | 631514 | 30 | 4.94077e+07 | 362012 | 1.40158 | 1(Win) |
| glaze | 1541.06 | 0.256243 | 94.424ms | 631514 | 30 | 3.00852e+07 | 390808 | 1.51313 | 2(Loss) |
