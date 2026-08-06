# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.6.87.2-microsoft-standard-WSL2 using the Clang 23.0.0 compiler).  

Latest Results: (Aug 06, 2026)
#### Using the following commits:
----
| Jsonifier: [90b27e4](https://github.com/nihilai-collective/jsonifier/commit/90b27e4)  
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
| jsonifier | 1241.98 | 0.0730269 | 1.19703ms | 1811 | 30 | 30.9379 | 1390.6 | 2.39523 | 1(Win) |
| glaze | 835.642 | 0.078134 | 0.729692ms | 1811 | 30 | 78.2345 | 2066.8 | 3.58962 | 2(Loss) |
| simdjson (ondemand) | 232.091 | 0.0475034 | 2.02474ms | 1811 | 30 | 374.879 | 7441.5 | 13.0511 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 768.137 | 0.0757144 | 0.778955ms | 1811 | 30 | 86.9437 | 2248.43 | 3.90241 | 1(Win) |
| glaze | 506.067 | 0.273169 | 1.09348ms | 1798 | 30 | 2570.08 | 3388.3 | 5.9419 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2152.02 | 0.035811 | 0.621601ms | 3873 | 30 | 11.3333 | 1716.33 | 1.3924 | 1(Win) |
| glaze | 1451.2 | 0.119878 | 1.90454ms | 3873 | 32 | 297.899 | 2545.19 | 2.07288 | 2(Loss) |
| simdjson (ondemand) | 525.169 | 0.0422542 | 1.96213ms | 3873 | 30 | 264.947 | 7033.13 | 5.77156 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3162.58 | 0.0678749 | 0.494918ms | 3873 | 30 | 18.8517 | 1167.9 | 0.933884 | 1(Win) |
| glaze | 1335.16 | 1.05477 | 1.04947ms | 3873 | 30 | 25542.7 | 2766.4 | 2.24802 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2135.66 | 0.0722147 | 0.612822ms | 3862 | 30 | 46.5299 | 1724.57 | 1.40199 | 1(Win) |
| glaze | 1555.67 | 0.0487611 | 0.776167ms | 3862 | 30 | 39.9816 | 2367.53 | 1.92878 | 2(Loss) |
| simdjson (ondemand) | 510.651 | 0.32361 | 2.07328ms | 3862 | 30 | 16343.3 | 7212.53 | 5.92649 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3014.73 | 0.245219 | 0.507794ms | 3862 | 30 | 269.252 | 1221.7 | 0.977853 | 1(Win) |
| glaze | 1501.93 | 0.348509 | 0.853617ms | 3862 | 30 | 2191.15 | 2452.23 | 1.99699 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1635.85 | 0.0485997 | 0.34214ms | 905 | 30 | 1.97241 | 527.6 | 1.79333 | 1(Win) |
| glaze | 484.683 | 0.349318 | 0.680027ms | 905 | 30 | 1160.77 | 1780.7 | 6.20586 | 2(Loss) |
| simdjson (ondemand) | 220.333 | 0.0758469 | 1.43954ms | 905 | 30 | 264.809 | 3917.13 | 13.7187 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1431.54 | 0.0331253 | 0.367432ms | 905 | 30 | 1.19655 | 602.9 | 2.05794 | 1(Win) |
| glaze | 365.715 | 0.182255 | 0.909356ms | 905 | 30 | 554.999 | 2359.97 | 8.22773 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3977.25 | 0.0530814 | 0.871398ms | 9578 | 30 | 44.5851 | 2296.63 | 0.753741 | 1(Win) |
| glaze | 2737.22 | 0.11132 | 1.19839ms | 9578 | 30 | 413.995 | 3337.07 | 1.10184 | 2(Loss) |
| simdjson (ondemand) | 1608.02 | 0.135944 | 3.72202ms | 9578 | 32 | 1908.26 | 5680.47 | 1.88349 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6363.44 | 0.102826 | 0.561949ms | 9578 | 30 | 65.3575 | 1435.43 | 0.466242 | 1(Win) |
| glaze | 3393.46 | 0.119502 | 0.918386ms | 9578 | 30 | 310.409 | 2691.73 | 0.887878 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5997.06 | 0.140276 | 1.51904ms | 33713 | 30 | 1696.7 | 5361.17 | 0.504539 | 1(Win) |
| simdjson (ondemand) | 5480.66 | 0.240076 | 1.8883ms | 33713 | 30 | 5950.42 | 5866.3 | 0.552226 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7384.24 | 0.167101 | 1.85055ms | 48024 | 30 | 3222.42 | 6202.3 | 0.409874 | 1(Win) |
| simdjson (ondemand) | 6779.28 | 0.118202 | 1.91785ms | 48024 | 30 | 1913.01 | 6755.77 | 0.446795 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2222.12 | 1.49938 | 316.817ms | 294588 | 128 | 4.59968e+08 | 126429 | 1.36711 | 1(Win) |
| glaze | 2020.42 | 2.49961 | 83.2119ms | 294588 | 32 | 3.86581e+08 | 139051 | 1.50387 | 2(Loss) |
| simdjson (ondemand) | 1341.27 | 2.42222 | 51.0364ms | 294588 | 30 | 7.72235e+08 | 209460 | 2.26533 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5746.74 | 0.547649 | 13.1457ms | 294588 | 30 | 2.15037e+06 | 48887 | 0.528265 | 1(Win) |
| glaze | 4399.2 | 1.17475 | 16.8794ms | 294588 | 30 | 1.68848e+07 | 63861.9 | 0.690366 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2315.7 | 0.956296 | 42.2679ms | 406546 | 30 | 7.6906e+07 | 167428 | 1.31203 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2258.35 | 2.18075 | 98.5194ms | 406546 | 32 | 4.48538e+08 | 171680 | 1.34511 | 1(Tie) |
| simdjson (ondemand) | 1785.28 | 2.46699 | 122.266ms | 406546 | 32 | 9.18533e+08 | 217172 | 1.70161 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5069.55 | 0.748638 | 46.4751ms | 406546 | 32 | 1.049e+07 | 76478.7 | 0.599307 | 1(Win) |
| glaze | 4789.16 | 1.04104 | 47.8279ms | 406546 | 32 | 2.27291e+07 | 80956.3 | 0.634235 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5899.31 | 0.169397 | 1.57477ms | 33713 | 30 | 2556.97 | 5450 | 0.513152 | 1(Win) |
| simdjson (ondemand) | 4025.48 | 0.0592513 | 2.3785ms | 33713 | 30 | 671.857 | 7986.93 | 0.752929 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7181.49 | 0.100075 | 1.81883ms | 48024 | 30 | 1221.97 | 6377.4 | 0.421663 | 1(Win) |
| simdjson (ondemand) | 5186.17 | 0.0824605 | 5.50054ms | 48024 | 32 | 1696.93 | 8831.03 | 0.584563 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2012.5 | 1.86403 | 172.136ms | 294588 | 64 | 4.33356e+08 | 139598 | 1.50971 | 1(Win) |
| jsonifier | 1844 | 2.27975 | 37.9577ms | 294588 | 30 | 3.61912e+08 | 152354 | 1.64759 | 2(Loss) |
| simdjson (ondemand) | 442.937 | 1.78148 | 156.179ms | 294588 | 30 | 3.83028e+09 | 634269 | 6.86017 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5765.63 | 0.199258 | 65.617ms | 294588 | 30 | 282807 | 48726.9 | 0.526375 | 1(Win) |
| glaze | 4683.39 | 1.06753 | 37.5568ms | 294588 | 32 | 1.31227e+07 | 59986.7 | 0.648553 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2465.67 | 1.55799 | 39.6112ms | 406546 | 30 | 1.80054e+08 | 157244 | 1.23229 | 1(Win) |
| jsonifier | 2302.3 | 0.702407 | 42.134ms | 406546 | 30 | 4.19755e+07 | 168402 | 1.31984 | 2(Loss) |
| simdjson (ondemand) | 613.452 | 1.02468 | 156.555ms | 406546 | 30 | 1.25822e+09 | 632017 | 4.95378 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 4845 | 1.01845 | 47.6641ms | 406546 | 32 | 2.12551e+07 | 80023.2 | 0.627078 | 1(Tie) |
| glaze STATISTICAL TIE | 4717.7 | 1.33725 | 21.7937ms | 406546 | 30 | 3.62333e+07 | 82182.6 | 0.643817 | 1(Tie) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1322.49 | 1.60541 | 40.1475ms | 94651 | 32 | 3.84223e+07 | 68254.5 | 2.2969 | 1(Tie) |
| glaze STATISTICAL TIE | 1279.46 | 1.25958 | 18.1493ms | 94651 | 30 | 2.36903e+07 | 70550.2 | 2.37431 | 1(Tie) |
| simdjson (ondemand) | 981.737 | 1.36704 | 53.9893ms | 94651 | 32 | 5.05563e+07 | 91945.5 | 3.09459 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5791.57 | 0.15451 | 4.23179ms | 94651 | 30 | 17397.8 | 15585.8 | 0.523801 | 1(Win) |
| glaze | 5068.71 | 1.54361 | 11.8075ms | 94651 | 32 | 2.41813e+06 | 17808.5 | 0.598607 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1564.77 | 2.24744 | 103.333ms | 136024 | 64 | 2.22171e+08 | 82902.1 | 1.94134 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1557.82 | 1.37163 | 21.2459ms | 136024 | 30 | 3.91373e+07 | 83272 | 1.95017 | 1(Tie) |
| simdjson (ondemand) | 1348.4 | 1.0756 | 24.2385ms | 136024 | 30 | 3.21229e+07 | 96204.5 | 2.25282 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4903.38 | 1.12834 | 16.6969ms | 136024 | 32 | 2.8515e+06 | 26455.8 | 0.618237 | 1(Win) |
| glaze | 4540.7 | 0.795461 | 7.46955ms | 136046 | 30 | 1.54983e+06 | 28573.5 | 0.668563 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 869.554 | 1.29764 | 556.848ms | 2090234 | 30 | 2.65479e+10 | 2.29244e+06 | 3.49434 | 1(Win) |
| glaze | 722.948 | 1.0249 | 702.05ms | 2090234 | 30 | 2.39584e+10 | 2.75732e+06 | 4.20261 | 2(Loss) |
| simdjson (ondemand) | 447.165 | 0.497698 | 2663.72ms | 2090234 | 32 | 1.5752e+10 | 4.45786e+06 | 6.79498 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1543.26 | 1.10664 | 361.849ms | 2090234 | 30 | 6.12977e+09 | 1.29169e+06 | 1.96869 | 1(Win) |
| glaze | 912.995 | 0.674338 | 575.607ms | 2090234 | 30 | 6.50323e+09 | 2.18337e+06 | 3.32786 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2301.76 | 0.98137 | 716.815ms | 6661897 | 30 | 2.20122e+10 | 2.76019e+06 | 1.3201 | 1(Win) |
| glaze | 1853.93 | 0.823815 | 866.404ms | 6661897 | 30 | 2.39106e+10 | 3.42693e+06 | 1.63906 | 2(Loss) |
| simdjson (ondemand) | 1268.7 | 1.14612 | 1198.57ms | 6661897 | 30 | 9.88232e+10 | 5.00772e+06 | 2.39493 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3087.47 | 1.36664 | 2630.53ms | 6661897 | 64 | 5.06149e+10 | 2.05776e+06 | 0.98405 | 1(Win) |
| glaze | 2152.53 | 1.16209 | 709.612ms | 6661897 | 30 | 3.52934e+10 | 2.95153e+06 | 1.41153 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1851.64 | 1.6463 | 65.3329ms | 500299 | 30 | 5.39864e+08 | 257676 | 1.64093 | 1(Win) |
| glaze | 1711.79 | 2.2929 | 67.874ms | 500299 | 30 | 1.22532e+09 | 278727 | 1.77507 | 2(Loss) |
| simdjson (ondemand) | 904.501 | 2.05268 | 173.824ms | 500299 | 30 | 3.51726e+09 | 527498 | 3.35882 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 5360.69 | 0.644816 | 22.9947ms | 500299 | 30 | 9.88121e+06 | 89003.9 | 0.566599 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5114.4 | 2.46603 | 61.9253ms | 500299 | 32 | 1.69362e+08 | 93290 | 0.593818 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3336.63 | 1.81759 | 102.747ms | 1439562 | 30 | 1.67788e+09 | 411456 | 0.910616 | 1(Win) |
| glaze | 2789.23 | 2.4168 | 118.375ms | 1439562 | 30 | 4.24516e+09 | 492205 | 1.0893 | 2(Loss) |
| simdjson (ondemand) | 2460.58 | 2.11784 | 189.179ms | 1439562 | 30 | 4.18886e+09 | 557947 | 1.23491 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5571.39 | 2.36398 | 59.2499ms | 1439562 | 30 | 1.01799e+09 | 246415 | 0.545004 | 1(Win) |
| glaze | 5074.2 | 2.36465 | 66.885ms | 1439584 | 30 | 1.22798e+09 | 270564 | 0.598469 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1930.99 | 0.93117 | 8.07573ms | 56369 | 30 | 2.01604e+06 | 27839.4 | 1.57202 | 1(Win) |
| jsonifier | 1748.9 | 1.85242 | 8.22709ms | 56369 | 30 | 9.72636e+06 | 30738 | 1.73563 | 2(Loss) |
| simdjson (ondemand) | 1130.13 | 0.49283 | 62.1894ms | 56369 | 64 | 3.5172e+06 | 47567.7 | 2.68773 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6549.21 | 0.842332 | 10.8638ms | 56369 | 64 | 305949 | 8208.27 | 0.462306 | 1(Win) |
| jsonifier | 5648.42 | 1.23152 | 2.6076ms | 56369 | 30 | 412129 | 9517.3 | 0.533824 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2434.22 | 0.657113 | 47.884ms | 94370 | 64 | 3.77752e+06 | 36972 | 1.24761 | 1(Win) |
| jsonifier | 1900.75 | 0.700771 | 12.2415ms | 94370 | 30 | 3.30288e+06 | 47348.9 | 1.59781 | 2(Loss) |
| simdjson (ondemand) | 1828.69 | 0.971211 | 30.3674ms | 94370 | 32 | 7.31081e+06 | 49214.6 | 1.66083 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6044.53 | 0.076968 | 3.93389ms | 94370 | 30 | 3939.89 | 14889.2 | 0.500296 | 1(Win) |
| glaze | 5104.52 | 1.13661 | 4.72057ms | 94370 | 30 | 1.20476e+06 | 17631.1 | 0.59443 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1567.55 | 1.34516 | 9.13544ms | 52708 | 30 | 5.58186e+06 | 32066.8 | 1.93702 | 1(Win) |
| glaze | 1392.09 | 1.59315 | 46.788ms | 52708 | 64 | 2.11795e+07 | 36108.6 | 2.18129 | 2(Loss) |
| simdjson (ondemand) | 1295.08 | 0.857826 | 10.2255ms | 52708 | 30 | 3.32569e+06 | 38813.3 | 2.34436 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5781.21 | 0.41865 | 2.86402ms | 52708 | 30 | 39750.1 | 8694.77 | 0.521168 | 1(Tie) |
| glaze STATISTICAL TIE | 5752.17 | 0.614296 | 2.51193ms | 52708 | 30 | 86450.3 | 8738.67 | 0.526203 | 1(Tie) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1818.28 | 1.07343 | 10.6907ms | 70103 | 30 | 4.6733e+06 | 36768.5 | 1.67 | 1(Win) |
| glaze | 1638.86 | 1.99692 | 11.7439ms | 70103 | 30 | 1.99081e+07 | 40793.8 | 1.85302 | 2(Loss) |
| jsonifier | 1552.82 | 1.07104 | 11.9678ms | 70103 | 30 | 6.37916e+06 | 43054.1 | 1.95502 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 6182.72 | 0.0439572 | 55.5038ms | 70103 | 30 | 677.789 | 10813.3 | 0.48867 | 1(Tie) |
| glaze STATISTICAL TIE | 6154.23 | 1.72925 | 3.06863ms | 70103 | 30 | 1.05867e+06 | 10863.3 | 0.492553 | 1(Tie) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1442.37 | 0.241771 | 2.37041ms | 11812 | 30 | 10696.1 | 7809.93 | 2.10148 | 1(Win) |
| glaze | 1261.34 | 0.143406 | 5.67212ms | 11812 | 32 | 5248.87 | 8930.81 | 2.40175 | 2(Loss) |
| simdjson (ondemand) | 953.165 | 0.316074 | 7.49475ms | 11812 | 32 | 44651.8 | 11818.3 | 3.18113 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5517.54 | 0.446606 | 0.722642ms | 11812 | 30 | 2494.17 | 2041.63 | 0.539728 | 1(Win) |
| glaze | 4374.89 | 0.152978 | 2.11199ms | 11812 | 32 | 496.5 | 2574.88 | 0.686868 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2571.24 | 0.0931349 | 3.32884ms | 31235 | 30 | 3492.58 | 11585.1 | 1.17935 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 2277.23 | 0.158287 | 3.48707ms | 31235 | 30 | 12861.2 | 13080.8 | 1.33174 | 2(Tie) |
| glaze STATISTICAL TIE | 2233.47 | 2.19938 | 3.62491ms | 31235 | 30 | 2.58134e+06 | 13337.1 | 1.35775 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6218.1 | 0.141701 | 1.41776ms | 31235 | 30 | 1382.4 | 4790.53 | 0.48288 | 1(Win) |
| glaze | 5706.15 | 0.101161 | 1.5336ms | 31235 | 30 | 836.644 | 5220.33 | 0.529978 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3505.49 | 1.02273 | 37.4797ms | 108313 | 64 | 5.81253e+06 | 29466.7 | 0.866128 | 1(Win) |
| glaze | 2201.25 | 1.8967 | 27.8887ms | 108313 | 32 | 2.53495e+07 | 46925.8 | 1.37911 | 2(Loss) |
| simdjson (ondemand) | 1429.15 | 2.02085 | 182.244ms | 108313 | 128 | 2.73077e+08 | 72277.7 | 2.12545 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 6449.6 | 2.12661 | 9.62095ms | 108313 | 32 | 3.71213e+06 | 16015.8 | 0.47009 | 1(Tie) |
| jsonifier STATISTICAL TIE | 6173.22 | 1.84503 | 4.4673ms | 108313 | 30 | 2.85934e+06 | 16732.8 | 0.490798 | 1(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 3037.98 | 0.648515 | 17.5893ms | 213963 | 30 | 5.69204e+06 | 67166.6 | 0.999928 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2968.22 | 1.16328 | 18.2074ms | 213963 | 30 | 1.91855e+07 | 68745.2 | 1.02341 | 1(Tie) |
| simdjson (ondemand) | 2665.14 | 1.97972 | 19.3892ms | 213963 | 30 | 6.89232e+07 | 76562.8 | 1.13944 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6470.35 | 2.33083 | 8.24382ms | 213963 | 30 | 1.62093e+07 | 31536.3 | 0.468442 | 1(Win) |
| glaze | 5784.69 | 2.38544 | 9.0158ms | 213963 | 30 | 2.1241e+07 | 35274.3 | 0.524912 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 876.423 | 1.38078 | 481.013ms | 1834197 | 30 | 2.27841e+10 | 1.99587e+06 | 3.46696 | 1(Win) |
| glaze | 653.244 | 0.862585 | 708.665ms | 1834197 | 30 | 1.60054e+10 | 2.67776e+06 | 4.65161 | 2(Loss) |
| simdjson (ondemand) | 377.029 | 0.848582 | 1195.68ms | 1834197 | 30 | 4.64999e+10 | 4.63951e+06 | 8.05945 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3005.16 | 1.17957 | 749.299ms | 9930848 | 30 | 4.1458e+10 | 3.15152e+06 | 1.01117 | 1(Win) |
| glaze | 2455.84 | 1.3309 | 2272.56ms | 9930848 | 32 | 8.42968e+10 | 3.85643e+06 | 1.23728 | 2(Loss) |
| simdjson (ondemand) | 1848.16 | 0.487576 | 1282.63ms | 9930848 | 30 | 1.87284e+10 | 5.12445e+06 | 1.64412 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2829.26 | 1.5286 | 867.482ms | 9930848 | 30 | 7.85484e+10 | 3.34744e+06 | 1.07392 | 1(Win) |
| glaze | 1614.9 | 1.55124 | 1405.1ms | 9930228 | 30 | 2.48259e+11 | 5.86427e+06 | 1.88157 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1505.04 | 1.83214 | 94.6576ms | 642697 | 30 | 1.67014e+09 | 407247 | 2.01818 | 1(Win) |
| glaze | 1315.52 | 2.22636 | 264.183ms | 642697 | 32 | 3.44318e+09 | 465918 | 2.30943 | 2(Loss) |
| simdjson (ondemand) | 594.722 | 1.46533 | 249.183ms | 642697 | 30 | 6.84193e+09 | 1.0306e+06 | 5.10897 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1768.76 | 2.0278 | 84.1969ms | 642697 | 30 | 1.48131e+09 | 346528 | 1.71744 | 1(Win) |
| glaze | 917.177 | 1.23615 | 163.919ms | 642692 | 30 | 2.04721e+09 | 668267 | 3.3121 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2141.82 | 2.48412 | 352.745ms | 1225964 | 32 | 5.88415e+09 | 545876 | 1.41853 | 1(Tie) |
| glaze STATISTICAL TIE | 2039.31 | 2.12764 | 137.329ms | 1225964 | 30 | 4.46382e+09 | 573316 | 1.48975 | 1(Tie) |
| simdjson (ondemand) | 1092.8 | 1.85681 | 302.793ms | 1225964 | 30 | 1.18394e+10 | 1.06989e+06 | 2.78019 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2441.31 | 1.95193 | 115.802ms | 1225964 | 30 | 2.62156e+09 | 478912 | 1.24443 | 1(Win) |
| glaze | 1547.94 | 1.61761 | 233.443ms | 1225970 | 30 | 4.47841e+09 | 755312 | 1.96268 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1145.49 | 1.89252 | 83.5231ms | 409725 | 30 | 1.25028e+09 | 341116 | 2.65244 | 1(Win) |
| glaze | 893.23 | 1.3305 | 1156.21ms | 409725 | 128 | 4.33611e+09 | 437451 | 3.40143 | 2(Loss) |
| simdjson (ondemand) | 768.181 | 2.35838 | 123.68ms | 409725 | 30 | 4.31723e+09 | 508661 | 3.9553 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3270.27 | 2.16983 | 149.024ms | 409725 | 64 | 4.30177e+08 | 119484 | 0.928824 | 1(Win) |
| glaze | 2879.69 | 2.48193 | 161.267ms | 409725 | 64 | 7.25863e+08 | 135690 | 1.05459 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1542.31 | 2.22501 | 118.072ms | 785750 | 30 | 3.50601e+09 | 485863 | 1.97007 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1419.04 | 1.85024 | 300.633ms | 785750 | 32 | 3.05485e+09 | 528069 | 2.14121 | 2(Tie) |
| glaze STATISTICAL TIE | 1414.08 | 1.77527 | 126.32ms | 785750 | 30 | 2.65502e+09 | 529919 | 2.14862 | 2(Tie) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3815.72 | 2.21572 | 233.076ms | 785750 | 64 | 1.21178e+09 | 196385 | 0.79588 | 1(Tie) |
| glaze STATISTICAL TIE | 3604.33 | 2.24749 | 50.8705ms | 785750 | 30 | 6.54994e+08 | 207903 | 0.842738 | 1(Tie) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1276.03 | 0.965641 | 1542.83ms | 8587914 | 30 | 1.15241e+11 | 6.41842e+06 | 2.3814 | 1(Win) |
| glaze | 1163.69 | 0.651065 | 1754.63ms | 8587914 | 30 | 6.299e+10 | 7.03802e+06 | 2.61142 | 2(Loss) |
| simdjson (ondemand) | 911.771 | 0.853773 | 2235.24ms | 8587914 | 30 | 1.76445e+11 | 8.9826e+06 | 3.33302 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2873.77 | 1.56247 | 782.526ms | 8588126 | 30 | 5.94891e+10 | 2.85001e+06 | 1.0571 | 1(Win) |
| glaze | 2696.85 | 1.90088 | 746.939ms | 8588126 | 30 | 9.99804e+10 | 3.03698e+06 | 1.12652 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1286.93 | 1.17001 | 1841.16ms | 9804437 | 30 | 2.1679e+11 | 7.26555e+06 | 2.36127 | 1(Win) |
| glaze | 1211.43 | 0.800293 | 4579.26ms | 9804437 | 32 | 1.22095e+11 | 7.71835e+06 | 2.50853 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3004.98 | 1.45972 | 879.774ms | 11078090 | 30 | 7.90139e+10 | 3.51579e+06 | 1.01083 | 1(Tie) |
| glaze STATISTICAL TIE | 2973.84 | 1.65844 | 2153.27ms | 11078090 | 32 | 1.11082e+11 | 3.55261e+06 | 1.02164 | 1(Tie) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5494.42 | 2.35069 | 117.269ms | 264040 | 128 | 1.48558e+08 | 45829.8 | 0.552498 | 1(Win) |
| simdjson (ondemand) | 5051.45 | 2.02462 | 29.7901ms | 264040 | 32 | 3.25943e+07 | 49848.7 | 0.601177 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7448.74 | 1.20715 | 13.2365ms | 399947 | 30 | 1.14625e+07 | 51205.8 | 0.407744 | 1(Win) |
| simdjson (ondemand) | 6965.31 | 0.53088 | 14.3788ms | 399947 | 30 | 2.53536e+06 | 54759.9 | 0.436115 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1842.3 | 1.67904 | 34.7081ms | 264040 | 30 | 1.58001e+08 | 136681 | 1.64914 | 1(Win) |
| glaze | 1614.72 | 1.68659 | 843.433ms | 264040 | 256 | 1.77094e+09 | 155946 | 1.88141 | 2(Loss) |
| simdjson (ondemand) | 1346.21 | 2.3348 | 47.9834ms | 264040 | 30 | 5.72183e+08 | 187050 | 2.25699 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6707.01 | 1.00874 | 9.89403ms | 264040 | 30 | 4.30294e+06 | 37544 | 0.452428 | 1(Win) |
| glaze | 4656.8 | 2.33043 | 12.4737ms | 263923 | 30 | 4.75962e+07 | 54049.2 | 0.652291 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2007.66 | 1.92626 | 522.03ms | 399947 | 128 | 1.71421e+09 | 189982 | 1.51316 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1949.37 | 1.9077 | 115.407ms | 399947 | 32 | 4.45846e+08 | 195663 | 1.5587 | 1(Tie) |
| jsonifier | 1706.68 | 2.33237 | 269.595ms | 399947 | 64 | 1.7389e+09 | 223485 | 1.78004 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6266.94 | 2.49815 | 15.7317ms | 399947 | 30 | 6.93513e+07 | 60862.1 | 0.484628 | 1(Win) |
| glaze | 5455.63 | 2.4697 | 85.7496ms | 399830 | 64 | 1.90691e+08 | 69892.5 | 0.556666 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2819.86 | 2.33834 | 38.7553ms | 466906 | 30 | 4.09018e+08 | 157907 | 1.07734 | 1(Win) |
| glaze | 2581.97 | 1.75467 | 213.73ms | 466906 | 64 | 5.86038e+08 | 172456 | 1.17661 | 2(Loss) |
| simdjson (ondemand) | 1275.96 | 1.79484 | 482.594ms | 466906 | 64 | 2.51084e+09 | 348974 | 2.38058 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3809.85 | 2.00704 | 223.018ms | 699405 | 64 | 7.90195e+08 | 175074 | 0.797335 | 1(Win) |
| glaze | 3539.56 | 1.93294 | 161.572ms | 699405 | 32 | 4.24568e+08 | 188443 | 0.858358 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4675.23 | 0.458621 | 77.6605ms | 631514 | 32 | 1.11691e+07 | 128819 | 0.64986 | 1(Win) |
| glaze | 2593.75 | 1.97281 | 55.5932ms | 631514 | 30 | 6.29506e+08 | 232196 | 1.17138 | 2(Loss) |
