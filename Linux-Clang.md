# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

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
| jsonifier | 1061.76 | 0.41671 | 1799.93ms | 6661897 | 30 | 1.86524e+10 | 5.98374e+06 | 2.1964 | 1(Win) |
| simdjson (ondemand) | 950.862 | 0.18686 | 2014.9ms | 6661897 | 30 | 4.67644e+09 | 6.6816e+06 | 2.45255 | 2(Loss) |
| glaze | 945.682 | 0.181139 | 2020.14ms | 6661897 | 30 | 4.44272e+09 | 6.7182e+06 | 2.46596 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1874.12 | 0.263303 | 224.411ms | 1439562 | 30 | 1.1161e+08 | 732545 | 1.24426 | 1(Win) |
| glaze | 1500.37 | 0.526821 | 273.695ms | 1439562 | 30 | 6.97127e+08 | 915024 | 1.55423 | 2(Loss) |
| simdjson (ondemand) | 1337.02 | 0.3643 | 309.935ms | 1439562 | 30 | 4.19781e+08 | 1.02681e+06 | 1.74411 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1230.04 | 2.05531 | 24.5082ms | 94370 | 30 | 6.7843e+07 | 73166.9 | 1.89415 | 1(Win) |
| glaze STATISTICAL TIE | 1091.52 | 1.83062 | 27.0163ms | 94370 | 30 | 6.83477e+07 | 82452.3 | 2.13509 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1027.97 | 2.46194 | 28.3372ms | 94370 | 30 | 1.39375e+08 | 87549.7 | 2.26732 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1342.24 | 1.99719 | 9.16249ms | 31235 | 30 | 5.8936e+06 | 22192.7 | 1.73452 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1324.51 | 0.117504 | 9.30914ms | 31235 | 30 | 20951 | 22489.9 | 1.75771 | 1(Tie) |
| glaze | 1133.48 | 1.38523 | 10.394ms | 31235 | 30 | 3.97578e+06 | 26280.2 | 2.05454 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1784.1 | 1.31383 | 37.0541ms | 213963 | 30 | 6.77393e+07 | 114372 | 1.30648 | 1(Win) |
| glaze | 1483.12 | 1.35429 | 44.0766ms | 213963 | 30 | 1.04152e+08 | 137583 | 1.57173 | 2(Loss) |
| simdjson (ondemand) | 1375.66 | 1.09824 | 46.9474ms | 213963 | 30 | 7.96095e+07 | 148329 | 1.69468 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1700.29 | 0.453138 | 1680.41ms | 9930848 | 30 | 1.91123e+10 | 5.57012e+06 | 1.3715 | 1(Win) |
| glaze | 1333.18 | 0.247088 | 2124.67ms | 9930848 | 30 | 9.2432e+09 | 7.10394e+06 | 1.74919 | 2(Loss) |
| simdjson (ondemand) | 544.418 | 0.377602 | 5225.7ms | 9930848 | 30 | 1.29449e+11 | 1.73962e+07 | 4.28353 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1721.86 | 0.284709 | 1650.26ms | 9930848 | 30 | 7.35695e+09 | 5.50031e+06 | 1.35433 | 1(Win) |
| simdjson (ondemand) | 1374.41 | 0.300903 | 2069.16ms | 9930848 | 30 | 1.28978e+10 | 6.89081e+06 | 1.6967 | 2(Loss) |
| glaze | 1349.72 | 0.377709 | 2106.57ms | 9930848 | 30 | 2.10727e+10 | 7.01684e+06 | 1.72776 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1124.1 | 0.223224 | 313.745ms | 1225964 | 30 | 1.61715e+08 | 1.0401e+06 | 2.0745 | 1(Win) |
| jsonifier | 1105.87 | 0.177747 | 317.628ms | 1225964 | 30 | 1.05942e+08 | 1.05724e+06 | 2.10871 | 2(Loss) |
| simdjson (ondemand) | 1062.82 | 0.254502 | 332.197ms | 1225964 | 30 | 2.35147e+08 | 1.10006e+06 | 2.19414 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 889.422 | 0.23338 | 256.614ms | 785750 | 30 | 1.15985e+08 | 842513 | 2.62189 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 885.854 | 0.307596 | 256.405ms | 785750 | 30 | 2.03109e+08 | 845907 | 2.63239 | 1(Tie) |
| glaze | 660.808 | 0.205453 | 342.95ms | 785750 | 30 | 1.62841e+08 | 1.13399e+06 | 3.52897 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3683.44 | 1.37646 | 33.7396ms | 399947 | 30 | 6.09456e+07 | 103550 | 0.632758 | 1(Win) |
| simdjson (ondemand) | 3453.07 | 1.48754 | 35.8732ms | 399947 | 30 | 8.09942e+07 | 110458 | 0.675064 | 2(Loss) |
| glaze | 2210.34 | 0.959055 | 54.6607ms | 399947 | 30 | 8.21664e+07 | 172561 | 1.05471 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1184.51 | 0.523989 | 99.9873ms | 399947 | 30 | 8.54074e+07 | 322007 | 1.96848 | 1(Win) |
| jsonifier | 1143.93 | 0.627319 | 104.107ms | 399947 | 30 | 1.31251e+08 | 333429 | 2.03806 | 2(Loss) |
| glaze | 1006.64 | 0.673648 | 115.745ms | 399947 | 30 | 1.95454e+08 | 378904 | 2.3163 | 3(Loss) |
