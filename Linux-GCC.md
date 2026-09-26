# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

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
| jsonifier STATISTICAL TIE | 1026.42 | 0.120904 | 1952.09ms | 6661897 | 30 | 1.68014e+09 | 6.18973e+06 | 2.27205 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1019.44 | 1.56014 | 2006.75ms | 6661897 | 30 | 2.83609e+11 | 6.23212e+06 | 2.28763 | 1(Tie) |
| glaze | 887.473 | 0.121435 | 2149.83ms | 6661897 | 30 | 2.26722e+09 | 7.15884e+06 | 2.62782 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1587.5 | 0.33114 | 263.065ms | 1439562 | 30 | 2.46025e+08 | 864803 | 1.46897 | 1(Win) |
| glaze | 1451.18 | 0.730975 | 285.633ms | 1439562 | 30 | 1.43465e+09 | 946040 | 1.60687 | 2(Loss) |
| jsonifier | 1157.29 | 0.213506 | 358.79ms | 1439562 | 30 | 1.9245e+08 | 1.18628e+06 | 2.01507 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1129.04 | 1.61938 | 26.6209ms | 94370 | 30 | 4.99888e+07 | 79712.5 | 2.06416 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1072.51 | 1.53437 | 27.8981ms | 94370 | 30 | 4.97335e+07 | 83914 | 2.17313 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1029.96 | 2.89461 | 28.4489ms | 94370 | 30 | 1.91923e+08 | 87380.1 | 2.26275 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1311.47 | 3.10146 | 45.567ms | 31235 | 80 | 3.96995e+07 | 22713.4 | 1.77537 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1247.54 | 0.0729502 | 9.81329ms | 31235 | 30 | 9102.25 | 23877.4 | 1.86637 | 1(Tie) |
| glaze | 1108.05 | 2.02359 | 10.4145ms | 31235 | 30 | 8.87821e+06 | 26883.2 | 2.10176 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1461.02 | 0.96278 | 44.7659ms | 213963 | 30 | 5.42424e+07 | 139663 | 1.59555 | 1(Win) |
| simdjson (ondemand) | 1404.73 | 0.910172 | 45.4879ms | 213963 | 30 | 5.244e+07 | 145260 | 1.65956 | 2(Loss) |
| glaze | 1346.52 | 0.669232 | 48.3436ms | 213963 | 30 | 3.08552e+07 | 151540 | 1.73133 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1583.22 | 0.151543 | 1794.18ms | 9930848 | 30 | 2.46538e+09 | 5.98199e+06 | 1.47299 | 1(Win) |
| glaze | 1286.16 | 0.203769 | 2207.57ms | 9930848 | 30 | 6.75436e+09 | 7.36364e+06 | 1.81324 | 2(Loss) |
| simdjson (ondemand) | 450.564 | 0.711804 | 6206.76ms | 9930848 | 30 | 6.71586e+11 | 2.10199e+07 | 5.17596 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1558.21 | 0.151721 | 1828.48ms | 9930848 | 30 | 2.55115e+09 | 6.07801e+06 | 1.49666 | 1(Win) |
| simdjson (ondemand) | 1441.52 | 0.118066 | 2003.92ms | 9930848 | 30 | 1.8051e+09 | 6.57001e+06 | 1.61779 | 2(Loss) |
| glaze | 1287.79 | 0.108198 | 2204.38ms | 9930848 | 30 | 1.8995e+09 | 7.35431e+06 | 1.81093 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1146.53 | 0.111479 | 308.806ms | 1225964 | 30 | 3.87696e+07 | 1.01974e+06 | 2.03399 | 1(Win) |
| glaze | 999.266 | 0.276209 | 355.367ms | 1225964 | 30 | 3.13323e+08 | 1.17003e+06 | 2.33372 | 2(Loss) |
| jsonifier | 895.426 | 0.662956 | 394.786ms | 1225964 | 30 | 2.24796e+09 | 1.30571e+06 | 2.60433 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 933.803 | 0.164365 | 243.394ms | 785750 | 30 | 5.21912e+07 | 802471 | 2.49729 | 1(Win) |
| jsonifier | 786.159 | 0.30669 | 288.806ms | 785750 | 30 | 2.5637e+08 | 953178 | 2.96634 | 2(Loss) |
| glaze | 684.413 | 0.332937 | 331.446ms | 785750 | 30 | 3.98637e+08 | 1.09488e+06 | 3.40734 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3280.15 | 1.2326 | 37.0771ms | 399947 | 30 | 6.16287e+07 | 116281 | 0.710698 | 1(Win) |
| jsonifier | 2996.86 | 0.905602 | 41.0292ms | 399947 | 30 | 3.98538e+07 | 127273 | 0.777796 | 2(Loss) |
| glaze | 1541.2 | 0.601103 | 76.5953ms | 399947 | 30 | 6.63902e+07 | 247481 | 1.51265 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1207.66 | 0.697331 | 97.1598ms | 399947 | 30 | 1.45518e+08 | 315833 | 1.93081 | 1(Win) |
| jsonifier | 994.006 | 0.863088 | 117.73ms | 399947 | 30 | 3.29047e+08 | 383719 | 2.34557 | 2(Loss) |
| glaze | 971.532 | 0.4461 | 120.692ms | 399947 | 30 | 9.2019e+07 | 392596 | 2.40014 | 3(Loss) |
