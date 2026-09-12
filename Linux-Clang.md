# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 20.1.8 compiler).  

Latest Results: (Sep 12, 2026)
#### Using the following commits:
----
| Jsonifier: [8fed030](https://github.com/nihilai-collective/jsonifier/commit/8fed030)  
| Glaze: [52fb059](https://github.com/stephenberry/glaze/commit/52fb059)  
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
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 592.753 | 0.141748 | 2.75375ms | 1811 | 30 | 511.734 | 2913.7 | 3.88351 | 1(Win) |
| glaze | 480.245 | 0.102129 | 1.13421ms | 1811 | 30 | 404.7 | 3596.3 | 4.80617 | 2(Loss) |
| simdjson (ondemand) | 145.543 | 0.404656 | 3.30757ms | 1811 | 30 | 69174.8 | 11866.6 | 15.974 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 367.438 | 0.100435 | 1.48731ms | 1811 | 30 | 668.593 | 4700.4 | 6.30068 | 1(Win) |
| glaze | 273.211 | 0.172939 | 3.96455ms | 1798 | 32 | 3769.79 | 6276.12 | 8.48613 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1342.89 | 0.120189 | 1.03513ms | 3873 | 30 | 327.844 | 2750.47 | 1.71306 | 1(Win) |
| glaze | 1013.74 | 0.072576 | 1.13817ms | 3873 | 30 | 209.775 | 3643.53 | 2.27645 | 2(Loss) |
| simdjson (ondemand) | 352.893 | 0.0584665 | 2.81449ms | 3873 | 30 | 1123.43 | 10466.6 | 6.58604 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1470.96 | 0.114488 | 0.928026ms | 3873 | 30 | 247.931 | 2511 | 1.5629 | 1(Win) |
| glaze | 1053.27 | 0.149418 | 2.37312ms | 3873 | 32 | 878.564 | 3506.78 | 2.19072 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1334.94 | 0.130741 | 1.02111ms | 3862 | 30 | 390.345 | 2759 | 1.72446 | 1(Win) |
| glaze | 813.026 | 0.0890584 | 1.36282ms | 3862 | 30 | 488.3 | 4530.1 | 2.8446 | 2(Loss) |
| simdjson (ondemand) | 351.809 | 0.0443863 | 6.39ms | 3862 | 32 | 690.968 | 10469 | 6.60632 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1626.59 | 0.163378 | 0.910003ms | 3862 | 30 | 410.562 | 2264.3 | 1.41048 | 1(Win) |
| glaze | 1030.81 | 0.16206 | 1.16448ms | 3862 | 30 | 1005.86 | 3573 | 2.23751 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 616.805 | 0.0638231 | 0.598253ms | 905 | 30 | 23.9264 | 1399.27 | 3.68088 | 1(Win) |
| glaze | 454.37 | 0.226524 | 0.706194ms | 905 | 30 | 555.431 | 1899.5 | 5.03186 | 2(Loss) |
| simdjson (ondemand) | 119.496 | 0.0601831 | 4.41035ms | 905 | 32 | 604.629 | 7222.62 | 19.4154 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 689.564 | 0.279308 | 1.11775ms | 905 | 32 | 391.081 | 1251.62 | 3.28743 | 1(Win) |
| glaze | 277.561 | 0.144059 | 1.02863ms | 905 | 30 | 601.983 | 3109.5 | 8.29842 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1984.16 | 0.0680457 | 1.4545ms | 9578 | 30 | 294.386 | 4603.6 | 1.16556 | 1(Win) |
| glaze | 1453.51 | 0.0974195 | 3.9365ms | 9578 | 32 | 1199.37 | 6284.28 | 1.59528 | 2(Loss) |
| simdjson (ondemand) | 780.522 | 0.163004 | 3.15047ms | 9578 | 30 | 10916.8 | 11702.8 | 2.97796 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3186.01 | 0.119839 | 0.986445ms | 9578 | 30 | 354.138 | 2867 | 0.722451 | 1(Win) |
| glaze | 2203.01 | 0.158364 | 2.67607ms | 9578 | 32 | 1379.69 | 4146.28 | 1.049 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2795.31 | 1.35481 | 19.7926ms | 233995 | 30 | 3.50936e+07 | 79831.8 | 0.833779 | 1(Win) |
| simdjson (ondemand) | 1495.27 | 0.633767 | 36.2197ms | 233995 | 30 | 2.68384e+07 | 149241 | 1.55908 | 2(Loss) |
| glaze | 846.905 | 0.451422 | 63.3668ms | 233995 | 30 | 4.24453e+07 | 263495 | 2.75312 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3316.96 | 0.562542 | 24.3263ms | 346753 | 30 | 9.43607e+06 | 99696.5 | 0.702685 | 1(Win) |
| jsonifier | 1913.61 | 0.61269 | 41.9719ms | 346753 | 30 | 3.36306e+07 | 172809 | 1.21824 | 2(Loss) |
| glaze | 1824.07 | 0.597746 | 43.8121ms | 346753 | 30 | 3.52299e+07 | 181292 | 1.27819 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1243.56 | 0.642125 | 43.8884ms | 233995 | 30 | 3.98325e+07 | 179448 | 1.87467 | 1(Win) |
| glaze | 926.634 | 0.512336 | 58.6708ms | 233995 | 30 | 4.56696e+07 | 240823 | 2.51626 | 2(Loss) |
| simdjson (ondemand) | 846.814 | 0.408812 | 63.5454ms | 233995 | 30 | 3.48181e+07 | 263523 | 2.75322 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2242.85 | 1.08144 | 24.2009ms | 233995 | 30 | 3.47326e+07 | 99496.1 | 1.03921 | 1(Win) |
| glaze | 1687.6 | 0.958822 | 32.9607ms | 233995 | 30 | 4.8225e+07 | 132232 | 1.3812 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1270.87 | 0.577995 | 63.1845ms | 346753 | 30 | 6.7859e+07 | 260207 | 1.8344 | 1(Win) |
| glaze | 1248.62 | 0.526238 | 64.1249ms | 346753 | 30 | 5.82731e+07 | 264844 | 1.86731 | 2(Loss) |
| simdjson (ondemand) | 1191.64 | 0.498813 | 67.1866ms | 346753 | 30 | 5.74841e+07 | 277508 | 1.95653 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2028.73 | 0.589736 | 40.6434ms | 346753 | 30 | 2.77222e+07 | 163003 | 1.14907 | 1(Win) |
| glaze | 1604.22 | 0.593793 | 49.7014ms | 346753 | 30 | 4.49475e+07 | 206138 | 1.45326 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2754.27 | 0.930249 | 19.9155ms | 233995 | 30 | 1.70419e+07 | 81021.3 | 0.846039 | 1(Win) |
| simdjson (ondemand) | 1879.96 | 0.458491 | 28.9795ms | 233995 | 30 | 8.88589e+06 | 118702 | 1.23999 | 2(Loss) |
| glaze | 1471.9 | 0.538487 | 36.8126ms | 233995 | 30 | 1.99954e+07 | 151610 | 1.58379 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3421.12 | 0.827062 | 23.6565ms | 346753 | 30 | 1.91735e+07 | 96661.2 | 0.681166 | 1(Win) |
| simdjson (ondemand) | 2450.46 | 0.743978 | 32.5791ms | 346753 | 30 | 3.02403e+07 | 134950 | 0.951263 | 2(Loss) |
| glaze | 1787.54 | 0.535722 | 44.8179ms | 346753 | 30 | 2.94665e+07 | 184997 | 1.30416 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1150.07 | 0.601175 | 47.3841ms | 233995 | 30 | 4.08212e+07 | 194035 | 2.02711 | 1(Win) |
| glaze | 949.315 | 0.571728 | 57.1061ms | 233995 | 30 | 5.41868e+07 | 235070 | 2.4559 | 2(Loss) |
| simdjson (ondemand) | 216.707 | 0.132565 | 247.811ms | 233995 | 30 | 5.59043e+07 | 1.02975e+06 | 10.761 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2252.15 | 1.05708 | 24.5066ms | 233995 | 30 | 3.2912e+07 | 99085.3 | 1.03481 | 1(Win) |
| glaze | 1822.46 | 0.937671 | 30.1887ms | 233995 | 30 | 3.95477e+07 | 122447 | 1.27904 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1262.27 | 0.303786 | 63.9191ms | 346753 | 30 | 1.90019e+07 | 261981 | 1.84711 | 1(Win) |
| jsonifier | 1175.24 | 0.538281 | 68.1669ms | 346753 | 30 | 6.88217e+07 | 281380 | 1.98395 | 2(Loss) |
| simdjson (ondemand) | 311.725 | 0.159919 | 254.743ms | 346753 | 30 | 8.63415e+07 | 1.06084e+06 | 7.48094 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2074.45 | 0.757802 | 38.2276ms | 346753 | 30 | 4.37792e+07 | 159411 | 1.12376 | 1(Win) |
| glaze | 1566.62 | 1.53972 | 50.0262ms | 346753 | 30 | 3.16897e+08 | 211085 | 1.48812 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 687.849 | 0.818404 | 31.9737ms | 94651 | 30 | 3.46035e+07 | 131230 | 3.3889 | 1(Win) |
| simdjson (ondemand) | 629.332 | 2.40596 | 34.4002ms | 94651 | 30 | 3.57264e+08 | 143432 | 3.70427 | 2(Loss) |
| glaze | 572.482 | 0.649981 | 38.2511ms | 94651 | 30 | 3.15101e+07 | 157675 | 4.07223 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2736.79 | 0.94478 | 8.3524ms | 94651 | 30 | 2.91306e+06 | 32982.5 | 0.850748 | 1(Tie) |
| glaze STATISTICAL TIE | 2663.64 | 1.00565 | 19.5297ms | 94651 | 32 | 3.7166e+06 | 33888.3 | 0.874163 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 899.921 | 0.856618 | 35.0104ms | 136024 | 30 | 4.57423e+07 | 144149 | 2.59056 | 1(Win) |
| glaze | 826.142 | 0.571687 | 38.6648ms | 136024 | 30 | 2.41746e+07 | 157022 | 2.82181 | 2(Loss) |
| jsonifier | 781.577 | 0.743518 | 40.3723ms | 136024 | 30 | 4.56869e+07 | 165975 | 2.98296 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3182.79 | 1.19816 | 10.1991ms | 136024 | 30 | 7.15431e+06 | 40757.5 | 0.731887 | 1(Win) |
| glaze | 1829.81 | 0.997013 | 17.478ms | 136046 | 30 | 1.49929e+07 | 70905.6 | 1.27331 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 449.412 | 0.101689 | 1069.29ms | 2090234 | 30 | 6.1033e+08 | 4.43558e+06 | 5.18925 | 1(Win) |
| glaze | 387.052 | 0.137305 | 1236.96ms | 2090234 | 30 | 1.50018e+09 | 5.15021e+06 | 6.02531 | 2(Loss) |
| simdjson (ondemand) | 306.654 | 0.0860044 | 1560.45ms | 2090234 | 30 | 9.3768e+08 | 6.50048e+06 | 7.60505 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 659.46 | 0.14933 | 740.693ms | 2090234 | 30 | 6.11267e+08 | 3.02278e+06 | 3.53635 | 1(Win) |
| glaze | 640.273 | 0.0737711 | 745.534ms | 2090234 | 30 | 1.58254e+08 | 3.11337e+06 | 3.64235 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1103.44 | 0.300365 | 1381.94ms | 6661897 | 30 | 8.97265e+09 | 5.75772e+06 | 2.1135 | 1(Win) |
| glaze | 994.691 | 0.131053 | 1531.22ms | 6661897 | 30 | 2.10201e+09 | 6.38719e+06 | 2.34457 | 2(Loss) |
| simdjson (ondemand) | 920.409 | 0.121795 | 1664.24ms | 6661897 | 30 | 2.12039e+09 | 6.90267e+06 | 2.53379 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1922.85 | 0.132143 | 801.384ms | 6661897 | 30 | 5.71897e+08 | 3.3041e+06 | 1.21283 | 1(Win) |
| glaze | 1490.22 | 0.289738 | 1050.48ms | 6661897 | 30 | 4.57746e+09 | 4.2633e+06 | 1.5649 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1013.55 | 0.311899 | 113.306ms | 500299 | 30 | 6.4673e+07 | 470746 | 2.30062 | 1(Win) |
| glaze | 821.403 | 0.300137 | 139.975ms | 500299 | 30 | 9.11814e+07 | 580863 | 2.83892 | 2(Loss) |
| simdjson (ondemand) | 506.352 | 0.123238 | 226.736ms | 500299 | 30 | 4.04543e+07 | 942273 | 4.60546 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1964.98 | 0.465089 | 58.8268ms | 500299 | 30 | 3.82594e+07 | 242813 | 1.18656 | 1(Win) |
| jsonifier | 1778.6 | 0.504084 | 65.3366ms | 500299 | 30 | 5.48567e+07 | 268257 | 1.31088 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1783.75 | 0.234527 | 184.964ms | 1439562 | 30 | 9.77463e+07 | 769656 | 1.30733 | 1(Win) |
| glaze | 1542.29 | 0.35413 | 214.421ms | 1439562 | 30 | 2.98109e+08 | 890153 | 1.51203 | 2(Loss) |
| simdjson (ondemand) | 1327.42 | 0.239003 | 248.567ms | 1439562 | 30 | 1.83303e+08 | 1.03424e+06 | 1.75679 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3288.85 | 0.632183 | 103.19ms | 1439562 | 30 | 2.08919e+08 | 417432 | 0.708981 | 1(Win) |
| glaze | 2165.57 | 0.365177 | 159.629ms | 1439584 | 30 | 1.60789e+08 | 633963 | 1.07679 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 927.772 | 0.878372 | 14.4664ms | 56369 | 30 | 7.771e+06 | 57942.8 | 2.51156 | 1(Win) |
| glaze | 785.64 | 0.672717 | 16.8347ms | 56369 | 30 | 6.35652e+06 | 68425.3 | 2.96633 | 2(Loss) |
| simdjson (ondemand) | 633.515 | 1.42757 | 20.3049ms | 56369 | 30 | 4.40233e+07 | 84856.2 | 3.67901 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1896.71 | 1.08242 | 7.12827ms | 56369 | 30 | 2.82352e+06 | 28342.6 | 1.22782 | 1(Win) |
| jsonifier | 1057.26 | 1.57966 | 12.4532ms | 56369 | 30 | 1.93537e+07 | 50846.2 | 2.20402 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1098.73 | 1.00059 | 20.0584ms | 94370 | 30 | 2.01518e+07 | 81910.8 | 2.12127 | 1(Win) |
| jsonifier | 1059.48 | 0.814346 | 21.0802ms | 94370 | 30 | 1.43556e+07 | 84945.7 | 2.19933 | 2(Loss) |
| simdjson (ondemand) | 1016.92 | 1.09365 | 21.5662ms | 94370 | 30 | 2.81043e+07 | 88501 | 2.292 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2376.2 | 1.83675 | 9.33544ms | 94370 | 30 | 1.45185e+07 | 37874.9 | 0.980345 | 1(Win) |
| glaze | 1723.88 | 1.44634 | 12.6648ms | 94370 | 30 | 1.71049e+07 | 52206.9 | 1.35134 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 824.931 | 1.38973 | 15.0057ms | 52708 | 30 | 2.15128e+07 | 60933.9 | 2.82451 | 1(Win) |
| jsonifier | 751.553 | 2.47259 | 16.5342ms | 52708 | 30 | 8.20466e+07 | 66883.2 | 3.0986 | 2(Loss) |
| glaze | 688.883 | 1.26189 | 18.199ms | 52708 | 30 | 2.54349e+07 | 72967.8 | 3.38205 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2678.96 | 1.34527 | 10.8974ms | 52708 | 32 | 2.03887e+06 | 18763.4 | 0.867725 | 1(Win) |
| jsonifier | 2474.66 | 2.06503 | 5.23519ms | 52708 | 30 | 5.27835e+06 | 20312.4 | 0.939906 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1083.52 | 1.51113 | 15.3013ms | 70103 | 30 | 2.6081e+07 | 61702.2 | 2.15051 | 1(Win) |
| glaze | 841.201 | 1.21032 | 19.6317ms | 70103 | 30 | 2.77585e+07 | 79476.2 | 2.77012 | 2(Loss) |
| jsonifier | 734.305 | 1.38507 | 22.779ms | 70103 | 30 | 4.77075e+07 | 91045.8 | 3.17202 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2392.56 | 2.29539 | 6.9296ms | 70103 | 30 | 1.23419e+07 | 27943 | 0.973201 | 1(Win) |
| jsonifier | 1524.24 | 1.10717 | 11.0179ms | 70103 | 30 | 7.07488e+06 | 43861.6 | 1.52815 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 705.699 | 2.1093 | 9.33243ms | 11812 | 32 | 3.62772e+06 | 15962.6 | 3.29681 | 1(Win) |
| glaze | 577.415 | 0.422228 | 5.16571ms | 11812 | 30 | 203557 | 19509 | 4.03168 | 2(Loss) |
| simdjson (ondemand) | 559.601 | 0.0365165 | 5.21617ms | 11812 | 30 | 1621.03 | 20130.1 | 4.16009 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2284.7 | 0.215999 | 1.46607ms | 11812 | 30 | 3402.6 | 4930.53 | 1.01337 | 1(Win) |
| glaze | 1190.17 | 0.130585 | 2.58151ms | 11812 | 30 | 4582.92 | 9464.9 | 1.95171 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1369.55 | 1.34633 | 5.6136ms | 31235 | 30 | 2.57247e+06 | 21750.2 | 1.70003 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1307.93 | 2.20972 | 5.70215ms | 31235 | 30 | 7.59822e+06 | 22775 | 1.78009 | 1(Tie) |
| glaze | 1118.62 | 0.222125 | 15.4443ms | 31235 | 32 | 111959 | 26629.2 | 2.08193 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2383.87 | 2.09174 | 6.90776ms | 31235 | 32 | 2.18617e+06 | 12495.7 | 0.975592 | 1(Win) |
| glaze | 1799.27 | 0.331435 | 4.18535ms | 31235 | 30 | 90325.1 | 16555.6 | 1.29323 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1831.64 | 1.41664 | 13.964ms | 108313 | 30 | 1.9148e+07 | 56394.9 | 1.27207 | 1(Win) |
| glaze | 1014.45 | 1.12486 | 25.2543ms | 108313 | 30 | 3.93568e+07 | 101824 | 2.29786 | 2(Loss) |
| simdjson (ondemand) | 780.211 | 0.633105 | 32.15ms | 108313 | 30 | 2.10771e+07 | 132394 | 2.98811 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1815.92 | 1.36974 | 13.8073ms | 108313 | 30 | 1.82123e+07 | 56883.2 | 1.28345 | 1(Win) |
| glaze | 1664.72 | 1.17105 | 15.0429ms | 108313 | 30 | 1.58398e+07 | 62049.7 | 1.4 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1486.9 | 0.697048 | 33.3589ms | 213963 | 30 | 2.74511e+07 | 137232 | 1.56791 | 1(Win) |
| simdjson (ondemand) | 1458.73 | 0.591914 | 34.1098ms | 213963 | 30 | 2.05669e+07 | 139883 | 1.59816 | 2(Loss) |
| jsonifier | 1391.11 | 0.867993 | 35.8767ms | 213963 | 30 | 4.86305e+07 | 146682 | 1.6757 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2767.87 | 0.789662 | 17.6928ms | 213963 | 30 | 1.0167e+07 | 73721.4 | 0.842091 | 1(Win) |
| glaze | 1631.82 | 0.804915 | 30.1596ms | 213963 | 30 | 3.03915e+07 | 125045 | 1.42842 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 468.369 | 0.101028 | 898.075ms | 1834197 | 30 | 4.27089e+08 | 3.73472e+06 | 4.97912 | 1(Win) |
| glaze | 348.26 | 0.129695 | 1206.72ms | 1834197 | 30 | 1.27307e+09 | 5.02276e+06 | 6.69645 | 2(Loss) |
| simdjson (ondemand) | 268.218 | 0.0674722 | 1570.26ms | 1834197 | 30 | 5.80882e+08 | 6.52167e+06 | 8.69481 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 386.075 | 0.0782075 | 1089.36ms | 1834197 | 30 | 3.76676e+08 | 4.5308e+06 | 6.04055 | 1(Win) |
| glaze | 379.405 | 0.116333 | 1109.06ms | 1833577 | 30 | 8.62415e+08 | 4.60889e+06 | 6.14672 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1469.29 | 0.748318 | 1548.48ms | 9930848 | 30 | 6.97997e+10 | 6.44585e+06 | 1.58722 | 1(Win) |
| glaze | 1330.53 | 0.119636 | 1704.03ms | 9930848 | 30 | 2.17558e+09 | 7.11809e+06 | 1.75275 | 2(Loss) |
| simdjson (ondemand) | 1296.17 | 0.151232 | 1748.3ms | 9930848 | 30 | 3.66313e+09 | 7.30673e+06 | 1.79911 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1574.01 | 0.27853 | 1432.63ms | 9930848 | 30 | 8.42598e+09 | 6.01698e+06 | 1.48158 | 1(Win) |
| glaze | 1259.39 | 0.378677 | 1787.18ms | 9930228 | 30 | 2.4325e+10 | 7.51965e+06 | 1.85168 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 834.441 | 0.579527 | 176.537ms | 642697 | 30 | 5.43613e+08 | 734532 | 2.79457 | 1(Win) |
| glaze | 734.993 | 0.184581 | 201.246ms | 642697 | 30 | 7.1079e+07 | 833918 | 3.17266 | 2(Loss) |
| simdjson (ondemand) | 559.688 | 0.155775 | 262.647ms | 642697 | 30 | 8.73045e+07 | 1.09512e+06 | 4.1666 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 683.993 | 0.12095 | 215.375ms | 642697 | 30 | 3.52404e+07 | 896097 | 3.40934 | 1(Win) |
| glaze | 629.822 | 0.171968 | 238.034ms | 642692 | 30 | 8.40205e+07 | 973162 | 3.70262 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1176.38 | 0.104352 | 239.83ms | 1225964 | 30 | 3.22692e+07 | 993874 | 1.98234 | 1(Win) |
| glaze | 1138.93 | 0.369878 | 245.908ms | 1225964 | 30 | 4.3251e+08 | 1.02655e+06 | 2.04747 | 2(Loss) |
| simdjson (ondemand) | 1033.39 | 0.162234 | 273.284ms | 1225964 | 30 | 1.01072e+08 | 1.13139e+06 | 2.25665 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1227.78 | 0.226255 | 231.825ms | 1225964 | 30 | 1.39262e+08 | 952262 | 1.89934 | 1(Win) |
| glaze | 996.324 | 0.253896 | 281.409ms | 1225970 | 30 | 2.66313e+08 | 1.17349e+06 | 2.34061 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 599.692 | 0.417943 | 156.742ms | 409725 | 30 | 2.22476e+08 | 651574 | 3.88851 | 1(Win) |
| simdjson (ondemand) | 487.735 | 0.487917 | 192.582ms | 409725 | 30 | 4.58384e+08 | 801140 | 4.78119 | 2(Loss) |
| glaze | 372.977 | 0.13855 | 252.921ms | 409725 | 30 | 6.32051e+07 | 1.04764e+06 | 6.25244 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1341.33 | 0.41997 | 70.7261ms | 409725 | 30 | 4.49028e+07 | 291312 | 1.73827 | 1(Win) |
| jsonifier | 1183.95 | 0.435381 | 77.9177ms | 409725 | 30 | 6.19408e+07 | 330034 | 1.96924 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 887.058 | 0.200184 | 203.625ms | 785750 | 30 | 8.57914e+07 | 844758 | 2.6289 | 1(Win) |
| jsonifier | 752.289 | 0.343468 | 238.843ms | 785750 | 30 | 3.5115e+08 | 996093 | 3.09983 | 2(Loss) |
| glaze | 673.846 | 0.104294 | 267.522ms | 785750 | 30 | 4.03538e+07 | 1.11205e+06 | 3.46074 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1862.55 | 0.348238 | 99.9382ms | 785750 | 30 | 5.88878e+07 | 402324 | 1.25193 | 1(Win) |
| glaze | 1584.09 | 0.282217 | 114.632ms | 785750 | 30 | 5.34686e+07 | 473049 | 1.47203 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 720.656 | 0.702231 | 2751.77ms | 8587914 | 30 | 1.91074e+11 | 1.13647e+07 | 3.23606 | 1(Win) |
| simdjson (ondemand) | 617.085 | 0.473379 | 3164.19ms | 8587914 | 30 | 1.1842e+11 | 1.32722e+07 | 3.77921 | 2(Loss) |
| glaze | 567.353 | 0.487404 | 3408.33ms | 8587914 | 30 | 1.48514e+11 | 1.44356e+07 | 4.11049 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2094.79 | 0.398471 | 952.504ms | 8588126 | 30 | 7.28168e+09 | 3.90983e+06 | 1.11326 | 1(Tie) |
| glaze STATISTICAL TIE | 2066.94 | 0.835005 | 944.606ms | 8588126 | 30 | 3.28429e+10 | 3.96251e+06 | 1.12824 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 719.874 | 0.397503 | 3165.87ms | 9804437 | 30 | 7.99712e+10 | 1.29887e+07 | 3.2396 | 1(Win) |
| jsonifier | 695.62 | 0.430265 | 3218.94ms | 9804437 | 30 | 1.00345e+11 | 1.34416e+07 | 3.35255 | 2(Loss) |
| glaze | 636.893 | 0.416514 | 3513.96ms | 9804437 | 30 | 1.12174e+11 | 1.4681e+07 | 3.66166 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2379.24 | 0.315186 | 1091.78ms | 11078090 | 30 | 5.87638e+09 | 4.44045e+06 | 0.980131 | 1(Win) |
| glaze | 2063.89 | 0.214872 | 1244.94ms | 11078090 | 30 | 3.62942e+09 | 5.11891e+06 | 1.12989 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2872.23 | 0.665061 | 21.5756ms | 264040 | 30 | 1.01988e+07 | 87670.1 | 0.81147 | 1(Win) |
| simdjson (ondemand) | 2652.35 | 0.91148 | 23.285ms | 264040 | 30 | 2.24644e+07 | 94937.9 | 0.878696 | 2(Loss) |
| glaze | 1160.88 | 0.567556 | 52.3814ms | 264040 | 30 | 4.54677e+07 | 216911 | 2.00847 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3691.82 | 0.781586 | 25.4302ms | 399947 | 30 | 1.95613e+07 | 103315 | 0.631298 | 1(Win) |
| simdjson (ondemand) | 3536.1 | 0.613614 | 26.3918ms | 399947 | 30 | 1.31421e+07 | 107864 | 0.659156 | 2(Loss) |
| glaze | 1570.13 | 0.595975 | 58.5881ms | 399947 | 30 | 6.28796e+07 | 242922 | 1.48496 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 949.969 | 0.633743 | 64.3207ms | 264040 | 30 | 8.4658e+07 | 265070 | 2.45419 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 842.333 | 0.67054 | 72.4045ms | 264040 | 30 | 1.20543e+08 | 298941 | 2.76798 | 2(Tie) |
| glaze STATISTICAL TIE | 829.73 | 0.537258 | 73.5149ms | 264040 | 30 | 7.97543e+07 | 303482 | 2.81008 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2458.6 | 0.824596 | 25.101ms | 264040 | 30 | 2.13977e+07 | 102419 | 0.948124 | 1(Win) |
| glaze | 2266.79 | 0.546568 | 27.43ms | 263923 | 30 | 1.10495e+07 | 111037 | 1.02821 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1206.01 | 0.461974 | 77.4003ms | 399947 | 30 | 6.40409e+07 | 316265 | 1.93334 | 1(Win) |
| glaze | 1028.57 | 0.845049 | 90.0575ms | 399947 | 30 | 2.94591e+08 | 370824 | 2.26687 | 2(Loss) |
| jsonifier | 953.739 | 0.549046 | 96.7721ms | 399947 | 30 | 1.44639e+08 | 399920 | 2.44482 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2823.78 | 0.816817 | 33.0334ms | 399947 | 30 | 3.65186e+07 | 135074 | 0.825398 | 1(Win) |
| glaze | 2258.69 | 0.517905 | 41.2171ms | 399830 | 30 | 2.29328e+07 | 168818 | 1.03212 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1381.21 | 0.394047 | 78.9144ms | 466906 | 30 | 4.84125e+07 | 322381 | 1.68818 | 1(Win) |
| jsonifier | 1183.14 | 0.460736 | 89.1624ms | 466906 | 30 | 9.02007e+07 | 376350 | 1.9707 | 2(Loss) |
| simdjson (ondemand) | 633.942 | 0.267182 | 169.199ms | 466906 | 30 | 1.05657e+08 | 702393 | 3.67838 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1934.2 | 0.454775 | 82.2909ms | 699405 | 30 | 7.37855e+07 | 344849 | 1.20547 | 1(Tie) |
| glaze STATISTICAL TIE | 1913.91 | 0.301057 | 85.0615ms | 699405 | 30 | 3.30243e+07 | 348504 | 1.21835 | 1(Tie) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2297.89 | 0.750484 | 63.3104ms | 631514 | 30 | 1.16068e+08 | 262092 | 1.01465 | 1(Win) |
| glaze | 1538.79 | 0.462922 | 93.9991ms | 631514 | 30 | 9.84784e+07 | 391383 | 1.51533 | 2(Loss) |
