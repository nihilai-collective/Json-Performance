# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [0953100](https://github.com/nihilai-collective/jsonifier/commit/0953100)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1132.97 | 0.076959 | 1765.88ms | 6661897 | 30 | 5.58723e+08 | 5.60761e+06 | 2.1852 | 1(Win) |
| glaze | 939.255 | 0.0562718 | 2039.59ms | 6661897 | 30 | 4.34642e+08 | 6.76417e+06 | 2.6359 | 2(Loss) |
| simdjson (ondemand) | 901.38 | 0.410749 | 2113.1ms | 6661897 | 30 | 2.51452e+10 | 7.04839e+06 | 2.74665 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1951.22 | 0.281957 | 216.038ms | 1439562 | 30 | 1.18068e+08 | 703596 | 1.26862 | 1(Win) |
| glaze | 1575.39 | 0.204823 | 264.587ms | 1439562 | 30 | 9.55793e+07 | 871451 | 1.57132 | 2(Loss) |
| simdjson (ondemand) | 1296.84 | 0.162248 | 321.257ms | 1439562 | 30 | 8.8505e+07 | 1.05863e+06 | 1.90882 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1211.9 | 1.77716 | 25.3784ms | 94370 | 30 | 5.22523e+07 | 74262 | 2.04156 | 1(Win) |
| glaze STATISTICAL TIE | 1128.85 | 2.047 | 26.8214ms | 94370 | 30 | 7.99007e+07 | 79725.3 | 2.19211 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1092.23 | 1.95868 | 27.5404ms | 94370 | 30 | 7.81424e+07 | 82398.3 | 2.2657 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1654.4 | 0.119217 | 8.45444ms | 31235 | 30 | 13823.1 | 18005.4 | 1.49332 | 1(Win) |
| simdjson (ondemand) | 1332.89 | 2.04367 | 9.54661ms | 31235 | 30 | 6.25804e+06 | 22348.5 | 1.85398 | 2(Loss) |
| glaze | 1212.08 | 1.27555 | 10.5031ms | 31235 | 30 | 2.94809e+06 | 24576 | 2.03938 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1663.49 | 1.39526 | 39.5211ms | 213963 | 30 | 8.78762e+07 | 122665 | 1.48764 | 1(Win) |
| simdjson (ondemand) | 1419.58 | 1.20011 | 45.1448ms | 213963 | 30 | 8.92726e+07 | 143740 | 1.74351 | 2(Loss) |
| glaze | 853.074 | 0.782171 | 75.2269ms | 213963 | 30 | 1.0501e+08 | 239195 | 2.9013 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1778.58 | 0.120843 | 1603.76ms | 9930848 | 30 | 1.24221e+09 | 5.32492e+06 | 1.39196 | 1(Win) |
| glaze | 1379.05 | 0.0921699 | 2073.76ms | 9930848 | 30 | 1.20202e+09 | 6.86763e+06 | 1.79528 | 2(Loss) |
| simdjson (ondemand) | 521.505 | 0.167484 | 5446.72ms | 9930848 | 30 | 2.77539e+10 | 1.81605e+07 | 4.74745 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1774.44 | 0.200443 | 1602.54ms | 9930848 | 30 | 3.43364e+09 | 5.33735e+06 | 1.39522 | 1(Win) |
| glaze | 1365.79 | 0.0954173 | 2088.39ms | 9930848 | 30 | 1.31334e+09 | 6.93428e+06 | 1.8127 | 2(Loss) |
| simdjson (ondemand) | 1342.31 | 0.0861553 | 2122.81ms | 9930848 | 30 | 1.10855e+09 | 7.05562e+06 | 1.8444 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1101.72 | 0.254717 | 323.063ms | 1225964 | 30 | 2.19207e+08 | 1.06123e+06 | 2.247 | 1(Win) |
| jsonifier | 1054.43 | 0.178719 | 338.364ms | 1225964 | 30 | 1.17809e+08 | 1.10882e+06 | 2.34781 | 2(Loss) |
| simdjson (ondemand) | 1025.88 | 0.14846 | 346.572ms | 1225964 | 30 | 8.5881e+07 | 1.13967e+06 | 2.41311 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 944.828 | 0.217828 | 241.727ms | 785750 | 30 | 8.95391e+07 | 793107 | 2.62005 | 1(Win) |
| simdjson (ondemand) | 881.405 | 0.583898 | 256.29ms | 785750 | 30 | 7.39287e+08 | 850176 | 2.80852 | 2(Loss) |
| glaze | 693.895 | 0.18018 | 327.981ms | 785750 | 30 | 1.13584e+08 | 1.07992e+06 | 3.56764 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3819.3 | 1.80116 | 33.3198ms | 399947 | 30 | 9.70648e+07 | 99866.2 | 0.647965 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3647.56 | 1.69838 | 34.2491ms | 399947 | 30 | 9.46214e+07 | 104568 | 0.678445 | 1(Tie) |
| glaze | 2394.09 | 0.838038 | 50.8793ms | 399947 | 30 | 5.34776e+07 | 159317 | 1.03381 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1273.51 | 0.644338 | 93.5793ms | 399947 | 30 | 1.11724e+08 | 299501 | 1.94361 | 1(Win) |
| jsonifier | 1143.74 | 0.295543 | 1067.62ms | 399947 | 160 | 1.55423e+08 | 333485 | 2.16395 | 2(Loss) |
| glaze | 1109.91 | 0.582658 | 106.252ms | 399947 | 30 | 1.20275e+08 | 343647 | 2.23007 | 3(Loss) |
