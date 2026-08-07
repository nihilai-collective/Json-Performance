# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the Clang 22.1.8 compiler).  

Latest Results: (Aug 07, 2026)
#### Using the following commits:
----
| Jsonifier: [e32235c](https://github.com/nihilai-collective/jsonifier/commit/e32235c)  
| Glaze: [2f6f5dc](https://github.com/stephenberry/glaze/commit/2f6f5dc)  
| Simdjson: [b3072d2](https://github.com/simdjson/simdjson/commit/b3072d2)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)

#### Note:
  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 801.788 | 0.209726 | 12.2433ms | 1811 | 30 | 612.271 | 2154.07 | 1(Win) |
| glaze | 514.284 | 0.127554 | 0.938792ms | 1811 | 30 | 550.478 | 3358.27 | 2(Loss) |
| simdjson (ondemand) | 184.879 | 0.0448096 | 2.42912ms | 1811 | 30 | 525.683 | 9341.8 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 518.78 | 0.547984 | 1.00017ms | 1811 | 30 | 9984.56 | 3329.17 | 1(Win) |
| glaze | 385.81 | 0.137434 | 1.23438ms | 1798 | 30 | 1119.29 | 4444.43 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1567.18 | 0.983658 | 0.776166ms | 3873 | 30 | 16123.8 | 2356.83 | 1(Win) |
| glaze | 944.368 | 0.0847996 | 1.03271ms | 3873 | 30 | 330.006 | 3911.17 | 2(Loss) |
| simdjson (ondemand) | 381.934 | 0.177953 | 2.41429ms | 3873 | 30 | 8884.89 | 9670.73 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1382.9 | 1.71243 | 0.827ms | 3873 | 30 | 62757 | 2670.9 | 1(Win) |
| glaze | 1129.27 | 0.226033 | 0.925625ms | 3873 | 30 | 1639.7 | 3270.77 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1476.54 | 0.791305 | 0.729875ms | 3862 | 30 | 11688 | 2494.4 | 1(Win) |
| glaze | 910.942 | 0.370794 | 1.11963ms | 3862 | 30 | 6742.63 | 4043.17 | 2(Loss) |
| simdjson (ondemand) | 404.494 | 0.209322 | 2.90242ms | 3862 | 30 | 10898.2 | 9105.43 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1765.51 | 0.381978 | 0.689833ms | 3862 | 30 | 1904.95 | 2086.13 | 1(Win) |
| glaze | 1116.53 | 0.235695 | 0.923167ms | 3862 | 30 | 1813.46 | 3298.7 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1215.88 | 0.525214 | 0.278375ms | 905 | 30 | 416.971 | 709.833 | 1(Win) |
| glaze | 328.103 | 0.507855 | 0.768917ms | 905 | 30 | 5353.98 | 2630.5 | 2(Loss) |
| simdjson (ondemand) | 190.505 | 0.0978677 | 1.17033ms | 905 | 30 | 589.775 | 4530.47 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 699.829 | 0.308603 | 0.401375ms | 905 | 30 | 434.547 | 1233.27 | 1(Win) |
| glaze | 292.859 | 1.57746 | 0.79425ms | 905 | 30 | 64836.2 | 2947.07 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1959.1 | 1.31819 | 1.30046ms | 9578 | 30 | 113323 | 4662.5 | 1(Win) |
| glaze | 1479.25 | 0.0677905 | 1.62808ms | 9578 | 30 | 525.689 | 6174.97 | 2(Loss) |
| simdjson (ondemand) | 689.095 | 0.0668915 | 3.34392ms | 9578 | 30 | 2358.6 | 13255.5 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3000.29 | 0.0636943 | 0.833042ms | 9578 | 30 | 112.809 | 3044.47 | 1(Win) |
| glaze | 2514.97 | 0.263808 | 1.01158ms | 9578 | 30 | 2754.1 | 3631.97 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3689.06 | 0.0610361 | 2.30717ms | 33713 | 30 | 848.907 | 8715.3 | 1(Win) |
| simdjson (ondemand) | 3012.63 | 1.74905 | 2.74363ms | 33713 | 30 | 1.04526e+06 | 10672.1 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4229.88 | 0.0514577 | 2.81854ms | 48024 | 30 | 931.289 | 10827.6 | 1(Win) |
| simdjson (ondemand) | 3494.65 | 1.46166 | 3.36888ms | 48024 | 30 | 1.10084e+06 | 13105.5 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1375.4 | 0.775742 | 52.3297ms | 294588 | 30 | 7.53231e+07 | 204261 | 1(Win) |
| glaze | 1057.19 | 0.229252 | 67.4833ms | 294588 | 30 | 1.11345e+07 | 265743 | 2(Loss) |
| simdjson (ondemand) | 947.729 | 2.28764 | 71.1004ms | 294588 | 30 | 1.37962e+09 | 296436 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2428.74 | 1.85552 | 69.8012ms | 294588 | 32 | 1.47417e+08 | 115673 | 1(Tie) |
| glaze STATISTICAL TIE | 2402.09 | 0.182323 | 28.574ms | 294588 | 30 | 1.36413e+06 | 116957 | 1(Tie) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1749.64 | 0.311128 | 55.1175ms | 406546 | 30 | 1.42601e+07 | 221596 | 1(Win) |
| jsonifier | 1274.93 | 1.00507 | 71.438ms | 406546 | 30 | 2.80259e+08 | 304105 | 2(Loss) |
| simdjson (ondemand) | 1193.53 | 0.463068 | 79.299ms | 406546 | 30 | 6.78831e+07 | 324845 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3250.77 | 0.776089 | 29.636ms | 406546 | 30 | 2.57036e+07 | 119268 | 1(Win) |
| glaze | 2459.09 | 0.221427 | 38.5046ms | 406546 | 30 | 3.6564e+06 | 157665 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3255.89 | 1.83874 | 2.62862ms | 33713 | 30 | 989051 | 9874.8 | 1(Win) |
| simdjson (ondemand) | 2300.41 | 0.0778939 | 3.64346ms | 33713 | 30 | 3555.6 | 13976.3 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3784.23 | 1.64108 | 4.22796ms | 48024 | 30 | 1.18343e+06 | 12102.7 | 1(Win) |
| simdjson (ondemand) | 2546.18 | 1.85982 | 4.47808ms | 48024 | 30 | 3.3574e+06 | 17987.5 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1244.2 | 0.731008 | 70.3159ms | 294588 | 30 | 8.17369e+07 | 225801 | 1(Win) |
| jsonifier | 1161.05 | 0.520892 | 3200.2ms | 294588 | 512 | 8.13379e+08 | 241972 | 2(Loss) |
| simdjson (ondemand) | 270.66 | 1.75103 | 699.254ms | 294588 | 32 | 1.0571e+10 | 1.03798e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2634.51 | 0.925475 | 31.9494ms | 294588 | 30 | 2.92202e+07 | 106639 | 1(Win) |
| glaze | 2378.98 | 0.502504 | 29.6145ms | 294588 | 30 | 1.05645e+07 | 118093 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1610.51 | 1.07572 | 58.8424ms | 406546 | 30 | 2.01192e+08 | 240739 | 1(Win) |
| jsonifier | 1339.54 | 0.830809 | 69.0293ms | 406546 | 30 | 1.73472e+08 | 289436 | 2(Loss) |
| simdjson (ondemand) | 408.212 | 1.15299 | 654.832ms | 406546 | 32 | 3.8375e+09 | 949783 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2600.94 | 2.24298 | 84.9042ms | 406546 | 32 | 3.57735e+08 | 149066 | 1(Win) |
| glaze | 1863.79 | 2.49673 | 113.298ms | 406546 | 32 | 8.6321e+08 | 208023 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 787.445 | 0.438095 | 28.4061ms | 94651 | 30 | 7.56602e+06 | 114632 | 1(Win) |
| glaze | 756.976 | 0.707392 | 32.0024ms | 94651 | 30 | 2.13466e+07 | 119246 | 2(Loss) |
| simdjson (ondemand) | 691.518 | 0.840767 | 32.7193ms | 94651 | 30 | 3.61341e+07 | 130534 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2890.07 | 1.73409 | 7.77879ms | 94651 | 30 | 8.80032e+06 | 31233.3 | 1(Win) |
| glaze | 2524.54 | 1.83 | 8.65062ms | 94651 | 30 | 1.28443e+07 | 35755.5 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1034.64 | 0.992468 | 31.9254ms | 136024 | 30 | 4.64521e+07 | 125379 | 1(Win) |
| simdjson (ondemand) | 920.941 | 0.797576 | 187.324ms | 136024 | 64 | 8.07778e+07 | 140859 | 2(Loss) |
| jsonifier | 814.67 | 1.80273 | 37.7294ms | 136024 | 30 | 2.47201e+08 | 159233 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2874.66 | 2.06045 | 12.5093ms | 136024 | 30 | 2.59361e+07 | 45126.2 | 1(Win) |
| glaze | 2576.77 | 1.98558 | 12.465ms | 136046 | 30 | 2.99859e+07 | 50351.3 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 550.723 | 0.726509 | 858.988ms | 2090234 | 30 | 2.07456e+10 | 3.61961e+06 | 1(Win) |
| glaze | 442.084 | 0.634872 | 2703.13ms | 2090234 | 32 | 2.62243e+10 | 4.50911e+06 | 2(Loss) |
| simdjson (ondemand) | 320.953 | 0.555203 | 1510.29ms | 2090234 | 30 | 3.56724e+10 | 6.21089e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1482.03 | 0.61628 | 407.935ms | 2090234 | 30 | 2.06137e+09 | 1.34505e+06 | 1(Win) |
| glaze | 1281.17 | 0.758213 | 371.978ms | 2090234 | 30 | 4.17522e+09 | 1.55592e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1256.63 | 0.633116 | 1198.81ms | 6661897 | 30 | 3.07376e+10 | 5.05581e+06 | 1(Win) |
| glaze | 1140.41 | 0.339492 | 1393.5ms | 6661897 | 30 | 1.07314e+10 | 5.57105e+06 | 2(Loss) |
| simdjson (ondemand) | 970.04 | 0.999808 | 1610.43ms | 6661897 | 30 | 1.28639e+11 | 6.54951e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3085.36 | 0.671862 | 2917ms | 6661897 | 64 | 1.22497e+10 | 2.05917e+06 | 1(Win) |
| glaze | 2348.57 | 0.531604 | 702.303ms | 6661897 | 30 | 6.20424e+09 | 2.70517e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1495.33 | 0.597055 | 88.8912ms | 500299 | 30 | 1.08877e+08 | 319075 | 1(Win) |
| glaze | 936.465 | 1.37074 | 125.291ms | 500299 | 30 | 1.46321e+09 | 509493 | 2(Loss) |
| simdjson (ondemand) | 638.557 | 1.38658 | 182.467ms | 500299 | 30 | 3.22013e+09 | 747189 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2307.55 | 0.956811 | 49.9728ms | 500299 | 30 | 1.17416e+08 | 206765 | 1(Win) |
| glaze | 1583.25 | 1.1519 | 72.0639ms | 500299 | 30 | 3.61499e+08 | 301356 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1944.86 | 1.36081 | 167.673ms | 1439562 | 30 | 2.76822e+09 | 705897 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1724.41 | 0.830306 | 191.968ms | 1439562 | 30 | 1.31092e+09 | 796139 | 2(Tie) |
| glaze STATISTICAL TIE | 1722.46 | 1.63548 | 220.425ms | 1439562 | 30 | 5.09768e+09 | 797042 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4623.62 | 0.175662 | 76.2641ms | 1439562 | 30 | 8.16155e+06 | 296926 | 1(Win) |
| glaze | 2459.63 | 0.432995 | 134.872ms | 1439584 | 30 | 1.75236e+08 | 558172 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1739.73 | 0.0431491 | 8.26287ms | 56369 | 30 | 5333.1 | 30899.9 | 1(Win) |
| glaze | 1059.1 | 1.18872 | 30.4535ms | 56369 | 32 | 1.16496e+07 | 50757.8 | 2(Loss) |
| simdjson (ondemand) | 885.974 | 1.25546 | 15.3047ms | 56369 | 30 | 1.74088e+07 | 60676.4 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2641.82 | 0.241383 | 5.56596ms | 56369 | 30 | 72378 | 20348.7 | 1(Win) |
| glaze | 2254.52 | 0.911075 | 29.3953ms | 56369 | 64 | 3.02038e+06 | 23844.4 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1551.36 | 1.40226 | 15.5263ms | 94370 | 30 | 1.98529e+07 | 58012.6 | 1(Win) |
| glaze STATISTICAL TIE | 1308.38 | 2.25858 | 108.405ms | 94370 | 64 | 1.54471e+08 | 68785.8 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1291.12 | 2.20121 | 16.5796ms | 94370 | 30 | 7.06284e+07 | 69705.6 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3457.42 | 0.2528 | 6.61958ms | 94370 | 30 | 129909 | 26030.5 | 1(Win) |
| glaze | 1965.62 | 2.25647 | 16.6942ms | 94370 | 30 | 3.20221e+07 | 45786.2 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1328.51 | 1.06467 | 60.542ms | 52708 | 64 | 1.03856e+07 | 37836.5 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1106 | 1.41386 | 13.7925ms | 52708 | 30 | 1.23873e+07 | 45448.7 | 2(Tie) |
| glaze STATISTICAL TIE | 1075.79 | 1.40365 | 15.4432ms | 52708 | 30 | 1.29044e+07 | 46725 | 2(Tie) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3766.67 | 2.0462 | 7.8975ms | 52708 | 32 | 2.38608e+06 | 13345 | 1(Win) |
| glaze | 3120.78 | 0.485989 | 4.05117ms | 52708 | 30 | 183824 | 16107 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1401.11 | 0.509132 | 318.11ms | 70103 | 256 | 1.51087e+07 | 47716 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1387.6 | 1.74023 | 11.7619ms | 70103 | 30 | 2.10902e+07 | 48180.6 | 1(Tie) |
| jsonifier | 1238.54 | 1.71478 | 14.3671ms | 70103 | 30 | 2.57034e+07 | 53979.2 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3887.13 | 0.29027 | 10.4315ms | 70103 | 32 | 79757.4 | 17199.2 | 1(Win) |
| glaze | 3328.66 | 1.02946 | 5.2345ms | 70103 | 30 | 1.28254e+06 | 20084.8 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1181.11 | 0.278211 | 2.70783ms | 11812 | 30 | 21121.9 | 9537.43 | 1(Win) |
| glaze | 751.82 | 1.24836 | 3.81188ms | 11812 | 30 | 1.04959e+06 | 14983.4 | 2(Loss) |
| simdjson (ondemand) | 646.939 | 1.34325 | 4.26617ms | 11812 | 30 | 1.64117e+06 | 17412.5 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3124.28 | 0.246067 | 1.04113ms | 11812 | 30 | 2361.43 | 3605.57 | 1(Win) |
| glaze | 1314.33 | 1.88411 | 2.34088ms | 11812 | 30 | 782300 | 8570.77 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1714.68 | 0.0836387 | 4.57575ms | 31235 | 30 | 6333.6 | 17372.3 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1461.98 | 1.82574 | 5.00858ms | 31235 | 30 | 4.15145e+06 | 20375.1 | 2(Tie) |
| glaze STATISTICAL TIE | 1416.37 | 1.6248 | 11.3903ms | 31235 | 32 | 3.7366e+06 | 21031.2 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3183.61 | 1.75451 | 5.53137ms | 31235 | 32 | 862394 | 9356.69 | 1(Win) |
| glaze | 2291.13 | 0.195783 | 3.384ms | 31235 | 30 | 19438.2 | 13001.4 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2290.22 | 1.69892 | 11.2982ms | 108313 | 30 | 1.76147e+07 | 45102.8 | 1(Win) |
| glaze | 1176.76 | 0.341298 | 22.6475ms | 108313 | 30 | 2.6926e+06 | 87779.2 | 2(Loss) |
| simdjson (ondemand) | 896.683 | 1.81379 | 28.1195ms | 108313 | 30 | 1.30973e+08 | 115197 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2227.21 | 1.64349 | 25.6842ms | 108313 | 32 | 1.85919e+07 | 46378.9 | 1(Win) |
| glaze | 1569.54 | 1.03261 | 37.5222ms | 108313 | 32 | 1.47788e+07 | 65812.6 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2131.21 | 2.24498 | 23.2737ms | 213963 | 30 | 1.38603e+08 | 95744.4 | 1(Win) |
| glaze | 2035.57 | 0.390324 | 25.0914ms | 213963 | 30 | 4.59282e+06 | 100243 | 2(Loss) |
| simdjson (ondemand) | 1810.83 | 0.47446 | 27.9931ms | 213963 | 30 | 8.57511e+06 | 112683 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4100.5 | 1.3253 | 12.8149ms | 213963 | 30 | 1.30484e+07 | 49762.5 | 1(Win) |
| glaze | 1767.38 | 0.971991 | 26.9779ms | 213963 | 30 | 3.77802e+07 | 115454 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 641.959 | 0.507477 | 677.287ms | 1834197 | 30 | 5.73629e+09 | 2.72483e+06 | 1(Win) |
| glaze | 427.59 | 0.750902 | 1002.12ms | 1834197 | 30 | 2.83091e+10 | 4.0909e+06 | 2(Loss) |
| simdjson (ondemand) | 319.233 | 0.706823 | 1366.07ms | 1834197 | 30 | 4.50007e+10 | 5.47947e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 783.415 | 0.0987803 | 546.052ms | 1834197 | 30 | 1.45939e+08 | 2.23282e+06 | 1(Win) |
| glaze | 668.953 | 1.39524 | 1496.15ms | 1833577 | 32 | 4.2565e+10 | 2.61399e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1759.25 | 0.91424 | 6426.07ms | 9930848 | 64 | 1.5503e+11 | 5.38341e+06 | 1(Win) |
| glaze | 1673.71 | 0.499548 | 8001.78ms | 9930848 | 64 | 5.11386e+10 | 5.65858e+06 | 2(Loss) |
| simdjson (ondemand) | 1414.48 | 0.356775 | 4098.78ms | 9930848 | 32 | 1.82608e+10 | 6.69561e+06 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1128.37 | 0.691307 | 156.751ms | 642697 | 30 | 4.2303e+08 | 543193 | 1(Win) |
| glaze | 921.634 | 0.896208 | 162.863ms | 642697 | 30 | 1.0657e+09 | 665040 | 2(Loss) |
| simdjson (ondemand) | 570.643 | 1.21987 | 274.259ms | 642697 | 30 | 5.15028e+09 | 1.07409e+06 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1172.23 | 1.2595 | 119.039ms | 642697 | 30 | 1.30108e+09 | 522871 | 1(Win) |
| glaze | 935.74 | 0.787292 | 170.744ms | 642692 | 30 | 7.9779e+08 | 655010 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1363.57 | 1.00521 | 215.209ms | 1225964 | 30 | 2.22863e+09 | 857436 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1352.77 | 1.10112 | 561.273ms | 1225964 | 32 | 2.8982e+09 | 864277 | 1(Tie) |
| simdjson (ondemand) | 990.941 | 1.33237 | 306.889ms | 1225964 | 30 | 7.41362e+09 | 1.17986e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1863.28 | 0.726437 | 382.774ms | 1225964 | 32 | 6.64883e+08 | 627479 | 1(Win) |
| glaze | 1439.2 | 1.21171 | 502.392ms | 1225970 | 32 | 3.10076e+09 | 812381 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 835.191 | 0.903818 | 114.743ms | 409725 | 30 | 5.36409e+08 | 467850 | 1(Win) |
| simdjson (ondemand) | 702.533 | 0.298153 | 136.437ms | 409725 | 30 | 8.24993e+07 | 556193 | 2(Loss) |
| glaze | 648.389 | 0.978797 | 163.272ms | 409725 | 30 | 1.04381e+09 | 602639 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2141.78 | 1.45062 | 44.6774ms | 409725 | 30 | 2.10116e+08 | 182439 | 1(Win) |
| glaze | 1677.66 | 0.578644 | 139.409ms | 409725 | 32 | 5.81234e+07 | 232910 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1147.03 | 1.70317 | 160.375ms | 785750 | 30 | 3.71415e+09 | 653297 | 1(Tie) |
| glaze STATISTICAL TIE | 1145.38 | 0.2726 | 415.216ms | 785750 | 32 | 1.01781e+08 | 654234 | 1(Tie) |
| simdjson (ondemand) | 1102.25 | 1.88296 | 2070.12ms | 785750 | 128 | 2.0975e+10 | 679839 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3135.37 | 0.342807 | 57.5999ms | 785750 | 30 | 2.01378e+07 | 238999 | 1(Win) |
| glaze | 2205.27 | 0.315678 | 84.667ms | 785750 | 30 | 3.45189e+07 | 339800 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1026.48 | 0.49572 | 4881.56ms | 8587914 | 32 | 5.00605e+10 | 7.97878e+06 | 1(Win) |
| simdjson (ondemand) | 790.132 | 0.604229 | 2552.36ms | 8587914 | 30 | 1.17679e+11 | 1.03654e+07 | 2(Loss) |
| glaze | 740.281 | 1.7858 | 2618.44ms | 8587914 | 30 | 1.17103e+12 | 1.10635e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3368.62 | 1.29771 | 624.542ms | 8588126 | 30 | 2.98653e+10 | 2.43134e+06 | 1(Win) |
| glaze | 3179.81 | 1.37824 | 633.709ms | 8588126 | 30 | 3.78062e+10 | 2.57571e+06 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1004.32 | 0.348909 | 2273.81ms | 9804437 | 30 | 3.16553e+10 | 9.31001e+06 | 1(Win) |
| glaze | 970.229 | 0.0932862 | 2323.85ms | 9804437 | 30 | 2.42467e+09 | 9.63714e+06 | 2(Loss) |
| simdjson (ondemand) | 943.873 | 0.629899 | 2531.8ms | 9804437 | 30 | 1.1681e+11 | 9.90625e+06 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3387.73 | 0.721269 | 762.211ms | 11078090 | 30 | 1.51785e+10 | 3.11857e+06 | 1(Win) |
| glaze | 2749.93 | 0.67424 | 10087ms | 11078090 | 128 | 8.58866e+10 | 3.84187e+06 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 3260.88 | 1.38174 | 21.0976ms | 264040 | 30 | 3.41544e+07 | 77221 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3167.73 | 0.440065 | 19.4453ms | 264040 | 30 | 3.67112e+06 | 79491.7 | 1(Tie) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3840.38 | 1.67854 | 23.961ms | 399947 | 30 | 8.33766e+07 | 99318.2 | 1(Win) |
| simdjson (ondemand) | 3589.78 | 1.07931 | 23.5814ms | 399947 | 30 | 3.94534e+07 | 106251 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1730.33 | 0.505446 | 38.6463ms | 264040 | 30 | 1.62313e+07 | 145526 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1286.8 | 0.287404 | 47.4617ms | 264040 | 30 | 9.4891e+06 | 195686 | 2(Tie) |
| glaze STATISTICAL TIE | 1286.55 | 0.309236 | 47.714ms | 264040 | 30 | 1.09897e+07 | 195723 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3945.2 | 1.07033 | 15.8833ms | 264040 | 30 | 1.4001e+07 | 63826.4 | 1(Win) |
| glaze | 3237.6 | 0.405995 | 19.628ms | 263923 | 30 | 2.98862e+06 | 77741.7 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1758.28 | 0.494972 | 53.6864ms | 399947 | 30 | 3.45869e+07 | 216928 | 1(Win) |
| simdjson (ondemand) | 1625.09 | 0.911834 | 55.6189ms | 399947 | 30 | 1.37406e+08 | 234707 | 2(Loss) |
| glaze | 1577.83 | 0.93761 | 59.3347ms | 399947 | 30 | 1.54116e+08 | 241736 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4848.81 | 1.10214 | 19.6243ms | 399947 | 30 | 2.25491e+07 | 78662.4 | 1(Win) |
| glaze | 3117.49 | 1.09718 | 29.705ms | 399830 | 30 | 5.40278e+07 | 122312 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1815.04 | 0.193209 | 59.2357ms | 466906 | 30 | 6.74008e+06 | 245326 | 1(Win) |
| jsonifier | 1617.22 | 0.589642 | 70.6356ms | 466906 | 30 | 7.90715e+07 | 275335 | 2(Loss) |
| simdjson (ondemand) | 787.795 | 0.201415 | 137.157ms | 466906 | 30 | 3.88809e+07 | 565218 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2272 | 0.196006 | 71.9224ms | 699405 | 30 | 9.93354e+06 | 293576 | 1(Win) |
| glaze | 1892.67 | 0.810455 | 77.3051ms | 699405 | 30 | 2.44731e+08 | 352415 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2769.52 | 0.268099 | 57.7879ms | 631514 | 30 | 1.01969e+07 | 217460 | 1(Win) |
| glaze | 1825.53 | 0.33586 | 80.1735ms | 631514 | 30 | 3.68319e+07 | 329908 | 2(Loss) |
