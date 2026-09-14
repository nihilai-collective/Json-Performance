# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 14, 2026)
#### Using the following commits:
----
| Jsonifier: [8a8469e](https://github.com/nihilai-collective/jsonifier/commit/8a8469e)  
| Glaze: [29f478d](https://github.com/stephenberry/glaze/commit/29f478d)  
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
| jsonifier | 755.051 | 0.100713 | 2.4689ms | 1811 | 30 | 159.214 | 2287.4 | 2.85095 | 1(Win) |
| glaze | 672.793 | 0.110985 | 1.05427ms | 1811 | 30 | 243.513 | 2567.07 | 3.21318 | 2(Loss) |
| simdjson (ondemand) | 175.663 | 0.0403102 | 6.18152ms | 1811 | 32 | 502.641 | 9831.94 | 12.4471 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 507.658 | 0.0534305 | 1.71934ms | 1811 | 30 | 99.1276 | 3402.1 | 4.25592 | 1(Win) |
| glaze | 371.167 | 0.366436 | 1.63106ms | 1798 | 30 | 8597.22 | 4619.77 | 5.86978 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1468.52 | 0.0806088 | 1.2052ms | 3873 | 30 | 123.316 | 2515.17 | 1.46942 | 1(Win) |
| glaze | 1286.68 | 0.0819009 | 1.14683ms | 3873 | 30 | 165.826 | 2870.63 | 1.687 | 2(Loss) |
| simdjson (ondemand) | 361.281 | 0.0391946 | 2.96601ms | 3873 | 30 | 481.702 | 10223.6 | 6.05522 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1980.08 | 0.0748267 | 1.09911ms | 3873 | 30 | 58.4471 | 1865.37 | 1.07841 | 1(Win) |
| glaze | 924.721 | 0.393345 | 1.47893ms | 3873 | 30 | 7405.31 | 3994.27 | 2.3386 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1574.96 | 0.112293 | 1.19842ms | 3862 | 30 | 206.878 | 2338.53 | 1.36863 | 1(Win) |
| glaze | 1207.78 | 0.0497879 | 1.1711ms | 3862 | 30 | 69.154 | 3049.47 | 1.7904 | 2(Loss) |
| simdjson (ondemand) | 339.13 | 0.0286496 | 6.72135ms | 3862 | 32 | 309.797 | 10860.4 | 6.45137 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1979.73 | 0.136436 | 1.05327ms | 3862 | 30 | 193.283 | 1860.4 | 1.07304 | 1(Win) |
| glaze | 924.177 | 0.210685 | 1.42995ms | 3862 | 30 | 2114.96 | 3985.27 | 2.34944 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 791.618 | 0.11116 | 0.894888ms | 905 | 30 | 44.0644 | 1090.27 | 2.69606 | 1(Win) |
| glaze | 596.513 | 0.164651 | 0.809104ms | 905 | 30 | 170.257 | 1446.87 | 3.60501 | 2(Loss) |
| simdjson (ondemand) | 148.164 | 0.0576855 | 1.89231ms | 905 | 30 | 338.74 | 5825.13 | 14.7073 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1092.96 | 0.106443 | 0.804646ms | 905 | 30 | 21.1954 | 789.667 | 1.93805 | 1(Win) |
| glaze | 253.192 | 0.188132 | 2.5525ms | 905 | 32 | 1316.05 | 3408.78 | 8.57486 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2168.5 | 0.125878 | 1.50776ms | 9578 | 30 | 843.444 | 4212.27 | 1.00176 | 1(Win) |
| jsonifier | 2152.08 | 0.063798 | 1.73672ms | 9578 | 30 | 219.972 | 4244.4 | 1.0067 | 2(Loss) |
| simdjson (ondemand) | 898.055 | 0.396717 | 2.92626ms | 9578 | 30 | 48845.8 | 10171.2 | 2.43457 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3471.97 | 0.0617415 | 1.43638ms | 9578 | 30 | 79.154 | 2630.87 | 0.624034 | 1(Win) |
| glaze | 2006.42 | 0.114699 | 1.60897ms | 9578 | 30 | 817.982 | 4552.53 | 1.08166 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 4467.62 | 0.732154 | 12.6194ms | 233995 | 30 | 4.01223e+06 | 49949.4 | 0.490552 | 1(Tie) |
| jsonifier STATISTICAL TIE | 4340.41 | 1.35344 | 13.1096ms | 233995 | 30 | 1.45261e+07 | 51413.3 | 0.504955 | 1(Tie) |
| glaze | 1582.31 | 0.230162 | 35.0974ms | 233995 | 30 | 3.16096e+06 | 141031 | 1.38588 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5781.32 | 0.837251 | 14.5228ms | 346753 | 30 | 6.88048e+06 | 57199.6 | 0.379158 | 1(Win) |
| jsonifier | 5440.43 | 1.20492 | 15.1538ms | 346753 | 30 | 1.6092e+07 | 60783.7 | 0.402876 | 2(Loss) |
| glaze | 1993.59 | 0.457107 | 40.7656ms | 346753 | 30 | 1.72476e+07 | 165877 | 1.09999 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1513.04 | 0.648465 | 38.3269ms | 233995 | 30 | 2.74413e+07 | 147488 | 1.4493 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1220.68 | 0.350508 | 45.62ms | 233995 | 30 | 1.23176e+07 | 182811 | 1.79649 | 2(Tie) |
| glaze STATISTICAL TIE | 1214.9 | 0.599718 | 45.1059ms | 233995 | 30 | 3.64037e+07 | 183681 | 1.80503 | 2(Tie) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3051.46 | 0.429079 | 18.4876ms | 233995 | 30 | 2.9539e+06 | 73130.7 | 0.718055 | 1(Win) |
| glaze | 2763.16 | 1.03003 | 20.0654ms | 233995 | 30 | 2.07598e+07 | 80760.7 | 0.793411 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1717.81 | 0.493394 | 47.353ms | 346753 | 30 | 2.70646e+07 | 192507 | 1.27659 | 1(Win) |
| jsonifier | 1614.94 | 0.619422 | 49.5912ms | 346753 | 30 | 4.82637e+07 | 204768 | 1.35749 | 2(Loss) |
| glaze | 1512.26 | 0.650582 | 52.9362ms | 346753 | 30 | 6.07177e+07 | 218673 | 1.45018 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3838.88 | 0.673189 | 21.6446ms | 346753 | 30 | 1.00885e+07 | 86142.1 | 0.570869 | 1(Win) |
| glaze | 2704.22 | 0.697449 | 30.6417ms | 346753 | 30 | 2.18224e+07 | 122286 | 0.810725 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4272.48 | 1.01824 | 13.2881ms | 233995 | 30 | 8.48549e+06 | 52230.8 | 0.512998 | 1(Win) |
| simdjson (ondemand) | 2961.05 | 0.768247 | 19.6058ms | 233995 | 30 | 1.00564e+07 | 75363.4 | 0.740372 | 2(Loss) |
| glaze | 1555.3 | 0.526139 | 34.9106ms | 233995 | 30 | 1.70965e+07 | 143480 | 1.40991 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5510.9 | 0.732756 | 15.4837ms | 346753 | 30 | 5.80009e+06 | 60006.4 | 0.397787 | 1(Win) |
| simdjson (ondemand) | 3760.7 | 0.585621 | 21.9363ms | 346753 | 30 | 7.95535e+06 | 87933 | 0.583022 | 2(Loss) |
| glaze | 1982.96 | 0.505146 | 41.7808ms | 346753 | 30 | 2.12895e+07 | 166765 | 1.10591 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1422.62 | 0.497698 | 39.567ms | 233995 | 30 | 1.82847e+07 | 156862 | 1.5414 | 1(Win) |
| glaze | 1305.51 | 0.617693 | 42.7881ms | 233995 | 30 | 3.34444e+07 | 170934 | 1.67967 | 2(Loss) |
| simdjson (ondemand) | 266.706 | 0.607593 | 198.037ms | 233995 | 30 | 7.75346e+08 | 836709 | 8.22361 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3060.12 | 0.647033 | 18.6812ms | 233995 | 30 | 6.679e+06 | 72923.7 | 0.71614 | 1(Win) |
| glaze | 3000.68 | 0.563318 | 18.6548ms | 233995 | 30 | 5.26506e+06 | 74368.2 | 0.730571 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1577.69 | 0.31401 | 52.3196ms | 346753 | 30 | 1.29958e+07 | 209603 | 1.38997 | 1(Win) |
| jsonifier | 1366.76 | 1.93217 | 53.8717ms | 346753 | 30 | 6.55643e+08 | 241952 | 1.60448 | 2(Loss) |
| simdjson (ondemand) | 396.294 | 0.326233 | 200.14ms | 346753 | 30 | 2.22322e+08 | 834456 | 5.53451 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3763.49 | 0.261549 | 22.1891ms | 346753 | 30 | 1.58449e+06 | 87867.9 | 0.582174 | 1(Win) |
| glaze | 2512.83 | 0.992491 | 31.5405ms | 346753 | 30 | 5.11787e+07 | 131600 | 0.872452 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 818.826 | 0.587826 | 27.2094ms | 94651 | 30 | 1.25975e+07 | 110239 | 2.67732 | 1(Tie) |
| glaze STATISTICAL TIE | 811.003 | 0.649927 | 27.8784ms | 94651 | 30 | 1.56984e+07 | 111302 | 2.70347 | 1(Tie) |
| jsonifier | 747.33 | 0.63073 | 29.1405ms | 94651 | 30 | 1.74114e+07 | 120785 | 2.9339 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3687 | 0.692906 | 6.64375ms | 94651 | 30 | 863322 | 24482.3 | 0.593397 | 1(Win) |
| glaze | 3497.86 | 1.71135 | 6.80911ms | 94651 | 30 | 5.85117e+06 | 25806.1 | 0.626003 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1162.3 | 0.616276 | 27.6212ms | 136024 | 30 | 1.41927e+07 | 111608 | 1.88637 | 1(Win) |
| glaze | 977.948 | 0.448123 | 33.1377ms | 136024 | 30 | 1.06002e+07 | 132648 | 2.24215 | 2(Loss) |
| jsonifier | 934.66 | 0.555998 | 34.0481ms | 136024 | 30 | 1.78645e+07 | 138791 | 2.34599 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4096.61 | 2.33214 | 8.52839ms | 136024 | 30 | 1.63611e+07 | 31665.9 | 0.533695 | 1(Win) |
| glaze | 3529.42 | 0.49881 | 9.72458ms | 136046 | 30 | 1.00869e+06 | 36760.6 | 0.620776 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 579.356 | 0.337298 | 820.434ms | 2090234 | 30 | 4.04061e+09 | 3.44072e+06 | 3.78573 | 1(Win) |
| glaze | 487.245 | 0.161164 | 984.295ms | 2090234 | 30 | 1.30423e+09 | 4.09117e+06 | 4.50137 | 2(Loss) |
| simdjson (ondemand) | 382.605 | 0.280512 | 1252.73ms | 2090234 | 30 | 6.40785e+09 | 5.21007e+06 | 5.73272 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1130.34 | 0.246715 | 425.135ms | 2090234 | 30 | 5.67915e+08 | 1.76354e+06 | 1.94015 | 1(Win) |
| glaze | 616.813 | 0.0876702 | 776.783ms | 2090234 | 30 | 2.40829e+08 | 3.23178e+06 | 3.55581 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1480.79 | 0.674629 | 1021.89ms | 6661897 | 30 | 2.51338e+10 | 4.29046e+06 | 1.48112 | 1(Win) |
| glaze | 1253.48 | 0.218855 | 1218.57ms | 6661897 | 30 | 3.69142e+09 | 5.0685e+06 | 1.74977 | 2(Loss) |
| simdjson (ondemand) | 1151.98 | 0.18233 | 1325.48ms | 6661897 | 30 | 3.0335e+09 | 5.5151e+06 | 1.90393 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2184.16 | 0.0985485 | 702.64ms | 6661897 | 30 | 2.46518e+08 | 2.9088e+06 | 1.00418 | 1(Win) |
| glaze | 1352.46 | 0.273816 | 1129.73ms | 6661897 | 30 | 4.9635e+09 | 4.69758e+06 | 1.62165 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1311.53 | 0.514089 | 87.518ms | 500299 | 30 | 1.0493e+08 | 363789 | 1.6722 | 1(Win) |
| glaze | 1173.94 | 0.55578 | 99.0319ms | 500299 | 30 | 1.53071e+08 | 406427 | 1.86816 | 2(Loss) |
| simdjson (ondemand) | 757.388 | 0.42974 | 153.62ms | 500299 | 30 | 2.19864e+08 | 629958 | 2.89556 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 3236.6 | 2.31569 | 82.3268ms | 500299 | 32 | 3.72901e+08 | 147415 | 0.677302 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3199.31 | 1.64046 | 38.1305ms | 500299 | 30 | 1.79557e+08 | 149133 | 0.685084 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2331.32 | 0.544379 | 142.062ms | 1439562 | 30 | 3.08305e+08 | 588882 | 0.940592 | 1(Win) |
| simdjson (ondemand) | 1882 | 0.505221 | 174.709ms | 1439562 | 30 | 4.07477e+08 | 729474 | 1.16512 | 2(Loss) |
| glaze | 1838.56 | 0.544645 | 184.787ms | 1439562 | 30 | 4.96194e+08 | 746709 | 1.1927 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4097.72 | 0.626711 | 83.4068ms | 1439562 | 30 | 1.32261e+08 | 335033 | 0.535002 | 1(Win) |
| glaze | 3248.68 | 0.747883 | 102.899ms | 1439584 | 30 | 2.99675e+08 | 422601 | 0.674892 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1134.73 | 0.584245 | 11.996ms | 56369 | 30 | 2.29831e+06 | 47374.9 | 1.93093 | 1(Win) |
| glaze | 1014.15 | 1.20687 | 12.9649ms | 56369 | 30 | 1.22778e+07 | 53007.9 | 2.16107 | 2(Loss) |
| simdjson (ondemand) | 909.183 | 1.2529 | 14.9803ms | 56369 | 30 | 1.64639e+07 | 59127.4 | 2.41082 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4203.63 | 0.35655 | 3.78044ms | 56369 | 30 | 62372.8 | 12788.4 | 0.519943 | 1(Win) |
| jsonifier | 3734.56 | 0.40226 | 4.19257ms | 56369 | 30 | 100586 | 14394.6 | 0.585052 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1508.89 | 0.861854 | 15.4508ms | 94370 | 30 | 7.92763e+06 | 59645.5 | 1.45261 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1445.32 | 1.00241 | 16.0374ms | 94370 | 30 | 1.16884e+07 | 62268.8 | 1.5166 | 2(Tie) |
| glaze STATISTICAL TIE | 1421.75 | 1.31779 | 15.7309ms | 94370 | 30 | 2.08753e+07 | 63301 | 1.54154 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4832.32 | 0.279969 | 11.3399ms | 94370 | 32 | 87001.9 | 18624.2 | 0.452301 | 1(Win) |
| glaze | 3477.14 | 1.52194 | 6.91862ms | 94370 | 30 | 4.65522e+06 | 25882.9 | 0.629746 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1173.67 | 0.902624 | 11.1596ms | 52708 | 30 | 4.48327e+06 | 42828.2 | 1.86665 | 1(Win) |
| jsonifier | 998.287 | 0.739063 | 13.3168ms | 52708 | 30 | 4.15457e+06 | 50352.5 | 2.19454 | 2(Loss) |
| glaze | 901.749 | 0.441275 | 14.4298ms | 52708 | 30 | 1.81519e+06 | 55743.1 | 2.43011 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4283.61 | 0.731455 | 3.46665ms | 52708 | 30 | 221020 | 11734.6 | 0.509957 | 1(Win) |
| jsonifier | 3678.05 | 0.309335 | 3.98537ms | 52708 | 30 | 53616.3 | 13666.6 | 0.594607 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1500.44 | 0.55181 | 11.7284ms | 70103 | 30 | 1.81357e+06 | 44557.1 | 1.46022 | 1(Win) |
| jsonifier | 1117.86 | 0.724688 | 16.0286ms | 70103 | 30 | 5.63534e+06 | 59806.5 | 1.96027 | 2(Loss) |
| glaze | 1059.7 | 1.05221 | 16.1456ms | 70103 | 30 | 1.32201e+07 | 63089.3 | 2.06813 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 4380.91 | 0.942403 | 9.61744ms | 70103 | 32 | 661863 | 15260.6 | 0.497637 | 1(Tie) |
| glaze STATISTICAL TIE | 4338.39 | 1.6419 | 9.64974ms | 70103 | 32 | 2.04861e+06 | 15410.2 | 0.504207 | 1(Tie) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 869.274 | 1.59483 | 3.80238ms | 11812 | 30 | 1.2814e+06 | 12958.9 | 2.51611 | 1(Win) |
| glaze | 804.07 | 1.5027 | 3.95702ms | 11812 | 30 | 1.32962e+06 | 14009.7 | 2.68353 | 2(Loss) |
| simdjson (ondemand) | 765.145 | 0.0854579 | 4.28698ms | 11812 | 30 | 4748.81 | 14722.4 | 2.85996 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3500.09 | 0.164714 | 1.24651ms | 11812 | 30 | 843.082 | 3218.43 | 0.616938 | 1(Win) |
| glaze | 3094.9 | 0.172163 | 1.36129ms | 11812 | 30 | 1178.03 | 3639.8 | 0.701078 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1893.44 | 0.0828056 | 4.59121ms | 31235 | 30 | 5091.22 | 15732.2 | 1.15596 | 1(Win) |
| jsonifier | 1697.94 | 1.38931 | 4.93444ms | 31235 | 30 | 1.7822e+06 | 17543.6 | 1.28901 | 2(Loss) |
| glaze | 1380.62 | 1.06414 | 5.73874ms | 31235 | 30 | 1.58145e+06 | 21575.8 | 1.58592 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5367.31 | 0.0872568 | 2.04642ms | 31235 | 30 | 703.541 | 5549.9 | 0.401138 | 1(Win) |
| glaze | 4179.6 | 0.184315 | 2.24633ms | 31235 | 30 | 5176.76 | 7127 | 0.521554 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2342.36 | 0.397969 | 11.5869ms | 108313 | 30 | 924004 | 44098.8 | 0.935568 | 1(Win) |
| glaze | 1426.19 | 0.836401 | 17.869ms | 108313 | 30 | 1.10093e+07 | 72427.6 | 1.53253 | 2(Loss) |
| simdjson (ondemand) | 1196.84 | 0.58682 | 21.605ms | 108313 | 30 | 7.69522e+06 | 86306.8 | 1.83175 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2706.72 | 0.565363 | 9.33545ms | 108313 | 30 | 1.39653e+06 | 38162.6 | 0.809431 | 1(Win) |
| jsonifier | 2065.19 | 0.873912 | 12.3177ms | 108313 | 30 | 5.73192e+06 | 50017.4 | 1.0604 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2264.66 | 0.331639 | 23.2271ms | 213963 | 30 | 2.67869e+06 | 90102.1 | 0.968088 | 1(Win) |
| glaze | 2008.95 | 0.85961 | 25.081ms | 213963 | 30 | 2.28699e+07 | 101571 | 1.09137 | 2(Loss) |
| jsonifier | 1766.33 | 0.883235 | 28.583ms | 213963 | 30 | 3.12326e+07 | 115523 | 1.24131 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4708.33 | 1.14785 | 26.2546ms | 213963 | 32 | 7.91886e+06 | 43338.3 | 0.46529 | 1(Win) |
| glaze | 3225.92 | 1.49902 | 14.782ms | 213963 | 30 | 2.69715e+07 | 63253.5 | 0.679523 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 613.612 | 0.266576 | 690.358ms | 1834197 | 30 | 1.73248e+09 | 2.8507e+06 | 3.57435 | 1(Win) |
| glaze | 436.75 | 0.182987 | 967.067ms | 1834197 | 30 | 1.61134e+09 | 4.0051e+06 | 5.02202 | 2(Loss) |
| simdjson (ondemand) | 404.052 | 0.183283 | 1046.04ms | 1834197 | 30 | 1.88879e+09 | 4.32921e+06 | 5.42808 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 729.512 | 0.615213 | 577.266ms | 1834197 | 30 | 6.52828e+09 | 2.3978e+06 | 3.00644 | 1(Win) |
| glaze | 395.096 | 0.14374 | 1061.13ms | 1833577 | 30 | 1.21414e+09 | 4.42585e+06 | 5.55122 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2075.39 | 0.182474 | 1105.69ms | 9930848 | 30 | 2.08017e+09 | 4.56339e+06 | 1.0568 | 1(Win) |
| simdjson (ondemand) | 1929.29 | 0.182668 | 1177.93ms | 9930848 | 30 | 2.41228e+09 | 4.90897e+06 | 1.13683 | 2(Loss) |
| glaze | 1742.57 | 0.221732 | 1309.37ms | 9930848 | 30 | 4.35687e+09 | 5.43497e+06 | 1.25866 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1911.64 | 0.296211 | 1189.34ms | 9930848 | 30 | 6.46075e+09 | 4.95428e+06 | 1.14738 | 1(Win) |
| glaze | 1359.82 | 0.108792 | 1680.99ms | 9930228 | 30 | 1.72216e+09 | 6.96432e+06 | 1.61299 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1093.72 | 0.584561 | 131.976ms | 642697 | 30 | 3.21943e+08 | 560401 | 2.00495 | 1(Win) |
| glaze | 923.772 | 0.338631 | 159.393ms | 642697 | 30 | 1.51446e+08 | 663501 | 2.37386 | 2(Loss) |
| simdjson (ondemand) | 803.811 | 0.257832 | 185.396ms | 642697 | 30 | 1.15958e+08 | 762522 | 2.72794 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1222.66 | 0.478889 | 119.675ms | 642697 | 30 | 1.72898e+08 | 501302 | 1.79335 | 1(Win) |
| glaze | 950.839 | 0.269708 | 155.053ms | 642692 | 30 | 9.06778e+07 | 644609 | 2.30599 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1488.72 | 0.157619 | 190.993ms | 1225964 | 30 | 4.59691e+07 | 785353 | 1.47306 | 1(Win) |
| simdjson (ondemand) | 1466.17 | 0.259234 | 194.754ms | 1225964 | 30 | 1.282e+08 | 797429 | 1.49558 | 2(Loss) |
| glaze | 1456.02 | 0.199011 | 195.406ms | 1225964 | 30 | 7.66121e+07 | 802991 | 1.50597 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1364.3 | 0.416648 | 205.381ms | 1225970 | 30 | 3.82472e+08 | 856978 | 1.60726 | 1(Win) |
| jsonifier | 1232.58 | 0.289882 | 228.894ms | 1225964 | 30 | 2.26826e+08 | 948558 | 1.77904 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 745.475 | 0.232726 | 127.814ms | 409725 | 30 | 4.46406e+07 | 524155 | 2.94201 | 1(Win) |
| simdjson (ondemand) | 687.329 | 0.408162 | 136.352ms | 409725 | 30 | 1.61526e+08 | 568496 | 3.19061 | 2(Loss) |
| glaze | 556.249 | 0.523064 | 170.432ms | 409725 | 30 | 4.0502e+08 | 702462 | 3.94248 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2242.95 | 0.515492 | 42.6823ms | 409725 | 30 | 2.41941e+07 | 174210 | 0.977667 | 1(Win) |
| glaze | 2192.12 | 0.493199 | 45.0132ms | 409725 | 30 | 2.31859e+07 | 178250 | 0.999902 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1268.78 | 0.259308 | 143.415ms | 785750 | 30 | 7.03635e+07 | 590606 | 1.72827 | 1(Win) |
| jsonifier | 1055.84 | 0.27461 | 171.439ms | 785750 | 30 | 1.13954e+08 | 709720 | 2.07712 | 2(Loss) |
| glaze | 875.905 | 0.451 | 209.352ms | 785750 | 30 | 4.46611e+08 | 855514 | 2.50354 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3283.36 | 0.495129 | 55.8295ms | 785750 | 30 | 3.8308e+07 | 228226 | 0.667476 | 1(Win) |
| glaze | 2561.38 | 0.411896 | 72.589ms | 785750 | 30 | 4.35629e+07 | 292557 | 0.855886 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 863.563 | 0.246712 | 2284.77ms | 8587914 | 30 | 1.64244e+10 | 9.48405e+06 | 2.54001 | 1(Win) |
| simdjson (ondemand) | 838.531 | 0.319589 | 2360.57ms | 8587914 | 30 | 2.92309e+10 | 9.76717e+06 | 2.61577 | 2(Loss) |
| glaze | 751.993 | 0.17165 | 2606.49ms | 8587914 | 30 | 1.04847e+10 | 1.08912e+07 | 2.91689 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2545.19 | 0.600131 | 771.263ms | 8588126 | 30 | 1.11885e+10 | 3.21795e+06 | 0.861739 | 1(Tie) |
| glaze STATISTICAL TIE | 2534.51 | 0.284061 | 780.25ms | 8588126 | 30 | 2.52786e+09 | 3.2315e+06 | 0.865336 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 930.567 | 0.149125 | 2418.65ms | 9804437 | 30 | 6.73551e+09 | 1.00479e+07 | 2.35701 | 1(Win) |
| jsonifier | 857.032 | 0.0696556 | 2663.11ms | 9804437 | 30 | 1.73255e+09 | 1.091e+07 | 2.55938 | 2(Loss) |
| glaze | 784.973 | 0.135191 | 2871.68ms | 9804437 | 30 | 7.77956e+09 | 1.19115e+07 | 2.79431 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2892.21 | 0.182082 | 880.404ms | 11078090 | 30 | 1.32717e+09 | 3.65288e+06 | 0.758346 | 1(Win) |
| glaze | 2674.06 | 0.162207 | 957.919ms | 11078090 | 30 | 1.23211e+09 | 3.95088e+06 | 0.820182 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 4821.57 | 1.1729 | 13.4574ms | 264040 | 30 | 1.12565e+07 | 52225.3 | 0.45454 | 1(Win) |
| jsonifier | 4588.51 | 1.34608 | 14.0067ms | 264040 | 30 | 1.63705e+07 | 54877.9 | 0.477673 | 2(Loss) |
| glaze | 1496.14 | 0.594916 | 41.2819ms | 264040 | 30 | 3.00766e+07 | 168305 | 1.46567 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6440.12 | 0.663076 | 15.1658ms | 399947 | 30 | 4.62662e+06 | 59225.4 | 0.340362 | 1(Win) |
| simdjson (ondemand) | 6230.01 | 1.00382 | 15.3879ms | 399947 | 30 | 1.13309e+07 | 61222.9 | 0.351819 | 2(Loss) |
| glaze | 2008.37 | 0.261133 | 46.451ms | 399947 | 30 | 7.37838e+06 | 189915 | 1.09188 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1317.85 | 0.52528 | 46.2645ms | 264040 | 30 | 3.02212e+07 | 191075 | 1.66391 | 1(Win) |
| simdjson (ondemand) | 1189.35 | 0.99843 | 50.125ms | 264040 | 30 | 1.34052e+08 | 211718 | 1.84368 | 2(Loss) |
| glaze | 1113.58 | 0.45263 | 55.7346ms | 264040 | 30 | 3.14271e+07 | 226125 | 1.96922 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4425.39 | 0.946214 | 14.357ms | 264040 | 30 | 8.69636e+06 | 56900.8 | 0.495179 | 1(Win) |
| glaze | 3797.7 | 1.29487 | 16.2859ms | 263923 | 30 | 2.20946e+07 | 66276.1 | 0.577183 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1889.22 | 0.479566 | 49.976ms | 399947 | 30 | 2.81227e+07 | 201892 | 1.16071 | 1(Win) |
| glaze | 1362.91 | 0.542219 | 69.1576ms | 399947 | 30 | 6.9078e+07 | 279856 | 1.60905 | 2(Loss) |
| jsonifier | 1303.82 | 0.367179 | 73.5983ms | 399947 | 30 | 3.46133e+07 | 292539 | 1.68188 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3839.82 | 0.632915 | 24.9871ms | 399947 | 30 | 1.18576e+07 | 99332.6 | 0.570886 | 1(Tie) |
| glaze STATISTICAL TIE | 3807.56 | 1.58079 | 25.3587ms | 399830 | 30 | 7.51848e+07 | 100145 | 0.575595 | 1(Tie) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2070.22 | 0.274608 | 52.1218ms | 466906 | 30 | 1.04659e+07 | 215087 | 1.05926 | 1(Win) |
| glaze | 1906.07 | 0.355018 | 56.846ms | 466906 | 30 | 2.0635e+07 | 233610 | 1.15057 | 2(Loss) |
| simdjson (ondemand) | 904.729 | 0.371702 | 122.76ms | 466906 | 30 | 1.004e+08 | 492165 | 2.42323 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3311.07 | 0.509647 | 50.5577ms | 699405 | 30 | 3.16214e+07 | 201447 | 0.66206 | 1(Win) |
| glaze | 2310.24 | 0.518137 | 68.8277ms | 699405 | 30 | 6.71357e+07 | 288716 | 0.949269 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3122.71 | 0.549116 | 46.8068ms | 631514 | 30 | 3.36475e+07 | 192864 | 0.702226 | 1(Win) |
| glaze | 1824.14 | 0.530573 | 79.0021ms | 631514 | 30 | 9.20577e+07 | 330160 | 1.20229 | 2(Loss) |
