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
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 673.038 | 0.42103 | 1.96408ms | 1811 | 30 | 3501.91 | 2566.13 | 3.91515 | 1(Win) |
| glaze | 465.656 | 0.207695 | 1.29373ms | 1811 | 30 | 1780.24 | 3708.97 | 5.6783 | 2(Loss) |
| simdjson (ondemand) | 149.356 | 2.08395 | 3.17302ms | 1811 | 30 | 1.74217e+06 | 11563.7 | 17.7964 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 386.864 | 0.862954 | 1.59759ms | 1811 | 30 | 44526.2 | 4464.37 | 6.81984 | 1(Win) |
| glaze | 261.808 | 0.449756 | 4.23862ms | 1798 | 32 | 27766.2 | 6549.47 | 10.1079 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1278.69 | 0.0517677 | 1.20301ms | 3873 | 30 | 67.0816 | 2888.57 | 2.06601 | 1(Win) |
| glaze | 1041.34 | 0.157881 | 1.23455ms | 3873 | 30 | 940.792 | 3546.97 | 2.53836 | 2(Loss) |
| simdjson (ondemand) | 314.559 | 1.91596 | 3.21861ms | 3873 | 30 | 1.51839e+06 | 11742.1 | 8.44944 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1876.66 | 0.389257 | 0.994188ms | 3873 | 30 | 1760.83 | 1968.17 | 1.39258 | 1(Win) |
| glaze | 906.971 | 0.24329 | 1.4047ms | 3873 | 30 | 2944.94 | 4072.43 | 2.90163 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1301.81 | 0.0886182 | 1.17631ms | 3862 | 30 | 188.579 | 2829.2 | 2.02869 | 1(Win) |
| glaze | 919.487 | 0.143347 | 2.79501ms | 3862 | 32 | 1055.02 | 4005.59 | 2.87961 | 2(Loss) |
| simdjson (ondemand) | 313.71 | 1.37807 | 3.20846ms | 3862 | 30 | 785292 | 11740.4 | 8.4744 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1838.24 | 0.295772 | 0.97887ms | 3862 | 30 | 1053.56 | 2003.6 | 1.41757 | 1(Win) |
| glaze | 883.348 | 0.153526 | 2.84047ms | 3862 | 32 | 1311.22 | 4169.47 | 2.99099 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 947.22 | 0.263424 | 0.721221ms | 905 | 30 | 172.833 | 911.167 | 2.73864 | 1(Win) |
| glaze | 409.532 | 0.00494969 | 0.894653ms | 905 | 30 | 0.326437 | 2107.47 | 6.38998 | 2(Loss) |
| simdjson (ondemand) | 112.964 | 0.15237 | 2.24175ms | 905 | 30 | 4065.73 | 7640.3 | 23.508 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 896.081 | 0.153358 | 0.707084ms | 905 | 30 | 65.454 | 963.167 | 2.8979 | 1(Win) |
| glaze | 227.817 | 0.0879627 | 1.32069ms | 905 | 30 | 333.154 | 3788.47 | 11.5584 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1718.39 | 0.0820298 | 1.84753ms | 9578 | 30 | 570.386 | 5315.6 | 1.54066 | 1(Win) |
| glaze | 1371.68 | 0.315067 | 2.02908ms | 9578 | 30 | 13206 | 6659.2 | 1.93395 | 2(Loss) |
| simdjson (ondemand) | 783.985 | 0.209476 | 3.29029ms | 9578 | 30 | 17870 | 11651.1 | 3.38953 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3277.97 | 0.273945 | 1.20499ms | 9578 | 30 | 1748.19 | 2786.57 | 0.802701 | 1(Win) |
| glaze | 1891.39 | 0.236678 | 1.60106ms | 9578 | 30 | 3919.42 | 4829.4 | 1.39915 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3746.66 | 0.510787 | 14.937ms | 233995 | 30 | 2.77668e+06 | 59561.1 | 0.710619 | 1(Win) |
| simdjson (ondemand) | 3343.81 | 0.313118 | 16.5753ms | 233995 | 30 | 1.30999e+06 | 66736.8 | 0.796284 | 2(Loss) |
| glaze | 1269.08 | 0.257773 | 42.6952ms | 233995 | 30 | 6.16355e+06 | 175840 | 2.09874 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4663.58 | 0.293029 | 17.6765ms | 346753 | 30 | 1.29522e+06 | 70909 | 0.570955 | 1(Win) |
| simdjson (ondemand) | 4043.1 | 1.34086 | 19.8165ms | 346753 | 30 | 3.60829e+07 | 81791.1 | 0.658585 | 2(Loss) |
| glaze | 1523.47 | 0.283515 | 52.5226ms | 346753 | 30 | 1.13618e+07 | 217064 | 1.74837 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1004.05 | 0.563525 | 53.9458ms | 233995 | 30 | 4.70602e+07 | 222256 | 2.65284 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 983.945 | 0.201339 | 55.2357ms | 233995 | 30 | 6.25528e+06 | 226796 | 2.70704 | 2(Tie) |
| glaze STATISTICAL TIE | 978.502 | 0.262609 | 56.273ms | 233995 | 30 | 1.07605e+07 | 228058 | 2.7221 | 2(Tie) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2250.29 | 0.294758 | 24.5899ms | 233995 | 30 | 2.56324e+06 | 99167.4 | 1.18334 | 1(Win) |
| jsonifier | 1964.52 | 0.391484 | 27.9345ms | 233995 | 30 | 5.93263e+06 | 113592 | 1.35564 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1364.21 | 0.185972 | 59.0702ms | 346753 | 30 | 6.09671e+06 | 242403 | 1.95249 | 1(Win) |
| glaze | 1142.5 | 0.257421 | 70.7293ms | 346753 | 30 | 1.66546e+07 | 289443 | 2.33146 | 2(Loss) |
| jsonifier | 954.952 | 0.251572 | 84.648ms | 346753 | 30 | 2.27679e+07 | 346289 | 2.78934 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2243.51 | 0.33469 | 35.965ms | 346753 | 30 | 7.30117e+06 | 147399 | 1.18703 | 1(Win) |
| glaze | 2097.06 | 0.403125 | 38.616ms | 346753 | 30 | 1.21232e+07 | 157692 | 1.26947 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3610.96 | 0.270802 | 15.464ms | 233995 | 30 | 840219 | 61799.3 | 0.737329 | 1(Win) |
| simdjson (ondemand) | 2050.35 | 0.319959 | 26.6466ms | 233995 | 30 | 3.63804e+06 | 108837 | 1.29888 | 2(Loss) |
| glaze | 1257.46 | 0.195555 | 43.1305ms | 233995 | 30 | 3.61315e+06 | 177466 | 2.11816 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4577.06 | 0.582838 | 17.849ms | 346753 | 30 | 5.31966e+06 | 72249.2 | 0.581772 | 1(Win) |
| simdjson (ondemand) | 2742.6 | 0.765964 | 29.2223ms | 346753 | 30 | 2.55889e+07 | 120575 | 0.971044 | 2(Loss) |
| glaze | 1530.21 | 0.216567 | 52.3594ms | 346753 | 30 | 6.57123e+06 | 216108 | 1.74069 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1019.4 | 0.213346 | 53.3923ms | 233995 | 30 | 6.54358e+06 | 218909 | 2.61294 | 1(Win) |
| jsonifier | 875.38 | 0.198301 | 62.5307ms | 233995 | 30 | 7.66638e+06 | 254924 | 3.04278 | 2(Loss) |
| simdjson (ondemand) | 174.878 | 0.213257 | 327.417ms | 233995 | 30 | 2.22163e+08 | 1.27606e+06 | 15.2331 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2348.34 | 0.366946 | 23.5169ms | 233995 | 30 | 3.64768e+06 | 95026.6 | 1.13398 | 1(Win) |
| jsonifier | 2158.65 | 0.42003 | 25.4437ms | 233995 | 30 | 5.65626e+06 | 103377 | 1.23343 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1177.51 | 0.224416 | 68.0263ms | 346753 | 30 | 1.19163e+07 | 280838 | 2.26215 | 1(Win) |
| jsonifier | 953.733 | 0.479021 | 84.105ms | 346753 | 30 | 8.27595e+07 | 346732 | 2.7928 | 2(Loss) |
| simdjson (ondemand) | 257.045 | 0.210373 | 309.402ms | 346753 | 30 | 2.19748e+08 | 1.2865e+06 | 10.3637 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2617.28 | 0.332309 | 30.9506ms | 346753 | 30 | 5.28865e+06 | 126348 | 1.01746 | 1(Win) |
| glaze | 2146.37 | 0.529926 | 37.7268ms | 346753 | 30 | 1.99979e+07 | 154069 | 1.24069 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 728.217 | 0.262323 | 30.4784ms | 94651 | 30 | 3.17193e+06 | 123955 | 3.65711 | 1(Win) |
| glaze | 673.866 | 0.286588 | 33.085ms | 94651 | 30 | 4.42119e+06 | 133953 | 3.9524 | 2(Loss) |
| jsonifier | 570.664 | 0.340307 | 38.5906ms | 94651 | 30 | 8.69267e+06 | 158178 | 4.66721 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3035.42 | 0.77543 | 7.65768ms | 94651 | 30 | 1.59521e+06 | 29737.6 | 0.876485 | 1(Win) |
| jsonifier | 2280.44 | 0.668345 | 10.0656ms | 94651 | 30 | 2.0996e+06 | 39582.8 | 1.16671 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 996.685 | 0.307754 | 32.0835ms | 136024 | 30 | 4.8133e+06 | 130154 | 2.67206 | 1(Win) |
| glaze | 812.22 | 0.288585 | 39.3324ms | 136024 | 30 | 6.37312e+06 | 159714 | 3.27912 | 2(Loss) |
| jsonifier | 704.96 | 0.264092 | 45.2948ms | 136024 | 30 | 7.08489e+06 | 184014 | 3.77814 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3183.3 | 0.38939 | 10.2914ms | 136024 | 30 | 755382 | 40751 | 0.836028 | 1(Win) |
| glaze | 2686.15 | 0.541385 | 12.0195ms | 136046 | 30 | 2.05137e+06 | 48300.9 | 0.990956 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 489.436 | 0.104724 | 978.023ms | 2090234 | 30 | 5.45777e+08 | 4.07286e+06 | 5.44282 | 1(Win) |
| glaze STATISTICAL TIE | 378.687 | 0.576756 | 1244.89ms | 2090234 | 30 | 2.76526e+10 | 5.26399e+06 | 7.03463 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 375.746 | 0.294397 | 1278.71ms | 2090234 | 30 | 7.31794e+09 | 5.30519e+06 | 7.08983 | 2(Tie) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 859.022 | 0.0663161 | 558.725ms | 2090234 | 30 | 7.10462e+07 | 2.32055e+06 | 3.10099 | 1(Win) |
| glaze | 795.831 | 0.203103 | 600.564ms | 2090234 | 30 | 7.76428e+08 | 2.50481e+06 | 3.34726 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1082.41 | 0.25911 | 1410.14ms | 6661897 | 30 | 6.93902e+09 | 5.86955e+06 | 2.46114 | 1(Win) |
| glaze | 910.912 | 0.0545242 | 1680.97ms | 6661897 | 30 | 4.33853e+08 | 6.97464e+06 | 2.92452 | 2(Loss) |
| jsonifier | 882.527 | 0.278552 | 1726.1ms | 6661897 | 30 | 1.20635e+10 | 7.19896e+06 | 3.01849 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1927.28 | 0.151958 | 788.436ms | 6661897 | 30 | 7.52791e+08 | 3.29649e+06 | 1.38213 | 1(Win) |
| glaze | 1609.47 | 1.62051 | 920.926ms | 6661897 | 30 | 1.22759e+11 | 3.94743e+06 | 1.65509 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 979.115 | 0.395031 | 116.934ms | 500299 | 30 | 1.11167e+08 | 487300 | 2.72036 | 1(Win) |
| glaze | 904.814 | 0.187918 | 127.267ms | 500299 | 30 | 2.94578e+07 | 527315 | 2.94389 | 2(Loss) |
| simdjson (ondemand) | 702.494 | 0.64009 | 162.395ms | 500299 | 30 | 5.66993e+08 | 679183 | 3.79173 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2069.58 | 0.298411 | 56.2426ms | 500299 | 30 | 1.41986e+07 | 230540 | 1.28677 | 1(Win) |
| jsonifier | 1564.49 | 0.41537 | 73.8994ms | 500299 | 30 | 4.81399e+07 | 304970 | 1.70255 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1778.15 | 0.112848 | 186.131ms | 1439562 | 30 | 2.27736e+07 | 772081 | 1.49804 | 1(Win) |
| glaze | 1287.43 | 0.71251 | 257.301ms | 1439562 | 30 | 1.73187e+09 | 1.06637e+06 | 2.06904 | 2(Loss) |
| jsonifier | 1097 | 0.0925991 | 301.254ms | 1439562 | 30 | 4.02888e+07 | 1.25148e+06 | 2.42826 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2348.99 | 0.284595 | 141.194ms | 1439562 | 30 | 8.29994e+07 | 584454 | 1.13385 | 1(Win) |
| glaze | 2280.75 | 0.413369 | 145.204ms | 1439584 | 30 | 1.85744e+08 | 601948 | 1.16784 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 888.265 | 0.356822 | 15.2072ms | 56369 | 30 | 1.399e+06 | 60519.8 | 2.99737 | 1(Tie) |
| jsonifier STATISTICAL TIE | 881.033 | 0.420023 | 15.657ms | 56369 | 30 | 1.97044e+06 | 61016.6 | 3.02134 | 1(Tie) |
| simdjson (ondemand) | 792.718 | 0.472068 | 17.0023ms | 56369 | 30 | 3.0745e+06 | 67814.4 | 3.35882 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2733.64 | 1.44024 | 5.16879ms | 56369 | 30 | 2.40652e+06 | 19665.2 | 0.972239 | 1(Win) |
| jsonifier | 2046 | 0.666825 | 6.8411ms | 56369 | 30 | 920907 | 26274.6 | 1.29896 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1247.24 | 0.415806 | 18.1675ms | 94370 | 30 | 2.70066e+06 | 72157.7 | 2.13484 | 1(Win) |
| glaze | 1149.87 | 0.423094 | 19.4751ms | 94370 | 30 | 3.28979e+06 | 78268.4 | 2.31576 | 2(Loss) |
| jsonifier | 989.912 | 0.441146 | 22.7692ms | 94370 | 30 | 4.82572e+06 | 90915.4 | 2.68984 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2966.46 | 0.544192 | 7.798ms | 94370 | 30 | 817741 | 30338.6 | 0.896988 | 1(Win) |
| glaze | 2460.79 | 0.98809 | 9.23156ms | 94370 | 30 | 3.91771e+06 | 36572.9 | 1.08107 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 972.95 | 0.621299 | 13.2712ms | 52708 | 30 | 3.09097e+06 | 51663.8 | 2.73575 | 1(Win) |
| jsonifier | 749.574 | 0.653647 | 17.4784ms | 52708 | 30 | 5.7641e+06 | 67059.8 | 3.55216 | 2(Loss) |
| glaze | 697.632 | 0.559995 | 18.0394ms | 52708 | 30 | 4.88416e+06 | 72052.7 | 3.81668 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3627.94 | 0.109989 | 3.9085ms | 52708 | 30 | 6967.04 | 13855.3 | 0.731921 | 1(Win) |
| jsonifier | 2787.02 | 0.251388 | 4.89368ms | 52708 | 30 | 61671.5 | 18035.8 | 0.953655 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1211.22 | 0.411258 | 13.8538ms | 70103 | 30 | 1.54588e+06 | 55196.7 | 2.19723 | 1(Win) |
| glaze | 794.338 | 1.72525 | 20.8021ms | 70103 | 30 | 6.32543e+07 | 84165 | 3.35131 | 2(Loss) |
| jsonifier | 690.428 | 0.629773 | 24.9248ms | 70103 | 30 | 1.11564e+07 | 96831.9 | 3.85576 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3362.56 | 1.48249 | 5.31109ms | 70103 | 30 | 2.60639e+06 | 19882.3 | 0.790699 | 1(Win) |
| glaze | 2779.56 | 0.800276 | 6.32471ms | 70103 | 30 | 1.11153e+06 | 24052.5 | 0.956679 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 738.533 | 2.07468 | 4.22505ms | 11812 | 30 | 3.00422e+06 | 15252.9 | 3.59938 | 1(Win) |
| glaze | 701.953 | 0.237825 | 4.46779ms | 11812 | 30 | 43698.6 | 16047.8 | 3.78705 | 2(Loss) |
| simdjson (ondemand) | 640.737 | 1.77359 | 4.68881ms | 11812 | 30 | 2.91685e+06 | 17581 | 4.14939 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2126.62 | 0.189213 | 1.71828ms | 11812 | 30 | 3013.62 | 5297.03 | 1.24327 | 1(Win) |
| glaze | 1890 | 0.195855 | 1.91736ms | 11812 | 30 | 4088.03 | 5960.2 | 1.40209 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1508.19 | 0.102363 | 5.41369ms | 31235 | 30 | 12262.5 | 19750.8 | 1.76332 | 1(Win) |
| glaze | 1071.67 | 0.59519 | 7.26933ms | 31235 | 30 | 821091 | 27795.8 | 2.48293 | 2(Loss) |
| jsonifier | 1017.01 | 1.23661 | 7.64946ms | 31235 | 30 | 3.93568e+06 | 29289.7 | 2.61631 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2930.86 | 1.41869 | 2.8815ms | 31235 | 30 | 623717 | 10163.6 | 0.905567 | 1(Tie) |
| glaze STATISTICAL TIE | 2859.16 | 0.180268 | 2.97012ms | 31235 | 30 | 10582 | 10418.5 | 0.928787 | 1(Tie) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1623.77 | 0.337038 | 16.0533ms | 108313 | 30 | 1.37908e+06 | 63614.4 | 1.63917 | 1(Win) |
| glaze | 1102.05 | 0.368738 | 23.1578ms | 108313 | 30 | 3.58356e+06 | 93730.1 | 2.41584 | 2(Loss) |
| simdjson (ondemand) | 1070.64 | 0.329997 | 23.82ms | 108313 | 30 | 3.04101e+06 | 96480.2 | 2.48721 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2388.38 | 0.525669 | 10.8296ms | 108313 | 30 | 1.55061e+06 | 43249.1 | 1.11447 | 1(Tie) |
| glaze STATISTICAL TIE | 2379.08 | 0.506028 | 10.9435ms | 108313 | 30 | 1.44815e+06 | 43418.2 | 1.11855 | 1(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1903.76 | 0.297786 | 26.4103ms | 213963 | 30 | 3.05621e+06 | 107183 | 1.39884 | 1(Win) |
| glaze | 1472.21 | 0.646953 | 33.8134ms | 213963 | 30 | 2.41214e+07 | 138602 | 1.80886 | 2(Loss) |
| jsonifier | 1121.05 | 0.35402 | 44.3957ms | 213963 | 30 | 1.24568e+07 | 182018 | 2.37554 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3550.31 | 0.255412 | 14.305ms | 213963 | 30 | 646469 | 57474.1 | 0.749857 | 1(Win) |
| glaze | 2426.52 | 0.262475 | 20.7942ms | 213963 | 30 | 1.46153e+06 | 84092.1 | 1.09732 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 428.282 | 0.0680944 | 982.844ms | 1834197 | 30 | 2.32047e+08 | 4.08428e+06 | 6.22003 | 1(Win) |
| glaze | 351.028 | 0.0709264 | 1197.15ms | 1834197 | 30 | 3.74754e+08 | 4.98316e+06 | 7.58903 | 2(Loss) |
| simdjson (ondemand) | 336.228 | 0.389894 | 1253.89ms | 1834197 | 30 | 1.23435e+10 | 5.2025e+06 | 7.92302 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 511.582 | 0.0974072 | 821.107ms | 1834197 | 30 | 3.32785e+08 | 3.41925e+06 | 5.20714 | 1(Win) |
| glaze | 508.632 | 0.0869831 | 826.508ms | 1833577 | 30 | 2.68276e+08 | 3.43792e+06 | 5.2374 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1563.4 | 0.365117 | 1457.91ms | 9930848 | 30 | 1.46764e+10 | 6.05782e+06 | 1.70393 | 1(Win) |
| glaze | 1297.23 | 0.118052 | 1747.12ms | 9930848 | 30 | 2.22845e+09 | 7.30078e+06 | 2.05355 | 2(Loss) |
| jsonifier | 1244.36 | 0.514654 | 1843.76ms | 9930848 | 30 | 4.60292e+10 | 7.61098e+06 | 2.14076 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1771.89 | 0.26859 | 1284.9ms | 9930848 | 30 | 6.18301e+09 | 5.34502e+06 | 1.50344 | 1(Win) |
| glaze | 1370.24 | 0.613542 | 1583.17ms | 9930228 | 30 | 5.39426e+10 | 6.91132e+06 | 1.94402 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 788.694 | 0.402282 | 188.538ms | 642697 | 30 | 2.9321e+08 | 777138 | 3.37729 | 1(Win) |
| glaze | 671.059 | 0.111459 | 220.272ms | 642697 | 30 | 3.10914e+07 | 913368 | 3.96946 | 2(Loss) |
| simdjson (ondemand) | 568.962 | 0.630449 | 258.552ms | 642697 | 30 | 1.38378e+09 | 1.07727e+06 | 4.68187 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 841.474 | 0.112077 | 175.943ms | 642697 | 30 | 1.99934e+07 | 728393 | 3.16547 | 1(Win) |
| glaze | 714.972 | 0.0644682 | 206.666ms | 642692 | 30 | 9.16307e+06 | 857263 | 3.72573 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1023.92 | 0.687815 | 274.287ms | 1225964 | 30 | 1.85049e+09 | 1.14186e+06 | 2.60157 | 1(Win) |
| glaze | 1001.31 | 0.154259 | 281.69ms | 1225964 | 30 | 9.73278e+07 | 1.16764e+06 | 2.6603 | 2(Loss) |
| jsonifier | 886.623 | 0.104978 | 317.462ms | 1225964 | 30 | 5.74901e+07 | 1.31868e+06 | 3.00442 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1410.9 | 0.249687 | 199.535ms | 1225964 | 30 | 1.28433e+08 | 828668 | 1.88796 | 1(Win) |
| glaze | 1123.89 | 0.0438921 | 250.47ms | 1225970 | 30 | 6.2547e+06 | 1.04029e+06 | 2.37011 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 585.47 | 0.124855 | 162.024ms | 409725 | 30 | 2.0831e+07 | 667403 | 4.5497 | 1(Win) |
| jsonifier | 502.956 | 1.03815 | 188.58ms | 409725 | 30 | 1.9515e+09 | 776896 | 5.29554 | 2(Loss) |
| glaze | 454.114 | 0.177397 | 207.408ms | 409725 | 30 | 6.98985e+07 | 860453 | 5.8659 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1681.63 | 0.655967 | 56.1729ms | 409725 | 30 | 6.96959e+07 | 232360 | 1.58357 | 1(Win) |
| jsonifier | 1596.45 | 0.322336 | 59.5384ms | 409725 | 30 | 1.86731e+07 | 244759 | 1.66844 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1054.23 | 0.152589 | 171.753ms | 785750 | 30 | 3.52912e+07 | 710801 | 2.52673 | 1(Win) |
| glaze | 713.524 | 0.0983793 | 253.412ms | 785750 | 30 | 3.20244e+07 | 1.05021e+06 | 3.73338 | 2(Loss) |
| jsonifier | 624.262 | 0.096572 | 289.431ms | 785750 | 30 | 4.03143e+07 | 1.20038e+06 | 4.26701 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2103.96 | 0.437543 | 85.648ms | 785750 | 30 | 7.28543e+07 | 356161 | 1.26596 | 1(Win) |
| glaze | 1845.24 | 0.255019 | 99.2165ms | 785750 | 30 | 3.21758e+07 | 406099 | 1.44333 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 743.456 | 0.286044 | 2649.93ms | 8587914 | 30 | 2.97888e+10 | 1.10162e+07 | 3.58321 | 1(Win) |
| jsonifier | 668.06 | 0.154193 | 2965.29ms | 8587914 | 30 | 1.072e+10 | 1.22595e+07 | 3.98744 | 2(Loss) |
| glaze | 597.826 | 0.420309 | 3287.38ms | 8587914 | 30 | 9.9468e+10 | 1.36998e+07 | 4.45612 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2028.1 | 0.448889 | 983.574ms | 8588126 | 30 | 9.85863e+09 | 4.0384e+06 | 1.31345 | 1(Win) |
| jsonifier | 1903.83 | 0.886316 | 1052.79ms | 8588126 | 30 | 4.36153e+10 | 4.302e+06 | 1.39922 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 828.998 | 0.363828 | 2724.21ms | 9804437 | 30 | 5.05188e+10 | 1.1279e+07 | 3.21343 | 1(Win) |
| glaze | 626.19 | 0.172731 | 3610.39ms | 9804437 | 30 | 1.99569e+10 | 1.49319e+07 | 4.25424 | 2(Loss) |
| jsonifier | 580.568 | 0.408263 | 3801.89ms | 9804437 | 30 | 1.297e+11 | 1.61053e+07 | 4.58845 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2198.81 | 0.700795 | 1147.82ms | 11078090 | 30 | 3.40141e+10 | 4.80483e+06 | 1.21151 | 1(Win) |
| glaze | 1871.85 | 0.429835 | 1306.76ms | 11078090 | 30 | 1.76569e+10 | 5.6441e+06 | 1.42307 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3651.65 | 0.319435 | 17.2774ms | 264040 | 30 | 1.45562e+06 | 68957.4 | 0.729146 | 1(Win) |
| simdjson (ondemand) | 3465.25 | 0.377074 | 18.0545ms | 264040 | 30 | 2.2524e+06 | 72666.6 | 0.768403 | 2(Loss) |
| glaze | 1179.09 | 0.216831 | 51.8825ms | 264040 | 30 | 6.43296e+06 | 213562 | 2.25901 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4563.21 | 0.410801 | 20.7726ms | 399947 | 30 | 3.5371e+06 | 83585.6 | 0.583547 | 1(Win) |
| simdjson (ondemand) | 4406.65 | 0.362967 | 21.3427ms | 399947 | 30 | 2.96105e+06 | 86555.4 | 0.604298 | 2(Loss) |
| glaze | 1459.05 | 0.183679 | 63.4205ms | 399947 | 30 | 6.9168e+06 | 261417 | 1.8256 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1057.6 | 0.589551 | 58.751ms | 264040 | 30 | 5.91105e+07 | 238095 | 2.51802 | 1(Win) |
| glaze STATISTICAL TIE | 837.566 | 0.215221 | 73.5496ms | 264040 | 30 | 1.256e+07 | 300643 | 3.17978 | 2(Tie) |
| jsonifier STATISTICAL TIE | 831.513 | 0.329567 | 74.1327ms | 264040 | 30 | 2.9882e+07 | 302831 | 3.20288 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2985.74 | 0.615053 | 20.8325ms | 263923 | 30 | 8.06489e+06 | 84299.7 | 0.891556 | 1(Win) |
| jsonifier | 2311.45 | 0.33504 | 26.7633ms | 264040 | 30 | 3.99655e+06 | 108940 | 1.15209 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1422.3 | 0.292806 | 64.8758ms | 399947 | 30 | 1.84971e+07 | 268170 | 1.87262 | 1(Win) |
| glaze | 1017.32 | 0.2895 | 91.3643ms | 399947 | 30 | 3.53435e+07 | 374926 | 2.61805 | 2(Loss) |
| jsonifier | 816.015 | 0.341713 | 112.948ms | 399947 | 30 | 7.65339e+07 | 467417 | 3.26359 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3499.63 | 0.62872 | 26.8616ms | 399947 | 30 | 1.40863e+07 | 108988 | 0.760912 | 1(Win) |
| glaze | 2521.69 | 0.479661 | 37.0694ms | 399830 | 30 | 1.57818e+07 | 151211 | 1.05541 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1601.7 | 0.263004 | 67.4041ms | 466906 | 30 | 1.60378e+07 | 278003 | 1.66268 | 1(Win) |
| glaze | 1543.22 | 0.208968 | 70.1146ms | 466906 | 30 | 1.09065e+07 | 288537 | 1.72609 | 2(Loss) |
| simdjson (ondemand) | 766.044 | 0.594022 | 139.116ms | 466906 | 30 | 3.57666e+08 | 581267 | 3.47677 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2338.03 | 0.307476 | 69.1843ms | 699405 | 30 | 2.30835e+07 | 285285 | 1.13896 | 1(Win) |
| glaze | 2124.64 | 0.246677 | 75.7966ms | 699405 | 30 | 1.79915e+07 | 313938 | 1.25361 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1672.94 | 0.755784 | 86.4336ms | 631514 | 30 | 2.22086e+08 | 360000 | 1.59222 | 1(Win) |
| glaze | 1531.97 | 0.213631 | 95.0071ms | 631514 | 30 | 2.116e+07 | 393127 | 1.73881 | 2(Loss) |
