# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Sep 19, 2026)
#### Using the following commits:
----
| Jsonifier: [3240669](https://github.com/nihilai-collective/jsonifier/commit/3240669)  
| Glaze: [a5fcd46](https://github.com/stephenberry/glaze/commit/a5fcd46)  
| Simdjson: [a683f0a](https://github.com/simdjson/simdjson/commit/a683f0a)  

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

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4972187](https://github.com/realtimechris/benchmarksuite/commit/4972187).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1095.41 | 0.498142 | 0.5093ms | 1811 | 30 | 1850.57 | 1576.67 | 2.70808 | 1(Win) |
| glaze | 545.976 | 0.282884 | 0.9874ms | 1811 | 30 | 2402.3 | 3163.33 | 5.48458 | 2(Loss) |
| simdjson (ondemand) | 161.11 | 0.0684514 | 7.8388ms | 1811 | 40 | 2153.85 | 10720 | 18.8137 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 664.91 | 0.136543 | 4.1698ms | 1811 | 80 | 1006.33 | 2597.5 | 4.50892 | 1(Win) |
| glaze | 514.412 | 0.262613 | 1.2381ms | 1798 | 30 | 2298.85 | 3333.33 | 5.84766 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1868.59 | 0.397337 | 0.6355ms | 3873 | 30 | 1850.57 | 1976.67 | 1.58665 | 1(Win) |
| glaze | 1509.64 | 0.378642 | 0.7561ms | 3873 | 30 | 2574.71 | 2446.67 | 1.98556 | 2(Loss) |
| simdjson (ondemand) | 375.269 | 0.146582 | 15.938ms | 3873 | 80 | 16651.9 | 9842.5 | 8.08151 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4088.83 | 0.369004 | 0.2991ms | 3873 | 30 | 333.333 | 903.333 | 0.725191 | 1(Win) |
| glaze | 2029.44 | 0.35193 | 1.36ms | 3873 | 40 | 1641.03 | 1820 | 1.47731 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2227.68 | 0.560329 | 0.5195ms | 3862 | 30 | 2574.71 | 1653.33 | 1.34549 | 1(Win) |
| glaze | 1567.27 | 0.395096 | 0.8102ms | 3862 | 30 | 2586.21 | 2350 | 1.91489 | 2(Loss) |
| simdjson (ondemand) | 368.309 | 0 | 3.2475ms | 3862 | 30 | 0 | 10000 | 8.21919 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3932.12 | 0.955362 | 0.3083ms | 3862 | 30 | 2402.3 | 936.667 | 0.752089 | 1(Win) |
| glaze | 2192.32 | 0.442132 | 0.5579ms | 3862 | 30 | 1655.17 | 1680 | 1.37154 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2538.46 | 2.67564 | 0.1254ms | 905 | 30 | 2482.76 | 340 | 1.1151 | 1(Win) |
| glaze | 2038.76 | 1.85528 | 0.1512ms | 905 | 30 | 1850.57 | 423.333 | 1.4411 | 2(Loss) |
| simdjson (ondemand) | 142.972 | 0.148237 | 2.0437ms | 905 | 30 | 2402.3 | 6036.67 | 21.1666 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1514.17 | 1.49292 | 0.1877ms | 905 | 30 | 2172.41 | 570 | 1.91783 | 1(Win) |
| glaze | 378.542 | 0.325781 | 0.7272ms | 905 | 30 | 1655.17 | 2280 | 7.92737 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2909.01 | 0.289719 | 0.9876ms | 9578 | 30 | 2482.76 | 3140 | 1.03119 | 1(Win) |
| jsonifier | 1856.56 | 0.857355 | 1.5459ms | 9578 | 30 | 53379.3 | 4920 | 1.62148 | 2(Loss) |
| simdjson (ondemand) | 822.415 | 0.105153 | 3.3888ms | 9578 | 30 | 4091.95 | 11106.7 | 3.68793 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4672.27 | 0.206843 | 6.3928ms | 9578 | 160 | 2616.35 | 1955 | 0.638864 | 1(Win) |
| glaze | 4077.81 | 0.350207 | 1.6386ms | 9578 | 40 | 2461.54 | 2240 | 0.736294 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 627.717 | 1.30602 | 2303.22ms | 2090234 | 40 | 6.88053e+10 | 3.17564e+06 | 4.84144 | 1(Win) |
| glaze | 380.037 | 0.87293 | 1551.62ms | 2090234 | 30 | 6.28953e+10 | 5.24529e+06 | 7.99666 | 2(Loss) |
| simdjson (ondemand) | 370.199 | 0.700593 | 1620.93ms | 2090234 | 30 | 4.26945e+10 | 5.38468e+06 | 8.20958 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1140.4 | 0.223398 | 526.462ms | 2090234 | 30 | 4.57465e+08 | 1.74799e+06 | 2.66464 | 1(Win) |
| glaze | 753.179 | 0.365612 | 796.299ms | 2090234 | 30 | 2.80903e+09 | 2.64665e+06 | 4.03478 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1582.63 | 0.684054 | 1211.01ms | 6661897 | 30 | 2.26225e+10 | 4.01439e+06 | 1.9202 | 1(Win) |
| simdjson (ondemand) | 1128.88 | 0.649602 | 1692.28ms | 6661897 | 30 | 4.00972e+10 | 5.62794e+06 | 2.69211 | 2(Loss) |
| glaze | 1046.8 | 0.568455 | 1828.9ms | 6661897 | 30 | 3.57092e+10 | 6.06923e+06 | 2.9032 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2481.99 | 0.2698 | 768.197ms | 6661897 | 30 | 1.43087e+09 | 2.55975e+06 | 1.2244 | 1(Win) |
| glaze | 1475.48 | 0.60777 | 6443.07ms | 6661897 | 80 | 5.47898e+10 | 4.30592e+06 | 2.05966 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1391.38 | 0.244277 | 103.684ms | 500299 | 30 | 2.10502e+07 | 342913 | 2.18415 | 1(Win) |
| glaze | 891.196 | 1.42587 | 158.393ms | 500299 | 30 | 1.74821e+09 | 535373 | 3.40991 | 2(Loss) |
| simdjson (ondemand) | 484.526 | 0.365609 | 297.22ms | 500299 | 30 | 3.88848e+08 | 984720 | 6.27238 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5743.39 | 1.45012 | 25.0906ms | 500299 | 30 | 4.35365e+07 | 83073.3 | 0.528958 | 1(Win) |
| glaze | 4518.06 | 1.37222 | 31.8662ms | 500299 | 30 | 6.29976e+07 | 105603 | 0.672478 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2297.41 | 0.782448 | 181.405ms | 1439562 | 30 | 6.55865e+08 | 597573 | 1.32262 | 1(Win) |
| glaze | 1881.52 | 0.489496 | 218.813ms | 1439562 | 30 | 3.82702e+08 | 729660 | 1.61506 | 2(Loss) |
| simdjson (ondemand) | 1314.65 | 0.366925 | 316.047ms | 1439562 | 30 | 4.40469e+08 | 1.04429e+06 | 2.31142 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3738.69 | 0.267701 | 1149.35ms | 1439562 | 160 | 1.54612e+08 | 367207 | 0.812335 | 1(Win) |
| glaze | 2011.12 | 0.601078 | 206.255ms | 1439584 | 30 | 5.05102e+08 | 682650 | 1.51061 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1252.9 | 0.347479 | 13.397ms | 56369 | 30 | 666851 | 42906.7 | 2.4245 | 1(Win) |
| glaze | 1184.35 | 0.865818 | 13.6499ms | 56369 | 30 | 4.63334e+06 | 45390 | 2.56476 | 2(Loss) |
| simdjson (ondemand) | 627.595 | 1.27662 | 26.1168ms | 56369 | 30 | 3.58729e+07 | 85656.7 | 4.84097 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5826.34 | 0.11542 | 2.8563ms | 56369 | 30 | 3402.3 | 9226.67 | 0.520599 | 1(Win) |
| glaze | 4378.55 | 1.06887 | 18.6353ms | 56369 | 80 | 1.37772e+06 | 12277.5 | 0.69254 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1766.75 | 0.478327 | 15.9226ms | 94370 | 30 | 1.7811e+06 | 50940 | 1.71926 | 1(Win) |
| jsonifier | 1447.44 | 0.512534 | 45.0264ms | 94370 | 40 | 4.0623e+06 | 62177.5 | 2.09867 | 2(Loss) |
| simdjson (ondemand) | 1013.15 | 0.361238 | 26.9804ms | 94370 | 30 | 3.08907e+06 | 88830 | 2.9989 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8270 | 0.0863485 | 7.9068ms | 94370 | 40 | 3532.05 | 10882.5 | 0.36692 | 1(Win) |
| glaze | 4510.06 | 0.35048 | 62.3397ms | 94370 | 160 | 782616 | 19955 | 0.672759 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 970.267 | 0.533103 | 8.487ms | 11812 | 40 | 153231 | 11610 | 3.13016 | 1(Win) |
| glaze | 731.164 | 1.95786 | 4.7379ms | 11812 | 30 | 2.72961e+06 | 15406.7 | 4.14954 | 2(Loss) |
| simdjson (ondemand) | 499.031 | 0.325561 | 6.976ms | 11812 | 30 | 162023 | 22573.3 | 6.08293 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3822.9 | 0.314393 | 0.9146ms | 11812 | 30 | 2574.71 | 2946.67 | 0.788114 | 1(Win) |
| glaze | 3252.59 | 0.378712 | 1.1145ms | 11812 | 30 | 5160.92 | 3463.33 | 0.927469 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1783.71 | 0.266249 | 5.3694ms | 31235 | 30 | 59310.3 | 16700 | 1.70318 | 1(Win) |
| glaze | 1530.34 | 0.749591 | 13.8226ms | 31235 | 40 | 851564 | 19465 | 1.98506 | 2(Loss) |
| simdjson (ondemand) | 1214.52 | 2.07031 | 7.2965ms | 31235 | 30 | 7.73513e+06 | 24526.7 | 2.49918 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7719.6 | 0.38896 | 25.0652ms | 31235 | 320 | 72086.2 | 3858.75 | 0.391075 | 1(Win) |
| glaze | 5170.13 | 0.370188 | 37.6849ms | 31235 | 320 | 145571 | 5761.56 | 0.585154 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2296.81 | 0.291368 | 13.8491ms | 108313 | 30 | 515126 | 44973.3 | 1.32276 | 1(Win) |
| glaze | 1461.24 | 0.408218 | 21.6449ms | 108313 | 30 | 2.49817e+06 | 70690 | 2.07907 | 2(Loss) |
| simdjson (ondemand) | 706.615 | 0.771267 | 44.189ms | 108313 | 30 | 3.81352e+07 | 146183 | 4.30033 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5201.17 | 4.44646 | 5.7866ms | 108313 | 30 | 2.33942e+07 | 19860 | 0.583532 | 1(Win) |
| glaze | 4502.19 | 1.05086 | 7.099ms | 108313 | 30 | 1.74392e+06 | 22943.3 | 0.674112 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2159.12 | 0.918692 | 28.6299ms | 213963 | 30 | 2.26144e+07 | 94506.7 | 1.40717 | 1(Tie) |
| glaze STATISTICAL TIE | 2146.7 | 1.03766 | 28.3985ms | 213963 | 30 | 2.91853e+07 | 95053.3 | 1.41544 | 1(Tie) |
| simdjson (ondemand) | 1340.59 | 0.320942 | 110.942ms | 213963 | 40 | 9.54554e+06 | 152210 | 2.2667 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7972.69 | 1.74179 | 37.6387ms | 213963 | 80 | 1.58983e+07 | 25593.8 | 0.380898 | 1(Win) |
| glaze | 4525.42 | 1.76522 | 67.5613ms | 213963 | 80 | 5.06814e+07 | 45090 | 0.67114 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 633.605 | 0.939798 | 828.542ms | 1834197 | 30 | 2.01951e+10 | 2.76075e+06 | 4.79636 | 1(Win) |
| glaze | 301.22 | 0.720384 | 1743.9ms | 1834197 | 30 | 5.25018e+10 | 5.80714e+06 | 10.0895 | 2(Loss) |
| simdjson (ondemand) | 36.7311 | 0.233721 | 14290.1ms | 1834197 | 30 | 3.71657e+11 | 4.76225e+07 | 82.7459 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 740.62 | 0.479095 | 712.875ms | 1834197 | 30 | 3.84119e+09 | 2.36184e+06 | 4.10323 | 1(Win) |
| glaze | 664.135 | 0.717344 | 780.23ms | 1833577 | 30 | 1.07019e+10 | 2.63295e+06 | 4.57588 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2208.96 | 0.740257 | 1284.21ms | 9930848 | 30 | 3.02194e+10 | 4.28745e+06 | 1.37578 | 1(Win) |
| glaze | 1322.6 | 0.611234 | 2137.79ms | 9930848 | 30 | 5.74712e+10 | 7.16073e+06 | 2.29782 | 2(Loss) |
| simdjson (ondemand) | 192.4 | 0.332661 | 14599.1ms | 9930848 | 30 | 8.04429e+11 | 4.92245e+07 | 15.797 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2301.84 | 0.828407 | 1206.32ms | 9930848 | 30 | 3.48522e+10 | 4.11444e+06 | 1.32026 | 1(Win) |
| glaze | 1829.36 | 0.456172 | 7758.6ms | 9930228 | 80 | 4.46136e+10 | 5.17678e+06 | 1.66101 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 650.369 | 0.90384 | 817.039ms | 1834197 | 30 | 1.77287e+10 | 2.68959e+06 | 4.67267 | 1(Win) |
| simdjson (ondemand) | 306.928 | 0.880035 | 1695.9ms | 1834197 | 30 | 7.54642e+10 | 5.69915e+06 | 9.90188 | 2(Loss) |
| glaze | 291.387 | 0.500985 | 1792.58ms | 1834197 | 30 | 2.71345e+10 | 6.0031e+06 | 10.4299 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 732.207 | 0.599452 | 720.351ms | 1834197 | 30 | 6.15254e+09 | 2.38898e+06 | 4.15039 | 1(Win) |
| glaze | 587.15 | 0.600024 | 894.226ms | 1833577 | 30 | 9.57988e+09 | 2.97818e+06 | 5.17576 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2216.34 | 0.755763 | 1270.67ms | 9930848 | 30 | 3.12891e+10 | 4.27317e+06 | 1.37119 | 1(Win) |
| simdjson (ondemand) | 1468.67 | 0.677718 | 1893.27ms | 9930848 | 30 | 5.72984e+10 | 6.44854e+06 | 2.06924 | 2(Loss) |
| glaze | 1296.58 | 0.765273 | 2193.96ms | 9930848 | 30 | 9.3741e+10 | 7.30446e+06 | 2.34394 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2354.96 | 0.670256 | 2815.33ms | 9930848 | 40 | 2.90635e+10 | 4.02164e+06 | 1.29051 | 1(Win) |
| glaze | 1284.34 | 0.648062 | 2181.27ms | 9930228 | 30 | 6.85031e+10 | 7.37358e+06 | 2.36621 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1224.59 | 1.51526 | 1530.5ms | 642697 | 160 | 9.20303e+09 | 500515 | 2.48135 | 1(Win) |
| simdjson (ondemand) | 769.425 | 1.03747 | 239.988ms | 642697 | 30 | 2.04904e+09 | 796600 | 3.94935 | 2(Loss) |
| glaze | 678.315 | 1.69686 | 269.344ms | 642697 | 30 | 7.05285e+09 | 903597 | 4.47935 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1141.78 | 0.921393 | 163.756ms | 642697 | 30 | 7.33935e+08 | 536813 | 2.661 | 1(Win) |
| glaze | 911.029 | 0.394043 | 201.401ms | 642692 | 30 | 2.10839e+08 | 672777 | 3.33463 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1494.19 | 0.401255 | 240.286ms | 1225964 | 30 | 2.95736e+08 | 782477 | 2.03376 | 1(Win) |
| simdjson (ondemand) | 1433.96 | 0.741907 | 574.571ms | 1225964 | 40 | 1.46365e+09 | 815342 | 2.11906 | 2(Loss) |
| glaze | 1162.99 | 1.48381 | 294.837ms | 1225964 | 30 | 6.6754e+09 | 1.00531e+06 | 2.61286 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1843.9 | 0.776498 | 191.373ms | 1225964 | 30 | 7.27245e+08 | 634073 | 1.64755 | 1(Win) |
| glaze | 1498.75 | 0.869373 | 236.11ms | 1225970 | 30 | 1.37986e+09 | 780100 | 2.02704 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 840.871 | 0.919074 | 142.073ms | 409725 | 30 | 5.47203e+08 | 464690 | 3.61396 | 1(Win) |
| glaze | 581.941 | 1.58154 | 200.589ms | 409725 | 30 | 3.38306e+09 | 671450 | 5.22205 | 2(Loss) |
| simdjson (ondemand) | 511.805 | 0.576154 | 1149.75ms | 409725 | 80 | 1.5479e+09 | 763462 | 5.93749 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2915.68 | 1.29649 | 96.6008ms | 409725 | 40 | 1.20755e+08 | 134015 | 1.04196 | 1(Win) |
| jsonifier | 1815.39 | 0.488348 | 681.215ms | 409725 | 160 | 1.76775e+08 | 215239 | 1.67326 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1230.36 | 0.553854 | 185.867ms | 785750 | 30 | 3.4136e+08 | 609047 | 2.46991 | 1(Win) |
| glaze | 981.642 | 1.09274 | 228.628ms | 785750 | 30 | 2.08746e+09 | 763363 | 3.09552 | 2(Loss) |
| simdjson (ondemand) | 946.296 | 0.483229 | 240.531ms | 785750 | 30 | 4.39281e+08 | 791877 | 3.21117 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2819.22 | 0.994065 | 79.8307ms | 785750 | 30 | 2.09441e+08 | 265800 | 1.07743 | 1(Win) |
| glaze | 2232.75 | 1.01382 | 99.8453ms | 785750 | 30 | 3.47323e+08 | 335617 | 1.3601 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4557.89 | 0.291184 | 17.168ms | 264040 | 30 | 776368 | 55246.7 | 0.666417 | 1(Win) |
| glaze | 2292.15 | 2.99498 | 30.9351ms | 264040 | 30 | 3.2476e+08 | 109857 | 1.32537 | 2(Loss) |
| simdjson (ondemand) | 1941.43 | 0.252237 | 91.8488ms | 264040 | 40 | 4.28128e+06 | 129702 | 1.56516 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6045 | 0.549513 | 19.3429ms | 399947 | 30 | 3.60654e+06 | 63096.7 | 0.502666 | 1(Win) |
| glaze | 3199.38 | 0.88493 | 36.8527ms | 399947 | 30 | 3.33897e+07 | 119217 | 0.949766 | 2(Loss) |
| simdjson (ondemand) | 2756.38 | 0.321466 | 42.0959ms | 399947 | 30 | 5.93633e+06 | 138377 | 1.10236 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1602.44 | 0.894105 | 47.2298ms | 264040 | 30 | 5.92204e+07 | 157140 | 1.89619 | 1(Win) |
| glaze | 1139.28 | 2.3528 | 67.3301ms | 264040 | 30 | 8.11272e+08 | 221023 | 2.66706 | 2(Loss) |
| simdjson (ondemand) | 819.057 | 1.33937 | 92.5902ms | 264040 | 30 | 5.0867e+08 | 307437 | 3.7101 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6364.69 | 3.52748 | 12.0763ms | 264040 | 30 | 5.843e+07 | 39563.3 | 0.477325 | 1(Win) |
| glaze | 4624.38 | 0.567509 | 176.942ms | 263923 | 160 | 1.52656e+07 | 54428.1 | 0.656883 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1525.94 | 2.235 | 171.888ms | 399947 | 40 | 1.24839e+09 | 249958 | 1.99139 | 1(Tie) |
| glaze STATISTICAL TIE | 1513.3 | 1.4715 | 178.326ms | 399947 | 40 | 5.50219e+08 | 252045 | 2.00817 | 1(Tie) |
| simdjson (ondemand) | 1219.81 | 0.569948 | 97.2483ms | 399947 | 30 | 9.52819e+07 | 312687 | 2.49136 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7561.84 | 1.31441 | 14.9791ms | 399947 | 30 | 1.31866e+07 | 50440 | 0.401669 | 1(Win) |
| glaze | 3322.73 | 0.656292 | 1464.02ms | 399830 | 640 | 3.63024e+08 | 114757 | 0.914353 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2473.41 | 0.593225 | 128.829ms | 466906 | 40 | 4.56209e+07 | 180025 | 1.22843 | 1(Win) |
| glaze | 1931.06 | 1.27654 | 70.2443ms | 466906 | 30 | 2.59932e+08 | 230587 | 1.57357 | 2(Loss) |
| simdjson (ondemand) | 1129.37 | 0.796198 | 119.047ms | 466906 | 30 | 2.95632e+08 | 394270 | 2.69048 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3535.73 | 0.924958 | 57.5304ms | 699405 | 30 | 9.13405e+07 | 188647 | 0.859279 | 1(Win) |
| glaze | 2391.08 | 0.425037 | 198.847ms | 699405 | 40 | 5.62318e+07 | 278955 | 1.27096 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2762.02 | 0.424392 | 66.7494ms | 631514 | 30 | 2.56902e+07 | 218050 | 1.10019 | 1(Win) |
| glaze | 2506.24 | 1.96241 | 71.3279ms | 631514 | 30 | 6.67142e+08 | 240303 | 1.21256 | 2(Loss) |
