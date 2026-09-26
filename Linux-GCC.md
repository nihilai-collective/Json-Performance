# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [e6f566c](https://github.com/nihilai-collective/jsonifier/commit/e6f566c)  
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
| simdjson (ondemand) | 1041.6 | 0.104833 | 1841.59ms | 6661897 | 30 | 1.22663e+09 | 6.09955e+06 | 2.23891 | 1(Win) |
| jsonifier | 1020.53 | 0.0734946 | 9531.38ms | 6661897 | 80 | 1.67473e+09 | 6.22546e+06 | 2.28512 | 2(Loss) |
| glaze | 892.168 | 0.106913 | 2148.99ms | 6661897 | 30 | 1.73893e+09 | 7.12117e+06 | 2.61394 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1586.87 | 0.229716 | 263.46ms | 1439562 | 30 | 1.18491e+08 | 865148 | 1.46953 | 1(Win) |
| glaze | 1442.89 | 0.218456 | 286.781ms | 1439562 | 30 | 1.29613e+08 | 951478 | 1.61612 | 2(Loss) |
| jsonifier | 1157.72 | 0.271599 | 358.952ms | 1439562 | 30 | 3.11195e+08 | 1.18584e+06 | 2.0142 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1149.34 | 1.78218 | 26.279ms | 94370 | 30 | 5.84245e+07 | 78304.2 | 2.02766 | 1(Win) |
| jsonifier STATISTICAL TIE | 1060.19 | 1.8478 | 28.1473ms | 94370 | 30 | 7.38133e+07 | 84889 | 2.19839 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1031.29 | 1.5595 | 28.6078ms | 94370 | 30 | 5.55642e+07 | 87267.5 | 2.26006 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1353.1 | 0.0870912 | 9.15457ms | 31235 | 30 | 11027.8 | 22014.6 | 1.72071 | 1(Win) |
| jsonifier | 1223.01 | 1.55825 | 9.88129ms | 31235 | 30 | 4.32133e+06 | 24356.3 | 1.90397 | 2(Loss) |
| glaze | 1083.28 | 2.84121 | 10.6868ms | 31235 | 30 | 1.83117e+07 | 27497.9 | 2.14963 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1467.33 | 1.74641 | 44.2832ms | 213963 | 30 | 1.76944e+08 | 139063 | 1.58857 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1446.38 | 1.24976 | 45.0553ms | 213963 | 30 | 9.3259e+07 | 141077 | 1.61172 | 1(Tie) |
| glaze | 1349 | 1.03286 | 48.1371ms | 213963 | 30 | 7.32248e+07 | 151261 | 1.72808 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1561.01 | 0.227046 | 1815.84ms | 9930848 | 30 | 5.69262e+09 | 6.0671e+06 | 1.49387 | 1(Win) |
| glaze | 1282.14 | 0.12635 | 2216.36ms | 9930848 | 30 | 2.6132e+09 | 7.3867e+06 | 1.81886 | 2(Loss) |
| simdjson (ondemand) | 451.182 | 0.266759 | 6245.07ms | 9930848 | 30 | 9.40655e+10 | 2.09911e+07 | 5.1687 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1566.1 | 0.0935955 | 1826.32ms | 9930848 | 30 | 9.61093e+08 | 6.04737e+06 | 1.48906 | 1(Win) |
| simdjson (ondemand) | 1432.64 | 0.118443 | 1976.37ms | 9930848 | 30 | 1.83923e+09 | 6.61073e+06 | 1.62775 | 2(Loss) |
| glaze | 1277.78 | 0.577484 | 2202.72ms | 9930848 | 30 | 5.49622e+10 | 7.41193e+06 | 1.82505 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1137.72 | 0.240135 | 311.389ms | 1225964 | 30 | 1.8269e+08 | 1.02764e+06 | 2.04962 | 1(Win) |
| glaze | 990.25 | 0.189764 | 357.38ms | 1225964 | 30 | 1.50597e+08 | 1.18068e+06 | 2.3549 | 2(Loss) |
| jsonifier | 894.906 | 0.528721 | 395.376ms | 1225964 | 30 | 1.43145e+09 | 1.30647e+06 | 2.60578 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 935.743 | 0.268923 | 242.787ms | 785750 | 30 | 1.39134e+08 | 800807 | 2.49202 | 1(Win) |
| jsonifier | 787.825 | 0.208749 | 288.243ms | 785750 | 30 | 1.18271e+08 | 951162 | 2.95997 | 2(Loss) |
| glaze | 675.023 | 0.445282 | 336.423ms | 785750 | 30 | 7.33033e+08 | 1.11011e+06 | 3.4546 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3327.23 | 1.25465 | 37.6657ms | 399947 | 30 | 6.20597e+07 | 114636 | 0.700531 | 1(Win) |
| jsonifier | 3004.57 | 1.17572 | 41.0263ms | 399947 | 30 | 6.68293e+07 | 126946 | 0.775762 | 2(Loss) |
| glaze | 1546.16 | 0.625801 | 76.5152ms | 399947 | 30 | 7.14979e+07 | 246689 | 1.50788 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1225.16 | 0.808714 | 96.1913ms | 399947 | 30 | 1.90166e+08 | 311323 | 1.90303 | 1(Win) |
| jsonifier | 1027.61 | 0.806578 | 114.435ms | 399947 | 30 | 2.68881e+08 | 371170 | 2.26884 | 2(Loss) |
| glaze | 999.283 | 0.488112 | 118.046ms | 399947 | 30 | 1.04133e+08 | 381693 | 2.33331 | 3(Loss) |
