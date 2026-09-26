# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [0c74f7f](https://github.com/nihilai-collective/jsonifier/commit/0c74f7f)  
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
| jsonifier | 1186.15 | 0.158526 | 1621.06ms | 6661897 | 30 | 2.16293e+09 | 5.35623e+06 | 1.96607 | 1(Win) |
| glaze | 999.356 | 0.117098 | 1913.8ms | 6661897 | 30 | 1.66255e+09 | 6.35738e+06 | 2.33358 | 2(Loss) |
| simdjson (ondemand) | 925.875 | 0.106205 | 2058.21ms | 6661897 | 30 | 1.59331e+09 | 6.86192e+06 | 2.51874 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1864.14 | 0.319391 | 225.478ms | 1439562 | 30 | 1.65985e+08 | 736463 | 1.25094 | 1(Win) |
| glaze | 1521.7 | 0.293449 | 271.945ms | 1439562 | 30 | 2.10277e+08 | 902199 | 1.53246 | 2(Loss) |
| simdjson (ondemand) | 1359.58 | 0.246464 | 305.707ms | 1439562 | 30 | 1.85815e+08 | 1.00978e+06 | 1.71522 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1142.63 | 2.19283 | 26.1722ms | 94370 | 30 | 8.9492e+07 | 78763.9 | 2.03971 | 1(Tie) |
| glaze STATISTICAL TIE | 1073.18 | 2.59078 | 27.387ms | 94370 | 30 | 1.41613e+08 | 83861 | 2.17167 | 1(Tie) |
| simdjson (ondemand) | 1059.51 | 1.19649 | 28.2988ms | 94370 | 30 | 3.09882e+07 | 84943.2 | 2.19966 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1340.5 | 2.10593 | 9.39716ms | 31235 | 30 | 6.56991e+06 | 22221.6 | 1.73684 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1282.06 | 1.86792 | 9.40857ms | 31235 | 30 | 5.65072e+06 | 23234.5 | 1.81609 | 1(Tie) |
| glaze | 1049.58 | 1.24275 | 11.0404ms | 31235 | 30 | 3.73199e+06 | 28380.9 | 2.2191 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1687.67 | 1.27147 | 39.1543ms | 213963 | 30 | 7.0899e+07 | 120907 | 1.38128 | 1(Win) |
| glaze | 1457.1 | 1.04883 | 44.7677ms | 213963 | 30 | 6.47197e+07 | 140040 | 1.59994 | 2(Loss) |
| simdjson (ondemand) | 1368.42 | 1.38833 | 46.9185ms | 213963 | 30 | 1.28571e+08 | 149115 | 1.70363 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1741.67 | 0.340821 | 1635.44ms | 9930848 | 30 | 1.03042e+10 | 5.43777e+06 | 1.33894 | 1(Win) |
| glaze | 1371.1 | 0.139409 | 2074.07ms | 9930848 | 30 | 2.78184e+09 | 6.90742e+06 | 1.70086 | 2(Loss) |
| simdjson (ondemand) | 530.284 | 0.19783 | 5296.65ms | 9930848 | 30 | 3.74509e+10 | 1.78599e+07 | 4.39767 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1703.04 | 0.223558 | 1683.47ms | 9930848 | 30 | 4.63686e+09 | 5.56111e+06 | 1.36932 | 1(Win) |
| simdjson (ondemand) | 1326.88 | 0.302885 | 2139.48ms | 9930848 | 30 | 1.40212e+10 | 7.13764e+06 | 1.75751 | 2(Loss) |
| glaze | 1289.64 | 0.172731 | 2204.9ms | 9930848 | 30 | 4.82719e+09 | 7.34375e+06 | 1.80826 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1110.39 | 0.115321 | 319.073ms | 1225964 | 30 | 4.42329e+07 | 1.05294e+06 | 2.10018 | 1(Win) |
| jsonifier | 1075.47 | 0.117842 | 330.992ms | 1225964 | 30 | 4.92355e+07 | 1.08712e+06 | 2.16836 | 2(Loss) |
| simdjson (ondemand) | 1065.15 | 0.213138 | 331.903ms | 1225964 | 30 | 1.64201e+08 | 1.09766e+06 | 2.18935 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 896.389 | 0.262011 | 253.63ms | 785750 | 30 | 1.43925e+08 | 835965 | 2.60155 | 1(Win) |
| jsonifier | 808.604 | 0.144749 | 281.54ms | 785750 | 30 | 5.39819e+07 | 926720 | 2.88398 | 2(Loss) |
| glaze | 687.567 | 0.312091 | 328.019ms | 785750 | 30 | 3.47075e+08 | 1.08986e+06 | 3.39164 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3540.4 | 2.26529 | 34.4358ms | 399947 | 30 | 1.78677e+08 | 107733 | 0.658388 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3337 | 2.21452 | 36.4597ms | 399947 | 30 | 1.92209e+08 | 114300 | 0.698549 | 1(Tie) |
| glaze | 2307.87 | 0.94726 | 52.5411ms | 399947 | 30 | 7.35259e+07 | 165269 | 1.0102 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1191.96 | 0.534902 | 99.5596ms | 399947 | 30 | 8.78925e+07 | 319993 | 1.95621 | 1(Win) |
| jsonifier | 1117.84 | 0.809048 | 107.31ms | 399947 | 30 | 2.28623e+08 | 341212 | 2.08581 | 2(Loss) |
| glaze | 1072.23 | 0.699904 | 110.04ms | 399947 | 30 | 1.85964e+08 | 355726 | 2.17467 | 3(Loss) |
