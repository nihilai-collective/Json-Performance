# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.6.87.2-microsoft-standard-WSL2 using the Clang 23.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1274.24 | 0.28061 | 1.23177ms | 1811 | 30 | 433.972 | 1355.4 | 2.34233 | 1(Win) |
| glaze | 861.986 | 0.0871541 | 0.693929ms | 1811 | 30 | 91.4816 | 2003.63 | 3.49463 | 2(Loss) |
| simdjson (ondemand) | 264.505 | 0.0467688 | 1.81022ms | 1811 | 30 | 279.771 | 6529.57 | 11.4425 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 744.741 | 0.0690036 | 0.777759ms | 1811 | 30 | 76.823 | 2319.07 | 4.02522 | 1(Win) |
| glaze | 482.943 | 0.477445 | 1.11036ms | 1798 | 30 | 8620.95 | 3550.53 | 6.22809 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2093.08 | 0.0480178 | 0.654986ms | 3873 | 30 | 21.5402 | 1764.67 | 1.43129 | 1(Win) |
| glaze | 1466.83 | 0.127118 | 0.828802ms | 3873 | 30 | 307.375 | 2518.07 | 2.04792 | 2(Loss) |
| simdjson (ondemand) | 521.837 | 2.09734 | 4.31423ms | 3873 | 32 | 705198 | 7078.03 | 5.80768 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3061.23 | 0.141261 | 0.507221ms | 3873 | 30 | 87.1506 | 1206.57 | 0.962888 | 1(Win) |
| glaze | 1485.73 | 0.156117 | 0.882261ms | 3873 | 30 | 451.895 | 2486.03 | 2.02013 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2174.5 | 0.0454407 | 0.688262ms | 3862 | 30 | 17.7713 | 1693.77 | 1.376 | 1(Win) |
| glaze | 1575.16 | 0.166633 | 0.771786ms | 3862 | 30 | 455.426 | 2338.23 | 1.90466 | 2(Loss) |
| simdjson (ondemand) | 516.715 | 0.0480719 | 1.91713ms | 3862 | 30 | 352.231 | 7127.9 | 5.85707 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3058.96 | 0.215275 | 0.509788ms | 3862 | 30 | 201.551 | 1204.03 | 0.96299 | 1(Win) |
| glaze | 1477.85 | 0.157796 | 0.838563ms | 3862 | 30 | 463.959 | 2492.2 | 2.0344 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1602.14 | 0.0617599 | 0.345874ms | 905 | 30 | 3.32069 | 538.7 | 1.83238 | 1(Win) |
| glaze | 483.444 | 0.18933 | 2.49818ms | 905 | 64 | 731.182 | 1785.27 | 6.22296 | 2(Loss) |
| simdjson (ondemand) | 232.819 | 0.0733806 | 1.14598ms | 905 | 30 | 221.995 | 3707.07 | 12.9441 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1437.42 | 0.0272944 | 0.338069ms | 905 | 30 | 0.805747 | 600.433 | 2.05017 | 1(Win) |
| glaze | 323.541 | 0.540613 | 1.92011ms | 905 | 32 | 6655.22 | 2667.59 | 9.28453 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4175.5 | 0.0948591 | 1.5759ms | 9578 | 32 | 137.797 | 2187.59 | 0.717174 | 1(Win) |
| glaze | 2699.58 | 0.189958 | 1.02595ms | 9578 | 30 | 1239.35 | 3383.6 | 1.11896 | 2(Loss) |
| simdjson (ondemand) | 1642.35 | 0.128498 | 1.60605ms | 9578 | 30 | 1532.27 | 5561.73 | 1.84405 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5999.54 | 0.0279462 | 0.648738ms | 9578 | 30 | 5.43103 | 1522.5 | 0.498695 | 1(Win) |
| glaze | 3503.38 | 0.125885 | 1.82239ms | 9578 | 32 | 344.725 | 2607.28 | 0.859724 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6072.57 | 0.134983 | 1.55682ms | 33713 | 30 | 1532.26 | 5294.5 | 0.49798 | 1(Win) |
| simdjson (ondemand) | 5638.72 | 0.422774 | 1.59757ms | 33713 | 30 | 17433 | 5701.87 | 0.536631 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7361.73 | 0.277164 | 1.8973ms | 48024 | 30 | 8919.72 | 6221.27 | 0.411144 | 1(Win) |
| simdjson (ondemand) | 7050.74 | 0.327423 | 1.9797ms | 48024 | 30 | 13570.2 | 6495.67 | 0.429539 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2213.68 | 1.92633 | 30.4204ms | 294588 | 30 | 1.79301e+08 | 126911 | 1.37213 | 1(Win) |
| glaze | 2008.02 | 0.743383 | 80.4877ms | 294588 | 32 | 3.46153e+07 | 139909 | 1.51305 | 2(Loss) |
| simdjson (ondemand) | 1400.91 | 0.653065 | 48.742ms | 294588 | 30 | 5.14571e+07 | 200542 | 2.16865 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5847.48 | 0.632995 | 11.9857ms | 294588 | 30 | 2.7747e+06 | 48044.8 | 0.519231 | 1(Win) |
| glaze | 4621.39 | 0.743408 | 37.7182ms | 294588 | 32 | 6.53567e+06 | 60791.5 | 0.656921 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2447.82 | 0.760938 | 38.7819ms | 406546 | 30 | 4.35794e+07 | 158391 | 1.24129 | 1(Win) |
| glaze | 2268.58 | 1.30794 | 40.7023ms | 406546 | 30 | 1.49902e+08 | 170905 | 1.33891 | 2(Loss) |
| simdjson (ondemand) | 1888.4 | 0.646357 | 51.7114ms | 406546 | 30 | 5.2832e+07 | 205313 | 1.60908 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5214.35 | 0.705577 | 68.8964ms | 406546 | 30 | 8.25712e+06 | 74354.9 | 0.582362 | 1(Win) |
| glaze | 4824.76 | 0.639521 | 19.9899ms | 406546 | 30 | 7.92317e+06 | 80359 | 0.629594 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5889.04 | 1.62104 | 1.54519ms | 33713 | 30 | 234972 | 5459.5 | 0.513994 | 1(Win) |
| simdjson (ondemand) | 3800.84 | 0.114339 | 10.8516ms | 33713 | 64 | 5986.97 | 8458.98 | 0.797356 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7170.96 | 0.121939 | 1.79661ms | 48024 | 30 | 1819.56 | 6386.77 | 0.422033 | 1(Win) |
| simdjson (ondemand) | 5135.17 | 0.100018 | 2.44191ms | 48024 | 30 | 2387.17 | 8918.73 | 0.59037 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2105.43 | 1.33052 | 32.0588ms | 294588 | 30 | 9.45613e+07 | 133436 | 1.44287 | 1(Win) |
| jsonifier | 1804.07 | 2.08692 | 36.8353ms | 294588 | 30 | 3.16852e+08 | 155726 | 1.68356 | 2(Loss) |
| simdjson (ondemand) | 453.369 | 0.438703 | 149.615ms | 294588 | 30 | 2.21713e+08 | 619675 | 6.70229 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5359.21 | 0.602023 | 12.7486ms | 294588 | 30 | 2.98797e+06 | 52422.1 | 0.566395 | 1(Win) |
| glaze | 4839.6 | 0.579977 | 14.4432ms | 294588 | 30 | 3.40059e+06 | 58050.4 | 0.627637 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2515.59 | 0.459641 | 140.622ms | 406546 | 32 | 1.60594e+07 | 154124 | 1.20789 | 1(Win) |
| jsonifier | 2186.38 | 0.569686 | 42.7817ms | 406546 | 30 | 3.06169e+07 | 177331 | 1.38981 | 2(Loss) |
| simdjson (ondemand) | 625.409 | 0.361158 | 152.706ms | 406546 | 30 | 1.50386e+08 | 619935 | 4.85905 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 4840.6 | 1.82804 | 19.2673ms | 406546 | 30 | 6.43152e+07 | 80096 | 0.627325 | 1(Tie) |
| glaze STATISTICAL TIE | 4767.95 | 0.848305 | 19.8268ms | 406546 | 30 | 1.42752e+07 | 81316.4 | 0.637096 | 1(Tie) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1352.1 | 1.07529 | 16.5359ms | 94651 | 30 | 1.54599e+07 | 66760 | 2.2469 | 1(Win) |
| jsonifier | 1262.21 | 0.947008 | 17.5213ms | 94651 | 30 | 1.37599e+07 | 71514.4 | 2.40658 | 2(Loss) |
| simdjson (ondemand) | 983.056 | 0.64339 | 52.4132ms | 94651 | 32 | 1.11685e+07 | 91822.1 | 3.09053 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5737.38 | 0.0904399 | 4.24632ms | 94651 | 30 | 6073.86 | 15733 | 0.527205 | 1(Win) |
| glaze | 5565.52 | 0.115623 | 4.4643ms | 94651 | 30 | 10549.9 | 16218.8 | 0.545079 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1618.15 | 1.29662 | 20.3028ms | 136024 | 30 | 3.24145e+07 | 80167.3 | 1.87741 | 1(Win) |
| jsonifier | 1477.69 | 1.18475 | 21.9605ms | 136024 | 30 | 3.24522e+07 | 87787.7 | 2.0559 | 2(Loss) |
| simdjson (ondemand) | 1323.37 | 2.18626 | 23.3044ms | 136024 | 30 | 1.37783e+08 | 98024.5 | 2.29496 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4872.33 | 0.375403 | 7.17931ms | 136046 | 30 | 299789 | 26628.7 | 0.623054 | 1(Win) |
| jsonifier | 4528.34 | 1.08021 | 7.1921ms | 136024 | 30 | 2.87273e+06 | 28646.8 | 0.670153 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 883.14 | 0.4591 | 595.156ms | 2090234 | 30 | 3.22156e+09 | 2.25718e+06 | 3.44078 | 1(Win) |
| glaze | 791.305 | 0.357327 | 658.052ms | 2090234 | 30 | 2.43084e+09 | 2.51913e+06 | 3.83995 | 2(Loss) |
| simdjson (ondemand) | 461.786 | 0.286079 | 1077.69ms | 2090234 | 30 | 4.5751e+09 | 4.31672e+06 | 6.57957 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1598.09 | 0.665249 | 353.596ms | 2090234 | 30 | 2.06575e+09 | 1.24737e+06 | 1.90098 | 1(Win) |
| glaze | 941.976 | 0.605605 | 556.877ms | 2090234 | 30 | 4.92732e+09 | 2.11619e+06 | 3.22543 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2053.33 | 0.517363 | 799.526ms | 6661897 | 30 | 7.68763e+09 | 3.09414e+06 | 1.47974 | 1(Win) |
| glaze | 1978 | 0.423054 | 817.497ms | 6661897 | 30 | 5.53932e+09 | 3.21197e+06 | 1.536 | 2(Loss) |
| simdjson (ondemand) | 1397.82 | 0.435255 | 1143.28ms | 6661897 | 30 | 1.1741e+10 | 4.54515e+06 | 2.17376 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3190.89 | 0.960666 | 461.359ms | 6661897 | 30 | 1.09758e+10 | 1.99107e+06 | 0.951999 | 1(Win) |
| glaze | 2251.66 | 0.740561 | 723.505ms | 6661897 | 30 | 1.30989e+10 | 2.8216e+06 | 1.34923 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1893.29 | 0.558426 | 61.1631ms | 500299 | 30 | 5.94123e+07 | 252007 | 1.60494 | 1(Win) |
| glaze | 1807.59 | 0.621222 | 64.4269ms | 500299 | 30 | 8.06631e+07 | 263955 | 1.681 | 2(Loss) |
| simdjson (ondemand) | 1010 | 0.788219 | 115.941ms | 500299 | 30 | 4.1594e+08 | 472397 | 3.00847 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 5397.99 | 0.766772 | 21.7933ms | 500299 | 30 | 1.378e+07 | 88388.8 | 0.562682 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5319.66 | 1.23616 | 73.7663ms | 500299 | 30 | 3.68778e+07 | 89690.4 | 0.570848 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3331.46 | 2.23001 | 96.1769ms | 1439562 | 30 | 2.53353e+09 | 412093 | 0.911837 | 1(Win) |
| glaze | 2984.23 | 0.339508 | 111.705ms | 1439562 | 30 | 7.31844e+07 | 460043 | 1.01823 | 2(Loss) |
| simdjson (ondemand) | 2588.1 | 0.39079 | 128.162ms | 1439562 | 30 | 1.28916e+08 | 530457 | 1.17406 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6165.05 | 1.17249 | 53.2484ms | 1439562 | 30 | 2.04516e+08 | 222687 | 0.492542 | 1(Win) |
| glaze | 5452.31 | 0.707429 | 61.3742ms | 1439584 | 30 | 9.5192e+07 | 251800 | 0.557068 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1872.77 | 0.042273 | 7.4538ms | 56369 | 30 | 4417.34 | 28705 | 1.62114 | 1(Tie) |
| glaze STATISTICAL TIE | 1869.4 | 0.165127 | 7.33313ms | 56369 | 30 | 67645.1 | 28756.7 | 1.62434 | 1(Tie) |
| simdjson (ondemand) | 1169.36 | 0.539582 | 11.5187ms | 56369 | 30 | 1.84596e+06 | 45971.9 | 2.5975 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6651.71 | 0.472814 | 5.10138ms | 56369 | 32 | 46724.4 | 8081.78 | 0.455259 | 1(Win) |
| jsonifier | 5782.65 | 0.132935 | 2.58728ms | 56369 | 30 | 4581.69 | 9296.37 | 0.521522 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2479.99 | 0.264269 | 9.2392ms | 94370 | 30 | 275921 | 36289.8 | 1.2246 | 1(Win) |
| jsonifier | 2320.2 | 0.890457 | 9.6657ms | 94370 | 30 | 3.57904e+06 | 38789.1 | 1.30894 | 2(Loss) |
| simdjson (ondemand) | 1817.91 | 2.19042 | 12.2511ms | 94370 | 30 | 3.52776e+07 | 49506.5 | 1.67079 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6010.1 | 0.382278 | 9.18275ms | 94370 | 32 | 104861 | 14974.5 | 0.503481 | 1(Win) |
| glaze | 5257.53 | 0.143278 | 4.46865ms | 94370 | 30 | 18046.2 | 17118 | 0.577078 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1497.34 | 0.583393 | 8.6937ms | 52708 | 30 | 1.15068e+06 | 33570.3 | 2.02786 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1478.15 | 2.24734 | 8.60323ms | 52708 | 30 | 1.75216e+07 | 34006.1 | 2.0541 | 1(Tie) |
| simdjson (ondemand) | 1308.09 | 0.248169 | 10.1033ms | 52708 | 30 | 272831 | 38427.2 | 2.32174 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6988.8 | 0.288648 | 2.33477ms | 52708 | 30 | 12930.2 | 7192.4 | 0.432948 | 1(Win) |
| jsonifier | 5839.05 | 1.38976 | 2.56593ms | 52708 | 30 | 429409 | 8608.63 | 0.516409 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1772.44 | 0.600901 | 22.7867ms | 70103 | 32 | 1.64394e+06 | 37719.5 | 1.71319 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1682.75 | 1.91029 | 10.1612ms | 70103 | 30 | 1.72803e+07 | 39729.8 | 1.80441 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1635.99 | 1.41619 | 10.6137ms | 70103 | 30 | 1.0048e+07 | 40865.4 | 1.85623 | 2(Tie) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6794.8 | 0.113441 | 2.75381ms | 70103 | 30 | 3737.48 | 9839.2 | 0.445862 | 1(Win) |
| jsonifier | 5979.58 | 0.354946 | 6.67405ms | 70103 | 32 | 50397.2 | 11180.6 | 0.504517 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1457.97 | 2.3169 | 2.40786ms | 11812 | 30 | 961359 | 7726.37 | 2.07784 | 1(Win) |
| glaze | 1361.37 | 0.0656749 | 5.03937ms | 11812 | 32 | 945.023 | 8274.59 | 2.22499 | 2(Loss) |
| simdjson (ondemand) | 935.54 | 0.129979 | 3.23409ms | 11812 | 30 | 7348.31 | 12041 | 3.24112 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5538.89 | 0.273793 | 0.733433ms | 11812 | 30 | 930.185 | 2033.77 | 0.539093 | 1(Win) |
| glaze | 4816.97 | 0.108947 | 0.842825ms | 11812 | 30 | 194.737 | 2338.57 | 0.623651 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2569.84 | 2.36423 | 6.65618ms | 31235 | 32 | 2.40325e+06 | 11591.4 | 1.17967 | 1(Win) |
| simdjson (ondemand) | 2262.48 | 1.94667 | 3.45826ms | 31235 | 30 | 1.9707e+06 | 13166.1 | 1.34024 | 2(Loss) |
| glaze | 2175.43 | 0.100269 | 8.00288ms | 31235 | 32 | 6032.25 | 13692.9 | 1.39449 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6296.92 | 0.071709 | 1.36588ms | 31235 | 30 | 345.22 | 4730.57 | 0.47643 | 1(Win) |
| glaze | 5853.07 | 0.150274 | 1.47438ms | 31235 | 30 | 1754.7 | 5089.3 | 0.515996 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3565.09 | 1.11024 | 7.24898ms | 108313 | 30 | 3.10437e+06 | 28974.1 | 0.851251 | 1(Win) |
| glaze | 2243.67 | 1.51236 | 11.2313ms | 108313 | 30 | 1.45438e+07 | 46038.6 | 1.35354 | 2(Loss) |
| simdjson (ondemand) | 1523.89 | 0.60913 | 16.5044ms | 108313 | 30 | 5.11439e+06 | 67783.9 | 1.99315 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6699.48 | 1.71003 | 4.0752ms | 108313 | 30 | 2.08548e+06 | 15418.4 | 0.45255 | 1(Win) |
| jsonifier | 6352.97 | 0.741346 | 4.20073ms | 108313 | 30 | 435884 | 16259.4 | 0.47635 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3175.38 | 0.407631 | 15.9333ms | 213963 | 30 | 2.05846e+06 | 64260.3 | 0.956686 | 1(Win) |
| glaze | 3031.58 | 0.943084 | 16.5133ms | 213963 | 30 | 1.20882e+07 | 67308.5 | 1.00193 | 2(Loss) |
| simdjson (ondemand) | 2798.1 | 0.402233 | 17.9636ms | 213963 | 30 | 2.58125e+06 | 72925 | 1.08564 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6705.1 | 0.0416271 | 7.67825ms | 213963 | 30 | 4814.37 | 30432.2 | 0.45226 | 1(Win) |
| glaze | 5740.87 | 1.36607 | 8.92687ms | 213963 | 30 | 7.07277e+06 | 35543.6 | 0.528948 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 907.541 | 0.470448 | 510.018ms | 1834197 | 30 | 2.46663e+09 | 1.92744e+06 | 3.34797 | 1(Win) |
| glaze | 704.314 | 0.183161 | 1450.68ms | 1834197 | 32 | 6.62178e+08 | 2.48359e+06 | 4.31403 | 2(Loss) |
| simdjson (ondemand) | 399.656 | 0.416766 | 1106.42ms | 1834197 | 30 | 9.98215e+09 | 4.37683e+06 | 7.60298 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1048.41 | 0.143233 | 982.698ms | 1834197 | 32 | 1.82754e+08 | 1.66845e+06 | 2.89819 | 1(Win) |
| glaze | 604.993 | 0.319519 | 753.788ms | 1833577 | 30 | 2.55865e+09 | 2.89034e+06 | 5.02267 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2976.78 | 0.179597 | 820.339ms | 9930848 | 30 | 9.79481e+08 | 3.18155e+06 | 1.02074 | 1(Win) |
| glaze | 2651.22 | 0.2355 | 855.591ms | 9930848 | 30 | 2.12318e+09 | 3.57225e+06 | 1.14604 | 2(Loss) |
| simdjson (ondemand) | 1921.4 | 0.222327 | 1248.36ms | 9930848 | 30 | 3.60284e+09 | 4.92911e+06 | 1.58142 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3087.12 | 0.59193 | 779.297ms | 9930848 | 30 | 9.89295e+09 | 3.06784e+06 | 0.984131 | 1(Win) |
| glaze | 1799.24 | 1.44686 | 1334.52ms | 9930228 | 30 | 1.73986e+11 | 5.26343e+06 | 1.68872 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1536.93 | 0.245765 | 96.4324ms | 642697 | 30 | 2.88183e+07 | 398798 | 1.97711 | 1(Win) |
| glaze | 1428.31 | 0.322563 | 294.475ms | 642697 | 32 | 6.13125e+07 | 429127 | 2.12737 | 2(Loss) |
| simdjson (ondemand) | 629.35 | 0.514688 | 234.909ms | 642697 | 30 | 7.53769e+08 | 973900 | 4.82817 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1855.92 | 0.266228 | 130.179ms | 642697 | 30 | 2.31912e+07 | 330254 | 1.63691 | 1(Win) |
| glaze | 969.498 | 0.356991 | 159.966ms | 642692 | 30 | 1.52808e+08 | 632202 | 3.13388 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2293.98 | 0.645888 | 124.869ms | 1225964 | 30 | 3.25098e+08 | 509670 | 1.32458 | 1(Win) |
| glaze | 2218.71 | 0.464318 | 126.622ms | 1225964 | 30 | 1.796e+08 | 526958 | 1.36959 | 2(Loss) |
| simdjson (ondemand) | 1169.6 | 0.357101 | 240.746ms | 1225964 | 30 | 3.82282e+08 | 999632 | 2.59805 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2619.99 | 0.575478 | 108.744ms | 1225964 | 30 | 1.9785e+08 | 446250 | 1.15978 | 1(Win) |
| glaze | 1624.16 | 1.75091 | 454.314ms | 1225970 | 32 | 5.08369e+09 | 719865 | 1.8706 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1196.04 | 0.320132 | 80.7555ms | 409725 | 30 | 3.28153e+07 | 326699 | 2.54061 | 1(Win) |
| glaze | 949.37 | 0.695123 | 98.5509ms | 409725 | 30 | 2.45561e+08 | 411583 | 3.20078 | 2(Loss) |
| simdjson (ondemand) | 818.085 | 0.5221 | 115.292ms | 409725 | 30 | 1.86559e+08 | 477633 | 3.71441 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 3254.33 | 1.86248 | 28.6075ms | 409725 | 30 | 1.50025e+08 | 120069 | 0.93297 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3249.08 | 0.766412 | 29.3567ms | 409725 | 30 | 2.54865e+07 | 120263 | 0.934792 | 1(Tie) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1549.4 | 2.4324 | 270.591ms | 785750 | 32 | 4.42854e+09 | 483638 | 1.9611 | 1(Tie) |
| glaze STATISTICAL TIE | 1495.96 | 0.592129 | 120.658ms | 785750 | 30 | 2.63928e+08 | 500917 | 2.03122 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1490.2 | 0.744656 | 121.51ms | 785750 | 30 | 4.20644e+08 | 502852 | 2.03915 | 1(Tie) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4171.98 | 0.904432 | 44.193ms | 785750 | 30 | 7.91693e+07 | 179615 | 0.728114 | 1(Win) |
| glaze | 3800.2 | 1.66941 | 46.8758ms | 785750 | 30 | 3.2509e+08 | 197187 | 0.799354 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1420.74 | 0.451649 | 1445.67ms | 8587914 | 30 | 2.03361e+10 | 5.76465e+06 | 2.13888 | 1(Win) |
| glaze | 1262.14 | 0.431381 | 1605.77ms | 8587914 | 30 | 2.35072e+10 | 6.48901e+06 | 2.40762 | 2(Loss) |
| simdjson (ondemand) | 1024.67 | 0.552545 | 2015.73ms | 8587914 | 30 | 5.85142e+10 | 7.99286e+06 | 2.96561 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3441.59 | 1.54258 | 566.544ms | 8588126 | 30 | 4.04293e+10 | 2.37979e+06 | 0.882699 | 1(Win) |
| glaze | 3068.94 | 0.963788 | 620.499ms | 8588126 | 30 | 1.98474e+10 | 2.66876e+06 | 0.989903 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1372.61 | 0.428983 | 1684.69ms | 9804437 | 30 | 2.56186e+10 | 6.81203e+06 | 2.2138 | 1(Win) |
| glaze | 1292.51 | 0.348547 | 1785.85ms | 9804437 | 30 | 1.90732e+10 | 7.23419e+06 | 2.3511 | 2(Loss) |
| simdjson (ondemand) | 1143.73 | 0.423833 | 2042.74ms | 9804437 | 30 | 3.60169e+10 | 8.17519e+06 | 2.65691 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3426.42 | 0.958334 | 810.511ms | 11078090 | 30 | 2.61941e+10 | 3.08336e+06 | 0.886672 | 1(Win) |
| glaze | 3308.98 | 1.21579 | 811.856ms | 11078090 | 30 | 4.52045e+10 | 3.1928e+06 | 0.918219 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5846.23 | 0.538495 | 11.0499ms | 264040 | 30 | 1.61388e+06 | 43071.9 | 0.519516 | 1(Win) |
| simdjson (ondemand) | 5725.22 | 0.420379 | 11.1066ms | 264040 | 30 | 1.02556e+06 | 43982.3 | 0.530536 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7792.07 | 0.583764 | 12.5867ms | 399947 | 30 | 2.4496e+06 | 48949.7 | 0.389823 | 1(Win) |
| simdjson (ondemand) | 7461.08 | 0.844485 | 30.1061ms | 399947 | 32 | 5.96398e+06 | 51121.2 | 0.407145 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1919.02 | 0.544635 | 32.1983ms | 264040 | 30 | 1.5322e+07 | 131217 | 1.58339 | 1(Win) |
| glaze | 1696.43 | 0.80235 | 36.5619ms | 264040 | 30 | 4.25518e+07 | 148434 | 1.79102 | 2(Loss) |
| simdjson (ondemand) | 1406.69 | 1.29835 | 44.0968ms | 264040 | 30 | 1.62051e+08 | 179008 | 2.15998 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6762.7 | 0.745201 | 9.45978ms | 264040 | 30 | 2.30976e+06 | 37234.9 | 0.448669 | 1(Win) |
| glaze | 5992.27 | 0.925315 | 11.2286ms | 263923 | 30 | 4.53182e+06 | 42003.6 | 0.506734 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2104.48 | 0.85647 | 94.8013ms | 399947 | 30 | 7.22869e+07 | 181241 | 1.44376 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2065.81 | 0.62366 | 45.2648ms | 399947 | 30 | 3.9778e+07 | 184634 | 1.47097 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2010.86 | 1.2883 | 45.8341ms | 399947 | 30 | 1.7914e+08 | 189679 | 1.51085 | 1(Tie) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6716.25 | 0.664635 | 14.2981ms | 399947 | 30 | 4.27404e+06 | 56790.5 | 0.452035 | 1(Win) |
| glaze | 6009.92 | 2.03568 | 16.2263ms | 399830 | 30 | 5.00441e+07 | 63446.3 | 0.505431 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 3098.45 | 0.992276 | 34.6824ms | 466906 | 30 | 6.10039e+07 | 143710 | 0.980697 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3067.79 | 1.36378 | 84.1052ms | 466906 | 32 | 1.25385e+08 | 145146 | 0.990231 | 1(Tie) |
| simdjson (ondemand) | 1336.39 | 0.496212 | 238.602ms | 466906 | 32 | 8.74733e+07 | 333193 | 2.27337 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3794.39 | 0.669203 | 42.6858ms | 699405 | 30 | 4.15155e+07 | 175787 | 0.800583 | 1(Win) |
| glaze | 3405.33 | 2.24797 | 46.246ms | 699405 | 30 | 5.81623e+08 | 195871 | 0.892019 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4776.84 | 0.4648 | 30.503ms | 631514 | 30 | 1.03024e+07 | 126079 | 0.636048 | 1(Win) |
| glaze | 2868.22 | 0.422924 | 51.4491ms | 631514 | 30 | 2.36585e+07 | 209977 | 1.0595 | 2(Loss) |
