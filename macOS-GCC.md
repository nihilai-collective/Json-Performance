# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [b7e65b3](https://github.com/nihilai-collective/jsonifier/commit/b7e65b3)  
| Glaze: [2d38174](https://github.com/stephenberry/glaze/commit/2d38174)  
| Simdjson: [645e5c8](https://github.com/simdjson/simdjson/commit/645e5c8)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |
| Glaze (structural-skip) | `NEON64` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1407.25 | 0.133788 | 1398.73ms | 6661897 | 30 | 1.09448e+09 | 4.51468e+06 | 1(Win) |
| simdjson (ondemand) | 1378.01 | 0.163953 | 1381.13ms | 6661897 | 30 | 1.71416e+09 | 4.61047e+06 | 2(Loss) |
| glaze | 1302.24 | 0.204901 | 7685.83ms | 6661897 | 80 | 7.99453e+09 | 4.87873e+06 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2296.93 | 0.927327 | 180.272ms | 1439562 | 30 | 9.21625e+08 | 597700 | 1(Win) |
| simdjson (ondemand) | 1959.85 | 0.121999 | 1056.03ms | 1439562 | 80 | 5.84279e+07 | 700499 | 2(Loss) |
| glaze | 1868.63 | 0.594499 | 514.571ms | 1439562 | 40 | 7.6309e+08 | 734694 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1635.4 | 0.145376 | 17.2078ms | 94370 | 30 | 192013 | 55031.5 | 1(Win) |
| glaze | 1541.91 | 2.08347 | 17.908ms | 94370 | 30 | 4.43656e+07 | 58368 | 2(Loss) |
| simdjson (ondemand) | 1252.13 | 0.303414 | 20.9431ms | 94370 | 30 | 1.4268e+06 | 71876.3 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1797.52 | 0.587581 | 5.19014ms | 31235 | 30 | 284441 | 16571.7 | 1(Win) |
| glaze | 1587.44 | 0.414471 | 5.7001ms | 31235 | 30 | 181467 | 18764.8 | 2(Loss) |
| simdjson (ondemand) | 1388.93 | 0.230426 | 597.234ms | 31235 | 1280 | 3.12606e+06 | 21446.8 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2298.81 | 1.72806 | 27.0851ms | 213963 | 30 | 7.05842e+07 | 88763.7 | 1(Win) |
| glaze | 2092.79 | 0.697936 | 29.4572ms | 213963 | 30 | 1.38924e+07 | 97501.9 | 2(Loss) |
| simdjson (ondemand) | 1566.78 | 2.38166 | 39.775ms | 213963 | 30 | 2.88629e+08 | 130236 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1955.56 | 0.108762 | 1470.79ms | 9930848 | 30 | 8.32341e+08 | 4.843e+06 | 1(Win) |
| glaze | 1898.42 | 0.210578 | 3584.15ms | 9930848 | 40 | 4.41441e+09 | 4.98878e+06 | 2(Loss) |
| simdjson (ondemand) | 547.898 | 0.300517 | 11815.2ms | 9930848 | 40 | 1.07937e+11 | 1.72857e+07 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2000.76 | 0.166972 | 1438.11ms | 9930848 | 30 | 1.87411e+09 | 4.7336e+06 | 1(Win) |
| glaze | 1882.51 | 0.209434 | 1515.95ms | 9930848 | 30 | 3.33055e+09 | 5.03094e+06 | 2(Loss) |
| simdjson (ondemand) | 1636.89 | 0.503355 | 8677.33ms | 9930848 | 80 | 6.78533e+10 | 5.78584e+06 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1111.08 | 0.222828 | 202.402ms | 785750 | 30 | 6.77541e+07 | 674432 | 1(Win) |
| glaze | 1078.63 | 0.100204 | 208.578ms | 785750 | 30 | 1.45385e+07 | 694724 | 2(Loss) |
| simdjson (ondemand) | 1012.83 | 0.309252 | 221.839ms | 785750 | 30 | 1.57051e+08 | 739857 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4272.78 | 0.494838 | 27.073ms | 399947 | 30 | 5.85372e+06 | 89267.2 | 1(Win) |
| simdjson (ondemand) | 3821.94 | 0.126079 | 30.796ms | 399947 | 30 | 474948 | 99797.3 | 2(Loss) |
| glaze | 3028.7 | 0.225634 | 37.8619ms | 399947 | 30 | 2.42227e+06 | 125935 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1940 | 0.428954 | 61.206ms | 399947 | 30 | 2.13376e+07 | 196608 | 1(Win) |
| glaze | 1812.55 | 0.27046 | 63.594ms | 399947 | 30 | 9.71741e+06 | 210432 | 2(Loss) |
| simdjson (ondemand) | 1696.95 | 0.568244 | 67.3779ms | 399947 | 30 | 4.89396e+07 | 224768 | 3(Loss) |
