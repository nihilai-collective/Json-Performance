# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [62c4541](https://github.com/nihilai-collective/jsonifier/commit/62c4541)  
| Glaze: [2d38174](https://github.com/stephenberry/glaze/commit/2d38174)  
| Simdjson: [645e5c8](https://github.com/simdjson/simdjson/commit/645e5c8)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX2` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1046.6 | 0.137024 | 1861.01ms | 6661897 | 30 | 2.07561e+09 | 6.07039e+06 | 2.22816 | 1(Win) |
| jsonifier | 987.922 | 1.48725 | 1919.76ms | 6661897 | 30 | 2.74436e+11 | 6.43095e+06 | 2.36059 | 2(Loss) |
| glaze | 851.135 | 1.52697 | 2253.25ms | 6661897 | 30 | 3.89747e+11 | 7.46448e+06 | 2.73993 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1551.89 | 0.189803 | 267.291ms | 1439562 | 30 | 8.45798e+07 | 884647 | 1.50263 | 1(Win) |
| glaze | 1436.94 | 0.699195 | 286.2ms | 1439562 | 30 | 1.33876e+09 | 955416 | 1.62278 | 2(Loss) |
| jsonifier | 1335.52 | 0.234643 | 313.204ms | 1439562 | 30 | 1.7454e+08 | 1.02797e+06 | 1.74606 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1122.47 | 2.50262 | 26.2791ms | 94370 | 30 | 1.2079e+08 | 80178.7 | 2.07633 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1067.4 | 2.16755 | 28.1533ms | 94370 | 30 | 1.00202e+08 | 84315.6 | 2.18307 | 1(Tie) |
| simdjson (ondemand) | 1041.21 | 1.66072 | 28.4199ms | 94370 | 30 | 6.1817e+07 | 86436.2 | 2.23838 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1329.46 | 1.53605 | 21.5456ms | 31235 | 40 | 4.73803e+06 | 22406 | 1.75159 | 1(Win) |
| jsonifier | 1173.98 | 1.75368 | 10.2733ms | 31235 | 30 | 5.93999e+06 | 25373.6 | 1.98345 | 2(Loss) |
| glaze | 1084.94 | 0.197605 | 10.8695ms | 31235 | 30 | 88305.1 | 27455.9 | 2.14647 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1456 | 0.606684 | 45.1227ms | 213963 | 30 | 2.16872e+07 | 140145 | 1.60103 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1434.68 | 1.17031 | 45.7441ms | 213963 | 30 | 8.31175e+07 | 142228 | 1.62479 | 1(Tie) |
| glaze | 1299.9 | 1.75782 | 49.0477ms | 213963 | 30 | 2.28416e+08 | 156974 | 1.79323 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1406.41 | 1.48733 | 1988.99ms | 9930848 | 30 | 3.00942e+11 | 6.734e+06 | 1.6581 | 1(Win) |
| glaze | 1289.39 | 0.141066 | 2215.86ms | 9930848 | 30 | 3.22083e+09 | 7.34515e+06 | 1.80865 | 2(Loss) |
| simdjson (ondemand) | 447.014 | 0.187214 | 6315.62ms | 9930848 | 30 | 4.71986e+10 | 2.11868e+07 | 5.21694 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1476.45 | 0.100782 | 1935.94ms | 9930848 | 30 | 1.25378e+09 | 6.41457e+06 | 1.57951 | 1(Win) |
| simdjson (ondemand) | 1431.47 | 0.169774 | 4681.65ms | 9930848 | 40 | 5.04675e+09 | 6.61615e+06 | 1.62916 | 2(Loss) |
| glaze | 1298.97 | 0.166573 | 2183.42ms | 9930848 | 30 | 4.42486e+09 | 7.29098e+06 | 1.79528 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1146.77 | 0.0991106 | 312.499ms | 1225964 | 30 | 3.06313e+07 | 1.01954e+06 | 2.03355 | 1(Win) |
| glaze | 978.104 | 0.220215 | 360.649ms | 1225964 | 30 | 2.07874e+08 | 1.19534e+06 | 2.38421 | 2(Loss) |
| jsonifier | 884.6 | 0.10722 | 397.89ms | 1225964 | 30 | 6.02473e+07 | 1.32169e+06 | 2.63625 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 914.434 | 0.284272 | 249.264ms | 785750 | 30 | 1.62799e+08 | 819468 | 2.55016 | 1(Win) |
| jsonifier | 790.174 | 0.202773 | 287.703ms | 785750 | 30 | 1.10934e+08 | 948335 | 2.95125 | 2(Loss) |
| glaze | 668.186 | 0.301541 | 340.294ms | 785750 | 30 | 3.43074e+08 | 1.12147e+06 | 3.49007 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3316.84 | 1.12739 | 37.1584ms | 399947 | 30 | 5.04223e+07 | 114995 | 0.702794 | 1(Win) |
| jsonifier | 2960.06 | 0.790751 | 41.6236ms | 399947 | 30 | 3.11462e+07 | 128855 | 0.787473 | 2(Loss) |
| glaze | 1545.32 | 0.529422 | 76.9539ms | 399947 | 30 | 5.12265e+07 | 246823 | 1.50878 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1251.59 | 0.605108 | 95.0793ms | 399947 | 30 | 1.02016e+08 | 304748 | 1.86296 | 1(Win) |
| jsonifier | 1025.97 | 0.414489 | 271.295ms | 399947 | 40 | 9.49776e+07 | 371764 | 2.27271 | 2(Loss) |
| glaze | 958.567 | 0.577228 | 122.617ms | 399947 | 30 | 1.58262e+08 | 397906 | 2.43222 | 3(Loss) |
