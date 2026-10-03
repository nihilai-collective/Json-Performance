# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [3ca767b](https://github.com/nihilai-collective/jsonifier/commit/3ca767b)  
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
| jsonifier | 990.731 | 0.38857 | 965.363ms | 905 | 40 | 458.336 | 871.15 | 2.2518 | 1(Win) |
| glaze | 773.735 | 0.149068 | 976.362ms | 905 | 30 | 82.9471 | 1115.47 | 2.9175 | 2(Loss) |
| simdjson (ondemand) | 104.762 | 0.614499 | 1791.07ms | 905 | 30 | 76887 | 8238.43 | 22.1619 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 864.285 | 0.242204 | 971.461ms | 905 | 80 | 467.99 | 998.6 | 2.59783 | 1(Win) |
| glaze | 101.074 | 0.0721469 | 1708.43ms | 905 | 30 | 1138.62 | 8539.07 | 22.9785 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 696.202 | 0.285216 | 1119.81ms | 1811 | 40 | 2002.5 | 2480.75 | 3.29895 | 1(Win) |
| glaze | 542.794 | 0.503252 | 1195.97ms | 1811 | 1280 | 328207 | 3181.88 | 4.24578 | 2(Loss) |
| simdjson (ondemand) | 140.859 | 1.40068 | 2061.84ms | 1811 | 2560 | 7.55071e+07 | 12261.3 | 16.4832 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 171.649 | 0.27996 | 1867.28ms | 1811 | 30 | 23805 | 10061.8 | 13.5375 | 1(Win) |
| glaze | 139.716 | 0.064976 | 2090.44ms | 1798 | 40 | 2543.61 | 12272.8 | 16.6428 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1638.05 | 0.121935 | 1090.31ms | 3862 | 80 | 601.34 | 2248.46 | 1.40079 | 1(Win) |
| glaze | 992.675 | 0.311518 | 1227.52ms | 3862 | 30 | 4007.72 | 3710.27 | 2.32608 | 2(Loss) |
| simdjson (ondemand) | 321.721 | 0.381805 | 2018.42ms | 3862 | 40 | 76420.2 | 11448.1 | 7.22488 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 435.321 | 1.63978 | 1674.58ms | 3862 | 4890 | 9.41212e+07 | 8460.63 | 5.33174 | 1(Tie) |
| glaze STATISTICAL TIE | 433.613 | 0.635044 | 1730.12ms | 3862 | 320 | 931063 | 8493.96 | 5.35547 | 1(Tie) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 669.458 | 0.501949 | 2186.67ms | 9578 | 4890 | 2.29368e+07 | 13644.3 | 3.47355 | 1(Win) |
| jsonifier | 637.31 | 0.681544 | 2224.18ms | 9578 | 4890 | 4.666e+07 | 14332.6 | 3.64918 | 2(Loss) |
| simdjson (ondemand) | 555.148 | 0.932998 | 2407.72ms | 9578 | 2560 | 6.033e+07 | 16453.8 | 4.18522 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1287.04 | 0.137551 | 1567.54ms | 9578 | 30 | 2859.02 | 7097.13 | 1.80293 | 1(Win) |
| glaze | 1013.83 | 0.112418 | 1745.21ms | 9578 | 30 | 3077.61 | 9009.67 | 2.29098 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1871.66 | 0.187243 | 1042.16ms | 3873 | 40 | 546.148 | 1973.42 | 1.22182 | 1(Win) |
| glaze | 1114.39 | 0.11986 | 1169.13ms | 3873 | 80 | 1262.58 | 3314.45 | 2.06935 | 2(Loss) |
| simdjson (ondemand) | 320.986 | 0.720568 | 2018.81ms | 3873 | 30 | 206249 | 11507 | 7.24165 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 459.985 | 1.26884 | 1634.98ms | 3873 | 160 | 1.66089e+06 | 8029.79 | 5.04715 | 1(Win) |
| glaze | 431.974 | 0.0637692 | 1699.74ms | 3873 | 30 | 891.913 | 8550.47 | 5.37528 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 447.842 | 0.0577616 | 6713.23ms | 2090234 | 80 | 5.28823e+08 | 4.45113e+06 | 5.20737 | 1(Win) |
| glaze | 378.994 | 0.11281 | 7928.21ms | 2090234 | 30 | 1.05619e+09 | 5.25972e+06 | 6.15328 | 2(Loss) |
| simdjson (ondemand) | 322.585 | 0.128058 | 9310.45ms | 2090234 | 30 | 1.87861e+09 | 6.17947e+06 | 7.22935 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 741.323 | 0.0279606 | 8384.67ms | 2090234 | 160 | 9.04461e+07 | 2.68898e+06 | 3.14582 | 1(Win) |
| glaze | 660.19 | 0.051704 | 9369.74ms | 2090234 | 160 | 3.89959e+08 | 3.01944e+06 | 3.5324 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1237.66 | 0.0692109 | 7753.34ms | 6661897 | 40 | 5.04893e+08 | 5.13328e+06 | 1.88425 | 1(Win) |
| glaze | 990.589 | 0.0970172 | 9695.16ms | 6661897 | 40 | 1.5487e+09 | 6.41364e+06 | 2.35424 | 2(Loss) |
| simdjson (ondemand) | 964.216 | 0.106953 | 9931.06ms | 6661897 | 30 | 1.48989e+09 | 6.58906e+06 | 2.41863 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2350.31 | 0.0468688 | 8421.51ms | 6661897 | 40 | 6.42056e+07 | 2.70316e+06 | 0.992226 | 1(Win) |
| glaze | 1483.35 | 0.111589 | 6484.67ms | 6661897 | 80 | 1.82744e+09 | 4.28306e+06 | 1.57214 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1017.88 | 0.10411 | 6047.87ms | 500299 | 320 | 7.62074e+07 | 468740 | 2.29085 | 1(Win) |
| glaze | 876.269 | 0.114116 | 7041.91ms | 500299 | 160 | 6.17729e+07 | 544493 | 2.66117 | 2(Loss) |
| simdjson (ondemand) | 606.975 | 0.126591 | 5040.72ms | 500299 | 30 | 2.97061e+07 | 786066 | 3.84195 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5290.7 | 0.140761 | 5064.79ms | 500299 | 2560 | 4.12515e+07 | 90181.3 | 0.440532 | 1(Win) |
| glaze | 2024.25 | 0.113353 | 6238.45ms | 500299 | 1280 | 9.13709e+07 | 235703 | 1.15178 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1885.43 | 0.125143 | 9325.35ms | 1439562 | 80 | 6.64276e+07 | 728151 | 1.23682 | 1(Win) |
| glaze | 1587.87 | 0.115363 | 5538.33ms | 1439562 | 30 | 2.98462e+07 | 864603 | 1.46863 | 2(Loss) |
| simdjson (ondemand) | 1545.26 | 0.125229 | 5638.94ms | 1439562 | 30 | 3.71358e+07 | 888444 | 1.50909 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12525.5 | 0.314152 | 6126.55ms | 1439562 | 320 | 3.79405e+07 | 109607 | 0.18611 | 1(Win) |
| glaze | 2219.93 | 0.145926 | 7933.19ms | 1439584 | 160 | 1.30311e+08 | 618440 | 1.05044 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 934.526 | 0.207849 | 6513.19ms | 56369 | 4890 | 6.99038e+07 | 57524 | 2.49355 | 1(Win) |
| glaze | 817.183 | 0.181439 | 7382.48ms | 56369 | 2560 | 3.64708e+07 | 65784.1 | 2.8521 | 2(Loss) |
| simdjson (ondemand) | 718.66 | 0.169275 | 8363.18ms | 56369 | 2560 | 4.10449e+07 | 74802.7 | 3.2431 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6398.86 | 0.2634 | 1731.46ms | 56369 | 30 | 14690.3 | 8401.13 | 0.36279 | 1(Win) |
| glaze | 2002.76 | 0.36103 | 3516.21ms | 56369 | 4890 | 4.59216e+07 | 26841.8 | 1.16256 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1142.2 | 0.144267 | 8651.79ms | 94370 | 4890 | 6.31874e+07 | 78794 | 2.04061 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1138.17 | 0.168588 | 8768.44ms | 94370 | 2560 | 4.54933e+07 | 79072.6 | 2.04775 | 1(Tie) |
| jsonifier | 1043.58 | 0.128563 | 9488ms | 94370 | 4890 | 6.01111e+07 | 86239.8 | 2.23349 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9944.28 | 0.532549 | 1841.16ms | 94370 | 320 | 743345 | 9050.25 | 0.233562 | 1(Win) |
| glaze | 1771.49 | 0.16889 | 5902.96ms | 94370 | 4890 | 3.60003e+07 | 50803.6 | 1.3152 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 927.332 | 0.685322 | 2040.56ms | 11812 | 4890 | 3.38903e+07 | 12147.5 | 2.507 | 1(Win) |
| glaze | 720.673 | 0.638087 | 2374.32ms | 11812 | 4890 | 4.86451e+07 | 15630.9 | 3.22816 | 2(Loss) |
| simdjson (ondemand) | 607.823 | 0.891542 | 2681.3ms | 11812 | 1280 | 3.49451e+07 | 18533 | 3.82914 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4349.68 | 0.282581 | 1123.75ms | 11812 | 30 | 1606.72 | 2589.8 | 0.52857 | 1(Win) |
| glaze | 1208.4 | 0.0975481 | 1806.06ms | 11812 | 30 | 2480.75 | 9322.07 | 1.92241 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1582.3 | 0.476026 | 2686.8ms | 31235 | 4890 | 3.92716e+07 | 18825.8 | 1.47095 | 1(Win) |
| simdjson (ondemand) | 1453.06 | 0.470367 | 2859.96ms | 31235 | 4890 | 4.54674e+07 | 20500.2 | 1.602 | 2(Loss) |
| glaze | 1333.11 | 0.435162 | 3041.07ms | 31235 | 4890 | 4.62338e+07 | 22344.7 | 1.74547 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10271.5 | 0.401618 | 1170.81ms | 31235 | 30 | 4069.72 | 2900.07 | 0.224278 | 1(Win) |
| glaze | 1860.51 | 0.505482 | 2488.28ms | 31235 | 40 | 261995 | 16010.7 | 1.25043 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1439.9 | 0.180963 | 8007.92ms | 108313 | 2560 | 4.31434e+07 | 71737.8 | 1.61876 | 1(Win) |
| glaze | 1072.69 | 0.171976 | 5335.95ms | 108313 | 2560 | 7.02076e+07 | 96295.3 | 2.17298 | 2(Loss) |
| simdjson (ondemand) | 830.649 | 0.450992 | 6814.65ms | 108313 | 160 | 5.03249e+07 | 124355 | 2.80654 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8815.09 | 1.48711 | 2001.42ms | 108313 | 4890 | 1.48492e+08 | 11718 | 0.263734 | 1(Win) |
| glaze | 1716.34 | 0.139383 | 6836.41ms | 108313 | 4890 | 3.44097e+07 | 60183.5 | 1.35778 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1503.8 | 0.154701 | 7377.65ms | 213963 | 1280 | 5.64021e+07 | 135690 | 1.55009 | 1(Win) |
| glaze | 1471.93 | 0.251392 | 7561.8ms | 213963 | 640 | 7.77292e+07 | 138628 | 1.58384 | 2(Loss) |
| jsonifier | 1360.03 | 0.143083 | 8071.06ms | 213963 | 2560 | 1.17976e+08 | 150034 | 1.71415 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13964.3 | 1.92606 | 2320.85ms | 213963 | 640 | 5.06939e+07 | 14612.3 | 0.166555 | 1(Win) |
| glaze | 1759.58 | 0.12182 | 6369.39ms | 213963 | 2560 | 5.109e+07 | 115966 | 1.32457 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 433.243 | 0.0922701 | 6092.07ms | 1834197 | 80 | 1.1103e+09 | 4.03752e+06 | 5.38275 | 1(Win) |
| glaze | 357.701 | 0.0669162 | 7367.58ms | 1834197 | 40 | 4.28326e+08 | 4.89019e+06 | 6.51963 | 2(Loss) |
| simdjson (ondemand) | 292.501 | 0.184273 | 8988ms | 1834197 | 30 | 3.64319e+09 | 5.98024e+06 | 7.97265 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 483.625 | 0.0451162 | 5451.39ms | 1834197 | 40 | 1.06512e+08 | 3.61691e+06 | 4.82201 | 1(Win) |
| glaze | 405.069 | 0.0599729 | 6496.46ms | 1833577 | 80 | 5.36218e+08 | 4.31689e+06 | 5.75716 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1651.13 | 0.1112 | 8651.03ms | 9930848 | 80 | 3.25469e+09 | 5.73593e+06 | 1.41236 | 1(Win) |
| glaze | 1396.56 | 0.136097 | 10286.7ms | 9930848 | 30 | 2.55547e+09 | 6.78151e+06 | 1.66984 | 2(Loss) |
| simdjson (ondemand) | 1388.13 | 0.163013 | 10236ms | 9930848 | 30 | 3.71087e+09 | 6.82268e+06 | 1.67993 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2524.62 | 0.0703814 | 5662.55ms | 9930848 | 40 | 2.7884e+08 | 3.75137e+06 | 0.923716 | 1(Win) |
| glaze | 1610.56 | 0.0974984 | 8882.63ms | 9930228 | 30 | 9.86011e+08 | 5.88008e+06 | 1.44795 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 426.4 | 0.204393 | 6161.67ms | 1834197 | 30 | 2.10918e+09 | 4.10232e+06 | 5.46907 | 1(Win) |
| glaze | 350.997 | 0.0768691 | 7495.3ms | 1834197 | 80 | 1.17403e+09 | 4.98359e+06 | 6.64404 | 2(Loss) |
| simdjson (ondemand) | 293.474 | 0.288588 | 8959.57ms | 1834197 | 40 | 1.1835e+10 | 5.96042e+06 | 7.94622 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 485.367 | 0.0430417 | 5421.52ms | 1834197 | 80 | 1.92496e+08 | 3.60393e+06 | 4.80464 | 1(Win) |
| glaze | 387.964 | 0.0665116 | 6768.63ms | 1833577 | 30 | 2.69608e+08 | 4.50721e+06 | 6.01101 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1744.04 | 0.186918 | 8204.81ms | 9930848 | 30 | 3.0909e+09 | 5.43039e+06 | 1.33711 | 1(Win) |
| glaze | 1391.98 | 0.189387 | 10267.6ms | 9930848 | 30 | 4.98118e+09 | 6.80385e+06 | 1.67532 | 2(Loss) |
| simdjson (ondemand) | 1371.28 | 0.0810492 | 10344.1ms | 9930848 | 80 | 2.50672e+09 | 6.90652e+06 | 1.70053 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2518.92 | 0.0636257 | 5664.95ms | 9930848 | 80 | 4.57826e+08 | 3.75987e+06 | 0.925803 | 1(Win) |
| glaze | 1436.28 | 0.112585 | 9941.36ms | 9930228 | 30 | 1.65319e+09 | 6.59355e+06 | 1.6236 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 751.558 | 0.0862157 | 5202.76ms | 642697 | 160 | 7.91006e+07 | 815537 | 3.10281 | 1(Win) |
| jsonifier | 701.385 | 0.0568319 | 5616.7ms | 642697 | 160 | 3.94643e+07 | 873876 | 3.3248 | 2(Loss) |
| simdjson (ondemand) | 586.427 | 0.091886 | 6678.67ms | 642697 | 40 | 3.68929e+07 | 1.04518e+06 | 3.9766 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 813.019 | 0.0656523 | 9721.6ms | 642697 | 320 | 7.83902e+07 | 753886 | 2.86824 | 1(Win) |
| glaze | 636.422 | 0.088129 | 6106.3ms | 642692 | 160 | 1.15259e+08 | 963070 | 3.66419 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1062.84 | 0.0545604 | 6969.52ms | 1225964 | 320 | 1.15273e+08 | 1.10005e+06 | 2.1941 | 1(Win) |
| jsonifier | 999.059 | 0.076105 | 7495.26ms | 1225964 | 160 | 1.26917e+08 | 1.17027e+06 | 2.3342 | 2(Loss) |
| glaze | 995.055 | 0.111435 | 7433.5ms | 1225964 | 160 | 2.74301e+08 | 1.17498e+06 | 2.34354 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1536.97 | 0.136507 | 9819.87ms | 1225964 | 40 | 4.31317e+07 | 760697 | 1.51724 | 1(Win) |
| glaze | 1078.73 | 0.0386143 | 6895.7ms | 1225970 | 320 | 5.60503e+07 | 1.08384e+06 | 2.16171 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 742.452 | 0.204312 | 6849.1ms | 409725 | 40 | 4.62483e+07 | 526289 | 3.14077 | 1(Win) |
| glaze | 586.631 | 0.217214 | 8546.79ms | 409725 | 160 | 3.34929e+08 | 666081 | 3.97504 | 2(Loss) |
| simdjson (ondemand) | 535.227 | 0.136957 | 9403.96ms | 409725 | 80 | 7.99779e+07 | 730053 | 4.35686 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2972.8 | 0.187512 | 7204.45ms | 409725 | 640 | 3.88768e+07 | 131440 | 0.784237 | 1(Win) |
| glaze | 1462.64 | 0.251324 | 7027.66ms | 409725 | 160 | 7.21275e+07 | 267150 | 1.59416 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 972.906 | 0.154757 | 9926.11ms | 785750 | 40 | 5.68313e+07 | 770218 | 2.39687 | 1(Win) |
| jsonifier | 960.859 | 0.0553059 | 10021.7ms | 785750 | 640 | 1.19062e+08 | 779875 | 2.42693 | 2(Loss) |
| glaze | 889.899 | 0.175715 | 5412.06ms | 785750 | 40 | 8.75722e+07 | 842061 | 2.62046 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5316.33 | 0.207355 | 7685.54ms | 785750 | 640 | 5.46703e+07 | 140952 | 0.43855 | 1(Win) |
| glaze | 1637.42 | 0.0820262 | 5931.59ms | 785750 | 640 | 9.01847e+07 | 457640 | 1.4241 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2768.48 | 0.319892 | 5113.18ms | 264040 | 640 | 5.41804e+07 | 90955.4 | 0.841921 | 1(Win) |
| simdjson (ondemand) | 2740.75 | 0.151388 | 5127.93ms | 264040 | 2560 | 4.95248e+07 | 91875.7 | 0.850456 | 2(Loss) |
| glaze | 1771.89 | 0.213994 | 7712.87ms | 264040 | 640 | 5.91899e+07 | 142113 | 1.31573 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3620.35 | 0.16867 | 5833.87ms | 399947 | 1280 | 4.04192e+07 | 105354 | 0.643899 | 1(Win) |
| jsonifier | 3557.99 | 0.475106 | 5935.94ms | 399947 | 160 | 4.15047e+07 | 107201 | 0.655153 | 2(Loss) |
| glaze | 2392.05 | 0.332254 | 8609.9ms | 399947 | 160 | 4.4908e+07 | 159453 | 0.97461 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 991.969 | 0.179162 | 6743.27ms | 264040 | 320 | 6.61893e+07 | 253847 | 2.35035 | 1(Win) |
| glaze | 932.497 | 0.11301 | 7192.86ms | 264040 | 1280 | 1.19204e+08 | 270037 | 2.50037 | 2(Loss) |
| simdjson (ondemand) | 853.915 | 0.0987888 | 7788.71ms | 264040 | 1280 | 1.08626e+08 | 294887 | 2.73054 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5620.47 | 0.494239 | 5330.49ms | 264040 | 1280 | 6.27596e+07 | 44802 | 0.414387 | 1(Win) |
| glaze | 2544.99 | 0.146679 | 5493.86ms | 263923 | 2560 | 5.38717e+07 | 98898.8 | 0.915863 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1183.93 | 0.475817 | 8186.03ms | 399947 | 30 | 7.04942e+07 | 322164 | 1.9694 | 1(Win) |
| glaze | 1079.91 | 0.149877 | 9268.38ms | 399947 | 320 | 8.96704e+07 | 353194 | 2.15911 | 2(Loss) |
| jsonifier | 915.957 | 0.390115 | 5420.19ms | 399947 | 80 | 2.1112e+08 | 416416 | 2.54492 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8084.06 | 0.302754 | 5631.78ms | 399947 | 2560 | 5.22355e+07 | 47181.7 | 0.288142 | 1(Win) |
| glaze | 2216.44 | 0.1873 | 9259.46ms | 399830 | 640 | 6.645e+07 | 172036 | 1.05186 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 649.713 | 0.150089 | 1578.56ms | 4630 | 30 | 3121.33 | 6796.1 | 3.56952 | 1(Win) |
| glaze | 451.39 | 0.157055 | 1915.1ms | 4630 | 30 | 7080.79 | 9782.03 | 5.14746 | 2(Loss) |
| simdjson (ondemand) | 387.66 | 0.125528 | 2058.9ms | 4630 | 30 | 6132.9 | 11390.2 | 5.99606 | 3(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 768.138 | 0.0627419 | 1460.67ms | 4630 | 30 | 390.23 | 5748.33 | 3.01601 | 1(Win) |
| glaze | 662.847 | 0.114873 | 1560.83ms | 4630 | 30 | 1756.67 | 6661.43 | 3.49983 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1524.02 | 0.0783646 | 1812.87ms | 14795 | 40 | 2105.46 | 9258.15 | 1.52428 | 1(Win) |
| simdjson (ondemand) | 1123.58 | 0.111538 | 2161.29ms | 14795 | 80 | 15694.8 | 12557.7 | 2.06972 | 2(Loss) |
| glaze | 1020.87 | 0.824129 | 2238.49ms | 14795 | 2560 | 3.32136e+07 | 13821.1 | 2.27828 | 3(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2332.12 | 0.0889282 | 1500.55ms | 14795 | 80 | 2315.77 | 6050.11 | 0.993868 | 1(Win) |
| glaze | 1464.47 | 0.13844 | 1858.16ms | 14795 | 40 | 7116.24 | 9634.62 | 1.58646 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4052.67 | 0.352474 | 1027.45ms | 5092 | 40 | 713.526 | 1198.25 | 0.557782 | 1(Win) |
| glaze | 1654.51 | 0.326452 | 1195.78ms | 5092 | 30 | 2754.2 | 2935.07 | 1.39179 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1299.75 | 0.187804 | 1795.24ms | 11724 | 40 | 10440 | 8602.3 | 1.78647 | 1(Win) |
| jsonifier | 1241.15 | 0.599981 | 1812.37ms | 11724 | 640 | 1.86965e+06 | 9008.49 | 1.87126 | 2(Loss) |
| glaze | 1206.79 | 0.196422 | 1860.83ms | 11724 | 30 | 9935.52 | 9265 | 1.9245 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8085.29 | 0.723856 | 1046.04ms | 11724 | 30 | 3005.98 | 1382.87 | 0.281073 | 1(Win) |
| glaze | 2087.94 | 0.334125 | 1470.73ms | 11746 | 30 | 9640.17 | 5365.03 | 1.1089 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 851.412 | 0.288792 | 1454.32ms | 4857 | 30 | 7405.41 | 5440.37 | 2.72055 | 1(Tie) |
| jsonifier STATISTICAL TIE | 846.27 | 0.25734 | 1458.03ms | 4857 | 40 | 7935.84 | 5473.43 | 2.73652 | 1(Tie) |
| simdjson (ondemand) | 715.829 | 0.21069 | 1548.01ms | 4857 | 80 | 14869.4 | 6470.81 | 3.23922 | 3(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3789.26 | 0.318981 | 1009.03ms | 4857 | 160 | 2432.63 | 1222.4 | 0.596887 | 1(Win) |
| glaze | 1858.21 | 0.176754 | 1123.97ms | 4857 | 40 | 776.512 | 2492.72 | 1.23675 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1095.1 | 0.643557 | 1544.28ms | 7376 | 640 | 1.09367e+06 | 6423.41 | 2.11758 | 1(Win) |
| simdjson (ondemand) | 1047.4 | 0.374674 | 1566.21ms | 7376 | 30 | 18995 | 6715.93 | 2.21385 | 2(Loss) |
| jsonifier | 778.95 | 2.63575 | 1779.52ms | 7376 | 1280 | 7.25171e+07 | 9030.49 | 2.9785 | 3(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5934.43 | 0.286537 | 1014.05ms | 7376 | 80 | 922.859 | 1185.34 | 0.381072 | 1(Win) |
| glaze | 1779.33 | 0.191981 | 1320.07ms | 7376 | 40 | 2304.13 | 3953.35 | 1.29899 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 997.393 | 0.142307 | 1311.22ms | 4390 | 40 | 1427.28 | 4197.57 | 2.31731 | 1(Win) |
| glaze | 816.649 | 0.13101 | 1398.72ms | 4390 | 30 | 1353.28 | 5126.6 | 2.83339 | 2(Loss) |
| simdjson (ondemand) | 667.309 | 0.108346 | 1542.05ms | 4390 | 40 | 1848.25 | 6273.9 | 3.47449 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3699.34 | 0.450808 | 1003.3ms | 4390 | 40 | 1041.18 | 1131.72 | 0.609977 | 1(Win) |
| glaze | 1189.67 | 0.405697 | 1226.63ms | 4390 | 80 | 16306.8 | 3519.15 | 1.94011 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1670.56 | 0.0951703 | 1548.09ms | 11521 | 40 | 1567.18 | 6577 | 1.38768 | 1(Win) |
| simdjson (ondemand) | 1596.35 | 0.0945772 | 1572.51ms | 11521 | 30 | 1271.22 | 6882.77 | 1.45322 | 2(Loss) |
| glaze | 1300.96 | 2.88364 | 1673.67ms | 11521 | 4890 | 2.9003e+08 | 8445.51 | 1.78461 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8916.08 | 0.656303 | 1015.78ms | 11521 | 30 | 1962.29 | 1232.3 | 0.253699 | 1(Win) |
| glaze | 1773.48 | 0.375476 | 1519.82ms | 11521 | 1280 | 692633 | 6195.33 | 1.3071 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1205.71 | 0.165778 | 1262.56ms | 4669 | 80 | 2998.52 | 3693.01 | 1.91444 | 1(Win) |
| glaze | 1070.93 | 0.166299 | 1289.87ms | 4669 | 160 | 7649.4 | 4157.81 | 2.15794 | 2(Loss) |
| simdjson (ondemand) | 815.305 | 0.105099 | 1446.01ms | 4669 | 30 | 988.386 | 5461.4 | 2.84269 | 3(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6032.84 | 0.311952 | 956.823ms | 4669 | 320 | 1696.4 | 738.078 | 0.368433 | 1(Win) |
| glaze | 1656.82 | 0.157237 | 1157.51ms | 4669 | 80 | 1428.56 | 2687.5 | 1.38832 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1528.57 | 0.078776 | 1489.34ms | 9249 | 30 | 619.913 | 5770.47 | 1.51581 | 1(Win) |
| glaze | 1380 | 0.700713 | 1547.47ms | 9249 | 640 | 1.28379e+06 | 6391.71 | 1.6799 | 2(Loss) |
| jsonifier | 1151.93 | 0.318102 | 1691.5ms | 9249 | 80 | 47463.9 | 7657.2 | 2.01465 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10428 | 0.519487 | 984.316ms | 9249 | 80 | 1544.64 | 845.85 | 0.214129 | 1(Win) |
| glaze | 1897.69 | 0.203583 | 1363ms | 9249 | 30 | 2686.24 | 4648.03 | 1.21896 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 474.547 | 0.48793 | 1861.48ms | 4604 | 30 | 61143.2 | 9252.43 | 4.89362 | 1(Win) |
| glaze | 364.072 | 0.0915023 | 2144.21ms | 4604 | 30 | 3653.27 | 12060 | 6.38489 | 2(Loss) |
| simdjson (ondemand) | 297.112 | 0.19391 | 2431.91ms | 4604 | 30 | 24634.9 | 14778 | 7.82963 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 691.613 | 0.0816168 | 1544.65ms | 4604 | 80 | 2147.8 | 6348.51 | 3.35213 | 1(Win) |
| glaze | 489.314 | 0.121335 | 1804.87ms | 4604 | 30 | 3556.23 | 8973.2 | 4.74586 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1463.42 | 1.31305 | 2569.96ms | 24579 | 30 | 1.327e+06 | 16017.5 | 1.58891 | 1(Win) |
| simdjson (ondemand) | 1415.9 | 0.686305 | 2597.82ms | 24579 | 40 | 516370 | 16555.2 | 1.64334 | 2(Loss) |
| glaze | 1267.64 | 0.319146 | 2793.58ms | 24579 | 30 | 104481 | 18491.4 | 1.83511 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3439.47 | 0.245982 | 1607.6ms | 24579 | 30 | 8430.85 | 6815.1 | 0.674427 | 1(Win) |
| glaze | 1819.92 | 0.118697 | 2221.2ms | 24579 | 40 | 9348.88 | 12879.9 | 1.27802 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 552.878 | 0.0903486 | 1710.73ms | 4604 | 30 | 1544.46 | 7941.57 | 4.19846 | 1(Win) |
| glaze | 334.88 | 0.82498 | 2149.32ms | 4604 | 4890 | 5.72119e+07 | 13111.3 | 6.94393 | 2(Loss) |
| simdjson (ondemand) | 275.56 | 0.711813 | 2436.37ms | 4604 | 4890 | 6.29041e+07 | 15933.8 | 8.44297 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 694.683 | 0.13179 | 1549.78ms | 4604 | 80 | 5550.76 | 6320.46 | 3.33788 | 1(Win) |
| glaze | 493.044 | 0.0857056 | 1804.59ms | 4604 | 160 | 9320.47 | 8905.33 | 4.71065 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1488.78 | 0.776275 | 2438.52ms | 24579 | 4890 | 7.30482e+07 | 15744.7 | 1.56196 | 1(Win) |
| simdjson (ondemand) | 1414.33 | 0.0640481 | 2654.48ms | 24579 | 30 | 3380.32 | 16573.4 | 1.6451 | 2(Loss) |
| glaze | 1209.56 | 0.643053 | 2766.74ms | 24579 | 4890 | 7.59411e+07 | 19379.3 | 1.92318 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3465.54 | 0.0807671 | 1604.34ms | 24579 | 30 | 895.316 | 6763.83 | 0.669504 | 1(Win) |
| glaze | 1840.34 | 0.0936721 | 2214.12ms | 24579 | 30 | 4270.45 | 12737 | 1.2634 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 573.243 | 0.35485 | 1096.47ms | 1181 | 30 | 1458.25 | 1964.77 | 3.99077 | 1(Win) |
| glaze | 495.092 | 0.0739627 | 1125.95ms | 1181 | 640 | 1811.9 | 2274.91 | 4.63274 | 2(Loss) |
| simdjson (ondemand) | 409.715 | 0.0690958 | 1183.49ms | 1181 | 320 | 1154.49 | 2748.96 | 5.61449 | 3(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 791.714 | 0.938595 | 1037.63ms | 1181 | 1280 | 228207 | 1422.6 | 2.87068 | 1(Win) |
| glaze | 582.611 | 0.234962 | 1090.95ms | 1181 | 40 | 825.276 | 1933.17 | 3.92913 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 857.645 | 0.172263 | 1181.31ms | 2496 | 40 | 914.358 | 2775.47 | 2.68311 | 1(Win) |
| glaze STATISTICAL TIE | 831.058 | 0.297548 | 1194.17ms | 2496 | 30 | 2179.03 | 2864.27 | 2.769 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 830.62 | 0.167385 | 1189.05ms | 2496 | 80 | 1840.81 | 2865.78 | 2.77207 | 2(Tie) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1642.95 | 0.206674 | 1037.79ms | 2496 | 80 | 717.302 | 1448.84 | 1.38486 | 1(Win) |
| glaze | 958.005 | 0.20448 | 1156.79ms | 2507 | 30 | 781.264 | 2495.67 | 2.39656 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 912.381 | 0.731458 | 1410.61ms | 4926 | 320 | 453906 | 5148.95 | 2.53828 | 1(Win) |
| glaze | 656.469 | 0.41706 | 1636.08ms | 4926 | 30 | 26722.7 | 7156.17 | 3.53476 | 2(Loss) |
| simdjson (ondemand) | 570.491 | 0.198635 | 1740.12ms | 4926 | 30 | 8026.44 | 8234.67 | 4.06959 | 3(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3202.02 | 0.287149 | 1043.22ms | 4926 | 80 | 1419.87 | 1467.14 | 0.709668 | 1(Win) |
| glaze | 1451.78 | 0.304989 | 1221.06ms | 4926 | 160 | 15583.8 | 3235.89 | 1.58792 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1112.84 | 0.0970502 | 1731.81ms | 9463 | 30 | 1858.26 | 8109.53 | 2.08649 | 1(Win) |
| simdjson (ondemand) | 1044.2 | 0.160013 | 1788.23ms | 9463 | 30 | 5737.55 | 8642.63 | 2.22406 | 2(Loss) |
| glaze | 990.174 | 0.19673 | 1839.51ms | 9463 | 40 | 12859.8 | 9114.17 | 2.34541 | 3(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5668.11 | 0.171582 | 1058.66ms | 9463 | 160 | 1194.11 | 1592.17 | 0.401851 | 1(Win) |
| glaze | 1641.91 | 0.342594 | 1446.86ms | 9463 | 30 | 10637.4 | 5496.4 | 1.4111 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2509.63 | 0.0985213 | 1013.87ms | 2821 | 640 | 713.886 | 1072 | 0.896595 | 1(Win) |
| jsonifier | 2246.96 | 0.13511 | 1034.94ms | 2821 | 160 | 418.707 | 1197.31 | 1.00561 | 2(Loss) |
| glaze | 1816.46 | 0.264323 | 1046.78ms | 2821 | 80 | 1226.07 | 1481.08 | 1.25083 | 3(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3381.37 | 0.135796 | 1025.85ms | 4147 | 160 | 403.622 | 1169.61 | 0.667516 | 1(Win) |
| jsonifier | 2989.71 | 0.113673 | 1048.71ms | 4147 | 160 | 361.776 | 1322.83 | 0.757837 | 2(Loss) |
| glaze | 2345.55 | 0.167723 | 1083.39ms | 4147 | 40 | 319.907 | 1686.12 | 0.971992 | 3(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1221.54 | 0.274276 | 1131.63ms | 2821 | 40 | 1459.58 | 2202.4 | 1.87597 | 1(Win) |
| jsonifier | 1082.48 | 0.196201 | 1168.08ms | 2821 | 30 | 713.333 | 2485.33 | 2.12145 | 2(Loss) |
| simdjson (ondemand) | 1003.79 | 0.510113 | 1179.16ms | 2821 | 2560 | 478510 | 2680.15 | 2.29082 | 3(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4078.31 | 0.24488 | 965.453ms | 2821 | 640 | 1670.05 | 659.664 | 0.539972 | 1(Win) |
| glaze | 2379.17 | 0.441537 | 1027.24ms | 2819 | 80 | 1991.42 | 1129.97 | 0.948386 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1443.05 | 0.171519 | 1193.31ms | 4147 | 40 | 883.874 | 2740.65 | 1.59438 | 1(Win) |
| glaze | 1392.04 | 0.65425 | 1189.29ms | 4147 | 1280 | 442244 | 2841.07 | 1.65339 | 2(Loss) |
| jsonifier | 943.907 | 0.391434 | 1349.64ms | 4147 | 320 | 86075 | 4189.91 | 2.44376 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6067.07 | 0.159299 | 956.521ms | 4147 | 1280 | 1380.22 | 651.861 | 0.36284 | 1(Win) |
| glaze | 1986.55 | 0.270849 | 1078.93ms | 4145 | 80 | 2323.78 | 1989.88 | 1.15166 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1295.76 | 0.185213 | 9260.21ms | 466906 | 320 | 1.29629e+08 | 343641 | 1.79952 | 1(Win) |
| jsonifier | 1277.3 | 0.137534 | 9094.71ms | 466906 | 640 | 1.4712e+08 | 348607 | 1.82553 | 2(Loss) |
| simdjson (ondemand) | 627.919 | 0.0682187 | 9144.28ms | 466906 | 320 | 7.48873e+07 | 709130 | 3.7137 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1870.73 | 0.143354 | 9316.82ms | 699405 | 320 | 8.35989e+07 | 356547 | 1.24646 | 1(Win) |
| jsonifier | 1762.84 | 0.218093 | 9643.88ms | 699405 | 160 | 1.08952e+08 | 378369 | 1.32275 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2402.89 | 0.145009 | 6651.3ms | 631514 | 640 | 8.45408e+07 | 250640 | 0.970348 | 1(Win) |
| glaze | 1400.93 | 0.11548 | 5619.41ms | 631514 | 320 | 7.88668e+07 | 429898 | 1.66448 | 2(Loss) |
