# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [c210b82](https://github.com/nihilai-collective/jsonifier/commit/c210b82)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 1450.95 | 0.0953354 | 1320.54ms | 6661897 | 30 | 5.22785e+08 | 4.37872e+06 | 1.70627 | 1(Win) |
| glaze STATISTICAL TIE | 1197.31 | 0.102081 | 1591.38ms | 6661897 | 30 | 8.80229e+08 | 5.30632e+06 | 2.06774 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1194.73 | 0.0678465 | 1598.34ms | 6661897 | 30 | 3.90512e+08 | 5.31777e+06 | 2.07218 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2536.26 | 0.301201 | 166.032ms | 1439562 | 30 | 7.97459e+07 | 541298 | 0.97601 | 1(Win) |
| glaze | 1967.53 | 0.287736 | 211.685ms | 1439562 | 30 | 1.20929e+08 | 697766 | 1.25818 | 2(Loss) |
| simdjson (ondemand) | 1917.37 | 0.214846 | 216.866ms | 1439562 | 30 | 7.09949e+07 | 716021 | 1.29113 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1531.77 | 1.36726 | 20.1002ms | 94370 | 30 | 1.93598e+07 | 58754.4 | 1.61538 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1526.7 | 1.33137 | 19.9027ms | 94370 | 30 | 1.84789e+07 | 58949.5 | 1.62083 | 1(Tie) |
| glaze | 1468.94 | 0.714611 | 21.0101ms | 94370 | 30 | 5.75068e+06 | 61267.4 | 1.6846 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1931.24 | 1.46525 | 6.9608ms | 31235 | 30 | 1.53235e+06 | 15424.3 | 1.27962 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1853 | 1.78338 | 7.16608ms | 31235 | 30 | 2.46572e+06 | 16075.6 | 1.33309 | 1(Tie) |
| glaze | 1508.31 | 1.6713 | 8.39272ms | 31235 | 30 | 3.26837e+06 | 19749.3 | 1.63891 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2246.23 | 1.33056 | 29.4066ms | 213963 | 30 | 4.38291e+07 | 90841.6 | 1.1018 | 1(Win) |
| glaze | 1969.99 | 0.76198 | 78.181ms | 213963 | 40 | 2.4917e+07 | 103580 | 1.25631 | 2(Loss) |
| simdjson (ondemand) | 1289.1 | 1.23777 | 49.7617ms | 213963 | 30 | 1.15161e+08 | 158289 | 1.91997 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2248.44 | 1.97306 | 1239.99ms | 9930848 | 30 | 2.0721e+11 | 4.21216e+06 | 1.10107 | 1(Win) |
| glaze | 1757.87 | 0.0838344 | 1622.3ms | 9930848 | 30 | 6.12022e+08 | 5.38767e+06 | 1.40837 | 2(Loss) |
| simdjson (ondemand) | 697.243 | 0.100514 | 4085.21ms | 9930848 | 30 | 5.59216e+09 | 1.35832e+07 | 3.55074 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2297.65 | 0.0916279 | 1238.37ms | 9930848 | 30 | 4.2794e+08 | 4.12195e+06 | 1.07748 | 1(Win) |
| simdjson (ondemand) | 1921.42 | 0.0825875 | 1487.12ms | 9930848 | 30 | 4.97139e+08 | 4.92906e+06 | 1.28848 | 2(Loss) |
| glaze | 1752.28 | 0.087775 | 1628.72ms | 9930848 | 30 | 6.75194e+08 | 5.40484e+06 | 1.41285 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1458.26 | 0.17104 | 243.489ms | 1225964 | 30 | 5.64156e+07 | 801755 | 1.69759 | 1(Win) |
| glaze | 1431.91 | 0.198319 | 249.803ms | 1225964 | 30 | 7.86628e+07 | 816509 | 1.72885 | 2(Loss) |
| jsonifier | 1349.89 | 0.21786 | 263.94ms | 1225964 | 30 | 1.06815e+08 | 866120 | 1.83385 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1276.22 | 0.266033 | 177.546ms | 785750 | 30 | 7.31999e+07 | 587164 | 1.93971 | 1(Win) |
| jsonifier | 1176 | 0.213194 | 194.8ms | 785750 | 30 | 5.53643e+07 | 637205 | 2.10502 | 2(Loss) |
| glaze | 893.133 | 0.133563 | 254.005ms | 785750 | 30 | 3.76731e+07 | 839012 | 2.77173 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5862.6 | 1.29506 | 21.9304ms | 399947 | 30 | 2.12974e+07 | 65059.7 | 0.42209 | 1(Win) |
| simdjson (ondemand) | 5524.68 | 0.577343 | 23.1728ms | 399947 | 30 | 4.76629e+06 | 69039.2 | 0.447935 | 2(Loss) |
| glaze | 3197.51 | 0.33188 | 38.7316ms | 399947 | 30 | 4.7018e+06 | 119286 | 0.774034 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1698.5 | 0.649182 | 69.3598ms | 399947 | 30 | 6.37567e+07 | 224562 | 1.45707 | 1(Win) |
| jsonifier | 1502.21 | 0.546561 | 80.1166ms | 399947 | 30 | 5.77754e+07 | 253906 | 1.64754 | 2(Loss) |
| glaze | 1436.92 | 0.56571 | 82.4513ms | 399947 | 30 | 6.76471e+07 | 265442 | 1.72241 | 3(Loss) |
