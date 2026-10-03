# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [701dfa9](https://github.com/nihilai-collective/jsonifier/commit/701dfa9)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10% AND mean shift < 5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 1141.46 | 0.314652 | 1078.68ms | 905 | 160 | 905.635 | 756.112 | 2.05827 | 1(Win) |
| glaze | 665.709 | 0.256265 | 1128.06ms | 905 | 40 | 441.538 | 1296.47 | 3.60624 | 2(Loss) |
| simdjson (ondemand) | 97.1605 | 0.566755 | 1872.65ms | 905 | 320 | 811071 | 8882.98 | 25.3724 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1195.94 | 0.123949 | 1070.54ms | 905 | 160 | 128.022 | 721.669 | 1.95916 | 1(Win) |
| simdjson (reflection) | 174.52 | 0.0703784 | 1489.46ms | 905 | 40 | 484.558 | 4945.43 | 14.0845 | 2(Loss) |
| glaze | 115.361 | 0.82623 | 1735.44ms | 905 | 2560 | 9.78181e+06 | 7481.5 | 21.3431 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 675.327 | 0.256693 | 1255.24ms | 1811 | 30 | 1292.87 | 2557.43 | 3.61119 | 1(Win) |
| glaze | 512.061 | 0.106376 | 1342.04ms | 1811 | 80 | 1029.85 | 3372.85 | 4.7833 | 2(Loss) |
| simdjson (ondemand) | 92.1049 | 0.326229 | 2911.86ms | 1811 | 30 | 112264 | 18751.5 | 26.8265 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) STATISTICAL TIE | 183.992 | 0.92423 | 2013.46ms | 1997 | 4890 | 4.47537e+07 | 10350.9 | 13.3649 | 1(Tie) |
| jsonifier STATISTICAL TIE | 168.19 | 1.7941 | 1993.1ms | 1811 | 1280 | 4.34452e+07 | 10268.8 | 14.666 | 1(Tie) |
| glaze | 140.996 | 1.60423 | 2167.48ms | 1798 | 1280 | 4.87205e+07 | 12161.4 | 17.5039 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1548.41 | 0.189235 | 1250.99ms | 3862 | 30 | 607.826 | 2378.63 | 1.57423 | 1(Win) |
| glaze | 900.068 | 0.138118 | 1415.96ms | 3862 | 80 | 2555.43 | 4092.01 | 2.72429 | 2(Loss) |
| simdjson (ondemand) | 277.576 | 0.749778 | 2291.16ms | 3862 | 4890 | 4.83988e+07 | 13268.8 | 8.89401 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 446.161 | 0.12975 | 1836.12ms | 3862 | 30 | 3441.72 | 8255.07 | 5.5227 | 1(Win) |
| glaze | 433.323 | 0.150896 | 1873.24ms | 3862 | 30 | 4934.86 | 8499.63 | 5.68809 | 2(Loss) |
| simdjson (reflection) | 292.598 | 0.0964902 | 2274.23ms | 3862 | 30 | 4425.57 | 12587.5 | 8.43508 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 796.811 | 0.761354 | 2197.82ms | 9578 | 30 | 228525 | 11463.6 | 3.09541 | 1(Win) |
| glaze | 653.979 | 0.943794 | 2381.74ms | 9578 | 2560 | 4.44853e+07 | 13967.3 | 3.77297 | 2(Loss) |
| simdjson (ondemand) | 481.686 | 0.58345 | 2850.8ms | 9578 | 4890 | 5.98602e+07 | 18963.2 | 5.12386 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1275.92 | 0.0799587 | 1763.89ms | 9578 | 30 | 982.999 | 7158.97 | 1.93023 | 1(Win) |
| glaze | 1102.35 | 0.0592907 | 1843.88ms | 9578 | 30 | 724.116 | 8286.23 | 2.23571 | 2(Loss) |
| simdjson (reflection) | 729.623 | 0.083312 | 2281.01ms | 9578 | 30 | 3263.54 | 12519.2 | 3.38252 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1518.19 | 0.156411 | 1263.81ms | 3873 | 160 | 2316.86 | 2432.89 | 1.60536 | 1(Win) |
| glaze | 1074.07 | 0.294179 | 1356.74ms | 3873 | 30 | 3070.26 | 3438.87 | 2.2818 | 2(Loss) |
| simdjson (ondemand) | 298.458 | 0.84472 | 2201.76ms | 3873 | 4890 | 5.34394e+07 | 12375.5 | 8.26977 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 444.992 | 0.102649 | 1855.07ms | 3873 | 30 | 2177.82 | 8300.33 | 5.53857 | 1(Win) |
| glaze | 429.741 | 0.532007 | 1885.93ms | 3873 | 640 | 1.33812e+06 | 8594.9 | 5.73623 | 2(Loss) |
| simdjson (reflection) | 289.833 | 0.0912097 | 2318.18ms | 3873 | 30 | 4053.25 | 12743.8 | 8.51674 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 451.681 | 0.160758 | 6629.77ms | 2090234 | 30 | 1.51006e+09 | 4.4133e+06 | 5.48116 | 1(Win) |
| glaze | 347.675 | 0.099022 | 8597.38ms | 2090234 | 40 | 1.28934e+09 | 5.73353e+06 | 7.12084 | 2(Loss) |
| simdjson (ondemand) | 346.14 | 0.104337 | 8675.76ms | 2090234 | 40 | 1.4442e+09 | 5.75894e+06 | 7.1523 | 3(Loss) |
| simdjson (reflection) | 331.035 | 0.07142 | 9069.7ms | 2090234 | 80 | 1.47969e+09 | 6.02173e+06 | 7.47874 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1098.41 | 0.0704392 | 5667.64ms | 2090234 | 80 | 1.30731e+08 | 1.81481e+06 | 2.25363 | 1(Win) |
| glaze | 719.482 | 0.0492173 | 8614.98ms | 2090234 | 80 | 1.48757e+08 | 2.77061e+06 | 3.44095 | 2(Loss) |
| simdjson (reflection) | 484.437 | 0.0563453 | 6198ms | 2090326 | 40 | 2.15045e+08 | 4.11507e+06 | 5.11048 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1186.46 | 0.0753528 | 8095.6ms | 6661897 | 30 | 4.88442e+08 | 5.35484e+06 | 2.08661 | 1(Win) |
| simdjson (ondemand) | 1014.51 | 0.0913718 | 9410.54ms | 6661897 | 40 | 1.30968e+09 | 6.2624e+06 | 2.44024 | 2(Loss) |
| simdjson (reflection) | 976.971 | 0.0424592 | 9823.4ms | 6661897 | 30 | 2.28716e+08 | 6.50304e+06 | 2.53408 | 3(Loss) |
| glaze | 887.046 | 0.0626432 | 5013.99ms | 6661897 | 40 | 8.05214e+08 | 7.16229e+06 | 2.79098 | 4(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3232.31 | 0.0885677 | 6165.26ms | 6661897 | 40 | 1.21222e+08 | 1.96555e+06 | 0.7659 | 1(Win) |
| glaze | 1289.5 | 0.0914246 | 7448.76ms | 6661897 | 30 | 6.08699e+08 | 4.92695e+06 | 1.91989 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 935.144 | 0.123468 | 6627.63ms | 500299 | 320 | 1.26988e+08 | 510212 | 2.6469 | 1(Win) |
| jsonifier | 904.598 | 0.0916014 | 6852.39ms | 500299 | 640 | 1.49394e+08 | 527441 | 2.73633 | 2(Loss) |
| simdjson (reflection) | 674.002 | 0.211826 | 9232.04ms | 500299 | 30 | 6.74556e+07 | 707895 | 3.67256 | 3(Loss) |
| simdjson (ondemand) | 662.131 | 0.188716 | 9291.83ms | 500299 | 80 | 1.47937e+08 | 720586 | 3.7383 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5873.61 | 0.302805 | 9251.76ms | 500299 | 1280 | 7.74438e+07 | 81231.5 | 0.421135 | 1(Win) |
| simdjson (reflection) | 2997.73 | 0.120602 | 8692.64ms | 500299 | 2560 | 9.43239e+07 | 159161 | 0.825342 | 2(Loss) |
| glaze | 2281.4 | 0.299975 | 5598.29ms | 500299 | 320 | 1.25944e+08 | 209136 | 1.08473 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2023.86 | 0.156007 | 8774.69ms | 1439562 | 160 | 1.79188e+08 | 678343 | 1.22306 | 1(Win) |
| simdjson (reflection) | 1647.29 | 0.194342 | 5364.11ms | 1439562 | 80 | 2.09867e+08 | 833412 | 1.50265 | 2(Loss) |
| simdjson (ondemand) | 1633.38 | 0.0601192 | 5373.05ms | 1439562 | 320 | 8.17078e+07 | 840511 | 1.51546 | 3(Loss) |
| glaze | 1512.7 | 0.080238 | 5793.34ms | 1439562 | 160 | 8.48471e+07 | 907566 | 1.63639 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12924.9 | 0.163778 | 5997.79ms | 1439562 | 2560 | 7.74738e+07 | 106219 | 0.191446 | 1(Win) |
| glaze | 1821.98 | 0.130458 | 9810.04ms | 1439584 | 80 | 7.73072e+07 | 753518 | 1.35869 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 969.814 | 0.199382 | 6539.84ms | 56369 | 4890 | 5.97288e+07 | 55430.9 | 2.55076 | 1(Win) |
| glaze | 960.957 | 0.201572 | 6604.48ms | 56369 | 4890 | 6.21785e+07 | 55941.8 | 2.57437 | 2(Loss) |
| simdjson (reflection) | 755.904 | 0.165495 | 8125.05ms | 56369 | 4890 | 6.77372e+07 | 71117 | 3.27302 | 3(Loss) |
| simdjson (ondemand) | 746.658 | 0.42232 | 8240.93ms | 56369 | 640 | 5.91698e+07 | 71997.7 | 3.31308 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5641.64 | 0.0800508 | 2048.63ms | 56369 | 30 | 1745.51 | 9528.73 | 0.437277 | 1(Win) |
| simdjson (reflection) | 4247.44 | 2.01438 | 2331.84ms | 56369 | 40 | 2.59997e+06 | 12656.5 | 0.581159 | 2(Loss) |
| glaze | 2439.53 | 0.671282 | 3188.61ms | 56369 | 2560 | 5.6017e+07 | 22036.1 | 1.01309 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1400.09 | 0.262676 | 7421.96ms | 94370 | 2560 | 7.29857e+07 | 64280.3 | 1.76695 | 1(Win) |
| glaze | 1244.03 | 0.294896 | 8304.27ms | 94370 | 1280 | 5.82582e+07 | 72344.3 | 1.98889 | 2(Loss) |
| simdjson (reflection) | 1174.78 | 0.274883 | 8674.05ms | 94370 | 1280 | 5.67627e+07 | 76608.7 | 2.10631 | 3(Loss) |
| simdjson (ondemand) | 1148.18 | 0.159964 | 8826.12ms | 94370 | 4890 | 7.68786e+07 | 78383.6 | 2.15451 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8431.14 | 0.110568 | 2168.67ms | 94370 | 40 | 5572.05 | 10674.5 | 0.292455 | 1(Win) |
| glaze | 1407.69 | 0.25046 | 7382.13ms | 94370 | 2560 | 6.56404e+07 | 63933.3 | 1.75755 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 978.414 | 0.13457 | 2236.27ms | 11812 | 40 | 9601.87 | 11513.3 | 2.52241 | 1(Win) |
| jsonifier | 776.601 | 2.0524 | 2532.22ms | 11812 | 30 | 2.65887e+06 | 14505.3 | 3.17986 | 2(Loss) |
| simdjson (reflection) | 625.938 | 0.63992 | 2794.26ms | 11812 | 4890 | 6.48551e+07 | 17996.7 | 3.94428 | 3(Loss) |
| simdjson (ondemand) | 566.134 | 0.573583 | 3031.29ms | 11812 | 4890 | 6.36957e+07 | 19897.8 | 4.36476 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4111.73 | 0.275282 | 1336.41ms | 11812 | 160 | 9100.67 | 2739.68 | 0.593747 | 1(Win) |
| simdjson (reflection) | 3025.31 | 0.0642726 | 1439.93ms | 11812 | 640 | 3665.54 | 3723.51 | 0.809924 | 2(Loss) |
| glaze | 1784.42 | 3.9249 | 1629.4ms | 11812 | 4890 | 3.00205e+08 | 6312.86 | 1.37875 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1786.98 | 1.73581 | 2669.13ms | 31235 | 4890 | 4.09407e+08 | 16669.5 | 1.38224 | 1(Win) |
| simdjson (reflection) | 1483.55 | 0.962065 | 3023.03ms | 31235 | 1280 | 4.77638e+07 | 20078.9 | 1.66565 | 2(Loss) |
| glaze | 1435.94 | 0.595166 | 3071.4ms | 31235 | 4890 | 7.45413e+07 | 20744.6 | 1.72098 | 3(Loss) |
| simdjson (ondemand) | 1341.49 | 0.731273 | 3237.45ms | 31235 | 2560 | 6.75007e+07 | 22205.2 | 1.84236 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9580.84 | 0.23488 | 1401.15ms | 31235 | 40 | 2133.19 | 3109.12 | 0.255339 | 1(Win) |
| glaze | 1383.92 | 0.752119 | 3134.76ms | 31235 | 2560 | 6.70922e+07 | 21524.3 | 1.78578 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1593.99 | 0.388663 | 7470.31ms | 108313 | 1280 | 8.1198e+07 | 64802.9 | 1.55219 | 1(Win) |
| glaze | 967.863 | 0.147257 | 5994.91ms | 108313 | 2560 | 6.32299e+07 | 106725 | 2.55695 | 2(Loss) |
| simdjson (reflection) | 886.079 | 0.215993 | 6478.11ms | 108313 | 1280 | 8.11535e+07 | 116576 | 2.79288 | 3(Loss) |
| simdjson (ondemand) | 706.348 | 0.190497 | 7971.2ms | 108313 | 1280 | 9.93368e+07 | 146239 | 3.5036 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7968.68 | 0.693295 | 2400.78ms | 108313 | 160 | 1.29224e+06 | 12962.7 | 0.309763 | 1(Win) |
| simdjson (reflection) | 4661.51 | 0.548138 | 3238.89ms | 108313 | 4890 | 7.21433e+07 | 22159.2 | 0.530152 | 2(Loss) |
| glaze | 1420.51 | 0.158904 | 8268.79ms | 108313 | 4890 | 6.52909e+07 | 72717.1 | 1.74183 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1768.38 | 0.170968 | 6424.78ms | 213963 | 2560 | 9.96324e+07 | 115389 | 1.39935 | 1(Win) |
| simdjson (reflection) | 1575.5 | 0.252105 | 7143.36ms | 213963 | 640 | 6.82314e+07 | 129515 | 1.57076 | 2(Loss) |
| glaze | 1388.95 | 0.133217 | 8013.69ms | 213963 | 2560 | 9.80532e+07 | 146910 | 1.78185 | 3(Loss) |
| simdjson (ondemand) | 1296.3 | 0.31384 | 8617.97ms | 213963 | 320 | 7.80964e+07 | 157410 | 1.90917 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14125.1 | 0.202744 | 2581.95ms | 213963 | 40 | 34312 | 14446 | 0.174826 | 1(Win) |
| glaze | 1165.33 | 0.0946762 | 9486.03ms | 213963 | 2560 | 7.03556e+07 | 175101 | 2.12374 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 414.611 | 0.497862 | 6360.19ms | 1834197 | 80 | 3.52955e+10 | 4.21896e+06 | 5.97116 | 1(Win) |
| glaze | 343.833 | 0.687666 | 7670.82ms | 1834197 | 30 | 3.67176e+10 | 5.08743e+06 | 7.20034 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 308.229 | 0.160595 | 8618.26ms | 1834197 | 30 | 2.49191e+09 | 5.67509e+06 | 8.03193 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 306.079 | 0.80172 | 8562ms | 1834197 | 30 | 6.29784e+10 | 5.71495e+06 | 8.08833 | 3(Tie) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 700.617 | 0.147266 | 7817.59ms | 1834197 | 30 | 4.05563e+08 | 2.4967e+06 | 3.53351 | 1(Win) |
| glaze | 361.87 | 0.0542477 | 7317.77ms | 1833577 | 40 | 2.74862e+08 | 4.83221e+06 | 6.84146 | 2(Loss) |
| simdjson (reflection) | 295.781 | 0.133844 | 9351.49ms | 1922245 | 80 | 5.50512e+09 | 6.19782e+06 | 8.37003 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1665.43 | 0.159332 | 8528.62ms | 9930848 | 40 | 3.28388e+09 | 5.6867e+06 | 1.48641 | 1(Win) |
| simdjson (ondemand) | 1422.05 | 0.151651 | 10134.9ms | 9930848 | 80 | 8.16054e+09 | 6.65994e+06 | 1.74089 | 2(Loss) |
| simdjson (reflection) | 1406.26 | 0.112662 | 10198.2ms | 9930848 | 30 | 1.72711e+09 | 6.73475e+06 | 1.76046 | 3(Loss) |
| glaze | 1299.03 | 0.099688 | 5067.59ms | 9930848 | 30 | 1.58469e+09 | 7.29068e+06 | 1.90573 | 4(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 419.997 | 0.106862 | 6309.83ms | 1834197 | 80 | 1.58467e+09 | 4.16485e+06 | 5.89461 | 1(Win) |
| glaze | 336.808 | 0.122467 | 7830.62ms | 1834197 | 40 | 1.61817e+09 | 5.19355e+06 | 7.35026 | 2(Loss) |
| simdjson (reflection) | 307.248 | 0.087094 | 8615.93ms | 1834197 | 30 | 7.37583e+08 | 5.6932e+06 | 8.0576 | 3(Loss) |
| simdjson (ondemand) | 305.991 | 0.167763 | 8576.73ms | 1834197 | 40 | 3.67895e+09 | 5.71659e+06 | 8.09056 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 698.231 | 0.0690577 | 7821.53ms | 1834197 | 40 | 1.19723e+08 | 2.50523e+06 | 3.54568 | 1(Win) |
| glaze | 354.114 | 0.042062 | 7478.18ms | 1833577 | 80 | 3.4513e+08 | 4.93805e+06 | 6.99132 | 2(Loss) |
| simdjson (reflection) | 298.464 | 0.268555 | 9218.5ms | 1922245 | 30 | 8.16249e+09 | 6.1421e+06 | 8.29468 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1698.51 | 0.127771 | 8369.83ms | 9930848 | 80 | 4.06059e+09 | 5.57595e+06 | 1.45749 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1408.16 | 0.110318 | 10191.5ms | 9930848 | 40 | 2.20202e+09 | 6.72567e+06 | 1.75808 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1406.29 | 0.099397 | 10201.6ms | 9930848 | 40 | 1.79239e+09 | 6.73461e+06 | 1.76042 | 2(Tie) |
| glaze | 1319.3 | 0.125453 | 5069.27ms | 9930848 | 40 | 3.24417e+09 | 7.17863e+06 | 1.87649 | 4(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3471.55 | 0.1538 | 8497.6ms | 9930848 | 80 | 1.4084e+09 | 2.72812e+06 | 0.713132 | 1(Win) |
| glaze | 1041.43 | 0.245528 | 6356.32ms | 9930228 | 40 | 1.994e+10 | 9.0935e+06 | 2.37719 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 639.755 | 0.116481 | 6146.34ms | 642697 | 160 | 1.99259e+08 | 958060 | 3.86941 | 1(Win) |
| jsonifier | 620.941 | 0.187777 | 6381.81ms | 642697 | 80 | 2.74843e+08 | 987088 | 3.98662 | 2(Loss) |
| simdjson (reflection) | 587.354 | 0.172006 | 6596.34ms | 642697 | 80 | 2.57745e+08 | 1.04353e+06 | 4.21463 | 3(Loss) |
| simdjson (ondemand) | 572.889 | 0.1695 | 6831.87ms | 642697 | 40 | 1.31544e+08 | 1.06988e+06 | 4.32105 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1173.93 | 0.145158 | 6818.57ms | 642697 | 160 | 9.19028e+07 | 522111 | 2.10859 | 1(Win) |
| simdjson (reflection) | 575.723 | 0.136502 | 6798ms | 643373 | 40 | 8.46513e+07 | 1.06573e+06 | 4.29974 | 2(Loss) |
| glaze | 570.987 | 0.0621034 | 6837.94ms | 642692 | 320 | 1.42211e+08 | 1.07344e+06 | 4.33553 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 1076.76 | 0.156843 | 6959.58ms | 1225964 | 30 | 8.70099e+07 | 1.08582e+06 | 2.29907 | 1(Win) |
| simdjson (ondemand) | 1045.49 | 0.0847813 | 7109.7ms | 1225964 | 160 | 1.43824e+08 | 1.11829e+06 | 2.36779 | 2(Loss) |
| glaze | 973.18 | 0.0728347 | 7654.46ms | 1225964 | 320 | 2.45017e+08 | 1.20139e+06 | 2.54367 | 3(Loss) |
| jsonifier | 923.915 | 0.0714623 | 8088.64ms | 1225964 | 320 | 2.61695e+08 | 1.26545e+06 | 2.67941 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2304.71 | 0.139559 | 6584.81ms | 1225964 | 320 | 1.60393e+08 | 507296 | 1.07406 | 1(Win) |
| glaze | 954.371 | 0.0885225 | 7814.9ms | 1225970 | 80 | 9.40855e+07 | 1.22507e+06 | 2.59391 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 691.459 | 0.106876 | 7389.66ms | 409725 | 320 | 1.16726e+08 | 565101 | 3.57993 | 1(Win) |
| simdjson (ondemand) | 604.061 | 0.11645 | 8432.61ms | 409725 | 160 | 9.07861e+07 | 646862 | 4.09795 | 2(Loss) |
| glaze | 594.166 | 0.162036 | 8491ms | 409725 | 320 | 3.63363e+08 | 657635 | 4.16614 | 3(Loss) |
| simdjson (reflection) | 582.023 | 0.0631664 | 8684.43ms | 409725 | 640 | 1.15095e+08 | 671356 | 4.25308 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3116.85 | 0.120226 | 6953.77ms | 409725 | 2560 | 5.81558e+07 | 125365 | 0.793863 | 1(Win) |
| simdjson (reflection) | 3008.63 | 0.20137 | 7190.11ms | 409725 | 1280 | 8.75481e+07 | 129875 | 0.82242 | 2(Loss) |
| glaze | 1747.86 | 0.144648 | 5971.06ms | 409725 | 1280 | 1.33847e+08 | 223556 | 1.41596 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1135.72 | 0.0938027 | 8527.43ms | 785750 | 640 | 2.45152e+08 | 659800 | 2.17956 | 1(Win) |
| simdjson (ondemand) | 1076.78 | 0.067971 | 9078.36ms | 785750 | 640 | 1.432e+08 | 695919 | 2.29884 | 2(Loss) |
| simdjson (reflection) | 1035.26 | 0.276764 | 9367.06ms | 785750 | 40 | 1.60527e+08 | 723826 | 2.39113 | 3(Loss) |
| glaze | 948.718 | 0.234128 | 5064.49ms | 785750 | 30 | 1.02594e+08 | 789855 | 2.6093 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5513.57 | 0.167087 | 7505.93ms | 785750 | 1280 | 6.60086e+07 | 135910 | 0.448768 | 1(Win) |
| glaze | 1151.09 | 0.0793242 | 8397.48ms | 785750 | 320 | 8.5332e+07 | 650992 | 2.15049 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 2824.3 | 0.304674 | 5057.43ms | 264040 | 640 | 4.72245e+07 | 89157.7 | 0.876161 | 1(Win) |
| simdjson (ondemand) | 2798.47 | 0.138541 | 5148.52ms | 264040 | 2560 | 3.97826e+07 | 89980.8 | 0.884296 | 2(Loss) |
| jsonifier | 2694.24 | 0.221091 | 5289.98ms | 264040 | 1280 | 5.46539e+07 | 93461.7 | 0.918498 | 3(Loss) |
| glaze | 1275.55 | 0.0956835 | 5291.83ms | 264040 | 1280 | 4.56698e+07 | 197412 | 1.94052 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 3633.36 | 0.121581 | 5884.65ms | 399947 | 2560 | 4.17025e+07 | 104977 | 0.681035 | 1(Win) |
| simdjson (ondemand) | 3587.71 | 0.134778 | 5958.95ms | 399947 | 2560 | 5.25589e+07 | 106313 | 0.689727 | 2(Loss) |
| jsonifier | 3438.2 | 0.139481 | 6206.65ms | 399947 | 2560 | 6.1293e+07 | 110936 | 0.719699 | 3(Loss) |
| glaze | 1615.04 | 0.16912 | 6293.76ms | 399947 | 320 | 5.10477e+07 | 236167 | 1.53267 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1137 | 0.228793 | 5931.8ms | 264040 | 320 | 8.21579e+07 | 221466 | 2.17665 | 1(Win) |
| glaze | 945.177 | 0.357058 | 6688.58ms | 264040 | 80 | 7.23904e+07 | 266414 | 2.61859 | 2(Loss) |
| simdjson (reflection) | 782.769 | 0.0958742 | 8447.48ms | 264040 | 1280 | 1.21755e+08 | 321689 | 3.16202 | 3(Loss) |
| simdjson (ondemand) | 643.788 | 0.157714 | 5103.67ms | 264040 | 320 | 1.2177e+08 | 391135 | 3.84461 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5849.43 | 0.499203 | 5324.14ms | 264040 | 1280 | 5.91121e+07 | 43048.3 | 0.422621 | 1(Win) |
| simdjson (reflection) | 4132.89 | 0.290225 | 7183.17ms | 264040 | 1280 | 4.00232e+07 | 60927.9 | 0.598236 | 2(Loss) |
| glaze | 3002.95 | 0.226438 | 9500.43ms | 263923 | 1280 | 4.61069e+07 | 83816.5 | 0.823703 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 1175.61 | 0.0921965 | 8592.08ms | 399947 | 1280 | 1.14529e+08 | 324443 | 2.10549 | 1(Win) |
| glaze | 1079.89 | 0.127094 | 9290.72ms | 399947 | 640 | 1.28965e+08 | 353201 | 2.2917 | 2(Loss) |
| jsonifier | 1019.74 | 0.318812 | 9843.41ms | 399947 | 80 | 1.13758e+08 | 374035 | 2.42664 | 3(Loss) |
| simdjson (ondemand) | 933.473 | 0.100208 | 5330.44ms | 399947 | 640 | 1.07298e+08 | 408602 | 2.65156 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7961.35 | 0.194726 | 5829.7ms | 399947 | 4890 | 4.25585e+07 | 47908.8 | 0.310563 | 1(Win) |
| glaze | 1651.39 | 0.0989077 | 6188.68ms | 399830 | 1280 | 6.67608e+07 | 230901 | 1.49846 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 644.196 | 1.04567 | 1710.38ms | 4630 | 320 | 1.64387e+06 | 6854.3 | 3.82201 | 1(Win) |
| glaze STATISTICAL TIE | 423.121 | 2.36018 | 2040.36ms | 4630 | 4890 | 2.96642e+08 | 10435.6 | 5.83006 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 420.628 | 0.112244 | 2117.87ms | 4630 | 30 | 4165.01 | 10497.4 | 5.86638 | 2(Tie) |
| simdjson (reflection) | 397.92 | 0.119316 | 2170.46ms | 4630 | 40 | 7011.79 | 11096.5 | 6.20224 | 4(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1090.4 | 0.220255 | 1416.66ms | 4630 | 40 | 3181.99 | 4049.43 | 2.24987 | 1(Win) |
| glaze | 702.753 | 0.0719346 | 1645.47ms | 4630 | 80 | 1634.26 | 6283.16 | 3.50186 | 2(Loss) |
| simdjson (reflection) | 502.978 | 0.0741315 | 1922.63ms | 4630 | 30 | 1270.55 | 8778.73 | 4.90013 | 3(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1548.9 | 0.0813685 | 1966.18ms | 14795 | 80 | 4395.29 | 9109.45 | 1.59176 | 1(Win) |
| simdjson (ondemand) | 1188.52 | 0.159208 | 2258.4ms | 14795 | 40 | 14289.2 | 11871.6 | 2.076 | 2(Loss) |
| simdjson (reflection) | 1064.78 | 0.763146 | 2311.53ms | 14795 | 4890 | 5.00079e+07 | 13251.3 | 2.31629 | 3(Loss) |
| glaze | 979.789 | 0.808316 | 2414.99ms | 14795 | 4890 | 6.62577e+07 | 14400.7 | 2.52002 | 4(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2887.05 | 0.0948574 | 1503.54ms | 14795 | 40 | 859.651 | 4887.2 | 0.85047 | 1(Win) |
| glaze | 1288.42 | 0.097295 | 2154.52ms | 14795 | 80 | 9082.17 | 10951.1 | 1.91501 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 799.595 | 0.166678 | 1662.99ms | 5092 | 80 | 8197.56 | 6073.21 | 3.0762 | 1(Win) |
| glaze | 763.296 | 0.388047 | 1700.36ms | 5092 | 640 | 390068 | 6362.02 | 3.22441 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 605.07 | 0.296135 | 1841.73ms | 5092 | 30 | 16945.9 | 8025.7 | 4.07088 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 598.632 | 0.561948 | 1856.4ms | 5092 | 1280 | 2.65987e+06 | 8112.02 | 4.11569 | 3(Tie) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3795.68 | 0.23598 | 1152.32ms | 5092 | 1280 | 11667 | 1279.38 | 0.632775 | 1(Win) |
| simdjson (reflection) | 2450.11 | 0.328551 | 1223.82ms | 5092 | 30 | 1272.14 | 1982 | 0.991254 | 2(Loss) |
| glaze | 1523.97 | 0.193035 | 1336.45ms | 5092 | 160 | 6053.64 | 3186.49 | 1.60458 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1264.01 | 2.51597 | 1884.19ms | 11724 | 4890 | 2.42197e+08 | 8845.55 | 1.95019 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1262.61 | 0.139593 | 1929.27ms | 11724 | 80 | 12224.4 | 8855.34 | 1.95219 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1254.5 | 0.24279 | 1950.29ms | 11724 | 80 | 37459.8 | 8912.65 | 1.96472 | 1(Tie) |
| glaze | 1150.45 | 0.490333 | 2043.13ms | 11724 | 80 | 181674 | 9718.74 | 2.14333 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8244.71 | 0.262567 | 1143.49ms | 11724 | 320 | 4057.26 | 1356.13 | 0.292033 | 1(Win) |
| glaze | 1372.68 | 0.384826 | 1851.77ms | 11746 | 640 | 631171 | 8160.55 | 1.7954 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 916.892 | 0.644628 | 1524.5ms | 4857 | 640 | 678731 | 5051.85 | 2.68003 | 1(Win) |
| jsonifier | 818.128 | 0.274755 | 1593.09ms | 4857 | 160 | 38717.4 | 5661.7 | 3.00362 | 2(Loss) |
| simdjson (reflection) | 673.137 | 0.433635 | 1715.24ms | 4857 | 640 | 569845 | 6881.21 | 3.65803 | 3(Loss) |
| simdjson (ondemand) | 630.086 | 0.529795 | 1763.83ms | 4857 | 80 | 121351 | 7351.38 | 3.90937 | 4(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3206.93 | 0.505615 | 1169.43ms | 4857 | 160 | 8533.28 | 1444.37 | 0.752211 | 1(Win) |
| simdjson (reflection) | 3131.47 | 0.3307 | 1163.98ms | 4857 | 40 | 957.122 | 1479.17 | 0.770311 | 2(Loss) |
| glaze | 2062.45 | 0.269865 | 1241.12ms | 4857 | 40 | 1469.34 | 2245.88 | 1.17969 | 3(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1108.67 | 0.275531 | 1666.3ms | 7376 | 80 | 24449.2 | 6344.79 | 2.2197 | 1(Win) |
| jsonifier | 1005.25 | 0.221227 | 1748.29ms | 7376 | 80 | 19171.8 | 6997.59 | 2.44666 | 2(Loss) |
| simdjson (reflection) | 983.99 | 0.257172 | 1750.4ms | 7376 | 40 | 13519.7 | 7148.75 | 2.50324 | 3(Loss) |
| simdjson (ondemand) | 902.978 | 0.348221 | 1794.06ms | 7376 | 160 | 117738 | 7790.11 | 2.72829 | 4(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4883.66 | 0.333881 | 1161.76ms | 7376 | 40 | 925.112 | 1440.38 | 0.49314 | 1(Win) |
| glaze | 1442.2 | 0.414316 | 1511.51ms | 7376 | 640 | 261358 | 4877.49 | 1.70342 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 961.957 | 0.408181 | 1436.6ms | 4390 | 30 | 9467.68 | 4352.2 | 2.55183 | 1(Win) |
| jsonifier | 785.681 | 0.169971 | 1536.39ms | 4390 | 30 | 2460.99 | 5328.67 | 3.12948 | 2(Loss) |
| simdjson (reflection) | 657.156 | 0.61376 | 1658.95ms | 4390 | 640 | 978520 | 6370.83 | 3.74459 | 3(Loss) |
| simdjson (ondemand) | 594.156 | 0.585674 | 1709.98ms | 4390 | 640 | 1.08998e+06 | 7046.35 | 4.1445 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3651.45 | 0.57274 | 1122.98ms | 4390 | 30 | 1293.7 | 1146.57 | 0.654837 | 1(Win) |
| simdjson (reflection) | 2607.36 | 0.44551 | 1160.27ms | 4390 | 40 | 2046.93 | 1605.7 | 0.926583 | 2(Loss) |
| glaze | 1865.98 | 0.20442 | 1217.68ms | 4390 | 160 | 3365.76 | 2243.67 | 1.30304 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1868.45 | 0.283937 | 1604.82ms | 11521 | 80 | 22302.3 | 5880.41 | 1.31662 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 1504.06 | 1.13655 | 1737.75ms | 11521 | 1280 | 8.82341e+06 | 7305.06 | 1.6373 | 2(Tie) |
| glaze STATISTICAL TIE | 1502.76 | 0.217708 | 1747.19ms | 11521 | 40 | 10134.8 | 7311.43 | 1.63896 | 2(Tie) |
| simdjson (ondemand) | 1410.94 | 0.106278 | 1795.93ms | 11521 | 40 | 2739.75 | 7787.2 | 1.74576 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8561.96 | 0.689713 | 1144.69ms | 11521 | 30 | 2350.13 | 1283.27 | 0.28089 | 1(Win) |
| glaze | 1448.57 | 0.495678 | 1760.37ms | 11521 | 640 | 904653 | 7584.92 | 1.7007 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1358.87 | 0.213728 | 1354.16ms | 4669 | 160 | 7847.55 | 3276.76 | 1.80156 | 1(Win) |
| glaze | 950.615 | 0.274275 | 1502.75ms | 4669 | 80 | 13203.8 | 4684.02 | 2.58329 | 2(Loss) |
| simdjson (reflection) | 851.096 | 0.455195 | 1563.89ms | 4669 | 160 | 90741.7 | 5231.73 | 2.888 | 3(Loss) |
| simdjson (ondemand) | 652.542 | 0.488721 | 1714.28ms | 4669 | 640 | 711759 | 6823.63 | 3.77308 | 4(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5446.73 | 0.259657 | 1106.71ms | 4669 | 640 | 2883.74 | 817.5 | 0.433502 | 1(Win) |
| simdjson (reflection) | 3135.15 | 0.315407 | 1164.23ms | 4669 | 320 | 6421.34 | 1420.25 | 0.768943 | 2(Loss) |
| glaze | 1260.08 | 0.236606 | 1376.46ms | 4669 | 30 | 2097.13 | 3533.67 | 1.94364 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9766.04 | 0.292658 | 1132.47ms | 9249 | 4890 | 34165.2 | 903.184 | 0.242887 | 1(Win) |
| glaze | 1111.36 | 0.161488 | 1833.64ms | 9249 | 80 | 13141.6 | 7936.68 | 2.21723 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 429.498 | 0.928674 | 2014.64ms | 4604 | 4890 | 4.40741e+07 | 10222.9 | 5.73467 | 1(Win) |
| glaze | 366.901 | 0.136608 | 2234.45ms | 4604 | 80 | 21380.4 | 11967 | 6.7266 | 2(Loss) |
| simdjson (ondemand) | 322.185 | 0.405701 | 2430.85ms | 4604 | 30 | 91705.3 | 13627.9 | 7.66277 | 3(Loss) |
| simdjson (reflection) | 300.709 | 0.95444 | 2476.95ms | 4604 | 2560 | 4.97182e+07 | 14601.2 | 8.21118 | 4(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 887.329 | 0.336611 | 1549.21ms | 4604 | 1280 | 355114 | 4948.24 | 2.76893 | 1(Win) |
| glaze | 497 | 0.220378 | 1929.39ms | 4604 | 30 | 11371.4 | 8834.43 | 4.96112 | 2(Loss) |
| simdjson (reflection) | 366.984 | 0.819577 | 2276.46ms | 4918 | 4890 | 5.36502e+07 | 12780.3 | 6.72612 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1549.97 | 2.32115 | 2545.32ms | 24579 | 320 | 3.94311e+07 | 15123.1 | 1.59269 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1410.43 | 0.952736 | 2665.52ms | 24579 | 2560 | 6.4182e+07 | 16619.3 | 1.751 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1391.2 | 0.611067 | 2688.01ms | 24579 | 4890 | 5.18365e+07 | 16849 | 1.77546 | 2(Tie) |
| glaze | 1186.1 | 0.837019 | 2957.73ms | 24579 | 4890 | 1.33804e+08 | 19762.6 | 2.08325 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4138.92 | 0.233121 | 1644.86ms | 24579 | 40 | 6972.3 | 5663.4 | 0.594465 | 1(Win) |
| glaze | 1335.64 | 0.615083 | 2756.17ms | 24579 | 4890 | 5.69803e+07 | 17549.9 | 1.84962 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 527.318 | 0.368667 | 1871.58ms | 4604 | 640 | 603080 | 8326.51 | 4.6737 | 1(Win) |
| glaze | 363.022 | 0.251892 | 2314.25ms | 4604 | 30 | 27845.5 | 12094.9 | 6.79874 | 2(Loss) |
| simdjson (reflection) | 322.12 | 0.246734 | 2466.01ms | 4604 | 40 | 45243.3 | 13630.7 | 7.66447 | 3(Loss) |
| simdjson (ondemand) | 305.312 | 0.70246 | 2473.58ms | 4604 | 4890 | 4.9904e+07 | 14381.1 | 8.087 | 4(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 894.29 | 0.249949 | 1546.74ms | 4604 | 80 | 12047.8 | 4909.73 | 2.74718 | 1(Win) |
| glaze | 489.669 | 0.335487 | 1956.66ms | 4604 | 40 | 36197.2 | 8966.7 | 5.03326 | 2(Loss) |
| simdjson (reflection) | 395.948 | 0.195056 | 2270.32ms | 4918 | 30 | 16015.5 | 11845.4 | 6.23267 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1716.55 | 0.911792 | 2396.64ms | 24579 | 2560 | 3.96871e+07 | 13655.5 | 1.43788 | 1(Win) |
| simdjson (ondemand) | 1483.86 | 0.199656 | 2712.53ms | 24579 | 80 | 79578.9 | 15796.9 | 1.66414 | 2(Loss) |
| simdjson (reflection) | 1427.15 | 1.04128 | 2665.61ms | 24579 | 1280 | 3.74396e+07 | 16424.6 | 1.73066 | 3(Loss) |
| glaze | 1188.96 | 1.02834 | 2973.49ms | 24579 | 1280 | 5.26112e+07 | 19715 | 2.07826 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4180.61 | 0.115876 | 1621.6ms | 24579 | 40 | 1688.48 | 5606.93 | 0.588144 | 1(Win) |
| glaze | 1350.42 | 0.579589 | 2748.48ms | 24579 | 4890 | 4.94927e+07 | 17357.9 | 1.82937 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 578.306 | 0.629243 | 1233.31ms | 1181 | 30 | 4505.5 | 1947.57 | 4.19317 | 1(Win) |
| glaze | 478.356 | 0.193227 | 1319.09ms | 1181 | 30 | 620.948 | 2354.5 | 5.09359 | 2(Loss) |
| simdjson (ondemand) | 408.054 | 0.265781 | 1321.15ms | 1181 | 40 | 2152.64 | 2760.15 | 5.98374 | 3(Loss) |
| simdjson (reflection) | 402.494 | 0.40716 | 1349.97ms | 1181 | 2560 | 332315 | 2798.28 | 6.06611 | 4(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1149.53 | 0.24685 | 1101.1ms | 1181 | 640 | 3743.73 | 979.78 | 2.07009 | 1(Win) |
| simdjson (reflection) | 617.919 | 0.224768 | 1181.55ms | 1187 | 80 | 1356.43 | 1831.97 | 3.92437 | 2(Loss) |
| glaze | 508.862 | 0.239611 | 1228.9ms | 1181 | 80 | 2250.1 | 2213.35 | 4.78116 | 3(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 874.136 | 0.428392 | 1297.94ms | 2496 | 80 | 10886.9 | 2723.11 | 2.79206 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 830.38 | 0.2021 | 1298.32ms | 2496 | 160 | 5370.19 | 2866.61 | 2.94258 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 819.017 | 0.89374 | 1293.57ms | 2496 | 40 | 26989 | 2906.38 | 2.98333 | 2(Tie) |
| glaze | 812.788 | 0.269149 | 1300.27ms | 2496 | 4890 | 303830 | 2928.65 | 3.00723 | 4(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2310.07 | 0.444642 | 1118.59ms | 2496 | 30 | 629.771 | 1030.43 | 1.03056 | 1(Win) |
| glaze | 740.258 | 0.215191 | 1347.06ms | 2507 | 30 | 1449.15 | 3229.77 | 3.30488 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 801.038 | 0.294459 | 1627.57ms | 4926 | 1280 | 381717 | 5864.64 | 3.07101 | 1(Win) |
| glaze | 679.959 | 0.311562 | 1708.8ms | 4926 | 40 | 18534.2 | 6908.95 | 3.62092 | 2(Loss) |
| simdjson (ondemand) | 639.441 | 0.12889 | 1780.91ms | 4926 | 80 | 7173.24 | 7346.73 | 3.85309 | 3(Loss) |
| simdjson (reflection) | 628.621 | 0.122989 | 1771.99ms | 4926 | 80 | 6758.26 | 7473.19 | 3.91801 | 4(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2976.81 | 0.578015 | 1184.09ms | 4926 | 160 | 13313.3 | 1578.13 | 0.811543 | 1(Win) |
| simdjson (reflection) | 2827.7 | 0.2545 | 1172.55ms | 4926 | 640 | 11441.3 | 1661.35 | 0.855442 | 2(Loss) |
| glaze | 1664.85 | 0.499645 | 1283.67ms | 4926 | 40 | 7950.96 | 2821.75 | 1.46771 | 3(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1344 | 0.0830959 | 1718.84ms | 9463 | 160 | 4981.25 | 6714.74 | 1.83163 | 1(Win) |
| simdjson (ondemand) | 1154.91 | 0.240487 | 1821.52ms | 9463 | 40 | 14125.4 | 7814.1 | 2.13326 | 2(Loss) |
| simdjson (reflection) | 1140.81 | 0.125765 | 1808.81ms | 9463 | 160 | 15836.8 | 7910.69 | 2.16017 | 3(Loss) |
| glaze | 1087.97 | 0.540515 | 1838.97ms | 9463 | 30 | 60305.8 | 8294.9 | 2.26553 | 4(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5449.43 | 0.415518 | 1168.39ms | 9463 | 30 | 1420.55 | 1656.07 | 0.444095 | 1(Win) |
| glaze | 1143.9 | 0.396355 | 1797.6ms | 9463 | 320 | 312895 | 7889.33 | 2.15408 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) STATISTICAL TIE | 2519.17 | 0.220754 | 1119.44ms | 2821 | 320 | 1778.52 | 1067.94 | 0.947782 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2502.1 | 0.400784 | 1126.32ms | 2821 | 160 | 2971.26 | 1075.22 | 0.955415 | 1(Tie) |
| jsonifier | 2114.57 | 0.273533 | 1146.55ms | 2821 | 80 | 968.885 | 1272.28 | 1.13548 | 3(Loss) |
| glaze | 1269.22 | 0.21166 | 1208.61ms | 2821 | 80 | 1610.28 | 2119.66 | 1.91694 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) STATISTICAL TIE | 3265.61 | 0.19162 | 1133.38ms | 4147 | 320 | 1723.33 | 1211.07 | 0.734796 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3249.13 | 0.251482 | 1114.58ms | 4147 | 80 | 749.613 | 1217.21 | 0.738871 | 1(Tie) |
| jsonifier | 2734.04 | 0.520389 | 1172.74ms | 4147 | 320 | 18132.8 | 1446.53 | 0.882151 | 3(Loss) |
| glaze | 1624.42 | 0.260847 | 1241.85ms | 4147 | 40 | 1613.26 | 2434.65 | 1.50031 | 4(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1140.82 | 0.270704 | 1267.09ms | 2821 | 30 | 1222.6 | 2358.23 | 2.13456 | 1(Win) |
| glaze | 1107.5 | 0.80238 | 1274.93ms | 2821 | 1280 | 486286 | 2429.18 | 2.20059 | 2(Loss) |
| simdjson (reflection) | 888.771 | 0.653683 | 1315.86ms | 2821 | 1280 | 501153 | 3027 | 2.75104 | 3(Loss) |
| simdjson (ondemand) | 701.632 | 0.262144 | 1406.41ms | 2821 | 160 | 16165.4 | 3834.37 | 3.49263 | 4(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3535.37 | 0.261667 | 1097.65ms | 2821 | 1280 | 5075.09 | 760.971 | 0.66538 | 1(Win) |
| simdjson (reflection) | 2701.7 | 0.652248 | 1115.46ms | 2821 | 80 | 3374.8 | 995.788 | 0.882028 | 2(Loss) |
| glaze | 2545.6 | 0.52591 | 1122.33ms | 2819 | 40 | 1233.94 | 1056.1 | 0.937762 | 3(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 1283.94 | 0.267575 | 1321.22ms | 4147 | 30 | 2037.93 | 3080.27 | 1.90387 | 1(Win) |
| glaze | 1253.82 | 0.224014 | 1333.08ms | 4147 | 160 | 7988.58 | 3154.28 | 1.95078 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 998.81 | 0.278681 | 1410.34ms | 4147 | 40 | 4870.55 | 3959.6 | 2.4547 | 3(Tie) |
| jsonifier STATISTICAL TIE | 997.965 | 0.38743 | 1413.61ms | 4147 | 2560 | 603481 | 3962.95 | 2.45473 | 3(Tie) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4995.28 | 0.280431 | 1089.65ms | 4147 | 640 | 3154.86 | 791.725 | 0.471993 | 1(Win) |
| glaze | 1431.95 | 0.170617 | 1299.09ms | 4145 | 80 | 1774.71 | 2760.55 | 1.70513 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1470.95 | 0.127882 | 7977.12ms | 466906 | 640 | 9.59101e+07 | 302714 | 1.68271 | 1(Win) |
| glaze | 1293.06 | 0.0956393 | 9030.23ms | 466906 | 640 | 6.94189e+07 | 344360 | 1.91428 | 2(Loss) |
| simdjson (ondemand) | 709.931 | 0.176498 | 8132.6ms | 466906 | 160 | 1.96078e+08 | 627211 | 3.4868 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2088 | 0.0986707 | 8436.95ms | 699405 | 1280 | 1.2717e+08 | 319447 | 1.18538 | 1(Win) |
| glaze | 1276.27 | 0.190083 | 6741.88ms | 699405 | 160 | 1.57899e+08 | 522621 | 1.93955 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2465.38 | 0.124412 | 6503.88ms | 631514 | 1280 | 1.18231e+08 | 244286 | 1.00388 | 1(Win) |
| glaze | 1545.92 | 0.29193 | 5060.05ms | 631514 | 160 | 2.06951e+08 | 389579 | 1.60127 | 2(Loss) |
