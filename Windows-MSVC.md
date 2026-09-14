# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36256.0 compiler).  

Latest Results: (Sep 14, 2026)
#### Using the following commits:
----
| Jsonifier: [8a8469e](https://github.com/nihilai-collective/jsonifier/commit/8a8469e)  
| Glaze: [29f478d](https://github.com/stephenberry/glaze/commit/29f478d)  
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
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 427.149 | 0.227581 | 2.7233ms | 1811 | 30 | 2540.23 | 4043.33 | 5.41003 | 1(Win) |
| glaze | 157.678 | 0.275922 | 4.0897ms | 1811 | 30 | 27402.3 | 10953.3 | 14.7469 | 2(Loss) |
| simdjson (ondemand) | 95.9858 | 0.0591853 | 5.8203ms | 1811 | 30 | 3402.3 | 17993.3 | 24.2308 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 310.258 | 0.179296 | 2.8166ms | 1811 | 30 | 2988.51 | 5566.67 | 7.46091 | 1(Win) |
| glaze | 157.493 | 2.00111 | 16.9333ms | 1798 | 64 | 3.03794e+06 | 10887.5 | 14.7389 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1019.39 | 0.216763 | 2.5067ms | 3873 | 30 | 1850.57 | 3623.33 | 2.2634 | 1(Win) |
| glaze | 661.537 | 0.15079 | 2.6676ms | 3873 | 30 | 2126.44 | 5583.33 | 3.49904 | 2(Loss) |
| simdjson (ondemand) | 228.563 | 0.0636345 | 5.3559ms | 3873 | 30 | 3172.41 | 16160 | 10.172 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1099.28 | 0.86329 | 2.4149ms | 3873 | 30 | 25241.4 | 3360 | 2.09704 | 1(Win) |
| glaze | 758.435 | 0.223424 | 2.6134ms | 3873 | 30 | 3551.72 | 4870 | 3.04715 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1159.42 | 0.247241 | 2.3959ms | 3862 | 30 | 1850.57 | 3176.67 | 1.98967 | 1(Win) |
| glaze | 557.481 | 0.143931 | 2.9994ms | 3862 | 30 | 2712.64 | 6606.67 | 4.1527 | 2(Loss) |
| simdjson (ondemand) | 234.941 | 0.0729127 | 5.2776ms | 3862 | 30 | 3919.54 | 15676.7 | 9.91714 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1582.99 | 0.352941 | 2.0226ms | 3862 | 30 | 2022.99 | 2326.67 | 1.44683 | 1(Win) |
| glaze | 744.56 | 0.18728 | 2.6474ms | 3862 | 30 | 2574.71 | 4946.67 | 3.11611 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 786.849 | 0.2849 | 2.9869ms | 905 | 32 | 312.5 | 1096.88 | 2.87714 | 1(Win) |
| glaze | 149.839 | 0.157937 | 2.7317ms | 905 | 30 | 2482.76 | 5760 | 15.4573 | 2(Loss) |
| simdjson (ondemand) | 67.0784 | 0.659618 | 4.5278ms | 905 | 30 | 216092 | 12866.7 | 34.7051 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 385.876 | 0.400084 | 1.9937ms | 905 | 30 | 2402.3 | 2236.67 | 5.95484 | 1(Win) |
| glaze | 126.181 | 0.400229 | 3.0626ms | 905 | 30 | 22482.8 | 6840 | 18.3691 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1135.16 | 0.11513 | 3.6578ms | 9578 | 30 | 2574.71 | 8046.67 | 2.04218 | 1(Win) |
| glaze | 868.004 | 0.0874425 | 3.9542ms | 9578 | 30 | 2540.23 | 10523.3 | 2.6779 | 2(Loss) |
| simdjson (ondemand) | 388.926 | 1.71315 | 33.4541ms | 9578 | 64 | 1.03606e+07 | 23485.9 | 5.98894 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2418.61 | 0.24365 | 2.337ms | 9578 | 30 | 2540.23 | 3776.67 | 0.956167 | 1(Win) |
| glaze | 1605.32 | 0.212339 | 2.8798ms | 9578 | 30 | 4379.31 | 5690 | 1.44243 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2357.77 | 1.29701 | 24.5627ms | 233995 | 30 | 4.52081e+07 | 94646.7 | 0.98868 | 1(Win) |
| simdjson (ondemand) | 1459.48 | 0.885556 | 38.5911ms | 233995 | 30 | 5.50007e+07 | 152900 | 1.59742 | 2(Loss) |
| glaze | 1012.81 | 1.41487 | 54.1683ms | 233995 | 30 | 2.9155e+08 | 220333 | 2.30211 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2987.8 | 1.29069 | 29.2969ms | 346753 | 30 | 6.1221e+07 | 110680 | 0.780107 | 1(Win) |
| simdjson (ondemand) | 1881.91 | 0.856419 | 43.9333ms | 346753 | 30 | 6.79417e+07 | 175720 | 1.239 | 2(Loss) |
| glaze | 1262.06 | 1.01294 | 69.9722ms | 346753 | 30 | 2.11335e+08 | 262023 | 1.84735 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 749.95 | 0.886408 | 73.0609ms | 233995 | 30 | 2.08707e+08 | 297560 | 3.10875 | 1(Win) |
| glaze | 681.889 | 1.82575 | 105.346ms | 233995 | 30 | 1.071e+09 | 327260 | 3.41941 | 2(Loss) |
| simdjson (ondemand) | 438.275 | 0.497369 | 136.112ms | 233995 | 30 | 1.92397e+08 | 509167 | 5.32035 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1387.75 | 1.84073 | 201.056ms | 233995 | 64 | 5.60726e+08 | 160803 | 1.67957 | 1(Win) |
| glaze | 1128.53 | 1.48394 | 1073.55ms | 233995 | 256 | 2.20427e+09 | 197740 | 2.06584 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 878.753 | 1.42113 | 90.4756ms | 346753 | 30 | 8.58012e+08 | 376317 | 2.65332 | 1(Tie) |
| jsonifier STATISTICAL TIE | 873.292 | 0.691343 | 93.2031ms | 346753 | 30 | 2.05604e+08 | 378670 | 2.66984 | 1(Tie) |
| simdjson (ondemand) | 617.703 | 0.50252 | 130.232ms | 346753 | 30 | 2.17125e+08 | 535353 | 3.77494 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1890.16 | 0.691278 | 44.1901ms | 346753 | 30 | 4.38805e+07 | 174953 | 1.23327 | 1(Win) |
| glaze | 1178.28 | 0.957226 | 69.5092ms | 346753 | 30 | 2.16516e+08 | 280653 | 1.97869 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2271.68 | 1.35297 | 25.2029ms | 233995 | 30 | 5.29926e+07 | 98233.3 | 1.02611 | 1(Win) |
| glaze | 1039.69 | 0.733146 | 53.2166ms | 233995 | 30 | 7.42865e+07 | 214637 | 2.24253 | 2(Loss) |
| simdjson (ondemand) | 981.865 | 0.778179 | 57.2567ms | 233995 | 30 | 9.38405e+07 | 227277 | 2.3748 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2938.94 | 0.861376 | 29.0207ms | 346753 | 30 | 2.81817e+07 | 112520 | 0.792891 | 1(Win) |
| simdjson (ondemand) | 1312.9 | 0.828021 | 62.8831ms | 346753 | 30 | 1.30491e+08 | 251877 | 1.7759 | 2(Loss) |
| glaze | 1262.37 | 0.696934 | 64.5868ms | 346753 | 30 | 9.99942e+07 | 261960 | 1.84695 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 770.687 | 1.06558 | 70.3745ms | 233995 | 30 | 2.85594e+08 | 289553 | 3.02533 | 1(Win) |
| glaze | 690.391 | 1.12362 | 79.054ms | 233995 | 30 | 3.95713e+08 | 323230 | 3.37726 | 2(Loss) |
| simdjson (ondemand) | 108.086 | 0.0649784 | 512.413ms | 233995 | 30 | 5.39929e+07 | 2.06461e+06 | 21.5756 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1514.28 | 1.78928 | 36.1225ms | 233995 | 30 | 2.08582e+08 | 147367 | 1.53929 | 1(Win) |
| glaze | 1118.41 | 2.35695 | 241.789ms | 233995 | 64 | 1.41543e+09 | 199528 | 2.08453 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 857.901 | 1.02913 | 94.2865ms | 346753 | 30 | 4.72093e+08 | 385463 | 2.71777 | 1(Tie) |
| jsonifier STATISTICAL TIE | 847.813 | 1.1859 | 94.741ms | 346753 | 30 | 6.41884e+08 | 390050 | 2.75017 | 1(Tie) |
| simdjson (ondemand) | 146.262 | 0.153468 | 538.659ms | 346753 | 30 | 3.61185e+08 | 2.26093e+06 | 15.9443 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1903.39 | 1.65704 | 42.9261ms | 346753 | 30 | 2.48639e+08 | 173737 | 1.22469 | 1(Win) |
| glaze | 1147.8 | 0.73054 | 71.3517ms | 346753 | 30 | 1.32897e+08 | 288107 | 2.03136 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 439.132 | 1.85874 | 118.847ms | 94651 | 32 | 4.67144e+08 | 205556 | 5.30907 | 1(Win) |
| glaze | 386.019 | 2.13454 | 286.888ms | 94651 | 64 | 1.5945e+09 | 233839 | 6.03946 | 2(Loss) |
| simdjson (ondemand) | 336.563 | 1.73426 | 67.6698ms | 94651 | 30 | 6.49037e+08 | 268200 | 6.92721 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1635.17 | 1.36132 | 69.2856ms | 94651 | 64 | 3.61432e+07 | 55203.1 | 1.42469 | 1(Win) |
| jsonifier | 1518.87 | 1.71277 | 16.1242ms | 94651 | 30 | 3.10836e+07 | 59430 | 1.53411 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 539.875 | 2.06678 | 308.835ms | 136024 | 64 | 1.57838e+09 | 240283 | 4.31851 | 1(Tie) |
| jsonifier STATISTICAL TIE | 526.137 | 1.19242 | 61.013ms | 136024 | 30 | 2.59306e+08 | 246557 | 4.43111 | 1(Tie) |
| simdjson (ondemand) | 461.187 | 2.44409 | 70.1831ms | 136024 | 30 | 1.41786e+09 | 281280 | 5.05568 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1976.88 | 1.89517 | 17.6451ms | 136024 | 30 | 4.63968e+07 | 65620 | 1.17891 | 1(Win) |
| glaze | 1286.76 | 0.791391 | 26.354ms | 136046 | 30 | 1.91022e+07 | 100830 | 1.8114 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 337.469 | 1.11527 | 1483.42ms | 2090234 | 30 | 1.30197e+11 | 5.90692e+06 | 6.91028 | 1(Win) |
| glaze STATISTICAL TIE | 198.79 | 1.75495 | 12065.2ms | 2090234 | 64 | 1.98204e+12 | 1.00277e+07 | 11.7311 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 197.921 | 0.786839 | 2461.82ms | 2090234 | 30 | 1.88408e+11 | 1.00717e+07 | 11.7819 | 2(Tie) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 518.448 | 1.63678 | 883.311ms | 2090234 | 30 | 1.18817e+11 | 3.84494e+06 | 4.49783 | 1(Win) |
| glaze | 421.953 | 0.147294 | 1146.33ms | 2090234 | 30 | 1.45263e+09 | 4.72423e+06 | 5.5264 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 828.009 | 1.03108 | 1826.65ms | 6661897 | 30 | 1.87774e+11 | 7.67296e+06 | 2.81641 | 1(Win) |
| simdjson (ondemand) | 585.36 | 0.503613 | 2625.8ms | 6661897 | 30 | 8.96325e+10 | 1.08536e+07 | 3.98384 | 2(Loss) |
| glaze | 563.228 | 0.605117 | 2710.71ms | 6661897 | 30 | 1.39774e+11 | 1.12801e+07 | 4.1405 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 735.924 | 0.6212 | 378.943ms | 500299 | 32 | 5.19047e+08 | 648331 | 3.16854 | 1(Win) |
| glaze | 463.166 | 0.274059 | 250.954ms | 500299 | 30 | 2.3911e+08 | 1.03013e+06 | 5.03474 | 2(Loss) |
| simdjson (ondemand) | 264.619 | 0.272073 | 432.521ms | 500299 | 30 | 7.21956e+08 | 1.80305e+06 | 8.81227 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1631.35 | 1.90091 | 70.5708ms | 500299 | 30 | 9.27275e+08 | 292470 | 1.42884 | 1(Win) |
| glaze | 1300.24 | 0.887733 | 89.3911ms | 500299 | 30 | 3.18346e+08 | 366950 | 1.79316 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1344.25 | 0.341347 | 622.646ms | 1439562 | 32 | 3.88906e+08 | 1.02129e+06 | 1.73457 | 1(Win) |
| glaze | 938.837 | 0.44096 | 365.659ms | 1439562 | 30 | 1.24738e+09 | 1.46231e+06 | 2.48386 | 2(Loss) |
| simdjson (ondemand) | 701.636 | 0.161825 | 471.095ms | 1439562 | 30 | 3.0078e+08 | 1.95667e+06 | 3.32354 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1878.12 | 0.458155 | 179.808ms | 1439562 | 30 | 3.36482e+08 | 730983 | 1.24137 | 1(Win) |
| glaze | 857.173 | 0.303697 | 388.862ms | 1439584 | 30 | 7.09804e+08 | 1.60165e+06 | 2.7201 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 676.311 | 1.54786 | 21.1515ms | 56369 | 30 | 4.54122e+07 | 79486.7 | 3.44649 | 1(Win) |
| glaze | 622.123 | 1.44152 | 22.5083ms | 56369 | 30 | 4.65471e+07 | 86410 | 3.74621 | 2(Loss) |
| simdjson (ondemand) | 287.08 | 0.897553 | 46.5852ms | 56369 | 30 | 8.47453e+07 | 187257 | 8.12026 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1428.08 | 2.36142 | 10.6814ms | 56369 | 30 | 2.37053e+07 | 37643.3 | 1.62989 | 1(Win) |
| glaze | 1267.87 | 0.161512 | 11.8514ms | 56369 | 30 | 140690 | 42400 | 1.83779 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 872.076 | 1.56582 | 26.3852ms | 94370 | 30 | 7.83366e+07 | 103200 | 2.6727 | 1(Win) |
| jsonifier | 719.717 | 1.60684 | 32.4795ms | 94370 | 30 | 1.21119e+08 | 125047 | 3.23863 | 2(Loss) |
| simdjson (ondemand) | 463.518 | 0.973924 | 52.2353ms | 94370 | 30 | 1.07277e+08 | 194163 | 5.02994 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2292.95 | 1.33423 | 10.8213ms | 94370 | 30 | 8.22741e+06 | 39250 | 1.01608 | 1(Win) |
| glaze | 1144.97 | 1.18258 | 20.4107ms | 94370 | 30 | 2.59217e+07 | 78603.3 | 2.03485 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 607.692 | 1.67395 | 22.6343ms | 52708 | 30 | 5.75166e+07 | 82716.7 | 3.83436 | 1(Win) |
| glaze | 497.276 | 1.30089 | 27.5376ms | 52708 | 30 | 5.18752e+07 | 101083 | 4.68739 | 2(Loss) |
| simdjson (ondemand) | 418.305 | 1.68019 | 34.2706ms | 52708 | 30 | 1.22295e+08 | 120167 | 5.57177 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2315.71 | 0.488912 | 6.7839ms | 52708 | 30 | 337885 | 21706.7 | 1.00503 | 1(Win) |
| glaze | 1913.2 | 0.205602 | 7.9963ms | 52708 | 30 | 87540.2 | 26273.3 | 1.21654 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 600.526 | 0.907268 | 181.725ms | 70103 | 64 | 6.52922e+07 | 111328 | 3.88094 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 529.884 | 2.16057 | 31.4948ms | 70103 | 30 | 2.22931e+08 | 126170 | 4.399 | 2(Tie) |
| jsonifier STATISTICAL TIE | 509.634 | 2.35666 | 36.3453ms | 70103 | 30 | 2.8673e+08 | 131183 | 4.57006 | 2(Tie) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2891.83 | 0.108898 | 15.4344ms | 70103 | 32 | 20282.3 | 23118.8 | 0.804386 | 1(Win) |
| glaze | 1658.4 | 2.12362 | 11.137ms | 70103 | 30 | 2.19874e+07 | 40313.3 | 1.40426 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 514.705 | 1.90204 | 29.2257ms | 11812 | 64 | 1.10904e+07 | 21885.9 | 4.52316 | 1(Win) |
| glaze | 396.276 | 0.133804 | 8.4507ms | 11812 | 30 | 43402.3 | 28426.7 | 5.87769 | 2(Loss) |
| simdjson (ondemand) | 254.093 | 0.0744061 | 12.4251ms | 11812 | 30 | 32643.7 | 44333.3 | 9.17028 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1122.36 | 0.433859 | 3.8433ms | 11812 | 30 | 56885.1 | 10036.7 | 2.07249 | 1(Win) |
| glaze | 1016.37 | 0.263436 | 4.1511ms | 11812 | 30 | 25574.7 | 11083.3 | 2.28503 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 938.698 | 0.109302 | 9.6148ms | 31235 | 30 | 36092 | 31733.3 | 2.48025 | 1(Win) |
| glaze | 811.441 | 0.0926767 | 10.4105ms | 31235 | 30 | 34724.1 | 36710 | 2.87163 | 2(Loss) |
| simdjson (ondemand) | 625.098 | 0.099468 | 13.0918ms | 31235 | 30 | 67402.3 | 47653.3 | 3.72827 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2478.89 | 0.405103 | 4.3402ms | 31235 | 30 | 71092 | 12016.7 | 0.936809 | 1(Win) |
| glaze | 1490.64 | 0.391378 | 6.2987ms | 31235 | 30 | 183506 | 19983.3 | 1.56172 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1238.45 | 1.37851 | 22.1785ms | 108313 | 30 | 3.96593e+07 | 83406.7 | 1.88204 | 1(Win) |
| glaze | 541.106 | 1.11346 | 47.3999ms | 108313 | 30 | 1.35539e+08 | 190897 | 4.30824 | 2(Loss) |
| simdjson (ondemand) | 315.926 | 0.654812 | 80.635ms | 108313 | 30 | 1.37513e+08 | 326960 | 7.38004 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1712.36 | 1.65616 | 15.863ms | 108313 | 30 | 2.99432e+07 | 60323.3 | 1.36133 | 1(Win) |
| glaze | 1308.2 | 1.10636 | 20.4998ms | 108313 | 30 | 2.28942e+07 | 78960 | 1.78112 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1070.93 | 1.12517 | 48.1145ms | 213963 | 30 | 1.37885e+08 | 190537 | 2.17691 | 1(Win) |
| glaze | 852.13 | 0.937717 | 59.5838ms | 213963 | 30 | 1.51262e+08 | 239460 | 2.73584 | 2(Loss) |
| simdjson (ondemand) | 589.204 | 0.624862 | 84.8611ms | 213963 | 30 | 1.40487e+08 | 346317 | 3.95704 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2804.82 | 1.38648 | 18.6736ms | 213963 | 30 | 3.05219e+07 | 72750 | 0.830884 | 1(Win) |
| glaze | 1278.86 | 0.992627 | 39.89ms | 213963 | 30 | 7.52529e+07 | 159557 | 1.82288 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 346.497 | 0.577128 | 1225.31ms | 1834197 | 30 | 2.5466e+10 | 5.04832e+06 | 6.72978 | 1(Win) |
| glaze | 187.919 | 0.535307 | 2236.69ms | 1834197 | 30 | 7.44868e+10 | 9.30842e+06 | 12.4098 | 2(Loss) |
| simdjson (ondemand) | 170.62 | 0.422983 | 2452.5ms | 1834197 | 30 | 5.64156e+10 | 1.02522e+07 | 13.668 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 332.415 | 0.0686917 | 1299.03ms | 1834197 | 30 | 3.91976e+08 | 5.26217e+06 | 7.01517 | 1(Win) |
| glaze | 268.653 | 0.106559 | 1615.92ms | 1833577 | 30 | 1.44317e+09 | 6.50891e+06 | 8.68021 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1184.17 | 0.20908 | 1975.41ms | 9930848 | 30 | 8.38871e+09 | 7.99786e+06 | 1.96916 | 1(Win) |
| glaze STATISTICAL TIE | 777.58 | 1.72994 | 2936.33ms | 9930848 | 30 | 1.33188e+12 | 1.21798e+07 | 2.99898 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 770.969 | 1.02911 | 2954.66ms | 9930848 | 30 | 4.79455e+11 | 1.22843e+07 | 3.02465 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 978.58 | 2.37606 | 2137.34ms | 9930848 | 30 | 1.58641e+12 | 9.6781e+06 | 2.38275 | 1(Win) |
| glaze | 599.62 | 0.09759 | 3815.69ms | 9930228 | 30 | 7.12685e+09 | 1.57937e+07 | 3.88898 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 670.994 | 0.3097 | 225.196ms | 642697 | 30 | 2.40093e+08 | 913457 | 3.47536 | 1(Win) |
| glaze | 428.881 | 0.333873 | 362.064ms | 642697 | 30 | 6.83005e+08 | 1.42912e+06 | 5.43719 | 2(Loss) |
| simdjson (ondemand) | 424.655 | 0.177489 | 352.099ms | 642697 | 30 | 1.9688e+08 | 1.44334e+06 | 5.49158 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 632.626 | 0.295603 | 234.988ms | 642697 | 30 | 2.4607e+08 | 968857 | 3.68604 | 1(Win) |
| glaze | 393.329 | 0.218175 | 376.187ms | 642692 | 30 | 3.46758e+08 | 1.55829e+06 | 5.92786 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 817.175 | 0.288523 | 347.243ms | 1225964 | 30 | 5.1122e+08 | 1.43075e+06 | 2.85376 | 1(Win) |
| simdjson (ondemand) | 756.364 | 0.20671 | 372.133ms | 1225964 | 30 | 3.06292e+08 | 1.54578e+06 | 3.0832 | 2(Loss) |
| glaze | 727.22 | 0.163164 | 393.682ms | 1225964 | 30 | 2.06441e+08 | 1.60773e+06 | 3.2067 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 910.64 | 0.286391 | 310.085ms | 1225964 | 30 | 4.05603e+08 | 1.2839e+06 | 2.56049 | 1(Win) |
| glaze | 685.235 | 0.143269 | 412.656ms | 1225970 | 30 | 1.79269e+08 | 1.70624e+06 | 3.40276 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 460.836 | 0.387433 | 205.837ms | 409725 | 30 | 3.23747e+08 | 847903 | 5.06015 | 1(Win) |
| glaze | 304.577 | 0.296907 | 309.93ms | 409725 | 30 | 4.35263e+08 | 1.28291e+06 | 7.65632 | 2(Loss) |
| simdjson (ondemand) | 260.947 | 0.177187 | 362.835ms | 409725 | 30 | 2.11186e+08 | 1.49741e+06 | 8.93651 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1067.4 | 0.690517 | 88.7256ms | 409725 | 30 | 1.9169e+08 | 366070 | 2.18421 | 1(Win) |
| glaze | 1020.66 | 0.582646 | 94.6956ms | 409725 | 30 | 1.49265e+08 | 382837 | 2.28439 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 603.714 | 0.247736 | 301.433ms | 785750 | 30 | 2.83666e+08 | 1.24123e+06 | 3.8627 | 1(Win) |
| glaze | 520.57 | 0.20069 | 350.542ms | 785750 | 30 | 2.50371e+08 | 1.43948e+06 | 4.47958 | 2(Loss) |
| simdjson (ondemand) | 477.922 | 0.234504 | 376.344ms | 785750 | 30 | 4.0558e+08 | 1.56793e+06 | 4.87939 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1721.94 | 0.549438 | 107.275ms | 785750 | 30 | 1.7151e+08 | 435177 | 1.3541 | 1(Win) |
| glaze | 819.983 | 0.453401 | 220.923ms | 785750 | 30 | 5.15045e+08 | 913860 | 2.84341 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 477.431 | 0.805949 | 4435.59ms | 8587914 | 30 | 5.73443e+11 | 1.71544e+07 | 4.88428 | 1(Win) |
| glaze STATISTICAL TIE | 342.88 | 2.29379 | 5794.73ms | 8587914 | 30 | 9.00578e+12 | 2.38861e+07 | 6.80118 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 334.979 | 0.673219 | 6011.54ms | 8587914 | 30 | 8.12781e+11 | 2.44495e+07 | 6.96161 | 2(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 431.671 | 2.23068 | 5517.45ms | 9804437 | 30 | 7.00386e+12 | 2.16606e+07 | 5.40215 | 1(Win) |
| simdjson (ondemand) | 362.526 | 1.08622 | 6316.12ms | 9804437 | 30 | 2.35464e+12 | 2.57919e+07 | 6.43262 | 2(Loss) |
| glaze | 341.418 | 0.941968 | 6355.03ms | 9804437 | 30 | 1.99648e+12 | 2.73864e+07 | 6.83028 | 3(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2043.73 | 1.50075 | 31.2786ms | 264040 | 30 | 1.02572e+08 | 123210 | 1.14064 | 1(Win) |
| simdjson (ondemand) | 1377.38 | 0.841955 | 45.5146ms | 264040 | 30 | 7.10773e+07 | 182817 | 1.69272 | 2(Loss) |
| glaze | 775.749 | 0.745477 | 80.2063ms | 264040 | 30 | 1.75666e+08 | 324600 | 3.00577 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2749.69 | 1.14296 | 35.1893ms | 399947 | 30 | 7.54088e+07 | 138713 | 0.847629 | 1(Win) |
| simdjson (ondemand) | 1825.26 | 0.883882 | 51.919ms | 399947 | 30 | 1.02344e+08 | 208967 | 1.27722 | 2(Loss) |
| glaze | 1040 | 0.630348 | 103.78ms | 399947 | 30 | 1.60333e+08 | 366750 | 2.24211 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 780.631 | 1.97732 | 79.5754ms | 264040 | 30 | 1.22046e+09 | 322570 | 2.98667 | 1(Win) |
| glaze | 492.602 | 0.729847 | 125.931ms | 264040 | 30 | 4.17573e+08 | 511180 | 4.7332 | 2(Loss) |
| simdjson (ondemand) | 418.168 | 0.58833 | 148.4ms | 264040 | 30 | 3.76532e+08 | 602170 | 5.57581 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2128.92 | 1.07281 | 29.9066ms | 264040 | 30 | 4.83044e+07 | 118280 | 1.09489 | 1(Win) |
| glaze | 1630.34 | 0.850375 | 39.0177ms | 263923 | 30 | 5.17063e+07 | 154383 | 1.42989 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 717.611 | 0.79012 | 316.848ms | 399947 | 32 | 5.6437e+08 | 531512 | 3.24899 | 1(Win) |
| glaze | 654.49 | 0.952254 | 140.72ms | 399947 | 30 | 9.23903e+08 | 582773 | 3.56261 | 2(Loss) |
| simdjson (ondemand) | 609.208 | 0.454967 | 152.992ms | 399947 | 30 | 2.4342e+08 | 626090 | 3.8274 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2826.51 | 1.19927 | 34.3417ms | 399947 | 30 | 7.85701e+07 | 134943 | 0.824742 | 1(Win) |
| glaze | 1542.07 | 0.919396 | 61.2279ms | 399830 | 30 | 1.55049e+08 | 247270 | 1.51189 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 990.53 | 0.850566 | 98.9119ms | 466906 | 30 | 4.38593e+08 | 449533 | 2.35403 | 1(Win) |
| glaze | 951.94 | 0.468248 | 114.393ms | 466906 | 30 | 1.43917e+08 | 467757 | 2.44948 | 2(Loss) |
| simdjson (ondemand) | 534.622 | 0.327475 | 201.887ms | 466906 | 30 | 2.23174e+08 | 832880 | 4.36193 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1718.92 | 0.602682 | 94.5988ms | 699405 | 30 | 1.64076e+08 | 388037 | 1.35648 | 1(Win) |
| glaze | 1113.17 | 0.459634 | 147.927ms | 699405 | 30 | 2.27552e+08 | 599193 | 2.09476 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1486.03 | 0.516263 | 99.0881ms | 631514 | 30 | 1.31333e+08 | 405280 | 1.56914 | 1(Win) |
| jsonifier | 1138.77 | 0.418912 | 129.202ms | 631514 | 30 | 1.47253e+08 | 528870 | 2.04771 | 2(Loss) |
