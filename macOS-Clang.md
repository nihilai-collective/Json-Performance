# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [0953100](https://github.com/nihilai-collective/jsonifier/commit/0953100)  
| Glaze: [2d38174](https://github.com/stephenberry/glaze/commit/2d38174)  
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
| simdjson (ondemand) | 1142.81 | 1.07776 | 1678.64ms | 6661897 | 30 | 1.07699e+11 | 5.55933e+06 | 1(Win) |
| glaze STATISTICAL TIE | 1090.19 | 1.78342 | 18588.4ms | 6661897 | 160 | 1.72831e+12 | 5.82769e+06 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1009.26 | 8.38768 | 1940.45ms | 6661897 | 30 | 8.36358e+12 | 6.29497e+06 | 2(Tie) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1457.44 | 1.7416 | 46.6654ms | 94370 | 40 | 4.62644e+07 | 61751.1 | 1(Tie) |
| glaze STATISTICAL TIE | 1447.92 | 0.841745 | 1710.51ms | 94370 | 1280 | 3.5039e+08 | 62157.1 | 1(Tie) |
| jsonifier | 1088.16 | 2.33931 | 2030.62ms | 94370 | 1280 | 4.79149e+09 | 82707.1 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1932.21 | 1.18058 | 5.42517ms | 31235 | 30 | 993778 | 15416.6 | 1(Win) |
| glaze STATISTICAL TIE | 1661.43 | 1.20925 | 31.3149ms | 31235 | 80 | 3.76045e+06 | 17929.1 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1630.11 | 2.06077 | 5.635ms | 31235 | 30 | 4.25431e+06 | 18273.6 | 2(Tie) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2079.59 | 1.49891 | 1379.56ms | 9930848 | 30 | 1.39795e+11 | 4.55417e+06 | 1(Win) |
| glaze | 1653.11 | 3.24211 | 1732.65ms | 9930848 | 30 | 1.03501e+12 | 5.72906e+06 | 2(Loss) |
| simdjson (ondemand) | 1428.86 | 1.32488 | 9479.43ms | 9930848 | 80 | 6.16931e+11 | 6.62822e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1507.83 | 0.328395 | 234.882ms | 1225964 | 30 | 1.94521e+08 | 775400 | 1(Win) |
| simdjson (ondemand) | 1334.59 | 0.227974 | 286.307ms | 1225964 | 30 | 1.1966e+08 | 876051 | 2(Loss) |
| jsonifier | 1276.41 | 1.12428 | 1522.33ms | 1225964 | 80 | 8.48422e+09 | 915983 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1292.06 | 0.385645 | 175.981ms | 785750 | 30 | 1.50073e+08 | 579967 | 1(Win) |
| simdjson (ondemand) | 1272.92 | 0.403332 | 179.526ms | 785750 | 30 | 1.69128e+08 | 588688 | 2(Loss) |
| jsonifier | 1129.25 | 0.642723 | 207.3ms | 785750 | 30 | 5.45707e+08 | 663583 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4192.31 | 0.513039 | 27.7757ms | 399947 | 30 | 6.53613e+06 | 90980.6 | 1(Win) |
| simdjson (ondemand) | 3880.37 | 0.916974 | 29.9217ms | 399947 | 30 | 2.43721e+07 | 98294.4 | 2(Loss) |
| glaze | 2684.13 | 0.626605 | 42.7892ms | 399947 | 30 | 2.37852e+07 | 142101 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1842.94 | 0.413758 | 65.385ms | 399947 | 30 | 2.19987e+07 | 206962 | 1(Win) |
| glaze STATISTICAL TIE | 1803.12 | 0.741279 | 65.4975ms | 399947 | 30 | 7.37635e+07 | 211533 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1788.88 | 0.413501 | 2838.82ms | 399947 | 640 | 4.97478e+08 | 213216 | 2(Tie) |
