# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.33.2-microsoft-standard-WSL2 using the GCC 16.1.0 compiler).  

Latest Results: (Sep 11, 2026)
#### Using the following commits:
----
| Jsonifier: [9a2d193](https://github.com/nihilai-collective/jsonifier/commit/9a2d193)  
| Glaze: [565edc9](https://github.com/stephenberry/glaze/commit/565edc9)  
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

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1142.54 | 0.199434 | 1.55361ms | 1811 | 30 | 272.654 | 1511.63 | 2.62049 | 1(Win) |
| glaze | 868.241 | 0.181583 | 0.774243ms | 1811 | 30 | 391.407 | 1989.2 | 3.46059 | 2(Loss) |
| simdjson (ondemand) | 236.776 | 2.0129 | 2.05001ms | 1811 | 30 | 646741 | 7294.27 | 12.7916 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 643.194 | 0.286731 | 1.01926ms | 1811 | 30 | 1778.37 | 2685.2 | 4.66875 | 1(Win) |
| glaze | 400.657 | 0.14811 | 1.33107ms | 1798 | 30 | 1205.37 | 4279.73 | 7.50523 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2034.16 | 0.310745 | 5.59651ms | 3873 | 128 | 4075.16 | 1815.78 | 1.47063 | 1(Win) |
| glaze | 1862.15 | 0.0630228 | 0.800393ms | 3873 | 30 | 46.8793 | 1983.5 | 1.60996 | 2(Loss) |
| simdjson (ondemand) | 454.634 | 0.420107 | 2.28916ms | 3873 | 30 | 34947.3 | 8124.3 | 6.66688 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3072.1 | 0.104308 | 0.661671ms | 3873 | 30 | 47.1828 | 1202.3 | 0.963224 | 1(Win) |
| glaze | 1410.8 | 0.16229 | 1.04321ms | 3873 | 30 | 541.582 | 2618.07 | 2.13371 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2068.73 | 0.053759 | 0.816324ms | 3862 | 30 | 27.4816 | 1780.37 | 1.44717 | 1(Win) |
| glaze | 1664.3 | 0.0785963 | 0.869958ms | 3862 | 30 | 90.7586 | 2213 | 1.81 | 2(Loss) |
| simdjson (ondemand) | 473.028 | 0.553504 | 2.1982ms | 3862 | 30 | 55720.4 | 7786.2 | 6.4037 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2891.12 | 0.21777 | 0.712474ms | 3862 | 30 | 230.892 | 1273.93 | 1.02418 | 1(Win) |
| glaze | 1440.96 | 0.0972725 | 1.11984ms | 3862 | 30 | 185.448 | 2556 | 2.07562 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1810.14 | 1.4773 | 0.562913ms | 905 | 30 | 1488.44 | 476.8 | 1.61079 | 1(Win) |
| glaze | 631.996 | 0.0362295 | 0.630092ms | 905 | 30 | 7.34368 | 1365.63 | 4.74232 | 2(Loss) |
| simdjson (ondemand) | 191.545 | 0.083656 | 1.34118ms | 905 | 30 | 426.257 | 4505.87 | 15.7932 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1715.29 | 0.189882 | 0.464356ms | 905 | 30 | 27.3851 | 503.167 | 1.70626 | 1(Win) |
| glaze | 348.548 | 0.140409 | 0.954935ms | 905 | 30 | 362.648 | 2476.2 | 8.64052 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3691.07 | 0.0308263 | 1.07748ms | 9578 | 30 | 17.4586 | 2474.7 | 0.81233 | 1(Win) |
| glaze | 2917.09 | 0.126888 | 1.08524ms | 9578 | 30 | 473.597 | 3131.3 | 1.0339 | 2(Loss) |
| simdjson (ondemand) | 1436.19 | 0.0890899 | 1.8902ms | 9578 | 30 | 963.168 | 6360.07 | 2.10887 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5825.69 | 0.104146 | 0.673063ms | 9578 | 30 | 79.9954 | 1567.93 | 0.510521 | 1(Win) |
| glaze | 3014.09 | 0.160338 | 1.04538ms | 9578 | 30 | 708.326 | 3030.53 | 0.996301 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5677.71 | 0.541467 | 10.0766ms | 233995 | 30 | 1.35873e+06 | 39303.7 | 0.534954 | 1(Win) |
| simdjson (ondemand) | 4278.99 | 0.478376 | 12.9487ms | 233995 | 30 | 1.8672e+06 | 52151.3 | 0.709911 | 2(Loss) |
| glaze | 2049.97 | 2.08826 | 26.0248ms | 233995 | 30 | 1.55028e+08 | 108858 | 1.48202 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7152.79 | 0.923792 | 11.5521ms | 346753 | 30 | 5.47217e+06 | 46232.2 | 0.424633 | 1(Win) |
| simdjson (ondemand) | 5281.33 | 1.69923 | 14.9401ms | 346753 | 30 | 3.3961e+07 | 62614.8 | 0.575181 | 2(Loss) |
| glaze | 2673.12 | 0.428494 | 29.6309ms | 346753 | 30 | 8.42975e+06 | 123709 | 1.13672 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1920.89 | 0.8187 | 29.645ms | 233995 | 30 | 2.71382e+07 | 116173 | 1.58186 | 1(Win) |
| glaze | 1757.08 | 1.20126 | 31.797ms | 233995 | 30 | 6.98268e+07 | 127003 | 1.72935 | 2(Loss) |
| simdjson (ondemand) | 1656.21 | 0.487917 | 33.3726ms | 233995 | 30 | 1.29657e+07 | 134738 | 1.83469 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4723.57 | 0.342922 | 12.0489ms | 233995 | 30 | 787381 | 47242.9 | 0.642664 | 1(Win) |
| glaze | 4268.39 | 0.257625 | 13.8254ms | 233995 | 30 | 544229 | 52280.8 | 0.711663 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2292.59 | 0.944656 | 35.4886ms | 346753 | 30 | 5.57001e+07 | 144243 | 1.32542 | 1(Win) |
| glaze | 2074.4 | 1.37813 | 92.0574ms | 346753 | 32 | 1.54448e+08 | 159414 | 1.46478 | 2(Loss) |
| jsonifier | 1810.6 | 0.568245 | 45.3789ms | 346753 | 30 | 3.23138e+07 | 182641 | 1.67833 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4646.66 | 0.593527 | 18.4923ms | 346753 | 30 | 5.35255e+06 | 71167.2 | 0.653351 | 1(Win) |
| glaze | 4380.09 | 0.648712 | 19.4878ms | 346753 | 30 | 7.19615e+06 | 75498.4 | 0.693558 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5483 | 0.202935 | 10.4527ms | 233995 | 30 | 204650 | 40699.4 | 0.553975 | 1(Win) |
| simdjson (ondemand) | 3211.73 | 1.61115 | 17.383ms | 233995 | 30 | 3.7595e+07 | 69481.3 | 0.945487 | 2(Loss) |
| glaze | 2128.86 | 0.51382 | 25.3715ms | 233995 | 30 | 8.70289e+06 | 104824 | 1.4272 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6513.56 | 2.49305 | 12.2885ms | 346753 | 30 | 4.80603e+07 | 50769.4 | 0.466193 | 1(Win) |
| simdjson (ondemand) | 4325.5 | 0.722516 | 19.6884ms | 346753 | 30 | 9.15347e+06 | 76451.2 | 0.702375 | 2(Loss) |
| glaze | 2733.26 | 0.655433 | 29.6374ms | 346753 | 30 | 1.8865e+07 | 120987 | 1.11171 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1898.13 | 0.566194 | 29.5577ms | 233995 | 30 | 1.32927e+07 | 117566 | 1.60082 | 1(Win) |
| jsonifier | 1637.42 | 0.85628 | 33.5199ms | 233995 | 30 | 4.0855e+07 | 136284 | 1.8554 | 2(Loss) |
| simdjson (ondemand) | 234.813 | 0.588165 | 227.939ms | 233995 | 30 | 9.37318e+08 | 950350 | 12.9425 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4844.36 | 0.334794 | 12.2383ms | 233995 | 30 | 713537 | 46064.9 | 0.626425 | 1(Win) |
| glaze | 4329.73 | 0.643972 | 13.7076ms | 233995 | 30 | 3.30482e+06 | 51540.2 | 0.701453 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2165.22 | 0.32369 | 38.4727ms | 346753 | 30 | 7.33193e+06 | 152728 | 1.40336 | 1(Win) |
| jsonifier | 1784.61 | 0.43017 | 45.1639ms | 346753 | 30 | 1.90614e+07 | 185300 | 1.70279 | 2(Loss) |
| simdjson (ondemand) | 339.694 | 0.696656 | 231.589ms | 346753 | 30 | 1.37982e+09 | 973492 | 8.94563 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5553.98 | 0.707349 | 75.5159ms | 346753 | 64 | 1.13522e+07 | 59540.9 | 0.546547 | 1(Win) |
| glaze | 4228.91 | 0.919981 | 18.9423ms | 346753 | 30 | 1.55261e+07 | 78197.3 | 0.718358 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1307.83 | 0.554254 | 17.5501ms | 94651 | 30 | 4.39024e+06 | 69020 | 2.32293 | 1(Win) |
| simdjson (ondemand) | 1242.55 | 0.832077 | 18.1149ms | 94651 | 30 | 1.09615e+07 | 72645.8 | 2.44503 | 2(Loss) |
| jsonifier | 1217.47 | 0.360822 | 18.9404ms | 94651 | 30 | 2.14704e+06 | 74142.4 | 2.49553 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 5715.79 | 0.937766 | 4.07837ms | 94651 | 30 | 657974 | 15792.4 | 0.530712 | 1(Win) |
| jsonifier | 5560.31 | 0.833851 | 4.37347ms | 94651 | 30 | 549732 | 16234 | 0.544292 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1691.83 | 0.448245 | 19.228ms | 136024 | 30 | 3.54379e+06 | 76675.7 | 1.79579 | 1(Win) |
| glaze | 1542.3 | 0.623872 | 21.3222ms | 136024 | 30 | 8.26055e+06 | 84110.1 | 1.96988 | 2(Loss) |
| jsonifier | 1328.81 | 0.650075 | 23.7764ms | 136024 | 30 | 1.20824e+07 | 97623.2 | 2.28647 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6903.48 | 0.0591312 | 5.34086ms | 136024 | 30 | 3703.82 | 18790.9 | 0.438861 | 1(Win) |
| glaze | 5638.56 | 0.365766 | 6.31981ms | 136046 | 30 | 212502 | 23010.1 | 0.538279 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 858.533 | 0.347273 | 555.646ms | 2090234 | 30 | 1.95047e+09 | 2.32187e+06 | 3.53943 | 1(Win) |
| simdjson (ondemand) | 745.119 | 0.764732 | 641.796ms | 2090234 | 30 | 1.25568e+10 | 2.67528e+06 | 4.07815 | 2(Loss) |
| glaze | 697.305 | 0.52617 | 682.274ms | 2090234 | 30 | 6.78764e+09 | 2.85872e+06 | 4.35798 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1524.64 | 1.43928 | 313.784ms | 2090234 | 30 | 1.06234e+10 | 1.30746e+06 | 1.99277 | 1(Win) |
| glaze | 1362.99 | 0.285399 | 352.453ms | 2090234 | 30 | 5.22677e+08 | 1.46253e+06 | 2.22925 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2211.34 | 0.299621 | 701.747ms | 6661897 | 30 | 2.22304e+09 | 2.87304e+06 | 1.37416 | 1(Win) |
| jsonifier | 1893.31 | 0.222012 | 809.773ms | 6661897 | 30 | 1.66505e+09 | 3.35565e+06 | 1.60495 | 2(Loss) |
| glaze | 1714.21 | 0.805691 | 884.731ms | 6661897 | 30 | 2.67501e+10 | 3.70624e+06 | 1.77267 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3511.73 | 0.24405 | 435.508ms | 6661897 | 30 | 5.84834e+08 | 1.80916e+06 | 0.865172 | 1(Win) |
| glaze | 3000.92 | 0.697084 | 522.574ms | 6661897 | 30 | 6.53399e+09 | 2.11711e+06 | 1.01244 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1756.17 | 1.18937 | 154.284ms | 500299 | 32 | 3.34128e+08 | 271684 | 1.73019 | 1(Win) |
| jsonifier | 1706.55 | 0.70834 | 66.8999ms | 500299 | 30 | 1.17659e+08 | 279583 | 1.78054 | 2(Loss) |
| simdjson (ondemand) | 1096.77 | 0.341 | 104.92ms | 500299 | 30 | 6.60171e+07 | 435025 | 2.7708 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5386.6 | 1.91355 | 20.9705ms | 500299 | 30 | 8.61845e+07 | 88575.8 | 0.563717 | 1(Tie) |
| glaze STATISTICAL TIE | 5378.97 | 0.408571 | 22.4088ms | 500299 | 30 | 3.94021e+06 | 88701.5 | 0.564823 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2783.79 | 0.426496 | 119.374ms | 1439562 | 30 | 1.3272e+08 | 493166 | 1.09163 | 1(Tie) |
| glaze STATISTICAL TIE | 2755.02 | 0.615449 | 120.29ms | 1439562 | 30 | 2.82174e+08 | 498317 | 1.10283 | 1(Tie) |
| jsonifier | 2535.71 | 0.290336 | 132.984ms | 1439562 | 30 | 7.41284e+07 | 541416 | 1.19843 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7043.08 | 1.21169 | 48.2299ms | 1439562 | 30 | 1.67355e+08 | 194925 | 0.43109 | 1(Win) |
| glaze | 5030.83 | 0.66009 | 67.2464ms | 1439584 | 30 | 9.73472e+07 | 272896 | 0.603825 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1853.33 | 0.362173 | 7.5406ms | 56369 | 30 | 331077 | 29006 | 1.63838 | 1(Win) |
| jsonifier | 1737.61 | 0.0689223 | 8.12672ms | 56369 | 30 | 13640.1 | 30937.7 | 1.74775 | 2(Loss) |
| simdjson (ondemand) | 1261.62 | 0.875962 | 10.8723ms | 56369 | 30 | 4.17945e+06 | 42610.2 | 2.40761 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6536.71 | 0.325109 | 2.38573ms | 56369 | 30 | 21445.8 | 8223.97 | 0.463278 | 1(Win) |
| jsonifier | 5599.52 | 0.228791 | 2.71592ms | 56369 | 30 | 14473.7 | 9600.4 | 0.538938 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2334.73 | 1.02751 | 9.81661ms | 94370 | 30 | 4.70643e+06 | 38547.6 | 1.30071 | 1(Win) |
| simdjson (ondemand) | 2020.35 | 0.904527 | 11.1312ms | 94370 | 30 | 4.87056e+06 | 44545.8 | 1.50333 | 2(Loss) |
| jsonifier | 1681.82 | 0.5494 | 31.4387ms | 94370 | 32 | 2.76589e+06 | 53512.3 | 1.80587 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7208.12 | 1.82719 | 3.35819ms | 94370 | 30 | 1.56139e+06 | 12485.7 | 0.419845 | 1(Win) |
| glaze | 5633.92 | 0.146817 | 4.6915ms | 94370 | 30 | 16501.3 | 15974.4 | 0.538433 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1788.44 | 1.26623 | 7.50105ms | 52708 | 30 | 3.7997e+06 | 28106.3 | 1.69739 | 1(Win) |
| jsonifier | 1549.85 | 0.781531 | 8.82875ms | 52708 | 30 | 1.92746e+06 | 32432.9 | 1.95921 | 2(Loss) |
| glaze | 1329.34 | 1.04711 | 9.93071ms | 52708 | 30 | 4.70318e+06 | 37813 | 2.28433 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 6345.98 | 0.367404 | 2.44464ms | 52708 | 30 | 25407.8 | 7920.97 | 0.477289 | 1(Tie) |
| glaze STATISTICAL TIE | 6197.05 | 2.03334 | 10.1735ms | 52708 | 64 | 1.74094e+06 | 8111.33 | 0.488499 | 1(Tie) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2127.83 | 0.590276 | 8.62363ms | 70103 | 30 | 1.03188e+06 | 31419.5 | 1.42712 | 1(Win) |
| glaze | 1575.32 | 0.76219 | 11.0607ms | 70103 | 30 | 3.13893e+06 | 42439.2 | 1.92767 | 2(Loss) |
| jsonifier | 1365.87 | 0.747586 | 12.7577ms | 70103 | 30 | 4.01698e+06 | 48947.2 | 2.22376 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6729.96 | 1.5059 | 6.10906ms | 70103 | 32 | 716126 | 9934 | 0.449976 | 1(Win) |
| glaze | 6307.97 | 0.619602 | 3.07433ms | 70103 | 30 | 129372 | 10598.6 | 0.480633 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1366.74 | 0.112992 | 5.34205ms | 11812 | 32 | 2775.4 | 8242.12 | 2.21685 | 1(Win) |
| jsonifier | 1361.18 | 0.0702746 | 2.4812ms | 11812 | 30 | 1014.69 | 8275.73 | 2.22579 | 2(Loss) |
| simdjson (ondemand) | 1078.25 | 0.113048 | 2.88173ms | 11812 | 30 | 4184.63 | 10447.3 | 2.81195 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6076.05 | 0.166751 | 0.762396ms | 11812 | 30 | 286.723 | 1853.97 | 0.488653 | 1(Win) |
| glaze | 4448.45 | 0.339752 | 0.957726ms | 11812 | 30 | 2220.63 | 2532.3 | 0.673479 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2662.24 | 0.123935 | 7.03701ms | 31235 | 32 | 6153.57 | 11189.1 | 1.1388 | 1(Win) |
| glaze | 2273.56 | 0.409797 | 3.62826ms | 31235 | 30 | 86482.8 | 13101.9 | 1.33436 | 2(Loss) |
| jsonifier | 2073.33 | 0.0705261 | 4.06156ms | 31235 | 30 | 3080.13 | 14367.3 | 1.46333 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7538.66 | 0.333753 | 1.34178ms | 31235 | 30 | 5217.55 | 3951.37 | 0.39605 | 1(Win) |
| glaze | 5141.78 | 0.507546 | 1.50559ms | 31235 | 30 | 25937.6 | 5793.33 | 0.587437 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3159.92 | 1.0457 | 8.31222ms | 108313 | 30 | 3.50543e+06 | 32689.2 | 0.960908 | 1(Win) |
| glaze | 2128.39 | 0.837489 | 12.1279ms | 108313 | 30 | 4.9561e+06 | 48532.2 | 1.42712 | 2(Loss) |
| simdjson (ondemand) | 1641.81 | 0.460203 | 15.531ms | 108313 | 30 | 2.51498e+06 | 62915.4 | 1.8503 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6184.32 | 1.5613 | 9.63851ms | 108313 | 32 | 2.17619e+06 | 16702.8 | 0.489371 | 1(Win) |
| glaze | 5263.45 | 1.58314 | 11.5715ms | 108313 | 32 | 3.08894e+06 | 19625 | 0.576228 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2919.26 | 0.606484 | 17.0267ms | 213963 | 30 | 5.39129e+06 | 69898.2 | 1.04062 | 1(Win) |
| glaze | 2754.04 | 2.47052 | 17.998ms | 213963 | 30 | 1.00516e+08 | 74091.5 | 1.10311 | 2(Loss) |
| jsonifier | 2048.24 | 0.840763 | 24.7679ms | 213963 | 30 | 2.10468e+07 | 99622.8 | 1.48325 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6483.42 | 0.557367 | 8.10869ms | 213963 | 30 | 923152 | 31472.7 | 0.466794 | 1(Win) |
| glaze | 5267.77 | 2.03024 | 9.64166ms | 213963 | 30 | 1.8554e+07 | 38735.8 | 0.576474 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 786.039 | 0.662018 | 540.978ms | 1834197 | 30 | 6.51125e+09 | 2.22537e+06 | 3.86584 | 1(Win) |
| glaze | 597.81 | 0.441505 | 706.316ms | 1834197 | 30 | 5.00676e+09 | 2.92606e+06 | 5.0833 | 2(Loss) |
| simdjson (ondemand) | 589.58 | 0.245363 | 711.214ms | 1834197 | 30 | 1.58982e+09 | 2.9669e+06 | 5.15416 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 971.949 | 0.666618 | 1008.79ms | 1834197 | 32 | 4.60585e+09 | 1.79971e+06 | 3.12607 | 1(Win) |
| glaze | 896.334 | 0.635393 | 463.436ms | 1833577 | 30 | 4.60962e+09 | 1.95087e+06 | 3.39003 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2546.9 | 0.721129 | 902.336ms | 9930848 | 30 | 2.15723e+10 | 3.71856e+06 | 1.19289 | 1(Win) |
| glaze | 2324.7 | 0.352235 | 966.594ms | 9930848 | 30 | 6.17764e+09 | 4.07398e+06 | 1.30703 | 2(Loss) |
| jsonifier | 2167.28 | 0.365964 | 1058.02ms | 9930848 | 30 | 7.67256e+09 | 4.36989e+06 | 1.40211 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3181.5 | 0.694604 | 751.52ms | 9930848 | 30 | 1.28264e+10 | 2.97683e+06 | 0.955033 | 1(Win) |
| glaze | 2076.02 | 0.689308 | 1089.68ms | 9930228 | 30 | 2.96621e+10 | 4.56171e+06 | 1.46341 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1327.18 | 0.739044 | 111.353ms | 642697 | 30 | 3.49474e+08 | 461824 | 2.28973 | 1(Win) |
| simdjson (ondemand) | 1191.72 | 0.383361 | 124.618ms | 642697 | 30 | 1.16628e+08 | 514319 | 2.54988 | 2(Loss) |
| glaze | 1040.97 | 0.46306 | 143.664ms | 642697 | 30 | 2.23015e+08 | 588801 | 2.91916 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1679.1 | 0.396598 | 87.8871ms | 642697 | 30 | 6.2876e+07 | 365032 | 1.80965 | 1(Win) |
| glaze | 1428.41 | 0.474963 | 103.974ms | 642692 | 30 | 1.24606e+08 | 429092 | 2.12701 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2157.16 | 1.21087 | 129.225ms | 1225964 | 30 | 1.29215e+09 | 541996 | 1.40832 | 1(Win) |
| glaze | 1761.96 | 0.496587 | 160.318ms | 1225964 | 30 | 3.25742e+08 | 663562 | 1.72467 | 2(Loss) |
| jsonifier | 1363.12 | 0.975814 | 202.348ms | 1225964 | 30 | 2.10157e+09 | 857718 | 2.22887 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2702.02 | 0.366625 | 105.188ms | 1225964 | 30 | 7.54995e+07 | 432703 | 1.12436 | 1(Win) |
| glaze | 2147.11 | 0.353188 | 131.984ms | 1225970 | 30 | 1.10964e+08 | 544534 | 1.41508 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 977.076 | 0.774859 | 96.4737ms | 409725 | 30 | 2.88068e+08 | 399912 | 3.10973 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 950.242 | 1.3111 | 97.2546ms | 409725 | 30 | 8.7198e+08 | 411205 | 3.19717 | 1(Tie) |
| glaze | 921.516 | 0.562208 | 103.182ms | 409725 | 30 | 1.70489e+08 | 424023 | 3.29748 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4837.15 | 0.40708 | 20.2989ms | 409725 | 30 | 3.24405e+06 | 80779.8 | 0.62787 | 1(Win) |
| glaze | 3501.55 | 0.801678 | 29.3597ms | 409725 | 30 | 2.40097e+07 | 111592 | 0.867429 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1683.93 | 0.841863 | 105.898ms | 785750 | 30 | 4.21044e+08 | 445002 | 1.80402 | 1(Win) |
| glaze | 1384.91 | 1.35012 | 128.511ms | 785750 | 30 | 1.60102e+09 | 541083 | 2.1939 | 2(Loss) |
| jsonifier | 1267.07 | 0.386528 | 149.487ms | 785750 | 30 | 1.56765e+08 | 591403 | 2.39832 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5460.46 | 2.10229 | 33.9178ms | 785750 | 30 | 2.497e+08 | 137232 | 0.55623 | 1(Win) |
| glaze | 3909.46 | 1.36527 | 47.3273ms | 785750 | 30 | 2.05444e+08 | 191676 | 0.777021 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1189.06 | 0.247157 | 1645.85ms | 8587914 | 30 | 8.69434e+09 | 6.88787e+06 | 2.55556 | 1(Win) |
| simdjson (ondemand) | 1150.8 | 0.474435 | 1768.29ms | 8587914 | 30 | 3.42016e+10 | 7.11682e+06 | 2.64058 | 2(Loss) |
| glaze | 1004.95 | 0.819674 | 1851.28ms | 8587914 | 30 | 1.33871e+11 | 8.1497e+06 | 3.02384 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2986.98 | 1.36835 | 652.535ms | 8588126 | 30 | 4.22323e+10 | 2.74199e+06 | 1.01699 | 1(Win) |
| glaze | 2602.65 | 0.677593 | 755.885ms | 8588126 | 30 | 1.36404e+10 | 3.1469e+06 | 1.16723 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1302.85 | 0.518396 | 1809.89ms | 9804437 | 30 | 4.15242e+10 | 7.17675e+06 | 2.33242 | 1(Win) |
| glaze | 1081.91 | 0.202862 | 1995.84ms | 9804437 | 30 | 9.22118e+09 | 8.64234e+06 | 2.80878 | 2(Loss) |
| jsonifier | 1046.93 | 0.298301 | 2114.64ms | 9804437 | 30 | 2.12931e+10 | 8.93109e+06 | 2.90266 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3481.55 | 1.16526 | 780.78ms | 11078090 | 30 | 3.75108e+10 | 3.03454e+06 | 0.872546 | 1(Win) |
| glaze | 2689.95 | 0.84398 | 974.436ms | 11078090 | 30 | 3.2963e+10 | 3.92754e+06 | 1.12934 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5478.37 | 0.6161 | 11.602ms | 264040 | 30 | 2.40581e+06 | 45964.1 | 0.554341 | 1(Win) |
| simdjson (ondemand) | 5168.08 | 0.499101 | 29.1083ms | 264040 | 32 | 1.89238e+06 | 48723.7 | 0.587771 | 2(Loss) |
| glaze | 1984.08 | 1.05802 | 31.231ms | 264040 | 30 | 5.40916e+07 | 126914 | 1.53141 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7182.86 | 0.722657 | 13.5709ms | 399947 | 30 | 4.4177e+06 | 53101.3 | 0.422907 | 1(Win) |
| simdjson (ondemand) | 6720.96 | 0.505155 | 14.6464ms | 399947 | 30 | 2.46554e+06 | 56750.7 | 0.452006 | 2(Loss) |
| glaze | 2524.92 | 0.840676 | 36.76ms | 399947 | 30 | 4.83826e+07 | 151062 | 1.20337 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1779.47 | 0.666978 | 35.6239ms | 264040 | 30 | 2.67241e+07 | 141508 | 1.70751 | 1(Win) |
| simdjson (ondemand) | 1601.55 | 0.576744 | 38.7915ms | 264040 | 30 | 2.46686e+07 | 157227 | 1.89734 | 2(Loss) |
| glaze | 1566.86 | 0.905916 | 39.4017ms | 264040 | 30 | 6.3588e+07 | 160709 | 1.93926 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6318.74 | 1.14968 | 10.2274ms | 263923 | 30 | 6.29173e+06 | 39833.3 | 0.4805 | 1(Win) |
| jsonifier | 5991.7 | 0.522035 | 10.2948ms | 264040 | 30 | 1.44398e+06 | 42026.2 | 0.506363 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2289.24 | 0.690279 | 42.0326ms | 399947 | 30 | 3.9682e+07 | 166614 | 1.32739 | 1(Win) |
| glaze | 1937.35 | 0.550917 | 49.3396ms | 399947 | 30 | 3.52926e+07 | 196877 | 1.56845 | 2(Loss) |
| jsonifier | 1464.16 | 1.83665 | 62.7947ms | 399947 | 30 | 6.86761e+08 | 260505 | 2.07503 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7470.52 | 0.811676 | 12.8498ms | 399947 | 30 | 5.15217e+06 | 51056.6 | 0.406473 | 1(Win) |
| glaze | 5726.84 | 1.31363 | 16.711ms | 399830 | 30 | 2.29504e+07 | 66582.5 | 0.530287 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2395.18 | 0.772478 | 47.0477ms | 466906 | 30 | 6.18693e+07 | 185905 | 1.26846 | 1(Win) |
| glaze | 2275.25 | 0.974895 | 47.1389ms | 466906 | 30 | 1.09203e+08 | 195704 | 1.33534 | 2(Loss) |
| simdjson (ondemand) | 1272.56 | 1.21742 | 83.6627ms | 466906 | 30 | 5.44381e+08 | 349905 | 2.38764 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3721.8 | 0.564776 | 44.2095ms | 699405 | 30 | 3.07345e+07 | 179216 | 0.816319 | 1(Win) |
| glaze | 3558.99 | 0.784557 | 45.1674ms | 699405 | 30 | 6.48594e+07 | 187414 | 0.853816 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3509.72 | 0.544793 | 41.7676ms | 631514 | 30 | 2.62183e+07 | 171597 | 0.865757 | 1(Win) |
| glaze | 2474.98 | 0.411248 | 57.897ms | 631514 | 30 | 3.00436e+07 | 243339 | 1.22786 | 2(Loss) |
