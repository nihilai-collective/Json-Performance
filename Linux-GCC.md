# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [b7e65b3](https://github.com/nihilai-collective/jsonifier/commit/b7e65b3)  
| Glaze: [2d38174](https://github.com/stephenberry/glaze/commit/2d38174)  
| Simdjson: [645e5c8](https://github.com/simdjson/simdjson/commit/645e5c8)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX512BW` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Xeon(R) 6973P-C-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 1552.51 | 0.457816 | 1230.5ms | 6661897 | 30 | 1.05301e+10 | 4.09228e+06 | 1.59695 | 1(Win) |
| simdjson (ondemand) | 1442.48 | 0.666381 | 1314.71ms | 6661897 | 30 | 2.5843e+10 | 4.40442e+06 | 1.71881 | 2(Loss) |
| glaze | 1350.89 | 0.0849567 | 1415.15ms | 6661897 | 30 | 4.78934e+08 | 4.70305e+06 | 1.83532 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2618.08 | 0.465081 | 160.181ms | 1439562 | 30 | 1.78432e+08 | 524382 | 0.946821 | 1(Win) |
| glaze | 2163.61 | 0.436993 | 193.907ms | 1439562 | 30 | 2.30661e+08 | 634529 | 1.14565 | 2(Loss) |
| jsonifier | 2131.91 | 0.427159 | 198.223ms | 1439562 | 30 | 2.26998e+08 | 643964 | 1.16273 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1829.42 | 1.60305 | 16.3048ms | 94370 | 30 | 1.86575e+07 | 49194.9 | 1.35433 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1521.97 | 2.25917 | 18.8593ms | 94370 | 30 | 5.35395e+07 | 59132.7 | 1.62789 | 2(Tie) |
| glaze STATISTICAL TIE | 1511.48 | 0.758831 | 19.3205ms | 94370 | 30 | 6.12455e+06 | 59543.1 | 1.63918 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2213.29 | 0.138348 | 12.6621ms | 31235 | 40 | 13868 | 13458.7 | 1.11757 | 1(Win) |
| jsonifier | 1866.44 | 0.168861 | 6.3493ms | 31235 | 30 | 21788.7 | 15959.8 | 1.32592 | 2(Loss) |
| glaze | 1621.43 | 1.09807 | 6.95068ms | 31235 | 30 | 1.22086e+06 | 18371.4 | 1.52655 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2740.36 | 1.80454 | 23.9464ms | 213963 | 30 | 5.41644e+07 | 74461.3 | 0.904216 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2612.43 | 1.77415 | 24.4185ms | 213963 | 30 | 5.76087e+07 | 78107.6 | 0.948643 | 1(Tie) |
| glaze | 2252.37 | 1.26511 | 28.8516ms | 213963 | 30 | 3.94071e+07 | 90593.9 | 1.10036 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2252.8 | 0.250233 | 1270.44ms | 9930848 | 30 | 3.32001e+09 | 4.20401e+06 | 1.10052 | 1(Win) |
| glaze | 1855.71 | 0.364558 | 1528.26ms | 9930848 | 30 | 1.0385e+10 | 5.10359e+06 | 1.33602 | 2(Loss) |
| simdjson (ondemand) | 632.816 | 0.139656 | 4479.37ms | 9930848 | 30 | 1.31057e+10 | 1.49661e+07 | 3.91812 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2251.91 | 0.2329 | 1270.28ms | 9930848 | 30 | 2.87826e+09 | 4.20567e+06 | 1.10098 | 1(Win) |
| simdjson (ondemand) | 2198.17 | 0.405412 | 1313.05ms | 9930848 | 30 | 9.153e+09 | 4.30848e+06 | 1.12786 | 2(Loss) |
| glaze | 1777.5 | 0.29192 | 1603.72ms | 9930848 | 30 | 7.2578e+09 | 5.32817e+06 | 1.39486 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1826.68 | 0.239943 | 195.643ms | 1225964 | 30 | 7.07566e+07 | 640052 | 1.3569 | 1(Win) |
| jsonifier | 1312.5 | 0.168884 | 270.043ms | 1225964 | 30 | 6.78978e+07 | 890794 | 1.8886 | 2(Loss) |
| glaze | 1236.44 | 0.240084 | 674.77ms | 1225964 | 40 | 2.06157e+08 | 945595 | 2.00479 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1548 | 0.454038 | 146.7ms | 785750 | 30 | 1.44921e+08 | 484075 | 1.60112 | 1(Win) |
| jsonifier | 1183.15 | 0.683376 | 191.624ms | 785750 | 30 | 5.61995e+08 | 633352 | 2.09524 | 2(Loss) |
| glaze | 1087.97 | 0.364345 | 211.24ms | 785750 | 30 | 1.88922e+08 | 688759 | 2.27834 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6892.63 | 2.03208 | 18.2236ms | 399947 | 30 | 3.79348e+07 | 55337.2 | 0.359502 | 1(Win) |
| simdjson (ondemand) | 6197.58 | 0.646778 | 19.7779ms | 399947 | 30 | 4.75326e+06 | 61543.2 | 0.399816 | 2(Loss) |
| glaze | 2971.64 | 0.774658 | 93.3674ms | 399947 | 40 | 3.95452e+07 | 128353 | 0.834119 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1948.51 | 0.733013 | 63.4755ms | 399947 | 30 | 6.1765e+07 | 195749 | 1.27218 | 1(Win) |
| glaze | 1679.33 | 0.433382 | 71.3382ms | 399947 | 30 | 2.90668e+07 | 227126 | 1.47613 | 2(Loss) |
| jsonifier | 1627.01 | 0.620667 | 72.2247ms | 399947 | 30 | 6.35131e+07 | 234430 | 1.52351 | 3(Loss) |
