# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [1294a69](https://github.com/nihilai-collective/jsonifier/commit/1294a69)  
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
| jsonifier | 1290.1 | 0.0880635 | 1492.49ms | 6661897 | 30 | 5.64242e+08 | 4.92466e+06 | 1.91895 | 1(Win) |
| simdjson (ondemand) | 1283.13 | 0.213808 | 1474.18ms | 6661897 | 30 | 3.36222e+09 | 4.95141e+06 | 1.92927 | 2(Loss) |
| glaze | 1061.64 | 0.0897691 | 9106.21ms | 6661897 | 80 | 2.3088e+09 | 5.98441e+06 | 2.33186 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2397.91 | 0.411166 | 174.469ms | 1439562 | 30 | 1.66246e+08 | 572530 | 1.03233 | 1(Win) |
| glaze | 2007.35 | 0.31537 | 207.877ms | 1439562 | 30 | 1.39565e+08 | 683922 | 1.2332 | 2(Loss) |
| jsonifier | 1842.73 | 0.29692 | 227.36ms | 1439562 | 30 | 1.46805e+08 | 745023 | 1.34339 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1608.51 | 2.28851 | 19.3228ms | 94370 | 30 | 4.91869e+07 | 55951.3 | 1.53832 | 1(Win) |
| glaze | 1462.17 | 1.68131 | 21.2405ms | 94370 | 30 | 3.21287e+07 | 61551.3 | 1.69212 | 2(Loss) |
| jsonifier | 1247.81 | 1.22185 | 24.2909ms | 94370 | 30 | 2.32985e+07 | 72125 | 1.98278 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2016.38 | 1.41624 | 6.70311ms | 31235 | 30 | 1.31321e+06 | 14773 | 1.22546 | 1(Win) |
| glaze | 1481.13 | 2.15602 | 8.59031ms | 31235 | 30 | 5.64056e+06 | 20111.7 | 1.66899 | 2(Loss) |
| jsonifier | 1395.02 | 0.159713 | 8.88584ms | 31235 | 30 | 34891.8 | 21353.1 | 1.77209 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2321.87 | 2.47874 | 28.1557ms | 213963 | 30 | 1.42359e+08 | 87882.4 | 1.0659 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2214.74 | 2.40532 | 29.699ms | 213963 | 30 | 1.47332e+08 | 92133 | 1.1172 | 1(Tie) |
| glaze | 1769.66 | 1.13915 | 37.4708ms | 213963 | 30 | 5.17581e+07 | 115305 | 1.39857 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2024.88 | 0.344579 | 1395.6ms | 9930848 | 30 | 7.79248e+09 | 4.67722e+06 | 1.22246 | 1(Win) |
| glaze | 1528.98 | 0.174917 | 1904.25ms | 9930848 | 30 | 3.52173e+09 | 6.19419e+06 | 1.61909 | 2(Loss) |
| simdjson (ondemand) | 537.85 | 0.356198 | 5279.89ms | 9930848 | 30 | 1.18019e+11 | 1.76086e+07 | 4.60306 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1995.59 | 0.375966 | 1409.05ms | 9930848 | 30 | 9.55094e+09 | 4.74585e+06 | 1.24041 | 1(Win) |
| simdjson (ondemand) | 1863.16 | 0.201028 | 1558.28ms | 9930848 | 30 | 3.13262e+09 | 5.08319e+06 | 1.32871 | 2(Loss) |
| glaze | 1502.75 | 0.235966 | 1927.3ms | 9930848 | 30 | 6.63465e+09 | 6.30229e+06 | 1.6474 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1514.52 | 1.04149 | 231.563ms | 1225964 | 30 | 1.93927e+09 | 771976 | 1.63453 | 1(Win) |
| jsonifier | 1215.04 | 0.301266 | 292.114ms | 1225964 | 30 | 2.52113e+08 | 962249 | 2.03746 | 2(Loss) |
| glaze | 1169.42 | 0.362111 | 299.994ms | 1225964 | 30 | 3.93202e+08 | 999782 | 2.11685 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1339.17 | 0.57226 | 171.457ms | 785750 | 30 | 3.07615e+08 | 559564 | 1.84843 | 1(Win) |
| glaze | 883.36 | 0.229498 | 258.17ms | 785750 | 30 | 1.13704e+08 | 848295 | 2.80246 | 2(Loss) |
| jsonifier | 813.042 | 0.243998 | 278.754ms | 785750 | 30 | 1.51719e+08 | 921662 | 3.04475 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5692.91 | 1.09651 | 22.4904ms | 399947 | 30 | 1.61912e+07 | 66999 | 0.434691 | 1(Win) |
| jsonifier | 4888.8 | 1.62214 | 25.706ms | 399947 | 30 | 4.80503e+07 | 78018.9 | 0.506207 | 2(Loss) |
| glaze | 2061.72 | 0.870258 | 57.8476ms | 399947 | 30 | 7.77609e+07 | 185000 | 1.20063 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1817.88 | 1.08951 | 65.4592ms | 399947 | 30 | 1.56768e+08 | 209816 | 1.36152 | 1(Win) |
| glaze | 1313.5 | 1.09149 | 88.9879ms | 399947 | 30 | 3.01375e+08 | 290384 | 1.88435 | 2(Loss) |
| jsonifier | 1207.82 | 0.710652 | 238.452ms | 399947 | 40 | 2.01454e+08 | 315792 | 2.04928 | 3(Loss) |
