# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

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
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1643.84 | 0.664495 | 87.287ms | 94370 | 80 | 1.05882e+07 | 54748.8 | 1(Win) |
| jsonifier | 1572.49 | 0.261505 | 18.626ms | 94370 | 30 | 672008 | 57233.1 | 2(Loss) |
| simdjson (ondemand) | 1102.49 | 3.17145 | 62.4791ms | 94370 | 40 | 2.681e+08 | 81632 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1701.99 | 1.29597 | 5.8711ms | 31235 | 30 | 1.54341e+06 | 17501.9 | 1(Win) |
| glaze | 1429.7 | 0.814755 | 34.487ms | 31235 | 80 | 2.30536e+06 | 20835.2 | 2(Loss) |
| simdjson (ondemand) | 1183.12 | 2.4492 | 37.527ms | 31235 | 80 | 3.04205e+07 | 25177.6 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2135.97 | 4.84825 | 29.771ms | 213963 | 30 | 6.43541e+08 | 95530.7 | 1(Tie) |
| glaze STATISTICAL TIE | 2096.05 | 0.538181 | 70.4169ms | 213963 | 40 | 1.09798e+07 | 97350.4 | 1(Tie) |
| simdjson (ondemand) | 1638.95 | 2.30191 | 36.158ms | 213963 | 30 | 2.46403e+08 | 124501 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2085.28 | 0.895118 | 3329.51ms | 9930848 | 40 | 6.61093e+10 | 4.54173e+06 | 1(Win) |
| glaze | 1637.47 | 0.498813 | 8732.03ms | 9930848 | 80 | 6.65877e+10 | 5.78381e+06 | 2(Loss) |
| simdjson (ondemand) | 1502.58 | 0.880824 | 4252.85ms | 9930848 | 40 | 1.23293e+11 | 6.30303e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1093.32 | 1.89809 | 6591.04ms | 1225964 | 320 | 1.3184e+11 | 1.06938e+06 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 999.698 | 2.33967 | 7187.9ms | 1225964 | 320 | 2.39595e+11 | 1.16952e+06 | 2(Tie) |
| jsonifier STATISTICAL TIE | 880.858 | 6.70541 | 393.035ms | 1225964 | 30 | 2.37638e+11 | 1.32731e+06 | 2(Tie) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 931.385 | 0.30805 | 24346.7ms | 785750 | 1280 | 7.86252e+09 | 804554 | 1(Win) |
| glaze STATISTICAL TIE | 772.599 | 7.01389 | 311.867ms | 785750 | 30 | 1.38835e+11 | 969907 | 2(Tie) |
| jsonifier STATISTICAL TIE | 692.972 | 3.91913 | 1561.76ms | 785750 | 80 | 1.43683e+11 | 1.08136e+06 | 2(Tie) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 3941.58 | 1.57356 | 29.3519ms | 399947 | 30 | 6.95586e+07 | 96768 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3833.41 | 0.0981735 | 30.3808ms | 399947 | 30 | 286249 | 99498.7 | 1(Tie) |
| glaze | 2689.94 | 0.562023 | 1857.16ms | 399947 | 640 | 4.06451e+08 | 141795 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1757.08 | 0.470548 | 341.635ms | 399947 | 80 | 8.34678e+07 | 217075 | 1(Win) |
| simdjson (ondemand) | 1709.95 | 0.0822241 | 1582.59ms | 399947 | 320 | 1.07644e+07 | 223059 | 2(Loss) |
| glaze | 1683.53 | 0.194634 | 23806.2ms | 399947 | 4890 | 9.50848e+08 | 226560 | 3(Loss) |
