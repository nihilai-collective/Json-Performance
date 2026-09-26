# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [e6f566c](https://github.com/nihilai-collective/jsonifier/commit/e6f566c)  
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

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1454.11 | 0.826305 | 1336.9ms | 6661897 | 30 | 3.91026e+10 | 4.36919e+06 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1060.91 | 2.84661 | 1845.16ms | 6661897 | 30 | 8.71793e+11 | 5.98851e+06 | 2(Tie) |
| glaze STATISTICAL TIE | 1032.7 | 1.19497 | 4015.02ms | 6661897 | 40 | 2.16183e+11 | 6.15211e+06 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2273.87 | 1.98745 | 371.323ms | 1439562 | 40 | 5.75944e+09 | 603759 | 1(Win) |
| glaze | 1990.31 | 0.486553 | 9264.84ms | 1439562 | 640 | 7.20878e+09 | 689779 | 2(Loss) |
| simdjson (ondemand) | 1665.55 | 0.761644 | 548.286ms | 1439562 | 40 | 1.57656e+09 | 824277 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1718.02 | 1.33558 | 16.9548ms | 94370 | 30 | 1.4685e+07 | 52384.7 | 1(Win) |
| glaze | 1584.83 | 1.29139 | 17.9425ms | 94370 | 30 | 1.61339e+07 | 56787.4 | 2(Loss) |
| simdjson (ondemand) | 1491 | 1.6875 | 17.8816ms | 94370 | 30 | 3.11258e+07 | 60361.1 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1993.99 | 0.233008 | 4.71792ms | 31235 | 30 | 36349.6 | 14938.9 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1653.48 | 1.18281 | 5.4465ms | 31235 | 30 | 1.36217e+06 | 18015.3 | 2(Tie) |
| glaze STATISTICAL TIE | 1616.11 | 2.30716 | 5.45175ms | 31235 | 30 | 5.42522e+06 | 18431.9 | 2(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2448.12 | 0.526149 | 25.796ms | 213963 | 30 | 5.76965e+06 | 83349.9 | 1(Win) |
| glaze | 2051.83 | 0.67567 | 30.6022ms | 213963 | 30 | 1.35452e+07 | 99448.5 | 2(Loss) |
| simdjson (ondemand) | 1821.52 | 0.246407 | 34.1632ms | 213963 | 30 | 2.28578e+06 | 112022 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2203.13 | 0.377255 | 1333.47ms | 9930848 | 30 | 7.89011e+09 | 4.29878e+06 | 1(Win) |
| glaze | 1738.14 | 0.860027 | 1686.5ms | 9930848 | 30 | 6.5879e+10 | 5.4488e+06 | 2(Loss) |
| simdjson (ondemand) | 622.489 | 0.388576 | 4624.32ms | 9930848 | 30 | 1.04853e+11 | 1.52144e+07 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2138.39 | 0.409377 | 1323.96ms | 9930848 | 30 | 9.86206e+09 | 4.42894e+06 | 1(Win) |
| glaze | 1703.81 | 0.229273 | 34636.1ms | 9930848 | 320 | 5.1974e+10 | 5.55861e+06 | 2(Loss) |
| simdjson (ondemand) | 1625.44 | 0.356316 | 8818.75ms | 9930848 | 80 | 3.4482e+10 | 5.82661e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1489.87 | 0.302426 | 236.737ms | 1225964 | 30 | 1.68974e+08 | 784747 | 1(Win) |
| simdjson (ondemand) | 1400.73 | 0.170643 | 258.14ms | 1225964 | 30 | 6.08617e+07 | 834686 | 2(Loss) |
| jsonifier | 1286.45 | 0.425004 | 273.919ms | 1225964 | 30 | 4.47588e+08 | 908836 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1307.73 | 0.257382 | 177.297ms | 785750 | 30 | 6.52542e+07 | 573015 | 1(Win) |
| glaze | 1274.79 | 0.736307 | 177.58ms | 785750 | 30 | 5.61994e+08 | 587822 | 2(Loss) |
| jsonifier | 1134.1 | 0.244069 | 200.858ms | 785750 | 30 | 7.80206e+07 | 660742 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4406.71 | 0.357143 | 26.192ms | 399947 | 30 | 2.86669e+06 | 86554.1 | 1(Win) |
| simdjson (ondemand) | 3955.78 | 0.392554 | 29.8892ms | 399947 | 30 | 4.29795e+06 | 96420.8 | 2(Loss) |
| glaze | 2838.85 | 0.30647 | 40.4676ms | 399947 | 30 | 5.08649e+06 | 134357 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1899.7 | 0.241221 | 63.2172ms | 399947 | 30 | 7.03702e+06 | 200779 | 1(Win) |
| simdjson (ondemand) | 1822.51 | 0.600939 | 148.3ms | 399947 | 40 | 6.32681e+07 | 209282 | 2(Loss) |
| glaze | 1746.98 | 0.612203 | 65.7967ms | 399947 | 30 | 5.35971e+07 | 218331 | 3(Loss) |
