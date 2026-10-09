# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Oct 15, 2026)
#### Using the following commits:
----
| Jsonifier: [3b56371](https://github.com/nihilai-collective/jsonifier/commit/3b56371)  
| Glaze: [e1ab988](https://github.com/stephenberry/glaze/commit/e1ab988)  
| Simdjson: [9c00353](https://github.com/simdjson/simdjson/commit/9c00353)  

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

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. The first epoch is kept only as an initial fallback; every later epoch is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result, whether or not it met the convergence thresholds. A result counts as converged only if that retained epoch has RSE <= 5% AND mean shift <= 2.5%; non-converged results are still included in the rankings and in win/tie/loss tallying, so a result that did not meet these thresholds should be read with its reduced statistical confidence in mind. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" performs fused scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through structural indexing/stage-1 + stage-2. The 'partial' tests require stage-1 + stage-2, so both jsonifier rows take the two-stage path there)

Each test is run twice. In the standard run, every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. In the run labelled "(Reused)", the object or string is created once and held across iterations; it is cleared (keeping its capacity) outside the timed region before each iteration, so only the parse or serialize work is measured. Parser instances are reused in both.

The "Small" tests use cut-down copies of the large documents, truncated by `GenerateSmallJson.py` so that each minified document is at most 5 KiB (arrays and numerically-keyed objects are shortened to as many leading entries as fit; the document structure is otherwise unchanged). They exercise per-call overhead (setup, dispatch, small allocations) rather than bulk throughput, which is where the standard and "(Reused)" runs differ most.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

Every test whose name contains "Reverse" parses keys in the reverse of their order in the JSON document. This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows. In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

`simdjson (ondemand)` extracts each field with an individual `find_field` lookup (`find_field_unordered` for the reverse-order tests) on MSVC/Windows, rather than the `object::for_each` API used on the other platforms, because instantiating `for_each` across these test structures drives MSVC compile times to intractable levels.

`simdjson (ondemand)` results include this harness's field-mapping layer (per-field lookups, string copies and `unescaped_key()` for maps, in `include/common.hpp`), since materializing into the shared test structs is what these tests measure; hand-tuned glue written by a simdjson specialist could perform differently.

`Results.csv` additionally carries `jsonifier (combined)` and `simdjson (combined)` summary rows. Each is a best-of-variants tally: per test, only the better-ranked of that library's two variants counts, and a test counts as a win when that position is 1 and no other library shares it, so two variants of the same library tying for first count as one win. These rows are not independent results and should not be summed with the per-variant rows.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ae63a25](https://github.com/nihilai-collective/benchmarksuite/commit/ae63a25).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 545.549 | 0.179804 | 165.432ms | 905 | 1280 | 10357.1 | 1582.03 | 0.546177 | 5.50702 | 1(Win) | true |
| glaze | 451.582 | 0.61818 | 193.539ms | 905 | 4890 | 682596 | 1911.23 | 0.896473 | 6.66099 | 2(Loss) | true |
| jsonifier (two-stage) | 129.198 | 0.595539 | 670.06ms | 905 | 2560 | 4.05181e+06 | 6680.27 | 0.284407 | 23.4601 | 3(Loss) | true |
| simdjson (ondemand) | 122.178 | 0.231753 | 713.281ms | 905 | 4890 | 1.31061e+06 | 7064.09 | 0.334145 | 24.8044 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 653.845 | 0.485237 | 138.358ms | 905 | 40 | 1641.03 | 1320 | 0.75188 | 4.60992 | 1(Win) | true |
| glaze | 526.667 | 0.29783 | 170.977ms | 905 | 1280 | 30491 | 1638.75 | 0.417774 | 5.69898 | 2(Loss) | true |
| jsonifier (two-stage) | 136.996 | 0.293873 | 638.76ms | 905 | 160 | 54842.8 | 6300 | 0.218731 | 22.1259 | 3(Loss) | true |
| simdjson (ondemand) | 127.837 | 0.271023 | 680.834ms | 905 | 4890 | 1.63721e+06 | 6751.37 | 0.511688 | 23.7077 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1145.04 | 0.744225 | 80.0035ms | 905 | 80 | 2517.41 | 753.75 | 0.165563 | 2.58131 | 1(Win) | true |
| glaze | 24.4341 | 0.45316 | 1021.53ms | 905 | 40 | 1.02487e+06 | 35322.5 | 0.434558 | 124.089 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1761.24 | 0.320465 | 58.2504ms | 905 | 2560 | 6313.4 | 490.039 | 0.617581 | 1.66064 | 1(Win) | true |
| glaze | 267.258 | 0.11646 | 345.966ms | 905 | 320 | 4526.25 | 3229.38 | 0.0966744 | 11.2188 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 546.552 | 0.242787 | 330.561ms | 1811 | 80 | 4708.86 | 3160 | 0.0790514 | 5.5263 | 1(Win) | true |
| glaze | 424.35 | 0.319628 | 403.123ms | 1811 | 40 | 6769.23 | 4070 | 0.488998 | 7.11745 | 2(Loss) | true |
| simdjson (ondemand) | 168.642 | 0.268443 | 1048.29ms | 1811 | 160 | 120929 | 10241.2 | 0.024417 | 17.99 | 3(Loss) | true |
| jsonifier (two-stage) | 76.588 | 0.483477 | 2226.17ms | 1811 | 2560 | 3.04304e+07 | 22550.6 | 1.4539 | 39.643 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 691.187 | 0.050025 | 260.694ms | 1811 | 80 | 125 | 2498.75 | 0.150301 | 4.33923 | 1(Win) | true |
| glaze | 540.142 | 0.0781861 | 326.139ms | 1811 | 40 | 250 | 3197.5 | 0.23511 | 5.54884 | 2(Loss) | true |
| simdjson (ondemand) | 176.272 | 0.396482 | 981.266ms | 1811 | 2560 | 3.86328e+06 | 9797.93 | 0.229768 | 17.2008 | 3(Loss) | true |
| jsonifier (two-stage) | 83.7282 | 0.345419 | 2108.52ms | 1811 | 40 | 203071 | 20627.5 | 0.133495 | 36.2602 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 203.362 | 0.264845 | 852.51ms | 1811 | 4890 | 2.47393e+06 | 8492.74 | 0.24952 | 14.9118 | 1(Win) | true |
| glaze | 138.431 | 0.591368 | 1241.68ms | 1798 | 2560 | 1.37362e+07 | 12386.7 | 0.209275 | 21.9142 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 791.342 | 0.444762 | 233.667ms | 1811 | 80 | 7537.97 | 2182.5 | 0.908059 | 3.78331 | 1(Win) | true |
| glaze | 315.276 | 0.115612 | 576.903ms | 1798 | 80 | 3162.97 | 5438.75 | 0.0689022 | 9.56275 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1513.6 | 0.568805 | 253.639ms | 3862 | 30 | 5747.13 | 2433.33 | 0.137174 | 1.98925 | 1(Win) | true |
| glaze | 1037.49 | 0.350896 | 363.351ms | 3862 | 30 | 4655.17 | 3550 | 0 | 2.91241 | 2(Loss) | true |
| jsonifier (two-stage) | 541.295 | 0.221887 | 687.173ms | 3862 | 640 | 145882 | 6804.22 | 0.121856 | 5.59782 | 3(Loss) | true |
| simdjson (ondemand) | 374.583 | 0.15647 | 1004.51ms | 3862 | 320 | 75742.9 | 9832.5 | 0.0763359 | 8.09692 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1983.71 | 0.495612 | 191.12ms | 3862 | 30 | 2540.23 | 1856.67 | 0 | 1.51259 | 1(Win) | true |
| glaze | 1294.58 | 0.28001 | 296.107ms | 3862 | 40 | 2538.46 | 2845 | 0.292056 | 2.322 | 2(Loss) | true |
| jsonifier (two-stage) | 591.424 | 0.539523 | 624.262ms | 3862 | 1280 | 1.44497e+06 | 6227.5 | 0.122792 | 5.11449 | 3(Loss) | true |
| simdjson (ondemand) | 404.402 | 0.315467 | 932.002ms | 3862 | 40 | 33019.2 | 9107.5 | 0.266055 | 7.50486 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 517.674 | 0.176303 | 721.664ms | 3862 | 320 | 50347.9 | 7114.69 | 0.144737 | 5.85092 | 1(Win) | true |
| glaze | 375.826 | 0.129443 | 1005.78ms | 3862 | 30 | 4827.59 | 9800 | 0.102145 | 8.08092 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3831.56 | 0.401933 | 110.817ms | 3862 | 160 | 2388.36 | 961.25 | 0.522876 | 0.768889 | 1(Win) | true |
| glaze | 1019.87 | 0.222523 | 393.109ms | 3862 | 2560 | 165319 | 3611.33 | 0.051893 | 2.95286 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 899.069 | 0.543545 | 1022.59ms | 9578 | 2560 | 7.80683e+06 | 10159.7 | 0.0488533 | 3.37226 | 1(Win) | true |
| glaze | 728.953 | 0.486446 | 1252.4ms | 9578 | 4890 | 1.81689e+07 | 12530.7 | 0.241384 | 4.1617 | 2(Loss) | true |
| jsonifier (two-stage) | 659.69 | 0.290367 | 1393.18ms | 9578 | 4890 | 7.90448e+06 | 13846.3 | 0.155122 | 4.59882 | 3(Loss) | true |
| simdjson (ondemand) | 606.611 | 0.274812 | 1504.93ms | 9578 | 4890 | 8.37358e+06 | 15057.9 | 0.301204 | 5.00252 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1593.51 | 0.401126 | 787.879ms | 9578 | 4890 | 2.5853e+06 | 5732.19 | 0.0149787 | 1.89901 | 1(Win) | true |
| glaze | 1146.99 | 0.28551 | 1020.8ms | 9578 | 4890 | 2.52801e+06 | 7963.68 | 0.120925 | 2.63882 | 2(Loss) | true |
| jsonifier (two-stage) | 1004.32 | 0.0894184 | 1151.74ms | 9578 | 80 | 5291.14 | 9095 | 0.0274801 | 3.01635 | 3(Loss) | true |
| simdjson (ondemand) | 853.074 | 0.554705 | 1306.37ms | 9578 | 80 | 282222 | 10707.5 | 0.0933053 | 3.55172 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1155.31 | 0.351401 | 795.013ms | 9578 | 4890 | 3.77459e+06 | 7906.38 | 0.332709 | 2.62245 | 1(Win) | true |
| glaze | 889.608 | 0.272544 | 1038.98ms | 9578 | 4890 | 3.82943e+06 | 10267.8 | 0.21792 | 3.40758 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7802.92 | 0.488395 | 136.842ms | 9578 | 640 | 20919.8 | 1170.62 | 0.753093 | 0.382116 | 1(Win) | true |
| glaze | 2381.7 | 0.149241 | 412.251ms | 9578 | 4890 | 160199 | 3835.19 | 0.00710312 | 1.25963 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1495.33 | 0.288305 | 250.473ms | 3873 | 2560 | 129827 | 2470.08 | 0.123199 | 2.01625 | 1(Win) | true |
| glaze | 1061.37 | 0.320164 | 365.86ms | 3873 | 30 | 3724.14 | 3480 | 0.0956938 | 2.84209 | 2(Loss) | true |
| jsonifier (two-stage) | 562.699 | 0.226187 | 660.081ms | 3873 | 4890 | 1.07792e+06 | 6564.05 | 0.160133 | 5.38596 | 3(Loss) | true |
| simdjson (ondemand) | 379.12 | 0.293574 | 993.577ms | 3873 | 160 | 130887 | 9742.5 | 0.192086 | 7.99245 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1977.82 | 0.282176 | 190.917ms | 3873 | 80 | 2221.52 | 1867.5 | 0.134048 | 1.51303 | 1(Win) | true |
| glaze | 1269.27 | 0.165081 | 297.736ms | 3873 | 40 | 923.077 | 2910 | 0.342466 | 2.36538 | 2(Loss) | true |
| jsonifier (two-stage) | 636.824 | 0.0685825 | 593.012ms | 3873 | 80 | 1265.82 | 5800 | 0.0862813 | 4.7491 | 3(Loss) | true |
| simdjson (ondemand) | 407.624 | 0.0604905 | 927.429ms | 3873 | 80 | 2403.48 | 9061.25 | 0.0690226 | 7.43652 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 551.555 | 0.195859 | 689.234ms | 3873 | 30 | 5160.92 | 6696.67 | 0 | 5.49138 | 1(Win) | true |
| glaze | 372.041 | 0.183045 | 997.87ms | 3873 | 2560 | 845412 | 9927.89 | 0.0668439 | 8.15108 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4901.8 | 0.393651 | 90.1645ms | 3873 | 1280 | 11262.1 | 753.516 | 0.385096 | 0.599954 | 1(Win) | true |
| glaze | 1036.43 | 0.211504 | 386.412ms | 3873 | 320 | 18180.3 | 3563.75 | 0.0701016 | 2.91816 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 587.536 | 0.797802 | 5128.47ms | 2090234 | 80 | 5.86139e+10 | 3.39282e+06 | 0.340588 | 5.17264 | 1(Win) | true |
| jsonifier (two-stage) | 548.13 | 0.97121 | 5427.31ms | 2090234 | 30 | 3.74257e+10 | 3.63673e+06 | 0.516557 | 5.54446 | 2(Loss) | true |
| glaze | 380.684 | 0.449341 | 7910.93ms | 2090234 | 80 | 4.42896e+10 | 5.23637e+06 | 0.212505 | 7.98375 | 3(Loss) | true |
| simdjson (ondemand) | 363.026 | 0.72806 | 8238.82ms | 2090234 | 30 | 4.79479e+10 | 5.49107e+06 | 0.048904 | 8.37184 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 703.787 | 0.572203 | 5136.81ms | 2090234 | 80 | 2.10135e+10 | 2.8324e+06 | 1.07309 | 4.31808 | 1(Win) | true |
| jsonifier (two-stage) | 647.533 | 0.748278 | 5413.84ms | 2090234 | 40 | 2.12252e+10 | 3.07846e+06 | 0.15098 | 4.69327 | 2(Loss) | true |
| glaze | 426.439 | 0.605569 | 7862.56ms | 2090234 | 30 | 2.40394e+10 | 4.67453e+06 | 0.733689 | 7.12713 | 3(Loss) | true |
| simdjson (ondemand) | 399.031 | 0.315526 | 8309.27ms | 2090234 | 80 | 1.98764e+10 | 4.99561e+06 | 0.121981 | 7.61622 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1338.96 | 0.413815 | 9165.02ms | 2090234 | 160 | 6.07272e+09 | 1.48876e+06 | 1.17359 | 2.26948 | 1(Win) | true |
| glaze | 836.984 | 0.385783 | 7742.7ms | 2090234 | 40 | 3.37678e+09 | 2.38165e+06 | 0.331162 | 3.63091 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1706.1 | 0.128778 | 7432.41ms | 2090234 | 320 | 7.2446e+08 | 1.1684e+06 | 0.129672 | 1.7811 | 1(Win) | true |
| glaze | 1052.49 | 0.697044 | 5835.19ms | 2090234 | 40 | 6.97169e+09 | 1.894e+06 | 0.253811 | 2.88739 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1653.61 | 0.635851 | 5736ms | 6661897 | 80 | 4.77451e+10 | 3.84206e+06 | 0.346912 | 1.83782 | 1(Win) | true |
| jsonifier | 1560.18 | 0.493349 | 6102.86ms | 6661897 | 80 | 3.22884e+10 | 4.07216e+06 | 0.734951 | 1.94795 | 2(Loss) | true |
| simdjson (ondemand) | 1120.68 | 0.392036 | 8574.66ms | 6661897 | 80 | 3.9516e+10 | 5.66912e+06 | 0.168459 | 2.71201 | 3(Loss) | true |
| glaze | 1041.16 | 0.269895 | 9134.26ms | 6661897 | 80 | 2.16992e+10 | 6.10214e+06 | 0.551724 | 2.91911 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1946.66 | 0.449416 | 5739.63ms | 6661897 | 80 | 1.72109e+10 | 3.26368e+06 | 0.103113 | 1.56117 | 1(Win) | true |
| jsonifier | 1800.94 | 0.503142 | 6099.2ms | 6661897 | 80 | 2.5204e+10 | 3.52776e+06 | 1.23738 | 1.68752 | 2(Loss) | true |
| simdjson (ondemand) | 1240.59 | 0.309775 | 8449.86ms | 6661897 | 80 | 2.01338e+10 | 5.12119e+06 | 0.231805 | 2.44987 | 3(Loss) | true |
| glaze | 1138.4 | 0.579945 | 9185.19ms | 6661897 | 30 | 3.14268e+10 | 5.58088e+06 | 0.371808 | 2.66974 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3311.73 | 0.561164 | 6034.71ms | 6661897 | 30 | 3.47687e+09 | 1.91842e+06 | 0.521482 | 0.917639 | 1(Win) | true |
| glaze | 1498.3 | 0.505687 | 6365.37ms | 6661897 | 30 | 1.37939e+10 | 4.24034e+06 | 0.630552 | 2.02845 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5227.88 | 0.268419 | 7880.9ms | 6661897 | 30 | 3.19223e+08 | 1.21527e+06 | 0.527944 | 0.581194 | 1(Win) | true |
| glaze | 3076.13 | 0.154526 | 6427.11ms | 6661897 | 160 | 1.62971e+09 | 2.06535e+06 | 0.210718 | 0.987898 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1513.43 | 0.163888 | 8154.19ms | 500299 | 1280 | 3.41697e+08 | 315260 | 0.207631 | 2.0078 | 1(Win) | true |
| jsonifier (two-stage) | 1231.71 | 0.322521 | 9819.88ms | 500299 | 640 | 9.98937e+08 | 387365 | 0.264864 | 2.46701 | 2(Loss) | true |
| glaze | 868.617 | 0.34657 | 6995.28ms | 500299 | 640 | 2.31934e+09 | 549290 | 0.601994 | 3.49877 | 3(Loss) | true |
| simdjson (ondemand) | 518.473 | 0.334701 | 5781.18ms | 500299 | 160 | 1.51789e+09 | 920244 | 0.0209819 | 5.86149 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1805.93 | 0.210739 | 7700.37ms | 500299 | 640 | 1.98393e+08 | 264197 | 0.156715 | 1.68271 | 1(Win) | true |
| jsonifier (two-stage) | 1433.11 | 0.289841 | 9449.45ms | 500299 | 1280 | 1.19187e+09 | 332927 | 0.21282 | 2.12032 | 2(Loss) | true |
| glaze | 946.947 | 0.486285 | 6893.66ms | 500299 | 320 | 1.92106e+09 | 503853 | 0.206525 | 3.20925 | 3(Loss) | true |
| simdjson (ondemand) | 558.611 | 0.475842 | 5629.45ms | 500299 | 80 | 1.32147e+09 | 854122 | 0.133942 | 5.44052 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7207.9 | 0.236459 | 6607.15ms | 500299 | 2560 | 6.27181e+07 | 66194.3 | 0.126538 | 0.421476 | 1(Win) | true |
| glaze | 4436.4 | 0.311899 | 5496.36ms | 500299 | 1280 | 1.44024e+08 | 107547 | 0.324672 | 0.684852 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7335.26 | 0.267642 | 6578.45ms | 500299 | 80 | 2.42453e+06 | 65045 | 0.314176 | 0.414165 | 1(Win) | true |
| glaze | 4998.01 | 0.20076 | 9556.42ms | 500299 | 2560 | 9.40288e+07 | 95462.4 | 0.0796514 | 0.607791 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3094.19 | 0.780888 | 5744.8ms | 1439562 | 30 | 3.60134e+08 | 443693 | 0.0975698 | 0.982015 | 1(Win) | true |
| jsonifier | 2591.59 | 0.923648 | 6650.92ms | 1439562 | 320 | 7.66111e+09 | 529742 | 0.22621 | 1.17248 | 2(Loss) | true |
| glaze | 1964.92 | 0.159671 | 8929.59ms | 1439562 | 320 | 3.98265e+08 | 698692 | 0.137006 | 1.54656 | 3(Loss) | true |
| simdjson (ondemand) | 1396.76 | 0.340427 | 6219.02ms | 1439562 | 320 | 3.58274e+09 | 982898 | 0.389476 | 2.17568 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3380.29 | 0.663552 | 5602.22ms | 1439562 | 160 | 1.16205e+09 | 406141 | 0.0104632 | 0.898858 | 1(Win) | true |
| jsonifier | 2911 | 0.494712 | 6459.78ms | 1439562 | 640 | 3.48387e+09 | 471616 | 2.08499 | 1.04385 | 2(Loss) | true |
| glaze | 2136.77 | 0.355108 | 8723.03ms | 1439562 | 160 | 8.32887e+08 | 642499 | 0.0628801 | 1.42216 | 3(Loss) | true |
| simdjson (ondemand) | 1484.48 | 0.189601 | 6034.94ms | 1439562 | 320 | 9.83879e+08 | 924816 | 0.00243286 | 2.04713 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4656.44 | 0.345791 | 7501.41ms | 1439562 | 640 | 6.65211e+08 | 294833 | 0.0976293 | 0.652134 | 1(Win) | true |
| glaze | 2046.85 | 0.282749 | 8554.5ms | 1439584 | 640 | 2.3019e+09 | 670736 | 0.138846 | 1.48427 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14776.2 | 0.152058 | 9286.29ms | 1439562 | 4890 | 9.76029e+07 | 92910.9 | 0.0065606 | 0.205545 | 1(Win) | true |
| glaze | 7509.2 | 0.198462 | 9385.34ms | 1439584 | 1280 | 1.6852e+08 | 182828 | 0.210095 | 0.40454 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1194.37 | 0.139458 | 4519.54ms | 56369 | 4890 | 1.92663e+07 | 45009.1 | 0.456715 | 2.54317 | 1(Win) | true |
| jsonifier | 1151.62 | 0.168301 | 4773.18ms | 56369 | 80 | 493772 | 46680 | 0.10186 | 2.63788 | 2(Loss) | true |
| jsonifier (two-stage) | 1014.27 | 0.153654 | 5333ms | 56369 | 2560 | 1.69785e+07 | 53001.2 | 0.0543618 | 2.99508 | 3(Loss) | true |
| simdjson (ondemand) | 611.188 | 0.185573 | 8797.66ms | 56369 | 2560 | 6.82027e+07 | 87956 | 0.105056 | 4.97127 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2136.84 | 0.111966 | 3135.74ms | 56369 | 40 | 31737.2 | 25157.5 | 0.261002 | 1.42069 | 1(Win) | true |
| jsonifier | 1583.53 | 0.258413 | 3866.17ms | 56369 | 2560 | 1.97014e+07 | 33948 | 0.0242848 | 1.91808 | 2(Loss) | true |
| jsonifier (two-stage) | 1369.82 | 0.262975 | 4411.36ms | 56369 | 640 | 6.81646e+06 | 39244.2 | 0.34717 | 2.21737 | 3(Loss) | true |
| simdjson (ondemand) | 764.407 | 0.147933 | 7553.53ms | 56369 | 2560 | 2.7708e+07 | 70326 | 0.319624 | 3.97465 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7156.95 | 0.379669 | 778.183ms | 56369 | 80 | 65061.7 | 7511.25 | 0.116628 | 0.423538 | 1(Win) | true |
| glaze | 4162.96 | 1.4734 | 1261.11ms | 56369 | 30 | 1.08602e+06 | 12913.3 | 0.780437 | 0.72949 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7223.11 | 0.299461 | 749.595ms | 56369 | 4890 | 2.42897e+06 | 7442.45 | 1.03289 | 0.419416 | 1(Win) | true |
| glaze | 4922.65 | 0.259723 | 1106.99ms | 56369 | 4890 | 3.93379e+06 | 10920.5 | 1.07535 | 0.614901 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1671.26 | 0.476282 | 5370.03ms | 94370 | 1280 | 8.42014e+07 | 53850.6 | 0.0579972 | 1.81762 | 1(Win) | true |
| jsonifier (two-stage) | 1602.92 | 0.235139 | 5601.17ms | 94370 | 4890 | 8.52315e+07 | 56146.3 | 0.0601275 | 1.8952 | 2(Loss) | true |
| jsonifier | 1375.83 | 0.473571 | 6471.35ms | 94370 | 4890 | 4.69262e+08 | 65413.6 | 0.687163 | 2.20815 | 3(Loss) | true |
| simdjson (ondemand) | 990.231 | 0.142847 | 9060.15ms | 94370 | 4890 | 8.24221e+07 | 90886.1 | 0.385871 | 3.06832 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2586.26 | 0.249909 | 3960.79ms | 94370 | 4890 | 3.69825e+07 | 34798.6 | 0.148659 | 1.1742 | 1(Win) | true |
| jsonifier (two-stage) | 2167.67 | 0.160754 | 4625.06ms | 94370 | 4890 | 2.17827e+07 | 41518.3 | 0.0589005 | 1.40123 | 2(Loss) | true |
| jsonifier | 1779.85 | 1.84862 | 5486.28ms | 94370 | 320 | 2.79605e+08 | 50565 | 0.282612 | 1.70693 | 3(Loss) | true |
| simdjson (ondemand) | 1226.36 | 0.148555 | 7776.16ms | 94370 | 2560 | 3.04262e+07 | 73386.5 | 0.0974726 | 2.47746 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10508.8 | 0.494688 | 870.456ms | 94370 | 640 | 1.14869e+06 | 8564.06 | 0.186444 | 0.28834 | 1(Win) | true |
| glaze | 4476.64 | 0.225579 | 2032.16ms | 94370 | 2560 | 5.26503e+06 | 20104 | 0.415627 | 0.677925 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10900.1 | 0.111448 | 844.2ms | 94370 | 30 | 2540.23 | 8256.67 | 0.0403877 | 0.278436 | 1(Win) | true |
| glaze | 5219.86 | 0.169621 | 1729.01ms | 94370 | 4890 | 4.18232e+06 | 17241.5 | 0.591264 | 0.580555 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1173.49 | 0.438277 | 959.331ms | 11812 | 4890 | 8.65554e+06 | 9599.39 | 0.263281 | 2.585 | 1(Win) | true |
| jsonifier (two-stage) | 1135.1 | 0.17266 | 1002.14ms | 11812 | 4890 | 1.43573e+06 | 9924.07 | 0.412694 | 2.67187 | 2(Loss) | true |
| glaze | 990.72 | 0.273214 | 1144.8ms | 11812 | 2560 | 2.47053e+06 | 11370.3 | 0.117356 | 3.06195 | 3(Loss) | true |
| simdjson (ondemand) | 506.219 | 0.22586 | 2229.41ms | 11812 | 4890 | 1.23526e+07 | 22252.8 | 0.043998 | 5.99641 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1335.47 | 0.15638 | 951.648ms | 11812 | 1280 | 222717 | 8435.08 | 0.169781 | 2.27059 | 1(Win) | true |
| jsonifier (two-stage) | 1276.33 | 0.365214 | 997.058ms | 11812 | 640 | 664960 | 8825.94 | 0.627071 | 2.37528 | 2(Loss) | true |
| glaze | 1203.83 | 0.241664 | 1053.59ms | 11812 | 40 | 20455.1 | 9357.5 | 0.980216 | 2.51777 | 3(Loss) | true |
| simdjson (ondemand) | 556.329 | 0.415089 | 2152.59ms | 11812 | 320 | 2.26056e+06 | 20248.4 | 0.0880472 | 5.45541 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6716.48 | 0.546732 | 172.208ms | 11812 | 640 | 53813.7 | 1677.19 | 0.0745851 | 0.444234 | 1(Win) | true |
| glaze | 3451.78 | 0.361283 | 329.987ms | 11812 | 4890 | 679774 | 3263.48 | 0.409834 | 0.874101 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7344.85 | 0.322423 | 156.263ms | 11812 | 4890 | 119576 | 1533.7 | 0.149874 | 0.408448 | 1(Win) | true |
| glaze | 4086.08 | 0.103111 | 282.903ms | 11812 | 320 | 2585.82 | 2756.88 | 0.54115 | 0.732758 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2651.17 | 0.3278 | 1133.03ms | 31235 | 2560 | 3.47269e+06 | 11235.8 | 0.217856 | 1.14414 | 1(Win) | true |
| jsonifier | 2235.85 | 0.298365 | 1339.84ms | 31235 | 4890 | 7.7269e+06 | 13322.9 | 0.102684 | 1.35727 | 2(Loss) | true |
| glaze | 1870.73 | 0.428315 | 1592.2ms | 31235 | 4890 | 2.27456e+07 | 15923.2 | 0.0841428 | 1.62234 | 3(Loss) | true |
| simdjson (ondemand) | 1268.91 | 0.259823 | 2360.55ms | 31235 | 2560 | 9.52393e+06 | 23475.3 | 0.107942 | 2.393 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2948.04 | 0.253023 | 1124.7ms | 31235 | 4890 | 3.19628e+06 | 10104.4 | 0.983192 | 1.02868 | 1(Win) | true |
| jsonifier | 2458.01 | 0.252588 | 1331.93ms | 31235 | 80 | 74960.4 | 12118.8 | 0.113332 | 1.23389 | 2(Loss) | true |
| glaze | 2164.03 | 0.211857 | 1492.81ms | 31235 | 2560 | 2.17712e+06 | 13765.1 | 1.12071 | 1.40216 | 3(Loss) | true |
| simdjson (ondemand) | 1379.52 | 0.350216 | 2260.41ms | 31235 | 1280 | 7.31998e+06 | 21593 | 0.188131 | 2.20056 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13941.3 | 0.418809 | 225.396ms | 31235 | 30 | 2402.3 | 2136.67 | 0.155763 | 0.21511 | 1(Win) | true |
| glaze | 5410.62 | 0.363483 | 567.053ms | 31235 | 640 | 256292 | 5505.47 | 0.10512 | 0.55923 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14829.1 | 0.175972 | 206.852ms | 31235 | 320 | 3998.43 | 2008.75 | 0.371978 | 0.202063 | 1(Win) | true |
| glaze | 6014.08 | 0.307907 | 499.296ms | 31235 | 4890 | 1.13734e+06 | 4953.05 | 0.0756505 | 0.500436 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1981.59 | 0.480575 | 5320.85ms | 108313 | 40 | 2.51025e+06 | 52127.5 | 0.00159867 | 1.53253 | 1(Win) | true |
| glaze | 1476.53 | 0.361736 | 7084.99ms | 108313 | 160 | 1.02466e+07 | 69958.1 | 0.0276875 | 2.0577 | 2(Loss) | true |
| jsonifier (two-stage) | 1385.05 | 0.289384 | 7629.84ms | 108313 | 2560 | 1.19239e+08 | 74578.9 | 0.51944 | 2.19361 | 3(Loss) | true |
| simdjson (ondemand) | 662.231 | 0.169009 | 7989.11ms | 108313 | 2560 | 1.77911e+08 | 155981 | 0.18785 | 4.58862 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2568.68 | 0.289052 | 4481.58ms | 108313 | 30 | 405333 | 40213.3 | 0.407824 | 1.18249 | 1(Win) | true |
| glaze | 1853.82 | 0.412947 | 5850.18ms | 108313 | 4890 | 2.58894e+08 | 55720.2 | 0.0882742 | 1.63853 | 2(Loss) | true |
| jsonifier (two-stage) | 1596.94 | 0.785368 | 6721.93ms | 108313 | 1280 | 3.30326e+08 | 64683.4 | 0.184651 | 1.90247 | 3(Loss) | true |
| simdjson (ondemand) | 746.916 | 0.227046 | 7224.48ms | 108313 | 2560 | 2.52397e+08 | 138296 | 0.341579 | 4.06846 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7614.79 | 0.276971 | 1356.31ms | 108313 | 4890 | 6.90278e+06 | 13565.1 | 0.145736 | 0.398401 | 1(Win) | true |
| glaze | 4058.14 | 0.245381 | 2612.59ms | 108313 | 4890 | 1.90765e+07 | 25453.8 | 0.587757 | 0.748157 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7970.32 | 0.474641 | 1327.18ms | 108313 | 30 | 113517 | 12960 | 0.387297 | 0.380455 | 1(Win) | true |
| glaze | 4641.97 | 0.382633 | 2260.68ms | 108313 | 4890 | 3.54512e+07 | 22252.5 | 0.0955185 | 0.653476 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2544.63 | 0.272489 | 8031.63ms | 213963 | 2560 | 1.22227e+08 | 80188.8 | 0.00623567 | 1.19398 | 1(Win) | true |
| glaze | 2182.24 | 0.170891 | 9376.47ms | 213963 | 2560 | 6.53656e+07 | 93505.3 | 0.091155 | 1.39232 | 2(Loss) | true |
| jsonifier | 2076.73 | 0.314166 | 5016.49ms | 213963 | 1280 | 1.21968e+08 | 98255.9 | 0.101513 | 1.46302 | 3(Loss) | true |
| simdjson (ondemand) | 1253.9 | 0.223798 | 8347.15ms | 213963 | 640 | 8.48878e+07 | 162733 | 0.142402 | 2.42352 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2968.12 | 0.141722 | 7152.13ms | 213963 | 4890 | 4.64193e+07 | 68747.6 | 0.124691 | 1.02356 | 1(Win) | true |
| glaze | 2587.96 | 0.254361 | 8141.36ms | 213963 | 4890 | 1.96686e+08 | 78846.3 | 0.437728 | 1.17393 | 2(Loss) | true |
| jsonifier | 2382.12 | 0.119789 | 8838.25ms | 213963 | 4890 | 5.14867e+07 | 85659.4 | 0.180447 | 1.27548 | 3(Loss) | true |
| simdjson (ondemand) | 1381.51 | 0.179992 | 7683.86ms | 213963 | 2560 | 1.80932e+08 | 147702 | 0.0417506 | 2.19964 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13624.6 | 0.658185 | 1542.94ms | 213963 | 30 | 291506 | 14976.7 | 0.13372 | 0.222754 | 1(Win) | true |
| glaze | 4568.66 | 0.373115 | 4443.55ms | 213963 | 2560 | 7.10927e+07 | 44663.2 | 0.248555 | 0.664726 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 13383.6 | 0.421108 | 1537.42ms | 213963 | 1280 | 5.27626e+06 | 15246.3 | 2.73698 | 0.226644 | -(Win) | false |
| glaze | 5475.78 | 0.348739 | 3754.84ms | 213963 | 1280 | 2.16171e+07 | 37264.3 | 0.0421576 | 0.554341 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 490.141 | 0.424017 | 5401.9ms | 1834197 | 40 | 9.15957e+09 | 3.56882e+06 | 0.245788 | 6.20053 | 1(Win) | true |
| jsonifier (two-stage) | 436.52 | 0.605707 | 5970.78ms | 1834197 | 40 | 2.35651e+10 | 4.00721e+06 | 1.06686 | 6.96196 | 2(Loss) | true |
| glaze | 287.836 | 0.470931 | 9001.06ms | 1834197 | 80 | 6.55249e+10 | 6.07717e+06 | 0.0343823 | 10.5589 | 3(Loss) | true |
| simdjson (ondemand) | 36.4887 | 0.142034 | 14379.3ms | 1834197 | 30 | 1.39086e+11 | 4.79388e+07 | 0.30524 | 83.2995 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 535.888 | 0.525918 | 5370.39ms | 1834197 | 30 | 8.84098e+09 | 3.26416e+06 | 0.592739 | 5.67113 | 1(Win) | true |
| jsonifier (two-stage) | 484.859 | 0.355827 | 5864.63ms | 1834197 | 80 | 1.31834e+10 | 3.6077e+06 | 0.174529 | 6.26799 | 2(Loss) | true |
| glaze | 302.57 | 0.457017 | 9117.81ms | 1834197 | 80 | 5.58463e+10 | 5.78122e+06 | 1.51562 | 10.0442 | 3(Loss) | true |
| simdjson (ondemand) | 36.8673 | 0.11924 | 14346.5ms | 1834197 | 30 | 9.60234e+10 | 4.74466e+07 | 0.194815 | 82.4442 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 885.111 | 0.242038 | 6150.09ms | 1834197 | 160 | 3.66085e+09 | 1.97628e+06 | 0.913389 | 3.43343 | 1(Win) | true |
| glaze | 681.136 | 0.231347 | 7983.97ms | 1833577 | 160 | 5.64389e+09 | 2.56723e+06 | 0.0441671 | 4.46176 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1004.52 | 0.22276 | 5426.69ms | 1834197 | 80 | 1.20375e+09 | 1.74135e+06 | 0.0364075 | 3.02526 | 1(Win) | true |
| glaze | 733.726 | 0.368724 | 7344.45ms | 1833577 | 80 | 6.17764e+09 | 2.38323e+06 | 0.0859343 | 4.14184 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2123.23 | 0.307836 | 6769.17ms | 9930848 | 80 | 1.50837e+10 | 4.46056e+06 | 0.0588277 | 1.43134 | 1(Win) | true |
| jsonifier | 1980.48 | 0.304056 | 7217.21ms | 9930848 | 40 | 8.45665e+09 | 4.78206e+06 | 0.126633 | 1.53458 | 2(Loss) | true |
| glaze | 1376.6 | 0.535788 | 10288.1ms | 9930848 | 40 | 5.43507e+10 | 6.87986e+06 | 0.00795865 | 2.20779 | 3(Loss) | true |
| simdjson (ondemand) | 193.812 | 0.102036 | 14716.8ms | 9930848 | 30 | 7.45829e+10 | 4.8866e+07 | 0.454629 | 15.6826 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2269.3 | 0.432744 | 6724.86ms | 9930848 | 40 | 1.3047e+10 | 4.17344e+06 | 0.367269 | 1.33914 | 1(Win) | true |
| jsonifier | 2101.74 | 0.466789 | 7254.04ms | 9930848 | 40 | 1.76977e+10 | 4.50617e+06 | 0.336539 | 1.44601 | 2(Loss) | true |
| glaze | 1451.68 | 0.401268 | 10288.8ms | 9930848 | 30 | 2.05599e+10 | 6.52402e+06 | 0.234094 | 2.09363 | 3(Loss) | true |
| simdjson (ondemand) | 192.856 | 0.184489 | 14723.3ms | 9930848 | 30 | 2.46248e+11 | 4.91082e+07 | 1.24916 | 15.7603 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3181.77 | 0.33314 | 9284.79ms | 9930848 | 80 | 7.86643e+09 | 2.97658e+06 | 0.890885 | 0.954997 | 1(Win) | true |
| glaze | 1885.08 | 0.601667 | 7551.47ms | 9930228 | 30 | 2.7409e+10 | 5.02377e+06 | 0.0749208 | 1.61229 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4798.26 | 0.243726 | 6095.89ms | 9930848 | 160 | 3.70277e+09 | 1.9738e+06 | 0.558888 | 0.633275 | 1(Win) | true |
| glaze | 3261.52 | 0.450561 | 8947.51ms | 9930228 | 80 | 1.36923e+10 | 2.90362e+06 | 0.0136917 | 0.931762 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 503.887 | 0.330145 | 5180ms | 1834197 | 80 | 1.05081e+10 | 3.47146e+06 | 0.319 | 6.03143 | 1(Win) | true |
| jsonifier (two-stage) | 439.777 | 0.548063 | 5949.14ms | 1834197 | 80 | 3.8017e+10 | 3.97753e+06 | 0.516049 | 6.91037 | 2(Loss) | true |
| glaze | 305.595 | 0.462049 | 8617.36ms | 1834197 | 80 | 5.59585e+10 | 5.72401e+06 | 0.0493074 | 9.94539 | 3(Loss) | true |
| simdjson (ondemand) | 253.557 | 0.917217 | 10364.5ms | 1834197 | 30 | 1.20117e+11 | 6.89875e+06 | 0.336606 | 11.9867 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 545.678 | 0.375364 | 5246.67ms | 1834197 | 30 | 4.34356e+09 | 3.2056e+06 | 0.421346 | 5.56946 | 1(Win) | true |
| jsonifier (two-stage) | 484.801 | 0.497912 | 5880.68ms | 1834197 | 30 | 9.68262e+09 | 3.60814e+06 | 0.632275 | 6.26855 | 2(Loss) | true |
| glaze | 321.02 | 0.307629 | 8690.55ms | 1834197 | 80 | 2.24788e+10 | 5.44897e+06 | 0.65034 | 9.46735 | 3(Loss) | true |
| simdjson (ondemand) | 270.512 | 0.467181 | 10113.8ms | 1834197 | 40 | 3.65049e+10 | 6.46636e+06 | 0.989404 | 11.2347 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 896.615 | 0.311891 | 6049.45ms | 1834197 | 80 | 2.96193e+09 | 1.95092e+06 | 0.0873426 | 3.38934 | 1(Win) | true |
| glaze | 602.403 | 0.329185 | 9015.53ms | 1833577 | 40 | 3.65227e+09 | 2.90276e+06 | 0.108462 | 5.04493 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1016.8 | 0.227726 | 5339.4ms | 1834197 | 160 | 2.45564e+09 | 1.72032e+06 | 0.141923 | 2.98876 | 1(Win) | true |
| glaze | 749.423 | 0.170429 | 7252.61ms | 1833577 | 160 | 2.53017e+09 | 2.33331e+06 | 0.126003 | 4.05532 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2171.14 | 0.40728 | 6583.42ms | 9930848 | 80 | 2.52507e+10 | 4.36214e+06 | 0.576272 | 1.39973 | 1(Win) | true |
| jsonifier | 2022.73 | 0.392014 | 7046.94ms | 9930848 | 30 | 1.0107e+10 | 4.68218e+06 | 0.368131 | 1.5025 | 2(Loss) | true |
| glaze | 1403.97 | 0.355258 | 10201.6ms | 9930848 | 40 | 2.29722e+10 | 6.7457e+06 | 0.426569 | 2.1648 | 3(Loss) | true |
| simdjson (ondemand) | 1263.25 | 0.362363 | 5286.12ms | 9930848 | 30 | 2.21412e+10 | 7.49715e+06 | 0.516449 | 2.40579 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2345.85 | 0.343746 | 6631.77ms | 9930848 | 30 | 5.77787e+09 | 4.03725e+06 | 0.744269 | 1.29549 | 1(Win) | true |
| jsonifier | 2139.45 | 0.451206 | 7067.41ms | 9930848 | 40 | 1.5958e+10 | 4.42674e+06 | 0.0937421 | 1.42047 | 2(Loss) | true |
| glaze | 1442.66 | 0.217386 | 10265.1ms | 9930848 | 30 | 6.10981e+09 | 6.5648e+06 | 0.690463 | 2.10663 | 3(Loss) | true |
| simdjson (ondemand) | 1329.19 | 0.234477 | 5241.04ms | 9930848 | 40 | 1.1165e+10 | 7.12522e+06 | 0.0844289 | 2.28645 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3118.7 | 0.463487 | 9337.21ms | 9930848 | 80 | 1.58486e+10 | 3.03677e+06 | 0.950087 | 0.974492 | 1(Win) | true |
| glaze | 1291.81 | 1.40095 | 5086.82ms | 9930228 | 40 | 4.21914e+11 | 7.33094e+06 | 1.10558 | 2.35262 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4801.24 | 0.343829 | 6094.05ms | 9930848 | 160 | 7.35987e+09 | 1.97257e+06 | 0.206947 | 0.632913 | 1(Win) | true |
| glaze | 3272.96 | 0.28461 | 8988.9ms | 9930228 | 80 | 5.42534e+09 | 2.89347e+06 | 0.0268205 | 0.92845 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 928.234 | 0.187216 | 8369.84ms | 642697 | 640 | 9.78057e+08 | 660312 | 0.0936653 | 3.27321 | 1(Win) | true |
| jsonifier (two-stage) | 815.44 | 0.339044 | 9649.95ms | 642697 | 40 | 2.59777e+08 | 751648 | 0.0898328 | 3.72673 | 2(Loss) | true |
| glaze | 687.784 | 0.356861 | 5614.55ms | 642697 | 160 | 1.61818e+09 | 891158 | 0.245226 | 4.41831 | 3(Loss) | true |
| simdjson (ondemand) | 423.62 | 0.368869 | 9107.52ms | 642697 | 30 | 8.54525e+08 | 1.44687e+06 | 0.242951 | 7.17397 | 4(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 980.23 | 0.176788 | 8370.61ms | 642697 | 320 | 3.91033e+08 | 625285 | 0.136474 | 3.10015 | 1(Win) | true |
| jsonifier (two-stage) | 843.854 | 0.264091 | 9626.15ms | 642697 | 320 | 1.17743e+09 | 726338 | 0.171972 | 3.60095 | 2(Loss) | true |
| glaze | 774.607 | 0.236139 | 5182.39ms | 642697 | 320 | 1.11721e+09 | 791270 | 0.315121 | 3.9234 | 3(Loss) | true |
| simdjson (ondemand) | 457.378 | 0.129484 | 8638.13ms | 642697 | 320 | 9.63483e+08 | 1.34008e+06 | 0.131791 | 6.64455 | 4(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1441.3 | 0.564409 | 5494.51ms | 642697 | 160 | 9.21748e+08 | 425258 | 0.0044089 | 2.1079 | 1(Win) | true |
| glaze | 920.471 | 0.190701 | 8397.49ms | 642692 | 640 | 1.03198e+09 | 665875 | 0.75535 | 3.30032 | 2(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1758.04 | 1.19253 | 8899.71ms | 642697 | 40 | 6.91434e+08 | 348640 | 0.133675 | 1.72835 | 1(Win) | true |
| glaze | 1274.08 | 0.228351 | 6177.44ms | 642692 | 160 | 1.9308e+08 | 481068 | 0.0734583 | 2.38537 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1475.85 | 0.321261 | 10060.6ms | 1225964 | 80 | 5.18178e+08 | 792204 | 0.039589 | 2.0591 | 1(Win) | true |
| jsonifier | 1198.01 | 0.219059 | 6154.27ms | 1225964 | 160 | 7.31266e+08 | 975926 | 0.0379912 | 2.53667 | 2(Loss) | true |
| glaze | 1178.75 | 0.229637 | 6272.9ms | 1225964 | 320 | 1.66014e+09 | 991871 | 0.965603 | 2.57801 | 3(Loss) | true |
| simdjson (ondemand) | 789.277 | 0.231235 | 9323.27ms | 1225964 | 320 | 3.75451e+09 | 1.48132e+06 | 0.346454 | 3.85028 | 4(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1548.88 | 0.140509 | 10003.9ms | 1225964 | 640 | 7.19963e+08 | 754850 | 0.283952 | 1.96193 | 1(Win) | true |
| glaze | 1321.12 | 0.471663 | 5787.57ms | 1225964 | 30 | 5.22708e+08 | 884987 | 0.0180826 | 2.30023 | 2(Loss) | true |
| jsonifier | 1245.52 | 0.444544 | 6133.65ms | 1225964 | 30 | 5.22406e+08 | 938703 | 0.105576 | 2.4399 | 3(Loss) | true |
| simdjson (ondemand) | 858.56 | 0.330341 | 8823.83ms | 1225964 | 30 | 6.071e+08 | 1.36178e+06 | 0.0649082 | 3.5397 | 4(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2381.14 | 0.178499 | 6339.55ms | 1225964 | 640 | 4.91629e+08 | 491012 | 0.763393 | 1.27571 | 1(Win) | true |
| glaze | 1521.68 | 0.329133 | 9789.98ms | 1225970 | 640 | 4.09292e+09 | 768343 | 0.378277 | 1.99661 | 2(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3317.72 | 0.25264 | 8991.13ms | 1225964 | 1280 | 1.01459e+09 | 352402 | 0.243099 | 0.915822 | 1(Win) | true |
| glaze | 2157.71 | 0.170835 | 6893.08ms | 1225970 | 640 | 5.48413e+08 | 541860 | 0.0341245 | 1.40838 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 862.74 | 0.247687 | 5745.6ms | 409725 | 640 | 8.05398e+08 | 452911 | 0.202375 | 3.5222 | 1(Win) | true |
| jsonifier (two-stage) | 854.406 | 0.424504 | 5892.77ms | 409725 | 160 | 6.03031e+08 | 457329 | 0.0117544 | 3.55639 | 2(Loss) | true |
| glaze | 781.527 | 0.278657 | 6299.35ms | 409725 | 640 | 1.24227e+09 | 499975 | 0.388287 | 3.88821 | 3(Loss) | true |
| simdjson (ondemand) | 517.523 | 0.273048 | 9565.3ms | 409725 | 640 | 2.72009e+09 | 755027 | 0.0475167 | 5.87173 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1234.61 | 0.346962 | 9612.27ms | 409725 | 320 | 3.8587e+08 | 316492 | 0.262642 | 2.4614 | 1(Win) | true |
| jsonifier (two-stage) | 1212.91 | 0.168929 | 9739.14ms | 409725 | 1280 | 3.79091e+08 | 322153 | 0.392923 | 2.50543 | 2(Loss) | true |
| glaze | 1078.28 | 0.310628 | 5404.31ms | 409725 | 320 | 4.05464e+08 | 362376 | 0.171732 | 2.81834 | 3(Loss) | true |
| simdjson (ondemand) | 644.601 | 0.134479 | 8506.21ms | 409725 | 640 | 4.25297e+08 | 606180 | 0.598909 | 4.71442 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3227.4 | 0.206653 | 6071.36ms | 409725 | 2560 | 1.60252e+08 | 121071 | 0.397943 | 0.940897 | 1(Win) | true |
| glaze | 2865.39 | 0.227501 | 6990.46ms | 409725 | 1280 | 1.23195e+08 | 136367 | 0.012545 | 1.06036 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6731.59 | 0.285756 | 5802.04ms | 409725 | 4890 | 1.3454e+08 | 58046.3 | 0.18041 | 0.451249 | 1(Win) | true |
| glaze | 3107.65 | 0.160187 | 6440.93ms | 409725 | 2560 | 1.03852e+08 | 125736 | 0.187634 | 0.977662 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1563.86 | 0.248384 | 6197.31ms | 785750 | 160 | 2.26642e+08 | 479167 | 0.950999 | 1.94311 | 1(Win) | true |
| jsonifier | 1360.4 | 0.322396 | 6986.41ms | 785750 | 320 | 1.00918e+09 | 550831 | 0.239359 | 2.23369 | 2(Loss) | true |
| glaze | 1296.81 | 0.4564 | 7303.08ms | 785750 | 320 | 2.22567e+09 | 577843 | 0.0192022 | 2.34319 | 3(Loss) | true |
| simdjson (ondemand) | 943.243 | 0.23613 | 5031.04ms | 785750 | 320 | 1.12609e+09 | 794440 | 0.0404996 | 3.22169 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2118.71 | 0.426058 | 5247.3ms | 785750 | 320 | 7.26627e+08 | 353682 | 0.0497199 | 1.43415 | 1(Win) | true |
| jsonifier | 1827.44 | 0.58019 | 5970.26ms | 785750 | 30 | 1.69802e+08 | 410053 | 0.0195135 | 1.66299 | 2(Loss) | true |
| glaze | 1692.11 | 0.549461 | 6403.19ms | 785750 | 160 | 9.47333e+08 | 442848 | 0.325937 | 1.79595 | 3(Loss) | true |
| simdjson (ondemand) | 1164.77 | 0.196031 | 9022.86ms | 785750 | 320 | 5.0897e+08 | 643348 | 0.0114622 | 2.60905 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4472.44 | 0.266518 | 8617.04ms | 785750 | 2560 | 5.10472e+08 | 167548 | 0.142363 | 0.678966 | 1(Win) | true |
| glaze | 2288.6 | 0.293729 | 8320.95ms | 785750 | 640 | 5.91977e+08 | 327427 | 0.200358 | 1.327 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11168.7 | 0.197444 | 6714.91ms | 785750 | 2560 | 4.49258e+07 | 67093.9 | 0.0182197 | 0.27194 | 1(Win) | true |
| glaze | 4630.19 | 0.205622 | 8316.91ms | 785750 | 1280 | 1.41749e+08 | 161840 | 0.0702866 | 0.656188 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5671.57 | 0.241658 | 4459.57ms | 264040 | 1280 | 1.47349e+07 | 44398.3 | 0.0760743 | 0.535597 | 1(Win) | true |
| jsonifier (two-stage) | 5587.58 | 0.443046 | 4484.62ms | 264040 | 4890 | 1.9494e+08 | 45065.7 | 0.102697 | 0.543565 | 2(Loss) | true |
| glaze | 2516.29 | 0.376317 | 5088.87ms | 264040 | 1280 | 1.81525e+08 | 100071 | 0.0400656 | 1.20753 | 3(Loss) | true |
| simdjson (ondemand) | 1917.55 | 0.111719 | 6732.07ms | 264040 | 2560 | 5.50985e+07 | 131317 | 0.0593985 | 1.58471 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 5970.01 | 0.123222 | 4355.39ms | 264040 | 4890 | 1.32091e+07 | 42178.8 | 0.173499 | 0.508776 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 5946.37 | 0.187101 | 4348.33ms | 264040 | 4890 | 3.0697e+07 | 42346.5 | 0.0737582 | 0.510739 | 1(Tie) | true |
| glaze | 2656.61 | 0.177668 | 9617.09ms | 264040 | 2560 | 7.2601e+07 | 94785.4 | 0.522578 | 1.14363 | 3(Loss) | true |
| simdjson (ondemand) | 1977.43 | 0.192084 | 6622.27ms | 264040 | 640 | 3.82914e+07 | 127341 | 0.016813 | 1.53669 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 7193.85 | 0.124008 | 5330.92ms | 399947 | 4890 | 2.11392e+07 | 53020.2 | 0.112361 | 0.42227 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 7168.22 | 0.208906 | 5335.85ms | 399947 | 2560 | 3.16317e+07 | 53209.7 | 0.439831 | 0.423781 | 1(Tie) | true |
| glaze | 3213.77 | 0.306026 | 6095.99ms | 399947 | 1280 | 1.68851e+08 | 118683 | 1.21015 | 0.945517 | 3(Loss) | true |
| simdjson (ondemand) | 2654.84 | 0.331725 | 7335.67ms | 399947 | 2560 | 5.81466e+08 | 143669 | 0.0484005 | 1.14461 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7474.24 | 0.217964 | 5211.52ms | 399947 | 4890 | 6.04994e+07 | 51031.1 | 0.197136 | 0.406419 | 1(Win) | true |
| jsonifier (two-stage) | 7337.69 | 0.30194 | 5312.56ms | 399947 | 2560 | 6.30618e+07 | 51980.8 | 0.136881 | 0.413895 | 2(Loss) | true |
| glaze | 3341.61 | 0.380969 | 5903.36ms | 399947 | 640 | 1.21019e+08 | 114142 | 0.241372 | 0.909241 | 3(Loss) | true |
| simdjson (ondemand) | 2767.55 | 0.13539 | 7158.73ms | 399947 | 2560 | 8.91309e+07 | 137819 | 0.159032 | 1.09799 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1241.32 | 0.25955 | 5184.29ms | 264040 | 1280 | 3.54832e+08 | 202855 | 0.778323 | 2.44782 | 1(Win) | true |
| glaze | 1186.19 | 0.23898 | 5442.58ms | 264040 | 1280 | 3.29433e+08 | 212284 | 0.514664 | 2.56187 | 2(Loss) | true |
| jsonifier (two-stage) | 1121.62 | 0.321196 | 5758.01ms | 264040 | 320 | 1.66394e+08 | 224504 | 0.128451 | 2.70923 | 3(Loss) | true |
| simdjson (ondemand) | 798.99 | 0.525001 | 8033.84ms | 264040 | 160 | 4.38024e+08 | 315158 | 0.607532 | 3.80327 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1763.3 | 0.167369 | 8348.33ms | 264040 | 2560 | 1.46244e+08 | 142805 | 0.127333 | 1.72331 | 1(Win) | true |
| glaze | 1652.87 | 0.269901 | 8892.44ms | 264040 | 160 | 2.70514e+07 | 152346 | 0.191221 | 1.83852 | 2(Loss) | true |
| jsonifier (two-stage) | 1513.81 | 0.140061 | 9563.34ms | 264040 | 2560 | 1.38954e+08 | 166341 | 0.255729 | 2.00732 | 3(Loss) | true |
| simdjson (ondemand) | 1019.69 | 0.156094 | 6784.98ms | 264040 | 1280 | 1.90189e+08 | 246947 | 0.226635 | 2.98037 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8248.33 | 0.289686 | 3058.03ms | 264040 | 4890 | 3.82447e+07 | 30528.4 | 0.086203 | 0.368153 | 1(Win) | true |
| glaze | 5005.57 | 1.30501 | 5350.11ms | 263923 | 30 | 1.2918e+07 | 50283.3 | 0.072867 | 0.606974 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8543.11 | 0.33235 | 3000.56ms | 264040 | 320 | 3.07078e+06 | 29475 | 0.101678 | 0.355267 | 1(Win) | true |
| glaze | 5708.76 | 0.283553 | 4512.95ms | 263923 | 2560 | 4.00109e+07 | 44089.5 | 0.797491 | 0.531892 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1620.7 | 0.555082 | 6098.59ms | 399947 | 80 | 1.36523e+08 | 235342 | 0.273754 | 1.87492 | 1(Win) | true |
| glaze | 1548.44 | 1.02845 | 6258.85ms | 399947 | 80 | 5.13419e+08 | 246325 | 0.0365504 | 1.96237 | 2(Loss) | true |
| jsonifier | 1337.46 | 0.466021 | 7262.8ms | 399947 | 1280 | 2.26081e+09 | 285181 | 0.0362029 | 2.27197 | 3(Loss) | true |
| simdjson (ondemand) | 1174.44 | 0.305553 | 8285.44ms | 399947 | 640 | 6.30222e+08 | 324766 | 0.446585 | 2.58754 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2155.38 | 0.436763 | 5034.01ms | 399947 | 640 | 3.82321e+08 | 176961 | 0.509223 | 1.40987 | 1(Win) | true |
| glaze | 2083.23 | 0.321703 | 5390.22ms | 399947 | 30 | 1.04078e+07 | 183090 | 0.244557 | 1.45881 | 2(Loss) | true |
| jsonifier | 1739.07 | 0.537388 | 6157.22ms | 399947 | 1280 | 1.7781e+09 | 219324 | 0.562464 | 1.74744 | 3(Loss) | true |
| simdjson (ondemand) | 1455.02 | 0.251108 | 7127.54ms | 399947 | 1280 | 5.54623e+08 | 262140 | 0.682763 | 2.0886 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11146.3 | 0.187349 | 3447.07ms | 399947 | 2560 | 1.05217e+07 | 34219.3 | 0.0511669 | 0.272467 | 1(Win) | true |
| glaze | 3721.29 | 0.331292 | 5202.75ms | 399830 | 2560 | 2.95003e+08 | 102466 | 0.544051 | 0.816455 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11183.3 | 0.12024 | 3414.17ms | 399947 | 4890 | 8.22372e+06 | 34106.1 | 0.109835 | 0.271534 | 1(Win) | true |
| glaze | 4277.6 | 0.418144 | 8976.34ms | 399830 | 1280 | 1.77833e+08 | 89140.5 | 0.0198909 | 0.710219 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 573.862 | 0.523811 | 791.635ms | 4630 | 160 | 259905 | 7694.38 | 0.383235 | 5.28596 | 1(Win) | true |
| jsonifier (two-stage) | 532.043 | 0.312481 | 836.278ms | 4630 | 4890 | 3.2887e+06 | 8299.16 | 0.134577 | 5.70045 | 2(Loss) | true |
| glaze | 330.124 | 0.22728 | 1359.73ms | 4630 | 320 | 295721 | 13375.3 | 0.435005 | 9.19133 | 3(Loss) | true |
| simdjson (ondemand) | 325.771 | 0.307979 | 1361.03ms | 4630 | 2560 | 4.46087e+06 | 13554 | 0.0123941 | 9.31531 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 713.33 | 0.236848 | 761.798ms | 4630 | 30 | 6448.28 | 6190 | 0.269978 | 4.26226 | 1(Win) | true |
| jsonifier (two-stage) | 671.816 | 0.172167 | 812.407ms | 4630 | 40 | 5121.79 | 6572.5 | 0.139665 | 4.51276 | 2(Loss) | true |
| glaze | 379.711 | 0.270788 | 1298.48ms | 4630 | 4890 | 4.84869e+06 | 11628.6 | 0.383685 | 7.98586 | 3(Loss) | true |
| simdjson (ondemand) | 358.341 | 0.241398 | 1375.6ms | 4630 | 4890 | 4.32659e+06 | 12322.1 | 0.0228054 | 8.46531 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1868.34 | 0.554981 | 227.551ms | 4630 | 30 | 5160.92 | 2363.33 | 1.52778 | 1.6116 | 1(Win) | true |
| glaze | 1098.39 | 0.345676 | 401.093ms | 4630 | 30 | 5793.1 | 4020 | 0.08285 | 2.7442 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2000.23 | 0.250625 | 225.503ms | 4630 | 40 | 1224.36 | 2207.5 | 0.113122 | 1.50281 | 1(Win) | true |
| glaze | 1201.91 | 0.158717 | 370.268ms | 4630 | 80 | 2719.94 | 3673.75 | 0.512996 | 2.5017 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1582.29 | 0.257755 | 898.941ms | 14795 | 2560 | 1.35242e+06 | 8917.23 | 0.101963 | 1.9164 | 1(Win) | true |
| jsonifier | 1477.22 | 0.325474 | 964.766ms | 14795 | 4890 | 4.72583e+06 | 9551.43 | 0.585612 | 2.05341 | 2(Loss) | true |
| simdjson (ondemand) | 976.951 | 0.187377 | 1438.67ms | 14795 | 160 | 117176 | 14442.5 | 0.0692881 | 3.10586 | 3(Loss) | true |
| glaze | 915.913 | 0.18449 | 1557.76ms | 14795 | 2560 | 2.0678e+06 | 15405 | 0.043887 | 3.31417 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1910.82 | 0.588478 | 875.452ms | 14795 | 320 | 604228 | 7384.06 | 0.676755 | 1.5858 | 1(Win) | true |
| jsonifier | 1779.62 | 0.214091 | 938.447ms | 14795 | 320 | 92198.2 | 7928.44 | 0.0512659 | 1.7029 | 2(Loss) | true |
| simdjson (ondemand) | 1078.28 | 0.252589 | 1457.41ms | 14795 | 4890 | 5.34203e+06 | 13085.3 | 0.184106 | 2.81358 | 3(Loss) | true |
| glaze | 1030.18 | 0.245822 | 1530.84ms | 14795 | 160 | 181369 | 13696.2 | 0.209472 | 2.94394 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5738.62 | 0.342682 | 247.54ms | 14795 | 4890 | 347141 | 2458.71 | 0.70043 | 0.525473 | 1(Win) | true |
| glaze | 2977.5 | 0.152459 | 492.593ms | 14795 | 80 | 4175.63 | 4738.75 | 0.341746 | 1.01679 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6432.95 | 0.485535 | 232.903ms | 14795 | 30 | 3402.3 | 2193.33 | 0.304878 | 0.467099 | 1(Win) | true |
| glaze | 3441.37 | 0.20255 | 429.541ms | 14795 | 30 | 2068.97 | 4100 | 0.819672 | 0.87539 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 954.049 | 0.328445 | 528.959ms | 5092 | 40 | 11179.5 | 5090 | 0.130804 | 3.17879 | 1(Win) | true |
| jsonifier (two-stage) | 805.492 | 0.363099 | 609.183ms | 5092 | 320 | 153340 | 6028.75 | 0.291121 | 3.75931 | 2(Loss) | true |
| glaze | 681.694 | 0.309837 | 727.447ms | 5092 | 1280 | 623555 | 7123.59 | 0.286514 | 4.44381 | 3(Loss) | true |
| simdjson (ondemand) | 466.901 | 0.454263 | 1041.34ms | 5092 | 4890 | 1.09157e+07 | 10400.7 | 0.0927384 | 6.49477 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1236.44 | 0.169323 | 495.154ms | 5092 | 80 | 3537.97 | 3927.5 | 0.443599 | 2.44986 | 1(Win) | true |
| jsonifier (two-stage) | 1021.26 | 0.281248 | 574.872ms | 5092 | 40 | 7153.85 | 4755 | 0.0350631 | 2.96222 | 2(Loss) | true |
| glaze | 824.904 | 0.269453 | 672.913ms | 5092 | 320 | 80516.8 | 5886.88 | 0.308839 | 3.66984 | 3(Loss) | true |
| simdjson (ondemand) | 588.887 | 0.098725 | 929.084ms | 5092 | 80 | 5302.22 | 8246.25 | 0.287183 | 5.14367 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6091.85 | 0.245401 | 83.4269ms | 5092 | 2560 | 9796.48 | 797.148 | 0.408384 | 0.485129 | 1(Win) | true |
| glaze | 3623.96 | 0.585421 | 140.733ms | 5092 | 40 | 2461.54 | 1340 | 0.249377 | 0.821087 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6462.7 | 0.276318 | 78.2742ms | 5092 | 1280 | 5517.96 | 751.406 | 0.124611 | 0.459487 | 1(Win) | true |
| glaze DID NOT CONVERGE | 4455.15 | 0.44072 | 112.693ms | 5092 | 40 | 923.077 | 1090 | 3.25444 | 0.66547 | -(Loss) | false |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1789.3 | 0.460879 | 646.574ms | 11724 | 160 | 132703 | 6248.75 | 0.120168 | 1.69442 | 1(Win) | true |
| jsonifier | 1533.62 | 0.381032 | 736.612ms | 11724 | 2560 | 1.97551e+06 | 7290.51 | 0.27944 | 1.97502 | 2(Loss) | true |
| glaze | 1298.7 | 0.227119 | 867.523ms | 11724 | 4890 | 1.86961e+06 | 8609.3 | 0.13048 | 2.33357 | 3(Loss) | true |
| simdjson (ondemand) | 1033.82 | 0.255873 | 1080.51ms | 11724 | 2560 | 1.96042e+06 | 10815.1 | 0.127661 | 2.93328 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2227.27 | 0.221947 | 614.786ms | 11724 | 30 | 3724.14 | 5020 | 0.066357 | 1.35914 | 1(Win) | true |
| jsonifier | 1820.11 | 0.545144 | 710.103ms | 11724 | 4890 | 5.48387e+06 | 6142.97 | 0.0444749 | 1.66353 | 2(Loss) | true |
| glaze | 1565.13 | 0.0991195 | 815.901ms | 11724 | 80 | 4011.08 | 7143.75 | 0.0174948 | 1.93594 | 3(Loss) | true |
| simdjson (ondemand) | 1258.13 | 0.487929 | 967.846ms | 11724 | 2560 | 4.81344e+06 | 8886.91 | 0.115736 | 2.40902 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11085.6 | 0.217207 | 105.499ms | 11724 | 640 | 3071.57 | 1008.59 | 0.232919 | 0.267677 | 1(Win) | true |
| glaze | 4559.78 | 0.422364 | 255.296ms | 11746 | 30 | 3229.89 | 2456.67 | 0.135501 | 0.659932 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13192.8 | 0.943527 | 90.7322ms | 11724 | 40 | 2557.69 | 847.5 | 0.294118 | 0.223424 | 1(Win) | true |
| glaze | 6216.78 | 0.228017 | 193.948ms | 11746 | 160 | 2700.86 | 1801.88 | 0.104167 | 0.478972 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1067.49 | 0.40213 | 441.869ms | 4857 | 1280 | 389718 | 4339.14 | 0.106341 | 2.83604 | 1(Win) | true |
| glaze | 999.487 | 0.890539 | 470.649ms | 4857 | 1280 | 2.18021e+06 | 4634.38 | 0.0472239 | 3.02592 | 2(Loss) | true |
| jsonifier (two-stage) | 938.918 | 0.224447 | 508.835ms | 4857 | 30 | 3678.16 | 4933.33 | 0.202293 | 3.21589 | 3(Loss) | true |
| simdjson (ondemand) | 639.433 | 0.30162 | 738.006ms | 4857 | 2560 | 1.2221e+06 | 7243.91 | 0.115266 | 4.73955 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1848.18 | 0.217185 | 304.904ms | 4857 | 160 | 4740.57 | 2506.25 | 0.446872 | 1.62604 | 1(Win) | true |
| jsonifier | 1461.02 | 0.29309 | 373.011ms | 4857 | 2560 | 221038 | 3170.39 | 0.684779 | 2.06853 | 2(Loss) | true |
| jsonifier (two-stage) | 1248.52 | 0.358524 | 443.839ms | 4857 | 40 | 7076.92 | 3710 | 0.815217 | 2.42067 | 3(Loss) | true |
| simdjson (ondemand) | 849.713 | 0.122075 | 600.972ms | 4857 | 80 | 3542.72 | 5451.25 | 0.388305 | 3.56744 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5934 | 0.272613 | 82.0167ms | 4857 | 2560 | 11592.5 | 780.586 | 0.0350175 | 0.500951 | 1(Win) | true |
| glaze | 3543.59 | 0.317954 | 132.438ms | 4857 | 2560 | 44220.1 | 1307.15 | 1.5852 | 0.841553 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6218.75 | 0.264139 | 76.6983ms | 4857 | 640 | 2477.28 | 744.844 | 0.271967 | 0.476973 | 1(Win) | true |
| glaze | 4784.5 | 0.619754 | 101.358ms | 4857 | 320 | 11520 | 968.125 | 0.257566 | 0.618547 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1384.02 | 0.547599 | 530.07ms | 7376 | 80 | 61968.4 | 5082.5 | 0.586797 | 2.18921 | 1(Win) | true |
| glaze | 1309.93 | 0.78247 | 560.02ms | 7376 | 160 | 282491 | 5370 | 0.831025 | 2.30705 | 2(Loss) | true |
| jsonifier | 1236.41 | 0.34011 | 581.108ms | 7376 | 2560 | 958510 | 5689.3 | 0.245027 | 2.44827 | 3(Loss) | true |
| simdjson (ondemand) | 911.327 | 0.801563 | 788.823ms | 7376 | 160 | 612476 | 7718.75 | 0.35501 | 3.32432 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2229.57 | 0.299189 | 377.87ms | 7376 | 40 | 3564.1 | 3155 | 0.0527983 | 1.35646 | 1(Win) | true |
| jsonifier (two-stage) | 1836.63 | 0.255024 | 464.197ms | 7376 | 30 | 2862.07 | 3830 | 0.173762 | 1.6447 | 2(Loss) | true |
| jsonifier | 1577.64 | 0.152936 | 522.494ms | 7376 | 80 | 3719.94 | 4458.75 | 0.0280426 | 1.91866 | 3(Loss) | true |
| simdjson (ondemand) | 1178.25 | 0.682665 | 641.934ms | 7376 | 4890 | 8.12246e+06 | 5970.1 | 0.260636 | 2.57038 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7159.59 | 0.619272 | 93.9203ms | 7376 | 40 | 1480.77 | 982.5 | 0.757576 | 0.417923 | 1(Win) | true |
| glaze | 3696.64 | 0.515448 | 198.845ms | 7376 | 1280 | 123143 | 1902.89 | 0.757012 | 0.811788 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8553.97 | 0.302488 | 86.68ms | 7376 | 640 | 3960.07 | 822.344 | 0.0569692 | 0.347845 | 1(Win) | true |
| glaze | 4851.24 | 0.720666 | 164.052ms | 7376 | 30 | 3275.86 | 1450 | 0.230415 | 0.616983 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1082.17 | 0.339308 | 393.623ms | 4390 | 160 | 27570.8 | 3868.75 | 0.0323206 | 2.79333 | 1(Win) | true |
| jsonifier (two-stage) | 999.326 | 0.209727 | 421.542ms | 4390 | 1280 | 98817.5 | 4189.45 | 0.27863 | 3.02813 | 2(Loss) | true |
| glaze | 972.627 | 0.333258 | 435.485ms | 4390 | 4890 | 1.00626e+06 | 4304.46 | 0.185587 | 3.11111 | 3(Loss) | true |
| simdjson (ondemand) | 521.698 | 0.36988 | 826.346ms | 4390 | 320 | 281944 | 8025 | 0.257672 | 5.81197 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1271.38 | 0.229506 | 381.736ms | 4390 | 640 | 36554.6 | 3292.97 | 0.0142369 | 2.37803 | 1(Win) | true |
| glaze | 1245.84 | 0.260935 | 382.623ms | 4390 | 4890 | 375992 | 3360.49 | 0.0260724 | 2.42132 | 2(Loss) | true |
| jsonifier (two-stage) | 1165.36 | 0.259182 | 413.906ms | 4390 | 4890 | 423962 | 3592.56 | 0.0733822 | 2.5956 | 3(Loss) | true |
| simdjson (ondemand) | 565.809 | 0.2516 | 815.863ms | 4390 | 640 | 221815 | 7399.38 | 0.198891 | 5.35284 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5980.9 | 0 | 69.0494ms | 4390 | 30 | 0 | 700 | 0 | 0.495444 | 1(Win) | true |
| glaze | 3489.99 | 0.242108 | 125.212ms | 4390 | 2560 | 21594.2 | 1199.61 | 0.313582 | 0.856689 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6807.53 | 0.65323 | 63.6787ms | 4390 | 80 | 1291.14 | 615 | 0.408163 | 0.431757 | 1(Win) | true |
| glaze | 4098.89 | 0.418617 | 109.532ms | 4390 | 640 | 11700.7 | 1021.41 | 0.50738 | 0.720438 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2430.81 | 0.213399 | 463.674ms | 11521 | 80 | 7443.04 | 4520 | 0.668151 | 1.24665 | 1(Win) | true |
| jsonifier | 2088.84 | 0.296772 | 547.987ms | 11521 | 30 | 7310.34 | 5260 | 0.189753 | 1.45123 | 2(Loss) | true |
| glaze | 1830.14 | 1.48363 | 597.134ms | 11521 | 1280 | 1.01548e+07 | 6003.52 | 0.234986 | 1.65515 | 3(Loss) | true |
| simdjson (ondemand) | 1297.2 | 0.189021 | 880.114ms | 11521 | 30 | 7689.66 | 8470 | 0.0786473 | 2.33847 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2811.84 | 0.265381 | 456.35ms | 11521 | 40 | 4301.28 | 3907.5 | 0.149063 | 1.07779 | 1(Win) | true |
| jsonifier | 2284.85 | 0.248995 | 536.398ms | 11521 | 640 | 91754.3 | 4808.75 | 0.365249 | 1.32507 | 2(Loss) | true |
| glaze | 2264.84 | 0.248687 | 544.641ms | 11521 | 80 | 11644 | 4851.25 | 0.910036 | 1.33358 | 3(Loss) | true |
| simdjson (ondemand) | 1379.88 | 0.265096 | 863.096ms | 11521 | 160 | 71289.3 | 7962.5 | 0.0313873 | 2.19534 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14250.4 | 0.611191 | 81.4989ms | 11521 | 1280 | 28424.3 | 771.016 | 0.373511 | 0.208316 | 1(Win) | true |
| glaze | 5054.53 | 0.324714 | 220.927ms | 11521 | 80 | 3985.76 | 2173.75 | 0.520231 | 0.594405 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 16968.8 | 0.611629 | 69.1363ms | 11521 | 160 | 2509.43 | 647.5 | 0.192678 | 0.174549 | 1(Win) | true |
| glaze | 6510.98 | 0.271529 | 170.79ms | 11521 | 2560 | 53747.6 | 1687.5 | 0.730732 | 0.456827 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1899.05 | 0.721106 | 238.108ms | 4669 | 4890 | 1.39792e+06 | 2344.7 | 0.062587 | 1.58509 | 1(Win) | true |
| glaze | 1352.04 | 0.435137 | 346.184ms | 4669 | 30 | 6160.92 | 3293.33 | 0.406504 | 2.23256 | 2(Loss) | true |
| jsonifier (two-stage) | 1330.9 | 0.240822 | 340.162ms | 4669 | 640 | 41545.8 | 3345.62 | 0.538833 | 2.26964 | 3(Loss) | true |
| simdjson (ondemand) | 673.632 | 0.26503 | 678.909ms | 4669 | 30 | 9206.9 | 6610 | 0.151057 | 4.50184 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2283.44 | 0.476142 | 225.808ms | 4669 | 30 | 2586.21 | 1950 | 0.510204 | 1.312 | 1(Win) | true |
| glaze | 1644.58 | 0.277008 | 299.185ms | 4669 | 40 | 2250 | 2707.5 | 1.02612 | 1.82816 | 2(Loss) | true |
| jsonifier (two-stage) | 1457.22 | 0.305682 | 330.562ms | 4669 | 640 | 55836.9 | 3055.62 | 0.0204583 | 2.07171 | 3(Loss) | true |
| simdjson (ondemand) | 732.956 | 0.16973 | 620.338ms | 4669 | 640 | 68043.8 | 6075 | 0.387297 | 4.13371 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5565.88 | 0 | 71.8552ms | 4669 | 40 | 0 | 800 | 0 | 0.519667 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2852.58 | 0.593708 | 140.029ms | 4669 | 640 | 54966.3 | 1560.94 | 3.00971 | 1.04845 | -(Loss) | false |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7120.77 | 0.27507 | 67.1591ms | 4669 | 640 | 1893.49 | 625.312 | 0.596125 | 0.415335 | 1(Win) | true |
| glaze | 4745.4 | 0.388312 | 109.73ms | 4669 | 2560 | 33986.2 | 938.32 | 1.89616 | 0.619743 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2440.93 | 0.257728 | 366.793ms | 9249 | 640 | 55511.3 | 3613.59 | 0.116883 | 1.23785 | 1(Win) | true |
| glaze | 2012.29 | 0.31099 | 454.23ms | 9249 | 30 | 5574.71 | 4383.33 | 0.378788 | 1.50519 | 2(Loss) | true |
| jsonifier | 1927.85 | 0.283384 | 474.34ms | 9249 | 640 | 107590 | 4575.31 | 0.0750751 | 1.56882 | 3(Loss) | true |
| simdjson (ondemand) | 1296.9 | 0.648697 | 707.538ms | 9249 | 160 | 311445 | 6801.25 | 0.0551673 | 2.33629 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2688.45 | 0.172164 | 359.237ms | 9249 | 2560 | 81678.8 | 3280.9 | 0.887666 | 1.1236 | 1(Win) | true |
| glaze | 2350.05 | 0.246824 | 410.293ms | 9249 | 30 | 2574.71 | 3753.33 | 0.0888889 | 1.28521 | 2(Loss) | true |
| jsonifier | 2054.57 | 0.288269 | 461.217ms | 9249 | 1280 | 196043 | 4293.12 | 0.188899 | 1.47258 | 3(Loss) | true |
| simdjson (ondemand) | 1418.59 | 0.286121 | 644.183ms | 9249 | 320 | 101280 | 6217.81 | 0.0955831 | 2.13619 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11249.8 | 0.261376 | 83.4173ms | 9249 | 320 | 1343.95 | 784.062 | 0.279776 | 0.262521 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3672.12 | 0.62831 | 240.028ms | 9249 | 4890 | 1.11381e+06 | 2402.02 | 3.35728 | 0.81946 | -(Loss) | false |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11904.6 | 0.262533 | 78.3906ms | 9249 | 640 | 2421.65 | 740.938 | 0.381033 | 0.249286 | 1(Win) | true |
| glaze | 5636.12 | 0.426827 | 181.224ms | 9249 | 80 | 3569.62 | 1565 | 0.634921 | 0.525938 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 426.257 | 0.359823 | 1042.35ms | 4604 | 1280 | 1.75839e+06 | 10300.6 | 0.624077 | 7.11376 | 1(Win) | true |
| jsonifier (two-stage) | 379.07 | 0.335392 | 1162.75ms | 4604 | 2560 | 3.86346e+06 | 11582.9 | 0.0482027 | 8.00132 | 2(Loss) | true |
| glaze | 274.189 | 0.177653 | 1615.77ms | 4604 | 2560 | 2.07184e+06 | 16013.5 | 0.30375 | 11.0678 | 3(Loss) | true |
| simdjson (ondemand) | 38.559 | 0.278773 | 5816.21ms | 4604 | 320 | 3.22455e+07 | 113870 | 0.38182 | 78.8052 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 504.219 | 0.314509 | 1009.51ms | 4604 | 4890 | 3.66782e+06 | 8707.96 | 0.066056 | 6.01249 | 1(Win) | true |
| jsonifier (two-stage) | 461.724 | 0.153416 | 1093.05ms | 4604 | 4890 | 1.04076e+06 | 9509.39 | 1.07069 | 6.56799 | 2(Loss) | true |
| glaze | 299.044 | 0.150107 | 1626.06ms | 4604 | 40 | 19429.5 | 14682.5 | 0.795195 | 10.1483 | 3(Loss) | true |
| simdjson (ondemand) | 39.4951 | 0.348782 | 5824.08ms | 4604 | 160 | 2.40554e+07 | 111171 | 0.340651 | 76.9397 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1519.28 | 0.303655 | 306.424ms | 4604 | 30 | 2310.34 | 2890 | 0.23015 | 1.98792 | 1(Win) | true |
| glaze | 926.098 | 0.299395 | 483.006ms | 4604 | 1280 | 257903 | 4741.09 | 0.0230749 | 3.26689 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1571.86 | 0.165825 | 289.041ms | 4604 | 30 | 643.678 | 2793.33 | 0.11919 | 1.91969 | 1(Win) | true |
| glaze | 994.975 | 0.565524 | 443.307ms | 4604 | 1280 | 797183 | 4412.89 | 1.03567 | 3.03491 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1866.64 | 0.290649 | 1255.75ms | 24579 | 4890 | 6.51405e+06 | 12557.5 | 0.221733 | 1.62506 | 1(Win) | true |
| jsonifier | 1717.15 | 0.38305 | 1364.45ms | 24579 | 2560 | 6.99944e+06 | 13650.7 | 0.0243174 | 1.7671 | 2(Loss) | true |
| glaze | 1197.31 | 0.295283 | 1960.1ms | 24579 | 4890 | 1.63418e+07 | 19577.5 | 0.240225 | 2.53528 | 3(Loss) | true |
| simdjson (ondemand) | 205.241 | 0.191035 | 5910.71ms | 24579 | 80 | 3.80815e+06 | 114209 | 0.00547273 | 14.8056 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2211.62 | 0.250332 | 1205.61ms | 24579 | 320 | 225265 | 10598.8 | 0.0235821 | 1.37106 | 1(Win) | true |
| jsonifier | 1980.23 | 0.200458 | 1332.01ms | 24579 | 4890 | 2.75331e+06 | 11837.2 | 0.186824 | 1.53171 | 2(Loss) | true |
| glaze | 1348.41 | 0.230478 | 1913.05ms | 24579 | 160 | 256841 | 17383.8 | 0.122091 | 2.25109 | 3(Loss) | true |
| simdjson (ondemand) | 205.228 | 0.115308 | 5941.59ms | 24579 | 2560 | 4.44033e+07 | 114216 | 0.311075 | 14.8065 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6141.48 | 0.251461 | 385.034ms | 24579 | 4890 | 450434 | 3816.73 | 0.190779 | 0.491752 | 1(Win) | true |
| glaze | 2916.95 | 0.242742 | 807.708ms | 24579 | 4890 | 1.86067e+06 | 8035.91 | 0.483711 | 1.03862 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6458.93 | 0.254104 | 366.037ms | 24579 | 1280 | 108853 | 3629.14 | 0.626029 | 0.467587 | 1(Win) | true |
| glaze | 3407.05 | 0.345479 | 692.181ms | 24579 | 2560 | 1.44629e+06 | 6879.96 | 0.331047 | 0.887819 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 450.638 | 0.212704 | 968.847ms | 4604 | 30 | 12885.1 | 9743.33 | 0.17135 | 6.72268 | 1(Win) | true |
| jsonifier (two-stage) | 397.325 | 0.262599 | 1113.96ms | 4604 | 4890 | 4.11789e+06 | 11050.7 | 0.0236182 | 7.63244 | 2(Loss) | true |
| glaze | 274.139 | 0.28853 | 1602.87ms | 4604 | 2560 | 5.46703e+06 | 16016.4 | 0.190108 | 11.07 | 3(Loss) | true |
| simdjson (ondemand) | 250.792 | 0.203576 | 1767.33ms | 4604 | 2560 | 3.2519e+06 | 17507.4 | 0.721238 | 12.103 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 548.058 | 0.546795 | 934.691ms | 4604 | 4890 | 9.38373e+06 | 8011.41 | 0.641422 | 5.53062 | 1(Win) | true |
| jsonifier (two-stage) | 487.212 | 0.315035 | 1035.59ms | 4604 | 4890 | 3.9415e+06 | 9011.92 | 0.0720965 | 6.22329 | 2(Loss) | true |
| glaze | 316.867 | 0.324008 | 1568.82ms | 4604 | 30 | 60471.3 | 13856.7 | 0.526442 | 9.57436 | 3(Loss) | true |
| simdjson (ondemand) | 270.549 | 0.208697 | 1762.37ms | 4604 | 4890 | 5.60942e+06 | 16228.9 | 0.0123381 | 11.2112 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1506.25 | 0.262011 | 310.803ms | 4604 | 40 | 2333.33 | 2915 | 0.0572082 | 2.00275 | 1(Win) | true |
| glaze | 933.822 | 0.74707 | 481.589ms | 4604 | 640 | 789668 | 4701.88 | 0.12612 | 3.24214 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1593.73 | 0.222745 | 293.704ms | 4604 | 80 | 3012.66 | 2755 | 1.0772 | 1.89525 | 1(Win) | true |
| glaze | 1003.31 | 0.227214 | 449.462ms | 4604 | 80 | 7909.81 | 4376.25 | 0.0857633 | 3.01711 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1875.63 | 0.605471 | 1225.62ms | 24579 | 1280 | 7.3288e+06 | 12497.3 | 0.0262487 | 1.61732 | 1(Win) | true |
| jsonifier | 1794.48 | 0.141606 | 1352.48ms | 24579 | 40 | 13685.9 | 13062.5 | 0.362319 | 1.68929 | 2(Loss) | true |
| simdjson (ondemand) | 1243.52 | 0.239338 | 1944.63ms | 24579 | 160 | 325660 | 18850 | 0.172712 | 2.44121 | 3(Loss) | true |
| glaze | 1202.55 | 0.193701 | 1994.01ms | 24579 | 2560 | 3.64945e+06 | 19492.3 | 0.113957 | 2.52432 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2325 | 0.304002 | 1162.09ms | 24579 | 160 | 150298 | 10081.9 | 0.302843 | 1.3044 | 1(Win) | true |
| jsonifier | 2069.2 | 0.277318 | 1310.52ms | 24579 | 1280 | 1.26325e+06 | 11328.2 | 0.370345 | 1.46595 | 2(Loss) | true |
| simdjson (ondemand) | 1312.61 | 0.185158 | 1936.01ms | 24579 | 4890 | 5.34627e+06 | 17857.8 | 0.0485407 | 2.3124 | 3(Loss) | true |
| glaze | 1294.91 | 0.225422 | 1976.47ms | 24579 | 1280 | 2.13132e+06 | 18101.9 | 1.04224 | 2.34411 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6457.4 | 0.221343 | 378.943ms | 24579 | 80 | 5164.56 | 3630 | 0.137931 | 0.46797 | 1(Win) | true |
| glaze | 2889.12 | 0.621864 | 845.191ms | 24579 | 30 | 76367.8 | 8113.33 | 0.8285 | 1.05027 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6759.1 | 0.286363 | 352.213ms | 24579 | 640 | 63119.5 | 3467.97 | 0.139866 | 0.446206 | 1(Win) | true |
| glaze | 3531.5 | 0.519388 | 699.755ms | 24579 | 160 | 190157 | 6637.5 | 0.431277 | 0.855542 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 680.929 | 0.436592 | 171.425ms | 1181 | 4890 | 255010 | 1654.05 | 0.128175 | 4.41698 | 1(Win) | true |
| jsonifier (two-stage) | 618.84 | 0.35193 | 196.659ms | 1181 | 40 | 1641.03 | 1820 | 0.738007 | 4.85356 | 2(Loss) | true |
| glaze | 280.068 | 0.417428 | 410.704ms | 1181 | 2560 | 721398 | 4021.48 | 0.0582468 | 10.8022 | 3(Loss) | true |
| simdjson (ondemand) | 229.887 | 0.808105 | 484.823ms | 1181 | 4890 | 7.66509e+06 | 4899.33 | 0.148298 | 13.1695 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 826.397 | 0.295584 | 155.877ms | 1181 | 2560 | 41545.4 | 1362.89 | 1.02502 | 3.62797 | 1(Win) | true |
| jsonifier (two-stage) | 767.488 | 0.511073 | 174.901ms | 1181 | 40 | 2250 | 1467.5 | 0.0568182 | 3.91044 | 2(Loss) | true |
| glaze | 579.767 | 1.15946 | 209.63ms | 1181 | 4890 | 2.48093e+06 | 1942.66 | 1.35856 | 5.15519 | 3(Loss) | true |
| simdjson (ondemand) | 398.158 | 0.147433 | 310.764ms | 1181 | 320 | 5565.83 | 2828.75 | 0.396127 | 7.54432 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1855.41 | 0.420301 | 65.1174ms | 1181 | 1280 | 8332.07 | 607.031 | 0.307929 | 1.59029 | 1(Win) | true |
| glaze | 1203.38 | 0.287034 | 98.4932ms | 1181 | 320 | 2309.46 | 935.938 | 0.638441 | 2.46865 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1663.19 | 0.878899 | 70.6589ms | 1181 | 640 | 22671.3 | 677.188 | 1.09539 | 1.77983 | 1(Win) | true |
| glaze | 1280.77 | 0.375789 | 92.4714ms | 1181 | 4890 | 53402 | 879.387 | 0.224729 | 2.30441 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1251.18 | 0.296831 | 197.311ms | 2496 | 40 | 1275.64 | 1902.5 | 0.307557 | 2.38864 | 1(Win) | true |
| jsonifier | 1023.08 | 0.352941 | 245.579ms | 2496 | 30 | 2022.99 | 2326.67 | 0 | 2.93738 | 2(Loss) | true |
| glaze | 562.403 | 0.701756 | 441.684ms | 2496 | 80 | 70575.9 | 4232.5 | 0.411765 | 5.3816 | 3(Loss) | true |
| simdjson (ondemand) | 502.652 | 0.181185 | 486.039ms | 2496 | 640 | 47117 | 4735.62 | 0.550727 | 6.02418 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1489.7 | 0.275212 | 182.027ms | 2496 | 2560 | 49507.1 | 1597.89 | 0.00977947 | 2.01668 | 1(Win) | true |
| jsonifier | 1234.15 | 0.186096 | 219.574ms | 2496 | 160 | 2061.32 | 1928.75 | 0.322997 | 2.43987 | 2(Loss) | true |
| glaze | 1117.05 | 0.314323 | 234.102ms | 2496 | 640 | 28712.7 | 2130.94 | 0.800116 | 2.68765 | 3(Loss) | true |
| simdjson (ondemand) | 815.152 | 0.116355 | 314.917ms | 2496 | 1280 | 14777.1 | 2920.16 | 0.320017 | 3.68056 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3617.33 | 0.398843 | 69.4275ms | 2496 | 1280 | 8817.14 | 658.047 | 0.321582 | 0.819359 | 1(Win) | true |
| glaze | 1943.42 | 0.36594 | 125.291ms | 2507 | 1280 | 25942.1 | 1230.23 | 0.273816 | 1.53871 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3180.95 | 0.224522 | 77.2619ms | 2496 | 2560 | 7226.56 | 748.32 | 0.379615 | 0.931953 | 1(Win) | true |
| glaze | 2223.25 | 0.235216 | 111.624ms | 2507 | 1280 | 8189.84 | 1075.39 | 0.240315 | 1.34243 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1002.26 | 0.160327 | 475.387ms | 4926 | 640 | 36142.3 | 4687.19 | 0.219532 | 3.02045 | 1(Win) | true |
| jsonifier (two-stage) | 974.647 | 0.350283 | 498.296ms | 4926 | 30 | 8551.72 | 4820 | 0.346981 | 3.10565 | 2(Loss) | true |
| glaze | 836.652 | 0.976609 | 577.933ms | 4926 | 40 | 120282 | 5615 | 0.560803 | 3.61809 | 3(Loss) | true |
| simdjson (ondemand) | 509.713 | 0.240854 | 926.54ms | 4926 | 320 | 157687 | 9216.56 | 0.165866 | 5.94872 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1236.3 | 0.409777 | 465.473ms | 4926 | 2560 | 620692 | 3799.88 | 0.262827 | 2.44743 | 1(Win) | true |
| jsonifier (two-stage) | 1182.21 | 0.188573 | 494.582ms | 4926 | 80 | 4492.09 | 3973.75 | 0.780275 | 2.56076 | 2(Loss) | true |
| glaze | 1155.74 | 0.532224 | 481.657ms | 4926 | 2560 | 1.19812e+06 | 4064.77 | 0.298801 | 2.61446 | 3(Loss) | true |
| simdjson (ondemand) | 628.258 | 0.475211 | 837.313ms | 4926 | 40 | 50506.4 | 7477.5 | 0.145089 | 4.82553 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5840.31 | 0.277701 | 86.6963ms | 4926 | 160 | 798.349 | 804.375 | 0.233645 | 0.509811 | 1(Win) | true |
| glaze | 3225.61 | 0.2743 | 153.68ms | 4926 | 1280 | 20428 | 1456.41 | 0.80026 | 0.930084 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6686.52 | 0.310709 | 72.6908ms | 4926 | 1280 | 6099.68 | 702.578 | 0.409745 | 0.441873 | 1(Win) | true |
| glaze | 3867.51 | 0.679962 | 127.639ms | 4926 | 4890 | 333583 | 1214.68 | 0.167135 | 0.767208 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1752.78 | 0.106139 | 532.649ms | 9463 | 160 | 4778.3 | 5148.75 | 0.145455 | 1.72785 | 1(Win) | true |
| jsonifier | 1490.65 | 0.757246 | 601.43ms | 9463 | 1280 | 2.69023e+06 | 6054.14 | 1.11563 | 2.03274 | 2(Loss) | true |
| glaze | 1333.15 | 0.700191 | 689.106ms | 9463 | 640 | 1.43784e+06 | 6769.38 | 0.310257 | 2.27325 | 3(Loss) | true |
| simdjson (ondemand) | 971.695 | 0.283381 | 958.861ms | 9463 | 320 | 221661 | 9287.5 | 0.0403606 | 3.12011 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2067.02 | 0.40533 | 525.427ms | 9463 | 4890 | 1.53143e+06 | 4366.01 | 0.0957175 | 1.46437 | 1(Win) | true |
| jsonifier | 1826.85 | 0.22968 | 592.897ms | 9463 | 30 | 3862.07 | 4940 | 0.470114 | 1.66164 | 2(Loss) | true |
| glaze | 1756.12 | 0.551648 | 589.67ms | 9463 | 4890 | 3.92991e+06 | 5138.96 | 0.860429 | 1.72244 | 3(Loss) | true |
| simdjson (ondemand) | 1153.72 | 0.256881 | 866.702ms | 9463 | 4890 | 1.97438e+06 | 7822.21 | 0.0332397 | 2.62736 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9917.16 | 0.416727 | 95.158ms | 9463 | 320 | 4601.88 | 910 | 0.614334 | 0.300921 | 1(Win) | true |
| glaze | 4211.88 | 0.376437 | 227.396ms | 9463 | 640 | 41636.1 | 2142.66 | 1.08915 | 0.714041 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11979.6 | 1.22975 | 78.7655ms | 9463 | 30 | 2574.71 | 753.333 | 0 | 0.246895 | 1(Win) | true |
| glaze | 5280.46 | 1.17516 | 172.952ms | 9463 | 4890 | 1.9725e+06 | 1709.06 | 0.475607 | 0.563535 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 4614.23 | 0.212343 | 60.8665ms | 2821 | 4890 | 7495.32 | 583.047 | 0.892281 | 0.63991 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 4607.44 | 0.182961 | 61.5149ms | 2821 | 1280 | 1460.88 | 583.906 | 0.107152 | 0.639188 | 1(Tie) | true |
| glaze | 2682.31 | 0.807899 | 103.12ms | 2821 | 4890 | 321079 | 1002.99 | 0.033352 | 1.11373 | 3(Loss) | true |
| simdjson (ondemand) | 2053.68 | 0.457362 | 143.837ms | 2821 | 40 | 1435.9 | 1310 | 1.00756 | 1.45879 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 5148.93 | 0.447466 | 57.7039ms | 2821 | 320 | 1749.22 | 522.5 | 0.119474 | 0.571249 | 1(Win) | true |
| jsonifier | 5041.88 | 0.350165 | 57.6134ms | 2821 | 640 | 2234.33 | 533.594 | 0.146199 | 0.582593 | 2(Loss) | true |
| glaze | 3083.46 | 0.610813 | 98.4043ms | 2821 | 80 | 2272.15 | 872.5 | 0 | 0.955317 | 3(Loss) | true |
| simdjson (ondemand) | 2008.05 | 0.287835 | 138.159ms | 2821 | 1280 | 19035.1 | 1339.77 | 0.310014 | 1.49103 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 6137.56 | 0.431688 | 69.4116ms | 4147 | 320 | 2476.1 | 644.375 | 0.290135 | 0.48288 | 1(Win) | true |
| jsonifier | 6050.56 | 0.268287 | 69.0031ms | 4147 | 4890 | 15037.9 | 653.64 | 0.462875 | 0.488004 | 2(Loss) | true |
| glaze | 3464.48 | 0.636133 | 117.716ms | 4147 | 4890 | 257868 | 1141.55 | 0.546318 | 0.863717 | 3(Loss) | true |
| simdjson (ondemand) | 2722.52 | 0.354013 | 146.168ms | 4147 | 640 | 16925.6 | 1452.66 | 0.0753498 | 1.10335 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 6717.43 | 0.521423 | 64.401ms | 4147 | 160 | 1507.86 | 588.75 | 0.422833 | 0.439743 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 6591.48 | 0.799106 | 65.45ms | 4147 | 30 | 689.655 | 600 | 0 | 0.445382 | 1(Tie) | true |
| glaze | 3709.7 | 0.336216 | 114.038ms | 4147 | 640 | 8222.59 | 1066.09 | 0.277697 | 0.794479 | 3(Loss) | true |
| simdjson (ondemand) | 2814.89 | 0.675201 | 143.182ms | 4147 | 4890 | 440069 | 1404.99 | 0.533131 | 1.06418 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1499.3 | 0.31348 | 187.438ms | 2821 | 160 | 5062.5 | 1794.38 | 0.243224 | 2.00032 | 1(Win) | true |
| glaze | 1479.28 | 0.249678 | 185.369ms | 2821 | 4890 | 100827 | 1818.67 | 0.842495 | 2.02855 | 2(Loss) | true |
| jsonifier (two-stage) | 1267.02 | 0.538318 | 221.389ms | 2821 | 30 | 3919.54 | 2123.33 | 0 | 2.37672 | 3(Loss) | true |
| simdjson (ondemand) | 970.516 | 0.253167 | 284.657ms | 2821 | 4890 | 240836 | 2772.04 | 0.27354 | 3.11261 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1951.6 | 0.243851 | 159.8ms | 2821 | 1280 | 14463.8 | 1378.52 | 0.344516 | 1.53619 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1946.42 | 0.259886 | 156.806ms | 2821 | 640 | 8258.12 | 1382.19 | 0.874048 | 1.5289 | 1(Tie) | true |
| jsonifier (two-stage) | 1576.56 | 0.132395 | 193.789ms | 2821 | 4890 | 24959.5 | 1706.44 | 0.0960245 | 1.90719 | 3(Loss) | true |
| simdjson (ondemand) | 1111.41 | 0.370801 | 258.865ms | 2821 | 320 | 25780.2 | 2420.62 | 0.362788 | 2.70825 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5380.63 | 0.716115 | 45.7107ms | 2821 | 40 | 512.821 | 500 | 0 | 0.545569 | 1(Win) | true |
| glaze | 4556.62 | 0.944214 | 68.2255ms | 2819 | 30 | 931.034 | 590 | 0 | 0.639435 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7246.64 | 0.482275 | 39.9903ms | 2821 | 640 | 2051.64 | 371.25 | 0.848896 | 0.398446 | 1(Win) | true |
| glaze | 5066.41 | 0.50432 | 54.38ms | 2819 | 4890 | 35019.6 | 530.634 | 0.430497 | 0.565132 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1865.75 | 0.617679 | 215.942ms | 4147 | 4890 | 838295 | 2119.73 | 0.385138 | 1.61235 | 1(Win) | true |
| jsonifier (two-stage) | 1833.09 | 0.418606 | 228.688ms | 4147 | 80 | 6525.32 | 2157.5 | 0.232288 | 1.64073 | 2(Loss) | true |
| jsonifier | 1481.58 | 0.199287 | 272.385ms | 4147 | 160 | 4527.91 | 2669.38 | 0.256889 | 2.03595 | 3(Loss) | true |
| simdjson (ondemand) | 1429.48 | 0.360753 | 290.563ms | 4147 | 30 | 2988.51 | 2766.67 | 0.598802 | 2.12526 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2358.98 | 0.280807 | 185.774ms | 4147 | 4890 | 108379 | 1676.52 | 0.479941 | 1.27042 | 1(Win) | true |
| jsonifier (two-stage) | 2224.19 | 0.255695 | 196.053ms | 4147 | 640 | 13229.7 | 1778.12 | 0.385154 | 1.34819 | 2(Loss) | true |
| jsonifier | 1853.85 | 0.410333 | 242.558ms | 4147 | 30 | 2298.85 | 2133.33 | 0 | 1.62164 | 3(Loss) | true |
| simdjson (ondemand) | 1610.54 | 0.164464 | 267.209ms | 4147 | 160 | 2609.67 | 2455.62 | 0.380325 | 1.8706 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7944.53 | 0.20707 | 52.7841ms | 4147 | 320 | 340.027 | 497.812 | 0.312891 | 0.36908 | 1(Win) | true |
| glaze | 3259.56 | 0.880675 | 119.481ms | 4145 | 1280 | 146007 | 1212.73 | 1.55044 | 0.915036 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9247.99 | 0.283425 | 45.125ms | 4147 | 4890 | 7183.87 | 427.648 | 0.256965 | 0.313662 | 1(Win) | true |
| glaze | 5557.79 | 0.558917 | 84.4781ms | 4145 | 80 | 1264.24 | 711.25 | 0.886525 | 0.523338 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3172.38 | 0.142224 | 7174.92ms | 466906 | 2560 | 1.02018e+08 | 140360 | 0.0970052 | 0.957876 | 1(Win) | true |
| glaze | 1931.79 | 0.168311 | 5892.59ms | 466906 | 1280 | 1.92654e+08 | 230500 | 0.0816173 | 1.57314 | 2(Loss) | true |
| simdjson (ondemand) | 1136.64 | 0.153274 | 10021ms | 466906 | 1280 | 4.61494e+08 | 391749 | 0.105148 | 2.67326 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3167.56 | 0.37167 | 7171.72ms | 466906 | 640 | 1.74704e+08 | 140574 | 0.375541 | 0.959302 | 1(Win) | true |
| glaze | 1930.65 | 0.211294 | 5869.51ms | 466906 | 1280 | 3.03972e+08 | 230635 | 0.229341 | 1.574 | 2(Loss) | true |
| simdjson (ondemand) | 1132.51 | 0.384544 | 10086.1ms | 466906 | 160 | 3.65751e+08 | 393176 | 0.0399154 | 2.683 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2418.2 | 0.390715 | 6891.66ms | 699405 | 640 | 7.43316e+08 | 275827 | 0.441413 | 1.25615 | 1(Win) | true |
| glaze | 2367.93 | 0.189248 | 7161.39ms | 699405 | 1280 | 3.63741e+08 | 281683 | 0.450217 | 1.28339 | 2(Loss) | true |
| simdjson (ondemand) | 926.78 | 0.298756 | 10029.8ms | 767297 | 640 | 3.56113e+09 | 789564 | 0.368586 | 3.27827 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3760.34 | 0.164274 | 9089.48ms | 699405 | 2560 | 2.1736e+08 | 177379 | 0.117229 | 0.808084 | 1(Win) | true |
| glaze | 2386.92 | 0.279481 | 7118.12ms | 699405 | 320 | 1.9518e+08 | 279441 | 0.16479 | 1.27318 | 2(Loss) | true |
| simdjson (ondemand) | 920.307 | 0.248134 | 10089.9ms | 767297 | 640 | 2.49123e+09 | 795116 | 0.177058 | 3.30133 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2929.37 | 0.223256 | 5229.26ms | 631514 | 1280 | 2.69672e+08 | 205593 | 0.35521 | 1.03739 | 1(Win) | true |
| glaze | 2334.37 | 0.176724 | 6567.44ms | 631514 | 1280 | 2.66091e+08 | 257997 | 0.280676 | 1.30185 | 2(Loss) | true |
