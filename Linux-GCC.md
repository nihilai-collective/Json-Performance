# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the GCC 16.1.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1212.12 | 2.87057 | 4.7156ms | 1811 | 30 | 50188.9 | 1424.87 | 2.45914 | 1(Win) |
| glaze | 1067.04 | 0.260685 | 1.29728ms | 1811 | 30 | 534.11 | 1618.6 | 2.80547 | 2(Loss) |
| simdjson (ondemand) | 240.878 | 0.178461 | 2.99008ms | 1811 | 30 | 4911.9 | 7170.03 | 12.5815 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 807.662 | 0.197024 | 1.43413ms | 1811 | 30 | 532.524 | 2138.4 | 3.71325 | 1(Win) |
| glaze | 652.981 | 0.194224 | 2.34641ms | 1798 | 30 | 780.378 | 2625.97 | 4.60382 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2108.41 | 0.0898646 | 1.70458ms | 3873 | 30 | 74.3506 | 1751.83 | 1.42128 | 1(Win) |
| glaze | 1987.83 | 0.11384 | 1.40195ms | 3873 | 30 | 134.231 | 1858.1 | 1.50809 | 2(Loss) |
| simdjson (ondemand) | 619.306 | 0.131438 | 2.66824ms | 3873 | 30 | 1843.51 | 5964.07 | 4.89121 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5605.96 | 0.432955 | 1.0401ms | 3873 | 30 | 244.12 | 658.867 | 0.521086 | 1(Win) |
| glaze | 2506.39 | 0.337182 | 1.30285ms | 3873 | 30 | 740.713 | 1473.67 | 1.19364 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2157.3 | 0.185946 | 1.33189ms | 3862 | 30 | 302.34 | 1707.27 | 1.38767 | 1(Win) |
| glaze | 1808.48 | 0.146054 | 1.40685ms | 3862 | 30 | 265.426 | 2036.57 | 1.65911 | 2(Loss) |
| simdjson (ondemand) | 561.241 | 4.17207 | 2.75847ms | 3862 | 30 | 2.2488e+06 | 6562.4 | 5.38491 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5564.14 | 0.26236 | 1.00963ms | 3862 | 30 | 90.4782 | 661.933 | 0.524038 | 1(Win) |
| glaze | 2523.59 | 0.369504 | 1.29413ms | 3862 | 30 | 872.464 | 1459.47 | 1.18638 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2646.12 | 1.01249 | 1.04274ms | 905 | 30 | 327.178 | 326.167 | 1.07565 | 1(Win) |
| glaze | 868.605 | 0.0902075 | 1.15333ms | 905 | 30 | 24.1023 | 993.633 | 3.35937 | 2(Loss) |
| simdjson (ondemand) | 196.064 | 0.18982 | 2.15988ms | 905 | 30 | 2094.62 | 4402 | 15.421 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3133.9 | 0.450168 | 0.904872ms | 905 | 30 | 46.1103 | 275.4 | 0.897974 | 1(Win) |
| glaze | 863.075 | 0.339912 | 1.10857ms | 905 | 30 | 346.621 | 1000 | 3.45414 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3390.06 | 0.189925 | 1.68124ms | 9578 | 30 | 785.633 | 2694.43 | 0.885787 | 1(Win) |
| glaze | 3265.03 | 0.226679 | 14.8287ms | 9578 | 80 | 3217.28 | 2797.61 | 0.920966 | 2(Loss) |
| simdjson (ondemand) | 1397.51 | 0.146103 | 2.79562ms | 9578 | 30 | 2735.75 | 6536.1 | 2.16724 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7889.86 | 0.184869 | 2.71339ms | 9578 | 40 | 183.23 | 1157.72 | 0.375786 | 1(Win) |
| glaze | 5012.78 | 0.286773 | 1.43873ms | 9578 | 30 | 819.2 | 1822.2 | 0.593823 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 800.55 | 1.13597 | 742.661ms | 2090234 | 30 | 2.40032e+10 | 2.49004e+06 | 3.79564 | 1(Win) |
| simdjson (ondemand) | 743.076 | 0.450912 | 800.225ms | 2090234 | 30 | 4.38964e+09 | 2.68264e+06 | 4.08887 | 2(Loss) |
| glaze | 689.53 | 0.954362 | 861.877ms | 2090234 | 30 | 2.28366e+10 | 2.89096e+06 | 4.40661 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1763.1 | 0.459993 | 792.765ms | 2090234 | 40 | 1.08193e+09 | 1.13062e+06 | 1.72331 | 1(Win) |
| glaze | 1405.41 | 0.384066 | 426.411ms | 2090234 | 30 | 8.90255e+08 | 1.41837e+06 | 2.16177 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2130.98 | 0.496443 | 894.34ms | 6661897 | 30 | 6.57199e+09 | 2.98139e+06 | 1.4256 | 1(Win) |
| jsonifier | 1955.82 | 0.263324 | 982.67ms | 6661897 | 30 | 2.19503e+09 | 3.2484e+06 | 1.55362 | 2(Loss) |
| glaze | 1730.99 | 0.260709 | 1096.47ms | 6661897 | 30 | 2.74691e+09 | 3.67033e+06 | 1.75525 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4368.12 | 0.288765 | 437.094ms | 6661897 | 30 | 5.29197e+08 | 1.45447e+06 | 0.695491 | 1(Win) |
| glaze | 3000.5 | 0.404366 | 645.702ms | 6661897 | 30 | 2.19927e+09 | 2.11741e+06 | 1.01236 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1758.3 | 0.870543 | 81.6569ms | 500299 | 30 | 1.67408e+08 | 271354 | 1.72804 | 1(Tie) |
| glaze STATISTICAL TIE | 1733.63 | 1.0229 | 415.803ms | 500299 | 80 | 6.34029e+08 | 275217 | 1.75254 | 1(Tie) |
| simdjson (ondemand) | 1170.44 | 0.404989 | 124.137ms | 500299 | 30 | 8.17657e+07 | 407644 | 2.59608 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6250.02 | 0.853392 | 247.919ms | 500299 | 160 | 6.79068e+07 | 76339.3 | 0.485985 | 1(Win) |
| glaze | 5514.42 | 1.42708 | 26.9474ms | 500299 | 30 | 4.57379e+07 | 86522.7 | 0.550754 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2969.09 | 0.461287 | 141.203ms | 1439562 | 30 | 1.36482e+08 | 462388 | 1.02341 | 1(Win) |
| glaze | 2713.35 | 0.950953 | 152.937ms | 1439562 | 30 | 6.94526e+08 | 505970 | 1.11979 | 2(Loss) |
| jsonifier | 2608.47 | 0.536916 | 159.949ms | 1439562 | 30 | 2.39565e+08 | 526314 | 1.16493 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10362 | 1.78021 | 40.6779ms | 1439562 | 30 | 1.66892e+08 | 132491 | 0.29312 | 1(Win) |
| glaze | 6434.78 | 0.658975 | 65.9728ms | 1439584 | 30 | 5.93015e+07 | 213355 | 0.472063 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1839.09 | 0.79661 | 9.92502ms | 56369 | 30 | 1.62663e+06 | 29230.6 | 1.65104 | 1(Win) |
| jsonifier | 1770.02 | 0.743064 | 10.3881ms | 56369 | 30 | 1.52792e+06 | 30371.3 | 1.71497 | 2(Loss) |
| simdjson (ondemand) | 1244.97 | 1.2668 | 13.9343ms | 56369 | 30 | 8.9763e+06 | 43179.8 | 2.43937 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6351.15 | 0.738178 | 37.7389ms | 56369 | 160 | 624624 | 8464.24 | 0.476779 | 1(Win) |
| jsonifier | 5722.76 | 0.497964 | 45.0385ms | 56369 | 160 | 350095 | 9393.66 | 0.528889 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2416.6 | 0.264392 | 12.3937ms | 94370 | 30 | 290856 | 37241.7 | 1.25665 | 1(Win) |
| simdjson (ondemand) | 2024.61 | 0.151792 | 14.5875ms | 94370 | 30 | 136585 | 44452.1 | 1.49994 | 2(Loss) |
| jsonifier | 1954.55 | 1.24339 | 15.2623ms | 94370 | 30 | 9.83345e+06 | 46045.4 | 1.55385 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8583.11 | 1.72923 | 4.08892ms | 94370 | 30 | 986290 | 10485.5 | 0.352874 | 1(Win) |
| glaze | 6256.89 | 1.44581 | 5.29345ms | 94370 | 30 | 1.29747e+06 | 14383.9 | 0.484396 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1446.67 | 0.304274 | 15.9898ms | 11812 | 80 | 44908.4 | 7786.7 | 2.09368 | 1(Win) |
| jsonifier | 1285.34 | 3.25259 | 8.12387ms | 11812 | 40 | 3.25036e+06 | 8764.08 | 2.35707 | 2(Loss) |
| simdjson (ondemand) | 1043.1 | 0.590199 | 9.50664ms | 11812 | 40 | 162498 | 10799.3 | 2.90624 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4953.96 | 0.641611 | 1.55388ms | 11812 | 30 | 6385.68 | 2273.9 | 0.604665 | 1(Win) |
| glaze | 3941.15 | 0.845596 | 8.42627ms | 11812 | 80 | 46732.2 | 2858.25 | 0.763482 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2457.25 | 3.40552 | 190.432ms | 31235 | 640 | 1.09077e+08 | 12122.5 | 1.23381 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2330.28 | 0.0706616 | 4.93429ms | 31235 | 30 | 2447.69 | 12783 | 1.30163 | 1(Tie) |
| glaze | 2296.4 | 0.12374 | 4.88516ms | 31235 | 30 | 7729.14 | 12971.6 | 1.32081 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7631.06 | 1.4852 | 4.65937ms | 31235 | 40 | 134444 | 3903.53 | 0.395427 | 1(Win) |
| glaze | 6333.63 | 0.775213 | 11.3474ms | 31235 | 80 | 106343 | 4703.15 | 0.476775 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3283.96 | 0.727523 | 10.6167ms | 108313 | 30 | 1.57102e+06 | 31454.5 | 0.924441 | 1(Win) |
| glaze | 2090.6 | 0.986191 | 15.6112ms | 108313 | 30 | 7.12302e+06 | 49409.5 | 1.45268 | 2(Loss) |
| simdjson (ondemand) | 1625.97 | 0.53639 | 20.0246ms | 108313 | 30 | 3.48353e+06 | 63528.5 | 1.86829 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6698.54 | 0.425157 | 5.53018ms | 108313 | 30 | 128950 | 15420.6 | 0.452932 | 1(Win) |
| glaze | 5729.12 | 1.34805 | 6.29331ms | 108313 | 30 | 1.77223e+06 | 18029.9 | 0.529618 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2922.74 | 0.592873 | 22.925ms | 213963 | 30 | 5.13974e+06 | 69814.9 | 1.03945 | 1(Win) |
| simdjson (ondemand) | 2872.78 | 0.411122 | 112.787ms | 213963 | 80 | 6.82187e+06 | 71029.1 | 1.05746 | 2(Loss) |
| glaze | 2733.61 | 0.546301 | 23.5863ms | 213963 | 30 | 4.98871e+06 | 74645.2 | 1.1113 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10937.6 | 0.227409 | 6.52542ms | 213963 | 30 | 53996.9 | 18655.9 | 0.277386 | 1(Win) |
| glaze | 5697.65 | 1.97998 | 26.7128ms | 213963 | 40 | 2.01125e+07 | 35813.2 | 0.532818 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 717.839 | 0.31616 | 731.351ms | 1834197 | 30 | 1.78063e+09 | 2.4368e+06 | 4.23272 | 1(Win) |
| glaze | 606.656 | 0.337986 | 871.422ms | 1834197 | 30 | 2.84922e+09 | 2.88339e+06 | 5.0087 | 2(Loss) |
| simdjson (ondemand) | 154.307 | 0.493818 | 3373.29ms | 1834197 | 30 | 9.40098e+10 | 1.1336e+07 | 19.6931 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1072.88 | 0.656581 | 489.422ms | 1834197 | 30 | 3.43786e+09 | 1.6304e+06 | 2.83179 | 1(Win) |
| glaze | 960.446 | 0.510714 | 548.615ms | 1833577 | 30 | 2.59376e+09 | 1.82065e+06 | 3.16374 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2690.01 | 0.47757 | 1068.96ms | 9930848 | 30 | 8.48126e+09 | 3.52073e+06 | 1.1296 | 1(Win) |
| glaze | 2378.5 | 0.350193 | 2766.9ms | 9930848 | 40 | 7.77753e+09 | 3.98184e+06 | 1.27749 | 2(Loss) |
| simdjson (ondemand) | 746.467 | 0.593135 | 3798.74ms | 9930848 | 30 | 1.69895e+11 | 1.26875e+07 | 4.07105 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4122.95 | 0.379877 | 702.052ms | 9930848 | 30 | 2.28436e+09 | 2.29709e+06 | 0.736932 | 1(Win) |
| glaze | 3235.09 | 0.572268 | 866.475ms | 9930228 | 30 | 8.41909e+09 | 2.92734e+06 | 0.938986 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 725.945 | 0.286609 | 3654.71ms | 1834197 | 80 | 3.81552e+09 | 2.40959e+06 | 4.18538 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 575.291 | 0.356365 | 2153.16ms | 1834197 | 40 | 4.69642e+09 | 3.0406e+06 | 5.28108 | 2(Tie) |
| glaze STATISTICAL TIE | 566.597 | 0.716471 | 920.473ms | 1834197 | 30 | 1.46778e+10 | 3.08725e+06 | 5.36208 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1060.29 | 0.432212 | 1167.36ms | 1834197 | 40 | 2.03374e+09 | 1.64976e+06 | 2.86545 | 1(Win) |
| glaze | 907.984 | 0.641639 | 572.981ms | 1833577 | 30 | 4.58084e+09 | 1.92584e+06 | 3.34624 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2643.43 | 0.403138 | 1070.56ms | 9930848 | 30 | 6.25846e+09 | 3.58277e+06 | 1.14938 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2619.32 | 0.796364 | 1103.86ms | 9930848 | 30 | 2.48738e+10 | 3.61575e+06 | 1.15992 | 1(Tie) |
| glaze | 2402.81 | 0.299459 | 1198.77ms | 9930848 | 30 | 4.17956e+09 | 3.94155e+06 | 1.26454 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4093.1 | 0.257095 | 7244.28ms | 9930848 | 160 | 5.66209e+09 | 2.31385e+06 | 0.742322 | 1(Win) |
| glaze | 2504.39 | 0.512858 | 11674ms | 9930228 | 160 | 6.01768e+10 | 3.78144e+06 | 1.213 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1188.08 | 0.795938 | 363.061ms | 642697 | 40 | 6.74436e+08 | 515895 | 2.55695 | 1(Win) |
| jsonifier | 1091.42 | 0.970253 | 169.095ms | 642697 | 30 | 8.90674e+08 | 561583 | 2.7833 | 2(Loss) |
| glaze | 1042.48 | 0.937633 | 177.922ms | 642697 | 30 | 9.11733e+08 | 587950 | 2.91436 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1862.57 | 0.852159 | 99.58ms | 642697 | 30 | 2.35911e+08 | 329074 | 1.63115 | 1(Win) |
| glaze | 1545.02 | 0.768063 | 119.876ms | 642692 | 30 | 2.78517e+08 | 396706 | 1.96658 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2240.97 | 0.615955 | 159.318ms | 1225964 | 30 | 3.09814e+08 | 521724 | 1.35577 | 1(Win) |
| glaze | 1750.57 | 0.65061 | 201.03ms | 1225964 | 30 | 5.66447e+08 | 667880 | 1.73555 | 2(Loss) |
| jsonifier | 1548.84 | 0.539379 | 227.536ms | 1225964 | 30 | 4.97337e+08 | 754868 | 1.96181 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3062.37 | 0.666749 | 116.255ms | 1225964 | 30 | 1.94395e+08 | 381786 | 0.99207 | 1(Win) |
| glaze | 2557.39 | 0.763378 | 138.848ms | 1225970 | 30 | 3.65398e+08 | 457175 | 1.18791 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1044.4 | 0.510842 | 264.956ms | 409725 | 40 | 1.46111e+08 | 374132 | 2.90922 | 1(Win) |
| glaze STATISTICAL TIE | 927.329 | 1.04012 | 127.006ms | 409725 | 30 | 5.76246e+08 | 421365 | 3.27609 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 926.946 | 1.2924 | 127.38ms | 409725 | 30 | 8.90414e+08 | 421539 | 3.27754 | 2(Tie) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5351.85 | 0.811741 | 114.152ms | 409725 | 80 | 2.80997e+07 | 73011 | 0.567494 | 1(Win) |
| glaze | 3624.17 | 2.12042 | 34.0261ms | 409725 | 30 | 1.56795e+08 | 107816 | 0.838105 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1701.42 | 0.603514 | 134.802ms | 785750 | 30 | 2.11953e+08 | 440425 | 1.7857 | 1(Win) |
| glaze | 1457.34 | 0.374639 | 156.505ms | 785750 | 30 | 1.11325e+08 | 514189 | 2.08502 | 2(Loss) |
| jsonifier | 1367.38 | 0.861398 | 165.627ms | 785750 | 30 | 6.68527e+08 | 548018 | 2.22192 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6736.08 | 1.04492 | 173.89ms | 785750 | 80 | 1.08097e+08 | 111244 | 0.450883 | 1(Win) |
| glaze | 4270.17 | 1.81716 | 53.4901ms | 785750 | 30 | 3.05061e+08 | 175485 | 0.711385 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5573.43 | 0.389843 | 156.878ms | 264040 | 160 | 4.96358e+06 | 45180.1 | 0.544894 | 1(Win) |
| simdjson (ondemand) | 5224.7 | 1.17847 | 15.7185ms | 264040 | 30 | 9.67769e+06 | 48195.7 | 0.58132 | 2(Loss) |
| glaze | 3032 | 0.90848 | 25.8812ms | 264040 | 30 | 1.70779e+07 | 83050.2 | 1.002 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7304.44 | 0.68173 | 40.725ms | 399947 | 40 | 5.06893e+06 | 52217.4 | 0.415789 | 1(Win) |
| simdjson (ondemand) | 6990.66 | 0.619365 | 17.5254ms | 399947 | 30 | 3.42597e+06 | 54561.3 | 0.43452 | 2(Loss) |
| glaze | 3602.94 | 1.00089 | 331.692ms | 399947 | 160 | 1.7963e+08 | 105863 | 0.842859 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1866.6 | 1.81692 | 198.957ms | 264040 | 80 | 4.80615e+08 | 134902 | 1.62747 | 1(Win) |
| glaze STATISTICAL TIE | 1602.15 | 1.44262 | 49.8789ms | 264040 | 30 | 1.54227e+08 | 157169 | 1.89644 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1583.21 | 0.784973 | 49.009ms | 264040 | 30 | 4.67622e+07 | 159049 | 1.91923 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6981.93 | 2.06317 | 27.0604ms | 264040 | 40 | 2.21473e+07 | 36065.7 | 0.434818 | 1(Win) |
| glaze | 6155.85 | 1.13062 | 31.5594ms | 263923 | 40 | 8.54816e+06 | 40887.3 | 0.493298 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2266.15 | 0.684017 | 53.5173ms | 399947 | 30 | 3.97631e+07 | 168311 | 1.34082 | 1(Win) |
| glaze | 1881.44 | 0.747789 | 62.0324ms | 399947 | 30 | 6.89449e+07 | 202727 | 1.61511 | 2(Loss) |
| jsonifier | 1802.39 | 0.937506 | 326.669ms | 399947 | 80 | 3.14881e+08 | 211619 | 1.68579 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8752.14 | 2.19825 | 32.2565ms | 399947 | 40 | 3.67105e+07 | 43580.1 | 0.346905 | 1(Win) |
| glaze | 5207.38 | 0.948882 | 239.449ms | 399830 | 160 | 7.72426e+07 | 73224.5 | 0.583204 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2428.35 | 2.03706 | 55.9002ms | 466906 | 30 | 4.18569e+08 | 183366 | 1.251 | 1(Win) |
| glaze | 2304.03 | 1.26206 | 58.5386ms | 466906 | 30 | 1.78469e+08 | 193259 | 1.31853 | 2(Loss) |
| simdjson (ondemand) | 1288.07 | 0.925598 | 106.92ms | 466906 | 30 | 3.07148e+08 | 345693 | 2.35881 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3592.09 | 1.14952 | 135.883ms | 699405 | 40 | 1.82245e+08 | 185687 | 0.845782 | 1(Win) |
| glaze | 3163.82 | 0.509509 | 64.5564ms | 699405 | 30 | 3.46146e+07 | 210822 | 0.960385 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3623.27 | 1.25008 | 52.6344ms | 631514 | 30 | 1.29528e+08 | 166220 | 0.838505 | 1(Win) |
| glaze | 2342.13 | 0.878135 | 77.5649ms | 631514 | 30 | 1.52964e+08 | 257142 | 1.29706 | 2(Loss) |
