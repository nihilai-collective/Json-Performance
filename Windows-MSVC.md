# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [62c4541](https://github.com/nihilai-collective/jsonifier/commit/62c4541)  
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
| jsonifier | 914.69 | 0.767407 | 5080.94ms | 6661897 | 40 | 1.13647e+11 | 6.94582e+06 | 2.70649 | 1(Win) |
| glaze STATISTICAL TIE | 711.832 | 1.19184 | 2702.27ms | 6661897 | 30 | 3.39465e+11 | 8.92525e+06 | 3.47783 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 709.761 | 0.674451 | 2733.16ms | 6661897 | 30 | 1.09344e+11 | 8.9513e+06 | 3.48796 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1514.3 | 0.780873 | 272.29ms | 1439562 | 30 | 1.50356e+09 | 906607 | 1.63476 | 1(Win) |
| glaze | 1336.35 | 0.25263 | 310.026ms | 1439562 | 30 | 2.02074e+08 | 1.02733e+06 | 1.85245 | 2(Loss) |
| simdjson (ondemand) | 858.371 | 0.658536 | 476.088ms | 1439562 | 30 | 3.32806e+09 | 1.59939e+06 | 2.88408 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1213.13 | 0.978782 | 22.4898ms | 94370 | 30 | 1.58177e+07 | 74186.7 | 2.0402 | 1(Win) |
| jsonifier | 896.07 | 0.629407 | 30.8052ms | 94370 | 30 | 1.19886e+07 | 100437 | 2.76201 | 2(Loss) |
| simdjson (ondemand) | 558.926 | 1.23628 | 48.1347ms | 94370 | 30 | 1.18882e+08 | 161020 | 4.42879 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1104.03 | 0.885502 | 40.5693ms | 31235 | 80 | 4.56661e+06 | 26981.2 | 2.24028 | 1(Win) |
| jsonifier | 1066.67 | 0.670939 | 42.5409ms | 31235 | 80 | 2.80854e+06 | 27926.2 | 2.31815 | 2(Loss) |
| simdjson (ondemand) | 735.144 | 1.2819 | 12.2259ms | 31235 | 30 | 8.09407e+06 | 40520 | 3.3647 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1415.12 | 0.741335 | 44.1636ms | 213963 | 30 | 3.428e+07 | 144193 | 1.74916 | 1(Tie) |
| glaze STATISTICAL TIE | 1399.97 | 0.794921 | 44.3623ms | 213963 | 30 | 4.02722e+07 | 145753 | 1.7679 | 1(Tie) |
| simdjson (ondemand) | 712.51 | 0.5601 | 85.8379ms | 213963 | 30 | 7.71876e+07 | 286383 | 3.4736 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1473.01 | 0.152101 | 1947.83ms | 9930848 | 30 | 2.86909e+09 | 6.42955e+06 | 1.68067 | 1(Win) |
| glaze | 981.425 | 0.688584 | 2911.42ms | 9930848 | 30 | 1.32463e+11 | 9.65004e+06 | 2.52249 | 2(Loss) |
| simdjson (ondemand) | 324.114 | 1.15822 | 8637.84ms | 9930848 | 30 | 3.43622e+12 | 2.92206e+07 | 7.63843 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1494.1 | 0.495806 | 1913.11ms | 9930848 | 30 | 2.96317e+10 | 6.33878e+06 | 1.65692 | 1(Win) |
| glaze | 1008.69 | 0.509714 | 2802.87ms | 9930848 | 30 | 6.87119e+10 | 9.3892e+06 | 2.45427 | 2(Loss) |
| simdjson (ondemand) | 979.42 | 0.68506 | 2933.11ms | 9930848 | 30 | 1.31647e+11 | 9.6698e+06 | 2.52756 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 965.413 | 0.286168 | 363.284ms | 1225964 | 30 | 3.60324e+08 | 1.21106e+06 | 2.56426 | 1(Win) |
| simdjson (ondemand) | 939.449 | 0.543936 | 1871.42ms | 1225964 | 80 | 3.66602e+09 | 1.24453e+06 | 2.63512 | 2(Loss) |
| glaze | 862.015 | 0.907312 | 944.017ms | 1225964 | 40 | 6.05758e+09 | 1.35632e+06 | 2.87189 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 766.284 | 0.265913 | 294.907ms | 785750 | 30 | 2.02857e+08 | 977900 | 3.2305 | 1(Win) |
| glaze | 661.111 | 0.239925 | 344.021ms | 785750 | 30 | 2.21867e+08 | 1.13347e+06 | 3.74456 | 2(Loss) |
| simdjson (ondemand) | 573.396 | 0.192081 | 395.915ms | 785750 | 30 | 1.89039e+08 | 1.30686e+06 | 4.31741 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4314.86 | 1.0687 | 26.7435ms | 399947 | 30 | 2.67734e+07 | 88396.7 | 0.573582 | 1(Win) |
| glaze | 2463.36 | 0.60455 | 46.7941ms | 399947 | 30 | 2.62865e+07 | 154837 | 1.00485 | 2(Loss) |
| simdjson (ondemand) | 2095.13 | 0.865193 | 54.756ms | 399947 | 30 | 7.44267e+07 | 182050 | 1.18139 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1065.74 | 1.18166 | 107.38ms | 399947 | 30 | 5.36547e+08 | 357890 | 2.32245 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1047.44 | 0.459564 | 553.369ms | 399947 | 80 | 2.2404e+08 | 364142 | 2.36289 | 1(Tie) |
| simdjson (ondemand) | 696.894 | 0.602786 | 164.131ms | 399947 | 30 | 3.26527e+08 | 547313 | 3.55187 | 3(Loss) |
