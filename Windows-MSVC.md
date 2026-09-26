# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

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

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1202.03 | 0.405235 | 345.062ms | 1439562 | 30 | 6.4264e+08 | 1.14213e+06 | 1.93998 | 1(Win) |
| glaze | 1022.49 | 0.3093 | 420.95ms | 1439562 | 30 | 5.17393e+08 | 1.34267e+06 | 2.28068 | 2(Loss) |
| simdjson (ondemand) | 702.065 | 0.470657 | 587.183ms | 1439562 | 30 | 2.54119e+09 | 1.95548e+06 | 3.32162 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 896.14 | 0.974685 | 151.038ms | 94370 | 80 | 7.6654e+07 | 100429 | 2.60041 | 1(Win) |
| jsonifier | 745.43 | 1.52535 | 37.2207ms | 94370 | 30 | 1.01745e+08 | 120733 | 3.12697 | 2(Loss) |
| simdjson (ondemand) | 460.6 | 0.936038 | 58.917ms | 94370 | 30 | 1.00352e+08 | 195393 | 5.06133 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 858.939 | 2.58864 | 10.7501ms | 31235 | 30 | 2.41782e+07 | 34680 | 2.71209 | 1(Win) |
| glaze | 772.724 | 1.26943 | 135.172ms | 31235 | 160 | 3.83151e+07 | 38549.4 | 3.01452 | 2(Loss) |
| simdjson (ondemand) | 627.645 | 0.074649 | 14.5967ms | 31235 | 30 | 37655.2 | 47460 | 3.71209 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1126.25 | 1.1865 | 55.2821ms | 213963 | 30 | 1.38632e+08 | 181177 | 2.06997 | 1(Win) |
| glaze | 965.77 | 1.25598 | 63.429ms | 213963 | 30 | 2.11261e+08 | 211283 | 2.41416 | 2(Loss) |
| simdjson (ondemand) | 624.946 | 0.712822 | 98.2944ms | 213963 | 30 | 1.62509e+08 | 326510 | 3.7308 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1191.48 | 0.129664 | 2440ms | 9930848 | 30 | 3.18684e+09 | 7.94876e+06 | 1.95715 | 1(Win) |
| glaze | 777.246 | 0.79765 | 3630.37ms | 9930848 | 30 | 2.83401e+11 | 1.21851e+07 | 3.00019 | 2(Loss) |
| simdjson (ondemand) | 260.645 | 0.666955 | 10851.5ms | 9930848 | 30 | 1.76194e+12 | 3.6336e+07 | 8.94712 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1209.64 | 0.490351 | 2355.72ms | 9930848 | 30 | 4.42176e+10 | 7.82943e+06 | 1.92775 | 1(Win) |
| simdjson (ondemand) | 815.848 | 0.462951 | 3526.65ms | 9930848 | 30 | 8.66455e+10 | 1.16085e+07 | 2.8583 | 2(Loss) |
| glaze | 791.901 | 0.533128 | 3568.6ms | 9930848 | 30 | 1.2196e+11 | 1.19596e+07 | 2.94471 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 781.461 | 0.202544 | 449.98ms | 1225964 | 30 | 2.75487e+08 | 1.49613e+06 | 2.98417 | 1(Win) |
| simdjson (ondemand) | 764.42 | 0.491978 | 2311.04ms | 1225964 | 80 | 4.52974e+09 | 1.52949e+06 | 3.0507 | 2(Loss) |
| glaze | 719.447 | 0.157925 | 490.832ms | 1225964 | 30 | 1.97598e+08 | 1.6251e+06 | 3.24141 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 644.365 | 0.304976 | 350.094ms | 785750 | 30 | 3.77361e+08 | 1.16293e+06 | 3.619 | 1(Win) |
| glaze STATISTICAL TIE | 504.744 | 1.22019 | 443.444ms | 785750 | 30 | 9.84475e+09 | 1.48461e+06 | 4.6201 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 492.78 | 0.193888 | 457.982ms | 785750 | 30 | 2.60787e+08 | 1.52066e+06 | 4.73235 | 2(Tie) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2861.5 | 1.08651 | 40.2776ms | 399947 | 30 | 6.29227e+07 | 133293 | 0.814617 | 1(Win) |
| simdjson (ondemand) | 1899.81 | 0.849781 | 60.788ms | 399947 | 30 | 8.73209e+07 | 200767 | 1.22696 | 2(Loss) |
| glaze | 1572.41 | 0.735799 | 73.6747ms | 399947 | 30 | 9.55684e+07 | 242570 | 1.48274 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 825.77 | 0.96472 | 358.909ms | 399947 | 40 | 7.94236e+08 | 461895 | 2.82358 | 1(Win) |
| glaze | 774.483 | 0.355072 | 1580.94ms | 399947 | 160 | 4.89254e+08 | 492482 | 3.01061 | 2(Loss) |
| simdjson (ondemand) | 599.43 | 0.668809 | 192.999ms | 399947 | 30 | 5.43318e+08 | 636303 | 3.88993 | 3(Loss) |
