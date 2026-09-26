# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [c210b82](https://github.com/nihilai-collective/jsonifier/commit/c210b82)  
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

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1024.66 | 0.148267 | 1867.45ms | 6661897 | 30 | 2.5354e+09 | 6.20039e+06 | 2.41613 | 1(Win) |
| jsonifier | 1003.69 | 0.101576 | 1930.33ms | 6661897 | 30 | 1.24024e+09 | 6.32993e+06 | 2.46663 | 2(Loss) |
| glaze | 880.554 | 0.0661249 | 2164.15ms | 6661897 | 30 | 6.82865e+08 | 7.21509e+06 | 2.81157 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1645.33 | 0.232858 | 254.945ms | 1439562 | 30 | 1.13255e+08 | 834406 | 1.50453 | 1(Win) |
| glaze | 1502.79 | 0.164564 | 277.084ms | 1439562 | 30 | 6.78034e+07 | 913548 | 1.64726 | 2(Loss) |
| jsonifier | 1106.19 | 0.139008 | 376.545ms | 1439562 | 30 | 8.92907e+07 | 1.24108e+06 | 2.23784 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1203.34 | 1.6975 | 25.3432ms | 94370 | 30 | 4.83542e+07 | 74790.6 | 2.05587 | 1(Tie) |
| glaze STATISTICAL TIE | 1154.53 | 1.91116 | 25.8975ms | 94370 | 30 | 6.6585e+07 | 77952.5 | 2.14325 | 1(Tie) |
| simdjson (ondemand) | 1115.8 | 1.41486 | 27.0662ms | 94370 | 30 | 3.907e+07 | 80658.1 | 2.21747 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1442.98 | 1.58895 | 9.08036ms | 31235 | 30 | 3.22778e+06 | 20643.3 | 1.71255 | 1(Win) |
| jsonifier STATISTICAL TIE | 1179.02 | 1.12879 | 10.5576ms | 31235 | 30 | 2.43997e+06 | 25265 | 2.09654 | 2(Tie) |
| glaze STATISTICAL TIE | 1165.87 | 1.21687 | 10.6275ms | 31235 | 30 | 2.89997e+06 | 25550.1 | 2.12026 | 2(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1593.98 | 1.2439 | 41.1181ms | 213963 | 30 | 7.60691e+07 | 128014 | 1.55251 | 1(Win) |
| jsonifier | 1537.55 | 1.2483 | 42.8728ms | 213963 | 30 | 8.23337e+07 | 132712 | 1.60957 | 2(Loss) |
| glaze | 1353.65 | 0.624936 | 48.3037ms | 213963 | 30 | 2.66231e+07 | 150741 | 1.8283 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1536.87 | 0.121738 | 1847.47ms | 9930848 | 30 | 1.6884e+09 | 6.1624e+06 | 1.61086 | 1(Win) |
| glaze | 1333.42 | 0.0520434 | 2140.02ms | 9930848 | 30 | 4.09913e+08 | 7.10263e+06 | 1.85669 | 2(Loss) |
| simdjson (ondemand) | 431.126 | 0.0999566 | 6596.29ms | 9930848 | 30 | 1.44647e+10 | 2.19676e+07 | 5.74256 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1540.97 | 0.058889 | 1850.51ms | 9930848 | 30 | 3.92984e+08 | 6.14601e+06 | 1.6066 | 1(Win) |
| simdjson (ondemand) | 1441.87 | 0.0764878 | 1981.84ms | 9930848 | 30 | 7.57227e+08 | 6.56841e+06 | 1.71702 | 2(Loss) |
| glaze | 1314.65 | 0.279367 | 2162.58ms | 9930848 | 30 | 1.21514e+10 | 7.20406e+06 | 1.8832 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1136.22 | 0.239926 | 314.751ms | 1225964 | 30 | 1.82856e+08 | 1.029e+06 | 2.17869 | 1(Win) |
| glaze | 959.146 | 0.257748 | 368.718ms | 1225964 | 30 | 2.96142e+08 | 1.21897e+06 | 2.58097 | 2(Loss) |
| jsonifier | 853.43 | 0.144864 | 416.415ms | 1225964 | 30 | 1.18158e+08 | 1.36997e+06 | 2.9007 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 962.141 | 0.19211 | 236.183ms | 785750 | 30 | 6.71604e+07 | 778836 | 2.57279 | 1(Win) |
| jsonifier | 832.109 | 0.704982 | 270.742ms | 785750 | 30 | 1.20917e+09 | 900542 | 2.97481 | 2(Loss) |
| glaze | 681.006 | 0.14559 | 334.041ms | 785750 | 30 | 7.69932e+07 | 1.10036e+06 | 3.635 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3537.05 | 1.55533 | 35.2398ms | 399947 | 30 | 8.439e+07 | 107835 | 0.699579 | 1(Win) |
| simdjson (ondemand) | 3249.45 | 1.3023 | 38.2403ms | 399947 | 30 | 7.01019e+07 | 117380 | 0.761509 | 2(Loss) |
| glaze | 1588.98 | 0.634863 | 75.2158ms | 399947 | 30 | 6.96709e+07 | 240041 | 1.55776 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1330.01 | 0.566639 | 90.1092ms | 399947 | 30 | 7.92188e+07 | 286779 | 1.86086 | 1(Win) |
| jsonifier | 1120.04 | 0.857125 | 106.271ms | 399947 | 30 | 2.55594e+08 | 340542 | 2.20943 | 2(Loss) |
| glaze | 1011.12 | 0.578663 | 288.07ms | 399947 | 40 | 1.90593e+08 | 377223 | 2.44781 | 3(Loss) |
