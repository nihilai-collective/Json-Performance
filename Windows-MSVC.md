# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [c210b82](https://github.com/nihilai-collective/jsonifier/commit/c210b82)  
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

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1205.73 | 0.404506 | 370.347ms | 1439562 | 30 | 6.36406e+08 | 1.13863e+06 | 1.93401 | 1(Win) |
| glaze | 860.118 | 3.32179 | 1090.8ms | 1439562 | 40 | 1.12447e+11 | 1.59614e+06 | 2.71109 | 2(Loss) |
| simdjson (ondemand) | 635.85 | 1.26916 | 6535.79ms | 1439562 | 160 | 1.20145e+11 | 2.15912e+06 | 3.66732 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 897.35 | 1.43614 | 30.6481ms | 94370 | 30 | 6.22386e+07 | 100293 | 2.59734 | 1(Win) |
| jsonifier | 741.968 | 1.45491 | 37.1765ms | 94370 | 30 | 9.34307e+07 | 121297 | 3.14084 | 2(Loss) |
| simdjson (ondemand) | 463.008 | 0.642885 | 140.473ms | 94370 | 40 | 6.24623e+07 | 194378 | 5.03493 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 863.671 | 1.03975 | 55.9243ms | 31235 | 80 | 1.0288e+07 | 34490 | 2.69681 | 1(Win) |
| glaze | 768.723 | 1.86688 | 27.418ms | 31235 | 40 | 2.09333e+07 | 38750 | 3.03148 | 2(Loss) |
| simdjson (ondemand) | 629.857 | 0.072353 | 14.5618ms | 31235 | 30 | 35126.4 | 47293.3 | 3.69943 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1103.3 | 1.24194 | 56.2317ms | 213963 | 30 | 1.58276e+08 | 184947 | 2.11299 | 1(Win) |
| glaze | 1000.59 | 1.04482 | 61.9827ms | 213963 | 30 | 1.36196e+08 | 203930 | 2.33025 | 2(Loss) |
| simdjson (ondemand) | 644.718 | 0.743592 | 95.4889ms | 213963 | 30 | 1.66161e+08 | 316497 | 3.61598 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1235.29 | 0.39399 | 2306.77ms | 9930848 | 30 | 2.7373e+10 | 7.66683e+06 | 1.88778 | 1(Win) |
| simdjson (ondemand) | 831.267 | 0.466581 | 3425.93ms | 9930848 | 30 | 8.47749e+10 | 1.13932e+07 | 2.80528 | 2(Loss) |
| glaze | 793.738 | 0.547487 | 3630.27ms | 9930848 | 30 | 1.28023e+11 | 1.19319e+07 | 2.93797 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 782.244 | 0.195542 | 448.91ms | 1225964 | 30 | 2.56256e+08 | 1.49464e+06 | 2.98123 | 1(Win) |
| simdjson (ondemand) | 759.231 | 0.944688 | 459.508ms | 1225964 | 30 | 6.34901e+09 | 1.53994e+06 | 3.07153 | 2(Loss) |
| glaze | 724.305 | 0.197503 | 489.752ms | 1225964 | 30 | 3.04918e+08 | 1.6142e+06 | 3.21964 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 640.3 | 0.267532 | 355.853ms | 785750 | 30 | 2.94087e+08 | 1.17031e+06 | 3.64202 | 1(Win) |
| glaze | 506.553 | 0.314939 | 446.361ms | 785750 | 30 | 6.51166e+08 | 1.47931e+06 | 4.60364 | 2(Loss) |
| simdjson (ondemand) | 447.728 | 2.84542 | 1155.37ms | 785750 | 40 | 9.07175e+10 | 1.67367e+06 | 5.20795 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2849.81 | 1.61072 | 42.3767ms | 399947 | 30 | 1.39423e+08 | 133840 | 0.817804 | 1(Win) |
| simdjson (ondemand) | 1852.96 | 1.4293 | 78.0394ms | 399947 | 30 | 2.59682e+08 | 205843 | 1.25802 | 2(Loss) |
| glaze | 1543.29 | 1.82969 | 77.9864ms | 399947 | 30 | 6.13458e+08 | 247147 | 1.51073 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 800.785 | 1.21451 | 154.774ms | 399947 | 30 | 1.00392e+09 | 476307 | 2.91133 | 1(Win) |
| glaze | 772.686 | 0.890069 | 390.274ms | 399947 | 40 | 7.72158e+08 | 493628 | 3.01743 | 2(Loss) |
| simdjson (ondemand) | 597.854 | 1.55576 | 188.609ms | 399947 | 30 | 2.95541e+09 | 637980 | 3.90001 | 3(Loss) |
