# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Oct 10, 2026)
#### Using the following commits:
----
| Jsonifier: [13785b6](https://github.com/nihilai-collective/jsonifier/commit/13785b6)  
| Glaze: [e194d23](https://github.com/stephenberry/glaze/commit/e194d23)  
| Simdjson: [7f6f8dc](https://github.com/simdjson/simdjson/commit/7f6f8dc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX2` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" performs fused scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through structural indexing/stage-1 + stage-2. The 'partial' tests require stage-1 + stage-2, so both jsonifier rows take the two-stage path there)

Each test is run twice. In the standard run, every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. In the run labelled "(Reused)", the object or string is created once and held across iterations; it is cleared (keeping its capacity) outside the timed region before each iteration, so only the parse or serialize work is measured. Parser instances are reused in both.

The "Small" tests use cut-down copies of the large documents, truncated by `GenerateSmallJson.py` so that each minified document is at most 5 KiB (arrays and numerically-keyed objects are shortened to as many leading entries as fit; the document structure is otherwise unchanged). They exercise per-call overhead (setup, dispatch, small allocations) rather than bulk throughput, which is where the standard and "(Reused)" runs differ most.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

`simdjson (ondemand)` extracts each field with an individual `find_field` lookup (`find_field_unordered` for the reverse-order tests) on MSVC/Windows, rather than the `object::for_each` API used on the other platforms, because instantiating `for_each` across these test structures drives MSVC compile times to intractable levels.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [6196208](https://github.com/nihilai-collective/benchmarksuite/commit/6196208).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 468.545 | 0.440612 | 182.654ms | 905 | 640 | 42158.6 | 1842.03 | 6.42937 | 1(Win) |
| glaze | 452.662 | 0.24294 | 194.883ms | 905 | 30 | 643.678 | 1906.67 | 6.61315 | 2(Loss) |
| jsonifier (two-stage) | 131.544 | 0.230261 | 679.064ms | 905 | 640 | 146074 | 6561.09 | 23.0424 | 3(Loss) |
| simdjson (ondemand) | 119.084 | 0.409013 | 727.474ms | 905 | 4890 | 4.29704e+06 | 7247.59 | 25.4261 | 4(Loss) |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 590.011 | 1.46453 | 149.343ms | 905 | 1280 | 587467 | 1462.81 | 5.08942 | 1(Win) |
| glaze | 521.594 | 0.325258 | 174.903ms | 905 | 640 | 18538.2 | 1654.69 | 5.76256 | 2(Loss) |
| jsonifier (two-stage) | 137.118 | 0.223726 | 647.755ms | 905 | 160 | 31729.2 | 6294.38 | 22.1049 | 3(Loss) |
| simdjson (ondemand) | 129.409 | 0.351249 | 693.243ms | 905 | 320 | 175611 | 6669.38 | 23.4205 | 4(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1075.9 | 0.116461 | 84.7855ms | 905 | 640 | 558.588 | 802.188 | 2.76029 | 1(Win) |
| glaze | 80.21 | 0.89677 | 1136.55ms | 905 | 2560 | 2.38365e+07 | 10760.2 | 37.8083 | 2(Loss) |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1554.2 | 0.212741 | 64.3494ms | 905 | 4890 | 6824.86 | 555.317 | 1.89229 | 1(Win) |
| glaze | 249.204 | 0.25838 | 339.83ms | 905 | 30 | 2402.3 | 3463.33 | 12.0644 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 513.138 | 0.260108 | 340.967ms | 1811 | 4890 | 374786 | 3365.77 | 5.88029 | 1(Win) |
| glaze | 420.22 | 0.0928311 | 403.421ms | 1811 | 80 | 1164.56 | 4110 | 7.19371 | 2(Loss) |
| jsonifier (two-stage) | 295.168 | 0.205502 | 604.855ms | 1811 | 320 | 46268 | 5851.25 | 10.258 | 3(Loss) |
| simdjson (ondemand) | 164.689 | 0.366626 | 1063.69ms | 1811 | 4890 | 7.22879e+06 | 10487.1 | 18.4194 | 4(Loss) |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 687.177 | 0.251158 | 263.559ms | 1811 | 30 | 1195.4 | 2513.33 | 4.37719 | 1(Win) |
| glaze | 547.228 | 0.237492 | 329.253ms | 1811 | 640 | 35956.5 | 3156.09 | 5.47268 | 2(Loss) |
| jsonifier (two-stage) | 329.728 | 0.258441 | 533.538ms | 1811 | 2560 | 469124 | 5237.97 | 9.17524 | 3(Loss) |
| simdjson (ondemand) | 179.346 | 0.256354 | 997.172ms | 1811 | 320 | 195022 | 9630 | 16.901 | 4(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 189.844 | 0.55433 | 925.724ms | 1811 | 160 | 406912 | 9097.5 | 15.9731 | 1(Win) |
| glaze | 125.575 | 1.17977 | 1363.51ms | 1798 | 2560 | 6.64366e+07 | 13654.9 | 24.1587 | 2(Loss) |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 722.638 | 0.200998 | 257.07ms | 1811 | 40 | 923.077 | 2390 | 4.14088 | 1(Win) |
| glaze | 322.219 | 0.188404 | 567.68ms | 1798 | 320 | 32166.8 | 5321.56 | 9.38305 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1489.12 | 0.510439 | 260.66ms | 3862 | 30 | 4781.61 | 2473.33 | 2.02874 | 1(Win) |
| glaze | 1045.22 | 0.63906 | 363.448ms | 3862 | 80 | 40568 | 3523.75 | 2.88806 | 2(Loss) |
| jsonifier (two-stage) | 540.08 | 0.286575 | 695.91ms | 3862 | 4890 | 1.86764e+06 | 6819.53 | 5.61209 | 3(Loss) |
| simdjson (ondemand) | 374.425 | 0.388362 | 1043.12ms | 3862 | 30 | 43781.6 | 9836.67 | 8.09943 | 4(Loss) |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1986.83 | 0.302608 | 195.646ms | 3862 | 80 | 2517.41 | 1853.75 | 1.50473 | 1(Win) |
| glaze | 1316.96 | 0.11919 | 300.176ms | 3862 | 30 | 333.333 | 2796.67 | 2.2807 | 2(Loss) |
| jsonifier (two-stage) | 607.457 | 0.204535 | 632.862ms | 3862 | 160 | 24606.5 | 6063.12 | 4.98179 | 3(Loss) |
| simdjson (ondemand) | 399.757 | 0.068514 | 957.359ms | 3862 | 30 | 1195.4 | 9213.33 | 7.59445 | 4(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 505.702 | 0.255866 | 747.288ms | 3862 | 320 | 111125 | 7283.12 | 5.99306 | 1(Win) |
| glaze | 327.184 | 1.32912 | 1148.97ms | 3862 | 1280 | 2.86537e+07 | 11257 | 9.26998 | 2(Loss) |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4120.94 | 0.414833 | 109.16ms | 3862 | 80 | 1099.68 | 893.75 | 0.718407 | 1(Win) |
| glaze | 1120.62 | 0.28187 | 368.954ms | 3862 | 30 | 2574.71 | 3286.67 | 2.68528 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 818.33 | 1.87025 | 1120.26ms | 9578 | 1280 | 5.57832e+07 | 11162.1 | 3.70534 | 1(Win) |
| glaze | 684.828 | 0.681961 | 1357.18ms | 9578 | 2560 | 2.1181e+07 | 13338.1 | 4.42924 | 2(Loss) |
| jsonifier (two-stage) STATISTICAL TIE | 628.25 | 0.695781 | 1446.3ms | 9578 | 4890 | 5.00424e+07 | 14539.3 | 4.82988 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 619.904 | 0.0667692 | 1542.69ms | 9578 | 40 | 3871.79 | 14735 | 4.89598 | 3(Tie) |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1637.95 | 0.186062 | 811.653ms | 9578 | 30 | 3229.89 | 5576.67 | 1.85062 | 1(Win) |
| glaze | 1179.76 | 0.166018 | 1049.66ms | 9578 | 40 | 6608.97 | 7742.5 | 2.56816 | 2(Loss) |
| jsonifier (two-stage) | 939.246 | 0.771936 | 1194.54ms | 9578 | 4890 | 2.75589e+07 | 9725.13 | 3.227 | 3(Loss) |
| simdjson (ondemand) | 857.412 | 0.125156 | 1327.68ms | 9578 | 30 | 5333.33 | 10653.3 | 3.53742 | 4(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1071.95 | 2.10996 | 833.977ms | 9578 | 1280 | 4.1377e+07 | 8521.17 | 2.82691 | 1(Win) |
| glaze | 807.315 | 1.1778 | 1125.14ms | 9578 | 2560 | 4.54617e+07 | 11314.4 | 3.7566 | 2(Loss) |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7507.32 | 0.126649 | 139.277ms | 9578 | 640 | 1519.73 | 1216.72 | 0.397589 | 1(Win) |
| glaze | 2419.68 | 0.129054 | 419.524ms | 9578 | 80 | 1898.73 | 3775 | 1.24309 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1505.28 | 0.239833 | 257.978ms | 3873 | 80 | 2770.57 | 2453.75 | 2.00168 | 1(Win) |
| glaze | 1079.99 | 0.214561 | 357.238ms | 3873 | 40 | 2153.85 | 3420 | 2.80238 | 2(Loss) |
| jsonifier (two-stage) | 569.037 | 0.157731 | 670.736ms | 3873 | 640 | 67085.2 | 6490.94 | 5.32393 | 3(Loss) |
| simdjson (ondemand) | 367.067 | 0.709174 | 1004.65ms | 3873 | 4890 | 2.49011e+07 | 10062.4 | 8.26196 | 4(Loss) |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2013.54 | 0.205338 | 195.153ms | 3873 | 160 | 2270.05 | 1834.38 | 1.48625 | 1(Win) |
| glaze | 1339.77 | 0.142465 | 288.886ms | 3873 | 160 | 2468.16 | 2756.88 | 2.23779 | 2(Loss) |
| jsonifier (two-stage) | 635.933 | 0.166783 | 599.872ms | 3873 | 320 | 30027.8 | 5808.12 | 4.76518 | 3(Loss) |
| simdjson (ondemand) | 403.45 | 0.344181 | 934.389ms | 3873 | 320 | 317718 | 9155 | 7.5133 | 4(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 537.786 | 0.531715 | 703.442ms | 3873 | 160 | 213380 | 6868.12 | 5.62714 | 1(Win) |
| glaze | 374.152 | 0.219813 | 1016.66ms | 3873 | 320 | 150680 | 9871.88 | 8.10219 | 2(Loss) |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4765.91 | 0.894678 | 94.621ms | 3873 | 40 | 1923.08 | 775 | 0.616273 | 1(Win) |
| glaze | 1114.15 | 0.285296 | 366.057ms | 3873 | 640 | 57250.4 | 3315.16 | 2.70254 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 579.456 | 0.805455 | 5151.15ms | 2090234 | 80 | 6.14217e+10 | 3.44013e+06 | 5.2449 | 1(Win) |
| jsonifier (two-stage) | 550.919 | 0.746122 | 5477.48ms | 2090234 | 80 | 5.83075e+10 | 3.61832e+06 | 5.51647 | 2(Loss) |
| glaze | 379.918 | 0.731762 | 7994.86ms | 2090234 | 40 | 5.8967e+10 | 5.24692e+06 | 7.99984 | 3(Loss) |
| simdjson (ondemand) | 356.42 | 0.433707 | 8399.38ms | 2090234 | 80 | 4.70705e+10 | 5.59285e+06 | 8.52729 | 4(Loss) |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 691.286 | 1.02993 | 5135.48ms | 2090234 | 80 | 7.05633e+10 | 2.88361e+06 | 4.39637 | 1(Win) |
| jsonifier (two-stage) | 622.356 | 0.763845 | 5509.44ms | 2090234 | 80 | 4.78865e+10 | 3.20299e+06 | 4.88324 | 2(Loss) |
| glaze | 412.84 | 0.792793 | 8021.84ms | 2090234 | 40 | 5.86146e+10 | 4.82851e+06 | 7.36185 | 3(Loss) |
| simdjson (ondemand) | 401.085 | 0.352942 | 8314.8ms | 2090234 | 80 | 2.46158e+10 | 4.97002e+06 | 7.57773 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1168.11 | 0.483326 | 5262.63ms | 2090234 | 160 | 1.08848e+10 | 1.70652e+06 | 2.60155 | 1(Win) |
| glaze | 792.974 | 0.706137 | 7901.52ms | 2090234 | 40 | 1.2604e+10 | 2.51383e+06 | 3.83259 | 2(Loss) |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1481.9 | 0.354442 | 8492.61ms | 2090234 | 320 | 7.27432e+09 | 1.34517e+06 | 2.05055 | 1(Win) |
| glaze | 1071.07 | 0.408882 | 5806.73ms | 2090234 | 160 | 9.26557e+09 | 1.86114e+06 | 2.83736 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1652.7 | 0.603124 | 5792.58ms | 6661897 | 80 | 4.30041e+10 | 3.84418e+06 | 1.83892 | 1(Win) |
| jsonifier | 1539.44 | 0.604123 | 6214.41ms | 6661897 | 80 | 4.9729e+10 | 4.127e+06 | 1.97422 | 2(Loss) |
| simdjson (ondemand) | 1095.27 | 0.651967 | 8696.56ms | 6661897 | 30 | 4.29065e+10 | 5.80063e+06 | 2.77485 | 3(Loss) |
| glaze | 1018.61 | 0.470406 | 9343.71ms | 6661897 | 80 | 6.8868e+10 | 6.23722e+06 | 2.9838 | 4(Loss) |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1928.09 | 0.588845 | 5766.11ms | 6661897 | 80 | 3.01185e+10 | 3.29512e+06 | 1.57623 | 1(Win) |
| jsonifier | 1755.86 | 0.747221 | 6181.33ms | 6661897 | 80 | 5.84797e+10 | 3.61833e+06 | 1.73086 | 2(Loss) |
| simdjson (ondemand) | 1226.96 | 0.59071 | 8554.21ms | 6661897 | 30 | 2.80678e+10 | 5.17808e+06 | 2.4771 | 3(Loss) |
| glaze | 1101.83 | 0.734102 | 9366.23ms | 6661897 | 30 | 5.37526e+10 | 5.76611e+06 | 2.75841 | 4(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2574.54 | 0.675388 | 7555.98ms | 6661897 | 80 | 2.22226e+10 | 2.46774e+06 | 1.18044 | 1(Win) |
| glaze | 1394.88 | 0.53772 | 6812.16ms | 6661897 | 40 | 2.39936e+10 | 4.55471e+06 | 2.17888 | 2(Loss) |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4414.83 | 0.424418 | 9024.75ms | 6661897 | 320 | 1.19373e+10 | 1.43908e+06 | 0.688272 | 1(Win) |
| glaze | 2953.94 | 0.480255 | 6675.15ms | 6661897 | 160 | 1.7071e+10 | 2.15078e+06 | 1.02877 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1454.11 | 0.322893 | 8363.79ms | 500299 | 1280 | 1.43679e+09 | 328119 | 2.08989 | 1(Win) |
| jsonifier (two-stage) | 1195.91 | 0.439949 | 5038.62ms | 500299 | 640 | 1.97174e+09 | 398963 | 2.541 | 2(Loss) |
| glaze | 836.755 | 0.459642 | 7288.7ms | 500299 | 640 | 4.39624e+09 | 570205 | 3.63188 | 3(Loss) |
| simdjson (ondemand) | 493.441 | 0.36246 | 6094.67ms | 500299 | 320 | 3.9306e+09 | 966930 | 6.15879 | 4(Loss) |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1764.14 | 0.780244 | 7984.7ms | 500299 | 320 | 1.42497e+09 | 270456 | 1.72262 | 1(Win) |
| jsonifier (two-stage) | 1425.09 | 0.289117 | 9741.15ms | 500299 | 1280 | 1.19931e+09 | 334802 | 2.13232 | 2(Loss) |
| glaze | 984.557 | 0.405529 | 6803.92ms | 500299 | 320 | 1.23587e+09 | 484606 | 3.08685 | 3(Loss) |
| simdjson (ondemand) | 537.739 | 0.480628 | 5848.59ms | 500299 | 160 | 2.90975e+09 | 887276 | 5.65173 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6849.61 | 0.299516 | 6975.33ms | 500299 | 4890 | 2.12851e+08 | 69656.8 | 0.44354 | 1(Win) |
| glaze | 4389.53 | 0.347875 | 5540.03ms | 500299 | 2560 | 3.66024e+08 | 108696 | 0.692149 | 2(Loss) |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6842.69 | 0.347414 | 6965.17ms | 500299 | 4890 | 2.86953e+08 | 69727.3 | 0.443958 | 1(Win) |
| glaze | 4884.54 | 0.326601 | 9742.55ms | 500299 | 4890 | 4.97685e+08 | 97680.1 | 0.621916 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2979.64 | 0.382279 | 5944.92ms | 1439562 | 640 | 1.98552e+09 | 460752 | 1.01983 | 1(Win) |
| jsonifier | 2557.66 | 0.441774 | 6823.26ms | 1439562 | 640 | 3.5988e+09 | 536770 | 1.18803 | 2(Loss) |
| glaze | 1870.37 | 1.10554 | 9439.81ms | 1439562 | 30 | 1.9755e+09 | 734013 | 1.62475 | 3(Loss) |
| simdjson (ondemand) | 1342.45 | 0.580248 | 6545.63ms | 1439562 | 80 | 2.81696e+09 | 1.02266e+06 | 2.26375 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 3412.29 | 0.873368 | 5716.42ms | 1439562 | 160 | 1.97554e+09 | 402332 | 0.890492 | 1(Win) |
| jsonifier | 2891.39 | 0.555104 | 6647.18ms | 1439562 | 640 | 4.44609e+09 | 474815 | 1.05096 | 2(Loss) |
| glaze | 1949.17 | 0.588765 | 9479.64ms | 1439562 | 640 | 1.10059e+10 | 704338 | 1.55904 | 3(Loss) |
| simdjson (ondemand) | 1416.57 | 0.379969 | 6373.39ms | 1439562 | 320 | 4.33939e+09 | 969150 | 2.1453 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4280.19 | 0.687322 | 8159.63ms | 1439562 | 320 | 1.55526e+09 | 320750 | 0.709528 | 1(Win) |
| glaze | 1852.44 | 0.360539 | 9394.95ms | 1439584 | 640 | 4.56952e+09 | 741127 | 1.63993 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14032.8 | 0.828243 | 5055.71ms | 1439562 | 30 | 1.96975e+07 | 97833.3 | 0.21645 | 1(Win) |
| glaze | 7457.58 | 0.377308 | 9626.53ms | 1439584 | 80 | 3.85976e+07 | 184094 | 0.407342 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1141.84 | 0.27182 | 4886.17ms | 56369 | 30 | 491310 | 47080 | 2.65994 | 1(Tie) |
| glaze STATISTICAL TIE | 1135.29 | 0.484828 | 4688.41ms | 56369 | 4890 | 2.57724e+08 | 47351.7 | 2.67554 | 1(Tie) |
| jsonifier (two-stage) | 1000.24 | 0.235726 | 5464.83ms | 56369 | 40 | 642026 | 53745 | 3.03706 | 3(Loss) |
| simdjson (ondemand) | 611.647 | 0.298117 | 9238.67ms | 56369 | 30 | 2.05955e+06 | 87890 | 4.96773 | 4(Loss) |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1932.38 | 0.418015 | 3250.46ms | 56369 | 4890 | 6.61285e+07 | 27819.4 | 1.57111 | 1(Win) |
| jsonifier | 1557.96 | 0.583501 | 3945.79ms | 56369 | 2560 | 1.03775e+08 | 34505.1 | 1.94937 | 2(Loss) |
| jsonifier (two-stage) | 1396.91 | 0.326816 | 4494.73ms | 56369 | 30 | 474540 | 38483.3 | 2.17452 | 3(Loss) |
| simdjson (ondemand) | 725.423 | 0.224096 | 7898.67ms | 56369 | 4890 | 1.34857e+08 | 74105.3 | 4.18823 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6600.11 | 1.16753 | 804.153ms | 56369 | 4890 | 4.42202e+07 | 8144.97 | 0.459088 | 1(Win) |
| glaze | 4429.63 | 0.429605 | 1268.94ms | 56369 | 320 | 869833 | 12135.9 | 0.68472 | 2(Loss) |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7300.78 | 0.41454 | 774.955ms | 56369 | 640 | 596287 | 7363.28 | 0.414934 | 1(Win) |
| glaze | 4782.43 | 0.77201 | 1114.86ms | 56369 | 4890 | 3.68246e+07 | 11240.7 | 0.630102 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1738.28 | 0.327974 | 5429.07ms | 94370 | 160 | 4.61349e+06 | 51774.4 | 1.74751 | 1(Win) |
| jsonifier (two-stage) | 1646.01 | 0.236713 | 5729.76ms | 94370 | 30 | 502540 | 54676.7 | 1.84532 | 2(Loss) |
| jsonifier | 1377.19 | 0.336304 | 6651.1ms | 94370 | 4890 | 2.36187e+08 | 65349.4 | 2.20567 | 3(Loss) |
| simdjson (ondemand) | 941.627 | 0.516591 | 9532.01ms | 94370 | 4890 | 1.1921e+09 | 95577.4 | 3.22674 | 4(Loss) |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2567.93 | 0.35636 | 4027.88ms | 94370 | 2560 | 3.9932e+07 | 35047 | 1.18256 | 1(Win) |
| jsonifier (two-stage) | 2185.35 | 0.365199 | 4762.78ms | 94370 | 80 | 1.80956e+06 | 41182.5 | 1.39016 | 2(Loss) |
| jsonifier | 1861.52 | 0.395413 | 5561.96ms | 94370 | 30 | 1.09637e+06 | 48346.7 | 1.63094 | 3(Loss) |
| simdjson (ondemand) | 1173 | 0.53968 | 8109.39ms | 94370 | 1280 | 2.19458e+08 | 76724.5 | 2.59016 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10364.5 | 0.497204 | 906.206ms | 94370 | 30 | 55919.5 | 8683.33 | 0.292538 | 1(Win) |
| glaze | 4514.58 | 0.480459 | 2089.49ms | 94370 | 40 | 366949 | 19935 | 0.672005 | 2(Loss) |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10821.4 | 0.101232 | 870.884ms | 94370 | 30 | 2126.44 | 8316.67 | 0.279993 | 1(Win) |
| glaze | 5091.66 | 0.363552 | 1790.88ms | 94370 | 640 | 2.64279e+06 | 17675.6 | 0.595145 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1192.67 | 0.883286 | 975.135ms | 11812 | 320 | 2.22718e+06 | 9445 | 2.5438 | 1(Win) |
| jsonifier (two-stage) | 1075.23 | 2.11677 | 1036.49ms | 11812 | 1280 | 6.29508e+07 | 10476.6 | 2.81956 | 2(Loss) |
| glaze | 973.096 | 0.484546 | 1222.04ms | 11812 | 80 | 251707 | 11576.2 | 3.11545 | 3(Loss) |
| simdjson (ondemand) | 505.474 | 0.32889 | 2281.17ms | 11812 | 320 | 1.7191e+06 | 22285.6 | 6.00608 | 4(Loss) |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1341.7 | 0.273191 | 960.234ms | 11812 | 320 | 168353 | 8395.94 | 2.25982 | 1(Win) |
| jsonifier (two-stage) | 1302.67 | 0.109452 | 1018.54ms | 11812 | 40 | 3583.33 | 8647.5 | 2.32726 | 2(Loss) |
| glaze | 1118.47 | 0.545055 | 1120.1ms | 11812 | 4890 | 1.47364e+07 | 10071.7 | 2.71072 | 3(Loss) |
| simdjson (ondemand) | 543.166 | 0.459127 | 2184.33ms | 11812 | 4890 | 4.43359e+07 | 20739.1 | 5.58713 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7218.13 | 0.248278 | 164.957ms | 11812 | 160 | 2402.12 | 1560.62 | 0.413888 | 1(Win) |
| glaze | 3290.16 | 0.279036 | 350.963ms | 11812 | 2560 | 233654 | 3423.79 | 0.916316 | 2(Loss) |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7819.38 | 1.43838 | 150.825ms | 11812 | 320 | 137404 | 1440.62 | 0.382929 | 1(Win) |
| glaze | 3959.51 | 0.28001 | 303.847ms | 11812 | 40 | 2538.46 | 2845 | 0.754457 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2641.33 | 0.419924 | 1163.14ms | 31235 | 640 | 1.43535e+06 | 11277.7 | 1.14856 | 1(Win) |
| jsonifier | 2202.77 | 0.757045 | 1357.54ms | 31235 | 4890 | 5.12505e+07 | 13523 | 1.37739 | 2(Loss) |
| glaze | 1819.18 | 0.681303 | 1624.9ms | 31235 | 4890 | 6.08583e+07 | 16374.4 | 1.66809 | 3(Loss) |
| simdjson (ondemand) | 1237.76 | 0.458948 | 2415.93ms | 31235 | 4890 | 5.96552e+07 | 24066.1 | 2.45298 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2929.01 | 0.604013 | 1141.55ms | 31235 | 80 | 301873 | 10170 | 1.03592 | 1(Win) |
| jsonifier | 2360.79 | 0.949748 | 1346.69ms | 31235 | 4890 | 7.02255e+07 | 12617.8 | 1.28474 | 2(Loss) |
| glaze | 2065.08 | 1.01484 | 1535.93ms | 31235 | 2560 | 5.48591e+07 | 14424.6 | 1.46912 | 3(Loss) |
| simdjson (ondemand) | 1335.27 | 0.628416 | 2329.93ms | 31235 | 4890 | 9.61051e+07 | 22308.6 | 2.27313 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14218.6 | 0.132491 | 219.895ms | 31235 | 160 | 1232.7 | 2095 | 0.211124 | 1(Win) |
| glaze | 5468.2 | 0.553792 | 559.226ms | 31235 | 40 | 36403.8 | 5447.5 | 0.552927 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15156.9 | 0.241786 | 204.669ms | 31235 | 320 | 7225.61 | 1965.31 | 0.19827 | 1(Win) |
| glaze | 6656.54 | 0.222746 | 480.726ms | 31235 | 40 | 3974.36 | 4475 | 0.451015 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1919.62 | 0.545728 | 5413.69ms | 108313 | 2560 | 2.20762e+08 | 53810.4 | 1.58249 | 1(Win) |
| glaze | 1450.52 | 0.291016 | 7125.96ms | 108313 | 4890 | 2.10017e+08 | 71212.4 | 2.09351 | 2(Loss) |
| jsonifier (two-stage) | 1312.01 | 0.437395 | 7827.86ms | 108313 | 4890 | 5.79886e+08 | 78730.5 | 2.31574 | 3(Loss) |
| simdjson (ondemand) | 659.795 | 0.372264 | 8007.32ms | 108313 | 2560 | 8.69533e+08 | 156557 | 4.60566 | 4(Loss) |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2484.27 | 0.619819 | 4487.2ms | 108313 | 2560 | 1.70033e+08 | 41579.8 | 1.22265 | 1(Win) |
| glaze | 1838 | 0.457814 | 6172.22ms | 108313 | 160 | 1.05918e+07 | 56200 | 1.65281 | 2(Loss) |
| jsonifier (two-stage) | 1569.03 | 0.59282 | 6850.43ms | 108313 | 2560 | 3.89925e+08 | 65833.7 | 1.93628 | 3(Loss) |
| simdjson (ondemand) | 726.321 | 0.421998 | 7390.23ms | 108313 | 1280 | 4.61038e+08 | 142217 | 4.1837 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7867.87 | 0.221882 | 1368.59ms | 108313 | 160 | 135772 | 13128.8 | 0.385628 | 1(Win) |
| glaze | 4054.46 | 0.765729 | 2523.78ms | 108313 | 2560 | 9.74287e+07 | 25477 | 0.74881 | 2(Loss) |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8008.36 | 0.298822 | 1328.54ms | 108313 | 320 | 475389 | 12898.4 | 0.378853 | 1(Win) |
| glaze | 4640.57 | 0.46461 | 2221.21ms | 108313 | 4890 | 5.23002e+07 | 22259.2 | 0.652708 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2485.03 | 0.286715 | 8217.9ms | 213963 | 4890 | 2.71034e+08 | 82112.2 | 1.22266 | 1(Win) |
| glaze | 2117.17 | 0.492791 | 9586.5ms | 213963 | 2560 | 5.77471e+08 | 96379 | 1.43513 | 2(Loss) |
| jsonifier | 2038.06 | 0.627881 | 5069.16ms | 213963 | 1280 | 5.05833e+08 | 100120 | 1.49071 | 3(Loss) |
| simdjson (ondemand) | 1211.38 | 0.393942 | 8594.43ms | 213963 | 1280 | 5.63628e+08 | 168445 | 2.50859 | 4(Loss) |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2850.93 | 0.488002 | 7328.17ms | 213963 | 2560 | 3.1231e+08 | 71573.4 | 1.0657 | 1(Win) |
| glaze | 2540.56 | 0.344292 | 8342.03ms | 213963 | 2560 | 1.95754e+08 | 80317.3 | 1.19591 | 2(Loss) |
| jsonifier | 2341.21 | 0.246678 | 9000.09ms | 213963 | 4890 | 2.26031e+08 | 87156.3 | 1.29778 | 3(Loss) |
| simdjson (ondemand) | 1347.67 | 0.414948 | 7980.38ms | 213963 | 640 | 2.52624e+08 | 151410 | 2.25484 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12955 | 0.851817 | 1615.76ms | 213963 | 640 | 1.15207e+07 | 15750.8 | 0.234039 | 1(Win) |
| glaze | 4577.06 | 1.0825 | 4721.41ms | 213963 | 80 | 1.86317e+07 | 44581.2 | 0.663462 | 2(Loss) |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13049.4 | 0.645341 | 1563.46ms | 213963 | 4890 | 4.97949e+07 | 15636.8 | 0.232507 | 1(Win) |
| glaze | 5275.61 | 0.396709 | 3902.35ms | 213963 | 4890 | 1.15129e+08 | 38678.2 | 0.575386 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 489.32 | 0.98329 | 5341.33ms | 1834197 | 40 | 4.94231e+10 | 3.57481e+06 | 6.21101 | 1(Win) |
| jsonifier (two-stage) | 449.664 | 0.481536 | 5900.2ms | 1834197 | 80 | 2.80713e+10 | 3.89007e+06 | 6.75878 | 2(Loss) |
| glaze | 293.276 | 0.428113 | 9002.9ms | 1834197 | 80 | 5.21609e+10 | 5.96443e+06 | 10.3632 | 3(Loss) |
| simdjson (ondemand) | 35.9803 | 0.343199 | 14617.9ms | 1834197 | 30 | 8.35173e+11 | 4.86162e+07 | 84.4763 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 533.926 | 0.473812 | 5377.56ms | 1834197 | 80 | 1.92766e+10 | 3.27616e+06 | 5.69194 | 1(Win) |
| jsonifier (two-stage) | 473.83 | 0.71498 | 5939.06ms | 1834197 | 40 | 2.78673e+10 | 3.69167e+06 | 6.41404 | 2(Loss) |
| glaze | 319.957 | 0.485199 | 8752.29ms | 1834197 | 80 | 5.62909e+10 | 5.46707e+06 | 9.49909 | 3(Loss) |
| simdjson (ondemand) | 35.9235 | 0.258489 | 14696.1ms | 1834197 | 30 | 4.7527e+11 | 4.86931e+07 | 84.6103 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 778.169 | 0.634694 | 6899.87ms | 1834197 | 80 | 1.62841e+10 | 2.24787e+06 | 3.90542 | 1(Win) |
| glaze | 667.61 | 0.317746 | 8159.53ms | 1833577 | 160 | 1.10824e+10 | 2.61925e+06 | 4.55223 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 902.903 | 0.89426 | 6049.71ms | 1834197 | 30 | 9.00449e+09 | 1.93734e+06 | 3.36585 | 1(Win) |
| glaze | 718.327 | 0.61418 | 7465.95ms | 1833577 | 80 | 1.78828e+10 | 2.43432e+06 | 4.23084 | 2(Loss) |
### Marine IK Reverse Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 0.387659%)

### Marine IK Reverse Test (Prettified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 0.295537%)


----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2723.28 | 0.476652 | 5210.21ms | 9930848 | 80 | 2.19827e+10 | 3.47772e+06 | 1.11601 | 1(Win) |
| glaze | 1789.29 | 0.549813 | 7879.32ms | 9930228 | 40 | 3.38727e+10 | 5.29272e+06 | 1.69862 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4605.91 | 0.257522 | 6526.9ms | 9930848 | 40 | 1.12158e+09 | 2.05623e+06 | 0.65979 | 1(Win) |
| glaze | 3276.82 | 0.36484 | 8951.64ms | 9930228 | 160 | 1.77885e+10 | 2.89006e+06 | 0.927448 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 496.802 | 0.519446 | 5315.35ms | 1834197 | 80 | 2.67606e+10 | 3.52098e+06 | 6.11751 | 1(Win) |
| jsonifier (two-stage) | 442.475 | 0.49248 | 5927.42ms | 1834197 | 80 | 3.03237e+10 | 3.95328e+06 | 6.86866 | 2(Loss) |
| glaze | 302.529 | 0.435861 | 8699.59ms | 1834197 | 80 | 5.08094e+10 | 5.78201e+06 | 10.0462 | 3(Loss) |
| simdjson (ondemand) | 253.734 | 0.511098 | 10421.8ms | 1834197 | 40 | 4.96596e+10 | 6.89394e+06 | 11.9784 | 4(Loss) |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 548.34 | 0.574987 | 5232.03ms | 1834197 | 80 | 2.69152e+10 | 3.19004e+06 | 5.5425 | 1(Win) |
| jsonifier (two-stage) | 477.056 | 0.484666 | 5969.76ms | 1834197 | 80 | 2.52656e+10 | 3.66671e+06 | 6.37072 | 2(Loss) |
| glaze | 318.244 | 0.474782 | 8681.83ms | 1834197 | 80 | 5.44817e+10 | 5.4965e+06 | 9.55008 | 3(Loss) |
| simdjson (ondemand) | 264.202 | 0.512545 | 10332.1ms | 1834197 | 40 | 4.60621e+10 | 6.62079e+06 | 11.5039 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 801.621 | 0.320112 | 6832.43ms | 1834197 | 160 | 7.80685e+09 | 2.18211e+06 | 3.79109 | 1(Win) |
| glaze | 585.161 | 0.558809 | 9254.26ms | 1833577 | 80 | 2.23082e+10 | 2.9883e+06 | 5.19366 | 2(Loss) |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 906.449 | 0.829198 | 5983.08ms | 1834197 | 40 | 1.02419e+10 | 1.92976e+06 | 3.35271 | 1(Win) |
| glaze | 724.502 | 0.458942 | 7417.07ms | 1833577 | 160 | 1.96315e+10 | 2.41357e+06 | 4.19468 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2175.09 | 0.590837 | 6543.65ms | 9930848 | 30 | 1.98553e+10 | 4.35421e+06 | 1.39727 | 1(Win) |
| jsonifier | 2024.82 | 0.56654 | 7029.99ms | 9930848 | 80 | 5.61762e+10 | 4.67736e+06 | 1.50098 | 2(Loss) |
| glaze | 1370.97 | 0.347208 | 10360.9ms | 9930848 | 80 | 4.60241e+10 | 6.90808e+06 | 2.2169 | 3(Loss) |
| simdjson (ondemand) | 1273.81 | 0.51081 | 5210.2ms | 9930848 | 40 | 5.76955e+10 | 7.43502e+06 | 2.38595 | 4(Loss) |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2358.13 | 0.754106 | 6492.69ms | 9930848 | 30 | 2.75183e+10 | 4.01623e+06 | 1.28881 | 1(Win) |
| jsonifier | 2161.27 | 0.405342 | 7040.94ms | 9930848 | 80 | 2.52398e+10 | 4.38204e+06 | 1.40622 | 2(Loss) |
| glaze | 1433.21 | 0.434882 | 10405.5ms | 9930848 | 80 | 6.60671e+10 | 6.6081e+06 | 2.12063 | 3(Loss) |
| simdjson (ondemand) | 1318.16 | 0.393751 | 5300.71ms | 9930848 | 30 | 2.40107e+10 | 7.18488e+06 | 2.30573 | 4(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2593.41 | 0.587468 | 5433.79ms | 9930848 | 80 | 3.68205e+10 | 3.65187e+06 | 1.1719 | 1(Win) |
| glaze | 1209.85 | 0.533342 | 5488.66ms | 9930228 | 30 | 5.22865e+10 | 7.82759e+06 | 2.51213 | 2(Loss) |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4348.24 | 0.441814 | 6757.88ms | 9930848 | 160 | 1.48165e+10 | 2.17808e+06 | 0.698883 | 1(Win) |
| glaze | 3215.47 | 0.51892 | 9153.6ms | 9930228 | 80 | 1.86862e+10 | 2.9452e+06 | 0.94514 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 896.972 | 0.756718 | 8523.99ms | 642697 | 160 | 4.27801e+09 | 683325 | 3.38806 | 1(Win) |
| jsonifier (two-stage) | 804.035 | 0.887456 | 9815.18ms | 642697 | 30 | 1.37302e+09 | 762310 | 3.77958 | 2(Loss) |
| glaze | 666.18 | 0.417451 | 5798.45ms | 642697 | 320 | 4.72052e+09 | 920057 | 4.56163 | 3(Loss) |
| simdjson (ondemand) | 420.978 | 0.393893 | 9230.11ms | 642697 | 160 | 5.26225e+09 | 1.45595e+06 | 7.21911 | 4(Loss) |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 958.42 | 0.700446 | 8436.22ms | 642697 | 160 | 3.21048e+09 | 639514 | 3.17068 | 1(Win) |
| jsonifier (two-stage) | 834.731 | 0.38919 | 9760.53ms | 642697 | 320 | 2.61332e+09 | 734277 | 3.64041 | 2(Loss) |
| glaze | 740.32 | 0.604494 | 5377.73ms | 642697 | 160 | 4.00754e+09 | 827918 | 4.10505 | 3(Loss) |
| simdjson (ondemand) | 450.381 | 0.289042 | 8772.97ms | 642697 | 320 | 4.95135e+09 | 1.3609e+06 | 6.7478 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1240.81 | 0.457685 | 6288.78ms | 642697 | 320 | 1.63564e+09 | 493971 | 2.44858 | 1(Win) |
| glaze | 917.626 | 0.452798 | 8573.96ms | 642692 | 160 | 1.46354e+09 | 667939 | 3.31072 | 2(Loss) |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1567.91 | 0.325982 | 5005.91ms | 642697 | 640 | 1.0393e+09 | 390918 | 1.93824 | 1(Win) |
| glaze | 1242.67 | 0.536854 | 6182.84ms | 642692 | 320 | 2.24366e+09 | 493228 | 2.44557 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1438.94 | 0.554274 | 5104.4ms | 1225964 | 320 | 6.49039e+09 | 812524 | 2.11191 | 1(Win) |
| jsonifier STATISTICAL TIE | 1169.11 | 0.838558 | 6310.51ms | 1225964 | 40 | 2.81303e+09 | 1.00006e+06 | 2.59926 | 2(Tie) |
| glaze STATISTICAL TIE | 1157.42 | 0.613016 | 6371.13ms | 1225964 | 160 | 6.13528e+09 | 1.01015e+06 | 2.62554 | 2(Tie) |
| simdjson (ondemand) | 775.042 | 0.396248 | 9424.91ms | 1225964 | 320 | 1.14338e+10 | 1.50852e+06 | 3.92108 | 4(Loss) |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1517.8 | 0.348174 | 5076.66ms | 1225964 | 320 | 2.30182e+09 | 770307 | 2.00211 | 1(Win) |
| glaze | 1296.74 | 0.312716 | 5923.8ms | 1225964 | 320 | 2.54391e+09 | 901626 | 2.3435 | 2(Loss) |
| jsonifier | 1222.98 | 0.306698 | 6264.55ms | 1225964 | 320 | 2.75099e+09 | 956000 | 2.4848 | 3(Loss) |
| simdjson (ondemand) | 833.488 | 0.448448 | 8989.7ms | 1225964 | 160 | 6.33142e+09 | 1.40274e+06 | 3.64618 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2010.62 | 0.32463 | 7396.43ms | 1225964 | 640 | 2.28062e+09 | 581498 | 1.51096 | 1(Win) |
| glaze | 1473.47 | 0.499163 | 5007.59ms | 1225970 | 160 | 2.51003e+09 | 793482 | 2.06197 | 2(Loss) |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2955.52 | 0.566767 | 5053.44ms | 1225964 | 160 | 8.04301e+08 | 395589 | 1.02813 | 1(Win) |
| glaze | 2144.45 | 0.248225 | 6959.26ms | 1225970 | 640 | 1.17219e+09 | 545210 | 1.41712 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 889.445 | 0.35078 | 5691.45ms | 409725 | 40 | 9.49898e+07 | 439312 | 3.4167 | 1(Win) |
| jsonifier (two-stage) | 832.552 | 0.38161 | 5998.77ms | 409725 | 640 | 2.05296e+09 | 469333 | 3.64985 | 2(Loss) |
| glaze | 788.3 | 0.331565 | 6328.81ms | 409725 | 640 | 1.7287e+09 | 495679 | 3.85511 | 3(Loss) |
| simdjson (ondemand) | 499.112 | 0.316761 | 9920.86ms | 409725 | 640 | 3.93579e+09 | 782879 | 6.08844 | 4(Loss) |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1240.33 | 0.574332 | 9615.18ms | 409725 | 640 | 2.09517e+09 | 315033 | 2.45019 | 1(Win) |
| jsonifier (two-stage) | 1167.17 | 0.779821 | 5032.7ms | 409725 | 640 | 4.36202e+09 | 334780 | 2.60366 | 2(Loss) |
| glaze | 1055.18 | 0.573046 | 5459.53ms | 409725 | 320 | 1.44099e+09 | 370310 | 2.88015 | 3(Loss) |
| simdjson (ondemand) | 615.667 | 0.434682 | 8815.7ms | 409725 | 320 | 2.43549e+09 | 634668 | 4.93617 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3287.04 | 0.317395 | 6157.71ms | 409725 | 1280 | 1.82215e+08 | 118874 | 0.92379 | 1(Win) |
| glaze | 2807.47 | 0.449055 | 7291.07ms | 409725 | 40 | 1.56247e+07 | 139180 | 1.08225 | 2(Loss) |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7039.12 | 0.401317 | 5568.67ms | 409725 | 4890 | 2.42679e+08 | 55510.4 | 0.431546 | 1(Win) |
| glaze | 2966.51 | 0.405925 | 6766.28ms | 409725 | 1280 | 3.65927e+08 | 131719 | 1.02424 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1528.69 | 0.647139 | 6257.4ms | 785750 | 160 | 1.61007e+09 | 490191 | 1.98779 | 1(Win) |
| jsonifier | 1350.72 | 0.348587 | 7044.58ms | 785750 | 640 | 2.39353e+09 | 554778 | 2.24977 | 2(Loss) |
| glaze | 1306.7 | 0.41242 | 7284.41ms | 785750 | 640 | 3.57996e+09 | 573468 | 2.32562 | 3(Loss) |
| simdjson (ondemand) | 928.988 | 0.438433 | 5061.48ms | 785750 | 320 | 4.00226e+09 | 806630 | 3.27121 | 4(Loss) |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2072.3 | 0.816988 | 5314.58ms | 785750 | 160 | 1.39641e+09 | 361602 | 1.46637 | 1(Win) |
| jsonifier | 1795.75 | 0.312679 | 6095.99ms | 785750 | 640 | 1.08957e+09 | 417291 | 1.69239 | 2(Loss) |
| glaze | 1688.62 | 0.445897 | 6415.95ms | 785750 | 320 | 1.25292e+09 | 443765 | 1.7997 | 3(Loss) |
| simdjson (ondemand) | 1135.05 | 0.324457 | 9154.15ms | 785750 | 640 | 2.93651e+09 | 660189 | 2.6773 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4045.2 | 0.421116 | 9618.75ms | 785750 | 1280 | 7.78937e+08 | 185244 | 0.750721 | 1(Win) |
| glaze | 2199.54 | 0.422436 | 8759.87ms | 785750 | 640 | 1.32559e+09 | 340685 | 1.38071 | 2(Loss) |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11460.8 | 0.351169 | 6512.98ms | 785750 | 4890 | 2.57796e+08 | 65383.5 | 0.26504 | 1(Win) |
| glaze | 4334.7 | 0.353199 | 8888.69ms | 785750 | 1280 | 4.77198e+08 | 172872 | 0.700927 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 5622.28 | 0.214712 | 4531.52ms | 264040 | 2560 | 2.36738e+07 | 44787.6 | 0.540275 | 1(Win) |
| jsonifier | 5548.98 | 0.298359 | 4539.39ms | 264040 | 4890 | 8.96397e+07 | 45379.2 | 0.547396 | 2(Loss) |
| glaze | 2547.87 | 0.185599 | 5110.48ms | 264040 | 1280 | 4.3067e+07 | 98830.7 | 1.19262 | 3(Loss) |
| simdjson (ondemand) | 1919.91 | 0.62704 | 6787.24ms | 264040 | 80 | 5.41076e+07 | 131156 | 1.58284 | 4(Loss) |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 6138.67 | 0.381519 | 4399.75ms | 264040 | 30 | 734759 | 41020 | 0.494902 | 1(Win) |
| jsonifier | 5874.42 | 0.254765 | 4428.5ms | 264040 | 2560 | 3.05301e+07 | 42865.2 | 0.51686 | 2(Loss) |
| glaze | 2580.11 | 0.491709 | 9763.51ms | 264040 | 320 | 7.36935e+07 | 97595.9 | 1.1776 | 3(Loss) |
| simdjson (ondemand) | 1957.2 | 0.611645 | 6653.99ms | 264040 | 320 | 1.98162e+08 | 128658 | 1.5525 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 7100.13 | 0.469236 | 5492.12ms | 399947 | 40 | 2.54164e+06 | 53720 | 0.427907 | 1(Win) |
| jsonifier | 6969.96 | 0.356329 | 5493.76ms | 399947 | 2560 | 9.7339e+07 | 54723.3 | 0.435848 | 2(Loss) |
| glaze | 3229.48 | 0.418302 | 6035.06ms | 399947 | 1280 | 3.12412e+08 | 118105 | 0.940902 | 3(Loss) |
| simdjson (ondemand) | 2677.96 | 0.498576 | 7285.42ms | 399947 | 640 | 3.22729e+08 | 142429 | 1.13471 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 7334.21 | 0.263083 | 5382.62ms | 399947 | 2560 | 4.79206e+07 | 52005.5 | 0.414166 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 7255.65 | 0.743083 | 5381.73ms | 399947 | 640 | 9.7658e+07 | 52568.6 | 0.418651 | 1(Tie) |
| glaze | 3388.94 | 0.330032 | 5868.06ms | 399947 | 160 | 2.20755e+07 | 112548 | 0.896536 | 3(Loss) |
| simdjson (ondemand) | 2725.38 | 0.25228 | 7272.14ms | 399947 | 2560 | 3.19121e+08 | 139951 | 1.11497 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1208.97 | 0.544269 | 5350.63ms | 264040 | 1280 | 1.64492e+09 | 208283 | 2.51348 | 1(Win) |
| glaze STATISTICAL TIE | 1125.35 | 0.513003 | 5706.11ms | 264040 | 1280 | 1.68661e+09 | 223760 | 2.70035 | 2(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1116.75 | 0.830425 | 5701.24ms | 264040 | 320 | 1.12196e+09 | 225483 | 2.72115 | 2(Tie) |
| simdjson (ondemand) | 774.333 | 0.328545 | 8287.8ms | 264040 | 1280 | 1.46111e+09 | 325193 | 3.92468 | 4(Loss) |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1728.67 | 0.566252 | 8359.46ms | 264040 | 1280 | 8.70851e+08 | 145666 | 1.75783 | 1(Win) |
| glaze | 1541.89 | 0.457496 | 9353.71ms | 264040 | 2560 | 1.42905e+09 | 163311 | 1.97077 | 2(Loss) |
| jsonifier (two-stage) | 1510.36 | 0.357665 | 9508.21ms | 264040 | 2560 | 9.10272e+08 | 166720 | 2.01195 | 3(Loss) |
| simdjson (ondemand) | 948.938 | 0.555697 | 7123.91ms | 264040 | 640 | 1.39162e+09 | 265358 | 3.20249 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8146.82 | 0.74056 | 3177.6ms | 264040 | 160 | 8.38307e+06 | 30908.8 | 0.372768 | 1(Win) |
| glaze | 4401.9 | 0.436189 | 5750.54ms | 263923 | 2560 | 1.59244e+08 | 57179.1 | 0.690124 | 2(Loss) |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8023.5 | 0.399476 | 3128.43ms | 264040 | 4890 | 7.68603e+07 | 31383.8 | 0.378435 | 1(Win) |
| glaze | 5287.81 | 0.759876 | 4818.9ms | 263923 | 160 | 2.09319e+07 | 47599.4 | 0.57439 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1621.23 | 0.470962 | 6069.8ms | 399947 | 640 | 7.8572e+08 | 235266 | 1.87433 | 1(Win) |
| glaze | 1560.16 | 0.453702 | 6236.35ms | 399947 | 1280 | 1.57477e+09 | 244474 | 1.94784 | 2(Loss) |
| jsonifier | 1371.62 | 0.75676 | 7019.04ms | 399947 | 320 | 1.41711e+09 | 278079 | 2.21543 | 3(Loss) |
| simdjson (ondemand) | 1103.03 | 0.497778 | 8894.61ms | 399947 | 640 | 1.89621e+09 | 345794 | 2.75509 | 4(Loss) |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2078.6 | 0.517951 | 5222.13ms | 399947 | 320 | 2.89061e+08 | 183498 | 1.46199 | 1(Win) |
| jsonifier (two-stage) | 2027.49 | 0.696974 | 5281.16ms | 399947 | 1280 | 2.20054e+09 | 188123 | 1.49877 | 2(Loss) |
| jsonifier | 1754.14 | 0.507291 | 6040.83ms | 399947 | 640 | 7.78704e+08 | 217440 | 1.73242 | 3(Loss) |
| simdjson (ondemand) | 1331.94 | 0.662536 | 7718.82ms | 399947 | 640 | 2.30374e+09 | 286364 | 2.2816 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10596.8 | 0.610071 | 3634.97ms | 399947 | 2560 | 1.23439e+08 | 35993.7 | 0.286609 | 1(Win) |
| glaze | 3436.38 | 0.616497 | 5608.08ms | 399830 | 2560 | 1.19798e+09 | 110962 | 0.884202 | 2(Loss) |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10725.6 | 0.379119 | 3587.62ms | 399947 | 4890 | 8.8884e+07 | 35561.6 | 0.282802 | 1(Win) |
| glaze | 4072.36 | 0.334804 | 9369.48ms | 399830 | 4890 | 4.80561e+08 | 93633.1 | 0.74602 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 588.735 | 0.169139 | 791.178ms | 4630 | 30 | 4827.59 | 7500 | 5.14295 | 1(Win) |
| jsonifier (two-stage) | 550.334 | 0.165644 | 844.763ms | 4630 | 30 | 5298.85 | 8023.33 | 5.50711 | 2(Loss) |
| simdjson (ondemand) | 331.013 | 0.378997 | 1384.73ms | 4630 | 160 | 408943 | 13339.4 | 9.16255 | 3(Loss) |
| glaze | 315.958 | 0.226102 | 1356.95ms | 4630 | 80 | 79873.4 | 13975 | 9.60857 | 4(Loss) |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 737.558 | 0.191767 | 751.783ms | 4630 | 30 | 3954.02 | 5986.67 | 4.10026 | 1(Win) |
| jsonifier (two-stage) | 668.068 | 0.313521 | 819.374ms | 4630 | 640 | 274810 | 6609.38 | 4.53438 | 2(Loss) |
| simdjson (ondemand) | 367.5 | 0.484108 | 1392.47ms | 4630 | 80 | 270658 | 12015 | 8.25594 | 3(Loss) |
| glaze | 350.09 | 0.58925 | 1344.14ms | 4630 | 80 | 441867 | 12612.5 | 8.66482 | 4(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1724.81 | 0.355358 | 269.545ms | 4630 | 30 | 2482.76 | 2560 | 1.74357 | 1(Win) |
| glaze | 1115.27 | 0.283683 | 402.676ms | 4630 | 1280 | 161464 | 3959.14 | 2.71173 | 2(Loss) |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1734.55 | 0.166485 | 263.271ms | 4630 | 160 | 2873.82 | 2545.62 | 1.72702 | 1(Win) |
| glaze | 1191.77 | 0.493251 | 379.166ms | 4630 | 320 | 106871 | 3705 | 2.53214 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1569.14 | 0.474654 | 917.624ms | 14795 | 2560 | 4.66339e+06 | 8991.95 | 1.93187 | 1(Win) |
| jsonifier | 1485.42 | 0.417719 | 970.195ms | 14795 | 80 | 125948 | 9498.75 | 2.04239 | 2(Loss) |
| simdjson (ondemand) | 1027.65 | 0.152816 | 1438.58ms | 14795 | 30 | 13206.9 | 13730 | 2.95269 | 3(Loss) |
| glaze | 905.093 | 0.161791 | 1578.03ms | 14795 | 4890 | 3.1107e+06 | 15589.1 | 3.35329 | 4(Loss) |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1936.14 | 0.856449 | 887.543ms | 14795 | 320 | 1.24655e+06 | 7287.5 | 1.56467 | 1(Win) |
| jsonifier | 1799.7 | 0.125517 | 933.624ms | 14795 | 80 | 7746.84 | 7840 | 1.68362 | 2(Loss) |
| simdjson (ondemand) | 1061.1 | 0.967666 | 1455.66ms | 14795 | 2560 | 4.23846e+07 | 13297.1 | 2.85896 | 3(Loss) |
| glaze | 986.459 | 0.538222 | 1566.27ms | 14795 | 4890 | 2.89804e+07 | 14303.3 | 3.07557 | 4(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5037.49 | 0.729567 | 281.087ms | 14795 | 4890 | 2.04193e+06 | 2800.92 | 0.598892 | 1(Win) |
| glaze | 2857.55 | 0.29857 | 499.701ms | 14795 | 640 | 139096 | 4937.66 | 1.05957 | 2(Loss) |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5490.12 | 0.331114 | 273.017ms | 14795 | 30 | 2172.41 | 2570 | 0.547448 | 1(Win) |
| glaze | 3343.7 | 0.161375 | 440.029ms | 14795 | 2560 | 118710 | 4219.77 | 0.902774 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 939.244 | 0.180257 | 532.506ms | 5092 | 1280 | 111177 | 5170.23 | 3.22167 | 1(Win) |
| jsonifier (two-stage) | 835.819 | 0.211698 | 612.874ms | 5092 | 40 | 6051.28 | 5810 | 3.62197 | 2(Loss) |
| glaze | 679.83 | 0.565785 | 746.105ms | 5092 | 160 | 261336 | 7143.12 | 4.45925 | 3(Loss) |
| simdjson (ondemand) | 489.281 | 0.151992 | 1043.11ms | 5092 | 40 | 9102.56 | 9925 | 6.19219 | 4(Loss) |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1240.29 | 0.327277 | 493.868ms | 5092 | 640 | 105086 | 3915.31 | 2.43501 | 1(Win) |
| jsonifier (two-stage) | 1049.08 | 0.219698 | 571.32ms | 5092 | 640 | 66189.7 | 4628.91 | 2.88261 | 2(Loss) |
| glaze | 854.009 | 0.249356 | 674.788ms | 5092 | 640 | 128668 | 5686.25 | 3.54378 | 3(Loss) |
| simdjson (ondemand) | 538.185 | 0.312859 | 1009.68ms | 5092 | 320 | 255012 | 9023.12 | 5.63265 | 4(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5557.78 | 0.566559 | 87.4557ms | 5092 | 80 | 1960.44 | 873.75 | 0.534618 | 1(Win) |
| glaze | 3397.92 | 0.838523 | 144.469ms | 5092 | 4890 | 702245 | 1429.14 | 0.879983 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6400.14 | 0.514539 | 80.8819ms | 5092 | 160 | 2438.68 | 758.75 | 0.464225 | 1(Win) |
| glaze | 4374.87 | 0.568877 | 120.5ms | 5092 | 80 | 3189.87 | 1110 | 0.681537 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1768.25 | 0.37475 | 662.482ms | 11724 | 160 | 89839.2 | 6323.12 | 1.71309 | 1(Win) |
| jsonifier | 1532.02 | 0.377981 | 756.118ms | 11724 | 320 | 243507 | 7298.12 | 1.97706 | 2(Loss) |
| glaze | 1276 | 0.356026 | 897.147ms | 11724 | 1280 | 1.24573e+06 | 8762.42 | 2.37587 | 3(Loss) |
| simdjson (ondemand) | 1061.31 | 0.190905 | 1082.37ms | 11724 | 40 | 16179.5 | 10535 | 2.85634 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2146.4 | 0.642737 | 621.907ms | 11724 | 1280 | 1.43486e+06 | 5209.14 | 1.40969 | 1(Win) |
| jsonifier | 1871.28 | 0.155692 | 715.26ms | 11724 | 40 | 3461.54 | 5975 | 1.61596 | 2(Loss) |
| glaze | 1557.95 | 0.185186 | 837.458ms | 11724 | 30 | 5298.85 | 7176.67 | 1.94207 | 3(Loss) |
| simdjson (ondemand) | 1171 | 0.559364 | 1051.18ms | 11724 | 1280 | 3.65119e+06 | 9548.12 | 2.58949 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11223 | 0.279136 | 108.556ms | 11724 | 80 | 618.671 | 996.25 | 0.266907 | 1(Win) |
| glaze | 3709.22 | 0.618344 | 264.332ms | 11746 | 40 | 13948.7 | 3020 | 0.808797 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13234.3 | 0.352303 | 89.538ms | 11724 | 640 | 5669.77 | 844.844 | 0.224802 | 1(Win) |
| glaze | 5723.45 | 0.789669 | 203.764ms | 11746 | 320 | 76437.2 | 1957.19 | 0.520562 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1093.58 | 0.514615 | 438.476ms | 4857 | 160 | 76018.5 | 4235.62 | 2.76375 | 1(Win) |
| glaze | 994.716 | 0.680623 | 471.589ms | 4857 | 2560 | 2.57153e+06 | 4656.6 | 3.0402 | 2(Loss) |
| jsonifier (two-stage) | 913.834 | 0.253753 | 527.417ms | 4857 | 320 | 52938.9 | 5068.75 | 3.31067 | 3(Loss) |
| simdjson (ondemand) | 642.441 | 0.276994 | 752.177ms | 4857 | 30 | 11965.5 | 7210 | 4.71604 | 4(Loss) |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1830.83 | 0.53714 | 308.66ms | 4857 | 320 | 59097.2 | 2530 | 1.6405 | 1(Win) |
| jsonifier | 1451.68 | 0.343037 | 376.835ms | 4857 | 640 | 76675.4 | 3190.78 | 2.08172 | 2(Loss) |
| jsonifier (two-stage) | 1241.82 | 0.291709 | 434.757ms | 4857 | 30 | 3551.72 | 3730 | 2.42064 | 3(Loss) |
| simdjson (ondemand) | 839.986 | 0.297937 | 611.548ms | 4857 | 320 | 86375.8 | 5514.38 | 3.60676 | 4(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5532.81 | 0.282695 | 86.5143ms | 4857 | 1280 | 7169.57 | 837.188 | 0.537953 | 1(Win) |
| glaze | 3474 | 0.904967 | 132.029ms | 4857 | 30 | 4367.82 | 1333.33 | 0.870126 | 2(Loss) |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6218.75 | 0.304943 | 79.7359ms | 4857 | 1280 | 6603.57 | 744.844 | 0.477321 | 1(Win) |
| glaze | 4556.53 | 0.502363 | 106.882ms | 4857 | 320 | 8345.51 | 1016.56 | 0.649556 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1345.88 | 0.492089 | 539.818ms | 7376 | 320 | 211675 | 5226.56 | 2.25019 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1341.57 | 0.197891 | 557.476ms | 7376 | 30 | 3229.89 | 5243.33 | 2.25273 | 1(Tie) |
| jsonifier | 1212.55 | 0.276257 | 600.097ms | 7376 | 640 | 164380 | 5801.25 | 2.49252 | 3(Loss) |
| simdjson (ondemand) | 957.699 | 0.172104 | 768.497ms | 7376 | 320 | 51134.8 | 7345 | 3.16515 | 4(Loss) |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2099.01 | 0.167808 | 372.234ms | 7376 | 80 | 2530.06 | 3351.25 | 1.43392 | 1(Win) |
| jsonifier (two-stage) | 1794.46 | 0.256564 | 467.775ms | 7376 | 30 | 3034.48 | 3920 | 1.6898 | 2(Loss) |
| jsonifier | 1541.48 | 0.246034 | 533.756ms | 7376 | 30 | 3781.61 | 4563.33 | 1.95846 | 3(Loss) |
| simdjson (ondemand) | 1245.7 | 0.218616 | 631.357ms | 7376 | 320 | 48767.6 | 5646.88 | 2.43212 | 4(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6821.14 | 0.505689 | 99.0549ms | 7376 | 80 | 2175.63 | 1031.25 | 0.436631 | 1(Win) |
| glaze | 3552.68 | 1.61355 | 201.381ms | 7376 | 30 | 30620.7 | 1980 | 0.845915 | 2(Loss) |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8375.73 | 0.230607 | 88.9295ms | 7376 | 640 | 2400.6 | 839.844 | 0.354853 | 1(Win) |
| glaze | 4519.35 | 0.396161 | 165.925ms | 7376 | 1280 | 48667.8 | 1556.48 | 0.657657 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1097.86 | 0.574764 | 394.594ms | 4390 | 1280 | 614925 | 3813.44 | 2.75538 | 1(Win) |
| jsonifier (two-stage) | 968.007 | 0.295612 | 421.125ms | 4390 | 40 | 6538.46 | 4325 | 3.12909 | 2(Loss) |
| glaze | 897.155 | 0.551581 | 486.511ms | 4390 | 320 | 212013 | 4666.56 | 3.3718 | 3(Loss) |
| simdjson (ondemand) | 526.786 | 0.318532 | 860.629ms | 4390 | 40 | 25634.6 | 7947.5 | 5.74788 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1305.26 | 0.121193 | 381.263ms | 4390 | 80 | 1208.86 | 3207.5 | 2.31715 | 1(Win) |
| jsonifier (two-stage) | 1211.18 | 0.266206 | 410.966ms | 4390 | 30 | 2540.23 | 3456.67 | 2.49217 | 2(Loss) |
| glaze | 1111.8 | 0.625991 | 442.257ms | 4390 | 320 | 177812 | 3765.62 | 2.72168 | 3(Loss) |
| simdjson (ondemand) | 567.55 | 0.257403 | 842.927ms | 4390 | 30 | 10816.1 | 7376.67 | 5.33806 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6797.92 | 0.264728 | 66.9608ms | 4390 | 4890 | 12998.3 | 615.869 | 0.434111 | 1(Win) |
| glaze | 3232.92 | 0.338491 | 135.299ms | 4390 | 2560 | 49189.5 | 1295 | 0.926404 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7418.69 | 0.412191 | 61.2666ms | 4390 | 4890 | 26459.4 | 564.335 | 0.396334 | 1(Win) |
| glaze | 3977.8 | 0.759752 | 114.626ms | 4390 | 40 | 2557.69 | 1052.5 | 0.741452 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2363.02 | 0.74961 | 476.537ms | 11521 | 640 | 777496 | 4649.69 | 1.28035 | 1(Win) |
| jsonifier | 2088.84 | 0.724678 | 555.964ms | 11521 | 160 | 232478 | 5260 | 1.44857 | 2(Loss) |
| glaze | 1823.24 | 1.05076 | 632.962ms | 11521 | 320 | 1.28307e+06 | 6026.25 | 1.66125 | 3(Loss) |
| simdjson (ondemand) | 1208.79 | 0.591573 | 921.013ms | 11521 | 4890 | 1.41385e+07 | 9089.47 | 2.49732 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2777.09 | 0.392131 | 465.829ms | 11521 | 640 | 154043 | 3956.41 | 1.08927 | 1(Win) |
| jsonifier | 2262.36 | 1.20661 | 542.264ms | 11521 | 2560 | 8.79088e+06 | 4856.56 | 1.33743 | 2(Loss) |
| glaze | 2020.63 | 1.49009 | 579.461ms | 11521 | 4890 | 3.21025e+07 | 5437.55 | 1.49737 | 3(Loss) |
| simdjson (ondemand) | 1320.29 | 0.321917 | 897.521ms | 11521 | 4890 | 3.50943e+06 | 8321.86 | 2.29478 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15967 | 0.394459 | 77.357ms | 11521 | 160 | 1178.85 | 688.125 | 0.18637 | 1(Win) |
| glaze | 5118.3 | 0.57957 | 230.548ms | 11521 | 30 | 4643.68 | 2146.67 | 0.583656 | 2(Loss) |
### Google Maps Response Small Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 0.653230%)


----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1985.18 | 0.491333 | 245.454ms | 4669 | 640 | 77728.3 | 2242.97 | 1.51524 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 1306.74 | 0.220103 | 365.75ms | 4669 | 40 | 2250 | 3407.5 | 2.31544 | 2(Tie) |
| glaze STATISTICAL TIE | 1295.51 | 0.479705 | 371.055ms | 4669 | 640 | 173979 | 3437.03 | 2.33057 | 2(Tie) |
| simdjson (ondemand) | 655.171 | 0.666535 | 713.616ms | 4669 | 80 | 164163 | 6796.25 | 4.62316 | 4(Loss) |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2277.23 | 0.80245 | 234.208ms | 4669 | 320 | 78780.5 | 1955.31 | 1.31941 | 1(Win) |
| glaze | 1606.57 | 0.67068 | 321.96ms | 4669 | 320 | 110568 | 2771.56 | 1.8712 | 2(Loss) |
| jsonifier (two-stage) | 1452.31 | 1.00999 | 349.596ms | 4669 | 640 | 613674 | 3065.94 | 2.0778 | 3(Loss) |
| simdjson (ondemand) | 708.192 | 0.406342 | 650.492ms | 4669 | 4890 | 3.19181e+06 | 6287.42 | 4.27901 | 4(Loss) |
### Instruments Small Test (Minified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 0.574967%)

### Instruments Small Test (Minified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 0.839457%)


----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2460.4 | 0.188182 | 394.656ms | 9249 | 40 | 1820.51 | 3585 | 1.22797 | 1(Win) |
| jsonifier | 1943.38 | 0.69617 | 494.909ms | 9249 | 80 | 79871.8 | 4538.75 | 1.55838 | 2(Loss) |
| glaze | 1808.68 | 0.955647 | 487.868ms | 9249 | 4890 | 1.06212e+07 | 4876.79 | 1.67183 | 3(Loss) |
| simdjson (ondemand) | 1222.79 | 0.631453 | 742.84ms | 9249 | 2560 | 5.31138e+06 | 7213.44 | 2.47798 | 4(Loss) |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2614.7 | 0.621867 | 384.187ms | 9249 | 320 | 140828 | 3373.44 | 1.15483 | 1(Win) |
| glaze | 2291.61 | 0.272859 | 433.374ms | 9249 | 320 | 35296.9 | 3849.06 | 1.31667 | 2(Loss) |
| jsonifier | 2063.36 | 0.438048 | 481.105ms | 9249 | 640 | 224421 | 4274.84 | 1.46531 | 3(Loss) |
| simdjson (ondemand) | 1344.14 | 0.531152 | 674.163ms | 9249 | 4890 | 5.94086e+06 | 6562.23 | 2.25455 | 4(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9156.26 | 0.928916 | 92.8633ms | 9249 | 30 | 2402.3 | 963.333 | 0.322251 | 1(Win) |
| glaze | 3789.45 | 0.874118 | 253.684ms | 9249 | 640 | 264946 | 2327.66 | 0.793884 | 2(Loss) |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11629.9 | 0.363816 | 81.8058ms | 9249 | 320 | 2436.42 | 758.438 | 0.25497 | 1(Win) |
| glaze | 4435.21 | 1.64374 | 200.955ms | 9249 | 1280 | 1.36785e+06 | 1988.75 | 0.67268 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 400.248 | 0.343386 | 1051.91ms | 4604 | 80 | 113519 | 10970 | 7.57299 | 1(Win) |
| jsonifier (two-stage) | 392.291 | 0.446696 | 1164.18ms | 4604 | 160 | 399943 | 11192.5 | 7.73092 | 2(Loss) |
| glaze | 280.759 | 0.370032 | 1603.14ms | 4604 | 320 | 1.0716e+06 | 15638.8 | 10.8124 | 3(Loss) |
| simdjson (ondemand) | 38.6773 | 0.240392 | 5867.27ms | 4604 | 2560 | 1.9065e+08 | 113522 | 78.566 | 4(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 523.327 | 0.144006 | 1010.62ms | 4604 | 30 | 4379.31 | 8390 | 5.78564 | 1(Win) |
| jsonifier (two-stage) | 486.057 | 0.162153 | 1101.8ms | 4604 | 30 | 6436.78 | 9033.33 | 6.24122 | 2(Loss) |
| glaze | 321.749 | 0.237088 | 1520.53ms | 4604 | 640 | 669940 | 13646.4 | 9.43224 | 3(Loss) |
| simdjson (ondemand) | 39.2734 | 0.734085 | 5880.89ms | 4604 | 160 | 1.07767e+08 | 111799 | 77.3707 | 4(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1314.09 | 0.165765 | 351.867ms | 4604 | 80 | 2454.11 | 3341.25 | 2.2987 | 1(Win) |
| glaze | 913.306 | 0.800042 | 492.676ms | 4604 | 40 | 59173.1 | 4807.5 | 3.30765 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1357.25 | 0.236094 | 337.833ms | 4604 | 40 | 2333.33 | 3235 | 2.22199 | 1(Win) |
| glaze | 910.612 | 0.23406 | 499.282ms | 4604 | 640 | 81515 | 4821.72 | 3.3191 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1903.98 | 0.363542 | 1276.36ms | 24579 | 80 | 160252 | 12311.2 | 1.59217 | 1(Win) |
| jsonifier | 1712.36 | 0.638434 | 1377.49ms | 24579 | 4890 | 3.7349e+07 | 13688.9 | 1.77185 | 2(Loss) |
| glaze | 1241.46 | 0.247144 | 1967.68ms | 24579 | 80 | 174201 | 18881.2 | 2.4447 | 3(Loss) |
| simdjson (ondemand) | 200.036 | 0.458342 | 5952.51ms | 24579 | 1280 | 3.69234e+08 | 117181 | 15.1908 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2314.53 | 0.284305 | 1189.02ms | 24579 | 80 | 66322.8 | 10127.5 | 1.30949 | 1(Win) |
| jsonifier | 1993.39 | 1.65314 | 1315.69ms | 24579 | 320 | 1.20925e+07 | 11759.1 | 1.52165 | 2(Loss) |
| glaze | 1333.96 | 0.150467 | 1925.33ms | 24579 | 4890 | 3.41852e+06 | 17572.1 | 2.27556 | 3(Loss) |
| simdjson (ondemand) | 203.041 | 0.56333 | 5953.22ms | 24579 | 640 | 2.70686e+08 | 115446 | 14.9655 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6067.72 | 0.26679 | 400.577ms | 24579 | 1280 | 135965 | 3863.12 | 0.498116 | 1(Win) |
| glaze | 2872.15 | 0.377142 | 845.96ms | 24579 | 640 | 606321 | 8161.25 | 1.05517 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6364.26 | 0.338078 | 383.668ms | 24579 | 160 | 24807.8 | 3683.12 | 0.474487 | 1(Win) |
| glaze | 3343.15 | 0.616164 | 702.559ms | 24579 | 4890 | 9.12678e+06 | 7011.45 | 0.904657 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 462.059 | 0.122026 | 993.636ms | 4604 | 40 | 5378.21 | 9502.5 | 6.5598 | 1(Win) |
| jsonifier (two-stage) | 421.105 | 0.210392 | 1097.64ms | 4604 | 30 | 14436.8 | 10426.7 | 7.19644 | 2(Loss) |
| glaze | 276.143 | 0.507396 | 1609.94ms | 4604 | 4890 | 3.18278e+07 | 15900.2 | 10.9915 | 3(Loss) |
| simdjson (ondemand) | 249.737 | 0.557244 | 1781.24ms | 4604 | 1280 | 1.22858e+07 | 17581.3 | 12.153 | 4(Loss) |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 574.701 | 0.146714 | 927.002ms | 4604 | 40 | 5025.64 | 7640 | 5.27115 | 1(Win) |
| jsonifier (two-stage) | 490.584 | 0.546036 | 1034.99ms | 4604 | 4890 | 1.16787e+07 | 8949.98 | 6.17934 | 2(Loss) |
| glaze | 326.994 | 0.141072 | 1521.79ms | 4604 | 40 | 14352.6 | 13427.5 | 9.27728 | 3(Loss) |
| simdjson (ondemand) | 262.17 | 1.09014 | 1794.94ms | 4604 | 1280 | 4.26655e+07 | 16747.6 | 11.5776 | 4(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1365.7 | 0.175847 | 335.881ms | 4604 | 80 | 2556.96 | 3215 | 2.21096 | 1(Win) |
| glaze | 905.769 | 0.43062 | 500.735ms | 4604 | 40 | 17429.5 | 4847.5 | 3.34142 | 2(Loss) |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1434.14 | 0.327417 | 318.947ms | 4604 | 320 | 32154.3 | 3061.56 | 2.10554 | 1(Win) |
| glaze | 1015.67 | 0.244886 | 448.935ms | 4604 | 640 | 71725.1 | 4322.97 | 2.97922 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1937.16 | 0.620809 | 1215.72ms | 24579 | 4890 | 2.75945e+07 | 12100.4 | 1.56573 | 1(Win) |
| jsonifier | 1894.94 | 0.117246 | 1294.47ms | 24579 | 30 | 6310.34 | 12370 | 1.6011 | 2(Loss) |
| simdjson (ondemand) | 1258.21 | 0.27376 | 1921.16ms | 24579 | 30 | 78034.5 | 18630 | 2.41269 | 3(Loss) |
| glaze | 1236.67 | 0.221883 | 1969.26ms | 24579 | 160 | 283000 | 18954.4 | 2.45528 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2423.95 | 0.172751 | 1126.81ms | 24579 | 320 | 89304 | 9670.31 | 1.25046 | 1(Win) |
| jsonifier | 2195.48 | 0.107059 | 1235.1ms | 24579 | 30 | 3919.54 | 10676.7 | 1.38038 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 1355.72 | 0.231928 | 1883.47ms | 24579 | 320 | 514571 | 17290 | 2.23757 | 3(Tie) |
| glaze STATISTICAL TIE | 1332.36 | 0.89359 | 1910.97ms | 24579 | 640 | 1.58177e+07 | 17593.1 | 2.27797 | 3(Tie) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5434.26 | 0.252817 | 441.094ms | 24579 | 1280 | 152220 | 4313.44 | 0.556286 | 1(Win) |
| glaze | 2840.61 | 0.235279 | 832.302ms | 24579 | 1280 | 482483 | 8251.88 | 1.06693 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5807.42 | 0.500073 | 414.136ms | 24579 | 4890 | 1.99222e+06 | 4036.28 | 0.520493 | 1(Win) |
| glaze | 3302.52 | 0.393064 | 720.371ms | 24579 | 4890 | 3.80605e+06 | 7097.73 | 0.915282 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 706.138 | 0.31348 | 169.927ms | 1181 | 40 | 1000 | 1595 | 4.22858 | 1(Win) |
| jsonifier (two-stage) | 633.934 | 0.517929 | 201.755ms | 1181 | 30 | 2540.23 | 1776.67 | 4.77163 | 2(Loss) |
| glaze | 277.925 | 0.364162 | 419.864ms | 1181 | 40 | 8711.54 | 4052.5 | 10.8631 | 3(Loss) |
| simdjson (ondemand) | 242.213 | 0.199672 | 506.791ms | 1181 | 30 | 2586.21 | 4650 | 12.5199 | 4(Loss) |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 879.055 | 0.369795 | 153.403ms | 1181 | 80 | 1795.89 | 1281.25 | 3.40976 | 1(Win) |
| jsonifier (two-stage) | 766.183 | 0.578886 | 180.669ms | 1181 | 30 | 2172.41 | 1470 | 3.92275 | 2(Loss) |
| glaze | 616.582 | 0.449549 | 210.386ms | 1181 | 30 | 2022.99 | 1826.67 | 4.85064 | 3(Loss) |
| simdjson (ondemand) | 396.93 | 0.191958 | 317.065ms | 1181 | 80 | 2373.42 | 2837.5 | 7.5317 | 4(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1711.36 | 0.419716 | 69.8219ms | 1181 | 320 | 2441.61 | 658.125 | 1.72924 | 1(Win) |
| glaze | 1111.47 | 0.622937 | 99.4396ms | 1181 | 30 | 1195.4 | 1013.33 | 2.68002 | 2(Loss) |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1877.15 | 0.295553 | 66.0715ms | 1181 | 160 | 503.145 | 600 | 1.56659 | 1(Win) |
| glaze | 1308.21 | 0.317289 | 90.2318ms | 1181 | 320 | 2387.83 | 860.938 | 2.26108 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1249.54 | 0.159883 | 209.538ms | 2496 | 160 | 1484.28 | 1905 | 2.41472 | 1(Win) |
| jsonifier | 1033.82 | 0.189663 | 247.025ms | 2496 | 40 | 762.821 | 2302.5 | 2.91939 | 2(Loss) |
| glaze | 537.5 | 0.332487 | 454.824ms | 2496 | 640 | 138759 | 4428.59 | 5.63024 | 3(Loss) |
| simdjson (ondemand) | 489.788 | 0.336007 | 515.508ms | 2496 | 30 | 8000 | 4860 | 6.16899 | 4(Loss) |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1509.1 | 0.424803 | 189.232ms | 2496 | 640 | 28734.7 | 1577.34 | 1.99434 | 1(Win) |
| jsonifier | 1216.8 | 1.34831 | 231.709ms | 2496 | 80 | 55656.6 | 1956.25 | 2.47503 | 2(Loss) |
| glaze | 1154.12 | 0.375863 | 243.796ms | 2496 | 40 | 2403.85 | 2062.5 | 2.6042 | 3(Loss) |
| simdjson (ondemand) | 766.625 | 0.198062 | 328.014ms | 2496 | 40 | 1512.82 | 3105 | 3.91483 | 4(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3294.63 | 0.92549 | 72.9694ms | 2496 | 40 | 1788.46 | 722.5 | 0.894491 | 1(Win) |
| glaze | 1907.6 | 0.739158 | 131.6ms | 2507 | 30 | 2574.71 | 1253.33 | 1.57167 | 2(Loss) |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3756.01 | 0.591716 | 69.5543ms | 2496 | 160 | 2250 | 633.75 | 0.787235 | 1(Win) |
| glaze | 2324.05 | 0.49498 | 113.6ms | 2507 | 80 | 2074.37 | 1028.75 | 1.28012 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1025.44 | 0.150859 | 492.561ms | 4926 | 80 | 3821.2 | 4581.25 | 2.94886 | 1(Win) |
| jsonifier (two-stage) | 914.806 | 1.11801 | 517.393ms | 4926 | 4890 | 1.61188e+07 | 5135.3 | 3.31013 | 2(Loss) |
| glaze | 780.209 | 0.859889 | 604.035ms | 4926 | 4890 | 1.31087e+07 | 6021.21 | 3.88094 | 3(Loss) |
| simdjson (ondemand) | 497.587 | 1.10034 | 960.126ms | 4926 | 2560 | 2.76276e+07 | 9441.17 | 6.0944 | 4(Loss) |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1271.97 | 0.180505 | 483.023ms | 4926 | 30 | 1333.33 | 3693.33 | 2.37077 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 1132.14 | 0.377294 | 509.11ms | 4926 | 2560 | 627464 | 4149.49 | 2.67259 | 2(Tie) |
| glaze STATISTICAL TIE | 1121.49 | 0.509605 | 508.237ms | 4926 | 4890 | 2.22829e+06 | 4188.88 | 2.69483 | 2(Tie) |
| simdjson (ondemand) | 593.656 | 0.157221 | 871.109ms | 4926 | 30 | 4643.68 | 7913.33 | 5.10392 | 4(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6224.83 | 0.36931 | 85.0383ms | 4926 | 320 | 2485.8 | 754.688 | 0.476783 | 1(Win) |
| glaze | 3120.25 | 0.24797 | 160.193ms | 4926 | 2560 | 35682 | 1505.59 | 0.960376 | 2(Loss) |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7156 | 0.317007 | 70.3558ms | 4926 | 2560 | 11087.3 | 656.484 | 0.41323 | 1(Win) |
| glaze | 3544.77 | 0.831782 | 133.615ms | 4926 | 4890 | 594211 | 1325.28 | 0.837546 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 1635.28 | 0.824173 | 553.424ms | 9463 | 4890 | 1.01163e+07 | 5518.71 | 1.85169 | 1(Win) |
| jsonifier | 1587.91 | 0.208077 | 630.69ms | 9463 | 30 | 4195.4 | 5683.33 | 1.90834 | 2(Loss) |
| glaze | 1363.11 | 0.731584 | 698.442ms | 9463 | 160 | 375358 | 6620.62 | 2.22256 | 3(Loss) |
| simdjson (ondemand) | 930.366 | 0.93935 | 989.765ms | 9463 | 1280 | 1.06271e+07 | 9700.08 | 3.25902 | 4(Loss) |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2077.01 | 0.201012 | 550.758ms | 9463 | 40 | 3051.28 | 4345 | 1.45827 | 1(Win) |
| glaze | 1847.89 | 0.642114 | 601.699ms | 9463 | 160 | 157344 | 4883.75 | 1.63713 | 2(Loss) |
| jsonifier | 1785.84 | 0.671816 | 627.978ms | 9463 | 320 | 368828 | 5053.44 | 1.69523 | 3(Loss) |
| simdjson (ondemand) | 1189.01 | 0.146114 | 890.868ms | 9463 | 30 | 3689.66 | 7590 | 2.55037 | 4(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11468.9 | 0.340324 | 86.2406ms | 9463 | 160 | 1147.41 | 786.875 | 0.259739 | 1(Win) |
| glaze | 4123.77 | 0.318751 | 242.078ms | 9463 | 320 | 15571.2 | 2188.44 | 0.729684 | 2(Loss) |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12592.3 | 0.631528 | 75.4378ms | 9463 | 2560 | 52441.5 | 716.68 | 0.235278 | 1(Win) |
| glaze | 5536.58 | 0.629031 | 184.43ms | 9463 | 40 | 4205.13 | 1630 | 0.541126 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 4852.88 | 0.357656 | 60.1521ms | 2821 | 640 | 2516.04 | 554.375 | 0.608517 | 1(Win) |
| jsonifier | 4673.09 | 0.571701 | 61.0763ms | 2821 | 1280 | 13865.8 | 575.703 | 0.629375 | 2(Loss) |
| glaze | 2703.83 | 1.64736 | 104.763ms | 2821 | 80 | 21493.7 | 995 | 1.10519 | 3(Loss) |
| simdjson (ondemand) | 2041.99 | 0.324475 | 137.685ms | 2821 | 80 | 1462.03 | 1317.5 | 1.46667 | 4(Loss) |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5340.58 | 0.380732 | 57.4203ms | 2821 | 320 | 1177.12 | 503.75 | 0.548384 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 5294.59 | 0.577998 | 55.9369ms | 2821 | 160 | 1380.11 | 508.125 | 0.552805 | 1(Tie) |
| glaze | 2834.59 | 0.226813 | 98.8143ms | 2821 | 2560 | 11863.2 | 949.102 | 1.03412 | 3(Loss) |
| simdjson (ondemand) | 2087.73 | 0.229704 | 136.775ms | 2821 | 2560 | 22430.3 | 1288.63 | 1.43542 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 6119.75 | 0.344235 | 68.9786ms | 4147 | 1280 | 6334.64 | 646.25 | 0.484349 | 1(Win) |
| jsonifier | 6033.68 | 0.299954 | 69.6545ms | 4147 | 640 | 2473.96 | 655.469 | 0.489531 | 2(Loss) |
| glaze | 3408.47 | 0.236081 | 119.733ms | 4147 | 320 | 2401.16 | 1160.31 | 0.878954 | 3(Loss) |
| simdjson (ondemand) | 2808.54 | 0.149721 | 148.256ms | 4147 | 2560 | 11379.2 | 1408.16 | 1.06913 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6774.97 | 0.936487 | 64.7023ms | 4147 | 80 | 2390.82 | 583.75 | 0.430609 | 1(Win) |
| jsonifier (two-stage) | 6240.45 | 0.591716 | 66.4116ms | 4147 | 160 | 2250 | 633.75 | 0.47048 | 2(Loss) |
| glaze | 3635.63 | 0.615922 | 116.083ms | 4147 | 320 | 14365.1 | 1087.81 | 0.811204 | 3(Loss) |
| simdjson (ondemand) | 2929.55 | 0.593067 | 145.519ms | 4147 | 40 | 2564.1 | 1350 | 1.02657 | 4(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1463.12 | 0.414001 | 192.499ms | 2821 | 640 | 37087.6 | 1838.75 | 2.0554 | 1(Win) |
| glaze | 1445.19 | 0.268729 | 193.175ms | 2821 | 640 | 16016.3 | 1861.56 | 2.07925 | 2(Loss) |
| jsonifier (two-stage) | 1216.65 | 0.762896 | 228.506ms | 2821 | 160 | 45533 | 2211.25 | 2.47576 | 3(Loss) |
| simdjson (ondemand) | 976.41 | 0.392042 | 292.255ms | 2821 | 320 | 37338.5 | 2755.31 | 3.09253 | 4(Loss) |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2007.7 | 0.678894 | 159.191ms | 2821 | 30 | 2482.76 | 1340 | 1.49936 | 1(Win) |
| glaze | 1820.86 | 0.340012 | 159.368ms | 2821 | 80 | 2018.99 | 1477.5 | 1.64063 | 2(Loss) |
| jsonifier (two-stage) | 1654.31 | 0.227999 | 189.266ms | 2821 | 160 | 2199.69 | 1626.25 | 1.81582 | 3(Loss) |
| simdjson (ondemand) | 1104.85 | 0.839241 | 268.182ms | 2821 | 160 | 66817.6 | 2435 | 2.72288 | 4(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5373.16 | 0.280146 | 52.845ms | 2821 | 4890 | 9621.12 | 500.695 | 0.545933 | 1(Win) |
| glaze | 4228.51 | 0.36386 | 69.0504ms | 2819 | 1280 | 6850.05 | 635.781 | 0.692876 | 2(Loss) |
### Twitter Small Test (Minified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 0.385379%)


----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1771.51 | 0.464491 | 216.734ms | 4147 | 40 | 4301.28 | 2232.5 | 1.69167 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1747.37 | 0.539394 | 238.697ms | 4147 | 30 | 4471.26 | 2263.33 | 1.72048 | 1(Tie) |
| jsonifier | 1512.39 | 0.400372 | 274.13ms | 4147 | 40 | 4384.62 | 2615 | 1.99987 | 3(Loss) |
| simdjson (ondemand) | 1271.67 | 0.378359 | 303.944ms | 4147 | 40 | 5538.46 | 3110 | 2.37346 | 4(Loss) |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2387.29 | 0.157755 | 185.834ms | 4147 | 4890 | 33399.3 | 1656.65 | 1.25453 | 1(Win) |
| jsonifier (two-stage) | 2272.92 | 0.522826 | 202.389ms | 4147 | 30 | 2482.76 | 1740 | 1.32662 | 2(Loss) |
| jsonifier | 1869.92 | 0.318975 | 236.235ms | 4147 | 40 | 1820.51 | 2115 | 1.61057 | 3(Loss) |
| simdjson (ondemand) | 1588.31 | 0.352435 | 274.538ms | 4147 | 30 | 2310.34 | 2490 | 1.89471 | 4(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6833.5 | 0.279617 | 63.5176ms | 4147 | 640 | 1676.06 | 578.75 | 0.429148 | 1(Win) |
| glaze | 3703.03 | 1.84898 | 122.608ms | 4145 | 40 | 15583.3 | 1067.5 | 0.802913 | 2(Loss) |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7887.59 | 0.269857 | 53.8561ms | 4147 | 640 | 1171.73 | 501.406 | 0.371115 | 1(Win) |
| glaze | 5433.65 | 1.09916 | 86.374ms | 4145 | 40 | 2557.69 | 727.5 | 0.540766 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3249.6 | 0.197587 | 7233.87ms | 466906 | 80 | 5.86418e+06 | 137025 | 0.935149 | 1(Win) |
| glaze | 1929.49 | 0.471594 | 5927.05ms | 466906 | 320 | 3.79019e+08 | 230774 | 1.57501 | 2(Loss) |
| simdjson (ondemand) | 1117.58 | 0.405301 | 5051.36ms | 466906 | 640 | 1.66893e+09 | 398429 | 2.71888 | 3(Loss) |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3144.92 | 0.392411 | 7236.32ms | 466906 | 1280 | 3.95124e+08 | 141586 | 0.966223 | 1(Win) |
| glaze | 1954.88 | 0.268166 | 5932.1ms | 466906 | 320 | 1.19392e+08 | 227777 | 1.55453 | 2(Loss) |
| simdjson (ondemand) | 1131.01 | 0.543514 | 5062.13ms | 466906 | 80 | 3.663e+08 | 393698 | 2.68664 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2368.74 | 0.421714 | 7173.22ms | 699405 | 640 | 9.02485e+08 | 281587 | 1.28296 | 1(Win) |
| jsonifier | 2260.27 | 0.277096 | 7648.13ms | 699405 | 640 | 4.27934e+08 | 295100 | 1.34416 | 2(Loss) |
| simdjson (ondemand) | 881.891 | 0.691482 | 5261.91ms | 767297 | 160 | 5.2672e+09 | 829753 | 3.4453 | 3(Loss) |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3333.26 | 0.696087 | 5175.73ms | 699405 | 160 | 3.10432e+08 | 200106 | 0.911702 | 1(Win) |
| glaze | 2377.95 | 0.432397 | 7165.61ms | 699405 | 640 | 9.41449e+08 | 280495 | 1.27797 | 2(Loss) |
| simdjson (ondemand) | 851.04 | 1.02425 | 5396.61ms | 767297 | 160 | 1.24095e+10 | 859832 | 3.57029 | 3(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2864.69 | 0.346888 | 5366.01ms | 631514 | 1280 | 6.80768e+08 | 210235 | 1.06078 | 1(Win) |
| glaze | 2320.53 | 0.399968 | 6692.95ms | 631514 | 640 | 6.8964e+08 | 259535 | 1.30962 | 2(Loss) |
