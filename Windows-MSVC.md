# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [0c74f7f](https://github.com/nihilai-collective/jsonifier/commit/0c74f7f)  
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

> Adaptive sampling on (AMD EPYC 9V45 96-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 634.619 | 0.81201 | 7158.57ms | 6661897 | 40 | 2.64333e+11 | 1.00112e+07 | 3.90126 | 1(Win) |
| simdjson (ondemand) | 569.78 | 0.491836 | 3351.69ms | 6661897 | 30 | 9.02283e+10 | 1.11504e+07 | 4.34522 | 2(Loss) |
| glaze | 543.357 | 0.392592 | 3555.8ms | 6661897 | 30 | 6.32164e+10 | 1.16926e+07 | 4.55651 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1993.44 | 0.871306 | 209.577ms | 1439562 | 30 | 1.08024e+09 | 688697 | 1.24191 | 1(Win) |
| glaze | 1795.27 | 0.218605 | 232.405ms | 1439562 | 30 | 8.38387e+07 | 764717 | 1.37899 | 2(Loss) |
| simdjson (ondemand) | 1133.24 | 0.194707 | 1828ms | 1439562 | 80 | 4.45115e+08 | 1.21146e+06 | 2.18466 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1625.4 | 0.813425 | 16.9757ms | 94370 | 30 | 6.08562e+06 | 55370 | 1.52259 | 1(Win) |
| jsonifier | 1261.13 | 0.852696 | 21.7295ms | 94370 | 30 | 1.11086e+07 | 71363.3 | 1.96223 | 2(Loss) |
| simdjson (ondemand) | 840.451 | 0.555425 | 32.1782ms | 94370 | 30 | 1.06125e+07 | 107083 | 2.94451 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1563.68 | 1.56851 | 5.9195ms | 31235 | 30 | 2.67845e+06 | 19050 | 1.58092 | 1(Tie) |
| glaze STATISTICAL TIE | 1546.09 | 0.156073 | 5.9715ms | 31235 | 30 | 27126.4 | 19266.7 | 1.60031 | 1(Tie) |
| simdjson (ondemand) | 1040.93 | 1.51739 | 8.5279ms | 31235 | 30 | 5.65661e+06 | 28616.7 | 2.37289 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1692.06 | 0.744772 | 36.0552ms | 213963 | 30 | 2.42e+07 | 120593 | 1.4628 | 1(Win) |
| glaze | 1608.18 | 1.63416 | 37.6054ms | 213963 | 30 | 1.28979e+08 | 126883 | 1.53934 | 2(Loss) |
| simdjson (ondemand) | 987.678 | 0.831437 | 62.8012ms | 213963 | 30 | 8.85169e+07 | 206597 | 2.50625 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1394.97 | 0.0343834 | 2054.94ms | 9930848 | 30 | 1.6348e+08 | 6.78926e+06 | 1.77482 | 1(Win) |
| glaze | 985.078 | 0.437585 | 14648.5ms | 9930848 | 80 | 1.41594e+11 | 9.61426e+06 | 2.51331 | 2(Loss) |
| simdjson (ondemand) | 459.897 | 0.343001 | 6143.3ms | 9930848 | 30 | 1.4968e+11 | 2.05933e+07 | 5.38342 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1398.98 | 0.423112 | 2026.89ms | 9930848 | 30 | 2.46141e+10 | 6.76979e+06 | 1.76973 | 1(Win) |
| simdjson (ondemand) | 1023.48 | 0.918979 | 2757.53ms | 9930848 | 30 | 2.16945e+11 | 9.25355e+06 | 2.41899 | 2(Loss) |
| glaze | 992.108 | 0.762042 | 2850.16ms | 9930848 | 30 | 1.58757e+11 | 9.54613e+06 | 2.49548 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1008.58 | 0.622042 | 814.77ms | 1225964 | 40 | 2.07987e+09 | 1.15922e+06 | 2.45466 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1005.7 | 0.107913 | 351.123ms | 1225964 | 30 | 4.72156e+07 | 1.16254e+06 | 2.46175 | 1(Tie) |
| glaze | 907.572 | 0.347491 | 387.046ms | 1225964 | 30 | 6.01176e+08 | 1.28824e+06 | 2.72788 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1108.08 | 0.276681 | 205.215ms | 785750 | 30 | 1.05029e+08 | 676260 | 2.23418 | 1(Win) |
| glaze | 911.932 | 0.485279 | 248.124ms | 785750 | 30 | 4.77033e+08 | 821717 | 2.71475 | 2(Loss) |
| simdjson (ondemand) | 834.877 | 0.267138 | 270.873ms | 785750 | 30 | 1.72471e+08 | 897557 | 2.9654 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6405.38 | 0.6565 | 18.1512ms | 399947 | 30 | 4.58464e+06 | 59546.7 | 0.386331 | 1(Win) |
| glaze | 3324.01 | 0.720243 | 34.4233ms | 399947 | 30 | 2.04909e+07 | 114747 | 0.744573 | 2(Loss) |
| simdjson (ondemand) | 3254.99 | 0.405498 | 35.0966ms | 399947 | 30 | 6.77338e+06 | 117180 | 0.760501 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1503.39 | 0.919809 | 76.6383ms | 399947 | 30 | 1.63373e+08 | 253707 | 1.64654 | 1(Win) |
| glaze | 1455.95 | 0.390566 | 79.0102ms | 399947 | 30 | 3.14069e+07 | 261973 | 1.70024 | 2(Loss) |
| simdjson (ondemand) | 961.997 | 0.379232 | 118.756ms | 399947 | 30 | 6.78246e+07 | 396487 | 2.57326 | 3(Loss) |
