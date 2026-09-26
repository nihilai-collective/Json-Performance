# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [1294a69](https://github.com/nihilai-collective/jsonifier/commit/1294a69)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 697.676 | 0.940509 | 6498.84ms | 6661897 | 40 | 2.93409e+11 | 9.10634e+06 | 3.54837 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 553.174 | 0.639784 | 3503.86ms | 6661897 | 30 | 1.61979e+11 | 1.14851e+07 | 4.47518 | 2(Tie) |
| glaze STATISTICAL TIE | 545.322 | 0.85949 | 3549.03ms | 6661897 | 30 | 3.00811e+11 | 1.16505e+07 | 4.53966 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1178.47 | 0.887604 | 348.787ms | 1439562 | 30 | 3.20761e+09 | 1.16496e+06 | 2.10055 | 1(Win) |
| glaze | 1030.9 | 0.756933 | 406.783ms | 1439562 | 30 | 3.04834e+09 | 1.33172e+06 | 2.40132 | 2(Loss) |
| simdjson (ondemand) | 650.148 | 0.510636 | 633.523ms | 1439562 | 30 | 3.48804e+09 | 2.11163e+06 | 3.80772 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 944.897 | 0.923428 | 29.2551ms | 94370 | 30 | 2.32074e+07 | 95246.7 | 2.61917 | 1(Win) |
| jsonifier | 748.922 | 0.170355 | 3162ms | 94370 | 1280 | 5.36429e+07 | 120170 | 3.3046 | 2(Loss) |
| simdjson (ondemand) | 457.378 | 0.825201 | 59.7991ms | 94370 | 30 | 7.90967e+07 | 196770 | 5.41179 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 941.467 | 1.90371 | 22.422ms | 31235 | 40 | 1.45122e+07 | 31640 | 2.62657 | 1(Win) |
| glaze | 854.096 | 2.50149 | 10.7375ms | 31235 | 30 | 2.28343e+07 | 34876.7 | 2.89556 | 2(Loss) |
| simdjson (ondemand) | 584.537 | 0.111563 | 15.8689ms | 31235 | 30 | 96965.5 | 50960 | 4.23295 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1132.86 | 0.95575 | 54.7944ms | 213963 | 30 | 8.89065e+07 | 180120 | 2.18475 | 1(Win) |
| glaze | 1081.03 | 0.848028 | 57.0795ms | 213963 | 30 | 7.68681e+07 | 188757 | 2.2896 | 2(Loss) |
| simdjson (ondemand) | 590.323 | 0.624246 | 104.462ms | 213963 | 30 | 1.39679e+08 | 345660 | 4.19314 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1174.98 | 0.338569 | 13282.9ms | 9930848 | 80 | 5.95795e+10 | 8.06041e+06 | 2.10687 | 1(Win) |
| glaze | 760.651 | 1.04978 | 3715.59ms | 9930848 | 30 | 5.12534e+11 | 1.24509e+07 | 3.25451 | 2(Loss) |
| simdjson (ondemand) | 261.901 | 0.195845 | 10909ms | 9930848 | 30 | 1.50468e+11 | 3.61618e+07 | 9.45273 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1200.07 | 0.599077 | 2387.16ms | 9930848 | 30 | 6.70576e+10 | 7.89188e+06 | 2.06278 | 1(Win) |
| glaze | 797.68 | 0.463612 | 3606.71ms | 9930848 | 30 | 9.08962e+10 | 1.18729e+07 | 3.10343 | 2(Loss) |
| simdjson (ondemand) | 755.799 | 0.698494 | 3738.75ms | 9930848 | 30 | 2.2983e+11 | 1.25308e+07 | 3.2754 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 753.688 | 0.152656 | 472.848ms | 1225964 | 30 | 1.68238e+08 | 1.55127e+06 | 3.28464 | 1(Win) |
| simdjson (ondemand) | 723.419 | 1.18083 | 485.208ms | 1225964 | 30 | 1.09263e+10 | 1.61617e+06 | 3.42191 | 2(Loss) |
| glaze | 684.195 | 0.158065 | 521.284ms | 1225964 | 30 | 2.18872e+08 | 1.70883e+06 | 3.61818 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 665.064 | 0.319437 | 340.257ms | 785750 | 30 | 3.88627e+08 | 1.12673e+06 | 3.72221 | 1(Win) |
| glaze | 504.853 | 1.13609 | 456.078ms | 785750 | 30 | 8.53067e+09 | 1.48429e+06 | 4.90348 | 2(Loss) |
| simdjson (ondemand) | 455.025 | 0.251664 | 494.886ms | 785750 | 30 | 5.15301e+08 | 1.64683e+06 | 5.44023 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3220.09 | 1.14259 | 36.0473ms | 399947 | 30 | 5.49509e+07 | 118450 | 0.768606 | 1(Win) |
| glaze STATISTICAL TIE | 1838.02 | 0.801954 | 62.5539ms | 399947 | 30 | 8.30856e+07 | 207517 | 1.34667 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1814.35 | 0.758832 | 63.6923ms | 399947 | 30 | 7.63439e+07 | 210223 | 1.36425 | 2(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 902.155 | 0.632833 | 129.203ms | 399947 | 30 | 2.14754e+08 | 422787 | 2.74344 | 1(Win) |
| glaze | 840.982 | 0.583033 | 137.263ms | 399947 | 30 | 2.09768e+08 | 453540 | 2.94326 | 2(Loss) |
| simdjson (ondemand) | 563.593 | 0.338962 | 204.395ms | 399947 | 30 | 1.57869e+08 | 676763 | 4.39199 | 3(Loss) |
