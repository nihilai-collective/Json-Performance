# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [3ca767b](https://github.com/nihilai-collective/jsonifier/commit/3ca767b)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| simdjson (reflection) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX512BW` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 9V45 96-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10% AND mean shift < 5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 2219.16 | 0.0813964 | 735.437ms | 905 | 1280 | 128.274 | 388.92 | 1.03998 | 1(Win) |
| glaze | 1658.96 | 0.413733 | 739.479ms | 905 | 40 | 185.321 | 520.25 | 1.4176 | 2(Loss) |
| simdjson (ondemand) | 123.741 | 0.0589446 | 1444.82ms | 905 | 30 | 507.085 | 6974.87 | 19.9304 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2133.91 | 0.204804 | 724.69ms | 905 | 160 | 109.784 | 404.456 | 1.08778 | 1(Win) |
| simdjson (reflection) | 278.434 | 0.361737 | 977.643ms | 905 | 1280 | 160934 | 3099.75 | 8.81497 | 2(Loss) |
| glaze | 180.098 | 0.158659 | 1191.12ms | 905 | 30 | 1734.34 | 4792.27 | 13.6664 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1295.54 | 0.16019 | 800.763ms | 1811 | 80 | 364.835 | 1333.11 | 1.87364 | 1(Win) |
| glaze | 903.055 | 0.102083 | 860.521ms | 1811 | 80 | 304.937 | 1912.51 | 2.70188 | 2(Loss) |
| simdjson (ondemand) | 199.296 | 0.0604367 | 1524.83ms | 1811 | 30 | 822.93 | 8666.03 | 12.386 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 342.949 | 0.19263 | 1194.52ms | 1997 | 320 | 36618.2 | 5553.27 | 7.14516 | 1(Win) |
| jsonifier | 315.143 | 0.0471174 | 1219.57ms | 1811 | 160 | 1066.86 | 5480.39 | 7.81833 | 2(Loss) |
| glaze | 270.482 | 0.391519 | 1300.98ms | 1798 | 640 | 394267 | 6339.46 | 9.11581 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2935.13 | 0.195195 | 787.031ms | 3862 | 320 | 1919.81 | 1254.83 | 0.826075 | 1(Win) |
| glaze | 1533.29 | 0.0514841 | 912.335ms | 3862 | 160 | 244.704 | 2402.08 | 1.59719 | 2(Loss) |
| simdjson (ondemand) | 474.22 | 0.0537951 | 1431.77ms | 3862 | 30 | 523.689 | 7766.63 | 5.20466 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 847.403 | 0.670267 | 1083.36ms | 3862 | 320 | 271576 | 4346.33 | 2.90343 | 1(Win) |
| glaze | 764.579 | 0.341634 | 1129.51ms | 3862 | 640 | 173333 | 4817.15 | 3.22093 | 2(Loss) |
| simdjson (reflection) | 530.713 | 1.45675 | 1371.03ms | 3862 | 2560 | 2.61647e+07 | 6939.89 | 4.64531 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1548.2 | 0.843254 | 1247.38ms | 9578 | 320 | 792067 | 5899.94 | 1.58952 | 1(Win) |
| glaze | 1216.6 | 0.163858 | 1389.68ms | 9578 | 40 | 6054.12 | 7508.07 | 2.02783 | 2(Loss) |
| simdjson (ondemand) | 919.686 | 1.13418 | 1666.44ms | 9578 | 30 | 380675 | 9931.97 | 2.6816 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2363.87 | 0.140768 | 1043.22ms | 9578 | 30 | 887.637 | 3864.13 | 1.04029 | 1(Win) |
| glaze | 2048.4 | 0.168136 | 1108.48ms | 9578 | 40 | 2248.54 | 4459.23 | 1.20172 | 2(Loss) |
| simdjson (reflection) | 1306.86 | 1.77586 | 1312.45ms | 9578 | 4890 | 7.53386e+07 | 6989.48 | 1.88739 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2896.59 | 0.129397 | 793.216ms | 3873 | 40 | 108.9 | 1275.15 | 0.837258 | 1(Win) |
| glaze | 1887.5 | 0.0784844 | 879.869ms | 3873 | 80 | 188.702 | 1956.86 | 1.29416 | 2(Loss) |
| simdjson (ondemand) | 499.4 | 0.050175 | 1401.34ms | 3873 | 30 | 413.137 | 7396.03 | 4.94039 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 786.811 | 0.134364 | 1142.81ms | 3873 | 30 | 1193.55 | 4694.37 | 3.12875 | 1(Win) |
| glaze | 724.336 | 0.0956662 | 1147.89ms | 3873 | 30 | 713.926 | 5099.27 | 3.40016 | 2(Loss) |
| simdjson (reflection) | 527.202 | 0.525284 | 1381.37ms | 3873 | 640 | 866780 | 7006.01 | 4.67878 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 809.499 | 0.440474 | 7828.04ms | 2090234 | 80 | 9.41211e+09 | 2.46251e+06 | 3.05842 | 1(Win) |
| simdjson (ondemand) | 680.772 | 0.160854 | 9294.77ms | 2090234 | 30 | 6.65537e+08 | 2.92815e+06 | 3.63674 | 2(Loss) |
| glaze | 630.065 | 0.205427 | 10187.1ms | 2090234 | 30 | 1.26724e+09 | 3.1638e+06 | 3.92942 | 3(Loss) |
| simdjson (reflection) | 603.723 | 0.16747 | 10220.3ms | 2090234 | 160 | 4.89227e+09 | 3.30185e+06 | 4.10088 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1792.58 | 0.0459954 | 7071.56ms | 2090234 | 80 | 2.09293e+07 | 1.11203e+06 | 1.38111 | 1(Win) |
| glaze | 1394.49 | 0.0641562 | 9192.23ms | 2090234 | 80 | 6.72859e+07 | 1.42948e+06 | 1.77538 | 2(Loss) |
| simdjson (reflection) | 870.504 | 0.0410526 | 7300.84ms | 2090326 | 40 | 3.53531e+07 | 2.29004e+06 | 2.84408 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2226.1 | 0.131649 | 8931.77ms | 6661897 | 80 | 1.12936e+09 | 2.854e+06 | 1.11216 | 1(Win) |
| simdjson (ondemand) | 1955.91 | 0.131066 | 10297.1ms | 6661897 | 40 | 7.24995e+08 | 3.24824e+06 | 1.2658 | 2(Loss) |
| simdjson (reflection) | 1753.29 | 0.309688 | 5400.27ms | 6661897 | 80 | 1.00746e+10 | 3.62363e+06 | 1.41208 | 3(Loss) |
| glaze | 1592.49 | 0.379896 | 6009.91ms | 6661897 | 40 | 9.18828e+09 | 3.98953e+06 | 1.55467 | 4(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5467.86 | 0.364808 | 7390.72ms | 6661897 | 30 | 5.39029e+08 | 1.16193e+06 | 0.45278 | 1(Win) |
| glaze | 2346.62 | 0.0411958 | 8552.48ms | 6661897 | 30 | 3.73196e+07 | 2.70742e+06 | 1.05504 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1647.47 | 0.123603 | 7611ms | 500299 | 1280 | 1.64017e+08 | 289609 | 1.50263 | 1(Win) |
| jsonifier | 1605.07 | 0.0644121 | 7660.31ms | 500299 | 1280 | 4.69266e+07 | 297260 | 1.54234 | 2(Loss) |
| simdjson (reflection) | 1398.01 | 0.176204 | 9140.79ms | 500299 | 80 | 2.89308e+07 | 341287 | 1.77076 | 3(Loss) |
| simdjson (ondemand) | 1385.93 | 0.278218 | 9100.09ms | 500299 | 40 | 3.6695e+07 | 344261 | 1.78619 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10355.5 | 0.414767 | 5168.29ms | 500299 | 640 | 2.33723e+07 | 46074.1 | 0.238764 | 1(Win) |
| simdjson (reflection) | 6213.65 | 0.22581 | 8510.13ms | 500299 | 640 | 1.92412e+07 | 76786.2 | 0.398243 | 2(Loss) |
| glaze | 4607.09 | 0.214807 | 5825.39ms | 500299 | 30 | 1.48465e+06 | 103563 | 0.537182 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3704.6 | 0.180331 | 9616.79ms | 1439562 | 160 | 7.14562e+07 | 370586 | 0.668249 | 1(Win) |
| simdjson (ondemand) | 3465.81 | 0.226313 | 5281.87ms | 1439562 | 80 | 6.42925e+07 | 396120 | 0.714285 | 2(Loss) |
| simdjson (reflection) | 3386.57 | 0.114449 | 5258.31ms | 1439562 | 640 | 1.37767e+08 | 405387 | 0.730997 | 3(Loss) |
| glaze | 2827.17 | 0.185192 | 6277.95ms | 1439562 | 40 | 3.2349e+07 | 485599 | 0.875658 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 25669.2 | 0.44853 | 6074.31ms | 1439562 | 320 | 1.84149e+07 | 53483.3 | 0.0963986 | 1(Win) |
| glaze | 3033.93 | 0.230188 | 5895.87ms | 1439584 | 40 | 4.34001e+07 | 452514 | 0.815972 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1727.21 | 0.332433 | 3756.91ms | 56369 | 1280 | 1.37028e+07 | 31124.1 | 1.43222 | 1(Win) |
| glaze STATISTICAL TIE | 1541.27 | 0.752042 | 3985.83ms | 56369 | 320 | 2.20169e+07 | 34878.8 | 1.60508 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1532.57 | 0.377743 | 4235.07ms | 56369 | 640 | 1.1236e+07 | 35076.8 | 1.61428 | 2(Tie) |
| simdjson (ondemand) | 1475.57 | 0.561015 | 4346.18ms | 56369 | 320 | 1.33678e+07 | 36431.8 | 1.67667 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9800.11 | 0.0505104 | 1257.3ms | 56369 | 80 | 614.144 | 5485.41 | 0.251435 | 1(Win) |
| simdjson (reflection) | 9320.47 | 0.0854215 | 1269.88ms | 56369 | 30 | 728.217 | 5767.7 | 0.264369 | 2(Loss) |
| glaze | 5371.76 | 1.57908 | 1684.2ms | 56369 | 80 | 1.99776e+06 | 10007.5 | 0.45966 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2452.38 | 0.1524 | 4357.86ms | 94370 | 4890 | 1.52958e+07 | 36698.4 | 1.00885 | 1(Win) |
| simdjson (reflection) | 2400.36 | 0.385916 | 4463ms | 94370 | 640 | 1.33993e+07 | 37493.7 | 1.03071 | 2(Loss) |
| simdjson (ondemand) | 2347.54 | 0.271408 | 4518.53ms | 94370 | 1280 | 1.38579e+07 | 38337.3 | 1.05393 | 3(Loss) |
| glaze | 2072.32 | 0.248267 | 4975.89ms | 94370 | 1280 | 1.488e+07 | 43428.8 | 1.19398 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14741.4 | 0.0397324 | 1322.26ms | 94370 | 80 | 470.728 | 6105.14 | 0.167247 | 1(Win) |
| glaze | 2021.57 | 0.469998 | 5004.56ms | 94370 | 320 | 1.40099e+07 | 44519 | 1.22397 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1757.11 | 0.512856 | 1336.37ms | 11812 | 320 | 345933 | 6411 | 1.40335 | 1(Win) |
| jsonifier | 1388.76 | 0.0338162 | 1507.19ms | 11812 | 160 | 1203.83 | 8111.44 | 1.77706 | 2(Loss) |
| simdjson (reflection) | 1309.87 | 0.111433 | 1527.79ms | 11812 | 40 | 3673.46 | 8599.92 | 1.8845 | 3(Loss) |
| simdjson (ondemand) | 997.884 | 0.446097 | 1768.29ms | 11812 | 320 | 811514 | 11288.7 | 2.47518 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7083.89 | 0.207154 | 826.593ms | 11812 | 40 | 434.062 | 1590.2 | 0.343532 | 1(Win) |
| simdjson (reflection) | 5849.95 | 0.205084 | 870.46ms | 11812 | 40 | 623.83 | 1925.62 | 0.417709 | 2(Loss) |
| glaze | 3933.86 | 0.075022 | 950.19ms | 11812 | 80 | 369.213 | 2863.55 | 0.62368 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3263.85 | 0.0527617 | 1573.24ms | 31235 | 40 | 927.515 | 9126.65 | 0.756397 | 1(Win) |
| simdjson (reflection) | 3171.69 | 0.106098 | 1603.21ms | 31235 | 30 | 2978.76 | 9391.83 | 0.7784 | 2(Loss) |
| glaze | 2656.2 | 0.540521 | 1796.85ms | 31235 | 160 | 587904 | 11214.5 | 0.929936 | 3(Loss) |
| simdjson (ondemand) | 2509.72 | 0.341386 | 1848.42ms | 31235 | 640 | 1.05076e+06 | 11869 | 0.984326 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16586.2 | 0.188 | 839.783ms | 31235 | 40 | 455.997 | 1795.95 | 0.146976 | 1(Win) |
| glaze | 2224.01 | 0.313582 | 2005.27ms | 31235 | 30 | 52921.5 | 13393.8 | 1.11119 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3069.1 | 0.0259067 | 4171.91ms | 108313 | 40 | 3041.07 | 33656.6 | 0.806016 | 1(Win) |
| simdjson (reflection) | 1791.07 | 0.264645 | 6345.66ms | 108313 | 640 | 1.49088e+07 | 57672.4 | 1.3816 | 2(Loss) |
| glaze | 1608.85 | 0.217489 | 7158.24ms | 108313 | 1280 | 2.49583e+07 | 64204.4 | 1.53819 | 3(Loss) |
| simdjson (ondemand) | 1389.51 | 0.478713 | 8340.23ms | 108313 | 160 | 2.02633e+07 | 74339.6 | 1.78117 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15022.7 | 0.0554896 | 1384.18ms | 108313 | 80 | 1164.61 | 6875.95 | 0.164198 | 1(Win) |
| simdjson (reflection) | 10093.6 | 0.0552373 | 1733.04ms | 108313 | 30 | 958.631 | 10233.7 | 0.244669 | 2(Loss) |
| glaze | 2491.34 | 0.409146 | 4722.85ms | 108313 | 640 | 1.84176e+07 | 41461.8 | 0.993117 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3369.83 | 0.0957826 | 6614.87ms | 213963 | 4890 | 1.64492e+07 | 60552.3 | 0.734324 | 1(Win) |
| simdjson (reflection) | 3197.62 | 0.177365 | 7021.8ms | 213963 | 1280 | 1.63972e+07 | 63813.4 | 0.77393 | 2(Loss) |
| simdjson (ondemand) | 2402.05 | 0.274663 | 9118.38ms | 213963 | 320 | 1.74207e+07 | 84948.6 | 1.03036 | 3(Loss) |
| glaze | 2270.93 | 0.141495 | 9611.43ms | 213963 | 1280 | 2.06903e+07 | 89853.6 | 1.08986 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 24529.9 | 0.0863995 | 1530.02ms | 213963 | 30 | 1549.64 | 8318.47 | 0.100595 | 1(Win) |
| glaze | 1763.44 | 0.10178 | 6404.5ms | 213963 | 1280 | 1.77537e+07 | 115712 | 1.40366 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 791.319 | 0.0862062 | 7022.39ms | 1834197 | 30 | 1.0894e+08 | 2.21052e+06 | 3.12867 | 1(Win) |
| simdjson (ondemand) | 627.801 | 0.214214 | 8833.82ms | 1834197 | 30 | 1.06872e+09 | 2.78628e+06 | 3.94358 | 2(Loss) |
| glaze | 620.91 | 0.0907108 | 9051.76ms | 1834197 | 80 | 5.22447e+08 | 2.8172e+06 | 3.98735 | 3(Loss) |
| simdjson (reflection) | 590.713 | 0.0627138 | 9312.26ms | 1834197 | 80 | 2.75903e+08 | 2.96121e+06 | 4.19119 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1220.28 | 0.0542825 | 9188.3ms | 1834197 | 320 | 1.93751e+08 | 1.43346e+06 | 2.02884 | 1(Win) |
| glaze | 903.558 | 0.198533 | 6005.79ms | 1833577 | 40 | 5.9049e+08 | 1.93528e+06 | 2.74003 | 2(Loss) |
| simdjson (reflection) | 548.093 | 0.228186 | 5005.47ms | 1922245 | 80 | 4.65992e+09 | 3.34468e+06 | 4.5171 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3273.88 | 0.135119 | 9151.04ms | 9930848 | 160 | 2.44456e+09 | 2.89284e+06 | 0.756223 | 1(Win) |
| simdjson (ondemand) | 2858.03 | 0.185529 | 5043.48ms | 9930848 | 80 | 3.02379e+09 | 3.31375e+06 | 0.866248 | 2(Loss) |
| simdjson (reflection) | 2737.28 | 0.189803 | 5303.98ms | 9930848 | 80 | 3.4501e+09 | 3.45993e+06 | 0.904458 | 3(Loss) |
| glaze | 2502.4 | 0.237893 | 5743.3ms | 9930848 | 40 | 3.24254e+09 | 3.78469e+06 | 0.989355 | 4(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6314.74 | 0.0628022 | 9599.6ms | 9930848 | 160 | 1.41949e+08 | 1.49979e+06 | 0.39206 | 1(Win) |
| glaze | 1883.02 | 0.207481 | 7419.67ms | 9930228 | 30 | 3.26653e+09 | 5.02927e+06 | 1.31475 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 779.957 | 0.251004 | 7110.25ms | 1834197 | 160 | 5.0703e+09 | 2.24272e+06 | 3.17425 | 1(Win) |
| simdjson (ondemand) | 626.776 | 0.121021 | 8872.45ms | 1834197 | 40 | 4.56299e+08 | 2.79083e+06 | 3.95003 | 2(Loss) |
| glaze | 623.74 | 0.0949541 | 8851.33ms | 1834197 | 30 | 2.12732e+08 | 2.80441e+06 | 3.96925 | 3(Loss) |
| simdjson (reflection) | 569.105 | 0.133337 | 9534.88ms | 1834197 | 160 | 2.68736e+09 | 3.07365e+06 | 4.35032 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1178.89 | 0.107879 | 9378.27ms | 1834197 | 80 | 2.04978e+08 | 1.48379e+06 | 2.10008 | 1(Win) |
| glaze | 909.789 | 0.0359947 | 6129.37ms | 1833577 | 160 | 7.65797e+07 | 1.92202e+06 | 2.72125 | 2(Loss) |
| simdjson (reflection) | 558.42 | 0.259947 | 5043.11ms | 1922245 | 40 | 2.91291e+09 | 3.28283e+06 | 4.43357 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3325.29 | 0.140889 | 9069.31ms | 9930848 | 30 | 4.83047e+08 | 2.84811e+06 | 0.744532 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 2757.37 | 0.098108 | 5132.43ms | 9930848 | 80 | 9.08406e+08 | 3.43472e+06 | 0.897879 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2755.11 | 0.141075 | 5209.3ms | 9930848 | 30 | 7.05535e+08 | 3.43754e+06 | 0.898619 | 2(Tie) |
| glaze | 2409.01 | 0.108501 | 5768.89ms | 9930848 | 80 | 1.45564e+09 | 3.9314e+06 | 1.02772 | 4(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6390.97 | 0.283717 | 9435.88ms | 9930848 | 40 | 7.07085e+08 | 1.4819e+06 | 0.387383 | 1(Win) |
| glaze | 1831.36 | 0.127183 | 7736.85ms | 9930228 | 30 | 1.29763e+09 | 5.17113e+06 | 1.35185 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1247.96 | 0.123308 | 6513.28ms | 642697 | 80 | 2.93417e+07 | 491140 | 1.98371 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1217.58 | 0.17554 | 6693.82ms | 642697 | 80 | 6.24679e+07 | 503393 | 2.03321 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1212.55 | 0.297342 | 6667.23ms | 642697 | 40 | 9.03615e+07 | 505481 | 2.04167 | 2(Tie) |
| glaze | 1127.65 | 0.0943854 | 7021.07ms | 642697 | 80 | 2.10553e+07 | 543539 | 2.19539 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2089.49 | 0.124466 | 7543.15ms | 642697 | 640 | 8.53131e+07 | 293337 | 1.18478 | 1(Win) |
| glaze | 1575.61 | 0.534602 | 5062.18ms | 642692 | 320 | 1.38394e+09 | 389003 | 1.57115 | 2(Loss) |
| simdjson (reflection) | 984.309 | 0.0412214 | 8280.57ms | 643373 | 320 | 2.1128e+07 | 623350 | 2.51511 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2122.95 | 0.344306 | 7071.93ms | 1225964 | 40 | 1.43822e+08 | 550730 | 1.16613 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2112.2 | 0.138704 | 7063.61ms | 1225964 | 160 | 9.43154e+07 | 553531 | 1.17206 | 1(Tie) |
| jsonifier | 1859.98 | 0.0793791 | 8289.51ms | 1225964 | 640 | 1.59342e+08 | 628592 | 1.33101 | 3(Loss) |
| glaze | 1665.08 | 0.187456 | 8821.84ms | 1225964 | 80 | 1.38604e+08 | 702173 | 1.48682 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4237.61 | 0.145462 | 7375.16ms | 1225964 | 160 | 2.57711e+07 | 275903 | 0.584189 | 1(Win) |
| glaze | 2304.08 | 0.0798286 | 6648.3ms | 1225970 | 160 | 2.62545e+07 | 507438 | 1.07443 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1228.61 | 0.177882 | 8177.24ms | 409725 | 80 | 2.56042e+07 | 318038 | 2.01479 | 1(Win) |
| simdjson (reflection) | 1193.17 | 0.166657 | 8964.74ms | 409725 | 80 | 2.38298e+07 | 327485 | 2.07469 | 2(Loss) |
| simdjson (ondemand) | 1165.66 | 0.230235 | 8502.04ms | 409725 | 80 | 4.7651e+07 | 335213 | 2.12365 | 3(Loss) |
| glaze | 947.2 | 0.497774 | 5415.1ms | 409725 | 30 | 1.26499e+08 | 412526 | 2.61352 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 5788.8 | 0.181755 | 7489.77ms | 409725 | 1280 | 1.92661e+07 | 67500 | 0.427476 | 1(Win) |
| jsonifier | 5384.5 | 0.0935425 | 8013.16ms | 409725 | 4890 | 2.25331e+07 | 72568.4 | 0.459592 | 2(Loss) |
| glaze | 3313.86 | 0.248244 | 6349.68ms | 409725 | 320 | 2.74172e+07 | 117912 | 0.746887 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2122.68 | 0.186854 | 9208.03ms | 785750 | 640 | 2.78475e+08 | 353020 | 1.16619 | 1(Win) |
| jsonifier | 1986.91 | 0.287343 | 9604.53ms | 785750 | 640 | 7.51607e+08 | 377143 | 1.24588 | 2(Loss) |
| simdjson (reflection) | 1865.78 | 0.312509 | 5046.54ms | 785750 | 320 | 5.04111e+08 | 401629 | 1.3268 | 3(Loss) |
| glaze | 1495.73 | 0.139103 | 6479.91ms | 785750 | 80 | 3.8853e+07 | 500992 | 1.65509 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9229.84 | 0.387899 | 9021.15ms | 785750 | 320 | 3.17372e+07 | 81187.8 | 0.268133 | 1(Win) |
| glaze | 1553.79 | 0.0646115 | 6239.34ms | 785750 | 320 | 3.1071e+07 | 482273 | 1.59327 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 6403.92 | 0.403045 | 4671.87ms | 264040 | 1280 | 3.21488e+07 | 39320.9 | 0.386351 | 1(Win) |
| jsonifier STATISTICAL TIE | 5917.22 | 0.717881 | 4993.49ms | 264040 | 30 | 2.79982e+06 | 42555.1 | 0.418152 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 5884.79 | 0.185553 | 4985.81ms | 264040 | 2560 | 1.61381e+07 | 42789.7 | 0.420451 | 2(Tie) |
| glaze | 2432.87 | 0.123312 | 5715.26ms | 264040 | 1280 | 2.08507e+07 | 103502 | 1.01739 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 8122.81 | 0.393339 | 5474.99ms | 399947 | 1280 | 4.36653e+07 | 46956.5 | 0.304415 | 1(Win) |
| jsonifier STATISTICAL TIE | 7540.34 | 0.344413 | 5852.55ms | 399947 | 640 | 1.94251e+07 | 50583.8 | 0.328166 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 7519.92 | 0.381561 | 5607.92ms | 399947 | 640 | 2.3971e+07 | 50721.1 | 0.329059 | 2(Tie) |
| glaze | 3084.29 | 0.129487 | 6620.4ms | 399947 | 1280 | 3.28211e+07 | 123665 | 0.802542 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1834.6 | 0.379696 | 7500.39ms | 264040 | 160 | 4.34557e+07 | 137255 | 1.34919 | 1(Win) |
| simdjson (reflection) | 1598.58 | 0.141683 | 8405.58ms | 264040 | 640 | 3.18778e+07 | 157520 | 1.54842 | 2(Loss) |
| glaze | 1548.25 | 0.284861 | 8008.97ms | 264040 | 160 | 3.43434e+07 | 162641 | 1.59876 | 3(Loss) |
| simdjson (ondemand) | 1196.35 | 0.114068 | 5645.66ms | 264040 | 640 | 3.68916e+07 | 210480 | 2.06914 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9372.27 | 0.450276 | 3421.74ms | 264040 | 2560 | 3.7467e+07 | 26867.4 | 0.263873 | 1(Win) |
| simdjson (reflection) | 7934.06 | 0.573663 | 3914.55ms | 264040 | 640 | 2.1215e+07 | 31737.6 | 0.311739 | 2(Loss) |
| glaze | 5946.42 | 0.808151 | 4957ms | 263923 | 320 | 3.74436e+07 | 42327.4 | 0.41608 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 2292.65 | 0.121018 | 9067.02ms | 399947 | 640 | 2.59426e+07 | 166366 | 1.07963 | 1(Win) |
| glaze | 1887.54 | 0.169839 | 5467.2ms | 399947 | 320 | 3.76911e+07 | 202072 | 1.31147 | 2(Loss) |
| jsonifier | 1848.82 | 0.284432 | 5452.24ms | 399947 | 160 | 5.50928e+07 | 206304 | 1.33891 | 3(Loss) |
| simdjson (ondemand) | 1805.84 | 0.405422 | 5647.22ms | 399947 | 40 | 2.93307e+07 | 211214 | 1.37079 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12138.5 | 0.176887 | 3832.35ms | 399947 | 4890 | 1.51071e+07 | 31422.4 | 0.203795 | 1(Win) |
| glaze | 2355.3 | 0.0887226 | 8642.28ms | 399830 | 1280 | 2.64081e+07 | 161893 | 1.05091 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1244.37 | 0.106153 | 1051.19ms | 4630 | 40 | 567.528 | 3548.4 | 1.97551 | 1(Win) |
| simdjson (ondemand) | 746.873 | 0.114736 | 1318.71ms | 4630 | 30 | 1380.34 | 5912 | 3.30133 | 2(Loss) |
| glaze STATISTICAL TIE | 697.623 | 3.01595 | 1322.02ms | 4630 | 2560 | 9.32846e+07 | 6329.37 | 3.53243 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 666.083 | 0.0743622 | 1369.49ms | 4630 | 80 | 1944.02 | 6629.07 | 3.70195 | 3(Tie) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1779.95 | 0.111217 | 974.987ms | 4630 | 30 | 228.355 | 2480.7 | 1.37633 | 1(Win) |
| glaze | 1438.15 | 0.158257 | 1009.84ms | 4630 | 30 | 708.271 | 3070.27 | 1.70671 | 2(Loss) |
| simdjson (reflection) | 909.861 | 0.0721927 | 1222.18ms | 4630 | 80 | 981.947 | 4852.95 | 2.70681 | 3(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2882.83 | 0.068022 | 1258.51ms | 14795 | 30 | 332.516 | 4894.37 | 0.854178 | 1(Win) |
| simdjson (ondemand) | 2089.28 | 0.709243 | 1449.08ms | 14795 | 320 | 734140 | 6753.35 | 1.18018 | 2(Loss) |
| simdjson (reflection) | 1836.17 | 1.34909 | 1822.5ms | 14795 | 160 | 1.71952e+06 | 7684.26 | 1.3436 | 3(Loss) |
| glaze | 1665.35 | 0.0621694 | 1575.11ms | 14795 | 30 | 832.326 | 8472.47 | 1.48173 | 4(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5381.24 | 0.108799 | 1028.32ms | 14795 | 30 | 244.138 | 2622 | 0.455318 | 1(Win) |
| glaze | 2223.11 | 0.0242441 | 1380.77ms | 14795 | 160 | 378.828 | 6346.8 | 1.10901 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1439.09 | 0.101238 | 1068.87ms | 5092 | 30 | 350.116 | 3374.43 | 1.70643 | 1(Win) |
| glaze | 1244.26 | 0.100663 | 1182.07ms | 5092 | 80 | 1234.78 | 3902.82 | 1.97545 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 1202.05 | 0.0878102 | 1239.74ms | 5092 | 40 | 503.362 | 4039.85 | 2.04661 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1184.39 | 1.00171 | 1164.08ms | 5092 | 160 | 269896 | 4100.1 | 2.07686 | 3(Tie) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6927.16 | 0.278845 | 836.307ms | 5092 | 40 | 152.846 | 701.025 | 0.343858 | 1(Win) |
| simdjson (reflection) | 4310.12 | 0.256404 | 899.311ms | 5092 | 40 | 333.815 | 1126.67 | 0.561003 | 2(Loss) |
| glaze | 2759.78 | 0.380821 | 928.799ms | 5092 | 30 | 1347.08 | 1759.6 | 0.884008 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 2466.99 | 0.0829386 | 1178.92ms | 11724 | 30 | 423.89 | 4532.2 | 0.99772 | 1(Win) |
| jsonifier | 2439.95 | 0.0992768 | 1220.27ms | 11724 | 40 | 827.84 | 4582.43 | 1.00782 | 2(Loss) |
| simdjson (ondemand) | 2405.54 | 0.0740027 | 1177.27ms | 11724 | 30 | 354.93 | 4647.97 | 1.02322 | 3(Loss) |
| glaze | 2060.14 | 0.0760204 | 1308.02ms | 11724 | 30 | 510.668 | 5427.23 | 1.19576 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13428.2 | 0.212362 | 870.404ms | 11724 | 160 | 500.256 | 832.644 | 0.17825 | 1(Win) |
| glaze | 2119.84 | 0.0914797 | 1341.76ms | 11746 | 30 | 701.045 | 5284.3 | 1.16202 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1527.17 | 0.0829809 | 1087.07ms | 4857 | 80 | 506.768 | 3033.06 | 1.60625 | 1(Win) |
| simdjson (reflection) | 1302.6 | 0.170661 | 1099.86ms | 4857 | 30 | 1104.86 | 3555.97 | 1.8873 | 2(Loss) |
| jsonifier | 1257.78 | 0.134254 | 1132.15ms | 4857 | 30 | 733.333 | 3682.67 | 1.95333 | 3(Loss) |
| simdjson (ondemand) | 1211.79 | 0.087018 | 1107.4ms | 4857 | 30 | 331.909 | 3822.43 | 2.03004 | 4(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5744.19 | 0.180258 | 856.531ms | 4857 | 1280 | 2704.44 | 806.379 | 0.416931 | 1(Win) |
| simdjson (reflection) | 5556.45 | 0.39171 | 847.343ms | 4857 | 80 | 853.022 | 833.625 | 0.430971 | 2(Loss) |
| glaze | 3896.47 | 0.258781 | 891.034ms | 4857 | 30 | 283.909 | 1188.77 | 0.62216 | 3(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2004.1 | 0.0724439 | 1112.21ms | 7376 | 320 | 2068.97 | 3509.95 | 1.22626 | 1(Win) |
| simdjson (reflection) | 1942.56 | 0.410603 | 1092.39ms | 7376 | 160 | 35371.6 | 3621.14 | 1.26529 | 2(Loss) |
| simdjson (ondemand) | 1759.88 | 0.117864 | 1178.85ms | 7376 | 30 | 665.826 | 3997.03 | 1.39716 | 3(Loss) |
| jsonifier | 1689.81 | 0.133744 | 1187.82ms | 7376 | 40 | 1239.87 | 4162.77 | 1.45552 | 4(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8094.36 | 0.166141 | 839.225ms | 7376 | 80 | 166.771 | 869.038 | 0.296524 | 1(Win) |
| glaze | 2132.6 | 0.0385978 | 1054.67ms | 7376 | 80 | 129.669 | 3298.46 | 1.1521 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1703.71 | 0.284587 | 964.745ms | 4390 | 30 | 1467.21 | 2457.37 | 1.43737 | 1(Win) |
| simdjson (reflection) | 1431.05 | 0.0948097 | 1022.72ms | 4390 | 30 | 230.806 | 2925.57 | 1.71474 | 2(Loss) |
| jsonifier | 1374.62 | 0.115879 | 1019.15ms | 4390 | 30 | 373.678 | 3045.67 | 1.78484 | 3(Loss) |
| simdjson (ondemand) | 1084.75 | 0.15319 | 1107.7ms | 4390 | 40 | 1398.26 | 3859.53 | 2.26785 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6194.29 | 0.13029 | 820.623ms | 4390 | 640 | 496.308 | 675.886 | 0.384415 | 1(Win) |
| simdjson (reflection) | 4969.44 | 0.359903 | 865.477ms | 4390 | 40 | 367.743 | 842.475 | 0.48295 | 2(Loss) |
| glaze | 3566.66 | 0.175652 | 829.785ms | 4390 | 80 | 340.096 | 1173.83 | 0.678545 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3290.09 | 0.078336 | 1063.84ms | 11521 | 80 | 547.494 | 3339.51 | 0.746663 | 1(Win) |
| simdjson (reflection) | 3266.43 | 0.0794439 | 1102.72ms | 11521 | 80 | 571.276 | 3363.7 | 0.752191 | 2(Loss) |
| glaze | 2784.28 | 0.0596193 | 1128.64ms | 11521 | 80 | 442.812 | 3946.19 | 0.883225 | 3(Loss) |
| simdjson (ondemand) | 2606.75 | 0.118227 | 1158.53ms | 11521 | 30 | 744.961 | 4214.93 | 0.944119 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14675.9 | 0.25379 | 779.895ms | 11521 | 80 | 288.809 | 748.663 | 0.162675 | 1(Win) |
| glaze | 2191.67 | 0.0764607 | 1227.38ms | 11521 | 30 | 440.786 | 5013.2 | 1.12377 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2609.15 | 0.114782 | 938.647ms | 4669 | 40 | 153.481 | 1706.58 | 0.933551 | 1(Win) |
| simdjson (reflection) | 1642.1 | 0.0812575 | 963.811ms | 4669 | 40 | 194.195 | 2711.6 | 1.49237 | 2(Loss) |
| glaze | 1506.46 | 0.171372 | 1030.48ms | 4669 | 30 | 769.72 | 2955.73 | 1.62917 | 3(Loss) |
| simdjson (ondemand) | 1269.34 | 0.0824329 | 1120.47ms | 4669 | 30 | 250.852 | 3507.9 | 1.9369 | 4(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8005.4 | 0.31412 | 797.646ms | 4669 | 160 | 488.42 | 556.212 | 0.294524 | 1(Win) |
| simdjson (reflection) | 5663.27 | 0.244392 | 851.91ms | 4669 | 640 | 2363.02 | 786.242 | 0.423056 | 2(Loss) |
| glaze | 2052.41 | 0.242448 | 945.927ms | 4669 | 40 | 1106.67 | 2169.5 | 1.19248 | 3(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2942.42 | 0.0885721 | 1029.04ms | 9249 | 80 | 563.98 | 2997.71 | 0.833932 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2941.89 | 0.0632909 | 1083.31ms | 9249 | 40 | 144.038 | 2998.25 | 0.834258 | 1(Tie) |
| simdjson (ondemand) | 2256.35 | 0.0679397 | 1147.01ms | 9249 | 30 | 211.614 | 3909.2 | 1.08949 | 3(Loss) |
| glaze | 2193.76 | 0.106691 | 1184.9ms | 9249 | 30 | 552.064 | 4020.73 | 1.12096 | 4(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13961.4 | 0.188229 | 806.709ms | 9249 | 320 | 452.537 | 631.778 | 0.169856 | 1(Win) |
| glaze | 1541.28 | 0.897702 | 1309.22ms | 9249 | 160 | 422289 | 5722.86 | 1.59872 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 878.095 | 0.287761 | 1248.36ms | 4604 | 1280 | 265009 | 5000.27 | 2.80419 | 1(Win) |
| glaze | 607.196 | 0.557657 | 1456.34ms | 4604 | 320 | 520352 | 7231.14 | 4.06227 | 2(Loss) |
| simdjson (ondemand) | 599.661 | 0.0622051 | 1481.33ms | 4604 | 40 | 829.795 | 7322 | 4.11416 | 3(Loss) |
| simdjson (reflection) | 563.013 | 0.0669338 | 1504.01ms | 4604 | 30 | 817.421 | 7798.6 | 4.38262 | 4(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1506.92 | 0.0940147 | 1063.02ms | 4604 | 30 | 225.114 | 2913.7 | 1.62807 | 1(Win) |
| glaze | 1039.96 | 0.133382 | 1170.48ms | 4604 | 30 | 951.379 | 4222 | 2.36581 | 2(Loss) |
| simdjson (reflection) | 801.961 | 0.0524692 | 1358.94ms | 4918 | 40 | 376.651 | 5848.38 | 3.07287 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3226.48 | 0.0931016 | 1526.15ms | 24579 | 30 | 1372.48 | 7265 | 0.764441 | 1(Win) |
| simdjson (ondemand) | 2748.91 | 0.0617145 | 1634.1ms | 24579 | 30 | 830.809 | 8527.13 | 0.897831 | 2(Loss) |
| simdjson (reflection) | 2625.41 | 0.347803 | 1679.76ms | 24579 | 320 | 308569 | 8928.27 | 0.940265 | 3(Loss) |
| glaze | 2158.78 | 0.0596616 | 1869.72ms | 24579 | 40 | 1678.66 | 10858.2 | 1.14397 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7166.33 | 0.0641933 | 1113.96ms | 24579 | 80 | 352.699 | 3270.9 | 0.342582 | 1(Win) |
| glaze | 2460.93 | 0.0730846 | 1736.59ms | 24579 | 30 | 1453.79 | 9525 | 1.00326 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 961.632 | 0.0921057 | 1241.16ms | 4604 | 30 | 530.576 | 4565.9 | 2.56043 | 1(Win) |
| glaze STATISTICAL TIE | 611.711 | 1.02048 | 1499.15ms | 4604 | 160 | 858429 | 7177.77 | 4.03188 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 602.927 | 0.0797534 | 1516.51ms | 4604 | 30 | 1011.95 | 7282.33 | 4.09159 | 2(Tie) |
| simdjson (reflection) | 556.571 | 0.0925626 | 1574.5ms | 4604 | 30 | 1599.64 | 7888.87 | 4.4327 | 4(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1470.42 | 0.111643 | 1077.67ms | 4604 | 40 | 444.538 | 2986.03 | 1.66832 | 1(Win) |
| glaze | 1029.55 | 0.10678 | 1209.33ms | 4604 | 40 | 829.497 | 4264.7 | 2.38961 | 2(Loss) |
| simdjson (reflection) | 798.966 | 0.0398114 | 1372.94ms | 4918 | 40 | 218.472 | 5870.3 | 3.0845 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3208.91 | 0.0692085 | 1505.12ms | 24579 | 40 | 1022.33 | 7304.77 | 0.768629 | 1(Win) |
| simdjson (ondemand) | 2769.18 | 0.040652 | 1640.05ms | 24579 | 40 | 473.64 | 8464.73 | 0.891176 | 2(Loss) |
| simdjson (reflection) | 2586.22 | 0.084431 | 1655.97ms | 24579 | 30 | 1756.81 | 9063.57 | 0.954323 | 3(Loss) |
| glaze | 2097.16 | 1.84544 | 1882.74ms | 24579 | 30 | 1.2764e+06 | 11177.2 | 1.17773 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7123.11 | 0.0834967 | 1058.91ms | 24579 | 40 | 301.987 | 3290.75 | 0.344917 | 1(Win) |
| glaze | 2405.36 | 0.0689756 | 1719.56ms | 24579 | 30 | 1355.44 | 9745.07 | 1.0264 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1001.49 | 0.394282 | 872.229ms | 1181 | 320 | 6291.75 | 1124.62 | 2.41252 | 1(Win) |
| glaze | 786.924 | 0.142493 | 905.836ms | 1181 | 160 | 665.487 | 1431.26 | 3.08656 | 2(Loss) |
| simdjson (ondemand) | 772.132 | 0.164004 | 881.024ms | 1181 | 80 | 457.842 | 1458.67 | 3.14915 | 3(Loss) |
| simdjson (reflection) | 761.431 | 0.231054 | 885.983ms | 1181 | 320 | 3737.81 | 1479.17 | 3.19456 | 4(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1815.84 | 0.155467 | 829.803ms | 1181 | 320 | 297.559 | 620.259 | 1.30425 | 1(Win) |
| glaze | 1145.22 | 0.265498 | 837.178ms | 1181 | 30 | 204.533 | 983.467 | 2.1031 | 2(Loss) |
| simdjson (reflection) | 1050.83 | 0.118845 | 847.167ms | 1187 | 160 | 262.255 | 1077.26 | 2.29774 | 3(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1585.02 | 0.0753425 | 929.36ms | 2496 | 320 | 409.683 | 1501.79 | 1.53362 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1552.85 | 0.185132 | 878.409ms | 2496 | 40 | 322.144 | 1532.9 | 1.56688 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1542.06 | 0.293429 | 911.694ms | 2496 | 30 | 615.482 | 1543.63 | 1.57841 | 2(Tie) |
| glaze | 1436.06 | 0.295668 | 901.248ms | 2496 | 40 | 960.763 | 1657.58 | 1.69758 | 4(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3823.29 | 0.101994 | 804.565ms | 2496 | 320 | 129.038 | 622.597 | 0.620837 | 1(Win) |
| glaze | 1445.07 | 0.10623 | 899.248ms | 2507 | 30 | 92.6724 | 1654.5 | 1.68662 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1469.82 | 0.0436198 | 1101.81ms | 4926 | 160 | 310.992 | 3196.18 | 1.67046 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1185.89 | 0.73393 | 1211.04ms | 4926 | 320 | 270494 | 3961.41 | 2.07332 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1178.91 | 0.112798 | 1156.81ms | 4926 | 80 | 1616.29 | 3984.88 | 2.08602 | 2(Tie) |
| glaze | 1061.25 | 0.141063 | 1209.42ms | 4926 | 40 | 1559.71 | 4426.68 | 2.31995 | 4(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5697.19 | 0.133458 | 839.871ms | 4926 | 320 | 387.529 | 824.581 | 0.420843 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 5671.45 | 0.278451 | 839.614ms | 4926 | 160 | 851.177 | 828.325 | 0.422938 | 1(Tie) |
| glaze | 3340.36 | 0.437132 | 888.577ms | 4926 | 40 | 1511.78 | 1406.38 | 0.727431 | 3(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2435.93 | 0.125784 | 1101.95ms | 9463 | 30 | 651.476 | 3704.8 | 1.00924 | 1(Win) |
| simdjson (ondemand) | 2251.09 | 0.138003 | 1129.3ms | 9463 | 30 | 918.276 | 4009 | 1.09304 | 2(Loss) |
| simdjson (reflection) | 2189.61 | 0.127054 | 1141.94ms | 9463 | 30 | 822.668 | 4121.57 | 1.12336 | 3(Loss) |
| glaze | 1680.98 | 0.551244 | 1285.07ms | 9463 | 320 | 280267 | 5368.68 | 1.46562 | 4(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9729.26 | 0.30958 | 825.997ms | 9463 | 40 | 329.84 | 927.575 | 0.247342 | 1(Win) |
| glaze | 1640.48 | 0.0255533 | 1285.53ms | 9463 | 320 | 632.354 | 5501.21 | 1.50214 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 5480.2 | 0.230886 | 778.629ms | 2821 | 320 | 411.112 | 490.916 | 0.428538 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 5464.83 | 0.237509 | 775.449ms | 2821 | 1280 | 1749.94 | 492.296 | 0.429295 | 1(Tie) |
| jsonifier | 4189.69 | 0.156043 | 801.548ms | 2821 | 4890 | 4909.51 | 642.127 | 0.566305 | 3(Loss) |
| glaze | 2483.13 | 0.160538 | 838.894ms | 2821 | 80 | 242.021 | 1083.44 | 0.973454 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 6831.19 | 0.180608 | 795.248ms | 4147 | 640 | 699.726 | 578.945 | 0.346126 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 6820.54 | 0.550114 | 802.853ms | 4147 | 40 | 407.003 | 579.85 | 0.346051 | 1(Tie) |
| jsonifier | 5668.49 | 0.128697 | 805.406ms | 4147 | 320 | 257.999 | 697.697 | 0.420048 | 3(Loss) |
| glaze | 3157.43 | 0.251786 | 855.114ms | 4147 | 30 | 298.392 | 1252.57 | 0.767575 | 4(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1883.4 | 0.118705 | 895.98ms | 2821 | 30 | 86.254 | 1428.43 | 1.28996 | 1(Win) |
| glaze | 1864.8 | 0.076842 | 876.485ms | 2821 | 160 | 196.634 | 1442.68 | 1.30404 | 2(Loss) |
| simdjson (reflection) | 1789.25 | 0.13831 | 900.858ms | 2821 | 80 | 345.99 | 1503.6 | 1.3603 | 3(Loss) |
| simdjson (ondemand) | 1372.66 | 0.120838 | 961.938ms | 2821 | 30 | 168.271 | 1959.93 | 1.77907 | 4(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6218.58 | 0.219492 | 797.794ms | 2821 | 80 | 72.1361 | 432.625 | 0.374371 | 1(Win) |
| glaze | 4995.49 | 0.418076 | 816.262ms | 2819 | 30 | 151.868 | 538.167 | 0.469753 | 2(Loss) |
| simdjson (reflection) | 4599.35 | 0.643805 | 786.205ms | 2821 | 30 | 425.444 | 584.933 | 0.514853 | 3(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 2526.06 | 0.257617 | 885.999ms | 4147 | 30 | 488.033 | 1565.63 | 0.96362 | 1(Win) |
| glaze | 2208.48 | 0.128736 | 963.608ms | 4147 | 40 | 212.589 | 1790.78 | 1.10468 | 2(Loss) |
| jsonifier | 2017.97 | 0.0838865 | 935.55ms | 4147 | 160 | 432.456 | 1959.83 | 1.21066 | 3(Loss) |
| simdjson (ondemand) | 1986.33 | 0.055815 | 937.652ms | 4147 | 160 | 197.601 | 1991.06 | 1.22976 | 4(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8281.29 | 0.138844 | 759.533ms | 4147 | 160 | 70.3474 | 477.569 | 0.282988 | 1(Win) |
| glaze | 2084.72 | 0.10882 | 894.373ms | 4145 | 30 | 127.73 | 1896.17 | 1.17044 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3346.19 | 0.0944826 | 7196.45ms | 466906 | 2560 | 4.04671e+07 | 133070 | 0.739734 | 1(Win) |
| glaze | 2587.02 | 0.243478 | 9327.59ms | 466906 | 160 | 2.80996e+07 | 172120 | 0.956865 | 2(Loss) |
| simdjson (ondemand) | 1507.63 | 0.211481 | 7777.43ms | 466906 | 320 | 1.24842e+08 | 295348 | 1.64197 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4559.92 | 0.261771 | 7842.03ms | 699405 | 160 | 2.34588e+07 | 146275 | 0.542826 | 1(Win) |
| glaze | 2199.53 | 0.126168 | 8099.83ms | 699405 | 160 | 2.34217e+07 | 303249 | 1.12551 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3779.13 | 0.261488 | 8608.44ms | 631514 | 160 | 2.77848e+07 | 159364 | 0.655004 | 1(Win) |
| glaze | 2783.76 | 0.117157 | 5678.46ms | 631514 | 320 | 2.05582e+07 | 216347 | 0.889273 | 2(Loss) |
