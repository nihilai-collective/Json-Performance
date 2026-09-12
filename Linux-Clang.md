# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.33.2-microsoft-standard-WSL2 using the Clang 24.0.0 compiler).  

Latest Results: (Sep 11, 2026)
#### Using the following commits:
----
| Jsonifier: [9a2d193](https://github.com/nihilai-collective/jsonifier/commit/9a2d193)  
| Glaze: [565edc9](https://github.com/stephenberry/glaze/commit/565edc9)  
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

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1020.79 | 0.0680077 | 1.64348ms | 1811 | 30 | 39.7195 | 1691.93 | 2.92984 | 1(Win) |
| glaze | 798.107 | 0.0903805 | 0.763888ms | 1811 | 30 | 114.759 | 2164 | 3.76981 | 2(Loss) |
| simdjson (ondemand) | 270.261 | 0.049028 | 3.95885ms | 1811 | 32 | 314.129 | 6390.5 | 11.2013 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 729.875 | 1.75272 | 0.897083ms | 1811 | 30 | 51604.4 | 2366.3 | 4.10768 | 1(Win) |
| glaze | 516.654 | 0.752699 | 1.05374ms | 1798 | 30 | 18721.6 | 3318.87 | 5.82004 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2117.6 | 0.0740499 | 0.770842ms | 3873 | 30 | 50.0471 | 1744.23 | 1.41355 | 1(Win) |
| glaze | 1747.03 | 0.0629459 | 0.752066ms | 3873 | 30 | 53.131 | 2114.2 | 1.72523 | 2(Loss) |
| simdjson (ondemand) | 512.902 | 1.94256 | 1.97711ms | 3873 | 30 | 587076 | 7201.33 | 5.90794 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3085.18 | 0.146788 | 0.628712ms | 3873 | 30 | 92.6483 | 1197.2 | 0.955013 | 1(Win) |
| glaze | 1442.35 | 0.151755 | 0.885837ms | 3873 | 30 | 453.062 | 2560.8 | 2.08448 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2133.48 | 0.138487 | 0.768707ms | 3862 | 30 | 171.471 | 1726.33 | 1.40298 | 1(Win) |
| glaze | 1374.42 | 0.0694792 | 0.937417ms | 3862 | 30 | 103.995 | 2679.73 | 2.19 | 2(Loss) |
| simdjson (ondemand) | 489.879 | 1.63352 | 2.14578ms | 3862 | 30 | 452498 | 7518.37 | 6.17482 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2966.33 | 0.091502 | 0.677235ms | 3862 | 30 | 38.723 | 1241.63 | 0.99376 | 1(Win) |
| glaze | 1427.26 | 0.160238 | 0.938867ms | 3862 | 30 | 512.947 | 2580.53 | 2.10655 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1436.14 | 0.26102 | 0.882054ms | 905 | 32 | 78.7409 | 600.969 | 2.0452 | 1(Win) |
| glaze | 648.994 | 0.143343 | 0.556694ms | 905 | 30 | 109.016 | 1329.87 | 4.61669 | 2(Loss) |
| simdjson (ondemand) | 235.796 | 0.091102 | 1.16465ms | 905 | 30 | 333.582 | 3660.27 | 12.7978 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2075.03 | 0.0700553 | 0.447078ms | 905 | 30 | 2.54713 | 415.933 | 1.39735 | 1(Win) |
| glaze | 370.583 | 0.129657 | 0.810525ms | 905 | 30 | 273.551 | 2328.97 | 8.12004 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3814.86 | 0.10523 | 0.975286ms | 9578 | 30 | 190.455 | 2394.4 | 0.7865 | 1(Win) |
| glaze | 2776.1 | 0.0907248 | 1.09596ms | 9578 | 30 | 267.333 | 3290.33 | 1.08777 | 2(Loss) |
| simdjson (ondemand) | 1626.31 | 0.120111 | 3.56685ms | 9578 | 32 | 1456.32 | 5616.56 | 1.86206 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6469.5 | 0.106218 | 0.722457ms | 9578 | 30 | 67.4724 | 1411.9 | 0.459285 | 1(Win) |
| glaze | 3442.4 | 0.155404 | 0.958573ms | 9578 | 30 | 510.12 | 2653.47 | 0.874967 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 5664.55 | 1.22785 | 9.51447ms | 233995 | 30 | 7.01932e+06 | 39395 | 0.536123 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5632.26 | 1.07016 | 9.89586ms | 233995 | 30 | 5.3935e+06 | 39620.9 | 0.539235 | 1(Tie) |
| glaze | 2357.2 | 0.633697 | 23.0655ms | 233995 | 30 | 1.0797e+07 | 94669.6 | 1.289 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7219.18 | 0.503026 | 11.5277ms | 346753 | 30 | 1.59282e+06 | 45807.1 | 0.420747 | 1(Win) |
| simdjson (ondemand) | 6789.76 | 2.18762 | 11.4322ms | 346753 | 30 | 3.40562e+07 | 48704.1 | 0.446809 | 2(Loss) |
| glaze | 2923.34 | 1.70547 | 28.9461ms | 346753 | 30 | 1.11658e+08 | 113120 | 1.03913 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2236.55 | 2.33642 | 25.0533ms | 233995 | 30 | 1.63035e+08 | 99776.4 | 1.35847 | 1(Win) |
| glaze | 1741.05 | 0.959642 | 30.7858ms | 233995 | 30 | 4.53868e+07 | 128173 | 1.74514 | 2(Loss) |
| simdjson (ondemand) | 1573.37 | 0.644586 | 34.5183ms | 233995 | 30 | 2.50746e+07 | 141833 | 1.93133 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4716.3 | 0.388269 | 12.1674ms | 233995 | 30 | 1.0125e+06 | 47315.7 | 0.643472 | 1(Win) |
| glaze | 4080.97 | 2.21229 | 13.5317ms | 233995 | 30 | 4.39028e+07 | 54681.8 | 0.744078 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2286.82 | 0.751546 | 35.2232ms | 346753 | 30 | 3.5433e+07 | 144606 | 1.32872 | 1(Win) |
| glaze STATISTICAL TIE | 2220.65 | 0.75092 | 36.3027ms | 346753 | 30 | 3.75136e+07 | 148916 | 1.36838 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2193.46 | 0.694319 | 37.0445ms | 346753 | 30 | 3.28716e+07 | 150762 | 1.38511 | 2(Tie) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5526.25 | 0.810486 | 15.0997ms | 346753 | 30 | 7.05653e+06 | 59839.7 | 0.549243 | 1(Win) |
| glaze | 4286.01 | 0.611828 | 19.5229ms | 346753 | 30 | 6.6852e+06 | 77155.5 | 0.708822 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5574.57 | 1.1472 | 10.4043ms | 233995 | 30 | 6.32688e+06 | 40030.9 | 0.544819 | 1(Win) |
| simdjson (ondemand) | 3687.4 | 0.786595 | 36.481ms | 233995 | 32 | 7.25147e+06 | 60518.3 | 0.823619 | 2(Loss) |
| glaze | 2332.33 | 0.687948 | 23.4131ms | 233995 | 30 | 1.29977e+07 | 95679.2 | 1.30276 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7023.82 | 0.517881 | 27.388ms | 346753 | 32 | 1.90241e+06 | 47081.2 | 0.432362 | 1(Win) |
| simdjson (ondemand) | 4935.41 | 0.853125 | 16.7551ms | 346753 | 30 | 9.80258e+06 | 67003.4 | 0.615583 | 2(Loss) |
| glaze | 2969.84 | 0.512881 | 27.0044ms | 346753 | 30 | 9.78426e+06 | 111349 | 1.02305 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2070.18 | 0.63144 | 26.8502ms | 233995 | 30 | 1.38989e+07 | 107795 | 1.46775 | 1(Win) |
| glaze | 1788.56 | 2.12728 | 29.8756ms | 233995 | 30 | 2.11339e+08 | 124768 | 1.69851 | 2(Loss) |
| simdjson (ondemand) | 384.683 | 0.321334 | 140.393ms | 233995 | 30 | 1.04242e+08 | 580101 | 7.89999 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4689.38 | 0.486746 | 11.9192ms | 233995 | 30 | 1.60957e+06 | 47587.4 | 0.647339 | 1(Win) |
| glaze | 4231.38 | 1.5754 | 12.9934ms | 233995 | 30 | 2.07086e+07 | 52738.2 | 0.717731 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2254.16 | 0.463386 | 35.2656ms | 346753 | 30 | 1.38637e+07 | 146702 | 1.34804 | 1(Win) |
| jsonifier | 2154.45 | 1.37049 | 36.7298ms | 346753 | 30 | 1.32751e+08 | 153491 | 1.41016 | 2(Loss) |
| simdjson (ondemand) | 562.106 | 0.456997 | 144.071ms | 346753 | 30 | 2.16846e+08 | 588304 | 5.40652 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5476.89 | 0.882246 | 14.9885ms | 346753 | 30 | 8.51283e+06 | 60379.1 | 0.554436 | 1(Win) |
| glaze | 4154.83 | 0.832877 | 20.0398ms | 346753 | 30 | 1.31831e+07 | 79591.6 | 0.731197 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1362.24 | 0.571421 | 16.8519ms | 94651 | 30 | 4.30106e+06 | 66262.9 | 2.23007 | 1(Win) |
| glaze | 1283.43 | 0.794848 | 17.9665ms | 94651 | 30 | 9.37556e+06 | 70332.1 | 2.36685 | 2(Loss) |
| simdjson (ondemand) | 1205.89 | 1.54068 | 18.4148ms | 94651 | 30 | 3.99007e+07 | 74854.6 | 2.51941 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5646.33 | 0.168056 | 9.54409ms | 94651 | 32 | 23098.1 | 15986.7 | 0.535966 | 1(Win) |
| glaze | 4963.45 | 0.0834138 | 4.99297ms | 94651 | 30 | 6903.68 | 18186.2 | 0.611392 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1653.44 | 0.460177 | 19.4719ms | 136024 | 30 | 3.91046e+06 | 78456.4 | 1.83755 | 1(Win) |
| glaze STATISTICAL TIE | 1607.08 | 0.469514 | 20.473ms | 136024 | 30 | 4.30899e+06 | 80719.6 | 1.8906 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1588.65 | 1.19125 | 20.1305ms | 136024 | 30 | 2.83856e+07 | 81655.7 | 1.91208 | 2(Tie) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6256.58 | 0.358017 | 12.1865ms | 136024 | 32 | 176325 | 20733.8 | 0.483922 | 1(Win) |
| glaze | 4675.76 | 0.830332 | 7.01319ms | 136046 | 30 | 1.59254e+06 | 27748.1 | 0.649277 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 895.159 | 0.231609 | 549.513ms | 2090234 | 30 | 7.98034e+08 | 2.22687e+06 | 3.3944 | 1(Win) |
| glaze | 797.143 | 0.255303 | 609.709ms | 2090234 | 30 | 1.22279e+09 | 2.50068e+06 | 3.81213 | 2(Loss) |
| simdjson (ondemand) | 584.394 | 0.420873 | 818.772ms | 2090234 | 30 | 6.18305e+09 | 3.41106e+06 | 5.19989 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1551.8 | 0.238082 | 308.289ms | 2090234 | 30 | 2.80603e+08 | 1.28457e+06 | 1.95786 | 1(Win) |
| glaze | 920.908 | 0.337108 | 517.561ms | 2090234 | 30 | 1.59741e+09 | 2.16461e+06 | 3.29978 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2105.49 | 0.434291 | 734.006ms | 6661897 | 30 | 5.15194e+09 | 3.01748e+06 | 1.44334 | 1(Win) |
| glaze | 1972.83 | 0.290751 | 782.959ms | 6661897 | 30 | 2.63014e+09 | 3.22038e+06 | 1.54038 | 2(Loss) |
| simdjson (ondemand) | 1738.46 | 0.608789 | 871.392ms | 6661897 | 30 | 1.48498e+10 | 3.65455e+06 | 1.74799 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3158.02 | 0.492196 | 488.096ms | 6661897 | 30 | 2.94146e+09 | 2.01179e+06 | 0.962047 | 1(Win) |
| glaze | 2217.43 | 1.72724 | 687.665ms | 6661897 | 30 | 7.34717e+10 | 2.86515e+06 | 1.37024 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1940.5 | 0.458689 | 61.032ms | 500299 | 30 | 3.81582e+07 | 245875 | 1.56601 | 1(Win) |
| glaze | 1732.74 | 0.789183 | 67.4273ms | 500299 | 30 | 1.41666e+08 | 275356 | 1.75369 | 2(Loss) |
| simdjson (ondemand) | 1023.39 | 0.635167 | 112.963ms | 500299 | 30 | 2.6307e+08 | 466216 | 2.96941 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5372.19 | 1.20672 | 21.6187ms | 500299 | 30 | 3.4458e+07 | 88813.4 | 0.565172 | 1(Tie) |
| glaze STATISTICAL TIE | 5358.18 | 0.919957 | 21.865ms | 500299 | 30 | 2.01317e+07 | 89045.6 | 0.566876 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3147.87 | 0.815381 | 105.511ms | 1439562 | 30 | 3.79376e+08 | 436127 | 0.965322 | 1(Win) |
| glaze | 2869.31 | 0.897139 | 114.038ms | 1439562 | 30 | 5.52772e+08 | 478468 | 1.05892 | 2(Loss) |
| simdjson (ondemand) | 2598.59 | 0.586545 | 301.078ms | 1439562 | 32 | 3.07281e+08 | 528314 | 1.1694 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6656.74 | 0.801941 | 51.0617ms | 1439562 | 30 | 8.20624e+07 | 206238 | 0.456136 | 1(Win) |
| glaze | 5277.41 | 0.916837 | 63.1622ms | 1439584 | 30 | 1.70662e+08 | 260145 | 0.575667 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1881.61 | 1.24289 | 7.5542ms | 56369 | 30 | 3.78275e+06 | 28570 | 1.61352 | 1(Win) |
| jsonifier | 1822.09 | 0.287236 | 7.74702ms | 56369 | 30 | 215447 | 29503.3 | 1.66637 | 2(Loss) |
| simdjson (ondemand) | 1266.64 | 0.693177 | 10.7006ms | 56369 | 30 | 2.59648e+06 | 42441.2 | 2.39801 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6138.66 | 0.289602 | 2.4398ms | 56369 | 30 | 19295.6 | 8757.23 | 0.493277 | 1(Win) |
| jsonifier | 5722.06 | 0.0434146 | 5.82799ms | 56369 | 32 | 532.351 | 9394.81 | 0.52912 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2454.14 | 0.377717 | 9.74933ms | 94370 | 30 | 575606 | 36672 | 1.23686 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 2019.46 | 1.3532 | 25.6942ms | 94370 | 32 | 1.16378e+07 | 44565.6 | 1.50357 | 2(Tie) |
| jsonifier STATISTICAL TIE | 2017.75 | 1.37016 | 11.0563ms | 94370 | 30 | 1.12046e+07 | 44603.2 | 1.50517 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7362.32 | 0.128239 | 3.40621ms | 94370 | 30 | 7372.28 | 12224.2 | 0.410711 | 1(Win) |
| glaze | 5269.82 | 0.120039 | 4.676ms | 94370 | 30 | 12608 | 17078 | 0.57571 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1659.87 | 0.453945 | 7.83566ms | 52708 | 30 | 566937 | 30283.3 | 1.82878 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1609.15 | 2.32632 | 8.01881ms | 52708 | 30 | 1.58424e+07 | 31237.8 | 1.88684 | 1(Tie) |
| glaze | 1476.41 | 1.9265 | 8.63856ms | 52708 | 30 | 1.29061e+07 | 34046.2 | 2.05672 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6467.89 | 0.10812 | 2.20705ms | 52708 | 30 | 2118.16 | 7771.67 | 0.468017 | 1(Win) |
| jsonifier | 6061.65 | 0.488199 | 5.44207ms | 52708 | 32 | 52446.3 | 8292.5 | 0.497458 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2131.82 | 1.71404 | 18.7769ms | 70103 | 32 | 9.24613e+06 | 31360.7 | 1.42398 | 1(Win) |
| jsonifier | 1745.72 | 1.76632 | 10.103ms | 70103 | 30 | 1.37274e+07 | 38296.8 | 1.73978 | 2(Loss) |
| glaze | 1620.21 | 1.71327 | 10.2371ms | 70103 | 30 | 1.49935e+07 | 41263.5 | 1.8745 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6912.05 | 0.207773 | 2.78986ms | 70103 | 30 | 12115.9 | 9672.3 | 0.436544 | 1(Win) |
| glaze | 6264.54 | 0.387478 | 3.04561ms | 70103 | 30 | 51299.2 | 10672 | 0.483789 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1420.65 | 0.276257 | 2.44799ms | 11812 | 30 | 14395.3 | 7929.33 | 2.133 | 1(Win) |
| glaze | 1326.42 | 0.186773 | 5.20402ms | 11812 | 32 | 8051.21 | 8492.62 | 2.28245 | 2(Loss) |
| simdjson (ondemand) | 1114.24 | 0.104143 | 6.08037ms | 11812 | 32 | 3547.34 | 10109.9 | 2.72002 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5576.63 | 0.552851 | 0.815466ms | 11812 | 30 | 3741.45 | 2020 | 0.531773 | 1(Win) |
| glaze | 4367.67 | 0.285337 | 0.959866ms | 11812 | 30 | 1624.74 | 2579.13 | 0.688388 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2748.51 | 0.103417 | 3.04143ms | 31235 | 30 | 3768.74 | 10837.9 | 1.10302 | 1(Win) |
| jsonifier | 2594.32 | 1.8578 | 3.15764ms | 31235 | 30 | 1.36507e+06 | 11482 | 1.16876 | 2(Loss) |
| glaze | 2083.24 | 1.59661 | 3.65336ms | 31235 | 30 | 1.56359e+06 | 14298.9 | 1.4557 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8111.25 | 0.128701 | 1.23744ms | 31235 | 30 | 670.185 | 3672.43 | 0.372031 | 1(Win) |
| glaze | 5868.4 | 0.832863 | 1.49936ms | 31235 | 30 | 53618.1 | 5076 | 0.514941 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3366.15 | 1.31628 | 7.82754ms | 108313 | 30 | 4.89457e+06 | 30686.5 | 0.901912 | 1(Win) |
| glaze | 2240.26 | 1.89279 | 11.4366ms | 108313 | 30 | 2.28503e+07 | 46108.6 | 1.35574 | 2(Loss) |
| simdjson (ondemand) | 1567.61 | 0.625471 | 16.3267ms | 108313 | 30 | 5.09592e+06 | 65893.6 | 1.93766 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6466.88 | 0.238773 | 4.25949ms | 108313 | 30 | 43637.7 | 15973 | 0.46895 | 1(Win) |
| glaze | 4554.97 | 2.38446 | 10.2158ms | 108313 | 32 | 9.35664e+06 | 22677.5 | 0.666334 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2927.13 | 0.443448 | 40.7549ms | 213963 | 32 | 3.05794e+06 | 69710.2 | 1.03786 | 1(Win) |
| glaze STATISTICAL TIE | 2830.3 | 1.17439 | 17.5641ms | 213963 | 30 | 2.15061e+07 | 72095.3 | 1.07334 | 2(Tie) |
| jsonifier STATISTICAL TIE | 2783.69 | 1.17818 | 18.1173ms | 213963 | 30 | 2.23757e+07 | 73302.3 | 1.09118 | 2(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8639.03 | 0.47859 | 28.8438ms | 213963 | 64 | 817812 | 23619.7 | 0.350784 | 1(Win) |
| glaze | 5765.33 | 0.224502 | 8.94738ms | 213963 | 30 | 189405 | 35392.8 | 0.526721 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 903.198 | 0.293737 | 464.503ms | 1834197 | 30 | 9.70879e+08 | 1.9367e+06 | 3.36464 | 1(Win) |
| glaze | 683.581 | 0.287108 | 622.05ms | 1834197 | 30 | 1.61928e+09 | 2.55892e+06 | 4.44559 | 2(Loss) |
| simdjson (ondemand) | 531.742 | 0.834116 | 784.503ms | 1834197 | 30 | 2.25873e+10 | 3.28962e+06 | 5.71493 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1080.05 | 0.292472 | 390.56ms | 1834197 | 30 | 6.73121e+08 | 1.61958e+06 | 2.81339 | 1(Win) |
| glaze | 580.993 | 0.421932 | 724.421ms | 1833577 | 30 | 4.83796e+09 | 3.00973e+06 | 5.23042 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2933.44 | 0.25244 | 783.203ms | 9930848 | 30 | 1.99276e+09 | 3.22856e+06 | 1.03593 | 1(Win) |
| glaze | 2531.92 | 0.680805 | 893.567ms | 9930848 | 30 | 1.94554e+10 | 3.74056e+06 | 1.20016 | 2(Loss) |
| simdjson (ondemand) | 2468.03 | 0.45157 | 924.669ms | 9930848 | 30 | 9.00831e+09 | 3.83739e+06 | 1.2311 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2533.29 | 0.78947 | 908.358ms | 9930848 | 30 | 2.61334e+10 | 3.73853e+06 | 1.19953 | 1(Win) |
| glaze | 1585.73 | 0.566457 | 1429.77ms | 9930228 | 30 | 3.43331e+10 | 5.97213e+06 | 1.91619 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1550.82 | 0.994223 | 95.443ms | 642697 | 30 | 4.63214e+08 | 395227 | 1.95922 | 1(Win) |
| glaze | 1405.65 | 0.601753 | 106.702ms | 642697 | 30 | 2.06545e+08 | 436043 | 2.16172 | 2(Loss) |
| simdjson (ondemand) | 1047.32 | 0.520032 | 140.247ms | 642697 | 30 | 2.77866e+08 | 585230 | 2.9014 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1803.64 | 0.417709 | 81.605ms | 642697 | 30 | 6.04479e+07 | 339826 | 1.6846 | 1(Win) |
| glaze | 919.727 | 0.46005 | 160.813ms | 642692 | 30 | 2.8198e+08 | 666414 | 3.30392 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2176.48 | 0.435855 | 129.807ms | 1225964 | 30 | 1.64457e+08 | 537185 | 1.39626 | 1(Win) |
| glaze | 2129.65 | 0.842356 | 131.243ms | 1225964 | 30 | 6.41579e+08 | 548995 | 1.42666 | 2(Loss) |
| simdjson (ondemand) | 1971.14 | 0.456604 | 143.307ms | 1225964 | 30 | 2.2005e+08 | 593144 | 1.54165 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1860.74 | 0.299005 | 151.29ms | 1225964 | 30 | 1.05892e+08 | 628336 | 1.63258 | 1(Win) |
| glaze | 1617.69 | 0.196496 | 174.804ms | 1225970 | 30 | 6.05059e+07 | 722742 | 1.87749 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1147.08 | 1.6966 | 80.588ms | 409725 | 30 | 1.00201e+09 | 340642 | 2.64912 | 1(Win) |
| simdjson (ondemand) | 945.822 | 0.542996 | 99.4521ms | 409725 | 30 | 1.50966e+08 | 413126 | 3.21283 | 2(Loss) |
| glaze | 900.746 | 1.29435 | 103.75ms | 409725 | 30 | 9.45808e+08 | 433801 | 3.3732 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3251.52 | 0.656748 | 29.2414ms | 409725 | 30 | 1.86866e+07 | 120173 | 0.934346 | 1(Win) |
| glaze | 3063.26 | 1.97417 | 31.9901ms | 409725 | 30 | 1.90242e+08 | 127558 | 0.991637 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1726.15 | 0.387197 | 106.581ms | 785750 | 30 | 8.47614e+07 | 434117 | 1.7604 | 1(Win) |
| jsonifier | 1559.32 | 0.976656 | 116.255ms | 785750 | 30 | 6.6085e+08 | 480562 | 1.94862 | 2(Loss) |
| glaze | 1400.23 | 0.770313 | 129.13ms | 785750 | 30 | 5.09828e+08 | 535161 | 2.1702 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4860.9 | 0.708649 | 37.595ms | 785750 | 30 | 3.5803e+07 | 154159 | 0.624789 | 1(Win) |
| glaze | 3618.18 | 1.36582 | 48.9322ms | 785750 | 30 | 2.40047e+08 | 207107 | 0.839624 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1383.33 | 1.79912 | 1433.3ms | 8587914 | 30 | 3.40382e+11 | 5.92055e+06 | 2.19686 | 1(Win) |
| glaze | 1152.73 | 0.397584 | 1688.79ms | 8587914 | 30 | 2.39389e+10 | 7.10497e+06 | 2.63627 | 2(Loss) |
| simdjson (ondemand) | 1085.81 | 0.230766 | 1801.14ms | 8587914 | 30 | 9.08934e+09 | 7.54283e+06 | 2.79873 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2696.32 | 1.01306 | 681.052ms | 8588126 | 30 | 2.84082e+10 | 3.03758e+06 | 1.12676 | 1(Win) |
| glaze | 2431.75 | 1.04571 | 816.095ms | 8588126 | 30 | 3.72134e+10 | 3.36806e+06 | 1.24938 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1199.99 | 0.286387 | 1868.89ms | 9804437 | 30 | 1.49389e+10 | 7.79193e+06 | 2.53244 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1198.94 | 0.307914 | 1808.79ms | 9804437 | 30 | 1.72994e+10 | 7.79877e+06 | 2.53459 | 1(Tie) |
| simdjson (ondemand) | 1171.5 | 0.406651 | 1902.06ms | 9804437 | 30 | 3.16027e+10 | 7.98141e+06 | 2.594 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2957.07 | 0.737116 | 824.966ms | 11078090 | 30 | 2.08066e+10 | 3.57276e+06 | 1.02734 | 1(Win) |
| glaze | 2578.48 | 0.701237 | 1006.48ms | 11078090 | 30 | 2.47658e+10 | 4.09733e+06 | 1.17835 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6119.51 | 0.203949 | 10.9477ms | 264040 | 30 | 211285 | 41148.4 | 0.496275 | 1(Win) |
| simdjson (ondemand) | 5552.81 | 1.62134 | 11.5624ms | 264040 | 30 | 1.62176e+07 | 45347.9 | 0.546969 | 2(Loss) |
| glaze | 2296.4 | 0.82577 | 27.2903ms | 264040 | 30 | 2.45971e+07 | 109654 | 1.32305 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7705.94 | 1.74937 | 12.6401ms | 399947 | 30 | 2.24926e+07 | 49496.8 | 0.394038 | 1(Win) |
| simdjson (ondemand) | 7117.32 | 1.24875 | 13.7485ms | 399947 | 30 | 1.34352e+07 | 53590.3 | 0.426784 | 2(Loss) |
| glaze | 2940.68 | 0.673219 | 31.2689ms | 399947 | 30 | 2.28741e+07 | 129704 | 1.03327 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1847.87 | 2.45829 | 32.7349ms | 264040 | 30 | 3.36654e+08 | 136269 | 1.64379 | 1(Win) |
| glaze STATISTICAL TIE | 1642.58 | 0.944497 | 37.7983ms | 264040 | 30 | 6.28937e+07 | 153300 | 1.84986 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1625.15 | 0.925112 | 38.2643ms | 264040 | 30 | 6.16398e+07 | 154944 | 1.86983 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6798.64 | 1.33565 | 22.115ms | 264040 | 32 | 7.8312e+06 | 37038 | 0.446372 | 1(Win) |
| glaze | 5929.78 | 0.90917 | 11.0081ms | 263923 | 30 | 4.46774e+06 | 42446.2 | 0.512041 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2299.5 | 0.795119 | 40.1443ms | 399947 | 30 | 5.21822e+07 | 165870 | 1.32145 | 1(Win) |
| glaze STATISTICAL TIE | 2015.2 | 1.10742 | 45.3146ms | 399947 | 30 | 1.318e+08 | 189272 | 1.50781 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1958.3 | 1.56507 | 47.0202ms | 399947 | 30 | 2.7876e+08 | 194770 | 1.55141 | 2(Tie) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7556.93 | 0.989812 | 12.4467ms | 399947 | 30 | 7.48757e+06 | 50472.8 | 0.401815 | 1(Win) |
| glaze | 5373.89 | 2.40825 | 16.6773ms | 399830 | 30 | 8.75984e+07 | 70955.6 | 0.565182 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2804.9 | 1.14366 | 37.8488ms | 466906 | 30 | 9.88871e+07 | 158750 | 1.08319 | 1(Win) |
| jsonifier | 2527.42 | 0.816113 | 42.6552ms | 466906 | 30 | 6.20192e+07 | 176178 | 1.20216 | 2(Loss) |
| simdjson (ondemand) | 1293.17 | 0.759604 | 82.9142ms | 466906 | 30 | 2.05231e+08 | 344329 | 2.34978 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4497.21 | 2.44512 | 36.0344ms | 699405 | 30 | 3.94541e+08 | 148315 | 0.675385 | 1(Win) |
| glaze | 3355.38 | 1.3278 | 46.9505ms | 699405 | 30 | 2.09006e+08 | 198787 | 0.905253 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4510.39 | 0.466432 | 33.5896ms | 631514 | 30 | 1.16368e+07 | 133527 | 0.673527 | 1(Win) |
| glaze | 2685.56 | 2.23153 | 54.474ms | 631514 | 30 | 7.51319e+08 | 224258 | 1.13087 | 2(Loss) |
