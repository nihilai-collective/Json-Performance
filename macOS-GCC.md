# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the GCC 16.1.0 compiler).  

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

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 847.451 | 1.11814 | 44.4439ms | 1811 | 128 | 66467.3 | 2038 | 1(Win) |
| glaze | 646.371 | 2.2367 | 3.82413ms | 1811 | 64 | 228596 | 2672 | 2(Loss) |
| simdjson (ondemand) | 140.278 | 2.144 | 6.87206ms | 1811 | 32 | 2.22974e+06 | 12312 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 521.469 | 1.90047 | 4.56115ms | 1811 | 64 | 253562 | 3312 | 1(Win) |
| glaze | 405.125 | 1.96115 | 1.2032ms | 1798 | 30 | 206702 | 4232.53 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1570.4 | 1.83789 | 6.38592ms | 3873 | 128 | 239181 | 2352 | 1(Win) |
| glaze | 1258.03 | 1.98011 | 3.42195ms | 3873 | 64 | 216308 | 2936 | 2(Loss) |
| simdjson (ondemand) | 363.828 | 0.656414 | 5.95302ms | 3873 | 32 | 142105 | 10152 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2139.97 | 2.35692 | 4.96998ms | 3873 | 128 | 211827 | 1726 | 1(Win) |
| glaze | 1199.01 | 1.56784 | 0.877056ms | 3873 | 30 | 69980.4 | 3080.53 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1638.39 | 2.47816 | 2.97907ms | 3862 | 64 | 198623 | 2248 | 1(Win) |
| glaze | 1273.19 | 2.44297 | 0.772864ms | 3862 | 30 | 149829 | 2892.8 | 2(Loss) |
| simdjson (ondemand) | 356.061 | 0.837938 | 8.54886ms | 3862 | 32 | 240409 | 10344 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1076.93 | 1.88147 | 4.29901ms | 3862 | 64 | 264988 | 3420 | 1(Win) |
| jsonifier | 591.249 | 1.35562 | 2.30195ms | 3862 | 30 | 213934 | 6229.33 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1525.54 | 1.94827 | 25.7838ms | 905 | 2048 | 248816 | 565.75 | 1(Win) |
| glaze | 661.868 | 2.22397 | 6.93018ms | 905 | 256 | 215305 | 1304 | 2(Loss) |
| simdjson (ondemand) | 191.556 | 2.10313 | 1.17811ms | 905 | 30 | 269376 | 4505.6 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 742.111 | 2.04153 | 6.34803ms | 905 | 256 | 144315 | 1163 | 1(Win) |
| glaze | 347.454 | 1.80513 | 6.61402ms | 905 | 128 | 257355 | 2484 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1974.95 | 1.96696 | 1.37984ms | 9578 | 30 | 248284 | 4625.07 | 1(Win) |
| glaze | 1680.42 | 1.97737 | 1.37395ms | 9578 | 30 | 346588 | 5435.73 | 2(Loss) |
| simdjson (ondemand) | 601.025 | 0.48782 | 3.79904ms | 9578 | 30 | 164895 | 15197.9 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3610.39 | 1.78387 | 6.73997ms | 9578 | 128 | 260721 | 2530 | 1(Win) |
| glaze | 2824.34 | 2.35436 | 2.03597ms | 9578 | 30 | 173934 | 3234.13 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3248.04 | 2.27069 | 2.976ms | 33713 | 30 | 1.51561e+06 | 9898.67 | 1(Win) |
| simdjson (ondemand) | 2695.08 | 0.406379 | 3.05715ms | 33713 | 30 | 70507.7 | 11929.6 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4125.37 | 0.524239 | 3.01517ms | 48024 | 30 | 101618 | 11101.9 | 1(Win) |
| simdjson (ondemand) | 3310.98 | 0.521073 | 3.51795ms | 48024 | 30 | 155855 | 13832.5 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1380.35 | 0.370558 | 50.037ms | 294588 | 30 | 1.70641e+07 | 203529 | 1(Win) |
| jsonifier | 1302.07 | 0.60271 | 53.1011ms | 294588 | 30 | 5.07343e+07 | 215765 | 2(Loss) |
| simdjson (ondemand) | 874.768 | 1.03542 | 78.345ms | 294588 | 30 | 3.31738e+08 | 321161 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2652.92 | 0.491928 | 26.1192ms | 294588 | 30 | 8.14153e+06 | 105899 | 1(Win) |
| jsonifier | 2567.48 | 1.47125 | 25.7879ms | 294588 | 30 | 7.77514e+07 | 109423 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1530.06 | 1.8605 | 74.0319ms | 406546 | 30 | 6.66786e+08 | 253397 | 1(Win) |
| jsonifier | 1265.08 | 0.616492 | 177.232ms | 406546 | 32 | 1.14232e+08 | 306472 | 2(Loss) |
| simdjson (ondemand) | 1159.52 | 1.23408 | 506.641ms | 406546 | 64 | 1.08976e+09 | 334372 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3070.77 | 0.595904 | 30.775ms | 406546 | 30 | 1.69824e+07 | 126259 | 1(Win) |
| glaze | 2517.6 | 1.06863 | 37.0068ms | 406546 | 30 | 8.12496e+07 | 154001 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3482.18 | 1.36178 | 2.42586ms | 33713 | 30 | 474270 | 9233.07 | 1(Win) |
| simdjson (ondemand) | 1921.33 | 0.531386 | 4.24986ms | 33713 | 30 | 237210 | 16733.9 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3992.26 | 1.34593 | 6.94093ms | 48024 | 32 | 762913 | 11472 | 1(Win) |
| simdjson (ondemand) | 2466.5 | 0.510888 | 4.61798ms | 48024 | 30 | 269978 | 18568.5 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1341.6 | 0.647626 | 51.8648ms | 294588 | 30 | 5.51768e+07 | 209408 | 1(Win) |
| jsonifier | 943.157 | 2.22245 | 69.994ms | 294588 | 30 | 1.31476e+09 | 297873 | 2(Loss) |
| simdjson (ondemand) | 248.028 | 0.392882 | 285.225ms | 294588 | 30 | 5.9412e+08 | 1.1327e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2739.91 | 1.68083 | 26.8268ms | 294588 | 30 | 8.91097e+07 | 102537 | 1(Win) |
| glaze | 2615.06 | 1.00665 | 67.6198ms | 294588 | 32 | 3.74257e+07 | 107432 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1630.43 | 0.563572 | 57.302ms | 406546 | 30 | 5.38812e+07 | 237798 | 1(Win) |
| jsonifier | 1125.74 | 0.838724 | 82.8759ms | 406546 | 30 | 2.50322e+08 | 344405 | 2(Loss) |
| simdjson (ondemand) | 336.576 | 1.13382 | 276.022ms | 406546 | 30 | 5.1176e+09 | 1.15193e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2944.59 | 0.748573 | 31.6462ms | 406546 | 30 | 2.91447e+07 | 131669 | 1(Win) |
| glaze | 2508.42 | 0.590683 | 37.3581ms | 406546 | 30 | 2.50062e+07 | 154564 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 741.488 | 0.869024 | 29.504ms | 94651 | 30 | 3.35758e+07 | 121737 | 1(Win) |
| jsonifier | 687.513 | 1.58679 | 31.5789ms | 94651 | 30 | 1.30212e+08 | 131294 | 2(Loss) |
| simdjson (ondemand) | 625.551 | 0.576183 | 34.868ms | 94651 | 30 | 2.0738e+07 | 144299 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3880.44 | 1.81542 | 6.16704ms | 94651 | 30 | 5.35015e+06 | 23261.9 | 1(Win) |
| jsonifier | 3134.24 | 0.98831 | 7.14624ms | 94651 | 30 | 2.43048e+06 | 28800 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 944.333 | 0.533021 | 33.301ms | 136024 | 30 | 1.60839e+07 | 137370 | 1(Win) |
| simdjson (ondemand) | 870.818 | 0.534519 | 35.988ms | 136024 | 30 | 1.90206e+07 | 148966 | 2(Loss) |
| jsonifier | 779.995 | 0.471234 | 106.731ms | 136024 | 32 | 1.96549e+07 | 166312 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3434 | 0.567839 | 124.064ms | 136046 | 128 | 5.89156e+06 | 37782 | 1(Win) |
| jsonifier | 3314.84 | 0.171027 | 9.67987ms | 136024 | 30 | 134386 | 39133.9 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 549.231 | 0.326786 | 876.42ms | 2090234 | 30 | 4.22014e+09 | 3.62944e+06 | 1(Win) |
| glaze | 465.249 | 0.171273 | 1035.15ms | 2090234 | 30 | 1.61554e+09 | 4.2846e+06 | 2(Loss) |
| simdjson (ondemand) | 381.574 | 0.823805 | 3245.02ms | 2090234 | 32 | 5.92694e+10 | 5.22415e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1563.17 | 0.49286 | 320.151ms | 2090234 | 30 | 1.18507e+09 | 1.27523e+06 | 1(Win) |
| glaze | 1371.08 | 0.283175 | 361.228ms | 2090234 | 30 | 5.08505e+08 | 1.45389e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1120.4 | 0.308738 | 1420.43ms | 6661897 | 30 | 9.19497e+09 | 5.67055e+06 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1119.12 | 0.276622 | 3664.11ms | 6661897 | 32 | 7.89163e+09 | 5.67704e+06 | 1(Tie) |
| glaze | 1073.91 | 0.534469 | 1492.63ms | 6661897 | 30 | 2.99936e+10 | 5.91605e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3228.5 | 0.374366 | 507.579ms | 6661897 | 30 | 1.6282e+09 | 1.96787e+06 | 1(Win) |
| glaze | 2726.78 | 0.204869 | 617.759ms | 6661897 | 30 | 6.83548e+08 | 2.32996e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1435.83 | 0.371926 | 83.4691ms | 500299 | 30 | 4.58231e+07 | 332297 | 1(Win) |
| glaze | 1138.92 | 0.338311 | 101.15ms | 500299 | 30 | 6.02601e+07 | 418927 | 2(Loss) |
| simdjson (ondemand) | 692.65 | 0.311568 | 166.052ms | 500299 | 30 | 1.38185e+08 | 688836 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1602.68 | 0.537863 | 71.7038ms | 500299 | 30 | 7.69182e+07 | 297702 | 1(Win) |
| glaze | 1536.32 | 1.16916 | 75.532ms | 500299 | 30 | 3.95515e+08 | 310562 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1642.83 | 1.07249 | 205.059ms | 1439562 | 30 | 2.40981e+09 | 835678 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1635.86 | 0.998804 | 201.629ms | 1439562 | 30 | 2.1079e+09 | 839236 | 1(Tie) |
| jsonifier | 1512.6 | 2.38356 | 259.42ms | 1439562 | 30 | 1.40405e+10 | 907622 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3162.08 | 2.35325 | 93.438ms | 1439562 | 30 | 3.13163e+09 | 434167 | 1(Win) |
| glaze | 2219.96 | 1.69064 | 331.142ms | 1439584 | 32 | 3.49812e+09 | 618432 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1290.02 | 0.714022 | 53.1651ms | 56369 | 64 | 5.6662e+06 | 41672 | 1(Win) |
| glaze | 1167.05 | 0.152919 | 11.606ms | 56369 | 30 | 148850 | 46062.9 | 2(Loss) |
| simdjson (ondemand) | 777.936 | 0.51692 | 16.9851ms | 56369 | 30 | 3.82791e+06 | 69102.9 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2514.86 | 2.01276 | 12.961ms | 56369 | 32 | 5.92361e+06 | 21376 | 1(Win) |
| jsonifier | 1981.05 | 1.36898 | 6.6921ms | 56369 | 30 | 4.14007e+06 | 27136 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1478.78 | 1.72032 | 14.8168ms | 94370 | 30 | 3.28852e+07 | 60859.7 | 1(Win) |
| jsonifier STATISTICAL TIE | 1219.75 | 0.907679 | 119.443ms | 94370 | 64 | 2.87057e+07 | 73784 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1196.72 | 0.735123 | 18.284ms | 94370 | 30 | 9.16909e+06 | 75204.3 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2890.29 | 2.06845 | 7.5351ms | 94370 | 30 | 1.2445e+07 | 31138.1 | 1(Win) |
| glaze | 2625.51 | 0.98347 | 8.59802ms | 94370 | 30 | 3.40945e+06 | 34278.4 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1140.48 | 2.06684 | 12.554ms | 52708 | 30 | 2.4895e+07 | 44074.7 | 1(Win) |
| glaze | 1042.21 | 0.960215 | 12.074ms | 52708 | 30 | 6.43428e+06 | 48230.4 | 2(Loss) |
| simdjson (ondemand) | 995.924 | 1.27214 | 30.6412ms | 52708 | 32 | 1.31922e+07 | 50472 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3757.94 | 1.37228 | 8.56781ms | 52708 | 32 | 1.07817e+06 | 13376 | 1(Win) |
| glaze | 2629.26 | 1.61204 | 50.2528ms | 52708 | 128 | 1.21576e+07 | 19118 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1295.62 | 1.5583 | 12.705ms | 70103 | 30 | 1.93972e+07 | 51601.1 | 1(Tie) |
| glaze STATISTICAL TIE | 1265.05 | 0.828219 | 38.302ms | 70103 | 32 | 6.13052e+06 | 52848 | 1(Tie) |
| jsonifier | 1044.2 | 0.343126 | 18.722ms | 70103 | 30 | 1.44789e+06 | 64025.6 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3799.53 | 0.544522 | 4.64384ms | 70103 | 30 | 275402 | 17595.7 | 1(Win) |
| glaze | 3319.75 | 0.401214 | 5.33581ms | 70103 | 30 | 195855 | 20138.7 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 944.273 | 0.406379 | 4.57088ms | 11812 | 30 | 70507.7 | 11929.6 | 1(Win) |
| glaze | 702.551 | 0.516269 | 4.06298ms | 11812 | 30 | 205572 | 16034.1 | 2(Loss) |
| simdjson (ondemand) | 534.884 | 1.15382 | 5.24979ms | 11812 | 30 | 1.77143e+06 | 21060.3 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4241.27 | 2.34666 | 3.39994ms | 11812 | 64 | 248621 | 2656 | 1(Win) |
| glaze | 1594.32 | 0.769085 | 1.92179ms | 11812 | 30 | 88586.6 | 7065.6 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1380.85 | 0.492535 | 5.43821ms | 31235 | 30 | 338678 | 21572.3 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1374.87 | 1.07711 | 5.76102ms | 31235 | 30 | 1.6338e+06 | 21666.1 | 1(Tie) |
| simdjson (ondemand) | 1283.85 | 0.301507 | 5.74797ms | 31235 | 30 | 146816 | 23202.1 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3757.57 | 2.14253 | 2.04288ms | 31235 | 30 | 865452 | 7927.47 | 1(Win) |
| glaze | 2289.04 | 1.83401 | 3.3792ms | 31235 | 30 | 1.70883e+06 | 13013.3 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2578.26 | 1.27124 | 10.774ms | 108313 | 30 | 7.78184e+06 | 40064 | 1(Win) |
| glaze | 1190.96 | 0.939727 | 21.1379ms | 108313 | 30 | 1.99293e+07 | 86732.8 | 2(Loss) |
| simdjson (ondemand) | 997.768 | 0.75 | 25.185ms | 108313 | 30 | 1.80861e+07 | 103526 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1939.27 | 0.537435 | 13.1269ms | 108313 | 30 | 2.45843e+06 | 53265.1 | 1(Win) |
| glaze | 1540.2 | 0.915424 | 457.201ms | 108313 | 256 | 9.64916e+07 | 67066 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1885.38 | 1.54496 | 26.9ms | 213963 | 30 | 8.38756e+07 | 108228 | 1(Win) |
| glaze | 1726.02 | 1.13661 | 28.7841ms | 213963 | 30 | 5.41662e+07 | 118221 | 2(Loss) |
| simdjson (ondemand) | 1638.16 | 1.09777 | 31.6669ms | 213963 | 30 | 5.60929e+07 | 124561 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2858.95 | 0.713516 | 19.9631ms | 213963 | 30 | 7.78025e+06 | 71372.8 | 1(Win) |
| glaze | 1851.34 | 0.457725 | 295.872ms | 213963 | 128 | 3.2578e+07 | 110218 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 564.741 | 0.109143 | 753.898ms | 1834197 | 30 | 3.4285e+08 | 3.0974e+06 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 369.772 | 0.166057 | 1148.81ms | 1834197 | 30 | 1.85124e+09 | 4.73056e+06 | 2(Tie) |
| glaze STATISTICAL TIE | 368.258 | 0.509249 | 1147.07ms | 1834197 | 30 | 1.75537e+10 | 4.75e+06 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 682.892 | 2.07017 | 1375.93ms | 1833577 | 32 | 8.99204e+10 | 2.56063e+06 | 1(Win) |
| jsonifier | 609.078 | 0.51033 | 717.125ms | 1834197 | 30 | 6.44421e+09 | 2.87193e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1693.67 | 0.36383 | 1354.43ms | 9930848 | 30 | 1.24175e+10 | 5.59189e+06 | 1(Win) |
| simdjson (ondemand) | 1627.62 | 0.222919 | 3320.36ms | 9930848 | 32 | 5.38409e+09 | 5.81881e+06 | 2(Loss) |
| jsonifier | 1553.54 | 0.76367 | 1557.68ms | 9930848 | 30 | 6.50218e+10 | 6.09626e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2357.93 | 0.455893 | 1023.2ms | 9930848 | 30 | 1.00591e+10 | 4.01657e+06 | 1(Win) |
| glaze | 1996.14 | 0.390804 | 1220.32ms | 9930228 | 30 | 1.03128e+10 | 4.74426e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1025.07 | 0.302223 | 144.778ms | 642697 | 30 | 9.79665e+07 | 597931 | 1(Win) |
| glaze | 834.664 | 0.417795 | 178.057ms | 642697 | 30 | 2.82382e+08 | 734336 | 2(Loss) |
| simdjson (ondemand) | 631.329 | 0.669356 | 231.011ms | 642697 | 30 | 1.26688e+09 | 970846 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 963.254 | 0.375082 | 158.657ms | 642697 | 30 | 1.70885e+08 | 636305 | 1(Win) |
| glaze | 946.504 | 0.282537 | 156.055ms | 642692 | 30 | 1.00423e+08 | 647561 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1279.28 | 0.421757 | 219.525ms | 1225964 | 30 | 4.45728e+08 | 913929 | 1(Win) |
| jsonifier | 1209.08 | 0.268768 | 240.066ms | 1225964 | 30 | 2.02638e+08 | 966989 | 2(Loss) |
| simdjson (ondemand) | 1085.18 | 0.957662 | 1505.58ms | 1225964 | 64 | 6.81331e+09 | 1.0774e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1936.57 | 1.32932 | 142.272ms | 1225964 | 30 | 1.9323e+09 | 603733 | 1(Win) |
| glaze | 1182.64 | 1.95038 | 1162.44ms | 1225970 | 64 | 2.37944e+10 | 988616 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 664.533 | 1.12606 | 140.153ms | 409725 | 30 | 1.31522e+09 | 587998 | 1(Win) |
| glaze | 515.628 | 0.641664 | 184.449ms | 409725 | 30 | 7.0933e+08 | 757803 | 2(Loss) |
| simdjson (ondemand) | 501.839 | 0.224203 | 188.282ms | 409725 | 30 | 9.14238e+07 | 778624 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3284.58 | 0.859666 | 28.684ms | 409725 | 30 | 3.13766e+07 | 118963 | 1(Win) |
| glaze | 1802.63 | 0.428519 | 52.447ms | 409725 | 30 | 2.58842e+07 | 216764 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 904.073 | 0.197638 | 199.276ms | 785750 | 30 | 8.0505e+07 | 828860 | 1(Win) |
| jsonifier | 880.857 | 0.466854 | 213.191ms | 785750 | 30 | 4.73197e+08 | 850705 | 2(Loss) |
| glaze | 868.3 | 0.452736 | 1149.92ms | 785750 | 64 | 9.77012e+08 | 863008 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2602.91 | 0.432275 | 70.4589ms | 785750 | 30 | 4.64613e+07 | 287889 | 1(Win) |
| glaze | 2125.85 | 0.633169 | 83.714ms | 785750 | 30 | 1.4944e+08 | 352495 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 890.116 | 0.688446 | 2204.09ms | 8587914 | 30 | 1.20377e+11 | 9.20113e+06 | 1(Win) |
| simdjson (ondemand) | 762.635 | 1.41693 | 2574.86ms | 8587914 | 30 | 6.94643e+11 | 1.07392e+07 | 2(Loss) |
| glaze | 646.16 | 2.40124 | 2846.26ms | 8587914 | 30 | 2.77901e+12 | 1.2675e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2794.39 | 1.12448 | 1677.23ms | 8588126 | 32 | 3.47598e+10 | 2.93097e+06 | 1(Win) |
| glaze | 2673.03 | 0.739192 | 1915.42ms | 8588126 | 32 | 1.64155e+10 | 3.06404e+06 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 885.392 | 0.29719 | 2580.81ms | 9804437 | 30 | 2.95504e+10 | 1.05606e+07 | 1(Win) |
| jsonifier | 844.809 | 0.282504 | 3000.56ms | 9804437 | 30 | 2.93291e+10 | 1.10679e+07 | 2(Loss) |
| glaze | 795.939 | 1.4816 | 2757.18ms | 9804437 | 30 | 9.08807e+11 | 1.17474e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2835.92 | 0.460022 | 4783.44ms | 11078090 | 64 | 1.87966e+10 | 3.72538e+06 | 1(Tie) |
| glaze STATISTICAL TIE | 2808.58 | 0.893496 | 940.678ms | 11078090 | 30 | 3.38893e+10 | 3.76165e+06 | 1(Tie) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3239.16 | 0.559865 | 20.2332ms | 264040 | 30 | 5.6828e+06 | 77738.7 | 1(Win) |
| simdjson (ondemand) | 2733.05 | 0.748337 | 22.3831ms | 264040 | 30 | 1.42613e+07 | 92134.4 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3884.04 | 0.771972 | 25.1602ms | 399947 | 30 | 1.72409e+07 | 98201.6 | 1(Win) |
| simdjson (ondemand) | 3083.44 | 1.66734 | 27.9831ms | 399947 | 30 | 1.27616e+08 | 123699 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1516.38 | 0.899744 | 42.1908ms | 264040 | 30 | 6.69703e+07 | 166059 | 1(Win) |
| simdjson (ondemand) | 1084.76 | 0.534982 | 57.0061ms | 264040 | 30 | 4.6267e+07 | 232132 | 2(Loss) |
| glaze | 970.662 | 0.2871 | 1588.96ms | 264040 | 256 | 1.42007e+08 | 259419 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2834.38 | 0.636512 | 21.696ms | 264040 | 30 | 9.59304e+06 | 88840.5 | 1(Win) |
| glaze | 2700.72 | 1.94691 | 110.886ms | 263923 | 64 | 2.107e+08 | 93196 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1511.58 | 0.566407 | 61.1702ms | 399947 | 30 | 6.12799e+07 | 252331 | 1(Win) |
| glaze | 1433.21 | 0.465065 | 64.47ms | 399947 | 30 | 4.59551e+07 | 266129 | 2(Loss) |
| jsonifier | 1301.31 | 0.552323 | 182.895ms | 399947 | 32 | 8.38647e+07 | 293104 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3818.02 | 0.242231 | 25.3811ms | 399947 | 30 | 1.75674e+06 | 99899.7 | 1(Win) |
| glaze | 3242.63 | 0.875546 | 70.1658ms | 399830 | 32 | 3.39206e+07 | 117592 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1563.5 | 0.341203 | 743.499ms | 466906 | 128 | 1.20864e+08 | 284794 | 1(Win) |
| jsonifier | 1414.84 | 1.0972 | 76.735ms | 466906 | 30 | 3.57711e+08 | 314718 | 2(Loss) |
| simdjson (ondemand) | 780.975 | 0.53235 | 141.859ms | 466906 | 30 | 2.76377e+08 | 570155 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2127.1 | 0.493565 | 75.66ms | 699405 | 30 | 7.18607e+07 | 313574 | 1(Win) |
| jsonifier | 2071.41 | 0.421169 | 77.95ms | 699405 | 30 | 5.51772e+07 | 322005 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2518.19 | 0.448842 | 58.1051ms | 631514 | 30 | 3.45699e+07 | 239164 | 1(Win) |
| glaze | 1779.56 | 0.408398 | 81.9141ms | 631514 | 30 | 5.73101e+07 | 338432 | 2(Loss) |
