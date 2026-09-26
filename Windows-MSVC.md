# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 920.636 | 0.543614 | 10689.2ms | 6661897 | 80 | 1.12588e+11 | 6.90097e+06 | 2.68909 | 1(Win) |
| glaze STATISTICAL TIE | 712.397 | 0.976041 | 2640.61ms | 6661897 | 30 | 2.27305e+11 | 8.91818e+06 | 3.47498 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 698.815 | 1.50699 | 2647.54ms | 6661897 | 30 | 5.63135e+11 | 9.09151e+06 | 3.54233 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1526.84 | 0.814841 | 271.122ms | 1439562 | 30 | 1.61043e+09 | 899160 | 1.62131 | 1(Win) |
| glaze | 1320.09 | 0.360561 | 313.153ms | 1439562 | 30 | 4.21824e+08 | 1.03998e+06 | 1.87532 | 2(Loss) |
| simdjson (ondemand) | 849.724 | 0.118789 | 489.425ms | 1439562 | 30 | 1.10504e+08 | 1.61567e+06 | 2.91345 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1231 | 0.822496 | 22.3662ms | 94370 | 30 | 1.08478e+07 | 73110 | 2.01034 | 1(Win) |
| jsonifier | 898.365 | 0.943725 | 30.5583ms | 94370 | 30 | 2.68148e+07 | 100180 | 2.75541 | 2(Loss) |
| simdjson (ondemand) | 608.302 | 0.903454 | 44.8033ms | 94370 | 30 | 5.35998e+07 | 147950 | 4.06886 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1099.19 | 1.93403 | 18.9007ms | 31235 | 40 | 1.09882e+07 | 27100 | 2.25008 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1056.44 | 1.68672 | 8.7167ms | 31235 | 30 | 6.78585e+06 | 28196.7 | 2.34059 | 1(Tie) |
| simdjson (ondemand) | 714.113 | 1.27123 | 12.5337ms | 31235 | 30 | 8.43568e+06 | 41713.3 | 3.46345 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1388.1 | 0.858243 | 44.4423ms | 213963 | 30 | 4.77503e+07 | 147000 | 1.783 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1372.97 | 0.929304 | 45.5234ms | 213963 | 30 | 5.72258e+07 | 148620 | 1.8027 | 1(Tie) |
| simdjson (ondemand) | 751.256 | 0.41406 | 81.8551ms | 213963 | 30 | 3.79446e+07 | 271613 | 3.29488 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1476.81 | 0.222051 | 1941.17ms | 9930848 | 30 | 6.08343e+09 | 6.413e+06 | 1.67626 | 1(Win) |
| glaze | 1029.94 | 0.296905 | 14181.1ms | 9930848 | 80 | 5.96309e+10 | 9.19545e+06 | 2.40352 | 2(Loss) |
| simdjson (ondemand) | 327.817 | 0.233607 | 8654.89ms | 9930848 | 30 | 1.36648e+11 | 2.88905e+07 | 7.5521 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1532.79 | 0.254861 | 1863.73ms | 9930848 | 30 | 7.43934e+09 | 6.17878e+06 | 1.6151 | 1(Win) |
| glaze | 1027.03 | 0.381981 | 2750.85ms | 9930848 | 30 | 3.72227e+10 | 9.22149e+06 | 2.41042 | 2(Loss) |
| simdjson (ondemand) | 1004.75 | 0.51177 | 2876.17ms | 9930848 | 30 | 6.98111e+10 | 9.42598e+06 | 2.46381 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 953.854 | 0.461844 | 381.719ms | 1225964 | 30 | 9.61401e+08 | 1.22573e+06 | 2.59526 | 1(Tie) |
| jsonifier STATISTICAL TIE | 952.238 | 0.194001 | 369.819ms | 1225964 | 30 | 1.70213e+08 | 1.22781e+06 | 2.59975 | 1(Tie) |
| glaze | 848.147 | 1.59893 | 403.8ms | 1225964 | 30 | 1.45745e+10 | 1.3785e+06 | 2.91877 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 762.377 | 0.65913 | 686.012ms | 785750 | 40 | 1.67893e+09 | 982912 | 3.24701 | 1(Win) |
| glaze | 663.429 | 0.329727 | 341.372ms | 785750 | 30 | 4.16113e+08 | 1.12951e+06 | 3.73125 | 2(Loss) |
| simdjson (ondemand) | 578.467 | 0.52453 | 389.389ms | 785750 | 30 | 1.38508e+09 | 1.29541e+06 | 4.27936 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4315.35 | 0.94713 | 27.0741ms | 399947 | 30 | 2.1024e+07 | 88386.7 | 0.573473 | 1(Win) |
| glaze | 2462.94 | 0.704882 | 47.044ms | 399947 | 30 | 3.57479e+07 | 154863 | 1.00487 | 2(Loss) |
| simdjson (ondemand) | 2109.58 | 0.510386 | 54.9494ms | 399947 | 30 | 2.55465e+07 | 180803 | 1.17316 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1090.52 | 0.630435 | 106.007ms | 399947 | 30 | 1.45862e+08 | 349760 | 2.26981 | 1(Win) |
| jsonifier | 1057 | 0.757823 | 109.904ms | 399947 | 30 | 2.24342e+08 | 360850 | 2.34152 | 2(Loss) |
| simdjson (ondemand) | 712.414 | 0.426036 | 161.687ms | 399947 | 30 | 1.56082e+08 | 535390 | 3.47457 | 3(Loss) |
