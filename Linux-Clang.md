# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [e6f566c](https://github.com/nihilai-collective/jsonifier/commit/e6f566c)  
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
| jsonifier | 1436.65 | 0.110561 | 1353.77ms | 6661897 | 30 | 7.1716e+08 | 4.42229e+06 | 1.72326 | 1(Win) |
| glaze | 1190.19 | 0.115613 | 1608.7ms | 6661897 | 30 | 1.14262e+09 | 5.33806e+06 | 2.08011 | 2(Loss) |
| simdjson (ondemand) | 1183.38 | 0.0752092 | 1616.6ms | 6661897 | 30 | 4.89117e+08 | 5.36877e+06 | 2.09202 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2552.74 | 0.328198 | 165.209ms | 1439562 | 30 | 9.34636e+07 | 537805 | 0.969704 | 1(Win) |
| glaze | 2046.63 | 0.271343 | 204.641ms | 1439562 | 30 | 9.93892e+07 | 670797 | 1.20955 | 2(Loss) |
| simdjson (ondemand) | 1933.96 | 0.606365 | 214.536ms | 1439562 | 30 | 5.55849e+08 | 709878 | 1.27998 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1568.73 | 0.725872 | 19.6416ms | 94370 | 30 | 5.20252e+06 | 57370.2 | 1.57744 | 1(Win) |
| glaze STATISTICAL TIE | 1461.75 | 0.850902 | 21.1481ms | 94370 | 30 | 8.2338e+06 | 61568.7 | 1.69293 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1435.81 | 0.529447 | 21.3738ms | 94370 | 30 | 3.304e+06 | 62681.2 | 1.72329 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1914.67 | 0.171827 | 7.01813ms | 31235 | 30 | 21438.7 | 15557.8 | 1.29063 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1876.84 | 1.86888 | 7.0777ms | 31235 | 30 | 2.63942e+06 | 15871.3 | 1.31666 | 1(Tie) |
| glaze | 1569.37 | 2.0657 | 8.10503ms | 31235 | 30 | 4.61201e+06 | 18980.9 | 1.5752 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2189.49 | 1.61393 | 30.1759ms | 213963 | 30 | 6.78705e+07 | 93195.5 | 1.13031 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2166.1 | 1.33517 | 30.8064ms | 213963 | 30 | 4.74587e+07 | 94202.1 | 1.14263 | 1(Tie) |
| glaze | 1949.56 | 1.31594 | 33.9884ms | 213963 | 30 | 5.69112e+07 | 104665 | 1.26955 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2294.33 | 0.104645 | 1254.18ms | 9930848 | 30 | 5.59781e+08 | 4.12791e+06 | 1.07902 | 1(Win) |
| glaze | 1688.11 | 0.114828 | 1672.94ms | 9930848 | 30 | 1.24507e+09 | 5.61031e+06 | 1.46654 | 2(Loss) |
| simdjson (ondemand) | 689.132 | 0.177955 | 4179.83ms | 9930848 | 30 | 1.79436e+10 | 1.37431e+07 | 3.59256 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2276.03 | 0.136058 | 1251.85ms | 9930848 | 30 | 9.61578e+08 | 4.1611e+06 | 1.0877 | 1(Win) |
| simdjson (ondemand) | 1806.33 | 0.219667 | 1538.4ms | 9930848 | 30 | 3.9795e+09 | 5.24311e+06 | 1.37052 | 2(Loss) |
| glaze | 1665.31 | 0.215733 | 1671.51ms | 9930848 | 30 | 4.51579e+09 | 5.68709e+06 | 1.4865 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1445.43 | 0.161654 | 246.864ms | 1225964 | 30 | 5.12925e+07 | 808872 | 1.7127 | 1(Win) |
| glaze | 1429.74 | 0.199243 | 248.825ms | 1225964 | 30 | 7.96389e+07 | 817749 | 1.73151 | 2(Loss) |
| jsonifier | 1336.75 | 0.255737 | 263.969ms | 1225964 | 30 | 1.50095e+08 | 874640 | 1.85192 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1247.59 | 0.277803 | 183.5ms | 785750 | 30 | 8.3526e+07 | 600638 | 1.98423 | 1(Win) |
| jsonifier | 1193.3 | 0.238284 | 191.522ms | 785750 | 30 | 6.71703e+07 | 627963 | 2.0735 | 2(Loss) |
| glaze | 888.984 | 0.271985 | 256.713ms | 785750 | 30 | 1.57686e+08 | 842928 | 2.78474 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5890.42 | 0.773258 | 21.9415ms | 399947 | 30 | 7.52112e+06 | 64752.5 | 0.420103 | 1(Win) |
| simdjson (ondemand) | 5479.12 | 2.09174 | 22.9971ms | 399947 | 30 | 6.3609e+07 | 69613.2 | 0.45166 | 2(Loss) |
| glaze | 3075.17 | 0.58914 | 40.0791ms | 399947 | 30 | 1.60186e+07 | 124032 | 0.804898 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1777.44 | 0.666519 | 68.2886ms | 399947 | 30 | 6.13706e+07 | 214589 | 1.39248 | 1(Win) |
| jsonifier | 1521.88 | 0.568809 | 182.917ms | 399947 | 40 | 8.12898e+07 | 250623 | 1.62639 | 2(Loss) |
| glaze | 1414.38 | 1.12957 | 83.6198ms | 399947 | 30 | 2.78371e+08 | 269672 | 1.74975 | 3(Loss) |
