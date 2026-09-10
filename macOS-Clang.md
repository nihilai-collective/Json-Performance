# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

Latest Results: (Oct 01, 2026)
#### Using the following commits:
----
| Jsonifier: [e2e111b](https://github.com/nihilai-collective/jsonifier/commit/e2e111b)  
| Simdjson (On Demand): [610f14d](https://github.com/simdjson/simdjson/commit/610f14d)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. 

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10.000000% AND mean shift < 5.000000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" is performing scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through stage-1 + stage-2)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ced5b69](https://github.com/nihilai-collective/benchmarksuite/commit/ced5b69).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 827.897 | 1.9238 | 203.778ms | 1811 | 30 | 48319.6 | 2086.13 | 1(Win) |
| jsonifier (two-stage) | 336.724 | 0.0714039 | 587.907ms | 1811 | 30 | 402.395 | 5129.13 | 2(Loss) |
| simdjson (ondemand) | 175.276 | 0.156965 | 975.633ms | 1811 | 4890 | 1.1698e+06 | 9853.65 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2354.45 | 0.156224 | 161.923ms | 3862 | 320 | 1911.13 | 1564.31 | 1(Win) |
| jsonifier (two-stage) | 636.079 | 0.405842 | 605.242ms | 3862 | 30 | 16566.8 | 5790.3 | 2(Loss) |
| simdjson (ondemand) | 447.189 | 0.0817962 | 880.725ms | 3862 | 30 | 1361.54 | 8236.1 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1752.12 | 0.1294 | 851.864ms | 9578 | 1280 | 58250.5 | 5213.29 | 1(Win) |
| simdjson (ondemand) | 1077.54 | 0.113372 | 1161.37ms | 9578 | 4890 | 451652 | 8477.02 | 2(Loss) |
| jsonifier (two-stage) | 744.801 | 0.157996 | 1585.8ms | 9578 | 160 | 60073.7 | 12264.1 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2409.75 | 0.14232 | 165.789ms | 3873 | 80 | 380.69 | 1532.76 | 1(Win) |
| jsonifier (two-stage) | 624.594 | 0.250207 | 690.949ms | 3873 | 40 | 8757.07 | 5913.57 | 2(Loss) |
| simdjson (ondemand) | 422.733 | 0.257162 | 889.975ms | 3873 | 1280 | 646228 | 8737.38 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2038.66 | 0.146545 | 5615.59ms | 6661897 | 80 | 1.66854e+09 | 3.11639e+06 | 1(Win) |
| jsonifier (two-stage) | 1942.62 | 0.179575 | 5806.75ms | 6661897 | 80 | 2.75934e+09 | 3.27048e+06 | 2(Loss) |
| simdjson (ondemand) | 1322.95 | 0.799193 | 8012.55ms | 6661897 | 80 | 1.17842e+11 | 4.80235e+06 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2276.83 | 0.0889531 | 6368.74ms | 500299 | 1280 | 4.44765e+07 | 209556 | 1(Win) |
| jsonifier (two-stage) | 1378.22 | 0.416326 | 9909.03ms | 500299 | 30 | 6.23176e+07 | 346187 | 2(Loss) |
| simdjson (ondemand) | 839.471 | 0.0881502 | 8652.08ms | 500299 | 160 | 4.01619e+07 | 568360 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3639.13 | 0.371251 | 5360.3ms | 1439562 | 320 | 6.27699e+08 | 377253 | 1(Win) |
| jsonifier (two-stage) | 3098.19 | 0.17542 | 6158.33ms | 1439562 | 320 | 1.93355e+08 | 443122 | 2(Loss) |
| simdjson (ondemand) | 2011 | 0.253551 | 9646.49ms | 1439562 | 160 | 4.79389e+08 | 682684 | 3(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2258.48 | 0.109887 | 2518.54ms | 56369 | 80 | 54730.7 | 23802.6 | 1(Win) |
| jsonifier (two-stage) | 1542.05 | 0.141054 | 3817.19ms | 56369 | 160 | 386877 | 34861.2 | 2(Loss) |
| simdjson (ondemand) | 1041.28 | 0.292461 | 5231.91ms | 56369 | 640 | 1.45902e+07 | 51626.6 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2463.42 | 0.0771103 | 3847.02ms | 94370 | 4890 | 3.88085e+06 | 36533.9 | 1(Win) |
| jsonifier (two-stage) | 2136.78 | 0.0675236 | 4310.87ms | 94370 | 4890 | 3.95521e+06 | 42118.6 | 2(Loss) |
| simdjson (ondemand) | 1656.57 | 0.176354 | 5801.59ms | 94370 | 320 | 2.93744e+06 | 54327.9 | 3(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1986.94 | 0.0337929 | 689.542ms | 11812 | 30 | 110.116 | 5669.43 | 1(Win) |
| jsonifier (two-stage) | 1293.56 | 0.315563 | 1048.96ms | 11812 | 30 | 22655.4 | 8708.4 | 2(Loss) |
| simdjson (ondemand) | 715.597 | 0.372815 | 1675.57ms | 11812 | 2560 | 8.81734e+06 | 15741.8 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3082.18 | 0.213095 | 1265.68ms | 31235 | 40 | 16965.8 | 9664.6 | 1(Win) |
| jsonifier (two-stage) | 2376.71 | 3.50664 | 1358.32ms | 31235 | 40 | 7.72634e+06 | 12533.3 | 2(Loss) |
| simdjson (ondemand) | 1665.54 | 0.994038 | 2037.26ms | 31235 | 4890 | 1.54556e+08 | 17884.9 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2354.75 | 1.43374 | 4652.73ms | 108313 | 40 | 1.58223e+07 | 43866.7 | 1(Win) |
| jsonifier (two-stage) | 1442.39 | 0.229162 | 7522.92ms | 108313 | 2560 | 6.89482e+07 | 71614 | 2(Loss) |
| simdjson (ondemand) | 1083.55 | 0.30977 | 5029.5ms | 108313 | 160 | 1.39529e+07 | 95330.8 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3171 | 0.239392 | 6805.76ms | 213963 | 320 | 7.59369e+06 | 64349.1 | 1(Win) |
| jsonifier (two-stage) | 2575.51 | 0.0943006 | 8489.01ms | 213963 | 1280 | 7.14481e+06 | 79227.4 | 2(Loss) |
| simdjson (ondemand) | 1942.34 | 0.690217 | 5534.52ms | 213963 | 30 | 1.57732e+07 | 105054 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 645.182 | 0.240128 | 9648.22ms | 1834197 | 80 | 3.3908e+09 | 2.71121e+06 | 1(Win) |
| jsonifier (two-stage) | 561.748 | 0.381691 | 5382.75ms | 1834197 | 80 | 1.13011e+10 | 3.1139e+06 | 2(Loss) |
| simdjson (ondemand) | 128.229 | 0.445198 | 10497.2ms | 1834197 | 30 | 1.10649e+11 | 1.36414e+07 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2637.71 | 0.124694 | 5989.83ms | 9930848 | 80 | 1.60361e+09 | 3.59053e+06 | 1(Win) |
| jsonifier (two-stage) | 2354.07 | 0.308921 | 6699.52ms | 9930848 | 80 | 1.23572e+10 | 4.02315e+06 | 2(Loss) |
| simdjson (ondemand) | 587.162 | 1.2914 | 11390.4ms | 9930848 | 30 | 1.30167e+12 | 1.61298e+07 | 3(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 765.548 | 0.077404 | 8633.63ms | 1834197 | 40 | 1.25122e+08 | 2.28493e+06 | 1(Win) |
| jsonifier (two-stage) | 604.613 | 0.217674 | 5046.97ms | 1834197 | 80 | 3.17278e+09 | 2.89313e+06 | 2(Loss) |
| simdjson (ondemand) | 384.914 | 0.143539 | 7433.96ms | 1834197 | 40 | 1.70203e+09 | 4.54446e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2876.77 | 0.312377 | 5581.14ms | 9930848 | 80 | 8.4608e+09 | 3.29217e+06 | 1(Win) |
| jsonifier (two-stage) | 2304.23 | 0.221657 | 6363.37ms | 9930848 | 40 | 3.32004e+09 | 4.11018e+06 | 2(Loss) |
| simdjson (ondemand) | 1818.27 | 0.297086 | 9432.05ms | 9930848 | 30 | 7.1836e+09 | 5.2087e+06 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1101.81 | 0.268185 | 7558.05ms | 642697 | 30 | 6.67716e+07 | 556289 | 1(Win) |
| jsonifier (two-stage) | 872.888 | 0.566211 | 9467.44ms | 642697 | 40 | 6.32285e+08 | 702179 | 2(Loss) |
| simdjson (ondemand) | 781.78 | 0.144045 | 5120.09ms | 642697 | 160 | 2.04061e+08 | 784010 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1570.98 | 0.163845 | 9994.07ms | 1225964 | 80 | 1.18952e+08 | 744232 | 1(Win) |
| jsonifier | 1531.15 | 0.0979104 | 5117.9ms | 1225964 | 320 | 1.78867e+08 | 763592 | 2(Loss) |
| simdjson (ondemand) | 1443.78 | 0.13849 | 5308.23ms | 1225964 | 80 | 1.00619e+08 | 809800 | 3(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1463.66 | 0.48303 | 7253.25ms | 409725 | 160 | 2.66056e+08 | 266964 | 1(Win) |
| jsonifier (two-stage) | 1126.45 | 0.10953 | 10068.2ms | 409725 | 640 | 9.23864e+07 | 346882 | 2(Loss) |
| simdjson (ondemand) | 793.496 | 0.349989 | 6758.2ms | 409725 | 160 | 4.75253e+08 | 492434 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2178.22 | 0.145518 | 9664.9ms | 785750 | 320 | 8.0195e+07 | 344019 | 1(Win) |
| jsonifier (two-stage) | 1935.53 | 0.141747 | 5313.22ms | 785750 | 320 | 9.63713e+07 | 387155 | 2(Loss) |
| simdjson (ondemand) | 1385.04 | 0.103948 | 7255.7ms | 785750 | 640 | 2.02423e+08 | 541031 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2361.64 | 0.1718 | 6469.05ms | 264040 | 640 | 2.14751e+07 | 106624 | 1(Win) |
| jsonifier (two-stage) | 1672.86 | 0.154874 | 8674.09ms | 264040 | 1280 | 6.95641e+07 | 150525 | 2(Loss) |
| simdjson (ondemand) | 1501.59 | 0.0848731 | 9447.4ms | 264040 | 2560 | 5.18583e+07 | 167695 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2633.12 | 0.234431 | 8511.16ms | 399947 | 640 | 7.38028e+07 | 144854 | 1(Win) |
| jsonifier (two-stage) | 2256.13 | 0.123831 | 9775.07ms | 399947 | 2560 | 1.12194e+08 | 169059 | 2(Loss) |
| simdjson (ondemand) | 2173.93 | 0.250415 | 5080.28ms | 399947 | 80 | 1.54428e+07 | 175452 | 3(Loss) |
