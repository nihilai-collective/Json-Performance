# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [b7e65b3](https://github.com/nihilai-collective/jsonifier/commit/b7e65b3)  
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
| glaze STATISTICAL TIE | 1010.66 | 0.108071 | 2063.63ms | 6661897 | 30 | 1.38461e+09 | 6.28627e+06 | 2.3075 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1007.79 | 0.905137 | 1951.13ms | 6661897 | 30 | 9.76807e+10 | 6.30419e+06 | 2.31408 | 1(Tie) |
| simdjson (ondemand) | 954.275 | 0.213164 | 2003.23ms | 6661897 | 30 | 6.04226e+09 | 6.6577e+06 | 2.44384 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1863.5 | 0.172499 | 225.695ms | 1439562 | 30 | 4.84506e+07 | 736718 | 1.25139 | 1(Win) |
| glaze | 1493.88 | 0.164981 | 281.316ms | 1439562 | 30 | 6.89637e+07 | 919000 | 1.56104 | 2(Loss) |
| simdjson (ondemand) | 1362.92 | 0.142221 | 306.198ms | 1439562 | 30 | 6.157e+07 | 1.00731e+06 | 1.71102 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1191.02 | 1.51551 | 25.2999ms | 94370 | 30 | 3.9343e+07 | 75563.9 | 1.95647 | 1(Win) |
| glaze | 1113.49 | 1.23188 | 27.008ms | 94370 | 30 | 2.97409e+07 | 80825.4 | 2.09329 | 2(Loss) |
| simdjson (ondemand) | 1051.4 | 1.65606 | 28.1986ms | 94370 | 30 | 6.02842e+07 | 85598.5 | 2.2166 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1473.53 | 0.0976343 | 8.67664ms | 31235 | 30 | 11686.7 | 20215.5 | 1.57986 | 1(Win) |
| simdjson (ondemand) | 1309.72 | 2.17866 | 9.20172ms | 31235 | 30 | 7.36591e+06 | 22743.8 | 1.77768 | 2(Loss) |
| glaze | 1121.45 | 0.166338 | 10.5805ms | 31235 | 30 | 58563.9 | 26562.1 | 2.07651 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1699.2 | 1.24187 | 38.813ms | 213963 | 30 | 6.67204e+07 | 120086 | 1.37191 | 1(Win) |
| glaze | 1445.01 | 1.41538 | 44.6327ms | 213963 | 30 | 1.1984e+08 | 141211 | 1.61324 | 2(Loss) |
| simdjson (ondemand) | 1380.29 | 0.759553 | 47.1839ms | 213963 | 30 | 3.78244e+07 | 147832 | 1.68907 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1596.68 | 0.0776142 | 1784.69ms | 9930848 | 30 | 6.35828e+08 | 5.93155e+06 | 1.46058 | 1(Win) |
| glaze | 1382.93 | 0.0802311 | 2055.87ms | 9930848 | 30 | 9.05686e+08 | 6.84834e+06 | 1.68634 | 2(Loss) |
| simdjson (ondemand) | 554.289 | 0.107412 | 5153.05ms | 9930848 | 30 | 1.01048e+10 | 1.70864e+07 | 4.20738 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1681.51 | 0.177713 | 1690.88ms | 9930848 | 30 | 3.00561e+09 | 5.63231e+06 | 1.38689 | 1(Win) |
| glaze | 1430.16 | 0.136456 | 1991.07ms | 9930848 | 30 | 2.4497e+09 | 6.6222e+06 | 1.63066 | 2(Loss) |
| simdjson (ondemand) | 1393.43 | 0.176389 | 2034.09ms | 9930848 | 30 | 4.3119e+09 | 6.79675e+06 | 1.6736 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1138.38 | 0.169288 | 311.63ms | 1225964 | 30 | 9.06899e+07 | 1.02705e+06 | 2.04848 | 1(Win) |
| jsonifier | 1058.66 | 0.13548 | 334.295ms | 1225964 | 30 | 6.71612e+07 | 1.10439e+06 | 2.2028 | 2(Loss) |
| simdjson (ondemand) | 1031.03 | 0.119996 | 343.081ms | 1225964 | 30 | 5.5547e+07 | 1.13398e+06 | 2.2618 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 869.922 | 0.261173 | 261.284ms | 785750 | 30 | 1.5184e+08 | 861398 | 2.68065 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 869.897 | 0.194822 | 260.967ms | 785750 | 30 | 8.44951e+07 | 861423 | 2.68074 | 1(Tie) |
| glaze | 680.357 | 1.09008 | 331.204ms | 785750 | 30 | 4.3245e+09 | 1.10141e+06 | 3.42759 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3702.71 | 0.980271 | 33.7653ms | 399947 | 30 | 3.05901e+07 | 103011 | 0.629537 | 1(Win) |
| simdjson (ondemand) | 3540.84 | 1.07172 | 35.1911ms | 399947 | 30 | 3.99831e+07 | 107720 | 0.658302 | 2(Loss) |
| glaze | 2301.18 | 0.642303 | 52.3475ms | 399947 | 30 | 3.40021e+07 | 165750 | 1.0131 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1203.27 | 0.43644 | 98.9909ms | 399947 | 30 | 5.74184e+07 | 316986 | 1.93783 | 1(Win) |
| jsonifier | 1153.19 | 0.513425 | 107.374ms | 399947 | 30 | 8.6513e+07 | 330753 | 2.0218 | 2(Loss) |
| glaze | 1072.25 | 0.481918 | 109.131ms | 399947 | 30 | 8.81615e+07 | 355718 | 2.17455 | 3(Loss) |
