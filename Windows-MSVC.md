# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [dded0f9](https://github.com/nihilai-collective/jsonifier/commit/dded0f9)  
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

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 328.165 | 0.32356 | 312.99ms | 905 | 30 | 2172.41 | 2630 | 7.07565 | 1(Win) |
| glaze | 202.422 | 0.133535 | 440.477ms | 905 | 80 | 2593.35 | 4263.75 | 11.4057 | 2(Loss) |
| simdjson (ondemand) | 62.406 | 0.0706248 | 1440.11ms | 905 | 30 | 2862.07 | 13830 | 37.2644 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 503.802 | 0.353557 | 179.636ms | 905 | 320 | 11739.4 | 1713.12 | 4.52829 | 1(Win) |
| glaze | 48.903 | 0.296818 | 1881.09ms | 905 | 4890 | 1.34189e+07 | 17648.7 | 47.5847 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 352.303 | 0.319229 | 505.772ms | 1811 | 4890 | 1.19762e+06 | 4902.33 | 6.56802 | 1(Win) |
| glaze | 186.445 | 0.0966019 | 894.462ms | 1811 | 30 | 2402.3 | 9263.33 | 12.4664 | 2(Loss) |
| simdjson (ondemand) | 90.5487 | 1.08251 | 2081.57ms | 1811 | 80 | 3.41057e+06 | 19073.8 | 25.6991 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 114.606 | 0.224045 | 1507.88ms | 1811 | 4890 | 5.57442e+06 | 15069.9 | 20.2906 | 1(Win) |
| glaze | 75.6711 | 0.093675 | 2377.63ms | 1798 | 30 | 13517.2 | 22660 | 30.7585 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1122.89 | 0.271816 | 343.263ms | 3862 | 40 | 3179.49 | 3280 | 2.05017 | 1(Win) |
| glaze | 492.145 | 0.0768184 | 784.64ms | 3862 | 80 | 2643.99 | 7483.75 | 4.71475 | 2(Loss) |
| simdjson (ondemand) | 213.661 | 0.344791 | 1733.72ms | 3862 | 1280 | 4.52167e+06 | 17238 | 10.8917 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 252.261 | 1.06648 | 1454.41ms | 3862 | 640 | 1.5517e+07 | 14600.3 | 9.21995 | 1(Win) |
| glaze | 196.556 | 0.342378 | 1892.6ms | 3862 | 4890 | 2.01267e+07 | 18738.1 | 11.8372 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 552.407 | 0.316044 | 1658.03ms | 9578 | 2560 | 6.99142e+06 | 16535.4 | 4.21171 | 1(Win) |
| glaze | 428.369 | 0.757607 | 2370.73ms | 9578 | 320 | 8.35127e+06 | 21323.4 | 5.434 | 2(Loss) |
| simdjson (ondemand) | 337.517 | 0.147452 | 2750.48ms | 9578 | 4890 | 7.78696e+06 | 27063.2 | 6.89993 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 644.23 | 0.343236 | 1450.41ms | 9578 | 4890 | 1.15814e+07 | 14178.6 | 3.60999 | 1(Win) |
| glaze | 482.783 | 0.152664 | 1899.59ms | 9578 | 4890 | 4.07972e+06 | 18920.1 | 4.82002 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1112.52 | 0.221024 | 342.88ms | 3873 | 40 | 2153.85 | 3320 | 2.07171 | 1(Win) |
| glaze | 546.59 | 0.269595 | 707.255ms | 3873 | 40 | 13275.6 | 6757.5 | 4.25019 | 2(Loss) |
| simdjson (ondemand) | 212.761 | 0.262625 | 1743.36ms | 3873 | 1280 | 2.66068e+06 | 17360.2 | 10.9374 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 287.326 | 0.0551802 | 1315.03ms | 3873 | 80 | 4025.32 | 12855 | 8.0914 | 1(Win) |
| glaze | 198.828 | 0.390284 | 1871.15ms | 3873 | 2560 | 1.34568e+07 | 18576.8 | 11.7037 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 353.668 | 0.71934 | 8462.66ms | 2090234 | 80 | 1.31509e+11 | 5.63636e+06 | 6.59374 | 1(Win) |
| glaze STATISTICAL TIE | 210.44 | 0.659703 | 6738.4ms | 2090234 | 40 | 1.56204e+11 | 9.47256e+06 | 11.0817 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 210.112 | 0.739865 | 6621.9ms | 2090234 | 40 | 1.97084e+11 | 9.48732e+06 | 11.0989 | 2(Tie) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 854.292 | 0.755811 | 5330.11ms | 6661897 | 40 | 1.26377e+11 | 7.43689e+06 | 2.72964 | 1(Win) |
| simdjson (ondemand) | 566.056 | 0.602316 | 7902.31ms | 6661897 | 40 | 1.82805e+11 | 1.12238e+07 | 4.11943 | 2(Loss) |
| glaze | 530.053 | 0.767336 | 8432.79ms | 6661897 | 30 | 2.53776e+11 | 1.19861e+07 | 4.39926 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1375.55 | 0.924909 | 7158.98ms | 6661897 | 80 | 1.45993e+11 | 4.61873e+06 | 1.69525 | 1(Win) |
| glaze | 697.482 | 0.70681 | 6374.24ms | 6661897 | 40 | 1.65804e+11 | 9.10888e+06 | 3.34308 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 694.128 | 0.134183 | 8819.97ms | 500299 | 640 | 5.44444e+08 | 687369 | 3.35938 | 1(Win) |
| glaze | 474.781 | 0.410473 | 6364.53ms | 500299 | 80 | 1.36123e+09 | 1.00493e+06 | 4.9116 | 2(Loss) |
| simdjson (ondemand) | 260.177 | 0.113185 | 5802.09ms | 500299 | 30 | 1.29247e+08 | 1.83384e+06 | 8.96301 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4276.4 | 0.303415 | 5781.87ms | 500299 | 320 | 3.66712e+07 | 111571 | 0.54495 | 1(Win) |
| glaze | 1338.41 | 0.215258 | 9289.28ms | 500299 | 160 | 9.4215e+07 | 356484 | 1.74213 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1344.66 | 0.180379 | 6504.03ms | 1439562 | 160 | 5.42661e+08 | 1.02098e+06 | 1.73419 | 1(Win) |
| glaze | 1042.02 | 0.281788 | 8325.3ms | 1439562 | 160 | 2.20533e+09 | 1.31751e+06 | 2.2379 | 2(Loss) |
| simdjson (ondemand) | 688.557 | 0.270512 | 6218.82ms | 1439562 | 40 | 1.16363e+09 | 1.99384e+06 | 3.3868 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3527.94 | 0.719213 | 5285.43ms | 1439562 | 30 | 2.34994e+08 | 389143 | 0.660698 | 1(Win) |
| glaze | 1037.96 | 0.291967 | 8419.01ms | 1439584 | 40 | 5.96544e+08 | 1.32269e+06 | 2.24635 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 656.097 | 0.197796 | 8254.87ms | 56369 | 1280 | 3.36194e+07 | 81935.5 | 3.55159 | 1(Win) |
| jsonifier | 552.988 | 0.118446 | 9851.86ms | 56369 | 2560 | 3.39414e+07 | 97213.2 | 4.21488 | 2(Loss) |
| simdjson (ondemand) | 310.509 | 0.352337 | 9064.85ms | 56369 | 160 | 5.95345e+07 | 173128 | 7.50767 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4765.6 | 0.406304 | 1136.05ms | 56369 | 2560 | 5.37758e+06 | 11280.4 | 0.487572 | 1(Win) |
| glaze | 1243.85 | 0.113184 | 4425.98ms | 56369 | 4890 | 1.1701e+07 | 43218.7 | 1.8728 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 937.371 | 0.154225 | 9666.16ms | 94370 | 2560 | 5.61299e+07 | 96011.4 | 2.48599 | 1(Win) |
| jsonifier | 710.512 | 1.15581 | 6564.4ms | 94370 | 30 | 6.43009e+07 | 126667 | 3.28037 | 2(Loss) |
| simdjson (ondemand) | 499.041 | 0.135485 | 9265.58ms | 94370 | 2560 | 1.52833e+08 | 180342 | 4.67137 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6785.44 | 0.36091 | 1355.5ms | 94370 | 1280 | 2.93305e+06 | 13263.4 | 0.34264 | 1(Win) |
| glaze | 1150.01 | 0.170356 | 7892.24ms | 94370 | 1280 | 2.27505e+07 | 78258.8 | 2.02628 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 733.719 | 0.229259 | 1545.65ms | 11812 | 2560 | 3.1716e+06 | 15353 | 3.17066 | 1(Win) |
| glaze | 524.655 | 0.264399 | 2216.22ms | 11812 | 2560 | 8.25008e+06 | 21470.9 | 4.43591 | 2(Loss) |
| simdjson (ondemand) | 251.683 | 0.115888 | 4580.94ms | 11812 | 4890 | 1.31561e+07 | 44758 | 9.25664 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3806.08 | 0.121956 | 309.848ms | 11812 | 320 | 4169.18 | 2959.69 | 0.605145 | 1(Win) |
| glaze | 1071.67 | 0.247535 | 1054.53ms | 11812 | 2560 | 1.73315e+06 | 10511.4 | 2.16691 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1144.57 | 0.312276 | 2641.8ms | 31235 | 1280 | 8.45448e+06 | 26025.5 | 2.03451 | 1(Win) |
| glaze | 1041.08 | 0.132547 | 3008.92ms | 31235 | 40 | 57532.1 | 28612.5 | 2.23606 | 2(Loss) |
| simdjson (ondemand) | 617.864 | 0.570053 | 4958.81ms | 31235 | 160 | 1.2085e+07 | 48211.2 | 3.77122 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8122.16 | 0.104126 | 401.025ms | 31235 | 160 | 2333.33 | 3667.5 | 0.284669 | 1(Win) |
| glaze | 1426.14 | 0.386124 | 2129.61ms | 31235 | 640 | 4.16287e+06 | 20887.2 | 1.63194 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 711.14 | 0.201252 | 7448.82ms | 108313 | 1280 | 1.09381e+08 | 145253 | 3.27783 | 1(Tie) |
| glaze STATISTICAL TIE | 704.658 | 0.66073 | 7687.59ms | 108313 | 160 | 1.50098e+08 | 146589 | 3.30824 | 1(Tie) |
| simdjson (ondemand) | 321.931 | 0.133548 | 8221.8ms | 108313 | 1280 | 2.35029e+08 | 320862 | 7.24243 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5637.91 | 0.187666 | 1837.5ms | 108313 | 4890 | 5.78102e+06 | 18321.6 | 0.412767 | 1(Win) |
| glaze | 1322.75 | 0.217696 | 7843.18ms | 108313 | 640 | 1.84963e+07 | 78091.1 | 1.76176 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1022.75 | 0.212042 | 5070.29ms | 213963 | 1280 | 2.29083e+08 | 199512 | 2.2794 | 1(Win) |
| jsonifier | 911.359 | 0.408389 | 5682.66ms | 213963 | 320 | 2.67545e+08 | 223898 | 2.55816 | 2(Loss) |
| simdjson (ondemand) | 605.46 | 0.182995 | 8648.44ms | 213963 | 320 | 1.21713e+08 | 337018 | 3.85093 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8978.48 | 0.0728787 | 2420.46ms | 213963 | 30 | 8229.89 | 22726.7 | 0.25915 | 1(Win) |
| glaze | 1325.34 | 0.20333 | 7950.18ms | 213963 | 1280 | 1.25439e+08 | 153961 | 1.75877 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 273.967 | 0.524932 | 9662.21ms | 1834197 | 40 | 4.49328e+10 | 6.38481e+06 | 8.51138 | 1(Win) |
| glaze | 174.726 | 0.86909 | 7068.22ms | 1834197 | 30 | 2.27105e+11 | 1.00112e+07 | 13.3461 | 2(Loss) |
| simdjson (ondemand) | 51.6909 | 0.237592 | 10295.8ms | 1834197 | 30 | 1.93931e+11 | 3.38401e+07 | 45.1157 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 389.293 | 0.126962 | 6760.63ms | 1834197 | 40 | 1.3018e+09 | 4.49334e+06 | 5.99009 | 1(Win) |
| glaze | 305.015 | 0.0779016 | 8616.81ms | 1833577 | 30 | 5.98372e+08 | 5.73296e+06 | 7.64545 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1183.61 | 0.233338 | 5625.63ms | 9930848 | 40 | 1.39441e+10 | 8.00164e+06 | 1.97022 | 1(Win) |
| glaze | 828.781 | 0.55298 | 8082.83ms | 9930848 | 40 | 1.59725e+11 | 1.14274e+07 | 2.81382 | 2(Loss) |
| simdjson (ondemand) | 256.044 | 1.36879 | 10875.5ms | 9930848 | 30 | 7.69015e+12 | 3.69889e+07 | 9.10789 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1576.78 | 0.539829 | 9273.63ms | 9930848 | 80 | 8.41071e+10 | 6.00641e+06 | 1.47891 | 1(Win) |
| glaze | 910.237 | 0.409681 | 7275.62ms | 9930228 | 30 | 5.45031e+10 | 1.04041e+07 | 2.56181 | 2(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 369.975 | 0.594603 | 7048.22ms | 1834197 | 40 | 3.16126e+10 | 4.72795e+06 | 6.30274 | 1(Win) |
| glaze | 286.113 | 0.502756 | 9270.96ms | 1833577 | 40 | 3.77658e+10 | 6.1117e+06 | 8.15051 | 2(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1534.63 | 0.634538 | 9192.6ms | 9930848 | 40 | 6.13399e+10 | 6.1714e+06 | 1.51943 | 1(Win) |
| glaze | 791.92 | 0.721499 | 8362.4ms | 9930228 | 30 | 2.23331e+11 | 1.19585e+07 | 2.94474 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 499.671 | 0.195222 | 7744.6ms | 642697 | 40 | 2.29385e+08 | 1.22666e+06 | 4.66705 | 1(Win) |
| simdjson (ondemand) | 445.524 | 0.192546 | 8787.63ms | 642697 | 40 | 2.80673e+08 | 1.37574e+06 | 5.2343 | 2(Loss) |
| glaze | 425.201 | 0.362772 | 9106.62ms | 642697 | 160 | 4.37536e+09 | 1.44149e+06 | 5.48439 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 609.219 | 0.13259 | 6346.51ms | 642697 | 320 | 5.69425e+08 | 1.00608e+06 | 3.82711 | 1(Win) |
| glaze | 520.842 | 0.168485 | 7424.38ms | 642692 | 320 | 1.25796e+09 | 1.17678e+06 | 4.47654 | 2(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1067.43 | 0.263079 | 6932.54ms | 1225964 | 160 | 1.32851e+09 | 1.09531e+06 | 2.18419 | 1(Win) |
| glaze | 785.539 | 0.220364 | 9417.8ms | 1225970 | 160 | 1.72117e+09 | 1.48838e+06 | 2.96819 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 516.934 | 0.100104 | 9663.69ms | 409725 | 640 | 3.66433e+08 | 755888 | 4.51105 | 1(Win) |
| glaze | 306.893 | 3.62145 | 6366.84ms | 409725 | 40 | 8.50426e+10 | 1.27322e+06 | 7.59744 | 2(Loss) |
| simdjson (ondemand) | 265.119 | 0.341589 | 9395.08ms | 409725 | 30 | 7.60381e+08 | 1.47384e+06 | 8.79599 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1470.25 | 1.92693 | 6805.05ms | 409725 | 80 | 2.0981e+09 | 265768 | 1.58459 | 1(Win) |
| glaze | 1066.59 | 0.255431 | 9373.66ms | 409725 | 320 | 2.8021e+08 | 366348 | 2.18605 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 773.964 | 0.391319 | 6179.76ms | 785750 | 30 | 4.30636e+08 | 968197 | 3.01301 | 1(Win) |
| glaze | 696.576 | 0.23131 | 6893.59ms | 785750 | 320 | 1.9814e+09 | 1.07576e+06 | 3.34771 | 2(Loss) |
| simdjson (ondemand) | 488.519 | 0.169903 | 9839.48ms | 785750 | 30 | 2.03765e+08 | 1.53392e+06 | 4.77364 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2261.19 | 1.32525 | 8699.81ms | 785750 | 160 | 3.0861e+09 | 331396 | 1.03078 | 1(Win) |
| glaze | 917.907 | 0.725255 | 5162.57ms | 785750 | 40 | 1.40221e+09 | 816368 | 2.53992 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2138.63 | 0.162533 | 6046.98ms | 264040 | 1280 | 4.68767e+07 | 117742 | 1.08992 | 1(Win) |
| simdjson (ondemand) | 1389.39 | 0.158485 | 9367.28ms | 264040 | 1280 | 1.05603e+08 | 181236 | 1.67799 | 2(Loss) |
| glaze | 1302.7 | 0.132498 | 5054.01ms | 264040 | 1280 | 8.39609e+07 | 193297 | 1.78979 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2909.89 | 0.263066 | 6774.25ms | 399947 | 640 | 7.60959e+07 | 131077 | 0.801004 | 1(Win) |
| simdjson (ondemand) | 1851.35 | 0.351779 | 5293.43ms | 399947 | 160 | 8.40406e+07 | 206022 | 1.25933 | 2(Loss) |
| glaze | 1486.06 | 0.124729 | 6549.36ms | 399947 | 1280 | 1.31183e+08 | 256665 | 1.56899 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 668.31 | 0.174588 | 5108.24ms | 264040 | 640 | 2.76943e+08 | 376783 | 3.48883 | 1(Win) |
| glaze | 645.472 | 0.543929 | 6134.81ms | 264040 | 40 | 1.80106e+08 | 390115 | 3.61237 | 2(Loss) |
| simdjson (ondemand) | 416.976 | 0.1621 | 7777.99ms | 264040 | 320 | 3.06645e+08 | 603891 | 5.5923 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4130.39 | 0.128509 | 6111.27ms | 264040 | 4890 | 3.00145e+07 | 60964.7 | 0.564038 | 1(Win) |
| glaze | 1747.69 | 0.851038 | 7429.75ms | 263923 | 30 | 4.50656e+07 | 144017 | 1.33372 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 844.074 | 0.183174 | 5850.08ms | 399947 | 640 | 4.38483e+08 | 451879 | 2.76245 | 1(Win) |
| jsonifier | 713.472 | 0.186802 | 6798.02ms | 399947 | 640 | 6.38256e+08 | 534596 | 3.26756 | 2(Loss) |
| simdjson (ondemand) | 605.09 | 0.111673 | 8015.04ms | 399947 | 640 | 3.17133e+08 | 630351 | 3.85372 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5336.65 | 0.127591 | 7156.68ms | 399947 | 4890 | 4.06645e+07 | 71471.6 | 0.436562 | 1(Win) |
| glaze | 1646.24 | 0.214762 | 5933.59ms | 399830 | 320 | 7.91827e+07 | 231623 | 1.4162 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 341.56 | 0.0918095 | 1321.91ms | 4630 | 40 | 5634.62 | 12927.5 | 6.80932 | 1(Win) |
| glaze | 190.879 | 0.0971425 | 2415.9ms | 4630 | 40 | 20198.7 | 23132.5 | 12.1895 | 2(Loss) |
| simdjson (ondemand) | 179.717 | 0.300538 | 2484.56ms | 4630 | 1280 | 6.97897e+06 | 24569.2 | 12.9563 | 3(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 706.765 | 0.140239 | 617.014ms | 4630 | 40 | 3070.51 | 6247.5 | 3.28475 | 1(Win) |
| glaze | 478.636 | 0.192911 | 927.855ms | 4630 | 4890 | 1.54873e+06 | 9225.19 | 4.84678 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 869.175 | 0.185237 | 1660.43ms | 14795 | 30 | 27126.4 | 16233.3 | 2.67737 | 1(Win) |
| simdjson (ondemand) | 546.955 | 0.121144 | 2676.53ms | 14795 | 30 | 29298.9 | 25796.7 | 4.25743 | 2(Loss) |
| glaze | 498.963 | 0.172483 | 2874.12ms | 14795 | 2560 | 6.09014e+06 | 28277.9 | 4.66694 | 3(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2163.22 | 0.0692486 | 667.89ms | 14795 | 160 | 3264.15 | 6522.5 | 1.07192 | 1(Win) |
| glaze | 1150.1 | 0.229912 | 1233.75ms | 14795 | 2560 | 2.0367e+06 | 12268.2 | 2.01782 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 495.521 | 0.115538 | 1008.93ms | 5092 | 40 | 5128.21 | 9800 | 4.68973 | 1(Win) |
| glaze | 385.57 | 0.188255 | 1287.72ms | 5092 | 4890 | 2.74899e+06 | 12594.6 | 6.02803 | 2(Loss) |
| simdjson (ondemand) | 254.18 | 0.078403 | 1982.78ms | 5092 | 80 | 17949.4 | 19105 | 9.15419 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3004.55 | 0.279394 | 150.718ms | 5092 | 80 | 1631.33 | 1616.25 | 0.758052 | 1(Win) |
| glaze | 1180.34 | 0.251204 | 417.024ms | 5092 | 4890 | 522303 | 4114.15 | 1.95223 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 800.177 | 0.308724 | 1407.75ms | 11724 | 2560 | 4.76387e+06 | 13973 | 2.90351 | 1(Win) |
| glaze | 747.551 | 0.0764227 | 1541.29ms | 11724 | 30 | 3919.54 | 14956.7 | 3.1068 | 2(Loss) |
| simdjson (ondemand) | 541.268 | 0.160752 | 2073.97ms | 11724 | 4890 | 5.39198e+06 | 20656.8 | 4.29955 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6024.89 | 0.205686 | 194.415ms | 11724 | 640 | 9324.9 | 1855.78 | 0.37976 | 1(Win) |
| glaze | 1533.98 | 0.224559 | 743.537ms | 11746 | 80 | 21512.7 | 7302.5 | 1.50896 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 550.55 | 0.333925 | 848.586ms | 4857 | 2560 | 2.0206e+06 | 8413.4 | 4.2137 | 1(Win) |
| jsonifier | 507.616 | 0.0945056 | 939.439ms | 4857 | 80 | 5949.37 | 9125 | 4.57476 | 2(Loss) |
| simdjson (ondemand) | 312.55 | 0.155079 | 1522.41ms | 4857 | 40 | 21128.2 | 14820 | 7.43172 | 3(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3333.87 | 0.146666 | 147.13ms | 4857 | 320 | 1328.76 | 1389.38 | 0.681813 | 1(Win) |
| glaze | 1231.73 | 0.433473 | 384.18ms | 4857 | 1280 | 340123 | 3760.55 | 1.87024 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 751.528 | 0.152057 | 980.446ms | 7376 | 40 | 8102.56 | 9360 | 3.09016 | 1(Win) |
| jsonifier | 551.902 | 0.256456 | 1275.99ms | 7376 | 4890 | 5.2246e+06 | 12745.6 | 4.21135 | 2(Loss) |
| simdjson (ondemand) | 447.333 | 0.191127 | 1577.47ms | 7376 | 4890 | 4.41708e+06 | 15725 | 5.19763 | 3(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4113.63 | 0.429827 | 161.861ms | 7376 | 30 | 1620.69 | 1710 | 0.554384 | 1(Win) |
| glaze | 1136.25 | 0.2214 | 625.466ms | 7376 | 4890 | 918674 | 6190.82 | 2.03569 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 674.9 | 0.144254 | 633.357ms | 4390 | 30 | 2402.3 | 6203.33 | 3.43204 | 1(Win) |
| glaze | 509.417 | 0.290267 | 827.993ms | 4390 | 2560 | 1.45686e+06 | 8218.48 | 4.55477 | 2(Loss) |
| simdjson (ondemand) | 248.27 | 0.207909 | 1703.2ms | 4390 | 2560 | 3.14681e+06 | 16863.2 | 9.36901 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3033.79 | 0.46414 | 122.167ms | 4390 | 40 | 1641.03 | 1380 | 0.749937 | 1(Win) |
| glaze | 1069.96 | 0.419402 | 398.71ms | 4390 | 1280 | 344720 | 3912.89 | 2.15436 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1065.39 | 0.306647 | 1035.67ms | 11521 | 2560 | 2.56025e+06 | 10312.9 | 2.18117 | 1(Win) |
| glaze | 969.123 | 0.301897 | 1137.58ms | 11521 | 2560 | 2.99903e+06 | 11337.3 | 2.39739 | 2(Loss) |
| simdjson (ondemand) | 607.197 | 0.162746 | 1816.12ms | 11521 | 4890 | 4.24082e+06 | 18095.1 | 3.83177 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6929.48 | 0.538602 | 163.82ms | 11521 | 2560 | 186705 | 1585.59 | 0.328924 | 1(Win) |
| glaze | 1359.99 | 0.213055 | 813.252ms | 11521 | 4890 | 1.44877e+06 | 8078.92 | 1.70555 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 703.315 | 0.257383 | 639.39ms | 4669 | 4890 | 1.29842e+06 | 6331.02 | 3.29401 | 1(Win) |
| glaze | 683.865 | 0.263059 | 671.543ms | 4669 | 4890 | 1.43457e+06 | 6511.08 | 3.38416 | 2(Loss) |
| simdjson (ondemand) | 325.828 | 0.181227 | 1375.68ms | 4669 | 4890 | 2.99935e+06 | 13665.8 | 7.13348 | 3(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4113.35 | 0.141831 | 115.81ms | 4669 | 640 | 1508.61 | 1082.5 | 0.546933 | 1(Win) |
| glaze | 1262.08 | 0.266808 | 358.271ms | 4669 | 4890 | 433294 | 3528.08 | 1.82185 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 868.463 | 0.505847 | 1025.35ms | 9249 | 1280 | 3.37858e+06 | 10156.5 | 2.67457 | 1(Win) |
| simdjson (ondemand) | 619.71 | 0.113404 | 1451.48ms | 9249 | 30 | 7816.09 | 14233.3 | 3.75195 | 2(Loss) |
| glaze | 568.975 | 0.0848236 | 913.248ms | 9249 | 40 | 6916.67 | 15502.5 | 4.084 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6485.98 | 0.438936 | 141.618ms | 9249 | 4890 | 174241 | 1359.94 | 0.347226 | 1(Win) |
| glaze | 1333.31 | 0.231639 | 669.882ms | 9249 | 4890 | 1.1483e+06 | 6615.5 | 1.73627 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 238.712 | 0.0937454 | 1919.46ms | 4604 | 30 | 8919.54 | 18393.3 | 9.74643 | 1(Win) |
| glaze | 153.861 | 0.154477 | 2871.38ms | 4604 | 4890 | 9.50271e+06 | 28536.9 | 15.1332 | 2(Loss) |
| simdjson (ondemand) | 40.7557 | 0.161465 | 5537.38ms | 4604 | 2560 | 7.74624e+07 | 107732 | 57.1924 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 597.919 | 0.125309 | 753.09ms | 4604 | 30 | 2540.23 | 7343.33 | 3.87526 | 1(Win) |
| glaze | 353.202 | 0.181061 | 1249.62ms | 4604 | 4890 | 2.47732e+06 | 12431.2 | 6.57594 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 871.303 | 0.468055 | 2697.84ms | 24579 | 1280 | 2.02952e+07 | 26902.7 | 2.67085 | 1(Win) |
| glaze | 670.905 | 0.147617 | 3508.19ms | 24579 | 4890 | 1.30073e+07 | 34938.4 | 3.47084 | 2(Loss) |
| simdjson (ondemand) | 209.322 | 0.150933 | 5735.28ms | 24579 | 2560 | 7.31318e+07 | 111982 | 11.136 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2903.73 | 0.108534 | 827.341ms | 24579 | 40 | 3070.51 | 8072.5 | 0.798701 | 1(Win) |
| glaze | 1268.41 | 0.15167 | 1854.85ms | 24579 | 4890 | 3.84164e+06 | 18480.1 | 1.83347 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 261.684 | 0.24138 | 1684.48ms | 4604 | 4890 | 8.02095e+06 | 16778.7 | 8.88998 | 1(Win) |
| glaze | 154.423 | 0.153043 | 2856.51ms | 4604 | 4890 | 9.25939e+06 | 28433.1 | 15.0792 | 2(Loss) |
| simdjson (ondemand) | 133.675 | 0.297613 | 3299.1ms | 4604 | 1280 | 1.22317e+07 | 32846.2 | 17.424 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 606.732 | 0.140287 | 742.778ms | 4604 | 30 | 3091.95 | 7236.67 | 3.82912 | 1(Win) |
| glaze | 366.18 | 0.228435 | 1205.5ms | 4604 | 2560 | 1.92063e+06 | 11990.6 | 6.34131 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 981.898 | 0.0948455 | 2474.57ms | 24579 | 40 | 20506.4 | 23872.5 | 2.37008 | 1(Win) |
| glaze | 676.392 | 0.0730221 | 3605.35ms | 24579 | 40 | 25615.4 | 34655 | 3.44335 | 2(Loss) |
| simdjson (ondemand) | 638.629 | 0.238525 | 3818.81ms | 24579 | 2560 | 1.96217e+07 | 36704.2 | 3.64725 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2877.7 | 0.224241 | 836.387ms | 24579 | 4890 | 1.63147e+06 | 8145.52 | 0.806437 | 1(Win) |
| glaze | 1290.7 | 0.193024 | 1823.42ms | 24579 | 4890 | 6.00915e+06 | 18161 | 1.80201 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 335.081 | 0.120847 | 348.52ms | 1181 | 160 | 2639.94 | 3361.25 | 6.89817 | 1(Win) |
| glaze | 190.998 | 0.475723 | 595.667ms | 1181 | 1280 | 1.00731e+06 | 5896.88 | 12.13 | 2(Loss) |
| simdjson (ondemand) | 177.902 | 0.325225 | 639.336ms | 1181 | 2560 | 1.08529e+06 | 6330.94 | 13.0247 | 3(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 749.143 | 0.125984 | 158.092ms | 1181 | 320 | 1148.02 | 1503.44 | 3.03761 | 1(Win) |
| glaze | 512.793 | 0.341847 | 224.109ms | 1181 | 4890 | 275669 | 2196.38 | 4.45787 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 516.21 | 0.25877 | 474.92ms | 2496 | 80 | 11390.8 | 4611.25 | 4.47178 | 1(Win) |
| glaze STATISTICAL TIE | 373.135 | 0.0667967 | 654.736ms | 2496 | 160 | 2905.27 | 6379.38 | 6.21077 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 371.739 | 0.190655 | 661.889ms | 2496 | 30 | 4471.26 | 6403.33 | 6.23528 | 2(Tie) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1507.6 | 0.331145 | 163.455ms | 2496 | 4890 | 133679 | 1578.92 | 1.5068 | 1(Win) |
| glaze | 755.192 | 0.38628 | 322.8ms | 2507 | 2560 | 382858 | 3165.9 | 3.04771 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 512.464 | 0.20491 | 923.701ms | 4926 | 4890 | 1.72543e+06 | 9167.08 | 4.5314 | 1(Win) |
| glaze | 421.173 | 0.289618 | 1117.45ms | 4926 | 4890 | 5.10302e+06 | 11154.1 | 5.51659 | 2(Loss) |
| simdjson (ondemand) | 256.05 | 0.219234 | 1855.48ms | 4926 | 2560 | 4.14184e+06 | 18347.2 | 9.08667 | 3(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2506.33 | 0.167806 | 196.073ms | 4926 | 320 | 3165.75 | 1874.38 | 0.911058 | 1(Win) |
| glaze | 1000.64 | 0.295256 | 475.87ms | 4926 | 4890 | 939586 | 4694.79 | 2.30891 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 750.157 | 0.267685 | 1206.88ms | 9463 | 4890 | 5.07119e+06 | 12030.3 | 3.09698 | 1(Win) |
| glaze | 717.378 | 0.167871 | 1305.14ms | 9463 | 30 | 13379.3 | 12580 | 3.23956 | 2(Loss) |
| simdjson (ondemand) | 482.987 | 0.137586 | 1916.75ms | 9463 | 40 | 26435.9 | 18685 | 4.81696 | 3(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4540.69 | 0.146269 | 207.398ms | 9463 | 160 | 1352.2 | 1987.5 | 0.503584 | 1(Win) |
| glaze | 1120.86 | 0.264762 | 813.053ms | 9463 | 2560 | 1.16334e+06 | 8051.48 | 2.07057 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1834.83 | 0.382581 | 155.062ms | 2821 | 80 | 2517.41 | 1466.25 | 1.23945 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1438.19 | 0.142356 | 194.906ms | 2821 | 320 | 2269.2 | 1870.62 | 1.58534 | 2(Tie) |
| glaze STATISTICAL TIE | 1425.96 | 0.420152 | 198.098ms | 2821 | 30 | 1885.06 | 1886.67 | 1.60958 | 2(Tie) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2491.27 | 0.402684 | 167.684ms | 4147 | 40 | 1634.62 | 1587.5 | 0.91527 | 1(Win) |
| simdjson (ondemand) | 1892.29 | 0.286672 | 217.914ms | 4147 | 40 | 1435.9 | 2090 | 1.20963 | 2(Loss) |
| glaze | 1616.17 | 0.409205 | 248.052ms | 4147 | 2560 | 256693 | 2447.07 | 1.42047 | 3(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 834.431 | 0.342025 | 327.383ms | 2821 | 4890 | 594635 | 3224.13 | 2.758 | 1(Win) |
| jsonifier | 746.662 | 0.124074 | 373.85ms | 2821 | 160 | 3197.72 | 3603.12 | 3.08936 | 2(Loss) |
| simdjson (ondemand) | 498.437 | 0.13173 | 556.407ms | 2821 | 80 | 4044.3 | 5397.5 | 4.64564 | 3(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3311.16 | 0.651783 | 87.0228ms | 2821 | 40 | 1121.79 | 812.5 | 0.665066 | 1(Win) |
| glaze | 1575.88 | 0.447898 | 175.35ms | 2819 | 4890 | 285503 | 1705.97 | 1.44024 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1055.34 | 0.213379 | 401.074ms | 4147 | 40 | 2557.69 | 3747.5 | 2.18606 | 1(Win) |
| jsonifier | 736.114 | 0.66195 | 546.064ms | 4147 | 1280 | 1.61897e+06 | 5372.66 | 3.13981 | 2(Loss) |
| simdjson (ondemand) | 687.33 | 0.270028 | 580.625ms | 4147 | 4890 | 1.1805e+06 | 5753.99 | 3.36979 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3717.87 | 0.535237 | 98.2346ms | 4147 | 80 | 2593.35 | 1063.75 | 0.606517 | 1(Win) |
| glaze | 1388.08 | 0.375065 | 289.715ms | 4145 | 4890 | 557885 | 2847.81 | 1.65264 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1228.6 | 0.204494 | 9026.31ms | 466906 | 320 | 1.75773e+08 | 362427 | 1.89782 | 1(Win) |
| glaze | 829.718 | 0.248015 | 6806.14ms | 466906 | 80 | 1.41724e+08 | 536660 | 2.81033 | 2(Loss) |
| simdjson (ondemand) | 535.643 | 0.182369 | 5255.6ms | 466906 | 160 | 3.67732e+08 | 831293 | 4.35351 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1183.6 | 0.369666 | 7167.19ms | 699405 | 640 | 2.77744e+09 | 563538 | 1.96952 | 1(Win) |
| glaze | 1044.18 | 0.19494 | 8139.35ms | 699405 | 160 | 2.48102e+08 | 638784 | 2.23321 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1353.01 | 0.112035 | 5652.92ms | 631514 | 640 | 1.59166e+08 | 445123 | 1.72342 | 1(Win) |
| jsonifier | 1190.74 | 0.109069 | 6458.78ms | 631514 | 320 | 9.73837e+07 | 505787 | 1.95832 | 2(Loss) |
