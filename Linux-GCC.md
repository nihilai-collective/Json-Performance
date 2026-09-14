# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 14, 2026)
#### Using the following commits:
----
| Jsonifier: [8a8469e](https://github.com/nihilai-collective/jsonifier/commit/8a8469e)  
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
| jsonifier | 558.241 | 0.056985 | 2.91774ms | 1811 | 30 | 93.2471 | 3093.83 | 4.12838 | 1(Win) |
| glaze | 417.642 | 0.0981098 | 1.43664ms | 1811 | 30 | 493.826 | 4135.37 | 5.53308 | 2(Loss) |
| simdjson (ondemand) | 137.717 | 2.00494 | 3.3613ms | 1811 | 30 | 1.89665e+06 | 12541 | 16.8849 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 394.178 | 0.0917941 | 1.48427ms | 1811 | 30 | 485.292 | 4381.53 | 5.86727 | 1(Win) |
| glaze | 275.963 | 0.298888 | 1.86745ms | 1798 | 30 | 10347 | 6213.53 | 8.40063 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1320.36 | 0.493765 | 2.27427ms | 3873 | 32 | 6105.22 | 2797.41 | 1.74341 | 1(Win) |
| glaze | 1007.99 | 0.0845272 | 1.25169ms | 3873 | 30 | 287.803 | 3664.3 | 2.29017 | 2(Loss) |
| simdjson (ondemand) | 301.642 | 0.0632555 | 3.34822ms | 3873 | 30 | 1799.82 | 12244.9 | 7.7093 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1349.94 | 0.0805771 | 1.18001ms | 3873 | 30 | 145.817 | 2736.1 | 1.70497 | 1(Win) |
| glaze | 1015.99 | 0.152541 | 1.28527ms | 3873 | 30 | 922.602 | 3635.47 | 2.27183 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1226.54 | 0.0897154 | 1.16027ms | 3862 | 30 | 217.73 | 3002.83 | 1.87883 | 1(Win) |
| glaze | 953.576 | 0.0908283 | 1.25257ms | 3862 | 30 | 369.214 | 3862.4 | 2.42208 | 2(Loss) |
| simdjson (ondemand) | 282.646 | 0.0892575 | 3.52819ms | 3862 | 30 | 4058.34 | 13030.7 | 8.2282 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1350.37 | 0.0881014 | 1.04517ms | 3862 | 30 | 173.223 | 2727.47 | 1.70458 | 1(Win) |
| glaze | 995.071 | 0.39783 | 1.26088ms | 3862 | 30 | 6504.78 | 3701.33 | 2.32036 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 753.646 | 0.214277 | 0.624626ms | 905 | 30 | 180.648 | 1145.2 | 2.99227 | 1(Win) |
| glaze | 417.388 | 0.144551 | 0.7766ms | 905 | 30 | 268.028 | 2067.8 | 5.48368 | 2(Loss) |
| simdjson (ondemand) | 97.2903 | 0.0918677 | 2.45948ms | 905 | 30 | 1992.53 | 8871.13 | 23.8718 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 827.705 | 0.122774 | 0.593268ms | 905 | 30 | 49.1678 | 1042.73 | 2.72416 | 1(Win) |
| glaze | 273.341 | 0.708974 | 1.06838ms | 905 | 30 | 15033.8 | 3157.5 | 8.42652 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1689.64 | 0.0586221 | 1.77503ms | 9578 | 30 | 301.306 | 5406.07 | 1.37063 | 1(Win) |
| glaze | 1379.3 | 0.120157 | 2.10832ms | 9578 | 30 | 1899.56 | 6622.4 | 1.68177 | 2(Loss) |
| simdjson (ondemand) | 697.537 | 0.287319 | 3.52511ms | 9578 | 30 | 42468.2 | 13095.1 | 3.33376 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3067.94 | 0.147227 | 1.0593ms | 9578 | 30 | 576.437 | 2977.33 | 0.750849 | 1(Win) |
| glaze | 1447.3 | 0.297238 | 1.88334ms | 9578 | 30 | 10557.5 | 6311.27 | 1.60074 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2489.33 | 1.03377 | 21.9117ms | 233995 | 30 | 2.57641e+07 | 89644.7 | 0.936349 | 1(Win) |
| jsonifier | 1512.95 | 0.704519 | 36.0882ms | 233995 | 30 | 3.23943e+07 | 147496 | 1.54066 | 2(Loss) |
| glaze | 1266.83 | 0.926343 | 42.5675ms | 233995 | 30 | 7.98804e+07 | 176152 | 1.84044 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3146.67 | 0.518659 | 25.7718ms | 346753 | 30 | 8.91296e+06 | 105092 | 0.740722 | 1(Win) |
| jsonifier | 2790.81 | 0.671041 | 29.1568ms | 346753 | 30 | 1.8967e+07 | 118492 | 0.835103 | 2(Loss) |
| glaze | 1557.06 | 1.2412 | 50.6885ms | 346753 | 30 | 2.08465e+08 | 212381 | 1.49743 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1076.93 | 0.70877 | 51.0012ms | 233995 | 30 | 6.47096e+07 | 207214 | 2.16496 | 1(Win) |
| glaze | 951.951 | 0.503201 | 57.4376ms | 233995 | 30 | 4.17435e+07 | 234419 | 2.44937 | 2(Loss) |
| simdjson (ondemand) | 861.487 | 1.09962 | 62.2106ms | 233995 | 30 | 2.43402e+08 | 259035 | 2.70636 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1999.34 | 0.707738 | 27.7329ms | 233995 | 30 | 1.872e+07 | 111614 | 1.16587 | 1(Win) |
| glaze | 1815.19 | 0.861676 | 30.2171ms | 233995 | 30 | 3.36651e+07 | 122938 | 1.28411 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1209.97 | 0.40813 | 66.3372ms | 346753 | 30 | 3.73259e+07 | 273304 | 1.92689 | 1(Tie) |
| glaze STATISTICAL TIE | 1208.15 | 0.517855 | 66.2635ms | 346753 | 30 | 6.0275e+07 | 273716 | 1.92982 | 1(Tie) |
| jsonifier | 935.376 | 0.473333 | 85.6535ms | 346753 | 30 | 8.40085e+07 | 353536 | 2.49257 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2119.28 | 1.02398 | 38.0231ms | 346753 | 30 | 7.65883e+07 | 156038 | 1.10004 | 1(Win) |
| glaze | 1723.25 | 0.608896 | 47.1113ms | 346753 | 30 | 4.09591e+07 | 191898 | 1.35292 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2509.79 | 1.17361 | 21.8396ms | 233995 | 30 | 3.26668e+07 | 88913.9 | 0.928692 | 1(Win) |
| simdjson (ondemand) | 1668.55 | 0.971986 | 32.5438ms | 233995 | 30 | 5.06965e+07 | 133742 | 1.3972 | 2(Loss) |
| glaze | 1279.31 | 0.663512 | 42.2045ms | 233995 | 30 | 4.01868e+07 | 174434 | 1.82251 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2680.56 | 1.85953 | 29.4825ms | 346753 | 30 | 1.57877e+08 | 123366 | 0.869451 | 1(Win) |
| simdjson (ondemand) | 2226.89 | 0.708735 | 36.3784ms | 346753 | 30 | 3.32301e+07 | 148498 | 1.04682 | 2(Loss) |
| glaze | 1587.89 | 0.59384 | 50.5375ms | 346753 | 30 | 4.58838e+07 | 208257 | 1.4684 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1013.74 | 0.691592 | 53.6281ms | 233995 | 30 | 6.95316e+07 | 220130 | 2.29998 | 1(Win) |
| jsonifier | 922.176 | 2.24361 | 56.9116ms | 233995 | 30 | 8.84302e+08 | 241987 | 2.52831 | 2(Loss) |
| simdjson (ondemand) | 185.619 | 0.344127 | 289.358ms | 233995 | 30 | 5.13483e+08 | 1.20222e+06 | 12.5625 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2291.33 | 1.08356 | 24.4125ms | 233995 | 30 | 3.34092e+07 | 97390.9 | 1.01723 | 1(Win) |
| glaze | 1832.77 | 0.751026 | 29.7594ms | 233995 | 30 | 2.50858e+07 | 121758 | 1.27181 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1215.71 | 0.495275 | 66.3862ms | 346753 | 30 | 5.44496e+07 | 272014 | 1.91788 | 1(Win) |
| jsonifier | 921.088 | 0.520328 | 87.2167ms | 346753 | 30 | 1.04692e+08 | 359020 | 2.53149 | 2(Loss) |
| simdjson (ondemand) | 245.978 | 0.18739 | 298.79ms | 346753 | 30 | 1.90397e+08 | 1.34438e+06 | 9.48008 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2457.57 | 0.849169 | 33.3871ms | 346753 | 30 | 3.91686e+07 | 134559 | 0.948536 | 1(Win) |
| glaze | 1643.63 | 0.53115 | 50.3693ms | 346753 | 30 | 3.42601e+07 | 201194 | 1.41847 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 686.734 | 1.13673 | 32.0004ms | 94651 | 30 | 6.69744e+07 | 131443 | 3.39466 | 1(Win) |
| jsonifier | 637.491 | 0.762268 | 34.9027ms | 94651 | 30 | 3.49493e+07 | 141596 | 3.65707 | 2(Loss) |
| simdjson (ondemand) | 544.858 | 2.1346 | 33.8855ms | 94651 | 30 | 3.7518e+08 | 165669 | 4.27619 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2836.59 | 2.49395 | 8.03015ms | 94651 | 30 | 1.88954e+07 | 31822.1 | 0.821126 | 1(Tie) |
| glaze STATISTICAL TIE | 2775.36 | 2.03905 | 8.45865ms | 94651 | 30 | 1.31943e+07 | 32524.1 | 0.838443 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 926.302 | 0.790652 | 34.1971ms | 136024 | 30 | 3.67806e+07 | 140044 | 2.51683 | 1(Win) |
| glaze | 825.904 | 1.55574 | 37.3954ms | 136024 | 30 | 1.79129e+08 | 157067 | 2.82287 | 2(Loss) |
| jsonifier | 699.963 | 0.631551 | 45.097ms | 136024 | 30 | 4.10978e+07 | 185328 | 3.3309 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3346.92 | 1.86544 | 22.7022ms | 136024 | 32 | 1.67284e+07 | 38758.8 | 0.696055 | 1(Win) |
| glaze | 1615.56 | 1.02118 | 19.2864ms | 136046 | 30 | 2.01768e+07 | 80308.7 | 1.44235 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 442.236 | 0.0921827 | 1084.55ms | 2090234 | 30 | 5.17968e+08 | 4.50756e+06 | 5.27302 | 1(Win) |
| glaze STATISTICAL TIE | 353.401 | 0.139366 | 1361.08ms | 2090234 | 30 | 1.85392e+09 | 5.64063e+06 | 6.59855 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 353.148 | 0.101973 | 1364.4ms | 2090234 | 30 | 9.93966e+08 | 5.64467e+06 | 6.60332 | 2(Tie) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 891.397 | 0.275308 | 537.484ms | 2090234 | 30 | 1.13712e+09 | 2.23627e+06 | 2.61605 | 1(Win) |
| glaze | 718.733 | 0.120475 | 672.856ms | 2090234 | 30 | 3.34943e+08 | 2.7735e+06 | 3.24452 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1030.88 | 0.15775 | 1489.43ms | 6661897 | 30 | 2.83557e+09 | 6.16297e+06 | 2.26209 | 1(Win) |
| jsonifier | 887.31 | 0.122403 | 1710.03ms | 6661897 | 30 | 2.30437e+09 | 7.16016e+06 | 2.62811 | 2(Loss) |
| glaze | 840.336 | 0.125008 | 1819.3ms | 6661897 | 30 | 2.67969e+09 | 7.5604e+06 | 2.77501 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1876.37 | 0.313654 | 812.295ms | 6661897 | 30 | 3.38361e+09 | 3.38594e+06 | 1.24271 | 1(Win) |
| glaze | 1364.96 | 0.363061 | 1100.33ms | 6661897 | 30 | 8.56714e+09 | 4.65456e+06 | 1.70831 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 925.955 | 0.574033 | 123.65ms | 500299 | 30 | 2.62467e+08 | 515276 | 2.51825 | 1(Win) |
| jsonifier | 782.035 | 1.84769 | 140.806ms | 500299 | 30 | 3.81232e+09 | 610104 | 2.98159 | 2(Loss) |
| simdjson (ondemand) | 596.159 | 0.266385 | 193.113ms | 500299 | 30 | 1.36357e+08 | 800328 | 3.9116 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1826.86 | 0.696653 | 64.2081ms | 500299 | 30 | 9.93122e+07 | 261170 | 1.27622 | 1(Win) |
| jsonifier | 1771.13 | 0.510622 | 65.9466ms | 500299 | 30 | 5.67646e+07 | 269388 | 1.31647 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1506.51 | 0.291071 | 219.516ms | 1439562 | 30 | 2.11074e+08 | 911291 | 1.5479 | 1(Win) |
| glaze | 1441.52 | 0.27648 | 229.189ms | 1439562 | 30 | 2.08002e+08 | 952378 | 1.61766 | 2(Loss) |
| jsonifier | 1266.47 | 0.214093 | 260.49ms | 1439562 | 30 | 1.61584e+08 | 1.08402e+06 | 1.84129 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3413.02 | 0.467982 | 99.4557ms | 1439562 | 30 | 1.06307e+08 | 402246 | 0.683197 | 1(Win) |
| glaze | 1923.05 | 0.327409 | 177.393ms | 1439584 | 30 | 1.63907e+08 | 713916 | 1.21261 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 834.703 | 0.923284 | 16.2064ms | 56369 | 30 | 1.06074e+07 | 64403.4 | 2.79223 | 1(Win) |
| jsonifier | 798.393 | 1.90309 | 16.9539ms | 56369 | 30 | 4.92593e+07 | 67332.3 | 2.91891 | 2(Loss) |
| simdjson (ondemand) | 690.566 | 1.40254 | 21.6491ms | 56369 | 30 | 3.5762e+07 | 77845.8 | 3.37505 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1845.98 | 2.1241 | 7.37683ms | 56369 | 30 | 1.14787e+07 | 29121.4 | 1.26181 | 1(Win) |
| jsonifier | 1746.96 | 1.21843 | 7.86298ms | 56369 | 30 | 4.21734e+06 | 30772.1 | 1.33344 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1136.18 | 1.39814 | 19.6641ms | 94370 | 30 | 3.6796e+07 | 79211.5 | 2.05145 | 1(Win) |
| simdjson (ondemand) | 1079.39 | 1.16727 | 20.5678ms | 94370 | 30 | 2.8417e+07 | 83379.1 | 2.15943 | 2(Loss) |
| jsonifier | 854.543 | 1.20086 | 26.402ms | 94370 | 30 | 4.79849e+07 | 105317 | 2.72747 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2469.91 | 1.42919 | 9.18548ms | 94370 | 30 | 8.13585e+06 | 36437.8 | 0.943245 | 1(Win) |
| glaze | 1664.29 | 1.3975 | 13.3725ms | 94370 | 30 | 1.71332e+07 | 54076.1 | 1.39999 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 856.772 | 1.04072 | 14.8822ms | 52708 | 30 | 1.11843e+07 | 58669.3 | 2.71895 | 1(Win) |
| glaze | 681.212 | 2.01189 | 18.0684ms | 52708 | 30 | 6.61176e+07 | 73789.5 | 3.42017 | 2(Loss) |
| jsonifier | 625.062 | 1.27322 | 20.3182ms | 52708 | 30 | 3.14511e+07 | 80418.1 | 3.72424 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2947.42 | 0.549747 | 43.8862ms | 52708 | 128 | 1.12514e+06 | 17054.4 | 0.789582 | 1(Win) |
| glaze | 2710.25 | 0.301508 | 4.99572ms | 52708 | 30 | 93811.3 | 18546.7 | 0.858361 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1111.01 | 0.847931 | 15.5501ms | 70103 | 30 | 7.8105e+06 | 60175.3 | 2.09677 | 1(Win) |
| glaze | 768.266 | 2.33195 | 20.8535ms | 70103 | 30 | 1.23541e+08 | 87021.2 | 3.0328 | 2(Loss) |
| jsonifier | 513.8 | 1.76542 | 32.4987ms | 70103 | 30 | 1.58308e+08 | 130120 | 4.53347 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3127.17 | 0.391683 | 5.6853ms | 70103 | 30 | 210359 | 21378.9 | 0.744487 | 1(Win) |
| glaze | 2254.79 | 1.10305 | 7.6094ms | 70103 | 30 | 3.209e+06 | 29650.4 | 1.033 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 675.872 | 0.246468 | 4.70672ms | 11812 | 30 | 50624.4 | 16667.1 | 3.44311 | 1(Win) |
| jsonifier | 629.071 | 1.70019 | 10.7265ms | 11812 | 32 | 2.96613e+06 | 17907 | 3.69947 | 2(Loss) |
| simdjson (ondemand) | 579.467 | 0.125393 | 11.5718ms | 11812 | 32 | 19014.5 | 19439.9 | 4.01682 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2490.13 | 0.130561 | 3.06571ms | 11812 | 32 | 1116.31 | 4523.78 | 0.929616 | 1(Win) |
| glaze | 1329.35 | 0.253077 | 10.8666ms | 11812 | 64 | 29434.3 | 8473.91 | 1.7468 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1407.27 | 0.0260358 | 5.48924ms | 31235 | 30 | 911.151 | 21167.2 | 1.65438 | 1(Win) |
| glaze | 1068.77 | 1.12952 | 7.12432ms | 31235 | 30 | 2.97324e+06 | 27871.4 | 2.17921 | 2(Loss) |
| jsonifier | 1004.54 | 0.868541 | 17.599ms | 31235 | 32 | 2.12265e+06 | 29653.3 | 2.31854 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2812.47 | 0.638203 | 2.91013ms | 31235 | 30 | 137071 | 10591.4 | 0.826341 | 1(Win) |
| glaze | 1876.78 | 0.971718 | 9.42918ms | 31235 | 32 | 761177 | 15871.8 | 1.23922 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1653.58 | 0.964751 | 15.7818ms | 108313 | 30 | 1.08958e+07 | 62467.6 | 1.40941 | 1(Win) |
| glaze | 981.289 | 0.563549 | 26.1147ms | 108313 | 30 | 1.05573e+07 | 105265 | 2.37557 | 2(Loss) |
| simdjson (ondemand) | 804.578 | 0.867142 | 31.3732ms | 108313 | 30 | 3.71815e+07 | 128384 | 2.89767 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1951.98 | 0.856154 | 13.1877ms | 108313 | 30 | 6.15791e+06 | 52918.1 | 1.19395 | 1(Win) |
| glaze | 1682.31 | 1.44577 | 15.1628ms | 108313 | 30 | 2.36412e+07 | 61401.1 | 1.3853 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1445.05 | 0.798624 | 34.5482ms | 213963 | 30 | 3.81521e+07 | 141207 | 1.61319 | 1(Win) |
| glaze | 1300.49 | 1.5256 | 38.1222ms | 213963 | 30 | 1.71896e+08 | 156903 | 1.79265 | 2(Loss) |
| jsonifier | 1137.35 | 0.702949 | 44.1374ms | 213963 | 30 | 4.77155e+07 | 179409 | 2.04956 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3009.78 | 1.48248 | 16.729ms | 213963 | 30 | 3.03045e+07 | 67796 | 0.774234 | 1(Win) |
| glaze | 1556.08 | 0.703878 | 32.4827ms | 213963 | 30 | 2.55581e+07 | 131131 | 1.49797 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 417.952 | 0.184783 | 1009.62ms | 1834197 | 30 | 1.79425e+09 | 4.18524e+06 | 5.5792 | 1(Win) |
| glaze | 330.199 | 0.329064 | 1255.95ms | 1834197 | 30 | 9.11636e+09 | 5.29749e+06 | 7.06234 | 2(Loss) |
| simdjson (ondemand) | 283.916 | 0.125998 | 1472.46ms | 1834197 | 30 | 1.80783e+09 | 6.16107e+06 | 8.21347 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 532.075 | 0.159749 | 784.842ms | 1834197 | 30 | 8.27459e+08 | 3.28756e+06 | 4.38244 | 1(Win) |
| glaze | 336.599 | 0.0827947 | 1252.87ms | 1833577 | 30 | 5.55009e+08 | 5.19502e+06 | 6.92764 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1316.63 | 0.189379 | 1727.08ms | 9930848 | 30 | 5.56712e+09 | 7.19323e+06 | 1.77109 | 1(Win) |
| jsonifier | 1292.26 | 0.107393 | 1768.01ms | 9930848 | 30 | 1.85844e+09 | 7.32889e+06 | 1.80427 | 2(Loss) |
| glaze | 1228 | 0.201234 | 1855.84ms | 9930848 | 30 | 7.2261e+09 | 7.7124e+06 | 1.89899 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1779.94 | 0.190971 | 1307.65ms | 9930848 | 30 | 3.09754e+09 | 5.32086e+06 | 1.31011 | 1(Win) |
| glaze | 1072.58 | 0.162184 | 2132.2ms | 9930228 | 30 | 6.15173e+09 | 8.82937e+06 | 2.17409 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 791.334 | 0.413718 | 186.427ms | 642697 | 30 | 3.08051e+08 | 774545 | 2.94682 | 1(Win) |
| glaze | 650.697 | 0.172741 | 228.759ms | 642697 | 30 | 7.94264e+07 | 941949 | 3.58379 | 2(Loss) |
| simdjson (ondemand) | 597.758 | 0.15944 | 250.823ms | 642697 | 30 | 8.01825e+07 | 1.02537e+06 | 3.90121 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 871.467 | 0.413841 | 170.314ms | 642697 | 30 | 2.54155e+08 | 703324 | 2.67577 | 1(Win) |
| glaze | 595.412 | 0.293162 | 250.88ms | 642692 | 30 | 2.73217e+08 | 1.0294e+06 | 3.91657 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1099.17 | 0.145006 | 256.697ms | 1225964 | 30 | 7.13712e+07 | 1.06369e+06 | 2.12157 | 1(Win) |
| glaze | 987.85 | 0.143291 | 286.352ms | 1225964 | 30 | 8.62842e+07 | 1.18355e+06 | 2.36066 | 2(Loss) |
| jsonifier | 791.983 | 0.197669 | 356.226ms | 1225964 | 30 | 2.55459e+08 | 1.47626e+06 | 2.94448 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1459.48 | 1.28719 | 197.391ms | 1225964 | 30 | 3.18983e+09 | 801089 | 1.59778 | 1(Win) |
| glaze | 960.07 | 0.180462 | 293.569ms | 1225970 | 30 | 1.44892e+08 | 1.2178e+06 | 2.42901 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 518.298 | 0.446176 | 182.069ms | 409725 | 30 | 3.39437e+08 | 753899 | 4.49916 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 515.473 | 0.223464 | 182.323ms | 409725 | 30 | 8.60815e+07 | 758031 | 4.52387 | 1(Tie) |
| glaze | 406.446 | 0.184048 | 233.69ms | 409725 | 30 | 9.39209e+07 | 961369 | 5.73753 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1380.84 | 0.626751 | 70.5826ms | 409725 | 30 | 9.43652e+07 | 282976 | 1.68852 | 1(Win) |
| jsonifier | 1343.29 | 0.447722 | 72.1975ms | 409725 | 30 | 5.08843e+07 | 290886 | 1.73578 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 940.852 | 0.442895 | 192.001ms | 785750 | 30 | 3.73292e+08 | 796459 | 2.47854 | 1(Win) |
| glaze | 662.259 | 0.266592 | 272.347ms | 785750 | 30 | 2.72978e+08 | 1.13151e+06 | 3.52131 | 2(Loss) |
| jsonifier | 648.587 | 0.164632 | 279.011ms | 785750 | 30 | 1.08538e+08 | 1.15536e+06 | 3.59549 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2022.68 | 0.419526 | 91.8027ms | 785750 | 30 | 7.24693e+07 | 370473 | 1.1528 | 1(Win) |
| glaze | 1500.08 | 0.329776 | 123.878ms | 785750 | 30 | 8.14136e+07 | 499539 | 1.55447 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 580.682 | 0.522455 | 3437.61ms | 8587914 | 30 | 1.62899e+11 | 1.41042e+07 | 4.01596 | 1(Win) |
| jsonifier | 522.922 | 0.515063 | 3682.16ms | 8587914 | 30 | 1.95228e+11 | 1.56621e+07 | 4.45946 | 2(Loss) |
| glaze | 502.292 | 0.621136 | 3934.84ms | 8587914 | 30 | 3.07721e+11 | 1.63054e+07 | 4.64277 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1734.44 | 0.353421 | 1154.38ms | 8588126 | 30 | 8.35574e+09 | 4.72215e+06 | 1.34436 | 1(Tie) |
| glaze STATISTICAL TIE | 1725.49 | 0.636952 | 1142.59ms | 8588126 | 30 | 2.74225e+10 | 4.74664e+06 | 1.35137 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 636.922 | 0.425867 | 3552.08ms | 9804437 | 30 | 1.17258e+11 | 1.46803e+07 | 3.66139 | 1(Win) |
| jsonifier STATISTICAL TIE | 500.155 | 0.362528 | 4464.66ms | 9804437 | 30 | 1.37797e+11 | 1.86947e+07 | 4.66259 | 2(Tie) |
| glaze STATISTICAL TIE | 499.62 | 0.311675 | 4446.05ms | 9804437 | 30 | 1.02068e+11 | 1.87147e+07 | 4.66764 | 2(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1959.09 | 0.462693 | 1290.29ms | 11078090 | 30 | 1.86779e+10 | 5.39276e+06 | 1.1902 | 1(Win) |
| glaze | 1638.57 | 0.283595 | 1543.82ms | 11078090 | 30 | 1.00304e+10 | 6.44763e+06 | 1.42305 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2613.5 | 1.20103 | 23.6371ms | 264040 | 30 | 4.01717e+07 | 96348.9 | 0.891885 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2545.76 | 1.16952 | 24.4411ms | 264040 | 30 | 4.01458e+07 | 98912.6 | 0.91566 | 1(Tie) |
| glaze | 1038.02 | 0.634081 | 58.8815ms | 264040 | 30 | 7.0981e+07 | 242586 | 2.24629 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3445.3 | 0.961885 | 27.1297ms | 399947 | 30 | 3.40187e+07 | 110707 | 0.676473 | 1(Win) |
| jsonifier | 2886.87 | 0.841045 | 32.4683ms | 399947 | 30 | 3.70433e+07 | 132122 | 0.807408 | 2(Loss) |
| glaze | 1295.39 | 0.542827 | 71.4338ms | 399947 | 30 | 7.66392e+07 | 294444 | 1.8 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 885.801 | 1.70571 | 68.4268ms | 264040 | 30 | 7.05343e+08 | 284272 | 2.63186 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 859.979 | 0.653397 | 70.7782ms | 264040 | 30 | 1.09809e+08 | 292807 | 2.71121 | 1(Tie) |
| glaze | 798.087 | 0.588816 | 76.8396ms | 264040 | 30 | 1.03543e+08 | 315515 | 2.92155 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2316.45 | 0.964734 | 27.42ms | 263923 | 30 | 3.29643e+07 | 108656 | 1.00618 | 1(Win) |
| jsonifier | 2251.68 | 0.828859 | 27.8123ms | 264040 | 30 | 2.57757e+07 | 111831 | 1.03496 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1236.06 | 0.546481 | 75.2179ms | 399947 | 30 | 8.53096e+07 | 308577 | 1.88636 | 1(Win) |
| glaze | 964.517 | 0.425406 | 96.2211ms | 399947 | 30 | 8.49013e+07 | 395451 | 2.41753 | 2(Loss) |
| jsonifier | 773.94 | 0.671618 | 119.639ms | 399947 | 30 | 3.28667e+08 | 492828 | 3.01211 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3028.82 | 0.784515 | 31.3348ms | 399947 | 30 | 2.92808e+07 | 125930 | 0.769559 | 1(Win) |
| glaze | 2021.8 | 0.634001 | 47.2133ms | 399830 | 30 | 4.2892e+07 | 188598 | 1.15308 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1345.06 | 0.806775 | 80.5154ms | 466906 | 30 | 2.13994e+08 | 331046 | 1.73345 | 1(Tie) |
| glaze STATISTICAL TIE | 1343.52 | 0.567541 | 80.3918ms | 466906 | 30 | 1.06142e+08 | 331425 | 1.73553 | 1(Tie) |
| simdjson (ondemand) | 657.113 | 0.448977 | 164.209ms | 466906 | 30 | 2.77683e+08 | 677625 | 3.54861 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2073.34 | 0.442587 | 80.0695ms | 699405 | 30 | 6.08183e+07 | 321705 | 1.1246 | 1(Win) |
| glaze | 1644.03 | 0.457269 | 98.4594ms | 699405 | 30 | 1.03254e+08 | 405714 | 1.41835 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1659.92 | 0.35339 | 88.1409ms | 631514 | 30 | 4.93201e+07 | 362825 | 1.40473 | 1(Win) |
| glaze | 1529.29 | 0.510056 | 95.2365ms | 631514 | 30 | 1.21045e+08 | 393817 | 1.5248 | 2(Loss) |
