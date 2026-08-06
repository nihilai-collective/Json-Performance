# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.6.87.2-microsoft-standard-WSL2 using the GCC 16.0.1 compiler).  

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
| jsonifier | 1273.27 | 0.0707551 | 1.14957ms | 1811 | 30 | 27.6333 | 1356.43 | 2.33348 | 1(Win) |
| glaze | 876.421 | 0.132606 | 0.711891ms | 1811 | 30 | 204.861 | 1970.63 | 3.4203 | 2(Loss) |
| simdjson (ondemand) | 239.687 | 0.0729797 | 1.97726ms | 1811 | 30 | 829.609 | 7205.67 | 12.6358 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 717.872 | 1.79486 | 0.836362ms | 1811 | 30 | 55940.7 | 2405.87 | 4.17848 | 1(Win) |
| glaze | 506.421 | 0.283873 | 1.05445ms | 1798 | 30 | 2771.58 | 3385.93 | 5.93102 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2053.7 | 0.0516078 | 0.682589ms | 3873 | 30 | 25.8448 | 1798.5 | 1.46058 | 1(Win) |
| glaze | 1901.29 | 0.0405795 | 0.714423ms | 3873 | 30 | 18.6437 | 1942.67 | 1.57674 | 2(Loss) |
| simdjson (ondemand) | 451.792 | 0.198908 | 2.17007ms | 3873 | 30 | 7933.14 | 8175.4 | 6.70612 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2946.3 | 0.204338 | 0.572106ms | 3873 | 30 | 196.861 | 1253.63 | 1.00418 | 1(Win) |
| glaze | 1406.22 | 0.130125 | 0.891027ms | 3873 | 30 | 350.455 | 2626.6 | 2.1366 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1701.09 | 0.0602294 | 0.735577ms | 3862 | 30 | 51.0161 | 2165.13 | 1.76478 | 1(Win) |
| jsonifier | 1680.29 | 0.0595814 | 0.737529ms | 3862 | 30 | 51.1678 | 2191.93 | 1.78238 | 2(Loss) |
| simdjson (ondemand) | 472.508 | 0.114045 | 2.14642ms | 3862 | 30 | 2370.74 | 7794.77 | 6.41145 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2845.7 | 0.167522 | 0.53585ms | 3862 | 30 | 141.03 | 1294.27 | 1.04133 | 1(Win) |
| glaze | 1423.01 | 0.158608 | 0.869623ms | 3862 | 30 | 505.564 | 2588.23 | 2.10252 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2226.33 | 0.414525 | 0.282333ms | 905 | 30 | 77.4713 | 387.667 | 1.29864 | 1(Win) |
| glaze | 713.03 | 0.0801749 | 0.522618ms | 905 | 30 | 28.254 | 1210.43 | 4.19543 | 2(Loss) |
| simdjson (ondemand) | 193.237 | 0.0785747 | 1.26925ms | 905 | 30 | 369.49 | 4466.4 | 15.658 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1202.11 | 0.352263 | 0.396636ms | 905 | 30 | 191.895 | 717.967 | 2.46464 | 1(Win) |
| glaze | 365.385 | 0.146995 | 0.839436ms | 905 | 30 | 361.679 | 2362.1 | 8.11727 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4120.42 | 0.0412689 | 0.799742ms | 9578 | 30 | 25.1092 | 2216.83 | 0.729662 | 1(Win) |
| glaze | 2770.99 | 0.153549 | 1.09292ms | 9578 | 30 | 768.593 | 3296.4 | 1.08846 | 2(Loss) |
| simdjson (ondemand) | 1498.32 | 0.954791 | 1.68793ms | 9578 | 30 | 101644 | 6096.37 | 2.02172 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5923.03 | 0.146523 | 0.625539ms | 9578 | 30 | 153.178 | 1542.17 | 0.501858 | 1(Win) |
| glaze | 3163.5 | 0.131483 | 0.96369ms | 9578 | 30 | 432.386 | 2887.4 | 0.943475 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5567.95 | 0.168395 | 1.70565ms | 33713 | 30 | 2836.51 | 5774.33 | 0.543345 | 1(Win) |
| simdjson (ondemand) | 4810.69 | 1.664 | 4.19442ms | 33713 | 32 | 395765 | 6683.28 | 0.629342 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6941.98 | 0.0838254 | 4.13603ms | 48024 | 32 | 978.706 | 6597.44 | 0.436258 | 1(Win) |
| simdjson (ondemand) | 6319.93 | 1.17532 | 2.07337ms | 48024 | 30 | 217633 | 7246.8 | 0.479465 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2003.71 | 0.531879 | 81.1295ms | 294588 | 32 | 1.77966e+07 | 140211 | 1.51649 | 1(Win) |
| glaze | 1884.16 | 0.440556 | 36.3761ms | 294588 | 30 | 1.29456e+07 | 149107 | 1.61274 | 2(Loss) |
| simdjson (ondemand) | 1691.69 | 0.469237 | 40.5586ms | 294588 | 30 | 1.82177e+07 | 166071 | 1.79624 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5278.52 | 0.295347 | 12.7124ms | 294588 | 30 | 741296 | 53223.5 | 0.575525 | 1(Win) |
| glaze | 4661.63 | 1.07873 | 67.0149ms | 294588 | 30 | 1.26795e+07 | 60266.7 | 0.651437 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2171.21 | 0.357433 | 44.0342ms | 406546 | 30 | 1.22215e+07 | 178570 | 1.39951 | 1(Win) |
| simdjson (ondemand) | 2018.33 | 2.32979 | 91.5049ms | 406546 | 30 | 6.0088e+08 | 192095 | 1.5051 | 2(Loss) |
| jsonifier | 1618.87 | 1.58486 | 56.4391ms | 406546 | 30 | 4.32217e+08 | 239496 | 1.87689 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5637.4 | 0.349697 | 17.1531ms | 406546 | 30 | 1.73527e+06 | 68775.1 | 0.538877 | 1(Win) |
| glaze | 4975.13 | 1.9077 | 20.0792ms | 406546 | 30 | 6.63056e+07 | 77930.1 | 0.610539 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5370.35 | 0.888358 | 1.67609ms | 33713 | 30 | 84856.9 | 5986.8 | 0.563749 | 1(Win) |
| simdjson (ondemand) | 2802.92 | 0.277005 | 3.1224ms | 33713 | 30 | 30288 | 11470.6 | 1.08217 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6793.03 | 0.140749 | 1.91659ms | 48024 | 30 | 2701.47 | 6742.1 | 0.4457 | 1(Win) |
| simdjson (ondemand) | 3698.89 | 0.315013 | 3.25351ms | 48024 | 30 | 45640.8 | 12381.9 | 0.820105 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1971.22 | 0.49882 | 34.657ms | 294588 | 30 | 1.51625e+07 | 142522 | 1.5415 | 1(Win) |
| jsonifier | 1709.21 | 0.420741 | 39.9366ms | 294588 | 30 | 1.4348e+07 | 164369 | 1.77786 | 2(Loss) |
| simdjson (ondemand) | 300.65 | 1.25487 | 222.69ms | 294588 | 30 | 4.12503e+09 | 934446 | 10.1086 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5595.52 | 0.952964 | 12.3342ms | 294588 | 30 | 6.86791e+06 | 50208.2 | 0.542836 | 1(Win) |
| glaze | 4725.56 | 2.07564 | 14.5653ms | 294588 | 30 | 4.56824e+07 | 59451.4 | 0.642753 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2246.53 | 0.485784 | 41.7734ms | 406546 | 30 | 2.10863e+07 | 172583 | 1.35258 | 1(Win) |
| jsonifier | 1745.16 | 0.653346 | 53.9666ms | 406546 | 30 | 6.32058e+07 | 222164 | 1.74132 | 2(Loss) |
| simdjson (ondemand) | 418.192 | 0.907964 | 227.075ms | 406546 | 30 | 2.12581e+09 | 927115 | 7.26733 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5538.11 | 0.789685 | 17.2374ms | 406546 | 30 | 9.16908e+06 | 70008.1 | 0.548537 | 1(Win) |
| glaze | 4972.98 | 1.11304 | 18.8964ms | 406546 | 30 | 2.25907e+07 | 77963.8 | 0.610882 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1281.42 | 0.927063 | 17.6514ms | 94651 | 30 | 1.27941e+07 | 70442.6 | 2.37088 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1230.21 | 0.728881 | 17.8384ms | 94651 | 30 | 8.58079e+06 | 73374.7 | 2.46939 | 2(Tie) |
| glaze STATISTICAL TIE | 1216.53 | 0.413866 | 69.6284ms | 94651 | 30 | 2.8291e+06 | 74199.9 | 2.49728 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5874.41 | 0.0516497 | 9.3398ms | 94651 | 32 | 2015.61 | 15366 | 0.515015 | 1(Tie) |
| glaze STATISTICAL TIE | 5793.24 | 0.872514 | 4.05416ms | 94651 | 30 | 554464 | 15581.3 | 0.523548 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1729.07 | 0.551727 | 18.5611ms | 136024 | 30 | 5.14016e+06 | 75024.6 | 1.75707 | 1(Win) |
| glaze | 1527.05 | 0.845709 | 20.7878ms | 136024 | 30 | 1.54841e+07 | 84949.6 | 1.98943 | 2(Loss) |
| jsonifier | 1185.03 | 0.64703 | 26.8078ms | 136024 | 30 | 1.50503e+07 | 109468 | 2.56405 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6640.5 | 0.840288 | 4.98909ms | 136024 | 30 | 808365 | 19535.1 | 0.456141 | 1(Win) |
| glaze | 5629.7 | 0.0466366 | 6.02797ms | 136046 | 30 | 3465.58 | 23046.3 | 0.53913 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 775.188 | 0.467646 | 665.763ms | 2090234 | 30 | 4.33842e+09 | 2.57151e+06 | 3.91988 | 1(Win) |
| glaze | 714.698 | 0.564032 | 708.581ms | 2090234 | 30 | 7.42461e+09 | 2.78915e+06 | 4.25191 | 2(Loss) |
| simdjson (ondemand) | 694.577 | 0.220286 | 740ms | 2090234 | 30 | 1.19907e+09 | 2.86995e+06 | 4.37502 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1586.17 | 1.25933 | 294.521ms | 2090234 | 30 | 7.51437e+09 | 1.25674e+06 | 1.91545 | 1(Win) |
| glaze | 1419.58 | 0.130922 | 340.41ms | 2090234 | 30 | 1.01395e+08 | 1.40422e+06 | 2.14037 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2045.61 | 0.187053 | 747.897ms | 6661897 | 30 | 1.01251e+09 | 3.10581e+06 | 1.48538 | 1(Win) |
| jsonifier | 1965.96 | 0.110917 | 831.805ms | 6661897 | 30 | 3.85448e+08 | 3.23164e+06 | 1.54572 | 2(Loss) |
| glaze | 1760.74 | 1.12563 | 849.212ms | 6661897 | 30 | 4.94903e+10 | 3.6083e+06 | 1.72586 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3157.98 | 0.184599 | 491.626ms | 6661897 | 30 | 4.13769e+08 | 2.01182e+06 | 0.962175 | 1(Win) |
| glaze | 3117.32 | 0.507547 | 496.591ms | 6661897 | 30 | 3.21001e+09 | 2.03806e+06 | 0.974503 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1802.81 | 0.506384 | 63.2528ms | 500299 | 30 | 5.38818e+07 | 264655 | 1.68563 | 1(Win) |
| jsonifier | 1695.68 | 0.488062 | 209.645ms | 500299 | 32 | 6.0349e+07 | 281375 | 1.79207 | 2(Loss) |
| simdjson (ondemand) | 1056.61 | 1.46843 | 106.419ms | 500299 | 30 | 1.31903e+09 | 451558 | 2.87557 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5616.91 | 0.733711 | 20.6877ms | 500299 | 30 | 1.1653e+07 | 84943.9 | 0.540721 | 1(Tie) |
| glaze STATISTICAL TIE | 5615.21 | 0.903079 | 21.3819ms | 500299 | 30 | 1.76644e+07 | 84969.6 | 0.540866 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2803.39 | 0.184026 | 119.207ms | 1439562 | 30 | 2.43654e+07 | 489718 | 1.08401 | 1(Win) |
| jsonifier STATISTICAL TIE | 2711.84 | 0.77834 | 123.694ms | 1439562 | 30 | 4.65792e+08 | 506251 | 1.12051 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2709.74 | 0.742215 | 120.012ms | 1439562 | 30 | 4.24215e+08 | 506644 | 1.1213 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6974.01 | 0.749443 | 47.7766ms | 1439562 | 30 | 6.52972e+07 | 196856 | 0.435541 | 1(Win) |
| glaze | 5224.79 | 0.688981 | 65.531ms | 1439584 | 30 | 9.83268e+07 | 262765 | 0.58147 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1860.49 | 1.78304 | 7.30893ms | 56369 | 30 | 7.96294e+06 | 28894.4 | 1.632 | 1(Tie) |
| glaze STATISTICAL TIE | 1816.67 | 0.746315 | 7.55311ms | 56369 | 30 | 1.46316e+06 | 29591.3 | 1.67142 | 1(Tie) |
| simdjson (ondemand) | 1272.29 | 0.779126 | 10.5333ms | 56369 | 30 | 3.25121e+06 | 42252.7 | 2.38684 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6667.76 | 0.325346 | 2.2385ms | 56369 | 30 | 20641.1 | 8062.33 | 0.45414 | 1(Win) |
| jsonifier | 5573.84 | 0.0816088 | 2.61899ms | 56369 | 30 | 1858.52 | 9644.63 | 0.54382 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2373.22 | 0.733307 | 9.47633ms | 94370 | 30 | 2.31998e+06 | 37922.4 | 1.27979 | 1(Win) |
| simdjson (ondemand) | 2152.69 | 0.156723 | 10.6237ms | 94370 | 30 | 128793 | 41807.4 | 1.41104 | 2(Loss) |
| jsonifier | 1795.08 | 1.19773 | 62.2917ms | 94370 | 64 | 2.30781e+07 | 50136.1 | 1.69186 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6869.4 | 0.0629081 | 3.51479ms | 94370 | 30 | 2037.82 | 13101.3 | 0.440119 | 1(Win) |
| glaze | 5456.21 | 1.68675 | 4.21382ms | 94370 | 30 | 2.32226e+06 | 16494.6 | 0.555824 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1851.72 | 0.362555 | 7.76404ms | 52708 | 30 | 290586 | 27145.8 | 1.63948 | 1(Win) |
| jsonifier | 1450.21 | 1.22593 | 8.94396ms | 52708 | 30 | 5.41675e+06 | 34661.3 | 2.09336 | 2(Loss) |
| glaze | 1325.34 | 2.31248 | 9.58629ms | 52708 | 30 | 2.30768e+07 | 37927.1 | 2.29116 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 7427.89 | 0.276353 | 2.01638ms | 52708 | 30 | 10492.3 | 6767.23 | 0.407278 | 1(Win) |
| jsonifier | 6054.13 | 0.419821 | 2.23955ms | 52708 | 30 | 36450.1 | 8302.8 | 0.497752 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2258.01 | 1.0326 | 8.03568ms | 70103 | 30 | 2.8042e+06 | 29608.2 | 1.34459 | 1(Win) |
| glaze | 1516.93 | 1.80473 | 10.7437ms | 70103 | 30 | 1.89796e+07 | 44072.8 | 2.0019 | 2(Loss) |
| jsonifier | 1341.8 | 1.05573 | 13.7033ms | 70103 | 30 | 8.3009e+06 | 49825.3 | 2.26362 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6508.05 | 0.574412 | 2.91167ms | 70103 | 30 | 104458 | 10272.7 | 0.465585 | 1(Win) |
| jsonifier | 6246.24 | 1.75042 | 2.90251ms | 70103 | 30 | 1.05304e+06 | 10703.3 | 0.483474 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1423.86 | 0.115695 | 5.16951ms | 11812 | 32 | 2680.96 | 7911.44 | 2.12721 | 1(Win) |
| jsonifier | 1373.68 | 0.0780624 | 2.31427ms | 11812 | 30 | 1229.36 | 8200.43 | 2.20533 | 2(Loss) |
| simdjson (ondemand) | 1121.76 | 0.699823 | 6.09739ms | 11812 | 32 | 158042 | 10042.1 | 2.70291 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5802.51 | 0.267249 | 0.712292ms | 11812 | 30 | 807.551 | 1941.37 | 0.513277 | 1(Win) |
| glaze | 4997.99 | 0.0954615 | 0.816122ms | 11812 | 30 | 138.878 | 2253.87 | 0.600988 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2616.86 | 0.0836986 | 3.09689ms | 31235 | 30 | 2723.2 | 11383.1 | 1.159 | 1(Win) |
| simdjson (ondemand) | 2564.06 | 0.454202 | 3.10772ms | 31235 | 30 | 83530.8 | 11617.5 | 1.18258 | 2(Loss) |
| glaze | 2187.21 | 0.14053 | 3.62327ms | 31235 | 30 | 10989.1 | 13619.2 | 1.38708 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8144.81 | 0.130448 | 1.16356ms | 31235 | 30 | 682.838 | 3657.3 | 0.367051 | 1(Win) |
| glaze | 6404.97 | 0.412713 | 1.39374ms | 31235 | 30 | 11052.7 | 4650.77 | 0.471365 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3196.77 | 0.861882 | 8.13444ms | 108313 | 30 | 2.32677e+06 | 32312.4 | 0.949743 | 1(Win) |
| glaze | 2117.14 | 0.942899 | 11.9025ms | 108313 | 30 | 6.34915e+06 | 48790.1 | 1.4348 | 2(Loss) |
| simdjson (ondemand) | 1585.95 | 0.426959 | 16.2109ms | 108313 | 30 | 2.31994e+06 | 65131.7 | 1.91561 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6601.27 | 0.299364 | 4.07838ms | 108313 | 30 | 65830.5 | 15647.8 | 0.458375 | 1(Win) |
| glaze | 5702.15 | 1.38449 | 4.90379ms | 108313 | 30 | 1.88705e+06 | 18115.2 | 0.532044 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2886.32 | 1.82037 | 17.6514ms | 213963 | 30 | 4.96853e+07 | 70695.8 | 1.05244 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2848.46 | 0.370657 | 17.5165ms | 213963 | 30 | 2.11507e+06 | 71635.6 | 1.06657 | 1(Tie) |
| jsonifier | 2244.5 | 0.723776 | 22.2125ms | 213963 | 30 | 1.29888e+07 | 90911.8 | 1.35357 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8258.97 | 0.249973 | 6.2817ms | 213963 | 30 | 114428 | 24706.6 | 0.367616 | 1(Win) |
| glaze | 5877.49 | 0.283186 | 8.66667ms | 213963 | 30 | 289974 | 34717.4 | 0.516512 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 821.62 | 0.374801 | 554.881ms | 1834197 | 30 | 1.91017e+09 | 2.129e+06 | 3.6985 | 1(Win) |
| glaze | 618.038 | 0.282967 | 730.015ms | 1834197 | 30 | 1.92422e+09 | 2.83029e+06 | 4.91704 | 2(Loss) |
| simdjson (ondemand) | 584.004 | 0.444701 | 774.726ms | 1834197 | 30 | 5.32253e+09 | 2.99523e+06 | 5.20348 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1015.48 | 2.39429 | 405.605ms | 1834197 | 30 | 5.10302e+10 | 1.72257e+06 | 2.99223 | 1(Win) |
| glaze | 934.077 | 0.580604 | 449.603ms | 1833577 | 30 | 3.54417e+09 | 1.87205e+06 | 3.2529 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2746.71 | 0.418689 | 884.195ms | 9930848 | 30 | 6.25246e+09 | 3.44805e+06 | 1.10635 | 1(Win) |
| glaze | 2521.25 | 0.229402 | 964.741ms | 9930848 | 30 | 2.2277e+09 | 3.75639e+06 | 1.20533 | 2(Loss) |
| jsonifier | 2335.69 | 0.18124 | 2470.1ms | 9930848 | 32 | 1.72823e+09 | 4.05482e+06 | 1.30106 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3111.15 | 0.536743 | 739.252ms | 9930848 | 30 | 8.00913e+09 | 3.04415e+06 | 0.976728 | 1(Win) |
| glaze | 2182.15 | 1.1185 | 1068.2ms | 9930228 | 30 | 7.0687e+10 | 4.33985e+06 | 1.39223 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1426.92 | 0.30742 | 103.622ms | 642697 | 30 | 5.23119e+07 | 429544 | 2.12967 | 1(Win) |
| glaze | 1076.03 | 0.334087 | 136.138ms | 642697 | 30 | 1.08644e+08 | 569617 | 2.82412 | 2(Loss) |
| simdjson (ondemand) | 1043.6 | 0.351967 | 141.755ms | 642697 | 30 | 1.28195e+08 | 587318 | 2.91184 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1668.17 | 0.53151 | 213.064ms | 642697 | 32 | 1.22041e+08 | 367423 | 1.82154 | 1(Win) |
| glaze | 1419.43 | 1.00843 | 103.182ms | 642692 | 30 | 5.68841e+08 | 431805 | 2.14043 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1866.13 | 0.487602 | 198.714ms | 1225964 | 30 | 2.79977e+08 | 626520 | 1.62825 | 1(Win) |
| glaze | 1816.81 | 0.379158 | 155.94ms | 1225964 | 30 | 1.78607e+08 | 643529 | 1.67252 | 2(Loss) |
| jsonifier | 1666.04 | 0.722854 | 216.431ms | 1225964 | 30 | 7.71978e+08 | 701764 | 1.82391 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2563.22 | 0.834906 | 109.375ms | 1225964 | 30 | 4.3509e+08 | 456133 | 1.18522 | 1(Win) |
| glaze | 2200.05 | 1.58471 | 127.349ms | 1225970 | 30 | 2.12774e+09 | 531432 | 1.3808 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1109.83 | 1.24382 | 82.9201ms | 409725 | 30 | 5.7532e+08 | 352075 | 2.7374 | 1(Win) |
| simdjson (ondemand) | 951.98 | 0.573845 | 152.031ms | 409725 | 30 | 1.66433e+08 | 410454 | 3.19211 | 2(Loss) |
| glaze | 872.522 | 0.64699 | 107.966ms | 409725 | 30 | 2.51854e+08 | 447833 | 3.48261 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4756.17 | 0.420957 | 20.3872ms | 409725 | 30 | 3.58812e+06 | 82155.2 | 0.638574 | 1(Win) |
| glaze | 3414.44 | 1.3993 | 27.8032ms | 409725 | 30 | 7.69293e+07 | 114439 | 0.889564 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1724.4 | 0.346137 | 158.352ms | 785750 | 30 | 6.78748e+07 | 434556 | 1.76217 | 1(Win) |
| glaze | 1402.17 | 0.884539 | 127.974ms | 785750 | 30 | 6.70384e+08 | 534422 | 2.16688 | 2(Loss) |
| jsonifier | 1173.7 | 0.277359 | 153.746ms | 785750 | 30 | 9.40726e+07 | 638453 | 2.58927 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5534.1 | 0.417117 | 33.2981ms | 785750 | 30 | 9.57001e+06 | 135406 | 0.54886 | 1(Win) |
| glaze | 4179.92 | 0.849939 | 44.3544ms | 785750 | 30 | 6.96512e+07 | 179273 | 0.726816 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1295.36 | 0.446707 | 1588.36ms | 8587914 | 30 | 2.39308e+10 | 6.3226e+06 | 2.34588 | 1(Win) |
| simdjson (ondemand) | 1224.49 | 0.228495 | 1656.17ms | 8587914 | 30 | 7.00716e+09 | 6.68857e+06 | 2.48169 | 2(Loss) |
| glaze | 1120.79 | 1.1102 | 1837.15ms | 8587914 | 30 | 1.97448e+11 | 7.3074e+06 | 2.71139 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3375.56 | 1.35438 | 582.498ms | 8588126 | 30 | 3.2397e+10 | 2.42635e+06 | 0.900076 | 1(Win) |
| glaze | 2924.72 | 1.4001 | 657.283ms | 8588126 | 30 | 4.61177e+10 | 2.80036e+06 | 1.03869 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1384.4 | 0.458951 | 4056.27ms | 9804437 | 32 | 3.07474e+10 | 6.75402e+06 | 2.195 | 1(Win) |
| glaze | 1178.44 | 0.837557 | 2006.56ms | 9804437 | 30 | 1.32489e+11 | 7.93441e+06 | 2.57869 | 2(Loss) |
| jsonifier | 1125.62 | 0.226872 | 10585.4ms | 9804437 | 64 | 2.27303e+10 | 8.30675e+06 | 2.6998 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3559.64 | 1.00647 | 783.438ms | 11078090 | 30 | 2.67696e+10 | 2.96796e+06 | 0.853482 | 1(Win) |
| glaze | 2852.8 | 0.955609 | 939.038ms | 11078090 | 30 | 3.75725e+10 | 3.70334e+06 | 1.06498 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5351.85 | 0.641846 | 11.5935ms | 264040 | 30 | 2.73599e+06 | 47050.6 | 0.567574 | 1(Win) |
| jsonifier | 5030.22 | 0.833269 | 12.679ms | 264040 | 30 | 5.21984e+06 | 50059.1 | 0.603772 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 7116.08 | 0.650994 | 13.3391ms | 399947 | 30 | 3.65257e+06 | 53599.6 | 0.426883 | 1(Win) |
| jsonifier | 6561.65 | 0.505627 | 14.4942ms | 399947 | 30 | 2.59155e+06 | 58128.5 | 0.462806 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1640.49 | 0.932578 | 37.5686ms | 264040 | 30 | 6.14729e+07 | 153496 | 1.85202 | 1(Win) |
| glaze STATISTICAL TIE | 1552.93 | 1.1604 | 39.5378ms | 264040 | 30 | 1.06211e+08 | 162150 | 1.95665 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1478.57 | 2.27798 | 39.6094ms | 264040 | 30 | 4.51518e+08 | 170305 | 2.0545 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6239.14 | 1.87655 | 10.4554ms | 263923 | 30 | 1.71928e+07 | 40341.6 | 0.48665 | 1(Win) |
| jsonifier | 5530.84 | 1.92733 | 11.0517ms | 264040 | 30 | 2.3099e+07 | 45528 | 0.548551 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2330.93 | 0.500211 | 40.7447ms | 399947 | 30 | 2.0099e+07 | 163634 | 1.30355 | 1(Win) |
| glaze | 2012.24 | 0.672638 | 47.3871ms | 399947 | 30 | 4.87673e+07 | 189549 | 1.51012 | 2(Loss) |
| jsonifier | 1319.48 | 0.766907 | 71.8674ms | 399947 | 30 | 1.47437e+08 | 289068 | 2.30276 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7112.59 | 0.35422 | 13.5237ms | 399947 | 30 | 1.08247e+06 | 53625.9 | 0.427114 | 1(Win) |
| glaze | 5740.22 | 0.987281 | 16.8766ms | 399830 | 30 | 1.29032e+07 | 66427.4 | 0.529096 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2459.49 | 0.803034 | 44.462ms | 466906 | 30 | 6.34102e+07 | 181044 | 1.23532 | 1(Win) |
| glaze | 2411.07 | 0.437146 | 44.3018ms | 466906 | 30 | 1.95531e+07 | 184680 | 1.26032 | 2(Loss) |
| simdjson (ondemand) | 1324.08 | 1.08201 | 80.4366ms | 466906 | 30 | 3.97209e+08 | 336292 | 2.29496 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3802.85 | 1.25322 | 44.1152ms | 699405 | 30 | 1.4495e+08 | 175396 | 0.798925 | 1(Win) |
| glaze | 3640.07 | 0.691679 | 95.9755ms | 699405 | 30 | 4.81912e+07 | 183239 | 0.834764 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3212.77 | 0.599538 | 45.3649ms | 631514 | 30 | 3.78932e+07 | 187458 | 0.945604 | 1(Win) |
| glaze | 2386.11 | 0.465865 | 60.8075ms | 631514 | 30 | 4.14788e+07 | 252402 | 1.27357 | 2(Loss) |
