# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

Latest Results: (Oct 16, 2026)
#### Using the following commits:
----
| Jsonifier: [06bd73a](https://github.com/nihilai-collective/jsonifier/commit/06bd73a)  
| Glaze: [e1ab988](https://github.com/stephenberry/glaze/commit/e1ab988)  
| Simdjson: [9c00353](https://github.com/simdjson/simdjson/commit/9c00353)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |
| Glaze (structural-skip) | `NEON64` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. The first epoch is kept only as an initial fallback; every later epoch is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result, whether or not it met the convergence thresholds. A result counts as converged only if that retained epoch has RSE <= 10% AND mean shift <= 5%; non-converged results are still included in the rankings and in win/tie/loss tallying, so a result that did not meet these thresholds should be read with its reduced statistical confidence in mind. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" performs fused scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through structural indexing/stage-1 + stage-2. The 'partial' tests require stage-1 + stage-2, so both jsonifier rows take the two-stage path there)

Each test is run twice. In the standard run, every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. In the run labelled "(Reused)", the object or string is created once and held across iterations; it is cleared (keeping its capacity) outside the timed region before each iteration, so only the parse or serialize work is measured. Parser instances are reused in both.

The "Small" tests use cut-down copies of the large documents, truncated by `GenerateSmallJson.py` so that each minified document is at most 5 KiB (arrays and numerically-keyed objects are shortened to as many leading entries as fit; the document structure is otherwise unchanged). They exercise per-call overhead (setup, dispatch, small allocations) rather than bulk throughput, which is where the standard and "(Reused)" runs differ most.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

Every test whose name contains "Reverse" parses keys in the reverse of their order in the JSON document. This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows. In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

`simdjson (ondemand)` results include this harness's field-mapping layer (per-field lookups, string copies and `unescaped_key()` for maps, in `include/common.hpp`), since materializing into the shared test structs is what these tests measure; hand-tuned glue written by a simdjson specialist could perform differently.

`Results.csv` additionally carries `jsonifier (combined)` and `simdjson (combined)` summary rows. Each is a best-of-variants tally: per test, only the better-ranked of that library's two variants counts, and a test counts as a win when that position is 1 and no other library shares it, so two variants of the same library tying for first count as one win. These rows are not independent results and should not be summed with the per-variant rows.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ae63a25](https://github.com/nihilai-collective/benchmarksuite/commit/ae63a25).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 979.917 | 0.30222 | 97.2029ms | 905 | 1280 | 9069.33 | 880.764 | 2.9105 | 1(Win) | true |
| glaze | 927.848 | 0.627591 | 191.813ms | 905 | 320 | 10905.5 | 930.191 | 0.332688 | 2(Loss) | true |
| jsonifier (two-stage) | 222.847 | 0.128087 | 393.397ms | 905 | 40 | 984.356 | 3872.95 | 1.01086 | 3(Loss) | true |
| simdjson (ondemand) | 182.383 | 0.0622184 | 484.183ms | 905 | 80 | 693.518 | 4732.23 | 0.0242956 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1161.23 | 0.210058 | 80.4558ms | 905 | 160 | 389.997 | 743.244 | 0.000840916 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1153.87 | 0.297395 | 78.9808ms | 905 | 1280 | 6333.72 | 747.981 | 1.14262 | 1(Tie) | true |
| jsonifier (two-stage) | 214.207 | 0.125101 | 414.553ms | 905 | 1280 | 32520.7 | 4029.16 | 0.0257238 | 3(Loss) | true |
| simdjson (ondemand) | 176.688 | 0.0888724 | 482.364ms | 905 | 30 | 565.375 | 4884.73 | 0.141057 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1829.03 | 0.328052 | 51.9204ms | 905 | 160 | 383.406 | 471.875 | 0.126991 | 1(Win) | true |
| glaze | 115.484 | 0.0730738 | 776.093ms | 905 | 30 | 894.74 | 7473.53 | 0.0566123 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2503.3 | 0.968532 | 56.7035ms | 905 | 40 | 446.025 | 344.775 | 1.50224 | 1(Win) | true |
| glaze | 673.962 | 0.26763 | 146.21ms | 905 | 30 | 352.386 | 1280.6 | 0.106607 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 771.619 | 0.669576 | 313.645ms | 1811 | 160 | 35937.8 | 2238.29 | 2.35093 | 1(Win) | true |
| glaze | 748.919 | 0.0555494 | 248.876ms | 1811 | 320 | 525.14 | 2306.13 | 0.0624304 | 2(Loss) | true |
| jsonifier (two-stage) | 267.171 | 0.693881 | 768.56ms | 1811 | 1280 | 2.57537e+06 | 6464.42 | 0.401194 | 3(Loss) | true |
| simdjson (ondemand) | 179.682 | 0.0917018 | 1067.25ms | 1811 | 160 | 12430.9 | 9612 | 0.130266 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 916.652 | 0.667554 | 215.531ms | 1811 | 160 | 25311.7 | 1884.14 | 1.10373 | 1(Win) | true |
| glaze | 854.992 | 0.904175 | 229.55ms | 1811 | 1280 | 426999 | 2020.02 | 2.67882 | 2(Loss) | true |
| jsonifier (two-stage) | 297.564 | 0.872914 | 589.8ms | 1811 | 160 | 410714 | 5804.14 | 0.05478 | 3(Loss) | true |
| simdjson (ondemand) | 161.131 | 2.63221 | 1007.07ms | 1811 | 40 | 3.18404e+06 | 10718.6 | 0.790217 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 260.942 | 0.271571 | 698.357ms | 1811 | 80 | 25846.7 | 6618.73 | 0.393613 | 1(Win) | true |
| glaze | 186.151 | 0.859236 | 1026.34ms | 1798 | 640 | 4.00918e+06 | 9211.4 | 1.32014 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 701.716 | 0.440604 | 263.647ms | 1811 | 640 | 75264.7 | 2461.26 | 2.24236 | 1(Win) | true |
| glaze | 600.435 | 0.10195 | 304.734ms | 1798 | 4890 | 41450.8 | 2855.77 | 0.572248 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1992.96 | 0.049141 | 203.419ms | 3862 | 640 | 527.834 | 1848.05 | 0.321639 | 1(Win) | true |
| glaze | 1111.92 | 0.450682 | 326.285ms | 3862 | 320 | 71312.8 | 3312.37 | 0.107248 | 2(Loss) | true |
| jsonifier (two-stage) | 544.168 | 1.37331 | 656.455ms | 3862 | 80 | 691174 | 6768.3 | 0.504505 | 3(Loss) | true |
| simdjson (ondemand) | 384.8 | 0.211904 | 942.466ms | 3862 | 2560 | 1.05311e+06 | 9571.43 | 1.24111 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2446.95 | 0.176642 | 166.912ms | 3862 | 40 | 282.763 | 1505.17 | 0.0238011 | 1(Win) | true |
| glaze | 1314.05 | 0.90397 | 279.184ms | 3862 | 320 | 205426 | 2802.84 | 0.251121 | 2(Loss) | true |
| jsonifier (two-stage) DID NOT CONVERGE | 591.354 | 0.17071 | 705.677ms | 3862 | 4890 | 552785 | 6228.23 | 6.46741 | -(Loss) | false |
| simdjson (ondemand) | 417.288 | 0.349789 | 969.98ms | 3862 | 640 | 610019 | 8826.25 | 0.776429 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2562.96 | 1.26491 | 184.416ms | 3862 | 4890 | 1.61573e+06 | 1437.05 | 1.27205 | 1(Win) | true |
| glaze | 452.435 | 0.198872 | 1117.79ms | 3862 | 40 | 10483.8 | 8140.6 | 0.0298824 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2853.11 | 2.82237 | 212.298ms | 3862 | 640 | 849561 | 1290.9 | 0.345303 | 1(Win) | true |
| glaze | 1968.12 | 0.10609 | 274.683ms | 3862 | 80 | 315.326 | 1871.38 | 0.025376 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1060.78 | 0.204225 | 864.243ms | 9578 | 2560 | 791700 | 8610.96 | 0.246157 | 1(Win) | true |
| glaze | 981.579 | 0.529764 | 949.241ms | 9578 | 160 | 388852 | 9305.71 | 0.982346 | 2(Loss) | true |
| simdjson (ondemand) | 747.464 | 0.146803 | 1267.91ms | 9578 | 2560 | 823903 | 12220.4 | 0.490835 | 3(Loss) | true |
| jsonifier (two-stage) | 610.395 | 0.250648 | 1564.15ms | 9578 | 1280 | 1.80081e+06 | 14964.6 | 0.157796 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1798.22 | 0.442289 | 820.088ms | 9578 | 4890 | 2.46822e+06 | 5079.62 | 1.58707 | 1(Win) | true |
| glaze | 1511.54 | 0.13358 | 901.786ms | 9578 | 2560 | 166815 | 6043.04 | 0.0653489 | 2(Loss) | true |
| simdjson (ondemand) | 1021.42 | 0.685109 | 1218.55ms | 9578 | 320 | 1.20117e+06 | 8942.7 | 0.665094 | 3(Loss) | true |
| jsonifier (two-stage) | 821.292 | 0.561827 | 1566.46ms | 9578 | 80 | 312356 | 11121.9 | 1.37657 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 983.221 | 0.990973 | 1084.25ms | 9578 | 640 | 5.42439e+06 | 9290.17 | 0.445922 | 1(Win) | true |
| glaze | 949.62 | 0.125076 | 1031.29ms | 9578 | 4890 | 707800 | 9618.89 | 0.724255 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6629.62 | 0.141201 | 166.862ms | 9578 | 30 | 113.545 | 1377.8 | 0.104139 | 1(Win) | true |
| glaze | 4149.25 | 0.129944 | 242.964ms | 9578 | 30 | 245.495 | 2201.43 | 0.0681839 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1923.41 | 0.117 | 201.349ms | 3873 | 80 | 403.842 | 1920.33 | 0.0793506 | 1(Win) | true |
| glaze | 1339.05 | 0.134242 | 295.469ms | 3873 | 30 | 411.344 | 2758.37 | 0.00120846 | 2(Loss) | true |
| jsonifier (two-stage) | 595.659 | 0.177719 | 652.097ms | 3873 | 2560 | 310892 | 6200.83 | 0.294297 | 3(Loss) | true |
| simdjson (ondemand) | 411.661 | 0.591326 | 1010.55ms | 3873 | 80 | 225196 | 8972.39 | 1.18897 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2313.02 | 0.217041 | 165.239ms | 3873 | 2560 | 30751 | 1596.86 | 0.121038 | 1(Win) | true |
| glaze | 1513.58 | 0.138595 | 253.62ms | 3873 | 4890 | 55935.1 | 2440.29 | 0.252593 | 2(Loss) | true |
| jsonifier (two-stage) | 603.631 | 0.63805 | 635.031ms | 3873 | 1280 | 1.95107e+06 | 6118.94 | 0.0246995 | 3(Loss) | true |
| simdjson (ondemand) | 410.708 | 0.295136 | 914.722ms | 3873 | 4890 | 3.44495e+06 | 8993.21 | 1.34892 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2385.28 | 0.415007 | 149.019ms | 3873 | 640 | 26430.7 | 1548.49 | 1.8073 | 1(Win) | true |
| glaze | 460.341 | 0.146539 | 844.155ms | 3873 | 30 | 4147.29 | 8023.57 | 0.670158 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3219.26 | 0.222659 | 138.223ms | 3873 | 80 | 522.1 | 1147.34 | 1.13601 | 1(Win) | true |
| glaze | 2058.05 | 0.192535 | 205.021ms | 3873 | 40 | 477.6 | 1794.7 | 0.0929524 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 631.565 | 0.422393 | 10865.6ms | 2090234 | 30 | 5.33223e+09 | 3.15629e+06 | 0.825539 | 1(Win) | true |
| jsonifier (two-stage) | 564.317 | 0.655955 | 5506.91ms | 2090234 | 30 | 1.61069e+10 | 3.53241e+06 | 2.02981 | 2(Loss) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 406.98 | 3.63965 | 7160.96ms | 2090234 | 30 | 9.53419e+11 | 4.89804e+06 | 8.4373 | -(Tie) | false |
| simdjson (ondemand) STATISTICAL TIE | 390.873 | 0.319729 | 7851.71ms | 2090234 | 80 | 2.12703e+10 | 5.09987e+06 | 2.13009 | 3(Tie) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 782.371 | 0.321894 | 5013.69ms | 2090234 | 80 | 5.38121e+09 | 2.5479e+06 | 3.06922 | 1(Win) | true |
| jsonifier (two-stage) | 695.602 | 0.327017 | 5327.64ms | 2090234 | 80 | 7.02584e+09 | 2.86572e+06 | 0.795365 | 2(Loss) | true |
| glaze | 535.767 | 0.945056 | 6595.42ms | 2090234 | 40 | 4.94554e+10 | 3.72065e+06 | 3.41858 | 3(Loss) | true |
| simdjson (ondemand) | 448.649 | 1.26581 | 7565.2ms | 2090234 | 30 | 9.48927e+10 | 4.44313e+06 | 0.739015 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1973.36 | 0.974282 | 6757.83ms | 2090234 | 30 | 2.90581e+09 | 1.01016e+06 | 3.06759 | 1(Win) | true |
| glaze | 1400.73 | 0.869207 | 9416.51ms | 2090234 | 40 | 6.12048e+09 | 1.42311e+06 | 0.0552651 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze STATISTICAL TIE | 1461.47 | 0.94023 | 10115.5ms | 2090234 | 40 | 6.57867e+09 | 1.36397e+06 | 3.40798 | 1(Tie) | true |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 1155.81 | 14.2412 | 8605.12ms | 2090234 | 40 | 2.41308e+12 | 1.72468e+06 | 11.4623 | -(Tie) | false |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 1684 | 0.453095 | 6153ms | 6661897 | 80 | 2.33767e+10 | 3.77274e+06 | 0.478765 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 1671.83 | 0.58101 | 5890.51ms | 6661897 | 80 | 3.90004e+10 | 3.8002e+06 | 0.663189 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 1134.28 | 1.39025 | 9677.32ms | 6661897 | 40 | 2.42549e+11 | 5.60114e+06 | 6.73007 | -(Tie) | false |
| glaze STATISTICAL TIE | 1107.25 | 1.15716 | 8680.62ms | 6661897 | 30 | 1.32257e+11 | 5.7379e+06 | 0.940771 | 3(Tie) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1966.93 | 1.15153 | 6058.92ms | 6661897 | 80 | 1.10678e+11 | 3.23005e+06 | 2.60336 | 1(Win) | true |
| jsonifier (two-stage) | 1770.89 | 1.328 | 6697.79ms | 6661897 | 30 | 6.80968e+10 | 3.58762e+06 | 2.92421 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 1359.04 | 0.887938 | 8175.54ms | 6661897 | 80 | 1.37844e+11 | 4.67484e+06 | 5.07342 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 908.19 | 6.3673 | 5409.88ms | 6661897 | 40 | 7.93622e+12 | 6.99554e+06 | 6.13964 | -(Loss) | false |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5777.86 | 0.694509 | 6970.78ms | 6661897 | 320 | 1.86624e+10 | 1.09959e+06 | 2.589 | 1(Win) | true |
| glaze | 2604.79 | 0.847413 | 8962.02ms | 6661897 | 160 | 6.83538e+10 | 2.43908e+06 | 4.33065 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6015.69 | 0.532878 | 7086.8ms | 6661897 | 40 | 1.26689e+09 | 1.05612e+06 | 0.909517 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3003.53 | 0.581959 | 6836.98ms | 6661897 | 160 | 2.42458e+10 | 2.11527e+06 | 5.56319 | -(Loss) | false |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1934.47 | 0.843399 | 7080.06ms | 500299 | 40 | 1.73087e+08 | 246643 | 0.832727 | 1(Win) | true |
| jsonifier (two-stage) | 1209.96 | 0.770162 | 5675.87ms | 500299 | 40 | 3.68928e+08 | 394329 | 0.953771 | 2(Loss) | true |
| glaze | 945.067 | 1.02495 | 6068.31ms | 500299 | 640 | 1.71363e+10 | 504855 | 1.46705 | 3(Loss) | true |
| simdjson (ondemand) | 828.213 | 0.373634 | 7463.72ms | 500299 | 640 | 2.96516e+09 | 576087 | 0.386179 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2329.95 | 0.321968 | 6593.19ms | 500299 | 320 | 1.39105e+08 | 204778 | 0.559656 | 1(Win) | true |
| jsonifier (two-stage) | 1450.53 | 0.339298 | 5303.56ms | 500299 | 640 | 7.97162e+08 | 328929 | 4.38465 | 2(Loss) | true |
| glaze | 1124.03 | 0.423002 | 6008.01ms | 500299 | 320 | 1.03167e+09 | 424476 | 0.134553 | 3(Loss) | true |
| simdjson (ondemand) | 919.472 | 0.282605 | 7512.87ms | 500299 | 320 | 6.88163e+08 | 518909 | 0.316928 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6087.99 | 1.41347 | 9380.77ms | 500299 | 160 | 1.96339e+08 | 78371.1 | 0.427447 | 1(Win) | true |
| glaze | 1569.68 | 0.815985 | 8271.34ms | 500299 | 80 | 4.92141e+08 | 303961 | 0.347514 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5006.14 | 1.11207 | 8096.31ms | 500299 | 2560 | 2.87581e+09 | 95307.4 | 0.787904 | 1(Win) | true |
| glaze | 1333.96 | 0.883271 | 8987.51ms | 500299 | 640 | 6.38767e+09 | 357674 | 4.98817 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2806.54 | 0.575619 | 6361.42ms | 1439562 | 160 | 1.26855e+09 | 489169 | 2.10871 | 1(Win) | true |
| jsonifier (two-stage) | 2718.67 | 0.788945 | 7441.15ms | 1439562 | 40 | 6.34893e+08 | 504979 | 0.249076 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1623.04 | 2.13732 | 5431.61ms | 1439562 | 320 | 1.0459e+11 | 845865 | 2.57971 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1558.21 | 2.58683 | 5388.29ms | 1439562 | 320 | 1.66224e+11 | 881057 | 1.02143 | 3(Tie) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3322.98 | 1.70863 | 6113.66ms | 1439562 | 40 | 1.99325e+09 | 413145 | 3.13116 | 1(Win) | true |
| jsonifier (two-stage) | 2776.78 | 0.709705 | 7488.87ms | 1439562 | 30 | 3.69365e+08 | 494413 | 4.88053 | 2(Loss) | true |
| simdjson (ondemand) | 2037.83 | 1.21997 | 5467.66ms | 1439562 | 80 | 5.40399e+09 | 673694 | 1.53427 | 3(Loss) | true |
| glaze | 1778.22 | 1.58654 | 5174.56ms | 1439562 | 320 | 4.8011e+10 | 772050 | 0.708847 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10585.2 | 2.24898 | 6422.6ms | 1439562 | 1280 | 1.08905e+10 | 129698 | 0.699333 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2035.46 | 1.40393 | 8389.74ms | 1439584 | 640 | 5.73874e+10 | 674488 | 8.07671 | -(Loss) | false |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15738.2 | 1.17514 | 5100.57ms | 1439562 | 30 | 3.15248e+07 | 87232 | 0.921066 | 1(Win) | true |
| glaze | 2154 | 4.39567 | 7552.96ms | 1439584 | 40 | 3.13974e+10 | 637371 | 1.44146 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1993.69 | 1.70777 | 3154.81ms | 56369 | 30 | 6.3613e+06 | 26963.9 | 1.32644 | 1(Win) | true |
| glaze STATISTICAL TIE | 1099.13 | 1.2232 | 5401.02ms | 56369 | 1280 | 4.58128e+08 | 48909.2 | 1.88887 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1085.47 | 0.725095 | 6341.21ms | 56369 | 320 | 4.12651e+07 | 49524.6 | 0.124031 | 2(Tie) | true |
| simdjson (ondemand) | 828.064 | 0.784859 | 6451.86ms | 56369 | 4890 | 1.26954e+09 | 64919.7 | 0.844569 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2403.8 | 1.61302 | 2584.88ms | 56369 | 40 | 5.20503e+06 | 22363.6 | 0.0665587 | 1(Win) | true |
| glaze | 1617.08 | 0.941269 | 3983.02ms | 56369 | 80 | 7.83315e+06 | 33243.7 | 2.02634 | 2(Loss) | true |
| jsonifier (two-stage) | 1447.1 | 0.834146 | 5748.03ms | 56369 | 30 | 2.88066e+06 | 37148.7 | 0.0486571 | 3(Loss) | true |
| simdjson (ondemand) | 1346.81 | 1.07171 | 5670.43ms | 56369 | 80 | 1.4639e+07 | 39914.7 | 3.89717 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9049.11 | 2.67441 | 776.827ms | 56369 | 1280 | 3.23099e+07 | 5940.66 | 1.19484 | 1(Win) | true |
| glaze | 2217.45 | 1.91638 | 2927.87ms | 56369 | 30 | 6.47527e+06 | 24243 | 2.18292 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10252 | 0.460297 | 649.731ms | 56369 | 640 | 372835 | 5243.61 | 3.67852 | 1(Win) | true |
| glaze | 2706.49 | 0.071268 | 2759.61ms | 56369 | 30 | 6011.43 | 19862.5 | 0.0902009 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2299.87 | 0.160343 | 3959.73ms | 94370 | 4890 | 1.92519e+07 | 39131.9 | 2.9756 | 1(Win) | true |
| glaze | 1891.94 | 0.297183 | 5177.06ms | 94370 | 640 | 1.27902e+07 | 47569.2 | 2.72209 | 2(Loss) | true |
| jsonifier (two-stage) | 1615.53 | 0.764022 | 6030.05ms | 94370 | 640 | 1.15939e+08 | 55708.1 | 0.584753 | 3(Loss) | true |
| simdjson (ondemand) | 1340.65 | 0.646754 | 7178.75ms | 94370 | 4890 | 9.21776e+08 | 67130.4 | 3.54947 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2834.72 | 0.0400959 | 3856.41ms | 94370 | 30 | 4861.5 | 31748.6 | 0.0698682 | 1(Win) | true |
| glaze | 2006.82 | 0.315214 | 4880.62ms | 94370 | 4890 | 9.77174e+07 | 44846.3 | 0.33699 | 2(Loss) | true |
| simdjson (ondemand) | 1854.88 | 0.801702 | 5660.56ms | 94370 | 640 | 9.68369e+07 | 48519.7 | 2.06935 | 3(Loss) | true |
| jsonifier (two-stage) | 1589.36 | 1.71866 | 6526.38ms | 94370 | 1280 | 1.2123e+09 | 56625.4 | 3.17013 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16248.5 | 0.255278 | 662.013ms | 94370 | 30 | 5997.77 | 5538.87 | 0.27487 | 1(Win) | true |
| glaze | 2514.94 | 0.615557 | 4306.52ms | 94370 | 40 | 1.94093e+06 | 35785.4 | 0.372084 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13907.3 | 1.16137 | 738.96ms | 94370 | 1280 | 7.22997e+06 | 6471.3 | 0.468156 | 1(Win) | true |
| glaze | 2730.83 | 0.244179 | 3527.63ms | 94370 | 640 | 4.14452e+06 | 32956.4 | 0.00992413 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2108.29 | 0.104385 | 615.13ms | 11812 | 4890 | 152115 | 5343.11 | 0.198695 | 1(Win) | true |
| jsonifier (two-stage) | 1012.18 | 0.411839 | 1117.68ms | 11812 | 640 | 1.34451e+06 | 11129.2 | 0.450501 | 2(Loss) | true |
| simdjson (ondemand) | 936.891 | 0.26687 | 1423.08ms | 11812 | 30 | 30888.1 | 12023.6 | 0.556996 | 3(Loss) | true |
| glaze DID NOT CONVERGE | 846.985 | 3.53918 | 1691.19ms | 11812 | 80 | 1.77252e+07 | 13299.9 | 12.1638 | -(Loss) | false |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2357.03 | 0.0952992 | 584.179ms | 11812 | 30 | 622.323 | 4779.23 | 0.0891955 | 1(Win) | true |
| jsonifier (two-stage) | 1109.61 | 1.72988 | 1291.96ms | 11812 | 40 | 1.23368e+06 | 10152.1 | 0.712879 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 914.913 | 1.67399 | 1348.16ms | 11812 | 30 | 1.27442e+06 | 12312.4 | 1.87003 | 3(Tie) | true |
| glaze STATISTICAL TIE | 913.168 | 1.08834 | 1383.38ms | 11812 | 80 | 1.44201e+06 | 12336 | 1.64866 | 3(Tie) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7924.8 | 0.0612984 | 145.164ms | 11812 | 320 | 242.952 | 1421.46 | 0.047903 | 1(Win) | true |
| glaze | 1418.09 | 0.400243 | 792.23ms | 11812 | 1280 | 1.29389e+06 | 7943.65 | 1.28997 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8525.61 | 0.0598872 | 136.153ms | 11812 | 640 | 400.722 | 1321.29 | 0.0438921 | 1(Win) | true |
| glaze | 1665.32 | 0.381734 | 708.44ms | 11812 | 4890 | 3.26049e+06 | 6764.35 | 0.687379 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3212.65 | 0.10063 | 1117.49ms | 31235 | 30 | 2611.75 | 9272.1 | 0.106299 | 1(Win) | true |
| simdjson (ondemand) | 2243.92 | 0.0351932 | 1391.53ms | 31235 | 80 | 1746.13 | 13275 | 0.0312521 | 2(Loss) | true |
| jsonifier (two-stage) | 2149.3 | 0.0222841 | 1551.91ms | 31235 | 80 | 763.073 | 13859.4 | 0.0299526 | 3(Loss) | true |
| glaze | 1981.76 | 0.044042 | 1611.51ms | 31235 | 40 | 1752.98 | 15031.1 | 0.0782878 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3296.43 | 0.43888 | 945.485ms | 31235 | 160 | 251656 | 9036.46 | 0.0235795 | 1(Win) | true |
| jsonifier (two-stage) | 2634.27 | 0.0297131 | 1538.89ms | 31235 | 80 | 903.123 | 11307.9 | 0.115318 | 2(Loss) | true |
| simdjson (ondemand) | 2386.49 | 0.0382006 | 1413.73ms | 31235 | 30 | 682.064 | 12481.9 | 0.0448447 | 3(Loss) | true |
| glaze | 1992.54 | 0.281416 | 1570.24ms | 31235 | 320 | 566388 | 14949.7 | 0.810367 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16956.1 | 0.118779 | 202.603ms | 31235 | 160 | 696.679 | 1756.78 | 0.413815 | 1(Win) | true |
| glaze | 2734.67 | 0.128362 | 1237.87ms | 31235 | 40 | 7820 | 10892.7 | 0.0866006 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18401.4 | 0.26355 | 173.503ms | 31235 | 80 | 1456.12 | 1618.79 | 0.127248 | 1(Win) | true |
| glaze | 2674.28 | 0.234552 | 1306.79ms | 31235 | 4890 | 3.33777e+06 | 11138.7 | 0.266754 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2500.07 | 0.0753863 | 5187ms | 108313 | 640 | 620901 | 41317 | 0.0763479 | 1(Win) | true |
| jsonifier (two-stage) | 1592.46 | 0.0305583 | 7392.1ms | 108313 | 30 | 11787 | 64865.2 | 0.572854 | 2(Loss) | true |
| glaze | 1410.1 | 0.384951 | 8505.39ms | 108313 | 40 | 3.1808e+06 | 73254.1 | 0.481943 | 3(Loss) | true |
| simdjson (ondemand) | 1075.97 | 1.05732 | 5224.23ms | 108313 | 40 | 4.12129e+07 | 96002.1 | 0.916511 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2557.17 | 1.34996 | 4420.99ms | 108313 | 30 | 8.9209e+06 | 40394.4 | 4.4871 | 1(Win) | true |
| glaze | 1546.37 | 0.0630413 | 7775.64ms | 108313 | 30 | 53199.5 | 66798.6 | 0.44918 | 2(Loss) | true |
| jsonifier (two-stage) | 1507.86 | 0.426585 | 7171.04ms | 108313 | 4890 | 4.17597e+08 | 68504.4 | 1.46933 | 3(Loss) | true |
| simdjson (ondemand) | 1311.57 | 0.184745 | 9019.81ms | 108313 | 320 | 6.77447e+06 | 78757.1 | 0.219892 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10012.5 | 0.687367 | 1063.07ms | 108313 | 4890 | 2.45901e+07 | 10316.6 | 0.549635 | 1(Win) | true |
| glaze | 1338.82 | 0.562463 | 7668.51ms | 108313 | 2560 | 4.82111e+08 | 77154.2 | 1.82945 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11928.9 | 0.388719 | 897.599ms | 108313 | 640 | 725118 | 8659.22 | 1.90265 | 1(Win) | true |
| glaze | 1755.26 | 0.878041 | 6566.83ms | 108313 | 80 | 2.13598e+07 | 58849 | 0.164653 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2545.18 | 0.508459 | 8270.03ms | 213963 | 4890 | 8.12571e+08 | 80171.6 | 1.09505 | 1(Win) | true |
| jsonifier (two-stage) | 2358.22 | 0.283217 | 9212.85ms | 213963 | 1280 | 7.68699e+07 | 86527.5 | 0.227692 | 2(Loss) | true |
| simdjson (ondemand) | 1933.19 | 0.541709 | 5865.99ms | 213963 | 640 | 2.09238e+08 | 105551 | 1.48934 | 3(Loss) | true |
| glaze | 1736.93 | 4.26899 | 5843.29ms | 213963 | 30 | 7.54541e+08 | 117478 | 0.440483 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2621.33 | 0.567848 | 8004.47ms | 213963 | 4890 | 9.55446e+08 | 77842.5 | 2.85178 | 1(Win) | true |
| jsonifier (two-stage) | 2550.64 | 0.881786 | 8381.58ms | 213963 | 40 | 1.99052e+07 | 80000 | 0.971306 | 2(Loss) | true |
| glaze | 2006.96 | 1.9741 | 6412.06ms | 213963 | 40 | 1.61139e+08 | 101672 | 0.759556 | 3(Loss) | true |
| simdjson (ondemand) | 1917.83 | 0.64927 | 6007.2ms | 213963 | 2560 | 1.22166e+09 | 106397 | 0.155015 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20145.1 | 0.552121 | 1224.45ms | 213963 | 320 | 1.00083e+06 | 10129.1 | 1.32019 | 1(Win) | true |
| glaze | 1906.97 | 0.211253 | 5900.18ms | 213963 | 2560 | 1.30808e+08 | 107003 | 0.630417 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17293.3 | 2.0372 | 1211.55ms | 213963 | 4890 | 2.82554e+08 | 11799.5 | 1.52804 | 1(Win) | true |
| glaze | 2198.1 | 0.41465 | 5447.19ms | 213963 | 80 | 1.18532e+07 | 92830.7 | 0.177495 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 589.036 | 0.344997 | 10053.4ms | 1834197 | 30 | 3.14892e+09 | 2.96964e+06 | 1.84125 | 1(Win) | true |
| jsonifier (two-stage) | 486.273 | 0.598804 | 5568.16ms | 1834197 | 40 | 1.85593e+10 | 3.59721e+06 | 2.44595 | 2(Loss) | true |
| glaze | 427.11 | 0.366597 | 6536.95ms | 1834197 | 30 | 6.76257e+09 | 4.09549e+06 | 0.603124 | 3(Loss) | true |
| simdjson (ondemand) | 366.993 | 0.156361 | 7788.88ms | 1834197 | 30 | 1.66632e+09 | 4.76638e+06 | 3.24837 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 669.676 | 0.499909 | 10170.6ms | 1834197 | 30 | 5.11525e+09 | 2.61205e+06 | 4.87054 | 1(Win) | true |
| jsonifier (two-stage) | 559.137 | 0.467181 | 5508.5ms | 1834197 | 30 | 6.40837e+09 | 3.12844e+06 | 0.468476 | 2(Loss) | true |
| glaze | 460.922 | 1.05177 | 6866.58ms | 1834197 | 80 | 1.27458e+11 | 3.79506e+06 | 0.424525 | 3(Loss) | true |
| simdjson (ondemand) | 367.77 | 3.42924 | 9715.88ms | 1834197 | 30 | 7.98095e+11 | 4.7563e+06 | 0.60034 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1261.76 | 0.94708 | 9599.9ms | 1834197 | 40 | 6.89565e+09 | 1.38634e+06 | 1.5152 | 1(Win) | true |
| glaze | 755.747 | 0.211808 | 7588.96ms | 1833577 | 80 | 1.92142e+09 | 2.31378e+06 | 3.745 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1288.93 | 0.378543 | 8945.35ms | 1834197 | 30 | 7.91741e+08 | 1.35711e+06 | 1.16245 | 1(Win) | true |
| glaze | 721.192 | 0.900698 | 7626.13ms | 1833577 | 30 | 1.43079e+10 | 2.42464e+06 | 1.38964 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2358.75 | 0.155001 | 6466.55ms | 9930848 | 40 | 1.54932e+09 | 4.01517e+06 | 0.276941 | 1(Win) | true |
| jsonifier (two-stage) | 2112.84 | 0.489724 | 7274.6ms | 9930848 | 30 | 1.44566e+10 | 4.4825e+06 | 0.968865 | 2(Loss) | true |
| glaze | 1689.64 | 0.315134 | 8824.31ms | 9930848 | 80 | 2.49612e+10 | 5.60523e+06 | 1.00854 | 3(Loss) | true |
| simdjson (ondemand) | 1638.74 | 0.230851 | 8828.31ms | 9930848 | 80 | 1.42399e+10 | 5.77932e+06 | 1.95259 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 2393.79 | 2.84811 | 7649.69ms | 9930848 | 80 | 1.01579e+12 | 3.9564e+06 | 0.76779 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2297.77 | 0.513565 | 6948.71ms | 9930848 | 30 | 1.34422e+10 | 4.12173e+06 | 0.856917 | 1(Tie) | true |
| glaze | 1864.29 | 0.343753 | 8787.83ms | 9930848 | 80 | 2.43964e+10 | 5.08009e+06 | 0.305799 | 3(Loss) | true |
| simdjson (ondemand) | 1737.95 | 0.268084 | 9343.31ms | 9930848 | 40 | 8.5369e+09 | 5.44941e+06 | 0.556818 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5897.75 | 0.552484 | 5418.95ms | 9930848 | 160 | 1.25939e+10 | 1.60583e+06 | 1.83704 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2649.3 | 0.422537 | 5840.92ms | 9930228 | 30 | 6.84397e+09 | 3.57461e+06 | 11.1395 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5822.91 | 1.14576 | 5619.68ms | 9930848 | 30 | 1.04184e+10 | 1.62647e+06 | 3.16646 | 1(Win) | true |
| glaze | 2821.7 | 0.138687 | 5075.85ms | 9930228 | 40 | 8.66619e+08 | 3.35621e+06 | 0.169266 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 587.628 | 0.303246 | 9618.12ms | 1834197 | 160 | 1.30376e+10 | 2.97676e+06 | 0.430215 | 1(Win) | true |
| jsonifier (two-stage) DID NOT CONVERGE | 493.596 | 0.647508 | 5661.74ms | 1834197 | 80 | 4.2124e+10 | 3.54385e+06 | 5.1337 | -(Loss) | false |
| glaze DID NOT CONVERGE | 401.005 | 2.31484 | 7471.49ms | 1834197 | 80 | 8.15691e+11 | 4.36211e+06 | 6.91428 | -(Loss) | false |
| simdjson (ondemand) | 329.435 | 1.94003 | 8409.8ms | 1834197 | 40 | 4.24454e+11 | 5.30977e+06 | 2.60948 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 695.864 | 0.271651 | 10302ms | 1834197 | 40 | 1.8652e+09 | 2.51375e+06 | 0.485373 | 1(Win) | true |
| jsonifier (two-stage) | 554.813 | 1.29036 | 5869.04ms | 1834197 | 80 | 1.32408e+11 | 3.15282e+06 | 1.16809 | 2(Loss) | true |
| glaze | 457.702 | 0.549655 | 6699.32ms | 1834197 | 80 | 3.53018e+10 | 3.82176e+06 | 1.43575 | 3(Loss) | true |
| simdjson (ondemand) | 392.431 | 0.576379 | 8224.62ms | 1834197 | 40 | 2.64023e+10 | 4.45741e+06 | 1.81242 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1277.84 | 0.473099 | 9157.14ms | 1834197 | 80 | 3.35533e+09 | 1.3689e+06 | 4.4249 | 1(Win) | true |
| glaze DID NOT CONVERGE | 614.761 | 2.11623 | 8422.45ms | 1833577 | 160 | 5.79741e+11 | 2.84442e+06 | 6.89924 | -(Loss) | false |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1303.64 | 0.417277 | 9080.88ms | 1834197 | 40 | 1.25396e+09 | 1.3418e+06 | 0.1073 | 1(Win) | true |
| glaze | 756.656 | 0.262417 | 7681.18ms | 1833577 | 80 | 2.94222e+09 | 2.311e+06 | 2.89769 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 2313.05 | 0.83302 | 6606.46ms | 9930848 | 30 | 3.49007e+10 | 4.0945e+06 | 8.20844 | -(Win) | false |
| jsonifier (two-stage) | 2076.89 | 1.23139 | 7225.77ms | 9930848 | 80 | 2.5225e+11 | 4.56009e+06 | 1.43457 | 2(Loss) | true |
| glaze | 1678.35 | 0.39207 | 8821.68ms | 9930848 | 80 | 3.91583e+10 | 5.64291e+06 | 2.60029 | 3(Loss) | true |
| simdjson (ondemand) | 1477.64 | 1.23813 | 9866.58ms | 9930848 | 80 | 5.03804e+11 | 6.40941e+06 | 3.41678 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 2372.14 | 5.11633 | 7877.35ms | 9930848 | 30 | 1.25179e+12 | 3.99251e+06 | 9.75725 | -(Tie) | false |
| jsonifier (two-stage) STATISTICAL TIE | 2066.24 | 5.76729 | 7028.59ms | 9930848 | 30 | 2.09641e+12 | 4.58359e+06 | 4.0372 | 1(Tie) | true |
| glaze | 1842.24 | 0.397222 | 8745.17ms | 9930848 | 30 | 1.25103e+10 | 5.14091e+06 | 1.15127 | 3(Loss) | true |
| simdjson (ondemand) | 1701.13 | 0.697347 | 9593.22ms | 9930848 | 80 | 1.20583e+11 | 5.56735e+06 | 1.47823 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 5549.13 | 0.939142 | 5586.93ms | 9930848 | 160 | 4.1106e+10 | 1.70672e+06 | 6.23342 | -(Win) | false |
| glaze DID NOT CONVERGE | 2407.89 | 0.552594 | 6626.91ms | 9930228 | 30 | 1.41702e+10 | 3.93298e+06 | 13.8889 | -(Loss) | false |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4502.53 | 4.09535 | 6415.46ms | 9930848 | 160 | 1.1873e+12 | 2.10344e+06 | 3.98027 | 1(Win) | true |
| glaze | 2767.51 | 0.417218 | 5408.01ms | 9930228 | 80 | 1.63064e+10 | 3.42193e+06 | 1.61463 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1006.17 | 0.488696 | 8660.52ms | 642697 | 40 | 3.54493e+08 | 609165 | 0.327602 | 1(Win) | true |
| jsonifier (two-stage) | 808.264 | 0.428135 | 10256.2ms | 642697 | 80 | 8.43253e+08 | 758321 | 0.0251446 | 2(Loss) | true |
| simdjson (ondemand) | 715.759 | 0.472059 | 5943.04ms | 642697 | 80 | 1.30726e+09 | 856327 | 0.212678 | 3(Loss) | true |
| glaze DID NOT CONVERGE | 499.934 | 8.52215 | 5603.35ms | 642697 | 30 | 3.27497e+11 | 1.22601e+06 | 14.7874 | -(Loss) | false |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1043.06 | 0.649324 | 8397.84ms | 642697 | 160 | 2.32936e+09 | 587620 | 0.60831 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1032.88 | 0.521478 | 8702.49ms | 642697 | 640 | 6.12871e+09 | 593415 | 1.35041 | 1(Tie) | true |
| jsonifier (two-stage) | 805.007 | 0.791818 | 5004.21ms | 642697 | 30 | 1.0904e+09 | 761389 | 1.75169 | 3(Loss) | true |
| simdjson (ondemand) | 777.793 | 0.298643 | 5504.9ms | 642697 | 320 | 1.77231e+09 | 788029 | 0.713119 | 4(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2449.85 | 0.440879 | 6957.64ms | 642697 | 40 | 4.86669e+07 | 250189 | 0.0666486 | 1(Win) | true |
| glaze | 952.94 | 1.95791 | 9709.08ms | 642692 | 80 | 1.26868e+10 | 643188 | 2.66946 | 2(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2428.22 | 0.261925 | 6544.51ms | 642697 | 640 | 2.79751e+08 | 252417 | 0.0814308 | 1(Win) | true |
| glaze | 1055.67 | 0.435291 | 8029.1ms | 642692 | 30 | 1.91614e+08 | 580594 | 0.631678 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1505.87 | 0.133824 | 5257.55ms | 1225964 | 160 | 1.72732e+08 | 776409 | 2.2467 | 1(Win) | true |
| jsonifier (two-stage) | 1437.96 | 0.140206 | 5650.49ms | 1225964 | 40 | 5.19821e+07 | 813075 | 0.029917 | 2(Loss) | true |
| jsonifier | 1340.08 | 0.561489 | 5622.89ms | 1225964 | 80 | 1.91984e+09 | 872463 | 1.14671 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1303.32 | 0.567963 | 6567.08ms | 1225964 | 320 | 8.30695e+09 | 897069 | 7.56451 | -(Loss) | false |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1657.19 | 0.184648 | 10319.6ms | 1225964 | 160 | 2.71534e+08 | 705515 | 0.10393 | 1(Win) | true |
| jsonifier | 1492.08 | 0.269663 | 5201.92ms | 1225964 | 160 | 7.14391e+08 | 783585 | 0.0366912 | 2(Loss) | true |
| simdjson (ondemand) | 1432.67 | 0.14503 | 5698.7ms | 1225964 | 80 | 1.12065e+08 | 816080 | 0.054364 | 3(Loss) | true |
| jsonifier (two-stage) | 1302.91 | 2.72587 | 6117.85ms | 1225964 | 320 | 1.91463e+11 | 897350 | 1.34437 | 4(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4332.74 | 0.22616 | 7220.63ms | 1225964 | 1280 | 4.76727e+08 | 269845 | 4.16938 | 1(Win) | true |
| glaze | 1582.01 | 0.502956 | 9243.45ms | 1225970 | 160 | 2.21067e+09 | 739047 | 1.02907 | 2(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4482.5 | 0.180322 | 7252.24ms | 1225964 | 1280 | 2.83154e+08 | 260830 | 0.178641 | 1(Win) | true |
| glaze | 1664.06 | 0.338871 | 9225.58ms | 1225970 | 640 | 3.62802e+09 | 702604 | 3.05892 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1709.33 | 0.831069 | 7397.66ms | 409725 | 30 | 1.08275e+08 | 228594 | 1.17323 | 1(Win) | true |
| glaze | 927.547 | 0.354157 | 5500.46ms | 409725 | 640 | 1.42457e+09 | 421266 | 0.398331 | 2(Loss) | true |
| jsonifier (two-stage) | 865.985 | 0.255784 | 6206.78ms | 409725 | 80 | 1.06561e+08 | 451214 | 0.262251 | 3(Loss) | true |
| simdjson (ondemand) | 816.747 | 0.802433 | 6464.12ms | 409725 | 30 | 4.42129e+08 | 478415 | 0.327266 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2216.15 | 0.321839 | 5404.91ms | 409725 | 320 | 1.03042e+08 | 176316 | 0.0935026 | 1(Win) | true |
| jsonifier (two-stage) | 1162.76 | 0.259008 | 5666.07ms | 409725 | 320 | 2.42428e+08 | 336050 | 0.134621 | 2(Loss) | true |
| glaze | 1036.17 | 0.278516 | 5695.97ms | 409725 | 160 | 1.76502e+08 | 377106 | 2.80303 | 3(Loss) | true |
| simdjson (ondemand) | 919.362 | 0.269574 | 6289.96ms | 409725 | 40 | 5.25084e+07 | 425017 | 2.80085 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8337.92 | 0.197403 | 4835.23ms | 409725 | 1280 | 1.09543e+07 | 46863.5 | 0.0845275 | 1(Win) | true |
| glaze | 1671.92 | 0.154941 | 6370.74ms | 409725 | 320 | 4.19602e+07 | 233711 | 0.300476 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8205.23 | 0.27779 | 5119.59ms | 409725 | 640 | 1.12e+07 | 47621.4 | 0.050795 | 1(Win) | true |
| glaze | 1695.17 | 0.677879 | 5967.86ms | 409725 | 160 | 3.90644e+08 | 230504 | 2.10274 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2255.16 | 0.365026 | 9398.63ms | 785750 | 30 | 4.41348e+07 | 332282 | 0.0162639 | 1(Win) | true |
| glaze | 1493.39 | 0.30342 | 8372.43ms | 785750 | 40 | 9.27195e+07 | 501778 | 0.0953837 | 2(Loss) | true |
| simdjson (ondemand) | 1443.65 | 0.17318 | 6723.38ms | 785750 | 80 | 6.46438e+07 | 519065 | 0.347174 | 3(Loss) | true |
| jsonifier (two-stage) | 1240.36 | 0.152803 | 8153.6ms | 785750 | 160 | 1.36349e+08 | 604137 | 0.179133 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2674.3 | 0.188418 | 8515.5ms | 785750 | 160 | 4.45976e+07 | 280204 | 1.6763 | 1(Win) | true |
| jsonifier (two-stage) | 1747.95 | 0.249873 | 7886.56ms | 785750 | 160 | 1.83598e+08 | 428701 | 0.06136 | 2(Loss) | true |
| glaze | 1653.75 | 0.344875 | 6285.71ms | 785750 | 30 | 7.32608e+07 | 453121 | 0.239988 | 3(Loss) | true |
| simdjson (ondemand) | 1597.37 | 0.206541 | 7316.46ms | 785750 | 40 | 3.75516e+07 | 469115 | 0.314166 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14228.9 | 0.230956 | 5937.8ms | 785750 | 4890 | 7.23429e+07 | 52664.1 | 2.08584 | 1(Win) | true |
| glaze DID NOT CONVERGE | 1886.22 | 2.51165 | 5211.61ms | 785750 | 640 | 6.3721e+10 | 397276 | 5.29546 | -(Loss) | false |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14888.5 | 0.371377 | 5335.94ms | 785750 | 160 | 5.59004e+06 | 50330.7 | 0.114923 | 1(Win) | true |
| glaze | 2333.78 | 0.395268 | 8753.97ms | 785750 | 1280 | 2.06179e+09 | 321089 | 2.55041 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 3666.28 | 0.678781 | 7873.69ms | 264040 | 80 | 1.73876e+07 | 68682.2 | 0.395783 | 1(Win) | true |
| jsonifier | 3421.38 | 0.38674 | 7699.28ms | 264040 | 2560 | 2.07404e+08 | 73598.4 | 1.23581 | 2(Loss) | true |
| simdjson (ondemand) | 3091.25 | 0.723691 | 9298.88ms | 264040 | 30 | 1.04256e+07 | 81458.4 | 0.524133 | 3(Loss) | true |
| glaze | 1792.32 | 1.85211 | 7125.14ms | 264040 | 40 | 2.70833e+08 | 140493 | 0.147347 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3673.21 | 0.666458 | 5020.67ms | 264040 | 80 | 1.66987e+07 | 68552.6 | 2.96464 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3634.8 | 0.565683 | 7499.24ms | 264040 | 640 | 9.8289e+07 | 69277.1 | 0.330159 | 1(Tie) | true |
| simdjson (ondemand) | 2694.8 | 1.45606 | 9347.6ms | 264040 | 640 | 1.18475e+09 | 93442.2 | 1.35867 | 3(Loss) | true |
| glaze | 1992.9 | 0.254027 | 7079.53ms | 264040 | 160 | 1.64835e+07 | 126353 | 0.245281 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4276.4 | 0.471603 | 9406.19ms | 399947 | 4890 | 8.65187e+08 | 89191.7 | 0.691045 | 1(Win) | true |
| jsonifier (two-stage) | 4196.6 | 0.184508 | 9554.83ms | 399947 | 4890 | 1.37514e+08 | 90887.6 | 0.43716 | 2(Loss) | true |
| simdjson (ondemand) | 3956 | 0.208433 | 5194.9ms | 399947 | 2560 | 1.03388e+08 | 96415.5 | 2.75093 | 3(Loss) | true |
| glaze | 2649.72 | 0.431181 | 8630.14ms | 399947 | 160 | 6.16374e+07 | 143947 | 0.675282 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 4502.93 | 0.0945404 | 9455.2ms | 399947 | 4890 | 3.13587e+07 | 84704.6 | 1.91148 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 4386.55 | 3.1538 | 5472.8ms | 399947 | 40 | 3.00807e+08 | 86952 | 0.109222 | 1(Tie) | true |
| simdjson (ondemand) | 4217.16 | 0.187261 | 6079.1ms | 399947 | 320 | 9.1793e+06 | 90444.6 | 0.0775523 | 3(Loss) | true |
| glaze DID NOT CONVERGE | 2316.48 | 0.856708 | 8902.1ms | 399947 | 1280 | 2.54697e+09 | 164655 | 5.04261 | -(Loss) | false |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1611.11 | 2.65335 | 7952.24ms | 264040 | 30 | 5.1594e+08 | 156294 | 0.664611 | 1(Win) | true |
| jsonifier (two-stage) | 1506.49 | 0.328768 | 8623.74ms | 264040 | 160 | 4.83178e+07 | 167149 | 0.611732 | 2(Loss) | true |
| simdjson (ondemand) | 1481.17 | 0.275435 | 9384.26ms | 264040 | 160 | 3.50822e+07 | 170006 | 0.259437 | 3(Loss) | true |
| glaze | 1362.48 | 1.82109 | 5176.74ms | 264040 | 30 | 3.39833e+08 | 184817 | 0.416517 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2625.35 | 0.133329 | 5947.72ms | 264040 | 1280 | 2.09327e+07 | 95914.1 | 0.285944 | 1(Win) | true |
| simdjson (ondemand) | 1728.32 | 0.105476 | 8936.65ms | 264040 | 2560 | 6.04562e+07 | 145695 | 0.722993 | 2(Loss) | true |
| glaze STATISTICAL TIE | 1627.28 | 0.202635 | 9399.71ms | 264040 | 640 | 6.2925e+07 | 154741 | 0.0515167 | 3(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1548.86 | 4.91107 | 5093.39ms | 264040 | 640 | 4.07988e+10 | 162576 | 1.09775 | 3(Tie) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12866 | 0.141752 | 2046.16ms | 264040 | 640 | 492592 | 19571.5 | 0.0389764 | 1(Win) | true |
| glaze | 3381.17 | 0.0562471 | 7641.66ms | 263923 | 40 | 70126.2 | 74440.6 | 0.0323293 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13211.8 | 0.0469475 | 2087.51ms | 264040 | 40 | 3202.59 | 19059.3 | 0.0636138 | 1(Win) | true |
| glaze | 3967.09 | 0.0603266 | 6515.8ms | 263923 | 4890 | 7.16367e+06 | 63446.1 | 0.335536 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2160.11 | 1.22987 | 5667.08ms | 399947 | 30 | 1.4148e+08 | 176574 | 1.49302 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1989.45 | 0.448096 | 5101.67ms | 399947 | 30 | 2.21412e+07 | 191721 | 0.300539 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1977.94 | 0.588812 | 5458.46ms | 399947 | 30 | 3.86769e+07 | 192836 | 0.203591 | 2(Tie) | true |
| glaze | 1738.23 | 0.651049 | 5587.82ms | 399947 | 80 | 1.6327e+08 | 219429 | 0.167739 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2717.44 | 0.305535 | 10047.2ms | 399947 | 30 | 5.51732e+06 | 140360 | 0.130612 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 2269.96 | 0.531335 | 5024.47ms | 399947 | 640 | 5.10133e+08 | 168029 | 0.046162 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2259.25 | 0.976944 | 10119.5ms | 399947 | 320 | 8.70492e+08 | 168825 | 2.74639 | 2(Tie) | true |
| glaze | 2138.73 | 0.889923 | 5260.18ms | 399947 | 30 | 7.55645e+07 | 178339 | 0.294356 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15833.1 | 0.455938 | 2386.51ms | 399947 | 4890 | 5.89917e+07 | 24089.9 | 0.151335 | 1(Win) | true |
| glaze | 3576.89 | 0.268211 | 6116.24ms | 399830 | 160 | 1.30802e+07 | 106603 | 0.312152 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 17137.6 | 0.180008 | 2523.73ms | 399947 | 4890 | 7.84864e+06 | 22256.2 | 7.07262 | -(Win) | false |
| glaze | 3777.49 | 1.23965 | 5209.5ms | 399830 | 80 | 1.25267e+08 | 100942 | 1.34119 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 652.938 | 0.0739425 | 707.387ms | 4630 | 40 | 1000.15 | 6762.52 | 0.0427785 | 1(Win) | true |
| jsonifier (two-stage) | 597.704 | 0.0703291 | 829.423ms | 4630 | 40 | 1079.74 | 7387.45 | 0.0200751 | 2(Loss) | true |
| glaze | 406.76 | 0.157553 | 1157.08ms | 4630 | 1280 | 374411 | 10855.3 | 0.215724 | 3(Loss) | true |
| simdjson (ondemand) | 382.893 | 0.0641127 | 1197.34ms | 4630 | 30 | 1639.9 | 11532 | 0.109091 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 777.334 | 0.132159 | 704.678ms | 4630 | 4890 | 275581 | 5680.33 | 0.183175 | 1(Win) | true |
| jsonifier (two-stage) | 698.583 | 0.334626 | 818.581ms | 4630 | 640 | 286303 | 6320.67 | 0.534575 | 2(Loss) | true |
| glaze | 470.175 | 0.0330493 | 1098.13ms | 4630 | 80 | 770.65 | 9391.21 | 0.226692 | 3(Loss) | true |
| simdjson (ondemand) | 417.933 | 1.58629 | 1456.51ms | 4630 | 80 | 2.24699e+06 | 10565.1 | 1.67232 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 1943.48 | 6.08563 | 376.054ms | 4630 | 80 | 1.52934e+06 | 2271.96 | 7.50374 | -(Win) | false |
| glaze | 1310.23 | 0.218589 | 402.243ms | 4630 | 1280 | 69459.7 | 3370.02 | 3.85168 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2305.43 | 0.194716 | 206.373ms | 4630 | 30 | 417.237 | 1915.27 | 0.0730435 | 1(Win) | true |
| glaze | 1542.55 | 0.350238 | 373.725ms | 4630 | 30 | 3015.29 | 2862.47 | 0.142271 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1583.36 | 0.326045 | 908.423ms | 14795 | 1280 | 1.08053e+06 | 8911.18 | 0.787969 | 1(Win) | true |
| jsonifier (two-stage) | 1379.55 | 1.28426 | 1023.19ms | 14795 | 2560 | 4.41672e+07 | 10227.7 | 2.32687 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1093.46 | 0.53907 | 1473.3ms | 14795 | 80 | 387084 | 12903.6 | 3.62148 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1091.3 | 0.0585873 | 1410.9ms | 14795 | 80 | 4590.26 | 12929.1 | 0.568328 | 3(Tie) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2003.76 | 0.17469 | 862.719ms | 14795 | 30 | 4539.36 | 7041.57 | 0.0194048 | 1(Win) | true |
| jsonifier (two-stage) | 1885.97 | 0.0933375 | 898.992ms | 14795 | 40 | 1950.44 | 7481.35 | 0.233344 | 2(Loss) | true |
| glaze | 1189.17 | 0.553493 | 1505.09ms | 14795 | 160 | 690063 | 11865.1 | 0.396367 | 3(Loss) | true |
| simdjson (ondemand) | 1013.03 | 0.872257 | 1529.64ms | 14795 | 2560 | 3.77842e+07 | 13928.1 | 1.2883 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6349.86 | 0.226231 | 241.502ms | 14795 | 30 | 758.102 | 2222.03 | 0.0465256 | 1(Win) | true |
| glaze | 2335.69 | 1.06463 | 629.26ms | 14795 | 2560 | 1.05886e+07 | 6040.88 | 0.283906 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6471.87 | 0.257466 | 229.956ms | 14795 | 640 | 20164.6 | 2180.14 | 0.682622 | 1(Win) | true |
| glaze | 2404.5 | 2.05666 | 569.305ms | 14795 | 4890 | 7.12222e+07 | 5868.01 | 4.09138 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1217.29 | 0.461911 | 496.275ms | 5092 | 160 | 54328.5 | 3989.29 | 0.887883 | 1(Win) | true |
| jsonifier (two-stage) | 896.047 | 0.486158 | 583.136ms | 5092 | 4890 | 3.39452e+06 | 5419.48 | 0.25238 | 2(Loss) | true |
| glaze | 845.992 | 0.13741 | 664.89ms | 5092 | 30 | 1866.4 | 5740.13 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 771.122 | 0.252379 | 724.518ms | 5092 | 640 | 161665 | 6297.46 | 0.507879 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1671.34 | 0.689174 | 417.71ms | 5092 | 4890 | 1.96072e+06 | 2905.53 | 3.01865 | 1(Win) | true |
| jsonifier (two-stage) | 1214.98 | 0.433118 | 631.423ms | 5092 | 1280 | 383588 | 3996.88 | 0.576842 | 2(Loss) | true |
| glaze | 1085.79 | 0.18447 | 527.553ms | 5092 | 1280 | 87126.2 | 4472.44 | 0.552089 | 3(Loss) | true |
| simdjson (ondemand) | 960.555 | 0.255806 | 596.685ms | 5092 | 640 | 107037 | 5055.52 | 0.193852 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7482.88 | 0.374885 | 77.5822ms | 5092 | 80 | 473.505 | 648.962 | 0.00192611 | 1(Win) | true |
| glaze | 1613.66 | 0.105213 | 324.508ms | 5092 | 40 | 401.01 | 3009.38 | 0.0368429 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8343.11 | 0.194468 | 77.4911ms | 5092 | 160 | 204.991 | 582.05 | 0.0494188 | 1(Win) | true |
| glaze | 1825.42 | 0.227906 | 285.19ms | 5092 | 40 | 1470.36 | 2660.28 | 0.13233 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2045.28 | 0.222942 | 616.84ms | 11724 | 80 | 11882.8 | 5466.66 | 0.246873 | 1(Win) | true |
| jsonifier (two-stage) | 1595.98 | 1.09479 | 726.854ms | 11724 | 1280 | 7.52955e+06 | 7005.64 | 0.0312708 | 2(Loss) | true |
| simdjson (ondemand) | 1460.75 | 1.18492 | 833.592ms | 11724 | 80 | 658070 | 7654.21 | 0.647545 | 3(Loss) | true |
| glaze | 1392.36 | 0.574086 | 827.138ms | 11724 | 4890 | 1.03922e+07 | 8030.13 | 0.465428 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2612.84 | 0.352662 | 610.683ms | 11724 | 30 | 6832.23 | 4279.2 | 0.0327057 | 1(Win) | true |
| jsonifier (two-stage) | 2078.95 | 0.646935 | 669.693ms | 11724 | 2560 | 3.09901e+06 | 5378.12 | 0.0307575 | 2(Loss) | true |
| glaze | 1793.54 | 0.191537 | 732.957ms | 11724 | 640 | 91246.6 | 6233.99 | 1.00196 | 3(Loss) | true |
| simdjson (ondemand) | 1680.5 | 0.971273 | 781.344ms | 11724 | 2560 | 1.06904e+07 | 6653.28 | 1.4313 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14891.2 | 0.663743 | 80.8942ms | 11724 | 1280 | 31790.8 | 750.837 | 0.00801254 | 1(Win) | true |
| glaze | 2037.52 | 0.458609 | 538.184ms | 11746 | 640 | 406859 | 5497.8 | 0.592839 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17577.2 | 0.621806 | 78.8454ms | 11724 | 30 | 469.334 | 636.1 | 0.655943 | 1(Win) | true |
| glaze | 2671.93 | 0.098748 | 456.019ms | 11746 | 160 | 2742.24 | 4192.42 | 0.253029 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1656.8 | 1.92308 | 416.487ms | 4857 | 40 | 115625 | 2795.75 | 3.3649 | 1(Win) | true |
| glaze | 1238.82 | 0.189824 | 501.533ms | 4857 | 80 | 4030.1 | 3739.05 | 0.378529 | 2(Loss) | true |
| jsonifier (two-stage) | 1093.63 | 0.151516 | 428.646ms | 4857 | 4890 | 201382 | 4235.43 | 2.08126 | 3(Loss) | true |
| simdjson (ondemand) | 1074.1 | 0.163837 | 437.786ms | 4857 | 4890 | 244105 | 4312.43 | 0.79612 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2461.51 | 0.0655289 | 220.483ms | 4857 | 320 | 486.573 | 1881.77 | 0.111473 | 1(Win) | true |
| glaze | 1696.93 | 0.19423 | 344.466ms | 4857 | 80 | 2248.69 | 2729.62 | 0.13628 | 2(Loss) | true |
| simdjson (ondemand) | 1545.97 | 0.127811 | 327.327ms | 4857 | 2560 | 37541.7 | 2996.17 | 0.0839429 | 3(Loss) | true |
| jsonifier (two-stage) | 1487.69 | 0.219785 | 381.948ms | 4857 | 40 | 1873.13 | 3113.55 | 0.141652 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9501.53 | 0.698989 | 54.828ms | 4857 | 40 | 464.462 | 487.5 | 0.563845 | 1(Win) | true |
| glaze | 2250.23 | 0.0966963 | 217.437ms | 4857 | 320 | 1267.8 | 2058.45 | 0.197422 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 9295.87 | 1.01921 | 64.2361ms | 4857 | 2560 | 66026.9 | 498.285 | 23.6999 | -(Win) | false |
| glaze | 2617.24 | 0.112404 | 230.322ms | 4857 | 160 | 633.192 | 1769.8 | 0.143877 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1999.01 | 0.191351 | 367.151ms | 7376 | 4890 | 221708 | 3518.89 | 0.0621167 | 1(Win) | true |
| simdjson (ondemand) | 1651.65 | 0.124104 | 437.285ms | 7376 | 4890 | 136611 | 4258.95 | 0.565192 | 2(Loss) | true |
| jsonifier (two-stage) | 1539.9 | 0.166367 | 472.772ms | 7376 | 30 | 1732.65 | 4568.03 | 0.123897 | 3(Loss) | true |
| glaze | 1490.63 | 1.2981 | 469.567ms | 7376 | 160 | 600393 | 4719 | 0.860273 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2520.95 | 0.113073 | 329.084ms | 7376 | 30 | 298.644 | 2790.33 | 0.00238926 | 1(Win) | true |
| glaze | 2221.34 | 0.218553 | 331.341ms | 7376 | 30 | 1436.98 | 3166.7 | 0.352816 | 2(Loss) | true |
| simdjson (ondemand) | 2183.97 | 0.0613244 | 360.286ms | 7376 | 320 | 1248.44 | 3220.88 | 0.199662 | 3(Loss) | true |
| jsonifier (two-stage) | 2031.61 | 0.105829 | 447.781ms | 7376 | 30 | 402.806 | 3462.43 | 0.282239 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13176.9 | 0.419217 | 58.1646ms | 7376 | 80 | 400.669 | 533.837 | 0.0960953 | 1(Win) | true |
| glaze | 2320.72 | 0.456208 | 308.776ms | 7376 | 1280 | 244755 | 3031.08 | 0.0314609 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14696.1 | 0.489513 | 53.5473ms | 7376 | 80 | 439.192 | 478.65 | 0.119985 | 1(Win) | true |
| glaze | 2814.87 | 0.0896874 | 260.749ms | 7376 | 160 | 803.723 | 2498.97 | 0.0215134 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1847.47 | 0.248835 | 230.408ms | 4390 | 2560 | 81402.1 | 2266.14 | 1.12701 | 1(Win) | true |
| jsonifier (two-stage) | 1000.78 | 0.996872 | 460.317ms | 4390 | 80 | 139130 | 4183.36 | 0.222504 | 2(Loss) | true |
| glaze | 881.791 | 0.605689 | 500.933ms | 4390 | 160 | 132317 | 4747.87 | 3.11337 | 3(Loss) | true |
| simdjson (ondemand) | 827.065 | 0.234893 | 557.413ms | 4390 | 4890 | 691351 | 5062.03 | 0.788382 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2220.94 | 0.196262 | 210.452ms | 4390 | 2560 | 35040.1 | 1885.07 | 0.339884 | 1(Win) | true |
| jsonifier (two-stage) | 1234.39 | 0.222975 | 421.57ms | 4390 | 40 | 2287.67 | 3391.65 | 0.412012 | 2(Loss) | true |
| glaze | 991.658 | 0.117504 | 463.274ms | 4390 | 80 | 1968.79 | 4221.85 | 0.0733736 | 3(Loss) | true |
| simdjson (ondemand) | 918.811 | 0.343634 | 517.399ms | 4390 | 1280 | 313818 | 4556.57 | 0.0512915 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6890.9 | 0.147899 | 66.8239ms | 4390 | 2560 | 2067.04 | 607.559 | 0.439822 | 1(Win) | true |
| glaze | 1285.12 | 2.13053 | 342.082ms | 4390 | 640 | 3.08315e+06 | 3257.77 | 0.198622 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7346.85 | 0.689396 | 63.3631ms | 4390 | 2560 | 39509.8 | 569.854 | 2.24819 | 1(Win) | true |
| glaze | 1629.32 | 0.117471 | 276.544ms | 4390 | 160 | 1457.8 | 2569.55 | 0.113963 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2855.76 | 0.450829 | 416.493ms | 11521 | 160 | 48137.2 | 3847.41 | 0.376429 | 1(Win) | true |
| simdjson (ondemand) | 2065.77 | 0.0821057 | 553.654ms | 11521 | 40 | 762.82 | 5318.73 | 1.07213 | 2(Loss) | true |
| jsonifier (two-stage) | 1886.27 | 0.32508 | 597.966ms | 11521 | 640 | 229473 | 5824.86 | 0.378988 | 3(Loss) | true |
| glaze | 1623.8 | 1.34394 | 781.122ms | 11521 | 640 | 5.29241e+06 | 6766.4 | 0.0862769 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3184.83 | 0.0985564 | 477.292ms | 11521 | 40 | 462.42 | 3449.88 | 0.162831 | 1(Win) | true |
| jsonifier (two-stage) | 2439.34 | 0.072789 | 578.249ms | 11521 | 40 | 429.959 | 4504.2 | 0.0333133 | 2(Loss) | true |
| simdjson (ondemand) | 2262.54 | 0.0809946 | 538.635ms | 11521 | 40 | 618.815 | 4856.18 | 0.0956742 | 3(Loss) | true |
| glaze | 1733.52 | 0.421918 | 689.089ms | 11521 | 4890 | 3.49693e+06 | 6338.12 | 4.60016 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16327 | 0.353855 | 72.8804ms | 11521 | 40 | 226.818 | 672.95 | 0.520315 | 1(Win) | true |
| glaze | 2348.03 | 0.293475 | 538.943ms | 11521 | 640 | 120696 | 4679.36 | 0.0686722 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17871.2 | 0.0705359 | 68.8382ms | 11521 | 2560 | 481.433 | 614.805 | 0.10891 | 1(Win) | true |
| glaze | 2812.76 | 0.151667 | 406.472ms | 11521 | 40 | 1403.97 | 3906.22 | 0.160383 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2462.34 | 0.133523 | 188.848ms | 4669 | 80 | 466.399 | 1808.33 | 0.113236 | 1(Win) | true |
| jsonifier (two-stage) | 1371.22 | 2.00219 | 457.596ms | 4669 | 30 | 126814 | 3247.27 | 0.997346 | 2(Loss) | true |
| glaze | 1186.16 | 0.0728645 | 392.339ms | 4669 | 160 | 1197.05 | 3753.87 | 0.187288 | 3(Loss) | true |
| simdjson (ondemand) | 1082.28 | 0.265953 | 504.62ms | 4669 | 1280 | 153246 | 4114.2 | 4.22392 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2792.93 | 0.137241 | 210.735ms | 4669 | 80 | 382.987 | 1594.28 | 0.10046 | 1(Win) | true |
| jsonifier (two-stage) | 1621.58 | 0.474708 | 396.77ms | 4669 | 2560 | 434978 | 2745.91 | 0.297645 | 2(Loss) | true |
| glaze | 1383.3 | 0.609917 | 341.608ms | 4669 | 320 | 123341 | 3218.9 | 0.0361279 | 3(Loss) | true |
| simdjson (ondemand) | 1278.32 | 0.417451 | 402.326ms | 4669 | 40 | 8457.47 | 3483.25 | 0.121864 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11278 | 0.428691 | 51.3661ms | 4669 | 160 | 458.342 | 394.812 | 0.255795 | 1(Win) | true |
| glaze | 1584.1 | 0.136846 | 310.696ms | 4669 | 80 | 1183.68 | 2810.88 | 0.131459 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13296.6 | 0.143531 | 37.6587ms | 4669 | 320 | 73.9279 | 334.875 | 0.00746491 | 1(Win) | true |
| glaze | 1841.18 | 0.132197 | 246.115ms | 4669 | 4890 | 49981.2 | 2418.39 | 0.126862 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2819.48 | 0.354304 | 323.784ms | 9249 | 1280 | 157258 | 3128.43 | 0.328803 | 1(Win) | true |
| jsonifier (two-stage) | 2551.47 | 0.147095 | 359.896ms | 9249 | 30 | 775.757 | 3457.03 | 0.0424436 | 2(Loss) | true |
| simdjson (ondemand) | 1991.49 | 0.0551879 | 486.663ms | 9249 | 160 | 955.962 | 4429.11 | 0.0251116 | 3(Loss) | true |
| glaze | 1898.83 | 0.363741 | 496.654ms | 9249 | 640 | 182718 | 4645.25 | 0.355418 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3152.97 | 0.065738 | 310.744ms | 9249 | 320 | 1082.26 | 2797.53 | 0.35964 | 1(Win) | true |
| jsonifier (two-stage) | 2745.75 | 0.113654 | 363.279ms | 9249 | 30 | 399.909 | 3212.43 | 0.0290622 | 2(Loss) | true |
| simdjson (ondemand) | 2317.42 | 0.070837 | 403.572ms | 9249 | 160 | 1163.11 | 3806.19 | 0.218872 | 3(Loss) | true |
| glaze | 2190.46 | 0.136456 | 548.307ms | 9249 | 160 | 4830.86 | 4026.79 | 0.0580825 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 21168.9 | 0.0179996 | 47.3051ms | 9249 | 40 | 0.225 | 416.675 | 0.002 | 1(Win) | true |
| glaze | 2078.49 | 0.174406 | 442.059ms | 9249 | 40 | 2191.18 | 4243.73 | 0.309498 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 24190.7 | 0.554537 | 42.955ms | 9249 | 80 | 327.073 | 364.625 | 0.0205648 | 1(Win) | true |
| glaze | 2117.99 | 0.891339 | 495.763ms | 9249 | 1280 | 1.76376e+06 | 4164.58 | 4.09751 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 545.75 | 1.01301 | 851.763ms | 4604 | 160 | 1.06275e+06 | 8045.29 | 0.733062 | 1(Win) | true |
| jsonifier (two-stage) | 473.318 | 0.278412 | 1041.87ms | 4604 | 30 | 20010.7 | 9276.47 | 0.831353 | 2(Loss) | true |
| glaze | 344.188 | 0.0330472 | 1328.9ms | 4604 | 80 | 1421.8 | 12756.7 | 0.0378089 | 3(Loss) | true |
| simdjson (ondemand) | 321.396 | 0.0656596 | 1512.47ms | 4604 | 40 | 3218.45 | 13661.4 | 0.165949 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 724.924 | 0.202876 | 784.365ms | 4604 | 1280 | 193267 | 6056.8 | 0.0155325 | 1(Win) | true |
| jsonifier (two-stage) | 572.412 | 0.946344 | 1151.67ms | 4604 | 320 | 1.68617e+06 | 7670.55 | 2.48405 | 2(Loss) | true |
| glaze | 398.75 | 0.0702807 | 1335.47ms | 4604 | 30 | 1796.65 | 11011.2 | 0.140053 | 3(Loss) | true |
| simdjson (ondemand) | 365.471 | 0.133326 | 1442.17ms | 4604 | 2560 | 656799 | 12013.9 | 0.00916668 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1635.99 | 0.250252 | 274.986ms | 4604 | 2560 | 115479 | 2683.83 | 0.472486 | 1(Win) | true |
| glaze | 876.82 | 0.065459 | 539.534ms | 4604 | 160 | 1719.13 | 5007.54 | 0.0783182 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1749.76 | 0.201262 | 267.685ms | 4604 | 40 | 1020.22 | 2509.32 | 0.126368 | 1(Win) | true |
| glaze | 906.682 | 0.217031 | 539.532ms | 4604 | 2560 | 282777 | 4842.62 | 0.647839 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2140.65 | 0.0531274 | 1149.19ms | 24579 | 40 | 1353.73 | 10950.1 | 0.0508625 | 1(Win) | true |
| jsonifier (two-stage) | 1938.48 | 1.05189 | 1367.98ms | 24579 | 80 | 1.2943e+06 | 12092.1 | 0.450937 | 2(Loss) | true |
| simdjson (ondemand) | 1468.06 | 0.222986 | 1646.63ms | 24579 | 1280 | 1.62258e+06 | 15966.9 | 0.440544 | 3(Loss) | true |
| glaze | 1355.59 | 0.168803 | 1768.94ms | 24579 | 1280 | 1.09054e+06 | 17291.6 | 0.0937166 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2517.83 | 1.02771 | 1322.94ms | 24579 | 30 | 274626 | 9309.73 | 2.36813 | 1(Win) | true |
| jsonifier (two-stage) | 2407.6 | 0.189626 | 1171.23ms | 24579 | 2560 | 872560 | 9736 | 0.164525 | 2(Loss) | true |
| simdjson (ondemand) | 1691.26 | 0.0565788 | 1863.4ms | 24579 | 30 | 1844.75 | 13859.7 | 0.169748 | 3(Loss) | true |
| glaze | 1541.56 | 0.0471357 | 1720.6ms | 24579 | 30 | 1541.08 | 15205.6 | 0.0925956 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6734.04 | 0.246747 | 432.32ms | 24579 | 2560 | 188852 | 3480.88 | 0.0021659 | 1(Win) | true |
| glaze | 2404.17 | 1.03501 | 1077.96ms | 24579 | 2560 | 2.60693e+07 | 9749.87 | 1.67635 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7352.66 | 0.114666 | 340.588ms | 24579 | 160 | 2138.11 | 3188.01 | 0.245661 | 1(Win) | true |
| glaze | 3196.1 | 0.330041 | 913.317ms | 24579 | 640 | 374975 | 7334.05 | 0.776091 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 609.738 | 0.0482447 | 763.413ms | 4604 | 160 | 1931.1 | 7200.99 | 0.231144 | 1(Win) | true |
| jsonifier (two-stage) | 467.746 | 0.728016 | 1001.47ms | 4604 | 160 | 747229 | 9386.98 | 2.13963 | 2(Loss) | true |
| glaze | 343.922 | 0.0581899 | 1375.33ms | 4604 | 40 | 2207.53 | 12766.6 | 0.053031 | 3(Loss) | true |
| simdjson (ondemand) | 317.001 | 0.269061 | 1440.41ms | 4604 | 640 | 888858 | 13850.8 | 0.0433263 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 780.443 | 0.233539 | 751.479ms | 4604 | 4890 | 844140 | 5625.93 | 0.0307496 | 1(Win) | true |
| jsonifier (two-stage) | 664.447 | 0.0490779 | 864.989ms | 4604 | 160 | 1682.84 | 6608.08 | 0.144783 | 2(Loss) | true |
| glaze | 401.279 | 0.0564751 | 1569.43ms | 4604 | 30 | 1145.54 | 10941.8 | 0.0640158 | 3(Loss) | true |
| simdjson (ondemand) | 361.756 | 0.401689 | 1636.13ms | 4604 | 320 | 760624 | 12137.2 | 0.199425 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1718.94 | 0.0611977 | 271.927ms | 4604 | 320 | 781.936 | 2554.32 | 0.118322 | 1(Win) | true |
| glaze | 873.593 | 0.0469647 | 526.058ms | 4604 | 160 | 891.489 | 5026.04 | 0.104441 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1613.58 | 0.271849 | 265.875ms | 4604 | 2560 | 140083 | 2721.1 | 0.181552 | 1(Win) | true |
| glaze | 943.963 | 0.336742 | 493.56ms | 4604 | 30 | 7359.96 | 4651.37 | 0.567916 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2438.18 | 0.0774909 | 988.85ms | 24579 | 30 | 1665.02 | 9613.87 | 0.172715 | 1(Win) | true |
| jsonifier (two-stage) | 2127.47 | 0.154596 | 1134.2ms | 24579 | 30 | 8704.03 | 11018 | 0.389955 | 2(Loss) | true |
| simdjson (ondemand) | 1554.86 | 0.0390943 | 1665.19ms | 24579 | 80 | 2778.83 | 15075.5 | 0.072604 | 3(Loss) | true |
| glaze | 1417.96 | 0.0808404 | 1756.26ms | 24579 | 4890 | 873307 | 16531 | 0.76335 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2648.39 | 0.116318 | 1086.69ms | 24579 | 1280 | 135665 | 8850.79 | 0.225204 | 1(Win) | true |
| jsonifier | 2603.88 | 0.762428 | 1068.39ms | 24579 | 160 | 753710 | 9002.09 | 0.64394 | 2(Loss) | true |
| glaze | 1594.55 | 0.121897 | 1752.28ms | 24579 | 640 | 205504 | 14700.3 | 0.197585 | 3(Loss) | true |
| simdjson (ondemand) | 1558.78 | 0.419496 | 1646.79ms | 24579 | 640 | 2.5468e+06 | 15037.6 | 0.834719 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6930.25 | 0.116122 | 353.588ms | 24579 | 40 | 617.046 | 3382.32 | 0.028818 | 1(Win) | true |
| glaze | 2779.51 | 0.147774 | 938.282ms | 24579 | 40 | 6212.2 | 8433.27 | 0.146559 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7308.27 | 0.134446 | 326.63ms | 24579 | 4890 | 90929.4 | 3207.38 | 0.0807302 | 1(Win) | true |
| glaze | 3277.9 | 0.14189 | 763.987ms | 24579 | 80 | 8236.24 | 7151.04 | 0.0001748 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 720.791 | 0.345288 | 177.728ms | 1181 | 40 | 1164.4 | 1562.58 | 0.182189 | 1(Win) | true |
| jsonifier (two-stage) | 618.373 | 0.178666 | 190.147ms | 1181 | 80 | 847.174 | 1821.38 | 0.0836579 | 2(Loss) | true |
| glaze | 493.978 | 0.097012 | 236.134ms | 1181 | 80 | 391.404 | 2280.04 | 0.0104154 | 3(Loss) | true |
| simdjson (ondemand) | 417.425 | 0.31819 | 275.431ms | 1181 | 1280 | 94346.5 | 2698.19 | 0.0851992 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 905.396 | 0.182513 | 146.451ms | 1181 | 160 | 824.767 | 1243.97 | 0.190556 | 1(Win) | true |
| glaze | 821.03 | 0.46609 | 211.152ms | 1181 | 40 | 1635.24 | 1371.8 | 1.03643 | 2(Loss) | true |
| jsonifier (two-stage) | 719.405 | 0.426909 | 178.22ms | 1181 | 1280 | 57178.6 | 1565.59 | 0.298049 | 3(Loss) | true |
| simdjson (ondemand) | 647.451 | 0.137844 | 198.264ms | 1181 | 80 | 459.994 | 1739.58 | 0.00287435 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2143.47 | 0.108104 | 57.8653ms | 1181 | 1280 | 413.011 | 525.452 | 0.100556 | 1(Win) | true |
| glaze | 898.363 | 0.249811 | 128.823ms | 1181 | 2560 | 25110.6 | 1253.71 | 0.0604712 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2359.46 | 0.353256 | 51.9277ms | 1181 | 160 | 454.958 | 477.35 | 0.0523451 | 1(Win) | true |
| glaze | 1006.74 | 0.149634 | 117.039ms | 1181 | 80 | 224.19 | 1118.75 | 0.278552 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1190.17 | 0.172329 | 240.279ms | 2496 | 30 | 356.378 | 2000.03 | 0.208765 | 1(Win) | true |
| jsonifier | 1146.61 | 0.363073 | 305.631ms | 2496 | 1280 | 72719.8 | 2076 | 1.91241 | 2(Loss) | true |
| glaze | 891.249 | 0.459521 | 345.811ms | 2496 | 40 | 6025.07 | 2670.82 | 3.42227 | 3(Loss) | true |
| simdjson (ondemand) | 872.706 | 0.105347 | 289.32ms | 2496 | 80 | 660.526 | 2727.57 | 0.0979764 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1401.26 | 0.142852 | 194.677ms | 2496 | 160 | 942.207 | 1698.74 | 0.0537452 | 1(Win) | true |
| jsonifier | 1374.82 | 0.252347 | 225.822ms | 2496 | 640 | 12217.2 | 1731.4 | 0.272377 | 2(Loss) | true |
| simdjson (ondemand) | 1302.83 | 0.154227 | 207.131ms | 2496 | 40 | 317.61 | 1827.08 | 0.0406096 | 3(Loss) | true |
| glaze | 472.53 | 0.550097 | 309.362ms | 2496 | 30 | 23037.2 | 5037.5 | 0.248091 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4385.66 | 0.192015 | 81.1388ms | 2496 | 80 | 86.8922 | 542.763 | 0.00690958 | 1(Win) | true |
| glaze | 1369.39 | 0.575937 | 220.947ms | 2507 | 30 | 3033.37 | 1745.93 | 1.86309 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4835.79 | 0.0839715 | 53.0241ms | 2496 | 4890 | 835.462 | 492.24 | 0.0262429 | 1(Win) | true |
| glaze | 1689.34 | 0.0983005 | 148.478ms | 2507 | 30 | 58.0644 | 1415.27 | 0.00471076 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1951.64 | 0.0831719 | 248.564ms | 4926 | 160 | 641.303 | 2407.11 | 0.0122049 | 1(Win) | true |
| jsonifier (two-stage) | 992.723 | 0.0581458 | 492.248ms | 4926 | 80 | 605.702 | 4732.24 | 0.00501852 | 2(Loss) | true |
| glaze STATISTICAL TIE | 919.023 | 0.286477 | 525.13ms | 4926 | 1280 | 274489 | 5111.73 | 0.185656 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 918.872 | 0.0663295 | 521.007ms | 4926 | 40 | 459.994 | 5112.57 | 0.0786655 | 3(Tie) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2299.18 | 0.076291 | 244.161ms | 4926 | 80 | 194.392 | 2043.25 | 0.129864 | 1(Win) | true |
| jsonifier (two-stage) | 1238.97 | 0.136697 | 530.324ms | 4926 | 80 | 2149.19 | 3791.71 | 0.414785 | 2(Loss) | true |
| glaze | 1101.76 | 0.11797 | 474.266ms | 4926 | 30 | 759.059 | 4263.9 | 0.162086 | 3(Loss) | true |
| simdjson (ondemand) | 1068.72 | 0.117982 | 477.698ms | 4926 | 30 | 806.892 | 4395.73 | 0.0280654 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8437.08 | 0.110639 | 63.974ms | 4926 | 1280 | 485.773 | 556.804 | 0.0872083 | 1(Win) | true |
| glaze | 1406.95 | 0.544959 | 347.011ms | 4926 | 1280 | 423811 | 3339 | 0.427282 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9019.7 | 0.450178 | 58.0678ms | 4926 | 80 | 439.809 | 520.837 | 0.209235 | 1(Win) | true |
| glaze | 1831.8 | 0.132335 | 285.623ms | 4926 | 80 | 921.461 | 2564.59 | 0.405336 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2464.77 | 0.163861 | 432.595ms | 9463 | 40 | 1439.84 | 3661.45 | 0.0122917 | 1(Win) | true |
| simdjson (ondemand) | 1632.48 | 0.0982808 | 622.754ms | 9463 | 80 | 2361.5 | 5528.16 | 0.242034 | 2(Loss) | true |
| glaze | 1543.68 | 0.130042 | 647.682ms | 9463 | 4890 | 282632 | 5846.17 | 0.351343 | 3(Loss) | true |
| jsonifier (two-stage) | 1415.63 | 0.226744 | 957.129ms | 9463 | 40 | 8357.72 | 6374.98 | 0.219173 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2758.18 | 0.129149 | 378.285ms | 9463 | 40 | 714.254 | 3271.95 | 0.0931298 | 1(Win) | true |
| glaze | 1798.91 | 0.06553 | 649.59ms | 9463 | 80 | 864.587 | 5016.71 | 0.000249168 | 2(Loss) | true |
| simdjson (ondemand) | 1720.07 | 0.768075 | 527.295ms | 9463 | 160 | 259832 | 5246.66 | 1.08394 | 3(Loss) | true |
| jsonifier (two-stage) | 1543.5 | 1.28264 | 823.007ms | 9463 | 80 | 449934 | 5846.86 | 0.250117 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15381 | 0.0519852 | 62.694ms | 9463 | 2560 | 238.17 | 586.737 | 0.146481 | 1(Win) | true |
| glaze | 1956.42 | 0.845071 | 473.076ms | 9463 | 160 | 243130 | 4612.81 | 0.46581 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17349 | 0.159326 | 55.5636ms | 9463 | 640 | 439.607 | 520.181 | 0.025238 | 1(Win) | true |
| glaze | 2594.65 | 0.0734793 | 356.864ms | 9463 | 160 | 1045.08 | 3478.16 | 0.0611328 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 3263.1 | 0.176199 | 84.6678ms | 2821 | 640 | 1350.62 | 824.466 | 0.393399 | 1(Win) | true |
| jsonifier | 3139.47 | 0.447746 | 86.2939ms | 2821 | 30 | 441.651 | 856.933 | 0.155352 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 2332.55 | 3.16274 | 118.181ms | 2821 | 1280 | 1.70326e+06 | 1153.38 | 6.62597 | -(Loss) | false |
| glaze | 2159.21 | 0.0429208 | 128.855ms | 2821 | 1280 | 366.068 | 1245.97 | 0.0878311 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3634.75 | 0.123269 | 79.876ms | 2821 | 4890 | 4070.72 | 740.165 | 0.0232795 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3133.35 | 0.892351 | 92.9261ms | 2821 | 160 | 9392.47 | 858.606 | 0.395151 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3086.62 | 0.202904 | 102.59ms | 2821 | 160 | 500.429 | 871.606 | 0.0854038 | 2(Tie) | true |
| glaze | 2235.76 | 0.0393544 | 127.643ms | 2821 | 1280 | 287.047 | 1203.31 | 0.122403 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4041.14 | 0.180843 | 119.663ms | 4147 | 160 | 501.17 | 978.656 | 0.264331 | 1(Win) | true |
| jsonifier (two-stage) | 3790.54 | 0.22338 | 109.187ms | 4147 | 1280 | 6952.9 | 1043.36 | 0.217348 | 2(Loss) | true |
| simdjson (ondemand) | 3727.73 | 0.230748 | 109.862ms | 4147 | 80 | 479.452 | 1060.94 | 0.0506371 | 3(Loss) | true |
| glaze | 2764.56 | 0.255548 | 165.012ms | 4147 | 30 | 400.944 | 1430.57 | 0.883853 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4153.83 | 0.140585 | 106.254ms | 4147 | 160 | 286.662 | 952.106 | 0.704611 | 1(Win) | true |
| jsonifier | 4031.99 | 0.165185 | 109.964ms | 4147 | 4890 | 12837.5 | 980.878 | 1.01286 | 2(Loss) | true |
| simdjson (ondemand) | 3872.22 | 0.265687 | 118.626ms | 4147 | 160 | 1178.18 | 1021.35 | 0.511735 | 3(Loss) | true |
| glaze | 3113 | 0.0973661 | 138.491ms | 4147 | 320 | 489.639 | 1270.44 | 0.00885439 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2192.04 | 0.144221 | 127.418ms | 2821 | 160 | 501.285 | 1227.31 | 0.0641234 | 1(Win) | true |
| glaze | 1710.98 | 0.122326 | 166.096ms | 2821 | 320 | 1183.87 | 1572.38 | 0.297427 | 2(Loss) | true |
| jsonifier (two-stage) | 1580.54 | 0.396512 | 222.137ms | 2821 | 40 | 1822.08 | 1702.15 | 0.449485 | 3(Loss) | true |
| simdjson (ondemand) | 1402.79 | 0.445747 | 241.318ms | 2821 | 640 | 46771.3 | 1917.84 | 0.047964 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2224.06 | 0.66189 | 144.654ms | 2821 | 160 | 10256.7 | 1209.64 | 1.10802 | 1(Win) | true |
| jsonifier (two-stage) | 1900.48 | 0.861772 | 259.979ms | 2821 | 80 | 11905.7 | 1415.6 | 1.72098 | 2(Loss) | true |
| glaze | 1832.83 | 0.699446 | 191.834ms | 2821 | 640 | 67460.6 | 1467.85 | 2.12764 | 3(Loss) | true |
| simdjson (ondemand) | 1694.71 | 0.468138 | 216.766ms | 2821 | 40 | 2209.13 | 1587.47 | 0.353085 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9258.59 | 0.359021 | 35.6682ms | 2821 | 40 | 43.5327 | 290.575 | 0.106224 | 1(Win) | true |
| glaze | 2647.34 | 0.602766 | 135.353ms | 2819 | 320 | 11989.9 | 1015.51 | 0.21372 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11428.7 | 1.49674 | 30.271ms | 2821 | 40 | 496.554 | 235.4 | 0.885714 | 1(Win) | true |
| glaze | 3059.8 | 0.759724 | 103.597ms | 2819 | 4890 | 217884 | 878.623 | 2.73407 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 1885.74 | 1.50246 | 213.622ms | 4147 | 640 | 635464 | 2097.27 | 0.0873924 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 1874.91 | 0.387896 | 215.683ms | 4147 | 1280 | 85693.7 | 2109.38 | 0.803089 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1836.97 | 0.262625 | 224.765ms | 4147 | 2560 | 81842.1 | 2152.94 | 0.107079 | 1(Tie) | true |
| simdjson (ondemand) | 1786.51 | 0.426579 | 263.89ms | 4147 | 1280 | 114148 | 2213.75 | 0.762332 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2532.94 | 0.111416 | 221.317ms | 4147 | 320 | 968.425 | 1561.38 | 0.358567 | 1(Win) | true |
| jsonifier (two-stage) | 2312.15 | 0.250374 | 185.997ms | 4147 | 2560 | 46952.3 | 1710.48 | 0.387931 | 2(Loss) | true |
| glaze | 2054.66 | 0.186177 | 213.548ms | 4147 | 4890 | 62798.4 | 1924.84 | 0.452722 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1490.36 | 6.12217 | 279.438ms | 4147 | 4890 | 1.29063e+08 | 2653.64 | 9.19343 | -(Loss) | false |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12531.1 | 0.134705 | 36.6964ms | 4147 | 2560 | 462.695 | 315.606 | 0.243055 | 1(Win) | true |
| glaze | 2604.24 | 0.296503 | 176.71ms | 4145 | 2560 | 51854.3 | 1517.9 | 0.200849 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14988.2 | 1.38022 | 35.2142ms | 4147 | 30 | 397.913 | 263.867 | 1.04672 | 1(Win) | true |
| glaze | 3876.72 | 0.125162 | 129.909ms | 4145 | 320 | 521.212 | 1019.67 | 0.417198 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2087.44 | 0.579774 | 11233ms | 466906 | 80 | 1.2236e+08 | 213312 | 0.168716 | 1(Win) | true |
| glaze | 1428.67 | 0.738973 | 8859.58ms | 466906 | 160 | 8.48735e+08 | 311672 | 1.0064 | 2(Loss) | true |
| simdjson (ondemand) | 595.628 | 2.94821 | 5979.42ms | 466906 | 320 | 1.55445e+11 | 747574 | 0.366283 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze DID NOT CONVERGE | 1415.4 | 0.50777 | 8194.85ms | 466906 | 1280 | 3.26619e+09 | 314593 | 5.53293 | -(Win) | false |
| jsonifier DID NOT CONVERGE | 982.168 | 7.84708 | 5816.62ms | 466906 | 40 | 5.06249e+10 | 453361 | 15.6756 | -(Loss) | false |
| simdjson (ondemand) | 685.068 | 0.427989 | 8547.85ms | 466906 | 160 | 1.23816e+09 | 649974 | 0.505082 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3294.63 | 0.364672 | 5190.43ms | 699405 | 320 | 1.74422e+08 | 202452 | 0.278486 | 1(Win) | true |
| glaze | 2228.05 | 0.166134 | 8979.95ms | 699405 | 30 | 7.42066e+06 | 299367 | 0.969891 | 2(Loss) | true |
| simdjson (ondemand) | 447.967 | 1.10753 | 5049.03ms | 767297 | 160 | 5.23683e+10 | 1.6335e+06 | 0.875092 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3222.95 | 0.504074 | 5927.96ms | 699405 | 80 | 8.70621e+07 | 206955 | 1.55992 | 1(Win) | true |
| glaze | 1782.62 | 1.54769 | 10100.6ms | 699405 | 40 | 1.34143e+09 | 374172 | 4.49743 | 2(Loss) | true |
| simdjson (ondemand) | 533.691 | 1.55167 | 5032.66ms | 767297 | 80 | 3.62105e+10 | 1.37111e+06 | 1.6635 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1956.52 | 0.480606 | 8542.96ms | 631514 | 1280 | 2.80147e+09 | 307822 | 1.58035 | 1(Win) | true |
| glaze | 1490.62 | 0.848783 | 5612.11ms | 631514 | 640 | 7.52676e+09 | 404034 | 3.57532 | 2(Loss) | true |
