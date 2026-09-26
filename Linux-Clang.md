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
| jsonifier | 1076.05 | 0.109967 | 1780.32ms | 6661897 | 30 | 1.26467e+09 | 5.90425e+06 | 2.16724 | 1(Win) |
| simdjson (ondemand) | 959.175 | 0.1004 | 1992.54ms | 6661897 | 30 | 1.32675e+09 | 6.62369e+06 | 2.43135 | 2(Loss) |
| glaze | 953.906 | 0.123136 | 2007.51ms | 6661897 | 30 | 2.0178e+09 | 6.66028e+06 | 2.44478 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1865.18 | 0.529395 | 223.956ms | 1439562 | 30 | 4.55512e+08 | 736053 | 1.25025 | 1(Win) |
| glaze | 1545.26 | 0.346548 | 268.491ms | 1439562 | 30 | 2.84387e+08 | 888444 | 1.50912 | 2(Loss) |
| simdjson (ondemand) | 1337.76 | 0.988478 | 308.497ms | 1439562 | 30 | 3.08716e+09 | 1.02625e+06 | 1.74316 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1245.61 | 1.36359 | 24.4214ms | 94370 | 30 | 2.91198e+07 | 72252.2 | 1.87088 | 1(Win) |
| glaze | 1121.79 | 2.24802 | 26.6869ms | 94370 | 30 | 9.75811e+07 | 80227.2 | 2.07775 | 2(Loss) |
| simdjson (ondemand) | 1021.24 | 2.19773 | 28.5148ms | 94370 | 30 | 1.12534e+08 | 88126.8 | 2.28242 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1342.38 | 1.76976 | 9.25363ms | 31235 | 30 | 4.6268e+06 | 22190.4 | 1.73447 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1327.53 | 0.372478 | 9.34443ms | 31235 | 30 | 209564 | 22438.7 | 1.75374 | 1(Tie) |
| glaze | 1144.88 | 1.36179 | 10.3845ms | 31235 | 30 | 3.76623e+06 | 26018.5 | 2.03412 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1723.74 | 1.68139 | 37.775ms | 213963 | 30 | 1.18848e+08 | 118377 | 1.35227 | 1(Win) |
| glaze | 1478.32 | 1.34211 | 43.9776ms | 213963 | 30 | 1.02953e+08 | 138029 | 1.57697 | 2(Loss) |
| simdjson (ondemand) | 1350.39 | 1.58036 | 47.7015ms | 213963 | 30 | 1.71076e+08 | 151105 | 1.72625 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1698.49 | 0.150112 | 1676.38ms | 9930848 | 30 | 2.10183e+09 | 5.57602e+06 | 1.373 | 1(Win) |
| glaze | 1336.83 | 0.113286 | 2131.75ms | 9930848 | 30 | 1.93239e+09 | 7.08452e+06 | 1.74445 | 2(Loss) |
| simdjson (ondemand) | 541.284 | 0.177143 | 5243.86ms | 9930848 | 30 | 2.882e+10 | 1.74969e+07 | 4.30836 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1724.89 | 0.105003 | 1661.59ms | 9930848 | 30 | 9.97185e+08 | 5.49067e+06 | 1.352 | 1(Win) |
| simdjson (ondemand) | 1375.11 | 0.145406 | 2069.48ms | 9930848 | 30 | 3.00876e+09 | 6.8873e+06 | 1.69582 | 2(Loss) |
| glaze | 1342.47 | 0.150626 | 2128.06ms | 9930848 | 30 | 3.38758e+09 | 7.05477e+06 | 1.73716 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1128 | 0.242312 | 315.298ms | 1225964 | 30 | 1.8924e+08 | 1.0365e+06 | 2.06738 | 1(Win) |
| jsonifier | 1097.4 | 0.183349 | 322.588ms | 1225964 | 30 | 1.14474e+08 | 1.0654e+06 | 2.12502 | 2(Loss) |
| simdjson (ondemand) | 1066.12 | 0.185363 | 332.908ms | 1225964 | 30 | 1.23968e+08 | 1.09665e+06 | 2.18735 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 886.225 | 0.407885 | 257.215ms | 785750 | 30 | 3.56844e+08 | 845553 | 2.63136 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 884.524 | 0.265753 | 257.121ms | 785750 | 30 | 1.52065e+08 | 847178 | 2.63642 | 1(Tie) |
| glaze | 667.168 | 0.322589 | 338.709ms | 785750 | 30 | 3.93839e+08 | 1.12318e+06 | 3.49537 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3726.57 | 1.5145 | 33.8149ms | 399947 | 30 | 7.20852e+07 | 102351 | 0.625478 | 1(Win) |
| simdjson (ondemand) | 3429.41 | 1.75612 | 35.9218ms | 399947 | 30 | 1.14445e+08 | 111220 | 0.679728 | 2(Loss) |
| glaze | 2281.66 | 1.08358 | 53.1386ms | 399947 | 30 | 9.84352e+07 | 167168 | 1.02177 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1164.18 | 0.68382 | 100.849ms | 399947 | 30 | 1.5058e+08 | 327628 | 2.0029 | 1(Win) |
| jsonifier | 1088.74 | 0.737167 | 108.504ms | 399947 | 30 | 2.00083e+08 | 350331 | 2.14142 | 2(Loss) |
| glaze | 1022.88 | 0.736696 | 114.314ms | 399947 | 30 | 2.2639e+08 | 372889 | 2.27946 | 3(Loss) |
