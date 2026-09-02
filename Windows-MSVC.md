# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Sep 02, 2026)
#### Using the following commits:
----
| Jsonifier: [a1bd83c](https://github.com/nihilai-collective/jsonifier/commit/a1bd83c)  
| Glaze: [a5f515c](https://github.com/stephenberry/glaze/commit/a5f515c)  
| Simdjson: [06856ec](https://github.com/simdjson/simdjson/commit/06856ec)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [f0ef39c](https://github.com/realtimechris/benchmarksuite/commit/f0ef39c).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1032.13 | 0.490742 | 1.6666ms | 1811 | 30 | 2022.99 | 1673.33 | 2.8787 | 1(Win) |
| glaze | 323.024 | 0.173269 | 2.5545ms | 1811 | 30 | 2574.71 | 5346.67 | 9.3159 | 2(Loss) |
| simdjson (ondemand) | 174.455 | 1.8919 | 7.3865ms | 1811 | 32 | 1.12258e+06 | 9900 | 17.3865 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 604.587 | 0.400127 | 1.873ms | 1811 | 30 | 3919.54 | 2856.67 | 4.98174 | 1(Win) |
| glaze | 357.696 | 0.208131 | 4.897ms | 1798 | 32 | 3185.48 | 4793.75 | 8.43813 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2086.77 | 0.48077 | 1.5955ms | 3873 | 30 | 2172.41 | 1770 | 1.44401 | 1(Win) |
| glaze | 1306.69 | 0.29051 | 2.5369ms | 3873 | 30 | 2022.99 | 2826.67 | 2.31214 | 2(Loss) |
| simdjson (ondemand) | 366.722 | 0.294581 | 15.4985ms | 3873 | 64 | 56339.3 | 10071.9 | 8.2694 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3011.07 | 0.669437 | 1.5119ms | 3873 | 30 | 2022.99 | 1226.67 | 0.979456 | 1(Win) |
| glaze | 1300.56 | 0.320323 | 1.8878ms | 3873 | 30 | 2482.76 | 2840 | 2.30673 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2196.67 | 0.468431 | 1.8912ms | 3862 | 30 | 1850.57 | 1676.67 | 1.37252 | 1(Win) |
| glaze | 1292.31 | 0.325781 | 1.8944ms | 3862 | 30 | 2586.21 | 2850 | 2.32525 | 2(Loss) |
| simdjson (ondemand) | 369.811 | 0.0885698 | 8.3863ms | 3862 | 32 | 2489.92 | 9959.38 | 8.2067 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2833.15 | 0.345395 | 2.7042ms | 3862 | 32 | 645.161 | 1300 | 1.04761 | 1(Win) |
| glaze | 1267.12 | 0.15936 | 2.0159ms | 3862 | 30 | 643.678 | 2906.67 | 2.3852 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1638.75 | 1.80551 | 1.3957ms | 905 | 30 | 2712.64 | 526.667 | 1.76958 | 1(Win) |
| glaze | 378.853 | 0.32592 | 3.7783ms | 905 | 32 | 1764.11 | 2278.12 | 7.9481 | 2(Loss) |
| simdjson (ondemand) | 145.055 | 0.150929 | 5.1505ms | 905 | 32 | 2580.65 | 5950 | 20.9007 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 690.46 | 0.742781 | 1.5322ms | 905 | 30 | 2586.21 | 1250 | 4.33816 | 1(Win) |
| glaze | 362.129 | 0.290369 | 2.081ms | 905 | 30 | 1436.78 | 2383.33 | 8.29282 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2807.67 | 0.284758 | 2.0565ms | 9578 | 30 | 2574.71 | 3253.33 | 1.07309 | 1(Win) |
| glaze | 1834.2 | 1.1768 | 2.6122ms | 9578 | 30 | 103034 | 4980 | 1.64969 | 2(Loss) |
| simdjson (ondemand) | 814.88 | 1.89895 | 9.2788ms | 9578 | 32 | 1.44991e+06 | 11209.4 | 3.72144 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4223.95 | 0.402086 | 3.1163ms | 9578 | 32 | 2419.35 | 2162.5 | 0.709758 | 1(Win) |
| glaze | 3004.08 | 0.325527 | 3.7828ms | 9578 | 32 | 3135.08 | 3040.62 | 1.00321 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3883.43 | 1.27784 | 15.7853ms | 233995 | 30 | 1.61755e+07 | 57463.3 | 0.782002 | 1(Win) |
| glaze | 1686.82 | 1.10226 | 34.1851ms | 233995 | 30 | 6.37924e+07 | 132293 | 1.80137 | 2(Loss) |
| simdjson (ondemand) | 1264.8 | 1.33711 | 105.425ms | 233995 | 32 | 1.78093e+08 | 176434 | 2.40268 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5520.38 | 1.26931 | 17.256ms | 346753 | 30 | 1.73445e+07 | 59903.3 | 0.550325 | 1(Win) |
| glaze | 2283.32 | 0.60798 | 87.6767ms | 346753 | 32 | 2.48105e+07 | 144828 | 1.33096 | 2(Loss) |
| simdjson (ondemand) | 1772.94 | 0.634189 | 47.785ms | 346753 | 30 | 4.19768e+07 | 186520 | 1.71403 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1629.58 | 0.982837 | 35.7559ms | 233995 | 30 | 5.43432e+07 | 136940 | 1.86344 | 1(Win) |
| glaze | 1240.92 | 1.65738 | 53.7393ms | 233995 | 30 | 2.66495e+08 | 179830 | 2.44842 | 2(Loss) |
| simdjson (ondemand) | 640.939 | 2.30685 | 198.758ms | 233995 | 32 | 2.06428e+09 | 348169 | 4.74116 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3686.87 | 1.74897 | 339.925ms | 233995 | 256 | 2.86882e+08 | 60527 | 0.823872 | 1(Win) |
| glaze | 3232.73 | 1.26403 | 19.3881ms | 233995 | 30 | 2.28408e+07 | 69030 | 0.939797 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2009.43 | 0.823127 | 102.602ms | 346753 | 32 | 5.8719e+07 | 164569 | 1.51203 | 1(Win) |
| glaze | 1601.66 | 2.31491 | 511.94ms | 346753 | 128 | 2.92401e+09 | 206467 | 1.89734 | 2(Loss) |
| simdjson (ondemand) | 919.204 | 2.0822 | 439.87ms | 346753 | 64 | 3.59122e+09 | 359756 | 3.30605 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3793.92 | 1.52812 | 461.974ms | 346753 | 256 | 4.54171e+08 | 87162.9 | 0.800785 | 1(Win) |
| glaze | 2524.31 | 1.69141 | 2883.05ms | 346753 | 1024 | 5.02755e+09 | 131002 | 1.20354 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3886.59 | 1.00686 | 15.3406ms | 233995 | 30 | 1.00263e+07 | 57416.7 | 0.781687 | 1(Win) |
| glaze | 1739.64 | 0.289885 | 332.987ms | 233995 | 128 | 1.76993e+07 | 128277 | 1.7469 | 2(Loss) |
| simdjson (ondemand) | 655.82 | 0.737255 | 199.568ms | 233995 | 32 | 2.01386e+08 | 340269 | 4.63431 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5181.06 | 0.808019 | 85.4939ms | 346753 | 64 | 1.70226e+07 | 63826.6 | 0.586358 | 1(Win) |
| glaze | 2266.44 | 0.882853 | 36.9312ms | 346753 | 30 | 4.97793e+07 | 145907 | 1.34072 | 2(Loss) |
| simdjson (ondemand) | 919.808 | 2.19986 | 89.8906ms | 346753 | 30 | 1.87654e+09 | 359520 | 3.304 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1689.37 | 1.11449 | 79.772ms | 233995 | 32 | 6.93535e+07 | 132094 | 1.79843 | 1(Win) |
| glaze | 1319.32 | 1.10907 | 103.416ms | 233995 | 32 | 1.1261e+08 | 169144 | 2.30343 | 2(Loss) |
| simdjson (ondemand) | 51.8019 | 1.1838 | 1036.05ms | 233995 | 30 | 7.80186e+10 | 4.30785e+06 | 58.6746 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4245.99 | 0.795447 | 15.4733ms | 233995 | 30 | 5.24323e+06 | 52556.7 | 0.715349 | 1(Win) |
| glaze | 2852.74 | 1.95369 | 841.219ms | 233995 | 512 | 1.19583e+09 | 78224.8 | 1.06485 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1927.17 | 1.36435 | 45.0183ms | 346753 | 30 | 1.64427e+08 | 171593 | 1.57687 | 1(Win) |
| glaze | 1710.32 | 1.04171 | 50.5778ms | 346753 | 30 | 1.21703e+08 | 193350 | 1.7769 | 2(Loss) |
| simdjson (ondemand) | 75.9765 | 1.47097 | 1011.42ms | 346753 | 30 | 1.22974e+11 | 4.35252e+06 | 40.0041 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3980.54 | 1.95692 | 103.849ms | 346753 | 64 | 1.69154e+08 | 83076.6 | 0.7632 | 1(Win) |
| glaze | 2310.87 | 2.42314 | 1454.64ms | 346753 | 512 | 6.15625e+09 | 143102 | 1.31465 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 759.263 | 2.40223 | 31.2762ms | 94651 | 30 | 2.44689e+08 | 118887 | 4.00176 | 1(Win) |
| glaze | 680.663 | 2.03007 | 722.775ms | 94651 | 256 | 1.85544e+09 | 132615 | 4.46401 | 2(Loss) |
| simdjson (ondemand) | 536.871 | 1.8107 | 861.384ms | 94651 | 256 | 2.37271e+09 | 168134 | 5.65975 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4519.34 | 1.53688 | 6.9973ms | 94651 | 30 | 2.82685e+06 | 19973.3 | 0.671567 | 1(Win) |
| jsonifier | 3870.21 | 1.93125 | 7.5369ms | 94651 | 30 | 6.08668e+06 | 23323.3 | 0.784293 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 994.138 | 1.74679 | 77.2587ms | 136024 | 32 | 1.66253e+08 | 130488 | 3.05643 | 1(Win) |
| glaze | 862.811 | 1.98009 | 756.168ms | 136024 | 256 | 2.26887e+09 | 150349 | 3.52172 | 2(Loss) |
| simdjson (ondemand) | 814.21 | 1.58414 | 41.2163ms | 136024 | 30 | 1.91102e+08 | 159323 | 3.73184 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4330.99 | 0.336158 | 84.2891ms | 136046 | 128 | 1.29806e+06 | 29957 | 0.701314 | 1(Win) |
| jsonifier | 3901.82 | 1.1798 | 9.9089ms | 136024 | 30 | 4.61568e+06 | 33246.7 | 0.778364 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 619.398 | 0.977445 | 849.028ms | 2090234 | 30 | 2.96863e+10 | 3.21829e+06 | 4.90656 | 1(Win) |
| glaze | 352.614 | 1.27172 | 1335.77ms | 2090234 | 30 | 1.55058e+11 | 5.65322e+06 | 8.61925 | 2(Loss) |
| simdjson (ondemand) | 269.937 | 0.722459 | 1848.53ms | 2090234 | 30 | 8.53912e+10 | 7.3847e+06 | 11.2593 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1004.64 | 1.09772 | 503.126ms | 2090234 | 30 | 1.42323e+10 | 1.9842e+06 | 3.02488 | 1(Win) |
| glaze | 647.496 | 1.59335 | 735.505ms | 2090234 | 30 | 7.21873e+10 | 3.07863e+06 | 4.69367 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1551.02 | 1.64814 | 1001.12ms | 6661897 | 30 | 1.36732e+11 | 4.09621e+06 | 1.95946 | 1(Win) |
| glaze | 919.009 | 1.0241 | 1661.1ms | 6661897 | 30 | 1.50369e+11 | 6.91318e+06 | 3.30709 | 2(Loss) |
| simdjson (ondemand) | 753.872 | 1.08771 | 1954.4ms | 6661897 | 30 | 2.52087e+11 | 8.42753e+06 | 4.03124 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1807.5 | 1.43879 | 843.247ms | 6661897 | 30 | 7.67286e+10 | 3.51495e+06 | 1.68141 | 1(Win) |
| glaze | 1139.41 | 1.2226 | 1341.99ms | 6661897 | 30 | 1.3942e+11 | 5.57596e+06 | 2.66727 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1341.46 | 0.714523 | 92.1064ms | 500299 | 30 | 1.93757e+08 | 355673 | 2.26548 | 1(Win) |
| glaze | 838.047 | 1.59624 | 144.169ms | 500299 | 30 | 2.47766e+09 | 569327 | 3.62636 | 2(Loss) |
| simdjson (ondemand) | 397.609 | 1.91406 | 286.9ms | 500299 | 30 | 1.58263e+10 | 1.19998e+06 | 7.64361 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4770.18 | 1.66021 | 60.8633ms | 500299 | 32 | 8.82398e+07 | 100022 | 0.636876 | 1(Win) |
| glaze | 4321.63 | 1.40602 | 30.0422ms | 500299 | 30 | 7.22879e+07 | 110403 | 0.70284 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2594.5 | 1.73233 | 647.392ms | 1439562 | 64 | 5.37769e+09 | 529148 | 1.17116 | 1(Win) |
| glaze | 1745.84 | 2.28144 | 194.72ms | 1439562 | 30 | 9.65592e+09 | 786370 | 1.74064 | 2(Loss) |
| simdjson (ondemand) | 1083.5 | 1.96959 | 304.876ms | 1439562 | 30 | 1.86843e+10 | 1.26708e+06 | 2.8048 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2554.03 | 2.12409 | 315.169ms | 1439562 | 32 | 4.17162e+09 | 537531 | 1.18915 | 1(Win) |
| glaze | 1279.47 | 2.10785 | 283.587ms | 1439584 | 30 | 1.53467e+10 | 1.07302e+06 | 2.37465 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1317.37 | 1.81823 | 11.7769ms | 56369 | 30 | 1.65151e+07 | 40806.7 | 2.3057 | 1(Win) |
| glaze | 1141.81 | 2.29933 | 29.4437ms | 56369 | 32 | 3.75016e+07 | 47081.2 | 2.65927 | 2(Loss) |
| simdjson (ondemand) | 531.22 | 0.845459 | 27.0661ms | 56369 | 30 | 2.19603e+07 | 101197 | 5.72004 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4855.34 | 0.0729345 | 8.97ms | 56369 | 32 | 2086.69 | 11071.9 | 0.624065 | 1(Win) |
| glaze | 3989.08 | 1.70239 | 567.613ms | 56369 | 2048 | 1.07791e+08 | 13476.2 | 0.760402 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1688.84 | 1.55158 | 15.2899ms | 94370 | 30 | 2.05099e+07 | 53290 | 1.79902 | 1(Win) |
| jsonifier | 1581.69 | 2.49473 | 15.312ms | 94370 | 30 | 6.04497e+07 | 56900 | 1.92021 | 2(Loss) |
| simdjson (ondemand) | 860.596 | 0.919624 | 28.3909ms | 94370 | 30 | 2.77467e+07 | 104577 | 3.53029 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5288.18 | 1.34829 | 23.6441ms | 94370 | 64 | 3.3698e+06 | 17018.8 | 0.573918 | 1(Win) |
| glaze | 4074.62 | 0.626165 | 16.5079ms | 94370 | 32 | 612097 | 22087.5 | 0.744735 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1180.05 | 1.05015 | 13.1369ms | 52708 | 30 | 6.00309e+06 | 42596.7 | 2.57322 | 1(Win) |
| glaze | 943.22 | 2.24351 | 288.521ms | 52708 | 256 | 3.65951e+08 | 53292.2 | 3.22017 | 2(Loss) |
| simdjson (ondemand) | 765.476 | 1.36141 | 18.2645ms | 52708 | 30 | 2.39768e+07 | 65666.7 | 3.9691 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5732.43 | 0.649974 | 16.9022ms | 52708 | 64 | 207897 | 8768.75 | 0.528596 | 1(Win) |
| glaze | 4490.57 | 2.11115 | 8.5083ms | 52708 | 32 | 1.78706e+06 | 11193.8 | 0.675029 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1234.14 | 0.83922 | 151.607ms | 70103 | 128 | 2.64551e+07 | 54171.9 | 2.46029 | 1(Win) |
| glaze | 1118.36 | 2.11467 | 17.1914ms | 70103 | 30 | 4.79423e+07 | 59780 | 2.71618 | 2(Loss) |
| simdjson (ondemand) | 984.906 | 1.93122 | 18.9115ms | 70103 | 30 | 5.15548e+07 | 67880 | 3.08406 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5653.74 | 2.15135 | 9.8951ms | 70103 | 32 | 2.07097e+06 | 11825 | 0.536157 | 1(Win) |
| glaze | 3248.12 | 1.74961 | 30.0067ms | 70103 | 64 | 8.29986e+06 | 20582.8 | 0.934454 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1177.92 | 0.759489 | 4.0887ms | 11812 | 30 | 158264 | 9563.33 | 2.57493 | 1(Win) |
| glaze | 679.754 | 2.07763 | 23.5549ms | 11812 | 64 | 7.58682e+06 | 16571.9 | 4.4644 | 2(Loss) |
| simdjson (ondemand) | 427.128 | 2.03313 | 8.4687ms | 11812 | 30 | 8.62547e+06 | 26373.3 | 7.10843 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3614.37 | 0.556448 | 2.2003ms | 11812 | 30 | 9022.99 | 3116.67 | 0.835557 | 1(Win) |
| glaze | 3304.07 | 1.99888 | 4.0387ms | 11812 | 32 | 148619 | 3409.38 | 0.912644 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2293.74 | 2.2344 | 4.3616ms | 31235 | 30 | 2.52602e+06 | 12986.7 | 1.32249 | 1(Win) |
| glaze | 1448.05 | 0.834668 | 59.2502ms | 31235 | 128 | 3.77357e+06 | 20571.1 | 2.09651 | 2(Loss) |
| simdjson (ondemand) | 1041.18 | 1.97057 | 9.4502ms | 31235 | 30 | 9.53541e+06 | 28610 | 2.91619 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5502.71 | 0.146432 | 2.6662ms | 31235 | 30 | 1885.06 | 5413.33 | 0.549547 | 1(Win) |
| glaze | 4608.77 | 0.282314 | 2.903ms | 31235 | 30 | 9988.51 | 6463.33 | 0.658033 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2472.95 | 1.88163 | 12.191ms | 108313 | 30 | 1.85318e+07 | 41770 | 1.22816 | 1(Win) |
| glaze | 1193.65 | 1.23913 | 53.6807ms | 108313 | 32 | 3.67953e+07 | 86537.5 | 2.54568 | 2(Loss) |
| simdjson (ondemand) | 582.077 | 0.860197 | 46.644ms | 108313 | 30 | 6.99066e+07 | 177460 | 5.22037 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4608.18 | 2.04477 | 15.8818ms | 108313 | 32 | 6.72265e+06 | 22415.6 | 0.658607 | 1(Win) |
| glaze | 3996.68 | 1.20813 | 72.2746ms | 108313 | 128 | 1.24797e+07 | 25845.3 | 0.759563 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2416.23 | 0.884255 | 54.8982ms | 213963 | 32 | 1.78445e+07 | 84450 | 1.25732 | 1(Win) |
| glaze | 1768.67 | 2.39885 | 302.184ms | 213963 | 128 | 9.80392e+08 | 115370 | 1.71789 | 2(Loss) |
| simdjson (ondemand) | 1055.6 | 2.19718 | 49.3994ms | 213963 | 30 | 5.41169e+08 | 193303 | 2.87862 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5838.93 | 1.55348 | 10.5857ms | 213963 | 30 | 8.84189e+06 | 34946.7 | 0.520003 | 1(Win) |
| glaze | 4119.9 | 1.97188 | 33.766ms | 213963 | 32 | 3.05221e+07 | 49528.1 | 0.737568 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 571.187 | 1.78871 | 719.792ms | 1834197 | 30 | 9.002e+10 | 3.06244e+06 | 5.32035 | 1(Win) |
| glaze | 227.649 | 1.75848 | 1788.51ms | 1834197 | 30 | 5.4772e+11 | 7.68389e+06 | 13.3487 | 2(Loss) |
| simdjson (ondemand) | 195.062 | 0.904624 | 2118ms | 1834197 | 30 | 1.97425e+11 | 8.96753e+06 | 15.5804 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 637.516 | 1.70149 | 682.278ms | 1834197 | 30 | 6.53864e+10 | 2.74382e+06 | 4.76711 | 1(Win) |
| glaze | 496.401 | 1.10368 | 844.889ms | 1833577 | 30 | 4.53464e+10 | 3.52263e+06 | 6.12235 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2477.49 | 1.2678 | 958.158ms | 9930848 | 30 | 7.04643e+10 | 3.82274e+06 | 1.22666 | 1(Win) |
| glaze | 1296.41 | 0.950933 | 1824.49ms | 9930848 | 30 | 1.44779e+11 | 7.30537e+06 | 2.34438 | 2(Loss) |
| simdjson (ondemand) | 1013 | 0.997218 | 2304ms | 9930848 | 30 | 2.60769e+11 | 9.34926e+06 | 3.00025 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1651.64 | 1.44784 | 1344.49ms | 9930848 | 30 | 2.06779e+11 | 5.73419e+06 | 1.84007 | 1(Win) |
| glaze | 816.346 | 0.815288 | 2829.28ms | 9930228 | 30 | 2.68357e+11 | 1.16007e+07 | 3.72288 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1257.32 | 2.12059 | 589.994ms | 642697 | 64 | 6.83934e+09 | 487483 | 2.41667 | 1(Win) |
| glaze | 657.185 | 1.73537 | 231.991ms | 642697 | 30 | 7.85852e+09 | 932650 | 4.62422 | 2(Loss) |
| simdjson (ondemand) | 437.074 | 2.07739 | 811.465ms | 642697 | 32 | 2.71574e+10 | 1.40233e+06 | 6.95284 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1265.86 | 1.3986 | 1226.39ms | 642697 | 128 | 5.87005e+09 | 484196 | 2.40051 | 1(Win) |
| glaze | 525.397 | 2.28855 | 652.41ms | 642692 | 32 | 2.28087e+10 | 1.16658e+06 | 5.78346 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1802.71 | 2.45544 | 379.183ms | 1225964 | 32 | 8.11542e+09 | 648562 | 1.68569 | 1(Win) |
| glaze | 1057.53 | 2.34323 | 266.111ms | 1225964 | 30 | 2.01337e+10 | 1.10557e+06 | 2.8733 | 2(Loss) |
| simdjson (ondemand) | 805.063 | 2.29379 | 834.887ms | 1225964 | 32 | 3.55103e+10 | 1.45227e+06 | 3.77475 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1334.24 | 1.89774 | 216.092ms | 1225964 | 30 | 8.29625e+09 | 876280 | 2.27697 | 1(Win) |
| glaze | 1012.19 | 2.37865 | 278.544ms | 1225970 | 30 | 2.26472e+10 | 1.15509e+06 | 3.00199 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 809.665 | 2.25539 | 271.213ms | 409725 | 32 | 3.79113e+09 | 482600 | 3.75323 | 1(Win) |
| glaze | 512.712 | 2.17705 | 914.447ms | 409725 | 64 | 1.76179e+10 | 762112 | 5.92213 | 2(Loss) |
| simdjson (ondemand) | 421.235 | 2.3312 | 234.643ms | 409725 | 30 | 1.40287e+10 | 927617 | 7.21418 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2711.44 | 1.60947 | 87.9773ms | 409725 | 32 | 1.72148e+08 | 144109 | 1.12014 | 1(Win) |
| jsonifier | 2349.07 | 2.29583 | 42.4843ms | 409725 | 30 | 4.37517e+08 | 166340 | 1.29362 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1185.39 | 2.26311 | 359.518ms | 785750 | 32 | 6.54944e+09 | 632153 | 2.56353 | 1(Win) |
| glaze STATISTICAL TIE | 826.358 | 1.98051 | 505.809ms | 785750 | 32 | 1.03213e+10 | 906809 | 3.67733 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 782.812 | 2.16407 | 237.588ms | 785750 | 30 | 1.28741e+10 | 957253 | 3.88205 | 2(Tie) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3789.51 | 1.00923 | 51.9856ms | 785750 | 30 | 1.19483e+08 | 197743 | 0.801696 | 1(Win) |
| glaze | 1557.21 | 2.35864 | 119.039ms | 785750 | 30 | 3.86474e+09 | 481213 | 1.95049 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 794.001 | 1.29448 | 2539.14ms | 8587914 | 30 | 5.34862e+11 | 1.03149e+07 | 3.82544 | 1(Win) |
| glaze | 582.425 | 0.770349 | 3409.88ms | 8587914 | 30 | 3.5204e+11 | 1.4062e+07 | 5.21832 | 2(Loss) |
| simdjson (ondemand) | 524.705 | 0.936037 | 3711.94ms | 8587914 | 30 | 6.40401e+11 | 1.56089e+07 | 5.79237 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1802.13 | 1.50509 | 1148.93ms | 8588126 | 30 | 1.40369e+11 | 4.54478e+06 | 1.68633 | 1(Win) |
| glaze | 1038.23 | 1.10234 | 2050.44ms | 8588126 | 30 | 2.26861e+11 | 7.88867e+06 | 2.92715 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 766.965 | 1.69143 | 2845.8ms | 9804437 | 30 | 1.27563e+12 | 1.21912e+07 | 3.96263 | 1(Win) |
| glaze | 628.602 | 0.905826 | 3618.35ms | 9804437 | 30 | 5.44634e+11 | 1.48746e+07 | 4.83501 | 2(Loss) |
| simdjson (ondemand) | 608.567 | 0.943522 | 3756.63ms | 9804437 | 30 | 6.30455e+11 | 1.53644e+07 | 4.99418 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1837.35 | 1.20602 | 1432.03ms | 11078090 | 30 | 1.44269e+11 | 5.75006e+06 | 1.65399 | 1(Win) |
| glaze | 1115.38 | 0.777303 | 5629.78ms | 11078090 | 32 | 1.73466e+11 | 9.472e+06 | 2.72445 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4040.78 | 1.41027 | 17.5674ms | 264040 | 30 | 2.31704e+07 | 62316.7 | 0.751879 | 1(Win) |
| simdjson (ondemand) | 1645.23 | 2.1196 | 769.247ms | 264040 | 256 | 2.69425e+09 | 153054 | 1.84689 | 2(Loss) |
| glaze | 1297.49 | 2.15357 | 51.0814ms | 264040 | 30 | 5.2405e+08 | 194073 | 2.34189 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5362.28 | 1.07037 | 19.6077ms | 399947 | 30 | 1.73898e+07 | 71130 | 0.566506 | 1(Win) |
| simdjson (ondemand) | 2277.56 | 2.32184 | 809.909ms | 399947 | 256 | 3.87054e+09 | 167468 | 1.33416 | 2(Loss) |
| glaze | 1873.34 | 1.38134 | 55.0224ms | 399947 | 30 | 2.37296e+08 | 203603 | 1.62222 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1516.28 | 0.962225 | 45.4451ms | 264040 | 30 | 7.66049e+07 | 166070 | 2.00418 | 1(Win) |
| glaze | 860.52 | 1.90193 | 73.6006ms | 264040 | 30 | 9.2924e+08 | 292623 | 3.53143 | 2(Loss) |
| simdjson (ondemand) | 710.982 | 2.04133 | 906.891ms | 264040 | 128 | 6.69053e+09 | 354170 | 4.27419 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5186.93 | 1.91108 | 13.8747ms | 264040 | 30 | 2.58226e+07 | 48546.7 | 0.585564 | 1(Win) |
| glaze | 3938.09 | 1.91951 | 19.3291ms | 263923 | 30 | 4.51529e+07 | 63913.3 | 0.771308 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1447.46 | 2.25592 | 670.088ms | 399947 | 128 | 4.52321e+09 | 263509 | 2.09939 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1066.17 | 2.28775 | 216.166ms | 399947 | 32 | 2.14348e+09 | 357747 | 2.85029 | 2(Tie) |
| glaze STATISTICAL TIE | 1044.46 | 2.26665 | 876.394ms | 399947 | 128 | 8.77001e+09 | 365183 | 2.90927 | 2(Tie) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6109.12 | 1.32776 | 39.6095ms | 399947 | 32 | 2.19907e+07 | 62434.4 | 0.497331 | 1(Win) |
| glaze | 3498.54 | 2.27668 | 575.914ms | 399830 | 256 | 1.57624e+09 | 108991 | 0.860624 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2240.65 | 2.30265 | 253.528ms | 466906 | 64 | 1.34013e+09 | 198727 | 1.3558 | 1(Win) |
| glaze | 2066.34 | 1.3198 | 57.4971ms | 466906 | 30 | 2.42657e+08 | 215490 | 1.47068 | 2(Loss) |
| simdjson (ondemand) | 1124.34 | 0.500393 | 102.69ms | 466906 | 30 | 1.17817e+08 | 396033 | 2.70238 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2771.55 | 2.18906 | 605.416ms | 699405 | 128 | 3.55251e+09 | 240661 | 1.09608 | 1(Win) |
| glaze | 2454.78 | 2.38675 | 668.804ms | 699405 | 128 | 5.38342e+09 | 271717 | 1.23791 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4077.93 | 1.17253 | 87.6494ms | 631514 | 32 | 9.59592e+07 | 147688 | 0.745128 | 1(Win) |
| glaze | 2458.07 | 2.037 | 141.768ms | 631514 | 32 | 7.97091e+08 | 245012 | 1.23614 | 2(Loss) |
