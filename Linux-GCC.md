# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

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

> Adaptive sampling on (INTEL(R) XEON(R) PLATINUM 8573C-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| simdjson (ondemand) | 1210.86 | 0.236548 | 1575.08ms | 6661897 | 30 | 4.62134e+09 | 5.24691e+06 | 1.81136 | 1(Win) |
| jsonifier | 1151.83 | 0.279583 | 1664ms | 6661897 | 30 | 7.1345e+09 | 5.51582e+06 | 1.90418 | 2(Loss) |
| glaze | 979.268 | 0.238779 | 1946.29ms | 6661897 | 30 | 7.19955e+09 | 6.48779e+06 | 2.23977 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1903.86 | 0.545691 | 218.806ms | 1439562 | 30 | 4.64519e+08 | 721098 | 1.15178 | 1(Win) |
| jsonifier | 1549.57 | 0.319779 | 270.067ms | 1439562 | 30 | 2.40803e+08 | 885971 | 1.41532 | 2(Loss) |
| glaze | 1517.13 | 0.675751 | 270.941ms | 1439562 | 30 | 1.12178e+09 | 904914 | 1.4455 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1280.79 | 0.854774 | 33.9916ms | 94370 | 30 | 1.08228e+07 | 70268 | 1.71124 | 1(Tie) |
| glaze STATISTICAL TIE | 1257.21 | 2.62751 | 23.165ms | 94370 | 30 | 1.06136e+08 | 71585.7 | 1.74338 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1244.84 | 1.15371 | 23.5758ms | 94370 | 30 | 2.08718e+07 | 72297.1 | 1.76064 | 1(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1489.1 | 5.60407 | 7.31841ms | 31235 | 30 | 3.7702e+07 | 20004 | 1.46941 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1367.53 | 1.01302 | 8.31888ms | 31235 | 30 | 1.46073e+06 | 21782.4 | 1.60083 | 1(Tie) |
| glaze | 1181.89 | 1.64713 | 9.41177ms | 31235 | 30 | 5.1702e+06 | 25203.8 | 1.85243 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1787.63 | 1.52705 | 35.4888ms | 213963 | 30 | 9.11492e+07 | 114146 | 1.22639 | 1(Win) |
| jsonifier | 1665.17 | 1.15028 | 38.0814ms | 213963 | 30 | 5.96062e+07 | 122541 | 1.31641 | 2(Loss) |
| glaze | 1533.3 | 1.79648 | 41.3597ms | 213963 | 30 | 1.7147e+08 | 133080 | 1.42987 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1569.45 | 1.29073 | 1763.92ms | 9930848 | 30 | 1.82002e+11 | 6.03449e+06 | 1.39744 | 1(Win) |
| glaze | 1381.77 | 0.243772 | 2048.64ms | 9930848 | 30 | 8.37507e+09 | 6.85409e+06 | 1.58727 | 2(Loss) |
| simdjson (ondemand) | 447.876 | 0.180701 | 6379.06ms | 9930848 | 30 | 4.38027e+10 | 2.1146e+07 | 4.89712 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1697.7 | 0.281107 | 1680.38ms | 9930848 | 30 | 7.37757e+09 | 5.5786e+06 | 1.2919 | 1(Win) |
| simdjson (ondemand) | 1640.06 | 0.255263 | 1734.16ms | 9930848 | 30 | 6.51853e+09 | 5.77467e+06 | 1.33725 | 2(Loss) |
| glaze | 1356.68 | 0.271906 | 2080.77ms | 9930848 | 30 | 1.08087e+10 | 6.98084e+06 | 1.61663 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1354.61 | 0.21389 | 261.718ms | 1225964 | 30 | 1.02242e+08 | 863105 | 1.61879 | 1(Win) |
| glaze | 1020.99 | 0.155843 | 350.159ms | 1225964 | 30 | 9.55453e+07 | 1.14513e+06 | 2.14788 | 2(Loss) |
| jsonifier | 914.51 | 0.319611 | 382.267ms | 1225964 | 30 | 5.0089e+08 | 1.27847e+06 | 2.39804 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1055.75 | 0.760807 | 211.062ms | 785750 | 30 | 8.74822e+08 | 709781 | 2.07698 | 1(Win) |
| jsonifier | 873.467 | 0.371462 | 259.51ms | 785750 | 30 | 3.04668e+08 | 857903 | 2.51067 | 2(Loss) |
| glaze | 801.595 | 0.487745 | 282.579ms | 785750 | 30 | 6.23685e+08 | 934823 | 2.73557 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4821.11 | 1.46059 | 25.2056ms | 399947 | 30 | 4.00581e+07 | 79114.4 | 0.454672 | 1(Win) |
| simdjson (ondemand) | 4340.79 | 1.87437 | 27.5888ms | 399947 | 30 | 8.13766e+07 | 87868.6 | 0.504993 | 2(Loss) |
| glaze | 2162.96 | 0.71101 | 54.6561ms | 399947 | 30 | 4.71609e+07 | 176342 | 1.01377 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1455.5 | 0.65231 | 81.359ms | 399947 | 30 | 8.76616e+07 | 262053 | 1.50656 | 1(Win) |
| glaze | 1116.95 | 0.671535 | 102.576ms | 399947 | 30 | 1.57759e+08 | 341482 | 1.96331 | 2(Loss) |
| jsonifier | 1094.64 | 0.39801 | 108.063ms | 399947 | 30 | 5.7699e+07 | 348441 | 2.00324 | 3(Loss) |
