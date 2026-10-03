# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

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
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX2` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10.000000% AND mean shift < 5.000000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

Every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. Parser instances are reused.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1001.91 | 0.336894 | 973.459ms | 905 | 30 | 252.668 | 861.433 | 2.23252 | 1(Win) |
| glaze | 770.079 | 0.116959 | 999.401ms | 905 | 160 | 274.924 | 1120.76 | 2.92515 | 2(Loss) |
| simdjson (ondemand) | 103.381 | 0.467967 | 1711.93ms | 905 | 40 | 61053.4 | 8348.52 | 22.4573 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 853.558 | 0.233741 | 995.795ms | 905 | 320 | 1787.52 | 1011.15 | 2.63105 | 1(Win) |
| glaze | 95.5333 | 2.76423 | 1780.2ms | 905 | 2560 | 1.59653e+08 | 9034.28 | 24.3116 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 713.488 | 0.167915 | 1139.9ms | 1811 | 80 | 1321.7 | 2420.65 | 3.21895 | 1(Win) |
| glaze | 544.46 | 0.221614 | 1222.89ms | 1811 | 160 | 7907.18 | 3172.14 | 4.23406 | 2(Loss) |
| simdjson (ondemand) | 147.57 | 0.695711 | 2073.36ms | 1811 | 40 | 265191 | 11703.6 | 15.7543 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 182.858 | 0.0745633 | 1832.89ms | 1811 | 30 | 1487.93 | 9445.07 | 12.7041 | 1(Win) |
| glaze | 131.135 | 1.02819 | 2132.85ms | 1798 | 2560 | 4.62737e+07 | 13075.9 | 17.7326 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1634.16 | 0.142546 | 1106.91ms | 3862 | 80 | 825.724 | 2253.81 | 1.40357 | 1(Win) |
| glaze | 992.559 | 0.188848 | 1243ms | 3862 | 80 | 3928.49 | 3710.7 | 2.32582 | 2(Loss) |
| simdjson (ondemand) | 302.748 | 3.07767 | 2037.91ms | 3862 | 320 | 4.48598e+07 | 12165.5 | 7.67936 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 446.964 | 0.373309 | 1721.51ms | 3862 | 30 | 28388.2 | 8240.23 | 5.19329 | 1(Win) |
| glaze | 434.944 | 0.664747 | 1735.68ms | 3862 | 640 | 2.02791e+06 | 8467.96 | 5.33821 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 670.896 | 0.996428 | 2199.82ms | 9578 | 4890 | 8.99994e+07 | 13615.1 | 3.46481 | 1(Win) |
| jsonifier | 625.211 | 0.738406 | 2279.43ms | 9578 | 4890 | 5.69109e+07 | 14609.9 | 3.71895 | 2(Loss) |
| simdjson (ondemand) | 592.659 | 0.175905 | 2446.56ms | 9578 | 30 | 22050.5 | 15412.4 | 3.92491 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1252.81 | 1.15728 | 1610.7ms | 9578 | 320 | 2.27829e+06 | 7291.03 | 1.85202 | 1(Win) |
| glaze | 1051.5 | 0.0903585 | 1771.1ms | 9578 | 30 | 1848.37 | 8686.9 | 2.20862 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1876.96 | 0.167783 | 1084.71ms | 3873 | 80 | 872.104 | 1967.85 | 1.21882 | 1(Win) |
| glaze | 1109.78 | 0.172995 | 1220.22ms | 3873 | 30 | 994.51 | 3328.2 | 2.07804 | 2(Loss) |
| simdjson (ondemand) | 327.606 | 0.616628 | 2050.17ms | 3873 | 30 | 144997 | 11274.5 | 7.09508 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 451.077 | 0.663117 | 1719.55ms | 3873 | 640 | 1.88692e+06 | 8188.37 | 5.14689 | 1(Win) |
| glaze | 425.759 | 0.528139 | 1759.56ms | 3873 | 320 | 671759 | 8675.28 | 5.45444 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 489.438 | 0.217033 | 6135.57ms | 2090234 | 30 | 2.34406e+09 | 4.07284e+06 | 4.76488 | 1(Win) |
| glaze | 374.675 | 0.134486 | 7992.95ms | 2090234 | 30 | 1.53587e+09 | 5.32035e+06 | 6.22425 | 2(Loss) |
| simdjson (ondemand) | 318.827 | 0.110612 | 9401.9ms | 2090234 | 40 | 1.91312e+09 | 6.2523e+06 | 7.31461 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 734.769 | 0.0373521 | 8431.78ms | 2090234 | 160 | 1.643e+08 | 2.71297e+06 | 3.17386 | 1(Win) |
| glaze | 662.73 | 0.0716637 | 9406.21ms | 2090234 | 40 | 1.85855e+08 | 3.00787e+06 | 3.51891 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1266.38 | 0.114862 | 7547.39ms | 6661897 | 30 | 9.96202e+08 | 5.0169e+06 | 1.84153 | 1(Win) |
| glaze | 979.552 | 0.0848315 | 9786.02ms | 6661897 | 40 | 1.21092e+09 | 6.4859e+06 | 2.38073 | 2(Loss) |
| simdjson (ondemand) | 943.716 | 0.102553 | 10091.2ms | 6661897 | 30 | 1.42998e+09 | 6.7322e+06 | 2.47113 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2340.15 | 0.0770438 | 8451.41ms | 6661897 | 30 | 1.31252e+08 | 2.7149e+06 | 0.996538 | 1(Win) |
| glaze | 1441.32 | 0.106742 | 6632.01ms | 6661897 | 80 | 1.77108e+09 | 4.40795e+06 | 1.61795 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 938.672 | 0.347962 | 6578.39ms | 500299 | 40 | 1.25128e+08 | 508295 | 2.48423 | 1(Win) |
| glaze | 873.405 | 0.19676 | 7037.66ms | 500299 | 160 | 1.84851e+08 | 546278 | 2.66988 | 2(Loss) |
| simdjson (ondemand) | 605.321 | 0.368724 | 5007.84ms | 500299 | 30 | 2.53403e+08 | 788214 | 3.85236 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5137.5 | 0.882924 | 5266.76ms | 500299 | 80 | 5.37887e+07 | 92870.4 | 0.453722 | 1(Win) |
| glaze | 1975.72 | 0.172182 | 6367.43ms | 500299 | 640 | 1.10654e+08 | 241493 | 1.18014 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1844.49 | 0.0782527 | 9610.43ms | 1439562 | 640 | 2.17114e+08 | 744312 | 1.26426 | 1(Win) |
| glaze | 1570.2 | 0.128233 | 5571.25ms | 1439562 | 160 | 2.01127e+08 | 874331 | 1.48515 | 2(Loss) |
| simdjson (ondemand) | 1551.84 | 0.0901618 | 5624.23ms | 1439562 | 320 | 2.03593e+08 | 884676 | 1.50269 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12852.3 | 0.239796 | 5899.48ms | 1439562 | 1280 | 8.39838e+07 | 106820 | 0.181377 | 1(Win) |
| glaze | 2188.09 | 0.314709 | 8100.18ms | 1439584 | 40 | 1.55963e+08 | 627440 | 1.06573 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 901.458 | 0.299524 | 6771.4ms | 56369 | 1280 | 4.08379e+07 | 59634.1 | 2.58516 | 1(Win) |
| glaze | 804.886 | 0.221409 | 7481.99ms | 56369 | 2560 | 5.59812e+07 | 66789.1 | 2.8955 | 2(Loss) |
| simdjson (ondemand) | 706.535 | 0.157347 | 8400.51ms | 56369 | 4890 | 7.00871e+07 | 76086.4 | 3.29874 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6091.14 | 1.75462 | 1750.91ms | 56369 | 4890 | 1.17262e+08 | 8825.55 | 0.381308 | 1(Win) |
| glaze | 1966.87 | 0.472136 | 3531.46ms | 56369 | 4890 | 8.14279e+07 | 27331.6 | 1.184 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1158.46 | 0.187854 | 8528.86ms | 94370 | 4890 | 1.04149e+08 | 77688.1 | 2.01182 | 1(Win) |
| simdjson (ondemand) | 1131.44 | 0.318337 | 8796.11ms | 94370 | 1280 | 8.20706e+07 | 79543 | 2.05931 | 2(Loss) |
| jsonifier | 1084.63 | 0.546773 | 9096.72ms | 94370 | 640 | 1.31735e+08 | 82976.1 | 2.14878 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9968.8 | 0.346125 | 1828.68ms | 94370 | 160 | 156232 | 9027.99 | 0.232931 | 1(Win) |
| glaze | 1761.36 | 0.203374 | 5933.49ms | 94370 | 4890 | 5.28045e+07 | 51095.9 | 1.32277 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 899.748 | 0.0516884 | 2168.89ms | 11812 | 80 | 3350.28 | 12520 | 2.58418 | 1(Win) |
| glaze | 716.217 | 0.567565 | 2403.83ms | 11812 | 4890 | 3.89672e+07 | 15728.2 | 3.24656 | 2(Loss) |
| simdjson (ondemand) | 596.259 | 0.66558 | 2697.49ms | 11812 | 4890 | 7.73191e+07 | 18892.5 | 3.90049 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4402.32 | 0.253492 | 1163.93ms | 11812 | 30 | 1262.21 | 2558.83 | 0.522065 | 1(Win) |
| glaze | 1212.72 | 0.393845 | 1847.66ms | 11812 | 40 | 53534.9 | 9288.88 | 1.91538 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1598.44 | 0.0655371 | 2865.32ms | 31235 | 30 | 4474.92 | 18635.7 | 1.45601 | 1(Win) |
| glaze | 1406.99 | 0.0493811 | 3067.73ms | 31235 | 30 | 3279.01 | 21171.4 | 1.65464 | 2(Loss) |
| jsonifier | 1377 | 0.536732 | 2991.89ms | 31235 | 4890 | 6.59237e+07 | 21632.6 | 1.69061 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10437.9 | 0.219364 | 1188.73ms | 31235 | 40 | 1567.64 | 2853.82 | 0.220628 | 1(Win) |
| glaze | 1881.97 | 0.162869 | 2518.04ms | 31235 | 40 | 26582.4 | 15828.1 | 1.23621 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1242.55 | 0.608925 | 9086.93ms | 108313 | 320 | 8.19993e+07 | 83131.6 | 1.87578 | 1(Win) |
| glaze | 1064.79 | 0.178416 | 5418.5ms | 108313 | 2560 | 7.66905e+07 | 97009.9 | 2.18898 | 2(Loss) |
| simdjson (ondemand) | 826.156 | 0.129791 | 6826.4ms | 108313 | 2560 | 6.74161e+07 | 125031 | 2.82176 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9196.68 | 0.99694 | 2020.53ms | 108313 | 30 | 376147 | 11231.8 | 0.25273 | 1(Win) |
| glaze | 1768.97 | 0.174512 | 6653ms | 108313 | 4890 | 5.07788e+07 | 58393 | 1.31734 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1513.21 | 0.164959 | 7362.45ms | 213963 | 1280 | 6.33348e+07 | 134846 | 1.5405 | 1(Win) |
| glaze | 1459.72 | 0.174199 | 7556.07ms | 213963 | 1280 | 7.58991e+07 | 139787 | 1.59703 | 2(Loss) |
| jsonifier | 1257.64 | 0.261318 | 8753.79ms | 213963 | 640 | 1.15048e+08 | 162249 | 1.8537 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14197.8 | 0.783136 | 2299.88ms | 213963 | 2560 | 3.24302e+07 | 14372 | 0.163577 | 1(Win) |
| glaze | 1740.04 | 0.13836 | 6454.39ms | 213963 | 2560 | 6.73943e+07 | 117268 | 1.33966 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 423.327 | 0.0689349 | 6223.28ms | 1834197 | 80 | 6.49096e+08 | 4.13209e+06 | 5.50883 | 1(Win) |
| glaze | 362.396 | 0.0921722 | 7296.88ms | 1834197 | 40 | 7.91745e+08 | 4.82684e+06 | 6.43508 | 2(Loss) |
| simdjson (ondemand) | 302.262 | 0.0890771 | 8699.74ms | 1834197 | 30 | 7.97221e+08 | 5.78712e+06 | 7.7153 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 482.148 | 0.0695208 | 5453.04ms | 1834197 | 30 | 1.90846e+08 | 3.62799e+06 | 4.83679 | 1(Win) |
| glaze | 399.028 | 0.053453 | 6579.3ms | 1833577 | 80 | 4.38962e+08 | 4.38224e+06 | 5.84434 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1601.68 | 0.151565 | 8890.52ms | 9930848 | 30 | 2.40958e+09 | 5.91303e+06 | 1.45601 | 1(Win) |
| simdjson (ondemand) | 1403.75 | 0.0715319 | 10149.9ms | 9930848 | 80 | 1.86331e+09 | 6.7468e+06 | 1.66128 | 2(Loss) |
| glaze | 1384.48 | 0.0809538 | 10303.1ms | 9930848 | 30 | 9.20016e+08 | 6.84069e+06 | 1.68443 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2525.89 | 0.0769864 | 5642.75ms | 9930848 | 40 | 3.33297e+08 | 3.74949e+06 | 0.923257 | 1(Win) |
| glaze | 1617.71 | 0.111877 | 8865.47ms | 9930228 | 30 | 1.28682e+09 | 5.85407e+06 | 1.44158 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 435.789 | 0.130431 | 6004.32ms | 1834197 | 80 | 2.19276e+09 | 4.01393e+06 | 5.35132 | 1(Win) |
| glaze | 356.585 | 0.13509 | 7422.09ms | 1834197 | 40 | 1.7566e+09 | 4.90549e+06 | 6.53997 | 2(Loss) |
| simdjson (ondemand) | 294.325 | 0.0712712 | 8965.03ms | 1834197 | 30 | 5.38253e+08 | 5.94317e+06 | 7.92339 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 480.676 | 0.0513682 | 5486.44ms | 1834197 | 40 | 1.39777e+08 | 3.6391e+06 | 4.85164 | 1(Win) |
| glaze | 392.873 | 0.100857 | 6681.28ms | 1833577 | 30 | 6.0454e+08 | 4.45089e+06 | 5.93591 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1643.07 | 0.255507 | 8686.41ms | 9930848 | 30 | 6.50713e+09 | 5.7641e+06 | 1.41933 | 1(Win) |
| simdjson (ondemand) | 1389.62 | 0.104819 | 10271.9ms | 9930848 | 80 | 4.08278e+09 | 6.8154e+06 | 1.67812 | 2(Loss) |
| glaze | 1359.17 | 0.230178 | 10490.4ms | 9930848 | 80 | 2.05798e+10 | 6.96806e+06 | 1.71579 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2526.32 | 0.062181 | 5647.8ms | 9930848 | 40 | 2.17356e+08 | 3.74885e+06 | 0.923101 | 1(Win) |
| glaze | 1407.72 | 0.127096 | 9994.84ms | 9930228 | 40 | 2.92423e+09 | 6.72735e+06 | 1.65656 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 755.902 | 0.216493 | 5200.24ms | 642697 | 40 | 1.23262e+08 | 810851 | 3.08497 | 1(Win) |
| jsonifier | 653.956 | 0.092091 | 5984.34ms | 642697 | 160 | 1.19199e+08 | 937256 | 3.56589 | 2(Loss) |
| simdjson (ondemand) | 589.981 | 0.0602493 | 6623.64ms | 642697 | 320 | 1.25369e+08 | 1.03889e+06 | 3.95265 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 810.392 | 0.171157 | 9761.78ms | 642697 | 40 | 6.70301e+07 | 756330 | 2.87754 | 1(Win) |
| glaze | 656.721 | 0.18869 | 5929.27ms | 642692 | 80 | 2.48104e+08 | 933302 | 3.55088 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1144.17 | 0.0701385 | 6503.87ms | 1225964 | 320 | 1.64375e+08 | 1.02185e+06 | 2.03812 | 1(Win) |
| simdjson (ondemand) | 1074.92 | 0.166818 | 6933.51ms | 1225964 | 30 | 9.87673e+07 | 1.08768e+06 | 2.16947 | 2(Loss) |
| jsonifier | 952.624 | 0.151272 | 8034.53ms | 1225964 | 30 | 1.03407e+08 | 1.22732e+06 | 2.448 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1528.44 | 0.0501796 | 9809.25ms | 1225964 | 640 | 9.42957e+07 | 764943 | 1.52571 | 1(Win) |
| glaze | 1073.16 | 0.101604 | 6927.47ms | 1225970 | 80 | 9.80266e+07 | 1.08947e+06 | 2.17302 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 724.559 | 0.0847924 | 6960.46ms | 409725 | 640 | 1.33823e+08 | 539286 | 3.21834 | 1(Win) |
| glaze | 594.421 | 0.212014 | 8511.27ms | 409725 | 30 | 5.82705e+07 | 657353 | 3.92302 | 2(Loss) |
| simdjson (ondemand) | 533.618 | 0.0689345 | 9423.91ms | 409725 | 640 | 1.63071e+08 | 732255 | 4.36997 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2957.66 | 0.25729 | 7201.26ms | 409725 | 640 | 7.3946e+07 | 132113 | 0.788149 | 1(Win) |
| glaze | 1393.37 | 0.156994 | 7349.47ms | 409725 | 640 | 1.24052e+08 | 280432 | 1.67339 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 973.416 | 0.0613976 | 9941.15ms | 785750 | 640 | 1.42973e+08 | 769814 | 2.39562 | 1(Win) |
| jsonifier | 960.472 | 0.123356 | 10129.1ms | 785750 | 160 | 1.48197e+08 | 780189 | 2.4279 | 2(Loss) |
| glaze | 892.887 | 0.11938 | 5323.4ms | 785750 | 320 | 3.21211e+08 | 839244 | 2.6117 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5080.07 | 0.222857 | 7976.1ms | 785750 | 640 | 6.91612e+07 | 147508 | 0.458908 | 1(Win) |
| glaze | 1617.29 | 0.255483 | 5957.81ms | 785750 | 80 | 1.121e+08 | 463335 | 1.44184 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2766.69 | 0.17979 | 5103.89ms | 264040 | 2560 | 6.85472e+07 | 91014.3 | 0.842472 | 1(Win) |
| jsonifier | 2638.24 | 0.161099 | 5308.24ms | 264040 | 2560 | 6.05257e+07 | 95445.6 | 0.883466 | 2(Loss) |
| glaze | 1742.96 | 0.243324 | 7936.56ms | 264040 | 640 | 7.90884e+07 | 144471 | 1.33751 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3572.04 | 0.576832 | 5886.94ms | 399947 | 160 | 6.07004e+07 | 106779 | 0.65257 | 1(Win) |
| jsonifier | 3466.99 | 0.205905 | 6073.8ms | 399947 | 1280 | 6.56813e+07 | 110014 | 0.672331 | 2(Loss) |
| glaze | 2328.72 | 0.219583 | 8829.46ms | 399947 | 640 | 8.27843e+07 | 163789 | 1.00113 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 917.222 | 0.159062 | 7228.69ms | 264040 | 640 | 1.22041e+08 | 274533 | 2.54168 | 1(Win) |
| glaze | 896.913 | 0.13198 | 7360.82ms | 264040 | 1280 | 1.75738e+08 | 280750 | 2.59957 | 2(Loss) |
| simdjson (ondemand) | 830.81 | 0.137798 | 7947.12ms | 264040 | 1280 | 2.23272e+08 | 303088 | 2.80637 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5678.52 | 0.26414 | 5285.05ms | 264040 | 4890 | 6.70885e+07 | 44344 | 0.410191 | 1(Win) |
| glaze | 2508.32 | 0.301149 | 5564.19ms | 263923 | 640 | 5.84427e+07 | 100345 | 0.929207 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1192.15 | 0.133695 | 8427.31ms | 399947 | 1280 | 2.34196e+08 | 319942 | 1.95577 | 1(Win) |
| glaze | 1105.17 | 0.106576 | 9016.99ms | 399947 | 1280 | 1.73171e+08 | 345123 | 2.10979 | 2(Loss) |
| jsonifier | 918.053 | 0.156116 | 5411.14ms | 399947 | 640 | 2.69241e+08 | 415465 | 2.5397 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8214.07 | 0.220933 | 5510.59ms | 399947 | 4890 | 5.14656e+07 | 46434.9 | 0.283562 | 1(Win) |
| glaze | 2198.43 | 0.207593 | 9333.02ms | 399830 | 640 | 8.29715e+07 | 173445 | 1.06045 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 611.987 | 0.688557 | 1614.88ms | 4630 | 320 | 789783 | 7215.04 | 3.79094 | 1(Win) |
| glaze | 447.783 | 0.160188 | 1892.39ms | 4630 | 30 | 7485.32 | 9860.83 | 5.18858 | 2(Loss) |
| simdjson (ondemand) | 381.111 | 0.693865 | 2061.07ms | 4630 | 30 | 193879 | 11585.9 | 6.09873 | 3(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 766.276 | 0.0797882 | 1464.75ms | 4630 | 30 | 634.148 | 5762.3 | 3.02272 | 1(Win) |
| glaze | 658.086 | 0.168769 | 1533.65ms | 4630 | 80 | 10258.2 | 6709.62 | 3.52418 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1376.8 | 1.74134 | 1866.72ms | 14795 | 4890 | 1.55728e+08 | 10248.1 | 1.68763 | 1(Win) |
| glaze | 1089.28 | 0.0767234 | 2205.41ms | 14795 | 30 | 2962.99 | 12953.2 | 2.13504 | 2(Loss) |
| simdjson (ondemand) | 1029.09 | 1.07986 | 2190.26ms | 14795 | 2560 | 5.61174e+07 | 13710.8 | 2.26002 | 3(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2435.01 | 0.991581 | 1468.02ms | 14795 | 320 | 1.05642e+06 | 5794.48 | 0.951578 | 1(Win) |
| glaze | 1454.57 | 0.213654 | 1878.43ms | 14795 | 40 | 17180.8 | 9700.23 | 1.59689 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 810.725 | 0.381033 | 1511.9ms | 5092 | 30 | 15627 | 5989.83 | 2.85752 | 1(Win) |
| glaze | 717.422 | 0.491154 | 1590.04ms | 5092 | 1280 | 1.41473e+06 | 6768.84 | 3.23248 | 2(Loss) |
| simdjson (ondemand) | 587.734 | 1.0945 | 1752.1ms | 5092 | 320 | 2.61695e+06 | 8262.42 | 3.94959 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4098.07 | 0.518795 | 1037.18ms | 5092 | 40 | 1511.72 | 1184.97 | 0.551046 | 1(Win) |
| glaze | 1647.45 | 0.240142 | 1208.51ms | 5092 | 40 | 2004.23 | 2947.65 | 1.39834 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1238.29 | 0.46278 | 1860.3ms | 11724 | 30 | 52381.2 | 9029.27 | 1.8756 | 1(Win) |
| glaze STATISTICAL TIE | 1212.12 | 0.0932994 | 1871.47ms | 11724 | 30 | 2221.98 | 9224.23 | 1.91628 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1200.04 | 2.27226 | 1859.11ms | 11724 | 80 | 3.58563e+06 | 9317.08 | 1.93507 | 2(Tie) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8266.48 | 0.288357 | 1056.62ms | 11724 | 160 | 2433.85 | 1352.56 | 0.27422 | 1(Win) |
| glaze | 2071.29 | 0.191148 | 1477.75ms | 11746 | 40 | 4274.59 | 5408.15 | 1.11794 | 2(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3799.94 | 0.591267 | 1053.59ms | 4857 | 30 | 1558.38 | 1218.97 | 0.59523 | 1(Win) |
| glaze | 1805.07 | 0.246007 | 1192.78ms | 4857 | 30 | 1195.54 | 2566.1 | 1.27299 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1100.55 | 0.303916 | 1598.08ms | 7376 | 30 | 11320 | 6391.6 | 2.10698 | 1(Win) |
| simdjson (ondemand) | 1047.8 | 0.172316 | 1622.83ms | 7376 | 40 | 5353.02 | 6713.4 | 2.21359 | 2(Loss) |
| jsonifier | 816.531 | 0.771258 | 1829.37ms | 7376 | 30 | 132439 | 8614.87 | 2.84439 | 3(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5655.49 | 0.65212 | 1048.56ms | 7376 | 30 | 1973.68 | 1243.8 | 0.399801 | 1(Win) |
| glaze | 1703.91 | 0.280023 | 1340.74ms | 7376 | 30 | 4009.2 | 4128.33 | 1.35642 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 934.714 | 0.131572 | 1337.18ms | 4390 | 40 | 1389.18 | 4479.05 | 2.47373 | 1(Win) |
| glaze | 793.178 | 0.133928 | 1447.53ms | 4390 | 30 | 1499.18 | 5278.3 | 2.9197 | 2(Loss) |
| simdjson (ondemand) | 649.748 | 0.613784 | 1520.93ms | 4390 | 1280 | 2.00208e+06 | 6443.46 | 3.56838 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3711.51 | 0.216004 | 999.328ms | 4390 | 320 | 1899.77 | 1128.01 | 0.608449 | 1(Win) |
| glaze | 1212.92 | 0.259826 | 1216.39ms | 4390 | 30 | 2412.98 | 3451.7 | 1.90254 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1565.17 | 0.281813 | 1602.46ms | 11521 | 80 | 31308.9 | 7019.85 | 1.48189 | 1(Win) |
| jsonifier | 1465.5 | 0.0844634 | 1633.96ms | 11521 | 40 | 1604 | 7497.27 | 1.58316 | 2(Loss) |
| glaze | 1432.87 | 0.145518 | 1678.48ms | 11521 | 30 | 3735.27 | 7668.03 | 1.61922 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9250.79 | 0.300164 | 987.435ms | 11521 | 80 | 1016.79 | 1187.71 | 0.244102 | 1(Win) |
| glaze | 1731.44 | 0.286276 | 1525.14ms | 11521 | 40 | 13200.7 | 6345.75 | 1.33899 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1120.18 | 0.0957435 | 1290.11ms | 4669 | 40 | 579.358 | 3974.97 | 2.0617 | 1(Win) |
| glaze | 1063.66 | 0.601773 | 1310.73ms | 4669 | 30 | 19038.2 | 4186.2 | 2.17259 | 2(Loss) |
| simdjson (ondemand) | 809.419 | 1.20093 | 1427.71ms | 4669 | 320 | 1.39665e+06 | 5501.11 | 2.86188 | 3(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6016.84 | 0.44554 | 964.144ms | 4669 | 640 | 6957.69 | 740.041 | 0.368681 | 1(Win) |
| glaze | 1650.31 | 0.131465 | 1151.96ms | 4669 | 320 | 4026.16 | 2698.11 | 1.39357 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1518.14 | 0.402856 | 1461.51ms | 9249 | 80 | 43828.1 | 5810.07 | 1.52664 | 1(Win) |
| glaze | 1408.82 | 0.31759 | 1525.57ms | 9249 | 160 | 63260.8 | 6260.94 | 1.64537 | 2(Loss) |
| jsonifier | 1150.52 | 0.235056 | 1676.6ms | 9249 | 40 | 12989.9 | 7666.57 | 2.0171 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10538.4 | 0.189309 | 979.378ms | 9249 | 2560 | 6427.29 | 836.993 | 0.211575 | 1(Win) |
| glaze | 1873.77 | 0.100086 | 1387.75ms | 9249 | 160 | 3551.62 | 4707.36 | 1.23485 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 424.514 | 0.492171 | 1932.98ms | 4604 | 40 | 103652 | 10342.9 | 5.47177 | 1(Win) |
| glaze | 361.711 | 0.223945 | 2119.88ms | 4604 | 30 | 22169.2 | 12138.7 | 6.42796 | 2(Loss) |
| simdjson (ondemand) | 282.237 | 0.804545 | 2384.72ms | 4604 | 2560 | 4.01036e+07 | 15556.8 | 8.24268 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 688.697 | 0.159672 | 1534.98ms | 4604 | 30 | 3108.8 | 6375.4 | 3.36581 | 1(Win) |
| glaze | 499.454 | 0.0910435 | 1775.26ms | 4604 | 30 | 1921.76 | 8791.03 | 4.64993 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1359.36 | 0.700322 | 2560.48ms | 24579 | 2560 | 3.73331e+07 | 17243.6 | 1.71169 | 1(Win) |
| jsonifier | 1311.89 | 0.821387 | 2622.15ms | 24579 | 2560 | 5.51402e+07 | 17867.6 | 1.77323 | 2(Loss) |
| glaze | 1200.43 | 0.44044 | 2783.63ms | 24579 | 4890 | 3.61692e+07 | 19526.7 | 1.93812 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3465.97 | 0.0584831 | 1559.32ms | 24579 | 30 | 469.31 | 6763 | 0.669272 | 1(Win) |
| glaze | 1789.2 | 0.120841 | 2212.47ms | 24579 | 30 | 7518.97 | 13101 | 1.2997 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 468.819 | 2.40737 | 1779.38ms | 4604 | 2560 | 1.30132e+08 | 9365.49 | 4.95334 | 1(Win) |
| glaze | 340.998 | 1.27286 | 2112.67ms | 4604 | 1280 | 3.43827e+07 | 12876.1 | 6.8193 | 2(Loss) |
| simdjson (ondemand) | 270.917 | 1.02054 | 2445.2ms | 4604 | 2560 | 7.00327e+07 | 16206.9 | 8.58761 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 693.896 | 0.143798 | 1545.58ms | 4604 | 30 | 2483.76 | 6327.63 | 3.34027 | 1(Win) |
| glaze | 489.424 | 0.103465 | 1815.6ms | 4604 | 30 | 2584.72 | 8971.2 | 4.74427 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1425.78 | 0.718479 | 2507.66ms | 24579 | 4890 | 6.82275e+07 | 16440.4 | 1.63126 | 1(Win) |
| simdjson (ondemand) | 1330.24 | 0.53607 | 2582.49ms | 24579 | 4890 | 4.36334e+07 | 17621.1 | 1.74943 | 2(Loss) |
| glaze | 1244.98 | 0.251889 | 2825.33ms | 24579 | 30 | 67475.6 | 18828 | 1.86971 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3401.54 | 0.124335 | 1578.88ms | 24579 | 40 | 2936.45 | 6891.1 | 0.681928 | 1(Win) |
| glaze | 1759.21 | 0.0917382 | 2241.14ms | 24579 | 30 | 4482.45 | 13324.4 | 1.32197 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 544.845 | 0.275954 | 1081.53ms | 1181 | 40 | 1301.64 | 2067.18 | 4.20144 | 1(Win) |
| glaze | 498.402 | 0.357792 | 1091.27ms | 1181 | 30 | 1961.2 | 2259.8 | 4.60556 | 2(Loss) |
| simdjson (ondemand) | 392.767 | 0.98336 | 1146.46ms | 1181 | 1280 | 1.01781e+06 | 2867.58 | 5.86107 | 3(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 802.529 | 0.129402 | 1005.88ms | 1181 | 160 | 527.692 | 1403.42 | 2.83091 | 1(Win) |
| glaze | 589.252 | 0.245386 | 1051.15ms | 1181 | 160 | 3519.79 | 1911.39 | 3.8797 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 841.061 | 0.115116 | 1156.92ms | 2496 | 30 | 318.441 | 2830.2 | 2.73564 | 1(Win) |
| jsonifier | 825.075 | 0.464796 | 1181.46ms | 2496 | 80 | 14385.3 | 2885.04 | 2.78986 | 2(Loss) |
| simdjson (ondemand) | 809.278 | 0.17584 | 1180.12ms | 2496 | 80 | 2140.03 | 2941.35 | 2.84462 | 3(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1655.45 | 0.284826 | 1035.63ms | 2496 | 30 | 503.197 | 1437.9 | 1.37321 | 1(Win) |
| glaze | 944.356 | 0.146994 | 1141.63ms | 2507 | 80 | 1107.97 | 2531.74 | 2.43205 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 873.993 | 0.465497 | 1419.27ms | 4926 | 1280 | 801340 | 5375.1 | 2.65016 | 1(Win) |
| glaze | 638.422 | 0.536211 | 1595.88ms | 4926 | 1280 | 1.99276e+06 | 7358.46 | 3.63443 | 2(Loss) |
| simdjson (ondemand) | 547.116 | 0.0849916 | 1753.55ms | 4926 | 40 | 2130.31 | 8586.48 | 4.24385 | 3(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3094.02 | 0.184938 | 1011.12ms | 4926 | 320 | 2523.17 | 1518.35 | 0.735211 | 1(Win) |
| glaze | 1417.05 | 0.392531 | 1199.22ms | 4926 | 30 | 5080.3 | 3315.2 | 1.62686 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1077.09 | 0.0766562 | 1746.56ms | 9463 | 40 | 1650.1 | 8378.73 | 2.15615 | 1(Win) |
| simdjson (ondemand) | 971.837 | 1.83404 | 1813.38ms | 9463 | 2560 | 7.42554e+07 | 9286.15 | 2.3899 | 2(Loss) |
| glaze | 901.877 | 1.9519 | 1790.38ms | 9463 | 4890 | 1.86547e+08 | 10006.5 | 2.57613 | 3(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5533.73 | 0.236499 | 1058.2ms | 9463 | 80 | 1190.06 | 1630.84 | 0.411953 | 1(Win) |
| glaze | 1626.17 | 0.296577 | 1467.88ms | 9463 | 80 | 21671.7 | 5549.62 | 1.42475 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2535.67 | 0.244204 | 1002.73ms | 2821 | 80 | 537.05 | 1060.99 | 0.887597 | 1(Win) |
| jsonifier | 2180.67 | 0.197028 | 1021.26ms | 2821 | 80 | 472.688 | 1233.71 | 1.0375 | 2(Loss) |
| glaze | 1737.86 | 0.237191 | 1043.01ms | 2821 | 320 | 4314.43 | 1548.07 | 1.30977 | 3(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3368.02 | 0.151002 | 995.3ms | 4147 | 1280 | 4024.33 | 1174.25 | 0.670587 | 1(Win) |
| jsonifier | 2884.67 | 0.153937 | 1030.46ms | 4147 | 80 | 356.329 | 1371 | 0.787081 | 2(Loss) |
| glaze | 2246.65 | 0.0908952 | 1072.27ms | 4147 | 160 | 409.638 | 1760.35 | 1.01617 | 3(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1225.84 | 0.199668 | 1125.11ms | 2821 | 640 | 12289.4 | 2194.66 | 1.86981 | 1(Win) |
| jsonifier | 1070.39 | 0.25711 | 1159.92ms | 2821 | 30 | 1252.8 | 2513.4 | 2.14634 | 2(Loss) |
| simdjson (ondemand) | 1026.87 | 0.226135 | 1160.07ms | 2821 | 40 | 1404.02 | 2619.93 | 2.2396 | 3(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4094.86 | 0.48622 | 923.777ms | 2821 | 4890 | 49900.3 | 656.998 | 0.537195 | 1(Win) |
| glaze | 2375.2 | 0.0905148 | 997.422ms | 2819 | 2560 | 2687.01 | 1131.87 | 0.9498 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1452.41 | 0.270157 | 1125.36ms | 4147 | 320 | 17317.1 | 2722.99 | 1.58342 | 1(Win) |
| glaze | 1382.08 | 0.623153 | 1167.21ms | 4147 | 640 | 203503 | 2861.55 | 1.66518 | 2(Loss) |
| jsonifier | 935.339 | 0.73174 | 1318.77ms | 4147 | 320 | 306333 | 4228.29 | 2.4711 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6060.43 | 1.05323 | 918.999ms | 4147 | 40 | 1889.58 | 652.575 | 0.363932 | 1(Win) |
| glaze | 1896.21 | 1.29576 | 1060.9ms | 4145 | 80 | 58373.8 | 2084.68 | 1.20698 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1305.46 | 0.220596 | 8954.07ms | 466906 | 160 | 9.05831e+07 | 341088 | 1.78617 | 1(Win) |
| glaze | 1238.86 | 0.202492 | 9362.04ms | 466906 | 640 | 3.39008e+08 | 359423 | 1.88219 | 2(Loss) |
| simdjson (ondemand) | 622.329 | 0.106624 | 9204.8ms | 466906 | 320 | 1.86242e+08 | 715500 | 3.74707 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2119.81 | 0.299993 | 8160.31ms | 699405 | 160 | 1.42562e+08 | 314653 | 1.09998 | 1(Win) |
| glaze | 1887.8 | 0.356125 | 9252.05ms | 699405 | 40 | 6.333e+07 | 353323 | 1.2352 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2395.48 | 0.112609 | 6646.64ms | 631514 | 1280 | 1.02598e+08 | 251415 | 0.973364 | 1(Win) |
| glaze | 1383.65 | 0.0884813 | 5660.07ms | 631514 | 640 | 9.4929e+07 | 435269 | 1.68527 | 2(Loss) |
