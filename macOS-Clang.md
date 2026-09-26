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
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1615.75 | 0.693818 | 269.636ms | 1439562 | 30 | 1.04262e+09 | 849682 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1545.19 | 6.80797 | 579.427ms | 1439562 | 40 | 1.4635e+11 | 888482 | 1(Tie) |
| glaze | 1282.46 | 5.7794 | 704.217ms | 1439562 | 40 | 1.53109e+11 | 1.0705e+06 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1516.11 | 1.4706 | 402.571ms | 94370 | 320 | 2.43861e+08 | 59361.2 | 1(Win) |
| glaze STATISTICAL TIE | 1384.38 | 3.38898 | 19.7773ms | 94370 | 30 | 1.45618e+08 | 65009.8 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1314.87 | 2.58469 | 105.919ms | 94370 | 80 | 2.50384e+08 | 68446.3 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1820.96 | 1.44138 | 5.29579ms | 31235 | 30 | 1.66788e+06 | 16358.4 | 1(Win) |
| glaze | 1408.02 | 1.8769 | 276.113ms | 31235 | 640 | 1.00909e+08 | 21156 | 2(Loss) |
| simdjson (ondemand) | 1327.4 | 0.681849 | 2433.96ms | 31235 | 4890 | 1.14489e+08 | 22440.8 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2105.88 | 4.25905 | 31.365ms | 213963 | 30 | 5.10925e+08 | 96895.8 | 1(Win) |
| glaze | 1813.02 | 2.44314 | 34.8828ms | 213963 | 30 | 2.26823e+08 | 112547 | 2(Loss) |
| simdjson (ondemand) | 1639.61 | 0.894392 | 403.96ms | 213963 | 160 | 1.9823e+08 | 124451 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1730.44 | 1.03552 | 18447.1ms | 9930848 | 160 | 5.13923e+11 | 5.47305e+06 | 1(Win) |
| glaze | 1387.79 | 1.36604 | 22826.3ms | 9930848 | 160 | 1.3905e+12 | 6.82436e+06 | 2(Loss) |
| simdjson (ondemand) | 1331.21 | 0.772617 | 2219.06ms | 9930848 | 30 | 9.06425e+10 | 7.11445e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1464.04 | 0.245861 | 11379.8ms | 1225964 | 640 | 2.46724e+09 | 798592 | 1(Win) |
| simdjson (ondemand) | 1300.25 | 0.76819 | 278.238ms | 1225964 | 30 | 1.43139e+09 | 899186 | 2(Loss) |
| jsonifier | 770.38 | 3.19609 | 4810.31ms | 1225964 | 160 | 3.76448e+11 | 1.51765e+06 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1260.06 | 0.233139 | 8795.14ms | 785750 | 640 | 1.23025e+09 | 594693 | 1(Win) |
| glaze | 1220.09 | 0.582538 | 209.15ms | 785750 | 30 | 3.84023e+08 | 614176 | 2(Loss) |
| jsonifier | 1073.04 | 1.55072 | 2330.16ms | 785750 | 160 | 1.87638e+10 | 698341 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 4009.02 | 1.09185 | 32.4372ms | 399947 | 30 | 3.23727e+07 | 95140.4 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3948.15 | 0.515016 | 29.5155ms | 399947 | 30 | 7.42645e+06 | 96607.1 | 1(Tie) |
| glaze | 2560.08 | 1.29781 | 45.3955ms | 399947 | 30 | 1.12161e+08 | 148987 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1977.82 | 0.297171 | 145.425ms | 399947 | 40 | 1.31372e+07 | 192848 | 1(Win) |
| simdjson (ondemand) | 1744.22 | 0.479901 | 762.422ms | 399947 | 160 | 1.76209e+08 | 218676 | 2(Loss) |
| glaze | 1637.95 | 0.74191 | 2989.84ms | 399947 | 640 | 1.91024e+09 | 232864 | 3(Loss) |
