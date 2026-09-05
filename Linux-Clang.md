# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 22.1.8 compiler).  

Latest Results: (Sep 05, 2026)
#### Using the following commits:
----
| Jsonifier: [5656577](https://github.com/nihilai-collective/jsonifier/commit/5656577)  
| Glaze: [a5f515c](https://github.com/stephenberry/glaze/commit/a5f515c)  
| Simdjson: [a346223](https://github.com/simdjson/simdjson/commit/a346223)  

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
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 614.869 | 0.0618599 | 2.85122ms | 1811 | 30 | 90.5759 | 2808.9 | 3.97442 | 1(Win) |
| glaze | 484.623 | 0.10979 | 2.22497ms | 1811 | 32 | 489.899 | 3563.81 | 5.05715 | 2(Loss) |
| simdjson (ondemand) | 145.336 | 0.0313896 | 3.08191ms | 1811 | 30 | 417.43 | 11883.5 | 16.983 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 341.732 | 0.131801 | 1.42477ms | 1811 | 30 | 1331.14 | 5053.97 | 7.18984 | 1(Win) |
| glaze | 274.097 | 0.120592 | 1.67669ms | 1798 | 30 | 1707.39 | 6255.83 | 8.98432 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1169.08 | 0.0869613 | 0.983401ms | 3873 | 30 | 226.455 | 3159.4 | 2.09092 | 1(Win) |
| glaze | 965.28 | 0.0811155 | 1.08333ms | 3873 | 30 | 289.013 | 3826.43 | 2.53958 | 2(Loss) |
| simdjson (ondemand) | 253.089 | 0.123159 | 3.685ms | 3873 | 30 | 9691.79 | 14594 | 9.758 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1657.31 | 0.0463081 | 0.746104ms | 3873 | 30 | 31.954 | 2228.67 | 1.45988 | 1(Win) |
| glaze | 1055.84 | 0.390477 | 1.01868ms | 3873 | 30 | 5597.7 | 3498.23 | 2.31782 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1192.05 | 0.0939218 | 0.972675ms | 3862 | 30 | 252.631 | 3089.7 | 2.04818 | 1(Win) |
| glaze | 841.484 | 0.0532879 | 1.22998ms | 3862 | 30 | 163.197 | 4376.9 | 2.91731 | 2(Loss) |
| simdjson (ondemand) | 334.452 | 0.0475435 | 2.95055ms | 3862 | 30 | 822.355 | 11012.3 | 7.37564 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1637.15 | 0.0580599 | 1.41785ms | 3862 | 30 | 51.1828 | 2249.7 | 1.4793 | 1(Win) |
| glaze | 1053.76 | 0.337777 | 2.21973ms | 3862 | 32 | 4460.16 | 3495.19 | 2.32431 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 659.692 | 0.0680851 | 0.495406ms | 905 | 30 | 23.8034 | 1308.3 | 3.65149 | 1(Win) |
| glaze | 485.219 | 0.562398 | 0.572421ms | 905 | 30 | 3002.13 | 1778.73 | 4.99315 | 2(Loss) |
| simdjson (ondemand) | 119.014 | 0.257146 | 1.91718ms | 905 | 30 | 10432.4 | 7251.9 | 20.7004 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 697.961 | 0.085714 | 0.49139ms | 905 | 30 | 33.7023 | 1236.57 | 3.42166 | 1(Win) |
| glaze | 306.864 | 0.140396 | 0.839524ms | 905 | 30 | 467.771 | 2812.57 | 7.96184 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2080.55 | 0.0319953 | 1.30307ms | 9578 | 30 | 59.1954 | 4390.33 | 1.17965 | 1(Win) |
| glaze | 1636.85 | 0.11645 | 1.5392ms | 9578 | 30 | 1266.87 | 5580.4 | 1.50305 | 2(Loss) |
| simdjson (ondemand) | 627.358 | 0.0390567 | 3.69325ms | 9578 | 30 | 970.133 | 14559.9 | 3.93638 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3231.13 | 0.114937 | 0.914476ms | 9578 | 30 | 316.723 | 2826.97 | 0.755279 | 1(Win) |
| glaze | 2229.22 | 0.158239 | 1.16331ms | 9578 | 30 | 1261.22 | 4097.53 | 1.10012 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2911.46 | 0.807546 | 18.5585ms | 233995 | 30 | 1.14933e+07 | 76647.1 | 0.849874 | 1(Win) |
| simdjson (ondemand) | 2799.45 | 0.606647 | 19.4736ms | 233995 | 30 | 7.01557e+06 | 79714 | 0.883804 | 2(Loss) |
| glaze | 1681.84 | 0.457201 | 32.4797ms | 233995 | 30 | 1.10402e+07 | 132685 | 1.47149 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3671.01 | 0.506181 | 21.8974ms | 346753 | 30 | 6.23738e+06 | 90081.3 | 0.674105 | 1(Win) |
| simdjson (ondemand) | 3551.06 | 0.543999 | 22.6599ms | 346753 | 30 | 7.69915e+06 | 93124.3 | 0.696769 | 2(Loss) |
| glaze | 2081.11 | 0.407821 | 38.7321ms | 346753 | 30 | 1.25982e+07 | 158900 | 1.18926 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1309.35 | 0.431603 | 41.6033ms | 233995 | 30 | 1.62328e+07 | 170432 | 1.89031 | 1(Win) |
| glaze | 1107.86 | 0.627761 | 52.7631ms | 233995 | 30 | 4.79683e+07 | 201429 | 2.23423 | 2(Loss) |
| simdjson (ondemand) | 1016.88 | 1.56684 | 54.6455ms | 233995 | 30 | 3.54686e+08 | 219451 | 2.43408 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2398.72 | 0.638715 | 22.7912ms | 233995 | 30 | 1.05923e+07 | 93030.8 | 1.03172 | 1(Win) |
| glaze | 2155.25 | 1.25277 | 24.8452ms | 233995 | 30 | 5.04757e+07 | 103540 | 1.14815 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1641.03 | 0.358948 | 51.2866ms | 346753 | 30 | 1.5696e+07 | 201513 | 1.50826 | 1(Win) |
| jsonifier | 1576.38 | 0.957874 | 51.9733ms | 346753 | 30 | 1.21132e+08 | 209778 | 1.57017 | 2(Loss) |
| simdjson (ondemand) | 1465.05 | 0.959101 | 55.8278ms | 346753 | 30 | 1.406e+08 | 225719 | 1.68956 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2833.13 | 0.779578 | 29.075ms | 346753 | 30 | 2.48397e+07 | 116722 | 0.873485 | 1(Win) |
| glaze | 1932.85 | 0.514552 | 41.3507ms | 346753 | 30 | 2.325e+07 | 171089 | 1.28026 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2840.66 | 0.600441 | 19.0735ms | 233995 | 30 | 6.67477e+06 | 78557.3 | 0.871045 | 1(Win) |
| simdjson (ondemand) | 1998.17 | 0.537058 | 27.0768ms | 233995 | 30 | 1.07923e+07 | 111680 | 1.23862 | 2(Loss) |
| glaze | 1679.95 | 0.600137 | 32.22ms | 233995 | 30 | 1.90653e+07 | 132835 | 1.47327 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3512.31 | 0.516614 | 22.9211ms | 346753 | 30 | 7.09754e+06 | 94151.5 | 0.704552 | 1(Win) |
| simdjson (ondemand) | 2641.72 | 0.502306 | 30.288ms | 346753 | 30 | 1.18611e+07 | 125180 | 0.936867 | 2(Loss) |
| glaze | 2090.66 | 0.468386 | 38.4947ms | 346753 | 30 | 1.64666e+07 | 158175 | 1.18389 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1218.64 | 0.429019 | 44.7645ms | 233995 | 30 | 1.85155e+07 | 183118 | 2.03098 | 1(Win) |
| glaze | 1171.02 | 0.360954 | 47.477ms | 233995 | 30 | 1.41942e+07 | 190565 | 2.1137 | 2(Loss) |
| simdjson (ondemand) | 213.345 | 0.206319 | 251.687ms | 233995 | 30 | 1.39718e+08 | 1.04598e+06 | 11.6039 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2612.2 | 0.564074 | 21.1849ms | 233995 | 30 | 6.96617e+06 | 85428 | 0.94735 | 1(Win) |
| glaze | 2166.71 | 1.4153 | 24.7722ms | 233995 | 30 | 6.37428e+07 | 102992 | 1.14209 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1550.77 | 0.339951 | 53.5049ms | 346753 | 30 | 1.57652e+07 | 213242 | 1.59621 | 1(Win) |
| glaze | 1482.49 | 0.72536 | 56.3811ms | 346753 | 30 | 7.85387e+07 | 223063 | 1.66965 | 2(Loss) |
| simdjson (ondemand) | 312.448 | 0.282687 | 254.123ms | 346753 | 30 | 2.68547e+08 | 1.05838e+06 | 7.92338 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2839.53 | 0.698907 | 28.3272ms | 346753 | 30 | 1.98749e+07 | 116459 | 0.871515 | 1(Win) |
| glaze | 2186.42 | 0.583815 | 36.8009ms | 346753 | 30 | 2.33907e+07 | 151247 | 1.13184 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 723.437 | 0.450351 | 30.4202ms | 94651 | 30 | 9.47269e+06 | 124774 | 3.42112 | 1(Win) |
| simdjson (ondemand) | 711.293 | 0.497836 | 31.0787ms | 94651 | 30 | 1.19742e+07 | 126904 | 3.47954 | 2(Loss) |
| glaze | 693.632 | 0.564226 | 32.2246ms | 94651 | 30 | 1.61741e+07 | 130136 | 3.56827 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3241.28 | 0.988266 | 6.90572ms | 94651 | 30 | 2.27241e+06 | 27848.9 | 0.762759 | 1(Win) |
| glaze | 2894.98 | 0.0503723 | 7.80224ms | 94651 | 30 | 7400.56 | 31180.3 | 0.854186 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 985.585 | 0.477202 | 32.0707ms | 136024 | 30 | 1.1835e+07 | 131620 | 2.51115 | 1(Win) |
| glaze STATISTICAL TIE | 883.128 | 0.900083 | 36.2791ms | 136024 | 30 | 5.24409e+07 | 146890 | 2.80262 | 2(Tie) |
| jsonifier STATISTICAL TIE | 867.117 | 0.825283 | 37.2325ms | 136024 | 30 | 4.57302e+07 | 149602 | 2.85428 | 2(Tie) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3042.81 | 0.747225 | 10.5811ms | 136024 | 30 | 3.04443e+06 | 42632.6 | 0.812936 | 1(Win) |
| glaze | 2688.04 | 0.900722 | 11.7539ms | 136046 | 30 | 5.67028e+06 | 48267.1 | 0.920267 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 430.556 | 0.0568209 | 1112.48ms | 2090234 | 30 | 2.0762e+08 | 4.62983e+06 | 5.74988 | 1(Win) |
| glaze | 363.431 | 0.0970597 | 1318.06ms | 2090234 | 30 | 8.50248e+08 | 5.48496e+06 | 6.81209 | 2(Loss) |
| simdjson (ondemand) | 285.13 | 0.0787617 | 1680.7ms | 2090234 | 30 | 9.09608e+08 | 6.9912e+06 | 8.68282 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 623.663 | 0.0789437 | 767.006ms | 2090234 | 30 | 1.91005e+08 | 3.19628e+06 | 3.9696 | 1(Win) |
| glaze | 599.504 | 0.172797 | 797.098ms | 2090234 | 30 | 9.90373e+08 | 3.32508e+06 | 4.12959 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1146.14 | 0.129811 | 1333.64ms | 6661897 | 30 | 1.55333e+09 | 5.54321e+06 | 2.16004 | 1(Win) |
| glaze | 921.228 | 0.147526 | 1649.84ms | 6661897 | 30 | 3.10542e+09 | 6.89653e+06 | 2.6874 | 2(Loss) |
| simdjson (ondemand) | 853.148 | 0.0712403 | 1786.2ms | 6661897 | 30 | 8.44343e+08 | 7.44686e+06 | 2.90185 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1805.14 | 0.128216 | 844.475ms | 6661897 | 30 | 6.10913e+08 | 3.51955e+06 | 1.37143 | 1(Win) |
| glaze | 1483.15 | 0.214715 | 1020.57ms | 6661897 | 30 | 2.5379e+09 | 4.28365e+06 | 1.66918 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 943.156 | 0.237903 | 121.627ms | 500299 | 30 | 4.34524e+07 | 505878 | 2.62434 | 1(Win) |
| glaze | 821.29 | 0.304584 | 139.528ms | 500299 | 30 | 9.39294e+07 | 580943 | 3.01377 | 2(Loss) |
| simdjson (ondemand) | 492.705 | 0.148281 | 232.824ms | 500299 | 30 | 6.18555e+07 | 968374 | 5.02404 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3231.66 | 0.524789 | 36.6091ms | 500299 | 30 | 1.80094e+07 | 147640 | 0.765759 | 1(Win) |
| glaze | 2202.45 | 0.357526 | 53.1042ms | 500299 | 30 | 1.79963e+07 | 216632 | 1.12373 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2012.55 | 0.31531 | 163.738ms | 1439562 | 30 | 1.38791e+08 | 682155 | 1.22991 | 1(Win) |
| glaze | 1583.7 | 0.103386 | 208.435ms | 1439562 | 30 | 2.40968e+07 | 866875 | 1.56307 | 2(Loss) |
| simdjson (ondemand) | 1278.25 | 0.185128 | 257.994ms | 1439562 | 30 | 1.18603e+08 | 1.07403e+06 | 1.93662 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3897.52 | 0.282677 | 85.0728ms | 1439562 | 30 | 2.97431e+07 | 352243 | 0.635092 | 1(Win) |
| glaze | 3196.72 | 0.271571 | 103.908ms | 1439584 | 30 | 4.08087e+07 | 429470 | 0.774331 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 980.664 | 0.758011 | 13.5688ms | 56369 | 30 | 5.1798e+06 | 54817.6 | 2.52236 | 1(Win) |
| glaze | 813.439 | 0.686803 | 16.6268ms | 56369 | 30 | 6.1804e+06 | 66086.9 | 3.04172 | 2(Loss) |
| simdjson (ondemand) | 695.778 | 1.31234 | 18.9982ms | 56369 | 30 | 3.08425e+07 | 77262.7 | 3.55641 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3464.5 | 0.0581296 | 4.0149ms | 56369 | 30 | 2440.7 | 15516.7 | 0.712872 | 1(Win) |
| glaze | 2492.42 | 1.49847 | 5.36632ms | 56369 | 30 | 3.13369e+06 | 21568.5 | 0.991541 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1290.25 | 0.614635 | 17.3951ms | 94370 | 30 | 5.51408e+06 | 69752.3 | 1.91759 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1158.92 | 0.594478 | 19.3134ms | 94370 | 30 | 6.39371e+06 | 77656.9 | 2.135 | 2(Tie) |
| glaze STATISTICAL TIE | 1143.12 | 0.791627 | 19.2276ms | 94370 | 30 | 1.16532e+07 | 78730.2 | 2.16455 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3305.51 | 0.105035 | 6.86653ms | 94370 | 30 | 24534.8 | 27226.7 | 0.747995 | 1(Win) |
| glaze | 2510.39 | 1.9788 | 8.77139ms | 94370 | 30 | 1.50977e+07 | 35850.3 | 0.985155 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 949.153 | 0.762772 | 13.4456ms | 52708 | 30 | 4.89544e+06 | 52959.1 | 2.60623 | 1(Win) |
| jsonifier | 847.395 | 0.693373 | 14.8181ms | 52708 | 30 | 5.07501e+06 | 59318.6 | 2.91914 | 2(Loss) |
| glaze | 798.028 | 0.748365 | 15.7069ms | 52708 | 30 | 6.66599e+06 | 62988.1 | 3.10034 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3419.68 | 0.130815 | 3.83871ms | 52708 | 30 | 11092.3 | 14699.1 | 0.722167 | 1(Win) |
| glaze | 3201.37 | 0.162516 | 9.22285ms | 52708 | 32 | 20836.3 | 15701.5 | 0.77145 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1166.69 | 1.89771 | 14.0024ms | 70103 | 30 | 3.54769e+07 | 57303.6 | 2.12039 | 1(Win) |
| glaze | 921.505 | 0.721109 | 17.7804ms | 70103 | 30 | 8.21109e+06 | 72550.2 | 2.68508 | 2(Loss) |
| jsonifier | 806.57 | 1.48153 | 20.8946ms | 70103 | 30 | 4.52412e+07 | 82888.5 | 3.0675 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3094.6 | 1.28123 | 5.44538ms | 70103 | 30 | 2.29848e+06 | 21603.9 | 0.798622 | 1(Tie) |
| glaze STATISTICAL TIE | 2983.76 | 1.49549 | 5.61426ms | 70103 | 30 | 3.3685e+06 | 22406.4 | 0.828392 | 1(Tie) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 747.414 | 1.8938 | 3.84285ms | 11812 | 30 | 2.44408e+06 | 15071.7 | 3.30356 | 1(Win) |
| glaze STATISTICAL TIE | 607.94 | 2.40735 | 10.6177ms | 11812 | 32 | 6.36727e+06 | 18529.5 | 4.06401 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 577.914 | 1.66785 | 11.169ms | 11812 | 32 | 3.3821e+06 | 19492.2 | 4.27498 | 2(Tie) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3015.3 | 0.113366 | 2.41674ms | 11812 | 32 | 573.984 | 3735.88 | 0.812913 | 1(Win) |
| glaze | 1805.35 | 0.262487 | 1.68393ms | 11812 | 30 | 8047.47 | 6239.67 | 1.36273 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1708.68 | 0.0785113 | 10.2706ms | 31235 | 32 | 5994.81 | 17433.3 | 1.44593 | 1(Win) |
| simdjson (ondemand) | 1379.15 | 1.36861 | 5.36164ms | 31235 | 30 | 2.62147e+06 | 21598.9 | 1.79205 | 2(Loss) |
| glaze | 1246.78 | 0.43986 | 6.12867ms | 31235 | 30 | 331327 | 23892 | 1.98253 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3495.08 | 0.142076 | 2.26542ms | 31235 | 30 | 4398.76 | 8522.83 | 0.705209 | 1(Win) |
| glaze | 2578.43 | 0.401256 | 2.99725ms | 31235 | 30 | 64466.7 | 11552.8 | 0.956732 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1928.29 | 0.732558 | 13.4397ms | 108313 | 30 | 4.61979e+06 | 53568.4 | 1.28299 | 1(Win) |
| glaze | 1082.02 | 0.568685 | 23.7843ms | 108313 | 30 | 8.84217e+06 | 95465.7 | 2.28716 | 2(Loss) |
| simdjson (ondemand) | 863.049 | 0.502104 | 29.2731ms | 108313 | 30 | 1.08342e+07 | 119687 | 2.86773 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2714.11 | 1.07417 | 9.27397ms | 108313 | 30 | 5.01389e+06 | 38058.6 | 0.911283 | 1(Win) |
| glaze | 1449.58 | 0.562297 | 17.417ms | 108313 | 30 | 4.81651e+06 | 71259 | 1.70697 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1727.33 | 0.403643 | 29.0315ms | 213963 | 30 | 6.82091e+06 | 118131 | 1.43285 | 1(Win) |
| glaze | 1592.29 | 0.500366 | 31.3645ms | 213963 | 30 | 1.23347e+07 | 128149 | 1.55419 | 2(Loss) |
| simdjson (ondemand) | 1552.09 | 0.49895 | 32.2884ms | 213963 | 30 | 1.29086e+07 | 131468 | 1.59464 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2620 | 0.75476 | 18.9108ms | 213963 | 30 | 1.0366e+07 | 77882 | 0.944518 | 1(Win) |
| glaze | 1728.6 | 1.76344 | 27.9705ms | 213963 | 30 | 1.29997e+08 | 118044 | 1.43145 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 497.814 | 0.111301 | 846.01ms | 1834197 | 30 | 4.58854e+08 | 3.51382e+06 | 4.97307 | 1(Win) |
| glaze | 345.268 | 0.105835 | 1210.36ms | 1834197 | 30 | 8.62507e+08 | 5.06629e+06 | 7.17042 | 2(Loss) |
| simdjson (ondemand) | 267.121 | 0.121304 | 1568.62ms | 1834197 | 30 | 1.89298e+09 | 6.54844e+06 | 9.26798 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 389.015 | 0.136982 | 1071.43ms | 1833577 | 30 | 1.13739e+09 | 4.49503e+06 | 6.36392 | 1(Win) |
| jsonifier | 362.97 | 0.112836 | 1152.7ms | 1834197 | 30 | 8.87092e+08 | 4.81921e+06 | 6.82069 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1866.94 | 0.13077 | 1215.08ms | 9930848 | 30 | 1.32023e+09 | 5.07291e+06 | 1.32607 | 1(Win) |
| glaze | 1344.66 | 0.0858107 | 1696.73ms | 9930848 | 30 | 1.09585e+09 | 7.04326e+06 | 1.84115 | 2(Loss) |
| simdjson (ondemand) | 1270.59 | 0.127166 | 1789.1ms | 9930848 | 30 | 2.6954e+09 | 7.45386e+06 | 1.94843 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1525.03 | 0.202926 | 1490.46ms | 9930848 | 30 | 4.76448e+09 | 6.21025e+06 | 1.62335 | 1(Win) |
| glaze | 1370.61 | 0.117393 | 1664.59ms | 9930228 | 30 | 1.97375e+09 | 6.90948e+06 | 1.80626 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 849.747 | 0.219563 | 174.911ms | 642697 | 30 | 7.52443e+07 | 721301 | 2.91321 | 1(Win) |
| glaze | 717.007 | 1.22965 | 202.573ms | 642697 | 30 | 3.31472e+09 | 854836 | 3.45238 | 2(Loss) |
| simdjson (ondemand) | 511.359 | 0.218305 | 287.49ms | 642697 | 30 | 2.05404e+08 | 1.19862e+06 | 4.84109 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 676.286 | 0.162682 | 217.694ms | 642697 | 30 | 6.52153e+07 | 906308 | 3.66047 | 1(Win) |
| glaze | 614.306 | 0.125217 | 239.816ms | 642692 | 30 | 4.68259e+07 | 997742 | 4.02982 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1190.97 | 0.520527 | 233.756ms | 1225964 | 30 | 7.8336e+08 | 981695 | 2.07848 | 1(Win) |
| glaze | 1104.89 | 0.312111 | 251.847ms | 1225964 | 30 | 3.2723e+08 | 1.05818e+06 | 2.24047 | 2(Loss) |
| simdjson (ondemand) | 970.271 | 0.239864 | 289.689ms | 1225964 | 30 | 2.50623e+08 | 1.20499e+06 | 2.55141 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1022.13 | 0.0883274 | 275.014ms | 1225964 | 30 | 3.06235e+07 | 1.14386e+06 | 2.42194 | 1(Win) |
| glaze | 969.514 | 0.0650142 | 289.796ms | 1225970 | 30 | 1.84412e+07 | 1.20594e+06 | 2.55334 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 640.193 | 0.243739 | 147.189ms | 409725 | 30 | 6.63949e+07 | 610354 | 3.86666 | 1(Win) |
| simdjson (ondemand) | 509.122 | 0.18565 | 184.983ms | 409725 | 30 | 6.09048e+07 | 767486 | 4.86222 | 2(Loss) |
| glaze | 406.684 | 0.226324 | 231.534ms | 409725 | 30 | 1.41858e+08 | 960805 | 6.08706 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2039.66 | 0.542727 | 46.8928ms | 409725 | 30 | 3.24305e+07 | 191573 | 1.21339 | 1(Win) |
| glaze | 1656.4 | 0.78179 | 56.7342ms | 409725 | 30 | 1.02037e+08 | 235900 | 1.49422 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 916.022 | 0.137572 | 197.519ms | 785750 | 30 | 3.79958e+07 | 818047 | 2.70249 | 1(Win) |
| jsonifier | 874.554 | 1.29597 | 204.643ms | 785750 | 30 | 3.69917e+09 | 856836 | 2.83051 | 2(Loss) |
| glaze | 681.453 | 0.134861 | 266.293ms | 785750 | 30 | 6.59765e+07 | 1.09964e+06 | 3.63271 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2400.49 | 1.65208 | 75.7746ms | 785750 | 30 | 7.97912e+08 | 312165 | 1.03104 | 1(Win) |
| glaze | 2187.92 | 0.296861 | 83.3405ms | 785750 | 30 | 3.10122e+07 | 342493 | 1.13128 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 686.68 | 0.497326 | 2839.11ms | 8587914 | 30 | 1.05553e+11 | 1.19271e+07 | 3.6053 | 1(Win) |
| glaze | 588.044 | 0.426293 | 3379.32ms | 8587914 | 30 | 1.05753e+11 | 1.39277e+07 | 4.21006 | 2(Loss) |
| simdjson (ondemand) | 549.398 | 0.712864 | 3470.45ms | 8587914 | 30 | 3.38795e+11 | 1.49074e+07 | 4.5062 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2268.29 | 0.52401 | 874.364ms | 8588126 | 30 | 1.07399e+10 | 3.61077e+06 | 1.09133 | 1(Tie) |
| glaze STATISTICAL TIE | 2263.86 | 0.28447 | 875.213ms | 8588126 | 30 | 3.17756e+09 | 3.61784e+06 | 1.09348 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 658.367 | 0.502573 | 3445.24ms | 9804437 | 30 | 1.52837e+11 | 1.42022e+07 | 3.76034 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 615.579 | 0.61209 | 3655.1ms | 9804437 | 30 | 2.59316e+11 | 1.51893e+07 | 4.02176 | 2(Tie) |
| glaze STATISTICAL TIE | 605.742 | 0.677918 | 3712.91ms | 9804437 | 30 | 3.28507e+11 | 1.5436e+07 | 4.08702 | 2(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2312.27 | 0.176451 | 1100.28ms | 11078090 | 30 | 1.94994e+09 | 4.56905e+06 | 1.0706 | 1(Win) |
| jsonifier | 2298.2 | 0.176325 | 1110.36ms | 11078090 | 30 | 1.97109e+09 | 4.59704e+06 | 1.0772 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3008.9 | 0.721104 | 20.3097ms | 264040 | 30 | 1.09255e+07 | 83687.7 | 0.822404 | 1(Win) |
| jsonifier | 2948.47 | 0.623524 | 20.822ms | 264040 | 30 | 8.50694e+06 | 85402.9 | 0.839243 | 2(Loss) |
| glaze | 1160.08 | 0.422879 | 52.6614ms | 264040 | 30 | 2.52765e+07 | 217061 | 2.13365 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3927.99 | 0.749618 | 23.7175ms | 399947 | 30 | 1.58952e+07 | 97102.9 | 0.629996 | 1(Win) |
| jsonifier | 3802.04 | 0.552721 | 24.4037ms | 399947 | 30 | 9.22371e+06 | 100320 | 0.650855 | 2(Loss) |
| glaze | 1653.5 | 0.336864 | 55.9714ms | 399947 | 30 | 1.81145e+07 | 230674 | 1.49704 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1013.91 | 0.405071 | 61.4136ms | 264040 | 30 | 3.03617e+07 | 248354 | 2.44082 | 1(Win) |
| glaze STATISTICAL TIE | 904.083 | 0.541868 | 66.9955ms | 264040 | 30 | 6.83329e+07 | 278523 | 2.7376 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 898.026 | 0.439877 | 67.6771ms | 264040 | 30 | 4.56401e+07 | 280402 | 2.7561 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4083.91 | 0.780997 | 15.8234ms | 264040 | 30 | 6.95677e+06 | 61658.6 | 0.605794 | 1(Win) |
| glaze | 2608.96 | 0.603176 | 23.6827ms | 263923 | 30 | 1.01585e+07 | 96474 | 0.948282 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1270.51 | 0.454608 | 72.5598ms | 399947 | 30 | 5.58783e+07 | 300209 | 1.94805 | 1(Win) |
| glaze | 1110.93 | 0.367691 | 83.2766ms | 399947 | 30 | 4.78101e+07 | 343333 | 2.22768 | 2(Loss) |
| jsonifier | 1074.44 | 0.374954 | 86.7708ms | 399947 | 30 | 5.3152e+07 | 354994 | 2.30365 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3447.57 | 0.512636 | 27.215ms | 399947 | 30 | 9.64981e+06 | 110634 | 0.717771 | 1(Win) |
| glaze | 2720.66 | 0.535884 | 33.9699ms | 399830 | 30 | 1.69226e+07 | 140153 | 0.909425 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1586.75 | 0.344957 | 68.0635ms | 466906 | 30 | 2.81122e+07 | 280622 | 1.55996 | 1(Win) |
| glaze | 1438.41 | 0.392983 | 74.6292ms | 466906 | 30 | 4.43978e+07 | 309561 | 1.72078 | 2(Loss) |
| simdjson (ondemand) | 708.159 | 0.272182 | 151.219ms | 466906 | 30 | 8.78692e+07 | 628780 | 3.49562 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2065.02 | 0.297787 | 77.574ms | 699405 | 30 | 2.77552e+07 | 323002 | 1.19864 | 1(Win) |
| jsonifier | 1862.95 | 0.338965 | 86.0847ms | 699405 | 30 | 4.41858e+07 | 358036 | 1.32868 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2659.53 | 0.391716 | 54.3956ms | 631514 | 30 | 2.36059e+07 | 226453 | 0.930633 | 1(Win) |
| glaze | 1574.53 | 0.219957 | 92.4284ms | 631514 | 30 | 2.12356e+07 | 382502 | 1.57215 | 2(Loss) |
