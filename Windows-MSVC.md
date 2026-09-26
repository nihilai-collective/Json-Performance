# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [48b1541](https://github.com/nihilai-collective/jsonifier/commit/48b1541)  
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

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 748.297 | 0.394012 | 26812.7ms | 6661897 | 160 | 1.79056e+11 | 8.49032e+06 | 3.11645 | 1(Win) |
| simdjson (ondemand) | 595.908 | 1.18434 | 7434.59ms | 6661897 | 40 | 6.37745e+11 | 1.06615e+07 | 3.91344 | 2(Loss) |
| glaze | 530.993 | 0.23267 | 37401.2ms | 6661897 | 160 | 1.23999e+11 | 1.19649e+07 | 4.39188 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1231.66 | 0.443572 | 354.636ms | 1439562 | 30 | 7.3338e+08 | 1.11465e+06 | 1.89327 | 1(Win) |
| glaze | 1002.39 | 0.291431 | 4353.45ms | 1439562 | 160 | 2.54907e+09 | 1.3696e+06 | 2.32637 | 2(Loss) |
| simdjson (ondemand) | 715.016 | 0.167089 | 585.361ms | 1439562 | 30 | 3.08778e+08 | 1.92006e+06 | 3.26148 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 896.605 | 1.59562 | 30.3326ms | 94370 | 30 | 7.6957e+07 | 100377 | 2.59951 | 1(Win) |
| jsonifier | 716.413 | 1.29462 | 38.4535ms | 94370 | 30 | 7.93501e+07 | 125623 | 3.25372 | 2(Loss) |
| simdjson (ondemand) | 500.481 | 0.800107 | 54.4969ms | 94370 | 30 | 6.21025e+07 | 179823 | 4.65824 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 889.493 | 1.02367 | 53.0499ms | 31235 | 80 | 9.40177e+06 | 33488.8 | 2.61888 | 1(Win) |
| glaze | 764.972 | 1.98695 | 27.1713ms | 31235 | 40 | 2.39455e+07 | 38940 | 3.0433 | 2(Loss) |
| simdjson (ondemand) | 607.836 | 2.42701 | 14.5534ms | 31235 | 30 | 4.244e+07 | 49006.7 | 3.83299 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1114.44 | 1.10192 | 55.7126ms | 213963 | 30 | 1.22119e+08 | 183097 | 2.09216 | 1(Win) |
| glaze | 990.218 | 0.922608 | 62.3962ms | 213963 | 30 | 1.08435e+08 | 206067 | 2.35427 | 2(Loss) |
| simdjson (ondemand) | 619.795 | 0.766243 | 99.1657ms | 213963 | 30 | 1.90913e+08 | 329223 | 3.7619 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1242.91 | 1.04173 | 11478.9ms | 9930848 | 80 | 5.0408e+11 | 7.61988e+06 | 1.87626 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 829.407 | 0.732198 | 3437.41ms | 9930848 | 30 | 2.09708e+11 | 1.14188e+07 | 2.81169 | 2(Tie) |
| glaze STATISTICAL TIE | 826.234 | 0.554344 | 3474.15ms | 9930848 | 30 | 1.21129e+11 | 1.14626e+07 | 2.82252 | 2(Tie) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 792.056 | 0.142999 | 1083.37ms | 1225964 | 40 | 1.78224e+08 | 1.47612e+06 | 2.94425 | 1(Win) |
| simdjson (ondemand) | 764.947 | 0.297547 | 1123.94ms | 1225964 | 40 | 8.27303e+08 | 1.52843e+06 | 3.04859 | 2(Loss) |
| glaze | 726.473 | 0.163504 | 486.53ms | 1225964 | 30 | 2.07729e+08 | 1.60938e+06 | 3.21007 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 644.977 | 0.628827 | 355.756ms | 785750 | 30 | 1.60127e+09 | 1.16182e+06 | 3.61544 | 1(Win) |
| glaze | 508.023 | 0.193626 | 470.351ms | 785750 | 30 | 2.4471e+08 | 1.47503e+06 | 4.59028 | 2(Loss) |
| simdjson (ondemand) | 484.85 | 0.356956 | 2328.89ms | 785750 | 80 | 2.43487e+09 | 1.54553e+06 | 4.80975 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2907.05 | 0.82997 | 235.292ms | 399947 | 80 | 9.48671e+07 | 131205 | 0.801817 | 1(Win) |
| simdjson (ondemand) | 1885.29 | 0.909209 | 60.7526ms | 399947 | 30 | 1.01507e+08 | 202313 | 1.23661 | 2(Loss) |
| glaze | 1547.61 | 0.7032 | 384.769ms | 399947 | 80 | 2.40285e+08 | 246456 | 1.50648 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 820.08 | 1.36566 | 147.513ms | 399947 | 30 | 1.21032e+09 | 465100 | 2.8428 | 1(Win) |
| glaze | 785.454 | 0.619776 | 161.596ms | 399947 | 30 | 2.7174e+08 | 485603 | 2.96844 | 2(Loss) |
| simdjson (ondemand) | 612.548 | 0.56007 | 188.173ms | 399947 | 30 | 3.64864e+08 | 622677 | 3.80642 | 3(Loss) |
