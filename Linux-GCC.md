# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

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
| jsonifier | 830.405 | 0.0541663 | 1.63689ms | 1811 | 30 | 38.0747 | 2079.83 | 2.9393 | 1(Win) |
| glaze | 570.365 | 1.65563 | 7.90321ms | 1811 | 128 | 321714 | 3028.07 | 4.29793 | 2(Loss) |
| simdjson (ondemand) | 133.96 | 1.59673 | 3.26766ms | 1811 | 30 | 1.27137e+06 | 12892.7 | 18.4393 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 531.106 | 0.121738 | 0.982439ms | 1811 | 30 | 470.162 | 3251.9 | 4.61949 | 1(Win) |
| glaze | 317.803 | 0.811607 | 1.44389ms | 1798 | 30 | 57527.6 | 5395.5 | 7.74698 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1398.06 | 0.0614614 | 1.51893ms | 3873 | 30 | 79.0989 | 2641.93 | 1.75079 | 1(Win) |
| glaze | 1259.26 | 0.0627954 | 0.886325ms | 3873 | 30 | 101.775 | 2933.13 | 1.94547 | 2(Loss) |
| simdjson (ondemand) | 306.381 | 1.60041 | 3.08734ms | 3873 | 30 | 1.11675e+06 | 12055.5 | 8.06265 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2086.38 | 0.0435302 | 0.647626ms | 3873 | 30 | 17.8161 | 1770.33 | 1.16383 | 1(Win) |
| glaze | 1016.54 | 0.586895 | 1.08951ms | 3873 | 30 | 13642.2 | 3633.47 | 2.41516 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1431.49 | 0.067534 | 0.823681ms | 3862 | 30 | 90.5759 | 2572.9 | 1.70977 | 1(Win) |
| glaze | 1102.37 | 0.0883342 | 0.95599ms | 3862 | 30 | 261.306 | 3341.07 | 2.22613 | 2(Loss) |
| simdjson (ondemand) | 300.419 | 0.0389656 | 3.14766ms | 3862 | 30 | 684.626 | 12259.8 | 8.22053 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2058.32 | 0.0681294 | 0.651341ms | 3862 | 30 | 44.5851 | 1789.37 | 1.17792 | 1(Win) |
| glaze | 1111.26 | 0.383605 | 0.97635ms | 3862 | 30 | 4849.33 | 3314.33 | 2.20751 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1093.61 | 0.0949771 | 0.375135ms | 905 | 30 | 16.8552 | 789.2 | 2.17864 | 1(Win) |
| glaze | 628.88 | 0.893017 | 0.482367ms | 905 | 30 | 4506.11 | 1372.4 | 3.85451 | 2(Loss) |
| simdjson (ondemand) | 94.1663 | 0.0477237 | 2.38845ms | 905 | 30 | 573.978 | 9165.43 | 26.204 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1023.05 | 0.0951821 | 0.387664ms | 905 | 30 | 19.3437 | 843.633 | 2.33569 | 1(Win) |
| glaze | 323.563 | 0.517408 | 1.70815ms | 905 | 32 | 6095.28 | 2667.41 | 7.56657 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1909.19 | 0.0463846 | 2.93646ms | 9578 | 32 | 157.597 | 4784.38 | 1.28873 | 1(Win) |
| jsonifier | 1404.02 | 0.0160126 | 1.80981ms | 9578 | 30 | 32.5575 | 6505.83 | 1.75251 | 2(Loss) |
| simdjson (ondemand) | 684.435 | 0.225748 | 3.42046ms | 9578 | 30 | 27230.4 | 13345.7 | 3.60945 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3935.22 | 0.111755 | 0.781146ms | 9578 | 30 | 201.868 | 2321.17 | 0.621087 | 1(Win) |
| glaze | 2160.74 | 0.513092 | 1.19656ms | 9578 | 30 | 14114.2 | 4227.4 | 1.13785 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 4061.77 | 1.15518 | 13.3933ms | 233995 | 30 | 1.20838e+07 | 54940.4 | 0.609109 | 1(Tie) |
| jsonifier STATISTICAL TIE | 4048.6 | 0.412654 | 13.672ms | 233995 | 30 | 1.55201e+06 | 55119 | 0.611194 | 1(Tie) |
| glaze | 1740.19 | 0.481949 | 31.3164ms | 233995 | 30 | 1.14589e+07 | 128236 | 1.42237 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 5111.56 | 1.11127 | 15.7711ms | 346753 | 30 | 1.55058e+07 | 64694.5 | 0.484049 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5050.63 | 0.52467 | 16.0138ms | 346753 | 30 | 3.54033e+06 | 65474.9 | 0.489965 | 1(Tie) |
| glaze | 2172.54 | 0.463186 | 36.9581ms | 346753 | 30 | 1.49121e+07 | 152213 | 1.13934 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1515.65 | 1.8071 | 36.5792ms | 233995 | 30 | 2.12373e+08 | 147234 | 1.63306 | 1(Win) |
| simdjson (ondemand) | 1416.23 | 0.546122 | 40.6533ms | 233995 | 30 | 2.2215e+07 | 157570 | 1.74771 | 2(Loss) |
| jsonifier | 1263.73 | 0.685548 | 42.9766ms | 233995 | 30 | 4.39642e+07 | 176584 | 1.95873 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3151.25 | 0.93612 | 17.3323ms | 233995 | 30 | 1.31836e+07 | 70814.9 | 0.785309 | 1(Win) |
| glaze | 2797.32 | 0.741477 | 19.4475ms | 233995 | 30 | 1.04965e+07 | 79774.5 | 0.884637 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1850.77 | 1.29198 | 41.9039ms | 346753 | 30 | 1.59871e+08 | 178677 | 1.33745 | 1(Win) |
| glaze | 1651.84 | 0.681289 | 48.5759ms | 346753 | 30 | 5.5807e+07 | 200194 | 1.49857 | 2(Loss) |
| jsonifier | 1255.92 | 0.439962 | 63.8196ms | 346753 | 30 | 4.02592e+07 | 263304 | 1.971 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3256.44 | 0.618268 | 24.9225ms | 346753 | 30 | 1.18257e+07 | 101549 | 0.760061 | 1(Win) |
| glaze | 2708.48 | 0.582478 | 29.6751ms | 346753 | 30 | 1.5173e+07 | 122094 | 0.913672 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3922.78 | 1.03118 | 13.9434ms | 233995 | 30 | 1.03232e+07 | 56886.9 | 0.630791 | 1(Win) |
| simdjson (ondemand) | 2528.55 | 0.731589 | 21.4387ms | 233995 | 30 | 1.25063e+07 | 88254.3 | 0.978813 | 2(Loss) |
| glaze | 1743.75 | 0.400983 | 31.2949ms | 233995 | 30 | 7.89983e+06 | 127974 | 1.41948 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4882.98 | 0.676464 | 16.5634ms | 346753 | 30 | 6.29624e+06 | 67722.9 | 0.506806 | 1(Win) |
| simdjson (ondemand) | 3395.34 | 0.625195 | 23.6908ms | 346753 | 30 | 1.11231e+07 | 97395.1 | 0.728933 | 2(Loss) |
| glaze | 2189.45 | 0.56691 | 36.7167ms | 346753 | 30 | 2.19948e+07 | 151038 | 1.13051 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1728.05 | 0.516084 | 32.4941ms | 233995 | 30 | 1.33249e+07 | 129137 | 1.43227 | 1(Win) |
| jsonifier | 1237.46 | 0.368165 | 44.5892ms | 233995 | 30 | 1.32238e+07 | 180333 | 2.00032 | 2(Loss) |
| simdjson (ondemand) | 232.535 | 0.350553 | 229.983ms | 233995 | 30 | 3.3952e+08 | 959663 | 10.6464 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3337.65 | 0.872624 | 16.4313ms | 233995 | 30 | 1.02119e+07 | 66860 | 0.741438 | 1(Win) |
| glaze | 2755.83 | 0.73969 | 19.7678ms | 233995 | 30 | 1.07629e+07 | 80975.6 | 0.897934 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2040.03 | 0.525211 | 40.8361ms | 346753 | 30 | 2.17449e+07 | 162100 | 1.21332 | 1(Win) |
| jsonifier | 1146.41 | 0.299072 | 70.1421ms | 346753 | 30 | 2.23271e+07 | 288456 | 2.15923 | 2(Loss) |
| simdjson (ondemand) | 340.506 | 0.931214 | 232.564ms | 346753 | 30 | 2.45364e+09 | 971170 | 7.27041 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3802.18 | 0.935973 | 21.2459ms | 346753 | 30 | 1.98803e+07 | 86973.6 | 0.65089 | 1(Win) |
| glaze | 2793.12 | 0.733296 | 28.7655ms | 346753 | 30 | 2.26121e+07 | 118394 | 0.885949 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 933.338 | 0.834554 | 23.5555ms | 94651 | 30 | 1.95435e+07 | 96713.3 | 2.65173 | 1(Win) |
| glaze | 883.46 | 0.682958 | 24.5706ms | 94651 | 30 | 1.46079e+07 | 102174 | 2.80155 | 2(Loss) |
| jsonifier | 590.829 | 0.643825 | 37.3269ms | 94651 | 30 | 2.90257e+07 | 152779 | 4.18936 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4116.91 | 1.71232 | 5.47463ms | 94651 | 30 | 4.22862e+06 | 21925.7 | 0.600544 | 1(Win) |
| glaze | 3767.87 | 2.18157 | 5.93041ms | 94651 | 30 | 8.19439e+06 | 23956.8 | 0.65627 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1332.64 | 0.312106 | 23.8534ms | 136024 | 30 | 2.76904e+06 | 97342.2 | 1.85721 | 1(Win) |
| glaze | 1166.48 | 0.691936 | 29.0299ms | 136024 | 30 | 1.77634e+07 | 111208 | 2.12175 | 2(Loss) |
| jsonifier | 721.323 | 0.707984 | 43.3913ms | 136024 | 30 | 4.86341e+07 | 179840 | 3.43139 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4517.34 | 1.79788 | 7.10129ms | 136024 | 30 | 7.9967e+06 | 28716.6 | 0.547503 | 1(Win) |
| glaze | 3435.17 | 1.06612 | 9.36535ms | 136046 | 30 | 4.8642e+06 | 37769.2 | 0.720148 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 531.458 | 0.0781817 | 901.645ms | 2090234 | 30 | 2.57979e+08 | 3.75082e+06 | 4.65832 | 1(Win) |
| simdjson (ondemand) | 459.084 | 0.124148 | 1044.19ms | 2090234 | 30 | 8.71776e+08 | 4.34213e+06 | 5.39249 | 2(Loss) |
| glaze | 437.791 | 0.0975089 | 1097.7ms | 2090234 | 30 | 5.91378e+08 | 4.55332e+06 | 5.65489 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1146.68 | 0.158634 | 416.482ms | 2090234 | 30 | 2.28149e+08 | 1.73841e+06 | 2.15899 | 1(Win) |
| glaze | 922.505 | 0.156931 | 517.031ms | 2090234 | 30 | 3.44978e+08 | 2.16086e+06 | 2.68358 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1342.05 | 0.169751 | 1141.63ms | 6661897 | 30 | 1.93733e+09 | 4.734e+06 | 1.84462 | 1(Win) |
| jsonifier | 1154.46 | 1.73279 | 1296.92ms | 6661897 | 30 | 2.72803e+11 | 5.50323e+06 | 2.14432 | 2(Loss) |
| glaze | 1112.7 | 0.107234 | 1373.36ms | 6661897 | 30 | 1.12467e+09 | 5.70979e+06 | 2.22488 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2732.14 | 0.843126 | 550.046ms | 6661897 | 30 | 1.15318e+10 | 2.32539e+06 | 0.906069 | 1(Win) |
| glaze | 2039.62 | 0.212519 | 746.061ms | 6661897 | 30 | 1.31466e+09 | 3.11493e+06 | 1.21363 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1193.98 | 0.295526 | 95.9015ms | 500299 | 30 | 4.18389e+07 | 399608 | 2.07306 | 1(Win) |
| jsonifier | 1070.96 | 0.403331 | 107.108ms | 500299 | 30 | 9.68637e+07 | 445511 | 2.31123 | 2(Loss) |
| simdjson (ondemand) | 908.216 | 0.247933 | 126.449ms | 500299 | 30 | 5.08947e+07 | 525340 | 2.72555 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3438.47 | 0.537709 | 33.9494ms | 500299 | 30 | 1.67011e+07 | 138760 | 0.719788 | 1(Win) |
| glaze | 2742.63 | 0.540358 | 42.2741ms | 500299 | 30 | 2.651e+07 | 173965 | 0.902399 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2297.5 | 0.223758 | 143.887ms | 1439562 | 30 | 5.36323e+07 | 597550 | 1.07744 | 1(Win) |
| glaze | 2023.01 | 0.313407 | 162.641ms | 1439562 | 30 | 1.35707e+08 | 678629 | 1.22363 | 2(Loss) |
| jsonifier | 1769.48 | 0.166277 | 186.47ms | 1439562 | 30 | 4.99289e+07 | 775862 | 1.39897 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5162.52 | 0.457597 | 64.3045ms | 1439562 | 30 | 4.44248e+07 | 265931 | 0.479478 | 1(Win) |
| glaze | 3382.91 | 0.248664 | 98.2161ms | 1439584 | 30 | 3.0552e+07 | 405833 | 0.731715 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1106.82 | 1.01829 | 12.0801ms | 56369 | 30 | 7.33828e+06 | 48569.5 | 2.23548 | 1(Win) |
| simdjson (ondemand) | 1039.87 | 0.783785 | 12.8169ms | 56369 | 30 | 4.92535e+06 | 51696.5 | 2.37918 | 2(Loss) |
| jsonifier | 881.849 | 0.918315 | 15.093ms | 56369 | 30 | 9.4015e+06 | 60960.2 | 2.80611 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3915.63 | 0.1409 | 3.56522ms | 56369 | 30 | 11225.9 | 13729 | 0.630985 | 1(Win) |
| glaze | 3574.39 | 1.37315 | 3.82131ms | 56369 | 30 | 1.27949e+06 | 15039.7 | 0.6913 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1681.04 | 0.960308 | 13.4428ms | 94370 | 30 | 7.92969e+06 | 53537.4 | 1.47193 | 1(Win) |
| glaze | 1490.65 | 0.964094 | 14.9079ms | 94370 | 30 | 1.01642e+07 | 60375 | 1.66004 | 2(Loss) |
| jsonifier | 1050.56 | 1.08535 | 21.2547ms | 94370 | 30 | 2.59347e+07 | 85666.7 | 2.35562 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4606.29 | 1.69958 | 4.87014ms | 94370 | 30 | 3.30802e+06 | 19538.1 | 0.536668 | 1(Win) |
| glaze | 3533.72 | 0.0696132 | 6.43444ms | 94370 | 30 | 9429.9 | 25468.4 | 0.699799 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1289.73 | 1.09008 | 9.85237ms | 52708 | 30 | 5.41499e+06 | 38974.4 | 1.91787 | 1(Win) |
| glaze | 1017.33 | 1.12948 | 12.3239ms | 52708 | 30 | 9.34342e+06 | 49409.8 | 2.43207 | 2(Loss) |
| jsonifier | 916.449 | 1.27143 | 13.828ms | 52708 | 30 | 1.45897e+07 | 54848.9 | 2.69946 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4095.85 | 0.35586 | 3.22421ms | 52708 | 30 | 57219.6 | 12272.5 | 0.602776 | 1(Win) |
| jsonifier | 3887.72 | 1.82598 | 3.35755ms | 52708 | 30 | 1.67216e+06 | 12929.5 | 0.635299 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1654.52 | 1.88101 | 9.98283ms | 70103 | 30 | 1.73315e+07 | 40407.9 | 1.49509 | 1(Win) |
| glaze | 1174.89 | 1.51922 | 14.1888ms | 70103 | 30 | 2.24201e+07 | 56903.4 | 2.10584 | 2(Loss) |
| jsonifier | 866.322 | 1.57096 | 19.3014ms | 70103 | 30 | 4.40928e+07 | 77171.5 | 2.85608 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4434.64 | 1.38257 | 3.8806ms | 70103 | 30 | 1.30333e+06 | 15075.7 | 0.557213 | 1(Win) |
| glaze | 3884.11 | 0.414422 | 4.3883ms | 70103 | 30 | 152651 | 17212.6 | 0.636298 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 889.605 | 0.172648 | 3.41586ms | 11812 | 30 | 14338.3 | 12662.7 | 2.77667 | 1(Win) |
| simdjson (ondemand) | 885.937 | 0.0695791 | 3.34363ms | 11812 | 30 | 2348.12 | 12715.1 | 2.78841 | 2(Loss) |
| jsonifier | 676.383 | 0.220625 | 4.31573ms | 11812 | 30 | 40503.4 | 16654.5 | 3.65405 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3609.32 | 0.857487 | 1.28946ms | 11812 | 30 | 21486.9 | 3121.03 | 0.679349 | 1(Win) |
| glaze | 2455.7 | 0.377196 | 1.26086ms | 11812 | 30 | 8981.54 | 4587.2 | 1.00145 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2052.99 | 1.48443 | 3.65108ms | 31235 | 30 | 1.39171e+06 | 14509.6 | 1.20348 | 1(Win) |
| glaze | 1613.5 | 0.0909493 | 4.81988ms | 31235 | 30 | 8457.98 | 18461.8 | 1.53192 | 2(Loss) |
| jsonifier | 1225.21 | 0.0955823 | 6.20834ms | 31235 | 30 | 16201 | 24312.7 | 2.01835 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4566.96 | 0.475429 | 1.75426ms | 31235 | 30 | 28848.3 | 6522.5 | 0.539644 | 1(Win) |
| glaze | 3777.68 | 0.166111 | 2.10202ms | 31235 | 30 | 5146.96 | 7885.27 | 0.652934 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2128.03 | 0.469408 | 12.0907ms | 108313 | 30 | 1.5575e+06 | 48540.4 | 1.16266 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1387.75 | 0.774524 | 18.1823ms | 108313 | 30 | 9.97082e+06 | 74433.7 | 1.78309 | 2(Tie) |
| glaze STATISTICAL TIE | 1374.16 | 0.993711 | 18.4934ms | 108313 | 30 | 1.67388e+07 | 75169.5 | 1.80091 | 2(Tie) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2459.73 | 0.858119 | 10.3563ms | 108313 | 30 | 3.89586e+06 | 41994.6 | 1.00584 | 1(Win) |
| glaze | 1891.26 | 0.404068 | 13.4917ms | 108313 | 30 | 1.46113e+06 | 54617.3 | 1.30834 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2431.74 | 0.720717 | 20.4588ms | 213963 | 30 | 1.09722e+07 | 83911.4 | 1.01774 | 1(Win) |
| glaze | 1841.1 | 0.577801 | 26.8002ms | 213963 | 30 | 1.23027e+07 | 110831 | 1.34427 | 2(Loss) |
| jsonifier | 1559.56 | 1.202 | 31.615ms | 213963 | 30 | 7.41995e+07 | 130839 | 1.58693 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3547.3 | 1.06376 | 14.252ms | 213963 | 30 | 1.12328e+07 | 57523 | 0.697584 | 1(Win) |
| glaze | 2307.93 | 0.482467 | 21.5349ms | 213963 | 30 | 5.45867e+06 | 88412.8 | 1.07225 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 548.849 | 0.83608 | 759.499ms | 1834197 | 30 | 2.13012e+10 | 3.18708e+06 | 4.51053 | 1(Win) |
| glaze | 428.264 | 0.170592 | 985.593ms | 1834197 | 30 | 1.4565e+09 | 4.08446e+06 | 5.78065 | 2(Loss) |
| simdjson (ondemand) | 419.17 | 0.0933695 | 2400.91ms | 1834197 | 32 | 4.85817e+08 | 4.17308e+06 | 5.90612 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 742.684 | 0.242865 | 566.705ms | 1834197 | 30 | 9.81598e+08 | 2.35528e+06 | 3.33346 | 1(Win) |
| glaze | 479.183 | 0.105701 | 878.765ms | 1833577 | 30 | 4.46352e+08 | 3.6492e+06 | 5.16648 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1915.97 | 0.921364 | 1183.36ms | 9930848 | 30 | 6.22267e+10 | 4.94307e+06 | 1.29208 | 1(Win) |
| jsonifier | 1719.54 | 1.80914 | 1296.61ms | 9930848 | 30 | 2.97861e+11 | 5.50776e+06 | 1.4396 | 2(Loss) |
| glaze | 1644.36 | 0.370004 | 1383.03ms | 9930848 | 30 | 1.36243e+10 | 5.75956e+06 | 1.50553 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2497.89 | 0.230041 | 894.531ms | 9930848 | 30 | 2.28222e+09 | 3.79152e+06 | 0.991035 | 1(Win) |
| glaze | 1578.46 | 0.212287 | 1429.24ms | 9930228 | 30 | 4.86655e+09 | 5.99966e+06 | 1.56831 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 986.097 | 1.07523 | 146.898ms | 642697 | 30 | 1.33999e+09 | 621565 | 2.51015 | 1(Win) |
| simdjson (ondemand) | 826.979 | 0.292341 | 179.303ms | 642697 | 30 | 1.40839e+08 | 741160 | 2.99345 | 2(Loss) |
| glaze | 774.504 | 0.384339 | 190.029ms | 642697 | 30 | 2.77533e+08 | 791376 | 3.19621 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1176.28 | 0.804525 | 304.864ms | 642697 | 32 | 5.62371e+08 | 521071 | 2.1045 | 1(Win) |
| glaze | 792.929 | 0.154552 | 186.127ms | 642692 | 30 | 4.28163e+07 | 772981 | 3.122 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1490.24 | 0.227544 | 189.737ms | 1225964 | 30 | 9.56085e+07 | 784552 | 1.66118 | 1(Win) |
| glaze | 1198.38 | 0.242939 | 235.557ms | 1225964 | 30 | 1.68531e+08 | 975626 | 2.06574 | 2(Loss) |
| jsonifier | 1032.84 | 0.288213 | 271.448ms | 1225964 | 30 | 3.19328e+08 | 1.13199e+06 | 2.3968 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2017.76 | 0.280154 | 139.552ms | 1225964 | 30 | 7.90554e+07 | 579439 | 1.22686 | 1(Win) |
| glaze | 1235.1 | 0.111659 | 227.619ms | 1225970 | 30 | 3.3517e+07 | 946624 | 2.00435 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 750.628 | 0.309348 | 125.177ms | 409725 | 30 | 7.77951e+07 | 520557 | 3.29793 | 1(Win) |
| glaze | 525.256 | 0.23422 | 183.555ms | 409725 | 30 | 9.10778e+07 | 743912 | 4.71304 | 2(Loss) |
| jsonifier | 382.962 | 2.33307 | 196.494ms | 409725 | 30 | 1.70001e+10 | 1.02032e+06 | 6.46415 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2156.34 | 0.557983 | 43.7517ms | 409725 | 30 | 3.067e+07 | 181207 | 1.14781 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2148.08 | 0.647281 | 43.8518ms | 409725 | 30 | 4.15901e+07 | 181904 | 1.15221 | 1(Tie) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1352.87 | 0.35511 | 134.604ms | 785750 | 30 | 1.16066e+08 | 553897 | 1.82977 | 1(Win) |
| glaze | 884.45 | 0.221174 | 203.626ms | 785750 | 30 | 1.05345e+08 | 847249 | 2.79895 | 2(Loss) |
| jsonifier | 756.158 | 0.100586 | 239.237ms | 785750 | 30 | 2.98088e+07 | 990996 | 3.27383 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3798.4 | 0.477699 | 47.7465ms | 785750 | 30 | 2.66438e+07 | 197280 | 0.651645 | 1(Win) |
| glaze | 2722.71 | 0.411373 | 67.1609ms | 785750 | 30 | 3.84556e+07 | 275222 | 0.909096 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 826.621 | 0.446763 | 2371.56ms | 8587914 | 30 | 5.87812e+10 | 9.90789e+06 | 2.995 | 1(Win) |
| glaze | 761.494 | 0.54136 | 2636.26ms | 8587914 | 30 | 1.01703e+11 | 1.07553e+07 | 3.25115 | 2(Loss) |
| jsonifier | 661.866 | 0.755878 | 2994.71ms | 8587914 | 30 | 2.62458e+11 | 1.23742e+07 | 3.74036 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2655.93 | 0.370941 | 736.764ms | 8588126 | 30 | 3.9255e+09 | 3.08377e+06 | 0.932006 | 1(Win) |
| jsonifier | 2462.35 | 1.31256 | 779.121ms | 8588126 | 30 | 5.71817e+10 | 3.32621e+06 | 1.00535 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 859.628 | 1.40868 | 2486.55ms | 9804437 | 30 | 7.04324e+11 | 1.08771e+07 | 2.87988 | 1(Win) |
| glaze | 754.358 | 1.04627 | 2915.97ms | 9804437 | 30 | 5.04542e+11 | 1.2395e+07 | 3.28186 | 2(Loss) |
| jsonifier | 656.019 | 0.886308 | 3402.04ms | 9804437 | 30 | 4.78744e+11 | 1.4253e+07 | 3.77372 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2782.53 | 0.586996 | 924.491ms | 11078090 | 30 | 1.49019e+10 | 3.79686e+06 | 0.88969 | 1(Win) |
| glaze | 2430.4 | 0.410926 | 1028.04ms | 11078090 | 30 | 9.57245e+09 | 4.34697e+06 | 1.01853 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 4499.34 | 0.498615 | 13.7753ms | 264040 | 30 | 2.33611e+06 | 55965.6 | 0.549971 | 1(Win) |
| jsonifier | 4075.37 | 0.875987 | 15.1388ms | 264040 | 30 | 8.78863e+06 | 61787.8 | 0.607172 | 2(Loss) |
| glaze | 1055.71 | 0.392127 | 57.6399ms | 264040 | 30 | 2.62435e+07 | 238519 | 2.3448 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5670.57 | 0.949114 | 16.3789ms | 399947 | 30 | 1.22267e+07 | 67263 | 0.43637 | 1(Win) |
| jsonifier | 5331.3 | 0.809279 | 17.3835ms | 399947 | 30 | 1.00567e+07 | 71543.4 | 0.464183 | 2(Loss) |
| glaze | 1463.62 | 0.333338 | 64.2684ms | 399947 | 30 | 2.26381e+07 | 260600 | 1.69127 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1462.21 | 0.482677 | 43.1874ms | 264040 | 30 | 2.07278e+07 | 172211 | 1.6928 | 1(Win) |
| glaze | 1126.41 | 0.45624 | 54.4032ms | 264040 | 30 | 3.12072e+07 | 223549 | 2.19736 | 2(Loss) |
| jsonifier | 1067.13 | 0.486157 | 57.6866ms | 264040 | 30 | 3.94801e+07 | 235968 | 2.31909 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3292.32 | 0.678633 | 18.7321ms | 263923 | 30 | 8.07498e+06 | 76449.5 | 0.751524 | 1(Win) |
| jsonifier | 2837.93 | 0.430895 | 21.7243ms | 264040 | 30 | 4.38532e+06 | 88729.7 | 0.872115 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1907.81 | 0.426928 | 48.3256ms | 399947 | 30 | 2.18556e+07 | 199925 | 1.29732 | 1(Win) |
| glaze | 1353.84 | 0.454785 | 68.3164ms | 399947 | 30 | 4.92495e+07 | 281731 | 1.82824 | 2(Loss) |
| jsonifier | 1092.1 | 0.487663 | 84.3279ms | 399947 | 30 | 8.70252e+07 | 349254 | 2.26656 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4391.35 | 0.439611 | 21.5041ms | 399947 | 30 | 4.37387e+06 | 86856.8 | 0.563447 | 1(Win) |
| glaze | 3520.62 | 0.677054 | 26.198ms | 399830 | 30 | 1.61317e+07 | 108307 | 0.702877 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1784.85 | 0.368744 | 60.1386ms | 466906 | 30 | 2.53878e+07 | 249475 | 1.38683 | 1(Win) |
| glaze | 1737.54 | 0.543142 | 62.2544ms | 466906 | 30 | 5.81219e+07 | 256269 | 1.42457 | 2(Loss) |
| simdjson (ondemand) | 911.645 | 0.419212 | 116.045ms | 466906 | 30 | 1.25775e+08 | 488432 | 2.71529 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3276.55 | 0.435535 | 49.144ms | 699405 | 30 | 2.35826e+07 | 203569 | 0.754431 | 1(Win) |
| glaze | 2312.3 | 0.476705 | 69.4358ms | 699405 | 30 | 5.67273e+07 | 288460 | 1.07049 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1791.69 | 0.241168 | 81.1069ms | 631514 | 30 | 1.97152e+07 | 336140 | 1.38162 | 1(Win) |
| glaze | 1707.19 | 0.266961 | 85.1672ms | 631514 | 30 | 2.66084e+07 | 352777 | 1.45001 | 2(Loss) |
