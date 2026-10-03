# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [f5d1ca8](https://github.com/nihilai-collective/jsonifier/commit/f5d1ca8)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| simdjson (reflection) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX2` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10% AND mean shift < 5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

Every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. Parser instances are reused.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` is simdjson 5's C++26 static-reflection API (`document.get<T>()` for reads, `simdjson::to_json` into a `std::string` for writes). Its single-pass writer emits minified JSON only (pretty output is a second FracturedJson reformatting pass), so it is absent from the prettified write tests.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1095.22 | 0.518321 | 930.803ms | 905 | 80 | 1334.69 | 788.038 | 2.03213 | 1(Win) |
| glaze | 680.247 | 0.357301 | 989.001ms | 905 | 30 | 616.53 | 1268.77 | 3.33171 | 2(Loss) |
| simdjson (ondemand) | 91.4202 | 2.95433 | 1745.65ms | 905 | 40 | 3.11165e+06 | 9440.75 | 25.4096 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1142.99 | 0.332634 | 915.932ms | 905 | 40 | 252.349 | 755.1 | 1.94785 | 1(Win) |
| simdjson (reflection) | 180.8 | 0.0601004 | 1308.9ms | 905 | 30 | 246.93 | 4773.63 | 12.7978 | 2(Loss) |
| glaze | 99.6381 | 1.66128 | 1654.13ms | 905 | 4890 | 1.01261e+08 | 8662.1 | 23.3077 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 699.53 | 0.229587 | 1096.34ms | 1811 | 160 | 5140.9 | 2468.95 | 3.28476 | 1(Win) |
| glaze | 520.076 | 0.174201 | 1175.46ms | 1811 | 30 | 1003.98 | 3320.87 | 4.4346 | 2(Loss) |
| simdjson (ondemand) | 111.689 | 1.01987 | 2324.18ms | 1811 | 1280 | 3.18357e+07 | 15463.5 | 20.8299 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 174.409 | 1.07357 | 1897.32ms | 1997 | 4890 | 6.72025e+07 | 10919.7 | 13.2991 | 1(Win) |
| jsonifier | 167.156 | 0.0857465 | 1898.73ms | 1811 | 30 | 2354.75 | 10332.3 | 13.8992 | 2(Loss) |
| glaze | 140.592 | 0.0589751 | 2131.17ms | 1798 | 40 | 2069.45 | 12196.3 | 16.5351 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1708.68 | 0.114754 | 1054.91ms | 3862 | 160 | 978.943 | 2155.52 | 1.34153 | 1(Win) |
| glaze | 1006.4 | 0.468204 | 1198.42ms | 3862 | 2560 | 751614 | 3659.68 | 2.2946 | 2(Loss) |
| simdjson (ondemand) | 299.266 | 0.164525 | 2089.28ms | 3862 | 30 | 12299.7 | 12307.1 | 7.76935 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 438.14 | 0.113247 | 1674.17ms | 3862 | 30 | 2718.79 | 8406.2 | 5.2988 | 1(Win) |
| glaze | 433.203 | 0.295119 | 1693.59ms | 3862 | 80 | 50364.7 | 8501.99 | 5.36032 | 2(Loss) |
| simdjson (reflection) | 288.958 | 0.109578 | 2135.01ms | 3862 | 30 | 5852.23 | 12746.1 | 8.04865 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 841.884 | 0.0950904 | 1986.11ms | 9578 | 40 | 4257.74 | 10849.8 | 2.75983 | 1(Win) |
| glaze | 682.079 | 0.605022 | 2127.76ms | 9578 | 4890 | 3.2102e+07 | 13391.8 | 3.40794 | 2(Loss) |
| simdjson (ondemand) | 495.377 | 0.402314 | 2636.01ms | 9578 | 4890 | 2.69103e+07 | 18439.1 | 4.69697 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1224.65 | 0.100564 | 1608.7ms | 9578 | 30 | 1687.82 | 7458.67 | 1.89476 | 1(Win) |
| glaze | 1056.54 | 0.165004 | 1711.71ms | 9578 | 40 | 8140 | 8645.48 | 2.19773 | 2(Loss) |
| simdjson (reflection) | 696.6 | 0.889995 | 2098ms | 9578 | 2560 | 3.48657e+07 | 13112.7 | 3.33834 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1640.4 | 0.236263 | 1058.13ms | 3873 | 30 | 848.999 | 2251.63 | 1.39865 | 1(Win) |
| glaze | 1205.43 | 0.173883 | 1142.91ms | 3873 | 40 | 1135.5 | 3064.12 | 1.91198 | 2(Loss) |
| simdjson (ondemand) | 292.652 | 0.661534 | 2060.2ms | 3873 | 4890 | 3.40883e+07 | 12621.1 | 7.93936 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 448.505 | 0.0912487 | 1672.82ms | 3873 | 80 | 4517.56 | 8235.31 | 5.17603 | 1(Win) |
| glaze | 421.295 | 0.274313 | 1728.05ms | 3873 | 80 | 46270.4 | 8767.2 | 5.51233 | 2(Loss) |
| simdjson (reflection) | 294.144 | 0.0646157 | 2103.84ms | 3873 | 30 | 1975.03 | 12557.1 | 7.90559 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 481.114 | 0.0859321 | 6251.38ms | 2090234 | 40 | 5.07066e+08 | 4.14331e+06 | 4.84719 | 1(Win) |
| simdjson (ondemand) | 359.683 | 0.0695919 | 8334.32ms | 2090234 | 80 | 1.19003e+09 | 5.5421e+06 | 6.48363 | 2(Loss) |
| glaze | 351.18 | 0.0658588 | 8521.53ms | 2090234 | 80 | 1.11802e+09 | 5.6763e+06 | 6.64062 | 3(Loss) |
| simdjson (reflection) | 343.4 | 0.0768063 | 8780.57ms | 2090234 | 80 | 1.59028e+09 | 5.8049e+06 | 6.79108 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1126.17 | 0.0641522 | 5533.41ms | 2090234 | 40 | 5.15783e+07 | 1.77008e+06 | 2.07075 | 1(Win) |
| glaze | 747.902 | 0.0697784 | 8314.42ms | 2090234 | 80 | 2.76714e+08 | 2.66533e+06 | 3.11808 | 2(Loss) |
| simdjson (reflection) | 433.103 | 0.103301 | 6900.44ms | 2090326 | 30 | 6.78233e+08 | 4.60281e+06 | 5.38448 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1239.73 | 0.121 | 7721.74ms | 6661897 | 80 | 3.07613e+09 | 5.12473e+06 | 1.88109 | 1(Win) |
| simdjson (ondemand) | 1061.38 | 0.107415 | 8978.41ms | 6661897 | 80 | 3.30735e+09 | 5.98589e+06 | 2.19718 | 2(Loss) |
| simdjson (reflection) | 1017.3 | 0.119957 | 9456.99ms | 6661897 | 30 | 1.68374e+09 | 6.24527e+06 | 2.29238 | 3(Loss) |
| glaze | 877.116 | 0.149475 | 5082.46ms | 6661897 | 30 | 3.51672e+09 | 7.24338e+06 | 2.65878 | 4(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3261.6 | 0.106419 | 6078.19ms | 6661897 | 160 | 6.87535e+08 | 1.9479e+06 | 0.714987 | 1(Win) |
| glaze | 1165.86 | 0.0962418 | 8210.46ms | 6661897 | 40 | 1.10026e+09 | 5.44946e+06 | 2.00027 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 989.699 | 0.0927188 | 6219.43ms | 500299 | 640 | 1.2787e+08 | 482088 | 2.3559 | 1(Win) |
| glaze | 934.415 | 0.103696 | 6576.09ms | 500299 | 640 | 1.79425e+08 | 510611 | 2.49541 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 650.011 | 0.242685 | 9482.42ms | 500299 | 40 | 1.2693e+08 | 734022 | 3.58736 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 647.106 | 0.0690519 | 9543.31ms | 500299 | 640 | 1.65897e+08 | 737317 | 3.60352 | 3(Tie) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4956.39 | 0.235484 | 5292.63ms | 500299 | 1280 | 6.57751e+07 | 96264.2 | 0.470244 | 1(Win) |
| simdjson (reflection) | 3078.64 | 0.113655 | 8374.13ms | 500299 | 2560 | 7.94251e+07 | 154978 | 0.757207 | 2(Loss) |
| glaze | 1972.03 | 0.102936 | 6398.54ms | 500299 | 1280 | 7.93916e+07 | 241944 | 1.18229 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1959.89 | 0.11862 | 9012.16ms | 1439562 | 320 | 2.20936e+08 | 700485 | 1.18975 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1643.64 | 0.290015 | 5318.98ms | 1439562 | 30 | 1.7604e+08 | 835266 | 1.41873 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1633.09 | 0.135139 | 5325.36ms | 1439562 | 160 | 2.06502e+08 | 840662 | 1.42785 | 2(Tie) |
| glaze | 1483.3 | 0.146684 | 5880.79ms | 1439562 | 320 | 5.89818e+08 | 925552 | 1.57208 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11137.4 | 0.124586 | 6770.16ms | 1439562 | 2560 | 6.03765e+07 | 123267 | 0.209289 | 1(Win) |
| glaze | 1521.79 | 0.175881 | 5707.61ms | 1439584 | 40 | 1.00708e+08 | 902158 | 1.53236 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1019.86 | 0.277562 | 6053.53ms | 56369 | 2560 | 5.47978e+07 | 52711 | 2.28465 | 1(Win) |
| glaze | 918.382 | 0.217113 | 6656.31ms | 56369 | 2560 | 4.13472e+07 | 58535.2 | 2.53714 | 2(Loss) |
| simdjson (reflection) | 718.894 | 0.187911 | 8303.05ms | 56369 | 2560 | 5.05467e+07 | 74778.3 | 3.24161 | 3(Loss) |
| simdjson (ondemand) | 700.332 | 0.137615 | 8498.22ms | 56369 | 4890 | 5.45648e+07 | 76760.2 | 3.32741 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5355.8 | 0.26898 | 1871.56ms | 56369 | 40 | 29156.2 | 10037.3 | 0.433951 | 1(Win) |
| glaze | 1826.03 | 0.521081 | 3744.8ms | 56369 | 1280 | 3.01223e+07 | 29439.7 | 1.27538 | 2(Loss) |
| simdjson (reflection) | 1356.18 | 0.223473 | 4769.9ms | 56369 | 4890 | 3.83716e+07 | 39639.2 | 1.71785 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1320.16 | 0.168513 | 7634.99ms | 94370 | 4890 | 6.45347e+07 | 68172.4 | 1.76484 | 1(Win) |
| glaze | 1244.53 | 0.154293 | 8027.01ms | 94370 | 4890 | 6.0878e+07 | 72315.2 | 1.87224 | 2(Loss) |
| simdjson (reflection) | 1135.28 | 0.17864 | 8782.95ms | 94370 | 2560 | 5.13398e+07 | 79273.7 | 2.05274 | 3(Loss) |
| simdjson (ondemand) | 1109.83 | 0.152335 | 8920.67ms | 94370 | 4890 | 7.46219e+07 | 81092 | 2.09967 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8237.84 | 0.16468 | 1965.62ms | 94370 | 40 | 12947.4 | 10925 | 0.282125 | 1(Win) |
| glaze | 1279.27 | 0.140402 | 7841.19ms | 94370 | 4890 | 4.77092e+07 | 70351.4 | 1.82184 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 892.687 | 0.62714 | 2064.39ms | 11812 | 4890 | 3.06258e+07 | 12619 | 2.60483 | 1(Win) |
| jsonifier | 805.918 | 0.618049 | 2191.16ms | 11812 | 4890 | 3.64939e+07 | 13977.6 | 2.88591 | 2(Loss) |
| simdjson (reflection) | 510.015 | 0.544865 | 2988.6ms | 11812 | 2560 | 3.70764e+07 | 22087.2 | 4.56468 | 3(Loss) |
| simdjson (ondemand) | 483.94 | 0.0848575 | 3249.27ms | 11812 | 40 | 15606.4 | 23277.2 | 4.81174 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4078.27 | 0.190739 | 1121.64ms | 11812 | 40 | 1110.28 | 2762.15 | 0.56464 | 1(Win) |
| simdjson (reflection) | 3120.25 | 0.347718 | 1217.25ms | 11812 | 80 | 12607 | 3610.22 | 0.739567 | 2(Loss) |
| glaze | 1386.21 | 0.269092 | 1674.63ms | 11812 | 40 | 19127.3 | 8126.35 | 1.67473 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1769.66 | 0.950943 | 2494.13ms | 31235 | 1280 | 3.27961e+07 | 16832.6 | 1.31456 | 1(Win) |
| glaze | 1340.67 | 0.724661 | 3015.08ms | 31235 | 1280 | 3.3183e+07 | 22218.7 | 1.73653 | 2(Loss) |
| simdjson (reflection) | 1268.07 | 0.986401 | 3169.7ms | 31235 | 320 | 1.71813e+07 | 23490.9 | 1.83622 | 3(Loss) |
| simdjson (ondemand) | 1139.22 | 0.417537 | 3399.63ms | 31235 | 4890 | 5.82867e+07 | 26147.8 | 2.04376 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9013.66 | 0.130858 | 1183.66ms | 31235 | 160 | 2992.26 | 3304.76 | 0.255814 | 1(Win) |
| glaze | 1294.96 | 0.339312 | 3091.32ms | 31235 | 4890 | 2.97906e+07 | 23003.1 | 1.7979 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1286.89 | 0.139837 | 8818.95ms | 108313 | 4890 | 6.16077e+07 | 80267.6 | 1.81101 | 1(Win) |
| glaze | 964.409 | 0.172012 | 5872.49ms | 108313 | 2560 | 8.68954e+07 | 107107 | 2.41685 | 2(Loss) |
| simdjson (reflection) | 763.849 | 0.126679 | 7403.24ms | 108313 | 2560 | 7.5127e+07 | 135230 | 3.05166 | 3(Loss) |
| simdjson (ondemand) | 691.789 | 0.159279 | 8120.15ms | 108313 | 1280 | 7.24001e+07 | 149316 | 3.36979 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8305.53 | 0.108625 | 2116.73ms | 108313 | 30 | 5475.31 | 12436.9 | 0.279925 | 1(Win) |
| simdjson (reflection) | 4595.19 | 0.490898 | 3090.73ms | 108313 | 2560 | 3.11728e+07 | 22479 | 0.506026 | 2(Loss) |
| glaze | 1673.16 | 0.200399 | 6980.03ms | 108313 | 2560 | 3.9185e+07 | 61736.8 | 1.39253 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1525.8 | 0.246548 | 7280.54ms | 213963 | 640 | 6.95766e+07 | 133733 | 1.5273 | 1(Win) |
| simdjson (reflection) | 1409.58 | 0.176435 | 7839.74ms | 213963 | 1280 | 8.34979e+07 | 144760 | 1.65379 | 2(Loss) |
| glaze | 1370.19 | 0.204477 | 8058.74ms | 213963 | 1280 | 1.18691e+08 | 148922 | 1.70124 | 3(Loss) |
| simdjson (ondemand) | 1280.4 | 0.306476 | 8612.22ms | 213963 | 320 | 7.63357e+07 | 159365 | 1.8207 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11961.9 | 0.214025 | 2586.08ms | 213963 | 40 | 53317.2 | 17058.5 | 0.194494 | 1(Win) |
| glaze | 1229.6 | 0.103116 | 8903.76ms | 213963 | 2560 | 7.49615e+07 | 165949 | 1.89587 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 447.088 | 0.130223 | 5908.48ms | 1834197 | 30 | 7.78763e+08 | 3.91249e+06 | 5.21603 | 1(Win) |
| glaze | 334.004 | 0.0757898 | 7848.19ms | 1834197 | 80 | 1.26037e+09 | 5.23714e+06 | 6.98207 | 2(Loss) |
| simdjson (ondemand) | 304.719 | 0.080187 | 8641.14ms | 1834197 | 80 | 1.69509e+09 | 5.74047e+06 | 7.65313 | 3(Loss) |
| simdjson (reflection) | 292.524 | 0.0608235 | 9006.6ms | 1834197 | 40 | 5.29143e+08 | 5.97978e+06 | 7.97222 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 713.644 | 0.0525146 | 7620.17ms | 1834197 | 160 | 2.651e+08 | 2.45112e+06 | 3.26775 | 1(Win) |
| glaze | 363.188 | 0.0728929 | 7246.45ms | 1833577 | 30 | 3.6951e+08 | 4.81468e+06 | 6.42104 | 2(Loss) |
| simdjson (reflection) | 292.656 | 0.0344365 | 9417.22ms | 1922245 | 80 | 3.72246e+08 | 6.26399e+06 | 7.96859 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1705.8 | 0.0913574 | 8331.97ms | 9930848 | 80 | 2.05824e+09 | 5.55212e+06 | 1.36712 | 1(Win) |
| simdjson (ondemand) | 1454.9 | 0.068861 | 9789.19ms | 9930848 | 40 | 8.03732e+08 | 6.50957e+06 | 1.60288 | 2(Loss) |
| simdjson (reflection) | 1400.55 | 0.156683 | 10157.7ms | 9930848 | 30 | 3.36772e+09 | 6.76217e+06 | 1.66509 | 3(Loss) |
| glaze | 1308.27 | 0.104989 | 5064.27ms | 9930848 | 40 | 2.31061e+09 | 7.23915e+06 | 1.78254 | 4(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3592.67 | 0.171303 | 8171.76ms | 9930848 | 40 | 8.15694e+08 | 2.63614e+06 | 0.649102 | 1(Win) |
| glaze | 1047.7 | 0.0419997 | 6349.13ms | 9930228 | 30 | 4.32369e+08 | 9.03901e+06 | 2.22588 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 449.921 | 0.0778924 | 5870.73ms | 1834197 | 80 | 7.33669e+08 | 3.88786e+06 | 5.18314 | 1(Win) |
| glaze | 332.016 | 0.0580678 | 7932.19ms | 1834197 | 80 | 7.48746e+08 | 5.2685e+06 | 7.02387 | 2(Loss) |
| simdjson (ondemand) | 300.872 | 0.0529184 | 8744.73ms | 1834197 | 80 | 7.57239e+08 | 5.81386e+06 | 7.75094 | 3(Loss) |
| simdjson (reflection) | 291.166 | 0.0723278 | 9021.46ms | 1834197 | 40 | 7.55232e+08 | 6.00766e+06 | 8.00932 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 718.253 | 0.0840712 | 7568.39ms | 1834197 | 30 | 1.25763e+08 | 2.43539e+06 | 3.24675 | 1(Win) |
| glaze | 358.6 | 0.0492136 | 7317.25ms | 1833577 | 40 | 2.3036e+08 | 4.87628e+06 | 6.50319 | 2(Loss) |
| simdjson (reflection) | 292.292 | 0.0730448 | 9437.64ms | 1922245 | 80 | 1.67901e+09 | 6.27179e+06 | 7.97847 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1688.77 | 0.127503 | 8445.84ms | 9930848 | 30 | 1.53389e+09 | 5.60811e+06 | 1.38089 | 1(Win) |
| simdjson (ondemand) | 1444.78 | 0.0935967 | 9902.37ms | 9930848 | 40 | 1.50573e+09 | 6.55516e+06 | 1.61409 | 2(Loss) |
| simdjson (reflection) | 1408.17 | 0.104915 | 10111.6ms | 9930848 | 80 | 3.98312e+09 | 6.72559e+06 | 1.65604 | 3(Loss) |
| glaze | 1271.35 | 0.193395 | 5200.53ms | 9930848 | 30 | 6.22664e+09 | 7.4494e+06 | 1.83424 | 4(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3594.77 | 0.156704 | 8167.77ms | 9930848 | 40 | 6.81788e+08 | 2.6346e+06 | 0.648706 | 1(Win) |
| glaze | 980.627 | 0.162791 | 6835.35ms | 9930228 | 40 | 9.88629e+09 | 9.65729e+06 | 2.37803 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 638.563 | 0.113294 | 6194.87ms | 642697 | 40 | 4.73019e+07 | 959849 | 3.65185 | 1(Win) |
| glaze | 618.353 | 0.0558898 | 6313.79ms | 642697 | 320 | 9.82099e+07 | 991220 | 3.7712 | 2(Loss) |
| simdjson (reflection) | 599.466 | 0.0648121 | 6529.91ms | 642697 | 320 | 1.40523e+08 | 1.02245e+06 | 3.89004 | 3(Loss) |
| simdjson (ondemand) | 583.652 | 0.146555 | 6651.93ms | 642697 | 40 | 9.47467e+07 | 1.05015e+06 | 3.99536 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1200.62 | 0.149172 | 6587.1ms | 642697 | 320 | 1.85576e+08 | 510505 | 1.9422 | 1(Win) |
| glaze | 634.848 | 0.0642761 | 6176.58ms | 642692 | 160 | 6.16149e+07 | 965458 | 3.67325 | 2(Loss) |
| simdjson (reflection) | 450.837 | 0.0762992 | 8616.27ms | 643373 | 160 | 1.72523e+08 | 1.36096e+06 | 5.17243 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 989.393 | 0.0640376 | 7492.94ms | 1225964 | 320 | 1.83248e+08 | 1.1817e+06 | 2.35693 | 1(Win) |
| simdjson (ondemand) | 970.304 | 0.118386 | 7628.1ms | 1225964 | 160 | 3.25581e+08 | 1.20495e+06 | 2.40328 | 2(Loss) |
| jsonifier | 934.943 | 0.0780013 | 7976.14ms | 1225964 | 160 | 1.52233e+08 | 1.25053e+06 | 2.49423 | 3(Loss) |
| glaze | 908.225 | 0.143376 | 8160.62ms | 1225964 | 40 | 1.36263e+08 | 1.28731e+06 | 2.56762 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2359.48 | 0.0813757 | 6414.64ms | 1225964 | 640 | 1.04062e+08 | 495521 | 0.98829 | 1(Win) |
| glaze | 1044.9 | 0.0585541 | 7107.03ms | 1225970 | 320 | 1.37364e+08 | 1.11893e+06 | 2.23175 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 678.314 | 0.0747511 | 7442.72ms | 409725 | 640 | 1.18669e+08 | 576052 | 3.43777 | 1(Win) |
| glaze | 589.373 | 0.215885 | 8575.86ms | 409725 | 320 | 6.55538e+08 | 662983 | 3.9565 | 2(Loss) |
| simdjson (ondemand) | 557.444 | 0.0782018 | 8994.97ms | 409725 | 640 | 1.92307e+08 | 700957 | 4.18315 | 3(Loss) |
| simdjson (reflection) | 524.411 | 0.140982 | 9572.97ms | 409725 | 160 | 1.76558e+08 | 745110 | 4.44667 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2724.02 | 0.213885 | 7707.74ms | 409725 | 640 | 6.02429e+07 | 143444 | 0.855791 | 1(Win) |
| simdjson (reflection) | 1522.88 | 0.300501 | 6705.77ms | 409725 | 160 | 9.51191e+07 | 256583 | 1.53094 | 2(Loss) |
| glaze | 1363.75 | 0.125058 | 7536.84ms | 409725 | 640 | 8.2172e+07 | 286523 | 1.70974 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1040.92 | 0.1864 | 9296.52ms | 785750 | 40 | 7.20257e+07 | 719891 | 2.24024 | 1(Win) |
| simdjson (ondemand) | 1017.95 | 0.125058 | 9511.24ms | 785750 | 160 | 1.356e+08 | 736133 | 2.29079 | 2(Loss) |
| simdjson (reflection) | 956.068 | 0.200519 | 5006.25ms | 785750 | 30 | 7.41012e+07 | 783783 | 2.43909 | 3(Loss) |
| glaze | 921.83 | 0.161254 | 5168.06ms | 785750 | 160 | 2.74923e+08 | 812893 | 2.52963 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4871.97 | 0.120586 | 8328.32ms | 785750 | 2560 | 8.8063e+07 | 153808 | 0.478522 | 1(Win) |
| glaze | 1094.54 | 0.0850884 | 8781.75ms | 785750 | 320 | 1.08591e+08 | 684624 | 2.13045 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2629.8 | 0.279849 | 5339.66ms | 264040 | 640 | 4.59541e+07 | 95752 | 0.886248 | 1(Win) |
| jsonifier STATISTICAL TIE | 2529.57 | 0.176896 | 5512.03ms | 264040 | 2560 | 7.93821e+07 | 99545.7 | 0.921337 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2524.96 | 0.160043 | 5532.32ms | 264040 | 2560 | 6.5215e+07 | 99727.8 | 0.922982 | 2(Tie) |
| glaze | 1271.97 | 0.124541 | 5272.74ms | 264040 | 1280 | 7.78065e+07 | 197966 | 1.83295 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3408.76 | 0.143919 | 6151.51ms | 399947 | 2560 | 6.63883e+07 | 111894 | 0.683707 | 1(Win) |
| simdjson (reflection) | 3298.17 | 0.143232 | 6351.92ms | 399947 | 2560 | 7.02393e+07 | 115646 | 0.706663 | 2(Loss) |
| jsonifier | 3263.79 | 0.363773 | 6388.19ms | 399947 | 640 | 1.15665e+08 | 116864 | 0.714034 | 3(Loss) |
| glaze | 1552.26 | 0.119218 | 6477.41ms | 399947 | 1280 | 1.09842e+08 | 245719 | 1.50196 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 885.036 | 0.132883 | 7478.43ms | 264040 | 1280 | 1.82966e+08 | 284517 | 2.63411 | 1(Win) |
| glaze | 829.543 | 0.157421 | 7920.3ms | 264040 | 1280 | 2.92279e+08 | 303550 | 2.81067 | 2(Loss) |
| simdjson (reflection) | 774.891 | 0.123867 | 8508.37ms | 264040 | 1280 | 2.07386e+08 | 324960 | 3.00894 | 3(Loss) |
| simdjson (ondemand) | 651.875 | 0.138419 | 5019.17ms | 264040 | 640 | 1.82971e+08 | 386283 | 3.57685 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4817.47 | 0.382976 | 6113.74ms | 264040 | 1280 | 5.12926e+07 | 52269.8 | 0.483665 | 1(Win) |
| simdjson (reflection) | 3618.9 | 0.155705 | 7827.32ms | 264040 | 4890 | 5.73985e+07 | 69581.4 | 0.643781 | 2(Loss) |
| glaze | 2589.63 | 0.150116 | 5399.97ms | 263923 | 2560 | 5.44973e+07 | 97194 | 0.900031 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 1089.62 | 0.326237 | 8958.95ms | 399947 | 80 | 1.0433e+08 | 350047 | 2.13989 | 1(Win) |
| glaze | 1023.1 | 0.115175 | 9726.86ms | 399947 | 1280 | 2.35991e+08 | 372806 | 2.27894 | 2(Loss) |
| simdjson (ondemand) | 946.245 | 0.185748 | 5267.1ms | 399947 | 320 | 1.79389e+08 | 403087 | 2.46411 | 3(Loss) |
| jsonifier | 904.637 | 0.50998 | 5409.91ms | 399947 | 80 | 3.69872e+08 | 421627 | 2.577 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6677.45 | 0.173815 | 6596.58ms | 399947 | 4890 | 4.82021e+07 | 57120.4 | 0.348948 | 1(Win) |
| glaze | 1632.37 | 0.299921 | 6240.7ms | 399830 | 160 | 7.85316e+07 | 233591 | 1.42833 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1374.96 | 0.415106 | 8413.65ms | 466906 | 30 | 5.42146e+07 | 323846 | 1.69588 | 1(Win) |
| glaze | 1276.79 | 0.0916634 | 9034.4ms | 466906 | 1280 | 1.30805e+08 | 348748 | 1.82629 | 2(Loss) |
| simdjson (ondemand) | 558.073 | 0.076604 | 5096.88ms | 466906 | 320 | 1.19545e+08 | 797882 | 4.17837 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1989.65 | 0.172753 | 8781.86ms | 699405 | 640 | 2.14651e+08 | 335237 | 1.17194 | 1(Win) |
| glaze | 1219.65 | 0.09589 | 7073.15ms | 699405 | 320 | 8.79997e+07 | 546881 | 1.91193 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2347.77 | 0.138186 | 6760.23ms | 631514 | 640 | 8.04194e+07 | 256524 | 0.993143 | 1(Win) |
| glaze | 1431.82 | 0.104447 | 5452.72ms | 631514 | 640 | 1.23527e+08 | 420624 | 1.62854 | 2(Loss) |
