# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [57ce61b](https://github.com/nihilai-collective/jsonifier/commit/57ce61b)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 558.211 | 0.0617922 | 3.00161ms | 1811 | 30 | 109.655 | 3094 | 4.38071 | 1(Win) |
| glaze | 492.581 | 0.140527 | 1.02473ms | 1811 | 30 | 728.323 | 3506.23 | 4.97651 | 2(Loss) |
| simdjson (ondemand) | 141.057 | 0.102533 | 3.16978ms | 1811 | 30 | 4728.24 | 12244 | 17.497 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 341.197 | 0.109558 | 1.43476ms | 1811 | 30 | 922.645 | 5061.9 | 7.20133 | 1(Win) |
| glaze | 283.871 | 0.0677288 | 1.62318ms | 1798 | 30 | 502.116 | 6040.43 | 8.66522 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1139.9 | 0.0722625 | 1.02488ms | 3873 | 30 | 164.478 | 3240.27 | 2.1453 | 1(Win) |
| glaze | 978.683 | 0.0559058 | 1.06984ms | 3873 | 30 | 133.551 | 3774.03 | 2.50467 | 2(Loss) |
| simdjson (ondemand) | 265.695 | 0.0838929 | 3.62163ms | 3873 | 30 | 4080.39 | 13901.6 | 9.29211 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1644.71 | 0.374532 | 0.771783ms | 3873 | 30 | 2122.34 | 2245.73 | 1.46884 | 1(Win) |
| glaze | 1091.01 | 0.112042 | 1.00477ms | 3873 | 30 | 431.637 | 3385.47 | 2.24465 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1166.59 | 0.0709842 | 1.00495ms | 3862 | 30 | 150.671 | 3157.13 | 2.09463 | 1(Win) |
| glaze | 795.942 | 0.0691072 | 1.30468ms | 3862 | 30 | 306.782 | 4627.33 | 3.0836 | 2(Loss) |
| simdjson (ondemand) | 325.543 | 0.0432954 | 2.87258ms | 3862 | 30 | 719.803 | 11313.7 | 7.57985 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1607.99 | 0.195289 | 0.767657ms | 3862 | 30 | 600.259 | 2290.5 | 1.50803 | 1(Win) |
| glaze | 1079.84 | 0.100411 | 2.17556ms | 3862 | 32 | 375.338 | 3410.78 | 2.26751 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 546.239 | 0.090908 | 0.600895ms | 905 | 30 | 61.8954 | 1580.03 | 4.4291 | 1(Win) |
| glaze | 493.468 | 0.0591142 | 0.612764ms | 905 | 30 | 32.069 | 1749 | 4.90217 | 2(Loss) |
| simdjson (ondemand) | 112.806 | 0.0435591 | 4.54355ms | 905 | 32 | 355.415 | 7650.94 | 21.8387 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 779.887 | 0.160848 | 0.448355ms | 905 | 30 | 95.0575 | 1106.67 | 3.06541 | 1(Win) |
| glaze | 310.903 | 0.488668 | 1.7673ms | 905 | 32 | 5888.81 | 2776.03 | 7.85028 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1857.56 | 0.0218784 | 1.44273ms | 9578 | 30 | 34.723 | 4917.37 | 1.32298 | 1(Win) |
| glaze | 1620.53 | 0.0487552 | 7.14389ms | 9578 | 64 | 483.349 | 5636.62 | 1.51799 | 2(Loss) |
| simdjson (ondemand) | 727.783 | 1.82252 | 7.2231ms | 9578 | 32 | 1.67433e+06 | 12550.8 | 3.39201 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3278.84 | 0.178794 | 0.92304ms | 9578 | 30 | 744.282 | 2785.83 | 0.745326 | 1(Win) |
| glaze | 2171.2 | 0.186292 | 1.19612ms | 9578 | 30 | 1842.72 | 4207.03 | 1.13052 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2742.09 | 0.465938 | 19.9054ms | 233995 | 30 | 4.31347e+06 | 81381.3 | 0.902456 | 1(Win) |
| simdjson (ondemand) | 2635.24 | 0.698081 | 20.547ms | 233995 | 30 | 1.04835e+07 | 84681.2 | 0.938957 | 2(Loss) |
| glaze | 1673.58 | 0.875348 | 32.4679ms | 233995 | 30 | 4.08696e+07 | 133340 | 1.47883 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3386.03 | 1.12627 | 23.5517ms | 346753 | 30 | 3.62963e+07 | 97662.8 | 0.730763 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3380.56 | 0.599608 | 23.7618ms | 346753 | 30 | 1.03209e+07 | 97820.8 | 0.731928 | 1(Tie) |
| glaze | 2090.96 | 0.827637 | 37.8071ms | 346753 | 30 | 5.13983e+07 | 158152 | 1.18376 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1270.86 | 0.411197 | 42.6318ms | 233995 | 30 | 1.564e+07 | 175593 | 1.94756 | 1(Win) |
| glaze | 1151.16 | 0.463629 | 50.0288ms | 233995 | 30 | 2.42331e+07 | 193853 | 2.15016 | 2(Loss) |
| simdjson (ondemand) | 1051.1 | 0.835808 | 53.6268ms | 233995 | 30 | 9.44632e+07 | 212307 | 2.35484 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2455.89 | 0.532156 | 22.4588ms | 233995 | 30 | 7.01446e+06 | 90865.2 | 1.00741 | 1(Win) |
| glaze | 2179.59 | 0.517348 | 24.9238ms | 233995 | 30 | 8.41686e+06 | 102384 | 1.13539 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1558.45 | 0.346824 | 61.1451ms | 346753 | 30 | 1.62478e+07 | 212191 | 1.58808 | 1(Win) |
| simdjson (ondemand) | 1397.75 | 1.61378 | 57.1266ms | 346753 | 30 | 4.37312e+08 | 236587 | 1.77076 | 2(Loss) |
| glaze | 1347.01 | 0.777947 | 58.959ms | 346753 | 30 | 1.09426e+08 | 245499 | 1.83755 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3184.67 | 0.54922 | 25.5687ms | 346753 | 30 | 9.75724e+06 | 103838 | 0.777036 | 1(Win) |
| glaze | 1943.02 | 0.44217 | 41.8817ms | 346753 | 30 | 1.69898e+07 | 170194 | 1.27351 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2652.05 | 1.40817 | 20.1189ms | 233995 | 30 | 4.21195e+07 | 84144.4 | 0.93309 | 1(Win) |
| simdjson (ondemand) | 1845.97 | 0.636626 | 29.3159ms | 233995 | 30 | 1.77687e+07 | 120888 | 1.34076 | 2(Loss) |
| glaze | 1724.49 | 0.443104 | 31.5528ms | 233995 | 30 | 9.86334e+06 | 129403 | 1.43517 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3388.87 | 0.625453 | 23.6576ms | 346753 | 30 | 1.11748e+07 | 97581 | 0.730161 | 1(Win) |
| simdjson (ondemand) | 2459.48 | 0.578134 | 32.6181ms | 346753 | 30 | 1.81272e+07 | 134455 | 1.00627 | 2(Loss) |
| glaze | 2101.43 | 0.494738 | 38.1918ms | 346753 | 30 | 1.81836e+07 | 157364 | 1.17779 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1178.07 | 0.339862 | 46.5556ms | 233995 | 30 | 1.24337e+07 | 189425 | 2.10098 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1174.87 | 0.36816 | 46.3436ms | 233995 | 30 | 1.467e+07 | 189941 | 2.10674 | 1(Tie) |
| simdjson (ondemand) | 203.461 | 0.605549 | 261.236ms | 233995 | 30 | 1.32334e+09 | 1.09679e+06 | 12.1674 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2569.31 | 0.701207 | 21.3244ms | 233995 | 30 | 1.11274e+07 | 86854.2 | 0.963054 | 1(Win) |
| glaze | 2184.65 | 0.529171 | 24.8441ms | 233995 | 30 | 8.76523e+06 | 102147 | 1.13239 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1604.72 | 0.324247 | 51.4519ms | 346753 | 30 | 1.33941e+07 | 206073 | 1.54242 | 1(Win) |
| jsonifier | 1523.52 | 0.324145 | 53.3228ms | 346753 | 30 | 1.48506e+07 | 217056 | 1.6245 | 2(Loss) |
| simdjson (ondemand) | 298.521 | 0.179024 | 265.756ms | 346753 | 30 | 1.17987e+08 | 1.10776e+06 | 8.29295 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3332.19 | 0.700958 | 24.5283ms | 346753 | 30 | 1.45173e+07 | 99240.9 | 0.742678 | 1(Win) |
| glaze | 2111.62 | 0.54744 | 37.7913ms | 346753 | 30 | 2.20499e+07 | 156605 | 1.1717 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 703.864 | 0.453649 | 31.3174ms | 94651 | 30 | 1.0154e+07 | 128244 | 3.51631 | 1(Win) |
| simdjson (ondemand) | 687.797 | 0.4802 | 32.1718ms | 94651 | 30 | 1.19151e+07 | 131240 | 3.59857 | 2(Loss) |
| glaze | 673.481 | 0.646466 | 32.7569ms | 94651 | 30 | 2.25222e+07 | 134029 | 3.67504 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3305.99 | 0.988723 | 6.82911ms | 94651 | 30 | 2.18634e+06 | 27303.8 | 0.747871 | 1(Win) |
| glaze | 2834.58 | 1.13027 | 7.91538ms | 94651 | 30 | 3.88653e+06 | 31844.7 | 0.872179 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 968.318 | 0.465632 | 32.7852ms | 136024 | 30 | 1.16735e+07 | 133967 | 2.55606 | 1(Win) |
| jsonifier | 889.622 | 0.677448 | 36.2506ms | 136024 | 30 | 2.92747e+07 | 145818 | 2.78212 | 2(Loss) |
| glaze | 856.003 | 0.419571 | 37.4862ms | 136024 | 30 | 1.21287e+07 | 151545 | 2.89137 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3799.02 | 2.47074 | 8.21901ms | 136024 | 30 | 2.13533e+07 | 34146.4 | 0.650822 | 1(Win) |
| glaze | 2683.84 | 0.591833 | 11.9131ms | 136046 | 30 | 2.45572e+06 | 48342.5 | 0.921694 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 427.097 | 0.083204 | 1119.44ms | 2090234 | 30 | 4.52424e+08 | 4.66732e+06 | 5.7966 | 1(Win) |
| glaze | 366.051 | 0.0692902 | 1309.54ms | 2090234 | 30 | 4.27142e+08 | 5.44569e+06 | 6.76336 | 2(Loss) |
| simdjson (ondemand) | 283.74 | 0.0616011 | 1686.98ms | 2090234 | 30 | 5.61886e+08 | 7.02546e+06 | 8.72537 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 629.524 | 0.0650329 | 759.889ms | 2090234 | 30 | 1.27219e+08 | 3.16652e+06 | 3.93265 | 1(Win) |
| glaze | 555.585 | 2.31601 | 807.46ms | 2090234 | 30 | 2.07154e+11 | 3.58794e+06 | 4.45605 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1123.62 | 0.0867866 | 1361.16ms | 6661897 | 30 | 7.22407e+08 | 5.65428e+06 | 2.20333 | 1(Win) |
| glaze | 966.7 | 0.0878713 | 1588.58ms | 6661897 | 30 | 1.00053e+09 | 6.57213e+06 | 2.56102 | 2(Loss) |
| simdjson (ondemand) | 852.447 | 0.074196 | 1798.83ms | 6661897 | 30 | 9.17368e+08 | 7.45299e+06 | 2.90426 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1779.72 | 0.0966574 | 861.558ms | 6661897 | 30 | 3.5718e+08 | 3.56983e+06 | 1.39107 | 1(Win) |
| glaze | 1492.43 | 0.245423 | 1018.46ms | 6661897 | 30 | 3.27461e+09 | 4.25701e+06 | 1.65878 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 944.278 | 0.451149 | 121.067ms | 500299 | 30 | 1.55891e+08 | 505278 | 2.62132 | 1(Win) |
| glaze | 806.858 | 0.468451 | 141.573ms | 500299 | 30 | 2.30205e+08 | 591334 | 3.06771 | 2(Loss) |
| simdjson (ondemand) | 482.674 | 0.140025 | 237.165ms | 500299 | 30 | 5.74759e+07 | 988498 | 5.12855 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3174.28 | 0.428065 | 36.5096ms | 500299 | 30 | 1.24197e+07 | 150309 | 0.779615 | 1(Win) |
| glaze | 2293.86 | 0.4283 | 50.5269ms | 500299 | 30 | 2.38091e+07 | 208000 | 1.0789 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1917.44 | 0.145963 | 171.959ms | 1439562 | 30 | 3.27659e+07 | 715992 | 1.29095 | 1(Win) |
| glaze | 1576.37 | 0.167251 | 209.284ms | 1439562 | 30 | 6.36508e+07 | 870907 | 1.57033 | 2(Loss) |
| simdjson (ondemand) | 1237.12 | 0.173761 | 266.063ms | 1439562 | 30 | 1.11549e+08 | 1.10973e+06 | 2.00096 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4531.1 | 0.287007 | 73.2689ms | 1439562 | 30 | 2.26862e+07 | 302989 | 0.546238 | 1(Win) |
| glaze | 3065.84 | 0.297777 | 108.285ms | 1439584 | 30 | 5.33432e+07 | 447803 | 0.807379 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 934.184 | 0.62024 | 14.3125ms | 56369 | 30 | 3.82171e+06 | 57545.1 | 2.64828 | 1(Win) |
| glaze | 823.906 | 0.594232 | 16.2997ms | 56369 | 30 | 4.50981e+06 | 65247.3 | 3.00324 | 2(Loss) |
| simdjson (ondemand) | 715.755 | 0.504185 | 18.7864ms | 56369 | 30 | 4.30182e+06 | 75106.2 | 3.45672 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3477.97 | 0.0920513 | 3.98431ms | 56369 | 30 | 6073.08 | 15456.6 | 0.710043 | 1(Win) |
| glaze | 2559 | 0.213729 | 5.28626ms | 56369 | 30 | 60477 | 21007.3 | 0.965696 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1313.06 | 0.705209 | 17.0734ms | 94370 | 30 | 7.00895e+06 | 68540.6 | 1.88435 | 1(Win) |
| glaze STATISTICAL TIE | 1146.11 | 0.500279 | 19.3756ms | 94370 | 30 | 4.62975e+06 | 78524.7 | 2.15907 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1140.83 | 0.598368 | 19.6898ms | 94370 | 30 | 6.68469e+06 | 78888.2 | 2.16887 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4589.35 | 0.211389 | 5.03375ms | 94370 | 30 | 51552.9 | 19610.2 | 0.538496 | 1(Win) |
| glaze | 2570.39 | 1.1872 | 8.60722ms | 94370 | 30 | 5.18371e+06 | 35013.4 | 0.962085 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 932.827 | 0.756231 | 13.7695ms | 52708 | 30 | 4.98174e+06 | 53885.9 | 2.65153 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 898.201 | 2.1082 | 13.7461ms | 52708 | 30 | 4.17592e+07 | 55963.3 | 2.75356 | 1(Tie) |
| glaze | 754.865 | 0.708743 | 16.5875ms | 52708 | 30 | 6.6821e+06 | 66589.7 | 3.27769 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3393.53 | 1.69716 | 3.82418ms | 52708 | 30 | 1.8959e+06 | 14812.4 | 0.727659 | 1(Win) |
| glaze | 3081.49 | 1.96568 | 4.11345ms | 52708 | 30 | 3.08444e+06 | 16312.3 | 0.801471 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1152.51 | 0.826054 | 15.1538ms | 70103 | 30 | 6.88852e+06 | 58008.8 | 2.14657 | 1(Win) |
| glaze STATISTICAL TIE | 902.839 | 0.803889 | 18.2288ms | 70103 | 30 | 1.06308e+07 | 74050.2 | 2.74039 | 2(Tie) |
| jsonifier STATISTICAL TIE | 891.902 | 0.702215 | 19.5473ms | 70103 | 30 | 8.3119e+06 | 74958.3 | 2.77399 | 2(Tie) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3698 | 1.41508 | 10.5312ms | 70103 | 32 | 2.09437e+06 | 18078.8 | 0.668157 | 1(Win) |
| glaze | 3127.42 | 2.03003 | 5.32176ms | 70103 | 30 | 5.64971e+06 | 21377.2 | 0.790141 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 703.367 | 2.47796 | 4.06304ms | 11812 | 30 | 4.72489e+06 | 16015.5 | 3.51216 | 1(Win) |
| glaze | 629.391 | 0.23747 | 4.70158ms | 11812 | 30 | 54193.2 | 17897.9 | 3.9248 | 2(Loss) |
| simdjson (ondemand) | 559.101 | 0.0805274 | 5.09343ms | 11812 | 30 | 7897.24 | 20148.1 | 4.41947 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3090.93 | 0.181784 | 1.05184ms | 11812 | 30 | 1316.74 | 3644.47 | 0.792708 | 1(Win) |
| glaze | 1663.72 | 0.192986 | 1.83297ms | 11812 | 30 | 5122.21 | 6770.83 | 1.47976 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1560.69 | 2.437 | 4.80304ms | 31235 | 30 | 6.4906e+06 | 19086.5 | 1.58306 | 1(Win) |
| simdjson (ondemand) | 1334.36 | 1.8882 | 5.51579ms | 31235 | 30 | 5.33039e+06 | 22323.9 | 1.85231 | 2(Loss) |
| glaze | 1237.82 | 1.18287 | 6.02158ms | 31235 | 30 | 2.43088e+06 | 24065 | 1.99657 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3858.5 | 0.234072 | 4.61371ms | 31235 | 32 | 10449.5 | 7720.09 | 0.638424 | 1(Win) |
| glaze | 2659.11 | 0.340927 | 2.91058ms | 31235 | 30 | 43757.6 | 11202.2 | 0.927931 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1927.53 | 0.88707 | 13.2515ms | 108313 | 30 | 6.77949e+06 | 53589.5 | 1.28324 | 1(Win) |
| glaze | 1089.55 | 0.605491 | 23.273ms | 108313 | 30 | 9.88563e+06 | 94805.6 | 2.27116 | 2(Loss) |
| simdjson (ondemand) | 835.325 | 0.554681 | 30.1709ms | 108313 | 30 | 1.41142e+07 | 123659 | 2.96284 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2744.78 | 1.16055 | 9.25311ms | 108313 | 30 | 5.72259e+06 | 37633.4 | 0.901097 | 1(Win) |
| glaze | 1449.22 | 0.507459 | 17.3741ms | 108313 | 30 | 3.92477e+06 | 71276.4 | 1.70745 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1617.1 | 0.434762 | 31.0092ms | 213963 | 30 | 9.02881e+06 | 126184 | 1.53045 | 1(Tie) |
| glaze STATISTICAL TIE | 1608.08 | 0.491234 | 30.7352ms | 213963 | 30 | 1.16563e+07 | 126891 | 1.53889 | 1(Tie) |
| simdjson (ondemand) | 1533.87 | 0.475429 | 32.7099ms | 213963 | 30 | 1.20003e+07 | 133030 | 1.61353 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4092.25 | 0.712686 | 12.2517ms | 213963 | 30 | 3.78853e+06 | 49862.8 | 0.604548 | 1(Win) |
| glaze | 1825.21 | 0.624773 | 27.1828ms | 213963 | 30 | 1.46358e+07 | 111796 | 1.35583 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 486.869 | 0.128254 | 862.876ms | 1834197 | 30 | 6.36985e+08 | 3.59281e+06 | 5.08482 | 1(Win) |
| glaze | 352.596 | 0.126062 | 1194.31ms | 1834197 | 30 | 1.17335e+09 | 4.961e+06 | 7.02138 | 2(Loss) |
| simdjson (ondemand) | 267.698 | 0.0914758 | 1572.78ms | 1834197 | 30 | 1.07186e+09 | 6.53434e+06 | 9.24818 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 392.502 | 0.0586208 | 1071.79ms | 1833577 | 30 | 2.04616e+08 | 4.4551e+06 | 6.30758 | 1(Win) |
| jsonifier | 372.164 | 0.075517 | 1129.05ms | 1834197 | 30 | 3.7795e+08 | 4.70015e+06 | 6.65224 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1778.12 | 0.129155 | 1283.33ms | 9930848 | 30 | 1.4197e+09 | 5.3263e+06 | 1.39227 | 1(Win) |
| glaze | 1410.39 | 0.120066 | 1613.67ms | 9930848 | 30 | 1.95007e+09 | 6.71499e+06 | 1.75533 | 2(Loss) |
| simdjson (ondemand) | 1266.02 | 0.100654 | 1796.67ms | 9930848 | 30 | 1.70088e+09 | 7.48078e+06 | 1.9555 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1576.31 | 0.737292 | 1413.43ms | 9930848 | 30 | 5.88698e+10 | 6.00822e+06 | 1.57052 | 1(Win) |
| glaze | 1305.11 | 0.302463 | 1741.37ms | 9930228 | 30 | 1.44508e+10 | 7.25625e+06 | 1.89689 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 837.488 | 0.173998 | 176.907ms | 642697 | 30 | 4.86482e+07 | 731859 | 2.95585 | 1(Win) |
| glaze | 726.576 | 0.298748 | 201.542ms | 642697 | 30 | 1.90538e+08 | 843578 | 3.40709 | 2(Loss) |
| simdjson (ondemand) | 529.378 | 0.15913 | 277.155ms | 642697 | 30 | 1.01837e+08 | 1.15782e+06 | 4.67637 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 685.175 | 0.0800924 | 214.844ms | 642697 | 30 | 1.53998e+07 | 894551 | 3.61305 | 1(Win) |
| glaze | 612.723 | 0.125871 | 257.101ms | 642692 | 30 | 4.75611e+07 | 1.00032e+06 | 4.04038 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1163.62 | 0.339826 | 243.774ms | 1225964 | 30 | 3.49758e+08 | 1.00477e+06 | 2.12737 | 1(Win) |
| glaze | 1106.07 | 0.221989 | 253.487ms | 1225964 | 30 | 1.65185e+08 | 1.05705e+06 | 2.23812 | 2(Loss) |
| simdjson (ondemand) | 968.09 | 0.168412 | 289.387ms | 1225964 | 30 | 1.24106e+08 | 1.20771e+06 | 2.55715 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1169.4 | 0.0640628 | 240.722ms | 1225964 | 30 | 1.23073e+07 | 999804 | 2.11687 | 1(Win) |
| glaze | 963.708 | 0.0861825 | 291.534ms | 1225970 | 30 | 3.27965e+07 | 1.21321e+06 | 2.56883 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 610.651 | 0.174758 | 154.254ms | 409725 | 30 | 3.75142e+07 | 639881 | 4.05382 | 1(Win) |
| simdjson (ondemand) | 496.92 | 0.204635 | 188.687ms | 409725 | 30 | 7.7677e+07 | 786332 | 4.98158 | 2(Loss) |
| glaze | 395.036 | 0.661329 | 235.749ms | 409725 | 30 | 1.28371e+09 | 989137 | 6.26653 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2065.71 | 0.417558 | 46.3839ms | 409725 | 30 | 1.87156e+07 | 189158 | 1.19811 | 1(Win) |
| glaze | 1739.73 | 0.373215 | 54.8359ms | 409725 | 30 | 2.10795e+07 | 224600 | 1.42262 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 935.92 | 0.139201 | 193.116ms | 785750 | 30 | 3.72648e+07 | 800656 | 2.64496 | 1(Win) |
| simdjson (ondemand) | 900.231 | 0.248196 | 200.678ms | 785750 | 30 | 1.28048e+08 | 832397 | 2.7498 | 2(Loss) |
| glaze | 667.562 | 0.185241 | 270.196ms | 785750 | 30 | 1.29713e+08 | 1.12252e+06 | 3.70837 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2858.84 | 0.784185 | 63.2829ms | 785750 | 30 | 1.2675e+08 | 262117 | 0.865782 | 1(Win) |
| glaze | 2150.16 | 0.637811 | 83.4093ms | 785750 | 30 | 1.48228e+08 | 348508 | 1.15118 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 698.259 | 0.592719 | 2827.97ms | 8587914 | 30 | 1.44998e+11 | 1.17293e+07 | 3.54555 | 1(Win) |
| simdjson (ondemand) | 588.713 | 0.319605 | 3512.94ms | 8587914 | 30 | 5.93083e+10 | 1.39118e+07 | 4.20527 | 2(Loss) |
| glaze | 487.286 | 1.17 | 3634.7ms | 8587914 | 30 | 1.16011e+12 | 1.68075e+07 | 5.08057 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2201.01 | 0.369476 | 896.844ms | 8588126 | 30 | 5.67081e+09 | 3.72114e+06 | 1.12471 | 1(Win) |
| glaze | 2074.5 | 0.283087 | 933.795ms | 8588126 | 30 | 3.7474e+09 | 3.94807e+06 | 1.19332 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 661.962 | 0.380613 | 3425.46ms | 9804437 | 30 | 8.67097e+10 | 1.4125e+07 | 3.73995 | 1(Win) |
| simdjson (ondemand) | 596.567 | 0.319257 | 3818.22ms | 9804437 | 30 | 7.51154e+10 | 1.56734e+07 | 4.14993 | 2(Loss) |
| glaze | 585.664 | 0.657205 | 3771.61ms | 9804437 | 30 | 3.30271e+11 | 1.59652e+07 | 4.22717 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2269.18 | 0.279695 | 1096.32ms | 11078090 | 30 | 5.08725e+09 | 4.65582e+06 | 1.0909 | 1(Win) |
| glaze | 2179.1 | 0.134153 | 1175.77ms | 11078090 | 30 | 1.26911e+09 | 4.84829e+06 | 1.13607 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2944.19 | 0.513364 | 21.0061ms | 264040 | 30 | 5.78335e+06 | 85527.1 | 0.840497 | 1(Win) |
| simdjson (ondemand) | 2869.94 | 0.788724 | 21.1524ms | 264040 | 30 | 1.4367e+07 | 87739.9 | 0.862245 | 2(Loss) |
| glaze | 1271.33 | 0.371907 | 47.9896ms | 264040 | 30 | 1.62783e+07 | 198066 | 1.94698 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3799.08 | 0.691408 | 24.4807ms | 399947 | 30 | 1.44556e+07 | 100398 | 0.651315 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3678.21 | 1.79574 | 24.6882ms | 399947 | 30 | 1.04026e+08 | 103697 | 0.672789 | 1(Tie) |
| glaze | 1717.32 | 0.325057 | 53.8604ms | 399947 | 30 | 1.56366e+07 | 222102 | 1.44138 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1012.49 | 0.360671 | 60.563ms | 264040 | 30 | 2.41382e+07 | 248703 | 2.44419 | 1(Win) |
| glaze | 886.405 | 0.365902 | 68.7636ms | 264040 | 30 | 3.24134e+07 | 284078 | 2.79232 | 2(Loss) |
| simdjson (ondemand) | 859.331 | 0.584998 | 71.0881ms | 264040 | 30 | 8.81553e+07 | 293028 | 2.88028 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4123.01 | 0.656749 | 35.5859ms | 264040 | 32 | 5.14827e+06 | 61073.9 | 0.599783 | 1(Win) |
| glaze | 2603.03 | 0.707116 | 23.9815ms | 263923 | 30 | 1.40249e+07 | 96693.8 | 0.950515 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1273.7 | 0.667599 | 73.7019ms | 399947 | 30 | 1.19901e+08 | 299458 | 1.94105 | 1(Win) |
| glaze | 1106.12 | 0.315361 | 83.9515ms | 399947 | 30 | 3.54764e+07 | 344827 | 2.23754 | 2(Loss) |
| jsonifier | 1058.03 | 0.396887 | 90.3908ms | 399947 | 30 | 6.14131e+07 | 360498 | 2.33936 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3747.04 | 0.631479 | 25.8625ms | 399947 | 30 | 1.23956e+07 | 101792 | 0.660299 | 1(Win) |
| glaze | 2699.38 | 0.524202 | 34.2656ms | 399830 | 30 | 1.64491e+07 | 141258 | 0.916664 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1678.68 | 0.340523 | 63.8287ms | 466906 | 30 | 2.44758e+07 | 265254 | 1.47443 | 1(Win) |
| jsonifier | 1366.7 | 0.322642 | 78.4796ms | 466906 | 30 | 3.31496e+07 | 325805 | 1.81111 | 2(Loss) |
| simdjson (ondemand) | 660.868 | 1.47021 | 160.288ms | 466906 | 30 | 2.94379e+09 | 673774 | 3.7457 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2097.95 | 0.315054 | 76.4401ms | 699405 | 30 | 3.00995e+07 | 317932 | 1.17987 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2094.47 | 0.330597 | 76.1837ms | 699405 | 30 | 3.32528e+07 | 318460 | 1.18182 | 1(Tie) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2407.86 | 0.346213 | 60.5842ms | 631514 | 30 | 2.24963e+07 | 250122 | 1.02794 | 1(Win) |
| glaze | 1606.12 | 0.229774 | 90.6048ms | 631514 | 30 | 2.22708e+07 | 374978 | 1.54125 | 2(Loss) |
