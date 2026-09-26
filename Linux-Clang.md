# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1159.65 | 0.132542 | 1667.6ms | 6661897 | 30 | 1.58187e+09 | 5.47863e+06 | 2.01104 | 1(Win) |
| glaze | 963.716 | 0.111472 | 1990.97ms | 6661897 | 30 | 1.62013e+09 | 6.59248e+06 | 2.4199 | 2(Loss) |
| simdjson (ondemand) | 958.602 | 0.223227 | 1988.38ms | 6661897 | 30 | 6.56649e+09 | 6.62765e+06 | 2.43277 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1822.17 | 0.247167 | 230.415ms | 1439562 | 30 | 1.04037e+08 | 753430 | 1.27977 | 1(Win) |
| glaze | 1530.75 | 0.261877 | 272.131ms | 1439562 | 30 | 1.65488e+08 | 896862 | 1.5234 | 2(Loss) |
| simdjson (ondemand) | 1375.06 | 0.116677 | 304.019ms | 1439562 | 30 | 4.07106e+07 | 998410 | 1.69593 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1137.02 | 1.56486 | 26.3391ms | 94370 | 30 | 4.60261e+07 | 79152.6 | 2.05007 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1131.36 | 1.79836 | 26.4265ms | 94370 | 30 | 6.13964e+07 | 79548.9 | 2.0602 | 1(Tie) |
| simdjson (ondemand) | 1009.52 | 2.36376 | 28.6743ms | 94370 | 30 | 1.33219e+08 | 89149.6 | 2.30893 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1316.64 | 0.0864171 | 9.37165ms | 31235 | 30 | 11467.5 | 22624.2 | 1.7683 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1315.19 | 1.88053 | 9.33544ms | 31235 | 30 | 5.44238e+06 | 22649.2 | 1.77029 | 1(Tie) |
| glaze | 1110.48 | 2.73368 | 10.4321ms | 31235 | 30 | 1.61316e+07 | 26824.4 | 2.09721 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1667.5 | 0.553275 | 39.9209ms | 213963 | 30 | 1.37515e+07 | 122369 | 1.39798 | 1(Win) |
| glaze | 1492.9 | 0.89238 | 43.7584ms | 213963 | 30 | 4.46311e+07 | 136681 | 1.56153 | 2(Loss) |
| simdjson (ondemand) | 1380.37 | 0.934469 | 47.0048ms | 213963 | 30 | 5.72449e+07 | 147823 | 1.68885 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1651.83 | 0.109882 | 1730.89ms | 9930848 | 30 | 1.19074e+09 | 5.73352e+06 | 1.41181 | 1(Win) |
| glaze | 1367.38 | 0.0826471 | 2084.47ms | 9930848 | 30 | 9.83037e+08 | 6.92622e+06 | 1.70552 | 2(Loss) |
| simdjson (ondemand) | 545.248 | 0.274714 | 5175.36ms | 9930848 | 30 | 6.83075e+10 | 1.73697e+07 | 4.27702 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1608.67 | 0.0999587 | 1792ms | 9930848 | 30 | 1.03896e+09 | 5.88734e+06 | 1.44969 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1385.38 | 0.175711 | 2054.93ms | 9930848 | 30 | 4.32865e+09 | 6.83625e+06 | 1.68328 | 2(Tie) |
| glaze STATISTICAL TIE | 1384.35 | 0.176696 | 2060.87ms | 9930848 | 30 | 4.38384e+09 | 6.84132e+06 | 1.68457 | 2(Tie) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1127.17 | 0.130599 | 314.685ms | 1225964 | 30 | 5.50522e+07 | 1.03726e+06 | 2.06888 | 1(Win) |
| jsonifier STATISTICAL TIE | 1054.96 | 0.21148 | 334.526ms | 1225964 | 30 | 1.64794e+08 | 1.10826e+06 | 2.21046 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1051.76 | 0.153669 | 1714.87ms | 1225964 | 80 | 2.33447e+08 | 1.11164e+06 | 2.21722 | 2(Tie) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 888.026 | 0.23759 | 601.858ms | 785750 | 40 | 1.60781e+08 | 843838 | 2.626 | 1(Win) |
| simdjson (ondemand) | 849.818 | 0.169715 | 267.823ms | 785750 | 30 | 6.71862e+07 | 881777 | 2.74411 | 2(Loss) |
| glaze | 698.661 | 0.25349 | 325.105ms | 785750 | 30 | 2.21758e+08 | 1.07255e+06 | 3.33778 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3646.14 | 2.21193 | 33.8249ms | 399947 | 30 | 1.60621e+08 | 104609 | 0.639306 | 1(Win) |
| simdjson (ondemand) | 3447.19 | 1.71164 | 35.7052ms | 399947 | 30 | 1.07602e+08 | 110646 | 0.676227 | 2(Loss) |
| glaze | 2297.19 | 1.24322 | 52.4353ms | 399947 | 30 | 1.2783e+08 | 166038 | 1.01489 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1150.27 | 0.777403 | 102.881ms | 399947 | 30 | 1.99353e+08 | 331592 | 2.02713 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1133.89 | 1.15214 | 522.031ms | 399947 | 80 | 1.2016e+09 | 336380 | 2.05624 | 1(Tie) |
| glaze | 1045.07 | 0.747731 | 112.337ms | 399947 | 30 | 2.23421e+08 | 364969 | 2.23116 | 3(Loss) |
