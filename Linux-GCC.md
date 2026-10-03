# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [dded0f9](https://github.com/nihilai-collective/jsonifier/commit/dded0f9)  
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

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10% AND mean shift < 5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 1479.93 | 0.266116 | 832.033ms | 905 | 80 | 192.686 | 583.188 | 1.59046 | 1(Win) |
| glaze | 632.359 | 0.429399 | 900.393ms | 905 | 80 | 2747.77 | 1364.85 | 3.82852 | 2(Loss) |
| simdjson (ondemand) | 91.755 | 1.92735 | 1828.08ms | 905 | 40 | 1.31468e+06 | 9406.3 | 26.9027 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1519.01 | 0.343987 | 821.444ms | 905 | 160 | 611.193 | 568.181 | 1.54597 | 1(Win) |
| simdjson (reflection) | 226.108 | 0.490908 | 1141.19ms | 905 | 640 | 224722 | 3817.09 | 10.8659 | 2(Loss) |
| glaze | 118.57 | 0.666319 | 1556.21ms | 905 | 80 | 188192 | 7279.04 | 20.7975 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 884.941 | 0.701451 | 962.908ms | 1811 | 640 | 119945 | 1951.66 | 2.73642 | 1(Win) |
| glaze | 588.86 | 0.233678 | 1059.89ms | 1811 | 80 | 3757.86 | 2932.96 | 4.16253 | 2(Loss) |
| simdjson (ondemand) | 116.501 | 1.24958 | 2216.98ms | 1811 | 640 | 2.1963e+07 | 14824.9 | 21.2101 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 252.402 | 0.128434 | 1527.59ms | 1997 | 30 | 2817.43 | 7545.47 | 9.76638 | 1(Win) |
| jsonifier | 224.859 | 0.725639 | 1535ms | 1811 | 320 | 994047 | 7680.83 | 10.9686 | 2(Loss) |
| glaze | 194.36 | 0.0680816 | 1658.04ms | 1798 | 30 | 1082.3 | 8822.33 | 12.6982 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2012.35 | 0.139112 | 952.785ms | 3862 | 160 | 1037.2 | 1830.24 | 1.21071 | 1(Win) |
| glaze | 1108.79 | 0.261987 | 1104.3ms | 3862 | 80 | 6058.66 | 3321.72 | 2.21146 | 2(Loss) |
| simdjson (ondemand) | 288.928 | 0.550134 | 2000.05ms | 3862 | 4890 | 2.40487e+07 | 12747.4 | 8.54941 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 647.051 | 1.02464 | 1325.22ms | 3862 | 320 | 1.08852e+06 | 5692.12 | 3.80627 | 1(Win) |
| glaze | 557.9 | 0.102611 | 1433.18ms | 3862 | 30 | 1376.63 | 6601.7 | 4.4188 | 2(Loss) |
| simdjson (reflection) | 369.615 | 0.0609453 | 1760.89ms | 3862 | 30 | 1106.44 | 9964.67 | 6.67885 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1014.33 | 1.43688 | 1652.55ms | 9578 | 4890 | 8.18725e+07 | 9005.24 | 2.43155 | 1(Win) |
| glaze | 881.219 | 0.0721529 | 1814.28ms | 9578 | 40 | 2237.44 | 10365.5 | 2.80019 | 2(Loss) |
| simdjson (ondemand) | 574.332 | 0.481734 | 2318.98ms | 9578 | 4890 | 2.87043e+07 | 15904.2 | 4.302 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1622.67 | 0.114376 | 1332.37ms | 9578 | 30 | 1243.59 | 5629.17 | 1.51815 | 1(Win) |
| glaze | 1401.88 | 0.0390589 | 1424.06ms | 9578 | 160 | 1036.3 | 6515.74 | 1.75818 | 2(Loss) |
| simdjson (reflection) | 950.712 | 0.757899 | 1727.24ms | 9578 | 320 | 1.69678e+06 | 9607.85 | 2.59601 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1957.05 | 0.0818995 | 955.341ms | 3873 | 640 | 1529.1 | 1887.33 | 1.24565 | 1(Win) |
| glaze | 1349.57 | 0.155688 | 1041.23ms | 3873 | 80 | 1452.47 | 2736.86 | 1.81447 | 2(Loss) |
| simdjson (ondemand) | 316.564 | 0.295025 | 1931.52ms | 3873 | 640 | 758351 | 11667.7 | 7.80161 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 572.134 | 0.596728 | 1406.42ms | 3873 | 30 | 44522 | 6455.8 | 4.30893 | 1(Win) |
| glaze | 561.277 | 0.07377 | 1433.79ms | 3873 | 320 | 7541.38 | 6580.68 | 4.39116 | 2(Loss) |
| simdjson (reflection) | 371.213 | 0.114351 | 1759.74ms | 3873 | 30 | 3883.76 | 9950.03 | 6.64981 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 603.112 | 0.0779173 | 10248.2ms | 2090234 | 80 | 5.30581e+08 | 3.3052e+06 | 4.10504 | 1(Win) |
| simdjson (ondemand) | 461.649 | 0.0364434 | 6492.41ms | 2090234 | 80 | 1.98104e+08 | 4.318e+06 | 5.36299 | 2(Loss) |
| glaze | 441.687 | 0.0373692 | 6796.51ms | 2090234 | 80 | 2.2755e+08 | 4.51315e+06 | 5.60538 | 3(Loss) |
| simdjson (reflection) | 437.579 | 0.0906296 | 6853.99ms | 2090234 | 30 | 5.11372e+08 | 4.55552e+06 | 5.65796 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1306.64 | 0.0514598 | 9662.94ms | 2090234 | 160 | 9.8613e+07 | 1.52559e+06 | 1.89472 | 1(Win) |
| glaze | 957.868 | 0.0359524 | 6479.94ms | 2090234 | 160 | 8.95685e+07 | 2.08108e+06 | 2.58465 | 2(Loss) |
| simdjson (reflection) | 628.928 | 0.0452631 | 9871.44ms | 2090326 | 30 | 6.17498e+07 | 3.16966e+06 | 3.93651 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1522.44 | 0.215093 | 6260.28ms | 6661897 | 80 | 6.44556e+09 | 4.1731e+06 | 1.62621 | 1(Win) |
| simdjson (ondemand) | 1357.91 | 0.128339 | 7026.93ms | 6661897 | 30 | 1.08167e+09 | 4.67873e+06 | 1.82326 | 2(Loss) |
| simdjson (reflection) | 1282.41 | 0.069531 | 7443.51ms | 6661897 | 80 | 9.49273e+08 | 4.95419e+06 | 1.9306 | 3(Loss) |
| glaze | 1125.13 | 0.0473101 | 8508.32ms | 6661897 | 30 | 2.14102e+08 | 5.64672e+06 | 2.20049 | 4(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3950.87 | 0.0950408 | 5006.6ms | 6661897 | 30 | 7.00732e+07 | 1.60807e+06 | 0.626625 | 1(Win) |
| glaze | 1681 | 0.0669179 | 5689.45ms | 6661897 | 30 | 1.91895e+08 | 3.77945e+06 | 1.47282 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1198.92 | 0.112833 | 5168.77ms | 500299 | 320 | 6.45202e+07 | 397959 | 2.06467 | 1(Win) |
| jsonifier | 1181.89 | 0.177798 | 5243.93ms | 500299 | 80 | 4.12148e+07 | 403695 | 2.0944 | 2(Loss) |
| simdjson (ondemand) | 936.883 | 0.0932798 | 6568.21ms | 500299 | 320 | 7.22128e+07 | 509266 | 2.64223 | 3(Loss) |
| simdjson (reflection) | 926.594 | 0.0681081 | 6645.82ms | 500299 | 640 | 7.8715e+07 | 514920 | 2.67148 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7288.97 | 0.120754 | 7359.36ms | 500299 | 4890 | 3.05521e+07 | 65458.1 | 0.33945 | 1(Win) |
| simdjson (reflection) | 3959.68 | 0.141998 | 6580.05ms | 500299 | 1280 | 3.74724e+07 | 120495 | 0.624979 | 2(Loss) |
| glaze | 3122.68 | 0.0903175 | 8232.23ms | 500299 | 2560 | 4.87514e+07 | 152792 | 0.79253 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2636.25 | 0.0643407 | 6731.72ms | 1439562 | 640 | 7.18522e+07 | 520768 | 0.938987 | 1(Win) |
| simdjson (ondemand) | 2372.02 | 0.0554759 | 7461.11ms | 1439562 | 640 | 6.59801e+07 | 578778 | 1.04362 | 2(Loss) |
| simdjson (reflection) | 2333.57 | 0.0890559 | 7547.85ms | 1439562 | 320 | 8.78401e+07 | 588314 | 1.06079 | 3(Loss) |
| glaze | 2055.66 | 0.0465514 | 8590.45ms | 1439562 | 640 | 6.18593e+07 | 667852 | 1.20422 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16555.6 | 0.151634 | 9108.64ms | 1439562 | 2560 | 4.04766e+07 | 82924.8 | 0.149449 | 1(Win) |
| glaze | 2415.19 | 0.0548735 | 7332.43ms | 1439584 | 640 | 6.22699e+07 | 568443 | 1.02499 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1177.43 | 0.168398 | 5311.13ms | 56369 | 4890 | 2.89066e+07 | 45657 | 2.10119 | 1(Win) |
| jsonifier | 1113.94 | 0.156813 | 5575.43ms | 56369 | 4890 | 2.80046e+07 | 48258.9 | 2.22117 | 2(Loss) |
| simdjson (reflection) | 1079.41 | 0.203241 | 5743.12ms | 56369 | 2560 | 2.62282e+07 | 49802.8 | 2.29226 | 3(Loss) |
| simdjson (ondemand) | 1019.16 | 0.221463 | 6028.67ms | 56369 | 2560 | 3.49333e+07 | 52747.2 | 2.42772 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7007.73 | 0.371532 | 1559.63ms | 56369 | 30 | 24369.1 | 7671.2 | 0.35193 | 1(Win) |
| simdjson (reflection) | 5538.03 | 0.152505 | 1768.36ms | 56369 | 30 | 6574.48 | 9707 | 0.445702 | 2(Loss) |
| glaze | 3598.64 | 0.493802 | 2238.67ms | 56369 | 4890 | 2.66085e+07 | 14938.3 | 0.686613 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 1683.51 | 0.303534 | 6098.48ms | 94370 | 1280 | 3.37023e+07 | 53458.6 | 1.46978 | 1(Win) |
| jsonifier | 1626.35 | 0.207342 | 6263.87ms | 94370 | 2560 | 3.3702e+07 | 55337.6 | 1.52142 | 2(Loss) |
| simdjson (ondemand) | 1604.7 | 0.402328 | 6373.34ms | 94370 | 640 | 3.25854e+07 | 56084.3 | 1.54187 | 3(Loss) |
| glaze | 1578.49 | 0.179981 | 6453.12ms | 94370 | 2560 | 2.69575e+07 | 57015.5 | 1.56762 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10410.8 | 0.117382 | 1678.64ms | 94370 | 30 | 3089.04 | 8644.7 | 0.237013 | 1(Win) |
| glaze | 1825.31 | 0.211409 | 5683.84ms | 94370 | 2560 | 2.78151e+07 | 49305.7 | 1.35555 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1231.7 | 0.603783 | 1704.04ms | 11812 | 320 | 975773 | 9145.74 | 2.00378 | 1(Win) |
| jsonifier | 982.321 | 1.42446 | 1884.82ms | 11812 | 4890 | 1.30482e+08 | 11467.5 | 2.51386 | 2(Loss) |
| simdjson (reflection) | 919.646 | 0.114786 | 2027.47ms | 11812 | 30 | 5930.69 | 12249.1 | 2.68584 | 3(Loss) |
| simdjson (ondemand) | 777.566 | 0.486941 | 2253.44ms | 11812 | 30 | 149296 | 14487.3 | 3.17773 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5367.75 | 0.186213 | 986.691ms | 11812 | 160 | 2443.45 | 2098.61 | 0.45481 | 1(Win) |
| simdjson (reflection) | 3832.43 | 0.239171 | 1080.58ms | 11812 | 30 | 1482.64 | 2939.33 | 0.639725 | 2(Loss) |
| glaze | 2593.53 | 0.149504 | 1219.2ms | 11812 | 160 | 6746.67 | 4343.42 | 0.947967 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2387.01 | 0.783137 | 2004.64ms | 31235 | 2560 | 2.44507e+07 | 12479.2 | 1.0347 | 1(Win) |
| simdjson (reflection) | 2139.36 | 0.390288 | 2191.49ms | 31235 | 40 | 118126 | 13923.8 | 1.15485 | 2(Loss) |
| glaze | 1896.79 | 0.460217 | 2319.31ms | 31235 | 4890 | 2.55436e+07 | 15704.5 | 1.30286 | 3(Loss) |
| simdjson (ondemand) | 1751.71 | 0.648413 | 2433.09ms | 31235 | 2560 | 3.11245e+07 | 17005.1 | 1.41098 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11605 | 0.120034 | 1032.72ms | 31235 | 160 | 1518.87 | 2566.82 | 0.210877 | 1(Win) |
| glaze | 1868.52 | 0.463091 | 2331.76ms | 31235 | 4890 | 2.6652e+07 | 15942.1 | 1.3226 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2128.35 | 0.225908 | 5606.17ms | 108313 | 2560 | 3.07735e+07 | 48533 | 1.16255 | 1(Win) |
| simdjson (reflection) | 1286.67 | 0.209101 | 8759.49ms | 108313 | 1280 | 3.60701e+07 | 80281 | 1.92335 | 2(Loss) |
| glaze | 1225.81 | 0.114105 | 9160.31ms | 108313 | 4890 | 4.52105e+07 | 84267.2 | 2.01892 | 3(Loss) |
| simdjson (ondemand) | 969.707 | 0.155042 | 5832.12ms | 108313 | 1280 | 3.49132e+07 | 106522 | 2.55238 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10269.4 | 0.663448 | 1792.23ms | 108313 | 320 | 1.42507e+06 | 10058.6 | 0.240373 | 1(Win) |
| simdjson (reflection) | 6085.12 | 0.43029 | 2456.63ms | 108313 | 4890 | 2.60888e+07 | 16975.1 | 0.406158 | 2(Loss) |
| glaze | 1847.41 | 0.140132 | 6324.75ms | 108313 | 4890 | 3.00208e+07 | 55913.7 | 1.33942 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) STATISTICAL TIE | 2288.64 | 0.141847 | 9611.21ms | 213963 | 2560 | 4.09453e+07 | 89158.3 | 1.08136 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2284.52 | 0.0994498 | 9630.21ms | 213963 | 4890 | 3.85836e+07 | 89318.8 | 1.08327 | 1(Tie) |
| glaze | 1805.41 | 0.305092 | 6133.64ms | 213963 | 320 | 3.80484e+07 | 113022 | 1.37091 | 3(Loss) |
| simdjson (ondemand) | 1762.3 | 0.220908 | 6264.21ms | 213963 | 640 | 4.18719e+07 | 115787 | 1.40446 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16384 | 0.0606987 | 2002.93ms | 213963 | 30 | 1714.42 | 12454.3 | 0.150761 | 1(Win) |
| glaze | 1495.4 | 0.090637 | 7339.08ms | 213963 | 2560 | 3.91576e+07 | 136453 | 1.65518 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 538.017 | 0.0454772 | 10113.1ms | 1834197 | 160 | 3.4979e+08 | 3.25125e+06 | 4.60169 | 1(Win) |
| simdjson (ondemand) | 432.467 | 0.0673372 | 6081.85ms | 1834197 | 80 | 5.93451e+08 | 4.04476e+06 | 5.72484 | 2(Loss) |
| glaze | 428.524 | 0.0467826 | 6164.64ms | 1834197 | 80 | 2.91744e+08 | 4.08198e+06 | 5.77755 | 3(Loss) |
| simdjson (reflection) | 420.802 | 0.0730954 | 6252.52ms | 1834197 | 40 | 3.69297e+08 | 4.15688e+06 | 5.88357 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 868.049 | 0.107103 | 6270.12ms | 1834197 | 30 | 1.39743e+08 | 2.01512e+06 | 2.85208 | 1(Win) |
| glaze | 502.159 | 0.0387076 | 5240.89ms | 1833577 | 40 | 7.26721e+07 | 3.48223e+06 | 4.93032 | 2(Loss) |
| simdjson (reflection) | 382.796 | 0.030446 | 7201.06ms | 1922245 | 80 | 1.70072e+08 | 4.78896e+06 | 6.46771 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2224.93 | 0.0529987 | 6401.02ms | 9930848 | 80 | 4.07154e+08 | 4.25666e+06 | 1.11276 | 1(Win) |
| simdjson (ondemand) | 2022.27 | 0.0640809 | 7047.85ms | 9930848 | 30 | 2.70192e+08 | 4.68325e+06 | 1.22428 | 2(Loss) |
| simdjson (reflection) | 1980.42 | 0.0347363 | 7187.03ms | 9930848 | 80 | 2.20757e+08 | 4.78221e+06 | 1.25015 | 3(Loss) |
| glaze | 1696.48 | 0.0547854 | 8403.63ms | 9930848 | 40 | 3.74168e+08 | 5.58262e+06 | 1.45939 | 4(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4390.29 | 0.0619418 | 6717.45ms | 9930848 | 80 | 1.42838e+08 | 2.15722e+06 | 0.563918 | 1(Win) |
| glaze | 1511.37 | 0.0479999 | 9419.98ms | 9930228 | 30 | 2.7138e+08 | 6.26596e+06 | 1.63813 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 541.624 | 0.0614818 | 10055.1ms | 1834197 | 160 | 6.30824e+08 | 3.22959e+06 | 4.57103 | 1(Win) |
| simdjson (ondemand) | 428.965 | 0.0405158 | 6124.17ms | 1834197 | 80 | 2.18367e+08 | 4.07778e+06 | 5.77156 | 2(Loss) |
| glaze | 418.362 | 0.0428874 | 6292.74ms | 1834197 | 80 | 2.57238e+08 | 4.18113e+06 | 5.91782 | 3(Loss) |
| simdjson (reflection) | 415.838 | 0.0645579 | 6320.98ms | 1834197 | 40 | 2.94987e+08 | 4.20651e+06 | 5.95377 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 873.616 | 0.13262 | 6211.9ms | 1834197 | 40 | 2.8205e+08 | 2.00228e+06 | 2.83394 | 1(Win) |
| glaze | 490.799 | 0.0280598 | 5353.65ms | 1833577 | 80 | 7.99557e+07 | 3.56283e+06 | 5.04444 | 2(Loss) |
| simdjson (reflection) | 382.987 | 0.0293625 | 7201.74ms | 1922245 | 80 | 1.58025e+08 | 4.78657e+06 | 6.46454 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2221.89 | 0.0824004 | 6395.24ms | 9930848 | 40 | 4.93454e+08 | 4.2625e+06 | 1.11427 | 1(Win) |
| simdjson (ondemand) | 2002.12 | 0.0739186 | 7112.76ms | 9930848 | 40 | 4.8906e+08 | 4.73039e+06 | 1.2366 | 2(Loss) |
| simdjson (reflection) | 1949.58 | 0.0790963 | 7309.34ms | 9930848 | 30 | 4.42918e+08 | 4.85786e+06 | 1.26992 | 3(Loss) |
| glaze | 1688.63 | 0.0353991 | 8432.95ms | 9930848 | 80 | 3.15337e+08 | 5.60855e+06 | 1.46616 | 4(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4377.25 | 0.130519 | 6734.34ms | 9930848 | 40 | 3.18992e+08 | 2.16364e+06 | 0.565604 | 1(Win) |
| glaze | 1425.29 | 0.0462875 | 9998.19ms | 9930228 | 80 | 7.5671e+08 | 6.6444e+06 | 1.73707 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 823.337 | 0.0865954 | 9564.95ms | 642697 | 320 | 1.32983e+08 | 744439 | 3.00678 | 1(Win) |
| simdjson (ondemand) | 816.806 | 0.06083 | 9637.25ms | 642697 | 640 | 1.33349e+08 | 750390 | 3.03083 | 2(Loss) |
| jsonifier | 805.48 | 0.278237 | 9791.24ms | 642697 | 80 | 3.5861e+08 | 760942 | 3.07343 | 3(Loss) |
| glaze | 781.472 | 0.223223 | 5000.47ms | 642697 | 40 | 1.22609e+08 | 784319 | 3.16792 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1525.28 | 0.0687693 | 5209.26ms | 642697 | 640 | 4.88743e+07 | 401843 | 1.62294 | 1(Win) |
| glaze | 824.939 | 0.0537429 | 9539.45ms | 642692 | 320 | 5.10215e+07 | 742987 | 3.00091 | 2(Loss) |
| simdjson (reflection) | 745.594 | 0.0499419 | 5236.91ms | 643373 | 320 | 5.40506e+07 | 822925 | 3.32034 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 1475.2 | 0.0892121 | 5045.97ms | 1225964 | 320 | 1.59976e+08 | 792553 | 1.67815 | 1(Win) |
| simdjson (ondemand) | 1466.18 | 0.14256 | 5064.29ms | 1225964 | 160 | 2.06776e+08 | 797426 | 1.68846 | 2(Loss) |
| glaze | 1210.35 | 0.0741801 | 6138.88ms | 1225964 | 320 | 1.64308e+08 | 965976 | 2.04539 | 3(Loss) |
| jsonifier | 1201.59 | 0.143773 | 6229.84ms | 1225964 | 40 | 7.82806e+07 | 973015 | 2.06027 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3057.7 | 0.0621812 | 9954.23ms | 1225964 | 1280 | 7.23593e+07 | 382369 | 0.809571 | 1(Win) |
| glaze | 1286.86 | 0.0604053 | 5774.2ms | 1225970 | 160 | 4.81913e+07 | 908550 | 1.92376 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 889.237 | 0.264276 | 5684.5ms | 409725 | 160 | 2.15767e+08 | 439415 | 2.78384 | 1(Win) |
| simdjson (ondemand) | 795.221 | 0.132368 | 6348.81ms | 409725 | 160 | 6.76853e+07 | 491365 | 3.11295 | 2(Loss) |
| glaze | 775.926 | 0.0912517 | 6526.78ms | 409725 | 320 | 6.75735e+07 | 503584 | 3.19033 | 3(Loss) |
| simdjson (reflection) | 765.928 | 0.108013 | 6614.35ms | 409725 | 160 | 4.85825e+07 | 510158 | 3.2321 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4096.82 | 0.115139 | 5297.43ms | 409725 | 2560 | 3.08728e+07 | 95377.5 | 0.604042 | 1(Win) |
| simdjson (reflection) | 3942.46 | 0.130648 | 5483.09ms | 409725 | 2560 | 4.29234e+07 | 99111.9 | 0.627666 | 2(Loss) |
| glaze | 2261.42 | 0.0897534 | 9257.26ms | 409725 | 2560 | 6.15692e+07 | 172787 | 1.09441 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1464.79 | 0.164907 | 6597.66ms | 785750 | 160 | 1.13873e+08 | 511576 | 1.68998 | 1(Win) |
| simdjson (ondemand) | 1435.61 | 0.0928998 | 6731.65ms | 785750 | 320 | 7.52447e+07 | 521973 | 1.72437 | 2(Loss) |
| simdjson (reflection) | 1378.72 | 0.0630476 | 6999.73ms | 785750 | 640 | 7.51505e+07 | 543509 | 1.79554 | 3(Loss) |
| glaze | 1252.07 | 0.0887472 | 7733.61ms | 785750 | 160 | 4.5138e+07 | 598489 | 1.97716 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7042.11 | 0.114483 | 5860.03ms | 785750 | 2560 | 3.79912e+07 | 106410 | 0.351403 | 1(Win) |
| glaze | 1512.39 | 0.132728 | 6416.98ms | 785750 | 160 | 6.91974e+07 | 495475 | 1.63679 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 4342.63 | 0.186471 | 6542.55ms | 264040 | 2560 | 2.99295e+07 | 57985.2 | 0.569824 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 4330.86 | 0.271907 | 6562.4ms | 264040 | 1280 | 3.19919e+07 | 58142.8 | 0.571365 | 1(Tie) |
| jsonifier | 3911.57 | 0.229384 | 7197.79ms | 264040 | 1280 | 2.79109e+07 | 64375.3 | 0.632647 | 3(Loss) |
| glaze | 1638.25 | 0.238568 | 8215.08ms | 264040 | 320 | 4.30283e+07 | 153706 | 1.51095 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 5613.52 | 0.294678 | 7563.97ms | 399947 | 640 | 2.56573e+07 | 67946.6 | 0.440846 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 5597.02 | 0.458665 | 7580.32ms | 399947 | 320 | 3.12632e+07 | 68146.9 | 0.442147 | 1(Tie) |
| jsonifier | 4973.81 | 0.111442 | 8422.36ms | 399947 | 4890 | 3.57134e+07 | 76685.5 | 0.497558 | 3(Loss) |
| glaze | 2107.11 | 0.100033 | 9640.9ms | 399947 | 1280 | 4.1969e+07 | 181016 | 1.17474 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1270.87 | 0.0952351 | 5255.24ms | 264040 | 1280 | 4.55768e+07 | 198139 | 1.94768 | 1(Win) |
| glaze | 1236.37 | 0.284003 | 5436.44ms | 264040 | 160 | 5.35314e+07 | 203668 | 2.00186 | 2(Loss) |
| simdjson (reflection) | 1132.95 | 0.114548 | 5877.01ms | 264040 | 1280 | 8.29658e+07 | 222258 | 2.18492 | 3(Loss) |
| simdjson (ondemand) | 846.484 | 0.11617 | 7766.11ms | 264040 | 640 | 7.64313e+07 | 297476 | 2.92435 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7438.22 | 0.408728 | 4170.83ms | 264040 | 1280 | 2.45065e+07 | 33853.3 | 0.332515 | 1(Win) |
| simdjson (reflection) | 5244.45 | 0.174056 | 5628.59ms | 264040 | 4890 | 3.4153e+07 | 48014.2 | 0.471536 | 2(Loss) |
| glaze | 3685.71 | 0.239116 | 7644.87ms | 263923 | 1280 | 3.41303e+07 | 68289.8 | 0.671148 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 1614.93 | 0.295329 | 6235.96ms | 399947 | 160 | 7.78454e+07 | 236184 | 1.5328 | 1(Win) |
| glaze | 1443.62 | 0.127808 | 6940.28ms | 399947 | 640 | 7.29781e+07 | 264210 | 1.71445 | 2(Loss) |
| jsonifier | 1262.82 | 0.294833 | 7750.46ms | 399947 | 80 | 6.34399e+07 | 302037 | 1.95952 | 3(Loss) |
| simdjson (ondemand) | 1236.07 | 0.133004 | 8106.51ms | 399947 | 320 | 5.39007e+07 | 308574 | 2.00254 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9089.69 | 0.258996 | 5000.15ms | 399947 | 2560 | 3.02367e+07 | 41961.7 | 0.272089 | 1(Win) |
| glaze | 2123.03 | 0.0774317 | 9572.09ms | 399830 | 2560 | 4.95125e+07 | 179605 | 1.16574 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 887.493 | 0.220281 | 1278.76ms | 4630 | 30 | 3603.37 | 4975.27 | 2.7735 | 1(Win) |
| glaze | 568.821 | 0.112707 | 1560.59ms | 4630 | 80 | 6123.57 | 7762.56 | 4.33506 | 2(Loss) |
| simdjson (ondemand) | 550.326 | 0.510792 | 1584.2ms | 4630 | 320 | 537477 | 8023.44 | 4.48224 | 3(Loss) |
| simdjson (reflection) | 518.997 | 0.112412 | 1642.06ms | 4630 | 40 | 3658.64 | 8507.77 | 4.75425 | 4(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1291.69 | 0.1975 | 1111.74ms | 4630 | 30 | 1367.42 | 3418.4 | 1.90048 | 1(Win) |
| glaze | 918.928 | 0.0777086 | 1256.89ms | 4630 | 30 | 418.271 | 4805.07 | 2.67824 | 2(Loss) |
| simdjson (reflection) | 642.365 | 0.0697243 | 1465.91ms | 4630 | 30 | 689.109 | 6873.83 | 3.83841 | 3(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1994.16 | 0.147113 | 1499.9ms | 14795 | 40 | 4333.85 | 7075.48 | 1.23651 | 1(Win) |
| simdjson (ondemand) | 1591.64 | 0.0990337 | 1681.92ms | 14795 | 40 | 3082.93 | 8864.8 | 1.55038 | 2(Loss) |
| simdjson (reflection) | 1497.3 | 0.205382 | 1738.02ms | 14795 | 40 | 14982.8 | 9423.35 | 1.64844 | 3(Loss) |
| glaze | 1301.96 | 1.33265 | 1856.08ms | 14795 | 40 | 834307 | 10837.2 | 1.8967 | 4(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3892.74 | 0.327016 | 1130.02ms | 14795 | 2560 | 359664 | 3624.59 | 0.630863 | 1(Win) |
| glaze | 1542.37 | 2.06491 | 1650.86ms | 14795 | 4890 | 1.74487e+08 | 9148 | 1.6001 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1039.19 | 0.170322 | 1268.17ms | 5092 | 80 | 5067.73 | 4672.96 | 2.36582 | 1(Win) |
| glaze | 974.435 | 0.160436 | 1296.34ms | 5092 | 160 | 10228.1 | 4983.51 | 2.52589 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 845.662 | 0.189605 | 1391.14ms | 5092 | 40 | 4741.78 | 5742.38 | 2.91274 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 842.958 | 0.129586 | 1390.78ms | 5092 | 80 | 4458.31 | 5760.8 | 2.92194 | 3(Tie) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4940.81 | 0.253046 | 879.387ms | 5092 | 320 | 1979.38 | 982.856 | 0.486375 | 1(Win) |
| simdjson (reflection) | 3029.15 | 0.320853 | 961.597ms | 5092 | 160 | 4233.19 | 1603.12 | 0.802159 | 2(Loss) |
| glaze | 1997.04 | 0.275636 | 1029.39ms | 5092 | 80 | 3593.88 | 2431.65 | 1.225 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1795.12 | 0.159866 | 1438.57ms | 11724 | 30 | 2974.4 | 6228.5 | 1.37252 | 1(Win) |
| simdjson (reflection) | 1776.88 | 0.124848 | 1442ms | 11724 | 40 | 2468.66 | 6292.43 | 1.38682 | 2(Loss) |
| jsonifier | 1714.3 | 0.782682 | 1447.79ms | 11724 | 40 | 104234 | 6522.12 | 1.43644 | 3(Loss) |
| glaze | 1530.89 | 0.526277 | 1540.54ms | 11724 | 320 | 472761 | 7303.52 | 1.61076 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9729.85 | 0.347846 | 905.167ms | 11724 | 160 | 2556.43 | 1149.13 | 0.24792 | 1(Win) |
| glaze | 1781.98 | 0.183659 | 1438.08ms | 11746 | 40 | 5331.65 | 6286.2 | 1.38267 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1163.37 | 0.489352 | 1186.86ms | 4857 | 30 | 11388.5 | 3981.53 | 2.11198 | 1(Win) |
| simdjson (reflection) | 917.659 | 0.17871 | 1309.38ms | 4857 | 40 | 3254.86 | 5047.62 | 2.68295 | 2(Loss) |
| jsonifier STATISTICAL TIE | 838.254 | 0.61512 | 1361.19ms | 4857 | 30 | 34659.8 | 5525.77 | 2.93829 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 823.789 | 0.838264 | 1356.11ms | 4857 | 320 | 710911 | 5622.79 | 2.98988 | 3(Tie) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4217.38 | 0.532896 | 896.627ms | 4857 | 1280 | 43847.6 | 1098.31 | 0.571437 | 1(Win) |
| simdjson (reflection) | 3911.7 | 0.311619 | 905.095ms | 4857 | 80 | 1089.28 | 1184.14 | 0.617006 | 2(Loss) |
| glaze | 2726.31 | 0.452932 | 954.986ms | 4857 | 40 | 2368.72 | 1699 | 0.892356 | 3(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1399.54 | 0.462523 | 1300.28ms | 7376 | 40 | 21617.1 | 5026.15 | 1.75763 | 1(Win) |
| simdjson (reflection) | 1333.32 | 0.183294 | 1329.8ms | 7376 | 160 | 14961.9 | 5275.77 | 1.84665 | 2(Loss) |
| simdjson (ondemand) | 1224.43 | 0.687597 | 1371.15ms | 7376 | 40 | 62416.6 | 5744.95 | 2.01168 | 3(Loss) |
| jsonifier | 1081.99 | 1.01254 | 1453.42ms | 7376 | 30 | 129999 | 6501.23 | 2.27792 | 4(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6118.38 | 0.498789 | 912.738ms | 7376 | 30 | 986.562 | 1149.7 | 0.394789 | 1(Win) |
| glaze | 1848.77 | 0.126261 | 1179.51ms | 7376 | 40 | 923.156 | 3804.85 | 1.32864 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1221.01 | 0.289956 | 1121.01ms | 4390 | 40 | 3953.79 | 3428.82 | 2.01054 | 1(Win) |
| jsonifier | 1023.84 | 0.241136 | 1181.85ms | 4390 | 2560 | 248904 | 4089.16 | 2.40069 | 2(Loss) |
| simdjson (reflection) | 867.064 | 3.26172 | 1232.47ms | 4390 | 4890 | 1.21291e+08 | 4828.51 | 2.83785 | 3(Loss) |
| simdjson (ondemand) | 775.075 | 0.614317 | 1318.86ms | 4390 | 640 | 704704 | 5401.58 | 3.17676 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4672.09 | 0.965775 | 869.676ms | 4390 | 160 | 11983.4 | 896.094 | 0.51248 | 1(Win) |
| simdjson (reflection) | 3264.83 | 0.205681 | 915.497ms | 4390 | 160 | 1113.06 | 1282.34 | 0.74131 | 2(Loss) |
| glaze | 2399.86 | 0.224109 | 952.928ms | 4390 | 160 | 2445.66 | 1744.53 | 1.01416 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2428.33 | 0.150203 | 1242.7ms | 11521 | 30 | 1385.62 | 4524.63 | 1.01283 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 2030.21 | 2.79552 | 1290.59ms | 11521 | 4890 | 1.11926e+08 | 5411.9 | 1.21281 | 2(Tie) |
| glaze STATISTICAL TIE | 1960.26 | 0.173446 | 1348.22ms | 11521 | 80 | 7560.85 | 5605.01 | 1.25627 | 2(Tie) |
| simdjson (ondemand) | 1773.31 | 0.65953 | 1405.81ms | 11521 | 640 | 1.06871e+06 | 6195.92 | 1.38957 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10024.7 | 0.234188 | 886.296ms | 11521 | 160 | 1054.11 | 1096.02 | 0.240229 | 1(Win) |
| glaze | 1890.8 | 0.123753 | 1370.01ms | 11521 | 160 | 8274.09 | 5810.93 | 1.30285 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1880.4 | 0.20871 | 1028.43ms | 4669 | 80 | 1954.01 | 2367.96 | 1.30033 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 1218.78 | 0.103381 | 1170.03ms | 4669 | 40 | 570.605 | 3653.4 | 2.01528 | 2(Tie) |
| glaze STATISTICAL TIE | 1217.44 | 0.160543 | 1172.24ms | 4669 | 30 | 1034.32 | 3657.43 | 2.01768 | 2(Tie) |
| simdjson (ondemand) | 873 | 1.46117 | 1309.6ms | 4669 | 30 | 166625 | 5100.47 | 2.81959 | 4(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6613.5 | 0.67074 | 852.659ms | 4669 | 40 | 815.743 | 673.275 | 0.358058 | 1(Win) |
| simdjson (reflection) | 3997.89 | 0.339574 | 900.064ms | 4669 | 80 | 1144.31 | 1113.76 | 0.602736 | 2(Loss) |
| glaze | 1633.89 | 0.199129 | 1070.88ms | 4669 | 40 | 1177.97 | 2725.22 | 1.49866 | 3(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 2226.28 | 0.355724 | 1200.26ms | 9249 | 30 | 5959.03 | 3962 | 1.10392 | 1(Win) |
| jsonifier | 1896.09 | 1.04245 | 1264.04ms | 9249 | 160 | 376276 | 4651.96 | 1.29712 | 2(Loss) |
| glaze | 1728.75 | 0.0914124 | 1336.81ms | 9249 | 30 | 652.616 | 5102.27 | 1.42383 | 3(Loss) |
| simdjson (ondemand) | 1616.95 | 0.44229 | 1349.12ms | 9249 | 1280 | 745112 | 5455.05 | 1.52267 | 4(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11339.9 | 0.515875 | 868.758ms | 9249 | 4890 | 78735.4 | 777.833 | 0.210123 | 1(Win) |
| glaze | 1464.52 | 0.194181 | 1408.65ms | 9249 | 40 | 5471.04 | 6022.8 | 1.68245 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 617.706 | 0.778397 | 1499.15ms | 4604 | 320 | 979625 | 7108.11 | 3.99107 | 1(Win) |
| glaze | 463.24 | 0.179594 | 1751.28ms | 4604 | 40 | 11590.5 | 9478.27 | 5.32621 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 438.397 | 0.632679 | 1803.68ms | 4604 | 160 | 642424 | 10015.4 | 5.63102 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 433.496 | 0.387421 | 1816.72ms | 4604 | 40 | 61592.4 | 10128.6 | 5.69526 | 3(Tie) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1088.97 | 0.305601 | 1201.08ms | 4604 | 160 | 24292.3 | 4031.99 | 2.25706 | 1(Win) |
| glaze | 625.832 | 0.464787 | 1494.33ms | 4604 | 80 | 85065.5 | 7015.81 | 3.93945 | 2(Loss) |
| simdjson (reflection) | 565.3 | 0.154605 | 1639.66ms | 4918 | 40 | 6581.51 | 8296.77 | 4.36297 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2178.09 | 0.294077 | 1881.85ms | 24579 | 640 | 641034 | 10761.9 | 1.13348 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 2011.62 | 1.93057 | 1958.39ms | 24579 | 30 | 1.51821e+06 | 11652.5 | 1.22762 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2007.52 | 0.254675 | 1983.06ms | 24579 | 40 | 35370.4 | 11676.2 | 1.23021 | 2(Tie) |
| glaze | 1606.67 | 0.197467 | 2279.84ms | 24579 | 40 | 33198.9 | 14589.4 | 1.53793 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5405.05 | 0.207959 | 1231.8ms | 24579 | 80 | 6506.9 | 4336.75 | 0.455068 | 1(Win) |
| glaze | 1773.31 | 0.472023 | 2096.91ms | 24579 | 4890 | 1.90368e+07 | 13218.4 | 1.39208 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 691.601 | 0.283674 | 1430.65ms | 4604 | 40 | 12973.6 | 6348.62 | 3.563 | 1(Win) |
| glaze | 453.86 | 0.212485 | 1756.52ms | 4604 | 30 | 12676.7 | 9674.17 | 5.43078 | 2(Loss) |
| simdjson (ondemand) | 441.315 | 0.397683 | 1787.74ms | 4604 | 320 | 500954 | 9949.16 | 5.59331 | 3(Loss) |
| simdjson (reflection) | 431.562 | 0.832172 | 1817.83ms | 4604 | 40 | 286728 | 10174 | 5.72038 | 4(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1109.95 | 0.116463 | 1192.47ms | 4604 | 30 | 636.737 | 3955.77 | 2.21373 | 1(Win) |
| glaze | 642.098 | 0.0868763 | 1476ms | 4604 | 40 | 1411.66 | 6838.07 | 3.83998 | 2(Loss) |
| simdjson (reflection) | 564.931 | 0.21992 | 1633.81ms | 4918 | 40 | 13334.5 | 8302.2 | 4.36695 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2202.48 | 2.23398 | 1810.51ms | 24579 | 2560 | 1.44711e+08 | 10642.7 | 1.12054 | 1(Win) |
| simdjson (ondemand) | 1995.49 | 0.893777 | 1954.32ms | 24579 | 30 | 330681 | 11746.7 | 1.2376 | 2(Loss) |
| simdjson (reflection) | 1935.43 | 0.715123 | 1992.79ms | 24579 | 2560 | 1.92032e+07 | 12111.2 | 1.27613 | 3(Loss) |
| glaze | 1543.61 | 0.527254 | 2266.07ms | 24579 | 4890 | 3.13472e+07 | 15185.4 | 1.60065 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5159.19 | 0.175467 | 1254.34ms | 24579 | 320 | 20337.9 | 4543.42 | 0.476841 | 1(Win) |
| glaze | 1765.7 | 0.541484 | 2087.26ms | 24579 | 4890 | 2.52684e+07 | 13275.4 | 1.39823 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 779.476 | 0.243777 | 927.78ms | 1181 | 160 | 1985.18 | 1444.93 | 3.1102 | 1(Win) |
| glaze | 589.115 | 0.365342 | 963.485ms | 1181 | 30 | 1463.59 | 1911.83 | 4.1374 | 2(Loss) |
| simdjson (ondemand) | 567.279 | 0.20859 | 978.881ms | 1181 | 80 | 1372.1 | 1985.42 | 4.30039 | 3(Loss) |
| simdjson (reflection) | 539.574 | 0.270658 | 988.25ms | 1181 | 30 | 957.551 | 2087.37 | 4.52408 | 4(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1490.19 | 0.587833 | 853.662ms | 1181 | 30 | 592.166 | 755.8 | 1.59972 | 1(Win) |
| simdjson (reflection) | 792.586 | 0.119971 | 915.652ms | 1187 | 320 | 939.53 | 1428.25 | 3.05969 | 2(Loss) |
| glaze | 683.253 | 0.265686 | 936.872ms | 1181 | 640 | 12275.9 | 1648.42 | 3.55952 | 3(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1138.27 | 0.272898 | 988.855ms | 2496 | 160 | 5210.99 | 2091.22 | 2.1451 | 1(Win) |
| jsonifier | 1122.12 | 0.412788 | 994.012ms | 2496 | 80 | 6134.2 | 2121.32 | 2.17487 | 2(Loss) |
| simdjson (reflection) | 1097.67 | 0.261758 | 994.215ms | 2496 | 80 | 2577.72 | 2168.56 | 2.22421 | 3(Loss) |
| glaze | 1013.23 | 0.177112 | 1013.99ms | 2496 | 80 | 1385.05 | 2349.3 | 2.41198 | 4(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2986.99 | 0.377168 | 852.206ms | 2496 | 80 | 722.739 | 796.913 | 0.798548 | 1(Win) |
| glaze | 991.069 | 0.173175 | 1025.16ms | 2507 | 320 | 5584.95 | 2412.41 | 2.46788 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1057.53 | 0.139791 | 1231.32ms | 4926 | 40 | 1542.5 | 4442.25 | 2.3258 | 1(Win) |
| glaze | 900.324 | 0.351991 | 1306.38ms | 4926 | 40 | 13493.2 | 5217.9 | 2.73432 | 2(Loss) |
| simdjson (ondemand) | 861.444 | 0.240674 | 1341.38ms | 4926 | 30 | 5167.9 | 5453.4 | 2.85844 | 3(Loss) |
| simdjson (reflection) | 830.863 | 1.13672 | 1350.98ms | 4926 | 160 | 660930 | 5654.12 | 2.96451 | 4(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3923.83 | 0.446238 | 897.953ms | 4926 | 40 | 1141.73 | 1197.25 | 0.615555 | 1(Win) |
| simdjson (reflection) | 3682.92 | 0.260926 | 902.823ms | 4926 | 160 | 1772.39 | 1275.56 | 0.656855 | 2(Loss) |
| glaze | 2121.57 | 0.32276 | 1002.01ms | 4926 | 160 | 8172.44 | 2214.3 | 1.15148 | 3(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1757.75 | 0.1266 | 1308.35ms | 9463 | 40 | 1689.94 | 5134.18 | 1.40049 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 1516.25 | 0.158815 | 1383.04ms | 9463 | 80 | 7148.07 | 5951.95 | 1.62486 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1458.28 | 2.53423 | 1375.27ms | 9463 | 4890 | 1.20275e+08 | 6188.52 | 1.68982 | 2(Tie) |
| glaze | 1421.96 | 0.294808 | 1434.82ms | 9463 | 320 | 112024 | 6346.6 | 1.73326 | 4(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6891.06 | 0.372367 | 920.3ms | 9463 | 80 | 1902.47 | 1309.61 | 0.351271 | 1(Win) |
| glaze | 1491.13 | 0.126701 | 1387.26ms | 9463 | 30 | 1764.03 | 6052.2 | 1.65264 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3875.99 | 0.153034 | 845.318ms | 2821 | 640 | 722.097 | 694.097 | 0.611447 | 1(Win) |
| simdjson (reflection) | 3826.5 | 0.395971 | 846.029ms | 2821 | 40 | 310.02 | 703.075 | 0.620728 | 2(Loss) |
| jsonifier | 2641.18 | 0.233521 | 885.087ms | 2821 | 320 | 1810.55 | 1018.6 | 0.910363 | 3(Loss) |
| glaze | 1645.91 | 0.190245 | 940.614ms | 2821 | 80 | 773.592 | 1634.55 | 1.47706 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) STATISTICAL TIE | 4973.14 | 0.208169 | 855.819ms | 4147 | 160 | 438.491 | 795.25 | 0.479692 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 4971.99 | 0.29928 | 856.198ms | 4147 | 1280 | 7253.89 | 795.433 | 0.479898 | 1(Tie) |
| jsonifier | 3471.18 | 0.392863 | 893.152ms | 4147 | 40 | 801.413 | 1139.35 | 0.694972 | 3(Loss) |
| glaze | 2130.13 | 0.126894 | 963.498ms | 4147 | 320 | 1776.19 | 1856.64 | 1.14434 | 4(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1474.48 | 0.172408 | 970.441ms | 2821 | 320 | 3166.58 | 1824.58 | 1.65201 | 1(Win) |
| simdjson (reflection) | 1273.52 | 0.309234 | 999.843ms | 2821 | 4890 | 208680 | 2112.51 | 1.91684 | 2(Loss) |
| jsonifier | 1234.81 | 0.162237 | 1008.25ms | 2821 | 640 | 7996.26 | 2178.73 | 1.97672 | 3(Loss) |
| simdjson (ondemand) | 936.976 | 0.143344 | 1084.75ms | 2821 | 160 | 2710.35 | 2871.28 | 2.61503 | 4(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4396.13 | 0.206206 | 844.006ms | 2821 | 2560 | 4076.7 | 611.973 | 0.536073 | 1(Win) |
| simdjson (reflection) | 3515.03 | 0.736867 | 857.188ms | 2821 | 40 | 1272.29 | 765.375 | 0.677623 | 2(Loss) |
| glaze | 3115.91 | 0.15384 | 872.948ms | 2819 | 640 | 1127.56 | 862.8 | 0.766815 | 3(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 1806.72 | 0.181419 | 1011.62ms | 4147 | 80 | 1261.66 | 2188.99 | 1.35203 | 1(Win) |
| glaze | 1598.53 | 0.271718 | 1035.04ms | 4147 | 160 | 7230.76 | 2474.07 | 1.53067 | 2(Loss) |
| simdjson (ondemand) | 1325.76 | 0.176982 | 1093.46ms | 4147 | 320 | 8919.6 | 2983.1 | 1.84913 | 3(Loss) |
| jsonifier | 1174.7 | 0.158536 | 1140.84ms | 4147 | 40 | 1139.54 | 3366.72 | 2.08354 | 4(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5986.95 | 0.436332 | 846.647ms | 4147 | 320 | 2658.52 | 660.584 | 0.395326 | 1(Win) |
| glaze | 1849 | 0.174396 | 1012.09ms | 4145 | 40 | 556.041 | 2137.9 | 1.32023 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1955.87 | 0.118184 | 6017.01ms | 466906 | 640 | 4.63313e+07 | 227661 | 1.26557 | 1(Win) |
| glaze | 1624.66 | 0.112332 | 7200ms | 466906 | 640 | 6.06628e+07 | 274073 | 1.52361 | 2(Loss) |
| simdjson (ondemand) | 911.173 | 0.188759 | 6301.91ms | 466906 | 160 | 1.36142e+08 | 488685 | 2.71682 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2721.24 | 0.0789772 | 6507.1ms | 699405 | 1280 | 4.79663e+07 | 245110 | 0.909603 | 1(Win) |
| glaze | 1691.82 | 0.165862 | 5102.03ms | 699405 | 80 | 3.42084e+07 | 394254 | 1.46324 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2528.4 | 0.0746793 | 6274.12ms | 631514 | 1280 | 4.05027e+07 | 238197 | 0.979035 | 1(Win) |
| glaze | 1824.77 | 0.0680045 | 8606.02ms | 631514 | 1280 | 6.44816e+07 | 330047 | 1.35663 | 2(Loss) |
