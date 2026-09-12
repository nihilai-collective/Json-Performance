# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Sep 11, 2026)
#### Using the following commits:
----
| Jsonifier: [9a2d193](https://github.com/nihilai-collective/jsonifier/commit/9a2d193)  
| Glaze: [52fb059](https://github.com/stephenberry/glaze/commit/52fb059)  
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

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1021.58 | 0.309657 | 3.2615ms | 1811 | 32 | 877.016 | 1690.62 | 2.91954 | 1(Win) |
| glaze | 334.278 | 1.50018 | 2.7694ms | 1811 | 30 | 180230 | 5166.67 | 9.03619 | 2(Loss) |
| simdjson (ondemand) | 171.438 | 1.4976 | 29.4724ms | 1811 | 128 | 2.91358e+06 | 10074.2 | 17.6826 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 570.629 | 1.65337 | 2.1083ms | 1811 | 30 | 75126.4 | 3026.67 | 5.29017 | 1(Win) |
| glaze | 363.542 | 1.33349 | 2.5408ms | 1798 | 30 | 118678 | 4716.67 | 8.3178 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2114.65 | 0.530388 | 1.8678ms | 3873 | 30 | 2574.71 | 1746.67 | 1.42173 | 1(Win) |
| glaze | 1285.47 | 1.27009 | 1.9223ms | 3873 | 30 | 39954 | 2873.33 | 2.34181 | 2(Loss) |
| simdjson (ondemand) | 374.349 | 0.826579 | 3.6479ms | 3873 | 30 | 199540 | 9866.67 | 8.09657 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2994.8 | 0.709765 | 1.6339ms | 3873 | 30 | 2298.85 | 1233.33 | 0.979155 | 1(Win) |
| glaze | 1263.48 | 0.314773 | 2.0058ms | 3873 | 30 | 2540.23 | 2923.33 | 2.38657 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2182.57 | 0.351993 | 3.2161ms | 3862 | 32 | 1129.03 | 1687.5 | 1.3709 | 1(Win) |
| glaze | 1302.98 | 0.29051 | 2.1497ms | 3862 | 30 | 2022.99 | 2826.67 | 2.30545 | 2(Loss) |
| simdjson (ondemand) | 361.836 | 0.912272 | 29.7509ms | 3862 | 128 | 1.10372e+06 | 10178.9 | 8.37286 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2790.22 | 0.562713 | 1.6224ms | 3862 | 30 | 1655.17 | 1320 | 1.06048 | 1(Win) |
| glaze | 1255.6 | 0.298424 | 1.9729ms | 3862 | 30 | 2298.85 | 2933.33 | 2.39207 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1550.43 | 1.65303 | 1.5183ms | 905 | 30 | 2540.23 | 556.667 | 1.87834 | 1(Win) |
| glaze | 376.341 | 0.201979 | 2.0072ms | 905 | 30 | 643.678 | 2293.33 | 7.94317 | 2(Loss) |
| simdjson (ondemand) | 143.686 | 0.110988 | 2.68ms | 905 | 30 | 1333.33 | 6006.67 | 21.0979 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 782.243 | 0.302115 | 1.617ms | 905 | 30 | 333.333 | 1103.33 | 3.82232 | 1(Win) |
| glaze | 359.615 | 0.346023 | 1.8274ms | 905 | 30 | 2068.97 | 2400 | 8.36983 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2300.83 | 2.02864 | 2.659ms | 9578 | 30 | 194586 | 3970 | 1.3045 | 1(Win) |
| glaze | 1912.27 | 0.164425 | 2.3621ms | 9578 | 30 | 1850.57 | 4776.67 | 1.58377 | 2(Loss) |
| simdjson (ondemand) | 816.534 | 0.102626 | 4.5271ms | 9578 | 30 | 3954.02 | 11186.7 | 3.71433 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4676.26 | 0.474272 | 2ms | 9578 | 30 | 2574.71 | 1953.33 | 0.639312 | 1(Win) |
| glaze | 3227.67 | 0.300694 | 1.9622ms | 9578 | 30 | 2172.41 | 2830 | 0.934301 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3971.44 | 1.48122 | 15.4073ms | 233995 | 30 | 2.07816e+07 | 56190 | 0.764996 | 1(Win) |
| glaze | 1726.18 | 0.744721 | 34.5567ms | 233995 | 30 | 2.78067e+07 | 129277 | 1.7604 | 2(Loss) |
| simdjson (ondemand) | 1302.82 | 1.02065 | 44.0948ms | 233995 | 30 | 9.16909e+07 | 171287 | 2.33265 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5004.38 | 1.72362 | 17.3039ms | 346753 | 30 | 3.89175e+07 | 66080 | 0.607162 | 1(Win) |
| glaze | 2208.62 | 1.90781 | 182.067ms | 346753 | 64 | 5.22216e+08 | 149727 | 1.37579 | 2(Loss) |
| simdjson (ondemand) | 1805.14 | 2.4848 | 46.0411ms | 346753 | 30 | 6.21619e+08 | 183193 | 1.68337 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1720.27 | 1.84558 | 339.294ms | 233995 | 128 | 7.33662e+08 | 129721 | 1.76612 | 1(Win) |
| glaze | 1252.23 | 1.19095 | 53.5382ms | 233995 | 30 | 1.35131e+08 | 178207 | 2.42659 | 2(Loss) |
| simdjson (ondemand) | 781.886 | 1.75368 | 345.255ms | 233995 | 64 | 1.60328e+09 | 285406 | 3.88651 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3367.9 | 2.25161 | 359.944ms | 233995 | 256 | 5.69797e+08 | 66259.4 | 0.901879 | 1(Win) |
| glaze | 3023.92 | 1.54252 | 455.501ms | 233995 | 256 | 3.31719e+08 | 73796.5 | 1.00465 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1958.66 | 2.1889 | 99.2367ms | 346753 | 32 | 4.37041e+08 | 168834 | 1.55148 | 1(Win) |
| glaze | 1603.22 | 1.88073 | 120.079ms | 346753 | 32 | 4.81569e+08 | 206266 | 1.89529 | 2(Loss) |
| simdjson (ondemand) | 1113.58 | 2.32481 | 361.624ms | 346753 | 64 | 3.05037e+09 | 296961 | 2.72905 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4916.86 | 1.48797 | 42.9949ms | 346753 | 32 | 3.20483e+07 | 67256.2 | 0.617745 | 1(Win) |
| glaze | 2410.55 | 2.40285 | 1408.96ms | 346753 | 512 | 5.56327e+09 | 137184 | 1.26023 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3639.91 | 1.59869 | 77.7294ms | 233995 | 64 | 6.14807e+07 | 61307.8 | 0.834543 | 1(Win) |
| glaze | 1733.2 | 1.26289 | 33.25ms | 233995 | 30 | 7.93171e+07 | 128753 | 1.75317 | 2(Loss) |
| simdjson (ondemand) | 645.597 | 2.11266 | 85.9374ms | 233995 | 30 | 1.59981e+09 | 345657 | 4.70751 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4967.17 | 0.982242 | 41.7378ms | 346753 | 32 | 1.36839e+07 | 66575 | 0.611623 | 1(Win) |
| glaze | 2307.51 | 0.719494 | 37.9174ms | 346753 | 30 | 3.18954e+07 | 143310 | 1.31664 | 2(Loss) |
| simdjson (ondemand) | 909.276 | 2.0999 | 445.403ms | 346753 | 64 | 3.73273e+09 | 363684 | 3.34211 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1734.41 | 0.951705 | 35.5297ms | 233995 | 30 | 4.49817e+07 | 128663 | 1.75198 | 1(Win) |
| glaze | 1286.47 | 1.82834 | 214.209ms | 233995 | 64 | 6.43731e+08 | 173462 | 2.36217 | 2(Loss) |
| simdjson (ondemand) | 53.0686 | 1.2856 | 1014.8ms | 233995 | 30 | 8.76742e+10 | 4.20503e+06 | 57.2732 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3857.37 | 2.04084 | 74.6254ms | 233995 | 64 | 8.92133e+07 | 57851.6 | 0.787454 | 1(Win) |
| glaze | 2541.31 | 2.40762 | 894.335ms | 233995 | 512 | 2.28847e+09 | 87811.1 | 1.19533 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1854.99 | 2.24273 | 221.947ms | 346753 | 64 | 1.02304e+09 | 178270 | 1.6382 | 1(Win) |
| glaze | 1660.03 | 0.923172 | 51.3605ms | 346753 | 30 | 1.0146e+08 | 199207 | 1.83065 | 2(Loss) |
| simdjson (ondemand) | 77.2359 | 0.866351 | 1017.83ms | 346753 | 30 | 4.12773e+10 | 4.28155e+06 | 39.3516 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4822.42 | 1.58779 | 18.7658ms | 346753 | 30 | 3.55648e+07 | 68573.3 | 0.63006 | 1(Win) |
| glaze | 2354.92 | 2.11289 | 1436.51ms | 346753 | 512 | 4.50723e+09 | 140425 | 1.28975 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 777.069 | 2.32792 | 144.628ms | 94651 | 64 | 4.68004e+08 | 116162 | 3.90959 | 1(Win) |
| glaze | 652.238 | 2.19655 | 346.825ms | 94651 | 128 | 1.18285e+09 | 138395 | 4.65825 | 2(Loss) |
| simdjson (ondemand) | 572.585 | 1.74368 | 396.162ms | 94651 | 128 | 9.67199e+08 | 157647 | 5.3068 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4419.4 | 1.78921 | 29.3377ms | 94651 | 64 | 8.5473e+06 | 20425 | 0.686783 | 1(Win) |
| jsonifier | 4143.19 | 2.02929 | 7.0682ms | 94651 | 30 | 5.86395e+06 | 21786.7 | 0.73281 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1020.78 | 1.7171 | 159.013ms | 136024 | 64 | 3.04745e+08 | 127081 | 2.97651 | 1(Win) |
| glaze STATISTICAL TIE | 886.921 | 2.36586 | 363.61ms | 136024 | 128 | 1.53268e+09 | 146262 | 3.42578 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 858.844 | 2.34471 | 38.7944ms | 136024 | 30 | 3.76273e+08 | 151043 | 3.53756 | 2(Tie) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4943.07 | 1.45572 | 8.1633ms | 136024 | 30 | 4.3784e+06 | 26243.3 | 0.614459 | 1(Win) |
| glaze | 3741.88 | 1.44242 | 10.3173ms | 136046 | 30 | 7.50409e+06 | 34673.3 | 0.81157 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 593.051 | 1.81105 | 1913.53ms | 2090234 | 32 | 1.18581e+11 | 3.36127e+06 | 5.1246 | 1(Win) |
| glaze | 352.14 | 1.1024 | 1363.54ms | 2090234 | 30 | 1.16831e+11 | 5.66083e+06 | 8.63064 | 2(Loss) |
| simdjson (ondemand) | 339.565 | 0.880884 | 1388.72ms | 2090234 | 30 | 8.02236e+10 | 5.87045e+06 | 8.94938 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 989.079 | 0.617708 | 485.878ms | 2090234 | 30 | 4.6496e+09 | 2.01541e+06 | 3.07252 | 1(Win) |
| glaze | 738.397 | 0.94498 | 634.7ms | 2090234 | 30 | 1.95244e+10 | 2.69964e+06 | 4.11586 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1442.22 | 1.80032 | 1026.2ms | 6661897 | 30 | 1.88694e+11 | 4.40522e+06 | 2.10732 | 1(Win) |
| simdjson (ondemand) | 1032.9 | 1.49783 | 1428.53ms | 6661897 | 30 | 2.54636e+11 | 6.15089e+06 | 2.94228 | 2(Loss) |
| glaze | 953.818 | 1.19464 | 1563.26ms | 6661897 | 30 | 1.89961e+11 | 6.6609e+06 | 3.18642 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1853.39 | 1.28122 | 808.263ms | 6661897 | 30 | 5.78667e+10 | 3.42793e+06 | 1.63978 | 1(Win) |
| glaze | 1134.96 | 1.88557 | 1342.02ms | 6661897 | 30 | 3.34222e+11 | 5.59778e+06 | 2.67769 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1291.36 | 1.31522 | 448.385ms | 500299 | 64 | 1.51126e+09 | 369472 | 2.35311 | 1(Win) |
| glaze | 885.106 | 0.307708 | 132.648ms | 500299 | 30 | 8.25405e+07 | 539057 | 3.4336 | 2(Loss) |
| simdjson (ondemand) | 471.224 | 1.84992 | 242.022ms | 500299 | 30 | 1.05253e+10 | 1.01252e+06 | 6.44913 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4845.19 | 1.56449 | 25.561ms | 500299 | 30 | 7.12041e+07 | 98473.3 | 0.626905 | 1(Win) |
| glaze | 4255.75 | 1.43025 | 66.3353ms | 500299 | 32 | 8.22779e+07 | 112112 | 0.713756 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2451.19 | 1.86943 | 136.796ms | 1439562 | 30 | 3.28887e+09 | 560083 | 1.23847 | 1(Win) |
| glaze | 1854.2 | 1.05618 | 180.145ms | 1439562 | 30 | 1.8346e+09 | 740413 | 1.63885 | 2(Loss) |
| simdjson (ondemand) | 1305.58 | 0.998235 | 258.216ms | 1439562 | 30 | 3.30553e+09 | 1.05154e+06 | 2.32758 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2741.03 | 1.08596 | 118.826ms | 1439562 | 30 | 8.87531e+08 | 500860 | 1.10825 | 1(Win) |
| glaze | 1349.26 | 0.947747 | 256.525ms | 1439584 | 30 | 2.7899e+09 | 1.01752e+06 | 2.25198 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1247.03 | 1.64884 | 227.076ms | 56369 | 256 | 1.29338e+08 | 43108.6 | 2.43553 | 1(Win) |
| glaze | 1175.03 | 1.36316 | 13.1391ms | 56369 | 30 | 1.16681e+07 | 45750 | 2.58498 | 2(Loss) |
| simdjson (ondemand) | 611.369 | 1.80031 | 23.1054ms | 56369 | 30 | 7.5178e+07 | 87930 | 4.96964 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4954.62 | 0.0963102 | 4.0052ms | 56369 | 30 | 3275.86 | 10850 | 0.611569 | 1(Win) |
| glaze | 4138.19 | 0.52003 | 9.2109ms | 56369 | 32 | 146038 | 12990.6 | 0.733087 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1665.81 | 1.46755 | 14.929ms | 94370 | 30 | 1.88593e+07 | 54026.7 | 1.82417 | 1(Win) |
| jsonifier | 1535.63 | 0.238226 | 15.7668ms | 94370 | 30 | 584782 | 58606.7 | 1.97798 | 2(Loss) |
| simdjson (ondemand) | 1029.29 | 0.780165 | 53.5216ms | 94370 | 32 | 1.48908e+07 | 87437.5 | 2.95203 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6487.14 | 0.684196 | 4.6773ms | 94370 | 30 | 270299 | 13873.3 | 0.467591 | 1(Win) |
| glaze | 3475.1 | 1.06585 | 1079.23ms | 94370 | 2048 | 1.56046e+08 | 25898 | 0.873723 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1216.71 | 0.677728 | 223.1ms | 52708 | 256 | 2.00692e+07 | 41313.3 | 2.49604 | 1(Win) |
| glaze | 946.575 | 1.18276 | 14.6793ms | 52708 | 30 | 1.18348e+07 | 53103.3 | 3.2093 | 2(Loss) |
| simdjson (ondemand) | 802.002 | 1.97741 | 647.39ms | 52708 | 512 | 7.86442e+08 | 62676 | 3.78793 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5531.36 | 0.500848 | 7.2468ms | 52708 | 32 | 66290.3 | 9087.5 | 0.547799 | 1(Win) |
| glaze | 4684.65 | 0.701061 | 4.5582ms | 52708 | 30 | 169759 | 10730 | 0.647029 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1257.27 | 0.962179 | 33.7681ms | 70103 | 32 | 8.37677e+06 | 53175 | 2.41539 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1103.28 | 1.13705 | 37.2402ms | 70103 | 32 | 1.51919e+07 | 60596.9 | 2.7532 | 2(Tie) |
| glaze STATISTICAL TIE | 1099.39 | 1.6667 | 318.321ms | 70103 | 256 | 2.6298e+08 | 60811.3 | 2.76279 | 2(Tie) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6029.8 | 1.95709 | 16.6216ms | 70103 | 64 | 3.01349e+06 | 11087.5 | 0.502882 | 1(Win) |
| glaze | 2770.49 | 1.9384 | 14.6374ms | 70103 | 32 | 7.00157e+06 | 24131.2 | 1.09562 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1068.43 | 0.180093 | 4.3084ms | 11812 | 30 | 10816.1 | 10543.3 | 2.84065 | 1(Win) |
| glaze | 712.361 | 2.36278 | 5.0292ms | 11812 | 30 | 4.18809e+06 | 15813.3 | 4.26058 | 2(Loss) |
| simdjson (ondemand) | 494.748 | 1.89291 | 14.8178ms | 11812 | 32 | 5.94415e+06 | 22768.8 | 6.13778 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4172.15 | 0.251135 | 1.9785ms | 11812 | 30 | 1379.31 | 2700 | 0.721303 | 1(Win) |
| glaze | 3281.01 | 0.254964 | 2.1926ms | 11812 | 30 | 2298.85 | 3433.33 | 0.922553 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1835.37 | 1.43973 | 5.9751ms | 31235 | 30 | 1.63803e+06 | 16230 | 1.65367 | 1(Win) |
| glaze | 1498.53 | 2.00715 | 13.6883ms | 31235 | 32 | 5.09402e+06 | 19878.1 | 2.02611 | 2(Loss) |
| simdjson (ondemand) | 1249.63 | 1.82905 | 16.0013ms | 31235 | 32 | 6.08306e+06 | 23837.5 | 2.43052 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6609.77 | 0.236304 | 2.3913ms | 31235 | 30 | 3402.3 | 4506.67 | 0.456308 | 1(Win) |
| glaze | 4160.25 | 1.04503 | 42.8014ms | 31235 | 256 | 1.43331e+06 | 7160.16 | 0.727932 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2325.95 | 2.43176 | 12.2644ms | 108313 | 30 | 3.49885e+07 | 44410 | 1.30569 | 1(Win) |
| glaze | 1203.34 | 0.858881 | 51.5797ms | 108313 | 32 | 1.73941e+07 | 85840.6 | 2.52521 | 2(Loss) |
| simdjson (ondemand) | 689.509 | 1.42761 | 39.7006ms | 108313 | 30 | 1.37222e+08 | 149810 | 4.40716 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4590.22 | 2.07969 | 6.4681ms | 108313 | 30 | 6.57068e+06 | 22503.3 | 0.661117 | 1(Win) |
| glaze | 4294.43 | 0.809876 | 7.3852ms | 108313 | 30 | 1.13844e+06 | 24053.3 | 0.70663 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2012.07 | 1.25498 | 26.8825ms | 213963 | 30 | 4.85943e+07 | 101413 | 1.50952 | 1(Win) |
| glaze | 1898.81 | 1.14892 | 66.8799ms | 213963 | 32 | 4.87805e+07 | 107462 | 1.60027 | 2(Loss) |
| simdjson (ondemand) | 1247.92 | 1.3206 | 41.8023ms | 213963 | 30 | 1.39884e+08 | 163513 | 2.42748 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6360.69 | 1.61169 | 8.8052ms | 213963 | 30 | 8.01959e+06 | 32080 | 0.477471 | 1(Win) |
| glaze | 3422.72 | 2.34409 | 15.9542ms | 213963 | 30 | 5.85876e+07 | 59616.7 | 0.887805 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 585.69 | 1.80404 | 701.117ms | 1834197 | 30 | 8.70905e+10 | 2.98661e+06 | 5.18816 | 1(Win) |
| simdjson (ondemand) | 280.713 | 1.5027 | 1465.32ms | 1834197 | 30 | 2.63045e+11 | 6.23136e+06 | 10.8264 | 2(Loss) |
| glaze | 260.699 | 1.51385 | 1612.25ms | 1834197 | 30 | 3.09526e+11 | 6.70974e+06 | 11.6567 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 614.592 | 1.77314 | 673.391ms | 1834197 | 30 | 7.6406e+10 | 2.84616e+06 | 4.94453 | 1(Win) |
| glaze | 492.833 | 1.47221 | 863.963ms | 1833577 | 30 | 8.18579e+10 | 3.54813e+06 | 6.16653 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2083.94 | 1.63446 | 1101.21ms | 9930848 | 30 | 1.65528e+11 | 4.54466e+06 | 1.45834 | 1(Win) |
| simdjson (ondemand) | 1423.25 | 1.18145 | 1604.29ms | 9930848 | 30 | 1.85422e+11 | 6.65435e+06 | 2.13534 | 2(Loss) |
| glaze | 1249.59 | 1.03598 | 1829.08ms | 9930848 | 30 | 1.84956e+11 | 7.57915e+06 | 2.43213 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1706.41 | 1.04272 | 1336.59ms | 9930848 | 30 | 1.00476e+11 | 5.55011e+06 | 1.78102 | 1(Win) |
| glaze | 847.042 | 0.787945 | 2721.37ms | 9930228 | 30 | 2.32821e+11 | 1.11803e+07 | 3.58805 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1338.91 | 0.455075 | 113.184ms | 642697 | 30 | 1.30195e+08 | 457777 | 2.26941 | 1(Win) |
| simdjson (ondemand) | 741.553 | 2.2843 | 195.029ms | 642697 | 30 | 1.06943e+10 | 826540 | 4.09775 | 2(Loss) |
| glaze | 623.992 | 2.14828 | 542.241ms | 642697 | 32 | 1.42491e+10 | 982262 | 4.8693 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1310.57 | 1.71449 | 270.083ms | 642697 | 32 | 2.05739e+09 | 467678 | 2.31863 | 1(Win) |
| glaze | 543.784 | 1.91196 | 263.713ms | 642692 | 30 | 1.39325e+10 | 1.12714e+06 | 5.58769 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1904.4 | 0.376736 | 153.483ms | 1225964 | 30 | 1.60484e+08 | 613930 | 1.59563 | 1(Win) |
| simdjson (ondemand) | 1389.43 | 1.92989 | 203.471ms | 1225964 | 30 | 7.91175e+09 | 841477 | 2.18703 | 2(Loss) |
| glaze | 1132.67 | 1.97415 | 250.941ms | 1225964 | 30 | 1.24575e+10 | 1.03223e+06 | 2.6829 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1404.05 | 2.10976 | 455.943ms | 1225964 | 32 | 9.87661e+09 | 832712 | 2.16363 | 1(Win) |
| glaze | 990.749 | 1.85872 | 282.138ms | 1225970 | 30 | 1.44339e+10 | 1.18009e+06 | 3.06703 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 844.924 | 0.304041 | 599.576ms | 409725 | 64 | 1.2653e+08 | 462461 | 3.59689 | 1(Win) |
| glaze | 518.839 | 2.27734 | 182.507ms | 409725 | 30 | 8.82465e+09 | 753113 | 5.85685 | 2(Loss) |
| simdjson (ondemand) | 481.236 | 2.28776 | 194.127ms | 409725 | 30 | 1.03517e+10 | 811960 | 6.31439 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2725.05 | 2.4909 | 36.5779ms | 409725 | 30 | 3.82712e+08 | 143390 | 1.11497 | 1(Tie) |
| glaze STATISTICAL TIE | 2631.1 | 1.05258 | 39.1828ms | 409725 | 30 | 7.33064e+07 | 148510 | 1.1543 | 1(Tie) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1239.33 | 0.299163 | 772.35ms | 785750 | 64 | 2.09407e+08 | 604641 | 2.45214 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 905.996 | 1.35011 | 198.704ms | 785750 | 30 | 3.74091e+09 | 827100 | 3.35389 | 2(Tie) |
| glaze STATISTICAL TIE | 892.701 | 1.37131 | 492.927ms | 785750 | 32 | 4.24012e+09 | 839419 | 3.40405 | 2(Tie) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4189.35 | 2.24767 | 44.9287ms | 785750 | 30 | 4.8491e+08 | 178870 | 0.725161 | 1(Win) |
| glaze | 1572.79 | 1.25778 | 117.081ms | 785750 | 30 | 1.07736e+09 | 476447 | 1.93115 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 849.023 | 1.65949 | 2438.86ms | 8587914 | 30 | 7.68786e+11 | 9.64646e+06 | 3.57963 | 1(Win) |
| glaze | 582.898 | 0.545046 | 3394.98ms | 8587914 | 30 | 1.75946e+11 | 1.40506e+07 | 5.21399 | 2(Loss) |
| simdjson (ondemand) | 557.662 | 0.705131 | 3464.02ms | 8587914 | 30 | 3.21732e+11 | 1.46864e+07 | 5.44995 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1777.02 | 1.33547 | 1095.85ms | 8588126 | 30 | 1.13659e+11 | 4.609e+06 | 1.71009 | 1(Win) |
| glaze | 997.769 | 0.976778 | 1973.47ms | 8588126 | 30 | 1.92864e+11 | 8.20859e+06 | 3.04584 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 785.813 | 1.3456 | 2918.23ms | 9804437 | 30 | 7.6906e+11 | 1.18988e+07 | 3.86761 | 1(Win) |
| glaze STATISTICAL TIE | 652.971 | 0.586086 | 3519.07ms | 9804437 | 30 | 2.11301e+11 | 1.43195e+07 | 4.65457 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 642.153 | 0.807253 | 3352.92ms | 9804437 | 30 | 4.14484e+11 | 1.45608e+07 | 4.73293 | 2(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1835.39 | 1.19873 | 1345.4ms | 11078090 | 30 | 1.42836e+11 | 5.75621e+06 | 1.65567 | 1(Win) |
| glaze | 1113.85 | 0.597627 | 2263.88ms | 11078090 | 30 | 9.63967e+10 | 9.48506e+06 | 2.72849 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4421.82 | 1.07933 | 15.9681ms | 264040 | 30 | 1.13336e+07 | 56946.7 | 0.687093 | 1(Win) |
| simdjson (ondemand) | 1853.39 | 1.05566 | 34.495ms | 264040 | 30 | 6.17127e+07 | 135863 | 1.63918 | 2(Loss) |
| glaze | 1239.54 | 1.6353 | 501.009ms | 264040 | 128 | 1.41261e+09 | 203147 | 2.45163 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5588.82 | 1.38973 | 41.756ms | 399947 | 32 | 2.87858e+07 | 68246.9 | 0.543464 | 1(Win) |
| simdjson (ondemand) | 2722.74 | 0.735439 | 37.4965ms | 399947 | 30 | 3.18426e+07 | 140087 | 1.11619 | 2(Loss) |
| glaze | 1766.8 | 0.762548 | 127.809ms | 399947 | 32 | 8.6719e+07 | 215881 | 1.71989 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1550.32 | 1.78391 | 43.8526ms | 264040 | 30 | 2.51864e+08 | 162423 | 1.95996 | 1(Win) |
| glaze | 843.115 | 2.04437 | 748.143ms | 264040 | 128 | 4.77192e+09 | 298664 | 3.60411 | 2(Loss) |
| simdjson (ondemand) | 763.294 | 1.91627 | 833.527ms | 264040 | 128 | 5.11541e+09 | 329897 | 3.98107 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5431.66 | 1.75844 | 30.9379ms | 264040 | 32 | 2.12657e+07 | 46359.4 | 0.559321 | 1(Win) |
| glaze | 3916.12 | 2.25837 | 41.671ms | 263923 | 32 | 6.74189e+07 | 64271.9 | 0.775819 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1430.97 | 2.04045 | 674.696ms | 399947 | 128 | 3.78624e+09 | 266546 | 2.11536 | 1(Win) |
| glaze STATISTICAL TIE | 1164.25 | 1.08239 | 85.25ms | 399947 | 30 | 3.77226e+08 | 327610 | 2.61011 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1117.43 | 1.91856 | 857.604ms | 399947 | 128 | 5.48937e+09 | 341335 | 2.71933 | 2(Tie) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6113.47 | 1.53551 | 17.2037ms | 399947 | 30 | 2.75333e+07 | 62390 | 0.497054 | 1(Win) |
| glaze | 3823.53 | 1.79454 | 29.0024ms | 399830 | 30 | 9.60841e+07 | 99726.7 | 0.794626 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2290.15 | 2.20687 | 115.075ms | 466906 | 32 | 5.89161e+08 | 194431 | 1.32663 | 1(Win) |
| glaze | 2081.92 | 1.3618 | 128.946ms | 466906 | 32 | 2.71462e+08 | 213878 | 1.4595 | 2(Loss) |
| simdjson (ondemand) | 1107.92 | 1.64402 | 101.102ms | 466906 | 30 | 1.30972e+09 | 401903 | 2.74223 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3184.32 | 1.06597 | 128.184ms | 699405 | 32 | 1.59538e+08 | 209466 | 0.954067 | 1(Win) |
| glaze | 2545.24 | 1.95388 | 659.702ms | 699405 | 128 | 3.35587e+09 | 262059 | 1.19395 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2644.49 | 2.10705 | 288.373ms | 631514 | 64 | 1.4737e+09 | 227741 | 1.14911 | 1(Win) |
| glaze | 2399.73 | 1.89781 | 640.505ms | 631514 | 128 | 2.90372e+09 | 250970 | 1.26633 | 2(Loss) |
