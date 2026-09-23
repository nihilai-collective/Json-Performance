# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

Latest Results: (Sep 23, 2026)
#### Using the following commits:
----
| Jsonifier: [38630d2](https://github.com/nihilai-collective/jsonifier/commit/38630d2)  
| Glaze: [59af451](https://github.com/stephenberry/glaze/commit/59af451)  
| Simdjson: [6913ee1](https://github.com/simdjson/simdjson/commit/6913ee1)  

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
  This is the commit of BenchmarkSuite that was used to generate these results: [6160583](https://github.com/nihilai-collective/benchmarksuite/commit/6160583).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 885.694 | 0.313994 | 0.672083ms | 1811 | 30 | 1124.69 | 1950 | 1(Tie) |
| jsonifier STATISTICAL TIE | 851.727 | 2.41668 | 45.5553ms | 1811 | 30 | 72043.6 | 2027.77 | 1(Tie) |
| simdjson (ondemand) | 180.508 | 0.0389419 | 3.01842ms | 1811 | 30 | 416.483 | 9568 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 985.34 | 0.341099 | 0.557125ms | 1811 | 30 | 1072.37 | 1752.8 | 1(Win) |
| glaze | 763.551 | 0.386257 | 1.78392ms | 1798 | 40 | 3009.65 | 2245.7 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1564.05 | 0.159337 | 1.71317ms | 3873 | 40 | 566.356 | 2361.55 | 1(Win) |
| glaze | 1519.72 | 0.189093 | 0.750042ms | 3873 | 30 | 633.633 | 2430.43 | 2(Loss) |
| simdjson (ondemand) | 391.199 | 1.87036 | 2.88121ms | 3873 | 30 | 935560 | 9441.7 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4214.49 | 0.275373 | 0.332083ms | 3873 | 30 | 174.731 | 876.4 | 1(Win) |
| glaze | 2352.82 | 0.139878 | 2.97192ms | 3873 | 80 | 385.749 | 1569.85 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1631.85 | 0.252189 | 0.699792ms | 3862 | 30 | 971.931 | 2257 | 1(Win) |
| glaze | 1370.45 | 0.163138 | 0.833625ms | 3862 | 30 | 576.672 | 2687.5 | 2(Loss) |
| simdjson (ondemand) | 424.631 | 0.164424 | 2.78087ms | 3862 | 30 | 6101.76 | 8673.63 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4052.64 | 0.705793 | 1.5215ms | 3862 | 80 | 3291.5 | 908.812 | 1(Win) |
| glaze | 2227.25 | 0.376829 | 2.7115ms | 3862 | 80 | 3106.46 | 1653.65 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1807.49 | 1.37463 | 0.160458ms | 905 | 30 | 1292.53 | 477.5 | 1(Win) |
| jsonifier | 1557.43 | 1.203 | 0.228792ms | 905 | 30 | 1333.32 | 554.167 | 2(Loss) |
| simdjson (ondemand) | 183.307 | 0.402583 | 1.59229ms | 905 | 30 | 10778.9 | 4708.37 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2438.52 | 2.38745 | 0.161625ms | 905 | 30 | 2142.06 | 353.933 | 1(Win) |
| glaze | 1078.84 | 0.460041 | 0.358583ms | 905 | 30 | 406.345 | 800 | 2(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 4358.38 | 0.304057 | 0.697166ms | 9578 | 30 | 1218.23 | 2095.8 | 1(Win) |
| jsonifier | 4248.57 | 0.42321 | 0.827875ms | 9578 | 30 | 2483.69 | 2149.97 | 2(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3267.07 | 1.77221 | 600.84ms | 6661897 | 30 | 3.56312e+10 | 1.94464e+06 | 1(Win) |
| glaze | 2994.36 | 0.315681 | 7631.3ms | 6661897 | 160 | 7.17805e+09 | 2.12175e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1303.07 | 0.646875 | 9326.38ms | 500299 | 1280 | 7.18088e+09 | 366154 | 1(Win) |
| glaze | 1095.44 | 0.950427 | 734.83ms | 500299 | 80 | 1.37091e+09 | 435553 | 2(Loss) |
| simdjson (ondemand) | 677.556 | 0.869527 | 215.01ms | 500299 | 30 | 1.12475e+09 | 704182 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2229.76 | 1.78252 | 149.564ms | 500299 | 40 | 5.81928e+08 | 213979 | 1(Win) |
| glaze | 1540.22 | 1.32749 | 200.298ms | 500299 | 40 | 6.76414e+08 | 309775 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2705.35 | 0.135623 | 381.677ms | 1439562 | 40 | 1.8947e+07 | 507467 | 1(Win) |
| glaze | 1938.14 | 0.447823 | 19067.5ms | 1439562 | 1280 | 1.288e+10 | 708347 | 2(Loss) |
| simdjson (ondemand) | 1805.45 | 0.291454 | 247.836ms | 1439562 | 30 | 1.4735e+08 | 760404 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6042.17 | 0.474772 | 68.4801ms | 1439562 | 30 | 3.49113e+07 | 227215 | 1(Win) |
| glaze | 2383.28 | 1.42241 | 3522.67ms | 1439584 | 320 | 2.14845e+10 | 576053 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1292.43 | 3.52814 | 17.4017ms | 56369 | 30 | 6.46075e+07 | 41594.4 | 1(Win) |
| simdjson (ondemand) | 967.879 | 0.645495 | 16.9766ms | 56369 | 30 | 3.85608e+06 | 55541.7 | 2(Loss) |
| glaze | 605.957 | 0.58421 | 26.9456ms | 56369 | 30 | 8.05854e+06 | 88715.3 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2772.59 | 0.0486915 | 6.02354ms | 56369 | 30 | 2673.86 | 19389 | 1(Win) |
| glaze | 2420.95 | 0.870409 | 39.4443ms | 56369 | 80 | 2.98845e+06 | 22205.2 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1727.54 | 0.143237 | 6398.09ms | 94370 | 4890 | 2.72287e+07 | 52096.1 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1524.35 | 1.08394 | 18.1668ms | 94370 | 30 | 1.22864e+07 | 59040.2 | 2(Tie) |
| glaze STATISTICAL TIE | 1488.91 | 1.60644 | 18.2182ms | 94370 | 30 | 2.82866e+07 | 60445.7 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5297.49 | 0.0665412 | 5.33113ms | 94370 | 30 | 3833.8 | 16988.8 | 1(Win) |
| glaze | 2444.24 | 0.213245 | 976.983ms | 94370 | 1280 | 7.89131e+06 | 36820.6 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 932.159 | 1.74039 | 3.73771ms | 11812 | 30 | 1.32704e+06 | 12084.6 | 1(Win) |
| glaze | 798.614 | 1.74462 | 4.31846ms | 11812 | 30 | 1.81675e+06 | 14105.4 | 2(Loss) |
| simdjson (ondemand) | 698.654 | 1.17312 | 4.86879ms | 11812 | 30 | 1.07332e+06 | 16123.6 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2155.55 | 1.56402 | 3.39417ms | 11812 | 40 | 267225 | 5225.95 | 1(Win) |
| glaze | 1455.28 | 1.26783 | 6.90392ms | 11812 | 40 | 385244 | 7740.62 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1823.91 | 0.140816 | 5.41542ms | 31235 | 30 | 15867.3 | 16331.9 | 1(Win) |
| simdjson (ondemand) | 1742.21 | 0.0583136 | 12.6392ms | 31235 | 40 | 3976.34 | 17097.8 | 2(Loss) |
| glaze | 1675.88 | 0.55518 | 27.2509ms | 31235 | 80 | 779029 | 17774.5 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6170.1 | 0.0899888 | 1.54296ms | 31235 | 30 | 566.234 | 4827.8 | 1(Win) |
| glaze | 2536.34 | 1.12989 | 3.58588ms | 31235 | 30 | 528280 | 11744.5 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2075.3 | 1.01815 | 15.6308ms | 108313 | 30 | 7.7044e+06 | 49773.6 | 1(Win) |
| glaze | 1261.6 | 1.11748 | 25.1838ms | 108313 | 30 | 2.51141e+07 | 81876.4 | 2(Loss) |
| simdjson (ondemand) | 1003.19 | 0.602877 | 31.0473ms | 108313 | 30 | 1.15604e+07 | 102967 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2417.68 | 0.181892 | 13.051ms | 108313 | 30 | 181180 | 42724.9 | 1(Win) |
| glaze | 1683.86 | 1.10706 | 18.4247ms | 108313 | 30 | 1.3836e+07 | 61344.5 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2054.36 | 2.05969 | 710.379ms | 213963 | 320 | 1.3393e+09 | 99325.8 | 1(Tie) |
| glaze STATISTICAL TIE | 2039.06 | 0.216355 | 2631.49ms | 213963 | 1280 | 6.00016e+07 | 100071 | 1(Tie) |
| simdjson (ondemand) | 1688.08 | 3.05671 | 42.0453ms | 213963 | 30 | 4.09563e+08 | 120878 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5025.2 | 0.871397 | 12.5527ms | 213963 | 30 | 3.75598e+06 | 40605.5 | 1(Win) |
| glaze | 1959.75 | 1.61566 | 31.0516ms | 213963 | 30 | 8.48984e+07 | 104121 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 472.539 | 3.55738 | 2680.73ms | 1834197 | 40 | 6.93644e+11 | 3.70176e+06 | 1(Win) |
| glaze | 409.724 | 0.254492 | 3355.08ms | 1834197 | 40 | 4.72191e+09 | 4.26928e+06 | 2(Loss) |
| simdjson (ondemand) | 110.316 | 2.84118 | 4587.85ms | 1834197 | 30 | 6.08889e+12 | 1.58566e+07 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 802.641 | 0.177261 | 687.342ms | 1834197 | 30 | 4.4771e+08 | 2.17934e+06 | 1(Win) |
| glaze | 602.541 | 5.67915 | 864.485ms | 1833577 | 30 | 8.14918e+11 | 2.9021e+06 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 2136.73 | 2.11234 | 26250.6ms | 9930228 | 320 | 2.80477e+12 | 4.4321e+06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2076.82 | 3.77508 | 1499.46ms | 9930848 | 30 | 8.89095e+11 | 4.56024e+06 | 1(Tie) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 411.858 | 4.99291 | 1287.69ms | 1834197 | 30 | 1.34905e+12 | 4.24716e+06 | 1(Tie) |
| glaze STATISTICAL TIE | 387.306 | 1.4532 | 1449.55ms | 1834197 | 30 | 1.29228e+11 | 4.5164e+06 | 1(Tie) |
| simdjson (ondemand) | 265.65 | 5.03306 | 4694.31ms | 1834197 | 40 | 4.39337e+12 | 6.58471e+06 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1213.56 | 0.280397 | 1584.47ms | 642697 | 160 | 3.20891e+08 | 505062 | 1(Win) |
| glaze | 972.915 | 2.18131 | 4386.37ms | 642692 | 320 | 6.04286e+10 | 629982 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 805.479 | 0.638655 | 764.383ms | 409725 | 80 | 7.67891e+08 | 485108 | 1(Win) |
| jsonifier | 770.199 | 1.72872 | 487.919ms | 409725 | 40 | 3.07672e+09 | 507329 | 2(Loss) |
| simdjson (ondemand) | 722.117 | 0.550357 | 410.254ms | 409725 | 40 | 3.54747e+08 | 541109 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2495.73 | 1.20818 | 46.746ms | 409725 | 30 | 1.07344e+08 | 156565 | 1(Win) |
| glaze | 1633.43 | 2.66405 | 71.9744ms | 409725 | 30 | 1.21839e+09 | 239217 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1370.09 | 0.935112 | 170.841ms | 785750 | 30 | 7.84724e+08 | 546933 | 1(Win) |
| simdjson (ondemand) | 1264.61 | 1.16364 | 178.873ms | 785750 | 30 | 1.42633e+09 | 592556 | 2(Loss) |
| jsonifier | 1007.73 | 2.82398 | 217.538ms | 785750 | 30 | 1.3229e+10 | 743603 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4282.37 | 0.678129 | 52.3401ms | 785750 | 30 | 4.22422e+07 | 174985 | 1(Win) |
| glaze | 2293.7 | 0.15708 | 18965.5ms | 785750 | 2560 | 6.74181e+08 | 326700 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3664.74 | 1.17024 | 21.5327ms | 264040 | 30 | 1.93965e+07 | 68711.1 | 1(Win) |
| simdjson (ondemand) | 3326.76 | 0.459046 | 22.9453ms | 264040 | 30 | 3.62185e+06 | 75691.7 | 2(Loss) |
| glaze | 2116.5 | 0.252297 | 35.9312ms | 264040 | 30 | 2.70302e+06 | 118974 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4566.38 | 0.353297 | 25.4565ms | 399947 | 30 | 2.61254e+06 | 83527.7 | 1(Win) |
| simdjson (ondemand) | 3691.16 | 1.01412 | 34.457ms | 399947 | 30 | 3.29442e+07 | 103333 | 2(Loss) |
| glaze | 2525.93 | 1.31128 | 46.4421ms | 399947 | 30 | 1.17617e+08 | 151001 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1014.34 | 3.32677 | 765.546ms | 264040 | 160 | 1.0913e+10 | 248249 | 1(Win) |
| glaze STATISTICAL TIE | 925.572 | 1.46598 | 3284.93ms | 264040 | 640 | 1.01802e+10 | 272057 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 918.794 | 4.84119 | 85.3379ms | 264040 | 30 | 5.28117e+09 | 274064 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3002.33 | 3.71584 | 265.237ms | 264040 | 160 | 1.55402e+09 | 83870.8 | 1(Win) |
| glaze | 2390.77 | 1.3264 | 2804.62ms | 263923 | 1280 | 2.49595e+09 | 105278 | 2(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6286.38 | 3.62658 | 43.6858ms | 399947 | 40 | 1.93668e+08 | 60673.9 | 1(Win) |
| glaze | 3289.85 | 3.06752 | 35.0872ms | 399830 | 30 | 3.79222e+08 | 115904 | 2(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1969.06 | 0.643792 | 2528.48ms | 699405 | 320 | 1.52188e+09 | 338743 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1956.75 | 4.81283 | 496.833ms | 699405 | 80 | 2.15316e+10 | 340873 | 1(Tie) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2207.33 | 0.404758 | 3357.47ms | 631514 | 640 | 7.8055e+08 | 272844 | 1(Win) |
| glaze | 1629.48 | 1.27629 | 111.491ms | 631514 | 30 | 6.67555e+08 | 369601 | 2(Loss) |
