# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 591.17 | 0.126739 | 2.65165ms | 1811 | 30 | 411.293 | 2921.5 | 3.89343 | 1(Win) |
| glaze | 479.578 | 0.083443 | 1.09725ms | 1811 | 30 | 270.907 | 3601.3 | 4.8134 | 2(Loss) |
| simdjson (ondemand) | 151.491 | 0.447067 | 2.95524ms | 1811 | 30 | 77935 | 11400.7 | 15.3435 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 366.253 | 0.0720294 | 1.43117ms | 1811 | 30 | 346.11 | 4715.6 | 6.31645 | 1(Win) |
| glaze | 257.075 | 2.00312 | 8.10776ms | 1798 | 64 | 1.14249e+06 | 6670.06 | 9.01713 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 974.38 | 0.0825172 | 1.09925ms | 3873 | 30 | 293.528 | 3790.7 | 2.37054 | 1(Win) |
| jsonifier | 722.546 | 0.216381 | 1.55056ms | 3873 | 30 | 3670.51 | 5111.9 | 3.20151 | 2(Loss) |
| simdjson (ondemand) | 348.445 | 0.0523822 | 6.29288ms | 3873 | 32 | 986.609 | 10600.2 | 6.67103 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1458.34 | 0.0947845 | 0.88546ms | 3873 | 30 | 172.892 | 2532.73 | 1.57518 | 1(Win) |
| glaze | 1098.75 | 0.183976 | 0.987171ms | 3873 | 30 | 1147.48 | 3361.63 | 2.09808 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1342.75 | 0.110116 | 1.88874ms | 3862 | 32 | 291.931 | 2742.94 | 1.71264 | 1(Win) |
| glaze | 803.887 | 0.0746953 | 1.31325ms | 3862 | 30 | 351.352 | 4581.6 | 2.87838 | 2(Loss) |
| simdjson (ondemand) | 344.175 | 0.934138 | 2.75204ms | 3862 | 30 | 299784 | 10701.2 | 6.75241 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1585.31 | 0.207977 | 0.828995ms | 3862 | 30 | 700.409 | 2323.27 | 1.4483 | 1(Win) |
| glaze | 1063 | 0.213284 | 1.03632ms | 3862 | 30 | 1638.3 | 3464.8 | 2.16958 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 566.248 | 0.0517269 | 0.626855ms | 905 | 30 | 18.6483 | 1524.2 | 4.01831 | 1(Win) |
| glaze | 449.464 | 0.139104 | 0.653866ms | 905 | 30 | 214.047 | 1920.23 | 5.0867 | 2(Loss) |
| simdjson (ondemand) | 114.377 | 0.0799422 | 2.03228ms | 905 | 30 | 1091.68 | 7545.9 | 20.294 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 691.013 | 0.398198 | 0.525315ms | 905 | 30 | 742.069 | 1249 | 3.27665 | 1(Win) |
| glaze | 282.941 | 0.262727 | 0.898285ms | 905 | 30 | 1926.79 | 3050.37 | 8.14405 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1861.17 | 0.0540686 | 1.53374ms | 9578 | 30 | 211.247 | 4907.83 | 1.24401 | 1(Win) |
| glaze | 1461.48 | 0.0617842 | 1.6964ms | 9578 | 30 | 447.344 | 6250.03 | 1.58593 | 2(Loss) |
| simdjson (ondemand) | 778.635 | 0.0629373 | 3.04328ms | 9578 | 30 | 1635.39 | 11731.2 | 2.98563 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3223.68 | 0.197034 | 0.963117ms | 9578 | 30 | 935.086 | 2833.5 | 0.713931 | 1(Win) |
| glaze | 2202.36 | 0.1739 | 1.20544ms | 9578 | 30 | 1560.6 | 4147.5 | 1.04945 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2712.15 | 1.00682 | 20.0621ms | 233995 | 30 | 2.05879e+07 | 82279.7 | 0.859455 | 1(Win) |
| simdjson (ondemand) | 2634.06 | 0.867352 | 20.6ms | 233995 | 30 | 1.61985e+07 | 84719.2 | 0.884839 | 2(Loss) |
| glaze | 1455.46 | 0.558508 | 37.0996ms | 233995 | 30 | 2.19985e+07 | 153323 | 1.60192 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3482.26 | 0.847239 | 23.1128ms | 346753 | 30 | 1.94201e+07 | 94964 | 0.669282 | 1(Win) |
| simdjson (ondemand) | 3330.98 | 0.813343 | 24.0599ms | 346753 | 30 | 1.95598e+07 | 99276.8 | 0.699663 | 2(Loss) |
| glaze | 1807.68 | 0.50337 | 44.3332ms | 346753 | 30 | 2.54387e+07 | 182936 | 1.28977 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1246.52 | 0.56461 | 43.7275ms | 233995 | 30 | 3.06501e+07 | 179022 | 1.87038 | 1(Win) |
| glaze | 915.863 | 0.653976 | 137.04ms | 233995 | 32 | 8.12506e+07 | 243655 | 2.54581 | 2(Loss) |
| simdjson (ondemand) | 831.696 | 0.447273 | 65.033ms | 233995 | 30 | 4.32066e+07 | 268313 | 2.80336 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2228.43 | 1.21582 | 24.1415ms | 233995 | 30 | 4.44706e+07 | 100140 | 1.04598 | 1(Win) |
| glaze | 1922.51 | 0.813071 | 27.8073ms | 233995 | 30 | 2.67211e+07 | 116075 | 1.21246 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1276.61 | 0.458513 | 62.4868ms | 346753 | 30 | 4.23206e+07 | 259038 | 1.82631 | 1(Win) |
| glaze | 1232.11 | 0.542836 | 65.0885ms | 346753 | 30 | 6.368e+07 | 268394 | 1.8924 | 2(Loss) |
| simdjson (ondemand) | 1156.72 | 0.508385 | 68.6803ms | 346753 | 30 | 6.33708e+07 | 285885 | 2.01554 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2121.34 | 0.607842 | 37.9808ms | 346753 | 30 | 2.69353e+07 | 155887 | 1.09899 | 1(Win) |
| glaze | 1665.38 | 0.521887 | 49.4263ms | 346753 | 30 | 3.22172e+07 | 198567 | 1.39995 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2650.15 | 0.914365 | 20.6694ms | 233995 | 30 | 1.77841e+07 | 84204.7 | 0.879513 | 1(Win) |
| simdjson (ondemand) | 1893.74 | 0.519891 | 28.7971ms | 233995 | 30 | 1.12595e+07 | 117839 | 1.23091 | 2(Loss) |
| glaze | 1447.84 | 0.663088 | 37.1318ms | 233995 | 30 | 3.13352e+07 | 154129 | 1.61033 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3456.26 | 0.573772 | 23.3823ms | 346753 | 30 | 9.04126e+06 | 95678.5 | 0.674289 | 1(Win) |
| simdjson (ondemand) | 2472.79 | 0.748317 | 32.346ms | 346753 | 30 | 3.0044e+07 | 133731 | 0.942697 | 2(Loss) |
| glaze | 1773.37 | 1.18233 | 44.4639ms | 346753 | 30 | 1.45826e+08 | 186475 | 1.31471 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1147.93 | 0.540206 | 47.288ms | 233995 | 30 | 3.30841e+07 | 194397 | 2.03105 | 1(Win) |
| glaze | 959.408 | 0.610653 | 56.2473ms | 233995 | 30 | 6.05225e+07 | 232597 | 2.43032 | 2(Loss) |
| simdjson (ondemand) | 219.526 | 0.135216 | 244.266ms | 233995 | 30 | 5.66783e+07 | 1.01653e+06 | 10.6227 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2245.86 | 0.931284 | 23.5943ms | 233995 | 30 | 2.56883e+07 | 99362.9 | 1.03794 | 1(Win) |
| glaze | 1997.24 | 0.793618 | 27.269ms | 233995 | 30 | 2.35882e+07 | 111731 | 1.16707 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1279.64 | 0.517139 | 62.8998ms | 346753 | 30 | 5.35795e+07 | 258423 | 1.822 | 1(Tie) |
| glaze STATISTICAL TIE | 1267.35 | 0.519998 | 63.2627ms | 346753 | 30 | 5.52298e+07 | 260930 | 1.8398 | 1(Tie) |
| simdjson (ondemand) | 318.038 | 0.12941 | 250.914ms | 346753 | 30 | 5.43173e+07 | 1.03978e+06 | 7.33233 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2078.48 | 0.570517 | 38.5478ms | 346753 | 30 | 2.47177e+07 | 159102 | 1.1216 | 1(Win) |
| glaze | 1663.68 | 0.562628 | 48.045ms | 346753 | 30 | 3.75201e+07 | 198769 | 1.40138 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 679.596 | 0.691217 | 32.3154ms | 94651 | 30 | 2.52871e+07 | 132823 | 3.43021 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 617.261 | 0.998078 | 34.886ms | 94651 | 30 | 6.39093e+07 | 146237 | 3.77627 | 2(Tie) |
| glaze STATISTICAL TIE | 610.012 | 0.597542 | 35.9315ms | 94651 | 30 | 2.34548e+07 | 147974 | 3.82187 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2713.55 | 1.09731 | 8.38555ms | 94651 | 30 | 3.99722e+06 | 33265 | 0.858479 | 1(Win) |
| glaze | 2502.48 | 1.8803 | 20.3417ms | 94651 | 32 | 1.47202e+07 | 36070.7 | 0.930614 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 880.319 | 0.569356 | 35.7642ms | 136024 | 30 | 2.11174e+07 | 147359 | 2.64822 | 1(Win) |
| jsonifier | 771.024 | 0.699951 | 41.1207ms | 136024 | 30 | 4.16056e+07 | 168247 | 3.02385 | 2(Loss) |
| glaze | 714.701 | 0.532476 | 43.8021ms | 136024 | 30 | 2.80223e+07 | 181506 | 3.26208 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3336.85 | 2.13864 | 9.56162ms | 136024 | 30 | 2.07374e+07 | 38875.8 | 0.698133 | 1(Win) |
| glaze | 1868.89 | 1.17427 | 17.1298ms | 136046 | 30 | 1.99372e+07 | 69422.9 | 1.24688 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 447.267 | 0.0941935 | 1072.85ms | 2090234 | 30 | 5.28711e+08 | 4.45685e+06 | 5.21409 | 1(Win) |
| glaze | 356.901 | 0.131585 | 1343.14ms | 2090234 | 30 | 1.62042e+09 | 5.58531e+06 | 6.53427 | 2(Loss) |
| simdjson (ondemand) | 303.794 | 0.157776 | 1585.98ms | 2090234 | 30 | 3.2154e+09 | 6.5617e+06 | 7.67653 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 675.715 | 0.0777942 | 708.899ms | 2090234 | 30 | 1.58008e+08 | 2.95007e+06 | 3.45126 | 1(Win) |
| glaze | 660.268 | 0.174354 | 724.922ms | 2090234 | 30 | 8.31254e+08 | 3.01908e+06 | 3.53199 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1192.33 | 0.0987465 | 1285.52ms | 6661897 | 30 | 8.30557e+08 | 5.32847e+06 | 1.95591 | 1(Win) |
| glaze | 940.639 | 0.1927 | 1616.56ms | 6661897 | 30 | 5.08201e+09 | 6.75422e+06 | 2.47926 | 2(Loss) |
| simdjson (ondemand) | 913.608 | 0.0983914 | 1669.89ms | 6661897 | 30 | 1.40447e+09 | 6.95405e+06 | 2.55261 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1936.26 | 0.0973365 | 794.318ms | 6661897 | 30 | 3.06015e+08 | 3.28122e+06 | 1.20442 | 1(Win) |
| glaze | 1485.47 | 0.168438 | 1030.56ms | 6661897 | 30 | 1.55694e+09 | 4.27696e+06 | 1.56992 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1006.01 | 0.281647 | 114.127ms | 500299 | 30 | 5.35292e+07 | 474274 | 2.31788 | 1(Win) |
| glaze | 820.268 | 0.35448 | 140.128ms | 500299 | 30 | 1.27542e+08 | 581666 | 2.84281 | 2(Loss) |
| simdjson (ondemand) | 501.477 | 0.187793 | 228.691ms | 500299 | 30 | 9.57714e+07 | 951434 | 4.65021 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2010.32 | 0.551102 | 57.4582ms | 500299 | 30 | 5.13234e+07 | 237337 | 1.15978 | 1(Win) |
| jsonifier | 1804.44 | 0.471777 | 63.8539ms | 500299 | 30 | 4.66842e+07 | 264416 | 1.29212 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1897.39 | 0.220364 | 174.433ms | 1439562 | 30 | 7.62689e+07 | 723558 | 1.22901 | 1(Win) |
| glaze | 1483.82 | 0.258966 | 221.571ms | 1439562 | 30 | 1.72228e+08 | 925228 | 1.57158 | 2(Loss) |
| simdjson (ondemand) | 1311.43 | 0.215972 | 253.029ms | 1439562 | 30 | 1.53351e+08 | 1.04685e+06 | 1.77819 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3374.32 | 0.362844 | 98.3059ms | 1439562 | 30 | 6.5381e+07 | 406860 | 0.690994 | 1(Win) |
| glaze | 2094.15 | 0.270226 | 159.301ms | 1439584 | 30 | 9.41534e+07 | 655586 | 1.11352 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 950.883 | 0.626626 | 14.18ms | 56369 | 30 | 3.765e+06 | 56534.5 | 2.45074 | 1(Win) |
| glaze | 819.365 | 0.568658 | 16.3527ms | 56369 | 30 | 4.1759e+06 | 65609 | 2.84456 | 2(Loss) |
| simdjson (ondemand) | 690.308 | 0.598755 | 19.3162ms | 56369 | 30 | 6.52251e+06 | 77874.9 | 3.37671 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1981.48 | 1.18265 | 6.75684ms | 56369 | 30 | 3.08841e+06 | 27130 | 1.17526 | 1(Win) |
| jsonifier | 1666.47 | 1.79876 | 7.96338ms | 56369 | 30 | 1.01008e+07 | 32258.5 | 1.39783 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1116.82 | 1.28746 | 19.8059ms | 94370 | 30 | 3.22915e+07 | 80584.4 | 2.08686 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1076.35 | 0.646376 | 20.6786ms | 94370 | 30 | 8.76296e+06 | 83614.1 | 2.16559 | 2(Tie) |
| glaze STATISTICAL TIE | 1068.41 | 0.630452 | 20.6156ms | 94370 | 30 | 8.46092e+06 | 84235.7 | 2.18166 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2439.76 | 1.55277 | 9.03791ms | 94370 | 30 | 9.84258e+06 | 36888.2 | 0.954939 | 1(Win) |
| glaze | 1440.67 | 0.717309 | 15.2692ms | 94370 | 30 | 6.02378e+06 | 62469.5 | 1.61764 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 841.983 | 0.982451 | 14.7793ms | 52708 | 30 | 1.03202e+07 | 59699.9 | 2.76744 | 1(Win) |
| jsonifier | 754.329 | 1.73186 | 16.6006ms | 52708 | 30 | 3.99559e+07 | 66637.1 | 3.08796 | 2(Loss) |
| glaze | 699.187 | 1.32095 | 17.6279ms | 52708 | 30 | 2.70557e+07 | 71892.5 | 3.33317 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2671.93 | 1.76176 | 10.8281ms | 52708 | 32 | 3.51518e+06 | 18812.7 | 0.870835 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2614.02 | 0.0939123 | 4.99821ms | 52708 | 30 | 9783.64 | 19229.5 | 0.890466 | 1(Tie) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1071.7 | 1.59197 | 15.4283ms | 70103 | 30 | 2.95881e+07 | 62382.7 | 2.17423 | 1(Win) |
| glaze | 837.764 | 0.696164 | 19.7432ms | 70103 | 30 | 9.25922e+06 | 79802.3 | 2.78183 | 2(Loss) |
| jsonifier | 719.107 | 1.55741 | 23.1401ms | 70103 | 30 | 6.28947e+07 | 92970 | 3.23713 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2925.14 | 1.96091 | 5.76553ms | 70103 | 30 | 6.02585e+06 | 22855.5 | 0.795966 | 1(Win) |
| glaze | 2477.41 | 1.15626 | 6.73877ms | 70103 | 30 | 2.92086e+06 | 26986 | 0.939965 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 716.098 | 0.178227 | 4.1193ms | 11812 | 30 | 23581.3 | 15730.8 | 3.24945 | 1(Win) |
| glaze | 568.343 | 1.30952 | 11.3503ms | 11812 | 32 | 2.15575e+06 | 19820.4 | 4.0955 | 2(Loss) |
| simdjson (ondemand) | 547.227 | 1.33397 | 5.19062ms | 11812 | 30 | 2.26217e+06 | 20585.2 | 4.2546 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2382.5 | 0.233635 | 1.33581ms | 11812 | 30 | 3660.81 | 4728.13 | 0.971958 | 1(Win) |
| glaze | 1237.52 | 0.174034 | 2.4573ms | 11812 | 30 | 7528.96 | 9102.73 | 1.87635 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1440.15 | 2.22511 | 5.24434ms | 31235 | 30 | 6.35461e+06 | 20683.9 | 1.61633 | 1(Win) |
| simdjson (ondemand) | 1359.41 | 0.0583993 | 5.61268ms | 31235 | 30 | 4912.66 | 21912.4 | 1.71276 | 2(Loss) |
| glaze | 1102.17 | 1.15009 | 6.72223ms | 31235 | 30 | 2.89847e+06 | 27026.7 | 2.11314 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2944.7 | 0.306925 | 2.65281ms | 31235 | 30 | 28919.3 | 10115.8 | 0.789238 | 1(Win) |
| glaze | 1879.37 | 1.68991 | 3.99575ms | 31235 | 30 | 2.15234e+06 | 15850 | 1.23798 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1820.46 | 0.667374 | 14.0965ms | 108313 | 30 | 4.3019e+06 | 56741.5 | 1.28018 | 1(Win) |
| glaze | 1018.3 | 0.918703 | 25.1195ms | 108313 | 30 | 2.60543e+07 | 101439 | 2.28895 | 2(Loss) |
| simdjson (ondemand) | 787.847 | 0.781534 | 31.7455ms | 108313 | 30 | 3.14988e+07 | 131111 | 2.95886 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1871.25 | 0.772164 | 13.5064ms | 108313 | 30 | 5.4505e+06 | 55201.1 | 1.24548 | 1(Win) |
| glaze | 1759.79 | 0.551176 | 14.4008ms | 108313 | 30 | 3.14008e+06 | 58697.4 | 1.32427 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1566.4 | 0.818446 | 31.6625ms | 213963 | 30 | 3.41014e+07 | 130267 | 1.48813 | 1(Win) |
| glaze STATISTICAL TIE | 1454.81 | 1.01803 | 33.8877ms | 213963 | 30 | 6.11652e+07 | 140259 | 1.60242 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1428.62 | 0.766541 | 34.2381ms | 213963 | 30 | 3.59613e+07 | 142831 | 1.63177 | 2(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2279.48 | 0.838283 | 21.7511ms | 213963 | 30 | 1.68931e+07 | 89516.5 | 1.02258 | 1(Win) |
| glaze | 1685.13 | 0.729699 | 29.2571ms | 213963 | 30 | 2.34218e+07 | 121089 | 1.38321 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 456.623 | 0.132017 | 918.813ms | 1834197 | 30 | 7.67291e+08 | 3.83079e+06 | 5.10716 | 1(Win) |
| glaze | 354.668 | 0.158055 | 1183.53ms | 1834197 | 30 | 1.82299e+09 | 4.93201e+06 | 6.57537 | 2(Loss) |
| simdjson (ondemand) | 273.936 | 0.0707687 | 1536.02ms | 1834197 | 30 | 6.12627e+08 | 6.38552e+06 | 8.51325 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 393.911 | 0.0482133 | 1066.99ms | 1833577 | 30 | 1.37422e+08 | 4.43917e+06 | 5.92033 | 1(Win) |
| jsonifier | 384.503 | 0.0340048 | 1093.57ms | 1834197 | 30 | 7.17952e+07 | 4.54932e+06 | 6.06518 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1661.21 | 0.124753 | 1373.72ms | 9930848 | 30 | 1.51757e+09 | 5.70115e+06 | 1.40382 | 1(Win) |
| glaze | 1340.14 | 0.119061 | 1695.59ms | 9930848 | 30 | 2.12388e+09 | 7.06702e+06 | 1.74018 | 2(Loss) |
| simdjson (ondemand) | 1302.17 | 0.119762 | 1747.43ms | 9930848 | 30 | 2.27614e+09 | 7.27311e+06 | 1.79092 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1646.84 | 0.286401 | 1378.51ms | 9930848 | 30 | 8.13842e+09 | 5.7509e+06 | 1.41609 | 1(Win) |
| glaze | 1344.18 | 0.0946049 | 1697.96ms | 9930228 | 30 | 1.33276e+09 | 7.04534e+06 | 1.7349 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 830.782 | 0.19919 | 177.103ms | 642697 | 30 | 6.47882e+07 | 737767 | 2.8069 | 1(Win) |
| glaze | 741.51 | 0.164542 | 200.114ms | 642697 | 30 | 5.54951e+07 | 826589 | 3.14484 | 2(Loss) |
| simdjson (ondemand) | 547.977 | 0.631619 | 267.239ms | 642697 | 30 | 1.49734e+09 | 1.11852e+06 | 4.25561 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 705.022 | 0.114331 | 209.067ms | 642697 | 30 | 2.96384e+07 | 869368 | 3.30759 | 1(Win) |
| glaze | 635.601 | 0.134858 | 231.973ms | 642692 | 30 | 5.07358e+07 | 964315 | 3.6689 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1215.05 | 0.149348 | 231.362ms | 1225964 | 30 | 6.1957e+07 | 962244 | 1.91922 | 1(Win) |
| glaze | 1144.62 | 0.15341 | 245.602ms | 1225964 | 30 | 7.36655e+07 | 1.02145e+06 | 2.03735 | 2(Loss) |
| simdjson (ondemand) | 1006.04 | 0.173396 | 278.802ms | 1225964 | 30 | 1.21821e+08 | 1.16215e+06 | 2.31797 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1243.72 | 0.119312 | 226.525ms | 1225964 | 30 | 3.77395e+07 | 940058 | 1.87496 | 1(Win) |
| glaze | 1039.67 | 0.204644 | 270.077ms | 1225970 | 30 | 1.58888e+08 | 1.12456e+06 | 2.24299 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 591.072 | 0.166525 | 160.032ms | 409725 | 30 | 3.63568e+07 | 661077 | 3.94523 | 1(Win) |
| simdjson (ondemand) | 496.809 | 0.171883 | 189.608ms | 409725 | 30 | 5.48267e+07 | 786508 | 4.69387 | 2(Loss) |
| glaze | 414.659 | 0.137046 | 226.786ms | 409725 | 30 | 5.00333e+07 | 942327 | 5.62386 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1401.53 | 0.48377 | 67.7378ms | 409725 | 30 | 5.45728e+07 | 278798 | 1.66361 | 1(Win) |
| jsonifier | 1239.61 | 0.411304 | 75.9836ms | 409725 | 30 | 5.04271e+07 | 315216 | 1.88101 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 905.46 | 0.152776 | 199.303ms | 785750 | 30 | 4.79579e+07 | 827590 | 2.57546 | 1(Win) |
| jsonifier | 808.478 | 0.155396 | 222.999ms | 785750 | 30 | 6.22347e+07 | 926865 | 2.8844 | 2(Loss) |
| glaze | 654.242 | 0.176858 | 276.092ms | 785750 | 30 | 1.23102e+08 | 1.14537e+06 | 3.56444 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1950.92 | 0.337915 | 92.4165ms | 785750 | 30 | 5.05386e+07 | 384100 | 1.19522 | 1(Win) |
| glaze | 1630.2 | 0.258601 | 110.83ms | 785750 | 30 | 4.23905e+07 | 459667 | 1.43039 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 748.645 | 0.175587 | 2631.42ms | 8587914 | 30 | 1.10696e+10 | 1.09399e+07 | 3.11506 | 1(Win) |
| simdjson (ondemand) | 654.252 | 0.11684 | 3012.26ms | 8587914 | 30 | 6.41788e+09 | 1.25182e+07 | 3.56451 | 2(Loss) |
| glaze | 628.098 | 0.12626 | 3129.3ms | 8587914 | 30 | 8.13161e+09 | 1.30395e+07 | 3.71293 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2244.9 | 0.160661 | 881.037ms | 8588126 | 30 | 1.03073e+09 | 3.6484e+06 | 1.03879 | 1(Win) |
| glaze | 2176.18 | 0.189164 | 905.833ms | 8588126 | 30 | 1.52056e+09 | 3.7636e+06 | 1.07157 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 720.861 | 0.215163 | 3118.73ms | 9804437 | 30 | 2.33668e+10 | 1.29709e+07 | 3.23509 | 1(Win) |
| jsonifier | 708.896 | 0.117088 | 3170.69ms | 9804437 | 30 | 7.15525e+09 | 1.31899e+07 | 3.28972 | 2(Loss) |
| glaze | 654.067 | 0.705961 | 3436.43ms | 9804437 | 30 | 3.05552e+11 | 1.42955e+07 | 3.5655 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2444.15 | 0.192407 | 1042.8ms | 11078090 | 30 | 2.0751e+09 | 4.32253e+06 | 0.95409 | 1(Win) |
| glaze | 2087.77 | 0.135081 | 1216.69ms | 11078090 | 30 | 1.40177e+09 | 5.06037e+06 | 1.11695 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2757.4 | 0.848222 | 22.4385ms | 264040 | 30 | 1.80003e+07 | 91320.9 | 0.845252 | 1(Win) |
| simdjson (ondemand) | 2666.15 | 1.15192 | 22.9034ms | 264040 | 30 | 3.55085e+07 | 94446.2 | 0.874195 | 2(Loss) |
| glaze | 1115.7 | 0.653975 | 54.4706ms | 264040 | 30 | 6.53567e+07 | 225696 | 2.08973 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3633.45 | 0.789333 | 25.7354ms | 399947 | 30 | 2.05972e+07 | 104974 | 0.641505 | 1(Win) |
| simdjson (ondemand) | 3553.28 | 0.507118 | 26.2699ms | 399947 | 30 | 8.88965e+06 | 107343 | 0.656001 | 2(Loss) |
| glaze | 1538.69 | 0.316535 | 60.21ms | 399947 | 30 | 1.84701e+07 | 247886 | 1.51527 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 984.952 | 0.644347 | 64.0276ms | 264040 | 30 | 8.14085e+07 | 255655 | 2.36711 | 1(Win) |
| simdjson (ondemand) | 842.383 | 1.00277 | 73.1642ms | 264040 | 30 | 2.69553e+08 | 298924 | 2.76781 | 2(Loss) |
| glaze | 806.946 | 0.53664 | 75.8152ms | 264040 | 30 | 8.41277e+07 | 312051 | 2.88936 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2435.24 | 0.749726 | 25.2243ms | 264040 | 30 | 1.80294e+07 | 103402 | 0.957081 | 1(Win) |
| glaze | 2272.01 | 0.78379 | 26.938ms | 263923 | 30 | 2.2618e+07 | 110781 | 1.02594 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1214.46 | 0.496944 | 78.0817ms | 399947 | 30 | 7.30759e+07 | 314065 | 1.91987 | 1(Win) |
| jsonifier | 1019.33 | 0.677798 | 91.0362ms | 399947 | 30 | 1.92972e+08 | 374185 | 2.28743 | 2(Loss) |
| glaze | 995.951 | 0.613946 | 94.304ms | 399947 | 30 | 1.65848e+08 | 382970 | 2.34111 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3010.43 | 0.861061 | 30.8093ms | 399947 | 30 | 3.57058e+07 | 126699 | 0.774237 | 1(Win) |
| glaze | 2274.5 | 0.723344 | 41.1564ms | 399830 | 30 | 4.41153e+07 | 167644 | 1.02495 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1409.16 | 0.342767 | 76.2191ms | 466906 | 30 | 3.5193e+07 | 315986 | 1.6547 | 1(Win) |
| jsonifier | 1222.65 | 0.791235 | 87.366ms | 466906 | 30 | 2.49108e+08 | 364189 | 1.90707 | 2(Loss) |
| simdjson (ondemand) | 637.24 | 0.227593 | 168.207ms | 466906 | 30 | 7.58738e+07 | 698757 | 3.65934 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2027.43 | 0.4556 | 79.33ms | 699405 | 30 | 6.7399e+07 | 328990 | 1.15006 | 1(Win) |
| glaze | 1798.13 | 0.587842 | 89.0788ms | 699405 | 30 | 1.42646e+08 | 370944 | 1.29679 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2352.39 | 0.390728 | 62.5041ms | 631514 | 30 | 3.00205e+07 | 256020 | 0.991195 | 1(Win) |
| glaze | 1451.99 | 0.356252 | 99.7082ms | 631514 | 30 | 6.55046e+07 | 414781 | 1.60596 | 2(Loss) |
