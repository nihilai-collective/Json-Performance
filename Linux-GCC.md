# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1020-azure using the GCC 16.0.1 compiler).  

Latest Results: (Aug 08, 2026)
#### Using the following commits:
----
| Jsonifier: [66d99df](https://github.com/nihilai-collective/jsonifier/commit/66d99df)  
| Glaze: [72b670e](https://github.com/stephenberry/glaze/commit/72b670e)  
| Simdjson: [20b2871](https://github.com/simdjson/simdjson/commit/20b2871)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (INTEL(R) XEON(R) PLATINUM 8573C-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)

#### Note:
  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 740.422 | 0.0386162 | 6.27926ms | 1811 | 64 | 51.9276 | 2332.59 | 2.89659 | 1(Win) |
| glaze | 548.212 | 0.0309542 | 1.27042ms | 1811 | 30 | 28.5299 | 3150.43 | 3.94434 | 2(Loss) |
| simdjson (ondemand) | 140.854 | 0.193735 | 3.45565ms | 1811 | 30 | 16929.3 | 12261.7 | 15.5173 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 419.085 | 0.247128 | 2.45219ms | 1811 | 30 | 3111.71 | 4121.13 | 5.16241 | 1(Win) |
| glaze | 324.004 | 0.506327 | 1.81925ms | 1798 | 30 | 21540.7 | 5292.23 | 6.71624 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1406.74 | 0.0392283 | 1.51006ms | 3873 | 30 | 31.8264 | 2625.63 | 1.53653 | 1(Win) |
| glaze | 1129.7 | 0.0440849 | 1.22221ms | 3873 | 30 | 62.3264 | 3269.53 | 1.91452 | 2(Loss) |
| simdjson (ondemand) | 312.214 | 2.37027 | 3.29458ms | 3873 | 30 | 2.35889e+06 | 11830.3 | 7.00184 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1876.12 | 0.332579 | 0.986004ms | 3873 | 30 | 1286.13 | 1968.73 | 1.14502 | 1(Win) |
| glaze | 892.816 | 0.154573 | 1.51216ms | 3873 | 30 | 1226.76 | 4137 | 2.42826 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1417.86 | 0.0390014 | 1.1247ms | 3862 | 30 | 30.792 | 2597.63 | 1.52317 | 1(Win) |
| glaze | 1136.1 | 0.0446085 | 1.23162ms | 3862 | 30 | 62.7402 | 3241.87 | 1.90461 | 2(Loss) |
| simdjson (ondemand) | 304.52 | 0.0291389 | 3.49469ms | 3862 | 30 | 372.616 | 12094.7 | 7.17846 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1624.3 | 0.190279 | 1.04449ms | 3862 | 30 | 558.466 | 2267.5 | 1.32146 | 1(Win) |
| glaze | 894.308 | 0.173695 | 1.47614ms | 3862 | 30 | 1535.14 | 4118.37 | 2.42177 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1288.3 | 0.129406 | 0.596031ms | 905 | 30 | 22.5471 | 669.933 | 1.62173 | 1(Win) |
| glaze | 443.505 | 0.0211203 | 0.93443ms | 905 | 30 | 5.06782 | 1946.03 | 4.80317 | 2(Loss) |
| simdjson (ondemand) | 126.359 | 0.0857266 | 2.17855ms | 905 | 30 | 1028.57 | 6830.33 | 17.2648 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 775.333 | 0.690001 | 0.707147ms | 905 | 30 | 1769.87 | 1113.17 | 2.75779 | 1(Win) |
| glaze | 236.647 | 0.146069 | 2.66572ms | 905 | 32 | 908.152 | 3647.09 | 9.07631 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2611.89 | 0.0619591 | 1.36061ms | 9578 | 30 | 140.855 | 3497.2 | 0.830967 | 1(Win) |
| glaze | 1802.58 | 0.106723 | 1.73606ms | 9578 | 30 | 877.402 | 5067.33 | 1.20672 | 2(Loss) |
| simdjson (ondemand) | 877.024 | 0.0605227 | 2.98413ms | 9578 | 30 | 1192.02 | 10415.1 | 2.49312 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2422.2 | 0.123046 | 1.40242ms | 9578 | 30 | 645.926 | 3771.07 | 0.896777 | 1(Win) |
| glaze | 1778.65 | 0.162808 | 1.74421ms | 9578 | 30 | 2097.22 | 5135.53 | 1.22073 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3746.19 | 0.0555823 | 5.59355ms | 33713 | 32 | 728.177 | 8582.38 | 0.582935 | 1(Win) |
| simdjson (ondemand) | 3710.66 | 0.32649 | 2.80737ms | 33713 | 30 | 24008 | 8664.57 | 0.588295 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 4909.7 | 0.0717404 | 5.80686ms | 48024 | 32 | 1433.12 | 9328.31 | 0.445074 | 1(Win) |
| jsonifier | 4375.31 | 0.968251 | 13.1072ms | 48024 | 64 | 657438 | 10467.7 | 0.499405 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1200.06 | 0.460896 | 57.4668ms | 294588 | 30 | 3.49262e+07 | 234106 | 1.82728 | 1(Win) |
| jsonifier STATISTICAL TIE | 1162.87 | 0.353478 | 58.4156ms | 294588 | 30 | 2.18783e+07 | 241593 | 1.88582 | 2(Tie) |
| glaze STATISTICAL TIE | 1162.42 | 0.604117 | 61.7662ms | 294588 | 30 | 6.39541e+07 | 241686 | 1.88663 | 2(Tie) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3257.4 | 1.63985 | 21.0137ms | 294588 | 30 | 6.00095e+07 | 86247.1 | 0.672907 | 1(Win) |
| glaze | 2852.13 | 0.708617 | 24.4363ms | 294588 | 30 | 1.46163e+07 | 98502.2 | 0.768447 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1575.32 | 0.311726 | 60.2182ms | 406546 | 30 | 1.76585e+07 | 246117 | 1.39206 | 1(Win) |
| glaze | 1238.75 | 0.230456 | 75.7476ms | 406546 | 30 | 1.56081e+07 | 312987 | 1.77034 | 2(Loss) |
| jsonifier | 1021.77 | 0.927398 | 88.4635ms | 406546 | 30 | 3.7151e+08 | 379453 | 2.14636 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3524.66 | 1.11454 | 27.1222ms | 406546 | 30 | 4.50916e+07 | 110000 | 0.62197 | 1(Win) |
| glaze | 2939.13 | 0.484887 | 32.0969ms | 406546 | 30 | 1.22739e+07 | 131914 | 0.745848 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3270.78 | 0.0535121 | 2.92996ms | 33713 | 30 | 830.075 | 9829.83 | 0.667897 | 1(Win) |
| simdjson (ondemand) | 2355.54 | 1.82298 | 3.78779ms | 33713 | 30 | 1.85737e+06 | 13649.2 | 0.92849 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4126.52 | 0.0890361 | 3.1973ms | 48024 | 30 | 2929.56 | 11098.8 | 0.529606 | 1(Win) |
| simdjson (ondemand) | 2816.21 | 1.19995 | 4.41712ms | 48024 | 30 | 1.14243e+06 | 16262.7 | 0.776881 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1215.03 | 0.378468 | 60.3264ms | 294588 | 30 | 2.29738e+07 | 231221 | 1.80478 | 1(Win) |
| jsonifier | 1036.53 | 0.393312 | 67.5984ms | 294588 | 30 | 3.40926e+07 | 271039 | 2.11571 | 2(Loss) |
| simdjson (ondemand) | 238.79 | 0.582719 | 287.131ms | 294588 | 30 | 1.41006e+09 | 1.17652e+06 | 9.18496 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3353.56 | 1.00729 | 21.2315ms | 294588 | 30 | 2.13624e+07 | 83774 | 0.653686 | 1(Win) |
| glaze | 2889.61 | 0.358715 | 23.9363ms | 294588 | 30 | 3.64898e+06 | 97224.6 | 0.758591 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1277.94 | 0.200982 | 72.2034ms | 406546 | 30 | 1.1154e+07 | 303388 | 1.716 | 1(Win) |
| jsonifier | 1034.76 | 0.688039 | 92.1923ms | 406546 | 30 | 1.99381e+08 | 374687 | 2.11945 | 2(Loss) |
| simdjson (ondemand) | 344.417 | 0.744257 | 276.796ms | 406546 | 30 | 2.10581e+09 | 1.12571e+06 | 6.36809 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3338.78 | 0.605791 | 28.8633ms | 406546 | 30 | 1.4846e+07 | 116124 | 0.656611 | 1(Win) |
| glaze | 3002.93 | 0.871052 | 31.4234ms | 406546 | 30 | 3.79437e+07 | 129112 | 0.730043 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 723.308 | 0.299164 | 30.2838ms | 94651 | 30 | 4.18161e+06 | 124796 | 3.03119 | 1(Win) |
| glaze STATISTICAL TIE | 706.709 | 1.01109 | 32.4045ms | 94651 | 30 | 5.00343e+07 | 127728 | 3.10239 | 2(Tie) |
| jsonifier STATISTICAL TIE | 694.228 | 0.339694 | 32.4827ms | 94651 | 30 | 5.85254e+06 | 130024 | 3.15828 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3918.64 | 0.689845 | 13.9266ms | 94651 | 32 | 808038 | 23035.1 | 0.558335 | 1(Win) |
| jsonifier | 3135.69 | 0.985496 | 7.59452ms | 94651 | 30 | 2.41444e+06 | 28786.7 | 0.698438 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1071.75 | 0.410949 | 29.2852ms | 136024 | 30 | 7.42231e+06 | 121038 | 2.04573 | 1(Win) |
| glaze | 939.335 | 0.344342 | 35.4484ms | 136024 | 30 | 6.78409e+06 | 138100 | 2.33429 | 2(Loss) |
| jsonifier | 728.439 | 0.556683 | 47.281ms | 136024 | 30 | 2.94837e+07 | 178083 | 3.01015 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3471.96 | 0.609996 | 9.49998ms | 136046 | 30 | 1.55883e+06 | 37369 | 0.630817 | 1(Win) |
| jsonifier | 3279.86 | 0.475339 | 10.1795ms | 136024 | 30 | 1.06034e+06 | 39551.2 | 0.667912 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 475.11 | 0.576339 | 989.14ms | 2090234 | 30 | 1.7542e+10 | 4.19567e+06 | 4.61628 | 1(Win) |
| glaze | 429.131 | 0.669253 | 1122.35ms | 2090234 | 30 | 2.89943e+10 | 4.64521e+06 | 5.11106 | 2(Loss) |
| simdjson (ondemand) | 402.871 | 0.665164 | 1192.82ms | 2090234 | 30 | 3.24966e+10 | 4.94799e+06 | 5.44419 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1073.39 | 0.687267 | 442.185ms | 2090234 | 30 | 4.88704e+09 | 1.85711e+06 | 2.04309 | 1(Win) |
| glaze | 901.498 | 0.7515 | 555.044ms | 2090234 | 30 | 8.28399e+09 | 2.21121e+06 | 2.43279 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1154.03 | 0.544533 | 1306.06ms | 6661897 | 30 | 2.6961e+10 | 5.50532e+06 | 1.90058 | 1(Win) |
| jsonifier STATISTICAL TIE | 1082.67 | 0.884605 | 1404.46ms | 6661897 | 30 | 8.08401e+10 | 5.86818e+06 | 2.02585 | 2(Tie) |
| glaze STATISTICAL TIE | 1065.8 | 0.570224 | 1457.5ms | 6661897 | 30 | 3.4662e+10 | 5.96102e+06 | 2.05789 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2230.15 | 0.697616 | 675.81ms | 6661897 | 30 | 1.1849e+10 | 2.84881e+06 | 0.98342 | 1(Win) |
| glaze | 1834.49 | 0.660932 | 830.442ms | 6661897 | 30 | 1.57181e+10 | 3.46324e+06 | 1.1955 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1132.91 | 0.557305 | 102.942ms | 500299 | 30 | 1.65264e+08 | 421149 | 1.93586 | 1(Win) |
| jsonifier | 1078.22 | 0.93632 | 108.485ms | 500299 | 30 | 5.15008e+08 | 442509 | 2.03403 | 2(Loss) |
| simdjson (ondemand) | 800.009 | 0.76106 | 144.809ms | 500299 | 30 | 6.18057e+08 | 596396 | 2.74134 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3406.53 | 1.35031 | 34.7743ms | 500299 | 30 | 1.07307e+08 | 140061 | 0.64342 | 1(Win) |
| glaze | 3203.64 | 1.96585 | 39.3804ms | 500299 | 30 | 2.57156e+08 | 148931 | 0.684299 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2027.92 | 0.456326 | 171.973ms | 1439562 | 30 | 2.86306e+08 | 676985 | 1.08129 | 1(Win) |
| glaze | 1781.61 | 0.471339 | 212.627ms | 1439562 | 30 | 3.95753e+08 | 770582 | 1.23087 | 2(Loss) |
| jsonifier | 1616.31 | 0.698517 | 195.562ms | 1439562 | 30 | 1.05605e+09 | 849387 | 1.35676 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5456.44 | 1.0079 | 61.704ms | 1439562 | 30 | 1.92931e+08 | 251606 | 0.401691 | 1(Win) |
| glaze | 3089.32 | 0.823465 | 109.762ms | 1439584 | 30 | 4.01754e+08 | 444400 | 0.709689 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1223.3 | 1.36558 | 12.0005ms | 56369 | 30 | 1.08037e+07 | 43944.8 | 1.79105 | 1(Win) |
| glaze | 938.848 | 0.88999 | 14.4792ms | 56369 | 30 | 7.7908e+06 | 57259.2 | 2.33432 | 2(Loss) |
| simdjson (ondemand) | 803.748 | 0.495154 | 16.7454ms | 56369 | 30 | 3.29035e+06 | 66883.7 | 2.72685 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3936.96 | 0.356214 | 4.19745ms | 56369 | 30 | 70974.2 | 13654.6 | 0.555315 | 1(Win) |
| jsonifier | 3488.59 | 1.4527 | 4.19369ms | 56369 | 30 | 1.50333e+06 | 15409.6 | 0.626846 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1345.8 | 0.721111 | 17.0157ms | 94370 | 30 | 6.97638e+06 | 66873.2 | 1.62875 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1333.44 | 0.636388 | 18.4456ms | 94370 | 30 | 5.53462e+06 | 67493.4 | 1.64386 | 1(Tie) |
| simdjson (ondemand) | 1282.32 | 0.66358 | 16.457ms | 94370 | 30 | 6.50704e+06 | 70184 | 1.70928 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4628.6 | 0.963035 | 5.25925ms | 94370 | 30 | 1.0519e+06 | 19443.9 | 0.472962 | 1(Win) |
| glaze | 3645.54 | 0.665534 | 6.42277ms | 94370 | 30 | 809853 | 24687.2 | 0.600541 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1104.63 | 1.00714 | 11.8272ms | 52708 | 30 | 6.30118e+06 | 45504.9 | 1.98339 | 1(Win) |
| jsonifier | 937.208 | 0.684658 | 13.7444ms | 52708 | 30 | 4.04529e+06 | 53634 | 2.33785 | 2(Loss) |
| glaze | 764.547 | 0.642233 | 15.7429ms | 52708 | 30 | 5.34874e+06 | 65746.5 | 2.86623 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4388.35 | 0.272311 | 3.43969ms | 52708 | 30 | 29187.8 | 11454.5 | 0.497923 | 1(Win) |
| jsonifier | 2973.83 | 1.78512 | 4.17167ms | 52708 | 30 | 2.73136e+06 | 16902.9 | 0.735406 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1468.58 | 0.679693 | 11.8862ms | 70103 | 30 | 2.87229e+06 | 45524 | 1.49193 | 1(Win) |
| glaze | 1008.41 | 0.586966 | 17.5326ms | 70103 | 30 | 4.54305e+06 | 66298 | 2.17337 | 2(Loss) |
| jsonifier | 834.788 | 0.646823 | 20.9382ms | 70103 | 30 | 8.05033e+06 | 80086.7 | 2.62531 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3960.9 | 1.68663 | 4.72389ms | 70103 | 30 | 2.43133e+06 | 16878.8 | 0.551865 | 1(Win) |
| jsonifier | 3449.21 | 0.269098 | 5.52076ms | 70103 | 30 | 81615.9 | 19382.8 | 0.634437 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 799.703 | 1.70624 | 4.00644ms | 11812 | 30 | 1.73297e+06 | 14086.2 | 2.73574 | 1(Win) |
| jsonifier | 758.064 | 0.184801 | 4.23696ms | 11812 | 30 | 22623.8 | 14860 | 2.88708 | 2(Loss) |
| simdjson (ondemand) | 672.741 | 1.12181 | 4.31051ms | 11812 | 30 | 1.05855e+06 | 16744.6 | 3.25244 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3912.52 | 0.148865 | 1.19053ms | 11812 | 30 | 551.109 | 2879.17 | 0.550457 | 1(Win) |
| glaze | 2752.93 | 0.886534 | 1.48451ms | 11812 | 30 | 39479.2 | 4091.93 | 0.788904 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1616.59 | 1.20646 | 5.01257ms | 31235 | 30 | 1.48261e+06 | 18426.4 | 1.35366 | 1(Win) |
| jsonifier | 1432.26 | 0.96831 | 5.64121ms | 31235 | 30 | 1.21672e+06 | 20798 | 1.52852 | 2(Loss) |
| glaze | 1223.25 | 0.842558 | 6.15667ms | 31235 | 30 | 1.26291e+06 | 24351.5 | 1.79014 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5679.39 | 0.441825 | 1.97808ms | 31235 | 30 | 16110.2 | 5244.93 | 0.383551 | 1(Win) |
| glaze | 4852.6 | 0.224605 | 2.01515ms | 31235 | 30 | 5702.87 | 6138.57 | 0.449319 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1984.02 | 0.533494 | 12.8425ms | 108313 | 30 | 2.31446e+06 | 52063.6 | 1.10447 | 1(Win) |
| glaze | 1216.18 | 0.648861 | 20.7117ms | 108313 | 30 | 9.11151e+06 | 84934.2 | 1.80257 | 2(Loss) |
| simdjson (ondemand) | 1116.44 | 0.770769 | 22.6404ms | 108313 | 30 | 1.52568e+07 | 92522.5 | 1.96357 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2840.99 | 1.62164 | 9.40084ms | 108313 | 30 | 1.04292e+07 | 36358.9 | 0.77071 | 1(Tie) |
| glaze STATISTICAL TIE | 2820.96 | 0.509489 | 21.7327ms | 108313 | 32 | 1.11375e+06 | 36617.1 | 0.776469 | 1(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2038.1 | 0.708174 | 25.4795ms | 213963 | 30 | 1.5081e+07 | 100118 | 1.07565 | 1(Win) |
| glaze | 1815.63 | 1.08169 | 28.125ms | 213963 | 30 | 4.43351e+07 | 112386 | 1.20753 | 2(Loss) |
| jsonifier | 1484.79 | 0.273299 | 33.5327ms | 213963 | 30 | 4.23198e+06 | 137427 | 1.4766 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5061.64 | 0.850396 | 10.0042ms | 213963 | 30 | 3.52581e+06 | 40313.2 | 0.432872 | 1(Win) |
| glaze | 3061.41 | 1.20163 | 15.4011ms | 213963 | 30 | 1.92442e+07 | 66652.5 | 0.715813 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 531.09 | 0.777413 | 792.102ms | 1834197 | 30 | 1.96689e+10 | 3.29366e+06 | 4.12957 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 371.665 | 0.610653 | 1132.83ms | 1834197 | 30 | 2.47798e+10 | 4.70646e+06 | 5.9013 | 2(Tie) |
| glaze STATISTICAL TIE | 371.224 | 0.772243 | 1141.8ms | 1834197 | 30 | 3.97236e+10 | 4.71205e+06 | 5.90829 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 640.247 | 0.84209 | 660.273ms | 1834197 | 30 | 1.58795e+10 | 2.73211e+06 | 3.42516 | 1(Win) |
| glaze | 607.969 | 0.851319 | 704.356ms | 1833577 | 30 | 1.79863e+10 | 2.87619e+06 | 3.6074 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1741.58 | 0.682032 | 1292.38ms | 9930848 | 30 | 4.12683e+10 | 5.43805e+06 | 1.2594 | 1(Win) |
| glaze | 1535.85 | 0.658666 | 1472.91ms | 9930848 | 30 | 4.94913e+10 | 6.16649e+06 | 1.42813 | 2(Loss) |
| jsonifier | 1384.89 | 0.703232 | 1642.56ms | 9930848 | 30 | 6.93842e+10 | 6.83866e+06 | 1.58378 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2105.34 | 1.01836 | 1093.07ms | 9930848 | 30 | 6.29581e+10 | 4.49847e+06 | 1.04177 | 1(Win) |
| glaze | 1657.08 | 0.589508 | 1365.47ms | 9930228 | 30 | 3.4051e+10 | 5.71498e+06 | 1.32357 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 930.133 | 0.829048 | 157.305ms | 642697 | 30 | 8.95372e+08 | 658963 | 2.35771 | 1(Win) |
| glaze | 687.136 | 0.524983 | 218.638ms | 642697 | 30 | 6.5787e+08 | 891998 | 3.19145 | 2(Loss) |
| simdjson (ondemand) | 640.46 | 0.609479 | 228.026ms | 642697 | 30 | 1.02063e+09 | 957006 | 3.42392 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 960.988 | 1.09547 | 151.081ms | 642697 | 30 | 1.46453e+09 | 637806 | 2.28171 | 1(Win) |
| glaze | 830.517 | 0.991698 | 174.635ms | 642692 | 30 | 1.6069e+09 | 737997 | 2.64016 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1188.99 | 0.736874 | 235.653ms | 1225964 | 30 | 1.57509e+09 | 983330 | 1.84433 | 1(Win) |
| glaze | 1060.64 | 0.560679 | 262.282ms | 1225964 | 30 | 1.14595e+09 | 1.10232e+06 | 2.06759 | 2(Loss) |
| jsonifier | 976.76 | 0.653763 | 290.644ms | 1225964 | 30 | 1.83714e+09 | 1.19699e+06 | 2.24515 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1637.23 | 0.694471 | 171.429ms | 1225964 | 30 | 7.37846e+08 | 714115 | 1.33924 | 1(Win) |
| glaze | 1289.92 | 1.00981 | 219.435ms | 1225970 | 30 | 2.51326e+09 | 906394 | 1.69996 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 725.782 | 0.673317 | 136.552ms | 409725 | 30 | 3.94215e+08 | 538377 | 3.02182 | 1(Win) |
| simdjson (ondemand) | 597.515 | 1.34579 | 145.077ms | 409725 | 30 | 2.32361e+09 | 653949 | 3.66964 | 2(Loss) |
| glaze | 531.883 | 0.507796 | 182.234ms | 409725 | 30 | 4.17495e+08 | 734642 | 4.12313 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2505.6 | 1.28128 | 39.0006ms | 409725 | 30 | 1.19776e+08 | 155948 | 0.874757 | 1(Win) |
| glaze | 2226.52 | 1.04799 | 43.0275ms | 409725 | 30 | 1.01477e+08 | 175496 | 0.984429 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1161.62 | 1.02196 | 173.84ms | 785750 | 30 | 1.30387e+09 | 645091 | 1.88775 | 1(Win) |
| glaze | 821.917 | 1.06366 | 216.472ms | 785750 | 30 | 2.82124e+09 | 911710 | 2.6681 | 2(Loss) |
| jsonifier | 797.285 | 0.501613 | 234.993ms | 785750 | 30 | 6.66807e+08 | 939876 | 2.75068 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3030.25 | 0.660037 | 58.8066ms | 785750 | 30 | 7.99229e+07 | 247290 | 0.72331 | 1(Win) |
| glaze | 2435.98 | 0.703839 | 73.4793ms | 785750 | 30 | 1.40634e+08 | 307618 | 0.899964 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 800.418 | 0.488051 | 2424.9ms | 8587914 | 30 | 7.48159e+10 | 1.02322e+07 | 2.74032 | 1(Win) |
| jsonifier | 772 | 0.460888 | 2594.45ms | 8587914 | 30 | 7.17221e+10 | 1.06089e+07 | 2.84115 | 2(Loss) |
| glaze | 686.812 | 0.55044 | 2893.04ms | 8587914 | 30 | 1.29253e+11 | 1.19248e+07 | 3.19362 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2517.15 | 0.453592 | 804.185ms | 8588126 | 30 | 6.53476e+09 | 3.25378e+06 | 0.871317 | 1(Win) |
| jsonifier | 1439.77 | 0.639341 | 1368.38ms | 8588126 | 30 | 3.96825e+10 | 5.68862e+06 | 1.52329 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 925.931 | 1.46076 | 2374.5ms | 9804437 | 30 | 6.52783e+11 | 1.00982e+07 | 2.36881 | 1(Win) |
| glaze | 726.551 | 0.394995 | 3074.29ms | 9804437 | 30 | 7.75206e+10 | 1.28694e+07 | 3.01891 | 2(Loss) |
| jsonifier | 675.391 | 0.474028 | 3346.76ms | 9804437 | 30 | 1.292e+11 | 1.38442e+07 | 3.2476 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2474.12 | 0.562001 | 1024.08ms | 11078090 | 30 | 1.72777e+10 | 4.27016e+06 | 0.886465 | 1(Win) |
| jsonifier | 1682.59 | 0.637429 | 1512.32ms | 11078090 | 30 | 4.8057e+10 | 6.27893e+06 | 1.30346 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3665.41 | 1.25722 | 15.7774ms | 264040 | 30 | 2.2379e+07 | 68698.4 | 0.598057 | 1(Win) |
| jsonifier | 3336.89 | 0.684977 | 18.8304ms | 264040 | 30 | 8.01549e+06 | 75462 | 0.656972 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5351.49 | 0.462854 | 18.2388ms | 399947 | 30 | 3.26487e+06 | 71273.5 | 0.409662 | 1(Win) |
| jsonifier | 4068.02 | 0.381484 | 23.3022ms | 399947 | 30 | 3.83807e+06 | 93760.5 | 0.53894 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1128.67 | 0.660963 | 53.3944ms | 264040 | 30 | 6.52354e+07 | 223102 | 1.94287 | 1(Win) |
| jsonifier | 1063.46 | 0.263867 | 57.9037ms | 264040 | 30 | 1.17109e+07 | 236782 | 2.06199 | 2(Loss) |
| glaze | 949.87 | 0.837933 | 63.712ms | 264040 | 30 | 1.4803e+08 | 265098 | 2.30864 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4159.8 | 1.92094 | 14.9557ms | 263923 | 30 | 4.05283e+07 | 60506.9 | 0.526826 | 1(Win) |
| jsonifier | 3293.46 | 1.143 | 19.9785ms | 264040 | 30 | 2.29114e+07 | 76457 | 0.665575 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1764.56 | 0.233196 | 56.304ms | 399947 | 30 | 7.62248e+06 | 216156 | 1.24274 | 1(Win) |
| glaze | 1067.53 | 1.65307 | 99.0725ms | 399947 | 30 | 1.04651e+09 | 357290 | 2.05414 | 2(Loss) |
| jsonifier | 875.092 | 0.41403 | 106.857ms | 399947 | 30 | 9.76973e+07 | 435862 | 2.50603 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4203.92 | 0.796488 | 23.5771ms | 399947 | 30 | 1.56666e+07 | 90729.5 | 0.521524 | 1(Win) |
| glaze | 3833.07 | 0.904192 | 25.2037ms | 399830 | 30 | 2.42717e+07 | 99478.4 | 0.571911 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1667.58 | 0.682909 | 64.9879ms | 466906 | 30 | 9.97548e+07 | 267020 | 1.3149 | 1(Tie) |
| glaze STATISTICAL TIE | 1646.57 | 0.288742 | 64.684ms | 466906 | 30 | 1.82911e+07 | 270427 | 1.33188 | 1(Tie) |
| simdjson (ondemand) | 923.48 | 1.16708 | 140.959ms | 466906 | 30 | 9.50011e+08 | 482172 | 2.37386 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2562.23 | 0.881396 | 62.453ms | 699405 | 30 | 1.57938e+08 | 260322 | 0.855647 | 1(Win) |
| glaze | 2186.39 | 0.678714 | 72.0622ms | 699405 | 30 | 1.28617e+08 | 305071 | 1.00321 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2980.03 | 0.526289 | 51.5467ms | 631514 | 30 | 3.39386e+07 | 202098 | 0.735808 | 1(Win) |
| glaze | 1696.67 | 0.560809 | 88.0347ms | 631514 | 30 | 1.18884e+08 | 354964 | 1.29263 | 2(Loss) |
