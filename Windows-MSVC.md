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

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 750.883 | 0.543548 | 13439.2ms | 6661897 | 80 | 1.69206e+11 | 8.46108e+06 | 3.10569 | 1(Win) |
| simdjson (ondemand) | 601.374 | 0.575442 | 3178.36ms | 6661897 | 30 | 1.10874e+11 | 1.05646e+07 | 3.87764 | 2(Loss) |
| glaze | 591.161 | 0.450581 | 3275.86ms | 6661897 | 30 | 7.0348e+10 | 1.07471e+07 | 3.94472 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1223.97 | 0.633225 | 786.308ms | 1439562 | 40 | 2.01789e+09 | 1.12166e+06 | 1.90522 | 1(Win) |
| glaze | 1019.97 | 0.268842 | 411.84ms | 1439562 | 30 | 3.92825e+08 | 1.34599e+06 | 2.28626 | 2(Loss) |
| simdjson (ondemand) | 707.652 | 0.2006 | 12582.4ms | 1439562 | 320 | 4.84654e+09 | 1.94004e+06 | 3.29533 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 886.653 | 1.43929 | 30.6809ms | 94370 | 30 | 6.40293e+07 | 101503 | 2.62836 | 1(Win) |
| jsonifier | 754.323 | 1.63888 | 36.1663ms | 94370 | 30 | 1.14701e+08 | 119310 | 3.08984 | 2(Loss) |
| simdjson (ondemand) | 479.514 | 0.586201 | 301.837ms | 94370 | 80 | 9.68384e+07 | 187686 | 4.86188 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 891.79 | 1.95161 | 23.654ms | 31235 | 40 | 1.69982e+07 | 33402.5 | 2.61093 | 1(Win) |
| glaze | 780.327 | 1.59769 | 58.9919ms | 31235 | 80 | 2.97579e+07 | 38173.8 | 2.9853 | 2(Loss) |
| simdjson (ondemand) | 615.964 | 1.91764 | 14.5633ms | 31235 | 30 | 2.58004e+07 | 48360 | 3.78284 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1153.16 | 0.837861 | 54.4405ms | 213963 | 30 | 6.59426e+07 | 176950 | 2.02168 | 1(Win) |
| glaze | 974.44 | 1.25649 | 62.7842ms | 213963 | 30 | 2.07684e+08 | 209403 | 2.39219 | 2(Loss) |
| simdjson (ondemand) | 614.026 | 0.63604 | 100.086ms | 213963 | 30 | 1.34028e+08 | 332317 | 3.79737 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1224.64 | 0.60501 | 2336.09ms | 9930848 | 30 | 6.56752e+10 | 7.73352e+06 | 1.90416 | 1(Win) |
| glaze | 796.471 | 0.506684 | 3595.89ms | 9930848 | 30 | 1.089e+11 | 1.1891e+07 | 2.92785 | 2(Loss) |
| simdjson (ondemand) | 268.501 | 0.152715 | 10634.4ms | 9930848 | 30 | 8.7049e+10 | 3.52728e+07 | 8.68531 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1249.07 | 0.369341 | 2300.41ms | 9930848 | 30 | 2.35277e+10 | 7.5823e+06 | 1.86694 | 1(Win) |
| glaze | 833.776 | 0.351261 | 3423.49ms | 9930848 | 30 | 4.77589e+10 | 1.13589e+07 | 2.79686 | 2(Loss) |
| simdjson (ondemand) | 801.872 | 0.499294 | 3534.8ms | 9930848 | 30 | 1.04327e+11 | 1.18109e+07 | 2.90794 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 770.453 | 1.94598 | 459.235ms | 1225964 | 30 | 2.61615e+10 | 1.51751e+06 | 3.0267 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 767.807 | 0.211337 | 472.608ms | 1225964 | 30 | 3.10687e+08 | 1.52274e+06 | 3.03711 | 1(Tie) |
| glaze | 729.55 | 0.418324 | 2417.07ms | 1225964 | 80 | 3.59552e+09 | 1.60259e+06 | 3.19634 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 646.247 | 0.459832 | 835.875ms | 785750 | 40 | 1.13718e+09 | 1.15954e+06 | 3.60838 | 1(Win) |
| glaze STATISTICAL TIE | 491.126 | 0.93179 | 455.312ms | 785750 | 30 | 6.06375e+09 | 1.52578e+06 | 4.74811 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 486.333 | 0.173035 | 469.198ms | 785750 | 30 | 2.1325e+08 | 1.54082e+06 | 4.79501 | 2(Tie) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2904.43 | 1.21435 | 39.6745ms | 399947 | 30 | 7.6295e+07 | 131323 | 0.802601 | 1(Win) |
| simdjson (ondemand) | 1899.78 | 0.816414 | 60.4718ms | 399947 | 30 | 8.06008e+07 | 200770 | 1.22722 | 2(Loss) |
| glaze | 1627.86 | 0.898375 | 70.1118ms | 399947 | 30 | 1.32925e+08 | 234307 | 1.43211 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 820.58 | 1.15268 | 153.729ms | 399947 | 30 | 8.61193e+08 | 464817 | 2.84113 | 1(Win) |
| glaze | 771.181 | 0.750661 | 736.282ms | 399947 | 80 | 1.10273e+09 | 494591 | 3.0234 | 2(Loss) |
| simdjson (ondemand) | 605.123 | 0.554815 | 197.229ms | 399947 | 30 | 3.66889e+08 | 630317 | 3.8533 | 3(Loss) |
