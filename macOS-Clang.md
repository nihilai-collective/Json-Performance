# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [abc3e34](https://github.com/nihilai-collective/jsonifier/commit/abc3e34)  
| Glaze: [99fcc35](https://github.com/stephenberry/glaze/commit/99fcc35)  
| Simdjson: [645e5c8](https://github.com/simdjson/simdjson/commit/645e5c8)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |
| Glaze (structural-skip) | `NEON64` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1231.82 | 2.85133 | 1633.62ms | 6661897 | 30 | 6.48813e+11 | 5.15765e+06 | 1(Tie) |
| glaze STATISTICAL TIE | 1226.59 | 0.465394 | 34865.2ms | 6661897 | 320 | 1.85947e+11 | 5.17963e+06 | 1(Tie) |
| simdjson (ondemand) | 1040.83 | 3.05678 | 4211.08ms | 6661897 | 40 | 1.3926e+12 | 6.10406e+06 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2456.1 | 0.911716 | 167.783ms | 1439562 | 30 | 7.79127e+08 | 558964 | 1(Win) |
| simdjson (ondemand) | 1910.06 | 0.441546 | 1205.49ms | 1439562 | 80 | 8.05761e+08 | 718758 | 2(Loss) |
| glaze | 1809.06 | 1.61831 | 226.303ms | 1439562 | 30 | 4.52484e+09 | 758889 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1632.41 | 1.71878 | 61.3264ms | 94370 | 40 | 3.59179e+07 | 55132.2 | 1(Win) |
| simdjson (ondemand) | 1430.69 | 1.29648 | 18.646ms | 94370 | 30 | 1.9954e+07 | 62905.6 | 2(Loss) |
| glaze | 1236.4 | 5.31961 | 48.3753ms | 94370 | 40 | 5.99751e+08 | 72790.7 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1926.46 | 0.0878658 | 5.0205ms | 31235 | 30 | 5537.63 | 15462.6 | 1(Win) |
| glaze STATISTICAL TIE | 1505.63 | 1.54957 | 13.4849ms | 31235 | 40 | 3.7595e+06 | 19784.4 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1476.54 | 4.55828 | 89.9629ms | 31235 | 160 | 1.35306e+08 | 20174.2 | 2(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2276.43 | 0.718512 | 137.435ms | 213963 | 80 | 3.31839e+07 | 89636.5 | 1(Win) |
| glaze | 1831.5 | 1.19066 | 669.044ms | 213963 | 320 | 5.63107e+08 | 111412 | 2(Loss) |
| simdjson (ondemand) | 1665.82 | 0.43769 | 6569.44ms | 213963 | 2560 | 7.3586e+08 | 122493 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1775.71 | 0.708239 | 19473.9ms | 9930848 | 160 | 2.28301e+11 | 5.33352e+06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1700.16 | 4.15154 | 1677.68ms | 9930848 | 30 | 1.60448e+12 | 5.57053e+06 | 1(Tie) |
| simdjson (ondemand) | 1443.21 | 2.17667 | 4686.4ms | 9930848 | 40 | 8.16128e+11 | 6.5623e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1371.96 | 0.562735 | 1288.44ms | 1225964 | 80 | 1.83981e+09 | 852192 | 1(Win) |
| simdjson (ondemand) | 1303.06 | 0.98029 | 264.958ms | 1225964 | 30 | 2.3209e+09 | 897249 | 2(Loss) |
| jsonifier | 1217.57 | 0.488253 | 23866.4ms | 1225964 | 1280 | 2.81365e+10 | 960251 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1171.48 | 1.7722 | 203.468ms | 785750 | 30 | 3.85517e+09 | 639658 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1158.01 | 0.952975 | 452.354ms | 785750 | 40 | 1.52114e+09 | 647102 | 1(Tie) |
| jsonifier | 1001.57 | 1.1665 | 1055.61ms | 785750 | 80 | 6.09343e+09 | 748173 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 4235.64 | 0.387968 | 27.6882ms | 399947 | 30 | 3.66168e+06 | 90050 | 1(Win) |
| jsonifier | 4068.69 | 0.262098 | 4996.95ms | 399947 | 2560 | 1.54549e+08 | 93745.1 | 2(Loss) |
| glaze | 2465.01 | 1.08784 | 45.8106ms | 399947 | 30 | 8.49995e+07 | 154733 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1980.96 | 0.247818 | 60.0639ms | 399947 | 30 | 6.83036e+06 | 192543 | 1(Win) |
| jsonifier | 1877.82 | 2.21561 | 63.226ms | 399947 | 30 | 6.07583e+08 | 203118 | 2(Loss) |
| glaze | 1571.73 | 1.5098 | 73.5808ms | 399947 | 30 | 4.02727e+08 | 242675 | 3(Loss) |
