# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [55785b4](https://github.com/nihilai-collective/jsonifier/commit/55785b4)  
| Glaze: [2518e75](https://github.com/stephenberry/glaze/commit/2518e75)  
| Simdjson: [9572dd0](https://github.com/simdjson/simdjson/commit/9572dd0)  

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
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 656.635 | 0.0848905 | 2.99626ms | 1811 | 30 | 149.564 | 2630.23 | 3.71264 | 1(Win) |
| glaze | 459.699 | 0.0658002 | 1.10231ms | 1811 | 30 | 183.344 | 3757.03 | 5.33065 | 2(Loss) |
| simdjson (ondemand) | 132.787 | 0.0353436 | 3.32255ms | 1811 | 30 | 633.972 | 13006.6 | 18.5895 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 391.906 | 0.136088 | 1.28712ms | 1811 | 30 | 1079.03 | 4406.93 | 6.26479 | 1(Win) |
| glaze | 276.875 | 1.81288 | 7.66269ms | 1798 | 64 | 806734 | 6193.08 | 8.8896 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1178.4 | 0.073498 | 0.979427ms | 3873 | 30 | 159.214 | 3134.4 | 2.07548 | 1(Win) |
| glaze | 1006.75 | 0.0490216 | 1.03757ms | 3873 | 30 | 97.0402 | 3668.83 | 2.43508 | 2(Loss) |
| simdjson (ondemand) | 305.958 | 0.109071 | 3.11247ms | 3873 | 30 | 5201.27 | 12072.2 | 8.06718 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1570.67 | 0.0666811 | 0.7828ms | 3873 | 30 | 73.7655 | 2351.6 | 1.54447 | 1(Win) |
| glaze | 1011.14 | 0.813331 | 1.06159ms | 3873 | 30 | 26480.9 | 3652.9 | 2.42523 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1135.63 | 0.077433 | 1.00934ms | 3862 | 30 | 189.2 | 3243.2 | 2.15634 | 1(Win) |
| glaze | 888.727 | 0.0597444 | 1.18448ms | 3862 | 30 | 183.909 | 4144.23 | 2.75933 | 2(Loss) |
| simdjson (ondemand) | 299.719 | 0.0252673 | 3.17414ms | 3862 | 30 | 289.223 | 12288.5 | 8.2376 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1521.08 | 1.82961 | 0.778774ms | 3862 | 30 | 58878.8 | 2421.37 | 1.59757 | 1(Win) |
| glaze | 1053.55 | 0.352295 | 1.02921ms | 3862 | 30 | 4550.44 | 3495.9 | 2.32353 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 768.566 | 0.10575 | 0.920799ms | 905 | 32 | 45.128 | 1122.97 | 3.11443 | 1(Win) |
| glaze | 457.097 | 0.653801 | 0.637341ms | 905 | 30 | 4571.87 | 1888.17 | 5.30534 | 2(Loss) |
| simdjson (ondemand) | 99.4475 | 0.0496696 | 2.29903ms | 905 | 30 | 557.459 | 8678.7 | 24.78 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 832.155 | 0.897759 | 0.852586ms | 905 | 32 | 2774.33 | 1037.16 | 2.86575 | 1(Win) |
| glaze | 329.443 | 0.190093 | 0.820577ms | 905 | 30 | 744.028 | 2619.8 | 7.40832 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1727.58 | 0.127901 | 1.5899ms | 9578 | 30 | 1371.95 | 5287.33 | 1.42261 | 1(Win) |
| glaze | 1473.76 | 0.0677866 | 1.73258ms | 9578 | 30 | 529.551 | 6197.97 | 1.67008 | 2(Loss) |
| simdjson (ondemand) | 695.108 | 1.91377 | 3.34307ms | 9578 | 30 | 1.89734e+06 | 13140.8 | 3.55109 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3254.19 | 0.159278 | 0.851675ms | 9578 | 30 | 599.651 | 2806.93 | 0.74985 | 1(Win) |
| glaze | 2319.78 | 0.308335 | 2.71793ms | 9578 | 32 | 4716.83 | 3937.56 | 1.05647 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2757.27 | 0.666915 | 19.7772ms | 233995 | 30 | 8.74012e+06 | 80933.3 | 0.897453 | 1(Win) |
| simdjson (ondemand) | 2545.23 | 0.528106 | 21.3414ms | 233995 | 30 | 6.43165e+06 | 87675.8 | 0.971987 | 2(Loss) |
| glaze | 1284.01 | 0.404602 | 42.1917ms | 233995 | 30 | 1.48339e+07 | 173795 | 1.92772 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3238.8 | 0.632204 | 24.8073ms | 346753 | 30 | 1.25e+07 | 102103 | 0.764032 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3199.39 | 0.588157 | 25.1654ms | 346753 | 30 | 1.1087e+07 | 103360 | 0.773447 | 1(Tie) |
| glaze | 1545.18 | 0.384375 | 51.5876ms | 346753 | 30 | 2.03008e+07 | 214013 | 1.60193 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1121.36 | 0.611458 | 48.3568ms | 233995 | 30 | 4.44202e+07 | 199005 | 2.20726 | 1(Win) |
| glaze | 1052.09 | 0.833348 | 51.3836ms | 233995 | 30 | 9.37306e+07 | 212106 | 2.35255 | 2(Loss) |
| simdjson (ondemand) | 844.384 | 0.316903 | 63.8958ms | 233995 | 30 | 2.1043e+07 | 264281 | 2.93146 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2456.47 | 0.7511 | 22.2371ms | 233995 | 30 | 1.39671e+07 | 90843.7 | 1.00737 | 1(Win) |
| glaze | 2076.72 | 0.560783 | 26.3216ms | 233995 | 30 | 1.08935e+07 | 107456 | 1.19167 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1233.18 | 0.305564 | 65.1051ms | 346753 | 30 | 2.01423e+07 | 268159 | 2.00729 | 1(Win) |
| simdjson (ondemand) | 1169.92 | 0.306149 | 68.3996ms | 346753 | 30 | 2.24655e+07 | 282660 | 2.11586 | 2(Loss) |
| jsonifier | 993.881 | 0.317261 | 81.5367ms | 346753 | 30 | 3.34292e+07 | 332726 | 2.49048 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2567.66 | 0.53813 | 31.1792ms | 346753 | 30 | 1.44099e+07 | 128790 | 0.96392 | 1(Win) |
| glaze | 2072.84 | 0.505975 | 39.3688ms | 346753 | 30 | 1.95473e+07 | 159534 | 1.19399 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2692.78 | 0.594028 | 20.4675ms | 233995 | 30 | 7.2702e+06 | 82871.6 | 0.918986 | 1(Win) |
| simdjson (ondemand) | 1672.35 | 0.437369 | 32.4322ms | 233995 | 30 | 1.02183e+07 | 133438 | 1.47998 | 2(Loss) |
| glaze | 1258.32 | 0.481395 | 42.5324ms | 233995 | 30 | 2.18653e+07 | 177344 | 1.96704 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3150.1 | 0.525936 | 25.6728ms | 346753 | 30 | 9.1449e+06 | 104977 | 0.785457 | 1(Win) |
| simdjson (ondemand) | 2214.22 | 0.463204 | 36.2068ms | 346753 | 30 | 1.4357e+07 | 149348 | 1.11771 | 2(Loss) |
| glaze | 1551.64 | 0.316456 | 51.4293ms | 346753 | 30 | 1.36461e+07 | 213123 | 1.59524 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1161.19 | 0.596211 | 47.5224ms | 233995 | 30 | 3.93849e+07 | 192178 | 2.13155 | 1(Win) |
| jsonifier | 1034.97 | 0.372981 | 52.827ms | 233995 | 30 | 1.94025e+07 | 215616 | 2.39166 | 2(Loss) |
| simdjson (ondemand) | 168.352 | 0.249755 | 315.573ms | 233995 | 30 | 3.28797e+08 | 1.32553e+06 | 14.7052 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2602.01 | 0.761266 | 21.0024ms | 233995 | 30 | 1.27876e+07 | 85762.7 | 0.950939 | 1(Win) |
| glaze | 2140.86 | 0.475989 | 25.555ms | 233995 | 30 | 7.38503e+06 | 104236 | 1.15587 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1228.4 | 0.357835 | 65.3773ms | 346753 | 30 | 2.78386e+07 | 269203 | 2.01506 | 1(Win) |
| jsonifier | 972.824 | 0.255188 | 82.7455ms | 346753 | 30 | 2.25742e+07 | 339927 | 2.54452 | 2(Loss) |
| simdjson (ondemand) | 246.373 | 0.159702 | 322.977ms | 346753 | 30 | 1.37848e+08 | 1.34223e+06 | 10.0485 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3093.99 | 0.723055 | 26.3413ms | 346753 | 30 | 1.7917e+07 | 106881 | 0.799741 | 1(Win) |
| glaze | 2214.61 | 0.536617 | 36.4685ms | 346753 | 30 | 1.92617e+07 | 149322 | 1.11748 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 658.265 | 0.517408 | 33.4955ms | 94651 | 30 | 1.51021e+07 | 137128 | 3.75965 | 1(Tie) |
| glaze STATISTICAL TIE | 655.283 | 0.495168 | 33.2084ms | 94651 | 30 | 1.39579e+07 | 137751 | 3.77691 | 1(Tie) |
| jsonifier | 637.897 | 0.4565 | 34.2888ms | 94651 | 30 | 1.25185e+07 | 141506 | 3.87998 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3395.87 | 1.20263 | 6.58032ms | 94651 | 30 | 3.06572e+06 | 26581.2 | 0.728001 | 1(Win) |
| glaze | 2823.28 | 1.20199 | 7.93983ms | 94651 | 30 | 4.4306e+06 | 31972.1 | 0.875878 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 920.941 | 0.481495 | 34.1644ms | 136024 | 30 | 1.37998e+07 | 140859 | 2.68747 | 1(Win) |
| glaze | 822.002 | 0.432982 | 38.3759ms | 136024 | 30 | 1.40071e+07 | 157813 | 3.01113 | 2(Loss) |
| jsonifier | 762.569 | 0.401514 | 41.7367ms | 136024 | 30 | 1.39957e+07 | 170113 | 3.24583 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3644.47 | 0.73227 | 8.82597ms | 136024 | 30 | 2.03811e+06 | 35594.4 | 0.67862 | 1(Win) |
| glaze | 2894.8 | 0.667592 | 11.1435ms | 136046 | 30 | 2.68584e+06 | 44819.6 | 0.854531 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 420.17 | 0.206852 | 1138.54ms | 2090234 | 30 | 2.88923e+09 | 4.74427e+06 | 5.89215 | 1(Win) |
| simdjson (ondemand) | 343.914 | 0.0786561 | 1392.14ms | 2090234 | 30 | 6.23556e+08 | 5.79622e+06 | 7.19866 | 2(Loss) |
| glaze | 334.856 | 0.0707696 | 1430.42ms | 2090234 | 30 | 5.32461e+08 | 5.95301e+06 | 7.39334 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 849.353 | 0.0919246 | 564.373ms | 2090234 | 30 | 1.39636e+08 | 2.34696e+06 | 2.9148 | 1(Win) |
| glaze | 730.736 | 0.0757961 | 655.744ms | 2090234 | 30 | 1.28258e+08 | 2.72794e+06 | 3.38792 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1023.81 | 0.0603552 | 1523.28ms | 6661897 | 30 | 4.20834e+08 | 6.20554e+06 | 2.41816 | 1(Win) |
| glaze | 873.628 | 0.0950964 | 1747.38ms | 6661897 | 30 | 1.4348e+09 | 7.27229e+06 | 2.83386 | 2(Loss) |
| jsonifier | 777.535 | 0.259441 | 1959.65ms | 6661897 | 30 | 1.3482e+10 | 8.17106e+06 | 3.18408 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2207.24 | 0.297194 | 690.316ms | 6661897 | 30 | 2.19531e+09 | 2.87838e+06 | 1.12162 | 1(Win) |
| glaze | 1742.75 | 0.13147 | 880.883ms | 6661897 | 30 | 6.89125e+08 | 3.64555e+06 | 1.42057 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 908.141 | 0.289987 | 125.759ms | 500299 | 30 | 6.96357e+07 | 525383 | 2.72569 | 1(Win) |
| jsonifier | 774.428 | 0.214011 | 147.968ms | 500299 | 30 | 5.21544e+07 | 616096 | 3.19637 | 2(Loss) |
| simdjson (ondemand) | 607.271 | 0.297632 | 456.475ms | 500299 | 32 | 1.74986e+08 | 785683 | 4.07635 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2787.67 | 1.09927 | 41.043ms | 500299 | 30 | 1.06196e+08 | 171154 | 0.887854 | 1(Win) |
| glaze | 1992.85 | 0.48897 | 57.7079ms | 500299 | 30 | 4.11145e+07 | 239417 | 1.24199 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1510.97 | 0.15534 | 218.734ms | 1439562 | 30 | 5.97632e+07 | 908601 | 1.63837 | 1(Win) |
| glaze | 1474.71 | 0.397959 | 223.127ms | 1439562 | 30 | 4.11759e+08 | 930942 | 1.6786 | 2(Loss) |
| jsonifier | 1003.8 | 0.145612 | 328.535ms | 1439562 | 30 | 1.18982e+08 | 1.36768e+06 | 2.4661 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4134.02 | 0.403145 | 80.4255ms | 1439562 | 30 | 5.37724e+07 | 332092 | 0.598779 | 1(Win) |
| glaze | 2663.08 | 0.270937 | 128.161ms | 1439584 | 30 | 5.8528e+07 | 515529 | 0.929541 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 858.28 | 0.728236 | 35.7919ms | 56369 | 32 | 6.6576e+06 | 62634.2 | 2.8826 | 1(Win) |
| glaze | 821.719 | 0.490835 | 16.1934ms | 56369 | 30 | 3.09333e+06 | 65421 | 3.01097 | 2(Loss) |
| simdjson (ondemand) | 693.475 | 0.800452 | 18.9849ms | 56369 | 30 | 1.15508e+07 | 77519.3 | 3.56828 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3065.78 | 0.14159 | 4.46713ms | 56369 | 30 | 18492 | 17534.8 | 0.805721 | 1(Win) |
| glaze | 2754.43 | 1.60671 | 4.84863ms | 56369 | 30 | 2.94992e+06 | 19516.8 | 0.89717 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1132.59 | 0.562218 | 19.563ms | 94370 | 30 | 5.98762e+06 | 79462.4 | 2.18484 | 1(Win) |
| simdjson (ondemand) | 1091.17 | 0.633262 | 20.2486ms | 94370 | 30 | 8.18408e+06 | 82478.5 | 2.26775 | 2(Loss) |
| jsonifier | 932.589 | 0.504051 | 23.9218ms | 94370 | 30 | 7.09836e+06 | 96503.7 | 2.65344 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3688.24 | 0.162178 | 6.19233ms | 94370 | 30 | 46982.4 | 24401.4 | 0.670264 | 1(Win) |
| glaze | 2728.13 | 1.45609 | 8.17129ms | 94370 | 30 | 6.92205e+06 | 32989 | 0.906533 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 890.82 | 0.764482 | 13.9017ms | 52708 | 30 | 5.58251e+06 | 56427 | 2.77707 | 1(Win) |
| jsonifier | 822.562 | 0.491842 | 15.6496ms | 52708 | 30 | 2.71011e+06 | 61109.4 | 3.00721 | 2(Loss) |
| glaze | 769.251 | 0.612869 | 16.2603ms | 52708 | 30 | 4.81143e+06 | 65344.4 | 3.21634 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3488.45 | 1.90837 | 3.67421ms | 52708 | 30 | 2.26848e+06 | 14409.3 | 0.706974 | 1(Win) |
| glaze | 3157.44 | 0.752243 | 4.07326ms | 52708 | 30 | 430250 | 15919.9 | 0.782216 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1160.63 | 0.893194 | 14.316ms | 70103 | 30 | 7.94137e+06 | 57602.5 | 2.13153 | 1(Win) |
| glaze | 891.601 | 0.459952 | 52.4844ms | 70103 | 32 | 3.80633e+06 | 74983.6 | 2.775 | 2(Loss) |
| jsonifier | 766.916 | 1.03932 | 22.3086ms | 70103 | 30 | 2.46263e+07 | 87174.3 | 3.22345 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3671.39 | 2.27249 | 4.58718ms | 70103 | 30 | 5.13733e+06 | 18209.8 | 0.67293 | 1(Win) |
| glaze | 2937.03 | 1.48648 | 5.72732ms | 70103 | 30 | 3.43476e+06 | 22763 | 0.841496 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 652.283 | 0.0985799 | 10.1431ms | 11812 | 32 | 9274.74 | 17269.8 | 3.7866 | 1(Tie) |
| glaze STATISTICAL TIE | 649.325 | 2.3962 | 4.49033ms | 11812 | 30 | 5.18428e+06 | 17348.5 | 3.80432 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 618.579 | 2.23843 | 4.57405ms | 11812 | 30 | 4.98499e+06 | 18210.8 | 3.99362 | 1(Tie) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3093.26 | 0.100131 | 2.3207ms | 11812 | 32 | 425.499 | 3641.72 | 0.792414 | 1(Win) |
| glaze | 1896.89 | 0.308412 | 1.63412ms | 11812 | 30 | 10063.4 | 5938.57 | 1.2967 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1454.55 | 1.33917 | 5.14347ms | 31235 | 30 | 2.25644e+06 | 20479.2 | 1.69873 | 1(Win) |
| glaze | 1122.73 | 0.551874 | 6.74927ms | 31235 | 30 | 643179 | 26531.7 | 2.20175 | 2(Loss) |
| jsonifier | 912.806 | 2.35944 | 8.0522ms | 31235 | 30 | 1.77854e+07 | 32633.5 | 2.70921 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3757.02 | 0.373744 | 2.13119ms | 31235 | 30 | 26343.1 | 7928.63 | 0.655931 | 1(Win) |
| glaze | 2766.37 | 0.230803 | 2.80796ms | 31235 | 30 | 18529.6 | 10767.9 | 0.891944 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1645.03 | 0.617042 | 15.6297ms | 108313 | 30 | 4.50366e+06 | 62792.4 | 1.50387 | 1(Win) |
| glaze | 992.697 | 0.649564 | 25.385ms | 108313 | 30 | 1.37055e+07 | 104055 | 2.49293 | 2(Loss) |
| simdjson (ondemand) | 884.318 | 0.71505 | 28.5145ms | 108313 | 30 | 2.09285e+07 | 116808 | 2.79861 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1960.48 | 0.516739 | 12.9359ms | 108313 | 30 | 2.22383e+06 | 52688.8 | 1.26198 | 1(Win) |
| glaze | 1459.56 | 0.626044 | 17.2381ms | 108313 | 30 | 5.88908e+06 | 70771.5 | 1.69513 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1579.22 | 0.522315 | 31.7055ms | 213963 | 30 | 1.3664e+07 | 129210 | 1.56717 | 1(Win) |
| glaze | 1433.76 | 0.488688 | 34.9458ms | 213963 | 30 | 1.45114e+07 | 142319 | 1.72622 | 2(Loss) |
| jsonifier | 1120.59 | 0.48834 | 44.3487ms | 213963 | 30 | 2.3722e+07 | 182093 | 2.20856 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2759.39 | 0.727463 | 18.0417ms | 213963 | 30 | 8.68148e+06 | 73947.8 | 0.896774 | 1(Win) |
| glaze | 1749.87 | 1.27583 | 28.3101ms | 213963 | 30 | 6.64013e+07 | 116610 | 1.41419 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 443.803 | 0.137663 | 947.133ms | 1834197 | 30 | 8.83215e+08 | 3.94145e+06 | 5.5783 | 1(Win) |
| glaze | 344.257 | 0.0809438 | 1222.11ms | 1834197 | 30 | 5.07476e+08 | 5.08117e+06 | 7.19146 | 2(Loss) |
| simdjson (ondemand) | 301.93 | 0.0809287 | 1394.21ms | 1834197 | 30 | 6.59489e+08 | 5.79349e+06 | 8.19965 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 582.219 | 0.139845 | 721.077ms | 1834197 | 30 | 5.29586e+08 | 3.00441e+06 | 4.25217 | 1(Win) |
| glaze | 352.139 | 0.0418192 | 1194.53ms | 1833577 | 30 | 1.29373e+08 | 4.96575e+06 | 7.03056 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1403.05 | 0.13941 | 1620.49ms | 9930848 | 30 | 2.65664e+09 | 6.75014e+06 | 1.76449 | 1(Win) |
| jsonifier | 1334.14 | 0.0973601 | 1708.67ms | 9930848 | 30 | 1.43302e+09 | 7.09879e+06 | 1.85557 | 2(Loss) |
| glaze | 1304.89 | 0.0607665 | 1749.44ms | 9930848 | 30 | 5.83543e+08 | 7.25791e+06 | 1.89727 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2129.86 | 0.275981 | 1068.64ms | 9930848 | 30 | 4.51802e+09 | 4.44667e+06 | 1.16238 | 1(Win) |
| glaze | 1299.04 | 0.100684 | 1758.47ms | 9930228 | 30 | 1.61629e+09 | 7.29016e+06 | 1.90573 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 784.591 | 0.229282 | 187.508ms | 642697 | 30 | 9.62472e+07 | 781202 | 3.15518 | 1(Win) |
| glaze | 622.309 | 0.141458 | 237.554ms | 642697 | 30 | 5.82338e+07 | 984919 | 3.97795 | 2(Loss) |
| simdjson (ondemand) | 579.794 | 0.0629613 | 254.384ms | 642697 | 30 | 1.32903e+07 | 1.05714e+06 | 4.26971 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 938.698 | 0.435003 | 156.23ms | 642697 | 30 | 2.42028e+08 | 652951 | 2.63724 | 1(Win) |
| glaze | 557.788 | 0.0832339 | 264.395ms | 642692 | 30 | 2.50951e+07 | 1.09884e+06 | 4.43819 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1054.35 | 0.0970385 | 266.043ms | 1225964 | 30 | 3.47371e+07 | 1.1089e+06 | 2.34791 | 1(Win) |
| glaze | 928.534 | 0.270907 | 300.777ms | 1225964 | 30 | 3.49078e+08 | 1.25916e+06 | 2.66606 | 2(Loss) |
| jsonifier | 830.914 | 0.192223 | 338.735ms | 1225964 | 30 | 2.1947e+08 | 1.40709e+06 | 2.97933 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1571.31 | 0.321522 | 179.196ms | 1225964 | 30 | 1.71702e+08 | 744074 | 1.5754 | 1(Win) |
| glaze | 932.235 | 0.107181 | 301.498ms | 1225970 | 30 | 5.42079e+07 | 1.25416e+06 | 2.65553 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 538.89 | 0.150177 | 174.684ms | 409725 | 30 | 3.55725e+07 | 725091 | 4.5936 | 1(Win) |
| simdjson (ondemand) | 527.338 | 0.143224 | 177.962ms | 409725 | 30 | 3.37881e+07 | 740975 | 4.69436 | 2(Loss) |
| glaze | 395.95 | 0.11982 | 237.431ms | 409725 | 30 | 4.19456e+07 | 986852 | 6.25208 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2036.36 | 1.48212 | 45.3202ms | 409725 | 30 | 2.42642e+08 | 191884 | 1.21532 | 1(Win) |
| glaze | 1680.23 | 0.526316 | 56.6573ms | 409725 | 30 | 4.49429e+07 | 232554 | 1.47293 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 946.131 | 0.154393 | 190.241ms | 785750 | 30 | 4.48585e+07 | 792014 | 2.61638 | 1(Win) |
| jsonifier | 730.442 | 0.0658392 | 246.845ms | 785750 | 30 | 1.36864e+07 | 1.02588e+06 | 3.38921 | 2(Loss) |
| glaze | 652.23 | 1.68299 | 269.717ms | 785750 | 30 | 1.12163e+10 | 1.1489e+06 | 3.79541 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2331.13 | 0.397037 | 77.3824ms | 785750 | 30 | 4.88674e+07 | 321453 | 1.06189 | 1(Win) |
| glaze | 1973.37 | 0.285302 | 91.7082ms | 785750 | 30 | 3.52112e+07 | 379731 | 1.25433 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 662.542 | 0.466005 | 2949.82ms | 8587914 | 30 | 9.95521e+10 | 1.23616e+07 | 3.73673 | 1(Win) |
| jsonifier | 621.071 | 0.52388 | 3124.86ms | 8587914 | 30 | 1.43178e+11 | 1.3187e+07 | 3.98616 | 2(Loss) |
| glaze | 610.791 | 0.123451 | 3283.91ms | 8587914 | 30 | 8.22053e+09 | 1.3409e+07 | 4.05335 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2258.38 | 0.812526 | 848.756ms | 8588126 | 30 | 2.60494e+10 | 3.62662e+06 | 1.09615 | 1(Win) |
| glaze | 2114.08 | 0.279123 | 928.094ms | 8588126 | 30 | 3.50805e+09 | 3.87415e+06 | 1.17096 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 704.225 | 0.924913 | 3121.27ms | 9804437 | 30 | 4.52423e+11 | 1.32773e+07 | 3.51549 | 1(Win) |
| glaze | 636.538 | 0.461712 | 3551.05ms | 9804437 | 30 | 1.37994e+11 | 1.46892e+07 | 3.88937 | 2(Loss) |
| jsonifier | 599.243 | 1.38039 | 3685.78ms | 9804437 | 30 | 1.39176e+12 | 1.56034e+07 | 4.13145 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2406.59 | 0.358245 | 1048.5ms | 11078090 | 30 | 7.42008e+09 | 4.38999e+06 | 1.02867 | 1(Win) |
| glaze | 2037.09 | 0.156448 | 1243.5ms | 11078090 | 30 | 1.97503e+09 | 5.18627e+06 | 1.2152 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2765.17 | 0.719601 | 22.357ms | 264040 | 30 | 1.28825e+07 | 91064.3 | 0.894951 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2761.06 | 0.759507 | 22.1539ms | 264040 | 30 | 1.43937e+07 | 91199.8 | 0.896221 | 1(Tie) |
| glaze | 1047.58 | 0.543665 | 57.8034ms | 264040 | 30 | 5.12326e+07 | 240370 | 2.3629 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3563.84 | 0.569911 | 26.0618ms | 399947 | 30 | 1.1161e+07 | 107025 | 0.694383 | 1(Win) |
| jsonifier | 3371.61 | 0.554243 | 27.5682ms | 399947 | 30 | 1.17937e+07 | 113127 | 0.734073 | 2(Loss) |
| glaze | 1361.26 | 0.326362 | 67.9296ms | 399947 | 30 | 2.50866e+07 | 280195 | 1.81842 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 929.366 | 0.542585 | 66.7648ms | 264040 | 30 | 6.4837e+07 | 270946 | 2.66235 | 1(Win) |
| simdjson (ondemand) | 909.448 | 0.368005 | 67.1417ms | 264040 | 30 | 3.11467e+07 | 276880 | 2.72132 | 2(Loss) |
| glaze | 851 | 0.624697 | 80.162ms | 264040 | 30 | 1.02504e+08 | 295897 | 2.90816 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2811.68 | 1.02285 | 21.8756ms | 264040 | 30 | 2.51742e+07 | 89557.8 | 0.880124 | 1(Win) |
| glaze | 2532.67 | 0.864223 | 24.1791ms | 263923 | 30 | 2.21294e+07 | 99379.9 | 0.976989 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1293.54 | 0.344592 | 71.9393ms | 399947 | 30 | 3.09725e+07 | 294864 | 1.91342 | 1(Win) |
| glaze | 1032.96 | 0.345813 | 89.8003ms | 399947 | 30 | 4.89152e+07 | 369250 | 2.3961 | 2(Loss) |
| jsonifier | 837.13 | 0.324881 | 110.178ms | 399947 | 30 | 6.57338e+07 | 455627 | 2.95626 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3293.95 | 0.804666 | 66.2673ms | 399947 | 32 | 2.77812e+07 | 115794 | 0.751248 | 1(Win) |
| glaze | 2727.1 | 0.628831 | 34.6457ms | 399830 | 30 | 2.31919e+07 | 139822 | 0.907359 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1383.88 | 0.377673 | 77.8033ms | 466906 | 30 | 4.43014e+07 | 321760 | 1.78861 | 1(Win) |
| glaze | 1350.29 | 0.287019 | 79.8465ms | 466906 | 30 | 2.68751e+07 | 329764 | 1.83314 | 2(Loss) |
| simdjson (ondemand) | 697.458 | 0.496505 | 163.538ms | 466906 | 30 | 3.01434e+08 | 638428 | 3.54917 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2420.25 | 0.354416 | 66.8936ms | 699405 | 30 | 2.8621e+07 | 275594 | 1.02274 | 1(Win) |
| glaze | 1899.47 | 0.276847 | 83.2616ms | 699405 | 30 | 2.83527e+07 | 351154 | 1.30313 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1766.69 | 0.297705 | 82.6483ms | 631514 | 30 | 3.08987e+07 | 340898 | 1.40115 | 1(Win) |
| glaze | 1584.3 | 0.217144 | 92.3327ms | 631514 | 30 | 2.04414e+07 | 380142 | 1.56255 | 2(Loss) |
