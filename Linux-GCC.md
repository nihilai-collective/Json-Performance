# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [beb3474](https://github.com/nihilai-collective/jsonifier/commit/beb3474)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 828.414 | 0.0609366 | 2.35268ms | 1811 | 30 | 48.4195 | 2084.83 | 2.94694 | 1(Win) |
| glaze | 364.822 | 0.350935 | 1.49308ms | 1811 | 30 | 8280.37 | 4734.1 | 6.74 | 2(Loss) |
| simdjson (ondemand) | 135.625 | 0.0576609 | 3.24315ms | 1811 | 30 | 1617.49 | 12734.4 | 18.2119 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 539.973 | 0.158987 | 0.962759ms | 1811 | 30 | 775.776 | 3198.5 | 4.54338 | 1(Win) |
| glaze | 363.175 | 0.589785 | 2.9078ms | 1798 | 32 | 24813.4 | 4721.44 | 6.77204 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1387.52 | 0.0852455 | 0.849069ms | 3873 | 30 | 154.483 | 2662 | 1.76466 | 1(Win) |
| glaze | 1243 | 0.104616 | 0.866685ms | 3873 | 30 | 289.914 | 2971.5 | 1.97143 | 2(Loss) |
| simdjson (ondemand) | 306.708 | 1.6548 | 3.01183ms | 3873 | 30 | 1.19141e+06 | 12042.7 | 8.05263 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2076.68 | 0.0646752 | 0.614969ms | 3873 | 30 | 39.6966 | 1778.6 | 1.17055 | 1(Win) |
| glaze | 1015.91 | 0.584771 | 1.05075ms | 3873 | 30 | 13560.5 | 3635.73 | 2.41628 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1422.85 | 0.0711068 | 0.820506ms | 3862 | 30 | 101.637 | 2588.53 | 1.71986 | 1(Win) |
| glaze | 1124.77 | 0.0648028 | 0.940336ms | 3862 | 30 | 135.085 | 3274.53 | 2.18058 | 2(Loss) |
| simdjson (ondemand) | 301.302 | 0.0480088 | 3.10373ms | 3862 | 30 | 1033.2 | 12223.9 | 8.19698 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2064.51 | 0.0582652 | 0.593016ms | 3862 | 30 | 32.4138 | 1784 | 1.17657 | 1(Win) |
| glaze | 1133.53 | 0.457544 | 0.947657ms | 3862 | 30 | 6630.53 | 3249.23 | 2.1642 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1079.02 | 0.134536 | 0.365616ms | 905 | 30 | 34.7402 | 799.867 | 2.21112 | 1(Win) |
| glaze | 625.372 | 0.946003 | 0.48201ms | 905 | 30 | 5113.61 | 1380.1 | 3.86983 | 2(Loss) |
| simdjson (ondemand) | 93.0252 | 0.0417211 | 2.38943ms | 905 | 30 | 449.499 | 9277.87 | 26.5295 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 929.971 | 0.77798 | 0.38849ms | 905 | 30 | 1563.93 | 928.067 | 2.57606 | 1(Win) |
| glaze | 327.966 | 0.580271 | 0.775309ms | 905 | 30 | 6995.56 | 2631.6 | 7.4667 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1035.57 | 0.0829469 | 11.0628ms | 9578 | 64 | 3425.87 | 8820.55 | 2.38147 | 1(Win) |
| glaze | 1023.22 | 0.11557 | 2.34571ms | 9578 | 30 | 3193.21 | 8927.03 | 2.40998 | 2(Loss) |
| simdjson (ondemand) | 695.593 | 0.314057 | 3.36599ms | 9578 | 30 | 51024.4 | 13131.7 | 3.55027 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3740.04 | 0.10987 | 0.797892ms | 9578 | 30 | 216.01 | 2442.3 | 0.654107 | 1(Win) |
| glaze | 2191.74 | 0.395806 | 1.17354ms | 9578 | 30 | 8163.14 | 4167.6 | 1.12156 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 4087.92 | 0.650475 | 13.3326ms | 233995 | 30 | 3.78261e+06 | 54588.9 | 0.605202 | 1(Tie) |
| jsonifier STATISTICAL TIE | 4058.26 | 0.419887 | 13.5322ms | 233995 | 30 | 1.59926e+06 | 54987.9 | 0.609716 | 1(Tie) |
| glaze | 1743.92 | 0.344037 | 31.1769ms | 233995 | 30 | 5.8142e+06 | 127961 | 1.41927 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 5086.16 | 0.578287 | 15.7933ms | 346753 | 30 | 4.24099e+06 | 65017.5 | 0.486471 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5031.88 | 0.489103 | 16.0118ms | 346753 | 30 | 3.09957e+06 | 65718.9 | 0.491777 | 1(Tie) |
| glaze | 2202.66 | 0.394818 | 36.4944ms | 346753 | 30 | 1.05405e+07 | 150132 | 1.12373 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1583.84 | 0.7595 | 36.3994ms | 233995 | 30 | 3.43533e+07 | 140895 | 1.56281 | 1(Win) |
| simdjson (ondemand) | 1519.79 | 0.420032 | 36.3179ms | 233995 | 30 | 1.14112e+07 | 146832 | 1.6287 | 2(Loss) |
| jsonifier | 1299.95 | 0.636279 | 41.6464ms | 233995 | 30 | 3.57914e+07 | 171665 | 1.90417 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3197.04 | 0.580549 | 17.0471ms | 233995 | 30 | 4.92625e+06 | 69800.6 | 0.774083 | 1(Win) |
| glaze | 2762.05 | 0.578542 | 19.6241ms | 233995 | 30 | 6.55455e+06 | 80793.4 | 0.895941 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2116.52 | 0.365037 | 39.4136ms | 346753 | 30 | 9.75863e+06 | 156242 | 1.16944 | 1(Win) |
| glaze | 1713.46 | 0.34731 | 48.2907ms | 346753 | 30 | 1.34786e+07 | 192995 | 1.44467 | 2(Loss) |
| jsonifier | 1245.32 | 0.262394 | 64.4943ms | 346753 | 30 | 1.4565e+07 | 265547 | 1.98779 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3262.58 | 0.607294 | 24.5753ms | 346753 | 30 | 1.13667e+07 | 101358 | 0.758588 | 1(Win) |
| glaze | 2648 | 0.688277 | 30.2483ms | 346753 | 30 | 2.21641e+07 | 124883 | 0.93452 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3925.68 | 0.385926 | 13.9329ms | 233995 | 30 | 1.44382e+06 | 56844.9 | 0.630336 | 1(Win) |
| simdjson (ondemand) | 2535.72 | 0.426076 | 21.4183ms | 233995 | 30 | 4.21799e+06 | 88004.5 | 0.976039 | 2(Loss) |
| glaze | 1746.16 | 0.347387 | 31.2771ms | 233995 | 30 | 5.91285e+06 | 127798 | 1.41752 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4941.76 | 0.519926 | 16.2781ms | 346753 | 30 | 3.63146e+06 | 66917.4 | 0.50078 | 1(Win) |
| simdjson (ondemand) | 3425.24 | 0.400293 | 23.3965ms | 346753 | 30 | 4.48059e+06 | 96544.9 | 0.72259 | 2(Loss) |
| glaze | 2195.65 | 0.440065 | 40.6916ms | 346753 | 30 | 1.31786e+07 | 150611 | 1.12736 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1699.47 | 0.391099 | 33.4679ms | 233995 | 30 | 7.91193e+06 | 131309 | 1.45649 | 1(Win) |
| jsonifier | 1214.65 | 0.902741 | 44.0765ms | 233995 | 30 | 8.25201e+07 | 183720 | 2.03793 | 2(Loss) |
| simdjson (ondemand) | 234.479 | 0.332436 | 533.932ms | 233995 | 32 | 3.20311e+08 | 951707 | 10.5582 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3382.97 | 0.529396 | 16.181ms | 233995 | 30 | 3.65847e+06 | 65964.2 | 0.731512 | 1(Win) |
| glaze | 2774.25 | 0.497634 | 19.5854ms | 233995 | 30 | 4.8069e+06 | 80438.1 | 0.892004 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1719.61 | 1.24663 | 46.3126ms | 346753 | 30 | 1.72417e+08 | 192305 | 1.4395 | 1(Win) |
| jsonifier | 1302.41 | 0.483032 | 61.6938ms | 346753 | 30 | 4.5125e+07 | 253906 | 1.90057 | 2(Loss) |
| simdjson (ondemand) | 345.852 | 0.0919536 | 229.499ms | 346753 | 30 | 2.31909e+07 | 956158 | 7.15827 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3761.74 | 0.78654 | 21.3821ms | 346753 | 30 | 1.43426e+07 | 87908.7 | 0.657846 | 1(Win) |
| glaze | 2659.57 | 1.92096 | 29.1092ms | 346753 | 30 | 1.7115e+08 | 124340 | 0.930445 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 949.042 | 0.529244 | 24.3678ms | 94651 | 30 | 7.60174e+06 | 95113 | 2.60792 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 947.903 | 0.579421 | 23.1709ms | 94651 | 30 | 9.1334e+06 | 95227.3 | 2.61095 | 1(Tie) |
| jsonifier | 574.906 | 0.412738 | 38.0526ms | 94651 | 30 | 1.25988e+07 | 157011 | 4.30527 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4220.63 | 0.0781561 | 6.8449ms | 94651 | 30 | 8381.93 | 21386.9 | 0.585792 | 1(Win) |
| glaze | 3855.62 | 0.988255 | 5.94278ms | 94651 | 30 | 1.60591e+06 | 23411.6 | 0.641299 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1321.07 | 0.497566 | 60.3164ms | 136024 | 32 | 7.63886e+06 | 98194.8 | 1.87349 | 1(Win) |
| glaze | 1141.61 | 0.517731 | 27.9269ms | 136024 | 30 | 1.0383e+07 | 113631 | 2.1681 | 2(Loss) |
| jsonifier | 740.361 | 0.338906 | 42.624ms | 136024 | 30 | 1.05785e+07 | 175215 | 3.34314 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4432.08 | 1.98324 | 6.93096ms | 136024 | 30 | 1.01085e+07 | 29269 | 0.557997 | 1(Win) |
| glaze | 3388.81 | 1.37312 | 9.32582ms | 136046 | 30 | 8.29118e+06 | 38285.9 | 0.730003 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 539.732 | 0.0894604 | 887.429ms | 2090234 | 30 | 3.27504e+08 | 3.69332e+06 | 4.58697 | 1(Win) |
| simdjson (ondemand) | 450.476 | 0.080534 | 1067.01ms | 2090234 | 30 | 3.81001e+08 | 4.4251e+06 | 5.49586 | 2(Loss) |
| glaze | 436.929 | 0.175514 | 1094.55ms | 2090234 | 30 | 1.9236e+09 | 4.56231e+06 | 5.66585 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1143.39 | 0.129702 | 419.174ms | 2090234 | 30 | 1.53397e+08 | 1.74342e+06 | 2.16523 | 1(Win) |
| glaze | 932.23 | 0.0797337 | 514.548ms | 2090234 | 30 | 8.72065e+07 | 2.13832e+06 | 2.65567 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1321.77 | 0.125177 | 1158.23ms | 6661897 | 30 | 1.08605e+09 | 4.80663e+06 | 1.87304 | 1(Win) |
| jsonifier | 1210.84 | 0.345269 | 1255.63ms | 6661897 | 30 | 9.84592e+09 | 5.24699e+06 | 2.04466 | 2(Loss) |
| glaze | 1118.69 | 0.100161 | 1363.84ms | 6661897 | 30 | 9.70718e+08 | 5.67921e+06 | 2.21308 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2859.33 | 0.124665 | 536.342ms | 6661897 | 30 | 2.30187e+08 | 2.22195e+06 | 0.865836 | 1(Win) |
| glaze | 2212.84 | 0.158766 | 685.779ms | 6661897 | 30 | 6.23353e+08 | 2.87109e+06 | 1.11875 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1150.76 | 0.522488 | 103.729ms | 500299 | 30 | 1.40787e+08 | 414615 | 2.15101 | 1(Win) |
| jsonifier | 1059.22 | 0.206256 | 108.079ms | 500299 | 30 | 2.58955e+07 | 450448 | 2.33693 | 2(Loss) |
| simdjson (ondemand) | 878.656 | 0.344374 | 130.012ms | 500299 | 30 | 1.04907e+08 | 543014 | 2.81721 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3339.38 | 0.403584 | 35.1362ms | 500299 | 30 | 9.97511e+06 | 142878 | 0.741151 | 1(Win) |
| glaze | 2703.26 | 0.358601 | 43.0498ms | 500299 | 30 | 1.20179e+07 | 176499 | 0.9155 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2261.15 | 0.146633 | 146.016ms | 1439562 | 30 | 2.37786e+07 | 607158 | 1.09479 | 1(Win) |
| glaze | 1992.31 | 0.120258 | 163.594ms | 1439562 | 30 | 2.06014e+07 | 689088 | 1.24251 | 2(Loss) |
| jsonifier | 1684.17 | 0.0823505 | 196.203ms | 1439562 | 30 | 1.3519e+07 | 815164 | 1.46981 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5009.04 | 0.362006 | 66.105ms | 1439562 | 30 | 2.95328e+07 | 274079 | 0.494182 | 1(Win) |
| glaze | 3457.23 | 0.232142 | 96.4545ms | 1439584 | 30 | 2.54946e+07 | 397108 | 0.716008 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1119.83 | 0.64569 | 12.013ms | 56369 | 30 | 2.88233e+06 | 48005 | 2.20942 | 1(Win) |
| simdjson (ondemand) | 1075.32 | 0.474647 | 12.4299ms | 56369 | 30 | 1.68913e+06 | 49992 | 2.30091 | 2(Loss) |
| jsonifier | 850.213 | 0.582569 | 15.5815ms | 56369 | 30 | 4.07044e+06 | 63228.5 | 2.91016 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4008.06 | 0.0782824 | 3.45219ms | 56369 | 30 | 3307.21 | 13412.4 | 0.616348 | 1(Win) |
| glaze | 3678.45 | 0.0996573 | 3.73507ms | 56369 | 30 | 6363.41 | 14614.2 | 0.671652 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1653.37 | 0.610803 | 13.4848ms | 94370 | 30 | 3.3163e+06 | 54433.3 | 1.49642 | 1(Win) |
| glaze | 1483.37 | 0.572117 | 15.017ms | 94370 | 30 | 3.61457e+06 | 60671.3 | 1.66818 | 2(Loss) |
| jsonifier | 980.001 | 1.75482 | 21.6091ms | 94370 | 30 | 7.79119e+07 | 91834.9 | 2.52512 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4828.34 | 0.0845949 | 4.73789ms | 94370 | 30 | 7459.01 | 18639.6 | 0.511991 | 1(Win) |
| glaze | 3488.92 | 0.83177 | 6.46045ms | 94370 | 30 | 1.38107e+06 | 25795.5 | 0.70878 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1257.67 | 1.14697 | 9.96767ms | 52708 | 30 | 6.30443e+06 | 39967.7 | 1.96639 | 1(Win) |
| glaze | 1014.32 | 0.578583 | 12.5073ms | 52708 | 30 | 2.46636e+06 | 49556.7 | 2.43932 | 2(Loss) |
| jsonifier | 927.623 | 0.682665 | 13.756ms | 52708 | 30 | 4.10532e+06 | 54188.2 | 2.66643 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4271.82 | 0.175896 | 3.06227ms | 52708 | 30 | 12851.7 | 11766.9 | 0.578063 | 1(Win) |
| jsonifier | 4016.81 | 0.392929 | 7.33764ms | 52708 | 32 | 77369.1 | 12514 | 0.614894 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1657.02 | 0.904472 | 10.0818ms | 70103 | 30 | 3.99514e+06 | 40346.9 | 1.4927 | 1(Win) |
| glaze | 1194.58 | 0.368594 | 14.1804ms | 70103 | 30 | 1.27662e+06 | 55965.6 | 2.07138 | 2(Loss) |
| jsonifier | 920.762 | 1.02891 | 18.268ms | 70103 | 30 | 1.67437e+07 | 72608.8 | 2.68682 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4291.12 | 2.37632 | 3.89469ms | 70103 | 30 | 4.1121e+06 | 15580 | 0.575758 | 1(Win) |
| glaze | 3884.81 | 0.187364 | 4.41215ms | 70103 | 30 | 31190.8 | 17209.4 | 0.63615 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 879.776 | 0.0855309 | 3.29508ms | 11812 | 30 | 3598.07 | 12804.2 | 2.80764 | 1(Win) |
| glaze | 839.525 | 1.63929 | 3.5006ms | 11812 | 30 | 1.45149e+06 | 13418.1 | 2.94213 | 2(Loss) |
| jsonifier | 686.411 | 0.102533 | 4.20926ms | 11812 | 30 | 8494.28 | 16411.2 | 3.59984 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3742.67 | 2.1874 | 0.882468ms | 11812 | 30 | 130036 | 3009.83 | 0.654843 | 1(Win) |
| glaze | 2532.45 | 0.280021 | 2.75228ms | 11812 | 32 | 4964.74 | 4448.19 | 0.97112 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2003.42 | 1.83486 | 3.78952ms | 31235 | 30 | 2.23288e+06 | 14868.6 | 1.23323 | 1(Win) |
| glaze | 1509.67 | 0.858537 | 5.02596ms | 31235 | 30 | 860911 | 19731.5 | 1.63738 | 2(Loss) |
| jsonifier | 1237.9 | 1.16357 | 6.01311ms | 31235 | 30 | 2.3519e+06 | 24063.3 | 1.99748 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4515.5 | 0.300737 | 1.77541ms | 31235 | 30 | 11807.7 | 6596.83 | 0.545804 | 1(Win) |
| glaze | 3624.17 | 0.175431 | 2.17717ms | 31235 | 30 | 6237.37 | 8219.27 | 0.680764 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2155.99 | 0.558554 | 11.922ms | 108313 | 30 | 2.14843e+06 | 47910.9 | 1.14743 | 1(Win) |
| glaze | 1374.96 | 0.501345 | 18.5436ms | 108313 | 30 | 4.25574e+06 | 75125.9 | 1.79982 | 2(Loss) |
| simdjson (ondemand) | 1335.1 | 1.19241 | 18.6766ms | 108313 | 30 | 2.55334e+07 | 77368.9 | 1.85349 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2449.29 | 0.71689 | 10.3425ms | 108313 | 30 | 2.74226e+06 | 42173.6 | 1.01015 | 1(Win) |
| glaze | 1882.37 | 0.626381 | 13.3956ms | 108313 | 30 | 3.54445e+06 | 54875 | 1.31446 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2424.09 | 0.514988 | 20.5129ms | 213963 | 30 | 5.63764e+06 | 84176.4 | 1.02098 | 1(Win) |
| glaze | 1789.58 | 0.526787 | 27.814ms | 213963 | 30 | 1.08235e+07 | 114022 | 1.38304 | 2(Loss) |
| jsonifier | 1669.02 | 0.51114 | 29.7111ms | 213963 | 30 | 1.17154e+07 | 122258 | 1.48269 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3542.65 | 0.723859 | 14.1928ms | 213963 | 30 | 5.21495e+06 | 57598.4 | 0.698467 | 1(Win) |
| glaze | 2336.47 | 0.542781 | 21.1939ms | 213963 | 30 | 6.74106e+06 | 87333.1 | 1.05927 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 556.049 | 0.0684734 | 756.621ms | 1834197 | 30 | 1.39197e+08 | 3.14581e+06 | 4.45232 | 1(Win) |
| glaze | 428.788 | 0.102815 | 979.241ms | 1834197 | 30 | 5.27767e+08 | 4.07947e+06 | 5.77381 | 2(Loss) |
| simdjson (ondemand) | 395.989 | 0.115915 | 1060.68ms | 1834197 | 30 | 7.86557e+08 | 4.41736e+06 | 6.25205 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 729.498 | 0.415937 | 573.768ms | 1834197 | 30 | 2.98414e+09 | 2.39785e+06 | 3.39375 | 1(Win) |
| glaze | 485.722 | 0.0604125 | 865.844ms | 1833577 | 30 | 1.41905e+08 | 3.60007e+06 | 5.09704 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1876.06 | 0.0514312 | 1215.7ms | 9930848 | 30 | 2.02235e+08 | 5.04824e+06 | 1.31965 | 1(Win) |
| glaze STATISTICAL TIE | 1673.17 | 0.12791 | 1354.35ms | 9930848 | 30 | 1.5726e+09 | 5.66038e+06 | 1.47966 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1671.87 | 0.0548847 | 1365.66ms | 9930848 | 30 | 2.89995e+08 | 5.66478e+06 | 1.4808 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2724.8 | 0.162033 | 834.895ms | 9930848 | 30 | 9.51553e+08 | 3.47578e+06 | 0.908592 | 1(Win) |
| glaze | 1694.99 | 0.0896274 | 1344.18ms | 9930228 | 30 | 7.52292e+08 | 5.58717e+06 | 1.46057 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1014.36 | 0.5008 | 146.648ms | 642697 | 30 | 2.74712e+08 | 604246 | 2.44041 | 1(Win) |
| simdjson (ondemand) | 850.472 | 0.167077 | 175.888ms | 642697 | 30 | 4.3496e+07 | 720686 | 2.91073 | 2(Loss) |
| glaze | 791.383 | 0.231354 | 187.587ms | 642697 | 30 | 9.63198e+07 | 774497 | 3.12816 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1232.33 | 0.839874 | 120.534ms | 642697 | 30 | 5.23492e+08 | 497371 | 2.00887 | 1(Win) |
| glaze | 797.499 | 0.142096 | 446.769ms | 642692 | 32 | 3.81643e+07 | 768551 | 3.10418 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1507.28 | 0.22293 | 187.651ms | 1225964 | 30 | 8.9707e+07 | 775682 | 1.64241 | 1(Win) |
| glaze | 1206.31 | 0.359068 | 232.357ms | 1225964 | 30 | 3.63343e+08 | 969215 | 2.0522 | 2(Loss) |
| jsonifier | 1082.92 | 0.193488 | 260.644ms | 1225964 | 30 | 1.30915e+08 | 1.07964e+06 | 2.28603 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2090.36 | 0.239243 | 135.447ms | 1225964 | 30 | 5.37176e+07 | 559317 | 1.18431 | 1(Win) |
| glaze | 1232.29 | 0.0850918 | 228.274ms | 1225970 | 30 | 1.95537e+07 | 948782 | 2.00897 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 753.24 | 0.230986 | 125.072ms | 409725 | 30 | 4.30736e+07 | 518751 | 3.28643 | 1(Win) |
| glaze | 525.264 | 0.150754 | 178.697ms | 409725 | 30 | 3.77302e+07 | 743900 | 4.71309 | 2(Loss) |
| jsonifier | 519.142 | 0.114781 | 180.826ms | 409725 | 30 | 2.2391e+07 | 752672 | 4.76843 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2469.26 | 0.3807 | 38.4434ms | 409725 | 30 | 1.08878e+07 | 158244 | 1.00231 | 1(Win) |
| glaze | 2176.93 | 0.482917 | 43.4271ms | 409725 | 30 | 2.25405e+07 | 179494 | 1.13691 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1352.04 | 0.27743 | 133.189ms | 785750 | 30 | 7.09278e+07 | 554236 | 1.83086 | 1(Win) |
| glaze | 884.528 | 0.121991 | 203.376ms | 785750 | 30 | 3.2042e+07 | 847175 | 2.79871 | 2(Loss) |
| jsonifier | 742.656 | 0.377926 | 242.468ms | 785750 | 30 | 4.36242e+08 | 1.00901e+06 | 3.33331 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3801.26 | 0.318007 | 47.6818ms | 785750 | 30 | 1.17899e+07 | 197132 | 0.651171 | 1(Win) |
| glaze | 2703.17 | 0.325026 | 89.233ms | 785750 | 30 | 2.43545e+07 | 277212 | 0.915711 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 876.236 | 0.228235 | 2413.87ms | 8587914 | 30 | 1.36527e+10 | 9.34688e+06 | 2.82545 | 1(Win) |
| glaze | 758.471 | 0.47684 | 2571.95ms | 8587914 | 30 | 7.95362e+10 | 1.07981e+07 | 3.26413 | 2(Loss) |
| jsonifier | 717.337 | 0.41564 | 2845.57ms | 8587914 | 30 | 6.75594e+10 | 1.14173e+07 | 3.4513 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2749.36 | 0.165668 | 717.734ms | 8588126 | 30 | 7.30685e+08 | 2.97897e+06 | 0.900409 | 1(Win) |
| jsonifier | 2437.74 | 0.384974 | 758.447ms | 8588126 | 30 | 5.01886e+09 | 3.35978e+06 | 1.01554 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 945.244 | 0.35855 | 2406.75ms | 9804437 | 30 | 3.77378e+10 | 9.89188e+06 | 2.61915 | 1(Win) |
| glaze | 828.835 | 0.222193 | 2768.09ms | 9804437 | 30 | 1.88492e+10 | 1.12812e+07 | 2.98705 | 2(Loss) |
| jsonifier | 678.951 | 0.451584 | 3277.59ms | 9804437 | 30 | 1.16029e+11 | 1.37716e+07 | 3.64639 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2960.06 | 0.253533 | 857.357ms | 11078090 | 30 | 2.45652e+09 | 3.56915e+06 | 0.836332 | 1(Win) |
| glaze | 2586.43 | 0.157572 | 987.592ms | 11078090 | 30 | 1.24281e+09 | 4.08474e+06 | 0.957161 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 4440.35 | 0.8305 | 13.7627ms | 264040 | 30 | 6.65436e+06 | 56709.1 | 0.557277 | 1(Win) |
| jsonifier | 4032 | 0.487924 | 15.331ms | 264040 | 30 | 2.78563e+06 | 62452.4 | 0.61375 | 2(Loss) |
| glaze | 1057.76 | 0.27876 | 57.3575ms | 264040 | 30 | 1.32115e+07 | 238059 | 2.34021 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5686.16 | 0.655448 | 16.3557ms | 399947 | 30 | 5.79916e+06 | 67078.5 | 0.435141 | 1(Win) |
| jsonifier | 5116.05 | 0.545085 | 18.19ms | 399947 | 30 | 4.95432e+06 | 74553.4 | 0.483718 | 2(Loss) |
| glaze | 1468.11 | 0.346229 | 62.784ms | 399947 | 30 | 2.42738e+07 | 259803 | 1.68609 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1308.51 | 0.471225 | 46.7883ms | 264040 | 30 | 2.46695e+07 | 192438 | 1.89147 | 1(Win) |
| glaze STATISTICAL TIE | 1124.25 | 0.40549 | 54.6379ms | 264040 | 30 | 2.47456e+07 | 223979 | 2.20121 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1116.84 | 0.38412 | 55.7336ms | 264040 | 30 | 2.25015e+07 | 225464 | 2.2162 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3256.55 | 0.865775 | 19.1424ms | 264040 | 30 | 1.34448e+07 | 77323.6 | 0.759932 | 1(Tie) |
| glaze STATISTICAL TIE | 3233 | 0.571558 | 19.1529ms | 263923 | 30 | 5.93998e+06 | 77852.4 | 0.76528 | 1(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1895.09 | 0.503962 | 49.2558ms | 399947 | 30 | 3.08648e+07 | 201267 | 1.30601 | 1(Win) |
| glaze | 1350.33 | 0.583194 | 68.6108ms | 399947 | 30 | 8.14088e+07 | 282463 | 1.83298 | 2(Loss) |
| jsonifier | 1140.27 | 0.696788 | 80.3048ms | 399947 | 30 | 1.62972e+08 | 334499 | 2.17044 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4303.95 | 0.424862 | 21.8731ms | 399947 | 30 | 4.25292e+06 | 88620.6 | 0.574988 | 1(Win) |
| glaze | 3603.79 | 0.666096 | 26.3096ms | 399830 | 30 | 1.49014e+07 | 105807 | 0.686642 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1888.82 | 0.288721 | 57.0777ms | 466906 | 30 | 1.38982e+07 | 235743 | 1.31047 | 1(Win) |
| glaze | 1714.3 | 0.239388 | 62.81ms | 466906 | 30 | 1.15987e+07 | 259742 | 1.44386 | 2(Loss) |
| simdjson (ondemand) | 894.864 | 0.871837 | 117.872ms | 466906 | 30 | 5.64595e+08 | 497591 | 2.76623 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3161.17 | 0.414899 | 50.1634ms | 699405 | 30 | 2.29916e+07 | 210999 | 0.782998 | 1(Win) |
| glaze | 2524.6 | 0.281443 | 63.0696ms | 699405 | 30 | 1.65872e+07 | 264202 | 0.980458 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1798.84 | 0.218214 | 80.6828ms | 631514 | 30 | 1.60128e+07 | 334804 | 1.37613 | 1(Win) |
| glaze | 1756.74 | 0.312531 | 82.4395ms | 631514 | 30 | 3.44396e+07 | 342827 | 1.40915 | 2(Loss) |
