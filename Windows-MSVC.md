# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [b7aa5cd](https://github.com/nihilai-collective/jsonifier/commit/b7aa5cd)  
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

`simdjson (ondemand)` extracts each field with an individual `find_field` lookup (`find_field_unordered` for the reverse-order tests) on MSVC/Windows, rather than the `object::for_each` API used on the other platforms, because instantiating `for_each` across these test structures drives MSVC compile times to intractable levels.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 509.518 | 0.22849 | 179.301ms | 905 | 640 | 9587.22 | 1693.91 | 5.90976 | 1(Win) |
| jsonifier | 498.078 | 0.492198 | 181.43ms | 905 | 320 | 23277.3 | 1732.81 | 6.04177 | 2(Loss) |
| simdjson (ondemand) | 124.868 | 0.212486 | 702.857ms | 905 | 160 | 34512.2 | 6911.88 | 24.2737 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1177.63 | 0.213442 | 77.4488ms | 905 | 2560 | 6264.4 | 732.891 | 2.51962 | 1(Win) |
| glaze | 86.7113 | 0.630857 | 1046.31ms | 905 | 1280 | 5.04682e+06 | 9953.44 | 34.9739 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 577.476 | 0.305477 | 308.693ms | 1811 | 640 | 53420.4 | 2990.78 | 5.23081 | 1(Win) |
| glaze | 439.187 | 0.190718 | 390.411ms | 1811 | 40 | 2250 | 3932.5 | 6.89978 | 2(Loss) |
| simdjson (ondemand) | 171.638 | 0.232453 | 1039.99ms | 1811 | 320 | 175078 | 10062.5 | 17.677 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 201.804 | 0.29737 | 865.528ms | 1811 | 4890 | 3.16723e+06 | 8558.32 | 15.0252 | 1(Win) |
| glaze | 136.371 | 0.629441 | 1256.36ms | 1798 | 4890 | 3.06306e+07 | 12573.8 | 22.2487 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1761.72 | 0.0960807 | 216.326ms | 3862 | 320 | 1291.14 | 2090.62 | 1.70995 | 1(Win) |
| glaze | 1109.78 | 0.305707 | 344.654ms | 3862 | 320 | 32938.9 | 3318.75 | 2.72373 | 2(Loss) |
| simdjson (ondemand) | 400.772 | 0.0799786 | 955.135ms | 3862 | 30 | 1620.69 | 9190 | 7.5675 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 483.821 | 0.206032 | 796.483ms | 3862 | 40 | 9839.74 | 7612.5 | 6.25665 | 1(Win) |
| glaze | 381.009 | 0.181112 | 1029.43ms | 3862 | 30 | 9195.4 | 9666.67 | 7.95689 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 922.856 | 0.562497 | 990.472ms | 9578 | 4890 | 1.51576e+07 | 9897.85 | 3.2861 | 1(Win) |
| glaze | 800.267 | 0.155549 | 1169.81ms | 9578 | 640 | 201742 | 11414.1 | 3.78952 | 2(Loss) |
| simdjson (ondemand) | 618.861 | 0.472561 | 1480.67ms | 9578 | 1280 | 6.22714e+06 | 14759.8 | 4.90323 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1161.89 | 0.281172 | 796.064ms | 9578 | 2560 | 1.25084e+06 | 7861.56 | 2.60759 | 1(Win) |
| glaze | 862.105 | 0.561414 | 1052.19ms | 9578 | 4890 | 1.73024e+07 | 10595.3 | 3.51788 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2224.21 | 0.233328 | 175.221ms | 3873 | 160 | 2402.12 | 1660.62 | 1.3499 | 1(Win) |
| glaze | 1101.74 | 0.23852 | 343.959ms | 3873 | 40 | 2557.69 | 3352.5 | 2.74154 | 2(Loss) |
| simdjson (ondemand) | 401.913 | 0.183347 | 948.363ms | 3873 | 30 | 8517.24 | 9190 | 7.55916 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 478.095 | 0.338704 | 776.773ms | 3873 | 2560 | 1.75286e+06 | 7725.62 | 6.33935 | 1(Win) |
| glaze | 372.101 | 0.444941 | 997.347ms | 3873 | 4890 | 9.53864e+06 | 9926.28 | 8.11949 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 560.19 | 0.674509 | 5335.27ms | 2090234 | 80 | 4.60877e+10 | 3.55844e+06 | 5.42514 | 1(Win) |
| glaze | 364.037 | 0.59221 | 8304.4ms | 2090234 | 80 | 8.41281e+10 | 5.47583e+06 | 8.3485 | 2(Loss) |
| simdjson (ondemand) | 341.809 | 0.552032 | 8765.19ms | 2090234 | 80 | 8.29165e+10 | 5.83191e+06 | 8.89142 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1197.31 | 0.245341 | 5179.62ms | 2090234 | 160 | 2.66954e+09 | 1.6649e+06 | 2.53795 | 1(Win) |
| glaze | 810.913 | 0.379617 | 7619.94ms | 2090234 | 80 | 6.96661e+09 | 2.45822e+06 | 3.7475 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1207.99 | 0.893571 | 7827.98ms | 6661897 | 30 | 6.62601e+10 | 5.2594e+06 | 2.51591 | 1(Win) |
| simdjson (ondemand) | 1066.42 | 0.353783 | 8970.86ms | 6661897 | 30 | 1.33272e+10 | 5.95759e+06 | 2.84991 | 2(Loss) |
| glaze | 1008.57 | 0.719215 | 9429.39ms | 6661897 | 30 | 6.15778e+10 | 6.29931e+06 | 3.01339 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2718.12 | 0.245198 | 7526.04ms | 6661897 | 30 | 9.85404e+08 | 2.33738e+06 | 1.11802 | 1(Win) |
| glaze | 1511.37 | 0.275346 | 6488.47ms | 6661897 | 40 | 5.3589e+09 | 4.20367e+06 | 2.01084 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 862.543 | 0.252093 | 7148.04ms | 500299 | 40 | 7.7782e+07 | 553158 | 3.52333 | 1(Win) |
| jsonifier | 690.59 | 0.441657 | 8949.97ms | 500299 | 80 | 7.44867e+08 | 690891 | 4.40073 | 2(Loss) |
| simdjson (ondemand) | 494.816 | 0.34135 | 6085.57ms | 500299 | 320 | 3.46675e+09 | 964242 | 6.14139 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9623.63 | 0.291004 | 5020.03ms | 500299 | 1280 | 2.66435e+07 | 49578.2 | 0.315633 | 1(Win) |
| glaze | 4470.5 | 0.872294 | 5410ms | 500299 | 640 | 5.54694e+08 | 106727 | 0.679551 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1865.04 | 0.782443 | 9300.49ms | 1439562 | 80 | 2.65386e+09 | 736108 | 1.62927 | 1(Win) |
| jsonifier | 1582.7 | 0.351817 | 5462.99ms | 1439562 | 320 | 2.98022e+09 | 867427 | 1.91999 | 2(Loss) |
| simdjson (ondemand) | 1359.9 | 0.296822 | 6411.43ms | 1439562 | 160 | 1.43667e+09 | 1.00954e+06 | 2.23463 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4428.63 | 0.272652 | 7922.53ms | 1439562 | 1280 | 9.14423e+08 | 309999 | 0.685722 | 1(Win) |
| glaze | 1886.97 | 0.304555 | 9256.95ms | 1439584 | 640 | 3.14236e+09 | 727565 | 1.60996 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1209.71 | 0.34622 | 4485.2ms | 56369 | 2560 | 6.05989e+07 | 44438.6 | 2.51091 | 1(Win) |
| jsonifier | 783.313 | 0.336211 | 6892.8ms | 56369 | 2560 | 1.36293e+08 | 68628.6 | 3.87843 | 2(Loss) |
| simdjson (ondemand) | 621.168 | 0.332333 | 8857.59ms | 56369 | 320 | 2.64704e+07 | 86542.8 | 4.89113 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8111 | 0.340388 | 666.691ms | 56369 | 4890 | 2.4888e+06 | 6627.75 | 0.373171 | 1(Win) |
| glaze | 4368.44 | 0.583637 | 1222.78ms | 56369 | 4890 | 2.52244e+07 | 12305.9 | 0.694141 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1785.1 | 0.749926 | 5163.28ms | 94370 | 160 | 2.28717e+07 | 50416.2 | 1.7015 | 1(Win) |
| jsonifier | 1107.97 | 0.743808 | 8114.51ms | 94370 | 1280 | 4.67243e+08 | 81227.9 | 2.74192 | 2(Loss) |
| simdjson (ondemand) | 970.734 | 0.217057 | 9264.07ms | 94370 | 4890 | 1.98026e+08 | 92711.5 | 3.12989 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12307.5 | 0.0874202 | 761.32ms | 94370 | 40 | 1634.62 | 7312.5 | 0.245809 | 1(Win) |
| glaze | 4218.38 | 0.426918 | 2172.21ms | 94370 | 1280 | 1.06188e+07 | 21334.8 | 0.719488 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1018.21 | 0.17053 | 1159.82ms | 11812 | 30 | 10678.2 | 11063.3 | 2.97771 | 1(Win) |
| jsonifier | 748.554 | 0.226765 | 1543.41ms | 11812 | 80 | 93163 | 15048.8 | 4.05443 | 2(Loss) |
| simdjson (ondemand) | 501.04 | 0.388415 | 2245.64ms | 11812 | 4890 | 3.72909e+07 | 22482.8 | 6.05918 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6432.43 | 0.226354 | 177.889ms | 11812 | 160 | 2514.15 | 1751.25 | 0.467107 | 1(Win) |
| glaze | 3405.59 | 0.193135 | 340.92ms | 11812 | 1280 | 52238.8 | 3307.73 | 0.886618 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1872.87 | 0.298015 | 1623.73ms | 31235 | 160 | 359472 | 15905 | 1.62053 | 1(Win) |
| jsonifier | 1551.88 | 0.426303 | 1932.33ms | 31235 | 4890 | 3.27427e+07 | 19194.8 | 1.9561 | 2(Loss) |
| simdjson (ondemand) | 1248.15 | 0.412146 | 2391.1ms | 31235 | 4890 | 4.73107e+07 | 23865.7 | 2.43244 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13016.7 | 0.229643 | 237.038ms | 31235 | 640 | 17675.2 | 2288.44 | 0.231207 | 1(Win) |
| glaze | 5541.96 | 0.149849 | 561.842ms | 31235 | 80 | 5189.87 | 5375 | 0.545504 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1397.54 | 0.53056 | 7299.87ms | 108313 | 2560 | 3.93679e+08 | 73912.3 | 2.17371 | 1(Win) |
| jsonifier | 707.866 | 0.309101 | 7662.33ms | 108313 | 80 | 1.62761e+07 | 145925 | 4.29266 | 2(Loss) |
| simdjson (ondemand) | 682.755 | 0.215274 | 7834.54ms | 108313 | 1280 | 1.35776e+08 | 151292 | 4.45056 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12071.9 | 0.133583 | 901.547ms | 108313 | 30 | 3919.54 | 8556.67 | 0.250873 | 1(Win) |
| glaze | 4261.53 | 0.374771 | 2468.47ms | 108313 | 2560 | 2.11253e+07 | 24239 | 0.712381 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2149.29 | 0.271741 | 9506.81ms | 213963 | 2560 | 1.70389e+08 | 94939 | 1.41359 | 1(Win) |
| simdjson (ondemand) | 1256.29 | 0.225157 | 8297.27ms | 213963 | 2560 | 3.42382e+08 | 162424 | 2.4188 | 2(Loss) |
| jsonifier | 1143.84 | 0.196774 | 9112.34ms | 213963 | 2560 | 3.15445e+08 | 178391 | 2.65663 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 17104 | 0.12157 | 1236.04ms | 213963 | 30 | 6310.34 | 11930 | 0.177389 | 1(Win) |
| glaze | 4553.11 | 0.339356 | 4504.52ms | 213963 | 4890 | 1.13104e+08 | 44815.7 | 0.66706 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 357.325 | 0.329054 | 7384.91ms | 1834197 | 30 | 7.78433e+09 | 4.89534e+06 | 8.50527 | 1(Win) |
| glaze | 302.318 | 0.646305 | 8653.24ms | 1834197 | 30 | 4.19527e+10 | 5.78604e+06 | 10.053 | 2(Loss) |
| simdjson (ondemand) | 36.0963 | 0.20652 | 14451.4ms | 1834197 | 30 | 3.00477e+11 | 4.846e+07 | 84.2013 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 797.232 | 0.230405 | 6822.88ms | 1834197 | 160 | 4.0891e+09 | 2.19413e+06 | 3.81179 | 1(Win) |
| glaze | 690.688 | 0.194405 | 7973.89ms | 1833577 | 30 | 7.26728e+08 | 2.53173e+06 | 4.39986 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1491.82 | 0.298854 | 9554.65ms | 9930848 | 80 | 2.8797e+10 | 6.34848e+06 | 2.03723 | 1(Win) |
| glaze | 1382.88 | 0.381503 | 10363.4ms | 9930848 | 30 | 2.04794e+10 | 6.84858e+06 | 2.19775 | 2(Loss) |
| simdjson (ondemand) | 190.484 | 0.208648 | 14838.3ms | 9930848 | 30 | 3.22853e+11 | 4.97197e+07 | 15.956 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2704.43 | 0.515364 | 5284.66ms | 9930848 | 30 | 9.7717e+09 | 3.50195e+06 | 1.12374 | 1(Win) |
| glaze | 1795.35 | 0.379549 | 7892.42ms | 9930228 | 80 | 3.20661e+10 | 5.27485e+06 | 1.6928 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 355.328 | 0.465978 | 7367.34ms | 1834197 | 40 | 2.10487e+10 | 4.92285e+06 | 8.55301 | 1(Win) |
| glaze | 300.876 | 0.49416 | 8821.99ms | 1834197 | 30 | 2.47613e+10 | 5.81378e+06 | 10.1011 | 2(Loss) |
| simdjson (ondemand) | 251.748 | 0.371188 | 10500.1ms | 1834197 | 30 | 1.99559e+10 | 6.94833e+06 | 12.0725 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 778.375 | 0.295152 | 6976.96ms | 1834197 | 160 | 7.03926e+09 | 2.24728e+06 | 3.90415 | 1(Win) |
| glaze | 595.871 | 0.331543 | 9153.6ms | 1833577 | 80 | 7.57294e+09 | 2.93459e+06 | 5.10012 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1498.6 | 0.404286 | 9507.91ms | 9930848 | 40 | 2.6112e+10 | 6.31977e+06 | 2.02803 | 1(Win) |
| glaze | 1340.96 | 0.33069 | 10615ms | 9930848 | 80 | 4.36386e+10 | 7.06267e+06 | 2.26644 | 2(Loss) |
| simdjson (ondemand) | 1237.88 | 0.423993 | 5373.32ms | 9930848 | 40 | 4.20911e+10 | 7.6508e+06 | 2.45516 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2636.64 | 0.623702 | 5386.6ms | 9930848 | 40 | 2.00764e+10 | 3.592e+06 | 1.15264 | 1(Win) |
| glaze | 1226.98 | 0.460737 | 5335.96ms | 9930228 | 40 | 5.05837e+10 | 7.7183e+06 | 2.47699 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 663.239 | 0.581754 | 5938.88ms | 642697 | 40 | 1.15614e+09 | 924138 | 4.58184 | 1(Win) |
| jsonifier | 493.826 | 0.170286 | 7869.32ms | 642697 | 320 | 1.42946e+09 | 1.24117e+06 | 6.15406 | 2(Loss) |
| simdjson (ondemand) | 409.356 | 0.220305 | 9394.75ms | 642697 | 320 | 3.48185e+09 | 1.49729e+06 | 7.42369 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1263.8 | 0.271439 | 6155.42ms | 642697 | 640 | 1.10913e+09 | 484985 | 2.40402 | 1(Win) |
| glaze | 918.832 | 0.305532 | 8477.65ms | 642692 | 320 | 1.32922e+09 | 667063 | 3.30615 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1139.9 | 0.283395 | 6462.6ms | 1225964 | 320 | 2.7037e+09 | 1.02568e+06 | 2.66589 | 1(Win) |
| simdjson (ondemand) | 768.064 | 0.232774 | 9607.86ms | 1225964 | 160 | 2.00886e+09 | 1.52223e+06 | 3.95666 | 2(Loss) |
| jsonifier | 724.339 | 0.512757 | 10131ms | 1225964 | 80 | 5.48006e+09 | 1.61412e+06 | 4.19546 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2092.27 | 0.249642 | 7181.14ms | 1225964 | 80 | 1.55683e+08 | 558804 | 1.4518 | 1(Win) |
| glaze | 1479.44 | 0.43027 | 5010.66ms | 1225970 | 160 | 1.84997e+09 | 790281 | 2.05348 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 769.293 | 0.614355 | 6479.64ms | 409725 | 30 | 2.92121e+08 | 507927 | 3.94991 | 1(Win) |
| jsonifier | 696.756 | 0.153265 | 7119.29ms | 409725 | 640 | 4.72814e+08 | 560805 | 4.36167 | 2(Loss) |
| simdjson (ondemand) | 519.886 | 0.153262 | 9540.77ms | 409725 | 640 | 8.49213e+08 | 751596 | 5.84513 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2875.66 | 0.200535 | 6995.93ms | 409725 | 1280 | 9.50385e+07 | 135880 | 1.05646 | 1(Win) |
| jsonifier | 2822.48 | 0.271407 | 7125.08ms | 409725 | 1280 | 1.80708e+08 | 138440 | 1.07595 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1307.26 | 0.272243 | 7289.15ms | 785750 | 640 | 1.55861e+09 | 573220 | 2.32448 | 1(Win) |
| jsonifier | 1146.69 | 0.225679 | 8308.19ms | 785750 | 640 | 1.392e+09 | 653488 | 2.65011 | 2(Loss) |
| simdjson (ondemand) | 953.792 | 0.266341 | 10029.9ms | 785750 | 320 | 1.40116e+09 | 785653 | 3.18598 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3887.05 | 0.311296 | 9924.19ms | 785750 | 320 | 1.15246e+08 | 192781 | 0.781298 | 1(Win) |
| glaze | 2200.09 | 0.393498 | 8622.27ms | 785750 | 640 | 1.14962e+09 | 340600 | 1.38017 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3702.83 | 0.249675 | 6805.01ms | 264040 | 2560 | 7.3801e+07 | 68004.3 | 0.820471 | 1(Win) |
| glaze | 2520.61 | 0.38823 | 5139.33ms | 264040 | 2560 | 3.85075e+08 | 99899.5 | 1.20543 | 2(Loss) |
| simdjson (ondemand) | 1894.85 | 0.23002 | 6777.01ms | 264040 | 2560 | 2.392e+08 | 132891 | 1.60361 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5081.55 | 0.335301 | 7622.22ms | 399947 | 320 | 2.0269e+07 | 75059.7 | 0.597869 | 1(Win) |
| glaze | 3287.06 | 0.313491 | 5999.6ms | 399947 | 1280 | 1.69375e+08 | 116037 | 0.924387 | 2(Loss) |
| simdjson (ondemand) | 2664.5 | 0.281895 | 7374.26ms | 399947 | 1280 | 2.08429e+08 | 143148 | 1.14043 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1124.9 | 0.72729 | 5672.24ms | 264040 | 640 | 1.69631e+09 | 223849 | 2.70127 | 1(Win) |
| jsonifier | 1064.12 | 0.365085 | 6107.27ms | 264040 | 1280 | 9.55344e+08 | 236636 | 2.85564 | 2(Loss) |
| simdjson (ondemand) | 764.656 | 0.330134 | 8407.52ms | 264040 | 1280 | 1.51286e+09 | 329309 | 3.97388 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9167.89 | 0.407296 | 2752.52ms | 264040 | 4890 | 6.1197e+07 | 27466.3 | 0.331142 | 1(Win) |
| glaze | 4156.13 | 0.289324 | 6039.53ms | 263923 | 4890 | 1.50125e+08 | 60560.3 | 0.730912 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1561.07 | 0.349719 | 6231.77ms | 399947 | 1280 | 9.34561e+08 | 244332 | 1.94661 | 1(Win) |
| jsonifier | 1405.57 | 0.282243 | 7151.14ms | 399947 | 30 | 1.75983e+07 | 271363 | 2.16204 | 2(Loss) |
| simdjson (ondemand) | 1145.5 | 0.325285 | 8570.17ms | 399947 | 640 | 7.50803e+08 | 332973 | 2.65291 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12062.2 | 0.405988 | 3154.78ms | 399947 | 4890 | 8.05914e+07 | 31621.1 | 0.251738 | 1(Win) |
| glaze | 3684.97 | 0.502572 | 5254.59ms | 399830 | 1280 | 3.4617e+08 | 103476 | 0.824513 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2716.97 | 0.247006 | 8412.23ms | 466906 | 2560 | 4.19511e+08 | 163887 | 1.11842 | 1(Win) |
| glaze | 1923.55 | 0.716817 | 6014.93ms | 466906 | 30 | 8.26019e+07 | 231487 | 1.57979 | 2(Loss) |
| simdjson (ondemand) | 1100.61 | 0.576541 | 5085.92ms | 466906 | 320 | 1.74103e+09 | 404573 | 2.76074 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2399.29 | 0.873813 | 7116.97ms | 699405 | 640 | 3.77668e+09 | 278001 | 1.26658 | 1(Win) |
| jsonifier | 2210.38 | 0.649916 | 7672.59ms | 699405 | 320 | 1.2308e+09 | 301761 | 1.37436 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3191.01 | 0.632242 | 9823.58ms | 631514 | 160 | 2.27823e+08 | 188736 | 0.952307 | 1(Win) |
| glaze | 2238.98 | 0.470199 | 6705.8ms | 631514 | 640 | 1.02379e+09 | 268988 | 1.35718 | 2(Loss) |
