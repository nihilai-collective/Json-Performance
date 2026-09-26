# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [abc3e34](https://github.com/nihilai-collective/jsonifier/commit/abc3e34)  
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

> Adaptive sampling on (Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| simdjson (ondemand) | 1064.43 | 0.488117 | 1822.59ms | 6661897 | 30 | 2.54642e+10 | 5.9687e+06 | 2.50262 | 1(Win) |
| jsonifier | 1020.45 | 1.38675 | 1918.1ms | 6661897 | 30 | 2.23632e+11 | 6.22597e+06 | 2.61048 | 2(Loss) |
| glaze | 877.617 | 0.581359 | 2253.49ms | 6661897 | 30 | 5.31369e+10 | 7.23924e+06 | 3.03541 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1825.71 | 0.48435 | 226.427ms | 1439562 | 30 | 3.97957e+08 | 751965 | 1.45899 | 1(Win) |
| jsonifier | 1408 | 0.208469 | 298.531ms | 1439562 | 30 | 1.23955e+08 | 975055 | 1.89187 | 2(Loss) |
| glaze | 1352.1 | 0.160525 | 308.113ms | 1439562 | 30 | 7.96992e+07 | 1.01537e+06 | 1.9701 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1200.18 | 0.80566 | 24.1818ms | 94370 | 30 | 1.09497e+07 | 74987.3 | 2.21862 | 1(Win) |
| glaze STATISTICAL TIE | 1119.3 | 1.81343 | 25.4988ms | 94370 | 30 | 6.37825e+07 | 80406.2 | 2.37858 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1089.15 | 1.69099 | 26.4409ms | 94370 | 30 | 5.85727e+07 | 82631.7 | 2.44439 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1465.87 | 3.17907 | 7.57826ms | 31235 | 30 | 1.25203e+07 | 20321.1 | 1.8141 | 1(Win) |
| jsonifier | 1215.98 | 1.22694 | 8.9884ms | 31235 | 30 | 2.71017e+06 | 24497.1 | 2.18785 | 2(Loss) |
| glaze | 1040.72 | 0.734186 | 10.1961ms | 31235 | 30 | 1.32478e+06 | 28622.4 | 2.55679 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1773.32 | 1.54526 | 35.8037ms | 213963 | 30 | 9.48488e+07 | 115067 | 1.50172 | 1(Win) |
| jsonifier | 1398.28 | 0.554723 | 46.0942ms | 213963 | 30 | 1.96589e+07 | 145930 | 1.90473 | 2(Loss) |
| glaze | 1317.98 | 1.00189 | 48.2455ms | 213963 | 30 | 7.21806e+07 | 154822 | 2.02082 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1520.31 | 0.347663 | 1898.23ms | 9930848 | 30 | 1.40717e+10 | 6.2295e+06 | 1.75218 | 1(Win) |
| glaze | 1257.34 | 0.178115 | 2271.5ms | 9930848 | 30 | 5.39993e+09 | 7.5324e+06 | 2.1187 | 2(Loss) |
| simdjson (ondemand) | 434.371 | 0.798554 | 6624.79ms | 9930848 | 30 | 9.09453e+11 | 2.18035e+07 | 6.1329 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1523.86 | 0.483817 | 1891.44ms | 9930848 | 30 | 2.71248e+10 | 6.215e+06 | 1.74811 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1507.52 | 0.701814 | 4486.32ms | 9930848 | 40 | 7.77592e+10 | 6.28237e+06 | 1.76703 | 1(Tie) |
| glaze | 1227.57 | 0.17555 | 2318.6ms | 9930848 | 30 | 5.50304e+09 | 7.71506e+06 | 2.17003 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 988.865 | 0.221768 | 357.846ms | 1225964 | 30 | 2.06253e+08 | 1.18234e+06 | 2.69385 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 956.932 | 2.14663 | 361.128ms | 1225964 | 30 | 2.06362e+10 | 1.22179e+06 | 2.78376 | 1(Tie) |
| jsonifier | 875.91 | 1.24553 | 2002.41ms | 1225964 | 80 | 2.21125e+10 | 1.33481e+06 | 3.04119 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1033.63 | 0.239341 | 219.78ms | 785750 | 30 | 9.03228e+07 | 724972 | 2.57712 | 1(Win) |
| jsonifier STATISTICAL TIE | 710.482 | 1.2488 | 306.964ms | 785750 | 30 | 5.20436e+09 | 1.05471e+06 | 3.74928 | 2(Tie) |
| glaze STATISTICAL TIE | 703.283 | 0.192932 | 322.208ms | 785750 | 30 | 1.26776e+08 | 1.0655e+06 | 3.78761 | 2(Tie) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4665.04 | 1.86053 | 26.1096ms | 399947 | 30 | 6.94202e+07 | 81761.1 | 0.570799 | 1(Win) |
| simdjson (ondemand) | 4300.47 | 2.17064 | 27.7801ms | 399947 | 30 | 1.11191e+08 | 88692.5 | 0.619081 | 2(Loss) |
| glaze | 1851.05 | 0.528998 | 63.6658ms | 399947 | 30 | 3.56448e+07 | 206055 | 1.4389 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1403.62 | 0.805147 | 82.9584ms | 399947 | 30 | 1.43608e+08 | 271740 | 1.8974 | 1(Win) |
| glaze | 995.734 | 0.44191 | 116.538ms | 399947 | 30 | 8.59622e+07 | 383053 | 2.67496 | 2(Loss) |
| jsonifier | 880.886 | 0.549421 | 132.427ms | 399947 | 30 | 1.69784e+08 | 432995 | 3.02334 | 3(Loss) |
