# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [48b1541](https://github.com/nihilai-collective/jsonifier/commit/48b1541)  
| Glaze: [99fcc35](https://github.com/stephenberry/glaze/commit/99fcc35)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| simdjson (ondemand) | 1349.81 | 0.0865134 | 1417.45ms | 6661897 | 30 | 4.9744e+08 | 4.70681e+06 | 1.83415 | 1(Win) |
| jsonifier | 1313.17 | 0.0987302 | 1504.34ms | 6661897 | 30 | 6.84503e+08 | 4.83813e+06 | 1.88534 | 2(Loss) |
| glaze | 1104.48 | 0.0807173 | 1731.46ms | 6661897 | 30 | 6.46752e+08 | 5.7523e+06 | 2.24159 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2393 | 0.243686 | 175.108ms | 1439562 | 30 | 5.86354e+07 | 573704 | 1.03444 | 1(Win) |
| glaze | 1984.64 | 0.309635 | 209.744ms | 1439562 | 30 | 1.37632e+08 | 691750 | 1.24732 | 2(Loss) |
| jsonifier | 1835.4 | 0.254441 | 228.043ms | 1439562 | 30 | 1.08666e+08 | 747996 | 1.34877 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1567.84 | 2.22969 | 19.5407ms | 94370 | 30 | 4.91444e+07 | 57402.7 | 1.57789 | 1(Win) |
| glaze | 1465.39 | 0.563739 | 21.2249ms | 94370 | 30 | 3.59616e+06 | 61415.9 | 1.68855 | 2(Loss) |
| jsonifier | 1245.05 | 1.52944 | 24.0671ms | 94370 | 30 | 3.66676e+07 | 72285 | 1.98752 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2052.2 | 0.609 | 6.65985ms | 31235 | 30 | 234423 | 14515.2 | 1.20365 | 1(Win) |
| glaze | 1448.24 | 2.69122 | 8.4011ms | 31235 | 30 | 9.19224e+06 | 20568.4 | 1.70675 | 2(Loss) |
| jsonifier | 1306.75 | 3.7482 | 9.02947ms | 31235 | 30 | 2.1901e+07 | 22795.5 | 1.8921 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2291.63 | 2.13069 | 28.623ms | 213963 | 30 | 1.07982e+08 | 89041.9 | 1.07983 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2229.11 | 1.38031 | 30.1627ms | 213963 | 30 | 4.78947e+07 | 91539.1 | 1.11018 | 1(Tie) |
| glaze | 1745.56 | 1.55575 | 37.16ms | 213963 | 30 | 9.92223e+07 | 116897 | 1.41777 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2144.11 | 0.111051 | 1327.29ms | 9930848 | 30 | 7.21841e+08 | 4.41712e+06 | 1.15461 | 1(Win) |
| glaze | 1660.34 | 0.0915491 | 1713.8ms | 9930848 | 30 | 8.18098e+08 | 5.70411e+06 | 1.49099 | 2(Loss) |
| simdjson (ondemand) | 564.472 | 0.068496 | 5072.96ms | 9930848 | 30 | 3.96222e+09 | 1.67781e+07 | 4.38605 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2155.25 | 0.0802853 | 1323.14ms | 9930848 | 30 | 3.73398e+08 | 4.3943e+06 | 1.1487 | 1(Win) |
| simdjson (ondemand) | 1966.51 | 0.0848447 | 1493.82ms | 9930848 | 30 | 5.00901e+08 | 4.81605e+06 | 1.25896 | 2(Loss) |
| glaze | 1651.73 | 0.633853 | 1723.98ms | 9930848 | 30 | 3.96271e+10 | 5.73385e+06 | 1.4989 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1555.85 | 0.820151 | 224.768ms | 1225964 | 30 | 1.13954e+09 | 751469 | 1.59106 | 1(Win) |
| jsonifier | 1213.31 | 0.316119 | 292.355ms | 1225964 | 30 | 2.78379e+08 | 963624 | 2.04035 | 2(Loss) |
| glaze | 1181.55 | 0.250665 | 299.742ms | 1225964 | 30 | 1.84572e+08 | 989526 | 2.0952 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1351.34 | 0.27876 | 169.458ms | 785750 | 30 | 7.16841e+07 | 554525 | 1.83181 | 1(Win) |
| glaze | 861.8 | 0.186607 | 263.202ms | 785750 | 30 | 7.89826e+07 | 869516 | 2.87254 | 2(Loss) |
| jsonifier | 817.446 | 0.129962 | 278.177ms | 785750 | 30 | 4.25801e+07 | 916696 | 3.02837 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5637.4 | 0.916869 | 22.7274ms | 399947 | 30 | 1.15447e+07 | 67658.7 | 0.438888 | 1(Win) |
| jsonifier | 4882.11 | 1.17523 | 25.6737ms | 399947 | 30 | 2.52907e+07 | 78126 | 0.506894 | 2(Loss) |
| glaze | 2058.65 | 0.763295 | 57.9261ms | 399947 | 30 | 5.99991e+07 | 185276 | 1.20236 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1861.79 | 0.802991 | 64.5058ms | 399947 | 30 | 8.11867e+07 | 204866 | 1.32929 | 1(Win) |
| glaze | 1336.28 | 0.588986 | 89.8029ms | 399947 | 30 | 8.4789e+07 | 285433 | 1.8521 | 2(Loss) |
| jsonifier | 1231.3 | 0.597048 | 97.1417ms | 399947 | 30 | 1.02617e+08 | 309771 | 2.01004 | 3(Loss) |
