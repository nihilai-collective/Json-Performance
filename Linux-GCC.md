# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [57ce61b](https://github.com/nihilai-collective/jsonifier/commit/57ce61b)  
| Glaze: [29f478d](https://github.com/stephenberry/glaze/commit/29f478d)  
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
| jsonifier | 651.164 | 0.122155 | 1.84578ms | 1811 | 30 | 314.92 | 2652.33 | 3.53135 | 1(Win) |
| glaze | 466.141 | 0.0687313 | 11.1058ms | 1811 | 128 | 830.082 | 3705.11 | 4.95245 | 2(Loss) |
| simdjson (ondemand) | 140.262 | 0.102178 | 3.22188ms | 1811 | 30 | 4748.87 | 12313.4 | 16.5773 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 391.616 | 0.349894 | 1.36091ms | 1811 | 30 | 7143.48 | 4410.2 | 5.90523 | 1(Win) |
| glaze | 267.684 | 0.299677 | 1.78524ms | 1798 | 30 | 11055 | 6405.7 | 8.6604 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1307.01 | 0.118528 | 0.986343ms | 3873 | 30 | 336.585 | 2825.97 | 1.76197 | 1(Win) |
| glaze | 1111.02 | 0.0934521 | 0.989749ms | 3873 | 30 | 289.569 | 3324.5 | 2.07573 | 2(Loss) |
| simdjson (ondemand) | 298.548 | 2.20696 | 3.19177ms | 3873 | 30 | 2.23655e+06 | 12371.8 | 7.78918 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1722.03 | 0.145545 | 0.821205ms | 3873 | 30 | 292.369 | 2144.9 | 1.32953 | 1(Win) |
| glaze | 967.886 | 0.364428 | 1.20236ms | 3873 | 30 | 5802.19 | 3816.13 | 2.38674 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1277.8 | 0.111976 | 0.962278ms | 3862 | 30 | 312.516 | 2882.37 | 1.8019 | 1(Win) |
| glaze | 963.353 | 0.0947431 | 1.15125ms | 3862 | 30 | 393.614 | 3823.2 | 2.39733 | 2(Loss) |
| simdjson (ondemand) | 294.139 | 1.82583 | 16.5112ms | 3862 | 64 | 3.34517e+06 | 12521.6 | 7.90564 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1638.75 | 0.0932031 | 0.876187ms | 3862 | 30 | 131.638 | 2247.5 | 1.39967 | 1(Win) |
| glaze | 960.756 | 0.337883 | 1.13999ms | 3862 | 30 | 5033.29 | 3833.53 | 2.40369 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 771.062 | 0.083975 | 0.566619ms | 905 | 30 | 26.5057 | 1119.33 | 2.93098 | 1(Win) |
| glaze | 486.422 | 0.557524 | 0.662398ms | 905 | 30 | 2935.75 | 1774.33 | 4.69702 | 2(Loss) |
| simdjson (ondemand) | 98.2815 | 0.175101 | 2.40179ms | 905 | 30 | 7093.33 | 8781.67 | 23.629 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 829.481 | 0.156384 | 0.528648ms | 905 | 30 | 79.431 | 1040.5 | 2.71621 | 1(Win) |
| glaze | 309.065 | 0.195398 | 0.891717ms | 905 | 30 | 893.223 | 2792.53 | 7.44843 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1694.21 | 0.0636377 | 1.65057ms | 9578 | 30 | 353.154 | 5391.47 | 1.3669 | 1(Win) |
| glaze | 1410.45 | 0.0680793 | 1.82081ms | 9578 | 30 | 583.154 | 6476.13 | 1.64365 | 2(Loss) |
| simdjson (ondemand) | 725.855 | 0.681669 | 7.46139ms | 9578 | 32 | 235476 | 12584.2 | 3.20366 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3038.38 | 0.172983 | 1.00242ms | 9578 | 30 | 811.321 | 3006.3 | 0.758523 | 1(Win) |
| glaze | 1312.58 | 0.139721 | 1.9513ms | 9578 | 30 | 2836.24 | 6959.03 | 1.76584 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2555.62 | 0.881652 | 21.2711ms | 233995 | 30 | 1.77801e+07 | 87319.2 | 0.911933 | 1(Win) |
| simdjson (ondemand) | 2466.87 | 0.86809 | 21.9449ms | 233995 | 30 | 1.85e+07 | 90460.9 | 0.944771 | 2(Loss) |
| glaze | 1281.38 | 0.433626 | 42.1849ms | 233995 | 30 | 1.71083e+07 | 174152 | 1.81951 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3129.75 | 0.638994 | 25.6542ms | 346753 | 30 | 1.36753e+07 | 105660 | 0.744777 | 1(Win) |
| jsonifier | 2756.9 | 1.60497 | 28.7698ms | 346753 | 30 | 1.11186e+08 | 119950 | 0.845393 | 2(Loss) |
| glaze | 1593.21 | 0.5188 | 50.0968ms | 346753 | 30 | 3.4787e+07 | 207562 | 1.46341 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1071.59 | 0.386989 | 51.2082ms | 233995 | 30 | 1.94839e+07 | 208247 | 2.1758 | 1(Win) |
| glaze | 1028.65 | 0.445054 | 52.8459ms | 233995 | 30 | 2.79657e+07 | 216940 | 2.26667 | 2(Loss) |
| simdjson (ondemand) | 871.423 | 0.470408 | 61.9639ms | 233995 | 30 | 4.35337e+07 | 256081 | 2.67558 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2078.44 | 0.62297 | 26.5755ms | 233995 | 30 | 1.34213e+07 | 107367 | 1.12151 | 1(Win) |
| glaze | 1911.87 | 0.783079 | 28.3504ms | 233995 | 30 | 2.50627e+07 | 116721 | 1.21918 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1220.09 | 0.308871 | 65.9948ms | 346753 | 30 | 2.10247e+07 | 271036 | 1.91103 | 1(Win) |
| glaze | 1170.78 | 0.546522 | 68.1672ms | 346753 | 30 | 7.14868e+07 | 282452 | 1.99148 | 2(Loss) |
| jsonifier | 918.178 | 0.431529 | 87.2199ms | 346753 | 30 | 7.2465e+07 | 360158 | 2.53945 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2222.74 | 0.572364 | 36.0365ms | 346753 | 30 | 2.17534e+07 | 148775 | 1.04877 | 1(Win) |
| glaze | 1773.19 | 0.526972 | 45.2788ms | 346753 | 30 | 2.89753e+07 | 186494 | 1.31479 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2543.98 | 0.502022 | 21.6854ms | 233995 | 30 | 5.8177e+06 | 87718.8 | 0.916114 | 1(Win) |
| simdjson (ondemand) | 1686.58 | 0.826276 | 32.7004ms | 233995 | 30 | 3.58568e+07 | 132312 | 1.3823 | 2(Loss) |
| glaze | 1265.68 | 1.06388 | 42.0501ms | 233995 | 30 | 1.05553e+08 | 176312 | 1.84208 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2765.57 | 0.549983 | 29.2589ms | 346753 | 30 | 1.29745e+07 | 119574 | 0.842797 | 1(Win) |
| simdjson (ondemand) | 2224.74 | 0.6004 | 36.1259ms | 346753 | 30 | 2.38938e+07 | 148642 | 1.04793 | 2(Loss) |
| glaze | 1592.59 | 0.613749 | 50.1568ms | 346753 | 30 | 4.87234e+07 | 207643 | 1.46402 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 988.703 | 0.515645 | 55.3537ms | 233995 | 30 | 4.06354e+07 | 225705 | 2.35821 | 1(Win) |
| jsonifier | 917.618 | 0.650522 | 59.0261ms | 233995 | 30 | 7.50819e+07 | 243190 | 2.54088 | 2(Loss) |
| simdjson (ondemand) | 184.568 | 0.662689 | 288.688ms | 233995 | 30 | 1.92594e+09 | 1.20907e+06 | 12.6348 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2311.61 | 0.656045 | 23.9232ms | 233995 | 30 | 1.2033e+07 | 96536.8 | 1.00833 | 1(Win) |
| glaze | 1883.7 | 0.704885 | 29.024ms | 233995 | 30 | 2.09192e+07 | 118466 | 1.23745 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1230.87 | 0.544767 | 65.4709ms | 346753 | 30 | 6.42625e+07 | 268663 | 1.89422 | 1(Win) |
| jsonifier | 925.182 | 0.503927 | 86.5043ms | 346753 | 30 | 9.7329e+07 | 357432 | 2.52012 | 2(Loss) |
| simdjson (ondemand) | 245.49 | 0.103765 | 328.157ms | 346753 | 30 | 5.86134e+07 | 1.34706e+06 | 9.49921 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2484.07 | 0.682699 | 32.4158ms | 346753 | 30 | 2.47796e+07 | 133124 | 0.938383 | 1(Win) |
| glaze | 1706.94 | 0.58517 | 47.0689ms | 346753 | 30 | 3.85559e+07 | 193733 | 1.36587 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 669.174 | 0.694075 | 32.7708ms | 94651 | 30 | 2.6297e+07 | 134892 | 3.48367 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 661.027 | 0.663715 | 33.1809ms | 94651 | 30 | 2.46432e+07 | 136554 | 3.52646 | 1(Tie) |
| jsonifier STATISTICAL TIE | 657.208 | 1.02911 | 33.4717ms | 94651 | 30 | 5.99366e+07 | 137348 | 3.54728 | 1(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2753.68 | 2.41828 | 8.13003ms | 94651 | 30 | 1.8852e+07 | 32780.2 | 0.845909 | 1(Tie) |
| glaze STATISTICAL TIE | 2718.18 | 1.74156 | 8.31503ms | 94651 | 30 | 1.00344e+07 | 33208.3 | 0.856416 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 918.117 | 0.61103 | 34.4217ms | 136024 | 30 | 2.23605e+07 | 141292 | 2.53898 | 1(Win) |
| glaze | 843.819 | 0.561034 | 37.4ms | 136024 | 30 | 2.23168e+07 | 153733 | 2.76282 | 2(Loss) |
| jsonifier | 705.254 | 0.627868 | 45.5378ms | 136024 | 30 | 4.00127e+07 | 183937 | 3.30568 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3165.03 | 2.01044 | 10.0902ms | 136024 | 30 | 2.03696e+07 | 40986.3 | 0.736029 | 1(Win) |
| glaze | 1658.61 | 1.164 | 18.963ms | 136046 | 30 | 2.48719e+07 | 78224.4 | 1.40504 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 445.95 | 0.195171 | 1077.85ms | 2090234 | 30 | 2.28335e+09 | 4.47001e+06 | 5.22943 | 1(Win) |
| glaze | 357.025 | 0.15193 | 1342.58ms | 2090234 | 30 | 2.15874e+09 | 5.58338e+06 | 6.53195 | 2(Loss) |
| simdjson (ondemand) | 354.595 | 0.128331 | 1349.51ms | 2090234 | 30 | 1.56137e+09 | 5.62163e+06 | 6.57669 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 906.652 | 0.302918 | 527.486ms | 2090234 | 30 | 1.3307e+09 | 2.19864e+06 | 2.57207 | 1(Win) |
| glaze | 732.456 | 0.0919112 | 653.057ms | 2090234 | 30 | 1.87709e+08 | 2.72153e+06 | 3.18384 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1047.53 | 0.174037 | 1467.89ms | 6661897 | 30 | 3.34248e+09 | 6.06501e+06 | 2.22624 | 1(Win) |
| glaze | 893.472 | 0.343175 | 1712.59ms | 6661897 | 30 | 1.78643e+10 | 7.11077e+06 | 2.61013 | 2(Loss) |
| jsonifier | 768.494 | 0.0759004 | 1990.17ms | 6661897 | 30 | 1.1812e+09 | 8.26718e+06 | 3.03462 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2044.58 | 0.29653 | 751.765ms | 6661897 | 30 | 2.54711e+09 | 3.10738e+06 | 1.14051 | 1(Win) |
| glaze | 1579.02 | 0.183944 | 966.169ms | 6661897 | 30 | 1.64327e+09 | 4.02355e+06 | 1.47685 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 910.642 | 0.517979 | 126.036ms | 500299 | 30 | 2.20958e+08 | 523941 | 2.56064 | 1(Win) |
| jsonifier | 828.411 | 0.326757 | 138.139ms | 500299 | 30 | 1.06252e+08 | 575949 | 2.81487 | 2(Loss) |
| simdjson (ondemand) | 590.705 | 0.33333 | 194.177ms | 500299 | 30 | 2.17465e+08 | 807717 | 3.94763 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1812.15 | 0.430152 | 63.7514ms | 500299 | 30 | 3.84802e+07 | 263291 | 1.28669 | 1(Tie) |
| glaze STATISTICAL TIE | 1804.11 | 0.478936 | 64.1046ms | 500299 | 30 | 4.8129e+07 | 264463 | 1.29235 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1524.99 | 0.327788 | 215.898ms | 1439562 | 30 | 2.61238e+08 | 900253 | 1.52914 | 1(Win) |
| glaze | 1489.67 | 0.130074 | 221.657ms | 1439562 | 30 | 4.31108e+07 | 921596 | 1.56541 | 2(Loss) |
| jsonifier | 1011.69 | 0.135539 | 326.198ms | 1439562 | 30 | 1.01487e+08 | 1.35701e+06 | 2.305 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3197.58 | 0.371998 | 105.34ms | 1439562 | 30 | 7.65278e+07 | 429347 | 0.729256 | 1(Win) |
| glaze | 1911.54 | 0.186648 | 176.242ms | 1439584 | 30 | 5.39106e+07 | 718213 | 1.21991 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 844.553 | 0.584687 | 15.871ms | 56369 | 30 | 4.15522e+06 | 63652.2 | 2.75965 | 1(Tie) |
| jsonifier STATISTICAL TIE | 828.812 | 0.774546 | 16.262ms | 56369 | 30 | 7.57154e+06 | 64861.1 | 2.81208 | 1(Tie) |
| simdjson (ondemand) | 673.82 | 1.02178 | 19.6462ms | 56369 | 30 | 1.99356e+07 | 79780.4 | 3.45911 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1874.77 | 1.11604 | 7.20329ms | 56369 | 30 | 3.0723e+06 | 28674.2 | 1.24236 | 1(Win) |
| jsonifier | 1752.43 | 0.978904 | 7.66525ms | 56369 | 30 | 2.7052e+06 | 30676 | 1.32916 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1157.65 | 0.625166 | 19.2863ms | 94370 | 30 | 7.08642e+06 | 77742.4 | 2.01324 | 1(Win) |
| simdjson (ondemand) | 1097.64 | 0.555367 | 20.3052ms | 94370 | 30 | 6.22061e+06 | 81992.9 | 2.12341 | 2(Loss) |
| jsonifier | 804.958 | 2.04898 | 27.102ms | 94370 | 30 | 1.57441e+08 | 111805 | 2.89543 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2469.45 | 1.86993 | 9.06056ms | 94370 | 30 | 1.39328e+07 | 36444.6 | 0.943262 | 1(Win) |
| glaze | 1704.33 | 0.592795 | 13.0746ms | 94370 | 30 | 2.93963e+06 | 52805.7 | 1.3673 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 844.634 | 1.53855 | 14.6429ms | 52708 | 30 | 2.51511e+07 | 59512.5 | 2.75869 | 1(Win) |
| glaze | 719.037 | 0.962457 | 17.5082ms | 52708 | 30 | 1.35811e+07 | 69907.8 | 3.24077 | 2(Loss) |
| jsonifier | 674.09 | 1.03822 | 18.995ms | 52708 | 30 | 1.79811e+07 | 74569 | 3.45631 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2847.67 | 0.104507 | 4.68337ms | 52708 | 30 | 10209 | 17651.7 | 0.817131 | 1(Win) |
| glaze | 2700.73 | 1.66106 | 10.9193ms | 52708 | 32 | 3.05854e+06 | 18612.1 | 0.861555 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1079.06 | 0.93334 | 15.3641ms | 70103 | 30 | 1.00319e+07 | 61957.1 | 2.15937 | 1(Win) |
| glaze | 817.073 | 1.01437 | 20.4733ms | 70103 | 30 | 2.06663e+07 | 81823 | 2.85165 | 2(Loss) |
| jsonifier | 569.94 | 2.46337 | 29.283ms | 70103 | 30 | 2.50492e+08 | 117303 | 4.08663 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3074.74 | 1.52622 | 12.5997ms | 70103 | 32 | 3.52405e+06 | 21743.4 | 0.757216 | 1(Win) |
| glaze | 2276.06 | 1.1957 | 7.39985ms | 70103 | 30 | 3.70057e+06 | 29373.3 | 1.0232 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 647.543 | 1.04203 | 4.50061ms | 11812 | 30 | 985808 | 17396.2 | 3.59328 | 1(Tie) |
| jsonifier STATISTICAL TIE | 637.778 | 1.44622 | 10.3734ms | 11812 | 32 | 2.08798e+06 | 17662.6 | 3.64877 | 1(Tie) |
| simdjson (ondemand) | 557.937 | 1.43817 | 5.14649ms | 11812 | 30 | 2.52942e+06 | 20190.1 | 4.17238 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2527.7 | 0.11442 | 1.36108ms | 11812 | 30 | 780.051 | 4456.53 | 0.91505 | 1(Win) |
| glaze | 1320.1 | 0.217882 | 2.36588ms | 11812 | 30 | 10370.4 | 8533.27 | 1.75916 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1347.76 | 1.68919 | 5.55777ms | 31235 | 30 | 4.18156e+06 | 22101.9 | 1.72754 | 1(Win) |
| glaze | 1137.77 | 1.07846 | 15.2467ms | 31235 | 32 | 2.55114e+06 | 26181.1 | 2.04666 | 2(Loss) |
| jsonifier | 896.662 | 1.93502 | 8.38834ms | 31235 | 30 | 1.2397e+07 | 33221 | 2.59775 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2702.28 | 0.395844 | 2.96858ms | 31235 | 30 | 57120.5 | 11023.3 | 0.86009 | 1(Win) |
| glaze | 1857.85 | 1.93467 | 4.09587ms | 31235 | 30 | 2.88666e+06 | 16033.6 | 1.25237 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1636.03 | 0.748565 | 15.7525ms | 108313 | 30 | 6.70127e+06 | 63137.7 | 1.42449 | 1(Win) |
| glaze | 962.785 | 0.517591 | 26.1508ms | 108313 | 30 | 9.25117e+06 | 107288 | 2.42114 | 2(Loss) |
| simdjson (ondemand) | 841.825 | 0.835977 | 29.8595ms | 108313 | 30 | 3.15666e+07 | 122704 | 2.76911 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1937.98 | 1.20083 | 13.0538ms | 108313 | 30 | 1.22899e+07 | 53300.6 | 1.20247 | 1(Win) |
| glaze | 1732.63 | 1.08559 | 14.5709ms | 108313 | 30 | 1.25661e+07 | 59617.7 | 1.34484 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1507.67 | 1.21961 | 32.4702ms | 213963 | 30 | 8.1738e+07 | 135342 | 1.54611 | 1(Win) |
| glaze | 1319.53 | 0.826471 | 37.812ms | 213963 | 30 | 4.90023e+07 | 154639 | 1.76676 | 2(Loss) |
| jsonifier | 1133.27 | 0.44774 | 43.9873ms | 213963 | 30 | 1.94977e+07 | 180055 | 2.05639 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3035.57 | 1.13177 | 16.389ms | 213963 | 30 | 1.73635e+07 | 67219.9 | 0.767803 | 1(Win) |
| glaze | 1619.64 | 0.656982 | 30.6095ms | 213963 | 30 | 2.05526e+07 | 125985 | 1.43924 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 426.544 | 0.113335 | 982.863ms | 1834197 | 30 | 6.48051e+08 | 4.10093e+06 | 5.46711 | 1(Win) |
| glaze | 333.85 | 0.0932661 | 1255.92ms | 1834197 | 30 | 7.16406e+08 | 5.23956e+06 | 6.98535 | 2(Loss) |
| simdjson (ondemand) | 282.643 | 0.0626479 | 1492.57ms | 1834197 | 30 | 4.50973e+08 | 6.18882e+06 | 8.25097 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 560.232 | 0.0720936 | 750.242ms | 1834197 | 30 | 1.5201e+08 | 3.12233e+06 | 4.16257 | 1(Win) |
| glaze | 355.639 | 0.051432 | 1180.69ms | 1833577 | 30 | 1.91853e+08 | 4.91688e+06 | 6.55732 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1399 | 0.292689 | 1625.4ms | 9930848 | 30 | 1.1778e+10 | 6.76969e+06 | 1.66693 | 1(Win) |
| glaze | 1275.49 | 0.0839741 | 1792.81ms | 9930848 | 30 | 1.16636e+09 | 7.42524e+06 | 1.82837 | 2(Loss) |
| jsonifier | 1269.26 | 0.129153 | 1794.33ms | 9930848 | 30 | 2.78615e+09 | 7.46166e+06 | 1.83732 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2061.81 | 0.226093 | 1107.67ms | 9930848 | 30 | 3.23574e+09 | 4.59344e+06 | 1.13106 | 1(Win) |
| glaze | 1201.05 | 0.247289 | 1899.59ms | 9930228 | 30 | 1.14059e+10 | 7.88495e+06 | 1.9416 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 803.686 | 0.222084 | 184.01ms | 642697 | 30 | 8.60589e+07 | 762640 | 2.90149 | 1(Win) |
| glaze | 655.304 | 0.212012 | 226.16ms | 642697 | 30 | 1.1797e+08 | 935328 | 3.55854 | 2(Loss) |
| simdjson (ondemand) | 604.205 | 0.0988936 | 245.489ms | 642697 | 30 | 3.01927e+07 | 1.01443e+06 | 3.85958 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 882.396 | 0.504633 | 166.632ms | 642697 | 30 | 3.68602e+08 | 694613 | 2.64271 | 1(Win) |
| glaze | 575.276 | 0.109636 | 256.237ms | 642692 | 30 | 4.0934e+07 | 1.06543e+06 | 4.05359 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1111.28 | 0.117323 | 593.56ms | 1225964 | 32 | 4.87556e+07 | 1.0521e+06 | 2.09843 | 1(Win) |
| glaze | 1001.76 | 0.231131 | 280.908ms | 1225964 | 30 | 2.18305e+08 | 1.16712e+06 | 2.32786 | 2(Loss) |
| jsonifier | 797.096 | 0.116015 | 352.912ms | 1225964 | 30 | 8.68727e+07 | 1.46679e+06 | 2.92563 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1481.36 | 0.937636 | 192.139ms | 1225964 | 30 | 1.64296e+09 | 789257 | 1.57416 | 1(Win) |
| glaze | 972.553 | 0.160855 | 289.002ms | 1225970 | 30 | 1.12182e+08 | 1.20217e+06 | 2.39784 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 518.01 | 0.264813 | 184.401ms | 409725 | 30 | 1.19704e+08 | 754318 | 4.50161 | 1(Win) |
| simdjson (ondemand) | 514.091 | 0.168539 | 183.057ms | 409725 | 30 | 4.92296e+07 | 760068 | 4.536 | 2(Loss) |
| glaze | 409.46 | 0.254376 | 230.126ms | 409725 | 30 | 1.76781e+08 | 954292 | 5.69522 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1407.38 | 0.347639 | 66.6731ms | 409725 | 30 | 2.79474e+07 | 277640 | 1.65668 | 1(Win) |
| jsonifier | 1356.26 | 0.470889 | 69.5503ms | 409725 | 30 | 5.52154e+07 | 288105 | 1.71919 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 937.322 | 0.215472 | 191.986ms | 785750 | 30 | 8.90212e+07 | 799458 | 2.48783 | 1(Win) |
| glaze | 666.85 | 0.239702 | 270.272ms | 785750 | 30 | 2.1766e+08 | 1.12372e+06 | 3.49702 | 2(Loss) |
| jsonifier | 652.859 | 0.136835 | 276.067ms | 785750 | 30 | 7.40027e+07 | 1.1478e+06 | 3.57191 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2004.3 | 0.389475 | 90.7677ms | 785750 | 30 | 6.36098e+07 | 373872 | 1.16337 | 1(Win) |
| glaze | 1481.9 | 0.265455 | 121.834ms | 785750 | 30 | 5.40549e+07 | 505669 | 1.57354 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 693.755 | 0.263389 | 2841.96ms | 8587914 | 30 | 2.90056e+10 | 1.18054e+07 | 3.36148 | 1(Win) |
| jsonifier | 635.377 | 0.527407 | 2989.67ms | 8587914 | 30 | 1.38652e+11 | 1.28901e+07 | 3.67028 | 2(Loss) |
| glaze | 616.985 | 0.454441 | 3256.49ms | 8587914 | 30 | 1.0917e+11 | 1.32743e+07 | 3.77976 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2139 | 0.327899 | 927.615ms | 8588126 | 30 | 4.72906e+09 | 3.82902e+06 | 1.0902 | 1(Win) |
| glaze | 2106.8 | 0.313623 | 936.516ms | 8588126 | 30 | 4.45952e+09 | 3.88755e+06 | 1.10686 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 787.129 | 0.246045 | 2900.85ms | 9804437 | 30 | 2.56273e+10 | 1.18789e+07 | 2.96271 | 1(Win) |
| glaze | 642.301 | 0.921071 | 3414.54ms | 9804437 | 30 | 5.39356e+11 | 1.45574e+07 | 3.63075 | 2(Loss) |
| jsonifier | 628.64 | 0.364311 | 3571.86ms | 9804437 | 30 | 8.80862e+10 | 1.48737e+07 | 3.7097 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2350.74 | 0.282617 | 1088.26ms | 11078090 | 30 | 4.8399e+09 | 4.49428e+06 | 0.991913 | 1(Win) |
| glaze | 1809.09 | 0.465398 | 1388.65ms | 11078090 | 30 | 2.21605e+10 | 5.83989e+06 | 1.28901 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2618.88 | 1.12328 | 23.4049ms | 264040 | 30 | 3.49952e+07 | 96151.1 | 0.889868 | 1(Win) |
| jsonifier | 2515.69 | 0.740038 | 24.5437ms | 264040 | 30 | 1.6461e+07 | 100095 | 0.926399 | 2(Loss) |
| glaze | 1040.9 | 0.603679 | 58.5224ms | 264040 | 30 | 6.39822e+07 | 241915 | 2.23994 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3456.59 | 0.761518 | 26.9532ms | 399947 | 30 | 2.11832e+07 | 110346 | 0.674274 | 1(Win) |
| jsonifier | 2913.28 | 0.689759 | 32.1125ms | 399947 | 30 | 2.44657e+07 | 130924 | 0.800102 | 2(Loss) |
| glaze | 1278.28 | 0.822701 | 71.4147ms | 399947 | 30 | 1.80782e+08 | 298384 | 1.82403 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 899.708 | 0.425694 | 68.5956ms | 264040 | 30 | 4.25847e+07 | 279878 | 2.59121 | 1(Win) |
| simdjson (ondemand) | 882.652 | 0.454172 | 70.5694ms | 264040 | 30 | 5.03643e+07 | 285286 | 2.64132 | 2(Loss) |
| glaze | 807.571 | 0.562739 | 75.4447ms | 264040 | 30 | 9.23663e+07 | 311809 | 2.88719 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2319.18 | 0.797582 | 27.4537ms | 263923 | 30 | 2.2478e+07 | 108528 | 1.00504 | 1(Win) |
| jsonifier | 2268.23 | 0.64073 | 27.2905ms | 264040 | 30 | 1.51788e+07 | 111016 | 1.0276 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1256.48 | 0.508518 | 73.4475ms | 399947 | 30 | 7.14868e+07 | 303561 | 1.85572 | 1(Win) |
| glaze | 937.259 | 2.3614 | 95.7688ms | 399947 | 30 | 2.77041e+09 | 406952 | 2.48776 | 2(Loss) |
| jsonifier | 774.182 | 0.439837 | 119.487ms | 399947 | 30 | 1.40872e+08 | 492674 | 3.01145 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3107.98 | 0.635782 | 30.1849ms | 399947 | 30 | 1.82636e+07 | 122723 | 0.750002 | 1(Win) |
| glaze | 1999.58 | 0.49683 | 46.4437ms | 399830 | 30 | 2.69283e+07 | 190693 | 1.16594 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1399.08 | 0.460002 | 77.0806ms | 466906 | 30 | 6.43009e+07 | 318265 | 1.66655 | 1(Win) |
| glaze | 1366.13 | 0.297453 | 78.9617ms | 466906 | 30 | 2.81988e+07 | 325939 | 1.70686 | 2(Loss) |
| simdjson (ondemand) | 664.631 | 0.264225 | 161.453ms | 466906 | 30 | 9.40082e+07 | 669960 | 3.50845 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2107.34 | 0.365575 | 76.5777ms | 699405 | 30 | 4.01664e+07 | 316515 | 1.10642 | 1(Win) |
| glaze | 1704.01 | 0.257505 | 93.9494ms | 699405 | 30 | 3.04795e+07 | 391433 | 1.36829 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1665.71 | 0.39209 | 87.4683ms | 631514 | 30 | 6.02921e+07 | 361563 | 1.39988 | 1(Win) |
| glaze | 1535.05 | 0.310454 | 95.186ms | 631514 | 30 | 4.45082e+07 | 392339 | 1.51905 | 2(Loss) |
