# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [f5d1ca8](https://github.com/nihilai-collective/jsonifier/commit/f5d1ca8)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX512BW` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Xeon(R) 6973P-C-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

Every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. Parser instances are reused.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

`simdjson (ondemand)` extracts each field with an individual `find_field` lookup (`find_field_unordered` for the reverse-order tests) on MSVC/Windows, rather than the `object::for_each` API used on the other platforms, because instantiating `for_each` across these test structures drives MSVC compile times to intractable levels.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 418.714 | 0.27957 | 218.702ms | 905 | 80 | 2656.65 | 2061.25 | 5.83014 | 1(Win) |
| glaze | 256.581 | 0.18505 | 354.993ms | 905 | 80 | 3099.68 | 3363.75 | 9.59472 | 2(Loss) |
| simdjson (ondemand) | 85.1789 | 0.0893103 | 1078.49ms | 905 | 40 | 3275.64 | 10132.5 | 29.0285 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 938.125 | 0.797608 | 96.9401ms | 905 | 40 | 2153.85 | 920 | 2.5584 | 1(Win) |
| glaze | 16.0672 | 1.28764 | 1277.41ms | 905 | 30 | 1.43525e+07 | 53716.7 | 154.226 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 587.45 | 0.349774 | 316.043ms | 1811 | 30 | 3172.41 | 2940 | 4.17964 | 1(Win) |
| glaze | 246.143 | 0.119987 | 663.468ms | 1811 | 30 | 2126.44 | 7016.67 | 10.0288 | 2(Loss) |
| simdjson (ondemand) | 131.551 | 1.73544 | 1339.08ms | 1811 | 80 | 4.15296e+06 | 13128.8 | 18.8071 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 173.535 | 0.0978597 | 1041.62ms | 1811 | 80 | 7588.61 | 9952.5 | 14.235 | 1(Win) |
| glaze | 118.516 | 0.794321 | 1457.89ms | 1798 | 1280 | 1.69056e+07 | 14468.2 | 20.8733 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1793.71 | 0.508018 | 216.728ms | 3862 | 30 | 3264.37 | 2053.33 | 1.3661 | 1(Win) |
| glaze | 719.09 | 0.0842255 | 531.5ms | 3862 | 160 | 2977.59 | 5121.88 | 3.42833 | 2(Loss) |
| simdjson (ondemand) | 303.635 | 0.0593906 | 1302.25ms | 3862 | 80 | 4151.9 | 12130 | 8.15005 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 420.204 | 0.198242 | 902.584ms | 3862 | 40 | 12076.9 | 8765 | 5.87989 | 1(Win) |
| glaze | 285.278 | 0.492125 | 1273.72ms | 3862 | 2560 | 1.03342e+07 | 12910.5 | 8.66843 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 872.582 | 0.733998 | 1069.41ms | 9578 | 320 | 1.8892e+06 | 10468.1 | 2.83146 | 1(Win) |
| glaze | 649.341 | 0.213297 | 1417.8ms | 9578 | 4890 | 4.40233e+06 | 14067 | 3.80941 | 2(Loss) |
| simdjson (ondemand) | 481.576 | 0.158376 | 1929.89ms | 9578 | 40 | 36096.2 | 18967.5 | 5.13789 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1115.92 | 0.670169 | 842.796ms | 9578 | 640 | 1.92591e+06 | 8185.47 | 2.21291 | 1(Win) |
| glaze | 746.672 | 0.215859 | 1285.24ms | 9578 | 30 | 20919.5 | 12233.3 | 3.30919 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1772.56 | 0.413356 | 215.593ms | 3873 | 80 | 5935.13 | 2083.75 | 1.38153 | 1(Win) |
| glaze | 744.556 | 1.13418 | 477.959ms | 3873 | 640 | 2.02602e+06 | 4960.78 | 3.31087 | 2(Loss) |
| simdjson (ondemand) | 311.432 | 0.0956676 | 1191.7ms | 3873 | 30 | 3862.07 | 11860 | 7.94807 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 431.829 | 0.255243 | 894.915ms | 3873 | 30 | 14298.9 | 8553.33 | 5.72805 | 1(Win) |
| glaze | 300.432 | 0.276408 | 1227.99ms | 3873 | 2560 | 2.95627e+06 | 12294.2 | 8.22974 | 2(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 818.559 | 0.18368 | 7574.21ms | 2090234 | 80 | 1.60069e+09 | 2.43526e+06 | 3.02819 | 1(Win) |
| glaze | 630.887 | 0.07804 | 9954.76ms | 2090234 | 160 | 9.72837e+08 | 3.15968e+06 | 3.92933 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1290.16 | 1.65817 | 7339.39ms | 6661897 | 40 | 2.66702e+11 | 4.9244e+06 | 1.92155 | 1(Win) |
| simdjson (ondemand) | 922.747 | 0.94666 | 5050.97ms | 6661897 | 30 | 1.2745e+11 | 6.88518e+06 | 2.68679 | 2(Loss) |
| glaze | 789.44 | 1.55273 | 5439.9ms | 6661897 | 30 | 4.6846e+11 | 8.04783e+06 | 3.14053 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1661.55 | 0.170088 | 5750.79ms | 6661897 | 40 | 1.69191e+09 | 3.8237e+06 | 1.49199 | 1(Win) |
| glaze | 940.012 | 0.156947 | 10238ms | 6661897 | 30 | 3.37566e+09 | 6.75872e+06 | 2.63746 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1061.32 | 0.16972 | 5780.05ms | 500299 | 640 | 3.72569e+08 | 449554 | 2.33594 | 1(Win) |
| glaze | 772.593 | 0.53086 | 8361.56ms | 500299 | 40 | 4.2991e+08 | 617560 | 3.20889 | 2(Loss) |
| simdjson (ondemand) | 383.943 | 0.0969603 | 7903.68ms | 500299 | 320 | 4.64583e+08 | 1.24269e+06 | 6.45685 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7617.52 | 0.219274 | 6702.04ms | 500299 | 1280 | 2.41445e+07 | 62634.8 | 0.325309 | 1(Win) |
| glaze | 3237.46 | 0.277658 | 7833.3ms | 500299 | 2560 | 4.28659e+08 | 147376 | 0.765599 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2101.87 | 0.20427 | 8518.12ms | 1439562 | 640 | 1.1393e+09 | 653168 | 1.17937 | 1(Win) |
| glaze | 1595.44 | 0.202832 | 5425.21ms | 1439562 | 320 | 9.74811e+08 | 860497 | 1.55381 | 2(Loss) |
| simdjson (ondemand) | 977.281 | 0.133072 | 8870.4ms | 1439562 | 160 | 5.59136e+08 | 1.40479e+06 | 2.53669 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2705.94 | 0.473326 | 6493.36ms | 1439562 | 80 | 4.61356e+08 | 507356 | 0.915695 | 1(Win) |
| glaze | 1119.03 | 0.186004 | 7829.47ms | 1439584 | 320 | 1.6664e+09 | 1.22686e+06 | 2.21448 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1134.28 | 0.272549 | 4814.49ms | 56369 | 1280 | 2.1357e+07 | 47393.7 | 2.18429 | 1(Win) |
| jsonifier | 809.02 | 0.176688 | 6811.5ms | 56369 | 1280 | 1.76436e+07 | 66447.9 | 3.06323 | 2(Loss) |
| simdjson (ondemand) | 445.384 | 0.230135 | 6180.99ms | 56369 | 320 | 2.46903e+07 | 120700 | 5.56544 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7287.32 | 0.0762281 | 751.414ms | 56369 | 160 | 5059.36 | 7376.88 | 0.338834 | 1(Win) |
| glaze | 3323.16 | 0.164179 | 1689.45ms | 56369 | 30 | 21160.9 | 16176.7 | 0.744324 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1548.83 | 0.113036 | 5818.63ms | 94370 | 4890 | 2.10963e+07 | 58107.4 | 1.59992 | 1(Win) |
| jsonifier | 1120.91 | 0.360173 | 8130.74ms | 94370 | 320 | 2.67608e+07 | 80290.3 | 2.21116 | 2(Loss) |
| simdjson (ondemand) | 714.93 | 0.0901788 | 6503.35ms | 94370 | 2560 | 3.29905e+07 | 125884 | 3.46724 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10667.5 | 0.165527 | 857.559ms | 94370 | 30 | 5850.57 | 8436.67 | 0.231747 | 1(Win) |
| glaze | 3133.07 | 0.471087 | 2853.33ms | 94370 | 1280 | 2.3439e+07 | 28725.2 | 0.790404 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1051.51 | 0.235996 | 1089.72ms | 11812 | 2560 | 1.63632e+06 | 10713 | 2.35187 | 1(Win) |
| glaze | 795.467 | 0.880155 | 1433.77ms | 11812 | 160 | 2.48566e+06 | 14161.2 | 3.109 | 2(Loss) |
| simdjson (ondemand) | 354.273 | 0.124536 | 3216.41ms | 11812 | 4890 | 7.66784e+06 | 31797 | 6.99018 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5621.86 | 0.360009 | 203.935ms | 11812 | 80 | 4162.97 | 2003.75 | 0.435669 | 1(Win) |
| glaze | 2615.67 | 0.220798 | 438.306ms | 11812 | 30 | 2712.64 | 4306.67 | 0.938989 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1928.96 | 0.935731 | 1590.08ms | 31235 | 320 | 6.6817e+06 | 15442.5 | 1.28239 | 1(Win) |
| glaze | 1573.06 | 0.221894 | 1966.72ms | 31235 | 2560 | 4.51983e+06 | 18936.3 | 1.57347 | 2(Loss) |
| simdjson (ondemand) | 841.228 | 0.624445 | 3672.15ms | 31235 | 640 | 3.12913e+07 | 35410.2 | 2.94467 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12133.6 | 0.227994 | 274.86ms | 31235 | 80 | 2506.33 | 2455 | 0.202584 | 1(Win) |
| glaze | 3614.96 | 0.420088 | 844.47ms | 31235 | 2560 | 3.06758e+06 | 8240.2 | 0.682977 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1126.33 | 0.383935 | 9158.26ms | 108313 | 2560 | 3.17383e+08 | 91709.4 | 2.20045 | 1(Win) |
| jsonifier | 1102.75 | 0.139572 | 9398.19ms | 108313 | 4890 | 8.35824e+07 | 93670.9 | 2.24754 | 2(Loss) |
| simdjson (ondemand) | 479.888 | 0.471094 | 5743.05ms | 108313 | 80 | 8.22595e+07 | 215249 | 5.16611 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9026.68 | 0.123466 | 1184.09ms | 108313 | 30 | 5988.51 | 11443.3 | 0.27365 | 1(Win) |
| glaze | 2277.8 | 0.178461 | 3851.52ms | 108313 | 4890 | 3.20275e+07 | 45348.7 | 1.08733 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1721.18 | 0.149368 | 6115.74ms | 213963 | 2560 | 8.02753e+07 | 118553 | 1.44008 | 1(Win) |
| jsonifier | 1575.5 | 0.208767 | 6664.82ms | 213963 | 1280 | 9.35785e+07 | 129515 | 1.57331 | 2(Loss) |
| simdjson (ondemand) | 872.932 | 0.287285 | 6149.58ms | 213963 | 160 | 7.21545e+07 | 233754 | 2.83987 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12319 | 0.291472 | 1614.74ms | 213963 | 2560 | 5.96708e+06 | 16564 | 0.200821 | 1(Win) |
| glaze | 3112.24 | 0.269116 | 6556.88ms | 213963 | 4890 | 1.52237e+08 | 65564.1 | 0.796221 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 601.913 | 0.335085 | 9198.02ms | 1834197 | 80 | 7.58619e+09 | 2.90611e+06 | 4.11836 | 1(Win) |
| glaze | 523.482 | 0.471188 | 5091.49ms | 1833577 | 40 | 9.90932e+09 | 3.34039e+06 | 4.73563 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1843.02 | 0.22798 | 7882.42ms | 9930848 | 40 | 5.4899e+09 | 5.13873e+06 | 1.34518 | 1(Win) |
| glaze | 1148.18 | 0.747801 | 5836.67ms | 9930228 | 30 | 1.14129e+11 | 8.24804e+06 | 2.15932 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 393.182 | 0.659771 | 6554.49ms | 1834197 | 80 | 6.89257e+10 | 4.4489e+06 | 6.30536 | 1(Win) |
| simdjson (ondemand) | 245.404 | 0.977243 | 5005.34ms | 1834197 | 40 | 1.94086e+11 | 7.12795e+06 | 10.1024 | 2(Loss) |
| glaze | 233.373 | 1.30425 | 5234.93ms | 1834197 | 40 | 3.82274e+11 | 7.49542e+06 | 10.6233 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 589.118 | 0.34029 | 9413.54ms | 1834197 | 80 | 8.16724e+09 | 2.96923e+06 | 4.20773 | 1(Win) |
| glaze | 395.365 | 0.424822 | 6476ms | 1833577 | 40 | 1.41213e+10 | 4.42283e+06 | 6.27014 | 2(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1820.24 | 0.315479 | 7926.57ms | 9930848 | 30 | 8.08307e+09 | 5.20303e+06 | 1.36199 | 1(Win) |
| glaze | 787.015 | 0.298727 | 8489.95ms | 9930228 | 30 | 3.87636e+10 | 1.20331e+07 | 3.15034 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 755.367 | 0.290384 | 5270.22ms | 642697 | 80 | 4.44151e+08 | 811425 | 3.28193 | 1(Win) |
| simdjson (ondemand) | 628.671 | 0.475623 | 6061.97ms | 642697 | 320 | 6.88084e+09 | 974951 | 3.943 | 2(Loss) |
| glaze | 567.299 | 0.403645 | 6874.16ms | 642697 | 320 | 6.08606e+09 | 1.08042e+06 | 4.36972 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 960.158 | 0.188755 | 8247.59ms | 642697 | 640 | 9.29185e+08 | 638357 | 2.5814 | 1(Win) |
| glaze | 643.565 | 0.323939 | 5942.95ms | 642692 | 160 | 1.52289e+09 | 952380 | 3.84956 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1107.09 | 0.392125 | 6782.16ms | 1225964 | 320 | 5.48772e+09 | 1.05608e+06 | 2.23906 | 1(Win) |
| glaze | 975.333 | 0.325474 | 7711.47ms | 1225964 | 80 | 1.21779e+09 | 1.19874e+06 | 2.54161 | 2(Loss) |
| jsonifier | 912.667 | 0.249964 | 8200.8ms | 1225964 | 320 | 3.28121e+09 | 1.28105e+06 | 2.71634 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1484.51 | 0.426416 | 5243.77ms | 1225964 | 80 | 9.02298e+08 | 787582 | 1.6695 | 1(Win) |
| glaze | 989.413 | 0.444199 | 7338.17ms | 1225970 | 30 | 8.26574e+08 | 1.18169e+06 | 2.50428 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 710.241 | 0.363326 | 7470.99ms | 409725 | 160 | 6.39273e+08 | 550158 | 3.49063 | 1(Win) |
| glaze | 657.727 | 0.612415 | 8193.47ms | 409725 | 40 | 5.29475e+08 | 594082 | 3.76916 | 2(Loss) |
| simdjson (ondemand) | 350.456 | 0.238009 | 7034.16ms | 409725 | 320 | 2.25349e+09 | 1.11496e+06 | 7.07344 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1880.25 | 0.92052 | 5224.34ms | 409725 | 80 | 2.92759e+08 | 207815 | 1.31807 | 1(Win) |
| jsonifier | 1550.93 | 0.621705 | 6527.8ms | 409725 | 80 | 1.96273e+08 | 251942 | 1.59821 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 976.622 | 1.03732 | 8768.68ms | 785750 | 40 | 2.53396e+09 | 767288 | 2.5382 | 1(Tie) |
| glaze STATISTICAL TIE | 961.413 | 0.422911 | 9685.5ms | 785750 | 320 | 3.47694e+09 | 779425 | 2.57788 | 1(Tie) |
| simdjson (ondemand) | 573.242 | 0.405979 | 8161.65ms | 785750 | 30 | 8.44932e+08 | 1.30721e+06 | 4.3244 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2021.53 | 0.224477 | 9428.21ms | 785750 | 1280 | 8.86267e+08 | 370685 | 1.22573 | 1(Win) |
| glaze | 1246.39 | 0.29085 | 7747.95ms | 785750 | 640 | 1.95697e+09 | 601218 | 1.98673 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3710.14 | 0.169651 | 6888.03ms | 264040 | 4890 | 6.48307e+07 | 67870.3 | 0.667904 | 1(Win) |
| glaze STATISTICAL TIE | 1860.71 | 0.74883 | 6921.48ms | 264040 | 80 | 8.21555e+07 | 135329 | 1.33206 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1859.07 | 0.602357 | 6948ms | 264040 | 160 | 1.06506e+08 | 135448 | 1.33338 | 2(Tie) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4811.74 | 0.332563 | 7805.02ms | 399947 | 320 | 2.22381e+07 | 79268.4 | 0.515058 | 1(Win) |
| glaze | 2581.22 | 0.173604 | 7613.52ms | 399947 | 2560 | 1.68466e+08 | 147767 | 0.960316 | 2(Loss) |
| simdjson (ondemand) | 2365.98 | 0.40153 | 8239.01ms | 399947 | 80 | 3.35204e+07 | 161210 | 1.04768 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 897.99 | 0.339236 | 6943.21ms | 264040 | 640 | 5.79135e+08 | 280413 | 2.76038 | 1(Win) |
| jsonifier | 889.398 | 0.229027 | 7233.12ms | 264040 | 1280 | 5.38183e+08 | 283122 | 2.78732 | 2(Loss) |
| simdjson (ondemand) | 507.923 | 0.312004 | 6191.05ms | 264040 | 320 | 7.65619e+08 | 495760 | 4.88078 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5863.76 | 0.205754 | 4219.4ms | 264040 | 4890 | 3.81761e+07 | 42943.1 | 0.422455 | 1(Win) |
| glaze | 2914.03 | 0.829358 | 8471.5ms | 263923 | 320 | 1.64211e+08 | 86374.1 | 0.850432 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1286.4 | 0.591308 | 7901.07ms | 399947 | 320 | 9.83631e+08 | 296502 | 1.92696 | 1(Win) |
| jsonifier | 1041.11 | 0.286668 | 9098.51ms | 399947 | 640 | 7.05911e+08 | 366358 | 2.38117 | 2(Loss) |
| simdjson (ondemand) | 741.275 | 0.48407 | 6431.74ms | 399947 | 80 | 4.9631e+08 | 514545 | 3.34441 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8897.89 | 0.99179 | 4844.05ms | 399947 | 80 | 1.44597e+07 | 42866.2 | 0.278479 | 1(Win) |
| glaze | 1957.83 | 0.340787 | 9908.85ms | 399830 | 2560 | 1.12773e+09 | 194760 | 1.26614 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2234.59 | 0.182038 | 5256.61ms | 466906 | 1280 | 1.68422e+08 | 199266 | 1.10931 | 1(Win) |
| glaze | 1238.75 | 0.463324 | 9111.75ms | 466906 | 40 | 1.10948e+08 | 359455 | 2.00137 | 2(Loss) |
| simdjson (ondemand) | 738.266 | 0.703843 | 7122.26ms | 466906 | 160 | 2.8834e+09 | 603138 | 3.35742 | 3(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1808 | 0.179754 | 8281.17ms | 631514 | 640 | 2.2946e+08 | 333107 | 1.37119 | 1(Win) |
| jsonifier | 1191.95 | 0.323443 | 6442.3ms | 631514 | 320 | 8.54668e+08 | 505272 | 2.07985 | 2(Loss) |
