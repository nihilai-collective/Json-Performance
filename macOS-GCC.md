# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [a5152b8](https://github.com/nihilai-collective/jsonifier/commit/a5152b8)  
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

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1189.13 | 2.4912 | 4249.52ms | 6661897 | 40 | 7.08623e+11 | 5.3428e+06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1175.71 | 2.19935 | 1637.22ms | 6661897 | 30 | 4.23745e+11 | 5.40378e+06 | 1(Tie) |
| glaze | 1002.05 | 0.98298 | 4799.55ms | 6661897 | 40 | 1.55369e+11 | 6.34026e+06 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1940.46 | 2.30728 | 2538.56ms | 1439562 | 160 | 4.26357e+10 | 707499 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1527.29 | 0.413403 | 23700ms | 1439562 | 1280 | 1.76757e+10 | 898896 | 2(Tie) |
| glaze STATISTICAL TIE | 1519.35 | 2.00753 | 1416.18ms | 1439562 | 80 | 2.63244e+10 | 903590 | 2(Tie) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1585.19 | 0.750278 | 91.21ms | 94370 | 80 | 1.45158e+07 | 56774.4 | 1(Win) |
| jsonifier | 1280.57 | 1.36541 | 458.06ms | 94370 | 320 | 2.94672e+08 | 70280 | 2(Loss) |
| simdjson (ondemand) | 1082.13 | 2.28338 | 277.09ms | 94370 | 160 | 5.77018e+08 | 83168 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1587.98 | 1.16277 | 29.6228ms | 31235 | 80 | 3.80602e+06 | 18758.4 | 1(Win) |
| glaze | 1409.85 | 1.35711 | 7.86611ms | 31235 | 30 | 2.46656e+06 | 21128.5 | 2(Loss) |
| simdjson (ondemand) | 1293.06 | 0.732902 | 38.507ms | 31235 | 80 | 2.28048e+06 | 23036.8 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2033.42 | 2.16469 | 151.113ms | 213963 | 80 | 3.77491e+08 | 100349 | 1(Win) |
| glaze | 1621.39 | 3.15835 | 92.546ms | 213963 | 40 | 6.31951e+08 | 125850 | 2(Loss) |
| simdjson (ondemand) | 1424.96 | 4.3807 | 41.9571ms | 213963 | 30 | 1.18054e+09 | 143198 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1731.1 | 0.596232 | 1699.95ms | 9930848 | 30 | 3.19215e+10 | 5.47098e+06 | 1(Win) |
| simdjson (ondemand) | 1523.21 | 1.84601 | 1837.04ms | 9930848 | 30 | 3.95221e+11 | 6.21764e+06 | 2(Loss) |
| glaze | 1429.58 | 1.27223 | 40692ms | 9930848 | 320 | 2.27322e+12 | 6.62488e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1283.66 | 0.363446 | 25548.6ms | 1225964 | 1280 | 1.40263e+10 | 910809 | 1(Win) |
| glaze | 1107.94 | 1.58885 | 326.645ms | 1225964 | 30 | 8.43357e+09 | 1.05527e+06 | 2(Loss) |
| jsonifier | 869.039 | 1.09245 | 16681.3ms | 1225964 | 640 | 1.38248e+11 | 1.34536e+06 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 939.667 | 0.367069 | 11289.6ms | 785750 | 640 | 5.484e+09 | 797463 | 1(Win) |
| simdjson (ondemand) | 885.8 | 1.44417 | 672.913ms | 785750 | 40 | 5.97027e+09 | 845958 | 2(Loss) |
| jsonifier | 704.042 | 6.48231 | 325.306ms | 785750 | 30 | 1.42808e+11 | 1.06435e+06 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3700.37 | 0.463177 | 1363.87ms | 399947 | 640 | 1.45878e+08 | 103076 | 1(Win) |
| simdjson (ondemand) | 3525.04 | 0.698018 | 33.439ms | 399947 | 30 | 1.71132e+07 | 108203 | 2(Loss) |
| glaze | 2612.98 | 1.83767 | 44.202ms | 399947 | 30 | 2.15868e+08 | 145971 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1607.31 | 2.85585 | 70.8731ms | 399947 | 30 | 1.37784e+09 | 237303 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1582.05 | 0.55546 | 81.2191ms | 399947 | 30 | 5.38014e+07 | 241092 | 1(Tie) |
| glaze | 1449.67 | 2.71538 | 74.7999ms | 399947 | 30 | 1.53127e+09 | 263108 | 3(Loss) |
