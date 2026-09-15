# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [4d272c2](https://github.com/nihilai-collective/jsonifier/commit/4d272c2)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 657.527 | 0.0656456 | 2.02427ms | 1811 | 30 | 89.1954 | 2626.67 | 3.71073 | 1(Win) |
| glaze | 458.284 | 0.0588747 | 1.08716ms | 1811 | 30 | 147.689 | 3768.63 | 5.3517 | 2(Loss) |
| simdjson (ondemand) | 132.62 | 0.0472909 | 7.65584ms | 1811 | 32 | 1213.74 | 13023 | 18.609 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 403.403 | 0.17035 | 1.26481ms | 1811 | 30 | 1595.75 | 4281.33 | 6.08102 | 1(Win) |
| glaze | 269.161 | 0.391785 | 1.72076ms | 1798 | 30 | 18688.4 | 6370.57 | 9.14145 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1173.14 | 0.0724391 | 0.991247ms | 3873 | 30 | 156.051 | 3148.47 | 2.08533 | 1(Win) |
| glaze | 547.572 | 0.31561 | 4.09037ms | 3873 | 32 | 14503.2 | 6745.38 | 4.49088 | 2(Loss) |
| simdjson (ondemand) | 305.612 | 0.0331315 | 3.13291ms | 3873 | 30 | 481.016 | 12085.9 | 8.0777 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1568.29 | 0.668711 | 0.793981ms | 3873 | 30 | 7441.18 | 2355.17 | 1.54895 | 1(Win) |
| glaze | 1052.11 | 0.307243 | 1.03556ms | 3873 | 30 | 3490.24 | 3510.63 | 2.32857 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1128.32 | 0.0710937 | 1.02241ms | 3862 | 30 | 161.564 | 3264.23 | 2.16824 | 1(Win) |
| glaze | 876.857 | 0.148803 | 1.19075ms | 3862 | 30 | 1171.95 | 4200.33 | 2.79613 | 2(Loss) |
| simdjson (ondemand) | 297.785 | 0.023058 | 3.19585ms | 3862 | 30 | 243.995 | 12368.3 | 8.28742 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1571.14 | 0.0422144 | 1.59184ms | 3862 | 32 | 31.3377 | 2344.22 | 1.5459 | 1(Win) |
| glaze | 1033.6 | 0.646999 | 1.05785ms | 3862 | 30 | 15945.9 | 3563.37 | 2.36998 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 769.001 | 0.0977288 | 0.507011ms | 905 | 30 | 36.092 | 1122.33 | 3.10468 | 1(Win) |
| glaze | 443.141 | 0.808154 | 0.65317ms | 905 | 30 | 7432.31 | 1947.63 | 5.47484 | 2(Loss) |
| simdjson (ondemand) | 97.9592 | 0.53344 | 10.8885ms | 905 | 64 | 141370 | 8810.56 | 25.1628 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 852.364 | 0.0563626 | 0.448012ms | 905 | 30 | 9.77126 | 1012.57 | 2.80206 | 1(Win) |
| glaze | 308.693 | 0.504563 | 0.849094ms | 905 | 30 | 5970.3 | 2795.9 | 7.91204 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1730.54 | 0.154927 | 1.54137ms | 9578 | 30 | 2006.15 | 5278.3 | 1.42098 | 1(Win) |
| glaze | 1398.3 | 0.163965 | 1.78475ms | 9578 | 30 | 3441.7 | 6532.43 | 1.76075 | 2(Loss) |
| simdjson (ondemand) | 704.343 | 0.0439861 | 3.35505ms | 9578 | 30 | 976.189 | 12968.5 | 3.50422 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3168.41 | 0.107432 | 7.62439ms | 9578 | 128 | 1227.85 | 2882.93 | 0.770976 | 1(Win) |
| glaze | 2240.72 | 0.168314 | 1.17184ms | 9578 | 30 | 1412.33 | 4076.5 | 1.09514 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2664.2 | 2.11924 | 19.9795ms | 233995 | 30 | 9.4528e+07 | 83760.7 | 0.928831 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2552.03 | 0.885689 | 21.0934ms | 233995 | 30 | 1.79939e+07 | 87442.2 | 0.969528 | 1(Tie) |
| glaze | 1427.35 | 0.431938 | 38.0643ms | 233995 | 30 | 1.3681e+07 | 156342 | 1.73403 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3293.17 | 0.512267 | 24.432ms | 346753 | 30 | 7.93828e+06 | 100417 | 0.751385 | 1(Win) |
| jsonifier | 3226.22 | 0.484247 | 25.0176ms | 346753 | 30 | 7.39108e+06 | 102500 | 0.767106 | 2(Loss) |
| glaze | 1798.15 | 0.365879 | 45.1623ms | 346753 | 30 | 1.35826e+07 | 183905 | 1.37648 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1279.48 | 0.689855 | 45.0546ms | 233995 | 30 | 4.3429e+07 | 174410 | 1.93455 | 1(Win) |
| jsonifier | 1131.78 | 0.35818 | 48.0457ms | 233995 | 30 | 1.49627e+07 | 197171 | 2.18696 | 2(Loss) |
| simdjson (ondemand) | 1003.6 | 1.5244 | 53.5951ms | 233995 | 30 | 3.44676e+08 | 222354 | 2.46636 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2457.58 | 0.666511 | 22.2317ms | 233995 | 30 | 1.09884e+07 | 90802.6 | 1.00697 | 1(Win) |
| glaze | 2100.46 | 0.566173 | 25.9461ms | 233995 | 30 | 1.08543e+07 | 106241 | 1.17811 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1478.72 | 0.614366 | 57.6941ms | 346753 | 30 | 5.66295e+07 | 223632 | 1.67392 | 1(Win) |
| glaze | 1273.04 | 1.45186 | 62.4365ms | 346753 | 30 | 4.26704e+08 | 259763 | 1.94445 | 2(Loss) |
| jsonifier | 1011.73 | 0.303005 | 79.2882ms | 346753 | 30 | 2.94262e+07 | 326856 | 2.44678 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2577.61 | 0.477969 | 31.1967ms | 346753 | 30 | 1.12805e+07 | 128293 | 0.960218 | 1(Win) |
| glaze | 2087.33 | 0.608741 | 38.7994ms | 346753 | 30 | 2.79026e+07 | 158427 | 1.18568 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2654.08 | 0.722407 | 20.4997ms | 233995 | 30 | 1.1068e+07 | 84079.8 | 0.932364 | 1(Win) |
| simdjson (ondemand) | 1698.75 | 0.397719 | 31.8764ms | 233995 | 30 | 8.18901e+06 | 131365 | 1.45693 | 2(Loss) |
| glaze | 1448.41 | 0.392758 | 37.5298ms | 233995 | 30 | 1.09851e+07 | 154069 | 1.70891 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3185.99 | 0.529655 | 25.4364ms | 346753 | 30 | 9.06689e+06 | 103795 | 0.776789 | 1(Win) |
| simdjson (ondemand) | 2279.48 | 0.37186 | 35.1384ms | 346753 | 30 | 8.73067e+06 | 145072 | 1.08583 | 2(Loss) |
| glaze | 1789.12 | 1.09078 | 44.424ms | 346753 | 30 | 1.21944e+08 | 184833 | 1.38346 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1363.12 | 0.391873 | 41.8385ms | 233995 | 30 | 1.23469e+07 | 163709 | 1.81584 | 1(Win) |
| jsonifier | 1030.58 | 1.25994 | 51.944ms | 233995 | 30 | 2.23289e+08 | 216533 | 2.40186 | 2(Loss) |
| simdjson (ondemand) | 179.52 | 0.0804779 | 300.247ms | 233995 | 30 | 3.00234e+07 | 1.24306e+06 | 13.7906 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2602.53 | 0.837255 | 20.9243ms | 233995 | 30 | 1.54617e+07 | 85745.3 | 0.950868 | 1(Win) |
| glaze | 2075.91 | 0.585026 | 26.0939ms | 233995 | 30 | 1.1865e+07 | 107497 | 1.19207 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1574.92 | 1.10664 | 52.4678ms | 346753 | 30 | 1.61979e+08 | 209973 | 1.57169 | 1(Win) |
| jsonifier | 1011.18 | 0.264691 | 79.7507ms | 346753 | 30 | 2.24795e+07 | 327034 | 2.44808 | 2(Loss) |
| simdjson (ondemand) | 262.041 | 0.0843614 | 304.18ms | 346753 | 30 | 3.40026e+07 | 1.26198e+06 | 9.44776 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3036.56 | 0.608266 | 62.0769ms | 346753 | 32 | 1.40415e+07 | 108903 | 0.814986 | 1(Win) |
| glaze | 2225.03 | 0.45622 | 36.2146ms | 346753 | 30 | 1.37924e+07 | 148623 | 1.11217 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 714.384 | 0.548277 | 30.766ms | 94651 | 30 | 1.43982e+07 | 126355 | 3.46462 | 1(Tie) |
| glaze STATISTICAL TIE | 713.472 | 0.51801 | 31.0872ms | 94651 | 30 | 1.28853e+07 | 126517 | 3.46899 | 1(Tie) |
| jsonifier | 682.661 | 0.519632 | 32.3892ms | 94651 | 30 | 1.4163e+07 | 132227 | 3.6256 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3410.29 | 1.04614 | 6.58852ms | 94651 | 30 | 2.3002e+06 | 26468.8 | 0.724952 | 1(Win) |
| glaze | 2844.58 | 1.34373 | 7.90513ms | 94651 | 30 | 5.45456e+06 | 31732.7 | 0.869377 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 991.027 | 0.507934 | 32.0198ms | 136024 | 30 | 1.32616e+07 | 130897 | 2.49746 | 1(Win) |
| glaze | 870.395 | 0.705836 | 36.192ms | 136024 | 30 | 3.31992e+07 | 149039 | 2.84364 | 2(Loss) |
| jsonifier | 765.329 | 0.54865 | 41.4481ms | 136024 | 30 | 2.59446e+07 | 169499 | 3.23398 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3585.15 | 1.13256 | 8.94334ms | 136024 | 30 | 5.03803e+06 | 36183.3 | 0.689866 | 1(Win) |
| glaze | 2784.2 | 1.10903 | 11.4508ms | 136046 | 30 | 8.01272e+06 | 46599.9 | 0.888415 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 430.058 | 0.144924 | 1113.44ms | 2090234 | 30 | 1.35375e+09 | 4.63519e+06 | 5.75674 | 1(Win) |
| simdjson (ondemand) | 348.805 | 0.0862578 | 1375.19ms | 2090234 | 30 | 7.29025e+08 | 5.71495e+06 | 7.09745 | 2(Loss) |
| glaze | 346.716 | 0.0930678 | 1380.33ms | 2090234 | 30 | 8.58938e+08 | 5.74938e+06 | 7.14055 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 845.055 | 0.082611 | 566.512ms | 2090234 | 30 | 1.13924e+08 | 2.3589e+06 | 2.92954 | 1(Win) |
| glaze | 723.283 | 0.107248 | 662.067ms | 2090234 | 30 | 2.62105e+08 | 2.75605e+06 | 3.4229 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1015.96 | 0.150664 | 1496.23ms | 6661897 | 30 | 2.66309e+09 | 6.2535e+06 | 2.43677 | 1(Win) |
| glaze | 877.949 | 0.101618 | 1733.73ms | 6661897 | 30 | 1.62226e+09 | 7.2365e+06 | 2.8199 | 2(Loss) |
| jsonifier | 833.733 | 0.105059 | 1832.44ms | 6661897 | 30 | 1.92277e+09 | 7.62028e+06 | 2.96945 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2238.88 | 0.224074 | 687.587ms | 6661897 | 30 | 1.21294e+09 | 2.83771e+06 | 1.10577 | 1(Win) |
| glaze | 1738.84 | 0.317812 | 881.012ms | 6661897 | 30 | 4.04519e+09 | 3.65374e+06 | 1.42372 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 898.601 | 0.239778 | 127.757ms | 500299 | 30 | 4.86256e+07 | 530961 | 2.75466 | 1(Win) |
| jsonifier | 775.464 | 0.206273 | 148.022ms | 500299 | 30 | 4.83219e+07 | 615274 | 3.19214 | 2(Loss) |
| simdjson (ondemand) | 575.24 | 1.58763 | 194.626ms | 500299 | 30 | 5.20213e+09 | 829432 | 4.30323 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2931.12 | 0.510639 | 39.6079ms | 500299 | 30 | 2.07271e+07 | 162778 | 0.844367 | 1(Win) |
| glaze | 2211.91 | 0.485102 | 52.1932ms | 500299 | 30 | 3.28483e+07 | 215706 | 1.11876 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1512.71 | 0.151094 | 218.742ms | 1439562 | 30 | 5.64113e+07 | 907559 | 1.63641 | 1(Win) |
| simdjson (ondemand) | 1495.54 | 0.103025 | 221.052ms | 1439562 | 30 | 2.68331e+07 | 917981 | 1.65518 | 2(Loss) |
| jsonifier | 1048.36 | 0.141481 | 314.417ms | 1439562 | 30 | 1.02981e+08 | 1.30954e+06 | 2.36129 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3913.37 | 0.319838 | 84.6518ms | 1439562 | 30 | 3.77695e+07 | 350816 | 0.632514 | 1(Win) |
| glaze | 2645.05 | 0.303754 | 125.034ms | 1439584 | 30 | 7.45712e+07 | 519043 | 0.935809 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 901.661 | 0.674353 | 15.1024ms | 56369 | 30 | 4.84943e+06 | 59620.7 | 2.74399 | 1(Win) |
| glaze | 883.379 | 0.443219 | 15.2352ms | 56369 | 30 | 2.18245e+06 | 60854.6 | 2.8003 | 2(Loss) |
| simdjson (ondemand) | 758.889 | 0.714245 | 17.8915ms | 56369 | 30 | 7.67963e+06 | 70837.3 | 3.25955 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3111.39 | 0.124502 | 4.43246ms | 56369 | 30 | 13881.9 | 17277.7 | 0.793897 | 1(Win) |
| glaze | 2817.94 | 1.28632 | 10.975ms | 56369 | 32 | 1.92694e+06 | 19076.9 | 0.876729 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1178.25 | 0.614916 | 19.13ms | 94370 | 30 | 6.61829e+06 | 76383 | 2.1 | 1(Tie) |
| glaze STATISTICAL TIE | 1168.04 | 0.654038 | 18.8951ms | 94370 | 30 | 7.61873e+06 | 77050.9 | 2.11852 | 1(Tie) |
| jsonifier | 942.515 | 0.574418 | 23.8255ms | 94370 | 30 | 9.02543e+06 | 95487.3 | 2.6255 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3767.22 | 1.13688 | 6.08875ms | 94370 | 30 | 2.21296e+06 | 23889.8 | 0.656158 | 1(Win) |
| glaze | 2690.97 | 1.29322 | 8.3034ms | 94370 | 30 | 5.61202e+06 | 33444.5 | 0.918977 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 926.594 | 0.984467 | 13.5596ms | 52708 | 30 | 8.55653e+06 | 54248.4 | 2.66987 | 1(Win) |
| jsonifier | 858.966 | 1.0354 | 15.0088ms | 52708 | 30 | 1.10139e+07 | 58519.5 | 2.87979 | 2(Loss) |
| glaze | 758.001 | 2.39554 | 15.9636ms | 52708 | 30 | 7.57077e+07 | 66314.2 | 3.26417 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3539.06 | 0.110365 | 3.71845ms | 52708 | 30 | 7371.51 | 14203.3 | 0.697618 | 1(Win) |
| glaze | 3193.74 | 0.280986 | 4.0739ms | 52708 | 30 | 58673.9 | 15739 | 0.773222 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1185.84 | 0.859443 | 14.1046ms | 70103 | 30 | 7.04336e+06 | 56378.3 | 2.08594 | 1(Win) |
| glaze | 911.245 | 0.784927 | 18.3588ms | 70103 | 30 | 9.94906e+06 | 73367.1 | 2.71538 | 2(Loss) |
| jsonifier | 754.701 | 1.08336 | 22.5453ms | 70103 | 30 | 2.76308e+07 | 88585.3 | 3.27697 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3522.89 | 1.37045 | 4.80749ms | 70103 | 30 | 2.02918e+06 | 18977.4 | 0.701191 | 1(Win) |
| glaze | 3018.74 | 0.178482 | 5.6559ms | 70103 | 30 | 46874.1 | 22146.8 | 0.818662 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 654.077 | 1.14553 | 9.79701ms | 11812 | 32 | 1.24553e+06 | 17222.4 | 3.77642 | 1(Tie) |
| jsonifier STATISTICAL TIE | 623.065 | 2.46869 | 4.58286ms | 11812 | 30 | 5.97632e+06 | 18079.7 | 3.96464 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 603.828 | 2.39861 | 4.65621ms | 11812 | 30 | 6.00704e+06 | 18655.6 | 4.09157 | 1(Tie) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3106.82 | 0.0739464 | 1.06976ms | 11812 | 30 | 215.661 | 3625.83 | 0.789186 | 1(Win) |
| glaze | 1736.61 | 0.533705 | 3.94717ms | 11812 | 32 | 38352.6 | 6486.66 | 1.41768 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1459.15 | 0.0726438 | 5.17574ms | 31235 | 30 | 6597.87 | 20414.7 | 1.69377 | 1(Win) |
| glaze | 1220.62 | 1.26971 | 6.14842ms | 31235 | 30 | 2.88039e+06 | 24403.9 | 2.02501 | 2(Loss) |
| jsonifier | 943.222 | 1.06118 | 7.88928ms | 31235 | 30 | 3.36944e+06 | 31581.1 | 2.62173 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3748.18 | 0.333186 | 2.13347ms | 31235 | 30 | 21034.8 | 7947.33 | 0.657429 | 1(Win) |
| glaze | 2876.99 | 0.217147 | 2.74009ms | 31235 | 30 | 15164.9 | 10353.9 | 0.857233 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1660.31 | 0.613935 | 15.3866ms | 108313 | 30 | 4.37671e+06 | 62214.4 | 1.49009 | 1(Win) |
| glaze | 1051 | 0.650694 | 24.1453ms | 108313 | 30 | 1.22697e+07 | 98283.2 | 2.35453 | 2(Loss) |
| simdjson (ondemand) | 910.152 | 0.510124 | 27.9346ms | 108313 | 30 | 1.00556e+07 | 113492 | 2.71914 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1916.2 | 0.540651 | 13.2829ms | 108313 | 30 | 2.5482e+06 | 53906.2 | 1.29107 | 1(Win) |
| glaze | 1443.71 | 0.680572 | 17.5026ms | 108313 | 30 | 7.11333e+06 | 71548.7 | 1.71383 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1587.18 | 1.52049 | 30.9203ms | 213963 | 30 | 1.14634e+08 | 128562 | 1.55932 | 1(Win) |
| glaze | 1437.12 | 0.445227 | 34.8046ms | 213963 | 30 | 1.19888e+07 | 141986 | 1.7222 | 2(Loss) |
| jsonifier | 1113.95 | 0.344239 | 44.71ms | 213963 | 30 | 1.19285e+07 | 183178 | 2.22176 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2656.05 | 0.526335 | 18.6491ms | 213963 | 30 | 4.90512e+06 | 76824.9 | 0.931613 | 1(Win) |
| glaze | 1766.54 | 0.576915 | 28.0647ms | 213963 | 30 | 1.33222e+07 | 115509 | 1.40073 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 429.347 | 0.157365 | 975.707ms | 1834197 | 30 | 1.23314e+09 | 4.07416e+06 | 5.76569 | 1(Win) |
| glaze | 337.933 | 0.158081 | 1249.23ms | 1834197 | 30 | 2.00868e+09 | 5.17625e+06 | 7.32599 | 2(Loss) |
| simdjson (ondemand) | 299.994 | 0.117089 | 1401.84ms | 1834197 | 30 | 1.39837e+09 | 5.83087e+06 | 8.25244 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 573.615 | 0.0727252 | 729.674ms | 1834197 | 30 | 1.47551e+08 | 3.04948e+06 | 4.31593 | 1(Win) |
| glaze | 349.301 | 0.107884 | 1218.1ms | 1833577 | 30 | 8.75059e+08 | 5.0061e+06 | 7.0876 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1383.09 | 0.0771988 | 1654.27ms | 9930848 | 30 | 8.38334e+08 | 6.84758e+06 | 1.78993 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1332.03 | 1.39202 | 1651.84ms | 9930848 | 30 | 2.93874e+11 | 7.11006e+06 | 1.85849 | 2(Tie) |
| glaze STATISTICAL TIE | 1296.67 | 0.353046 | 1759.53ms | 9930848 | 30 | 1.99479e+10 | 7.30395e+06 | 1.90923 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2009.81 | 0.306334 | 1155.07ms | 9930848 | 30 | 6.25134e+09 | 4.71228e+06 | 1.23177 | 1(Win) |
| glaze | 1262.92 | 0.109819 | 1808.4ms | 9930228 | 30 | 2.03443e+09 | 7.49864e+06 | 1.96021 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 787.858 | 1.09484 | 190.697ms | 642697 | 30 | 2.17639e+09 | 777962 | 3.14193 | 1(Win) |
| glaze | 634.6 | 0.227093 | 232.434ms | 642697 | 30 | 1.44324e+08 | 965842 | 3.90094 | 2(Loss) |
| simdjson (ondemand) | 595.382 | 0.232617 | 249.364ms | 642697 | 30 | 1.72038e+08 | 1.02946e+06 | 4.15785 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 755.628 | 0.781623 | 195.49ms | 642697 | 30 | 1.2059e+09 | 811144 | 3.27615 | 1(Win) |
| glaze | 557.23 | 0.134282 | 264.651ms | 642692 | 30 | 6.5448e+07 | 1.09994e+06 | 4.44251 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1069 | 0.320687 | 262.279ms | 1225964 | 30 | 3.69048e+08 | 1.0937e+06 | 2.31568 | 1(Win) |
| glaze | 963.669 | 0.234137 | 293.056ms | 1225964 | 30 | 2.42082e+08 | 1.21325e+06 | 2.56887 | 2(Loss) |
| jsonifier | 808.373 | 0.247668 | 347.198ms | 1225964 | 30 | 3.8494e+08 | 1.44632e+06 | 3.06243 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1520.55 | 0.339044 | 184.519ms | 1225964 | 30 | 2.03886e+08 | 768914 | 1.62805 | 1(Win) |
| glaze | 935.758 | 0.1207 | 300.167ms | 1225970 | 30 | 6.82294e+07 | 1.24944e+06 | 2.64551 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 540.023 | 0.262861 | 174.574ms | 409725 | 30 | 1.08526e+08 | 723569 | 4.58389 | 1(Win) |
| jsonifier | 533.015 | 0.455092 | 175.98ms | 409725 | 30 | 3.33907e+08 | 733083 | 4.64388 | 2(Loss) |
| glaze | 399.06 | 0.188853 | 236.039ms | 409725 | 30 | 1.02583e+08 | 979161 | 6.20337 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2135.37 | 0.468816 | 44.4554ms | 409725 | 30 | 2.20783e+07 | 182987 | 1.15903 | 1(Win) |
| glaze | 1774 | 0.418605 | 53.6296ms | 409725 | 30 | 2.55042e+07 | 220262 | 1.3951 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 950.288 | 0.202493 | 189.348ms | 785750 | 30 | 7.6489e+07 | 788550 | 2.60488 | 1(Win) |
| jsonifier | 707.085 | 0.157833 | 254.886ms | 785750 | 30 | 8.39351e+07 | 1.05977e+06 | 3.50095 | 2(Loss) |
| glaze | 666.855 | 0.297723 | 269.99ms | 785750 | 30 | 3.35779e+08 | 1.12371e+06 | 3.71223 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2408.99 | 0.359517 | 75.018ms | 785750 | 30 | 3.75195e+07 | 311063 | 1.02756 | 1(Win) |
| glaze | 2035.93 | 0.443902 | 87.9744ms | 785750 | 30 | 8.00825e+07 | 368062 | 1.21575 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 613.285 | 0.432218 | 3279.59ms | 8587914 | 30 | 9.99488e+10 | 1.33544e+07 | 4.03674 | 1(Win) |
| simdjson (ondemand) | 570.704 | 0.823156 | 3277.54ms | 8587914 | 30 | 4.18638e+11 | 1.43508e+07 | 4.33808 | 2(Loss) |
| glaze | 555.039 | 0.68457 | 3472.14ms | 8587914 | 30 | 3.06115e+11 | 1.47558e+07 | 4.46042 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2156.11 | 0.74148 | 926.191ms | 8588126 | 30 | 2.37998e+10 | 3.79863e+06 | 1.14818 | 1(Win) |
| glaze | 2072.18 | 0.194455 | 949.465ms | 8588126 | 30 | 1.77215e+09 | 3.9525e+06 | 1.19464 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 632.265 | 0.873176 | 3628.87ms | 9804437 | 30 | 5.00232e+11 | 1.47885e+07 | 3.91556 | 1(Win) |
| jsonifier | 578.437 | 0.50483 | 3951.84ms | 9804437 | 30 | 1.99777e+11 | 1.61647e+07 | 4.27989 | 2(Loss) |
| glaze | 551.133 | 0.850126 | 3907.3ms | 9804437 | 30 | 6.24051e+11 | 1.69655e+07 | 4.49201 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2269.64 | 0.421702 | 1101.93ms | 11078090 | 30 | 1.15597e+10 | 4.65487e+06 | 1.09072 | 1(Win) |
| glaze | 1973.82 | 0.184758 | 1276.67ms | 11078090 | 30 | 2.93389e+09 | 5.35252e+06 | 1.25417 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2852.05 | 0.582958 | 21.7575ms | 264040 | 30 | 7.94733e+06 | 88290.3 | 0.867658 | 1(Win) |
| simdjson (ondemand) | 2783.51 | 0.680477 | 22.0308ms | 264040 | 30 | 1.13685e+07 | 90464.3 | 0.889078 | 2(Loss) |
| glaze | 1104.52 | 0.328333 | 55.3477ms | 264040 | 30 | 1.68089e+07 | 227979 | 2.2411 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3573.42 | 0.602491 | 26.0588ms | 399947 | 30 | 1.24068e+07 | 106738 | 0.692567 | 1(Win) |
| jsonifier | 3432.89 | 0.56532 | 27.1519ms | 399947 | 30 | 1.18358e+07 | 111107 | 0.72092 | 2(Loss) |
| glaze | 1408.04 | 0.326742 | 65.6385ms | 399947 | 30 | 2.35022e+07 | 270887 | 1.75802 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1025.7 | 0.400717 | 60.9932ms | 264040 | 30 | 2.90331e+07 | 245498 | 2.41285 | 1(Win) |
| simdjson (ondemand) | 965.024 | 0.424277 | 63.9758ms | 264040 | 30 | 3.67692e+07 | 260935 | 2.56482 | 2(Loss) |
| glaze | 881.295 | 0.406898 | 70.0788ms | 264040 | 30 | 4.05499e+07 | 285725 | 2.80862 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2841.39 | 0.729089 | 21.7301ms | 264040 | 30 | 1.25245e+07 | 88621.5 | 0.870907 | 1(Win) |
| glaze | 2594.87 | 0.659852 | 23.7535ms | 263923 | 30 | 1.22896e+07 | 96997.9 | 0.953395 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1459.29 | 0.651936 | 64.4813ms | 399947 | 30 | 8.71071e+07 | 261373 | 1.69592 | 1(Win) |
| glaze | 1023.71 | 0.614945 | 90.0306ms | 399947 | 30 | 1.57487e+08 | 372584 | 2.41724 | 2(Loss) |
| jsonifier | 924.924 | 0.285174 | 101.706ms | 399947 | 30 | 4.14892e+07 | 412379 | 2.67613 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3400.22 | 0.785264 | 27.252ms | 399947 | 30 | 2.32778e+07 | 112175 | 0.727756 | 1(Win) |
| glaze | 2646.85 | 1.9423 | 33.9477ms | 399830 | 30 | 2.3488e+08 | 144061 | 0.934495 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1399.1 | 0.307819 | 77.0852ms | 466906 | 30 | 2.8792e+07 | 318259 | 1.76921 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1389.37 | 0.307626 | 78.5117ms | 466906 | 30 | 2.91601e+07 | 320487 | 1.78159 | 1(Tie) |
| simdjson (ondemand) | 722.086 | 0.266451 | 149.812ms | 466906 | 30 | 8.09914e+07 | 616653 | 3.42818 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2375.93 | 1.85535 | 65.8821ms | 699405 | 30 | 8.13886e+08 | 280734 | 1.04169 | 1(Win) |
| glaze | 2177.36 | 0.29422 | 73.9214ms | 699405 | 30 | 2.43703e+07 | 306336 | 1.13678 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1786.93 | 0.270309 | 81.5785ms | 631514 | 30 | 2.48996e+07 | 337036 | 1.38517 | 1(Win) |
| glaze | 1660.95 | 0.698095 | 87.2545ms | 631514 | 30 | 1.92222e+08 | 362599 | 1.49032 | 2(Loss) |
