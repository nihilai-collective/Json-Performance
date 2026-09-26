# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [48b1541](https://github.com/nihilai-collective/jsonifier/commit/48b1541)  
| Glaze: [99fcc35](https://github.com/stephenberry/glaze/commit/99fcc35)  
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
| jsonifier | 1189.91 | 0.0937809 | 1611.78ms | 6661897 | 30 | 7.52168e+08 | 5.33928e+06 | 1.95989 | 1(Win) |
| glaze | 965.697 | 0.0846764 | 2089.47ms | 6661897 | 30 | 9.31022e+08 | 6.57896e+06 | 2.41496 | 2(Loss) |
| simdjson (ondemand) | 959.822 | 0.178581 | 1985.78ms | 6661897 | 30 | 4.19187e+09 | 6.61923e+06 | 2.4297 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1868.86 | 0.353547 | 224.142ms | 1439562 | 30 | 2.02358e+08 | 734603 | 1.24779 | 1(Win) |
| glaze | 1551.92 | 0.134354 | 270.284ms | 1439562 | 30 | 4.23785e+07 | 884628 | 1.50265 | 2(Loss) |
| simdjson (ondemand) | 1361.53 | 0.329682 | 304.802ms | 1439562 | 30 | 3.31525e+08 | 1.00833e+06 | 1.71277 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1176.38 | 2.02611 | 25.5506ms | 94370 | 30 | 7.20811e+07 | 76504.6 | 1.98083 | 1(Win) |
| glaze | 1095.12 | 2.04516 | 27.1275ms | 94370 | 30 | 8.47453e+07 | 82180.8 | 2.12782 | 2(Loss) |
| simdjson (ondemand) | 1039.85 | 0.862461 | 28.6418ms | 94370 | 30 | 1.67159e+07 | 86549.6 | 2.24136 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1433.35 | 0.180192 | 8.9538ms | 31235 | 30 | 42069.9 | 20782.1 | 1.62408 | 1(Win) |
| simdjson (ondemand) | 1355.79 | 0.0980812 | 9.15592ms | 31235 | 30 | 13931.3 | 21971 | 1.71732 | 2(Loss) |
| glaze | 1100.73 | 2.61406 | 10.4969ms | 31235 | 30 | 1.50133e+07 | 27062.1 | 2.11562 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1705.61 | 1.22678 | 38.7588ms | 213963 | 30 | 6.46214e+07 | 119635 | 1.36663 | 1(Win) |
| glaze STATISTICAL TIE | 1423.18 | 1.11558 | 45.5683ms | 213963 | 30 | 7.67507e+07 | 143377 | 1.63808 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1397.93 | 0.994397 | 46.5736ms | 213963 | 30 | 6.32044e+07 | 145967 | 1.6677 | 2(Tie) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1879.41 | 0.100641 | 1522.13ms | 9930848 | 30 | 7.71619e+08 | 5.03925e+06 | 1.24083 | 1(Win) |
| glaze | 1345.22 | 0.0884069 | 2120.84ms | 9930848 | 30 | 1.16219e+09 | 7.04032e+06 | 1.73361 | 2(Loss) |
| simdjson (ondemand) | 548.074 | 0.201696 | 5169.46ms | 9930848 | 30 | 3.64428e+10 | 1.72802e+07 | 4.25508 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1835.3 | 0.064684 | 1553.41ms | 9930848 | 30 | 3.34253e+08 | 5.16036e+06 | 1.27066 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1377.11 | 1.30535 | 2037.4ms | 9930848 | 30 | 2.41775e+11 | 6.87732e+06 | 1.69346 | 2(Tie) |
| glaze STATISTICAL TIE | 1370.14 | 0.0701304 | 2083.23ms | 9930848 | 30 | 7.04984e+08 | 6.9123e+06 | 1.7021 | 2(Tie) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1146.03 | 0.207202 | 309.254ms | 1225964 | 30 | 1.34051e+08 | 1.02019e+06 | 2.03484 | 1(Win) |
| jsonifier | 1135.3 | 0.0742987 | 311.999ms | 1225964 | 30 | 1.75639e+07 | 1.02984e+06 | 2.05408 | 2(Loss) |
| simdjson (ondemand) | 1073.35 | 0.205176 | 329.659ms | 1225964 | 30 | 1.49846e+08 | 1.08927e+06 | 2.17264 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 867.247 | 0.215908 | 261.676ms | 785750 | 30 | 1.0441e+08 | 864055 | 2.68895 | 1(Win) |
| jsonifier | 861.861 | 0.192351 | 262.581ms | 785750 | 30 | 8.39083e+07 | 869456 | 2.70576 | 2(Loss) |
| glaze | 694.139 | 0.176693 | 326.876ms | 785750 | 30 | 1.09153e+08 | 1.07954e+06 | 3.35957 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3658.96 | 1.52411 | 33.845ms | 399947 | 30 | 7.57258e+07 | 104243 | 0.637023 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3540.56 | 1.17348 | 34.7676ms | 399947 | 30 | 4.79442e+07 | 107728 | 0.658272 | 1(Tie) |
| glaze | 2321.16 | 0.988946 | 51.7449ms | 399947 | 30 | 7.92246e+07 | 164322 | 1.00437 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1122.91 | 2.30711 | 100.767ms | 399947 | 30 | 1.84234e+09 | 339670 | 2.07641 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1108.62 | 0.78653 | 106.142ms | 399947 | 30 | 2.19678e+08 | 344047 | 2.10321 | 1(Tie) |
| glaze | 1065.67 | 0.61587 | 110.504ms | 399947 | 30 | 1.45768e+08 | 357916 | 2.18805 | 3(Loss) |
