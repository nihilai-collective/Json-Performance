# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Sep 23, 2026)
#### Using the following commits:
----
| Jsonifier: [9b1cd1d](https://github.com/nihilai-collective/jsonifier/commit/9b1cd1d)  
| Glaze: [76db773](https://github.com/stephenberry/glaze/commit/76db773)  
| Simdjson: [6913ee1](https://github.com/simdjson/simdjson/commit/6913ee1)  

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

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1039.71 | 0.52484 | 175.709ms | 1811 | 4890 | 371687 | 1661.15 | 2.86308 | 1(Win) |
| glaze | 540.847 | 0.145054 | 1.2992ms | 1811 | 30 | 643.678 | 3193.33 | 5.53571 | 2(Loss) |
| simdjson (ondemand) | 180.534 | 0.144679 | 3.6208ms | 1811 | 30 | 5747.13 | 9566.67 | 16.7834 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 612.992 | 3.37057 | 9.9205ms | 1811 | 160 | 1.44296e+06 | 2817.5 | 4.90542 | 1(Win) |
| glaze | 503.955 | 3.03282 | 11.4025ms | 1798 | 160 | 1.70377e+06 | 3402.5 | 5.99424 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1947.41 | 0.175747 | 0.6544ms | 3873 | 30 | 333.333 | 1896.67 | 1.54167 | 1(Win) |
| glaze | 1651.38 | 0.400084 | 0.707ms | 3873 | 30 | 2402.3 | 2236.67 | 1.82225 | 2(Loss) |
| simdjson (ondemand) | 419.566 | 1.94512 | 2.8278ms | 3873 | 30 | 879644 | 8803.33 | 7.22261 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4397.12 | 1.083 | 0.2862ms | 3873 | 30 | 2482.76 | 840 | 0.676358 | 1(Win) |
| glaze | 2073.32 | 1.47005 | 50.0679ms | 3873 | 1280 | 877882 | 1781.48 | 1.44888 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2238.96 | 0.484272 | 1.4034ms | 3862 | 40 | 2538.46 | 1645 | 1.33558 | 1(Win) |
| glaze | 1594.41 | 0.241163 | 0.7253ms | 3862 | 30 | 931.034 | 2310 | 1.87613 | 2(Loss) |
| simdjson (ondemand) | 421.889 | 1.0595 | 2.9492ms | 3862 | 30 | 256655 | 8730 | 7.17457 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4161.68 | 0.45394 | 1.4297ms | 3862 | 80 | 1291.14 | 885 | 0.712633 | 1(Win) |
| glaze | 2120.78 | 0.515272 | 0.6053ms | 3862 | 30 | 2402.3 | 1736.67 | 1.41264 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2669.3 | 2.42908 | 0.1176ms | 905 | 30 | 1850.57 | 323.333 | 1.07068 | 1(Win) |
| glaze | 2054.94 | 1.76853 | 0.1455ms | 905 | 30 | 1655.17 | 420 | 1.40645 | 2(Loss) |
| simdjson (ondemand) | 147.471 | 0.136632 | 4.6187ms | 905 | 40 | 2557.69 | 5852.5 | 20.532 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1523.07 | 1.54478 | 0.1847ms | 905 | 30 | 2298.85 | 566.667 | 1.95186 | 1(Win) |
| glaze | 383.589 | 0.412656 | 0.7819ms | 905 | 30 | 2586.21 | 2250 | 7.85937 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2896.71 | 0.293788 | 1.021ms | 9578 | 30 | 2574.71 | 3153.33 | 1.03965 | 1(Win) |
| jsonifier | 1861.29 | 0.0859427 | 3.8662ms | 9578 | 40 | 711.538 | 4907.5 | 1.61472 | 2(Loss) |
| simdjson (ondemand) | 802.309 | 1.68136 | 18.0694ms | 9578 | 80 | 2.93142e+06 | 11385 | 3.77883 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5279.94 | 0.491886 | 0.6624ms | 9578 | 30 | 2172.41 | 1730 | 0.567558 | 1(Win) |
| glaze | 3930.84 | 0.206039 | 4.1601ms | 9578 | 80 | 1833.86 | 2323.75 | 0.763813 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 579.349 | 0.816324 | 5388.23ms | 2090234 | 80 | 6.31139e+10 | 3.44076e+06 | 5.2449 | 1(Win) |
| glaze STATISTICAL TIE | 354.628 | 1.17928 | 3874.58ms | 2090234 | 40 | 1.75768e+11 | 5.62111e+06 | 8.56951 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 354.473 | 1.07075 | 1671.53ms | 2090234 | 30 | 1.08774e+11 | 5.62357e+06 | 8.57363 | 2(Tie) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1093.11 | 0.716709 | 1270.04ms | 2090234 | 40 | 6.83299e+09 | 1.82361e+06 | 2.77998 | 1(Win) |
| glaze | 773.446 | 1.12072 | 757.787ms | 2090234 | 30 | 2.50291e+10 | 2.5773e+06 | 3.92903 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1431.92 | 0.829638 | 6567.57ms | 6661897 | 80 | 1.084e+11 | 4.4369e+06 | 2.12233 | 1(Win) |
| simdjson (ondemand) | 1070.34 | 1.07592 | 1782.11ms | 6661897 | 30 | 1.22357e+11 | 5.93574e+06 | 2.83916 | 2(Loss) |
| glaze | 982.846 | 0.567433 | 9836.03ms | 6661897 | 80 | 1.07633e+11 | 6.46417e+06 | 3.09203 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2270.33 | 1.54671 | 842.99ms | 6661897 | 30 | 5.62028e+10 | 2.7984e+06 | 1.33855 | 1(Win) |
| glaze | 1377.36 | 0.64545 | 6987.35ms | 6661897 | 80 | 7.09111e+10 | 4.61264e+06 | 2.20641 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1397.96 | 0.611896 | 103.29ms | 500299 | 30 | 1.30843e+08 | 341300 | 2.1736 | 1(Win) |
| glaze | 910.961 | 0.364934 | 1675.08ms | 500299 | 160 | 5.84533e+08 | 523757 | 3.33593 | 2(Loss) |
| simdjson (ondemand) | 494.221 | 0.309957 | 12247.9ms | 500299 | 640 | 5.73061e+09 | 965403 | 6.1486 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5838.14 | 1.36022 | 61.2196ms | 500299 | 40 | 4.94296e+07 | 81725 | 0.520363 | 1(Win) |
| glaze | 4465.97 | 0.630372 | 2833.77ms | 500299 | 1280 | 5.80539e+08 | 106835 | 0.680298 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2298.81 | 0.817344 | 427.744ms | 1439562 | 40 | 9.53069e+08 | 597210 | 1.32173 | 1(Win) |
| glaze | 1854.4 | 2.71115 | 222.843ms | 1439562 | 30 | 1.2086e+10 | 740333 | 1.63859 | 2(Loss) |
| simdjson (ondemand) | 1374.84 | 0.533548 | 306.714ms | 1439562 | 30 | 8.51579e+08 | 998570 | 2.21026 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3405.73 | 2.2881 | 556.367ms | 1439562 | 80 | 6.80587e+09 | 403108 | 0.891764 | 1(Win) |
| glaze | 1828.51 | 3.13262 | 224.55ms | 1439584 | 30 | 1.65965e+10 | 750827 | 1.66144 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1187.01 | 1.00471 | 584.148ms | 56369 | 640 | 1.32507e+08 | 45288.3 | 2.55884 | 1(Win) |
| glaze | 1094.97 | 1.1112 | 616ms | 56369 | 640 | 1.90475e+08 | 49095.2 | 2.77396 | 2(Loss) |
| simdjson (ondemand) | 627.033 | 1.11598 | 27.2932ms | 56369 | 30 | 2.74623e+07 | 85733.3 | 4.84635 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5891.25 | 0.134505 | 6.9013ms | 56369 | 40 | 6025.64 | 9125 | 0.514941 | 1(Win) |
| glaze | 4488.53 | 0.872211 | 4.3221ms | 56369 | 30 | 327368 | 11976.7 | 0.675362 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1688.84 | 1.5754 | 16.6585ms | 94370 | 30 | 2.11444e+07 | 53290 | 1.79902 | 1(Win) |
| jsonifier | 1451.12 | 1.11662 | 19.981ms | 94370 | 30 | 1.43879e+07 | 62020 | 2.09351 | 2(Loss) |
| simdjson (ondemand) | 979.377 | 1.92933 | 27.7321ms | 94370 | 30 | 9.42979e+07 | 91893.3 | 3.10198 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7824.55 | 1.92303 | 147.673ms | 94370 | 640 | 3.13114e+07 | 11502 | 0.387618 | 1(Win) |
| glaze | 3882.16 | 2.9469 | 69.8805ms | 94370 | 160 | 7.46743e+07 | 23182.5 | 0.781841 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 952.148 | 0.828179 | 75.9074ms | 11812 | 320 | 3.07211e+06 | 11830.9 | 3.18566 | 1(Win) |
| glaze | 721.524 | 2.3514 | 11.3461ms | 11812 | 40 | 5.39087e+06 | 15612.5 | 4.20521 | 2(Loss) |
| simdjson (ondemand) | 491.872 | 1.5467 | 73.2662ms | 11812 | 160 | 2.00758e+07 | 22901.9 | 6.17138 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4391.74 | 0.297763 | 1.916ms | 11812 | 40 | 2333.33 | 2565 | 0.686867 | 1(Win) |
| glaze | 3184.4 | 0.28064 | 2.5951ms | 11812 | 40 | 3942.31 | 3537.5 | 0.946245 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1790.48 | 1.00863 | 55.0434ms | 31235 | 160 | 4.50536e+06 | 16636.9 | 1.69558 | 1(Win) |
| glaze | 1480.89 | 1.91242 | 15.0188ms | 31235 | 40 | 5.91926e+06 | 20115 | 2.04981 | 2(Loss) |
| simdjson (ondemand) | 1227.61 | 1.45388 | 18.0997ms | 31235 | 40 | 4.97823e+06 | 24265 | 2.47253 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7996.78 | 0.186141 | 3.0065ms | 31235 | 40 | 1923.08 | 3725 | 0.378031 | 1(Win) |
| glaze | 5409.86 | 1.56451 | 18.5712ms | 31235 | 160 | 1.18738e+06 | 5506.25 | 0.558751 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2300.05 | 3.72139 | 14.3945ms | 108313 | 30 | 8.37947e+07 | 44910 | 1.32055 | 1(Win) |
| glaze | 1355.3 | 0.873092 | 1954.64ms | 108313 | 1280 | 5.66791e+08 | 76216 | 2.2406 | 2(Loss) |
| simdjson (ondemand) | 710.52 | 1.15802 | 46.644ms | 108313 | 30 | 8.50279e+07 | 145380 | 4.2761 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5925.45 | 0.620075 | 14.7599ms | 108313 | 40 | 467378 | 17432.5 | 0.512007 | 1(Win) |
| glaze | 3916.97 | 1.83078 | 42.2652ms | 108313 | 80 | 1.86476e+07 | 26371.2 | 0.774846 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1966.02 | 2.05074 | 650.663ms | 213963 | 320 | 1.44968e+09 | 103789 | 1.54535 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1952.15 | 2.43862 | 645.293ms | 213963 | 320 | 2.07918e+09 | 104527 | 1.55625 | 1(Tie) |
| simdjson (ondemand) | 1216.03 | 3.05206 | 250.842ms | 213963 | 80 | 2.09829e+09 | 167801 | 2.49863 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8453.98 | 1.99403 | 8.2364ms | 213963 | 30 | 6.9493e+06 | 24136.7 | 0.359129 | 1(Win) |
| glaze | 4297.92 | 2.10844 | 603.257ms | 213963 | 640 | 6.41306e+08 | 47476.7 | 0.706709 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 588.262 | 1.55359 | 2083.49ms | 1834197 | 40 | 8.53654e+10 | 2.97355e+06 | 5.1659 | 1(Win) |
| glaze | 275.665 | 1.11058 | 1909.67ms | 1834197 | 30 | 1.48988e+11 | 6.34547e+06 | 11.0249 | 2(Loss) |
| simdjson (ondemand) | 36.2108 | 0.458546 | 34016.3ms | 1834197 | 40 | 1.96265e+12 | 4.83068e+07 | 83.935 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 728.26 | 0.26242 | 1732.02ms | 1834197 | 40 | 1.58917e+09 | 2.40192e+06 | 4.17281 | 1(Win) |
| glaze | 637.833 | 1.55299 | 812.623ms | 1833577 | 30 | 5.43803e+10 | 2.74152e+06 | 4.7618 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1937.76 | 0.989063 | 3376.01ms | 9930848 | 40 | 9.34722e+10 | 4.88751e+06 | 1.56834 | 1(Win) |
| glaze | 1327.06 | 0.367683 | 22370.4ms | 9930848 | 160 | 1.10169e+11 | 7.13669e+06 | 2.29008 | 2(Loss) |
| simdjson (ondemand) | 187.694 | 0.628593 | 14870.8ms | 9930848 | 30 | 3.0181e+12 | 5.04588e+07 | 16.1931 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2256.14 | 0.812629 | 12822.4ms | 9930848 | 160 | 1.86186e+11 | 4.19779e+06 | 1.34695 | 1(Win) |
| glaze | 1754.08 | 0.862871 | 3719.96ms | 9930228 | 40 | 8.68102e+10 | 5.39895e+06 | 1.73253 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 627.296 | 1.36416 | 837.295ms | 1834197 | 30 | 4.34109e+10 | 2.78852e+06 | 4.84445 | 1(Win) |
| simdjson (ondemand) | 312.938 | 1.1099 | 1674.3ms | 1834197 | 30 | 1.15469e+11 | 5.58969e+06 | 9.71165 | 2(Loss) |
| glaze | 290.573 | 0.950509 | 4260.14ms | 1834197 | 40 | 1.30964e+11 | 6.01992e+06 | 10.4592 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 708.083 | 1.39388 | 741.301ms | 1834197 | 30 | 3.55708e+10 | 2.47037e+06 | 4.29183 | 1(Win) |
| glaze | 575.572 | 1.26107 | 914.008ms | 1833577 | 30 | 4.40352e+10 | 3.03808e+06 | 5.27995 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2004.17 | 1.15544 | 1416.6ms | 9930848 | 30 | 8.94382e+10 | 4.72555e+06 | 1.51637 | 1(Win) |
| simdjson (ondemand) | 1454.92 | 0.612991 | 1952.97ms | 9930848 | 30 | 4.77665e+10 | 6.50949e+06 | 2.08883 | 2(Loss) |
| glaze | 1272.74 | 0.761123 | 5188.82ms | 9930848 | 40 | 1.2831e+11 | 7.44125e+06 | 2.38783 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2332.9 | 0.708842 | 1208.95ms | 9930848 | 30 | 2.48428e+10 | 4.05967e+06 | 1.30272 | 1(Win) |
| glaze | 1197.1 | 0.971369 | 5519.13ms | 9930228 | 40 | 2.36204e+11 | 7.91096e+06 | 2.53864 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1225.16 | 1.30134 | 361.586ms | 642697 | 40 | 1.69539e+09 | 500282 | 2.48026 | 1(Win) |
| simdjson (ondemand) | 765.141 | 1.8412 | 241.231ms | 642697 | 30 | 6.52612e+09 | 801060 | 3.97121 | 2(Loss) |
| glaze | 649.067 | 2.05547 | 656.492ms | 642697 | 40 | 1.50701e+10 | 944315 | 4.68153 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1089.56 | 1.67299 | 170.752ms | 642697 | 30 | 2.65716e+09 | 562543 | 2.78834 | 1(Win) |
| glaze | 827.536 | 2.93803 | 504.454ms | 642692 | 40 | 1.89411e+10 | 740655 | 3.67101 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1407.78 | 2.23075 | 577.358ms | 1225964 | 40 | 1.37294e+10 | 830508 | 2.15832 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1394.03 | 2.6386 | 252.189ms | 1225964 | 30 | 1.46919e+10 | 838697 | 2.17973 | 1(Tie) |
| glaze | 1093.54 | 2.30341 | 326.568ms | 1225964 | 30 | 1.81951e+10 | 1.06916e+06 | 2.77865 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1742.05 | 0.678295 | 4217.55ms | 1225964 | 320 | 6.63164e+09 | 671146 | 1.74377 | 1(Win) |
| glaze | 1452.14 | 1.4034 | 244.497ms | 1225970 | 30 | 3.83026e+09 | 805140 | 2.09214 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 835.382 | 0.543431 | 144.762ms | 409725 | 30 | 1.93832e+08 | 467743 | 3.63773 | 1(Win) |
| glaze | 566.767 | 1.83282 | 209.261ms | 409725 | 30 | 4.78999e+09 | 689427 | 5.36082 | 2(Loss) |
| simdjson (ondemand) | 494.273 | 1.5956 | 238.638ms | 409725 | 30 | 4.7733e+09 | 790543 | 6.14736 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2774.12 | 3.50787 | 43.0242ms | 409725 | 30 | 7.32392e+08 | 140853 | 1.09481 | 1(Win) |
| jsonifier | 1837.49 | 1.58078 | 313.364ms | 409725 | 80 | 9.03997e+08 | 212651 | 1.65297 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1156.16 | 0.456705 | 8202.35ms | 785750 | 640 | 5.60769e+09 | 648137 | 2.62816 | 1(Win) |
| glaze | 929.403 | 2.27923 | 555.775ms | 785750 | 40 | 1.35082e+10 | 806270 | 3.26767 | 2(Loss) |
| simdjson (ondemand) | 873.969 | 2.01015 | 595.782ms | 785750 | 40 | 1.18821e+10 | 857410 | 3.47684 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2592.51 | 1.56038 | 910.948ms | 785750 | 160 | 3.2547e+09 | 289044 | 1.17151 | 1(Win) |
| glaze | 2000.28 | 2.80523 | 263.306ms | 785750 | 40 | 4.4176e+09 | 374622 | 1.51823 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4275.03 | 1.63277 | 753.463ms | 264040 | 640 | 5.91956e+08 | 58902 | 0.710582 | 1(Win) |
| glaze | 2226.81 | 4.64862 | 169.248ms | 264040 | 80 | 2.2106e+09 | 113080 | 1.34748 | 2(Loss) |
| simdjson (ondemand) | 1871.76 | 2.47477 | 97.3954ms | 264040 | 40 | 4.43372e+08 | 134530 | 1.62313 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5784.39 | 1.02718 | 1701.29ms | 399947 | 1280 | 5.87204e+08 | 65939.4 | 0.525184 | 1(Win) |
| glaze | 3115.49 | 3.69772 | 36.7977ms | 399947 | 30 | 6.14811e+08 | 122427 | 0.975323 | 2(Loss) |
| simdjson (ondemand) | 2571.36 | 1.23322 | 1861.4ms | 399947 | 640 | 2.14161e+09 | 148333 | 1.18164 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1578.97 | 2.08551 | 49.4445ms | 264040 | 30 | 3.31848e+08 | 159477 | 1.92439 | 1(Win) |
| glaze | 1131.4 | 1.71499 | 69.2822ms | 264040 | 30 | 4.37071e+08 | 222563 | 2.68543 | 2(Loss) |
| simdjson (ondemand) | 813.746 | 0.733206 | 95.4759ms | 264040 | 30 | 1.54432e+08 | 309443 | 3.7345 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5626.58 | 1.65299 | 12.8015ms | 264040 | 30 | 1.64177e+07 | 44753.3 | 0.539981 | 1(Win) |
| glaze | 4674.32 | 3.94207 | 16.4882ms | 263923 | 30 | 1.35172e+08 | 53846.7 | 0.649833 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1607.78 | 1.03689 | 74.9091ms | 399947 | 30 | 1.81526e+08 | 237233 | 1.88998 | 1(Win) |
| glaze | 1433.81 | 1.68223 | 823.316ms | 399947 | 160 | 3.20416e+09 | 266018 | 2.11849 | 2(Loss) |
| simdjson (ondemand) | 1197.18 | 0.424352 | 1041.34ms | 399947 | 160 | 2.92453e+08 | 318597 | 2.53821 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7540.16 | 3.73673 | 75.05ms | 399947 | 80 | 2.85835e+08 | 50585 | 0.402848 | 1(Win) |
| glaze | 3888.71 | 0.97917 | 318.799ms | 399830 | 160 | 1.47494e+08 | 98055 | 0.781352 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2263.81 | 1.66957 | 611.224ms | 466906 | 160 | 1.72547e+09 | 196693 | 1.3421 | 1(Win) |
| glaze | 1927.07 | 0.956004 | 72.2539ms | 466906 | 30 | 1.46387e+08 | 231063 | 1.57695 | 2(Loss) |
| simdjson (ondemand) | 1149.1 | 0.552015 | 118.228ms | 466906 | 30 | 1.37267e+08 | 387500 | 2.64406 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3336.64 | 1.92484 | 62.4624ms | 699405 | 30 | 4.44169e+08 | 199903 | 0.910394 | 1(Win) |
| glaze | 2335.42 | 2.97794 | 87.5281ms | 699405 | 30 | 2.17009e+09 | 285603 | 1.3011 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2730.73 | 0.555094 | 340.362ms | 631514 | 80 | 1.19904e+08 | 220549 | 1.1127 | 1(Win) |
| glaze | 2347.93 | 2.65473 | 369.824ms | 631514 | 80 | 3.70958e+09 | 256506 | 1.29422 | 2(Loss) |
