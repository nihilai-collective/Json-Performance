# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [b7e65b3](https://github.com/nihilai-collective/jsonifier/commit/b7e65b3)  
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
| jsonifier | 1351.65 | 1.89986 | 1670.63ms | 6661897 | 30 | 2.39239e+11 | 4.7004e+06 | 1(Win) |
| simdjson (ondemand) | 1126.13 | 0.607352 | 8480.59ms | 6661897 | 80 | 9.39268e+10 | 5.64169e+06 | 2(Loss) |
| glaze | 1046.57 | 1.51006 | 10121.3ms | 6661897 | 80 | 6.7226e+11 | 6.07055e+06 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2609.1 | 0.458375 | 1683.27ms | 1439562 | 160 | 9.30766e+08 | 526186 | 1(Win) |
| glaze | 1966.55 | 1.23255 | 214.012ms | 1439562 | 30 | 2.22118e+09 | 698112 | 2(Loss) |
| simdjson (ondemand) | 1768.02 | 0.831822 | 236.645ms | 1439562 | 30 | 1.25161e+09 | 776504 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1862.46 | 0.0762255 | 16.2133ms | 94370 | 30 | 40702.1 | 48322.3 | 1(Win) |
| glaze | 1625.09 | 0.46698 | 17.1571ms | 94370 | 30 | 2.00647e+06 | 55380.5 | 2(Loss) |
| simdjson (ondemand) | 1508.49 | 1.0813 | 18.1643ms | 94370 | 30 | 1.24851e+07 | 59661 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1843.99 | 1.41617 | 12.2181ms | 31235 | 40 | 2.09342e+06 | 16154.1 | 1(Win) |
| simdjson (ondemand) | 1672.94 | 0.935798 | 30.8626ms | 31235 | 80 | 2.22113e+06 | 17805.8 | 2(Loss) |
| glaze | 1565.21 | 1.7476 | 13.2835ms | 31235 | 40 | 4.42467e+06 | 19031.3 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2439.34 | 0.30083 | 26.5673ms | 213963 | 30 | 1.89975e+06 | 83650.1 | 1(Win) |
| glaze | 2025.57 | 0.637065 | 164.855ms | 213963 | 80 | 3.29489e+07 | 100738 | 2(Loss) |
| simdjson (ondemand) | 1823.65 | 0.40115 | 34.2444ms | 213963 | 30 | 6.04408e+06 | 111892 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2100.86 | 0.580214 | 1410.72ms | 9930848 | 30 | 2.05247e+10 | 4.50807e+06 | 1(Win) |
| glaze | 1722.19 | 0.215856 | 1645.78ms | 9930848 | 30 | 4.22728e+09 | 5.49927e+06 | 2(Loss) |
| simdjson (ondemand) | 1610.72 | 0.225539 | 1760.24ms | 9930848 | 30 | 5.27592e+09 | 5.87986e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1493.09 | 0.40573 | 236.086ms | 1225964 | 30 | 3.02816e+08 | 783054 | 1(Win) |
| jsonifier | 1297.77 | 0.330898 | 271.174ms | 1225964 | 30 | 2.66607e+08 | 900908 | 2(Loss) |
| simdjson (ondemand) | 1220 | 0.694787 | 652.186ms | 1225964 | 40 | 1.77337e+09 | 958337 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1282.66 | 0.266204 | 176.842ms | 785750 | 30 | 7.25596e+07 | 584215 | 1(Win) |
| glaze | 1266.96 | 0.325714 | 177.529ms | 785750 | 30 | 1.11336e+08 | 591453 | 2(Loss) |
| jsonifier | 1109.47 | 0.31171 | 204.796ms | 785750 | 30 | 1.32973e+08 | 675414 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4268.56 | 0.524955 | 27.6654ms | 399947 | 30 | 6.60098e+06 | 89355.5 | 1(Win) |
| simdjson (ondemand) | 3958.62 | 0.365083 | 29.562ms | 399947 | 30 | 3.7121e+06 | 96351.4 | 2(Loss) |
| glaze | 2646.22 | 1.17413 | 42.5038ms | 399947 | 30 | 8.59223e+07 | 144138 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1822.9 | 0.530875 | 64.3911ms | 399947 | 30 | 3.70156e+07 | 209238 | 1(Win) |
| glaze STATISTICAL TIE | 1774.35 | 0.195564 | 1533.69ms | 399947 | 320 | 5.65526e+07 | 214962 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1745.93 | 1.37086 | 2766.92ms | 399947 | 640 | 5.74002e+09 | 218461 | 2(Tie) |
