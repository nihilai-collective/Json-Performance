# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [b01e9de](https://github.com/nihilai-collective/jsonifier/commit/b01e9de)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 1446.29 | 0.0589726 | 1325.78ms | 6661897 | 30 | 2.01328e+08 | 4.3928e+06 | 1.71181 | 1(Win) |
| glaze | 1254.18 | 0.0591647 | 1725.55ms | 6661897 | 30 | 2.69479e+08 | 5.0657e+06 | 1.97403 | 2(Loss) |
| simdjson (ondemand) | 1199.72 | 0.0569145 | 1590.36ms | 6661897 | 30 | 2.72524e+08 | 5.29565e+06 | 2.06365 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2441.72 | 0.255846 | 172.27ms | 1439562 | 30 | 6.20791e+07 | 562256 | 1.01374 | 1(Win) |
| glaze | 2073.38 | 0.18553 | 202.263ms | 1439562 | 30 | 4.52746e+07 | 662143 | 1.1939 | 2(Loss) |
| simdjson (ondemand) | 1956.61 | 0.148424 | 213.043ms | 1439562 | 30 | 3.25372e+07 | 701658 | 1.26525 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1581.86 | 1.32118 | 19.3452ms | 94370 | 30 | 1.69503e+07 | 56893.9 | 1.56436 | 1(Win) |
| jsonifier STATISTICAL TIE | 1464.45 | 0.633349 | 21.0112ms | 94370 | 30 | 4.54493e+06 | 61455.4 | 1.68959 | 2(Tie) |
| glaze STATISTICAL TIE | 1462.68 | 1.04421 | 20.9653ms | 94370 | 30 | 1.23841e+07 | 61529.7 | 1.69188 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1876.76 | 2.7072 | 6.94984ms | 31235 | 30 | 5.53898e+06 | 15872.1 | 1.31677 | 1(Win) |
| jsonifier | 1675.8 | 0.329807 | 7.70787ms | 31235 | 30 | 103105 | 17775.4 | 1.47496 | 2(Loss) |
| glaze | 1559.12 | 3.25875 | 8.02068ms | 31235 | 30 | 1.16291e+07 | 19105.6 | 1.58514 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2222.87 | 1.37399 | 29.9686ms | 213963 | 30 | 4.7724e+07 | 91796.4 | 1.11336 | 1(Win) |
| jsonifier | 2024.69 | 1.15559 | 32.5651ms | 213963 | 30 | 4.06901e+07 | 100781 | 1.22229 | 2(Loss) |
| glaze | 1944.78 | 1.38781 | 33.7064ms | 213963 | 30 | 6.3609e+07 | 104922 | 1.27253 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2235.33 | 0.079571 | 1276.77ms | 9930848 | 30 | 3.40973e+08 | 4.23686e+06 | 1.10756 | 1(Win) |
| glaze | 1853.28 | 0.081996 | 1532.71ms | 9930848 | 30 | 5.26742e+08 | 5.11029e+06 | 1.3359 | 2(Loss) |
| simdjson (ondemand) | 708.632 | 0.0715554 | 4032.99ms | 9930848 | 30 | 2.74371e+09 | 1.33649e+07 | 3.49378 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2257.55 | 0.0869572 | 1261.67ms | 9930848 | 30 | 3.99237e+08 | 4.19517e+06 | 1.09665 | 1(Win) |
| simdjson (ondemand) | 1940.33 | 0.174269 | 1465.81ms | 9930848 | 30 | 2.17063e+09 | 4.88102e+06 | 1.27595 | 2(Loss) |
| glaze | 1827.07 | 0.0761632 | 1563.15ms | 9930848 | 30 | 4.67598e+08 | 5.18359e+06 | 1.35504 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1431.89 | 0.324597 | 247.85ms | 1225964 | 30 | 2.1074e+08 | 816522 | 1.7289 | 1(Tie) |
| glaze STATISTICAL TIE | 1423.67 | 0.256571 | 248.891ms | 1225964 | 30 | 1.3319e+08 | 821238 | 1.73888 | 1(Tie) |
| jsonifier | 1327.27 | 0.17992 | 268.048ms | 1225964 | 30 | 7.53563e+07 | 880884 | 1.86518 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1283.76 | 0.244445 | 179.342ms | 785750 | 30 | 6.1078e+07 | 583714 | 1.92827 | 1(Win) |
| jsonifier | 1190.77 | 0.192047 | 193.584ms | 785750 | 30 | 4.38174e+07 | 629297 | 2.07897 | 2(Loss) |
| glaze | 888.485 | 0.236904 | 254.493ms | 785750 | 30 | 1.19767e+08 | 843402 | 2.78634 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5775.67 | 2.0731 | 21.8614ms | 399947 | 30 | 5.62292e+07 | 66039 | 0.428433 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 5547.99 | 0.60578 | 22.9589ms | 399947 | 30 | 5.20337e+06 | 68749.1 | 0.445968 | 1(Tie) |
| glaze | 3123.83 | 0.912793 | 39.7535ms | 399947 | 30 | 3.72646e+07 | 122100 | 0.792353 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1720.09 | 0.854308 | 69.0582ms | 399947 | 30 | 1.0766e+08 | 221744 | 1.43893 | 1(Win) |
| jsonifier | 1519.27 | 0.560236 | 81.4832ms | 399947 | 30 | 5.93469e+07 | 251054 | 1.62917 | 2(Loss) |
| glaze | 1411.6 | 0.908236 | 83.2144ms | 399947 | 30 | 1.80676e+08 | 270203 | 1.7534 | 3(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2241.55 | 0.770073 | 62.3844ms | 466906 | 30 | 7.02014e+07 | 198646 | 1.10423 | 1(Win) |
| glaze | 1742.78 | 0.844466 | 79.6498ms | 466906 | 30 | 1.39656e+08 | 255498 | 1.42027 | 2(Loss) |
| simdjson (ondemand) | 877.34 | 0.290032 | 155.149ms | 466906 | 30 | 6.50033e+07 | 507530 | 2.82161 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3202.23 | 0.67624 | 67.0407ms | 699405 | 30 | 5.95216e+07 | 208294 | 0.772983 | 1(Win) |
| glaze | 2713.61 | 0.55438 | 76.3065ms | 699405 | 30 | 5.57058e+07 | 245800 | 0.91219 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3427.13 | 0.736362 | 55.2428ms | 631514 | 30 | 5.02353e+07 | 175733 | 0.72221 | 1(Win) |
| glaze | 1831.13 | 0.438257 | 101.338ms | 631514 | 30 | 6.23314e+07 | 328900 | 1.35185 | 2(Loss) |
