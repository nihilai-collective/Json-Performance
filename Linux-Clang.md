# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 14, 2026)
#### Using the following commits:
----
| Jsonifier: [fde86fb](https://github.com/nihilai-collective/jsonifier/commit/fde86fb)  
| Glaze: [b91062d](https://github.com/stephenberry/glaze/commit/b91062d)  
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

> Adaptive sampling on (INTEL(R) XEON(R) PLATINUM 8573C-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 675.186 | 0.0837726 | 3.24721ms | 1811 | 30 | 137.757 | 2557.97 | 3.19245 | 1(Win) |
| glaze | 623.068 | 0.150494 | 1.1641ms | 1811 | 30 | 522.064 | 2771.93 | 3.4607 | 2(Loss) |
| simdjson (ondemand) | 156.552 | 0.0506566 | 6.73043ms | 1811 | 32 | 999.403 | 11032.1 | 13.9584 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 460.831 | 0.0634315 | 1.86696ms | 1811 | 30 | 169.545 | 3747.8 | 4.68802 | 1(Win) |
| glaze | 280.333 | 0.316609 | 1.96038ms | 1798 | 30 | 11251.2 | 6116.67 | 7.74349 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1330.56 | 0.0813338 | 1.2971ms | 3873 | 30 | 152.93 | 2775.97 | 1.62148 | 1(Win) |
| glaze | 1156.82 | 0.0651928 | 1.22425ms | 3873 | 30 | 129.982 | 3192.87 | 1.87724 | 2(Loss) |
| simdjson (ondemand) | 322.066 | 0.0291712 | 3.26122ms | 3873 | 30 | 335.766 | 11468.4 | 6.7925 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1803.51 | 0.17132 | 1.90364ms | 3873 | 32 | 393.935 | 2048 | 1.17632 | 1(Win) |
| glaze | 831.338 | 0.134631 | 1.53932ms | 3873 | 30 | 1073.37 | 4442.93 | 2.6167 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1376.17 | 0.144016 | 1.26854ms | 3862 | 30 | 445.678 | 2676.33 | 1.56769 | 1(Win) |
| glaze | 1108.83 | 0.0487286 | 1.24325ms | 3862 | 30 | 78.5931 | 3321.6 | 1.95187 | 2(Loss) |
| simdjson (ondemand) | 310.205 | 0.0376141 | 3.35026ms | 3862 | 30 | 598.34 | 11873.1 | 7.05277 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1821.54 | 0.0717866 | 1.08455ms | 3862 | 30 | 63.2057 | 2021.97 | 1.18241 | 1(Win) |
| glaze | 797.465 | 0.139846 | 3.21894ms | 3862 | 32 | 1334.9 | 4618.5 | 2.72683 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 715.256 | 0.143888 | 0.902579ms | 905 | 30 | 90.4368 | 1206.67 | 2.9849 | 1(Win) |
| glaze | 554.747 | 0.041962 | 0.819085ms | 905 | 30 | 12.7862 | 1555.8 | 3.87308 | 2(Loss) |
| simdjson (ondemand) | 131.602 | 0.0479833 | 2.0596ms | 905 | 30 | 297.082 | 6558.23 | 16.5559 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 992.459 | 0.0379918 | 0.773783ms | 905 | 30 | 3.27471 | 869.633 | 2.13267 | 1(Win) |
| glaze | 226.817 | 0.21583 | 1.40439ms | 905 | 30 | 2023.45 | 3805.17 | 9.57267 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1949.16 | 0.0970455 | 1.6508ms | 9578 | 30 | 620.478 | 4686.27 | 1.11664 | 1(Win) |
| jsonifier | 1878.3 | 0.106393 | 1.87667ms | 9578 | 30 | 803.099 | 4863.07 | 1.15456 | 2(Loss) |
| simdjson (ondemand) | 869.017 | 0.060607 | 6.58879ms | 9578 | 32 | 1298.64 | 10511.1 | 2.51549 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3241.14 | 0.0309842 | 1.55041ms | 9578 | 30 | 22.8747 | 2818.23 | 0.66817 | 1(Win) |
| glaze | 1789.07 | 0.301992 | 1.69481ms | 9578 | 30 | 7131.9 | 5105.6 | 1.21619 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3997.53 | 0.524653 | 13.9313ms | 233995 | 30 | 2.57333e+06 | 55823.2 | 0.548296 | 1(Win) |
| jsonifier | 3891.79 | 0.502882 | 14.5282ms | 233995 | 30 | 2.49442e+06 | 57340 | 0.563212 | 2(Loss) |
| glaze | 1402.84 | 0.374082 | 38.7093ms | 233995 | 30 | 1.06231e+07 | 159074 | 1.56313 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5567.39 | 0.606589 | 15.0496ms | 346753 | 30 | 3.89446e+06 | 59397.5 | 0.393712 | 1(Win) |
| jsonifier | 5014.42 | 0.705596 | 15.9221ms | 346753 | 30 | 6.4958e+06 | 65947.7 | 0.437151 | 2(Loss) |
| glaze | 1821.62 | 0.676931 | 44.0624ms | 346753 | 30 | 4.5304e+07 | 181536 | 1.20383 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1419.1 | 0.867462 | 40.0152ms | 233995 | 30 | 5.58226e+07 | 157251 | 1.54529 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1116.82 | 0.862042 | 49.8254ms | 233995 | 30 | 8.90072e+07 | 199813 | 1.96359 | 2(Tie) |
| glaze STATISTICAL TIE | 1116.64 | 0.647497 | 49.4805ms | 233995 | 30 | 5.02329e+07 | 199846 | 1.96387 | 2(Tie) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2850.65 | 0.564068 | 19.7008ms | 233995 | 30 | 5.84939e+06 | 78282.2 | 0.76881 | 1(Win) |
| glaze | 2525.46 | 0.983052 | 21.6955ms | 233995 | 30 | 2.26364e+07 | 88362.3 | 0.867974 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1535.45 | 0.369615 | 52.487ms | 346753 | 30 | 1.90102e+07 | 215369 | 1.42824 | 1(Win) |
| jsonifier | 1402.3 | 1.05787 | 57.2195ms | 346753 | 30 | 1.867e+08 | 235819 | 1.56387 | 2(Loss) |
| glaze | 1365.87 | 0.259963 | 58.8971ms | 346753 | 30 | 1.1884e+07 | 242108 | 1.60561 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3308.81 | 0.416125 | 24.5534ms | 346753 | 30 | 5.18879e+06 | 99942.1 | 0.662518 | 1(Win) |
| glaze | 2398.84 | 0.400791 | 33.8153ms | 346753 | 30 | 9.15794e+06 | 137854 | 0.913935 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3711.55 | 0.426821 | 15.259ms | 233995 | 30 | 1.97568e+06 | 60124.5 | 0.590605 | 1(Win) |
| simdjson (ondemand) | 2524.9 | 0.431576 | 21.7362ms | 233995 | 30 | 4.36477e+06 | 88381.8 | 0.868333 | 2(Loss) |
| glaze | 1389.36 | 0.540341 | 38.9512ms | 233995 | 30 | 2.25964e+07 | 160617 | 1.57834 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4985.7 | 1.22021 | 16.4322ms | 346753 | 30 | 1.96507e+07 | 66327.5 | 0.439692 | 1(Win) |
| simdjson (ondemand) | 3434.58 | 0.447181 | 23.7319ms | 346753 | 30 | 5.56138e+06 | 96282.4 | 0.638327 | 2(Loss) |
| glaze | 1808.47 | 0.396191 | 44.2757ms | 346753 | 30 | 1.57452e+07 | 182856 | 1.21261 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1265.57 | 0.26214 | 43.5691ms | 233995 | 30 | 6.40955e+06 | 176327 | 1.73281 | 1(Win) |
| glaze | 1197.39 | 0.916993 | 47.2525ms | 233995 | 30 | 8.76184e+07 | 186368 | 1.83146 | 2(Loss) |
| simdjson (ondemand) | 232.692 | 0.256079 | 231.348ms | 233995 | 30 | 1.80934e+08 | 959016 | 9.42587 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2845.59 | 0.488971 | 19.822ms | 233995 | 30 | 4.41118e+06 | 78421.3 | 0.769772 | 1(Win) |
| glaze | 2592.5 | 1.53946 | 20.5804ms | 233995 | 30 | 5.26787e+07 | 86077 | 0.845546 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1391.62 | 0.279551 | 57.9328ms | 346753 | 30 | 1.32387e+07 | 237630 | 1.57583 | 1(Win) |
| jsonifier | 1355.51 | 0.576312 | 58.7781ms | 346753 | 30 | 5.93022e+07 | 243959 | 1.61778 | 2(Loss) |
| simdjson (ondemand) | 343.439 | 0.374349 | 231.614ms | 346753 | 30 | 3.89777e+08 | 962876 | 6.38636 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3368.6 | 0.397548 | 24.4492ms | 346753 | 30 | 4.5692e+06 | 98168.1 | 0.650807 | 1(Win) |
| glaze | 2349.51 | 0.34971 | 34.7862ms | 346753 | 30 | 7.26813e+06 | 140748 | 0.933167 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 754.251 | 0.306046 | 29.6657ms | 94651 | 30 | 4.02451e+06 | 119677 | 2.90709 | 1(Win) |
| jsonifier | 728.919 | 0.362887 | 30.5092ms | 94651 | 30 | 6.05839e+06 | 123836 | 3.00811 | 2(Loss) |
| glaze | 706.157 | 0.436904 | 31.3168ms | 94651 | 30 | 9.35711e+06 | 127828 | 3.10517 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3216.24 | 2.20274 | 7.76168ms | 94651 | 30 | 1.14657e+07 | 28065.8 | 0.6802 | 1(Tie) |
| glaze STATISTICAL TIE | 3177.44 | 1.22121 | 7.68098ms | 94651 | 30 | 3.61077e+06 | 28408.4 | 0.689308 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1067.84 | 0.260807 | 29.5559ms | 136024 | 30 | 3.01147e+06 | 121481 | 2.05317 | 1(Win) |
| glaze STATISTICAL TIE | 881.763 | 1.8793 | 35.5908ms | 136024 | 30 | 2.29318e+08 | 147117 | 2.48671 | 2(Tie) |
| jsonifier STATISTICAL TIE | 876.584 | 0.266121 | 36.7624ms | 136024 | 30 | 4.6529e+06 | 147986 | 2.5015 | 2(Tie) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3880.25 | 1.1784 | 8.72842ms | 136024 | 30 | 4.65608e+06 | 33431.5 | 0.563584 | 1(Win) |
| glaze | 2944.91 | 0.55257 | 11.2405ms | 136046 | 30 | 1.77796e+06 | 44056.9 | 0.744148 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 515.658 | 0.139325 | 927.26ms | 2090234 | 30 | 8.70252e+08 | 3.86575e+06 | 4.25356 | 1(Win) |
| glaze | 437.717 | 0.0924343 | 1092.96ms | 2090234 | 30 | 5.31608e+08 | 4.55409e+06 | 5.01095 | 2(Loss) |
| simdjson (ondemand) | 344.553 | 0.130179 | 1393.71ms | 2090234 | 30 | 1.70168e+09 | 5.78547e+06 | 6.36594 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1024.09 | 0.133717 | 469.36ms | 2090234 | 30 | 2.03237e+08 | 1.9465e+06 | 2.14153 | 1(Win) |
| glaze | 552.355 | 0.022351 | 866.511ms | 2090234 | 30 | 1.95195e+07 | 3.60892e+06 | 3.97086 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1164.59 | 0.135266 | 1314.2ms | 6661897 | 30 | 1.63361e+09 | 5.45539e+06 | 1.88339 | 1(Win) |
| glaze | 1107.8 | 0.088547 | 1368.47ms | 6661897 | 30 | 7.73644e+08 | 5.73504e+06 | 1.97994 | 2(Loss) |
| simdjson (ondemand) | 1038.99 | 0.185465 | 1470.39ms | 6661897 | 30 | 3.8585e+09 | 6.11486e+06 | 2.11107 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1968.35 | 0.106428 | 774.905ms | 6661897 | 30 | 3.54019e+08 | 3.22772e+06 | 1.11426 | 1(Win) |
| glaze | 1193.86 | 0.878943 | 1248.57ms | 6661897 | 30 | 6.56342e+10 | 5.32161e+06 | 1.83714 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1243.98 | 0.858538 | 96.8878ms | 500299 | 30 | 3.25293e+08 | 383546 | 1.76304 | 1(Win) |
| glaze | 1053.86 | 0.241254 | 109.252ms | 500299 | 30 | 3.57903e+07 | 452738 | 2.08107 | 2(Loss) |
| simdjson (ondemand) | 694.316 | 0.540131 | 164.537ms | 500299 | 30 | 4.133e+08 | 687184 | 3.15866 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3109.98 | 2.18748 | 37.861ms | 500299 | 30 | 3.37872e+08 | 153417 | 0.705 | 1(Win) |
| jsonifier | 2595.7 | 1.16679 | 43.5886ms | 500299 | 30 | 1.37993e+08 | 183812 | 0.844571 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1973.16 | 0.216974 | 168.177ms | 1439562 | 30 | 6.83708e+07 | 695773 | 1.11139 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1751.5 | 0.532373 | 190.02ms | 1439562 | 30 | 5.2239e+08 | 783828 | 1.25193 | 2(Tie) |
| glaze STATISTICAL TIE | 1742.6 | 0.563691 | 189.813ms | 1439562 | 30 | 5.91654e+08 | 787830 | 1.25844 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3746.35 | 0.650318 | 89.712ms | 1439562 | 30 | 1.7038e+08 | 366457 | 0.584998 | 1(Win) |
| glaze | 2965.28 | 0.773603 | 112.512ms | 1439584 | 30 | 3.84859e+08 | 462990 | 0.739346 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1067.75 | 0.831033 | 12.9989ms | 56369 | 30 | 5.25166e+06 | 50346.6 | 2.05237 | 1(Win) |
| glaze | 994.023 | 0.603603 | 13.8985ms | 56369 | 30 | 3.19678e+06 | 54080.9 | 2.20494 | 2(Loss) |
| simdjson (ondemand) | 810.659 | 0.535395 | 16.5595ms | 56369 | 30 | 3.78159e+06 | 66313.5 | 2.70404 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3597.15 | 0.380814 | 4.02075ms | 56369 | 30 | 97165 | 14944.5 | 0.60811 | 1(Win) |
| jsonifier | 3324.23 | 0.0600354 | 4.60632ms | 56369 | 30 | 2827.71 | 16171.5 | 0.658221 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1336.28 | 0.398501 | 16.9343ms | 94370 | 30 | 2.16098e+06 | 67349.6 | 1.6404 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1335.58 | 0.500931 | 17.0479ms | 94370 | 30 | 3.41826e+06 | 67385.1 | 1.64111 | 1(Tie) |
| glaze STATISTICAL TIE | 1330.31 | 0.503684 | 16.9429ms | 94370 | 30 | 3.48337e+06 | 67652 | 1.64781 | 1(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4371.87 | 0.459622 | 5.47732ms | 94370 | 30 | 268569 | 20585.7 | 0.499585 | 1(Win) |
| glaze | 3115.51 | 1.13033 | 7.4771ms | 94370 | 30 | 3.19844e+06 | 28887.1 | 0.702825 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1036.07 | 1.40553 | 12.4902ms | 52708 | 30 | 1.395e+07 | 48516.2 | 2.11444 | 1(Win) |
| jsonifier | 963.817 | 0.698602 | 13.7194ms | 52708 | 30 | 3.9824e+06 | 52153.3 | 2.2728 | 2(Loss) |
| glaze | 824.256 | 0.622033 | 15.4453ms | 52708 | 30 | 4.31695e+06 | 60983.8 | 2.65855 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3684.22 | 0.506154 | 3.93781ms | 52708 | 30 | 143070 | 13643.7 | 0.593178 | 1(Win) |
| jsonifier | 3178.67 | 1.65903 | 4.20654ms | 52708 | 30 | 2.06486e+06 | 15813.6 | 0.687359 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1307.46 | 0.62733 | 13.1151ms | 70103 | 30 | 3.08695e+06 | 51133.8 | 1.67571 | 1(Win) |
| jsonifier | 1029.96 | 0.478787 | 17.1553ms | 70103 | 30 | 2.89759e+06 | 64910.6 | 2.12678 | 2(Loss) |
| glaze | 988.57 | 0.689677 | 17.3127ms | 70103 | 30 | 6.52636e+06 | 67628.4 | 2.21692 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4000.59 | 0.0443183 | 4.7966ms | 70103 | 30 | 1645.56 | 16711.4 | 0.546327 | 1(Win) |
| glaze | 3825.01 | 0.528787 | 4.99563ms | 70103 | 30 | 256266 | 17478.5 | 0.571917 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 795.675 | 0.0694463 | 4.10747ms | 11812 | 30 | 2899.98 | 14157.5 | 2.75021 | 1(Win) |
| glaze | 733.831 | 0.366421 | 4.32268ms | 11812 | 30 | 94915.4 | 15350.7 | 2.98205 | 2(Loss) |
| simdjson (ondemand) | 688.782 | 1.5886 | 4.47204ms | 11812 | 30 | 2.02504e+06 | 16354.7 | 3.17704 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3169.58 | 0.175905 | 1.35208ms | 11812 | 30 | 1172.52 | 3554.03 | 0.680133 | 1(Win) |
| glaze | 2865.2 | 0.0866077 | 1.44061ms | 11812 | 30 | 347.834 | 3931.6 | 0.75811 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1647.42 | 1.41169 | 4.85528ms | 31235 | 30 | 1.95468e+06 | 18081.6 | 1.32862 | 1(Win) |
| jsonifier | 1486.73 | 1.30425 | 5.45508ms | 31235 | 30 | 2.04863e+06 | 20036 | 1.47257 | 2(Loss) |
| glaze | 1179.07 | 1.32391 | 6.56914ms | 31235 | 30 | 3.35617e+06 | 25264 | 1.85716 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4759.74 | 0.0891611 | 2.13592ms | 31235 | 30 | 934.092 | 6258.33 | 0.453523 | 1(Win) |
| glaze | 3597.82 | 1.383 | 2.54783ms | 31235 | 30 | 393342 | 8279.47 | 0.606683 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2151.33 | 0.369994 | 12.532ms | 108313 | 30 | 946797 | 48014.5 | 1.01872 | 1(Win) |
| glaze | 1347.94 | 0.398748 | 18.9436ms | 108313 | 30 | 2.80117e+06 | 76632.1 | 1.62625 | 2(Loss) |
| simdjson (ondemand) | 1068.26 | 0.947778 | 23.4154ms | 108313 | 30 | 2.51965e+07 | 96694.8 | 2.0522 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2737.81 | 1.1266 | 26.7744ms | 108313 | 32 | 5.78155e+06 | 37729.2 | 0.798895 | 1(Win) |
| glaze | 2490.74 | 0.768394 | 9.93442ms | 108313 | 30 | 3.04644e+06 | 41471.7 | 0.879644 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1998.97 | 0.907354 | 24.9585ms | 213963 | 30 | 2.57359e+07 | 102078 | 1.09661 | 1(Win) |
| jsonifier STATISTICAL TIE | 1789.5 | 0.313934 | 28.3248ms | 213963 | 30 | 3.84425e+06 | 114027 | 1.22527 | 2(Tie) |
| glaze STATISTICAL TIE | 1777.23 | 0.373936 | 28.589ms | 213963 | 30 | 5.52979e+06 | 114814 | 1.23374 | 2(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4911.9 | 1.3522 | 27.7614ms | 213963 | 32 | 1.00975e+07 | 41542.2 | 0.445783 | 1(Win) |
| glaze | 3366.5 | 0.857369 | 16.2441ms | 213963 | 30 | 8.10175e+06 | 60612.3 | 0.65099 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 550.918 | 0.286608 | 760.589ms | 1834197 | 30 | 2.48438e+09 | 3.17512e+06 | 3.9812 | 1(Win) |
| glaze | 391.355 | 0.516527 | 1071.79ms | 1834197 | 30 | 1.59904e+10 | 4.46967e+06 | 5.60451 | 2(Loss) |
| simdjson (ondemand) | 368.658 | 0.115917 | 1138.72ms | 1834197 | 30 | 9.07536e+08 | 4.74485e+06 | 5.94957 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 657.61 | 0.540304 | 637.803ms | 1834197 | 30 | 6.19659e+09 | 2.65998e+06 | 3.33518 | 1(Win) |
| glaze | 355.767 | 0.11943 | 1175.01ms | 1833577 | 30 | 1.03375e+09 | 4.91512e+06 | 6.16529 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1775.81 | 0.331576 | 1285.85ms | 9930848 | 30 | 9.38139e+09 | 5.33322e+06 | 1.23514 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1770.89 | 0.396722 | 1284.41ms | 9930848 | 30 | 1.35046e+10 | 5.34804e+06 | 1.23855 | 1(Tie) |
| glaze | 1561.12 | 0.153172 | 1461.36ms | 9930848 | 30 | 2.59049e+09 | 6.06669e+06 | 1.40502 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1736.4 | 0.381866 | 1297.41ms | 9930848 | 30 | 1.30142e+10 | 5.45429e+06 | 1.26319 | 1(Win) |
| glaze | 1228.99 | 0.145456 | 1854.22ms | 9930228 | 30 | 3.76886e+09 | 7.7057e+06 | 1.78472 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1006.09 | 0.346031 | 146.527ms | 642697 | 30 | 1.33319e+08 | 609216 | 2.17974 | 1(Win) |
| glaze | 833.074 | 0.213698 | 177.5ms | 642697 | 30 | 7.41597e+07 | 735737 | 2.63236 | 2(Loss) |
| simdjson (ondemand) | 742.163 | 0.682038 | 207.123ms | 642697 | 30 | 9.51814e+08 | 825861 | 2.95475 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1119.15 | 0.337689 | 131.483ms | 642697 | 30 | 1.0261e+08 | 547668 | 1.95924 | 1(Win) |
| glaze | 861.547 | 0.309855 | 170.172ms | 642692 | 30 | 1.45776e+08 | 711416 | 2.54499 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1357.2 | 0.680338 | 212.085ms | 1225964 | 30 | 1.03047e+09 | 861455 | 1.61571 | 1(Win) |
| jsonifier STATISTICAL TIE | 1316.99 | 0.615544 | 215.1ms | 1225964 | 30 | 8.95837e+08 | 887758 | 1.6651 | 2(Tie) |
| glaze STATISTICAL TIE | 1306.53 | 0.505236 | 217.584ms | 1225964 | 30 | 6.13239e+08 | 894870 | 1.67843 | 2(Tie) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1239.27 | 0.103537 | 227.597ms | 1225970 | 30 | 2.86243e+07 | 943436 | 1.76948 | 1(Win) |
| jsonifier | 1102.1 | 0.420046 | 254.306ms | 1225964 | 30 | 5.95697e+08 | 1.06085e+06 | 1.98969 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 672.695 | 0.173296 | 142.028ms | 409725 | 30 | 3.03982e+07 | 580864 | 3.26024 | 1(Win) |
| simdjson (ondemand) | 633.103 | 0.179959 | 149.048ms | 409725 | 30 | 3.70086e+07 | 617189 | 3.46384 | 2(Loss) |
| glaze | 506.766 | 0.151014 | 186.007ms | 409725 | 30 | 4.06749e+07 | 771054 | 4.32742 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1941.22 | 0.396668 | 48.9563ms | 409725 | 30 | 1.91255e+07 | 201288 | 1.12962 | 1(Win) |
| glaze | 1869.94 | 1.32224 | 50.1937ms | 409725 | 30 | 2.29021e+08 | 208961 | 1.17233 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1147.53 | 1.46285 | 155.795ms | 785750 | 30 | 2.73756e+09 | 653011 | 1.91091 | 1(Win) |
| jsonifier | 945.327 | 0.144759 | 191.366ms | 785750 | 30 | 3.95016e+07 | 792688 | 2.31994 | 2(Loss) |
| glaze | 801.265 | 0.119575 | 225.083ms | 785750 | 30 | 3.75164e+07 | 935208 | 2.73686 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2958.12 | 0.340402 | 61.7274ms | 785750 | 30 | 2.23071e+07 | 253319 | 0.740955 | 1(Win) |
| glaze | 2256.31 | 1.03944 | 80.6426ms | 785750 | 30 | 3.5751e+08 | 332113 | 0.971762 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 775.159 | 1.26161 | 2483.76ms | 8587914 | 30 | 5.33049e+11 | 1.05657e+07 | 2.8297 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 757.44 | 0.276103 | 2609.82ms | 8587914 | 30 | 2.67389e+10 | 1.08128e+07 | 2.89587 | 1(Tie) |
| glaze | 682.367 | 0.200109 | 2877.29ms | 8587914 | 30 | 1.73059e+10 | 1.20024e+07 | 3.21453 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2357.39 | 0.134633 | 834.737ms | 8588126 | 30 | 6.56387e+08 | 3.4743e+06 | 0.930391 | 1(Tie) |
| glaze STATISTICAL TIE | 2341.5 | 0.325313 | 851.984ms | 8588126 | 30 | 3.88447e+09 | 3.49787e+06 | 0.936734 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 869.097 | 0.0808542 | 2591.93ms | 9804437 | 30 | 2.27005e+09 | 1.07586e+07 | 2.52384 | 1(Win) |
| jsonifier | 786.335 | 0.0667416 | 2860.34ms | 9804437 | 30 | 1.88949e+09 | 1.18909e+07 | 2.7895 | 2(Loss) |
| glaze | 720.824 | 0.243185 | 3109.74ms | 9804437 | 30 | 2.98525e+10 | 1.29716e+07 | 3.04294 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2661.54 | 0.381962 | 961.268ms | 11078090 | 30 | 6.89647e+09 | 3.96947e+06 | 0.824098 | 1(Win) |
| glaze | 2406.43 | 0.275472 | 1059.61ms | 11078090 | 30 | 4.38795e+09 | 4.39028e+06 | 0.911473 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 4316.54 | 0.435062 | 14.6382ms | 264040 | 30 | 1.93238e+06 | 58335.7 | 0.50779 | 1(Win) |
| jsonifier | 4229.33 | 0.572722 | 15.0316ms | 264040 | 30 | 3.48824e+06 | 59538.6 | 0.518297 | 2(Loss) |
| glaze | 1326.71 | 0.54803 | 45.9357ms | 264040 | 30 | 3.24579e+07 | 189799 | 1.65292 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5657.26 | 1.41808 | 17.1944ms | 399947 | 30 | 2.7423e+07 | 67421.2 | 0.387495 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 5616.22 | 0.511533 | 16.978ms | 399947 | 30 | 3.62064e+06 | 67913.9 | 0.390339 | 1(Tie) |
| glaze | 1776.16 | 0.26198 | 52.166ms | 399947 | 30 | 9.4951e+06 | 214744 | 1.23464 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1146.45 | 0.311914 | 53.9796ms | 264040 | 30 | 1.40805e+07 | 219641 | 1.91271 | 1(Win) |
| simdjson (ondemand) | 1109.11 | 0.434397 | 55.3547ms | 264040 | 30 | 2.91801e+07 | 227037 | 1.97716 | 2(Loss) |
| glaze | 966.411 | 0.550065 | 63.5089ms | 264040 | 30 | 6.16261e+07 | 260560 | 2.26917 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4183.19 | 0.709501 | 15.3208ms | 264040 | 30 | 5.47207e+06 | 60195.3 | 0.523933 | 1(Win) |
| glaze | 3420.54 | 1.98987 | 18.638ms | 263923 | 30 | 6.43186e+07 | 73583.9 | 0.640875 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1726.91 | 0.267829 | 54.9135ms | 399947 | 30 | 1.04979e+07 | 220868 | 1.26984 | 1(Win) |
| glaze | 1244.19 | 0.319931 | 75.153ms | 399947 | 30 | 2.88577e+07 | 306560 | 1.76261 | 2(Loss) |
| jsonifier | 1223.84 | 0.226323 | 76.5735ms | 399947 | 30 | 1.49258e+07 | 311659 | 1.79176 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4755.84 | 0.649402 | 20.4283ms | 399947 | 30 | 8.13766e+06 | 80200.2 | 0.460896 | 1(Win) |
| glaze | 3752.24 | 0.826037 | 26.285ms | 399830 | 30 | 2.11393e+07 | 101621 | 0.584306 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1896.22 | 0.182926 | 57.1719ms | 466906 | 30 | 5.53546e+06 | 234823 | 1.15654 | 1(Win) |
| jsonifier | 1762.33 | 0.345722 | 61.3434ms | 466906 | 30 | 2.28907e+07 | 252663 | 1.24434 | 2(Loss) |
| simdjson (ondemand) | 822.566 | 0.191224 | 132.031ms | 466906 | 30 | 3.21457e+07 | 541326 | 2.66533 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2782.57 | 0.325984 | 59.5871ms | 699405 | 30 | 1.8318e+07 | 239708 | 0.787893 | 1(Win) |
| glaze | 2152.08 | 0.229057 | 75.134ms | 699405 | 30 | 1.51198e+07 | 309934 | 1.01908 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2859.32 | 0.420293 | 51.5411ms | 631514 | 30 | 2.35107e+07 | 210630 | 0.766919 | 1(Win) |
| glaze | 1627.96 | 0.165452 | 89.413ms | 631514 | 30 | 1.12395e+07 | 369948 | 1.34718 | 2(Loss) |
