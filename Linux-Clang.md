# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the Clang 24.0.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [2fb9afb](https://github.com/nihilai-collective/jsonifier/commit/2fb9afb)  
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

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 1982.71 | 1.60423 | 347.323ms | 905 | 1280 | 62419.9 | 435.3 | 1.45489 | 1(Win) |
| glaze | 1440.11 | 0.3193 | 352.766ms | 905 | 160 | 585.902 | 599.312 | 2.04457 | 2(Loss) |
| simdjson (ondemand) | 226.003 | 0.133176 | 698.248ms | 905 | 80 | 2069.23 | 3818.86 | 13.3714 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2318.23 | 0.523964 | 330.785ms | 905 | 640 | 2435.39 | 372.3 | 1.2406 | 1(Win) |
| glaze | 224.101 | 0.231744 | 694.378ms | 905 | 40 | 3186.31 | 3851.28 | 13.4907 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1287.65 | 0.390348 | 439.782ms | 1811 | 160 | 4385.98 | 1341.29 | 2.32092 | 1(Win) |
| glaze | 939.582 | 0.295192 | 483.292ms | 1811 | 320 | 9421.65 | 1838.16 | 3.19464 | 2(Loss) |
| simdjson (ondemand) | 267.803 | 0.182496 | 988.073ms | 1811 | 80 | 11081.6 | 6449.16 | 11.3108 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 332.782 | 0.27742 | 841.755ms | 1811 | 30 | 6218.92 | 5189.9 | 9.09884 | 1(Win) |
| glaze | 311.973 | 0.200599 | 866.631ms | 1798 | 40 | 4862.53 | 5496.32 | 9.70184 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3195.28 | 0.287895 | 429.177ms | 3862 | 30 | 330.368 | 1152.67 | 0.934222 | 1(Win) |
| glaze | 1732.11 | 0.490958 | 518.464ms | 3862 | 80 | 8718.72 | 2126.36 | 1.73404 | 2(Loss) |
| simdjson (ondemand) | 609.095 | 0.786655 | 935.374ms | 3862 | 160 | 362029 | 6046.82 | 4.96944 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1017.63 | 0.509283 | 675.882ms | 3862 | 160 | 54361.1 | 3619.3 | 2.96547 | 1(Win) |
| glaze | 950.827 | 0.198133 | 721.544ms | 3862 | 30 | 1767.08 | 3873.57 | 3.17628 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1708.57 | 0.17305 | 862.765ms | 9578 | 30 | 2567.73 | 5346.17 | 1.77051 | 1(Win) |
| glaze | 1454.94 | 0.177164 | 938.561ms | 9578 | 30 | 3711.36 | 6278.13 | 2.07996 | 2(Loss) |
| simdjson (ondemand) | 1183.43 | 0.35866 | 1116.71ms | 9578 | 80 | 61308.2 | 7718.46 | 2.55894 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3634.24 | 0.436036 | 558.737ms | 9578 | 30 | 3603.21 | 2513.4 | 0.828865 | 1(Win) |
| glaze | 2087.11 | 0.174639 | 750.791ms | 9578 | 30 | 1752.53 | 4376.53 | 1.44837 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3312.32 | 0.687597 | 413.142ms | 3873 | 1280 | 75250.1 | 1115.1 | 0.899901 | 1(Win) |
| glaze | 1911.79 | 0.101577 | 492.528ms | 3873 | 40 | 154.051 | 1932 | 1.57044 | 2(Loss) |
| simdjson (ondemand) | 610.626 | 0.550959 | 905.224ms | 3873 | 320 | 355413 | 6048.85 | 4.95848 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 985.971 | 0.535092 | 686.024ms | 3873 | 30 | 12054.4 | 3746.13 | 3.06181 | 1(Win) |
| glaze | 934.28 | 0.202 | 715.955ms | 3873 | 40 | 2550.96 | 3953.4 | 3.23191 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 973.294 | 0.700069 | 6356.62ms | 2090234 | 30 | 6.16744e+09 | 2.0481e+06 | 3.12215 | 1(Win) |
| glaze | 752.418 | 0.368097 | 8271.26ms | 2090234 | 160 | 1.52166e+10 | 2.64933e+06 | 4.03869 | 2(Loss) |
| simdjson (ondemand) | 639.583 | 0.172687 | 9724.18ms | 2090234 | 160 | 4.63485e+09 | 3.11672e+06 | 4.7513 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1450.13 | 0.281547 | 8719.03ms | 2090234 | 80 | 1.19831e+09 | 1.37464e+06 | 2.09546 | 1(Win) |
| glaze | 942.234 | 0.343939 | 6608.39ms | 2090234 | 40 | 2.11785e+09 | 2.11561e+06 | 3.225 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2503.26 | 0.472437 | 7843.63ms | 6661897 | 30 | 4.31314e+09 | 2.538e+06 | 1.21392 | 1(Win) |
| glaze STATISTICAL TIE | 1916.39 | 0.187283 | 10273.9ms | 6661897 | 160 | 6.168e+09 | 3.31524e+06 | 1.58575 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1899.92 | 0.401825 | 5026.42ms | 6661897 | 30 | 5.41654e+09 | 3.34398e+06 | 1.59951 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5096.93 | 0.184303 | 7885.43ms | 6661897 | 320 | 1.68885e+09 | 1.24649e+06 | 0.596141 | 1(Win) |
| glaze | 3084.21 | 0.454184 | 6387.72ms | 6661897 | 40 | 3.50133e+09 | 2.05994e+06 | 0.985217 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1832.57 | 0.304279 | 6771.4ms | 500299 | 320 | 2.00831e+08 | 260357 | 1.65809 | 1(Win) |
| jsonifier | 1762.33 | 0.282358 | 7009.7ms | 500299 | 1280 | 7.47991e+08 | 270734 | 1.7241 | 2(Loss) |
| simdjson (ondemand) | 1199.22 | 0.366395 | 5136.35ms | 500299 | 160 | 3.40003e+08 | 397862 | 2.53382 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9815.96 | 0.373019 | 5251.8ms | 500299 | 2560 | 8.4158e+07 | 48606.8 | 0.3094 | 1(Win) |
| glaze | 5552.92 | 0.316382 | 8912.44ms | 500299 | 2560 | 1.89182e+08 | 85922.7 | 0.546935 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3555.93 | 0.906209 | 5041.79ms | 1439562 | 30 | 3.67226e+08 | 386080 | 0.854428 | 1(Win) |
| simdjson (ondemand) | 3001.33 | 0.417715 | 5949.43ms | 1439562 | 160 | 5.84135e+08 | 457422 | 1.01235 | 2(Loss) |
| glaze | 2795.1 | 0.873224 | 6079.91ms | 1439562 | 320 | 5.88663e+09 | 491171 | 1.08706 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 19176.4 | 0.271254 | 7489.99ms | 1439562 | 2560 | 9.6543e+07 | 71591.9 | 0.158385 | 1(Win) |
| glaze | 5546.62 | 0.188738 | 6385.53ms | 1439584 | 1280 | 2.79348e+08 | 247519 | 0.547709 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1975.85 | 0.748127 | 3015.78ms | 56369 | 1280 | 5.30314e+07 | 27207.4 | 1.53647 | 1(Tie) |
| glaze STATISTICAL TIE | 1970.12 | 0.977529 | 2998.57ms | 56369 | 1280 | 9.10673e+07 | 27286.4 | 1.54096 | 1(Tie) |
| simdjson (ondemand) | 1424.28 | 0.415627 | 4054.67ms | 56369 | 4890 | 1.2034e+08 | 37743.8 | 2.1319 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11584.1 | 0.384591 | 777.587ms | 56369 | 160 | 50965.6 | 4640.66 | 0.260711 | 1(Win) |
| glaze | 6012.86 | 0.375279 | 1200.8ms | 56369 | 640 | 720456 | 8940.45 | 0.503442 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2458.72 | 0.278331 | 3949.33ms | 94370 | 4890 | 5.07555e+07 | 36603.8 | 1.23488 | 1(Win) |
| simdjson (ondemand) | 2214.4 | 0.789965 | 4261.86ms | 94370 | 1280 | 1.31942e+08 | 40642.3 | 1.37107 | 2(Loss) |
| jsonifier | 2060.01 | 0.278118 | 4648.72ms | 94370 | 4890 | 7.21935e+07 | 43688.3 | 1.47425 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15541.2 | 0.830059 | 887.614ms | 94370 | 160 | 369690 | 5790.95 | 0.194485 | 1(Win) |
| glaze | 4795.46 | 0.550335 | 2154.1ms | 94370 | 4890 | 5.2164e+07 | 18767.4 | 0.632476 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1863.36 | 0.184343 | 921.316ms | 11812 | 80 | 9935.74 | 6045.44 | 1.62436 | 1(Win) |
| jsonifier | 1767.91 | 0.257139 | 967.366ms | 11812 | 2560 | 687231 | 6371.81 | 1.71212 | 2(Loss) |
| simdjson (ondemand) | 1316.02 | 2.39878 | 1139.61ms | 11812 | 4890 | 2.06165e+08 | 8559.77 | 2.30236 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8263.27 | 0.234659 | 442.619ms | 11812 | 80 | 818.664 | 1363.24 | 0.36102 | 1(Win) |
| glaze | 3879.2 | 1.16428 | 603.267ms | 11812 | 1280 | 1.46315e+06 | 2903.9 | 0.775731 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3226.34 | 0.149281 | 1248.93ms | 31235 | 40 | 7598.55 | 9232.75 | 0.939634 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3222.64 | 0.396207 | 1269.89ms | 31235 | 40 | 53649.1 | 9243.35 | 0.940307 | 1(Tie) |
| glaze | 2671.9 | 0.278812 | 1496.8ms | 31235 | 30 | 28986 | 11148.6 | 1.13488 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16130.7 | 0.587961 | 491.483ms | 31235 | 1280 | 150898 | 1846.66 | 0.18539 | 1(Win) |
| glaze | 4933.24 | 0.571488 | 941.112ms | 31235 | 320 | 381052 | 6038.23 | 0.613227 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2575 | 0.338282 | 4297.28ms | 108313 | 4890 | 9.0048e+07 | 40114.8 | 1.17926 | 1(Win) |
| glaze | 2257.88 | 0.866651 | 4902.67ms | 108313 | 640 | 1.00607e+08 | 45748.8 | 1.34509 | 2(Loss) |
| simdjson (ondemand) | 1762.75 | 0.490283 | 6224.47ms | 108313 | 1280 | 1.05654e+08 | 58599 | 1.72306 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16611.1 | 0.791743 | 962.888ms | 108313 | 30 | 72720.4 | 6218.47 | 0.18224 | 1(Win) |
| glaze | 6497.11 | 0.841518 | 1981.25ms | 108313 | 30 | 536994 | 15898.7 | 0.466878 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3069.81 | 0.494705 | 6874.35ms | 213963 | 4890 | 5.28756e+08 | 66470.2 | 0.989428 | 1(Win) |
| glaze | 2862.68 | 0.613818 | 7491ms | 213963 | 640 | 1.22515e+08 | 71279.7 | 1.06123 | 2(Loss) |
| jsonifier | 2641.95 | 0.585452 | 7928.08ms | 213963 | 4890 | 9.99817e+08 | 77235 | 1.14961 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 20906.8 | 0.0760004 | 1348.78ms | 213963 | 30 | 1650.65 | 9760.03 | 0.144983 | 1(Win) |
| glaze | 5376.71 | 0.710908 | 4154.1ms | 213963 | 2560 | 1.86342e+08 | 37950.9 | 0.564727 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 814.946 | 0.543558 | 6761.92ms | 1834197 | 30 | 4.08365e+09 | 2.14643e+06 | 3.72883 | 1(Win) |
| glaze | 665.034 | 0.370366 | 8383.31ms | 1834197 | 30 | 2.84699e+09 | 2.63028e+06 | 4.56943 | 2(Loss) |
| simdjson (ondemand) | 598.606 | 0.352302 | 9308.21ms | 1834197 | 40 | 4.23937e+09 | 2.92217e+06 | 5.07659 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 791.872 | 0.656273 | 6888.21ms | 1834197 | 80 | 1.68128e+10 | 2.20898e+06 | 3.83756 | 1(Win) |
| glaze | 609.899 | 0.660252 | 8975.07ms | 1833577 | 30 | 1.07503e+10 | 2.86709e+06 | 4.98285 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5617.34 | 0.433128 | 5226.6ms | 9930848 | 160 | 8.53226e+09 | 1.68599e+06 | 0.540934 | 1(Win) |
| glaze | 3405.36 | 0.537813 | 8645.48ms | 9930228 | 160 | 3.57912e+10 | 2.78097e+06 | 0.892327 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 843.789 | 0.316087 | 6537.89ms | 1834197 | 80 | 3.43501e+09 | 2.07306e+06 | 3.60128 | 1(Win) |
| glaze | 661.251 | 0.775895 | 8295.95ms | 1834197 | 30 | 1.26382e+10 | 2.64533e+06 | 4.59547 | 2(Loss) |
| simdjson (ondemand) | 593.143 | 0.691618 | 9131.16ms | 1834197 | 80 | 3.32809e+10 | 2.94908e+06 | 5.1225 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3289.54 | 0.311436 | 9081.75ms | 9930848 | 160 | 1.28635e+10 | 2.87906e+06 | 0.923766 | 1(Win) |
| simdjson (ondemand) | 2713.64 | 0.547729 | 5254.51ms | 9930848 | 80 | 2.9234e+10 | 3.49007e+06 | 1.11977 | 2(Loss) |
| glaze | 2597.67 | 0.548017 | 5623.37ms | 9930848 | 40 | 1.59681e+10 | 3.64588e+06 | 1.16985 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1364.92 | 0.342541 | 5741.48ms | 642697 | 640 | 1.51427e+09 | 449055 | 2.22602 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1360.2 | 0.33936 | 5781.34ms | 642697 | 320 | 7.48307e+08 | 450614 | 2.23378 | 1(Tie) |
| simdjson (ondemand) | 1122.77 | 0.284821 | 6973.13ms | 642697 | 640 | 1.54723e+09 | 545902 | 2.70609 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1468.39 | 0.530385 | 5362.15ms | 642697 | 160 | 7.84205e+08 | 417411 | 2.06925 | 1(Win) |
| glaze | 1012.87 | 0.556874 | 7810.07ms | 642692 | 80 | 9.08448e+08 | 605129 | 2.99994 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2092.25 | 0.336202 | 7142.14ms | 1225964 | 640 | 2.25895e+09 | 558809 | 1.45216 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2078.74 | 0.261313 | 7193.15ms | 1225964 | 320 | 6.91241e+08 | 562443 | 1.46161 | 1(Tie) |
| jsonifier | 1881.18 | 0.301101 | 7932.77ms | 1225964 | 640 | 2.2413e+09 | 621509 | 1.61512 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2776.92 | 0.671532 | 5403.44ms | 1225964 | 40 | 3.19759e+08 | 421032 | 1.09422 | 1(Win) |
| glaze | 1694.84 | 0.5244 | 8693.59ms | 1225970 | 80 | 1.04693e+09 | 689843 | 1.79256 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1507.62 | 0.681827 | 6922.03ms | 409725 | 160 | 4.99655e+08 | 259180 | 2.01527 | 1(Win) |
| glaze | 1170.32 | 0.376381 | 8802.85ms | 409725 | 640 | 1.01068e+09 | 333879 | 2.59627 | 2(Loss) |
| simdjson (ondemand) | 1014.05 | 0.584202 | 9825.45ms | 409725 | 640 | 3.24317e+09 | 385329 | 2.99599 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1924.83 | 0.364618 | 5124.34ms | 785750 | 80 | 1.61194e+08 | 389307 | 1.57871 | 1(Win) |
| simdjson (ondemand) | 1894.25 | 0.612122 | 5081.48ms | 785750 | 80 | 4.69097e+08 | 395593 | 1.60392 | 2(Loss) |
| glaze | 1828.28 | 0.725827 | 5291.92ms | 785750 | 160 | 1.41601e+09 | 409865 | 1.66193 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11186.7 | 0.403945 | 7020.96ms | 785750 | 1280 | 9.37174e+07 | 66985.9 | 0.27146 | 1(Win) |
| glaze | 3805.78 | 0.435229 | 5133.79ms | 785750 | 640 | 4.69998e+08 | 196898 | 0.798252 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5657.75 | 0.823253 | 4732.17ms | 264040 | 1280 | 1.71842e+08 | 44506.8 | 0.536741 | 1(Win) |
| simdjson (ondemand) | 5353.18 | 0.480773 | 5012.86ms | 264040 | 2560 | 1.30929e+08 | 47039 | 0.567316 | 2(Loss) |
| glaze | 3319.11 | 0.234108 | 7847.59ms | 264040 | 4890 | 1.54255e+08 | 75866.2 | 0.915101 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7440.92 | 0.346325 | 5490.16ms | 399947 | 4890 | 1.54109e+08 | 51259.7 | 0.408148 | 1(Win) |
| simdjson (ondemand) | 7013.72 | 0.312054 | 5768.99ms | 399947 | 4890 | 1.40824e+08 | 54381.9 | 0.432734 | 2(Loss) |
| glaze | 4104.53 | 0.378442 | 9659.35ms | 399947 | 1280 | 1.58302e+08 | 92926.4 | 0.740118 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1996.4 | 0.853858 | 6930.08ms | 264040 | 30 | 3.47968e+07 | 126131 | 1.52199 | 1(Win) |
| jsonifier | 1861.73 | 0.483112 | 7445.97ms | 264040 | 640 | 2.73264e+08 | 135255 | 1.63188 | 2(Loss) |
| simdjson (ondemand) | 1530.66 | 0.693684 | 8547.56ms | 264040 | 1280 | 1.66693e+09 | 164510 | 1.98449 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12181.6 | 1.03837 | 2405.98ms | 264040 | 4890 | 2.25292e+08 | 20671.2 | 0.249101 | 1(Win) |
| glaze | 6064.55 | 1.25587 | 4871.5ms | 263923 | 80 | 2.17337e+07 | 41502.9 | 0.500788 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2240.77 | 0.477229 | 8814.02ms | 399947 | 2560 | 1.68928e+09 | 170218 | 1.35571 | 1(Win) |
| glaze | 2082.65 | 1.02367 | 9393.79ms | 399947 | 640 | 2.2494e+09 | 183141 | 1.45876 | 2(Loss) |
| jsonifier | 1875.08 | 0.411067 | 5392.9ms | 399947 | 1280 | 8.94952e+08 | 203414 | 1.62035 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 16654.6 | 0.897007 | 2566.87ms | 399947 | 4890 | 2.06365e+08 | 22901.7 | 0.182201 | 1(Win) |
| glaze | 4003.03 | 0.952789 | 9798.41ms | 399830 | 4890 | 4.02787e+09 | 95254.8 | 0.758723 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2925.38 | 0.842262 | 7883.97ms | 466906 | 640 | 1.05188e+09 | 152211 | 1.03851 | 1(Win) |
| glaze | 2429.29 | 0.92199 | 9858.06ms | 466906 | 80 | 2.28477e+08 | 183295 | 1.25067 | 2(Loss) |
| simdjson (ondemand) | 1128.03 | 1.07257 | 9774.19ms | 466906 | 320 | 5.73617e+09 | 394739 | 2.69292 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4314.96 | 0.334302 | 8183.18ms | 699405 | 1280 | 3.41815e+08 | 154580 | 0.704095 | 1(Win) |
| glaze | 3721.49 | 0.271204 | 9263.04ms | 699405 | 2560 | 6.04862e+08 | 179230 | 0.816268 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4457.34 | 0.245229 | 7051.14ms | 631514 | 2560 | 2.8106e+08 | 135116 | 0.681544 | 1(Win) |
| glaze | 2443.11 | 0.201577 | 6384.88ms | 631514 | 1280 | 3.16061e+08 | 246513 | 1.24368 | 2(Loss) |
