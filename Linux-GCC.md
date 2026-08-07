# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.6.87.2-microsoft-standard-WSL2 using the GCC 16.0.1 compiler).  

Latest Results: (Aug 07, 2026)
#### Using the following commits:
----
| Jsonifier: [e32235c](https://github.com/nihilai-collective/jsonifier/commit/e32235c)  
| Glaze: [2f6f5dc](https://github.com/stephenberry/glaze/commit/2f6f5dc)  
| Simdjson: [b3072d2](https://github.com/simdjson/simdjson/commit/b3072d2)  

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

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)

#### Note:
  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1257.94 | 0.136574 | 1.18683ms | 1811 | 30 | 105.482 | 1372.97 | 2.36256 | 1(Win) |
| glaze | 887.363 | 0.122388 | 0.723522ms | 1811 | 30 | 170.23 | 1946.33 | 3.37719 | 2(Loss) |
| simdjson (ondemand) | 239.882 | 0.0586609 | 2.06506ms | 1811 | 30 | 535.131 | 7199.8 | 12.6244 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 745.352 | 0.0756336 | 0.803975ms | 1811 | 30 | 92.1437 | 2317.17 | 4.02408 | 1(Win) |
| glaze | 532.744 | 0.210565 | 1.20755ms | 1798 | 30 | 1377.96 | 3218.63 | 5.6335 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2034.73 | 0.0433954 | 0.710869ms | 3873 | 30 | 18.6161 | 1815.27 | 1.47493 | 1(Win) |
| glaze | 1835.05 | 0.0640241 | 0.717293ms | 3873 | 30 | 49.8207 | 2012.8 | 1.63276 | 2(Loss) |
| simdjson (ondemand) | 472.984 | 0.15126 | 2.16158ms | 3873 | 30 | 4185.75 | 7809.1 | 6.40612 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2991.72 | 0.124067 | 0.533563ms | 3873 | 30 | 70.3862 | 1234.6 | 0.997866 | 1(Win) |
| glaze | 1362.41 | 0.205105 | 0.911561ms | 3873 | 30 | 927.582 | 2711.07 | 2.20771 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2104.9 | 0.0438154 | 0.687067ms | 3862 | 30 | 17.6333 | 1749.77 | 1.42216 | 1(Win) |
| glaze | 1748.11 | 0.180675 | 0.752306ms | 3862 | 30 | 434.714 | 2106.9 | 1.72027 | 2(Loss) |
| simdjson (ondemand) | 468.734 | 0.0760905 | 2.14434ms | 3862 | 30 | 1072.4 | 7857.53 | 6.46641 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2897.93 | 0.192632 | 1.03596ms | 3862 | 32 | 191.802 | 1270.94 | 1.02311 | 1(Win) |
| glaze | 1368.52 | 0.136449 | 0.945696ms | 3862 | 30 | 404.562 | 2691.3 | 2.18331 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2200.6 | 0.241548 | 0.319633ms | 905 | 30 | 26.9241 | 392.2 | 1.31285 | 1(Win) |
| glaze | 657.018 | 0.254432 | 1.05056ms | 905 | 32 | 357.468 | 1313.62 | 4.56236 | 2(Loss) |
| simdjson (ondemand) | 189.559 | 0.0585174 | 1.39459ms | 905 | 30 | 212.961 | 4553.07 | 15.9466 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1194.79 | 0.447495 | 0.390215ms | 905 | 30 | 313.482 | 722.367 | 2.47433 | 1(Win) |
| glaze | 363.798 | 0.164195 | 0.810176ms | 905 | 30 | 455.214 | 2372.4 | 8.26037 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3942.29 | 0.03742 | 0.804328ms | 9578 | 30 | 22.5517 | 2317 | 0.761251 | 1(Win) |
| glaze | 2746.99 | 0.123428 | 1.04392ms | 9578 | 30 | 505.338 | 3325.2 | 1.09744 | 2(Loss) |
| simdjson (ondemand) | 1485.49 | 0.0866812 | 1.80887ms | 9578 | 30 | 852.276 | 6149 | 2.03871 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5863.21 | 0.151254 | 0.604212ms | 9578 | 30 | 166.576 | 1557.9 | 0.50783 | 1(Win) |
| glaze | 3172.88 | 0.182653 | 0.952574ms | 9578 | 30 | 829.499 | 2878.87 | 0.946464 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5416.31 | 0.16486 | 1.76637ms | 33713 | 30 | 2873.03 | 5936 | 0.559004 | 1(Win) |
| simdjson (ondemand) | 5077.6 | 1.43245 | 1.87463ms | 33713 | 30 | 246805 | 6331.97 | 0.596548 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6628.42 | 0.190599 | 2.02499ms | 48024 | 30 | 5203.09 | 6909.53 | 0.456954 | 1(Win) |
| simdjson (ondemand) | 6026.67 | 0.0701079 | 1.99974ms | 48024 | 30 | 851.564 | 7599.43 | 0.50288 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2076.9 | 0.775317 | 33.2304ms | 294588 | 30 | 3.29973e+07 | 135269 | 1.46302 | 1(Win) |
| glaze | 1975.76 | 0.381259 | 82.7551ms | 294588 | 32 | 9.40481e+06 | 142194 | 1.53793 | 2(Loss) |
| simdjson (ondemand) | 1665.76 | 0.531159 | 41.4041ms | 294588 | 30 | 2.40754e+07 | 168656 | 1.82416 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5355.07 | 0.898118 | 13.0131ms | 294588 | 30 | 6.66023e+06 | 52462.7 | 0.566906 | 1(Win) |
| glaze | 4143.54 | 0.399359 | 17.0708ms | 294588 | 30 | 2.19955e+06 | 67802.2 | 0.73284 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2193.09 | 0.456119 | 43.4941ms | 406546 | 30 | 1.95068e+07 | 176788 | 1.38546 | 1(Win) |
| glaze | 2122.64 | 1.42456 | 43.7859ms | 406546 | 30 | 2.03119e+08 | 182656 | 1.43153 | 2(Loss) |
| jsonifier | 1801.8 | 0.390972 | 53.6572ms | 406546 | 30 | 2.12334e+07 | 215181 | 1.68649 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5605.95 | 0.341173 | 17.2145ms | 406546 | 30 | 1.67028e+06 | 69160.9 | 0.541604 | 1(Win) |
| glaze | 4788.92 | 0.429523 | 49.3701ms | 406546 | 32 | 3.86961e+06 | 80960.3 | 0.634223 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5373.31 | 0.0826621 | 1.71991ms | 33713 | 30 | 733.914 | 5983.5 | 0.563464 | 1(Win) |
| simdjson (ondemand) | 2750.79 | 0.0864092 | 3.07128ms | 33713 | 30 | 3060 | 11688 | 1.10287 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6579.11 | 0.207115 | 4.247ms | 48024 | 32 | 6652.03 | 6961.31 | 0.460427 | 1(Win) |
| simdjson (ondemand) | 3770.09 | 0.103161 | 3.29378ms | 48024 | 30 | 4711.58 | 12148.1 | 0.804717 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1978.11 | 0.432457 | 34.6369ms | 294588 | 30 | 1.13172e+07 | 142025 | 1.53614 | 1(Win) |
| jsonifier | 1650.02 | 0.508351 | 41.2479ms | 294588 | 30 | 2.24751e+07 | 170266 | 1.84159 | 2(Loss) |
| simdjson (ondemand) | 308.101 | 0.438333 | 220.667ms | 294588 | 30 | 4.79263e+08 | 911848 | 9.86349 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5231.09 | 0.389691 | 13.3846ms | 294588 | 30 | 1.31404e+06 | 53706 | 0.580257 | 1(Win) |
| glaze | 4755.17 | 0.339035 | 37.0548ms | 294588 | 32 | 1.28392e+06 | 59081.2 | 0.63859 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2264.53 | 0.396199 | 92.7824ms | 406546 | 30 | 1.38042e+07 | 171211 | 1.34189 | 1(Win) |
| jsonifier | 1697.92 | 0.370955 | 55.8635ms | 406546 | 30 | 2.15252e+07 | 228346 | 1.78978 | 2(Loss) |
| simdjson (ondemand) | 424.671 | 0.567558 | 221.732ms | 406546 | 30 | 8.05482e+08 | 912971 | 7.15627 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5363.02 | 0.751699 | 17.7586ms | 406546 | 30 | 8.85952e+06 | 72293.7 | 0.566221 | 1(Win) |
| glaze | 5022.21 | 0.508572 | 19.6629ms | 406546 | 30 | 4.62442e+06 | 77199.6 | 0.604881 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1289.06 | 0.568065 | 17.9831ms | 94651 | 30 | 4.74701e+06 | 70024.7 | 2.35683 | 1(Win) |
| glaze STATISTICAL TIE | 1236.99 | 1.10126 | 18.4657ms | 94651 | 30 | 1.93739e+07 | 72972.3 | 2.45577 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1214.38 | 0.792829 | 18.2331ms | 94651 | 30 | 1.04188e+07 | 74330.8 | 2.50165 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 5858.06 | 0.0490858 | 4.0327ms | 94651 | 30 | 1716.23 | 15408.9 | 0.51778 | 1(Win) |
| jsonifier | 5629.69 | 1.59138 | 9.26149ms | 94651 | 32 | 2.08342e+06 | 16034 | 0.537282 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1698.01 | 0.445557 | 19.2554ms | 136024 | 30 | 3.47597e+06 | 76396.7 | 1.78919 | 1(Win) |
| glaze | 1459.07 | 0.807721 | 21.1424ms | 136024 | 30 | 1.54712e+07 | 88907.9 | 2.08219 | 2(Loss) |
| jsonifier | 1234.82 | 0.432854 | 27.3434ms | 136024 | 30 | 6.20343e+06 | 105054 | 2.46066 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6667.31 | 0.40049 | 4.98926ms | 136024 | 30 | 182152 | 19456.5 | 0.454608 | 1(Win) |
| glaze | 5651.63 | 0.43618 | 5.78501ms | 136046 | 30 | 300799 | 22956.8 | 0.537024 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 761.372 | 0.66591 | 677.315ms | 2090234 | 30 | 9.11903e+09 | 2.61817e+06 | 3.99044 | 1(Win) |
| glaze | 710.896 | 0.185664 | 725.499ms | 2090234 | 30 | 8.13121e+08 | 2.80407e+06 | 4.27405 | 2(Loss) |
| simdjson (ondemand) | 669.31 | 1.31222 | 744.748ms | 2090234 | 30 | 4.58218e+10 | 2.97829e+06 | 4.54024 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1639.25 | 0.165969 | 301.477ms | 2090234 | 30 | 1.22202e+08 | 1.21605e+06 | 1.85347 | 1(Win) |
| glaze | 1374.7 | 1.3247 | 351.198ms | 2090234 | 30 | 1.10695e+10 | 1.45006e+06 | 2.21024 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2059.61 | 0.28386 | 801.011ms | 6661897 | 30 | 2.30013e+09 | 3.08469e+06 | 1.47543 | 1(Win) |
| glaze STATISTICAL TIE | 1773.64 | 1.00606 | 2091.53ms | 6661897 | 32 | 4.15587e+10 | 3.58205e+06 | 1.71334 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1770.49 | 0.799938 | 918.055ms | 6661897 | 30 | 2.47195e+10 | 3.58842e+06 | 1.7164 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3112.73 | 0.293005 | 540.523ms | 6661897 | 30 | 1.07297e+09 | 2.04107e+06 | 0.976121 | 1(Win) |
| glaze | 3082.83 | 0.199907 | 1226.98ms | 6661897 | 32 | 5.43126e+08 | 2.06086e+06 | 0.985562 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1776.59 | 0.803314 | 66.1222ms | 500299 | 30 | 1.3963e+08 | 268561 | 1.71029 | 1(Win) |
| jsonifier | 1695.31 | 0.552674 | 67.5306ms | 500299 | 30 | 7.25805e+07 | 281436 | 1.79241 | 2(Loss) |
| simdjson (ondemand) | 1148.73 | 0.264521 | 100.413ms | 500299 | 30 | 3.62128e+07 | 415346 | 2.64538 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 5421.32 | 0.573137 | 53.1168ms | 500299 | 32 | 8.14173e+06 | 88008.6 | 0.560284 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5319.62 | 0.851855 | 21.7512ms | 500299 | 30 | 1.75126e+07 | 89691.1 | 0.570854 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2892.2 | 0.548204 | 169.083ms | 1439562 | 30 | 2.03147e+08 | 474681 | 1.05057 | 1(Win) |
| glaze | 2787.49 | 0.276591 | 119.332ms | 1439562 | 30 | 5.56714e+07 | 492513 | 1.09016 | 2(Loss) |
| jsonifier | 2674.1 | 0.24746 | 346.485ms | 1439562 | 32 | 5.16495e+07 | 513397 | 1.13642 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7103.22 | 1.11206 | 47.9766ms | 1439562 | 30 | 1.38588e+08 | 193275 | 0.427523 | 1(Win) |
| glaze | 5284.05 | 0.432195 | 65.8486ms | 1439584 | 30 | 3.78286e+07 | 259818 | 0.574827 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1846.2 | 0.946714 | 7.4167ms | 56369 | 30 | 2.27972e+06 | 29118 | 1.64448 | 1(Tie) |
| glaze STATISTICAL TIE | 1840.1 | 0.373107 | 7.51732ms | 56369 | 30 | 356440 | 29214.5 | 1.64998 | 1(Tie) |
| simdjson (ondemand) | 1290.21 | 0.188973 | 10.4973ms | 56369 | 30 | 185987 | 41665.9 | 2.35405 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6016.41 | 2.28564 | 2.34344ms | 56369 | 30 | 1.25124e+06 | 8935.17 | 0.503225 | 1(Win) |
| jsonifier | 5437.06 | 0.388578 | 2.68577ms | 56369 | 30 | 44282.4 | 9887.27 | 0.555259 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2254.29 | 1.68376 | 22.9392ms | 94370 | 32 | 1.44597e+07 | 39923.2 | 1.34725 | 1(Win) |
| simdjson (ondemand) | 2075.09 | 1.84127 | 11.1078ms | 94370 | 30 | 1.91314e+07 | 43370.7 | 1.46356 | 2(Loss) |
| jsonifier | 1989.8 | 0.891348 | 12.1053ms | 94370 | 30 | 4.876e+06 | 45229.7 | 1.52649 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6752 | 1.373 | 3.48438ms | 94370 | 30 | 1.00476e+06 | 13329.1 | 0.447934 | 1(Win) |
| glaze | 5504.02 | 1.91031 | 4.15563ms | 94370 | 30 | 2.92708e+06 | 16351.4 | 0.551018 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1545.61 | 1.55333 | 40.4475ms | 52708 | 64 | 1.63328e+07 | 32522 | 1.9642 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1510.36 | 1.49343 | 8.8921ms | 52708 | 30 | 7.41115e+06 | 33281.1 | 2.01051 | 1(Tie) |
| glaze | 1303.51 | 2.05014 | 10.2766ms | 52708 | 30 | 1.87505e+07 | 38562.2 | 2.32915 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 6487.81 | 0.540629 | 2.19874ms | 52708 | 30 | 52635.2 | 7747.8 | 0.466583 | 1(Tie) |
| jsonifier STATISTICAL TIE | 6334.46 | 1.18378 | 2.19834ms | 52708 | 30 | 264727 | 7935.37 | 0.475904 | 1(Tie) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2056.74 | 0.965082 | 8.17668ms | 70103 | 30 | 2.95233e+06 | 32505.6 | 1.47608 | 1(Win) |
| glaze | 1559.46 | 0.53063 | 10.9023ms | 70103 | 30 | 1.55249e+06 | 42870.8 | 1.94762 | 2(Loss) |
| jsonifier | 1354.6 | 0.509337 | 14.3479ms | 70103 | 30 | 1.89574e+06 | 49354.2 | 2.24224 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6473.28 | 0.152347 | 2.84582ms | 70103 | 30 | 7426.99 | 10327.9 | 0.466484 | 1(Win) |
| glaze | 6221.62 | 0.851111 | 2.88521ms | 70103 | 30 | 250935 | 10745.7 | 0.487368 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1393.76 | 0.0956275 | 2.27064ms | 11812 | 30 | 1792.09 | 8082.33 | 2.17334 | 1(Win) |
| jsonifier | 1344.95 | 0.100685 | 2.37058ms | 11812 | 30 | 2133.48 | 8375.63 | 2.25319 | 2(Loss) |
| simdjson (ondemand) | 1119.11 | 0.100324 | 2.73116ms | 11812 | 30 | 3059.4 | 10065.9 | 2.70876 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5625.74 | 0.353399 | 0.746266ms | 11812 | 30 | 1502.24 | 2002.37 | 0.528338 | 1(Win) |
| glaze | 4879.99 | 0.110114 | 0.828178ms | 11812 | 30 | 193.826 | 2308.37 | 0.61468 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2615.43 | 0.133003 | 3.09666ms | 31235 | 30 | 6883.95 | 11389.3 | 1.15924 | 1(Win) |
| jsonifier STATISTICAL TIE | 2324.85 | 2.19413 | 3.35107ms | 31235 | 30 | 2.37106e+06 | 12812.9 | 1.30435 | 2(Tie) |
| glaze STATISTICAL TIE | 2238.54 | 0.115406 | 3.53847ms | 31235 | 30 | 7075.09 | 13306.9 | 1.35516 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8149.12 | 0.134268 | 1.16949ms | 31235 | 30 | 722.654 | 3655.37 | 0.366673 | 1(Win) |
| glaze | 6481.6 | 0.146567 | 2.98512ms | 31235 | 32 | 1451.92 | 4595.78 | 0.465631 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3270.64 | 0.868969 | 18.3789ms | 108313 | 32 | 2.41021e+06 | 31582.6 | 0.928313 | 1(Win) |
| glaze | 2129.82 | 1.64691 | 11.9364ms | 108313 | 30 | 1.91397e+07 | 48499.5 | 1.4259 | 2(Loss) |
| simdjson (ondemand) | 1579.17 | 0.463957 | 16.1285ms | 108313 | 30 | 2.763e+06 | 65411.1 | 1.9237 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6558.03 | 0.287295 | 4.20707ms | 108313 | 30 | 61431.4 | 15751 | 0.461416 | 1(Win) |
| glaze | 5820.56 | 0.614616 | 11.3247ms | 108313 | 32 | 380706 | 17746.6 | 0.521133 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2838.08 | 0.761041 | 18.3528ms | 213963 | 30 | 8.98183e+06 | 71897.5 | 1.07029 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2831.22 | 0.705242 | 18.2258ms | 213963 | 30 | 7.75047e+06 | 72071.8 | 1.07292 | 1(Tie) |
| jsonifier | 2310.92 | 1.00181 | 21.4842ms | 213963 | 30 | 2.34745e+07 | 88298.5 | 1.31448 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8089.1 | 0.23777 | 14.805ms | 213963 | 32 | 115118 | 25225.4 | 0.374994 | 1(Win) |
| glaze | 5646.52 | 2.06776 | 9.03525ms | 213963 | 30 | 1.67509e+07 | 36137.5 | 0.537639 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 807.787 | 0.172909 | 1269.93ms | 1834197 | 32 | 4.48623e+08 | 2.16545e+06 | 3.76161 | 1(Win) |
| glaze | 609.597 | 0.220998 | 691.702ms | 1834197 | 30 | 1.20644e+09 | 2.86948e+06 | 4.98425 | 2(Loss) |
| simdjson (ondemand) | 542.235 | 1.07414 | 756.924ms | 1834197 | 30 | 3.60211e+10 | 3.22596e+06 | 5.60311 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1027.02 | 0.276279 | 412.175ms | 1834197 | 30 | 6.64284e+08 | 1.70321e+06 | 2.95835 | 1(Win) |
| glaze | 872.676 | 0.659124 | 476.457ms | 1833577 | 30 | 5.23296e+09 | 2.00376e+06 | 3.48034 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2581.22 | 0.402508 | 2178.99ms | 9930848 | 32 | 6.97945e+09 | 3.66911e+06 | 1.17714 | 1(Win) |
| glaze | 2424.51 | 0.182546 | 981.429ms | 9930848 | 30 | 1.52543e+09 | 3.90627e+06 | 1.2533 | 2(Loss) |
| jsonifier | 2083.31 | 0.253771 | 2714.09ms | 9930848 | 32 | 4.25892e+09 | 4.54603e+06 | 1.45853 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2826.78 | 0.735539 | 863.034ms | 9930848 | 30 | 1.82188e+10 | 3.35038e+06 | 1.07482 | 1(Win) |
| glaze | 2355.8 | 1.38464 | 1063.67ms | 9930228 | 30 | 9.29478e+10 | 4.01995e+06 | 1.28972 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1439.12 | 0.356477 | 104.241ms | 642697 | 30 | 6.91513e+07 | 425900 | 2.11154 | 1(Win) |
| glaze | 1084.66 | 0.333594 | 135.823ms | 642697 | 30 | 1.06607e+08 | 565085 | 2.80166 | 2(Loss) |
| simdjson (ondemand) | 1045.79 | 0.359185 | 141.315ms | 642697 | 30 | 1.32947e+08 | 586084 | 2.90537 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1690.43 | 0.323394 | 502.224ms | 642697 | 64 | 8.79959e+07 | 362584 | 1.7974 | 1(Win) |
| glaze | 1445.2 | 0.612244 | 101.819ms | 642692 | 30 | 2.02265e+08 | 424107 | 2.1019 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1859.18 | 0.918303 | 820.943ms | 1225964 | 64 | 2.13435e+09 | 628864 | 1.63434 | 1(Win) |
| glaze | 1699.25 | 2.07979 | 158.647ms | 1225964 | 30 | 6.14329e+09 | 688051 | 1.78831 | 2(Loss) |
| jsonifier | 1578.16 | 0.299262 | 178.603ms | 1225964 | 30 | 1.47462e+08 | 740845 | 1.92555 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2546 | 1.34588 | 109.439ms | 1225964 | 30 | 1.14597e+09 | 459218 | 1.19326 | 1(Win) |
| glaze | 2224.89 | 0.346132 | 126.903ms | 1225970 | 30 | 9.9254e+07 | 525499 | 1.36576 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1105.78 | 0.852671 | 84.5714ms | 409725 | 30 | 2.72355e+08 | 353366 | 2.74791 | 1(Win) |
| simdjson (ondemand) | 965.314 | 0.357731 | 99.4812ms | 409725 | 30 | 6.29044e+07 | 404784 | 3.14798 | 2(Loss) |
| glaze | 906.898 | 0.360025 | 103.821ms | 409725 | 30 | 7.21865e+07 | 430858 | 3.35077 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4484.74 | 0.642397 | 21.2664ms | 409725 | 30 | 9.39809e+06 | 87127.6 | 0.677202 | 1(Win) |
| glaze | 3371.47 | 1.39415 | 27.9244ms | 409725 | 30 | 7.83228e+07 | 115897 | 0.901052 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1697.4 | 0.336248 | 107.814ms | 785750 | 30 | 6.61058e+07 | 441469 | 1.79022 | 1(Win) |
| glaze | 1458.25 | 0.324072 | 125.639ms | 785750 | 30 | 8.31976e+07 | 513870 | 2.08389 | 2(Loss) |
| jsonifier | 1245.73 | 0.291548 | 148.171ms | 785750 | 30 | 9.22709e+07 | 601536 | 2.43949 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5343.59 | 0.290799 | 34.6119ms | 785750 | 30 | 4.98897e+06 | 140233 | 0.568361 | 1(Win) |
| glaze | 4065.98 | 1.11919 | 44.5138ms | 785750 | 30 | 1.27634e+08 | 184297 | 0.747071 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1276.7 | 0.45113 | 3801.29ms | 8587914 | 32 | 2.68012e+10 | 6.41505e+06 | 2.38026 | 1(Win) |
| simdjson (ondemand) | 1208.25 | 0.379382 | 1748.48ms | 8587914 | 30 | 1.98399e+10 | 6.77848e+06 | 2.5151 | 2(Loss) |
| glaze | 1142.82 | 0.305586 | 1832.78ms | 8587914 | 30 | 1.43882e+10 | 7.16654e+06 | 2.65912 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3184.65 | 0.939081 | 651.85ms | 8588126 | 30 | 1.74986e+10 | 2.5718e+06 | 0.953885 | 1(Win) |
| glaze | 2976.8 | 0.423835 | 706.821ms | 8588126 | 30 | 4.07956e+09 | 2.75137e+06 | 1.02054 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1295.12 | 0.852079 | 1765.71ms | 9804437 | 30 | 1.13529e+11 | 7.2196e+06 | 2.34638 | 1(Win) |
| glaze | 1206.49 | 0.370516 | 4561.04ms | 9804437 | 32 | 2.63852e+10 | 7.74995e+06 | 2.51877 | 2(Loss) |
| jsonifier | 1107.83 | 0.400389 | 2127.73ms | 9804437 | 30 | 3.42596e+10 | 8.44012e+06 | 2.74312 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3198.43 | 0.953803 | 1870.78ms | 11078090 | 32 | 3.17632e+10 | 3.30315e+06 | 0.94987 | 1(Win) |
| glaze | 2903.1 | 0.640404 | 953.719ms | 11078090 | 30 | 1.62943e+10 | 3.63918e+06 | 1.04657 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5387.96 | 0.590459 | 11.7266ms | 264040 | 30 | 2.2845e+06 | 46735.3 | 0.563759 | 1(Win) |
| jsonifier | 5266.01 | 0.521264 | 12.1963ms | 264040 | 30 | 1.86386e+06 | 47817.6 | 0.576832 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 7148.97 | 0.438901 | 13.2732ms | 399947 | 30 | 1.64503e+06 | 53353 | 0.424901 | 1(Win) |
| jsonifier | 6587.24 | 1.46688 | 14.279ms | 399947 | 30 | 2.16426e+07 | 57902.7 | 0.461152 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1735.88 | 0.634642 | 35.8296ms | 264040 | 30 | 2.54261e+07 | 145061 | 1.75037 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1584.13 | 1.03824 | 38.5513ms | 264040 | 30 | 8.17098e+07 | 158957 | 1.91795 | 2(Tie) |
| glaze STATISTICAL TIE | 1564.38 | 0.856233 | 39.6635ms | 264040 | 30 | 5.69847e+07 | 160963 | 1.94237 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6506.08 | 0.723706 | 10.3782ms | 263923 | 30 | 2.35159e+06 | 38686.4 | 0.466711 | 1(Win) |
| jsonifier | 6029.86 | 1.45352 | 10.6142ms | 264040 | 30 | 1.10533e+07 | 41760.2 | 0.503371 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2283.11 | 1.15374 | 40.8709ms | 399947 | 30 | 1.11453e+08 | 167062 | 1.33085 | 1(Win) |
| glaze | 1893.77 | 0.612724 | 48.7458ms | 399947 | 30 | 4.56881e+07 | 201408 | 1.60454 | 2(Loss) |
| jsonifier | 1387.56 | 0.839151 | 68.1697ms | 399947 | 30 | 1.59625e+08 | 274884 | 2.18996 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6982.34 | 2.43704 | 13.7525ms | 399947 | 30 | 5.31678e+07 | 54626.3 | 0.434786 | 1(Win) |
| glaze | 5750.37 | 1.09304 | 16.7746ms | 399830 | 30 | 1.576e+07 | 66310.1 | 0.528248 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2442.44 | 0.389244 | 44.3833ms | 466906 | 30 | 1.5107e+07 | 182308 | 1.24401 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2432.09 | 0.893814 | 44.2168ms | 466906 | 30 | 8.03366e+07 | 183084 | 1.24923 | 1(Tie) |
| simdjson (ondemand) | 1318.8 | 0.988994 | 81.6572ms | 466906 | 30 | 3.34508e+08 | 337636 | 2.30377 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3706.29 | 0.633334 | 44.2295ms | 699405 | 30 | 3.89731e+07 | 179965 | 0.819701 | 1(Tie) |
| glaze STATISTICAL TIE | 3648.07 | 0.961273 | 44.0932ms | 699405 | 30 | 9.26715e+07 | 182838 | 0.832953 | 1(Tie) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3235.1 | 0.455274 | 44.999ms | 631514 | 30 | 2.15506e+07 | 186164 | 0.939226 | 1(Win) |
| glaze | 2439.21 | 0.500573 | 60.2409ms | 631514 | 30 | 4.58274e+07 | 246908 | 1.24584 | 2(Loss) |
