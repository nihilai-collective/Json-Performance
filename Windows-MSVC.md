# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Aug 06, 2026)
#### Using the following commits:
----
| Jsonifier: [50382ef](https://github.com/nihilai-collective/jsonifier/commit/50382ef)  
| Glaze: [2f6f5dc](https://github.com/stephenberry/glaze/commit/2f6f5dc)  
| Simdjson: [b3072d2](https://github.com/simdjson/simdjson/commit/b3072d2)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `SSSE3` |
| Glaze (string-escape) | `SSE2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)

#### Note:
  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1021.96 | 0.329637 | 1.5935ms | 1811 | 30 | 931.034 | 1690 | 2.91353 | 1(Win) |
| glaze | 347.04 | 0.157817 | 2.3317ms | 1811 | 30 | 1850.57 | 4976.67 | 8.69711 | 2(Loss) |
| simdjson (ondemand) | 186.273 | 0.0996521 | 7.0877ms | 1811 | 32 | 2731.85 | 9271.88 | 16.2601 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 572.718 | 0.301835 | 3.4023ms | 1811 | 32 | 2651.21 | 3015.62 | 5.25343 | 1(Win) |
| glaze | 375.312 | 0.136799 | 7.8233ms | 1798 | 64 | 2500 | 4568.75 | 8.0596 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2090.71 | 0.495496 | 1.5696ms | 3873 | 30 | 2298.85 | 1766.67 | 1.42875 | 1(Win) |
| glaze | 1204.84 | 0.137479 | 10.5134ms | 3873 | 128 | 2273.62 | 3065.62 | 2.5053 | 2(Loss) |
| simdjson (ondemand) | 370.748 | 2.04897 | 7.3861ms | 3873 | 32 | 1.33339e+06 | 9962.5 | 8.17861 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3052.55 | 0.460402 | 1.5053ms | 3873 | 30 | 931.034 | 1210 | 0.973104 | 1(Win) |
| glaze | 1383.36 | 0.318713 | 1.8235ms | 3873 | 30 | 2172.41 | 2670 | 2.17853 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2170.78 | 0.196464 | 1.4649ms | 3862 | 30 | 333.333 | 1696.67 | 1.37543 | 1(Win) |
| glaze | 1208.19 | 1.66976 | 18.485ms | 3862 | 256 | 663292 | 3048.44 | 2.48564 | 2(Loss) |
| simdjson (ondemand) | 385.664 | 0.0972227 | 3.4652ms | 3862 | 30 | 2586.21 | 9550 | 7.86094 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2740.9 | 0.663057 | 2.3801ms | 3862 | 32 | 2540.32 | 1343.75 | 1.08084 | 1(Win) |
| glaze | 1365.79 | 0.216545 | 1.7904ms | 3862 | 30 | 1022.99 | 2696.67 | 2.20407 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1275.48 | 1.16069 | 1.3101ms | 905 | 30 | 1850.57 | 676.667 | 2.29926 | 1(Win) |
| glaze | 379.652 | 0.361221 | 1.6324ms | 905 | 30 | 2022.99 | 2273.33 | 7.89989 | 2(Loss) |
| simdjson (ondemand) | 145.821 | 1.69033 | 9.4595ms | 905 | 64 | 640595 | 5918.75 | 20.7613 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1446.49 | 0.558659 | 1.1709ms | 905 | 30 | 333.333 | 596.667 | 2.03462 | 1(Win) |
| glaze | 370.949 | 0.457711 | 1.6378ms | 905 | 30 | 3402.3 | 2326.67 | 8.06748 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3048.15 | 0.298617 | 1.7951ms | 9578 | 30 | 2402.3 | 2996.67 | 0.995643 | 1(Win) |
| glaze | 1875.62 | 0.174736 | 2.4001ms | 9578 | 30 | 2172.41 | 4870 | 1.61386 | 2(Loss) |
| simdjson (ondemand) | 832.914 | 0.371835 | 3.7381ms | 9578 | 30 | 49885.1 | 10966.7 | 3.64086 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3848.72 | 2.36402 | 1.6362ms | 9578 | 30 | 94436.8 | 2373.33 | 0.775078 | 1(Win) |
| glaze | 2940.22 | 0.149101 | 1.8798ms | 9578 | 30 | 643.678 | 3106.67 | 1.02471 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3977.47 | 0.278739 | 3.2131ms | 33713 | 30 | 15229.9 | 8083.33 | 0.761407 | 1(Win) |
| simdjson (ondemand) | 1356.06 | 1.70016 | 15.307ms | 33713 | 32 | 5.19959e+06 | 23709.4 | 2.23858 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4849.69 | 1.49671 | 7.1731ms | 48024 | 32 | 639315 | 9443.75 | 0.624761 | 1(Win) |
| simdjson (ondemand) | 1967.04 | 0.0744851 | 7.032ms | 48024 | 30 | 9022.99 | 23283.3 | 1.54432 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1273.22 | 0.9741 | 54.6779ms | 294588 | 30 | 1.38596e+08 | 220653 | 2.38577 | 1(Tie) |
| glaze STATISTICAL TIE | 1270.9 | 1.82077 | 138.368ms | 294588 | 32 | 5.18399e+08 | 221056 | 2.39118 | 1(Tie) |
| simdjson (ondemand) | 718.011 | 0.915175 | 96.4936ms | 294588 | 30 | 3.84678e+08 | 391277 | 4.23241 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4724.87 | 2.0347 | 15.6212ms | 294588 | 30 | 4.39108e+07 | 59460 | 0.642991 | 1(Win) |
| glaze | 3237.53 | 1.85712 | 877.565ms | 294588 | 512 | 1.32969e+09 | 86776.4 | 0.938139 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1655.15 | 1.32081 | 57.9152ms | 406546 | 30 | 2.87178e+08 | 234247 | 1.83587 | 1(Win) |
| jsonifier | 1596.86 | 1.17836 | 59.2569ms | 406546 | 30 | 2.45562e+08 | 242797 | 1.9028 | 2(Loss) |
| simdjson (ondemand) | 982.761 | 0.709887 | 95.7589ms | 406546 | 30 | 2.35301e+08 | 394513 | 3.09218 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4622.6 | 1.01622 | 22.1588ms | 406546 | 30 | 2.17944e+07 | 83873.3 | 0.657359 | 1(Win) |
| glaze | 3517.4 | 1.78509 | 562.972ms | 406546 | 256 | 9.91145e+08 | 110227 | 0.863692 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3890.83 | 0.557997 | 3.3452ms | 33713 | 30 | 63781.6 | 8263.33 | 0.779451 | 1(Win) |
| simdjson (ondemand) | 724.79 | 1.42042 | 27.1181ms | 33713 | 32 | 1.27044e+07 | 44359.4 | 4.19122 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4827.75 | 0.097654 | 3.5078ms | 48024 | 30 | 2574.71 | 9486.67 | 0.626864 | 1(Win) |
| simdjson (ondemand) | 1007.83 | 1.59714 | 12.257ms | 48024 | 30 | 1.58032e+07 | 45443.3 | 3.01346 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1370.98 | 1.20792 | 51.2773ms | 294588 | 30 | 1.83809e+08 | 204920 | 2.21669 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1362.45 | 0.74817 | 52.1881ms | 294588 | 30 | 7.14024e+07 | 206203 | 2.2305 | 1(Tie) |
| simdjson (ondemand) | 66.631 | 0.206626 | 997.038ms | 294588 | 30 | 2.27704e+09 | 4.21637e+06 | 45.6144 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4701.42 | 2.47722 | 15.8234ms | 294588 | 30 | 6.57391e+07 | 59756.7 | 0.646032 | 1(Win) |
| glaze | 3305.08 | 2.32115 | 431.657ms | 294588 | 256 | 9.96583e+08 | 85002.7 | 0.918936 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1701.12 | 0.826805 | 56.5894ms | 406546 | 30 | 1.06532e+08 | 227917 | 1.78647 | 1(Win) |
| jsonifier | 1606.77 | 1.42121 | 59.3139ms | 406546 | 30 | 3.52821e+08 | 241300 | 1.8911 | 2(Loss) |
| simdjson (ondemand) | 93.6592 | 0.125653 | 994.368ms | 406546 | 30 | 8.11684e+08 | 4.13961e+06 | 32.452 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4525.12 | 0.760547 | 22.4428ms | 406546 | 30 | 1.27389e+07 | 85680 | 0.671469 | 1(Win) |
| glaze | 3371.21 | 2.48054 | 285.805ms | 406546 | 128 | 1.04172e+09 | 115007 | 0.901163 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 830.289 | 1.30845 | 27.6059ms | 94651 | 30 | 6.07056e+07 | 108717 | 3.65944 | 1(Win) |
| glaze | 675.298 | 2.30224 | 161.819ms | 94651 | 64 | 6.06096e+08 | 133669 | 4.49935 | 2(Loss) |
| simdjson (ondemand) | 557.52 | 1.98322 | 40.4287ms | 94651 | 30 | 3.0931e+08 | 161907 | 5.45029 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4720.57 | 1.09895 | 27.1526ms | 94651 | 64 | 2.82618e+06 | 19121.9 | 0.642921 | 1(Win) |
| jsonifier | 3806.03 | 0.16558 | 7.2117ms | 94651 | 30 | 46264.4 | 23716.7 | 0.797424 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1006.67 | 1.21365 | 32.0299ms | 136024 | 30 | 7.33776e+07 | 128863 | 3.01853 | 1(Win) |
| glaze | 950.999 | 1.94837 | 36.4462ms | 136024 | 30 | 2.11902e+08 | 136407 | 3.19476 | 2(Loss) |
| simdjson (ondemand) | 803.186 | 1.61533 | 40.5717ms | 136024 | 30 | 2.04194e+08 | 161510 | 3.78352 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4315.2 | 1.7423 | 8.8702ms | 136046 | 30 | 8.23264e+06 | 30066.7 | 0.703815 | 1(Win) |
| jsonifier | 3748.49 | 1.55413 | 9.7222ms | 136024 | 30 | 8.67789e+06 | 34606.7 | 0.810478 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 577.604 | 1.25445 | 847.761ms | 2090234 | 30 | 5.62282e+10 | 3.45116e+06 | 5.26116 | 1(Win) |
| glaze | 355.636 | 0.607394 | 1343.69ms | 2090234 | 30 | 3.47729e+10 | 5.60518e+06 | 8.54492 | 2(Loss) |
| simdjson (ondemand) | 256.046 | 0.518241 | 1867.77ms | 2090234 | 30 | 4.88359e+10 | 7.78533e+06 | 11.8694 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 975.946 | 0.561926 | 490.233ms | 2090234 | 30 | 3.952e+09 | 2.04253e+06 | 3.11357 | 1(Win) |
| glaze | 694.375 | 0.434745 | 695.22ms | 2090234 | 30 | 4.67296e+09 | 2.87079e+06 | 4.37624 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1536.76 | 1.02166 | 1025.46ms | 6661897 | 30 | 5.35201e+10 | 4.1342e+06 | 1.97759 | 1(Win) |
| glaze | 1003.59 | 0.599887 | 1509.36ms | 6661897 | 30 | 4.32656e+10 | 6.33055e+06 | 3.0282 | 2(Loss) |
| simdjson (ondemand) | 797.18 | 0.510737 | 1912.37ms | 6661897 | 30 | 4.9705e+10 | 7.9697e+06 | 3.81233 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1787.67 | 0.904423 | 866.104ms | 6661897 | 30 | 3.09946e+10 | 3.55395e+06 | 1.69987 | 1(Win) |
| glaze | 1146.41 | 0.414959 | 1332.5ms | 6661897 | 30 | 1.58653e+10 | 5.54189e+06 | 2.6509 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1340.48 | 0.986217 | 87.3016ms | 500299 | 30 | 3.69661e+08 | 355933 | 2.26697 | 1(Win) |
| glaze | 836.191 | 1.11375 | 136.905ms | 500299 | 30 | 1.21157e+09 | 570590 | 3.63424 | 2(Loss) |
| simdjson (ondemand) | 423.311 | 0.329553 | 273.358ms | 500299 | 30 | 4.13916e+08 | 1.12712e+06 | 7.17934 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4798.57 | 1.24005 | 25.3562ms | 500299 | 30 | 4.5607e+07 | 99430 | 0.633016 | 1(Win) |
| glaze | 4253.06 | 1.46794 | 28.615ms | 500299 | 30 | 8.13566e+07 | 112183 | 0.714417 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2222.48 | 0.647463 | 152.53ms | 1439562 | 30 | 4.79882e+08 | 617720 | 1.36732 | 1(Win) |
| glaze | 1827.71 | 0.415843 | 182.308ms | 1439562 | 30 | 2.92703e+08 | 751143 | 1.66263 | 2(Loss) |
| simdjson (ondemand) | 1144.58 | 0.548017 | 289.355ms | 1439562 | 30 | 1.29622e+09 | 1.19946e+06 | 2.65508 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2628.36 | 1.05679 | 123.419ms | 1439562 | 30 | 9.14097e+08 | 522330 | 1.15561 | 1(Win) |
| glaze | 1213.15 | 1.7373 | 246.281ms | 1439584 | 30 | 1.15963e+10 | 1.13168e+06 | 2.50457 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1360.95 | 1.30282 | 11.0997ms | 56369 | 30 | 7.94483e+06 | 39500 | 2.23215 | 1(Win) |
| glaze | 1171.96 | 1.40526 | 12.5807ms | 56369 | 30 | 1.24649e+07 | 45870 | 2.5922 | 2(Loss) |
| simdjson (ondemand) | 518.746 | 0.945194 | 26.2616ms | 56369 | 30 | 2.87829e+07 | 103630 | 5.85796 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4741.93 | 0.196029 | 4.102ms | 56369 | 30 | 14816.1 | 11336.7 | 0.640044 | 1(Win) |
| glaze | 4389.58 | 2.15212 | 4.2855ms | 56369 | 30 | 2.08395e+06 | 12246.7 | 0.690689 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1719.93 | 1.25505 | 14.1452ms | 94370 | 30 | 1.29386e+07 | 52326.7 | 1.76615 | 1(Win) |
| jsonifier | 1477.88 | 1.25364 | 16.015ms | 94370 | 30 | 1.74845e+07 | 60896.7 | 2.05552 | 2(Loss) |
| simdjson (ondemand) | 834.064 | 1.39432 | 26.9702ms | 94370 | 30 | 6.79072e+07 | 107903 | 3.64296 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5336.92 | 1.93099 | 5.2107ms | 94370 | 30 | 3.18102e+06 | 16863.3 | 0.568335 | 1(Win) |
| glaze | 4122.06 | 0.871055 | 6.4597ms | 94370 | 30 | 1.08506e+06 | 21833.3 | 0.735984 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1146.24 | 1.82373 | 12.0259ms | 52708 | 30 | 1.91888e+07 | 43853.3 | 2.64941 | 1(Win) |
| glaze | 946.099 | 2.10188 | 14.2228ms | 52708 | 30 | 3.74125e+07 | 53130 | 3.2114 | 2(Loss) |
| simdjson (ondemand) | 775.834 | 1.14962 | 16.9376ms | 52708 | 30 | 1.66437e+07 | 64790 | 3.91587 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5222.47 | 1.74085 | 13.8689ms | 52708 | 64 | 1.79683e+06 | 9625 | 0.580179 | 1(Win) |
| glaze | 4501.88 | 0.550812 | 8.2234ms | 52708 | 32 | 121038 | 11165.6 | 0.673191 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1152.22 | 1.24671 | 15.3416ms | 70103 | 30 | 1.56984e+07 | 58023.3 | 2.63658 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1123.43 | 2.48379 | 15.8793ms | 70103 | 30 | 6.55437e+07 | 59510 | 2.7038 | 1(Tie) |
| simdjson (ondemand) | 1008.88 | 1.22631 | 17.3303ms | 70103 | 30 | 1.98113e+07 | 66266.7 | 3.01119 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5285.01 | 0.587549 | 9.0426ms | 70103 | 32 | 176774 | 12650 | 0.574461 | 1(Win) |
| glaze | 3297.16 | 2.40164 | 5.4773ms | 70103 | 30 | 7.11426e+06 | 20276.7 | 0.91974 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1092.92 | 0.967413 | 29.0532ms | 11812 | 128 | 1.27263e+06 | 10307 | 2.77593 | 1(Win) |
| glaze | 734.182 | 0.615282 | 4.8706ms | 11812 | 30 | 267368 | 15343.3 | 4.13347 | 2(Loss) |
| simdjson (ondemand) | 450.832 | 0.840313 | 7.2412ms | 11812 | 30 | 1.32257e+06 | 24986.7 | 6.73646 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3742.46 | 0.291549 | 1.8192ms | 11812 | 30 | 2310.34 | 3010 | 0.807269 | 1(Win) |
| glaze | 3527.14 | 0.342578 | 3.624ms | 11812 | 32 | 3830.65 | 3193.75 | 0.859023 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2177.54 | 1.62191 | 18.6062ms | 31235 | 64 | 3.15053e+06 | 13679.7 | 1.39292 | 1(Win) |
| glaze | 1532.83 | 0.310452 | 6.1837ms | 31235 | 30 | 109195 | 19433.3 | 1.98007 | 2(Loss) |
| simdjson (ondemand) | 1111.3 | 1.12396 | 34.7675ms | 31235 | 64 | 5.80903e+06 | 26804.7 | 2.73328 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5077.5 | 0.287015 | 2.6671ms | 31235 | 30 | 8505.75 | 5866.67 | 0.596426 | 1(Win) |
| glaze | 4804.52 | 0.409207 | 2.8373ms | 31235 | 30 | 19310.3 | 6200 | 0.629871 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2348.15 | 1.70147 | 11.9065ms | 108313 | 30 | 1.68064e+07 | 43990 | 1.29391 | 1(Win) |
| glaze | 1221.13 | 1.0321 | 21.4383ms | 108313 | 30 | 2.28664e+07 | 84590 | 2.48747 | 2(Loss) |
| simdjson (ondemand) | 594.448 | 1.1247 | 43.1499ms | 108313 | 30 | 1.14586e+08 | 173767 | 5.11175 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4652.94 | 2.20865 | 6.3788ms | 108313 | 30 | 7.21241e+06 | 22200 | 0.652231 | 1(Win) |
| glaze | 4137.5 | 2.32912 | 16.0636ms | 108313 | 32 | 1.08197e+07 | 24965.6 | 0.733855 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2226.5 | 0.9602 | 23.6596ms | 213963 | 30 | 2.32315e+07 | 91646.7 | 1.36459 | 1(Win) |
| glaze | 1889.94 | 1.00837 | 27.2503ms | 213963 | 30 | 3.55582e+07 | 107967 | 1.60769 | 2(Loss) |
| simdjson (ondemand) | 1121.43 | 0.663856 | 45.5119ms | 213963 | 30 | 4.37729e+07 | 181957 | 2.7099 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5244.18 | 1.13989 | 10.7634ms | 213963 | 30 | 5.90162e+06 | 38910 | 0.579309 | 1(Win) |
| glaze | 3756.22 | 1.84165 | 67.4816ms | 213963 | 64 | 6.40574e+07 | 54323.4 | 0.808765 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 636.21 | 0.341105 | 666.501ms | 1834197 | 30 | 2.63869e+09 | 2.74945e+06 | 4.77663 | 1(Win) |
| glaze | 283.577 | 0.700512 | 1466.33ms | 1834197 | 30 | 5.60149e+10 | 6.16844e+06 | 10.7174 | 2(Loss) |
| simdjson (ondemand) | 230.045 | 0.421635 | 1863.34ms | 1834197 | 30 | 3.08363e+10 | 7.60385e+06 | 13.2111 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 659.338 | 0.424406 | 642.399ms | 1834197 | 30 | 3.80329e+09 | 2.653e+06 | 4.60909 | 1(Win) |
| glaze | 527.765 | 0.433508 | 787.532ms | 1833577 | 30 | 6.18917e+09 | 3.31329e+06 | 5.75831 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2423.12 | 0.253338 | 940.63ms | 9930848 | 30 | 2.94134e+09 | 3.90852e+06 | 1.25408 | 1(Win) |
| glaze | 1308.13 | 0.325273 | 1746.31ms | 9930848 | 30 | 1.66374e+10 | 7.23993e+06 | 2.32327 | 2(Loss) |
| simdjson (ondemand) | 1094.67 | 0.281084 | 2100.77ms | 9930848 | 30 | 1.77419e+10 | 8.65174e+06 | 2.77635 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1683.34 | 0.784238 | 1298.95ms | 9930848 | 30 | 5.84045e+10 | 5.6262e+06 | 1.80533 | 1(Win) |
| glaze | 944.529 | 0.252525 | 2455.77ms | 9930228 | 30 | 1.92317e+10 | 1.00264e+07 | 3.21773 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1328.55 | 0.68574 | 112.243ms | 642697 | 30 | 3.00258e+08 | 461347 | 2.28734 | 1(Win) |
| glaze | 671.928 | 0.407362 | 221.857ms | 642697 | 30 | 4.14238e+08 | 912187 | 4.52251 | 2(Loss) |
| simdjson (ondemand) | 476.659 | 0.356648 | 310.856ms | 642697 | 30 | 6.30953e+08 | 1.28587e+06 | 6.37587 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1324.72 | 0.516569 | 112.839ms | 642697 | 30 | 1.71375e+08 | 462683 | 2.29379 | 1(Win) |
| glaze | 583.534 | 0.649232 | 247.436ms | 642692 | 30 | 1.39507e+09 | 1.05036e+06 | 5.20628 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1909.12 | 0.54221 | 149.104ms | 1225964 | 30 | 3.30785e+08 | 612413 | 1.59166 | 1(Win) |
| glaze | 1181.4 | 0.274946 | 241.154ms | 1225964 | 30 | 2.22115e+08 | 989650 | 2.57227 | 2(Loss) |
| simdjson (ondemand) | 883.215 | 0.782989 | 316.826ms | 1225964 | 30 | 3.22296e+09 | 1.32377e+06 | 3.44093 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1436.42 | 0.779416 | 197.33ms | 1225964 | 30 | 1.20741e+09 | 813950 | 2.11497 | 1(Win) |
| glaze | 1178.51 | 0.318371 | 241.93ms | 1225970 | 30 | 2.99283e+08 | 992080 | 2.57821 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 849.875 | 0.932286 | 112.949ms | 409725 | 30 | 5.51182e+08 | 459767 | 3.5755 | 1(Win) |
| glaze | 573.811 | 0.423303 | 165.453ms | 409725 | 30 | 2.49271e+08 | 680963 | 5.29597 | 2(Loss) |
| simdjson (ondemand) | 444.544 | 0.441582 | 209.773ms | 409725 | 30 | 4.51958e+08 | 878977 | 6.83587 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2668.41 | 2.17259 | 36.3143ms | 409725 | 30 | 3.0364e+08 | 146433 | 1.13823 | 1(Win) |
| jsonifier | 2405.02 | 1.78877 | 39.6223ms | 409725 | 30 | 2.53381e+08 | 162470 | 1.26356 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1201.57 | 0.443931 | 150.038ms | 785750 | 30 | 2.29943e+08 | 623640 | 2.52908 | 1(Win) |
| glaze | 939.325 | 0.360284 | 193.134ms | 785750 | 30 | 2.47827e+08 | 797753 | 3.23515 | 2(Loss) |
| simdjson (ondemand) | 825.851 | 0.389423 | 218.551ms | 785750 | 30 | 3.74568e+08 | 907367 | 3.67991 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3428.26 | 1.03484 | 53.5142ms | 785750 | 30 | 1.53494e+08 | 218580 | 0.886215 | 1(Win) |
| glaze | 1696.87 | 0.946864 | 106.381ms | 785750 | 30 | 5.24527e+08 | 441607 | 1.78992 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 796.138 | 1.20713 | 2379.27ms | 8587914 | 30 | 4.62621e+11 | 1.02873e+07 | 3.81747 | 1(Win) |
| glaze | 630.178 | 0.441225 | 3166.37ms | 8587914 | 30 | 9.86485e+10 | 1.29964e+07 | 4.82297 | 2(Loss) |
| simdjson (ondemand) | 583.335 | 0.715267 | 3356.55ms | 8587914 | 30 | 3.02551e+11 | 1.40401e+07 | 5.21014 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1834.57 | 1.00244 | 1070.93ms | 8588126 | 30 | 6.0085e+10 | 4.46442e+06 | 1.65635 | 1(Win) |
| glaze | 1169.57 | 0.478502 | 1745.31ms | 8588126 | 30 | 3.36847e+10 | 7.0028e+06 | 2.59846 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 852.908 | 0.262527 | 2681.12ms | 9804437 | 30 | 2.4849e+10 | 1.09628e+07 | 3.56296 | 1(Win) |
| glaze | 672.643 | 0.368754 | 3346.23ms | 9804437 | 30 | 7.88261e+10 | 1.39008e+07 | 4.51847 | 2(Loss) |
| simdjson (ondemand) | 660.361 | 0.683836 | 3407.61ms | 9804437 | 30 | 2.8126e+11 | 1.41593e+07 | 4.60253 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1877.98 | 0.694963 | 3197.38ms | 11078090 | 32 | 4.89125e+10 | 5.62566e+06 | 1.6182 | 1(Win) |
| glaze | 1277.71 | 0.436114 | 1969.04ms | 11078090 | 30 | 3.90111e+10 | 8.26864e+06 | 2.37858 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4185.18 | 1.16614 | 15.9602ms | 264040 | 30 | 1.47685e+07 | 60166.7 | 0.725948 | 1(Win) |
| simdjson (ondemand) | 1858.18 | 0.650801 | 33.9908ms | 264040 | 30 | 2.33336e+07 | 135513 | 1.63525 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5376.39 | 1.37968 | 18.2441ms | 399947 | 30 | 2.87412e+07 | 70943.3 | 0.565061 | 1(Win) |
| simdjson (ondemand) | 2598.05 | 0.863263 | 36.8311ms | 399947 | 30 | 4.81858e+07 | 146810 | 1.16959 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1517.77 | 1.06139 | 41.992ms | 264040 | 30 | 9.30241e+07 | 165907 | 2.00204 | 1(Win) |
| glaze | 887.273 | 0.754779 | 69.906ms | 264040 | 30 | 1.37653e+08 | 283800 | 3.42481 | 2(Loss) |
| simdjson (ondemand) | 747.686 | 1.17991 | 81.7535ms | 264040 | 30 | 4.7372e+08 | 336783 | 4.06415 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5448.82 | 1.65369 | 12.9576ms | 264040 | 30 | 1.75212e+07 | 46213.3 | 0.557432 | 1(Win) |
| glaze | 4156.61 | 2.25111 | 15.9014ms | 263923 | 30 | 5.57433e+07 | 60553.3 | 0.730684 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1477.8 | 0.810285 | 63.7495ms | 399947 | 30 | 1.31212e+08 | 258100 | 2.05635 | 1(Win) |
| glaze | 1144.64 | 0.803295 | 80.8911ms | 399947 | 30 | 2.14952e+08 | 333223 | 2.65472 | 2(Loss) |
| simdjson (ondemand) | 1077.74 | 1.13063 | 85.4141ms | 399947 | 30 | 4.80329e+08 | 353907 | 2.81957 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5620.4 | 1.73845 | 17.5786ms | 399947 | 30 | 4.17555e+07 | 67863.3 | 0.540564 | 1(Win) |
| glaze | 3261.73 | 2.27824 | 30.0016ms | 399830 | 30 | 2.12802e+08 | 116903 | 0.931509 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2456.56 | 1.14151 | 44.6659ms | 466906 | 30 | 1.28436e+08 | 181260 | 1.23674 | 1(Win) |
| glaze | 1895.87 | 0.821639 | 57.3949ms | 466906 | 30 | 1.11719e+08 | 234867 | 1.60296 | 2(Loss) |
| simdjson (ondemand) | 1102.4 | 0.895843 | 98.5553ms | 466906 | 30 | 3.92797e+08 | 403917 | 2.75602 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3231.14 | 2.00444 | 50.1818ms | 699405 | 30 | 5.13633e+08 | 206430 | 0.940211 | 1(Win) |
| glaze | 2791.01 | 0.715041 | 58.5979ms | 699405 | 30 | 8.76028e+07 | 238983 | 1.0887 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4145.6 | 1.15817 | 36.2022ms | 631514 | 30 | 8.49294e+07 | 145277 | 0.732854 | 1(Win) |
| glaze | 2488.6 | 0.552371 | 59.6598ms | 631514 | 30 | 5.36089e+07 | 242007 | 1.22108 | 2(Loss) |
