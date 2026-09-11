# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 20.1.8 compiler).  

Latest Results: (Sep 11, 2026)
#### Using the following commits:
----
| Jsonifier: [9a2d193](https://github.com/nihilai-collective/jsonifier/commit/9a2d193)  
| Glaze: [565edc9](https://github.com/stephenberry/glaze/commit/565edc9)  
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

> Adaptive sampling on (Intel(R) Xeon(R) 6973P-C-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 804.077 | 0.10314 | 3.00543ms | 1811 | 30 | 147.237 | 2147.93 | 3.03129 | 1(Win) |
| glaze | 773.434 | 0.354151 | 1.07402ms | 1811 | 30 | 1876.24 | 2233.03 | 3.16518 | 2(Loss) |
| simdjson (ondemand) | 208.76 | 0.049394 | 2.68669ms | 1811 | 30 | 500.971 | 8273.17 | 11.8303 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 592.916 | 0.0869479 | 1.65978ms | 1811 | 30 | 192.438 | 2912.9 | 4.1196 | 1(Win) |
| glaze | 339.799 | 0.222312 | 1.76879ms | 1798 | 30 | 3775.56 | 5046.23 | 7.24553 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1754.64 | 0.0450088 | 1.20026ms | 3873 | 30 | 26.9299 | 2105.03 | 1.39134 | 1(Win) |
| glaze | 1532.94 | 0.0632501 | 1.9464ms | 3873 | 32 | 74.3216 | 2409.47 | 1.60171 | 2(Loss) |
| simdjson (ondemand) | 419.862 | 0.0488266 | 2.69316ms | 3873 | 30 | 553.499 | 8797.13 | 5.88961 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2301.54 | 0.0854001 | 1.0736ms | 3873 | 30 | 56.3506 | 1604.83 | 1.0483 | 1(Win) |
| glaze | 1179.64 | 0.549982 | 1.18957ms | 3873 | 30 | 8896.37 | 3131.1 | 2.07464 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1596.95 | 0.0380122 | 1.25832ms | 3862 | 30 | 23.0575 | 2306.33 | 1.52498 | 1(Win) |
| glaze | 1454.56 | 0.0513827 | 1.11804ms | 3862 | 30 | 50.7828 | 2532.1 | 1.68122 | 2(Loss) |
| simdjson (ondemand) | 395.181 | 0.0459587 | 2.84517ms | 3862 | 30 | 550.414 | 9320 | 6.25805 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1989.18 | 0.182916 | 1.12805ms | 3862 | 30 | 344.116 | 1851.57 | 1.2082 | 1(Win) |
| glaze | 1340.61 | 1.34665 | 1.18675ms | 3862 | 30 | 41063.4 | 2747.33 | 1.825 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 969.312 | 0.177339 | 0.88727ms | 905 | 30 | 74.8 | 890.4 | 2.48958 | 1(Win) |
| glaze | 685.924 | 0.127463 | 0.810788ms | 905 | 30 | 77.1678 | 1258.27 | 3.53694 | 2(Loss) |
| simdjson (ondemand) | 179.625 | 0.0355714 | 1.73063ms | 905 | 30 | 87.6368 | 4804.87 | 13.6742 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1264.46 | 0.105993 | 0.816073ms | 905 | 30 | 15.7023 | 682.567 | 1.8937 | 1(Win) |
| glaze | 380.807 | 0.19533 | 1.92606ms | 905 | 32 | 627.157 | 2266.44 | 6.42493 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2580.67 | 0.181658 | 1.3951ms | 9578 | 30 | 1240.26 | 3539.5 | 0.952057 | 1(Win) |
| jsonifier | 2523.01 | 0.0891212 | 1.66356ms | 9578 | 30 | 312.317 | 3620.4 | 0.971323 | 2(Loss) |
| simdjson (ondemand) | 951.301 | 2.45877 | 2.73303ms | 9578 | 30 | 1.67213e+06 | 9601.9 | 2.59777 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4560.15 | 0.0296979 | 1.28548ms | 9578 | 30 | 10.6161 | 2003.07 | 0.535484 | 1(Win) |
| glaze | 2453.81 | 0.171933 | 1.46379ms | 9578 | 30 | 1228.88 | 3722.5 | 0.994146 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5212.74 | 1.32462 | 11.7209ms | 233995 | 30 | 9.6469e+06 | 42809.6 | 0.47524 | 1(Win) |
| jsonifier | 4412.06 | 1.1089 | 13.2642ms | 233995 | 30 | 9.43709e+06 | 50578.4 | 0.561521 | 2(Loss) |
| glaze | 1831.93 | 0.572839 | 29.8108ms | 233995 | 30 | 1.46077e+07 | 121814 | 1.35308 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 6829.1 | 1.1283 | 12.5392ms | 346753 | 30 | 8.9553e+06 | 48423.6 | 0.362813 | 1(Win) |
| jsonifier | 6627.85 | 0.593331 | 13.1124ms | 346753 | 30 | 2.62912e+06 | 49893.9 | 0.373831 | 2(Loss) |
| glaze | 2352.79 | 0.418451 | 34.6828ms | 346753 | 30 | 1.03773e+07 | 140552 | 1.05361 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1808.63 | 1.00507 | 32.5581ms | 233995 | 30 | 4.61347e+07 | 123383 | 1.37051 | 1(Win) |
| glaze | 1472.07 | 0.353588 | 37.6977ms | 233995 | 30 | 8.61932e+06 | 151593 | 1.68398 | 2(Loss) |
| simdjson (ondemand) | 1429.93 | 0.306943 | 38.471ms | 233995 | 30 | 6.88368e+06 | 156060 | 1.73361 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3437.19 | 0.527469 | 17.8469ms | 233995 | 30 | 3.51821e+06 | 64923.6 | 0.720603 | 1(Win) |
| glaze | 2844.43 | 0.764107 | 19.8072ms | 233995 | 30 | 1.07808e+07 | 78453.4 | 0.871257 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2022.3 | 0.301413 | 40.2449ms | 346753 | 30 | 7.28781e+06 | 163522 | 1.2258 | 1(Win) |
| jsonifier | 1892.27 | 0.384319 | 43.9627ms | 346753 | 30 | 1.35326e+07 | 174758 | 1.31009 | 2(Loss) |
| glaze | 1802.76 | 0.403559 | 45.1525ms | 346753 | 30 | 1.64398e+07 | 183435 | 1.37513 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4333.69 | 0.853471 | 19.1782ms | 346753 | 30 | 1.2724e+07 | 76306.6 | 0.571619 | 1(Win) |
| glaze | 3019.71 | 1.40355 | 27.7619ms | 346753 | 30 | 7.08742e+07 | 109510 | 0.820559 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4863.84 | 0.495574 | 12.0242ms | 233995 | 30 | 1.55093e+06 | 45880.5 | 0.509404 | 1(Win) |
| simdjson (ondemand) | 3385.19 | 0.436458 | 17.8853ms | 233995 | 30 | 2.48344e+06 | 65921 | 0.732034 | 2(Loss) |
| glaze | 1845.04 | 0.446149 | 29.789ms | 233995 | 30 | 8.73536e+06 | 120948 | 1.34347 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6645.09 | 0.733105 | 12.7525ms | 346753 | 30 | 3.99294e+06 | 49764.5 | 0.372898 | 1(Win) |
| simdjson (ondemand) | 4531.39 | 0.642279 | 19.7295ms | 346753 | 30 | 6.59094e+06 | 72977.5 | 0.546899 | 2(Loss) |
| glaze | 2255.14 | 0.819597 | 35.4583ms | 346753 | 30 | 4.33325e+07 | 146638 | 1.09922 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1707.15 | 0.483292 | 32.6495ms | 233995 | 30 | 1.19732e+07 | 130718 | 1.45207 | 1(Win) |
| glaze | 1552.38 | 0.48706 | 37.3166ms | 233995 | 30 | 1.47064e+07 | 143751 | 1.59686 | 2(Loss) |
| simdjson (ondemand) | 314.855 | 0.358408 | 172.993ms | 233995 | 30 | 1.93584e+08 | 708755 | 7.87458 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3523.15 | 0.446895 | 16.3431ms | 233995 | 30 | 2.40372e+06 | 63339.6 | 0.702826 | 1(Win) |
| glaze | 3471.08 | 0.463055 | 17.8194ms | 233995 | 30 | 2.6587e+06 | 64289.7 | 0.713891 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1854.34 | 0.319302 | 44.1369ms | 346753 | 30 | 9.7272e+06 | 178333 | 1.33687 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1854.22 | 0.412865 | 47.8034ms | 346753 | 30 | 1.62651e+07 | 178344 | 1.33697 | 1(Tie) |
| simdjson (ondemand) | 465.203 | 0.323568 | 172.708ms | 346753 | 30 | 1.58711e+08 | 710850 | 5.32962 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4320.74 | 0.653404 | 19.7214ms | 346753 | 30 | 7.50253e+06 | 76535.3 | 0.573339 | 1(Win) |
| glaze | 3174.76 | 0.583583 | 25.9857ms | 346753 | 30 | 1.10852e+07 | 104162 | 0.780499 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1049.65 | 0.520235 | 21.3964ms | 94651 | 30 | 6.00456e+06 | 85996.4 | 2.36115 | 1(Win) |
| jsonifier | 989.4 | 0.328727 | 22.7777ms | 94651 | 30 | 2.69836e+06 | 91233.3 | 2.50499 | 2(Loss) |
| glaze | 959.55 | 0.515639 | 24.7556ms | 94651 | 30 | 7.05874e+06 | 94071.4 | 2.58303 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4107.36 | 1.049 | 5.99207ms | 94651 | 30 | 1.59441e+06 | 21976.7 | 0.602579 | 1(Win) |
| jsonifier | 3384.25 | 1.97641 | 7.25143ms | 94651 | 30 | 8.33684e+06 | 26672.5 | 0.729769 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1456.95 | 0.504393 | 23.5625ms | 136024 | 30 | 6.05066e+06 | 89037.2 | 1.70105 | 1(Win) |
| glaze STATISTICAL TIE | 1250.25 | 0.45421 | 26.4971ms | 136024 | 30 | 6.66307e+06 | 103758 | 1.98251 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1245.49 | 0.448961 | 27.875ms | 136024 | 30 | 6.55976e+06 | 104154 | 1.99007 | 2(Tie) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4566.74 | 1.71598 | 7.5465ms | 136024 | 30 | 7.12796e+06 | 28406 | 0.541219 | 1(Win) |
| glaze | 3656.28 | 1.68551 | 9.41296ms | 136046 | 30 | 1.07319e+07 | 35485.1 | 0.677182 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 617.307 | 0.444079 | 723.374ms | 2090234 | 30 | 6.1692e+09 | 3.22919e+06 | 4.01638 | 1(Win) |
| glaze | 594.933 | 0.37204 | 804.577ms | 2090234 | 30 | 4.66181e+09 | 3.35063e+06 | 4.16719 | 2(Loss) |
| simdjson (ondemand) | 454.422 | 0.265322 | 1053.82ms | 2090234 | 30 | 4.06385e+09 | 4.38667e+06 | 5.45582 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1282.09 | 0.629091 | 371.635ms | 2090234 | 30 | 2.87011e+09 | 1.5548e+06 | 1.93325 | 1(Win) |
| glaze | 696.35 | 0.2214 | 710.662ms | 2090234 | 30 | 1.20507e+09 | 2.86264e+06 | 3.56011 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1689.02 | 0.200352 | 903.016ms | 6661897 | 30 | 1.70386e+09 | 3.76152e+06 | 1.46784 | 1(Win) |
| glaze | 1513.44 | 0.11314 | 1011.24ms | 6661897 | 30 | 6.76736e+08 | 4.1979e+06 | 1.63811 | 2(Loss) |
| simdjson (ondemand) | 1356.03 | 0.4431 | 1127.26ms | 6661897 | 30 | 1.29295e+10 | 4.68521e+06 | 1.82833 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2418.12 | 0.236484 | 684.427ms | 6661897 | 30 | 1.15816e+09 | 2.62737e+06 | 1.02518 | 1(Win) |
| glaze | 1497.28 | 0.0395448 | 1026.87ms | 6661897 | 30 | 8.44678e+07 | 4.24321e+06 | 1.65586 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1559.63 | 0.349117 | 74.6185ms | 500299 | 30 | 3.42197e+07 | 305919 | 1.58946 | 1(Win) |
| glaze | 1351.64 | 0.302382 | 87.6553ms | 500299 | 30 | 3.41796e+07 | 352994 | 1.83407 | 2(Loss) |
| simdjson (ondemand) | 937.866 | 0.669674 | 122.825ms | 500299 | 30 | 3.48197e+08 | 508732 | 2.64344 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3788.74 | 0.829298 | 31.475ms | 500299 | 30 | 3.27199e+07 | 125932 | 0.654075 | 1(Win) |
| glaze | 3534.11 | 1.52147 | 32.5483ms | 500299 | 30 | 1.26574e+08 | 135005 | 0.701083 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2649.17 | 0.377637 | 126.166ms | 1439562 | 30 | 1.14898e+08 | 518228 | 0.935764 | 1(Win) |
| simdjson (ondemand) | 2357.86 | 0.574884 | 140.352ms | 1439562 | 30 | 3.36131e+08 | 582255 | 1.05131 | 2(Loss) |
| glaze | 2243.36 | 0.337294 | 149.007ms | 1439562 | 30 | 1.2782e+08 | 611971 | 1.10497 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4822.96 | 1.22931 | 69.7126ms | 1439562 | 30 | 3.6735e+08 | 284654 | 0.513539 | 1(Win) |
| glaze | 3334.54 | 0.518158 | 101.278ms | 1439584 | 30 | 1.36536e+08 | 411719 | 0.74326 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1435.71 | 0.737451 | 10.199ms | 56369 | 30 | 2.28735e+06 | 37443.2 | 1.7253 | 1(Win) |
| glaze | 1265.52 | 0.67087 | 11.9913ms | 56369 | 30 | 2.43636e+06 | 42478.8 | 1.95756 | 2(Loss) |
| simdjson (ondemand) | 1174.3 | 0.731265 | 12.2924ms | 56369 | 30 | 3.36198e+06 | 45778.6 | 2.10986 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4178.7 | 0.101914 | 3.7303ms | 56369 | 30 | 5156.91 | 12864.7 | 0.591045 | 1(Win) |
| jsonifier | 3895.27 | 2.05922 | 3.92809ms | 56369 | 30 | 2.42288e+06 | 13800.8 | 0.632093 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1869.32 | 0.4531 | 12.393ms | 94370 | 30 | 1.42762e+06 | 48145 | 1.32547 | 1(Win) |
| jsonifier STATISTICAL TIE | 1807.68 | 0.631924 | 13.0025ms | 94370 | 30 | 2.96946e+06 | 49786.6 | 1.37065 | 2(Tie) |
| glaze STATISTICAL TIE | 1783.88 | 1.05125 | 14.1036ms | 94370 | 30 | 8.43865e+06 | 50450.8 | 1.38895 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5482.92 | 1.34693 | 4.57042ms | 94370 | 30 | 1.46641e+06 | 16414.3 | 0.450847 | 1(Win) |
| glaze | 3830.53 | 0.357771 | 6.66993ms | 94370 | 30 | 211974 | 23495 | 0.646021 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1489.71 | 1.49319 | 9.02917ms | 52708 | 30 | 7.61562e+06 | 33742.4 | 1.6627 | 1(Win) |
| jsonifier | 1374.7 | 0.926873 | 10.124ms | 52708 | 30 | 3.44589e+06 | 36565.3 | 1.80168 | 2(Loss) |
| glaze | 1137.18 | 0.70586 | 11.6069ms | 52708 | 30 | 2.92045e+06 | 44202.4 | 2.17867 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4699.66 | 2.28672 | 3.25989ms | 52708 | 30 | 1.7946e+06 | 10695.7 | 0.525545 | 1(Win) |
| jsonifier | 4298.37 | 0.598418 | 3.71817ms | 52708 | 30 | 146919 | 11694.3 | 0.573622 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1790.06 | 0.735058 | 10.6453ms | 70103 | 30 | 2.261e+06 | 37348.1 | 1.38381 | 1(Win) |
| jsonifier | 1377.95 | 1.16826 | 14.344ms | 70103 | 30 | 9.63833e+06 | 48517.9 | 1.79803 | 2(Loss) |
| glaze | 1339.76 | 0.471033 | 12.8782ms | 70103 | 30 | 1.65746e+06 | 49901 | 1.84932 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 5127.71 | 1.89425 | 4.15886ms | 70103 | 30 | 1.82988e+06 | 13038.1 | 0.48202 | 1(Win) |
| jsonifier | 4780.52 | 1.63047 | 4.13859ms | 70103 | 30 | 1.5598e+06 | 13985 | 0.517165 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1074.65 | 2.12561 | 3.29475ms | 11812 | 30 | 1.48938e+06 | 10482.3 | 2.30093 | 1(Win) |
| glaze | 851.714 | 1.48718 | 3.85419ms | 11812 | 30 | 1.16067e+06 | 13226 | 2.9033 | 2(Loss) |
| simdjson (ondemand) | 812.078 | 1.66023 | 4.1497ms | 11812 | 30 | 1.59113e+06 | 13871.6 | 3.04459 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3686.84 | 0.251682 | 2.44248ms | 11812 | 32 | 1892.31 | 3055.41 | 0.66552 | 1(Win) |
| glaze | 1781.96 | 0.10782 | 2.08881ms | 11812 | 30 | 1393.7 | 6321.57 | 1.38359 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2331.44 | 0.0955993 | 3.73292ms | 31235 | 30 | 4475.75 | 12776.7 | 1.06088 | 1(Win) |
| jsonifier | 1780.25 | 0.949219 | 5.04062ms | 31235 | 30 | 756788 | 16732.5 | 1.39004 | 2(Loss) |
| glaze | 1492.09 | 1.33091 | 5.46369ms | 31235 | 30 | 2.11793e+06 | 19964 | 1.65874 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6148.32 | 0.0945144 | 3.48955ms | 31235 | 32 | 670.991 | 4844.91 | 0.39591 | 1(Win) |
| glaze | 4307.61 | 0.340802 | 2.27362ms | 31235 | 30 | 16662.3 | 6915.2 | 0.571154 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2645.68 | 2.1736 | 10.4806ms | 108313 | 30 | 2.16058e+07 | 39043.1 | 0.936146 | 1(Win) |
| glaze | 1873.27 | 0.714941 | 15.4681ms | 108313 | 30 | 4.66252e+06 | 55141.6 | 1.32264 | 2(Loss) |
| simdjson (ondemand) | 1537.95 | 0.495493 | 17.2646ms | 108313 | 30 | 3.32255e+06 | 67164.1 | 1.61126 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3821.71 | 2.11649 | 7.72014ms | 108313 | 30 | 9.81746e+06 | 27028.6 | 0.647904 | 1(Win) |
| jsonifier | 3163.97 | 2.27818 | 87.6151ms | 108313 | 128 | 7.08081e+07 | 32647.4 | 0.782358 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2863.12 | 0.717113 | 18.1837ms | 213963 | 30 | 7.836e+06 | 71268.7 | 0.865556 | 1(Win) |
| jsonifier | 2636.63 | 0.586275 | 19.4801ms | 213963 | 30 | 6.17594e+06 | 77390.9 | 0.939983 | 2(Loss) |
| glaze | 2069.03 | 0.516146 | 24.3919ms | 213963 | 30 | 7.77339e+06 | 98621.5 | 1.19785 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5895.95 | 2.31186 | 8.53386ms | 213963 | 30 | 1.9205e+07 | 34608.7 | 0.420152 | 1(Win) |
| glaze | 3839.54 | 1.26575 | 14.2745ms | 213963 | 30 | 1.35748e+07 | 53144.6 | 0.645277 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 706.423 | 0.0938976 | 596.498ms | 1834197 | 30 | 1.62178e+08 | 2.47617e+06 | 3.50965 | 1(Win) |
| glaze | 517.803 | 0.299351 | 809.44ms | 1834197 | 30 | 3.06793e+09 | 3.37817e+06 | 4.78824 | 2(Loss) |
| simdjson (ondemand) | 477.279 | 0.116038 | 884.508ms | 1834197 | 30 | 5.42587e+08 | 3.665e+06 | 5.19487 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 864.07 | 0.122707 | 489.134ms | 1834197 | 30 | 1.85119e+08 | 2.0244e+06 | 2.8689 | 1(Win) |
| glaze | 403.914 | 0.262476 | 1028.53ms | 1833577 | 30 | 3.87364e+09 | 4.32922e+06 | 6.13837 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2262.35 | 0.250701 | 1020.5ms | 9930848 | 30 | 3.30436e+09 | 4.18627e+06 | 1.09596 | 1(Win) |
| simdjson (ondemand) | 2180.23 | 0.901522 | 1018.36ms | 9930848 | 30 | 4.6009e+10 | 4.34395e+06 | 1.13722 | 2(Loss) |
| glaze | 2001.04 | 0.172988 | 1141.7ms | 9930848 | 30 | 2.01102e+09 | 4.73295e+06 | 1.23907 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2043.28 | 0.141944 | 1120.68ms | 9930848 | 30 | 1.29859e+09 | 4.63509e+06 | 1.21337 | 1(Win) |
| glaze | 1503.6 | 0.0559539 | 1521.04ms | 9930228 | 30 | 3.72594e+08 | 6.29836e+06 | 1.64894 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1260.6 | 0.499617 | 117.395ms | 642697 | 30 | 1.77034e+08 | 486217 | 1.96651 | 1(Win) |
| glaze | 1121.79 | 0.319523 | 133.366ms | 642697 | 30 | 9.14361e+07 | 546382 | 2.20988 | 2(Loss) |
| simdjson (ondemand) | 939.629 | 0.248811 | 158.331ms | 642697 | 30 | 7.90245e+07 | 652304 | 2.63814 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1562.14 | 0.428144 | 95.7513ms | 642697 | 30 | 8.46594e+07 | 392362 | 1.58658 | 1(Win) |
| glaze | 1094.19 | 0.270996 | 136.502ms | 642692 | 30 | 6.91303e+07 | 560159 | 2.26524 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1757.72 | 0.552455 | 161.284ms | 1225964 | 30 | 4.05107e+08 | 665162 | 1.4103 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1718.68 | 0.271262 | 164.525ms | 1225964 | 30 | 1.02156e+08 | 680271 | 1.44232 | 2(Tie) |
| glaze STATISTICAL TIE | 1708.7 | 0.199492 | 165.8ms | 1225964 | 30 | 5.58978e+07 | 684244 | 1.45077 | 2(Tie) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1560.06 | 0.334915 | 181.194ms | 1225970 | 30 | 1.89002e+08 | 749441 | 1.58895 | 1(Win) |
| jsonifier | 1424.45 | 0.239479 | 200.255ms | 1225964 | 30 | 1.1591e+08 | 820789 | 1.74026 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 907.276 | 0.42966 | 106.669ms | 409725 | 30 | 1.02725e+08 | 430678 | 2.73233 | 1(Win) |
| simdjson (ondemand) | 872.642 | 0.440745 | 108.544ms | 409725 | 30 | 1.16845e+08 | 447772 | 2.84046 | 2(Loss) |
| glaze | 671.068 | 0.27924 | 142.611ms | 409725 | 30 | 7.93103e+07 | 582272 | 3.69427 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2630.35 | 0.545306 | 37.783ms | 409725 | 30 | 1.96862e+07 | 148552 | 0.942175 | 1(Win) |
| glaze | 2399.77 | 2.02983 | 91.8976ms | 409725 | 32 | 3.49555e+08 | 162826 | 1.03255 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1600.03 | 0.35231 | 113.862ms | 785750 | 30 | 8.16738e+07 | 468334 | 1.54913 | 1(Win) |
| jsonifier | 1299.21 | 0.472864 | 139.937ms | 785750 | 30 | 2.23154e+08 | 576774 | 1.90819 | 2(Loss) |
| glaze | 1069.33 | 0.245891 | 170.709ms | 785750 | 30 | 8.90738e+07 | 700764 | 2.31819 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3859.39 | 0.722584 | 47.9357ms | 785750 | 30 | 5.90514e+07 | 194163 | 0.641974 | 1(Win) |
| glaze | 2811.95 | 1.2754 | 64.9598ms | 785750 | 30 | 3.46552e+08 | 266488 | 0.881356 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1025.69 | 0.0695169 | 1938.4ms | 8587914 | 30 | 9.24364e+08 | 7.98491e+06 | 2.41731 | 1(Win) |
| simdjson (ondemand) | 950.56 | 0.193393 | 2252.42ms | 8587914 | 30 | 8.32951e+09 | 8.61605e+06 | 2.60838 | 2(Loss) |
| glaze | 878.765 | 0.321515 | 2251.55ms | 8587914 | 30 | 2.69372e+10 | 9.31998e+06 | 2.82151 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2775.12 | 0.161415 | 716.862ms | 8588126 | 30 | 6.8084e+08 | 2.95133e+06 | 0.893381 | 1(Win) |
| glaze | 2682.25 | 0.282052 | 738.546ms | 8588126 | 30 | 2.22526e+09 | 3.05351e+06 | 0.92436 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1099.25 | 0.435608 | 2046.43ms | 9804437 | 30 | 4.11873e+10 | 8.50599e+06 | 2.25556 | 1(Win) |
| jsonifier | 958.513 | 0.893635 | 2314.66ms | 9804437 | 30 | 2.27977e+11 | 9.75494e+06 | 2.58678 | 2(Loss) |
| glaze | 909.822 | 0.195655 | 2473.54ms | 9804437 | 30 | 1.21292e+10 | 1.0277e+07 | 2.72521 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3085.5 | 0.539281 | 821.218ms | 11078090 | 30 | 1.0229e+10 | 3.42405e+06 | 0.803521 | 1(Win) |
| glaze | 2916.55 | 0.331908 | 875.766ms | 11078090 | 30 | 4.33659e+09 | 3.6224e+06 | 0.850055 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5910.31 | 1.15991 | 12.0929ms | 264040 | 30 | 7.32636e+06 | 42604.9 | 0.419169 | 1(Win) |
| jsonifier | 5518.41 | 1.02783 | 11.8741ms | 264040 | 30 | 6.59891e+06 | 45630.5 | 0.448945 | 2(Loss) |
| glaze | 1864.14 | 0.497607 | 33.0983ms | 264040 | 30 | 1.35543e+07 | 135080 | 1.32972 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 7730.07 | 0.663447 | 12.8909ms | 399947 | 30 | 3.21493e+06 | 49342.3 | 0.320529 | 1(Win) |
| jsonifier | 7073.39 | 1.22422 | 13.919ms | 399947 | 30 | 1.30734e+07 | 53923.1 | 0.350294 | 2(Loss) |
| glaze | 2444.45 | 0.299239 | 38.3054ms | 399947 | 30 | 6.54036e+06 | 156035 | 1.0141 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1521.68 | 0.400275 | 41.8573ms | 264040 | 30 | 1.31623e+07 | 165480 | 1.62897 | 1(Win) |
| jsonifier | 1465.14 | 0.544709 | 44.4064ms | 264040 | 30 | 2.62924e+07 | 171866 | 1.69174 | 2(Loss) |
| glaze | 1345.93 | 0.303146 | 49.6242ms | 264040 | 30 | 9.64977e+06 | 187088 | 1.84173 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5951.94 | 0.688296 | 11.3926ms | 264040 | 30 | 2.54387e+06 | 42306.9 | 0.416183 | 1(Win) |
| glaze | 4547.25 | 1.54387 | 34.6755ms | 263923 | 32 | 2.33683e+07 | 55351.4 | 0.544784 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2186.74 | 0.396225 | 43.1592ms | 399947 | 30 | 1.4329e+07 | 174424 | 1.13358 | 1(Win) |
| glaze | 1751.08 | 0.348432 | 53.5712ms | 399947 | 30 | 1.72804e+07 | 217820 | 1.41563 | 2(Loss) |
| jsonifier | 1473.71 | 0.431487 | 64.4767ms | 399947 | 30 | 3.74143e+07 | 258816 | 1.68195 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6617.86 | 0.960964 | 14.8358ms | 399947 | 30 | 9.20249e+06 | 57634.8 | 0.374302 | 1(Win) |
| glaze | 3828.59 | 1.23657 | 26.4254ms | 399830 | 30 | 4.55019e+07 | 99594.9 | 0.647295 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2371.57 | 0.852996 | 46.0348ms | 466906 | 30 | 7.6949e+07 | 187756 | 1.04522 | 1(Win) |
| glaze | 2272 | 0.254069 | 48.8383ms | 466906 | 30 | 7.43817e+06 | 195984 | 1.09116 | 2(Loss) |
| simdjson (ondemand) | 1111.83 | 0.408851 | 97.9187ms | 466906 | 30 | 8.04328e+07 | 400489 | 2.22895 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3280.57 | 0.645955 | 50.285ms | 699405 | 30 | 5.17468e+07 | 203320 | 0.755288 | 1(Win) |
| glaze | 3014.06 | 0.247702 | 55.3891ms | 699405 | 30 | 9.01436e+06 | 221298 | 0.822528 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3660.87 | 0.531384 | 40.5999ms | 631514 | 30 | 2.29264e+07 | 164513 | 0.677086 | 1(Win) |
| glaze | 2258.73 | 0.251876 | 66.2496ms | 631514 | 30 | 1.35311e+07 | 266636 | 1.09757 | 2(Loss) |
