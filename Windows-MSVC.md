# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [e6f566c](https://github.com/nihilai-collective/jsonifier/commit/e6f566c)  
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
| jsonifier | 685.962 | 0.904975 | 6631.01ms | 6661897 | 40 | 2.81014e+11 | 9.26185e+06 | 3.60891 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 550.478 | 1.47826 | 3496.73ms | 6661897 | 30 | 8.73248e+11 | 1.15414e+07 | 4.49719 | 2(Tie) |
| glaze STATISTICAL TIE | 546.19 | 1.83041 | 3651.18ms | 6661897 | 30 | 1.35997e+12 | 1.1632e+07 | 4.53256 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1130.23 | 0.475256 | 7726.68ms | 1439562 | 320 | 1.06642e+10 | 1.21468e+06 | 2.19023 | 1(Win) |
| glaze | 1042.97 | 0.317851 | 947.323ms | 1439562 | 40 | 7.00209e+08 | 1.31632e+06 | 2.3735 | 2(Loss) |
| simdjson (ondemand) | 663.994 | 0.468546 | 616.022ms | 1439562 | 30 | 2.81552e+09 | 2.0676e+06 | 3.72826 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 664.21 | 1.09012 | 41.5514ms | 94370 | 30 | 6.54521e+07 | 135497 | 3.72601 | 1(Win) |
| glaze | 563.346 | 0.712006 | 46.1323ms | 94370 | 30 | 3.88156e+07 | 159757 | 4.39351 | 2(Loss) |
| simdjson (ondemand) | 426.916 | 0.80442 | 63.3098ms | 94370 | 30 | 8.6272e+07 | 210810 | 5.79845 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 884.267 | 0.110003 | 10.6464ms | 31235 | 30 | 41195.4 | 33686.7 | 2.79717 | 1(Win) |
| glaze | 873.037 | 0.141261 | 24.4834ms | 31235 | 40 | 92923.1 | 34120 | 2.83295 | 2(Loss) |
| simdjson (ondemand) | 570.725 | 1.93233 | 15.7292ms | 31235 | 30 | 3.05151e+07 | 52193.3 | 4.33414 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1085.78 | 0.932687 | 56.7826ms | 213963 | 30 | 9.21691e+07 | 187930 | 2.27933 | 1(Win) |
| jsonifier | 1056.92 | 0.736254 | 305.941ms | 213963 | 80 | 1.61637e+08 | 193062 | 2.34165 | 2(Loss) |
| simdjson (ondemand) | 520.807 | 0.580751 | 2468.76ms | 213963 | 320 | 1.65673e+09 | 391798 | 4.75272 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 983.397 | 1.22442 | 2852.86ms | 9930848 | 30 | 4.17157e+11 | 9.6307e+06 | 2.51728 | 1(Win) |
| glaze | 724.64 | 0.633222 | 3926.92ms | 9930848 | 30 | 2.05476e+11 | 1.30697e+07 | 3.41628 | 2(Loss) |
| simdjson (ondemand) | 234.16 | 0.452586 | 12198.5ms | 9930848 | 30 | 1.00525e+12 | 4.04459e+07 | 10.5729 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 997.45 | 0.973213 | 2873.23ms | 9930848 | 30 | 2.5617e+11 | 9.49501e+06 | 2.48185 | 1(Win) |
| glaze | 720.697 | 0.970443 | 3971.02ms | 9930848 | 30 | 4.87898e+11 | 1.31412e+07 | 3.4349 | 2(Loss) |
| simdjson (ondemand) | 668.552 | 1.64262 | 4125.48ms | 9930848 | 30 | 1.62441e+12 | 1.41661e+07 | 3.70285 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 727.693 | 0.28479 | 484.446ms | 1225964 | 30 | 6.28102e+08 | 1.60668e+06 | 3.40187 | 1(Win) |
| jsonifier | 705.587 | 1.07318 | 2533.92ms | 1225964 | 80 | 2.52982e+10 | 1.65702e+06 | 3.50829 | 2(Loss) |
| glaze | 685.822 | 0.129045 | 1230.41ms | 1225964 | 40 | 1.93585e+08 | 1.70477e+06 | 3.60969 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 636.25 | 0.507521 | 354.132ms | 785750 | 30 | 1.07187e+09 | 1.17776e+06 | 3.89064 | 1(Win) |
| glaze | 512.894 | 0.233986 | 445.095ms | 785750 | 30 | 3.50604e+08 | 1.46102e+06 | 4.82652 | 2(Loss) |
| simdjson (ondemand) | 455.428 | 0.143348 | 498.283ms | 785750 | 30 | 1.66892e+08 | 1.64537e+06 | 5.43553 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3147.54 | 1.27416 | 36.8947ms | 399947 | 30 | 7.1521e+07 | 121180 | 0.786394 | 1(Win) |
| glaze STATISTICAL TIE | 1815.65 | 0.906138 | 79.26ms | 399947 | 30 | 1.08705e+08 | 210073 | 1.36323 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1805.11 | 0.761459 | 63.9207ms | 399947 | 30 | 7.76628e+07 | 211300 | 1.37117 | 2(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 872.593 | 0.754894 | 133.247ms | 399947 | 30 | 3.26644e+08 | 437110 | 2.83625 | 1(Win) |
| glaze | 816.574 | 1.209 | 143.63ms | 399947 | 30 | 9.56726e+08 | 467097 | 3.03106 | 2(Loss) |
| simdjson (ondemand) | 553.655 | 0.475831 | 1033.61ms | 399947 | 80 | 8.59651e+08 | 688911 | 4.47036 | 3(Loss) |
