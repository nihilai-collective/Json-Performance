# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [b01e9de](https://github.com/nihilai-collective/jsonifier/commit/b01e9de)  
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
| simdjson (ondemand) | 1061.68 | 0.140763 | 1808.32ms | 6661897 | 30 | 2.12868e+09 | 5.9842e+06 | 2.19656 | 1(Win) |
| jsonifier | 950.22 | 0.0968306 | 2115.96ms | 6661897 | 30 | 1.25746e+09 | 6.68611e+06 | 2.45417 | 2(Loss) |
| glaze | 888.217 | 0.189529 | 2141.72ms | 6661897 | 30 | 5.51352e+09 | 7.15285e+06 | 2.62552 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1575.56 | 0.154618 | 265.881ms | 1439562 | 30 | 5.44542e+07 | 871357 | 1.48007 | 1(Win) |
| glaze | 1433.37 | 0.278259 | 290.326ms | 1439562 | 30 | 2.13091e+08 | 957795 | 1.6269 | 2(Loss) |
| jsonifier | 1126.85 | 0.220491 | 368.02ms | 1439562 | 30 | 2.16485e+08 | 1.21833e+06 | 2.06936 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1111.2 | 2.00856 | 27.0373ms | 94370 | 30 | 7.93916e+07 | 80992 | 2.09724 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1034.63 | 2.90573 | 28.1744ms | 94370 | 30 | 1.91661e+08 | 86986.2 | 2.25248 | 1(Tie) |
| jsonifier | 1033.79 | 2.88712 | 28.6267ms | 94370 | 30 | 1.89521e+08 | 87056.9 | 2.25423 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1329.94 | 2.37224 | 9.12468ms | 31235 | 30 | 8.46942e+06 | 22397.9 | 1.75081 | 1(Win) |
| jsonifier | 1193.91 | 1.44466 | 10.088ms | 31235 | 30 | 3.8976e+06 | 24950 | 1.9502 | 2(Loss) |
| glaze | 1076.29 | 2.83629 | 25.2532ms | 31235 | 40 | 2.46482e+07 | 27676.5 | 2.1637 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1414.83 | 1.01421 | 45.9487ms | 213963 | 30 | 6.41874e+07 | 144223 | 1.64764 | 1(Win) |
| glaze STATISTICAL TIE | 1320.59 | 1.14421 | 49.1188ms | 213963 | 30 | 9.37729e+07 | 154516 | 1.76532 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1303.11 | 2.00578 | 48.9771ms | 213963 | 30 | 2.95937e+08 | 156587 | 1.78887 | 2(Tie) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1519.46 | 0.280144 | 1882.73ms | 9930848 | 30 | 9.14703e+09 | 6.23301e+06 | 1.53472 | 1(Win) |
| glaze | 1294.82 | 0.182193 | 2191.38ms | 9930848 | 30 | 5.32769e+09 | 7.31436e+06 | 1.80098 | 2(Loss) |
| simdjson (ondemand) | 451.658 | 0.172929 | 6325.67ms | 9930848 | 30 | 3.94466e+10 | 2.0969e+07 | 5.16326 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1519.15 | 0.209519 | 1865.6ms | 9930848 | 30 | 5.11848e+09 | 6.23427e+06 | 1.53501 | 1(Win) |
| simdjson (ondemand) | 1411.92 | 0.370917 | 2028.78ms | 9930848 | 30 | 1.85706e+10 | 6.70773e+06 | 1.65161 | 2(Loss) |
| glaze | 1308.43 | 0.0891334 | 2176.63ms | 9930848 | 30 | 1.24874e+09 | 7.23826e+06 | 1.78233 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1131.46 | 0.172047 | 312.643ms | 1225964 | 30 | 9.48178e+07 | 1.03333e+06 | 2.06103 | 1(Win) |
| glaze | 993.296 | 0.144613 | 358.302ms | 1225964 | 30 | 8.69231e+07 | 1.17706e+06 | 2.34768 | 2(Loss) |
| jsonifier | 892.06 | 0.146069 | 398.067ms | 1225964 | 30 | 1.09953e+08 | 1.31064e+06 | 2.61418 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 938.2 | 0.193911 | 243.034ms | 785750 | 30 | 7.19619e+07 | 798710 | 2.48555 | 1(Win) |
| jsonifier | 789.878 | 1.58118 | 283.889ms | 785750 | 30 | 6.75049e+09 | 948691 | 2.95232 | 2(Loss) |
| glaze | 688.315 | 0.229259 | 330.27ms | 785750 | 30 | 1.86883e+08 | 1.08867e+06 | 3.38792 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3388.76 | 1.13594 | 36.8198ms | 399947 | 30 | 4.90404e+07 | 112554 | 0.687847 | 1(Win) |
| jsonifier | 2981.62 | 1.57269 | 41.3044ms | 399947 | 30 | 1.21425e+08 | 127924 | 0.781703 | 2(Loss) |
| glaze | 1531.33 | 0.662068 | 79.513ms | 399947 | 30 | 8.15821e+07 | 249077 | 1.52255 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1212.03 | 0.821621 | 96.8196ms | 399947 | 30 | 2.0056e+08 | 314695 | 1.92374 | 1(Win) |
| glaze | 960.414 | 0.637457 | 121.758ms | 399947 | 30 | 1.9227e+08 | 397140 | 2.4278 | 2(Loss) |
| jsonifier | 927.492 | 1.27198 | 123.813ms | 399947 | 30 | 8.20859e+08 | 411237 | 2.51393 | 3(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1371.42 | 0.583432 | 100.692ms | 466906 | 30 | 1.07652e+08 | 324683 | 1.70009 | 1(Win) |
| glaze | 1208.04 | 0.969169 | 110.495ms | 466906 | 30 | 3.82837e+08 | 368593 | 1.93012 | 2(Loss) |
| simdjson (ondemand) | 657.283 | 0.461478 | 207.197ms | 466906 | 30 | 2.93209e+08 | 677450 | 3.54769 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1915.92 | 0.646326 | 108.309ms | 699405 | 30 | 1.51889e+08 | 348137 | 1.21691 | 1(Win) |
| glaze | 1214.11 | 0.342763 | 167.669ms | 699405 | 30 | 1.06378e+08 | 549378 | 1.92059 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1658.78 | 0.571637 | 112.349ms | 631514 | 30 | 1.29227e+08 | 363074 | 1.40571 | 1(Win) |
| glaze | 1427.43 | 0.625003 | 129.009ms | 631514 | 30 | 2.08613e+08 | 421917 | 1.63351 | 2(Loss) |
