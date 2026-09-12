# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 12, 2026)
#### Using the following commits:
----
| Jsonifier: [8fed030](https://github.com/nihilai-collective/jsonifier/commit/8fed030)  
| Glaze: [52fb059](https://github.com/stephenberry/glaze/commit/52fb059)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 831.231 | 0.0556068 | 2.35207ms | 1811 | 30 | 40.0471 | 2077.77 | 2.93687 | 1(Win) |
| glaze | 575.554 | 0.094117 | 0.86504ms | 1811 | 30 | 239.289 | 3000.77 | 4.2582 | 2(Loss) |
| simdjson (ondemand) | 112.26 | 1.24826 | 3.87592ms | 1811 | 30 | 1.1064e+06 | 15384.8 | 22.0098 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 541.927 | 0.146075 | 0.937258ms | 1811 | 30 | 650.171 | 3186.97 | 4.52901 | 1(Win) |
| glaze | 349.322 | 0.659679 | 1.33116ms | 1798 | 30 | 31456.8 | 4908.67 | 7.04227 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1391.08 | 0.0528969 | 1.71881ms | 3873 | 32 | 63.125 | 2655.19 | 1.76051 | 1(Win) |
| glaze | 1230.46 | 0.0992921 | 0.862858ms | 3873 | 30 | 266.51 | 3001.8 | 1.99156 | 2(Loss) |
| simdjson (ondemand) | 268.234 | 1.43191 | 3.45065ms | 3873 | 30 | 1.16632e+06 | 13770 | 9.21129 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2073.49 | 0.0713823 | 0.619667ms | 3873 | 30 | 48.5057 | 1781.33 | 1.17143 | 1(Win) |
| glaze | 1017.5 | 0.438543 | 1.03388ms | 3873 | 30 | 7602.82 | 3630.07 | 2.41136 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1431.4 | 0.0792968 | 0.822327ms | 3862 | 30 | 124.892 | 2573.07 | 1.71022 | 1(Win) |
| glaze | 1106.74 | 0.139006 | 0.942826ms | 3862 | 30 | 641.982 | 3327.87 | 2.21626 | 2(Loss) |
| simdjson (ondemand) | 258.551 | 1.54848 | 3.54322ms | 3862 | 30 | 1.4597e+06 | 14245.1 | 9.55532 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2045.1 | 0.0763266 | 0.610894ms | 3862 | 30 | 56.6851 | 1800.93 | 1.18823 | 1(Win) |
| glaze | 1028.89 | 1.93355 | 4.85716ms | 3862 | 64 | 306603 | 3579.67 | 2.38543 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1086.31 | 0.126407 | 0.348526ms | 905 | 30 | 30.2586 | 794.5 | 2.19396 | 1(Win) |
| glaze | 603.423 | 1.49637 | 0.464408ms | 905 | 30 | 13742.1 | 1430.3 | 4.01731 | 2(Loss) |
| simdjson (ondemand) | 79.9168 | 0.0431542 | 2.74068ms | 905 | 30 | 651.609 | 10799.7 | 30.8945 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 945.629 | 0.954619 | 0.406201ms | 905 | 30 | 2277.39 | 912.7 | 2.53761 | 1(Win) |
| glaze | 343.076 | 0.564545 | 0.725895ms | 905 | 30 | 6051.11 | 2515.7 | 7.13624 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1822.55 | 0.099266 | 3.02871ms | 9578 | 32 | 792.028 | 5011.81 | 1.35032 | 1(Win) |
| jsonifier | 1391.07 | 0.0304546 | 1.79472ms | 9578 | 30 | 119.972 | 6566.4 | 1.76771 | 2(Loss) |
| simdjson (ondemand) | 752.706 | 0.128513 | 3.08262ms | 9578 | 30 | 7296.55 | 12135.3 | 3.28126 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3725.24 | 0.193426 | 0.794376ms | 9578 | 30 | 674.828 | 2452 | 0.656637 | 1(Win) |
| glaze | 2185.13 | 0.390714 | 1.16188ms | 9578 | 30 | 8002.65 | 4180.2 | 1.12491 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 4037.29 | 0.812264 | 32.8093ms | 233995 | 32 | 6.45026e+06 | 55273.4 | 0.612929 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 4004.15 | 0.515749 | 13.6145ms | 233995 | 30 | 2.4785e+06 | 55730.9 | 0.617909 | 1(Tie) |
| glaze | 1742.81 | 0.517891 | 31.1757ms | 233995 | 30 | 1.3192e+07 | 128043 | 1.42022 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5198.61 | 0.41666 | 15.632ms | 346753 | 30 | 2.10743e+06 | 63611.2 | 0.475951 | 1(Win) |
| jsonifier | 5048.98 | 0.345641 | 16.0773ms | 346753 | 30 | 1.53747e+06 | 65496.3 | 0.490108 | 2(Loss) |
| glaze | 2190.71 | 0.504514 | 36.5703ms | 346753 | 30 | 1.73996e+07 | 150951 | 1.1298 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1547.55 | 0.538391 | 37.0547ms | 233995 | 30 | 1.80817e+07 | 144199 | 1.5995 | 1(Win) |
| simdjson (ondemand) | 1508.1 | 0.525683 | 36.4604ms | 233995 | 30 | 1.81519e+07 | 147971 | 1.64133 | 2(Loss) |
| jsonifier | 1236.82 | 1.00491 | 43.0836ms | 233995 | 30 | 9.86222e+07 | 180426 | 2.00144 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3066.86 | 0.490849 | 17.9923ms | 233995 | 30 | 3.82685e+06 | 72763.3 | 0.806869 | 1(Win) |
| glaze | 2773.63 | 0.514363 | 19.5913ms | 233995 | 30 | 5.13782e+06 | 80456 | 0.892197 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1882.63 | 1.79182 | 39.9873ms | 346753 | 30 | 2.97181e+08 | 175653 | 1.31473 | 1(Win) |
| glaze | 1615.86 | 0.834403 | 48.8646ms | 346753 | 30 | 8.74797e+07 | 204653 | 1.53188 | 2(Loss) |
| jsonifier | 1229.36 | 0.425881 | 65.8986ms | 346753 | 30 | 3.93711e+07 | 268992 | 2.01358 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3282.72 | 0.627614 | 24.5839ms | 346753 | 30 | 1.19916e+07 | 100736 | 0.75392 | 1(Win) |
| glaze | 2685.8 | 0.426077 | 30.0535ms | 346753 | 30 | 8.25637e+06 | 123125 | 0.92136 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3909.41 | 0.988837 | 13.9247ms | 233995 | 30 | 9.55789e+06 | 57081.5 | 0.632965 | 1(Win) |
| simdjson (ondemand) | 2528.48 | 0.492553 | 21.4712ms | 233995 | 30 | 5.66921e+06 | 88256.6 | 0.978854 | 2(Loss) |
| glaze | 1735.36 | 0.530967 | 31.2191ms | 233995 | 30 | 1.39859e+07 | 128593 | 1.42636 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4917.55 | 0.791286 | 16.3276ms | 346753 | 30 | 8.49439e+06 | 67246.8 | 0.503067 | 1(Win) |
| simdjson (ondemand) | 3375.83 | 0.717407 | 23.7574ms | 346753 | 30 | 1.4816e+07 | 97958 | 0.733057 | 2(Loss) |
| glaze | 2182.17 | 0.494096 | 37.0195ms | 346753 | 30 | 1.68193e+07 | 151542 | 1.13418 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1699.51 | 0.469326 | 33.7753ms | 233995 | 30 | 1.13929e+07 | 131305 | 1.45639 | 1(Win) |
| jsonifier | 1228.47 | 0.286552 | 44.2827ms | 233995 | 30 | 8.1286e+06 | 181654 | 2.01501 | 2(Loss) |
| simdjson (ondemand) | 234.812 | 0.132765 | 228.988ms | 233995 | 30 | 4.776e+07 | 950356 | 10.5436 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3199.02 | 1.00886 | 17.0229ms | 233995 | 30 | 1.48581e+07 | 69757.2 | 0.773491 | 1(Win) |
| glaze | 2768.65 | 0.717607 | 19.6274ms | 233995 | 30 | 1.00362e+07 | 80600.6 | 0.89383 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1736.57 | 0.645352 | 47.6771ms | 346753 | 30 | 4.53077e+07 | 190427 | 1.42538 | 1(Win) |
| jsonifier | 1118.12 | 0.33708 | 72.0255ms | 346753 | 30 | 2.98163e+07 | 295756 | 2.21394 | 2(Loss) |
| simdjson (ondemand) | 342.214 | 0.0950709 | 232.41ms | 346753 | 30 | 2.53198e+07 | 966322 | 7.23446 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3833.58 | 0.817437 | 20.9702ms | 346753 | 30 | 1.49163e+07 | 86261.4 | 0.645449 | 1(Win) |
| glaze | 2824.38 | 0.644921 | 28.9252ms | 346753 | 30 | 1.71053e+07 | 117084 | 0.876209 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 947.471 | 0.798506 | 23.2566ms | 94651 | 30 | 1.73619e+07 | 95270.7 | 2.61195 | 1(Tie) |
| glaze STATISTICAL TIE | 931.138 | 0.412374 | 24.7442ms | 94651 | 30 | 4.79431e+06 | 96941.8 | 2.65779 | 1(Tie) |
| jsonifier | 574.53 | 0.502089 | 38.2725ms | 94651 | 30 | 1.86685e+07 | 157113 | 4.3083 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4075.57 | 2.01412 | 5.48697ms | 94651 | 30 | 5.96992e+06 | 22148.1 | 0.606687 | 1(Win) |
| glaze | 3709.77 | 2.29945 | 5.96584ms | 94651 | 30 | 9.39131e+06 | 24332 | 0.666213 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1305.08 | 0.900922 | 23.8963ms | 136024 | 30 | 2.40576e+07 | 99398.1 | 1.89628 | 1(Win) |
| glaze | 1093.22 | 0.638605 | 28.5207ms | 136024 | 30 | 1.72268e+07 | 118661 | 2.26415 | 2(Loss) |
| jsonifier | 724.131 | 0.409285 | 43.6405ms | 136024 | 30 | 1.61276e+07 | 179142 | 3.41815 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4646.74 | 0.0586423 | 6.96894ms | 136024 | 30 | 8040.41 | 27916.9 | 0.532256 | 1(Win) |
| glaze | 3900.59 | 0.735725 | 8.40845ms | 136046 | 30 | 1.79665e+06 | 33262.5 | 0.634115 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 536.479 | 0.0423125 | 900.033ms | 2090234 | 30 | 7.41553e+07 | 3.71571e+06 | 4.61484 | 1(Win) |
| simdjson (ondemand) | 456.764 | 0.0439086 | 1051.93ms | 2090234 | 30 | 1.10161e+08 | 4.36419e+06 | 5.42027 | 2(Loss) |
| glaze | 427.651 | 0.056987 | 1119.47ms | 2090234 | 30 | 2.11682e+08 | 4.66129e+06 | 5.78927 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1142.81 | 0.110528 | 419.583ms | 2090234 | 30 | 1.11508e+08 | 1.7443e+06 | 2.16635 | 1(Win) |
| glaze | 939.135 | 0.257223 | 510.628ms | 2090234 | 30 | 8.94284e+08 | 2.12259e+06 | 2.6362 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1337.81 | 0.0640326 | 1138.91ms | 6661897 | 30 | 2.77416e+08 | 4.74902e+06 | 1.85063 | 1(Win) |
| jsonifier | 1239.15 | 0.0615461 | 1242.45ms | 6661897 | 30 | 2.98723e+08 | 5.12712e+06 | 1.99798 | 2(Loss) |
| glaze | 1116.76 | 0.0562148 | 1368.45ms | 6661897 | 30 | 3.06831e+08 | 5.68903e+06 | 2.21695 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2877.78 | 0.174421 | 532.929ms | 6661897 | 30 | 4.44836e+08 | 2.2077e+06 | 0.86029 | 1(Win) |
| glaze | 2219.94 | 0.209574 | 689.827ms | 6661897 | 30 | 1.07922e+09 | 2.86191e+06 | 1.1152 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1143.69 | 0.23598 | 100.677ms | 500299 | 30 | 2.90745e+07 | 417177 | 2.16435 | 1(Win) |
| jsonifier | 1052.24 | 0.296451 | 109.76ms | 500299 | 30 | 5.4207e+07 | 453435 | 2.35245 | 2(Loss) |
| simdjson (ondemand) | 881.155 | 0.329454 | 129.762ms | 500299 | 30 | 9.54698e+07 | 541474 | 2.80934 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3337.43 | 0.567086 | 34.8021ms | 500299 | 30 | 1.97176e+07 | 142961 | 0.741616 | 1(Win) |
| glaze | 2740.36 | 0.522986 | 42.3375ms | 500299 | 30 | 2.4874e+07 | 174109 | 0.903159 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2274.41 | 0.234305 | 145.144ms | 1439562 | 30 | 6.0008e+07 | 603618 | 1.0884 | 1(Win) |
| glaze | 2005.67 | 0.351691 | 164.344ms | 1439562 | 30 | 1.73855e+08 | 684497 | 1.23422 | 2(Loss) |
| jsonifier | 1746.71 | 1.17387 | 187.268ms | 1439562 | 30 | 2.55378e+09 | 785977 | 1.41721 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5225.04 | 0.388973 | 63.5839ms | 1439562 | 30 | 3.1336e+07 | 262749 | 0.473752 | 1(Win) |
| glaze | 3418.88 | 0.264527 | 96.8126ms | 1439584 | 30 | 3.38509e+07 | 401563 | 0.724058 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1094.55 | 0.71859 | 12.266ms | 56369 | 30 | 3.73676e+06 | 49114.1 | 2.26043 | 1(Win) |
| simdjson (ondemand) | 1055.01 | 1.23481 | 12.7531ms | 56369 | 30 | 1.18765e+07 | 50954.8 | 2.34538 | 2(Loss) |
| jsonifier | 883.541 | 0.814918 | 15.0345ms | 56369 | 30 | 7.37524e+06 | 60843.4 | 2.8008 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3905.66 | 1.60616 | 3.51454ms | 56369 | 30 | 1.4662e+06 | 13764 | 0.632538 | 1(Win) |
| glaze | 3618.99 | 0.298351 | 3.80072ms | 56369 | 30 | 58922.8 | 14854.3 | 0.682767 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1644.33 | 0.728027 | 13.4941ms | 94370 | 30 | 4.76331e+06 | 54732.6 | 1.50483 | 1(Win) |
| glaze | 1475.41 | 0.805584 | 15.0959ms | 94370 | 30 | 7.24407e+06 | 60998.6 | 1.67712 | 2(Loss) |
| jsonifier | 1046.04 | 0.403928 | 21.3014ms | 94370 | 30 | 3.62327e+06 | 86037 | 2.3656 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4702.28 | 0.140349 | 11.1469ms | 94370 | 32 | 23089.6 | 19139.3 | 0.525701 | 1(Win) |
| glaze | 3451.44 | 1.09235 | 6.51953ms | 94370 | 30 | 2.43395e+06 | 26075.6 | 0.716522 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1284.71 | 0.772032 | 9.80085ms | 52708 | 30 | 2.73737e+06 | 39126.5 | 1.92522 | 1(Win) |
| glaze | 993.708 | 0.804628 | 12.605ms | 52708 | 30 | 4.96989e+06 | 50584.5 | 2.4897 | 2(Loss) |
| jsonifier | 944.9 | 0.613444 | 13.5297ms | 52708 | 30 | 3.19487e+06 | 53197.4 | 2.61842 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4307.82 | 0.253521 | 3.06309ms | 52708 | 30 | 26253.6 | 11668.6 | 0.573097 | 1(Win) |
| jsonifier | 3799.71 | 2.06243 | 3.37735ms | 52708 | 30 | 2.23322e+06 | 13229 | 0.650066 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1634.13 | 1.05111 | 10.2445ms | 70103 | 30 | 5.54772e+06 | 40911.9 | 1.5137 | 1(Win) |
| glaze | 1157.71 | 1.0974 | 14.3774ms | 70103 | 30 | 1.20483e+07 | 57747.8 | 2.1373 | 2(Loss) |
| jsonifier | 894.523 | 1.25065 | 18.8293ms | 70103 | 30 | 2.6211e+07 | 74738.6 | 2.76612 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4339.23 | 1.35592 | 3.92791ms | 70103 | 30 | 1.30929e+06 | 15407.2 | 0.569453 | 1(Win) |
| glaze | 3907.77 | 0.411824 | 4.42323ms | 70103 | 30 | 148922 | 17108.3 | 0.63238 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 886.541 | 0.111877 | 3.30732ms | 11812 | 30 | 6062.53 | 12706.5 | 2.78622 | 1(Win) |
| glaze | 851.317 | 0.825173 | 3.51103ms | 11812 | 30 | 357664 | 13232.2 | 2.90163 | 2(Loss) |
| jsonifier | 676.944 | 0.0595897 | 4.31195ms | 11812 | 30 | 2949.89 | 16640.7 | 3.65105 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3909.17 | 0.289485 | 0.889116ms | 11812 | 30 | 2087.62 | 2881.63 | 0.626741 | 1(Win) |
| glaze | 2487.17 | 0.295477 | 2.83903ms | 11812 | 32 | 5731.04 | 4529.16 | 0.988867 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2103.38 | 0.122815 | 3.63704ms | 31235 | 30 | 9075.59 | 14162 | 1.17418 | 1(Win) |
| glaze | 1560.98 | 0.122236 | 4.98339ms | 31235 | 30 | 16323.4 | 19082.9 | 1.58356 | 2(Loss) |
| jsonifier | 1245.04 | 0.0755756 | 6.0849ms | 31235 | 30 | 9808.53 | 23925.4 | 1.98616 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4538.78 | 0.245677 | 1.82276ms | 31235 | 30 | 7799.31 | 6563 | 0.54303 | 1(Win) |
| glaze | 3607.23 | 0.285534 | 2.16261ms | 31235 | 30 | 16679.1 | 8257.87 | 0.683816 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2119.7 | 1.07888 | 12.0826ms | 108313 | 30 | 8.29244e+06 | 48731.1 | 1.16716 | 1(Win) |
| simdjson (ondemand) | 1390.94 | 0.457101 | 18.2909ms | 108313 | 30 | 3.45692e+06 | 74262.9 | 1.77925 | 2(Loss) |
| glaze | 1349.25 | 0.785812 | 18.7302ms | 108313 | 30 | 1.08575e+07 | 76557.3 | 1.83424 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2410.43 | 1.49953 | 10.4043ms | 108313 | 30 | 1.2388e+07 | 42853.4 | 1.02643 | 1(Win) |
| glaze | 1874.09 | 1.25329 | 13.377ms | 108313 | 30 | 1.43154e+07 | 55117.5 | 1.32037 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2477.18 | 0.378218 | 20.2292ms | 213963 | 30 | 2.91184e+06 | 82372.2 | 0.999034 | 1(Win) |
| glaze | 1803.96 | 2.29904 | 26.9791ms | 213963 | 30 | 2.02879e+08 | 113113 | 1.37192 | 2(Loss) |
| jsonifier | 1610.74 | 0.404247 | 30.9735ms | 213963 | 30 | 7.86754e+06 | 126681 | 1.53652 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3493.6 | 0.849854 | 14.2887ms | 213963 | 30 | 7.39164e+06 | 58407.1 | 0.708311 | 1(Win) |
| glaze | 2245.13 | 0.74776 | 22.0331ms | 213963 | 30 | 1.3856e+07 | 90885.9 | 1.10209 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 555.863 | 0.121969 | 756.466ms | 1834197 | 30 | 4.41951e+08 | 3.14687e+06 | 4.45385 | 1(Win) |
| glaze | 426.389 | 0.206616 | 984.992ms | 1834197 | 30 | 2.15542e+09 | 4.10242e+06 | 5.80636 | 2(Loss) |
| simdjson (ondemand) | 415.153 | 0.092439 | 1017.15ms | 1834197 | 30 | 4.551e+08 | 4.21345e+06 | 5.9635 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 739.62 | 0.257275 | 567.163ms | 1834197 | 30 | 1.11069e+09 | 2.36503e+06 | 3.34737 | 1(Win) |
| glaze | 483.821 | 0.0677666 | 869.483ms | 1833577 | 30 | 1.79963e+08 | 3.61422e+06 | 5.11717 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1930.4 | 0.270081 | 1175.55ms | 9930848 | 30 | 5.26727e+09 | 4.90612e+06 | 1.2825 | 1(Win) |
| glaze STATISTICAL TIE | 1676.7 | 0.150096 | 1359.5ms | 9930848 | 30 | 2.15637e+09 | 5.64848e+06 | 1.47658 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1675.76 | 0.0592613 | 1359.42ms | 9930848 | 30 | 3.3652e+08 | 5.65163e+06 | 1.47737 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2711.19 | 0.0929879 | 842.556ms | 9930848 | 30 | 3.16538e+08 | 3.49322e+06 | 0.913174 | 1(Win) |
| glaze | 1692.95 | 0.0930897 | 1344.79ms | 9930228 | 30 | 8.13494e+08 | 5.59391e+06 | 1.46235 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1024.59 | 0.341716 | 145.621ms | 642697 | 30 | 1.25361e+08 | 598212 | 2.41603 | 1(Win) |
| simdjson (ondemand) | 832.01 | 0.307504 | 199.089ms | 642697 | 30 | 1.53949e+08 | 736678 | 2.97544 | 2(Loss) |
| glaze | 783.471 | 0.233999 | 188.559ms | 642697 | 30 | 1.00534e+08 | 782318 | 3.15977 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1240.57 | 1.0805 | 119.3ms | 642697 | 30 | 8.5494e+08 | 494065 | 1.99545 | 1(Win) |
| glaze | 794.103 | 0.13869 | 186.724ms | 642692 | 30 | 3.43769e+07 | 771838 | 3.1174 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1483.85 | 0.275661 | 189.679ms | 1225964 | 30 | 1.4153e+08 | 787929 | 1.66835 | 1(Win) |
| glaze | 1212.89 | 0.260137 | 232.474ms | 1225964 | 30 | 1.88642e+08 | 963955 | 2.04106 | 2(Loss) |
| jsonifier | 1050.99 | 0.552973 | 267.661ms | 1225964 | 30 | 1.13524e+09 | 1.11245e+06 | 2.35551 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2034.8 | 0.27777 | 137.966ms | 1225964 | 30 | 7.64196e+07 | 574587 | 1.21663 | 1(Win) |
| glaze | 1238.22 | 0.100388 | 227.101ms | 1225970 | 30 | 2.69557e+07 | 944243 | 1.99934 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 738.491 | 0.244221 | 127.281ms | 409725 | 30 | 5.00936e+07 | 529112 | 3.35211 | 1(Win) |
| glaze | 502.682 | 0.124847 | 187.327ms | 409725 | 30 | 2.82539e+07 | 777319 | 4.92477 | 2(Loss) |
| jsonifier | 490.985 | 0.834425 | 189.702ms | 409725 | 30 | 1.32295e+09 | 795838 | 5.04187 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2402.05 | 0.461847 | 39.4079ms | 409725 | 30 | 1.69332e+07 | 162671 | 1.03038 | 1(Win) |
| glaze | 2197.32 | 0.684033 | 42.9807ms | 409725 | 30 | 4.43888e+07 | 177828 | 1.12637 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1343.57 | 0.223273 | 133.654ms | 785750 | 30 | 4.65199e+07 | 557729 | 1.84247 | 1(Win) |
| glaze | 867.227 | 0.150053 | 207.487ms | 785750 | 30 | 5.04329e+07 | 864075 | 2.85461 | 2(Loss) |
| jsonifier | 740.058 | 0.242895 | 243.012ms | 785750 | 30 | 1.81466e+08 | 1.01256e+06 | 3.34519 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3788.53 | 0.476923 | 47.9634ms | 785750 | 30 | 2.6696e+07 | 197794 | 0.65337 | 1(Win) |
| glaze | 2716.01 | 0.427495 | 67.0358ms | 785750 | 30 | 4.1734e+07 | 275901 | 0.911373 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 888.779 | 0.147766 | 2228.28ms | 8587914 | 30 | 5.56234e+09 | 9.21498e+06 | 2.78562 | 1(Win) |
| glaze | 776.983 | 0.14243 | 2541.61ms | 8587914 | 30 | 6.76206e+09 | 1.05409e+07 | 3.18645 | 2(Loss) |
| jsonifier | 722.931 | 0.250085 | 2719.93ms | 8587914 | 30 | 2.40813e+10 | 1.1329e+07 | 3.4247 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2743.13 | 0.545474 | 731.612ms | 8588126 | 30 | 7.95746e+09 | 2.98574e+06 | 0.90249 | 1(Tie) |
| glaze STATISTICAL TIE | 2716.86 | 0.176865 | 723.403ms | 8588126 | 30 | 8.52836e+08 | 3.01461e+06 | 0.911192 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 982.281 | 0.294795 | 2305.94ms | 9804437 | 30 | 2.3623e+10 | 9.5189e+06 | 2.52043 | 1(Win) |
| glaze | 811.767 | 0.230745 | 2773.35ms | 9804437 | 30 | 2.11918e+10 | 1.15184e+07 | 3.04981 | 2(Loss) |
| jsonifier | 699.447 | 0.206691 | 3206.86ms | 9804437 | 30 | 2.29034e+10 | 1.3368e+07 | 3.53967 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2941.54 | 0.203359 | 829.91ms | 11078090 | 30 | 1.6004e+09 | 3.59162e+06 | 0.841631 | 1(Win) |
| glaze | 2598.7 | 0.123149 | 981.022ms | 11078090 | 30 | 7.51977e+08 | 4.06545e+06 | 0.952663 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 4433.26 | 1.0393 | 13.8733ms | 264040 | 30 | 1.04543e+07 | 56799.8 | 0.558144 | 1(Win) |
| jsonifier | 4078.35 | 0.849633 | 15.0694ms | 264040 | 30 | 8.25573e+06 | 61742.7 | 0.606765 | 2(Loss) |
| glaze | 1050.4 | 0.465862 | 58.2386ms | 264040 | 30 | 3.74167e+07 | 239726 | 2.35664 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5711.62 | 0.88907 | 16.3411ms | 399947 | 30 | 1.0575e+07 | 66779.5 | 0.433265 | 1(Win) |
| jsonifier | 5200.68 | 0.434331 | 17.9739ms | 399947 | 30 | 3.04401e+06 | 73340.2 | 0.475815 | 2(Loss) |
| glaze | 1455.15 | 0.333245 | 63.2805ms | 399947 | 30 | 2.28895e+07 | 262117 | 1.70111 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1445.86 | 0.556284 | 44.2875ms | 264040 | 30 | 2.81578e+07 | 174157 | 1.71188 | 1(Win) |
| glaze | 1118.01 | 0.50494 | 54.9646ms | 264040 | 30 | 3.88018e+07 | 225229 | 2.21369 | 2(Loss) |
| jsonifier | 1093.58 | 0.691425 | 56.651ms | 264040 | 30 | 7.60415e+07 | 230261 | 2.26292 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3404.98 | 0.725212 | 18.0811ms | 263923 | 30 | 8.62137e+06 | 73920.1 | 0.726656 | 1(Win) |
| jsonifier | 2996.81 | 0.60136 | 20.6323ms | 264040 | 30 | 7.6597e+06 | 84025.4 | 0.825795 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1996.17 | 0.752285 | 46.1766ms | 399947 | 30 | 6.19866e+07 | 191076 | 1.23999 | 1(Win) |
| glaze | 1337.54 | 0.559873 | 68.7828ms | 399947 | 30 | 7.64706e+07 | 285165 | 1.85045 | 2(Loss) |
| jsonifier | 1106.93 | 0.812636 | 83.0603ms | 399947 | 30 | 2.35222e+08 | 344574 | 2.23574 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4183.15 | 0.569907 | 22.3138ms | 399947 | 30 | 8.10082e+06 | 91180 | 0.591481 | 1(Win) |
| glaze | 3587.02 | 0.698696 | 26.6635ms | 399830 | 30 | 1.65494e+07 | 106302 | 0.689921 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1771.89 | 0.365911 | 60.8232ms | 466906 | 30 | 2.53664e+07 | 251300 | 1.3969 | 1(Win) |
| glaze | 1727.78 | 0.428988 | 62.3646ms | 466906 | 30 | 3.66684e+07 | 257716 | 1.43264 | 2(Loss) |
| simdjson (ondemand) | 915.424 | 0.37042 | 116.421ms | 466906 | 30 | 9.7392e+07 | 486415 | 2.70417 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3288.4 | 0.600708 | 49.0556ms | 699405 | 30 | 4.45385e+07 | 202835 | 0.75268 | 1(Win) |
| glaze | 2411.84 | 0.59979 | 66.5367ms | 699405 | 30 | 8.25429e+07 | 276554 | 1.02631 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1794.23 | 0.284233 | 80.7674ms | 631514 | 30 | 2.73074e+07 | 335665 | 1.37969 | 1(Win) |
| glaze | 1691.27 | 1.20621 | 84.3946ms | 631514 | 30 | 5.53491e+08 | 356100 | 1.46367 | 2(Loss) |
