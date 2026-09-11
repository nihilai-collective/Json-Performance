# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 11, 2026)
#### Using the following commits:
----
| Jsonifier: [f2a9be6](https://github.com/nihilai-collective/jsonifier/commit/f2a9be6)  
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

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 655.945 | 0.117167 | 1.87232ms | 1811 | 30 | 285.517 | 2633 | 3.50751 | 1(Win) |
| glaze | 465.034 | 0.134677 | 1.1783ms | 1811 | 30 | 750.547 | 3713.93 | 4.96264 | 2(Loss) |
| simdjson (ondemand) | 139.07 | 2.13175 | 3.21031ms | 1811 | 30 | 2.10265e+06 | 12419 | 16.7234 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 400.782 | 0.102911 | 1.381ms | 1811 | 30 | 590.023 | 4309.33 | 5.76902 | 1(Win) |
| glaze | 270.332 | 0.230984 | 1.77219ms | 1798 | 30 | 6439.76 | 6342.97 | 8.57588 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1323.33 | 0.100572 | 1.04384ms | 3873 | 30 | 236.395 | 2791.13 | 1.73854 | 1(Win) |
| glaze | 1095.79 | 0.09157 | 1.06847ms | 3873 | 30 | 285.803 | 3370.7 | 2.10462 | 2(Loss) |
| simdjson (ondemand) | 305.407 | 0.0559982 | 3.15893ms | 3873 | 30 | 1375.96 | 12094 | 7.61398 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1736.22 | 0.106251 | 0.846997ms | 3873 | 30 | 153.275 | 2127.37 | 1.31893 | 1(Win) |
| glaze | 1072.13 | 0.181642 | 1.10979ms | 3873 | 30 | 1174.78 | 3445.1 | 2.15267 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1276.24 | 0.216188 | 7.85762ms | 3862 | 128 | 4982.32 | 2885.88 | 1.80414 | 1(Win) |
| glaze | 959.955 | 0.0925084 | 1.16045ms | 3862 | 30 | 377.926 | 3836.73 | 2.40604 | 2(Loss) |
| simdjson (ondemand) | 295.832 | 2.07441 | 3.22782ms | 3862 | 30 | 2.001e+06 | 12449.9 | 7.86005 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1636.49 | 0.128718 | 0.832148ms | 3862 | 30 | 251.766 | 2250.6 | 1.40306 | 1(Win) |
| glaze | 1030.23 | 0.135359 | 1.09227ms | 3862 | 30 | 702.516 | 3575.03 | 2.2398 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 767.838 | 0.257333 | 0.59815ms | 905 | 30 | 250.999 | 1124.03 | 2.94365 | 1(Win) |
| glaze | 490.161 | 0.285646 | 0.691154ms | 905 | 30 | 758.924 | 1760.8 | 4.65112 | 2(Loss) |
| simdjson (ondemand) | 98.9947 | 0.0968426 | 2.37811ms | 905 | 30 | 2138.59 | 8718.4 | 23.4621 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 828.552 | 0.107783 | 0.540041ms | 905 | 30 | 37.8161 | 1041.67 | 2.71989 | 1(Win) |
| glaze | 303.188 | 0.412819 | 0.965839ms | 905 | 30 | 4142.99 | 2846.67 | 7.59359 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1686.87 | 0.0733742 | 1.70343ms | 9578 | 30 | 473.582 | 5414.93 | 1.3731 | 1(Win) |
| glaze | 1416.24 | 0.0466277 | 8.26165ms | 9578 | 64 | 578.821 | 6449.69 | 1.63717 | 2(Loss) |
| simdjson (ondemand) | 709.177 | 1.8831 | 7.51726ms | 9578 | 32 | 1.88251e+06 | 12880.1 | 3.27944 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3141.52 | 0.152098 | 0.928229ms | 9578 | 30 | 586.731 | 2907.6 | 0.733445 | 1(Win) |
| glaze | 2282.53 | 0.22939 | 1.20705ms | 9578 | 30 | 2528.07 | 4001.83 | 1.01235 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2587.56 | 0.682958 | 21.0851ms | 233995 | 30 | 1.04074e+07 | 86241.5 | 0.900729 | 1(Win) |
| simdjson (ondemand) | 2479.41 | 0.83613 | 21.9082ms | 233995 | 30 | 1.69896e+07 | 90003.2 | 0.940091 | 2(Loss) |
| glaze | 1277.65 | 0.543268 | 42.3539ms | 233995 | 30 | 2.70109e+07 | 174660 | 1.82486 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3134.21 | 0.73677 | 25.7447ms | 346753 | 30 | 1.81288e+07 | 105510 | 0.743642 | 1(Win) |
| jsonifier | 2783.48 | 0.883806 | 28.7364ms | 346753 | 30 | 3.30751e+07 | 118804 | 0.837312 | 2(Loss) |
| glaze | 1585.49 | 0.394291 | 51.8313ms | 346753 | 30 | 2.02893e+07 | 208572 | 1.47055 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1069.87 | 0.606303 | 51.104ms | 233995 | 30 | 4.79788e+07 | 208581 | 2.17917 | 1(Win) |
| glaze | 954.997 | 0.538858 | 56.6482ms | 233995 | 30 | 4.7564e+07 | 233671 | 2.44159 | 2(Loss) |
| simdjson (ondemand) | 884.198 | 0.582863 | 61.1523ms | 233995 | 30 | 6.49186e+07 | 252381 | 2.63675 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2108.91 | 0.874865 | 26.1016ms | 233995 | 30 | 2.57099e+07 | 105815 | 1.10516 | 1(Win) |
| glaze | 1867.41 | 0.829356 | 29.2059ms | 233995 | 30 | 2.94671e+07 | 119500 | 1.24818 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1238.41 | 0.470334 | 64.918ms | 346753 | 30 | 4.73202e+07 | 267028 | 1.88257 | 1(Win) |
| glaze | 1206.97 | 0.347155 | 66.403ms | 346753 | 30 | 2.71403e+07 | 273982 | 1.93178 | 2(Loss) |
| jsonifier | 865.374 | 1.43287 | 90.5984ms | 346753 | 30 | 8.99426e+08 | 382135 | 2.69412 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2165.72 | 0.760737 | 36.9727ms | 346753 | 30 | 4.04788e+07 | 152693 | 1.07632 | 1(Win) |
| glaze | 1732.41 | 0.467019 | 46.9098ms | 346753 | 30 | 2.38414e+07 | 190885 | 1.34574 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2525.48 | 0.939304 | 21.812ms | 233995 | 30 | 2.06661e+07 | 88361.4 | 0.922909 | 1(Win) |
| simdjson (ondemand) | 1703.81 | 0.427665 | 31.989ms | 233995 | 30 | 9.41242e+06 | 130974 | 1.36831 | 2(Loss) |
| glaze | 1280.89 | 0.524023 | 42.2226ms | 233995 | 30 | 2.50042e+07 | 174219 | 1.82028 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2777.19 | 0.55957 | 29.0487ms | 346753 | 30 | 1.33187e+07 | 119074 | 0.839241 | 1(Win) |
| simdjson (ondemand) | 2234.37 | 0.740992 | 36.3151ms | 346753 | 30 | 3.60811e+07 | 148001 | 1.04343 | 2(Loss) |
| glaze | 1586.73 | 0.631743 | 50.3311ms | 346753 | 30 | 5.20039e+07 | 208409 | 1.46944 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1014.89 | 0.473615 | 53.7275ms | 233995 | 30 | 3.25349e+07 | 219881 | 2.29736 | 1(Win) |
| jsonifier | 947.398 | 0.590504 | 57.6856ms | 233995 | 30 | 5.80384e+07 | 235545 | 2.46097 | 2(Loss) |
| simdjson (ondemand) | 186.423 | 0.225791 | 289.635ms | 233995 | 30 | 2.19155e+08 | 1.19704e+06 | 12.509 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2268.86 | 0.95507 | 24.3099ms | 233995 | 30 | 2.64722e+07 | 98355.6 | 1.02726 | 1(Win) |
| glaze | 1850.14 | 0.680365 | 29.6733ms | 233995 | 30 | 2.02028e+07 | 120616 | 1.25989 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1213.54 | 0.442385 | 66.2516ms | 346753 | 30 | 4.35966e+07 | 272499 | 1.92133 | 1(Win) |
| jsonifier | 928.649 | 0.429954 | 86.4834ms | 346753 | 30 | 7.0324e+07 | 356097 | 2.51088 | 2(Loss) |
| simdjson (ondemand) | 269.75 | 0.112752 | 295.591ms | 346753 | 30 | 5.73176e+07 | 1.22591e+06 | 8.64498 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2491.59 | 0.688642 | 32.567ms | 346753 | 30 | 2.50608e+07 | 132722 | 0.93553 | 1(Win) |
| glaze | 1640.83 | 0.595475 | 48.7901ms | 346753 | 30 | 4.32076e+07 | 201537 | 1.42085 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 666.541 | 0.642875 | 32.9965ms | 94651 | 30 | 2.2739e+07 | 135425 | 3.4978 | 1(Tie) |
| glaze STATISTICAL TIE | 664.053 | 1.61396 | 32.4449ms | 94651 | 30 | 1.44395e+08 | 135932 | 3.51081 | 1(Tie) |
| jsonifier | 633.694 | 0.761113 | 35.1241ms | 94651 | 30 | 3.52623e+07 | 142445 | 3.67921 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2853.87 | 0.95161 | 18.2272ms | 94651 | 32 | 2.89901e+06 | 31629.4 | 0.816228 | 1(Win) |
| glaze | 2734.42 | 1.13491 | 19.3971ms | 94651 | 32 | 4.49152e+06 | 33011.1 | 0.851618 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 923.434 | 0.61385 | 34.2138ms | 136024 | 30 | 2.23083e+07 | 140478 | 2.52471 | 1(Win) |
| glaze | 845.086 | 0.480932 | 37.4817ms | 136024 | 30 | 1.635e+07 | 153502 | 2.75867 | 2(Loss) |
| jsonifier | 671.188 | 0.562608 | 46.6251ms | 136024 | 30 | 3.54713e+07 | 193273 | 3.4737 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3235.17 | 1.99779 | 9.97766ms | 136024 | 30 | 1.92513e+07 | 40097.6 | 0.720065 | 1(Win) |
| glaze | 1657.11 | 0.895367 | 18.7745ms | 136046 | 30 | 1.47432e+07 | 78294.9 | 1.40649 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 442.522 | 0.137053 | 1076.78ms | 2090234 | 30 | 1.14345e+09 | 4.50464e+06 | 5.26994 | 1(Win) |
| glaze | 354.535 | 0.114617 | 1351.49ms | 2090234 | 30 | 1.24592e+09 | 5.62258e+06 | 6.57788 | 2(Loss) |
| simdjson (ondemand) | 351.216 | 0.129542 | 1365.46ms | 2090234 | 30 | 1.62174e+09 | 5.67572e+06 | 6.64003 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 889.338 | 0.522663 | 542.386ms | 2090234 | 30 | 4.11739e+09 | 2.24145e+06 | 2.62221 | 1(Win) |
| glaze | 700.769 | 0.390972 | 681.636ms | 2090234 | 30 | 3.71068e+09 | 2.84459e+06 | 3.32786 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1037.98 | 0.116737 | 1466.91ms | 6661897 | 30 | 1.53163e+09 | 6.1208e+06 | 2.24672 | 1(Win) |
| glaze | 861.33 | 0.185594 | 1773.06ms | 6661897 | 30 | 5.6222e+09 | 7.37612e+06 | 2.70752 | 2(Loss) |
| jsonifier | 780.498 | 0.147719 | 1951.64ms | 6661897 | 30 | 4.33759e+09 | 8.14003e+06 | 2.98794 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2119.07 | 0.210347 | 725.86ms | 6661897 | 30 | 1.19316e+09 | 2.99815e+06 | 1.10051 | 1(Win) |
| glaze | 1587.63 | 0.200851 | 961.985ms | 6661897 | 30 | 1.93806e+09 | 4.00175e+06 | 1.46888 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 915.142 | 0.255186 | 126.074ms | 500299 | 30 | 5.3103e+07 | 521364 | 2.54807 | 1(Win) |
| jsonifier | 831.506 | 0.365881 | 138.037ms | 500299 | 30 | 1.3223e+08 | 573805 | 2.8044 | 2(Loss) |
| simdjson (ondemand) | 598.002 | 0.427536 | 191.48ms | 500299 | 30 | 3.49077e+08 | 797861 | 3.89946 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1817.92 | 0.556574 | 63.6398ms | 500299 | 30 | 6.40143e+07 | 262455 | 1.28253 | 1(Win) |
| jsonifier | 1785.55 | 0.465935 | 64.7738ms | 500299 | 30 | 4.65036e+07 | 267213 | 1.30582 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1533.53 | 0.735039 | 545.138ms | 1439562 | 32 | 1.38563e+09 | 895237 | 1.52062 | 1(Win) |
| glaze | 1475.26 | 0.134984 | 224.621ms | 1439562 | 30 | 4.73377e+07 | 930594 | 1.58072 | 2(Loss) |
| jsonifier | 1065.64 | 0.192215 | 310.957ms | 1439562 | 30 | 1.83965e+08 | 1.28831e+06 | 2.18836 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3406.14 | 0.429479 | 100.179ms | 1439562 | 30 | 8.98961e+07 | 403059 | 0.684582 | 1(Win) |
| glaze | 1951.1 | 0.241732 | 174.072ms | 1439584 | 30 | 8.6797e+07 | 703652 | 1.19518 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 907.316 | 1.46503 | 14.8692ms | 56369 | 30 | 2.26035e+07 | 59249.1 | 2.56863 | 1(Win) |
| glaze | 838.45 | 1.39422 | 15.8567ms | 56369 | 30 | 2.39723e+07 | 64115.5 | 2.7797 | 2(Loss) |
| simdjson (ondemand) | 709.221 | 1.05419 | 18.5254ms | 56369 | 30 | 1.91548e+07 | 75798.2 | 3.28651 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1880.35 | 1.09591 | 7.11729ms | 56369 | 30 | 2.9449e+06 | 28589.2 | 1.2386 | 1(Win) |
| jsonifier | 1715.27 | 1.91147 | 7.77014ms | 56369 | 30 | 1.07664e+07 | 31340.6 | 1.35802 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1107.59 | 0.577904 | 20.0001ms | 94370 | 30 | 6.61524e+06 | 81256.2 | 2.10456 | 1(Tie) |
| glaze STATISTICAL TIE | 1101.34 | 1.33163 | 19.8639ms | 94370 | 30 | 3.5523e+07 | 81716.7 | 2.11629 | 1(Tie) |
| jsonifier | 885.507 | 0.69159 | 25.0932ms | 94370 | 30 | 1.48219e+07 | 101635 | 2.63197 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2545.48 | 1.20039 | 8.81593ms | 94370 | 30 | 5.40378e+06 | 35356.1 | 0.915209 | 1(Win) |
| glaze | 1717.08 | 0.582573 | 13.0234ms | 94370 | 30 | 2.7971e+06 | 52413.4 | 1.35695 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 849.329 | 0.89294 | 15.3043ms | 52708 | 30 | 8.37851e+06 | 59183.5 | 2.74332 | 1(Win) |
| glaze | 712.747 | 0.981106 | 17.8053ms | 52708 | 30 | 1.43627e+07 | 70524.7 | 3.26928 | 2(Loss) |
| jsonifier | 640.402 | 2.2042 | 19.5728ms | 52708 | 30 | 8.97988e+07 | 78491.7 | 3.63781 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3016.98 | 0.145525 | 9.96489ms | 52708 | 32 | 18811.9 | 16661.1 | 0.771335 | 1(Win) |
| glaze | 2819.23 | 0.337086 | 4.67433ms | 52708 | 30 | 108367 | 17829.8 | 0.825373 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1087.2 | 1.57653 | 15.3638ms | 70103 | 30 | 2.81955e+07 | 61493.2 | 2.14283 | 1(Win) |
| glaze | 798.25 | 1.43851 | 20.612ms | 70103 | 30 | 4.35455e+07 | 83752.5 | 2.91945 | 2(Loss) |
| jsonifier | 518.006 | 1.48536 | 31.9663ms | 70103 | 30 | 1.10252e+08 | 129063 | 4.49898 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2983.63 | 0.866731 | 5.78714ms | 70103 | 30 | 1.13155e+06 | 22407.4 | 0.78033 | 1(Win) |
| glaze | 2226.97 | 2.16537 | 7.55996ms | 70103 | 30 | 1.26775e+07 | 30020.9 | 1.04552 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 671.703 | 0.2027 | 10.1281ms | 11812 | 32 | 36978.4 | 16770.5 | 3.46418 | 1(Win) |
| jsonifier | 628.964 | 1.8105 | 4.67459ms | 11812 | 30 | 3.1544e+06 | 17910.1 | 3.7003 | 2(Loss) |
| simdjson (ondemand) | 563.096 | 0.112636 | 5.22192ms | 11812 | 30 | 15232.1 | 20005.1 | 4.13361 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2555.36 | 0.121908 | 1.33375ms | 11812 | 30 | 866.424 | 4408.3 | 0.905184 | 1(Win) |
| glaze | 1262.11 | 0.142801 | 2.4854ms | 11812 | 30 | 4873.49 | 8925.4 | 1.83999 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1325.87 | 1.80829 | 5.71767ms | 31235 | 30 | 4.95148e+06 | 22466.7 | 1.75601 | 1(Win) |
| glaze | 1118.75 | 1.10742 | 6.76288ms | 31235 | 30 | 2.60836e+06 | 26626.2 | 2.08158 | 2(Loss) |
| jsonifier | 882.87 | 1.27895 | 8.65072ms | 31235 | 30 | 5.5862e+06 | 33740 | 2.63854 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2914.6 | 0.0767068 | 6.21327ms | 31235 | 32 | 1966.72 | 10220.3 | 0.797297 | 1(Win) |
| glaze | 1871.21 | 0.92892 | 19.5681ms | 31235 | 64 | 1.39951e+06 | 15919.1 | 1.24332 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1695.62 | 0.996154 | 15.2634ms | 108313 | 30 | 1.10479e+07 | 60919.1 | 1.37443 | 1(Win) |
| glaze | 952.164 | 1.26422 | 26.5042ms | 108313 | 30 | 5.6429e+07 | 108485 | 2.44787 | 2(Loss) |
| simdjson (ondemand) | 840.559 | 0.74786 | 29.7499ms | 108313 | 30 | 2.53389e+07 | 122889 | 2.77313 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1934.84 | 1.45845 | 13.083ms | 108313 | 30 | 1.81875e+07 | 53387.1 | 1.20443 | 1(Win) |
| glaze | 1715.53 | 1.2555 | 14.6413ms | 108313 | 30 | 1.71441e+07 | 60211.7 | 1.35835 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1535.04 | 0.659483 | 32.3132ms | 213963 | 30 | 2.3055e+07 | 132929 | 1.51842 | 1(Win) |
| glaze | 1315.57 | 0.715934 | 37.6815ms | 213963 | 30 | 3.6993e+07 | 155105 | 1.77199 | 2(Loss) |
| jsonifier | 1032.87 | 1.57531 | 47.5972ms | 213963 | 30 | 2.90562e+08 | 197557 | 2.25679 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3166.58 | 0.789683 | 15.7918ms | 213963 | 30 | 7.76823e+06 | 64438.9 | 0.736036 | 1(Win) |
| glaze | 1618.31 | 0.720614 | 30.6997ms | 213963 | 30 | 2.47676e+07 | 126089 | 1.44043 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 438.366 | 0.0907994 | 963.698ms | 1834197 | 30 | 3.93827e+08 | 3.99033e+06 | 5.31982 | 1(Win) |
| glaze | 328.83 | 2.27564 | 1248.4ms | 1834197 | 30 | 4.39617e+11 | 5.31954e+06 | 7.09204 | 2(Loss) |
| simdjson (ondemand) | 288.006 | 0.0829019 | 1458.6ms | 1834197 | 30 | 7.60568e+08 | 6.07357e+06 | 8.0973 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 550.948 | 0.136109 | 765.259ms | 1834197 | 30 | 5.60228e+08 | 3.17494e+06 | 4.23283 | 1(Win) |
| glaze | 353.611 | 0.0735959 | 1184.78ms | 1833577 | 30 | 3.97353e+08 | 4.94509e+06 | 6.59506 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1350.07 | 0.084527 | 1689.97ms | 9930848 | 30 | 1.05481e+09 | 7.01506e+06 | 1.72737 | 1(Win) |
| glaze | 1231.08 | 0.132567 | 1847.73ms | 9930848 | 30 | 3.12028e+09 | 7.69311e+06 | 1.89435 | 2(Loss) |
| jsonifier | 1085.61 | 0.734961 | 2074.61ms | 9930848 | 30 | 1.23331e+11 | 8.72391e+06 | 2.14816 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2026.43 | 0.487661 | 1120.19ms | 9930848 | 30 | 1.55836e+10 | 4.67363e+06 | 1.1508 | 1(Win) |
| glaze | 1202.09 | 0.233475 | 1891.59ms | 9930228 | 30 | 1.01496e+10 | 7.87812e+06 | 1.93992 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 804.101 | 0.197492 | 184.004ms | 642697 | 30 | 6.7985e+07 | 762247 | 2.90001 | 1(Win) |
| glaze | 656.238 | 0.284315 | 224.761ms | 642697 | 30 | 2.11549e+08 | 933996 | 3.5535 | 2(Loss) |
| simdjson (ondemand) | 601.71 | 0.14782 | 245.754ms | 642697 | 30 | 6.80185e+07 | 1.01864e+06 | 3.87555 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 873.275 | 0.216885 | 168.986ms | 642697 | 30 | 6.95168e+07 | 701868 | 2.67029 | 1(Win) |
| glaze | 602.122 | 0.116505 | 245.078ms | 642692 | 30 | 4.21935e+07 | 1.01793e+06 | 3.87285 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1107.93 | 0.199136 | 253.615ms | 1225964 | 30 | 1.3248e+08 | 1.05528e+06 | 2.1048 | 1(Win) |
| glaze | 974.351 | 0.188034 | 287.826ms | 1225964 | 30 | 1.52728e+08 | 1.19995e+06 | 2.39336 | 2(Loss) |
| jsonifier | 843.599 | 0.186286 | 335.166ms | 1225964 | 30 | 1.99969e+08 | 1.38593e+06 | 2.76433 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1534.84 | 0.315402 | 182.628ms | 1225964 | 30 | 1.73173e+08 | 761755 | 1.5193 | 1(Win) |
| glaze | 966.55 | 0.169763 | 290.29ms | 1225970 | 30 | 1.26509e+08 | 1.20964e+06 | 2.41272 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 521.239 | 0.202088 | 180.936ms | 409725 | 30 | 6.88516e+07 | 749645 | 4.47385 | 1(Win) |
| simdjson (ondemand) | 512.492 | 0.17198 | 183.04ms | 409725 | 30 | 5.1581e+07 | 762440 | 4.55024 | 2(Loss) |
| glaze | 402.354 | 0.334062 | 230.597ms | 409725 | 30 | 3.15752e+08 | 971146 | 5.79395 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1405.94 | 0.409271 | 67.4553ms | 409725 | 30 | 3.88147e+07 | 277924 | 1.65839 | 1(Win) |
| jsonifier | 1356.26 | 0.408416 | 69.4256ms | 409725 | 30 | 4.15362e+07 | 288104 | 1.71915 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 941.05 | 0.165639 | 192.593ms | 785750 | 30 | 5.21901e+07 | 796291 | 2.47804 | 1(Win) |
| glaze | 665.049 | 0.214857 | 634.973ms | 785750 | 32 | 1.87547e+08 | 1.12676e+06 | 3.50649 | 2(Loss) |
| jsonifier | 614.158 | 0.0984697 | 294.24ms | 785750 | 30 | 4.33048e+07 | 1.22013e+06 | 3.7971 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2010.49 | 0.358574 | 90.2852ms | 785750 | 30 | 5.35851e+07 | 372720 | 1.15975 | 1(Win) |
| glaze | 1486.83 | 0.419103 | 121.593ms | 785750 | 30 | 1.33848e+08 | 503992 | 1.56833 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 687.319 | 0.237569 | 2879.58ms | 8587914 | 30 | 2.40414e+10 | 1.1916e+07 | 3.39296 | 1(Win) |
| jsonifier | 665.794 | 0.374775 | 2969.8ms | 8587914 | 30 | 6.37616e+10 | 1.23012e+07 | 3.50258 | 2(Loss) |
| glaze | 620.458 | 0.545589 | 3176.33ms | 8587914 | 30 | 1.55598e+11 | 1.32e+07 | 3.75864 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2147.03 | 0.352454 | 913.68ms | 8588126 | 30 | 5.42308e+09 | 3.8147e+06 | 1.08612 | 1(Win) |
| jsonifier | 2048.23 | 0.506357 | 935.041ms | 8588126 | 30 | 1.22992e+10 | 3.99871e+06 | 1.13849 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 769.209 | 0.401442 | 2917.06ms | 9804437 | 30 | 7.1437e+10 | 1.21557e+07 | 3.03174 | 1(Win) |
| glaze | 660.07 | 0.441306 | 3408.48ms | 9804437 | 30 | 1.17237e+11 | 1.41655e+07 | 3.53306 | 2(Loss) |
| jsonifier | 596.423 | 0.810783 | 3717.46ms | 9804437 | 30 | 4.84693e+11 | 1.56772e+07 | 3.91007 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2450.35 | 0.165094 | 1047.08ms | 11078090 | 30 | 1.52005e+09 | 4.31159e+06 | 0.951698 | 1(Win) |
| glaze | 1846.85 | 0.289855 | 1366.46ms | 11078090 | 30 | 8.24798e+09 | 5.72049e+06 | 1.26268 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2632.6 | 0.610603 | 23.3452ms | 264040 | 30 | 1.02332e+07 | 95650.1 | 0.885281 | 1(Win) |
| jsonifier | 2501.86 | 1.10056 | 24.8598ms | 264040 | 30 | 3.68099e+07 | 100648 | 0.931484 | 2(Loss) |
| glaze | 1043.18 | 0.491524 | 58.428ms | 264040 | 30 | 4.22314e+07 | 241386 | 2.23518 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3410.61 | 0.979371 | 27.0044ms | 399947 | 30 | 3.59879e+07 | 111833 | 0.683363 | 1(Win) |
| jsonifier | 2856.16 | 0.814811 | 32.5136ms | 399947 | 30 | 3.55202e+07 | 133543 | 0.816097 | 2(Loss) |
| glaze | 1296.84 | 0.505118 | 71.1414ms | 399947 | 30 | 6.62122e+07 | 294114 | 1.79797 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 880.225 | 0.686938 | 69.0914ms | 264040 | 30 | 1.15854e+08 | 286073 | 2.64838 | 1(Win) |
| simdjson (ondemand) | 856.676 | 0.526175 | 71.3477ms | 264040 | 30 | 7.1761e+07 | 293936 | 2.72168 | 2(Loss) |
| glaze | 765.649 | 1.81968 | 77.7463ms | 264040 | 30 | 1.07446e+09 | 328882 | 3.04523 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2266.41 | 0.770109 | 28.0225ms | 264040 | 30 | 2.19628e+07 | 111104 | 1.02839 | 1(Tie) |
| glaze STATISTICAL TIE | 2251.64 | 0.980129 | 28.0944ms | 263923 | 30 | 3.60117e+07 | 111784 | 1.03515 | 1(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1267.57 | 0.888425 | 73.1121ms | 399947 | 30 | 2.14398e+08 | 300905 | 1.8394 | 1(Win) |
| glaze | 950.433 | 0.6688 | 96.2082ms | 399947 | 30 | 2.16111e+08 | 401311 | 2.45334 | 2(Loss) |
| jsonifier | 653.089 | 1.62959 | 139.317ms | 399947 | 30 | 2.71729e+09 | 584023 | 3.5703 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3109.19 | 0.788742 | 30.0179ms | 399947 | 30 | 2.80867e+07 | 122675 | 0.749675 | 1(Win) |
| glaze | 2061.82 | 0.845348 | 44.673ms | 399830 | 30 | 7.3323e+07 | 184937 | 1.13068 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1390.66 | 0.370568 | 77.6702ms | 466906 | 30 | 4.2235e+07 | 320190 | 1.67664 | 1(Win) |
| glaze | 1318.53 | 0.482093 | 81.0755ms | 466906 | 30 | 7.95171e+07 | 337706 | 1.76841 | 2(Loss) |
| simdjson (ondemand) | 669.881 | 0.208595 | 161.769ms | 466906 | 30 | 5.76756e+07 | 664710 | 3.48101 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2047.19 | 0.506421 | 78.6219ms | 699405 | 30 | 8.16743e+07 | 325815 | 1.13891 | 1(Win) |
| glaze | 1668.64 | 0.325459 | 96.6671ms | 699405 | 30 | 5.07749e+07 | 399730 | 1.39743 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1659.13 | 0.407764 | 89.1201ms | 631514 | 30 | 6.57273e+07 | 362997 | 1.40541 | 1(Win) |
| glaze | 1542.14 | 0.400951 | 94.489ms | 631514 | 30 | 7.35568e+07 | 390535 | 1.51206 | 2(Loss) |
